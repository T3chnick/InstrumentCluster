 void tahometr(void){                                    //измеряем частоту на входе тахометра по прерыванию
 if(!tt){micros_th = micros();}
 else   {th = (30000000/(micros() - micros_th));}
 tt = !tt;
 tz = millis();
 }

void speedometr(){                               //измеряем частоту на входе спидометра по прерыванию
  if(!st){micros_sp = micros();}
  else   {sp = (150000/(micros() - micros_sp));}
  st = !st;
  sz = millis();
  odometrPulses ++;
}

void ResSpThCount() {
  if(millis() - tz > 60) { th = 0; }
  if(millis() - sz > 60) { sp = 0; };
}

void SetInterrupts() {
  attachInterrupt(51, tahometr,   RISING);
  attachInterrupt(52, speedometr, RISING);
}