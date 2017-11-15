#include <Bounce2.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <SPI.h>
#include <RH_RF69.h>
#include <avr/sleep.h>
#include "PinChangeInterrupt.h"
#include "LowPower.h"
#include <EEPROMex.h>

#define RF69_FREQ     915.0
#define RFM69_CS      10
#define RFM69_INT     3
#define RFM69_RST     9
#define RFM69_EN      A0

RH_RF69 rf69(RFM69_CS, RFM69_INT);
Adafruit_7segment matrix = Adafruit_7segment();

Bounce P1U_db = Bounce(); 
Bounce P1D_db = Bounce(); 
Bounce P2U_db = Bounce(); 
Bounce P2D_db = Bounce(); 
const int P1U = 5;
const int P1D = 6;
const int P2U = 4;
const int P2D = A2;
unsigned long lastChange, lastScoreCheck;
int P1Score, P2Score, P1UState, P1DState, P2UState, P2DState;
boolean P1UChanged,P1DChanged,P2UChanged,P2DChanged;
int shortPress = 1500;
boolean isserver = true;
boolean sleeping = false;
int min_dim = 5;
int min_off = 10;
int level_dim = 4;
int level_bright = 12;
int P1ScoreMemory = 0;
int P2ScoreMemory = 4;
int BrightnessMemory = 8;
const int memBase = 350;

void setup() {
  matrix.begin(0x70);    
    
  pinMode(P1U,INPUT_PULLUP);  
  P1U_db.attach(P1U);
  P1U_db.interval(50);  
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(P1U), wake, CHANGE);

  pinMode(P1D,INPUT_PULLUP);
  P1D_db.attach(P1D);
  P1D_db.interval(50);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(P1D), wake, CHANGE);
  
  pinMode(P2U,INPUT_PULLUP);
  P2U_db.attach(P2U);
  P2U_db.interval(50);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(P2U), wake, CHANGE);

  
  pinMode(P2D,INPUT_PULLUP);
  P2D_db.attach(P2D);
  P2D_db.interval(50);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(P2U), wake, CHANGE);
      
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);
  
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init())
    writeErrorCode(1042);
  
  if (!rf69.setFrequency(RF69_FREQ)) 
    writeErrorCode(1043);
   
  rf69.setTxPower(20, true);
  
  uint8_t key[] = { 0x29, 0x7F, 0x03, 0x04, 0x05, 0x06, 0x11, 0x08,
                    0x01, 0x15, 0x03, 0x04, 0x05, 0x06, 0x04, 0x08};
  rf69.setEncryptionKey(key);
    
  matrix.print(10000, DEC);
  matrix.writeDisplay();
  delay(500);
  
  matrix.clear();
  matrix.writeDisplay();

  if (!EEPROM.isReady())
    writeErrorCode(1044);

  
  EEPROM.setMemPool(memBase, EEPROMSizeATmega328);
  P1Score = EEPROM.readInt(memBase+P1ScoreMemory);
  P2Score = EEPROM.readInt(memBase+P2ScoreMemory);

  if (P1Score < 0
      || P1Score > 99
      || P2Score < 0
      || P2Score > 99){
      
    EEPROM.writeInt(memBase+P1ScoreMemory,0);
    EEPROM.writeInt(memBase+P2ScoreMemory,0);  
    P1Score = 0;
    P2Score = 0;
  }      
  
  if (P1Score < 0)
    P1Score = 0;
    
  if (P2Score < 0)
    P2Score = 0;
    
  level_bright = EEPROM.readInt(memBase+BrightnessMemory);
  if (level_bright < 0)
    level_bright = 12;    
  matrix.setBrightness(level_bright);  
  
  lastChange = millis();    
}

void parseScore(char recv[]) {
  matrix.writeDigitRaw(2, 0x08);  
  matrix.writeDisplay();
      
  char p1s_[5];
  memcpy(p1s_, &recv[0], 5);
  p1s_[3] = '\0';

  char p2s_[3];
  memcpy(p2s_, &recv[3], 2);
  p2s_[3] = '\0';
  
  int i;
  i = strtol(p1s_, NULL, 10);
  
  int x;
  x = strtol(p2s_, NULL, 10);

  if ((P1Score > 9 && i < 9) || (P2Score > 9 && x <9))
    matrix.clear();
    
  P1Score = i;
  P2Score = x;

  saveScore();
  lastChange = millis();
  delay(50);
  
  matrix.writeDigitRaw(2, 0x00);
  matrix.writeDisplay();
}

