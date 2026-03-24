
#include <ICSC.h>
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define sw3 A6
#define sw1 2
#define sw2 3
const uint8_t versionNumber = 55;
const uint8_t digit1 = 18;
const uint8_t digit2 = 19;
const uint8_t digit3 = 20;
const uint8_t digit4 = 21;
const uint8_t segA = 0;
const uint8_t segB = 1;
const uint8_t segC = 2;
const uint8_t segD = 3;
const uint8_t segE = 4;
const uint8_t segF = 5;
const uint8_t segG = 16;
const uint8_t segDP = 17;


byte powerbtn = LOW;
byte menubtn = LOW;
byte upbtn = LOW;
byte downbtn = LOW;

byte actualTemperature_data;

byte statep1;
byte lastp1;
byte p1;
byte p2;
long p1Millis;

byte statep2;
byte lastp2;
long p2Millis;

unsigned long plusData = 3600;
byte buttonOnPressed = 1;
unsigned long down;
unsigned long prevt;
unsigned long dataRemain;
int dataRemain2;
byte downPlus = 0;
byte dataPlus = 0;
int lastsec;
unsigned long minute;
unsigned long second;
unsigned long hour;
long lastplusData;
int sum;
unsigned long maxTime = 12;


long buttonTimer = 0;

boolean buttonActive = false;
boolean longPressActive = false;
byte smdCount = 0;
byte preRunSet = 0;
byte preRunSet_running = 0;
byte preRunSet_setting = 0;
unsigned long preRunSet_time = 5;
unsigned long preRunSet_adjustTime = 0;
unsigned long preRunSet_down = 0;
unsigned long lastpreRunSet_adjustTime = 1800;
byte lightStop = 0;
byte smdCount2 = 0;
int preRunSet_hour;
int preRunSet_minute;
int preRunSet_second;
long prevtPRS = 0;
int ts1_read;
byte tempSet_read = 80;
float ts1_read1;
float diff;
unsigned long preHeat_time = 1800;
byte tempSet = 0;
long prevreadAnalog = 0;
byte preHeat_reached = 0;
unsigned long preHeat_time2 = 1800;
unsigned long prevpreHeat_down;
unsigned long preHeat_startDown;
byte preHeat_stop = 0;
byte preRunSet_display;
int preHeat_diff;
byte prevmenuMillis;
/*==============================6/25/2018======================*/
int prevfiveMinutes;
unsigned int down2;
boolean menu_On = false;
byte menu_On_setttings = 0;
byte savePoint = 0;
byte savePoint2 = 0;
byte nextSession = 0;
byte plusData_savePoint = 0;
//============================6/26/2018
byte dataRemain_savePoint;
//============================6/28/2018
byte plusOne = 0;
byte preRun = 1;
byte p4Plus = 0;
//===============7/9/2018
long prevfastCount;
long debfastCount;
long debfastCount2;
long debfastCount3;
byte fastCnt;
byte fastCnt2;
byte fastCnt3;




long intervalBlink = 100;
unsigned long previousMilBlink;
byte ledBlink;
long slowBlink = 1000;
long fastBlink = 200;
unsigned long previousSlow;
byte ledSlow;
byte ledFast;
unsigned long previousFast;


byte lastupbtn = LOW;
long upbtnmillis = 0;
byte upbtnState = LOW;

long powerbtnMillis;
byte powerbtnState;
byte lastpowerbtn;
long buttonTimer2;

byte sessionSet_data = 0;
byte temperatureSet_data = 90;
byte fanSet = 1;
long prevblinkDisplay;
byte blinkDisplayState = 0;
byte lightbtn;
byte lastlightbtn;
long lightbtnmillis;
byte lightbtnState;
byte lightActive = 0;
boolean powerbtnActive = false;
boolean powerbtnStop = true;
boolean bothActive = false;
long bothMillis;
boolean bothDisplay = false;
byte bothChange = 0;
long prevbothDisplay;
long prevblinkBoth;
byte blinkBothStart = 0;
boolean displayOnce = false;
byte noToShortPress = 1;  // short press function is disable during displayTime
byte conversion = 0;
int tempSet_display = 50;
boolean temporaryData = false;
//7/10/2018


int totalTemp;
float totalTempFah;
byte changeDisplay = 0;
int tempSet_on = 30;
float lasttempSet_on = 30.0;
unsigned long prevsetTempBlink;
long intervalsetTempBlink = 1000;
byte statesetTempBlink;
byte prevdurationSetTemp;
long intervaldurationSetTemp = 5000;
byte setTempDisplay_On = 0;
boolean changeDisplayTemp = false;
boolean tempSet_on_1 = false;
unsigned long time_On = 3600;
unsigned long time_On2 = 3600;
byte dipSwitch9_data = 0;
//7/11/2018
byte peZO = 13;
byte pzDetect = 1;
byte piezoState = LOW;
long previousMilpiezo = 0;
long intervalpiezo = 500;
unsigned long previousMilBuz;
long intervalBuz = 500;
int tempSet_onFah;
unsigned long prevpiezoing;
//7/13/2018
unsigned long maxTimeDown;
//7/16/2018
byte advUser_data = 1;
byte fanOff = 0;
byte steamerOff = 0;
unsigned long lastdown;
byte combi_data = 0;
byte VERSION_data = 0;
byte VERSION2_data = 66;
byte versionFACELIFT = 13;  //12.8
byte CabinDrying = 0;
unsigned long prevcabinMillis;
boolean startDrying = false;
int DryingTime;
unsigned long prevcabinMillis2;
unsigned long secMillis;
byte remoteOn_data = 1;
byte triggerOFF = 0;
byte alternateDisplayGo = 0;
byte fanOff_data = 0;
boolean errorTrue = false;
byte ERROR1_data = 0;
byte ERROR2_data = 0;
byte errorAlternate = 0;
byte safetySwitch_data = 0;
byte steamLevel_data = 0;
byte combiDetect_data = 3;
byte blink11State = 0;
byte sendPreRunTurnOn = 0;
byte fanOff_PRERUN = 0;
byte fanOff_PREV = 0;
byte lightPlus = 0;
byte fanOfflast = fanOff;
byte lastlightActive;
byte preHeat_data = 0;

byte paraSaSugod = 0;
boolean kas_a_lang = true;
byte lastbuttonOnPressed = 1;
byte receiveFromBoard_data;
byte fanDetect_data;
byte fillDetect_data = 0;
byte beepOnce = 0;
byte beepOnce2 = 0;
byte beepOnce3 = 0;
byte beepOnce4 = 0;
byte beepOnce5 = 0;
byte beepOnce6 = 0;
byte beepOnce7 = 0;
byte beepOnce8 = 0;
byte DHP = 0;  //domestic Hotel Public
byte oneTimeOnly = 1;
byte preRunTime = 0;
unsigned long prevkeylock;
long keylockInterval = 5000;
byte keylocklock = 0;
byte Klock;
byte displayKLockGo = 0;
unsigned long beepInterval = 1000;
byte beepState = 0;
byte displayBlink2 = 0;

unsigned long beepbeep2 = 1000;
long beepbeepInterval2 = 1000;
byte decreStop = 0;

unsigned long prevdelayTone;
unsigned long prevdelayTone2;
long toneInterval = 300;

unsigned long prevbeepBuzzer;
long beepBuzzerInterval = 500;

unsigned long prevbeepBuzzer2;
long beepBuzzerInterval2 = 500;
float saveSetTemp = 0.0;
unsigned long hh;
unsigned long mm;
unsigned long ss;
unsigned long lasttime_On2;
unsigned long Preheat_hh;
unsigned long Preheat_mm;
byte keylockReset = 0;
byte combiPLUS = 50;
byte lastcombiPLUS = 50;
byte combiPLUS2;
byte lastcombiPLUS2;
byte steamerOff_PRERUN = 0;
byte HumidSet_read = 50;
int tempSet_on_data;
int tempSet_on_Fah;
int humidSet_on = 50;
byte laststeamerOff = 6;
byte tempDATA = 0;
byte HOT_data = 0;
byte steamerMillis = 0;
byte threeAttempts = 0;
unsigned long receiveMillis;
byte narecieve = 0;
unsigned long narecievemillis;
unsigned long prevbeepdry;
long cabininterval = 1000;  //1000 original
byte cabinSendOnce = true;
byte everyOnsend = true;
unsigned long prevdisplayblink;
byte displayblinkState = HIGH;
byte noMoreCombi = 0;
boolean sendOnce4or6 = true;
byte dlidungan;

unsigned long prevsendmillis;
unsigned long sendmillis;
byte sendplus = 0;
byte displayCurrentTemp = 0;
//curve formula
float x2 = 0.0;
float y = 0.0;
byte humidityData_data = 0;

byte combiByte = 0;
byte tempByte = 0;
byte lastcombiPLUS2_data = 0;
byte eepromDetect = 0;
byte eepromDetect2 = 0;
unsigned long tempmillis;
unsigned long combiInterval;

unsigned long displayForViewMillis;
byte displayForView = 0;
byte no_button_work = 0;
byte gotomenuSTEAMER = 0;
byte unlitime = 0;

int save_tempSet_on = 30;
int save_humidSet_on = 30;
byte save_combiPLUS2 = 30;
byte stopBeep = 1;
unsigned long last_preRunSet_down;
byte lastpreRunSet_running = 0;
byte enableUnlimitedTime = 0;
byte lastenableUnlimitedTime = 0;
byte threeDisplayOnly = 0;
int displayForTemp = 30;
byte displayForHumid = 30;
unsigned long displayForTime;
byte displayDetected = 0;
unsigned long fill_dry_buzz;

byte saveSteamer;
byte saveFanOff;
byte backToTempView;
byte addTime = 0;

unsigned long preRunTimeMax;
unsigned long preSession;

byte forTemp;
byte forCombi;

int fahrenheit;
int combifahrenheit;
int save_fahrenheit;
int save_combifahrenheit;

byte save_tempSet_fah;
byte save_humidSet_fah;

int prerunfah = 176;
int precombifah = 120;

byte prefahDisplay;
byte precelDisplay;
byte smdDetected = 0;
byte smdNTC_data = 0;
unsigned long smdlong;

boolean buttonActiveHigh = false;
boolean longPressActiveHigh = false;
unsigned long longPressTimeHigh;

boolean buttonActiveLow = false;
boolean longPressActiveLow = false;
unsigned long longPressTimeLow;

const unsigned long longPressTime = 2000;
const unsigned long longPressTime2 = 1000;
unsigned long nobuttonWorkmillis;
byte preRun_savePoint = 0;
unsigned long hh_prerun;
unsigned long mm_prerun;
byte no40min = 0;
byte savehh;
byte savemm;
boolean prerunstop1 = false;
unsigned long prevprerundeb;
unsigned long prerunmillis;
unsigned long prerunmillis2;
byte prerunstop2 = false;
byte toggleisPressed = 0;
byte togglemillis;
byte blinkfast = 33;
byte resetTemp = 0;
unsigned long preRunSet_down_last;
byte humidLimit = 55;
byte fanOffMode = 0;
byte displayFanOffMode = 0;
unsigned long fanOffModeMillis;
byte gikanSaOnMode = 1;
int fanTimeMillis;

unsigned long hh_session;
unsigned long mm_session;

byte prevblinkRunning;
byte blinkingLed = 0;
byte preRunLed;

byte resetDisplay = 1;
byte resetDisplayMode = 1;
byte resetMillis;
byte activatederror = 0;
byte displaySetTemp = 1;
unsigned long setTempMillis;
byte toggleOnce = 1;
byte goToMenu = 0;
byte smddeb = 0;
byte displayOpen = 0;
byte hiTempSmd_data = 0;
byte stopPzDetect = 0;
unsigned int piezoTone = 4000;
byte stopOnce = 0;
byte stopOnce2 = 0;
byte sendToKnow = 0;
byte versionOnce = 1;
unsigned long NoLongerConnected;
unsigned long sendsigisasugod;
byte displayStartUp = 1;
//unsigned long delaySendmillis;
byte delaySendmillis = 0;
byte oneSecondBlink = 0;
byte savePoints[5];
unsigned long timeForCountdown = 21600;
byte displayHotForFiveSec = 1;
int divi = 0;
byte sensorChange = 0;
byte lastsensorChange = 0;
byte fastbeep3 = 0;
byte save_steamerOff_PRERUN;
long brightness = 500;
long brightness2 = 500;

unsigned long every100MillisSend;
boolean everyOnsend2 = false;
byte increment = 0;
byte powerStateOfBoard = 1;
byte dontSendYet = 0;
boolean fanActivated = false;


//---------------------New variables added--------------------------------------------------
bool backtoyou_data = false;
bool prev_backtoyou_data = false;
bool lighttoyou_data;
String tempScale;
int hh_sessions;
int mm_sessions;
uint16_t sessionTime_data;
unsigned long prev_sessionTime_data = -1;
unsigned long lastUpdateTime = 0;
int zero;
unsigned long prev_tempSet_on_data = -1;
unsigned long prev_tempSet_on_Fah = -1;
unsigned long prev_tempSet_on_ESP = -1;
unsigned long prev_tempSet_on_ESP2 = -1;


const unsigned long interval = 5000;
const unsigned long interval2 = 7000;
unsigned long previousMillis = 0;
byte Tempscale;
// int tempSet_on_ESP;
int tempSet_on_ESP2;

boolean back = false;
byte buttonOnPressedappui_data = 3;

bool initialized = false;
byte E11_data;
byte E12_data;

// Define a constant for the update interval in microseconds


//------------------------------------------------------------------------------------------


