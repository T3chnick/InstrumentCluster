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
boolean clock2dot;

// Display routines //
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_SSD1306.h>
#include <fonts/FreeSans18pt7b.h>
#include <fonts/FreeSans24pt7b.h>
Adafruit_SH1106 dl(-1);
Adafruit_SH1106 dr(-1);
Adafruit_SH1106 display(47, -1, 49);
boolean DisplayST;
int16_t DispPage = 3;
uint32_t lDispTimer, cDispTimer, rDispTimer;

//Analog buttons routines//
#define wkL_pin  A1                        // input from left key block on steering wheel
#define wkR_pin  A0                        // input from right key block on steering wheel
uint8_t avg = 10;                          //    
#define key1 526                           //analog value for resistive key
#define key2 693                           //analog value for resistive key
#define key3 780                           //analog value for resistive key
#define key4 826                           //analog value for resistive key
#define btuppin      8       
#define btdnpin      7      
uint8_t  flagL, flagR;                     // Debounce function for key block on steering wheel
uint32_t eventR, eventL;                   // Timer for key block on steering wheel

//taho routines
volatile uint32_t    micros_th = 0;         //pulse time
volatile uint64_t    tz        = 0;         //counter
volatile uint16_t    th        = 0;         //rpm
volatile boolean     tt        = false;     //trigger 

//Speed & km routines
volatile uint32_t    micros_sp = 0;        //pulse time
volatile uint64_t    sz = 0;               //counter
volatile uint16_t    sp = 0;               //Speed
volatile boolean     st = false;           //trigger
volatile uint64_t    odometrPulses;
uint64_t servicereset, tripreset;
uint32_t odometr, toService;
float trip;

//StartStop routines
uint64_t  StarterTime;
uint32_t  lastWork;        
uint8_t   statusEngine=0;  
bool    cLock, stateIgn = false, stateACC = false; 
#define TrunkPin      22       //-->выход на багажник
#define ClosePin      23       //-->выход на цз
#define DoorPin       50       //<--Вход с концевика двери
#define BrakePin      24       //<--Вход с тормоза
#define ClutchPin     24       //<--Вход с тормоза
#define IgnPin        25       //-->Выход на зажигание 
#define ACCPin        26       //-->Выход на ACC 
#define StarterPin    97       //-->Выход на стартера          
#define Yled          28       //-->Выход на глазок Y 
#define Gled          29       //-->Выход на глазок G 
#define Wled          30       //-->Выход на подсветку кнопки  
#define SSButtPin     31       //<--Вход с кнопки 
GButton ssButt(SSButtPin);

// CruiseControl routines
#include <Servo.h>
Servo CCservo; 
uint8_t CCstatus, CCspeedSet, CClastSpeed;
#define CCservoPin    32 
#define CCkeyPin      A2
#define accel  1
#define decel  1
#define cancel 1
#define reset  1

// other
GButton butt1(53);
uint32_t btKeyTime, btKeyDelay;
//odometrPulses = 11638450000;

void setup() {
  Wire.begin();
  ReadEEprom();
  setupSSpins();
  initDisplays();
  SetupButtons();  
  SetInterrupts();
  CCservo.attach(CCservoPin);
}

void loop() {
  // digitalWrite(btuppin,HIGH);
  //  digitalWrite(btdnpin,LOW);

  if (digitalRead(9) || !digitalRead(DoorPin) ) {
    ControlStartStop();
    CheckButt();  
    UpdDisplays();  
    if (millis()-EEtime > 60000) {eeprom.eeprom_write(0, odometrPulses);  EEtime=millis(); } 
  }
  else { if(DisplayST) {DisplaysOFF();}}

  ResSpThCount();

    
}

