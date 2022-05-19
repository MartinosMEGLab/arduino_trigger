int value = 0;
float value1 = 0;

void setup() {
  Serial.begin(9600);
  DDRD = B11111111;
}

void loop() {
  for (int i = 1; i < 255; i++) {

    PORTD = i;
    Serial.print(i);
    Serial.print(",");
    Serial.println(analogRead(A0));
  }
}
