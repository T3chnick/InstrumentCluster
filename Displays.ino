void UpdDisplays() {
  if (!DisplayST) { initDisplays(); }
  if (millis() - cDispTimer > cDispInterval) { UpdKM(); cDispUpd(); cDispTimer = millis(); }
  if (millis() - lDispTimer > 400) { lDispUpd(); lDispTimer = millis(); }
  if (millis() - rDispTimer > 1000) { rDispUpd(); rDispTimer = millis(); }
  }
void cDispUpd() {
  
  DispSubPage = constrain(DispSubPage, 0, SubPageMax);
  c.clearDisplay();

  switch (DispPage) {
    case 0: { SubPageMax = 4; VolButtBusy = 0;  
        switch (DispSubPage) {
          case 0: { cDispInterval = 2000;  // odometr
              PrintMsgF(56, 31, "KM");
              c.setFont(&wwDigital8pt7b);
              c.setCursor(getXtrip(), 25);
              c.print(trip, 1);
              c.setCursor(35, 56);
              c.print(odometr);
              if (buttR.isHold()) { tripreset = odometrPulses; tripTime = 0; SaveKm(); }
            } break;

          case 1: { cDispInterval = 150;   // speed
              PrintMsgF(47, 11, "SPEED");
              float temSp = Speed();
              c.setFont(&wwDigital24pt7b);
              c.setCursor(getXsp(temSp), 55);
              c.print(temSp, 0);
            } break;

          case 2: { cDispInterval = 1000;  // Service A
              PrintMsgF(37, 11, "SERVICE A");
              c.setFont(); c.setCursor(25, 27); c.print("IN         KM");
              c.setFont(&wwDigital8pt7b); c.setCursor(43, 35); c.print(ServiceA);
              c.setFont(); 
              uint32_t sec = serviceAtime / 1000ul; 
              c.setCursor(6, 42); c.print(sec / 3600ul ); c.print(":"); c.print((sec % 3600ul) / 60ul); c.print(" H");
              uint16_t rpm =  (thPulses/60) / (serviceAtime/1000/60);
              c.setCursor(69, 42); c.print(rpm); c.print(" RPM");
              uint32_t revs = thPulses/60;
              c.setCursor(25, 53); c.print("REVS "); c.print(revs);
              if (buttR.isHold()) { serviceAreset = odometr; thPulses = 0; serviceAtime = 0; SaveKm(); }
            } break;

          case 3: { cDispInterval = 1000;  // ServiceB
              PrintMsgF(37, 11, "SERVICE B");
              c.setFont(&wwDigital8pt7b);
              c.setCursor(43, 40);
              c.print(ServiceB);
              PrintMsgF(17, 51, "hold R to reset");
              if (buttR.isHold()) { serviceBreset = odometr; SaveKm(); }
            } break;

          case 4: { cDispInterval = 10000; // Oil level
              PrintMsgF(36, 11, "OIL LEVEL");
              c.drawBitmap(32, 24,  oil, 62, 21, WHITE);
              PrintMsgF(56, 50, "OK");
              //PrintMsgF(23, 50, "! LOW LEVEL !");
            } break;
          }
      } break;

    case 1: { SubPageMax = 1; VolButtBusy = 0; cDispInterval = 1000; 
    
        switch (DispSubPage) {  
          case 0: {
            PrintMsgF(29, 11, "AFTER START"); 
            uint32_t sec = afStartTime / 1000ul; 
            c.setFont();          
            c.setCursor(6, 27);
            c.print(sec / 3600ul );
            c.print(":");
            c.print((sec % 3600ul) / 60ul);
            c.print(" H");

            c.setCursor(68, 27);
            c.print(afStart,1);
            c.print(" KM");
                        
            c.setCursor(40, 40);
            c.print(afStart/(afStartTime/1000.0/60.0/60.0),1);
            c.print(" KMH");

            c.setCursor(26, 52);
            c.print("--.-");
            c.print(" L.100KM");
            } break;

          case 1: {
            PrintMsgF(29, 11, "AFTER RESET"); 
            if (buttR.isHold()) { tripreset = odometrPulses; tripTime = 1; SaveKm(); }
            
            uint32_t sec = tripTime / 1000ul; 
            c.setFont();           
            c.setCursor(6, 27);
            c.print(sec / 3600ul );
            c.print(":");
            c.print((sec % 3600ul) / 60ul);
            c.print(" H");

            c.setCursor(68, 27);
            c.print(trip,1);
            c.print(" KM");
                        
            c.setCursor(40, 40);
            c.print(trip/(tripTime/1000.0/60.0/60.0),1);
            c.print(" KMH");

            c.setCursor(26, 52);
            c.print("--.-");
            c.print(" L.100KM");
            }break;
        }
      }break;


    case 2: { SubPageMax = 7; VolButtBusy = 1; cDispInterval = 60000;  //Settings
        
        DateTime now = myRTC.now();
        int H = now.hour();
        int M = now.minute();

        switch (DispSubPage) {
         
          case 0: {
            PrintMsgF(38, 11, "SETTINGS");
            PrintMsgF(4, 34, "PRESS DOWN TO ENTER");
            } break;

          case 1: {
              if(vKeyEvent) { 
                if(vKeyEvent == 1){ H++; if (H > 23) { H = 0; }} 
                else if (vKeyEvent == 2) { H--; if (H < 0) { H = 23; }}
                setRTC.setHour(H); 
              }
              PrintClock(H, M);
              c.drawRect(24, 24, 76, 15, WHITE);
            } break;

          case 2: {
              if(vKeyEvent) {
                if(vKeyEvent == 1) { M++; if (M > 59) { M = 0; }}
                else if (vKeyEvent == 2) { M--; if (M < 0) { M = 59; }}
                setRTC.setMinute(M); setRTC.setSecond(0);
              }
              PrintClock(H, M);
              c.drawRect(24, 40, 76, 15, WHITE);
            } break;

          case 3: {
              if(vKeyEvent) { (vKeyEvent == 1) ? ServiceAinterval += 500 : ServiceAinterval -= 500; 
                SaveIntervals();
              }
              PrintServiceSet();
              c.drawRect(10, 24, 104, 15, WHITE);
            } break;

          case 4: {
              if(vKeyEvent) { (vKeyEvent == 1) ? ServiceBinterval += 500 : ServiceBinterval -= 500; 
                SaveIntervals();
              }            
              PrintServiceSet();
              c.drawRect(10, 40, 104, 15, WHITE);
            } break;

          case 5: {
              if(vKeyEvent) { (vKeyEvent == 1) ? CC_Kp += 0.1 : CC_Kp -= 0.1; 
                saveCCpid();
              }            
              PrintCC();
              c.drawRect(20, 20, 84, 13, WHITE); 
            } break;

          case 6: {
              if(vKeyEvent) { (vKeyEvent == 1) ? CC_Ki += 0.02 : CC_Ki += 0.02; 
                saveCCpid();
              }                       
              PrintCC();
              c.drawRect(20, 33, 84, 13, WHITE);
            } break;

          case 7: {
              if(vKeyEvent) { (vKeyEvent == 1) ? CC_Kd += 0.02 : CC_Kd += 0.02;  
                saveCCpid();
              }              
              PrintCC();
              c.drawRect(20, 46, 84, 13, WHITE);
            } break;
        }
      }break;
  }
  vKeyEvent = 0;
  c.display();
  }

