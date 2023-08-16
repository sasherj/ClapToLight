#include <EEPROM.h>

const int buttons[] = {2, 3, 4}; // buttons and their pins
const int bzzr = 12;
const int sensorPin = A0;
const int ledPins[] = {13, 8, 7}; // LEDs


int sensitivity = 510;  // sensitivity of the sound sensor, can also change it by changing the screw

// Maximum number of rhythms and the maximum number of claps per rhythm
const int rythmsMax = 3;
const int clapsMax = 8;

// Storing rhythms
int rhythmLengths[rythmsMax];
int rhythms[rythmsMax][clapsMax];

// Current rhythm index
int currentRhythm = 0;

bool clapDetected = false;
bool enableAddClap = true; // Flag to enable/disable adding claps to the rhythm

void setup() {
  for (int i = 0; i < rythmsMax; i++) {
    rhythmLengths[i] = 0;
  }

  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  
  pinMode(bzzr, OUTPUT);
  Serial.begin(9600);
  
  loadRhythmsFromEEPROM(); // for Loading saved rhythms from EEPROM
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  if (sensorValue > sensitivity && enableAddClap) {
    clapDetected = true;
    addClapToRhythm();
    checkSavedRhythms();
  }

   if (sensorValue > sensitivity && !enableAddClap) {
    
    checkSavedRhythms();
          tone(bzzr, 500, 200);  // Play a tone 

  }
  
  

  if (clapDetected && sensorValue < sensitivity) {
    clapDetected = false;
  }
  
  // Check for button presses to call the functions
  
  if (digitalRead(buttons[0]) == HIGH) {
    switchRhythm();
    delay(1000); //  delay of a second 
  }
  
  if (digitalRead(buttons[1]) == HIGH) {
    enableAddClap = !enableAddClap; // Toggle the flag to enable/disable adding claps
    saveRhythmsToEEPROM();

    delay(1000); //  delay of a second 
  }
  
  if (digitalRead(buttons[2]) == HIGH) {
    playRhythm(currentRhythm);
    delay(1000); //  delay of a second 
  }
  
  delay(10);  
}

void addClapToRhythm() {
  if (rhythmLengths[currentRhythm] < clapsMax) {
    int clapIndex = rhythmLengths[currentRhythm];
    rhythms[currentRhythm][clapIndex] = HIGH;
    rhythmLengths[currentRhythm]++;
    
    // Blink the corresponding LED
    digitalWrite(ledPins[currentRhythm], HIGH);
    delay(100);
    digitalWrite(ledPins[currentRhythm], LOW);
  }
}

//The followinf function gets activated on pressing a button 
//and plays the rhythm back to the user
void playRhythm(int rhythmIndex) {
  if (rhythmIndex >= 0 && rhythmIndex < rythmsMax) {
    int rhythmLength = rhythmLengths[rhythmIndex];
    int* rhythm = rhythms[rhythmIndex];
    
    for (int i = 0; i < rhythmLength; i++) {
      digitalWrite(ledPins[rhythmIndex], rhythm[i]);
      tone(bzzr, 1000, 200);  // Play a tone 
      delay(200);
      digitalWrite(ledPins[rhythmIndex], LOW);
      delay(200);
    }
  }
}

//Not using the function at the moment
void resetRhythms() {
  for (int i = 0; i < rythmsMax; i++) {
    rhythmLengths[i] = 0;
  }
  currentRhythm = 0;
}

//The folowing fucntion writes to the EEPROM
void saveRhythmsToEEPROM() {
  int address = 0;
  
  for (int i = 0; i < rythmsMax; i++) {
    EEPROM.put(address, rhythmLengths[i]);
    address += sizeof(int);
    
    for (int j = 0; j < rhythmLengths[i]; j++) {
      EEPROM.put(address, rhythms[i][j]);
      address += sizeof(int);
    }
  }
}
//The folowing fucntion loads from the EEPROM

void loadRhythmsFromEEPROM() {
  int address = 0;
  
  for (int i = 0; i < rythmsMax; i++) {
    EEPROM.get(address, rhythmLengths[i]);
    address += sizeof(int);
    
    for (int j = 0; j < rhythmLengths[i]; j++) {
      EEPROM.get(address, rhythms[i][j]);
      address += sizeof(int);
    }
  }
}
//Here We only do a switch in the rhythm array
void switchRhythm() {
  currentRhythm++;
  if (currentRhythm >= rythmsMax) {
    currentRhythm = 0;
  }
}

//
void checkSavedRhythms() {
  for (int i = 0; i < rythmsMax; i++) {
    if (rhythmLengths[i] > 0 && rhythmLengths[i] == rhythmLengths[currentRhythm]) {
      bool match = true;
      for (int j = 0; j < rhythmLengths[i]; j++) {
        if (rhythms[i][j] != rhythms[currentRhythm][j]) {
          match = false;
          break;
        }
      }
      if (match) {
        digitalWrite(ledPins[i], HIGH); // Turn on the LED corresponding to the matched rhythm
        delay(1000);
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
}
