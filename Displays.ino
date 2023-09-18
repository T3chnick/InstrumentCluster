
void UpdDisplays() {
  if (!DisplayST) { initDisplays(); }
  if (millis() - cDispTimer > cDispInterval) { cDispUpd(); cDispTimer = millis(); }
  if (millis() - lDispTimer > 200) { lDispUpd(); lDispTimer = millis(); }
  if (millis() - rDispTimer > 1000) { rDispUpd(); rDispTimer = millis(); }
}
void cDispUpd() {
  DispPage = constrain(DispPage, 0, 1);
  DispSubPage = constrain(DispSubPage, 0, SubPageMax);
  display.clearDisplay();

  switch (DispPage) {

    case 0: { SubPageMax = 3; VolButtBusy = 0;
    
        switch (DispSubPage) {

          case 0: { cDispInterval = 500;  // odometr
              PrintMsgF(56, 31, "KM");
              display.setFont(&Seven_Segment9pt7b);
              display.setCursor(getXtrip(), 25);
              display.print(trip, 1);
              display.setCursor(35, 56);
              display.print(odometr);
              if (buttR.isHold()) { tripreset = odometrPulses; SaveKm(); }
            } break;

          case 1: { cDispInterval = 150;  // speed
              PrintMsgF(47, 11, "SPEED");
              float temSp = Speed();
              display.setFont(&digits18pt7b);
              display.setCursor(getXsp(temSp), 55);
              display.print(temSp, 0);
            } break;

          case 2: { cDispInterval = 500;  //Service A
              PrintMsgF(37, 11, "SERVICE A");
              display.setFont(&Seven_Segment9pt7b);
              display.setCursor(43, 40);
              display.print(ServiceA);
              PrintMsgF(17, 51, "hold R to reset");
              if (buttR.isHold()) { serviceAreset = odometr; SaveKm(); }
            } break;

          case 3: { cDispInterval = 500;  // ServiceB
              PrintMsgF(37, 11, "SERVICE B");
              display.setFont(&Seven_Segment9pt7b);
              display.setCursor(43, 40);
              display.print(ServiceB);
              PrintMsgF(17, 51, "hold R to reset");
              if (buttR.isHold()) { serviceBreset = odometr; SaveKm(); }
            } break;
        }
      }
      break;



    case 1: { SubPageMax = 4; VolButtBusy = 1; cDispInterval = 100;  //set clock
        PrintMsgF(38, 11, "SETTINGS");
        DateTime now = myRTC.now();
        int H = now.hour();
        int M = now.minute();

        switch (DispSubPage) {

          case 0: {
              PrintCC();
              display.drawRect(20, 20, 84, 13, WHITE); if (keyPlus) { CC_Kp += 0.1; saveCCpid(); } 
              else if (keyMinus) { CC_Kp -= 0.1; saveCCpid(); }
            } break;

          case 1: {
              PrintCC();
              display.drawRect(20, 33, 84, 13, WHITE);
              if (keyPlus) { CC_Ki += 0.02; saveCCpid(); } 
              else if (keyMinus) { CC_Ki -= 0.02; saveCCpid(); }
            } break;

          case 2: {
              PrintCC();
              display.drawRect(20, 46, 84, 13, WHITE);
              if (keyPlus) { CC_Kd += 0.01; saveCCpid();} 
              else if (keyMinus) {CC_Kd -= 0.01;saveCCpid();}
            } break;

          case 3: {
              PrintClock(H, M);
              display.drawRect(24, 24, 76, 15, WHITE);
              if (keyPlus) {H++; if (H > 23) { H = 0; } setRTC.setHour(H); } 
              else if (keyMinus) { H--; if (H < 0) { H = 23; } setRTC.setHour(H); }
            } break;

          case 4: {
              PrintClock(H, M);
              display.drawRect(24, 40, 76, 15, WHITE);
              if (keyPlus) { M++; if (M > 59) { M = 0; } setRTC.setMinute(M); setRTC.setSecond(0); } 
              else if (keyMinus) { M--; if (M < 0) { M = 59; } setRTC.setMinute(M); setRTC.setSecond(0); }
            } break;
        }
      }
      break;

    case 2:
      {
      }
      break;
  }
  keyPlus = 0;
  keyMinus = 0;
  display.display();
}

void lDispUpd() {
  dl.clearDisplay();
  dl.setFont();
  dl.setCursor(110, 13);
  dl.print("th");
  dl.setFont(&digits18pt7b);
  dl.setCursor(0, 44);
  dl.print(sp, 1);
  dl.display();
}

void rDispUpd() {

  dr.clearDisplay();
  DateTime now = myRTC.now();

  int H = now.hour();
  if (H < 10) {
    dr.setCursor(12, 44);
    dr.print("0");
    dr.setCursor(36, 44);
  } else {
    dr.setCursor(12, 44);
  }
  dr.print(H);

  int M = now.minute();
  if (M < 10) {
    dr.setCursor(75, 44);
    dr.print("0");
    dr.setCursor(99, 44);
  } else {
    dr.setCursor(76, 44);
  }
  dr.print(M);

  if (clock2dot) {
    dr.fillRect(62, 19, 4, 6, WHITE);
    dr.fillRect(62, 34, 4, 6, WHITE);
  }
  clock2dot = !clock2dot;

  dr.display();
}

void initDisplays() {
  display.begin(SH1106_SWITCHCAPVCC);
  display.setTextColor(WHITE);
  cDispUpd();
  dl.begin(SH1106_SWITCHCAPVCC, 0x3C);
  dl.setTextColor(WHITE);
  dl.setFont(&digits18pt7b);
  lDispUpd();
  dr.begin(SH1106_SWITCHCAPVCC, 0x3D);
  dr.setTextColor(WHITE);
  dr.setFont(&digits18pt7b);
  rDispUpd();

  DisplayST = 1;
}

void DisplaysOFF() {

  dl.clearDisplay();
  dl.display();
  dr.clearDisplay();
  dr.display();
  display.clearDisplay();
  display.display();
  eeprom.eeprom_write(0, odometrPulses);
  DisplayST = 0;
}

void PrintClock(int H, int M) {
  PrintMsgF(30, 28, "HOUR"); PrintMsgN(83, 28, H);
  PrintMsgF(30, 44, "MINUTE"); PrintMsgN(83, 44, M);
}

void PrintCC() {
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
  display.setFont();
  display.setCursor(x, y);
  display.print(msg);
}

void PrintMsgN(uint8_t x, uint8_t y, uint16_t num) {
  display.setFont();
  display.setCursor(x, y);
  display.print(num);
}

void PrintMsgFl(uint8_t x, uint8_t y, float num, uint8_t d) {
  display.setFont();
  display.setCursor(x, y);
  display.print(num, d);
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
