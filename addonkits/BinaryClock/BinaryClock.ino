
int led1[] = {13,12};
int led2[] = {12,13};
int led3[] = {11,13};
int led4[] = {A2,13};
int led5[] = {A3,13};
int led6[] = {13,A3};
int led7[] = {12,11};
int led8[] = {13,11};
int led9[] = {13,A2};
int led10[] = {A3,A2};

byte hours = 12;
byte minutes = 59;  
byte seconds = 30;

unsigned long nextRunTime = 0;
unsigned long nextSecond = 0;

const int leftButton = A1;
const int rightButton = 10;

unsigned long debounceDelay = 50;
unsigned long lastLeftDebounceTime = 0;
unsigned long lastRightDebounceTime = 0;
int leftButtonState;
int rightButtonState;
int lastLeftButtonState = HIGH;
int lastRightButtonState = HIGH;


void setup() {
  // put your setup code here, to run once:
  pinMode(leftButton, INPUT);
  digitalWrite(leftButton, HIGH);
  pinMode(rightButton, INPUT);
  digitalWrite(rightButton, HIGH);
 
  nextSecond = 1000;
  nextRunTime = millis() + 15;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() > nextRunTime){
    nextRunTime = millis() + 15;
    UpdateLEDs();
  }
  
  if(millis() > nextSecond){
    nextSecond += 1000;
    seconds += 1;
    if(seconds > 59){
      seconds = 0;
      minutes += 1;
      if(minutes > 59){
        minutes = 0;
        hours += 1;
        if(hours > 12){
          hours = 1;
        }
      }
    }
  }

  CheckButtons();  

}


void UpdateLEDs(){
  digitalWrite(9,bitRead(seconds,0));
  digitalWrite(8,bitRead(seconds,1));
  digitalWrite(7,bitRead(seconds,2));
  digitalWrite(6,bitRead(seconds,3));
  digitalWrite(5,bitRead(seconds,4));
  digitalWrite(4,bitRead(seconds,5));
  if(bitRead(minutes,0)){showLED(led1[0], led1[1]);}
  if(bitRead(minutes,1)){showLED(led2[0], led2[1]);}
  if(bitRead(minutes,2)){showLED(led3[0], led3[1]);}
  if(bitRead(minutes,3)){showLED(led4[0], led4[1]);}
  if(bitRead(minutes,4)){showLED(led5[0], led5[1]);}
  if(bitRead(minutes,5)){showLED(led6[0], led6[1]);}
  if(bitRead(hours,0)){showLED(led7[0], led7[1]);}
  if(bitRead(hours,1)){showLED(led8[0], led8[1]);}
  if(bitRead(hours,2)){showLED(led9[0], led9[1]);}
  if(bitRead(hours,3)){showLED(led10[0], led10[1]);}
  
}

void showLED(int highPin, int lowPin){
  pinMode(highPin, OUTPUT);
  pinMode(lowPin, OUTPUT);
  digitalWrite(highPin, HIGH);
  digitalWrite(lowPin, LOW);
  delay(2);
  digitalWrite(highPin, LOW);
  pinMode(highPin, INPUT);
  pinMode(lowPin, INPUT);
}

void CheckButtons(){
  int buttonState = digitalRead(leftButton);

  if(buttonState != lastLeftButtonState){
    lastLeftDebounceTime = millis();
  }

  if((millis() - lastLeftDebounceTime) > debounceDelay) {
    if(buttonState != leftButtonState){
      leftButtonState = buttonState;
    if(leftButtonState == LOW){
      minutes -= 1;
      if(minutes < 1){
        minutes = 59;
        hours -= 1;
        if(hours < 1){
          hours = 12;
        }
      }
    }
    }
  }
  lastLeftButtonState = buttonState;

  buttonState = digitalRead(rightButton);

  if(buttonState != lastRightButtonState){
    lastRightDebounceTime = millis();
  }

  if((millis() - lastRightDebounceTime) > debounceDelay) {
    if(buttonState != rightButtonState){
      rightButtonState = buttonState;
    if(rightButtonState == LOW){
      minutes += 1;
      if(minutes > 59){
        minutes = 1;
        hours += 1;
        if(hours > 12){
          hours = 1;
        }
      }
    }
    }
  }
  lastRightButtonState = buttonState;
}

