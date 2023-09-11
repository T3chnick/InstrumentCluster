void CheckButt() {
  ssButt.tick(); butt1.tick(); 
  if (butt1.isClick()) { DispPage++;  lDispUpd(); if (DispPage > 7)  DispPage = 0;} 
  if (butt1.isHold()) { tripreset = odometrPulses; DispPage = 2; 
  eeprom.eeprom_write(10, tripreset); 
  eeprom.eeprom_write(0, odometrPulses);
  }
  wkl(); wkr();
}


void wkl(void){ ///// Steering wheel left block /////
  uint16_t wkl = analogRead(wkL_pin);
  if(wkl>1000) {eventL=millis();
         if(flagL == 2) { flagL = 0; } 
    else if(flagL == 4) { flagL = 0; }
    else if(flagL == 5) { DispPage++; flagL = 0; lDispUpd(); }
    else if(flagL == 6) { DispPage--; flagL = 0; lDispUpd(); }
  }
  else if(millis()-eventL > 10 ) {
         if(key(wkl,key1)) { flagL = 2; } //next
    else if(key(wkl,key2)) { flagL = 4; } //prev 
    else if(key(wkl,key3)) { flagL = 5; } //nav
    else if(key(wkl,key4)) { flagL = 6; } //bk
  }
}

void wkr(void){ ///// Steering wheel right block /////
 uint16_t wkr = analogRead(wkR_pin);
  if(wkr>=1000) { eventR=millis();
         if(flagR == 1) { btCnt(btuppin, 100,0); } 
    else if(flagR == 2) { btCnt(btdnpin, 100,0); } 
    if(millis()-btKeyTime > btKeyDelay) {flagR = 0; pinMode(btuppin, INPUT); pinMode(btdnpin, INPUT);} 
  } 
  else if(millis()-eventR > 10){
         if(key(wkr,key1)) { btCnt(btuppin, 950,3); }
    else if(key(wkr,key4)) { btCnt(btdnpin, 950,3); }
    else if(key(wkr,key2) && !flagR) { flagR = 1; } 
    else if(key(wkr,key3) && !flagR) { flagR = 2; } 
  }   
}

bool key(uint16_t Val,uint16_t keyVal){
  if(Val>(keyVal-avg)&& Val<(keyVal+avg)) { return 1;} else {return 0;} 
}


void btCnt(uint8_t pin, uint32_t delay,uint8_t flag) {
  pinMode(pin, OUTPUT); 
  digitalWrite(pin,LOW); 
  if(!flagR) { btKeyTime = millis();} 
  flagR = flag;  
  btKeyDelay = delay;
}

void SetupButtons() {
  butt1.setDebounce(20);         // настройка антидребезга (по умолчанию 80 мс)
  butt1.setTimeout(1000);        // настройка таймаута на удержание (по умолчанию 500 мс)
  butt1.setClickTimeout(600);    // настройка таймаута между кликами (по умолчанию 300 мс)
  butt1.setType(HIGH_PULL);
  butt1.setDirection(NORM_OPEN);
  pinMode(53, INPUT_PULLUP);
 // pinMode(btuppin, OUTPUT);
 // pinMode(btdnpin, OUTPUT);

}
