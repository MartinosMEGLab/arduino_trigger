const int defaultOuptut = 0;
bool newCommandAvailable = false;
String serialCommand = "";
int triggerWidth = 200;

const int pin_13 = 13;

//====================================================================

void setup() {
  pinMode(pin_13, OUTPUT);
  Serial.begin(9600);
  DDRD = B11111111;
  PORTD = 0;
}

//====================================================================

void loop() {
  if (newCommandAvailable) {
    parseCommand();
    readyForNextCommand();
  }
}

//====================================================================

void parseCommand()
{
  int commandValue = 0;
  int commandLength = serialCommand.length();

  for(int i = commandLength - 1; i >= 0; i--)
  {
    char charI = serialCommand.charAt(i);
    if(charI >= '0' && charI <= '9')
    {
      commandValue += (charI - '0') * pow(10, commandLength - i);
    }
    else if(charI == 'w') 
    {
      setWidth(commandValue);
      return;
    } 
    else {
      return;
    }
  }
  triggerWithHeight(commandValue);
  return;
}

//====================================================================

void setWidth(int widthValue)
{
   triggerWidth = widthValue;
}

//====================================================================

void triggerWithHeight(int heightValue)
{
//  int initialTime = millis();
//  while(millis() < initialTime + triggerWidth){
//      PORTD = heightValue;
//      digitalWrite(pin_13, HIGH);
//  }

  PORTD = heightValue;
  digitalWrite(pin_13, HIGH);
  Serial.print("T");
  Serial.println(analogRead(A0));
  delay(triggerWidth);
  PORTD = defaultOuptut;
  digitalWrite(pin_13, LOW);
}

//====================================================================

void readyForNextCommand()
{
  serialCommand = "";
  newCommandAvailable = false;
}

//====================================================================

void serialEvent()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      newCommandAvailable = true;
      return;
    }
    serialCommand += inChar;
  }
}
