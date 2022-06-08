int value = 0;
int triggerWidth = 30;

void setup() {
  Serial.begin(9600);
  DDRD = B11111111;
}


void loop() {
  sendTrigger(value);
  delay(100);
  value += 10;
  if(value >255) {
    value = 0;
  }
}

void sendTrigger(int x) {
  PORTD = x;
  delay(triggerWidth);
  PORTD = 0;
}

