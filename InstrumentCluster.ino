#define SYSRESETREQ    (1<<2)
#define VECTKEY        (0x05fa0000UL)
#define VECTKEY_MASK   (0x0000ffffUL)
#define AIRCR          (*(uint32_t*)0xe000ed0cUL) // fixed arch-defined address
#define REQUEST_EXTERNAL_RESET (AIRCR=(AIRCR&VECTKEY_MASK)|VECTKEY|SYSRESETREQ)


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
#include <fonts/wwDigital14pt7b.h>
#include <fonts/wwDigital8pt7b.h>
#include <fonts/FreeSans18pt7b.h>
#include <fonts/FreeSans24pt7b.h>
Adafruit_SH1106 dl(-1);
Adafruit_SH1106 dr(-1);
Adafruit_SH1106 c(4, 6, 5);
bool DisplayST, Msg;
int8_t Disp_Page = 0, Disp_Sub_Page, Sub_Page_Max = 10;
uint16_t c_Disp_Interval;
uint32_t lDispTimer, cDispTimer, rDispTimer, updTimer;

//Analog buttons routines//
#define wkL_pin A1  // input from left key block on steering wheel
#define wkR_pin A0  // input from right key block on steering wheel
uint8_t avg = 20;   //
#define key1 526    //analog value for resistive key
#define key2 693    //analog value for resistive key
#define key3 780    //analog value for resistive key
#define key4 826    //analog value for resistive key
#define btuppin 8
#define btdnpin 7
bool Vol_Butt_Busy; 
int8_t v_Key_Event;
uint32_t v_Key_Event_Time;
int8_t flagL, flagR;     // Debounce function for key block on steering wheel
uint32_t eventR, eventL;  // Timer for key block on steering wheel

//taho routines
volatile uint32_t micros_th = 0;  //pulse time
volatile uint64_t tz = 0;         //counter
volatile uint16_t th = 0;         //rpm
volatile bool tt = false;         //trigger
volatile uint64_t TH_Pulses; 

//Speed & km routines
volatile uint32_t micros_sp = 0;  //pulse time
volatile uint64_t sz = 0;         //counter
volatile float sp = 0;            //Speed
volatile bool st = false;         //trigger
volatile uint64_t Odometr_Pulses;
volatile int32_t  Service_A_KM, Service_B_KM, Service_A_interval, Service_B_interval;
volatile uint32_t driveTcount, odometr, service_A_reset, service_B_reset, service_A_time, Service_B_KMtime;
volatile float SpAvg[20], Trip_KM;
volatile uint8_t saveSpeedPos;

//After start routines
uint32_t af_Start_KM_Time; 
uint64_t af_Start_KM_Reset; 
float af_Start_KM;
volatile uint32_t af_Start_KM_Inj_Milis;

//After reset routines
uint32_t Trip_KM_Time;
int16_t Inj_Flow = 115;
uint64_t Trip_KM_Reset;
volatile float injTime; 
volatile int32_t microsInj,  af_Reset_Inj_Milis;


//StartStop routines
uint32_t holdACCtime, lastWork, StarterTime;
uint8_t Engine_ST;
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

int x;
// other
GButton buttR(53);
uint32_t btKeyTime, btKeyDelay;
//Odometr_Pulses = 11638450000;

void setup() {
  Wire.begin(); //SaveIntervals();//settime();
  ReadEEprom();
  if(Engine_ST) {Engine_ST = 3; StartIgn();}
  af_Start_KM_Time = 1;
  af_Start_KM_Reset = Odometr_Pulses;
  UpdKM();
  setupSSpins();
  initDisplays();
  SetupButtons();
  SetInterrupts();
  CCservo.attach(CCservoPin);
  Wire.setClock(800000);
  //Serial.begin(115200);
  }

void loop() {
//if (x < 104) x++; else x=0;
//volume_MSG();
  CheckButt();

  if (digitalRead(9) || !digitalRead(DoorPin)) {
    updTimer = millis();  
    if (millis() - EEtime > 120000) { SaveKm(); EEtime = millis(); }
  } 

    if (millis() - updTimer < 10000) {UpdDisplays();}
    else if( DisplayST) { DisplaysOFF();}
    if (millis() - updTimer > 10800000) {af_Start_KM_Time = 1; af_Start_KM_Reset = Odometr_Pulses; af_Start_KM_Inj_Milis = 0;}

  ResSpThCount();
//Serial.println(analogRead(wkL_pin));
  }
