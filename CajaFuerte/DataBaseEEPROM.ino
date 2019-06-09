void savePersona(int counterEEPROM, byte rfidKey[], String pin) {
  uint8_t end = (counterEEPROM + 2) * 9;
  uint8_t start = end - 8;
  uint8_t iteration = 0;
  for ( uint8_t j = start; j <= end; j++ ) {
    if (iteration == 0) {      
      EEPROM.write( start + j, counterEEPROM );
      Serial.print(counterEEPROM);
    } else if (iteration <= 4) {
      EEPROM.write( start + j, pin.charAt(iteration - 1));
      Serial.print(pin.charAt(iteration - 1));
    } else if (iteration <= 8) {
      EEPROM.write( start + j, rfidKey[iteration - 5] );
      Serial.print(rfidKey[iteration - 5],HEX);
    }
    iteration++;
  }
  Serial.println();
  counterEEPROM++;
  EEPROM.write(0, counterEEPROM);
}
