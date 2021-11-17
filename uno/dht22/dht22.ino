#include <DHT.h>
#define DHTPIN 2 // номер пина, к которому подсоединен датчик

// Раскомментируйте в соответствии с используемым датчиком

// Инициируем датчик

DHT dht(DHTPIN, DHT22);

//DHT dht(DHTPIN, DHT11, 1);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {

//  Serial.print("test\r\n");

//    Serial.print(h);
//    // Задержка 2 секунды между измерениями
//    
    delay(2000);
    
    //Считываем влажность
    float h = dht.readHumidity();
    // Считываем температуру
    float t = dht.readTemperature(false);
    // Проверка удачно прошло ли считывание.
    if (isnan(h) || isnan(t)) {
      Serial.println("Не удается считать показания");
      return;
    }
    //Serial.print("Влажность: " + h + " %\t" + "Температура: " + t + " *C ");

    Serial.print("H");
    Serial.print(h);
    Serial.print("\r\n");
    
    Serial.print("T");
    Serial.print(t);
    Serial.print("\r\n");
}
