void CruiseControl(){
  uint8_t CCkey = analogRead(CCkeyPin);
  bool Brake = digitalRead(BrakePin);
  bool Clutch = digitalRead(ClutchPin);

  switch (CCstatus) {

    case 1: //CC off 
      CCservo.write(0); CCTargetSp=0; PreviousSpeed=0;
      break;

    case 2: //CC standby       
      if (key(CCkey,reset)) {CCstatus=3; break;}
      else if(!Brake && !Clutch) { if( key(CCkey,accel) || key(CCkey,decel)) {CCTargetSp=sp; CCstatus=3;} break;}
      CCservo.write(0);
      break;

    case 3: //CC on
      if(Brake || Clutch) { CCstatus=1; CCservo.write(0); break; }
      
      break;

  }
}

void ComputeCC(){

  float CurrSpeed = Speed();

  if(CurrSpeed < CCTargetSp){
         if(CurrSpeed < (CCTargetSp - diff_H)) { throttle += react_H; }
    else if(CurrSpeed < (CCTargetSp - diff_M)) { throttle += react_M; }
    else if(CurrSpeed < (CCTargetSp - diff_L)) { throttle += react_L; }
    else { }
  }
  else if(CurrSpeed > CCTargetSp){
         if(CurrSpeed > (CCTargetSp + diff_H)) { throttle -= react_H; }
    else if(CurrSpeed > (CCTargetSp + diff_M)) { throttle -= react_M; }
    else if(CurrSpeed > (CCTargetSp + diff_L)) { throttle -= react_L; }
    else { }
  }

  throttle = constrain(throttle, 0, 150);
  CCservo.write(throttle);


}