void setup() {

  ICSC.begin(8, 57600, 14);
  delay(300);
  TCCR1A = 0;  // Set entire TCCR1A register to 0
  TCCR1B = 0;  // Set entire TCCR1B register to 0
  TCNT1 = 0;   // Initialize counter value to 0

  // Set compare match register for desired increment
  OCR1A = 16000;  // Value to count up to

  // Turn on CTC mode (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);

  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  // Enable global interrupts

  DDRB |= (1 << 0);
  DDRB |= (1 << 1);
  DDRB |= (1 << 2);
  DDRB |= (1 << 3);
  DDRB |= (1 << 4);
  DDRB |= (1 << 5);
  DDRB &= ~(1 << 6);
  DDRB &= ~(1 << 7);

  DDRC |= (1 << 0);
  DDRC |= (1 << 1);
  DDRC |= (1 << 2);
  DDRC |= (1 << 3);
  DDRC |= (1 << 4);
  DDRC |= (1 << 5);
  DDRC &= ~(1 << 6);
  DDRC &= ~(1 << 7);

  DDRD &= ~(1 << 0);
  DDRD |= (1 << 1);
  DDRD &= ~(1 << 2);
  DDRD &= ~(1 << 3);
  DDRD |= (1 << 4);
  DDRD |= (1 << 5);
  DDRD |= (1 << 6);
  DDRD |= (1 << 7);

  //set LED off - off LED - set to HIGH
  PORTB |= (1 << 0);
  PORTB |= (1 << 1);
  PORTB |= (1 << 2);
  PORTB |= (1 << 3);
  PORTB |= (1 << 4);
  PORTB |= (1 << 5);
  PORTB &= ~(1 << 6);  // Clear bit 6 of PORTB
  PORTB &= ~(1 << 7);  // Clear bit 7 of PORTB

  PORTC |= (1 << 0);
  PORTC |= (1 << 1);
  PORTC &= ~(1 << 2);  // Clear bit 2 of PORTC
  PORTC &= ~(1 << 3);  // Clear bit 3 of PORTC
  PORTC &= ~(1 << 4);  // Clear bit 4 of PORTC
  PORTC &= ~(1 << 5);  // Clear bit 5 of PORTC
  PORTC &= ~(1 << 6);  // Clear bit 6 of PORTC
  PORTC &= ~(1 << 7);  // Clear bit 7 of PORTC

  pinMode(sw3, INPUT_PULLUP);




  bothChange = EEPROM.read(1);
  save_tempSet_on = EEPROM.read(3);
  keylocklock = EEPROM.read(5);
  hh = EEPROM.read(6);
  mm = EEPROM.read(7);
  ss = EEPROM.read(2);

  Preheat_hh = EEPROM.read(8);
  Preheat_mm = EEPROM.read(9);
  save_humidSet_on = EEPROM.read(11);
  save_combiPLUS2 = EEPROM.read(12);
  saveSteamer = EEPROM.read(10);
  enableUnlimitedTime = EEPROM.read(13);
  save_fahrenheit = EEPROM.read(14);

  save_combifahrenheit = EEPROM.read(15);
  hh_prerun = EEPROM.read(16);
  mm_prerun = EEPROM.read(17);
  fanOff_PRERUN = EEPROM.read(20);
  steamerOff_PRERUN = EEPROM.read(21);
  combiPLUS = EEPROM.read(22);
  hh_session = EEPROM.read(23);
  mm_session = EEPROM.read(24);
  sensorChange = EEPROM.read(25);
  tempSet_read = EEPROM.read(26);
  HumidSet_read = EEPROM.read(27);
  lastsensorChange = sensorChange;
  sessionTime_data = EEPROM.read(28);
  buttonOnPressedappui_data = EEPROM.read(29);
  if (save_fahrenheit == 255) save_fahrenheit = 176;
  if (save_combifahrenheit == 255) save_combifahrenheit = 122;
  if (save_tempSet_on == 255) save_tempSet_on = 80;
  if (save_humidSet_on == 255) save_humidSet_on = 50;
  if (keylocklock == 255) keylocklock = 0;
  if (save_combiPLUS2 == 255) save_combiPLUS2 = 50;
  if (bothChange == 255) bothChange = 0;
  if (Preheat_hh == 255) Preheat_hh = 5;
  if (Preheat_mm == 255) Preheat_mm = 0;
  if (hh == 255) hh = 6;
  if (mm == 255) mm = 0;
  if (ss == 255) ss = 0;




  if (saveSteamer == 255) saveSteamer = 0;
  if (enableUnlimitedTime == 255) enableUnlimitedTime = 0;
  if (hh_prerun == 255) hh_prerun = 0;
  if (mm_prerun == 255) mm_prerun = 0;
  if (fanOff_PRERUN == 255) fanOff_PRERUN = 0;
  if (steamerOff_PRERUN == 255) steamerOff_PRERUN = 0;
  if (combiPLUS == 255) combiPLUS = 50;
  if (hh_session == 255) hh_session = 6;
  if (mm_session == 255) mm_session = 0;
  if (tempSet_read == 255) tempSet_read = 80;
  if (HumidSet_read == 255) HumidSet_read = 50;
  if (sessionTime_data == 255) sessionTime_data = 21600;
   


  // ICSC.registerCommand('new', &onoff);
  ICSC.process();
  ICSC.registerCommand('s', &sessionSet);          //                    1
  ICSC.registerCommand('t', &temperatureSet);      //                2
  ICSC.registerCommand('x', &actualTemperature1);  //hundreds    3
  ICSC.registerCommand('z', &combi);               //to let the interface know that the board is in combi5
  ICSC.registerCommand('l', &VERSION);             //tenths                 6
  ICSC.registerCommand('R', &remoteOn);            //tenths                7
  ICSC.registerCommand('q', &ERROR1);              //para sa off                  8
  ICSC.registerCommand('m', &steamLevel);          //tenths              12
  ICSC.registerCommand('n', &combiDetect);         //receive what sensor is using   13
  ICSC.registerCommand('p', &preHeat);             //tenths                 14
  ICSC.registerCommand('I', &receiveFromBoard);    //tenths        15
  ICSC.registerCommand('g', &fanDetect);           //tenths               16
  ICSC.registerCommand('y', &fillDetect);          //tenths              17
  ICSC.registerCommand('B', &HOT);                 //tenths             18
  ICSC.registerCommand('A', &humidityData);        //tenths             19
  ICSC.registerCommand('h', &smdNTC);              //tenths             19
  ICSC.registerCommand('H', &hiTempSmd);           //                  1
                                                   //------------------------------New Communication variables added--------------------------------------
  ICSC.registerCommand('P', &backtoyou);
  ICSC.registerCommand('E', &lighttoyou);
  ICSC.registerCommand('TT', &targettemp);
  ICSC.registerCommand('ct', &sessionTime);
  ICSC.registerCommand('N', &nowifi);
  ICSC.registerCommand('j', &nonetwork);
  save_steamerOff_PRERUN = steamerOff_PRERUN;
  //-------------------------------------------------------------------------------------------------------
  ICSC.send(5, 'A', 1, (char *)&advUser_data);
  delay(1);
}

void sendtime() {
  static unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis >= 8000) {
    lastMillis = currentMillis;
    down;
    tempSet_on;
    // buttonOnPressed;
    // lightActive;
    ICSC.send(9, 'H', 5, (char *)&down);
    ICSC.send(9, 'tt', 2, (char *)&tempSet_on);
    // ICSC.send(5, 'W', 1, (char *)&buttonOnPressed);
    // ICSC.send(0, 'l', 1, (char *)&lightActive);
    // ICSC.send(9, 'M', 5, (char *)&mm);
    // ICSC.send(9, 'S', 5, (char *)&ss);
  }
}


ISR(TIMER1_COMPA_vect) {

  if (enableUnlimitedTime == 0 && remoteOn_data && buttonOnPressed == 2) {
    down--;
  }

  if (buttonOnPressed == 2) {
    backToTempView++;
    prevmenuMillis++;
    prevdurationSetTemp++;
    prevfiveMinutes++;
    togglemillis++;
    displayblinkState = !displayblinkState;
    if (!remoteOn_data) {
      alternateDisplayGo++;
    }
    if (remoteOn_data && displayKLockGo) {
      Klock++;
    }
    if (HOT_data && setTempDisplay_On) {
      steamerMillis++;
    }
  }
  if (preRunSet_running == 1) {
    preRunSet_down--;
    resetMillis++;
    prevblinkRunning++;
    blinkDisplayState = !blinkDisplayState;
  }
  if (buttonOnPressed == 3) {
    DryingTime--;
  }
  if (!preRunSet && !preRunSet_running && fanOff) {
    if (fanOff == 1) {
      fanTimeMillis++;
    }
  }
  sendtime();
}

void lighttoyou(unsigned char source, char command, unsigned char length, char *data) {
  lighttoyou_data = *data;



  if (lighttoyou_data == true) {
    lightActive = 1;
    ICSC.send(0, 'l', 1, (char *)&lightActive);
    displayLed(11);
  } else if (lighttoyou_data == false) {
    lightActive = 0;
    ICSC.send(0, 'l', 1, (char *)&lightActive);
  }
}
// void onoff(unsigned char src, char command, unsigned char len, char *data) {

//   buttonOnPressedappui_data = *(int *)data;
//   unsigned long delayActivateMillis[3];
//   EEPROM.write(29, buttonOnPressedappui_data);
//   if (ERROR1_data != 7) {
//     if (remoteOn_data != 0) {
//       if (downbtn == LOW) {
//         if ((buttonOnPressedappui_data == 4) || (buttonOnPressedappui_data == 3)) {
//           if (powerbtnStop == false && millis() - delayActivateMillis[0] > 100) {
//             if (buttonOnPressed == 1) {
//               if (errorTrue == false) {
//                 if (preRunSet == 0 && bothDisplay == false) {
//                   if (ERROR1_data != 9)
//                     buttonOnPressed = 2;
//                   else {
//                     displayFanOffMode = 2;
//                     pzDetect = 1;
//                     intervalBuz = 100;
//                   }
//                 }
//                 if (preRunSet == 1)
//                   preRunSet = 0;

//                 if (preRunSet_running == 1) {
//                   preRunSet = 0;
//                   preRunSet_running = 0;
//                 }
//               } else {

//                 buttonOnPressed = 1;
//                 errorTrue = false;
//                 activatederror = 0;
//                 preRunSet = 0;
//               }
//             } else if (buttonOnPressed == 3)
//               buttonOnPressed = 1;
//             else {  //buttonOnPressed==2
//               if (steamerOff == 1) {
//                 buttonOnPressed = 3;
//                 DryingTime = 2400;
//               } else
//                 buttonOnPressed = 1;
//             }
//             powerbtnStop = true;
//           }
//         } else {
//           delayActivateMillis[0] = millis();
//           powerbtnStop = false;
//         }
//       }
//     }
//   }
// }
void sessionTime(unsigned char source, char command, unsigned char length, char *data) {
  sessionTime_data = *(unsigned long *)data;
  if (sessionTime_data != prev_sessionTime_data) {
    prev_sessionTime_data = sessionTime_data;
    intervalBuz = 300;
    pzDetect = 1;
    savePoint = 1;
    nextSession = 0;
    savePoints[0] = 1;
    down = sessionTime_data;
    ICSC.send(9, 'H', 5, (char *)&down);
    if (down > 300) {
      hh = ((down / 3600) % 100);
      mm = ((down / 60) % 60);
      ss = down % 60;
      EEPROM.write(6, hh);
      EEPROM.write(7, mm);
      EEPROM.write(2, ss);
      savePoints[0] = 0;
    }
  }
}


void backtoyou(unsigned char source, char command, unsigned char length, char *data) {
  delay(500);
  backtoyou_data = *data;
  EEPROM.write(29, backtoyou_data);
  unsigned long delayActivateMillis[3];

  if (ERROR1_data != 7) {
    if (remoteOn_data != 0) {
      if (downbtn == LOW) {
        if ((backtoyou_data == true) || (backtoyou_data == false)) {
          if (powerbtnStop == false && millis() - delayActivateMillis[0] > 100) {
            if (buttonOnPressed == 1) {
              if (errorTrue == false) {
                if (preRunSet == 0 && bothDisplay == false) {
                  if (ERROR1_data != 9)
                    buttonOnPressed = 2;
                  else {
                    displayFanOffMode = 2;
                    pzDetect = 1;
                    intervalBuz = 100;
                  }
                }
                if (preRunSet == 1)
                  preRunSet = 0;

                if (preRunSet_running == 1) {
                  preRunSet = 0;
                  preRunSet_running = 0;
                }
              } else {

                buttonOnPressed = 1;
                errorTrue = false;
                activatederror = 0;
                preRunSet = 0;
              }
            } else if (buttonOnPressed == 3)
              buttonOnPressed = 1;
            else {  //buttonOnPressed==2
              if (steamerOff == 1) {
                buttonOnPressed = 3;
                DryingTime = 2400;
              } else
                buttonOnPressed = 1;
            }
            powerbtnStop = true;
          }
        } else {
          delayActivateMillis[0] = millis();
          powerbtnStop = false;
        }
      }
    }
  }
}
void fanDetect(unsigned char src, char command, unsigned char len, char *data) {
  fanDetect_data = *data;
}

#define MAX_TEMP_C 90
#define MIN_TEMP_C 30
void targettemp(unsigned char src, char command, unsigned char len, char *data) {
  tempSet_on_ESP2 = *(int *)data;

  if (tempSet_on_ESP2 != prev_tempSet_on_ESP2) {
    prev_tempSet_on_ESP2 = tempSet_on_ESP2;

    // Clamp temperature
    if (tempSet_on_ESP2 > MAX_TEMP_C) {
      tempSet_on_ESP2 = MAX_TEMP_C;
    } else if (tempSet_on_ESP2 < MIN_TEMP_C) {
      tempSet_on_ESP2 = MIN_TEMP_C;
    }

    intervalBuz = 300;
    pzDetect = 1;
    savePoint = 1;
    nextSession = 0;
    savePoints[0] = 1;

    tempSet_on = tempSet_on_ESP2;
    save_tempSet_on = tempSet_on;
    tempSet_on_data = tempSet_on_ESP2;


    ICSC.send(9, 'tt', 2, (char *)&tempSet_on);
    ICSC.send(5, 'k', 5, (char *)&tempSet_on_data);
  }
}

// void targetFah(unsigned char src, char command, unsigned char len, char *data) {
//   tempSet_on_ESP = *(int *)data;
//   if (tempSet_on_ESP != prev_tempSet_on_ESP) {
//     prev_tempSet_on_ESP = tempSet_on_ESP;
//     savePoint = 1;
//     intervalBuz = 300;
//     pzDetect = 1;
//     savePoint = 1;
//     nextSession = 0;
//     savePoints[0] = 1;
//     tempSet_on_Fah = tempSet_on_ESP;
//     save_fahrenheit = fahrenheit;
//     fahrenheit = tempSet_on_ESP;  //sauna_temperature
//     EEPROM.write(14, save_fahrenheit);
//   }
// }

void combi(unsigned char src, char command, unsigned char len, char *data) {
  combi_data = *data;
  if (combi_data == 0) {
    steamerOff = 0;
    steamerOff_PRERUN = 0;
  }
}
void temperatureSet(unsigned char src, char command, unsigned char len, char *data) {
  delay(10);
  tempDATA = *(int *)data;
  if (tempDATA == 0) {
    temperatureSet_data = 90;
    humidLimit = 55;
  } else if (tempDATA == 1) {
    temperatureSet_data = 120;
    humidLimit = 65;
  }
}


void steamLevel(unsigned char src, char command, unsigned char len, char *data) {
  fill_dry_buzz = 500;
  steamLevel_data = *data;
  if (steamLevel_data == 2) {
    if (buttonOnPressed == 2) {
      steamerOff = 0;
    } else {
      steamerOff_PRERUN = 0;
      tempSet_display = tempSet_read;

      ICSC.send(5, 'k', 5, (char *)&tempSet_display);
    }
  }
}
void dipSwitch9(unsigned char src, char command, unsigned char len, char *data) {
  dipSwitch9_data = *data;
}
void hiTempSmd(unsigned char src, char command, unsigned char len, char *data) {
  hiTempSmd_data = *data;
}
void combiDetect(unsigned char src, char command, unsigned char len, char *data) {
  combiDetect_data = *data;
  dontSendYet++;
}
void HOT(unsigned char src, char command, unsigned char len, char *data) {
  steamerOff = 0;
  //laststeamerOff = steamerOff;
  HOT_data = *data;
}
void preHeat(unsigned char src, char command, unsigned char len, char *data) {
  preHeat_data = *data;
}
void smdNTC(unsigned char src, char command, unsigned char len, char *data) {
  smdNTC_data = *data;
  dontSendYet++;
}

void fillDetect(unsigned char src, char command, unsigned char len, char *data) {
  fill_dry_buzz = 1500;
  fillDetect_data = *data;
}

