//====================================================================
//====================================================================
// DEFAULT PARAMETERS:

// Default analog output when no triggers are happening.
const int defaultOuptut = 0;

// Default Trigger width in milliseconds.
int triggerWidth = 20;

//====================================================================
//====================================================================

const int pin_13 = 13;              // LED to indicate trigger sent.
bool newCommandAvailable = false;   // Gloabl flag to track commands.
String commandString = "";          // Buffer to store new commands.

//====================================================================
/*Setup outputs and their initial values;*/
void setup() {
  pinMode(pin_13, OUTPUT);
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for native USB port only
  DDRD = B11111111;
  PORTD = defaultOuptut;
  commandString.reserve(10);
}

//====================================================================
/*Wait for command and, when availbale, parse it.*/
void loop() {
  if (newCommandAvailable) {
    processCommand();
    readyForNextCommand();
  }
}

//====================================================================
/*Parse command in global var 'commandString' and acts upon it.*/
void processCommand()
{
  int commandValue = 0;
  int commandLength = commandString.length();
  
  /*We read commands back to front.*/
  for(int i = commandLength - 1; i >= 0; i--)
  {
    char charI = commandString.charAt(i);

    /*If we have a number, add it to result accounting for magintude.*/
    if(isDigit(charI))
    {
      commandValue += (charI - '0') * toThePowerOf(10, (commandLength - 1) - i);
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
    
//    Serial.print("charI: ");
//    Serial.println(charI);
//    Serial.print("i: ");
//    Serial.println(i);
//    Serial.print("commandValue: ");
//    Serial.println(commandValue);
//    Serial.print("commandLength: ");
//    Serial.println(commandLength);
//    Serial.println("****************************");
  }
  
  /*We get her if we did not adjust width or return early.*/
  Serial.print("\nAbout to send trigger: ");
  Serial.println(commandValue);
  
  sendTrigger(commandValue);
}

//====================================================================
/*Output 'heightValue' for 'triggerWidth' milliseconds.*/
void sendTrigger(int heightValue)
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
  commandString = "";
  newCommandAvailable = false;
}

//====================================================================
/*Reads from serial port to'commandString', with delimiter '\n'.*/
void serialEvent()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') /*We never send '\n' to 'commandString'.*/  
    { 
      newCommandAvailable = true;
      return;
    }
    commandString += inChar;
  }
}

//====================================================================
/*Integer version of pow standard function.*/
int toThePowerOf(int a, int b) {
  int cumulative = 1;
  for (int i = 0; i < b; i++) {
    cumulative = cumulative * a;
  }
  return cumulative;
}

