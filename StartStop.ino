
void ControlStartStop(void) {
  bool Clutch = digitalRead(BrakePin);
  bool Door = !digitalRead(DoorPin);

  switch (Engine_ST) {

    case 0:  //acc and ign switch || start
      if (cLock) { StopAll(); break; }
      if (ssButt.isSingle()) { if (Clutch) { StartStarter();} else { StartACC();holdACC = 1; holdACCtime = millis(); Engine_ST = 4; }}
      if (ssButt.isHolded()) { StartIgn(); Engine_ST = 3; }
    break;
      //----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
    case 1:  // Starter work
      if (th > 400) { StopStarter(); StartACC(); Engine_ST = 2; }
      if (ssButt.isSingle() || millis() - StarterTime > 10000 || !Clutch) { StopStarter(); Engine_ST = 3; }
    break;
    //----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
    case 2:  // Engine work
      lastWork = millis();
      if (th < 20) { Engine_ST = 3; }
      if (ssButt.isSingle()) { StopIgn(); Engine_ST = 4; }
      if (ssButt.isHolded()) { StopAll(); }
    break;
    //----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
    case 3:  // Work fail or Cancel starter
      if (th > 300) { Engine_ST = 2; StartACC(); }
      if (ssButt.isSingle()) { (Clutch) ? StartStarter() : StopAll(); }
      if (ssButt.isHolded()) { StopAll(); }
      if (millis() - lastWork > 30000) { StopAll(); }
    break;
    //----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
    case 4:  //Engine off acc on
      if (ssButt.isSingle()) { (Clutch) ? StartStarter() : StopAll(); }
      if (ssButt.isHolded()) { StopAll(); }
      if (!holdACC) { if (Door || millis() - lastWork > (20 * (60 * 1000))) { StopAll(); }} 
      else if (millis() - holdACCtime > (30 * (60 * 1000)) ) { StopAll(); }
    break;
   }
  }

void SSButtLed() {
  }

void StartIgn(void) {
  digitalWrite(IgnPin, HIGH);
  lastWork = millis();
  stateIgn = 1;
  }

void StopIgn(void) {
  digitalWrite(IgnPin, LOW);
  stateIgn = 0;
  }

void StopAll(void) {
  digitalWrite(IgnPin, LOW);
  digitalWrite(StarterPin, LOW);
  digitalWrite(ACCPin, LOW);
  digitalWrite(Wled, LOW);
  digitalWrite(Gled, LOW);
  digitalWrite(Yled, LOW);
  stateACC = 0;
  holdACC = 0;
  stateIgn = 0;
  Engine_ST = 0;
  }

void StartStarter(void) {
  digitalWrite(ACCPin, LOW);
  stateACC = 0;
  StartIgn();
  Engine_ST = 1;
  if (th < 10) {
    digitalWrite(StarterPin, HIGH);
    StarterTime = millis();
  }
  }

void StopStarter(void) {
  digitalWrite(StarterPin, LOW);
  }

void StartACC(void) {
  digitalWrite(ACCPin, HIGH);
  stateACC = 1;
  }

void setupSSpins() {
  pinMode(SSButtPin, INPUT_PULLUP);
  pinMode(BrakePin, INPUT);
  pinMode(IgnPin, OUTPUT);
  pinMode(StarterPin, OUTPUT);
  pinMode(ACCPin, OUTPUT);
  pinMode(Wled, OUTPUT);
  pinMode(Yled, OUTPUT);
  pinMode(Gled, OUTPUT);
  }