void receiveFromBoard(unsigned char src, char command, unsigned char len, char *data) {
  receiveFromBoard_data = 1;
  powerStateOfBoard = *data;
  dontSendYet++;
}
void humidityData(unsigned char src, char command, unsigned char len, char *data) {
  humidityData_data = *data;
  dontSendYet++;
}

void remoteOn(unsigned char src, char command, unsigned char len, char *data) {
  remoteOn_data = *data;
}
void actualTemperature1(unsigned char src, char command, unsigned char len, char *data) {
  actualTemperature_data = *data;
  dontSendYet++;
}

void sessionSet(unsigned char src, char command, unsigned char len, char *data) {
  sessionSet_data = *data;  //v12
  if (sessionSet_data == 1 || sessionSet_data == 2 || sessionSet_data == 3) {
    no40min = 1;
  }
  switch (sessionSet_data) {
    case 0:
      maxTime = 21600;  //session time 6hours
      DHP = 1;
      break;
    case 1:
      maxTime = 3600;  //1hour
      DHP = 1;
      break;
    case 2:
      maxTime = 7200;  //2hours
      DHP = 1;
      break;
    case 3:
      maxTime = 14400;  //4hour
      DHP = 1;
      break;
    case 4:
      maxTime = 28800;  //8hour
      DHP = 2;
      break;
    case 5:
      maxTime = 43200;  //12hour
      DHP = 2;
      break;
    case 6:
      maxTime = 64800;  //18hours
      DHP = 3;
      break;
    case 7:
      unlitime = 1;
      maxTime = 86400;  //24hours
      DHP = 3;
      break;
  }
  if (DHP == 1) {
    preRunSet_time = 21600;  // its in min equivalent to 6 hours
  }
  if (DHP == 2 || DHP == 3) {
    preRunSet_time = 356400;
  }
}

void VERSION(unsigned char src, char command, unsigned char len, char *data) {
  VERSION_data = *data;
}
void safetySwitch(unsigned char src, char command, unsigned char len, char *data) {
  safetySwitch_data = *data;
  if (safetySwitch_data == 1) {
    lightActive = 1;
    ICSC.send(0, 'l', 5, (char *)&lightActive);  //send signal to on
  }
}
void ERROR1(unsigned char src, char command, unsigned char len, char *data) {
  ERROR1_data = *data;  //indicator
  if ((ERROR1_data >= 1 && ERROR1_data <= 8) || ERROR1_data == 10) {
    errorTrue = true;
    lightActive = 1;
    ICSC.send(0, 'l', 5, (char *)&lightActive);  //send signal to on
    buttonOnPressed = 1;
  }
}
void nowifi(unsigned char src, char command, unsigned char len, char *data) {

  E11_data = *data;
}
void nonetwork(unsigned char src, char command, unsigned char len, char *data) {

  E12_data = *data;
}
unsigned long tenSecondsSendMillis;
unsigned long delayActivateMillis[3];

void loop() {

  ICSC.process();

  if (receiveFromBoard_data == 1) {

    if (millis() - receiveMillis > 100) {
      ICSC.send(5, 'I', 1, NULL);  //send signal to on
      receiveFromBoard_data = 0;
      NoLongerConnected = millis();
      dontSendYet = 0;
    }
  } else {
    receiveMillis = millis();
    if (millis() - NoLongerConnected > 10000) {
      if (VERSION_data == 0) {
        ERROR1_data = 7;
        ICSC.send(9, 'E', 1, (char *)&ERROR1_data);
        errorTrue = true;
        buttonOnPressed = 1;
      } else {
        ERROR1_data = 7;
        ICSC.send(9, 'E', 1, (char *)&ERROR1_data);
        errorTrue = true;
        buttonOnPressed = 1;
      }
    }
  }

  if (millis() < 3000) {
    //send this to let the board know that it is connected with userAdvceInterface
    if (millis() <= 2000 && millis() > 1100)
      displayNumber(VERSION_data);

    if (millis() > 2000)
      displayS(versionNumber);

    previousMilBuz = millis();
    intervalBuz = 100;
  } else {
    //to stop from diverging thier data from one another
    buttonFunction();

    if (ERROR1_data != 7) {
      if (remoteOn_data != 0) {
        if (downbtn == LOW) {
          if (powerbtn == HIGH) {

            if (powerbtnStop == false && millis() - delayActivateMillis[0] > 100) {
              if (buttonOnPressed == 1) {
                if (errorTrue == false) {
                  if (preRunSet == 0 && bothDisplay == false) {
                    if (ERROR1_data != 9)
                      buttonOnPressed = 2;
                    else {
                      displayFanOffMode = 2;
                      pzDetect = 1;
                      intervalBuz = 100;
                    }
                  }
                  if (preRunSet == 1)
                    preRunSet = 0;

                  if (preRunSet_running == 1) {
                    preRunSet = 0;
                    preRunSet_running = 0;
                  }
                } else {
                  ICSC.send(5, 'W', 1, (char *)&buttonOnPressed);

                  buttonOnPressed = 1;
                  errorTrue = false;
                  activatederror = 0;
                  preRunSet = 0;
                }
              } else if (buttonOnPressed == 3)
                buttonOnPressed = 1;
              else {  //buttonOnPressed==2
                if (steamerOff == 1) {
                  buttonOnPressed = 3;
                  DryingTime = 2400;
                } else
                  buttonOnPressed = 1;
              }
              powerbtnStop = true;
            }

          } else {
            delayActivateMillis[0] = millis();
            powerbtnStop = false;
          }
        }
      }
    }

    if (buttonOnPressed != lastbuttonOnPressed) {
      if (errorTrue == false)
        ICSC.send(5, 'W', 1, (char *)&buttonOnPressed);



      powerStateOfBoard = buttonOnPressed;
      lastbuttonOnPressed = buttonOnPressed;
    }

    if (VERSION_data >= 7) {
      if (buttonOnPressed != powerStateOfBoard) {
        ICSC.send(5, 'W', 1, (char *)&buttonOnPressed);

        powerStateOfBoard = buttonOnPressed;
      }
    } else {
      if (millis() - tenSecondsSendMillis >= 5000 && dontSendYet == 0 && errorTrue == false && buttonOnPressed == 1) {
        ICSC.send(5, 'W', 1, (char *)&buttonOnPressed);  //send signal to off



        tenSecondsSendMillis = millis();
      }
    }

    if (displayBlink2 == 1) {
      static unsigned long errorblink1 = millis();
      if (millis() - errorblink1 >= 1000) {
        errorAlternate = !errorAlternate;
        errorblink1 = millis();
      }
      static unsigned long twoSeconds = millis();
      if (millis() - twoSeconds >= 500) {
        pzDetect = 1;
        intervalBuz = 200;
        twoSeconds = millis();
      }
    }

    if (buttonOnPressed == 2) {
      if (ERROR1_data == 9)
        ERROR2_data = 1;

      if (ERROR1_data == 0)
        ERROR2_data = 0;
    }

    if (remoteOn_data == 0) {
      if (errorTrue == false) {
        if (ERROR1_data != 9) {
          if (buttonOnPressed == 3) {
            buttonOnPressed = 1;
            delay(10);
          } else
            buttonOnPressed = 2;
        } else {
          if (stopBeep == 1) {
            displayFanOffMode = 2;
            pzDetect = 1;
            intervalBuz = 100;
            stopBeep = 0;
          }
        }
      }
      triggerOFF = 1;
    }

    if (remoteOn_data == 1)
      stopBeep = 1;

    if (triggerOFF == 1 && remoteOn_data == 1) {
      if (buttonOnPressed == 2) {
        if (steamerOff == 0)
          buttonOnPressed = 1;
        else
          buttonOnPressed = 3;
      }
      errorTrue = false;
      preRunSet_running = 0;
      preRunSet = 0;
      triggerOFF = 0;
    }
    piezoBuzz();
    buzzLimit();
    menu();
    lightFunction();
    if (fanOff != fanOfflast) {
      ICSC.send(0, 'f', 5, (char *)&fanOff);
      fanOfflast = fanOff;
    }
    off();


    if (smdCount == 4 && smdCount2 == 3) {
      if (buttonOnPressed == 1) {
        displayFanOffMode = 3;
        preRunSet = 0;
      } else
        smdDetected = 1;
    }
    if (smdCount == 6 && smdCount2 == 3) {
      if (buttonOnPressed == 1) {
        displayFanOffMode = 4;
        preRunSet = 0;
      }
    }
    if (smdCount == 8 && smdCount2 == 3) {
      if (buttonOnPressed == 1) {
        ICSC.send(5, 'H', 1, NULL);  //send signal to off
        preRunSet = 0;
      }
    }

    if (menubtn == HIGH)
      displayCurrentTemp = 1;
    else {
      if (displayCurrentTemp == 1) {
        smdCount++;
        displayCurrentTemp = 0;
      }
    }

    if (lightActive == 1) {
      if (lightStop == 1) {
        smdCount2++;
        lightStop = 0;
      }
    } else
      lightStop = 1;

    if (steamerOff != laststeamerOff) {
      ICSC.send(5, 'C', 5, (char *)&steamerOff);
      if (no40min == 0) {
        if (steamerOff == 1) {
          if (DHP != 3)
            maxTimeDown = maxTimeDown - 2400;

          addTime = 1;
        }
      }
      tempSet_on_data = (steamerOff == 0) ? tempSet_on : humidSet_on;

      ICSC.send(5, 'k', 5, (char *)&tempSet_on_data);



      laststeamerOff = steamerOff;
    }
  }


  if (combiDetect_data == 3) {
    steamerOff = 0;
    steamerOff_PRERUN = 0;
  }

  if (HOT_data == 0)
    steamerMillis = 0;

  if (fastbeep3 == 1) {
    fastBeeping2();
    fastbeep3 = 0;
  }
}


void numbers(byte x) {
  switch (x) {
    case 0:
      PORTB &= ~(1 << 0);  //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB &= ~(1 << 3);  //d
      PORTB &= ~(1 << 4);  //e
      PORTB &= ~(1 << 5);  //f
      PORTC |= (1 << 0);   //g
      break;
    case 1:
      PORTB |= (1 << 0);   //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB |= (1 << 3);   //d
      PORTB |= (1 << 4);   //e
      PORTB |= (1 << 5);   //f
      PORTC |= (1 << 0);   //g
      break;
    case 2:
      PORTB &= ~(1 << 0);  //a
      PORTB &= ~(1 << 1);  //b
      PORTB |= (1 << 2);   //c
      PORTB &= ~(1 << 3);  //d
      PORTB &= ~(1 << 4);  //e
      PORTB |= (1 << 5);   //f
      PORTC &= ~(1 << 0);  //g
      break;
    case 3:
      PORTB &= ~(1 << 0);  //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB &= ~(1 << 3);  //d
      PORTB |= (1 << 4);   //e
      PORTB |= (1 << 5);   //f
      PORTC &= ~(1 << 0);  //g
      break;
    case 4:
      PORTB |= (1 << 0);   //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB |= (1 << 3);   //d
      PORTB |= (1 << 4);   //e
      PORTB &= ~(1 << 5);  //f
      PORTC &= ~(1 << 0);  //g
      break;
    case 5:
      PORTB &= ~(1 << 0);  //a
      PORTB |= (1 << 1);   //b
      PORTB &= ~(1 << 2);  //c
      PORTB &= ~(1 << 3);  //d
      PORTB |= (1 << 4);   //e
      PORTB &= ~(1 << 5);  //f
      PORTC &= ~(1 << 0);  //g
      break;
    case 6:
      PORTB &= ~(1 << 0);  //a
      PORTB |= (1 << 1);   //b
      PORTB &= ~(1 << 2);  //c
      PORTB &= ~(1 << 3);  //d
      PORTB &= ~(1 << 4);  //e
      PORTB &= ~(1 << 5);  //f
      PORTC &= ~(1 << 0);  //g
      break;
    case 7:
      PORTB &= ~(1 << 0);  //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB |= (1 << 3);   //d
      PORTB |= (1 << 4);   //e
      PORTB |= (1 << 5);   //f
      PORTC |= (1 << 0);   //g
      break;
    case 8:
      PORTB &= ~(1 << 0);  //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB &= ~(1 << 3);  //d
      PORTB &= ~(1 << 4);  //e
      PORTB &= ~(1 << 5);  //f
      PORTC &= ~(1 << 0);  //g
      break;
    case 9:
      PORTB &= ~(1 << 0);  //a
      PORTB &= ~(1 << 1);  //b
      PORTB &= ~(1 << 2);  //c
      PORTB &= ~(1 << 3);  //d
      PORTB |= (1 << 4);   //e
      PORTB &= ~(1 << 5);  //f
      PORTC &= ~(1 << 0);  //g
      break;
  }
}


void displayNumber3(int toDisplay) {  //for fahrenhiet 3 digit display
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        numbers(toDisplay / 100);
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        numbers((toDisplay % 100) / 10);
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        numbers((toDisplay % 100) % 10);
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}


void buttonFunction() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  if (digitalRead(1) == LOW)  //10
  {
    menubtn = HIGH;
  } else menubtn = LOW;

  if (digitalRead(2) == LOW)  //9
  {
    powerbtn = HIGH;
  } else
    powerbtn = LOW;

  if (digitalRead(0) == 0)  //minus button//8
  {
    downbtn = HIGH;
  } else downbtn = LOW;

  if (digitalRead(3) == 0)  //plus button//11
  {
    upbtn = HIGH;
  } else upbtn = LOW;
  DDRB |= (1 << 0);
  DDRB |= (1 << 1);
  DDRB |= (1 << 2);
  DDRB |= (1 << 3);
  PORTB |= (1 << 0);
  PORTB |= (1 << 1);
  PORTB |= (1 << 2);
  PORTB |= (1 << 3);
}


long plus(unsigned long data) {
  if (upbtn == HIGH) {
    if (buttonActiveHigh == false) {
      buttonActiveHigh = true;
      longPressTimeHigh = millis();
    }
    if ((millis() - longPressTimeHigh) > longPressTime2 && no_button_work == 0) {
      longPressActiveHigh = true;
      //
      unsigned long fastCount = millis();
      if (fastCount - prevfastCount >= debfastCount) {
        prevfastCount = fastCount;
        fastCnt++;
        if (fastCnt > 35) {
          fastCnt = 35;
        }
        if (fastCnt >= 0 && fastCnt < 6) {
          debfastCount = 250;
        } else if (fastCnt >= 6 && fastCnt < 20) {
          debfastCount = 175;
        } else if (fastCnt >= 20 && fastCnt < 35) {
          debfastCount = 100;
        } else debfastCount = 50;
        data++;
        if (buttonOnPressed == 2) {
          if (menu_On_setttings == 2) {
            data = data + 300;
          }
        }
      }
    }
  } else {
    if (buttonActiveHigh == true) {
      //
      if (longPressActiveHigh == true) {
        longPressActiveHigh = false;
        fastCnt = 0;
        debfastCount = 250;
      } else {
        data++;
        if (buttonOnPressed == 2) {
          if (menu_On_setttings == 2) {
            data = data + 300;
          }
        }
      }
      buttonActiveHigh = false;
    }
  }
  return data;
}
long minus(unsigned long data) {
  if (downbtn == HIGH) {
    if (buttonActiveLow == false) {
      buttonActiveLow = true;
      longPressTimeLow = millis();
    }
    if ((millis() - longPressTimeLow) > longPressTime2 && no_button_work == 0) {
      longPressActiveLow = true;
      //
      unsigned long fastCount = millis();
      if (fastCount - prevfastCount >= debfastCount) {
        prevfastCount = fastCount;
        fastCnt++;
        if (fastCnt > 35) {
          fastCnt = 35;
        }
        if (fastCnt >= 0 && fastCnt < 6) {
          debfastCount = 250;
        } else if (fastCnt >= 6 && fastCnt < 20) {
          debfastCount = 175;
        } else if (fastCnt >= 20 && fastCnt < 35) {
          debfastCount = 100;
        } else debfastCount = 50;
        data--;
        if (buttonOnPressed == 2) {
          if (menu_On_setttings == 2) {
            data = data - 300;
          }
        }
      }
    }
  } else {
    if (buttonActiveLow == true) {
      //
      if (longPressActiveLow == true) {
        longPressActiveLow = false;
        fastCnt = 0;
        debfastCount = 250;
      } else {
        data--;
        if (buttonOnPressed == 2) {
          if (menu_On_setttings == 2) {
            data = data - 300;
          }
        }
      }
      buttonActiveLow = false;
    }
  }
  return data;
}

