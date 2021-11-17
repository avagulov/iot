#define CLK 5
#define DIO 4
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
uint32_t Now, clocktimer;
boolean flag;
void setup() {
  Serial.begin(9600);
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  disp.clear();
  disp.displayByte(_H, _E, _L, _L);
}
void loop(){}
