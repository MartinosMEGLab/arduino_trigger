

int rightChannelPin = 9;
int leftChannelPin = 10;

int leftChannelBrightness = 0;
int rightChannelBrightness = 0;
bool newCommandAvailable = false;

void setup() {
  pinMode(rightChannelPin, OUTPUT);
  pinMode(leftChannelPin, OUTPUT);
  delay(100);
  analogWrite(rightChannelPin, 0);
  analogWrite(leftChannelPin, 0);
  Serial.begin(9600);
  while (!Serial){
    ;
  }
}


void serialEvent() {
  if ( Serial.available() ) {
    parseCommand();
  }
}

void loop() {
  if (newCommandAvailable) {
    executeCommand();
//    printValues();
    newCommandAvailable = false;
  }
}

void parseCommand() {
  leftChannelBrightness = Serial.parseInt();
  rightChannelBrightness = Serial.parseInt();
  newCommandAvailable = true;
  discardOtherSerialInputs();
}

void discardOtherSerialInputs() {
  while ( Serial.available() ) {
    char inChar = (char) Serial.read();
    delay(2);
  }
}

void executeCommand() {
  if ( leftChannelBrightness >= 0 && leftChannelBrightness <= 255 ) {
    analogWrite(leftChannelPin, leftChannelBrightness);
//    Serial.print("sending: left chan = ");
//    Serial.println(leftChannelBrightness);
  }
  if ( rightChannelBrightness >= 0 && rightChannelBrightness <= 255 ) {
    analogWrite(rightChannelPin, rightChannelBrightness);
//    Serial.print("sending: right chan = ");
//    Serial.println(rightChannelBrightness);
  }
}

void printValues() {
  Serial.print("newCommandAvailable: ");
  Serial.println(newCommandAvailable);
  Serial.print("left: ");
  Serial.println(leftChannelBrightness);
  Serial.print("right: ");
  Serial.println(rightChannelBrightness);
}