void downtime() {


  if (down > maxTimeDown) {
    down = maxTimeDown;
  }
  if (down == 0) {

    hh = EEPROM.read(6);
    mm = EEPROM.read(7);
    ss = EEPROM.read(2);
    down = (hh * 3600) + (mm * 60) + ss;
    ICSC.send(9, 'H', 5, (char *)&down);
    // ICSC.send(9, 'M', 5, (char *)&mm);
    // ICSC.send(9, 'S', 5, (char *)&ss);





    // Send the retrieved hour and minute values

    if (steamerOff == 0) {
      buttonOnPressed = 1;
    } else {
      buttonOnPressed = 3;
      DryingTime = 2400;
    }

    pzDetect = 1;
    intervalBuz = 5000;
  }
}
// Function to send time using ICSC protocol


void downtime_preSetRun() {
  if (preRunSet_down <= 0) {
    buttonOnPressed = 2;
  }
}


void menu() {
  if (menubtn == HIGH) {
    if (buttonActive == false) {
      buttonActive = true;
      buttonTimer = millis();
      buttonTimer2 = millis();
    }
    if ((millis() - buttonTimer) > longPressTime && (longPressActive == false)) {
      longPressActive = true;
      if (buttonOnPressed == 2) {
        if (remoteOn_data != 0) {
          if (keylocklock == 0) {
            if (menu_On == false) {
              menu_On = true;
            } else {
              if (HOT_data == 0 && fillDetect_data == 0 && steamLevel_data == 0) {
                pzDetect = 1;
                intervalBuz = 300;
                menu_On = false;
              }
            }
          } else {
            if (setTempDisplay_On == 1) {
              pzDetect = 1;
              intervalBuz = 100;
              displayKLockGo = 1;
              Klock = 0;
            }
          }
        }
      } else {
        if (preRunSet == 1) {
          intervalBuz = 100;
          pzDetect = 1;
          preRunSet_running = 1;
        }
      }
    }
  } else {
    if (buttonActive == true) {
      if (longPressActive == true) {
        longPressActive = false;
      } else if ((millis() - buttonTimer2 >= 10) && longPressActive == false) {
        if (buttonOnPressed == 2) {
          if (setTempDisplay_On == 0) {
            setTempDisplay_On = 1;
          }
          if (remoteOn_data != 0) {
            if (setTempDisplay_On == 1) {
              menu_On_setttings++;
              if (menu_On == false) {
                toggleisPressed = 1;
                togglemillis = 0;
              }
            }
          }
        } else {
          if (preRunSet == 0 && preRunSet_running == 0 && preRunSet_time != 0) {
            if (ERROR1_data != 9 && keylocklock == 0) {
              preRunSet = 1;
              ICSC.send(0, 'n', 1, (char *)&preRunSet);
            } else {
              if (ERROR1_data == 9) {
                displayFanOffMode = 2;
              } else {
                if (keylocklock == 1) displayFanOffMode = 5;
              }

              pzDetect = 1;
              intervalBuz = 100;
            }
          }
          if (preRunSet == 1 || preRunSet_running == 1) {
            preRunSet_setting++;
            blinkingLed = 1;
            ledSlow = LOW;  //when pressed u see the red light 1st before it will off
            previousSlow = millis();
            prevblinkRunning = 0;
          }
        }
      }
      buttonActive = false;
    }
  }
  if (preRunSet_setting > 5) {
    preRunSet_setting = 0;
  }
}


double Thermister(double RawADC) {
  double Temp;
  Temp = 10000 * (RawADC * (5 / 1023.0)) / (5 - (RawADC * (5 / 1023.0)));
  Temp = 1 / (0.001138177396 + 0.0002326061337 * log(Temp) + 0.0000000961782205 * log(Temp) * log(Temp) * log(Temp));
  Temp = Temp - 273;
  return Temp;
}

void preHeat_timeCountdown() {
  unsigned long preHeat_down = millis();
  if (preHeat_down - prevpreHeat_down >= 1000) {
    prevpreHeat_down = preHeat_down;
    preHeat_startDown++;
  }
}


void noDisplay7Seg() {
  PORTB |= (1 << 0);  //a
  PORTB |= (1 << 1);  //b
  PORTB |= (1 << 2);  //c
  PORTB |= (1 << 3);  //d
  PORTB |= (1 << 4);  //e
  PORTB |= (1 << 5);  //f
  PORTC |= (1 << 0);  //g
  PORTC |= (1 << 1);  //dp

  PORTC |= (1 << 2);  //col1
  PORTC |= (1 << 3);  //col2
  PORTC |= (1 << 4);  //col3
  PORTC |= (1 << 5);  //col4
  PORTD |= (1 << 4);  //col5
}



void displayOff() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC |= (1 << 0);   //g
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 0);  //a
        PORTB |= (1 << 1);   //b
        PORTB |= (1 << 2);   //c
        PORTB |= (1 << 3);   //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 0);  //a
        PORTB |= (1 << 1);   //b
        PORTB |= (1 << 2);   //c
        PORTB |= (1 << 3);   //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}



void displayS(uint8_t versionNumber) {
  // Your existing displayS function code goes here

  for (uint8_t digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        PORTC &= ~(1 << 2);  // col1
        numbers(versionNumber / 10);
        break;
      case 1:
        PORTC &= ~(1 << 3);  // col2
        numbers(versionNumber % 10);
        break;
      case 3:
        if (combi_data == 1) {
          PORTC &= ~(1 << 5);  // col4
          numbers(5);
        }
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}


void displayColon() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:

        break;
      case 1:

        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTC &= ~(1 << 1);  //dp
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTC &= ~(1 << 1);  //dp
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}


void displayCel() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}



void displayHot() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}


void displayFah() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}


void displayOn() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC |= (1 << 0);   //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB |= (1 << 0);   //a
        PORTB |= (1 << 1);   //b
        PORTB &= ~(1 << 2);  //c
        PORTB |= (1 << 3);   //d
        PORTB &= ~(1 << 4);  //e
        PORTB |= (1 << 5);   //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}



void setBlinkLed(int toBlink) {
  unsigned long currentMilBlink = millis();
  if (currentMilBlink - previousMilBlink > intervalBlink) {
    previousMilBlink = currentMilBlink;
    ledBlink = !ledBlink;
  }
  if (ledBlink == LOW) {
    displayLed(toBlink);
  }
}

void blinkSlowLed(int toBlink) {
  unsigned long currentSlow = millis();
  if (currentSlow - previousSlow > slowBlink) {
    previousSlow = currentSlow;
    ledSlow = !ledSlow;
  }
  if (ledSlow == LOW) {
    displayLed(toBlink);
  }
}

void blinkFastLed(int toBlink) {
  unsigned long currentFast = millis();
  if (currentFast - previousFast > fastBlink) {
    previousFast = currentFast;
    ledFast = !ledFast;
  }
  if (ledFast == LOW) {
    displayLed(toBlink);
  }
}

void displayMin(byte toDisplay) {  //display Minutes 7 segment
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col4
        PORTC &= ~(1 << 1);  //dp
        numbers(toDisplay / 10);
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTC &= ~(1 << 1);  //dp
        numbers(toDisplay % 10);
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}



void displayNumberFah3(int toDisplay) {  //for fahrenhiet 3 digit display
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        PORTC &= ~(1 << 2);  //col1
        numbers(toDisplay / 100);
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        numbers((toDisplay % 100) / 10);
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        numbers((toDisplay % 100) % 10);
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 0);  //a
        PORTB |= (1 << 1);   //b
        PORTB |= (1 << 2);   //c
        PORTB |= (1 << 3);   //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}

void displayNumberFah2(int toDisplay) {  //for fahrenhiet 2 digit display
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        numbers(toDisplay / 10);
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        numbers(toDisplay % 10);
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 0);  //a
        PORTB |= (1 << 1);   //b
        PORTB |= (1 << 2);   //c
        PORTB |= (1 << 3);   //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}


void displayLed(byte toDisplayled) {
  PORTD &= ~(1 << 4);  //col5
  switch (toDisplayled) {
    case 11:
      PORTB &= ~(1 << 0);  //a
      break;
    case 12:
      PORTB &= ~(1 << 1);  //b
      break;
    case 13:
      PORTB &= ~(1 << 2);  //c
      break;
    case 14:
      PORTB &= ~(1 << 3);  //d
      break;
    case 15:
      PORTB &= ~(1 << 4);  //e
      break;
    case 16:
      PORTB &= ~(1 << 5);  //f
      break;
    case 33:
      PORTC &= ~(1 << 0);  //g
      break;
    case 69:              // Case to turn off LED corresponding to case 11
      PORTB |= (1 << 0);  // Turn off LED corresponding to case 11
      break;
  }
  delayMicroseconds(100);
  noDisplay7Seg();
  delayMicroseconds(100);
}



void displayNumber(byte toDisplay) {  //2 digit
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        numbers(toDisplay / 10);
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        numbers(toDisplay % 10);
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
    delayMicroseconds(brightness2);
  }
}



void lightFunction() {
  int lightbtn = analogRead(sw3);


  if (lightbtn <= 100) {
    lightbtn = HIGH;
  } else {
    lightbtn = LOW;
  }

  if (lightbtn != lastlightbtn) {
    lightbtnmillis = millis();
  }
  if (millis() - lightbtnmillis >= 20) {
    if (lightbtn != lightbtnState) {
      lightbtnState = lightbtn;
      if (lightbtnState == HIGH) {
        lightActive = !lightActive;
        lightPlus = 0;
      }
    }
  }
  lastlightbtn = lightbtn;
  if (lightActive == 1) {
    displayLed(11);
  }

  if (lightActive != lastlightActive) {
    ICSC.send(0, 'l', 1, (char *)&lightActive);
    lastlightActive = lightActive;
  }
}



void bothbtn() {

  // =====================================
  // BOTH BUTTON HOLD DETECTION (1.5 sec)
  // =====================================
  if (powerbtn == HIGH && downbtn == HIGH && keylocklock == 0) {

    if (!bothActive) {
      bothMillis = millis();
      displayOnce = false;
      bothActive = true;
    }

    if ((millis() - bothMillis >= 1500) && !displayOnce) {

      noToShortPress = 0;

      bothDisplay = true;

      bothChange = !bothChange;

      EEPROM.write(1, bothChange);

      prevbothDisplay = millis();

      displayOnce = true;
    }

  } else {
    bothActive = false;
  }


  // =====================================
  // SCALE CHANGE DISPLAY (Highest priority)
  // =====================================
  if (bothDisplay) {

    if (millis() - prevblinkBoth >= 500) {
      blinkBothStart = !blinkBothStart;
      prevblinkBoth = millis();
    }

    if (blinkBothStart) {

      if (bothChange == 1) {
        displayFah();
      } else {
        displayCel();
      }

    } else {
      displayOn();
    }


    if (millis() - prevbothDisplay >= 2000) {

      bothDisplay = false;

      noToShortPress = 1;
    }

    return;
  }


  // =====================================
  // FAN OFF MODE DISPLAY
  // =====================================
  if (displayFanOffMode != 0) {

    if (millis() - fanOffModeMillis > 1500) {

      displayFanOffMode = 0;

      smdCount = 0;
      smdCount2 = 0;
    }
  }


  if (displayFanOffMode == 1) {

    if (fanOff == 1)
      displayOn();
    else
      displayOff();

    return;
  }

  else if (displayFanOffMode == 2) {

    oPEn();

    return;
  }

  else if (displayFanOffMode == 3) {

    if (smdNTC_data > 99)
      displayNumber3(smdNTC_data);
    else
      displayNumber(smdNTC_data);

    return;
  }

  else if (displayFanOffMode == 4) {

    if (hiTempSmd_data > 99)
      displayNumber3(hiTempSmd_data);
    else
      displayNumber(hiTempSmd_data);

    return;
  }

  else if (displayFanOffMode == 5) {

    displayKLock();

    return;
  }



  // =====================================
  // ERROR DISPLAY PRIORITY
  // E11 = highest
  // E12 = second
  // =====================================
  static unsigned long lastRun = 0;

  const unsigned long interval = 5;

  if (millis() - lastRun >= interval) {

    lastRun = millis();

    if (E11_data != 1) {

      E11();
    }

    else if (E12_data != 1) {

      E12();
    }

    else {

      displayColon();  // NORMAL DISPLAY
    }
  }


  fanOffModeMillis = millis();
}
// void startup() {
//   static unsigned long lastMillis = 0;
//   unsigned long currentMillis = millis();  // Current time in milliseconds

//   if (currentMillis - lastMillis >= 16000) {  // Execute every second
//     lastMillis = currentMillis;
//     // hh = EEPROM.read(6);
//     // mm = EEPROM.read(7);
//     // ss = EEPROM.read(2);
//     // ICSC.send(9, 'H', 2, (char *)&hh);
//     // ICSC.send(9, 'M', 2, (char *)&mm);
//     // ICSC.send(9, 'S', 2, (char *)&ss);
//     // if (EEPROM.read(1) == 1) {
//     //   Tempscale = 1;

//     //   ICSC.send(9, 'TS', 1, (char *)&Tempscale);

//     // } else {

//     //   Tempscale = 2;

//     //   ICSC.send(9, 'TS', 1, (char *)&Tempscale);
//     // }
//     save_tempSet_on = EEPROM.read(3);
//     save_fahrenheit = EEPROM.read(14);
//     ICSC.send(9, 'TF', 2, (char *)&save_fahrenheit);
//     ICSC.send(9, 'tt', 2, (char *)&save_tempSet_on);
//   }
// }

void piezoBuzz() {
  if (pzDetect == 1) {
    tone(peZO, 4000);
    unsigned long currentMilBuz = millis();
    if (currentMilBuz - previousMilBuz > intervalBuz) {
      pzDetect = 0;
    }
  } else {
    noTone(peZO);
    previousMilBuz = millis();
  }
}


