#define LED 16

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(2000);

  Serial.print(HIGH);
    Serial.print("--");
      Serial.print(LOW);
}
