void ReadEEprom(){
  eeprom.eeprom_read(0,&odometrPulses);
  eeprom.eeprom_read(10,&tripreset);
  eeprom.eeprom_read(20,&serviceAreset);
  eeprom.eeprom_read(30,&serviceBreset);
}

void SaveKm(){
  eeprom.eeprom_write(0, odometrPulses);
  eeprom.eeprom_write(10, tripreset);  
  eeprom.eeprom_write(20,serviceAreset);
  eeprom.eeprom_write(30,serviceBreset);
}