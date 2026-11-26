// Planta Costa Norte - Nodo 5: Gateway (fog)
// Instalacion heredada del proveedor anterior
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#include <time.h>
#include "mbedtls/md.h"

const char* CLAVE  = "costa-norte-gc-6402";
const char* TS_KEY = "TU_WRITE_KEY";     // clave de escritura de ThingSpeak

const int PIN_PIXEL = 5, PIN_ACK = 13;
const float UMBRAL_GAS = 2000;           // ppm

Adafruit_NeoPixel pixel(1, PIN_PIXEL, NEO_GRB + NEO_KHZ800);
WiFiClient net;
PubSubClient mqtt(net);

// Cada lectura guarda cuando llego (millis); una lectura vieja no decide nada
struct Lectura {
  float valor = 0;
  unsigned long rxMs = 0;
  bool recibida = false;
};
Lectura pozas, secadores, perimetro;
int viento = 0;
bool lavadorOn = false, alerta = false;
bool ordenPendiente = false;                // ON/OFF enviada, esperando confirmacion de N4
unsigned long tOrden = 0;
const unsigned long T_CONF_LAVADOR = 10000; // R5
const unsigned long CADUCIDAD_MS = 10000;   // decision del grupo, no de la especificacion

bool fresco(const Lectura& l) {
  return l.recibida && millis() - l.rxMs < CADUCIDAD_MS;
}

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

// Orden firmada para N1: "<comando>|<ts>|<firma>", firma = HMAC("pozas|<comando>|<ts>")
String ordenPozas(const String& comando) {
  long ts = time(nullptr);
  return comando + "|" + String(ts) + "|" + firmar("pozas|" + comando + "|" + String(ts));
}

// Estado real del lavador: lo publica N4 (CONFIRMADO tras encender, OFF al apagar)
void procesarEstadoLavador(const String& msg) {
  Serial.println("Estado lavador: " + msg);
  if (msg.indexOf("CONFIRMADO") >= 0) {
    lavadorOn = true;
    ordenPendiente = false;
    Serial.println("Lavador CONFIRMADO: ON");
  } else if (msg.indexOf("\"lavador\":\"OFF\"") >= 0) {
    lavadorOn = false;
    ordenPendiente = false;
    Serial.println("Lavador confirmado: OFF");
  }
}

// Extrae el texto de un campo del JSON
String campo(const String& m, const char* k) {
  String key = "\"" + String(k) + "\":";
  int i = m.indexOf(key);
  if (i < 0) return "";
  i += key.length();
  int j = i;
  while (j < (int)m.length() && m[j] != ',' && m[j] != '}') j++;
  return m.substring(i, j);
}

String sinComillas(String s) { s.replace("\"", ""); return s; }

void alRecibir(char* t, byte* p, unsigned int n) {
  String msg;
  for (unsigned int i = 0; i < n; i++) msg += (char)p[i];
  String topico(t);

  if (topico.endsWith("/alerta")) {
    alerta = true;
    Serial.println("ALERTA: " + msg);
    mqtt.publish("upc/gc/pozas/cmd", ordenPozas("VENT:MAX").c_str());   // respuesta de respaldo
    return;
  }
  if (topico.endsWith("/estado")) {
    procesarEstadoLavador(msg);
    return;
  }

  String id    = sinComillas(campo(msg, "id"));
  long ts      = campo(msg, "ts").toInt();
  String valor = campo(msg, "valor");
  String firma = sinComillas(campo(msg, "firma"));

  if (firma != firmar(id + "|" + String(ts) + "|" + valor)) {
    Serial.println("RECHAZADO (firma invalida): " + id);
    return;
  }
  // Hora real y ventana de 60 s en ambos sentidos (R9; misma regla que N1).
  // Simetrica porque los relojes de los nodos pueden ir adelantados o atrasados.
  long ahora = time(nullptr);
  if (ahora < 1700000000) {
    Serial.println("RECHAZADO: hora no sincronizada");
    return;
  }
  if (ts <= 0 || abs(ahora - ts) > 60) {
    Serial.println("RECHAZADO: timestamp invalido " + id);
    return;
  }

  float v = valor.toFloat();
  Lectura nueva = {v, millis(), true};
  if (id == "pozas") pozas = nueva;
  else if (id == "secadores") secadores = nueva;
  else if (id == "perimetro") {
    perimetro = nueva;
    viento = campo(msg, "viento").toInt();
  }
  Serial.println("OK " + id + ": " + String(v, 1) + " ppm");
}

