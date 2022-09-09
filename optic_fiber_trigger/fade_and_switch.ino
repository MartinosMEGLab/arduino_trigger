
int rightChannel = 9;          
int leftChannel = 10;
int currentChannel = rightChannel;

int brightness = 0;    
int brightnessStep = 5;   
int delayMs = 10;

void setup() {
  pinMode(rightChannel, OUTPUT);
  pinMode(leftChannel, OUTPUT);
  delay(100);
  analogWrite(rightChannel, brightness);
  analogWrite(leftChannel, brightness);
}

void loop() {
  switchChannel();
  cycleUpDown();
}


void switchChannel() {
  if (currentChannel == rightChannel) {
    currentChannel = leftChannel;
  } else {
    currentChannel = rightChannel;
  }
}

void cycleUpDown() {
  brightness = 0;
  while(brightness < 255) {
    analogWrite(currentChannel, brightness);
    brightness = brightness + brightnessStep;
    delay(delayMs);
  }
  while(brightness > 0) {
    analogWrite(currentChannel, brightness);
    brightness = brightness - brightnessStep;
    delay(delayMs);
  }
  brightness = 0;
}


