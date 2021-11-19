#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

void setup()
 {
 Serial.begin(9600);
 const char* ssid     = "TC139";
 const char* password = "9197615070";
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.mode(WIFI_STA); // Задаем режим работы WIFI_STA (клиент)
 WiFi.begin(ssid, password); // Подключаемся
 while (WiFi.status() != WL_CONNECTED) // Ждем пока статус не станет WL_CONNECTED
 {
 delay(500);
 }
 Serial.println("WiFi connected");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP()); // показывает наше IP


  WiFiClient client;
  HTTPClient http;

  String serverPath = "http://ys.ru";
  
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverPath.c_str());
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
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
 
 void loop()
 {}
