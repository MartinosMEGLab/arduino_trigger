int value = 0;
float value1 = 0.;
float sampledValue = 0.0;
void setup() {
  Serial.begin(9600);
  DDRD = B11111111;
}

void loop() {
  for (int i = 0; i < 360; i++) {
    value1 = sin(i * DEG_TO_RAD) + 1;
    value = ( value1 * 255.0) / 2.0;
  
    PORTD = value;
    delay(5);
//    Serial.print(value1);
//    Serial.print(",");
    sampledValue = analogRead(A0) * 255.0 / 1008.0;
    
    Serial.print(value);
    Serial.print(",");
    Serial.println(sampledValue);
  }
}

