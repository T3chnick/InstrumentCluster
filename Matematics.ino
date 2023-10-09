void tahometr(void) {  //измеряем частоту на входе тахометра по прерыванию
  if (!tt) { micros_th = micros(); } 
  else { th = (30000000 / (micros() - micros_th)); }
  tt = !tt;
  tz = millis();
}

void speedometr() {  //измеряем частоту на входе спидометра по прерыванию
  if (!st) { micros_sp = micros(); } 
  else { sp = (150000.0 / (micros() - micros_sp)); SaveSp(); }
  st = !st;
  sz = millis();
  odometrPulses++;
}

void SaveSp() {
  saveSpeedPos++;
  if (saveSpeedPos > 10) { saveSpeedPos = 0; }
  SpAvg[saveSpeedPos] = sp;
}

float Speed() {
  float speed;
  for (uint8_t i = 0; i < 10; i++) { speed += SpAvg[i]; }
  return (speed / 10);
}

uint8_t getXtrip() {
  uint8_t xpos;  //1.0 = 50 // 10.0 = 46 // 100 = 42 // 1000 = 38 //
  if (trip < 10.0) {
    xpos = 51;
  } else if (trip < 100.0) {
    xpos = 46;
  } else if (trip < 1000.0) {
    xpos = 42;
  } else {
    xpos = 38;
  }
  return (xpos);
}

uint8_t getXsp(float data) {
  uint8_t xpos;
  if (data < 9.50) {
    xpos = 48;
  } else if (data < 19.50) {
    xpos = 27;
  } else if (data < 99.50) {
    xpos = 34;
  } else if (data < 199.50) {
    xpos = 13;
  } else {
    xpos = 19;
  }
  return (xpos);
}

void ResSpThCount() {
  if (millis() - tz > 60) { th = 0; }
  if (millis() - sz > 60) {
    sp = 0;
    for (int i = 0; i < 10; i++) { SpAvg[i] = 0; }
  }
}

void UpdKM() {
  odometr = odometrPulses / 24000;
  trip = (odometrPulses - tripreset) / 24000.0;
  afStart = (odometrPulses - afStartReset) / 24000.0;
  ServiceA = (ServiceAinterval - (odometr - serviceAreset));
  ServiceB = (ServiceBinterval - (odometr - serviceBreset));
  if( millis() - driveTcount < 2000  && th > 0 ) {
    uint32_t count = millis() - driveTcount;
    tripTime += count;
    afStartTime += count;
  }
  driveTcount = millis();
}

void SetInterrupts() {
  attachInterrupt(51, tahometr, RISING);
  attachInterrupt(52, speedometr, RISING);
}