void buzzLimit() {
  if (upbtn == HIGH && downbtn == LOW && menubtn == LOW) {
    if (buttonOnPressed == 1) {
      if (preRunSet == 1 || preRunSet_running == 1) {
        switch (preRunSet_setting) {
          case 0:
            if (plusData >= preSession || plusData >= maxTime) {
              fastBeeping();
            }
            break;
          case 1:
            if (preRunSet_down >= preRunTimeMax) {
              fastBeeping();
            }
            break;
          case 4:
            if (steamerOff_PRERUN == 0) {
              if (temperatureSet_data <= tempSet_read) {
                fastBeeping();
              }
            } else {
              if (combiDetect_data == 2) {
                if (temperatureSet_data != 90) {
                  if (HumidSet_read >= 65) {
                    fastBeeping();
                  }
                } else {
                  if (HumidSet_read >= 55) {
                    fastBeeping();
                  }
                }
              }
              if (combiDetect_data == 1) {
                if ((int)x2 <= HumidSet_read) {
                  fastBeeping();
                }
              }
            }
            break;
          case 5:
            if (combiDetect_data == 2) {
              if (combiPLUS >= 100) {
                fastBeeping();
              }
            }
            if (combiDetect_data == 1) {
              if (combiPLUS >= (int)y) {
                fastBeeping();
              }
            }
            break;
        }
      }
    } else {
      if (keylocklock == 0) {
        switch (menu_On_setttings) {
          case 0:
            if (steamerOff == 0) {
              if (temperatureSet_data <= tempSet_on) {
                fastBeeping();
              }
            } else {
              if (combiDetect_data == 2) {
                if (temperatureSet_data != 90) {
                  if (65 <= humidSet_on) {
                    fastBeeping();
                  }
                } else {
                  if (55 <= humidSet_on) {
                    fastBeeping();
                  }
                }
              }
              if (combiDetect_data == 1) {
                if ((int)x2 <= humidSet_on) {
                  fastBeeping();
                }
              }
            }
            break;
          case 1:
            if (combiDetect_data == 2) {
              if (combiPLUS2 >= 100) {
                fastBeeping();
              }
            }
            if (combiDetect_data == 1) {
              if (combiPLUS2 >= (int)y) {
                fastBeeping();
              }
            }
            break;
          case 2:
            if (down >= maxTimeDown) {
              fastBeeping();
            }
            break;
        }
      }
    }
  } else {
    beepBuzzerInterval = 500;
  }

  if (downbtn == HIGH && upbtn == LOW && menubtn == LOW) {
    if (buttonOnPressed == 1) {
      if (preRunSet == 1 || preRunSet_running == 1) {
        switch (preRunSet_setting) {
          case 0:
            if (plusData <= 300) {
              fastBeeping2();
            }
            break;
          case 1:
            if (preRunSet == 1 && preRunSet_running == 0) {
              if ((preRunSet_down / 60) <= 0) {
                fastBeeping2();
              }
            }
            if (preRunSet_running == 1) {
              if ((preRunSet_down / 60) <= 5) {
                fastBeeping2();
              }
            }

            break;
          case 4:
            if (steamerOff_PRERUN == 0) {
              if (tempSet_read <= 30) {
                fastBeeping2();
              }
            } else {
              if (HumidSet_read <= 30) {
                fastBeeping2();
              }
            }

            break;
          case 5:

            if (combiDetect_data == 2) {
              if (combiPLUS <= 30) {
                fastBeeping2();
              }
            }
            if (combiDetect_data == 1) {
              if (combiPLUS <= 15) {
                fastBeeping2();
              }
            }
            break;
        }
      }
    } else {
      if (keylocklock == 0) {
        switch (menu_On_setttings) {
          case 0:
            if (steamerOff == 0) {
              if (tempSet_on <= 30) {
                fastBeeping2();
              }
            } else {
              if (humidSet_on <= 30) {
                fastbeep3 = 1;
              }
            }

            break;
          case 1:
            if (combiDetect_data == 2) {

              if (combiPLUS2 <= 30) {
                fastBeeping2();
              }
            }
            if (combiDetect_data == 1) {
              if (combiPLUS2 <= 15) {
                fastBeeping2();
              }
            }

            break;
          case 2:
            if (down <= 300) {
              fastBeeping2();
            }
            break;
        }
      }
    }
  } else {
    beepBuzzerInterval2 = 500;
  }
}