void conectar() {
  while (WiFi.status() != WL_CONNECTED) delay(200);
  while (!mqtt.connected()) {
    String id = "gc-gateway-" + WiFi.macAddress();
    if (mqtt.connect(id.c_str())) {
      mqtt.subscribe("upc/gc/+/dato");
      mqtt.subscribe("upc/gc/lavador/estado");
      mqtt.subscribe("upc/gc/lavador/alerta");
      Serial.println("Gateway conectado");
    } else {
      delay(1000);
    }
  }
}

void enviarThingSpeak() {
  if (String(TS_KEY) == "TU_WRITE_KEY") return;
  HTTPClient http;
  http.begin("http://api.thingspeak.com/update?api_key=" + String(TS_KEY) +
             "&field1=" + String(pozas.valor) + "&field2=" + String(secadores.valor) +
             "&field3=" + String(perimetro.valor) + "&field4=" + String(viento) +
             "&field5=" + String(lavadorOn ? 1 : 0));
  http.GET();
  http.end();
}

void setup() {
  Serial.begin(115200);
  pixel.begin();
  pinMode(PIN_ACK, INPUT_PULLUP);
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) delay(200);

  // Hora real por NTP; espera acotada para no bloquear para siempre
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  unsigned long t0 = millis();
  while (time(nullptr) < 1700000000 && millis() - t0 < 15000) delay(200);
  if (time(nullptr) < 1700000000) Serial.println("Sin hora NTP: se rechazaran datos");

  mqtt.setServer("broker.hivemq.com", 1883);
  mqtt.setBufferSize(512);
  mqtt.setKeepAlive(60);
  mqtt.setCallback(alRecibir);
  conectar();
}

unsigned long tDecision = 0, tNube = 0;

void loop() {
  if (!mqtt.connected()) conectar();
  mqtt.loop();

  if (digitalRead(PIN_ACK) == LOW && alerta) {
    alerta = false;
    Serial.println("Alerta reconocida por el operador");
  }

  // R5: sin confirmacion en 10 s, falla del lavador y ventilacion maxima
  if (ordenPendiente && millis() - tOrden > T_CONF_LAVADOR) {
    ordenPendiente = false;
    alerta = true;
    Serial.println("ALERTA: falla del lavador (sin confirmacion en 10 s)");
    mqtt.publish("upc/gc/pozas/cmd", ordenPozas("VENT:MAX").c_str());
  }

  if (millis() - tDecision >= 2000) {
    tDecision = millis();
    bool pozasOK = fresco(pozas), secOK = fresco(secadores), perOK = fresco(perimetro);
    bool todosFrescos = pozasOK && secOK && perOK;
    bool haciaComunidad = perOK && viento >= 90 && viento <= 180;
    // Solo cuentan los sensores frescos; un dato caducado no confirma nada
    int confirmaciones = (pozasOK && pozas.valor > UMBRAL_GAS) +
                         (secOK && secadores.valor > UMBRAL_GAS) +
                         (perOK && perimetro.valor > UMBRAL_GAS);
    float conc = 0;
    if (pozasOK) conc = max(conc, pozas.valor);
    if (secOK) conc = max(conc, secadores.valor);
    if (perOK) conc = max(conc, perimetro.valor);
    mqtt.publish("upc/gc/gateway/conc", String(conc, 1).c_str());

    // Regla combinada (fog)
    if (!lavadorOn && !ordenPendiente && confirmaciones >= 2 && haciaComunidad) {
      mqtt.publish("upc/gc/lavador/cmd", "ON", true);
      ordenPendiente = true;
      tOrden = millis();
      Serial.println("Orden: lavador ON (esperando confirmacion)");
    } else if (lavadorOn && !ordenPendiente && todosFrescos && conc < UMBRAL_GAS * 0.8) {
      mqtt.publish("upc/gc/lavador/cmd", "OFF", true);
      ordenPendiente = true;
      tOrden = millis();
      Serial.println("Orden: lavador OFF (esperando confirmacion)");
    }

    // Semaforo general de la planta
    if (alerta || lavadorOn) pixel.setPixelColor(0, pixel.Color(255, 0, 0));
    else if (confirmaciones >= 1) pixel.setPixelColor(0, pixel.Color(255, 150, 0));
    else pixel.setPixelColor(0, pixel.Color(0, 255, 0));
    pixel.show();
  }

  if (millis() - tNube >= 20000) {
    tNube = millis();
    enviarThingSpeak();
  }
}
