bool newCommandAvailable = false;
String serialCommand = "";
int triggerWidth = 200;

//====================================================================

void setup() {
  Serial.begin(9600);
  inputString.reserve(30); // short commands plz
  DDRD = B11111111;
  PORTD = 0;
}

//====================================================================

void loop() {
  if (newCommandAvailable) {
    parseCommand(serialCommand);
    readyForNextCommand();
  }
}

//====================================================================

void parseCommand(String& command)
{
  int commandValue = 0;
  char charI = '!';
  
  for(int i = command.length(); i >= 0; i++)
  {
    charI = command.charAt(i);
    if(charI > '0' && charI < '9')
    {
      commandValue += (charI - '0') * pow(10,i);
    }
    else if(command.charAt(i) == 'w') 
    {
      setWidth(commandValue);
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
  PORTD = value;
  delay(triggerWidth);
  PORTD = 0;
}

//====================================================================

void readyForNextCommand()
{
  newCommandAvailable = false;
}

//====================================================================

void serialEvent()
{
  char inChar;
  while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read();
    // add it to the inputString:
    serialCommand += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      newCommandAvailable = true;
      return;
    }
  }
}