void off() {
  ICSC.process();
  if (buttonOnPressed == 1) {  //off
    forTemp = HumidSet_read;
    forCombi = combiPLUS;
  } else {  //on
    forTemp = humidSet_on;
    forCombi = combiPLUS2;
    tenSecondsSendMillis = millis();
  }
  //formula
  if (tempDATA == 0) {
    //formula of the curve
    //for temperature settings
    if (forTemp > 59.6 && forTemp <= 90.0) {
      y = 100.0 - sqrt((1635.0 / 13.0) * (forTemp - 30.0));
    } else if (forTemp > 52.579 && forTemp <= 59.6) {
      y = 134.35 - 1.6 * forTemp;
    } else if (forTemp > 45.0 && forTemp <= 52.579) {
      y = 100.0 - sqrt((4250.0 / 13.0) * (forTemp - 45.0));
    } else {
      y = 100.0;
    }
    //for humidity settings
    if (forCombi >= 0.0 && forCombi <= 38.98) {
      x2 = 30.0 + (((13.0) * (100.0 - forCombi) * (100.0 - forCombi)) / 1635.0);
    } else if (forCombi > 38.98 && forCombi < 50.224) {
      x2 = (134.35 - forCombi) / 1.6;
    } else {
      x2 = ((13.0) * (100.0 - forCombi) * (100.0 - forCombi)) / 4250.0 + 45.0;
    }
    //end of the formula
  } else {
    //formula of the curve
    //for temperature settings
    if (forTemp > 69.7 && forTemp <= 120.0) {
      y = 100.0 - sqrt((1635.0 / 13.0) * (forTemp - 40.0));
    } else if (forTemp > 62.531 && forTemp <= 69.7) {
      y = 150.43 - 1.6 * forTemp;
    } else if (forTemp > 55.0 && forTemp <= 62.531) {
      y = 100.0 - sqrt((4250.0 / 13.0) * (forTemp - 55.0));
    } else {
      y = 100.0;
    }
    //for humidity settings
    if (forCombi >= 0.0 && forCombi <= 38.83) {
      x2 = 40.0 + (((13.0) * (100.0 - forCombi) * (100.0 - forCombi)) / 1635.0);
    } else if (forCombi > 38.83 && forCombi < 50.38) {
      x2 = (150.43 - forCombi) / 1.6;
    } else {
      x2 = ((13.0) * (100.0 - forCombi) * (100.0 - forCombi)) / 4250.0 + 55.0;
    }
    //end of the formula
  }
  switch (buttonOnPressed) {
    case 1:  /////////////////////////////////////////////////////////////////OFF
      if (tempDATA == 0) {
        if (save_tempSet_on > 90) {
          save_tempSet_on = 90;
          save_fahrenheit = 194;
        }
        if (save_humidSet_on > 55) {
          save_humidSet_on = 55;
          save_combifahrenheit = 131;
        }
      }
      if (preRunSet_running != lastpreRunSet_running) {
        ICSC.send(5, 'P', 2, (char *)&preRunSet_running);
        lastpreRunSet_running = preRunSet_running;
      }
      savePoint = 0;
      everyOnsend = true;
      oneTimeOnly = 1;
      displayForView = 0;
      prevdurationSetTemp = 0;
      prevfiveMinutes = 0;  //========================5 minutes
      delaySendmillis = 0;
      maxTimeDown = maxTime;  //maximum time as reference for the session time

      if (time_On2 > maxTime)
        time_On2 = maxTime;
      else
        time_On2 = hh * 3600 + mm * 60;


      changeDisplayTemp = false;
      setTempDisplay_On = 0;
      menu_On = false;
      if (errorTrue == false) {
        if (preRunSet == 0 && preRunSet_running == 0)  ///////////////////////////////////////////////////////// /*=================OFF state================*/
        {
          if (fanOff == 1) {
            displayLed(14);
            if (fanTimeMillis > 14400)
              fanOff = 0;
          } else
            fanTimeMillis = 0;
          fanButton();

          if (remoteOn_data == 0 && ERROR1_data == 9) {
            if (powerbtn == HIGH) {
              displayOpen = 1;
            } else {
              if (displayOpen == 1) {
                displayFanOffMode = 2;
                pzDetect = 1;
                intervalBuz = 100;
                displayOpen = 0;
              }
            }
          }
          if (kas_a_lang == true) {
            plusData = maxTime;
            if (time_On2 > maxTime) {
              hh = maxTime / 3600;
              mm = (maxTime / 60) % 60;
              ss = maxTime % 60;
              // ICSC.send(9, 'H', 2, (char *)&hh);
              // ICSC.send(9, 'M', 2, (char *)&mm);
              // ICSC.send(9, 'S', 2, (char *)&ss);
              EEPROM.write(6, hh);
              EEPROM.write(7, mm);
              EEPROM.write(2, ss);
            }
            ICSC.send(0, 'f', 5, (char *)&fanOff);
            kas_a_lang = false;
          }
          displayBlink2 = 0;
          menu_On_setttings = 0;
          if (combiDetect_data == 2) {
            sensorChange = 2;
          }
          if (combiDetect_data == 1) {
            sensorChange = 1;
          }
          if (sensorChange != lastsensorChange) {
            combiPLUS2 = 50;
            humidSet_on = 50;
            save_combiPLUS2 = combiPLUS2;
            save_humidSet_on = humidSet_on;
            EEPROM.write(12, save_combiPLUS2);   //set humidity
            EEPROM.write(11, save_humidSet_on);  //set temp with combi
            EEPROM.write(25, sensorChange);
            combiPLUS = 50;
            HumidSet_read = 50;
            EEPROM.write(22, combiPLUS);      //
            EEPROM.write(27, HumidSet_read);  //
            lastsensorChange = sensorChange;
          }
          tempSet_on = save_tempSet_on;
          //save the temperature
          humidSet_on = save_humidSet_on;  //save the humidity(temeperature ni)
          fahrenheit = save_fahrenheit;

          combifahrenheit = save_combifahrenheit;
          combiPLUS2 = save_combiPLUS2;  //save humidity2
          lastcombiPLUS = combiPLUS;
          lastcombiPLUS2 = combiPLUS2;
          bothbtn();        //pressed simultaenously the down and power btn /////////////// displayColon is in this function
          down = time_On2;  //save the time

          preRunSet_setting = 0;  //to always go back to 1 when menu is pressed
          if (combiDetect_data != 3 && combi_data == 1) {
            steamerOff = saveSteamer;
            steamerOff_PRERUN = save_steamerOff_PRERUN;
          }
          if (resetTemp == 1) {
            ICSC.send(5, 'k', 5, (char *)&tempSet_on_data);  //temperature



            resetTemp = 0;
          }
          preRunSet_adjustTime = (hh_prerun * 3600) + (mm_prerun * 60);
          preRunSet_down = preRunSet_adjustTime;
          if (((hh_session * 3600) + (mm_session * 60)) < plusData) {
            plusData = (hh_session * 3600) + (mm_session * 60);
          }
          displayblinkState = HIGH;
          blinkDisplayState = 1;
          if (resetDisplayMode == 1) {
            smdCount = 0;
            smdCount2 = 0;
            resetDisplayMode = 0;
          }
        }
        if (preRunSet == 1 && preRunSet_running == 0) /*====================== menu state==============*/
        {
          preRunTime = 1;
          noToShortPress = 1;
          preRun_savePoint = 1;
          resetDisplayMode = 1;
          fanOffModeMillis = millis();
        }
        if (preRunSet == 1 || preRunSet_running == 1) /*====================== menu state==============*/
        {
          switch (preRunSet_setting) {
            case 0:  //////////////////////////////////////////////////////////////////////////////////////session
              if (maxTime > plusData) {
                if (preSession > plusData) {
                  plusData = plus(plusData);
                }
              }
              if (plusData > 300) {
                plusData = minus(plusData);
              }
              if (plusData > lastplusData) {
                plusData = plusData + 299;
              }
              if (plusData < lastplusData) {
                plusData = plusData - 299;
              }
              break;
            case 1:  //////////////////////////////////////////////////////////////////////////////////////pre run
              //======================increase or decrease function======================
              unsigned long prerundeb;
              prerundeb = millis();
              if (upbtn == HIGH) {
                if (prerunstop1 == false) {
                  if (preRunTimeMax > preRunSet_down) {
                    if (preRunSet == 1 && preRunSet_running == 0) {
                      preRunSet_down = preRunSet_down + 900;
                    }
                    if (preRunSet_running == 1) {
                      preRunSet_down = preRunSet_down + 300;
                    }
                  }
                  prerunmillis = millis();
                  prerunstop1 = true;
                }
                if (millis() - prerunmillis > 1000) {
                  if (prerundeb - prevprerundeb > debfastCount2) {
                    if (preRunTimeMax > preRunSet_down) {
                      if (preRunSet == 1 && preRunSet_running == 0) {
                        preRunSet_down = preRunSet_down + 900;
                      }
                      if (preRunSet_running == 1) {
                        preRunSet_down = preRunSet_down + 300;
                      }
                    }
                    fastCnt2++;
                    if (fastCnt2 > 35) {
                      fastCnt2 = 35;
                    }
                    if (fastCnt2 >= 0 && fastCnt2 < 6) {
                      debfastCount2 = 250;
                    } else if (fastCnt2 >= 6 && fastCnt2 < 20) {
                      debfastCount2 = 175;
                    } else if (fastCnt2 >= 20 && fastCnt2 < 35) {
                      debfastCount2 = 100;
                    } else debfastCount2 = 50;
                    prevprerundeb = prerundeb;
                  }
                }
              } else {
                prerunstop1 = false;
                debfastCount2 = 250;
                fastCnt2 = 0;
              }
              if (downbtn == HIGH) {
                if (prerunstop2 == false) {
                  if (preRunSet == 1 && preRunSet_running == 0) {
                    if (preRunSet_down > 0) {
                      preRunSet_down = preRunSet_down - 900;
                    }
                  }
                  if (preRunSet_running == 1) {
                    if (preRunSet_down > 300) {
                      preRunSet_down = preRunSet_down - 300;
                    }
                  }
                  prerunmillis2 = millis();
                  prerunstop2 = true;
                }
                if (preRunSet_running == 1) {
                  if (preRunSet_down < 300) {
                    preRunSet_down = 300;
                  }
                }
                if (millis() - prerunmillis2 > 1000) {
                  if (prerundeb - prevprerundeb > debfastCount3) {
                    if (preRunSet == 1 && preRunSet_running == 0) {
                      if (preRunSet_down > 0) {
                        preRunSet_down = preRunSet_down - 900;
                      }
                    }
                    if (preRunSet_running == 1) {
                      if (preRunSet_down > 300) {
                        preRunSet_down = preRunSet_down - 300;
                      } else {
                        preRunSet_down = 300;
                      }
                    }
                    fastCnt3++;
                    if (fastCnt3 > 35) {
                      fastCnt3 = 35;
                    }
                    if (fastCnt3 >= 0 && fastCnt3 < 6) {
                      debfastCount3 = 250;
                    } else if (fastCnt3 >= 6 && fastCnt3 < 20) {
                      debfastCount3 = 175;
                    } else if (fastCnt3 >= 20 && fastCnt3 < 35) {
                      debfastCount3 = 100;
                    } else debfastCount3 = 50;
                    prevprerundeb = prerundeb;
                  }
                }
              } else {
                prerunstop2 = false;
                debfastCount3 = 250;
                fastCnt3 = 0;
              }
              break;
            case 2:  ///////////////////////////////////////////////////////////////////////////////////steamer
              intervalBuz = 100;
              if (combi_data == 1 && combiDetect_data != 3) {
                if (downbtn == HIGH || upbtn == HIGH) {
                  if (beepOnce4 == 1) {
                    pzDetect = 1;
                    steamerOff_PRERUN = !steamerOff_PRERUN;
                    beepOnce4 = 0;
                  }
                } else {
                  beepOnce4 = 1;
                }
              } else {
                preRunSet_setting = 3;
              }
              break;
            case 3:  ///////////////////////////////////////////////////////////////////////////////////////////////fan
              intervalBuz = 100;
              if (fanDetect_data == 1) {
                if (downbtn == HIGH || upbtn == HIGH) {
                  if (beepOnce4 == 1) {
                    pzDetect = 1;
                    fanOff_PRERUN = !fanOff_PRERUN;
                    beepOnce4 = 0;
                  }
                } else {
                  beepOnce4 = 1;
                }
              } else {
                preRunSet_setting = 4;
              }
              break;
            case 4:  /////////////////////////////////////////////////////////////////////////////////////////////set temp
              if (bothChange == 1) {
                //fahrenheit
                // tempSet_read = (prerunfah - 32.0) * (5.0 / 9.0);
                // HumidSet_read = (precombifah - 32.0) * (5.0 / 9.0);
                tempSet_read = fahToCel(prerunfah);
                HumidSet_read = fahToCel(precombifah);
              } else {  //celsius d
                //prerunfah = tempSet_read * (9.0 / 5.0) + 32.0;
                //precombifah = HumidSet_read * (9.0 / 5.0) + 32.0;
                prerunfah = celToFah(tempSet_read);
                precombifah = celToFah(HumidSet_read);
              }
              if (steamerOff_PRERUN == 0) {  //sauna mode
                if (bothChange == 1) {
                  if (temperatureSet_data > tempSet_read)
                    prerunfah = plus(prerunfah);

                  if (tempSet_read > 30)
                    prerunfah = minus(prerunfah);

                } else {
                  if (temperatureSet_data > tempSet_read)
                    tempSet_read = plus(tempSet_read);

                  if (tempSet_read > 30)
                    tempSet_read = minus(tempSet_read);
                }
              } else {  //combi mode
                if (temperatureSet_data != 90) {
                  if (combiDetect_data == 2) {
                    if (65 > HumidSet_read) {
                      if (bothChange == 1)
                        precombifah = plus(precombifah);
                      else
                        HumidSet_read = plus(HumidSet_read);
                    }
                  }
                  if (combiDetect_data == 1) {
                    if ((int)x2 > HumidSet_read) {
                      if (HumidSet_read < 120) {
                        if (bothChange == 1)
                          precombifah = plus(precombifah);
                        else
                          HumidSet_read = plus(HumidSet_read);
                      }
                    }
                  }
                } else {
                  if (combiDetect_data == 2) {
                    if (55 > HumidSet_read) {
                      if (bothChange == 1)
                        precombifah = plus(precombifah);
                      else
                        HumidSet_read = plus(HumidSet_read);
                    }
                  }
                  if (combiDetect_data == 1) {
                    if ((int)x2 > HumidSet_read) {
                      if (HumidSet_read < 90) {
                        if (bothChange == 1)
                          precombifah = plus(precombifah);
                        else
                          HumidSet_read = plus(HumidSet_read);
                      }
                    }
                  }
                }
                if (bothChange == 1)
                  precombifah = minus(precombifah);
                else if (HumidSet_read > 30)
                  HumidSet_read = minus(HumidSet_read);
              }
              break;
            case 5:  ////////////////////////////////////////////////////////////////////////////////////combi
              if (steamerOff_PRERUN == 1) {

                if (combiDetect_data == 2) {

                  if (combiPLUS > 30)
                    combiPLUS = minus(combiPLUS);

                  if (combiPLUS < 100)
                    combiPLUS = plus(combiPLUS);

                  if (combiPLUS > lastcombiPLUS)
                    combiPLUS = combiPLUS + 4;

                  if (combiPLUS < lastcombiPLUS)
                    combiPLUS = combiPLUS - 4;
                }

                if (combiDetect_data == 1) {
                  if (combiPLUS > 15)
                    combiPLUS = minus(combiPLUS);

                  if ((int)y > combiPLUS) {
                    combiPLUS = plus(combiPLUS);
                    if (combiPLUS > lastcombiPLUS)
                      combiPLUS = combiPLUS + 0;
                  }
                  if (combiPLUS < lastcombiPLUS)
                    combiPLUS = combiPLUS - 0;
                }
              } else
                preRunSet_setting = 0;
              break;
          }
        } /*====================== END of menu state============*/

        if (steamerOff_PRERUN == 0) {
          if (DHP == 1) {
            preRunTimeMax = preRunSet_time - 900;
            preSession = preRunSet_time - preRunSet_down;
          } else {
            preRunTimeMax = preRunSet_time;
            preSession = maxTime;
          }
        } else {
          if (DHP == 1) {
            preRunTimeMax = preRunSet_time - 2700;
            preSession = preRunSet_time - preRunSet_down - 2400;
          }
          if (DHP == 2) {
            preRunTimeMax = preRunSet_time;
            preSession = maxTime - 2400;
          }
          if (DHP == 3) {
            preRunTimeMax = preRunSet_time;
            preSession = maxTime;
          }
        }
        if (preRunSet_down >= preRunTimeMax) {
          preRunSet_down = preRunTimeMax;
        }
        if (plusData >= preSession) {

          if (steamerOff_PRERUN == 0) {
            if (preSession < 900) {
              preSession = 900;
            }
          } else {
            if (preSession < 300) {
              preSession = 300;
            }
          }
          plusData = preSession;
        }
        if (plusData < 300) {
          plusData = 300;
        }
        lastpreRunSet_adjustTime = preRunSet_down;
        lastplusData = plusData;
        lastcombiPLUS = combiPLUS;
        if (steamerOff_PRERUN == 0) {
          if (bothChange == 1) {
            prefahDisplay = prerunfah;
          } else {
            precelDisplay = tempSet_read;
          }
        } else {
          if (bothChange == 1) {
            prefahDisplay = precombifah;
          } else {
            precelDisplay = HumidSet_read;
          }
        }
        if (preRunSet_running == 1) /*================ preRunSet_running is ON ================== */
        {
          if (menubtn == HIGH || upbtn == HIGH || downbtn == HIGH) {
            resetMillis = 0;
          }
          if (resetMillis >= 5) {
            if (preRunSet_setting != 1) {
              preRunSet_setting = 1;
            }
            resetMillis = 5;
          }
          if (prevblinkRunning >= 5) {
            blinkingLed = 0;
            prevblinkRunning = 5;
          }
          if (preRun_savePoint == 1) {
            hh_prerun = preRunSet_down / 3600;
            mm_prerun = (preRunSet_down / 60) % 60;
            hh_session = plusData / 3600;
            mm_session = (plusData / 60) % 60;


            EEPROM.write(16, hh_prerun);      // set temp no combi
            EEPROM.write(17, mm_prerun);      // set temp no combi
            EEPROM.write(20, fanOff_PRERUN);  //
            if (combi_data == 1) {
              save_steamerOff_PRERUN = steamerOff_PRERUN;
              EEPROM.write(21, steamerOff_PRERUN);  //
              EEPROM.write(22, combiPLUS);          //
              EEPROM.write(27, HumidSet_read);      //
            }
            EEPROM.write(23, hh_session);    //
            EEPROM.write(24, mm_session);    //
            EEPROM.write(26, tempSet_read);  //
            preRun_savePoint = 0;
          }
          if (ERROR1_data == 9) {
            preRunSet_running = 0;
            preRunSet = 0;
            errorTrue = true;
            activatederror = 9;
            ICSC.send(5, 'J', 1, NULL);
          }
          downtime_preSetRun();
          if (preRunSet_down <= 0) {
            pzDetect = 1;
            intervalBuz = 5000;
            preRunSet_setting = 0;  //to always go back to 1 when menu is pressed
            preHeat_startDown = 0;
            time_On2 = plusData;
            hh = ((plusData / 3600) % 100);
            mm = ((plusData / 60) % 60);
            ss = plusData % 60;

            down = plusData;




            preRunSet_running = 0;
            preRunSet = 0;
            if (steamerOff_PRERUN == 0) {
              tempSet_on = tempSet_read;
              fahrenheit = prerunfah;

              tempSet_on_Fah = prerunfah;
            } else {
              humidSet_on = HumidSet_read;
              combifahrenheit = precombifah;
              tempSet_on_Fah = precombifah;
            }
            fanOff = fanOff_PRERUN;
            steamerOff = steamerOff_PRERUN;
            combiPLUS2 = combiPLUS;
            save_combiPLUS2 = combiPLUS2;
            saveSteamer = steamerOff;
            save_tempSet_on = tempSet_on;

            save_humidSet_on = humidSet_on;
            save_fahrenheit = fahrenheit;

            save_combifahrenheit = combifahrenheit;
            // ICSC.send(9, 'H', 2, (char *)&hh);
            // ICSC.send(9, 'M', 2, (char *)&mm);
            // ICSC.send(9, 'S', 2, (char *)&mm);

            EEPROM.write(3, save_tempSet_on);        // set temp no combi
            EEPROM.write(14, save_fahrenheit);       // set temp fah no combi
            EEPROM.write(15, save_combifahrenheit);  //set temp fah with combi
            EEPROM.write(10, saveSteamer);
            EEPROM.write(6, hh);
            EEPROM.write(7, mm);
            EEPROM.write(2, ss);
            EEPROM.write(12, save_combiPLUS2);   //set humidity
            EEPROM.write(11, save_humidSet_on);  //set temp with combi

            buttonOnPressed = 2;
          }
          //*====================show display=======================
          if (upbtn == HIGH || downbtn == HIGH) {  //when pressed, display will not blink
            blinkDisplayState = 1;
          }
        }  //*================ END of preRunSet_running==================
        if (preRunSet_running == 1 || preRunSet == 1) {
          if (fanOff_PRERUN == 1) {
            if (preRunSet_setting != 3) {
              displayLed(14);
            }
          }
          if (combi_data == 1) {
            if (steamerOff_PRERUN == 1) {
              if (preRunSet_setting != 2) {
                displayLed(13);
              }
            }
          }
          if (preRunSet_setting == 0) {  //******************************session
            blinkFastLed(33);

            displayHour(plusData / 3600);
            displayMin((plusData / 60) % 60);


          } else if (preRunSet_setting == 1) {  //****************************pre run
            if (preRunSet == 1 && preRunSet_running == 0) {
              blinkFastLed(12);
              displayHour(preRunSet_down / 3600);
              displayMin((preRunSet_down / 60) % 60);
            }
            if (preRunSet_running == 1) {
              if (blinkingLed == 1) {
                blinkFastLed(12);
              }
              if (blinkDisplayState != 0) {  //blinking the display
                if (preRunSet_down < 60) {
                  displayNumber(preRunSet_down);  //preRunSet_down
                } else {
                  displayHour(preRunSet_down / 3600);
                  displayMin((preRunSet_down / 60) % 60);
                }
              }
            }
          } else if (preRunSet_setting == 2) {  //*********************************pre steamer
            if (combi_data == 1) {
              blinkFastLed(13);
              if (steamerOff_PRERUN == 0) {
                displayOff();
              } else {
                displayOn();
              }
            } else {
              preRunSet_setting = 3;
            }
          } else if (preRunSet_setting == 3) {  //***********************************fan
            if (fanDetect_data == 1) {

              blinkFastLed(14);


              if (fanOff_PRERUN == 0) {
                displayOff();
              } else {
                displayOn();
              }
            }
          } else if (preRunSet_setting == 4) {  //*********************************/set temp
            blinkFastLed(15);
            if (bothChange != 1) {  //cel
              if (precelDisplay > 99) {
                displayNumber3(precelDisplay);
              } else {
                displayNumber(precelDisplay);
              }
            } else {  //fah
              if (prefahDisplay > 99) {
                displayNumberFah3(prefahDisplay);
              } else {
                displayNumberFah2(prefahDisplay);
              }
            }
          } else {  //**********************************combi
            if (steamerOff_PRERUN == 1) {
              blinkFastLed(16);
              if (combiPLUS > 99) {
                displayNumber3(combiPLUS);
              } else {
                displayNumber(combiPLUS);
              }
            } else {
              preRunSet_setting = 0;
            }
          }
        }
      } else {
        fanOff = 0;
        preRunSet = 0;
        preRunSet_running = 0;
        intervalBuz = 50;
        static unsigned long errorblink1 = millis();
        if (millis() - errorblink1 >= 450) {
          errorAlternate = !errorAlternate;
          errorblink1 = millis();
        }
        if (errorAlternate == 1) {
          if (stopPzDetect == 1) {
            pzDetect = 1;
            stopPzDetect = 0;
          }
          if (activatederror == 9) {
            oPEn();
          } else {
            displayError(ERROR1_data);
          }
        } else {
          stopPzDetect = 1;
        }
        if (ERROR1_data == 4 || ERROR1_data == 6) {
          steamerOff = 0;
        }
      }
      break;
    case 2:  ///////////////////////////////////////////////////////////////////////////////////////////////////ON-----------------------------------------------------
      unsigned long durationSetTemp;
      cabinSendOnce = false;
      if (everyOnsend == true) {
        if (no40min == 0) {
          if (steamerOff == 1) {
            if (DHP != 3) {
              maxTimeDown = maxTimeDown - 2400;
            }
            addTime = 1;
          }
        }
        everyOnsend = false;
        everyOnsend2 = true;
        every100MillisSend = millis();
      }
      if (everyOnsend2 == true && dontSendYet == 0) {
        if (millis() - every100MillisSend >= 10) {
          increment++;
          switch (increment) {
            case 1:
              ICSC.send(5, 'k', 5, (char *)&tempSet_on_data);  //temperature



              break;
            case 2:
              ICSC.send(5, 'C', 5, (char *)&steamerOff);  //combi
              break;
            case 3:
              ICSC.send(5, 'L', 5, (char *)&combiPLUS2);  //humidity
              break;
            case 4:
              int sendmaxhot = (int)x2;
              ICSC.send(5, 'm', 5, (char *)&sendmaxhot);  //temp
              increment = 0;
              everyOnsend2 = false;
              break;
          }
        }
      }
      if (prevdurationSetTemp >= 5) {
        setTempDisplay_On = 1;
        prevdurationSetTemp = 5;
      }
      if (prevfiveMinutes >= 300) {  //==============5 minutes=======================
        nextSession = 1;
        prevfiveMinutes = 300;
      } else {
        nextSession = 0;
      }
      if (ERROR2_data == 0) {
        displayBlink2 = 0;

        if (bothChange == 1) {  //fah
          //tempSet_on = (fahrenheit - 32.0) * (5.0 / 9.0);
          //humidSet_on = (combifahrenheit - 32.0) * (5.0 / 9.0);
          tempSet_on = fahToCel(fahrenheit);
          humidSet_on = fahToCel(combifahrenheit);
        } else {  //cel
          //fahrenheit = (tempSet_on * (9.0 / 5.0)) + 32.0;
          //combifahrenheit = (humidSet_on * (9.0 / 5.0)) + 32.0;
          fahrenheit = celToFah(tempSet_on);

          combifahrenheit = celToFah(humidSet_on);
        }


        //=====================================================================================================
        if (unlitime == 1) {
          if (down == 86400)
            if (nextSession == 0)
              enableUnlimitedTime = 1;

          if (enableUnlimitedTime != lastenableUnlimitedTime) {
            EEPROM.write(13, enableUnlimitedTime);
            lastenableUnlimitedTime = enableUnlimitedTime;
          }
        } else
          enableUnlimitedTime = 0;


        if (enableUnlimitedTime == 1 && downbtn == HIGH) {
          down = 86399;
          enableUnlimitedTime = 0;
        }


        displayLed(12);
        if (remoteOn_data != 0) {  //remoteOn_data = 1
          if (displayKLockGo == 0 && bothDisplay == false) {
            if (menu_On_setttings == 0 && menu_On == false && setTempDisplay_On == 1) {  //============temperature======================================
              if (toggleisPressed == 1) {
                blinkFastLed(15);
              } else {
                if (actualTemperature_data < (tempSet_on_data + 10) && (actualTemperature_data > tempSet_on_data - 10)) {
                  displayLed(15);
                } else {
                  blinkSlowLed(15);
                }
              }
            }
            if (HOT_data == 0 && fillDetect_data == 0 && steamLevel_data == 0) {
              unsigned long keylock = millis();
              if (downbtn == HIGH && upbtn == HIGH && menubtn == LOW) {
                no_button_work = 1;
                if (keylockReset == 1) {
                  prevkeylock = millis();
                  keylockReset = 0;
                }
                if (keylock - prevkeylock >= keylockInterval) {
                  if (beepOnce7 == 1) {
                    keylocklock = !keylocklock;
                    EEPROM.write(5, keylocklock);
                    pzDetect = 1;
                    intervalBuz = 1000;
                    menu_On = false;
                    beepOnce7 = 0;
                  }
                }
              }
              if (downbtn == LOW && upbtn == HIGH && menubtn == HIGH) {
                no_button_work = 1;
                if (keylocklock == 0) {
                  if (bothActive == false) {
                    bothMillis = millis();
                    displayOnce = false;
                    bothActive = true;
                  }
                  if (millis() - bothMillis >= 1500) {
                    if (displayOnce == false) {
                      bothDisplay = true;
                      bothChange = !bothChange;
                      EEPROM.write(1, bothChange);
                      prevbothDisplay = millis();
                      displayOnce = true;
                    }
                  }
                } else {
                  displayKLockGo = 1;
                  Klock = 0;
                }
              }
              if (downbtn == LOW && upbtn == LOW && menubtn == LOW) {
                bothActive = false;
                keylockReset = 1;
                beepOnce7 = 1;
                no_button_work = 0;
              }
              if (menu_On_setttings != 3) {
                if (steamerOff == 1) {
                  displayLed(13);
                }
              }
              if (menu_On_setttings != 4) {
                if (fanOff == 1) {
                  displayLed(14);
                }
              }
              if (menu_On == true) {  //==========================menu_on is turned On===============
                savePoint = 1;
                if (prevmenuMillis >= 5) {  //if no button is touched within 5 seconds
                  menu_On = false;
                  prevmenuMillis = 5;
                }
                if (menubtn == HIGH || upbtn == HIGH || downbtn == HIGH) {  //button is touched within 5 seconds
                  prevmenuMillis = 0;
                }
                if (menu_On_setttings == 2) {  //==================================================session
                  if (maxTimeDown > down)      //unit hour
                  {
                    down = plus(down);
                    if (down >= maxTimeDown) {
                      down = maxTimeDown;
                    }
                  }
                  if (down > 300) {  //5 minutes
                    down = minus(down);
                    decreStop = 1;
                  }
                  if (down < 300 && downbtn == HIGH) {
                    down = 300;
                  }
                  if (down < 300 && downbtn == LOW && decreStop == 1) {
                    down = 300;
                    decreStop = 0;
                  }
                  if (downbtn == HIGH || upbtn == HIGH) {
                    savePoints[0] = 1;
                  }
                  displayForTime = down;
                  blinkFastLed(33);
                } else if (menu_On_setttings == 0) {  //==============================================temp
                  blinkFastLed(15);
                  if (steamerOff == 0) {
                    tempSet_on_Fah = fahrenheit;

                    tempSet_on_data = tempSet_on;
                    if (bothChange == 1) {
                      if (temperatureSet_data > tempSet_on)
                        fahrenheit = plus(fahrenheit);


                      if (tempSet_on > 30)
                        fahrenheit = minus(fahrenheit);


                    } else {
                      if (temperatureSet_data > tempSet_on) {
                        tempSet_on = plus(tempSet_on);
                      }
                      if (tempSet_on > 30) {
                        tempSet_on = minus(tempSet_on);
                      }
                    }
                  } else {
                    tempSet_on_Fah = combifahrenheit;
                    tempSet_on_data = humidSet_on;
                    if (temperatureSet_data != 90) {  //limitation temp is in 120
                      if (combiDetect_data == 2) {
                        if (65 > humidSet_on) {
                          if (bothChange == 1) {
                            combifahrenheit = plus(combifahrenheit);
                          } else {
                            humidSet_on = plus(humidSet_on);
                          }
                        }
                      }
                      if (combiDetect_data == 1) {
                        if ((int)x2 > humidSet_on) {
                          if (humidSet_on < 120) {
                            if (bothChange == 1) {
                              combifahrenheit = plus(combifahrenheit);
                            } else {
                              humidSet_on = plus(humidSet_on);
                            }
                          }
                        }
                      }
                    } else {  //limitation temp is in 110
                      if (combiDetect_data == 2) {
                        if (55 > humidSet_on) {
                          if (bothChange == 1) {
                            combifahrenheit = plus(combifahrenheit);
                          } else {
                            humidSet_on = plus(humidSet_on);
                          }
                        }
                      }
                      if (combiDetect_data == 1) {
                        if ((int)x2 > humidSet_on) {
                          if (humidSet_on < 90) {
                            if (bothChange == 1) {
                              combifahrenheit = plus(combifahrenheit);
                            } else {
                              humidSet_on = plus(humidSet_on);
                            }
                          }
                        }
                      }
                    }
                    if (humidSet_on > 30) {
                      if (bothChange == 1) {
                        combifahrenheit = minus(combifahrenheit);
                      } else {
                        humidSet_on = minus(humidSet_on);
                      }
                    }
                  }
                  if (bothChange == 1) {  //fah
                    displayForTemp = tempSet_on_Fah;
                  } else {
                    displayForTemp = tempSet_on_data;
                  }
                } else if (menu_On_setttings == 3) {  //================================================steamer
                  intervalBuz = 100;
                  if (combi_data == 1 && combiDetect_data != 3) {
                    blinkFastLed(13);
                    if (downbtn == HIGH || upbtn == HIGH) {
                      if (beepOnce4 == 1) {
                        steamerOff = !steamerOff;
                        pzDetect = 1;
                        beepOnce4 = 0;
                      }
                    } else {
                      beepOnce4 = 1;
                    }
                    if (no40min == 0) {
                      if (addTime == 1 && steamerOff == 0) {
                        if (DHP != 3) {
                          maxTimeDown = maxTimeDown + 2400;
                        }
                        addTime = 0;
                      }
                    }
                    if (tempSet_on_data > 255) {
                      tempSet_on_data = 100;
                    }
                  } else {
                    menu_On_setttings = 4;
                  }
                } else if (menu_On_setttings == 1) {  //================================================combi
                  if (steamerOff == 1) {
                    displayForHumid = combiPLUS2;
                    blinkFastLed(16);
                    if (combiDetect_data == 2) {  //ts2
                      if (combiPLUS2 > 30) {
                        combiPLUS2 = minus(combiPLUS2);
                      }
                      if (combiPLUS2 < 100) {
                        combiPLUS2 = plus(combiPLUS2);
                      }
                      if (combiPLUS2 > lastcombiPLUS2) {
                        combiPLUS2 = combiPLUS2 + 4;
                        if (combiPLUS2 > 100) {
                          combiPLUS2 = 100;
                        }
                      }
                      if (combiPLUS2 < lastcombiPLUS2) {
                        combiPLUS2 = combiPLUS2 - 4;
                      }
                    }
                    if (combiDetect_data == 1) {  //th sensor
                      if (combiPLUS2 > 15) {
                        combiPLUS2 = minus(combiPLUS2);
                      }
                      if ((int)y > combiPLUS2) {
                        combiPLUS2 = plus(combiPLUS2);
                        if (combiPLUS2 > lastcombiPLUS2) {
                          combiPLUS2 = combiPLUS2 + 0;
                        }
                      }
                      if (combiPLUS2 < lastcombiPLUS2) {
                        combiPLUS2 = combiPLUS2 + 0;
                      }
                    }
                    lastcombiPLUS2 = combiPLUS2;
                  } else {
                    menu_On_setttings = 2;
                  }
                } else {  //================================================fan
                  intervalBuz = 100;
                  if (fanDetect_data == 1) {
                    blinkFastLed(14);
                    if (downbtn == HIGH || upbtn == HIGH) {
                      if (beepOnce4 == 1) {
                        pzDetect = 1;
                        fanOff = !fanOff;
                        beepOnce4 = 0;
                      }
                    } else {
                      beepOnce4 = 1;
                    }
                    fanOff_PREV = fanOff;
                  } else {
                    menu_On_setttings = 0;
                  }
                }
              } else {  //===========================gawas na sa menu_On=============================================
                if (togglemillis >= 5) {
                  toggleisPressed = 0;
                  smdDetected = 0;
                  smdCount = 0;
                  smdCount2 = 0;
                  togglemillis = 5;
                }
                if (upbtn == HIGH || downbtn == HIGH || menubtn == HIGH) {
                  backToTempView = 0;
                } else {
                  if (backToTempView >= 7) {
                    if (menu_On_setttings >= 3) {
                      menu_On_setttings = 0;  //temp display
                    }
                    if (menu_On_setttings == 1) {
                      if (combiDetect_data == 2) {  //ts2
                        menu_On_setttings = 0;      //temp display
                      }
                    }
                    backToTempView = 7;
                  }
                }
                if (keylocklock == 1 && setTempDisplay_On == 1 && no_button_work == 0) {
                  if (upbtn == HIGH || downbtn == HIGH) {
                    if (toggleOnce == 1) {

                      pzDetect = 1;
                      intervalBuz = 100;

                      displayKLockGo = 1;
                      Klock = 0;
                      toggleOnce = 0;
                    }
                  } else {
                    toggleOnce = 1;
                  }
                }

                if (savePoint == 1) {

                  if (no_button_work == 0) {
                    intervalBuz = 300;
                    pzDetect = 1;
                  }

                  if (nextSession == 0) {

                    if (savePoints[0] == 1) {

                      if (down > 300) {  //greater than 5 minutes

                        hh = ((down / 3600) % 100);
                        mm = ((down / 60) % 60);
                        ss = down % 60;

                        // ICSC.send(9, 'H', 5, (char *)&hh);
                        // ICSC.send(9, 'M', 5, (char *)&mm);
                        // ICSC.send(9, 'S', 5, (char *)&ss);
                        EEPROM.write(6, hh);
                        EEPROM.write(7, mm);
                        EEPROM.write(2, ss);


                      } else {

                        hh = 0;
                        mm = 5;
                        ss = 0;
                        // ICSC.send(9, 'H', 5, (char *)&hh);
                        // ICSC.send(9, 'M', 5, (char *)&mm);
                        // ICSC.send(9, 'S', 5, (char *)&ss);
                        EEPROM.write(6, hh);
                        EEPROM.write(7, mm);
                        EEPROM.write(2, ss);
                      }
                      savePoints[0] = 0;
                    }


                    save_tempSet_on = tempSet_on;
                    // ICSC.send(9, 'tt', 5, (char *)&save_tempSet_on);  //sauna_temperature
                    save_humidSet_on = humidSet_on;  //combi_temperature
                    save_fahrenheit = fahrenheit;
                    //sauna_fahrenheit
                    save_combifahrenheit = combifahrenheit;
                    //combi_fahrenheit
                    EEPROM.write(3, save_tempSet_on);        // set temp no combi
                    EEPROM.write(11, save_humidSet_on);      //set temp with combi
                    EEPROM.write(14, save_fahrenheit);       // set temp fah no combi
                    EEPROM.write(15, save_combifahrenheit);  //set temp fah with combi
                    saveSteamer = steamerOff;
                    EEPROM.write(10, saveSteamer);
                    save_combiPLUS2 = combiPLUS2;
                    EEPROM.write(12, save_combiPLUS2);  //set humidity
                  }

                  int sendmaxhot = (int)x2;
                  int sendmaxHumid = (int)y;
                  ICSC.send(5, 'm', 5, (char *)&sendmaxhot);  //temp
                  ICSC.send(5, 'k', 5, (char *)&tempSet_on_data);
                  ICSC.send(5, 'L', 5, (char *)&combiPLUS2);
                  // ICSC.send(5, 'k', 5, (char *)&save_fahrenheit);
                  // ICSC.send(5, 'k', 5, (char *)&save_tempSet_on);
                  // ICSC.send(9, 'TF', 5, (char *)&save_fahrenheit);
                  ICSC.send(9, 'tt', 2, (char *)&tempSet_on);


                  savePoint = 0;
                }



                beepOnce4 = 1;
                prevmenuMillis = 0;
                if (setTempDisplay_On == 1) {
                  if (menu_On_setttings >= 0) {
                    if (upbtn == HIGH || downbtn == HIGH) {
                      if (keylocklock == 0 && no_button_work == 0 && (millis() - delayActivateMillis[2] > 50)) {
                        menu_On = true;
                      }
                    } else {
                      delayActivateMillis[2] = millis();
                    }
                  }
                  if (menu_On_setttings == 2)  //==========================session time
                    blinkfast = 33;
                  else if (menu_On_setttings == 0) {  //============temperature======================================
                    blinkfast = 15;
                    //displaying the current temp from the sensor.
                    totalTempFah = 1.8 * actualTemperature_data + 32.0;

                    int intFah = (int)totalTempFah;

                    if (togglemillis >= 5)
                      displayForTemp = (bothChange == 1) ? intFah : actualTemperature_data;

                    else
                      displayForTemp = (bothChange == 1) ? tempSet_on_Fah : tempSet_on_data;
                  } else if (menu_On_setttings == 1) {  //==================humidity display
                    if (steamerOff == 1 || humidityData_data != 0) {
                      blinkfast = 16;
                      if (combiDetect_data == 2)
                        displayForHumid = combiPLUS2;

                      if (combiDetect_data == 1)
                        displayForHumid = humidityData_data;

                    } else
                      menu_On_setttings = 2;

                  } else if (menu_On_setttings == 3) {

                    if (combi_data == 1 && combiDetect_data != 3)
                      blinkfast = 13;
                    else
                      menu_On_setttings = 4;

                  } else {

                    if (fanDetect_data == 1)
                      blinkfast = 14;
                    else
                      menu_On_setttings = 0;
                  }
                  if (menu_On_setttings != 0) {

                    if (toggleisPressed == 1)
                      blinkFastLed(blinkfast);
                    else
                      displayLed(blinkfast);
                  }
                }
                displayForTime = down;
              }
              if (menu_On_setttings > 4)
                menu_On_setttings = 0;

              displayDetected = 0;
            } else if (HOT_data == 1 && fillDetect_data == 0 && steamLevel_data == 0)
              displayDetected = 1;
            else if (HOT_data == 0 && fillDetect_data == 1 && steamLevel_data == 0)
              displayDetected = 2;
            else displayDetected = 3;
          } else if (bothDisplay == true && displayKLockGo == 0) {
            unsigned long blinkBoth = millis();
            if (blinkBoth - prevblinkBoth >= 500) {
              blinkBothStart = !blinkBothStart;
              prevblinkBoth = blinkBoth;
            }
            if (blinkBothStart == 1) {

              if (bothChange == 1) {
                displayFah();
                // Tempscale = 1;
                // EEPROM.write(19, Tempscale);
                // ICSC.send(9, 'TS', 1, (char *)&Tempscale);



              } else {
                displayCel();
                // Tempscale = 2;
                // EEPROM.write(19, Tempscale);
                // ICSC.send(9, 'TS', 1, (char *)&Tempscale);
              }
            } else
              displayOn();

            if (millis() - prevbothDisplay >= 2000)
              bothDisplay = false;
          } else {
            displayKLock();

            if (Klock >= 2)
              displayKLockGo = 0;
          }
        } else {
          totalTempFah = 1.8 * actualTemperature_data + 32.0;
          int intFah = (int)totalTempFah;
          if (bothChange == 1)  //fah
            displayForTemp = intFah;

          else displayForTemp = actualTemperature_data;

          if (steamerOff == 1)
            displayLed(13);

          if (fanOff == 1)
            displayLed(14);

          if (menu_On_setttings == 0 && alternateDisplayGo == 1) {
            if (totalTemp < (tempSet_on_data + 10) && (totalTemp > tempSet_on_data - 10))
              displayLed(15);
            else
              blinkSlowLed(15);
          }

          if (menu_On_setttings == 1 && alternateDisplayGo == 2)
            displayLed(16);

          if (steamLevel_data == 0 && fillDetect_data == 0 && HOT_data == 0) {
            displayDetected = 0;
            totalTemp = actualTemperature_data;
            if (humidityData_data != 0) {
              if (alternateDisplayGo == 1) {
                displayDetected = 0;
                menu_On_setttings = 0;
              } else if (alternateDisplayGo == 2) {
                displayForHumid = humidityData_data;
                menu_On_setttings = 1;
              } else
                displayDetected = 4;

              if (alternateDisplayGo > 2)
                alternateDisplayGo = 0;
            } else {
              if (alternateDisplayGo == 1) {
                displayDetected = 0;
                menu_On_setttings = 0;
              } else
                displayDetected = 4;

              if (alternateDisplayGo > 1)
                alternateDisplayGo = 0;
            }
          } else if (steamLevel_data == 1 && fillDetect_data == 0 && HOT_data == 0)
            displayDetected = 3;
          else if (steamLevel_data == 0 && fillDetect_data == 1 && HOT_data == 0)
            displayDetected = 2;
          else
            displayDetected = 1;
        }
        //============================================showing the display============================================
        if (everyOnsend == false) {
          if (setTempDisplay_On == 0) {
            if (steamerOff == 0) {
              if (bothChange == 1) {
                tempSet_on_Fah = fahrenheit;

              } else tempSet_on_data = tempSet_on;
            } else {
              if (bothChange == 1)
                tempSet_on_Fah = combifahrenheit;
              else
                tempSet_on_data = humidSet_on;
            }
            displayLed(15);
            if (bothChange == 1) {  //fah
              if (displayblinkState == 1) {
                if (tempSet_on_Fah > 99)
                  displayNumberFah3(tempSet_on_Fah);
                else
                  displayNumberFah2(tempSet_on_Fah);
              }
            } else {
              if (displayblinkState == 1) {
                if (tempSet_on_data > 99)
                  displayNumber3(tempSet_on_data);
                else
                  displayNumber(tempSet_on_data);
              }
            }
          } else {
            if (displayDetected == 0) {
              if (displayKLockGo == 0 && bothDisplay == false) {
                if (smdDetected == 0) {
                  if (menu_On_setttings == 0) {  //---------------------------------- temp
                    if (bothChange == 1) {       //fah
                      if (displayForTemp > 99)
                        displayNumberFah3(displayForTemp);
                      else
                        displayNumberFah2(displayForTemp);
                    } else {
                      if (displayForTemp > 99)
                        displayNumber3(displayForTemp);
                      else
                        displayNumber(displayForTemp);
                    }
                  } else if (menu_On_setttings == 1) {  //--------------------------combi
                    if (displayForHumid > 99)
                      displayNumber3(displayForHumid);
                    else
                      displayNumber(displayForHumid);

                  } else if (menu_On_setttings == 2) {  //---------------------------session
                    if (enableUnlimitedTime == 0) {
                      if (down < 60)
                        displayNumber(displayForTime);
                      else {
                        displayHour((displayForTime / 3600) % 99);
                        displayMin((displayForTime / 60) % 60);
                      }
                    } else {
                      displayHour(24);
                      displayMin(0);
                    }
                  } else if (menu_On_setttings == 3) {  //--------------------------------steamer
                    if (steamerOff == 0)
                      displayOff();
                    else
                      displayOn();
                  } else {  //------------------------------------------------------------fan
                    if (fanOff == 0)
                      displayOff();
                    else
                      displayOn();
                  }
                } else
                  displayNumber(smdNTC_data);
              }
            } else if (displayDetected == 1) {
              displayHot();
              if (steamerMillis > 5) {
                HOT_data = 0;
                tempSet_on_data = tempSet_on;
              }
              static unsigned long beepSound = millis();
              if (millis() - beepSound > 500) {
                pzDetect = 1;
                intervalBuz = 100;
                beepSound = millis();
              }
            } else if (displayDetected == 2)
              displayFill();

            else if (displayDetected == 3)
              displayDry();
            else
              displayRem();
          }
          if (steamLevel_data == 1 || fillDetect_data == 1) {
            intervalBuz = 100;
            unsigned long beepdry = millis();
            if (beepdry - prevbeepdry > fill_dry_buzz) {
              pzDetect = 1;
              prevbeepdry = beepdry;
            }
          }
        }
        //=============================================================================================================
      } else {
        displayBlink2 = 1;
        if (errorAlternate == 1)
          oPEn();
      }
      if (remoteOn_data != 0)
        downtime();  //countdown of sesstion Time
      else {
        DryingTime = 2400;
        if (powerbtn == HIGH || menubtn == HIGH || upbtn == HIGH || downbtn == HIGH) {
          if (beepOnce6 == 1) {
            pzDetect = 1;
            intervalBuz = 100;
            beepOnce6 = 0;
          }
        } else
          beepOnce6 = 1;
      }
      break;
    case 3:  //////////////////////////////////////////////////////////////////////////////CABIN DRYING/////////////////////////////////////////////////////
      preRunSet = 0;
      preRunSet_running = 0;
      if (downbtn == HIGH || upbtn == HIGH || menubtn == HIGH) {
        if (beepOnce == 1) {
          intervalBuz = 100;
          pzDetect = 1;
          beepOnce = 0;
        }
      } else
        beepOnce = 1;
      resetTemp = 1;
      if ((DryingTime / 60) <= 29) {
        displayLed(14);
        if (cabinSendOnce == false) {
          byte timer10minutes = 3;
          ICSC.send(5, 'W', 5, (char *)&timer10minutes);
          cabinSendOnce = true;
        }
      } else
        displayBlink2 = 0;
      if (ERROR1_data == 9 && cabinSendOnce == true) {
        displayBlink2 = 1;
        if (errorAlternate == 1)
          oPEn();
      } else {
        displayBlink2 = 0;
        if (DryingTime < 60)
          displayNumber(DryingTime);
        else {
          displayHour((DryingTime / 3600) % 24);
          displayMin((DryingTime / 60) % 60);
        }
      }
      if (DryingTime <= 0) {
        preRunSet = 0;
        preRunSet_running = 0;
        intervalBuz = 1000;
        pzDetect = 1;
        buttonOnPressed = 1;
      }
      break;
  }
}