void lDispUpd() {
  dl.clearDisplay();
  dl.setCursor(0, 44);
  dl.print(th);
  dl.display();
  }

void rDispUpd() {
  dr.clearDisplay();
  DateTime now = myRTC.now();

  int H = now.hour();
  if (H < 10) {
    dr.setCursor(5, 44);
    dr.print("0");
    dr.setCursor(33, 44);
  } else {
    dr.setCursor(5, 44);
  }
  dr.print(H);

  int M = now.minute();
  if (M < 10) {
    dr.setCursor(67, 44);
    dr.print("0");
    dr.setCursor(95, 44);
  } else {
    dr.setCursor(67, 44);
  }
  dr.print(M);

  if (clock2dot) {
    dr.fillRect(62, 19, 4, 6, WHITE);
    dr.fillRect(62, 34, 4, 6, WHITE);
  }
  clock2dot = !clock2dot;
  dr.display();
  }

void PrintClock(int H, int M) {
  PrintMsgF(36, 11, "SET CLOCK");
  PrintMsgF(30, 28, "HOUR"); PrintMsgN(83, 28, H);
  PrintMsgF(30, 44, "MINUTE"); PrintMsgN(83, 44, M);
  }

void PrintServiceSet() {
  PrintMsgF(36, 11, "INTERVALS");
  PrintMsgF(13, 28, "ServiceA"); PrintMsgN(82, 28, ServiceAinterval);
  PrintMsgF(13, 44, "ServiceB"); PrintMsgN(82, 44, ServiceBinterval);
  }

void PrintCC() {
  PrintMsgF(38, 11, "CC SETUP");
  PrintMsgF(23, 23, "CC_Kp");
  if (CC_Kp < 10) {
    PrintMsgFl(78, 23, CC_Kp, 2);
  } else {
    PrintMsgFl(72, 23, CC_Kp, 2);
  }
  PrintMsgF(23, 36, "CC_Ki");
  PrintMsgFl(78, 36, CC_Ki, 2);
  PrintMsgF(23, 49, "CC_Kd");
  PrintMsgFl(78, 49, CC_Kd, 2);
  }

void PrintMsgF(uint8_t x, uint8_t y, const char *msg) {
  c.setFont();
  c.setCursor(x, y);
  c.print(msg);
  }

void PrintMsgN(uint8_t x, uint8_t y, uint16_t num) {
  c.setFont();
  c.setCursor(x, y);
  c.print(num);
  }

void PrintMsgFl(uint8_t x, uint8_t y, float num, uint8_t d) {
  c.setFont();
  c.setCursor(x, y);
  c.print(num, d);
  }

void initDisplays() {
  c.begin(SH1106_SWITCHCAPVCC);
  c.setTextColor(WHITE);
  cDispUpd();
  dl.begin(SH1106_SWITCHCAPVCC, 0x3C);
  dl.setTextColor(WHITE);
  dl.setFont(&wwDigital24pt7b);
  lDispUpd();
  dr.begin(SH1106_SWITCHCAPVCC, 0x3D);
  dr.setTextColor(WHITE);
  dr.setFont(&wwDigital24pt7b);
  rDispUpd();
  DisplayST = 1;
  }

void DisplaysOFF() {
  dl.clearDisplay();
  dl.display();
  dr.clearDisplay();
  dr.display();
  c.clearDisplay();
  c.display();
  eeprom.eeprom_write(0, odometrPulses);
  DisplayST = 0;
  }

void settime() {
  //setRTC.setClockMode(false);  // set to 24h
  //setClockMode(true); // set to 12h
  //setRTC.setYear(year);
  //setRTC.setMonth(month);
  //setRTC.setDate(date);
  //setRTC.setDoW(dOW);
  setRTC.setHour(23);
  setRTC.setMinute(9);
  //setRTC.setSecond(second);
  }
