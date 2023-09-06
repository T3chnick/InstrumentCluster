void ReadEEprom(){
  eeprom.eeprom_read(0,&odometrPulses);
  eeprom.eeprom_read(10,&tripreset);
}