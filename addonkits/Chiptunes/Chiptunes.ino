/*
  Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM

  Connect the positive side of the Buzzer to pin 3,
  then the negative side to a 1k ohm resistor. Connect
  the other side of the 1 k ohm resistor to
  ground(GND) pin on the Arduino.

  by: Dipto Pratyaksa
  last updated: 31/3/13
*/

/*************************************************
   Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 11

const int leftButton = 12;
const int rightButton = 13;

unsigned long debounceDelay = 50;
unsigned long lastLeftDebounceTime = 0;
unsigned long lastRightDebounceTime = 0;
int leftButtonState;
int rightButtonState;
int lastLeftButtonState = HIGH;
int lastRightButtonState = HIGH;

int selectedTune = 1;

unsigned long lastPhaserTime = 0;
int phaserCounter = 0;
bool phaserSound = false;
int phaserDelay = 5;

//Mario main theme melody
int melody1[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Mario main them tempo
int tempo1[] = {
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,

  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,

  6, 6, 6,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,

  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,

  6, 6, 6,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,

  8, 8, 8, 8,
  8, 8, 6,
  3,
  8, 8, 8, 8,
  8, 8, 6,
  3,
  8, 8, 8, 8,
  8, 8, 6,
  3,
  8, 8, 8, 8,
  8, 8, 6,
  6, 9, 9, 9,
  6, 6,
  6, 6,
  6, 6,
  9, 9, 9, 9, 9, 9,
  8, 8, 8,
  8, 8, 8,
  3, 3, 3
};

//Zelda Theme
int melody2[] = {NOTE_AS3, NOTE_F3, NOTE_F3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3, 0, NOTE_AS3, NOTE_FS3, NOTE_FS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
                  NOTE_F2, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_AS1,
                  NOTE_F2, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_AS1, NOTE_F2, NOTE_AS1,
                  NOTE_AS3, 0, NOTE_F3, 0, NOTE_AS3, NOTE_AS3, NOTE_B3, NOTE_CS4, NOTE_DS4,
                  NOTE_F5, NOTE_AS3, NOTE_AS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_F5, 0,
                  NOTE_AS3, 0, NOTE_F3, 0, NOTE_AS3, NOTE_AS3, NOTE_B3, NOTE_CS4, NOTE_DS4,
                  NOTE_F5, NOTE_AS3, NOTE_AS3, NOTE_B3, NOTE_CS4, NOTE_DS4, NOTE_F5,
                  };
int tempo2[] = {1, 4, 4, 4, 8, 8, 2, 2, 1, 4, 4, 4, 8, 8, 2,
                4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8,
                4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8,
                2, 16, 3, 16, 4, 8, 8, 8, 8,
                4, 4, 8, 8, 8, 8, 2, 3,
                2, 16, 3, 16, 4, 8, 8, 8, 8,
                4, 4, 8, 8, 8, 8, 2,
                };


//Star Wars Imperial March
int melody3[] = {NOTE_A3, NOTE_A3, NOTE_A3, NOTE_F3, NOTE_C4, NOTE_A3, NOTE_F3, NOTE_C4, NOTE_A3,
                  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_C4, NOTE_GS3, NOTE_F3, NOTE_C4, NOTE_A3,
                  NOTE_A4, NOTE_A3, NOTE_A3, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_F4, 0, NOTE_AS3, NOTE_DS4, NOTE_D4, NOTE_CS4,
                  NOTE_C4, NOTE_B3, NOTE_C4, 0, NOTE_F3, NOTE_GS3, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_E4,
                  NOTE_A4, NOTE_A3, NOTE_A3, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_F4, 0, NOTE_AS3, NOTE_FS4, NOTE_D4, NOTE_CS4,
                  NOTE_C4, NOTE_B3, NOTE_C4, 0, NOTE_F3, NOTE_GS3, NOTE_F3, NOTE_C4, NOTE_A3, NOTE_F3, NOTE_C4, NOTE_A3};
int tempo3[] = {2, 2, 2, 3, 8, 2, 3, 8, 1,
                  2, 2, 2, 3, 8, 2, 3, 8, 1,
                  2, 3, 8, 2, 3, 8, 8, 8, 4, 4, 4, 2, 3, 8,
                  8, 8, 4, 4, 4, 2, 3, 8, 2, 3, 8, 1,
                  2, 3, 8, 2, 3, 8, 8, 8, 4, 4, 4, 2, 3, 8,
                  8, 8, 4, 4, 4, 2, 3, 8, 2, 3, 8, 1};

//Star Wars Theme
int melody4[] = {NOTE_F4, NOTE_F4, NOTE_F4, NOTE_AS4, NOTE_F5, NOTE_DS5, NOTE_D5, NOTE_C5, NOTE_AS5, NOTE_F5, NOTE_DS5, NOTE_D5, NOTE_C5,
                  NOTE_AS5, NOTE_F5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_C5
                  };
int tempo4[] = {8,8,8,1,1,8,8,8,1,2,8,8,8,1,2,8,8,8,1
                };
                
//Tetris
int melody5[] = {NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4};
int tempo5[] = {8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  };


//Jeopardy
int melody6[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4, NOTE_C4,
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_CS4,
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3, NOTE_C4, NOTE_F4, NOTE_C4,
  NOTE_F4, NOTE_D4, NOTE_C4, NOTE_AS3,
  NOTE_A3, NOTE_G3, NOTE_F3};
int tempo6[] = {4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4,
  3, 8, 8, 8, 8, 8,
  4, 4, 4, 4, 4, 4, 2,
  3, 8, 4, 4,
  4, 4, 4 };




//Happy Birthday
int melody7[] = {NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_C6, NOTE_B5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D6, NOTE_C6,
                  NOTE_G5, NOTE_G5, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_F6, NOTE_F6, NOTE_E6, NOTE_C6, NOTE_D6, NOTE_C6};
int tempo7[] = {8,8,4,4,4,2,8,8,4,4,4,2,
                8,8,4,4,4,4,2,8,8,4,4,4,1};





void setup(void)
{
  pinMode(11, OUTPUT);//buzzer
  //pinMode(2, OUTPUT);//led indicator when playing a note
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  updateLEDs();
}

void loop()
{
  //play the tunes
  //play(1);
  //play(1);
  //play(2);
  CheckButtons();
  if(phaserSound){
    if((millis() - lastPhaserTime) > phaserDelay){
      lastPhaserTime = millis();
      PlayPhaserSound();
    }
  }
}


void PlayTune() {
  switch (selectedTune) {
    case 1:
      play1();
      break;
    case 2:
      play2();
      break;
    case 3:
      play3();
      break;
    case 4:
      play4();
      break;
    case 5:
      play5();
      break;
    case 6:
      play6();
      break;
    case 7:
      play7();
      break;
  }
}

void play1() {

  int size = sizeof(melody1) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / tempo1[thisNote];

    //buzz(melodyPin, melody[thisNote], noteDuration);
    tone(melodyPin, melody1[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    // stop the tone playing:
    //buzz(melodyPin, 0, noteDuration);
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  }
}


void play2() {
  int size = sizeof(melody2) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo2[thisNote];
    tone(melodyPin, melody2[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  } 

}

void play3() {
  int size = sizeof(melody3) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo3[thisNote];
    tone(melodyPin, melody3[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  }

}

void play4() {
  int size = sizeof(melody4) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo4[thisNote];
    tone(melodyPin, melody4[thisNote], noteDuration);
    int pauseBetweenNotes;
    if(tempo4[thisNote] > 2){
      pauseBetweenNotes = noteDuration * 1.30;
    }else{
      pauseBetweenNotes = noteDuration * 1.1; //The long notes don't sound right with such a long pause
    }
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  }

}

void play5() {
  int size = sizeof(melody5) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo5[thisNote];
    tone(melodyPin, melody5[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  }

}

void play6() {
  int size = sizeof(melody6) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo6[thisNote];
    tone(melodyPin, melody6[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  }

}

void play7() {
  int size = sizeof(melody7) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {
    int noteDuration = 1000 / tempo7[thisNote];
    tone(melodyPin, melody7[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    if(digitalRead(13) == LOW){return;}
    tone(melodyPin, 0, noteDuration);
    if(digitalRead(13) == LOW){return;}
  }

}


void CheckButtons() {
  int buttonState = digitalRead(leftButton);

  if (buttonState != lastLeftButtonState) {
    lastLeftDebounceTime = millis();
  }

  if ((millis() - lastLeftDebounceTime) > debounceDelay) {
    if (buttonState != leftButtonState) {
      leftButtonState = buttonState;
      if (leftButtonState == LOW) {
        selectedTune += 1;
        if (selectedTune > 8) {
          selectedTune = 1;
        }
        updateLEDs();
      }
    }
  }
  lastLeftButtonState = buttonState;

  buttonState = digitalRead(rightButton);

  if (buttonState != lastRightButtonState) {
    lastRightDebounceTime = millis();
  }

  if ((millis() - lastRightDebounceTime) > debounceDelay) {
    if (buttonState != rightButtonState) {
      rightButtonState = buttonState;
      if (rightButtonState == LOW) {
        if(selectedTune == 8){
          phaserSound = true;
          phaserCounter = 0;
        }else{
        PlayTune();
        }
      }else{
        if(selectedTune == 8){
          phaserSound = false;
          noTone(melodyPin);
        }
      }
    }
  }
  lastRightButtonState = buttonState;
}

void updateLEDs() {
  for (int x = 2; x < 10; x++) {
    digitalWrite(x, LOW);
  }

  digitalWrite(selectedTune + 1, HIGH);
}

void PlayPhaserSound(){
  if(phaserCounter < 1){
    phaserCounter = 100;  
  }
  if(phaserCounter > 10){
    tone(melodyPin, phaserCounter * 20);
  }else{
    noTone(melodyPin);
  }
  phaserCounter --;
}

