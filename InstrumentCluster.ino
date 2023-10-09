#include <Wire.h>
#include <Adafruit_INA219.h>
#include "uEEPROMLib.h"
#include "GyverButton.h"

// eeprom routines
uEEPROMLib eeprom(0x57);
uint32_t EEtime;

// Clock routines //
#include <DS3231.h>
RTClib myRTC;
DS3231 setRTC;
bool clock2dot;

// Display routines //
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <fonts/wwDigital24pt7b.h>
#include <fonts/wwDigital8pt7b.h>
#include <fonts/digits18pt7b.h>
#include <fonts/FreeSans18pt7b.h>
#include <fonts/FreeSans24pt7b.h>
Adafruit_SH1106 dl(-1);
Adafruit_SH1106 dr(-1);
Adafruit_SH1106 c(4, 6, 5);
bool DisplayST;
int8_t DispPage = 0, DispSubPage, SubPageMax = 10;
uint16_t cDispInterval;
uint32_t lDispTimer, cDispTimer, rDispTimer, updTimer;

//Analog buttons routines//
#define wkL_pin A1  // input from left key block on steering wheel
#define wkR_pin A0  // input from right key block on steering wheel
uint8_t avg = 10;   //
#define key1 526    //analog value for resistive key
#define key2 693    //analog value for resistive key
#define key3 780    //analog value for resistive key
#define key4 826    //analog value for resistive key
#define btuppin 8
#define btdnpin 7
bool VolButtBusy, keyPlus, keyMinus;
uint8_t flagL, flagR;     // Debounce function for key block on steering wheel
uint32_t eventR, eventL;  // Timer for key block on steering wheel

//taho routines
volatile uint32_t micros_th = 0;  //pulse time
volatile uint64_t tz = 0;         //counter
volatile uint16_t th = 0;         //rpm
volatile bool tt = false;         //trigger

//Speed & km routines
volatile uint32_t micros_sp = 0;  //pulse time
volatile uint64_t sz = 0;         //counter
volatile float sp = 0;            //Speed
volatile bool st = false;         //trigger
volatile uint64_t odometrPulses;
volatile uint64_t tripreset, afStartReset;
volatile int32_t  ServiceA, ServiceB; 
volatile uint32_t tripTime, afStartTime, driveTcount, odometr, serviceAreset, serviceBreset, ServiceAinterval = 5000, ServiceBinterval = 10000;
volatile float SpAvg[20], afStart, trip;
volatile uint8_t saveSpeedPos;

//StartStop routines
uint32_t holdACCtime, lastWork, StarterTime;
uint8_t statusEngine;
bool cLock, stateIgn, holdACC, stateACC;
#define TrunkPin 22    //-->выход на багажник
#define ClosePin 23    //-->выход на цз
#define DoorPin 50     //<--Вход с концевика двери
#define BrakePin 24    //<--Вход с тормоза
#define ClutchPin 24   //<--Вход с тормоза
#define IgnPin 25      //-->Выход на зажигание
#define ACCPin 26      //-->Выход на ACC
#define StarterPin 97  //-->Выход на стартера
#define Yled 28        //-->Выход на глазок Y
#define Gled 29        //-->Выход на глазок G
#define Wled 30        //-->Выход на подсветку кнопки
#define SSButtPin 31   //<--Вход с кнопки
GButton ssButt(SSButtPin);

// CruiseControl routines
#include <Servo.h>
Servo CCservo;
float CCTargetSp, PreviousSpeed;
uint8_t throttle, CCstatus;
float CC_Kp = 9.0, CC_Ki = 0.5, CC_Kd = 0.0;
#define CCservoPin 32
#define CCkeyPin A2
#define accel 1
#define decel 1
#define cancel 1
#define reset 1



// other
GButton buttR(53);
uint32_t btKeyTime, btKeyDelay;
//odometrPulses = 11638450000;

void setup() {
  Wire.begin();  //SaveIntervals();//settime();
  ReadEEprom();
  afStartTime = 1;
  afStartReset = odometrPulses;
  UpdKM();
  setupSSpins();
  initDisplays();
  SetupButtons();
  SetInterrupts();
  CCservo.attach(CCservoPin);


}

void loop() {

  CheckButt();

  if (digitalRead(9) || !digitalRead(DoorPin)) {
    updTimer = millis();  
    if (millis() - EEtime > 120000) { SaveKm(); EEtime = millis(); }
  } 

    if (millis() - updTimer < 30000) {UpdDisplays();}
    else if( DisplayST) { DisplaysOFF();}
    if (millis() - updTimer > 10800000) {afStartTime = 1; afStartReset = odometrPulses;}



  ResSpThCount();
}
