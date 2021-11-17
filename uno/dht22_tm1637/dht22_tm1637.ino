#include <DHT.h>
#define DHTPIN 2 // номер пина, к которому подсоединен датчик

#define CLK 5
#define DIO 4
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);

// Раскомментируйте в соответствии с используемым датчиком

// Инициируем датчик

DHT dht(DHTPIN, DHT22);

//DHT dht(DHTPIN, DHT11, 1);

void setup() {
  Serial.begin(9600);
  dht.begin();

  disp.clear();
  disp.brightness(1);  // яркость, 0 - 7 (минимум - максимум)
  disp.clear();
  disp.displayByte(_H, _E, _L, _L);
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

    //void point(boolean PointFlag);                      // вкл / выкл точку (POINT_ON / POINT_OFF)
    //void displayByte(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3);  // если лень создавать массив, выводит байты в ячейки

    disp.displayInt(t);

}
