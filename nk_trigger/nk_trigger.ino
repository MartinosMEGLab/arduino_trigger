//====================================================================
//====================================================================
// DEFAULT PARAMETERS:

// Default analog output when no triggers are happening.
const int defaultOuptut = 0;

// Default Trigger width in milliseconds.
int triggerWidth = 200;

//====================================================================
//====================================================================

const int pin_13 = 13;              // LED to indicate trigger sent.
bool newCommandAvailable = false;   // Gloabl flag to track commands.
String serialCommand = "";          // Buffer to store new commands.

//====================================================================
/*Setup outputs and their initial values;*/
void setup() {
  pinMode(pin_13, OUTPUT);
  Serial.begin(9600);
  DDRD = B11111111;
  PORTD = defaultOuptut;
}

//====================================================================
/*Wait for command and, when availbale, parse it.*/
void loop() {
  if (newCommandAvailable) {
    parseCommand();
    readyForNextCommand();
  }
}

//====================================================================
/*Parse command in global var 'serialCommand' and acts upon it.*/
void parseCommand()
{
  int commandValue = 0;
  int commandLength = serialCommand.length();
  
  /*We read commands back to front.*/
  for(int i = commandLength - 1; i >= 0; i--)
  {
    char charI = serialCommand.charAt(i);

    /*If we have a number, add it to result accounting for magintude.*/
    if(charI >= '0' && charI <= '9')
    {
      commandValue += (charI - '0') * pow(10, (commandLength - 1) - i);
    }

    /*If we have a 'w', adjust trigger width.*/
    else if(charI == 'w') 
    {
      triggerWidth = commandValue;
      return;
    } 

    /*If anything else shows up, give up and return early.*/
    else 
    {
      return;
    }
  }
  
  /*We get her if we did not adjust width or return early.*/
  triggerWithHeight(commandValue);
}

//====================================================================
/*Output 'heightValue' for 'triggerWidth' milliseconds.*/
void triggerWithHeight(int heightValue)
{
  PORTD = heightValue;
  digitalWrite(pin_13, HIGH);
  delay(triggerWidth);
  PORTD = defaultOuptut;
  digitalWrite(pin_13, LOW);
}

//====================================================================
/*Resets the command global variables.*/
void readyForNextCommand()
{
  serialCommand = "";
  newCommandAvailable = false;
}

//====================================================================
/*Reads from serial port to'serialCommand', with delimiter '\n'.*/
void serialEvent()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') /*We never send '\n' to 'serialCommand'.*/  
    { 
      newCommandAvailable = true;
      return;
    }
    serialCommand += inChar;
  }
}
