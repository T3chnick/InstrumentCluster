void tahometr(void){                                    //измеряем частоту на входе тахометра по прерыванию
 if(!tt){micros_th = micros();}
 else   {th = (30000000/(micros() - micros_th));}
 tt = !tt;
 tz = millis();
 SaveTaho();
}
 void SaveTaho(){
  saveTahoPos ++; if(saveTahoPos = 21) {saveTahoPos = 0;}
  ThAvg[saveSpeedPos] = th;
}
uint16_t Taho(){
  uint16_t taho = ThAvg[0];
 for(uint8_t i = 1; i < 20; i++) { taho+= ThAvg[i]; }
 return(taho/20);
}

void speedometr(){                               //измеряем частоту на входе спидометра по прерыванию
  if(!st){micros_sp = micros();}
  else   {sp = (150000.0/(micros() - micros_sp));}
  st = !st;
  sz = millis();
  odometrPulses ++;
  SaveSpeed();
}
void SaveSpeed(){
  saveSpeedPos ++; if(saveSpeedPos = 21) {saveSpeedPos = 0;}
  SpAvg[saveSpeedPos] = sp;
}
float Speed(){
  float speed = SpAvg[0];
 for(uint8_t i = 1; i < 20; i++) { speed+= SpAvg[i]; }
 return(speed/20);
}

uint8_t getXtrip(){
  uint8_t xpos; //1.0 = 50 // 10.0 = 46 // 100 = 42 // 1000 = 38 //
  if(trip < 10.0) {xpos=50;} 
  else if(trip < 100.0) {xpos=46;} 
  else if(trip < 1000.0) {xpos=42;} 
  else {xpos=38;}
  return(xpos);
}

uint8_t getXsp(){
  uint8_t xpos;
  if(Speed() < 10) {xpos=52;}
  else if(Speed() < 20) {xpos=35;}  
  else if(Speed() < 100) {xpos=42;} 
  else {xpos=23;}
  return(xpos);
}

void ResSpThCount() {
  if(millis() - tz > 60) { th = 0; }
  if(millis() - sz > 60) { sp = 0; };
}

void UpdKM() {
    odometr = odometrPulses/24000;
    trip = (odometrPulses-tripreset)/24000; 
    //if(odometr - serviceAreset !> )
    ServiceA = (ServiceAinterval - (odometr - serviceAreset));
    ServiceB = (ServiceBinterval - (odometr - serviceBreset));

}

void SetInterrupts() {
  attachInterrupt(51, tahometr,   RISING);
  attachInterrupt(52, speedometr, RISING);
}