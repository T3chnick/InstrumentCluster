void CruiseControl(){
  uint8_t CCkey = analogRead(CCkeyPin);
  bool Brake = digitalRead(BrakePin);
  bool Clutch = digitalRead(ClutchPin);

  switch (CCstatus) {

    case 1: //CC off 
      CCservo.write(0); CCspeedSet=0; CClastSpeed=0;
      break;

    case 2: //CC standby       
      if (key(CCkey,reset)) {CCstatus=3; break;}
      else if(!Brake && !Clutch) { if( key(CCkey,accel) || key(CCkey,decel)) {CCspeedSet=sp; CCstatus=3;} break;}
      CCservo.write(0);
      break;

    case 3: //CC on
      if(Brake || Clutch) { CCstatus=3; CCservo.write(0); break; }
      
      break;

  }
}