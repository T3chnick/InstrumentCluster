void tahometr(void) {  //измеряем частоту на входе тахометра по прерыванию
  if (!tt) { micros_th = micros(); } 
  else { th = (30000000 / (micros() - micros_th)); }
  tt = !tt;
  tz = millis();
  TH_Pulses ++;
  }

void speedometr() {    //измеряем частоту на входе спидометра по прерыванию
  if (!st) { micros_sp = micros(); } 
  else { sp = (150000.0 / (micros() - micros_sp)); SaveSp(); }
  st = !st;
  sz = millis();
  Odometr_Pulses++;
  }

void injON(){
  microsInj = micros();
  }

void injOFF(){
  injTime = (((micros() - microsInj) - 2000.0)/1000.0)*4;
  if(injTime < 35) {af_Reset_Inj_Milis += injTime; af_Start_KM_Inj_Milis += injTime; }
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

uint8_t getXTrip_KM() {
  uint8_t xpos;  //1.0 = 50 // 10.0 = 46 // 100 = 42 // 1000 = 38 //
  if (Trip_KM < 10.0) {
    xpos = 50;
  } 
  else if (Trip_KM < 20.0) {
    xpos = 43;
  } 
  else if (Trip_KM < 100.0) {
    xpos = 46;
  } 
  else if (Trip_KM < 200.0) {
    xpos = 39;
  }  
  else if (Trip_KM < 1000.0) {
    xpos = 42;
  } 
  else if (Trip_KM < 2000.0) {
    xpos = 34;
  } 
  else {
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
  odometr = Odometr_Pulses / 24000;
  Trip_KM = (Odometr_Pulses - Trip_KM_Reset) / 24000.0;
  af_Start_KM = (Odometr_Pulses - af_Start_KM_Reset) / 24000.0;
  Service_A_KM = (Service_A_interval - (odometr - service_A_reset));
  Service_B_KM = (Service_B_interval - (odometr - service_B_reset));
  if( millis() - driveTcount < 2000 && th > 0 ) {
    uint32_t count = millis() - driveTcount;
    Trip_KM_Time += count;
    af_Start_KM_Time += count;
    service_A_time += count;
  }
  driveTcount = millis();
  }

void SetInterrupts() {
  attachInterrupt(51, tahometr, RISING);
  attachInterrupt(52, speedometr, RISING);
  attachInterrupt(9, injON, FALLING);
  attachInterrupt(9, injOFF, RISING);
  }