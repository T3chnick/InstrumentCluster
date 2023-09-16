void ReadEEprom(){
  eeprom.eeprom_read(0,&odometrPulses);
  eeprom.eeprom_read(10,&tripreset);
  eeprom.eeprom_read(20,&serviceAreset);
  eeprom.eeprom_read(30,&serviceBreset);
  eeprom.eeprom_read(40,&CC_Kp);
  eeprom.eeprom_read(44,&CC_Ki);
  eeprom.eeprom_read(48,&CC_Kd);
}

void SaveKm(){
  eeprom.eeprom_write(0, odometrPulses);
  eeprom.eeprom_write(10, tripreset);  
  eeprom.eeprom_write(20,serviceAreset);
  eeprom.eeprom_write(30,serviceBreset);
}

void saveCCpid(){
  eeprom.eeprom_write(40,CC_Kp);
  eeprom.eeprom_write(44,CC_Ki);
  eeprom.eeprom_write(48,CC_Kd);
}