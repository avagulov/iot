#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int LED = D1;
int SERIAL_BAND = 9600;
int LOOP_DELAY = 10000;

const char* SID    = "TC139";
const char* PASSWORD = "9197615070";

void setup()
{
  Serial.begin(SERIAL_BAND);
  pinMode(LED, OUTPUT);

  initWiFi();

  WiFiClient client;
  HTTPClient http;

  String serverPath = "http://ys.ru";

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverPath.c_str());

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}

void loop() {
  if(statusWiFi()){
    
  }

  delay(LOOP_DELAY);
}

bool statusWiFi(){
  switch (WiFi.status()) {
    case WL_CONNECTED:
      Serial.println("Connection successfully established");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP()); // показывает наше IP

      digitalWrite(LED, LOW);
      return true;
      break;
    case WL_NO_SSID_AVAIL:
      Serial.println("Configured SSID cannot be reached");
      digitalWrite(LED, LOW);
      break;
    case WL_CONNECT_FAILED:
      Serial.println("Connection failed");
      digitalWrite(LED, LOW);
      break;
  }

  return false;
}

void initWiFi() {
  //Включаем светодиод, горит, значит подключается
  digitalWrite(LED, HIGH);

  Serial.print("Connecting to ");
  Serial.println(SID);

  WiFi.mode(WIFI_STA); // Задаем режим работы WIFI_STA (клиент)
  WiFi.begin(SID, PASSWORD); // Подключаемся

  //The ESP8266 tries to reconnect automatically when the connection is lost
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}
