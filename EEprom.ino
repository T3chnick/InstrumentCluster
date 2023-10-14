void ReadEEprom() {
  eeprom.eeprom_read(0, &Odometr_Pulses);
  eeprom.eeprom_read(10, &Trip_KM_Reset);
  eeprom.eeprom_read(20, &service_A_reset);
  eeprom.eeprom_read(30, &service_B_reset);
  eeprom.eeprom_read(40, &Trip_KM_Time);

  eeprom.eeprom_read(50, &CC_Kp);
  eeprom.eeprom_read(54, &CC_Ki);
  eeprom.eeprom_read(58, &CC_Kd);

  eeprom.eeprom_read(62, &Service_A_interval);
  eeprom.eeprom_read(66, &Service_B_interval);

  eeprom.eeprom_read(70, &service_A_time);
  eeprom.eeprom_read(78, &TH_Pulses);
  eeprom.eeprom_read(86, &af_Reset_Inj_Milis);
  eeprom.eeprom_read(90, &Inj_Flow);
  eeprom.eeprom_read(92, &avg);
  eeprom.eeprom_read(93, &Engine_ST);
  }

void SaveKm() {
  eeprom.eeprom_write(0, Odometr_Pulses);
  eeprom.eeprom_write(10, Trip_KM_Reset);
  eeprom.eeprom_write(20, service_A_reset);
  eeprom.eeprom_write(30, service_B_reset);
  eeprom.eeprom_write(40, Trip_KM_Time);
  eeprom.eeprom_write(70, service_A_time);
  eeprom.eeprom_write(78, TH_Pulses);
  eeprom.eeprom_write(86, af_Reset_Inj_Milis);
  }

void SaveIntervals() {
  Service_A_interval = constrain(Service_A_interval, 0, 40000);
  Service_B_interval = constrain(Service_B_interval, 0, 40000);
  eeprom.eeprom_write(62, Service_A_interval);
  eeprom.eeprom_write(66, Service_B_interval);
  Inj_Flow =  constrain(Inj_Flow, 0, 600);
  eeprom.eeprom_write(90, Inj_Flow);
  }

void Save_Settings() {
  CC_Kp = constrain(CC_Kp, 0.0, 30.0);
  eeprom.eeprom_write(50, CC_Kp);
  CC_Ki = constrain(CC_Ki, 0.0, 9.9);
  eeprom.eeprom_write(54, CC_Ki);
  CC_Kd = constrain(CC_Kd, 0.0, 9.9);
  eeprom.eeprom_write(58, CC_Kd);
  avg = constrain(avg,10,30);
  eeprom.eeprom_write(92, avg);
  }