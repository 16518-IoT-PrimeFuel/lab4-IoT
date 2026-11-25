// Planta Costa Norte - Nodo 4: Lavador de gases
// F1 y F2 corregidos por Schneider Delgado, F3 corregido por Carlos Lopez
#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include "mbedtls/md.h"

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASS = "";
const char* BROKER    = "broker.hivemq.com";

const char* T_CMD    = "upc/gc/lavador/cmd";
const char* T_CONC   = "upc/gc/gateway/conc";
const char* T_ESTADO = "upc/gc/lavador/estado";
const char* T_ALERTA = "upc/gc/lavador/alerta";

const int PIN_RELE   = 26;   // F1
const int PIN_CONF   = 14;
const int PIN_STEP   = 18;
const int PIN_DIR    = 19;

const unsigned long T_CONFIRMACION = 10000;
const unsigned long T_MODO_SEGURO  = 60000;
const float CONC_ALTA = 2000.0;   // ppm

const char* CLAVE = "costa-norte-gc-6402"; // misma clave de grupo usada en N1 y N5

WiFiClient net;
PubSubClient mqtt(net);

bool lavadorOn = false;
int intensidad = 1;
float concentracion = 0;
unsigned long tOrden = 0;
unsigned long ultimoContacto = 0;
unsigned long tPaso = 0;
bool esperandoConf = false;
bool modoSeguro = false;

void publicar(const char* topico, String msg) {
  mqtt.publish(topico, msg.c_str());
  Serial.println(String(topico) + " -> " + msg);
}

void encender(const char* motivo) {
  lavadorOn = true;
  digitalWrite(PIN_RELE, HIGH);
  tOrden = millis();
  esperandoConf = true;
  publicar(T_ESTADO, String("{\"lavador\":\"ON\",\"motivo\":\"") + motivo + "\"}");
}

void apagar(const char* motivo) {
  lavadorOn = false;
  digitalWrite(PIN_RELE, LOW);
  esperandoConf = false;
  publicar(T_ESTADO, String("{\"lavador\":\"OFF\",\"motivo\":\"") + motivo + "\"}");
}

// F3: firma HMAC-SHA256 truncada a 8 bytes, mismo formato que el resto del grupo
String firmar(const String& m) {
  byte out[32];
  mbedtls_md_context_t c;
  mbedtls_md_init(&c);
  mbedtls_md_setup(&c, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1);
  mbedtls_md_hmac_starts(&c, (const unsigned char*)CLAVE, strlen(CLAVE));
  mbedtls_md_hmac_update(&c, (const unsigned char*)m.c_str(), m.length());
  mbedtls_md_hmac_finish(&c, out);
  mbedtls_md_free(&c);
  char h[17];
  for (int i = 0; i < 8; i++) sprintf(h + 2 * i, "%02x", out[i]);
  return String(h);
}

// F3: valida antiguedad (mismo criterio que R9, 60 s) y firma sobre "lavador|<comando>|<ts>"
bool ordenValida(const String& comando, long ts, const String& firmaRecibida) {
  if (abs((long)time(nullptr) - ts) > 60) return false;
  String base = "lavador|" + comando + "|" + String(ts);
  return firmar(base) == firmaRecibida;
}

void girarMotor() {
  if (!lavadorOn) return;
  unsigned long periodo = 4000 / intensidad;   // microsegundos entre pasos
  if (micros() - tPaso >= periodo) {
    tPaso = micros();
    digitalWrite(PIN_STEP, !digitalRead(PIN_STEP));
  }
}

void alRecibir(char* topic, byte* payload, unsigned int len) {
  String msg;
  for (unsigned int i = 0; i < len; i++) msg += (char)payload[i];
  msg.trim();
  String t = String(topic);

  if (t == T_CONC) {
    concentracion = msg.toFloat();
    ultimoContacto = millis();
    modoSeguro = false;
    return;
  }

  if (t != T_CMD) return;

  // F3: formato nuevo obligatorio, "<comando>|<ts>|<firma>"
  int p1 = msg.indexOf('|');
  int p2 = msg.lastIndexOf('|');
  if (p1 < 0 || p2 <= p1) {
    publicar(T_ALERTA, "{\"alerta\":\"orden rechazada: formato\"}");
    return;
  }

  String comando = msg.substring(0, p1);
  long ts = msg.substring(p1 + 1, p2).toInt();
  String firma = msg.substring(p2 + 1);

  if (!ordenValida(comando, ts, firma)) {
    publicar(T_ALERTA, "{\"alerta\":\"orden rechazada: firma invalida o vencida\"}");
    return;
  }

  // Solo una orden ya validada cuenta como contacto real con el gateway (R6)
  ultimoContacto = millis();
  modoSeguro = false;

  if (comando == "ON") {
    encender("orden gateway");
  } else if (comando == "OFF") {
    // F3 / R7: el lavador no se apaga mientras la concentracion sea alta,
    // ni siquiera con una orden ya validada
    if (concentracion >= CONC_ALTA) {
      publicar(T_ALERTA, "{\"alerta\":\"orden OFF ignorada: concentracion alta\"}");
    } else {
      apagar("orden gateway");
    }
  } else if (comando.startsWith("INT:")) {
    intensidad = constrain(comando.substring(4).toInt(), 1, 5);
    publicar(T_ESTADO, "{\"intensidad\":" + String(intensidad) + "}");
  }
}

void conectar() {
  static unsigned long ultimoIntento = 0;

  if (WiFi.status() != WL_CONNECTED || mqtt.connected()) return;
  if (millis() - ultimoIntento < 5000) return;

  ultimoIntento = millis();
  String id = "gc-lavador-" + String(random(0xffff), HEX);

  if (mqtt.connect(id.c_str())) {
    mqtt.subscribe(T_CMD);
    mqtt.subscribe(T_CONC);
    publicar(T_ESTADO, "{\"nodo\":\"lavador\",\"estado\":\"online\"}");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_CONF, INPUT);
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  digitalWrite(PIN_DIR, HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(200);

  // F3: necesario para que la validacion de antiguedad del timestamp tenga sentido
  configTime(0, 0, "pool.ntp.org");
  for (int i = 0; i < 50 && time(nullptr) < 1700000000; i++) delay(200);

  mqtt.setServer(BROKER, 1883);
  mqtt.setCallback(alRecibir);
  mqtt.setKeepAlive(60);
  mqtt.setSocketTimeout(2);
  conectar();
  ultimoContacto = millis();
}

void loop() {
  if (!mqtt.connected()) conectar();
  mqtt.loop();

  // Lazo cerrado: confirmacion de funcionamiento
  if (esperandoConf) {
    if (digitalRead(PIN_CONF) == HIGH) {
      esperandoConf = false;
      publicar(T_ESTADO, "{\"lavador\":\"CONFIRMADO\"}");
    } else if (millis() - tOrden > T_CONFIRMACION) {
      esperandoConf = false;
      publicar(T_ALERTA, "{\"alerta\":\"falla del lavador\"}");
    }
  }

  // F2: modo seguro sin contacto real con el gateway
  if (!modoSeguro && millis() - ultimoContacto >= T_MODO_SEGURO) {
    modoSeguro = true;
    Serial.println("[F2] Activando modo seguro tras 60 segundos");
    encender("modo seguro");
  }

  girarMotor();
}
