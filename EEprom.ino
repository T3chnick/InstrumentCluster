void ReadEEprom() {
  eeprom.eeprom_read(0, &odometrPulses);
  eeprom.eeprom_read(10, &tripreset);
  eeprom.eeprom_read(20, &serviceAreset);
  eeprom.eeprom_read(30, &serviceBreset);
  eeprom.eeprom_read(40, &CC_Kp);
  eeprom.eeprom_read(44, &CC_Ki);
  eeprom.eeprom_read(48, &CC_Kd);
}

void SaveKm() {
  eeprom.eeprom_write(0, odometrPulses);
  eeprom.eeprom_write(10, tripreset);
  eeprom.eeprom_write(20, serviceAreset);
  eeprom.eeprom_write(30, serviceBreset);
}

void saveCCpid() {
  CC_Kp = constrain(CC_Kp, 0.0, 30.0);
  eeprom.eeprom_write(40, CC_Kp);
  CC_Ki = constrain(CC_Ki, 0.0, 30.0);
  eeprom.eeprom_write(44, CC_Ki);
  CC_Kd = constrain(CC_Kd, 0.0, 30.0);
  eeprom.eeprom_write(48, CC_Kd);
}