void displayHour(byte toDisplay) {  //display Hour 7 segment
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        if (toDisplay < 10) {
          PORTC |= (1 << 2);  //col1
        } else {
          PORTC &= ~(1 << 2);  //col1
          numbers(toDisplay / 10);
        }
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        numbers(toDisplay % 10);
        break;
      case 2:
        break;
      case 3:
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}


void displayRem() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        PORTC &= ~(1 << 2);  //col1
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
      case 1:

        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}

void displayError(byte toDisplay) {
  for (byte digit = 0; digit < 4; digit++) {
    if (toDisplay == 10) {
      switch (digit) {
        case 0:
          break;
        case 1:
          PORTC &= ~(1 << 3);  //col2
          PORTB &= ~(1 << 0);  //a
          PORTB &= ~(1 << 3);  //d
          PORTB &= ~(1 << 4);  //e
          PORTB &= ~(1 << 5);  //f
          PORTC &= ~(1 << 0);  //g
          break;
        case 2:
          PORTC &= ~(1 << 4);  //col3
          numbers(toDisplay / 10);
          break;
        case 3:
          PORTC &= ~(1 << 5);  //col4
          numbers(toDisplay % 10);
          break;
      }
    } else {
      switch (digit) {
        case 0:
          break;
        case 1:
          break;
        case 2:
          PORTC &= ~(1 << 4);  //col3
          PORTB &= ~(1 << 0);  //a
          PORTB &= ~(1 << 3);  //d
          PORTB &= ~(1 << 4);  //e
          PORTB &= ~(1 << 5);  //f
          PORTC &= ~(1 << 0);  //g
          break;
        case 3:
          PORTC &= ~(1 << 5);  //col4
          numbers(toDisplay);
          break;
      }
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}




void oPEn() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        PORTC &= ~(1 << 2);  //col1
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}
void E11() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {

      // blank (1st digit)
      case 0:
        PORTC &= ~(1 << 2);  // col1
        break;

      // E (2nd digit)
      case 1:
        PORTC &= ~(1 << 3);  // col2
        PORTB &= ~(1 << 0);  // a
        PORTB &= ~(1 << 3);  // d
        PORTB &= ~(1 << 4);  // e
        PORTB &= ~(1 << 5);  // f
        PORTC &= ~(1 << 0);  // g
        break;

      // 1 (3rd digit)
      case 2:
        PORTC &= ~(1 << 4);  // col3
        PORTB &= ~(1 << 1);  // b
        PORTB &= ~(1 << 2);  // c
        break;

      // 1 (4th digit)
      case 3:
        PORTC &= ~(1 << 5);  // col4
        PORTB &= ~(1 << 1);  // b
        PORTB &= ~(1 << 2);  // c
        break;
    }

    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}


