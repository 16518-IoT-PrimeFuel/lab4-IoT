// Planta Costa Norte - Nodo 1: Pozas de materia prima
// Version corregida por el equipo PrimeFuel (G3, prefijo gc)
//   F1 (visible)    temperatura en Celsius (DS18B20)
//   F2 (silenciosa) accion local autonoma: temp OR gas, sin bloquear por WiFi/MQTT, sin publicar sin hora NTP
//   F3 (seguridad)  ordenes firmadas HMAC y con antiguedad < 60 s (R10)
#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <time.h>
#include "mbedtls/md.h"

const char* CLAVE    = "costa-norte-gc-6402";
const char* T_DATOS  = "upc/gc/pozas/datos";
const char* T_CMD    = "upc/gc/pozas/cmd";
const char* T_ALERTA = "upc/gc/pozas/alerta";

const int PIN_GAS = 34, PIN_TEMP = 4, PIN_BUZZER = 25, PIN_VENT = 26;
float umbralGas = 2000;       // ppm (R1)
const float UMBRAL_T = 35;    // grados C (R1)
bool ventMax = false;

WiFiClient net;
PubSubClient mqtt(net);
OneWire bus(PIN_TEMP);
DallasTemperature sensor(&bus);

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

void alertar(const String& texto) {
  Serial.println(texto);
  if (mqtt.connected()) mqtt.publish(T_ALERTA, ("{\"alerta\":\"" + texto + "\"}").c_str());
}

// F3: misma convencion que N4 Lavador -> "<comando>|<ts>|<firma>",
// firma = HMAC("pozas|<comando>|<ts>"), antiguedad maxima 60 s
bool ordenValida(const String& comando, long ts, const String& firma) {
  if (abs((long)time(nullptr) - ts) > 60) return false;
  return firmar("pozas|" + comando + "|" + String(ts)) == firma;
}

void alRecibir(char* t, byte* p, unsigned int n) {
  String msg;
  for (unsigned int i = 0; i < n; i++) msg += (char)p[i];
  msg.trim();

  int p1 = msg.indexOf('|');
  int p2 = msg.lastIndexOf('|');
  if (p1 < 0 || p2 <= p1) { alertar("Orden rechazada: formato"); return; }

  String comando = msg.substring(0, p1);
  long ts = msg.substring(p1 + 1, p2).toInt();
  String firma = msg.substring(p2 + 1);
  if (!ordenValida(comando, ts, firma)) { alertar("Orden rechazada: firma invalida o vencida"); return; }

  if (comando.startsWith("UMBRAL:")) {
    float nuevo = comando.substring(7).toFloat();
    if (nuevo < 500 || nuevo > 5000) { alertar("Orden rechazada: umbral fuera de rango"); return; }
    umbralGas = nuevo;
    Serial.println("Nuevo umbral de gas: " + String(umbralGas));
  } else if (comando == "VENT:MAX") {
    ventMax = true;
    Serial.println("Orden aceptada: VENT:MAX");
  } else if (comando == "VENT:NORMAL") {
    ventMax = false;
    Serial.println("Orden aceptada: VENT:NORMAL");
  }
}

// F2: reconexion sin bloqueo (un intento cada 5 s); el loop sigue leyendo y actuando
unsigned long tReintento = 0;
void conectar() {
  if (mqtt.connected() || WiFi.status() != WL_CONNECTED) return;
  if (tReintento != 0 && millis() - tReintento < 5000) return;
  tReintento = millis();
  String id = "gc-pozas-" + WiFi.macAddress();
  if (mqtt.connect(id.c_str())) {
    mqtt.subscribe(T_CMD);
    Serial.println("MQTT conectado");
  } else {
    Serial.println("MQTT sin conexion, reintento en 5 s");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_VENT, OUTPUT);
  sensor.begin();
  WiFi.begin("Wokwi-GUEST", "");
  for (int i = 0; i < 50 && WiFi.status() != WL_CONNECTED; i++) delay(200);
  configTime(0, 0, "pool.ntp.org");
  for (int i = 0; i < 50 && time(nullptr) < 1700000000; i++) delay(200);
  mqtt.setServer("broker.hivemq.com", 1883);
  mqtt.setBufferSize(512);
  mqtt.setKeepAlive(60);
  mqtt.setCallback(alRecibir);
  conectar();
}

unsigned long tPub = 0;

void loop() {
  conectar();
  if (mqtt.connected()) mqtt.loop();
  if (millis() - tPub < 2000) return;
  tPub = millis();

  float gas = analogRead(PIN_GAS) * 10000.0 / 4095.0;
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);   // F1: Celsius, no Fahrenheit

  // F2 / R2: accion local (edge) -> gas O temperatura, sin esperar al gateway
  bool ventilar = (gas > umbralGas) || (temp > UMBRAL_T) || ventMax;
  digitalWrite(PIN_VENT, ventilar);
  if (gas > umbralGas || temp > UMBRAL_T) tone(PIN_BUZZER, 1000); else noTone(PIN_BUZZER);
  Serial.println("Gas: " + String(gas, 1) + " ppm | Temp: " + String(temp, 1) +
                 " C | Ventilacion: " + (ventilar ? "ON" : "OFF"));

  long ts = time(nullptr);
  if (!mqtt.connected() || ts < 1700000000) {   // F2 / R9: sin broker u hora valida no se publica
    Serial.println("Sin broker u hora valida: no se publica");
    return;
  }

  String v = String(gas, 1) + "ppm";
  String msg = "{\"id\":\"pozas\",\"ts\":" + String(ts) + ",\"valor\":\"" + v +
               "\",\"unidad\":\"ppm\",\"temp\":" + String(temp, 1) +
               ",\"calidad\":\"ok\",\"firma\":\"" + firmar("pozas|" + String(ts) + "|" + v) + "\"}";
  mqtt.publish(T_DATOS, msg.c_str());
  Serial.println(msg);
}
