void CheckButt() {
  ssButt.tick();
  buttR.tick();
  if (buttR.isClick()) { Disp_Sub_Page++; updTimer = millis(); cDispUpd(); }
  wkl();
  wkr();
  }

void wkl(void) {  ///// Steering wheel left block /////
  uint16_t wkl = analogRead(wkL_pin);
  if (wkl > 1000) { eventL = millis();
    if (flagL) {
           if (flagL == 2) { Disp_Sub_Page--; } 
      else if (flagL == 4) { Disp_Sub_Page++; } 
      else if (flagL == 5) { Disp_Page++; Disp_Sub_Page = 0; } 
      else if (flagL == 6) { Disp_Page--; Disp_Sub_Page = 0; }
      Disp_Page = constrain(Disp_Page, 0, 2);
      cDispUpd();
      flagL = 0;
    }
  } else if (millis() - eventL > 10 && !flagL) { updTimer = millis();
         if (key(wkl, key1)) { flagL = 2; }  
    else if (key(wkl, key2)) { flagL = 4; }  
    else if (key(wkl, key3)) { flagL = 5; }  
    else if (key(wkl, key4)) { flagL = 6; }  
  }
  }

void wkr(void) {  ///// Steering wheel right block /////
  uint16_t wkr = analogRead(wkR_pin);
  if (wkr > 1000) { eventR = millis();
    if (flagR) { 
           if (flagR == 3) { btCnt(btuppin, 200); } 
      else if (flagR == 4) { btCnt(btdnpin, 200); }
      else if (flagR == 1 || flagR == 2 ) { v_Key_Event = flagR; cDispUpd();} 
      flagR = 0;
    }
    if (millis() - btKeyTime > btKeyDelay) {
      pinMode(btuppin, INPUT);
      pinMode(btdnpin, INPUT);
    }
  } else if (millis() - eventR > 10) { updTimer = millis();
         if (key(wkr, key1)) { if(Vol_Butt_Busy) flagR = 1; else btCnt(btuppin, 950); }
    else if (key(wkr, key4)) { if(Vol_Butt_Busy) flagR = 2; else btCnt(btdnpin, 950); }
    else if (key(wkr, key2)) { flagR = 3; } 
    else if (key(wkr, key3)) { flagR = 4; }
  }
  }

bool key(uint16_t Val, uint16_t keyVal) {
    if (Val > (keyVal - avg) && Val < (keyVal + avg)) {
      return 1; } else { return 0; }
  }


void btCnt(uint8_t pin, uint32_t delay) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  if (flagR != 5) { btKeyTime = millis(); flagR = 5;}
  btKeyDelay = delay;
  }

void SetupButtons() {
  buttR.setDebounce(20);       // настройка антидребезга (по умолчанию 80 мс)
  buttR.setTimeout(1000);      // настройка таймаута на удержание (по умолчанию 500 мс)
  buttR.setClickTimeout(600);  // настройка таймаута между кликами (по умолчанию 300 мс)
  buttR.setType(HIGH_PULL);
  buttR.setDirection(NORM_OPEN);
  pinMode(53, INPUT_PULLUP);
  }
