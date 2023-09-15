const unsigned char cruise [] PROGMEM = {
	// 'cruise, 36x42px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x03, 
	0xe0, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xf0, 
	0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfc, 
	0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x7e, 0x67, 0xe0, 0x00, 0x01, 0xf0, 0x60, 0xf8, 
	0x00, 0x03, 0xc0, 0x60, 0x3c, 0x00, 0x07, 0x00, 0x60, 0x0e, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 
	0x1f, 0x80, 0x00, 0x1f, 0x80, 0x19, 0xc6, 0x00, 0x3d, 0x80, 0x39, 0x87, 0x00, 0x19, 0xc0, 0x30, 
	0x03, 0x00, 0x00, 0xc0, 0x60, 0x03, 0x00, 0x00, 0x60, 0x60, 0x01, 0x80, 0x00, 0x60, 0x60, 0x01, 
	0x80, 0x00, 0x70, 0xc0, 0x01, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0xe0, 
	0x00, 0x30, 0xe8, 0x00, 0xf0, 0x01, 0x70, 0xfc, 0x00, 0xf0, 0x01, 0xf0, 0xf8, 0x00, 0xf0, 0x01, 
	0xf0, 0xc0, 0x00, 0x60, 0x00, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x30, 0xe0, 0x00, 0x00, 0x00, 0x70, 
	0x60, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x60, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x30, 
	0x00, 0x00, 0x00, 0xc0, 0x39, 0x80, 0x00, 0x19, 0xc0, 0x1d, 0xc0, 0x00, 0x3b, 0x80, 0x0f, 0x80, 
	0x00, 0x1f, 0x00, 0x07, 0x00, 0x00, 0x0e, 0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00
};

void UpdDisplays() { if(!DisplayST) {initDisplays();}
  if (millis()-lDispTimer > 50) { lDispUpd(); lDispTimer=millis(); }
  if (millis()-rDispTimer > 500) { rDispUpd(); rDispTimer=millis(); }
  if (millis()-cDispTimer > 100) { cDispUpd(); cDispTimer=millis(); }

}
void cDispUpd(){ DispPage = constrain(DispPage,0,7);
  display.clearDisplay();
  if (DispSubPage > SubPageMax) { DispSubPage = 0; } else if (DispSubPage < 0)  { DispSubPage = SubPageMax; }
  
  switch(DispPage) { 

    case 0: { SubPageMax = 3; switch(DispSubPage) { 

        case 0: { // odometr
        PrintMsgF(56,31,"km");        
        display.setFont(&Seven_Segment9pt7b);
        display.setCursor(getXtrip(),25); display.print(trip,1);
        display.setCursor(35,56); display.print(odometr);
        if (butt1.isHold()) { tripreset = odometrPulses; SaveKm(); }
        }break;
      
        case 1: {  // speed
        PrintMsgF(47,11,"SPEED");
        display.setFont(&digits18pt7b); display.setCursor(getXsp(),55); display.print(Speed(),0); 
        } break;

        case 2: { //Service A
        PrintMsgF(37,11,"SERVICE A");
        display.setFont(&Seven_Segment9pt7b); display.setCursor(46,40); display.print(ServiceA);
        PrintMsgF(17,51,"hold R to reset");
        if (butt1.isHold()) { serviceAreset = odometr; SaveKm(); }
        } break;

        case 3: { // ServiceB
        PrintMsgF(37,11,"SERVICE B");
        display.setFont(&Seven_Segment9pt7b); display.setCursor(43,40); display.print(ServiceB);
        PrintMsgF(17,51,"hold R to reset");
        if (butt1.isHold()) { serviceBreset = odometr; SaveKm(); }
        } break;


      }
    
    }break;

    case 1:{} break;

    case 2:{} break;

  }

  display.display();
}//SP//100=32// 10=42// 1=52

void lDispUpd(){ 
  dl.clearDisplay();
  dl.setFont(); dl.setCursor(110,13); dl.print("th");
  dl.setFont(&FreeSans18pt7b); dl.setCursor(0,42); dl.print(Taho()); 
    dl.display(); 
}

void rDispUpd(){
  DateTime now = myRTC.now();
  dr.clearDisplay();
  if(now.hour() < 10) { dr.setCursor(6,44); dr.println("0"); dr.setCursor(32,44); dr.print(now.hour()); }
    else { dr.setCursor(6,44); dr.print(now.hour()); }
  if(now.minute() < 10) { dr.setCursor(70,44); dr.println("0"); dr.setCursor(96,44); dr.print(now.minute()); }
    else { dr.setCursor(70,44); dr.print(now.minute()); }
  if(clock2dot == 0) { dr.fillRect(62, 19, 4,6,WHITE); dr.fillRect(62, 34, 4,6,WHITE); } 
  dr.display();
    clock2dot = !clock2dot;
}

void initDisplays() {
  display.begin(SH1106_SWITCHCAPVCC);  display.clearDisplay(); display.setTextColor(WHITE);  display.display(); cDispUpd(); 
  dl.begin(SH1106_SWITCHCAPVCC, 0x3C); dl.clearDisplay(); dl.display(); dl.setTextColor(WHITE); dl.setFont(&FreeSans24pt7b); lDispUpd();
  dr.begin(SH1106_SWITCHCAPVCC, 0x3D); dr.clearDisplay(); dr.display(); dr.setTextColor(WHITE); dr.setFont(&FreeSans24pt7b); rDispUpd(); 
  
  DisplayST=1;
}

void DisplaysOFF() {
  
  dl.clearDisplay(); dl.display(); 
  dr.clearDisplay(); dr.display(); 
  display.clearDisplay(); display.display();
  eeprom.eeprom_write(0, odometrPulses);
  DisplayST=0;
}

void PrintMsgF(uint8_t x, uint8_t y, const char *msg){
      display.setFont();
      display.setCursor(x,y);
      display.print(msg);
}


void settime() {
   //setRTC.setClockMode(false);  // set to 24h
   //setClockMode(true); // set to 12h
   //setRTC.setYear(year);
   //setRTC.setMonth(month);
   //setRTC.setDate(date);
   //setRTC.setDoW(dOW);
   //setRTC.setHour(20);
   //setRTC.setMinute(35);
   //setRTC.setSecond(second);
}