void sendScore() {
  matrix.writeDigitRaw(2, 0x04);
  matrix.writeDisplay();

  char radiopacket[20];
  sprintf(radiopacket, "%02d:%02d", P1Score, P2Score);
    
  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();

  delay(50);
  matrix.writeDigitRaw(2, 0x00);
  matrix.writeDisplay();
}

void writeErrorCode(int errorcode) {  
  matrix.clear();
  matrix.writeDisplay();
  matrix.print(errorcode,DEC);
  matrix.writeDisplay();
  while(1);
}

void changeScore(char player, char dir) {
  switch(player) {
    case '1':
      switch(dir) {
        case 'U':
          P1Score++;
          break;
        case 'D':
          P1Score--;
          break;
      }
      break;
    case '2':
      switch(dir) {
        case 'U':
          P2Score++;
          break;
        case 'D':
          P2Score--;
          break;
      }
      break;
  }
  
  sendScore();
  saveScore();
}

void saveScore() {
  EEPROM.writeInt(memBase+P1ScoreMemory,P1Score);
  EEPROM.writeInt(memBase+P2ScoreMemory,P2Score);  
}

void loop() {   
  if (lastChange > 0 && millis() - lastChange > (min_off * 60000)) {
    matrix.clear();
    matrix.writeDisplay();     
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    sleeping = true;   
  } 
  else if (lastChange > 0 && millis() - lastChange > (min_dim * 60000)) {
    matrix.setBrightness(level_dim);  
  } 
  else {
    matrix.setBrightness(level_bright);      
  }
  
  P1UChanged = P1U_db.update();
  P1DChanged = P1D_db.update();
  P2UChanged = P2U_db.update();
  P2DChanged = P2D_db.update();

  if (P1UChanged || P1DChanged || P2UChanged || P2DChanged)
    lastChange = millis();

  int duration = millis()-lastChange;
  int P1UState = P1U_db.read();
  int P1DState = P1D_db.read();
  int P2UState = P2U_db.read();
  int P2DState = P2D_db.read();

  if (P1U_db.rose() && P1UChanged && duration < shortPress) 
    changeScore('1', 'U');
  else if (P1D_db.rose() && P1DChanged && duration < shortPress && P1Score > 0) 
    changeScore('1', 'D');
  else if (P2U_db.rose() && P2UChanged && duration < shortPress) 
    changeScore('2', 'U');
  else if (P2D_db.rose() && P2DChanged && duration < shortPress && P2Score > 0) 
    changeScore('2', 'D');
  else if (P2DState == LOW && duration > shortPress) 
    resetScores();
  else if (P1DState == LOW && duration > shortPress) 
    cycleBrightness();

  uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
    
  if (rf69.waitAvailableTimeout(50))  {       
    if (rf69.recv(buf, &len)) {
      parseScore((char *)buf);
    }
  }

  matrix.clear();
  writeScore(P1Score,1);
  writeScore(P2Score,4);

  if (!sleeping)
    matrix.writeDisplay();
}

void resetScores() {
  P1Score = 0;
  P2Score = 0;
  sendScore();
  saveScore();
  matrix.clear();
  matrix.writeDisplay();
  lastChange = millis();
}

void cycleBrightness() {
  level_bright++;
  
  if (level_bright > 15)
    level_bright = 1;
    
  matrix.setBrightness(level_bright);
  EEPROM.writeInt(memBase+BrightnessMemory, level_bright);
  
  matrix.clear();
  matrix.println(level_bright);
  matrix.writeDisplay();
  
  delay(500);
  matrix.clear();
  matrix.writeDisplay();
}

void writeScore(int score, int dpos) {
  int value = score;
  int itteration = 0;
  
  if (value == 0)
    matrix.writeDigitNum(dpos-itteration,0,false);
    
  while (value > 0) {
    int digit = value % 10;
    matrix.writeDigitNum(dpos-itteration,digit,false);
    value /= 10;
    itteration++;
  }
}

void wake() {
  sleeping = false;
  lastChange = millis();
}