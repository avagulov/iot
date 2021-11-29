#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

const int WIFI_LED = D1;
const int SEND_LED = D2;
const int SENSOR = D3;
const int SERIAL_BAND = 9600;
const int LOOP_DELAY = 1000;

DHT dht(SENSOR, DHT22);

const char* SID1    = "TC139";
const char* SID2    = "OnePlus";
const char* PASSWORD = "9197615070";
const String HOST = "185.165.162.35:8080";
const int HOUSE_ID = 1;
const int TEMP_SENSOR_ID = 1;
const int HUM_SENSOR_ID = 2;
const String TEMP_POST_URL = "http://" + HOST + "/v1/telemetry/" + HOUSE_ID + "/" + TEMP_SENSOR_ID + "/measurements/";
const String HUM_POST_URL = "http://" + HOST + "/v1/telemetry/" + HOUSE_ID + "/" + HUM_SENSOR_ID + "/measurements/";
const int DEEP_SLEEP = 300e6; //300 cек

ESP8266WiFiMulti wifiMulti;

void setup()
{
  Serial.begin(SERIAL_BAND);
  pinMode(WIFI_LED, OUTPUT);
  pinMode(SEND_LED, OUTPUT);

  dht.begin();

  initWiFi();
}

void loop() {
  if (statusWiFi()) {
    //Считываем влажность
    float h = dht.readHumidity();
    // Считываем температуру
    float t = dht.readTemperature(false);

    Serial.printf("H = %2.1f\n", h);
    Serial.printf("T = %2.1f\n", t);

    digitalWrite(SEND_LED, HIGH);

    WiFiClient client;
    HTTPClient http;

    //---- TEMP

    http.begin(client, TEMP_POST_URL);
    http.addHeader("Content-Type", "application/json");
    Serial.println(TEMP_POST_URL);

    String val = "{ \"value\" : " + String(t, 1) + " }";
    Serial.println(val);

    int httpResponseCode = http.POST(val);
    Serial.println("HTTP Response code: " + String(httpResponseCode));

    //---- HUM

    Serial.println("Sending HUM");

    http.begin(client, HUM_POST_URL);
    http.addHeader("Content-Type", "application/json");
    Serial.println(HUM_POST_URL);

    val = "{ \"value\" : " + String(h, 1) +  "}";
    Serial.println(val);

    httpResponseCode = http.POST(val);
    Serial.println("HTTP Response code: " + String(httpResponseCode));

    // Free resources
    http.end();

    delay(1000);
    digitalWrite(SEND_LED, LOW);
    
    Serial.println("Deep Sleep");
    WiFi.disconnect();
    ESP.deepSleep(DEEP_SLEEP);
  }

  delay(LOOP_DELAY);
}

bool statusWiFi() {
  switch (WiFi.status()) {
    case WL_CONNECTED:
      Serial.println("Connection successfully established");
      WiFi.printDiag(Serial);

      digitalWrite(WIFI_LED, LOW);
      return true;
      break;
    case WL_NO_SSID_AVAIL:
      Serial.println("Configured SSID cannot be reached");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("Connection failed");
      break;
  }

  return false;
}

void initWiFi() {
  //Включаем светодиод, горит, значит подключается
  digitalWrite(WIFI_LED, HIGH);

  Serial.println("Connecting to WiFi");

  WiFi.mode(WIFI_STA); // Задаем режим работы WIFI_STA (клиент)
  
  wifiMulti.addAP(SID2, PASSWORD);
  wifiMulti.addAP(SID1, PASSWORD);
  
  wifiMulti.run();

  //The ESP8266 tries to reconnect automatically when the connection is lost
  //WiFi.setAutoReconnect(true);
  //WiFi.persistent(true);
}
