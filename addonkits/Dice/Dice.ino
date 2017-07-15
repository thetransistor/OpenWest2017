
int led1[] = {A2,A0};
int led2[] = {A0,A2};
int led3[] = {A1,A2};
int led4[] = {A0,A3};
int led5[] = {A2,A1};
int led6[] = {A1,A0};
int led7[] = {A0,A1};

int numToDisplay = 6;

unsigned long nextRunTime = 0;
unsigned long nextRollTime = 0;
int rollCounter = 0;

unsigned long nextCylonTime = 0;
int cylonCounter = 2;
int cylonDelay = 90;
bool cylonLedOn = false;
bool cylonCountUp = true;

void setup() {
  // put your setup code here, to run once:
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
 
  nextRunTime = millis() + 15;

  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() > nextRunTime){
    nextRunTime = millis() + 15;
    UpdateLEDs();
  }

  if(digitalRead(10) == LOW){
    rollCounter = 20;
    //numToDisplay = random(1,7);
  }

  if(rollCounter > 0 && (millis() > nextRollTime)){
    nextRollTime = millis() + 50;
    numToDisplay = random(1,7);
    rollCounter -= 1;
  }

  if(millis() > nextCylonTime){
    nextCylonTime = millis() + cylonDelay;
    UpdateCylon();
  }
}


void UpdateLEDs(){
  switch(numToDisplay){
    case 1:
      showLED(led4[0], led4[1]);
      break;
    case 2:
      showLED(led1[0], led1[1]);
      showLED(led7[0], led7[1]);
      break;
    case 3:
      showLED(led1[0], led1[1]);
      showLED(led4[0], led4[1]);
      showLED(led7[0], led7[1]);
      break;
    case 4:
      showLED(led1[0], led1[1]);
      showLED(led2[0], led2[1]);
      showLED(led6[0], led6[1]);
      showLED(led7[0], led7[1]);
      break;
    case 5:
      showLED(led1[0], led1[1]);
      showLED(led2[0], led2[1]);
      showLED(led4[0], led4[1]);
      showLED(led6[0], led6[1]);
      showLED(led7[0], led7[1]);
      break;
    case 6:
      showLED(led1[0], led1[1]);
      showLED(led2[0], led2[1]);
      showLED(led3[0], led3[1]);
      showLED(led5[0], led5[1]);
      showLED(led6[0], led6[1]);
      showLED(led7[0], led7[1]);
      break;
  }
}

void showLED(int highPin, int lowPin){
  pinMode(highPin, OUTPUT);
  pinMode(lowPin, OUTPUT);
  digitalWrite(highPin, HIGH);
  digitalWrite(lowPin, LOW);
  delay(3);
  digitalWrite(highPin, LOW);
  pinMode(highPin, INPUT);
  pinMode(lowPin, INPUT);
}

void UpdateCylon(){
  if(cylonCountUp){
    if(cylonCounter == 9){
      digitalWrite(cylonCounter, HIGH);
      digitalWrite(cylonCounter-1, LOW);
      cylonCountUp = false;
      cylonCounter --;
    }else{                                                                                                        
      digitalWrite(cylonCounter, HIGH);
      digitalWrite(cylonCounter-1, LOW);
      cylonCounter ++;
    }
  }else{
    if(cylonCounter == 2){
      digitalWrite(cylonCounter, HIGH);
      digitalWrite(cylonCounter+1, LOW);
      cylonCountUp = true;
      cylonCounter ++;
    }else{
      digitalWrite(cylonCounter, HIGH);
      digitalWrite(cylonCounter+1, LOW);
      cylonCounter --;
    }
  }
}

