void CheckButt() {
  ssButt.tick();
  buttR.tick();
  if (buttR.isClick()) { DispSubPage++; }
  wkl();
  wkr();
}

void wkl(void) {  ///// Steering wheel left block /////
  uint16_t wkl = analogRead(wkL_pin);
  if (wkl > 1000) { eventL = millis();
    if (flagL != 0) {
           if (flagL == 2) { DispSubPage--; } 
      else if (flagL == 4) { DispSubPage++; } 
      else if (flagL == 5) { DispPage++; DispSubPage = 0; } 
      else if (flagL == 6) { DispPage--; DispSubPage = 0; }
      cDispUpd();
      flagL = 0;
    }
  } else if (millis() - eventL > 10) {
    if (key(wkl, key1)) { flagL = 2; }  //next
    else if (key(wkl, key2)) { flagL = 4; }                                        //prev
    else if (key(wkl, key3)) { flagL = 5; }  //nav
    else if (key(wkl, key4)) { flagL = 6; }  //bk
  }
}

void wkr(void) {  ///// Steering wheel right block /////
  uint16_t wkr = analogRead(wkR_pin);
  if (wkr >= 1000) { eventR = millis();
    if (flagR != 0) { 
           if (flagR == 1) { btCnt(btuppin, 200); } 
      else if (flagR == 2) { btCnt(btdnpin, 200); }
      else if (flagR == 3) { keyPlus = 1; } 
      else if (flagR == 4) { keyMinus = 1;}
      flagR = 0;
    }
    if (millis() - btKeyTime > btKeyDelay) {
      pinMode(btuppin, INPUT);
      pinMode(btdnpin, INPUT);
    }
  } else if (millis() - eventR > 10) {
         if (key(wkr, key1)) { if (!VolButtBusy) { btCnt(btuppin, 950); } else { flagR = 3; }} 
    else if (key(wkr, key4)) { if (!VolButtBusy) { btCnt(btdnpin, 950); } else { flagR = 4; }} 
    else if (key(wkr, key2)) { flagR = 1; } 
    else if (key(wkr, key3)) { flagR = 2; }
  }
}

bool key(uint16_t Val, uint16_t keyVal) {
  if (Val > (keyVal - avg) && Val < (keyVal + avg)) {
    return 1; } else { return 0; }
}


void btCnt(uint8_t pin, uint32_t delay) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  if (flagR < 3) { btKeyTime = millis(); flagR = 5;}
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