void E12() {
  for (byte digit = 0; digit < 4; digit++) {

    switch (digit) {

      // blank (1st digit)
      case 0:
        PORTC &= ~(1 << 2);  // col1
        break;

      // E (2nd digit)
      case 1:
        PORTC &= ~(1 << 3);  // col2
        PORTB &= ~(1 << 0);  // a
        PORTB &= ~(1 << 3);  // d
        PORTB &= ~(1 << 4);  // e
        PORTB &= ~(1 << 5);  // f
        PORTC &= ~(1 << 0);  // g
        break;

      // 1 (3rd digit)
      case 2:
        PORTC &= ~(1 << 4);  // col3
        PORTB &= ~(1 << 1);  // b
        PORTB &= ~(1 << 2);  // c
        break;

      // 2 (4th digit)
      case 3:
        PORTC &= ~(1 << 5);  // col4
        PORTB &= ~(1 << 0);  // a
        PORTB &= ~(1 << 1);  // b
        PORTB &= ~(1 << 3);  // d
        PORTB &= ~(1 << 4);  // e
        PORTC &= ~(1 << 0);  // g
        break;
    }

    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}


void displayKLock() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        PORTC &= ~(1 << 2);  //col1
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        break;
    }

    PORTC &= ~(1 << 0);  //g
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}


void fastBeeping() {
  unsigned long beepBuzzer = millis();
  if (beepBuzzer - prevbeepBuzzer >= beepBuzzerInterval) {
    beepBuzzerInterval = beepBuzzerInterval - 25;
    if (beepBuzzerInterval < 100) {
      beepBuzzerInterval = 100;
    }
    pzDetect = 1;
    intervalBuz = 75;
    prevbeepBuzzer = beepBuzzer;
  }
}

void fastBeeping2() {
  unsigned long beepBuzzer2 = millis();
  if (beepBuzzer2 - prevbeepBuzzer2 >= beepBuzzerInterval2) {
    beepBuzzerInterval2 = beepBuzzerInterval2 - 25;
    if (beepBuzzerInterval2 < 100) {
      beepBuzzerInterval2 = 100;
    }
    pzDetect = 1;
    intervalBuz = 75;
    prevbeepBuzzer2 = beepBuzzer2;
  }
}



void displayFill() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        PORTC &= ~(1 << 2);  //col1
        PORTB &= ~(1 << 0);  //a
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTB &= ~(1 << 5);  //f
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}


void displayDry() {
  for (byte digit = 0; digit < 4; digit++) {
    switch (digit) {
      case 0:
        break;
      case 1:
        PORTC &= ~(1 << 3);  //col2
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
      case 2:
        PORTC &= ~(1 << 4);  //col3
        PORTB &= ~(1 << 4);  //e
        PORTC &= ~(1 << 0);  //g
        break;
      case 3:
        PORTC &= ~(1 << 5);  //col4
        PORTB &= ~(1 << 1);  //b
        PORTB &= ~(1 << 2);  //c
        PORTB &= ~(1 << 3);  //d
        PORTB &= ~(1 << 5);  //f
        PORTC &= ~(1 << 0);  //g
        break;
    }
    delayMicroseconds(brightness);
    noDisplay7Seg();
  }
}

void fanButton() {
  if (!bothDisplay && !bothActive) {
    if (downbtn == HIGH || upbtn == HIGH) {
      if (!fanOffMode) {
        delayActivateMillis[1] = millis();
        fanOffMode = 1;
      }
      if (millis() - delayActivateMillis[1] > 50 && !fanActivated) {
        if (fanDetect_data == 1 && keylocklock == 0) {
          fanOff = !fanOff;
          displayFanOffMode = 1;
        } else {
          if (keylocklock == 1)
            displayFanOffMode = 5;
          pzDetect = 1;
          intervalBuz = 100;
        }
        fanActivated = true;
      }
    } else {
      if (fanOffMode) {
        if (fanActivated)
          fanActivated = false;
        else {
        }
        fanOffMode = 0;
      }
    }
  }
}

int celToFah(int x) {
  return ((9 * x) / 5) + 32;
}
int fahToCel(int x) {
  return ((x - 32) * 5) / 9;
}
