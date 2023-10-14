void CheckButt() {
  ssButt.tick();
  buttR.tick();
  if (buttR.isClick()) { REQUEST_EXTERNAL_RESET;}// Disp_Sub_Page++; updTimer = millis(); cDispUpd(); }
  wkl();
  wkr();
  }

void wkl(void) {  ///// Steering wheel left block /////
  uint16_t wkl = analogRead(wkL_pin);
  if (wkl > 880) { eventL = millis(); flagL = 0; }

    else   if (millis() - eventL > 5 && !flagL) { updTimer = millis();
           if (Msg) { Msg = 0; }
      else if (key(wkl, key1)) { Disp_Sub_Page--; }  
      else if (key(wkl, key2)) { Disp_Sub_Page++; }  
      else if (key(wkl, key3)) { Disp_Page++; Disp_Sub_Page = 0; }  
      else if (key(wkl, key4)) { Disp_Page--; Disp_Sub_Page = 0; } 
      flagL = 1;
      Disp_Page = constrain(Disp_Page, 0, 2);
      cDispUpd();
      }
    else if (millis() - eventL > 300 ) { eventL = millis(); flagL = 0; } 
  } 
 

void wkr(void) {  ///// Steering wheel right block /////
  uint16_t wkr = analogRead(wkR_pin);
  if (wkr > 1000) { eventR = millis(); v_Key_Event_Time = 0;
    if (flagR) { 
           if (flagR == 3) { btCnt(btuppin, 200); } 
      else if (flagR == 4) { btCnt(btdnpin, 200); }
      flagR = 0;
    }
    if (millis() - btKeyTime > btKeyDelay) {
      pinMode(btuppin, INPUT);
      pinMode(btdnpin, INPUT);
    }
  } else if (millis() - eventR > 10) { updTimer = millis();
         if (key(wkr, key1)) { if(Vol_Butt_Busy) V_Key( 1); else btCnt(btuppin, 950); }
    else if (key(wkr, key4)) { if(Vol_Butt_Busy) V_Key(-1); else btCnt(btdnpin, 950); }
    else if (key(wkr, key2)) { flagR = 3; } 
    else if (key(wkr, key3)) { flagR = 4; }
  }
  }

void V_Key(int8_t x) {
  if(millis() - v_Key_Event_Time > 150){
    v_Key_Event = x; cDispUpd();
    v_Key_Event_Time = millis(); 
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
