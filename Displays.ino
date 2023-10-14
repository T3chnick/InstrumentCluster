void UpdDisplays() {
  if (!DisplayST) { initDisplays(); }
  if (millis() - cDispTimer > c_Disp_Interval) {  cDispUpd(); cDispTimer = millis(); }
  if (millis() - lDispTimer > 400) { lDispUpd(); lDispTimer = millis(); }
  if (millis() - rDispTimer > 1000) { rDispUpd(); rDispTimer = millis(); }
  }
void cDispUpd() {
  Msg = 0;
  Disp_Sub_Page = constrain(Disp_Sub_Page, 0, Sub_Page_Max);
  UpdKM();
  c.clearDisplay();

  switch (Disp_Page) {
    case 0: { Sub_Page_Max = 4; Vol_Butt_Busy = 0;  
        switch (Disp_Sub_Page) {
          case 0: { c_Disp_Interval = 2000;  // odometr
              Print_Msg_NoFont(56, 32, "KM");
              c.setFont(&wwDigital8pt7b);
              c.setCursor(getXTrip_KM(), 25);
              c.print(Trip_KM, 1);
              c.setCursor(35, 56);
              c.print(odometr);
              if (buttR.isHold()) { Trip_KM_Reset = Odometr_Pulses; Trip_KM_Time = 1; af_Reset_Inj_Milis = 0; SaveKm(); }
            } break;

          case 1: { c_Disp_Interval = 150;   // speed
              Print_Msg_NoFont(47, 11, "SPEED");
              float temSp = Speed();
              c.setFont(&wwDigital24pt7b);
              c.setCursor(getXsp(temSp), 55);
              c.print(temSp, 0);
            } break;

          case 2: { c_Disp_Interval = 1000;  // Service A
              Print_Msg_NoFont(34, 11, "SERVICE A");
              c.setFont(); c.setCursor(22, 27); c.print("IN         KM");
              c.setFont(&wwDigital8pt7b); c.setCursor(42, 35); c.print(Service_A_KM);
              c.setFont(); 
              
              uint32_t sec = service_A_time / 1000ul; 
              c.setCursor(6, 41); c.print(sec / 3600ul ); c.print(":"); c.print((sec % 3600ul) / 60ul); c.print(" H");
              
              uint16_t rpm =  (((TH_Pulses/2) / (service_A_time/1000))*60);
              c.setCursor(69, 41); (rpm > 7000) ? c.print("--") : c.print(rpm); c.print(" RPM");
              
              uint16_t revsKM = (TH_Pulses/2) / (odometr - service_A_reset);
              c.setCursor(26, 53); c.print("REVS.KM "); (revsKM > 20000) ? c.print("--") : c.print(revsKM);
              
              if (buttR.isHold()) { service_A_reset = odometr; TH_Pulses = 0; service_A_time = 0; SaveKm(); }
            } break;

          case 3: { c_Disp_Interval = 1000;  // Service_B_KM
              Print_Msg_NoFont(34, 11, "SERVICE B");
              c.setFont(&wwDigital8pt7b);
              c.setCursor(43, 40);
              c.print(Service_B_KM);
              Print_Msg_NoFont(17, 51, "hold R to reset");
              if (buttR.isHold()) { service_B_reset = odometr; SaveKm(); }
            } break;

          case 4: { c_Disp_Interval = 10000; // Oil level
              Print_Msg_NoFont(36, 11, "OIL LEVEL");
              c.drawBitmap(32, 24,  oil, 62, 21, WHITE);
              Print_Msg_NoFont(56, 50, "OK");
              //Print_Msg_NoFont(23, 50, "! LOW LEVEL !");
            } break;
          }
      } break;

    case 1: { Sub_Page_Max = 2; Vol_Butt_Busy = 0; c_Disp_Interval = 1000; 
    
        switch (Disp_Sub_Page) {  
          case 0: {  // AFTER START
            Print_Msg_NoFont(29, 11, "AFTER START"); 
            uint32_t sec = af_Start_KM_Time / 1000ul; 
            c.setFont();          
            c.setCursor(6, 27);
            c.print(sec / 3600ul );
            c.print(":");
            c.print((sec % 3600ul) / 60ul);
            c.print(" H");

            c.setCursor(68, 27);
            c.print(af_Start_KM,1);
            c.print(" KM");
                        
            c.setCursor(40, 40);
            c.print(af_Start_KM/(af_Start_KM_Time/1000.0/60.0/60.0),1);
            c.print(" KMH");

            float FuelCons = (( (af_Start_KM_Inj_Milis * (Inj_Flow/60000)) /1000.0 ) / Trip_KM) * 100;
            c.setCursor(26, 52);
            (FuelCons > 0 && FuelCons < 40) ? c.print(FuelCons,1) : c.print("--.-");
            c.print(" L.100KM");
            } break;

          case 1: {  // AFTER RESET
            Print_Msg_NoFont(29, 11, "AFTER RESET"); 
            if (buttR.isHold()) { Trip_KM_Reset = Odometr_Pulses; Trip_KM_Time = 1; af_Reset_Inj_Milis = 0; SaveKm(); }
            
            uint32_t sec = Trip_KM_Time / 1000ul; 
            c.setFont();           
            c.setCursor(6, 27);
            c.print(sec / 3600ul );
            c.print(":");
            c.print((sec % 3600ul) / 60ul);
            c.print(" H");

            c.setCursor(68, 27);
            c.print(Trip_KM,1);
            c.print(" KM");
                        
            c.setCursor(40, 40);
            c.print(Trip_KM/(Trip_KM_Time/1000.0/60.0/60.0),1);
            c.print(" KMH");
            
            float FuelCons = (( (af_Reset_Inj_Milis * (Inj_Flow/60000)) /1000.0 ) / Trip_KM) * 100;
            c.setCursor(26, 52);
            (FuelCons > 0 && FuelCons < 40) ? c.print(FuelCons,1) : c.print("--.-");
            c.print(" L.100KM");
            }break;

          case 2: { c_Disp_Interval = 400; // ECO
            Print_Msg_NoFont(53, 11, "ECO"); 

              float FuelNow = ((Inj_Flow/60000) * injTime / 1000.0) *th *30;
              if(sp) { FuelNow /sp *100;
                Print_Msg_NoFont(41, 52, "L/100KM"); 
              }
                else { 
                  Print_Msg_NoFont(54, 52, "L/H");
                }

              c.setFont(&wwDigital14pt7b);
              FuelNow = constrain(FuelNow,0,40);
              if(FuelNow) {
                FuelNow < 10 ? c.setCursor(42, 44) : c.setCursor(31, 44);
                c.print(FuelNow,1);
              }
              else { c.setCursor(48, 44); c.print("--"); }
              
              
              
           }break;

          }break;
      }break;


    case 2: { Sub_Page_Max = 9; Vol_Butt_Busy = 1; c_Disp_Interval = 60000;  //Settings
        
        DateTime now = myRTC.now();
        int H = now.hour();
        int M = now.minute();

        switch (Disp_Sub_Page) {       
          case 0: {
            Print_Msg_NoFont(38, 11, "SETTINGS");
            Print_Msg_NoFont(4, 34, "PRESS DOWN TO ENTER");
            } break;

          case 1: {  // set hour
              if(v_Key_Event) { H += v_Key_Event; if (H > 23) { H = 0; } else if (H < 0) { H = 23; }
                setRTC.setHour(H); 
              }
              Print_Clock_Setup(H, M);
              c.drawRect(24, 24, 76, 15, WHITE);
            } break;

          case 2: {  // set minute
              if(v_Key_Event) { M += v_Key_Event; if (M > 59) { M = 0;} else if (M < 0) { M = 59; }
                setRTC.setMinute(M); setRTC.setSecond(0);
              }
              Print_Clock_Setup(H, M);
              c.drawRect(24, 40, 76, 15, WHITE);
            } break;

          case 3: {  // set Service_A_KM
              if(v_Key_Event) { (v_Key_Event == 1) ? Service_A_interval += 500 : Service_A_interval -= 500; 
                SaveIntervals();
              }
              Print_Service_Set();
              c.drawRect(9, 24, 104, 15, WHITE);
            } break;

          case 4: {  // set Service_B_KM
              if(v_Key_Event) { (v_Key_Event == 1) ? Service_B_interval += 500 : Service_B_interval -= 500; 
                SaveIntervals();
              }            
              Print_Service_Set();
              c.drawRect(9, 40, 104, 15, WHITE);
            } break;

          case 5: {
              if(v_Key_Event) {CC_Kp += v_Key_Event/10.0;
                Save_Settings();
              }            
              Print_CC_Setup();
              c.drawRect(20, 20, 84, 13, WHITE); 
            } break;

          case 6: {
              if(v_Key_Event) { CC_Ki += v_Key_Event/50.0; 
                Save_Settings();
              }                       
              Print_CC_Setup();
              c.drawRect(20, 33, 84, 13, WHITE);
            } break;

          case 7: {
              if(v_Key_Event) { CC_Kd += v_Key_Event/50.0;  
                Save_Settings();
              }              
              Print_CC_Setup();
              c.drawRect(20, 46, 84, 13, WHITE);
            } break;
          case 8: {  // Inj_Flow
              if(v_Key_Event) {Inj_Flow += v_Key_Event; 
                SaveIntervals();
              }
              PrintInj_Flow();
              c.drawRect(9, 24, 104, 15, WHITE);
            }break;

          case 9: {
              if(v_Key_Event) {avg += v_Key_Event;
                Save_Settings();
              }            
              Print_WK_Setup();
              c.drawRect(20, 20, 84, 13, WHITE); 
            } break;
         
          }break;
      }break;
  }
  v_Key_Event = 0;
   
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




void Print_Clock_Setup(int H, int M) {
  Print_Msg_NoFont(36, 11, "SET CLOCK");
  Print_Msg_NoFont(30, 28, "HOUR"); Print_Msg_Num(83, 28, H);
  Print_Msg_NoFont(30, 44, "MINUTE"); Print_Msg_Num(83, 44, M);
  }

void Print_Service_Set() {
  Print_Msg_NoFont(36, 11, "INTERVALS");
  Print_Msg_NoFont(13, 28, "Service_A"); Print_Msg_Num(82, 28, Service_A_interval);
  Print_Msg_NoFont(13, 44, "Service_B"); Print_Msg_Num(82, 44, Service_B_interval);
  }

void Print_CC_Setup() {
  Print_Msg_NoFont(38, 11, "CC SETUP");
  Print_Msg_NoFont(23, 23, "CC_Kp");
  if (CC_Kp < 10.0) {
    Print_Msg_Float(78, 23, CC_Kp, 2);
  } else {
    Print_Msg_Float(72, 23, CC_Kp, 2);
  }
  Print_Msg_NoFont(23, 36, "CC_Ki");
  Print_Msg_Float(78, 36, CC_Ki, 2);
  Print_Msg_NoFont(23, 49, "CC_Kd");
  Print_Msg_Float(78, 49, CC_Kd, 2);
  }

void Print_WK_Setup() {
  Print_Msg_NoFont(38, 11, "WK SETUP");

  Print_Msg_NoFont(23, 23, "WK_AVG");
  Print_Msg_Num(90, 23, avg);

 /* Print_Msg_NoFont(23, 36, "CC_Ki");
  Print_Msg_Float(78, 36, CC_Ki, 2);

  Print_Msg_NoFont(23, 49, "CC_Kd");
  Print_Msg_Float(78, 49, CC_Kd, 2);
*/  }

void PrintInj_Flow() {
  Print_Msg_NoFont(41, 11, "INJ SET");
  
  Print_Msg_NoFont(12, 28,  "INJ_FLOW");
  Print_Msg_Float(92, 28, Inj_Flow, 0);

  float liter = ( (af_Reset_Inj_Milis * (Inj_Flow/60.0/1000.0)) /1000.0 );
  Print_Msg_NoFont(11, 46,  "TOTAL.CONS");
  Print_Msg_Float(82, 46, liter, 1);
  }

void volume_MSG(){
  c_Disp_Interval = 3000;
  cDispTimer = millis();
  Msg = 1;
  c.clearDisplay();
  Print_Msg_NoFont(47, 11, "AUDIO");
  c.drawRect(7, 30, 108, 16, WHITE); 
  c.fillRect(9, 32, x, 12, WHITE); 
  Print_Msg_NoFont(36, 51, "VOLUME "); c.print(x);
  c.display();
}

void Print_Msg_NoFont(uint8_t x, uint8_t y, char *msg) {
  c.setFont();
  c.setCursor(x, y);
  c.print(msg);
  }

void Print_Msg_Num(uint8_t x, uint8_t y, uint16_t num) {
  c.setFont();
  c.setCursor(x, y);
  c.print(num);
  }

void Print_Msg_Float(uint8_t x, uint8_t y, float num, uint8_t d) {
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
  eeprom.eeprom_write(0, Odometr_Pulses);
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
