void RegistrarPersona() {
  String pinPersona = "";
  //Capturar su Pin
  keypadControl.resetPin();
  while (keypadControl.getKey() != 'C') {
    keypadControl.keyPadLoop();
    if (millis() % 1000 == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2-AgregarPersona");
      lcd.setCursor(0, 1);
      if (keypadControl.getTempPin().length() > 0) {
        lcd.print(keypadControl.getTempPin());
      } else {
        lcd.print("Ingrese Pin");
      }
    }

    if (keypadControl.getTempPin().length() == 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2-AgregarPersona");
      lcd.setCursor(0, 1);
      lcd.print("...OK");
      delay(500);
      break;
    }
  }
  pinPersona = keypadControl.getTempPin();
  keypadControl.resetPin();
  //Capturar su Tarjeta
  byte personaCard[4] = {0x00, 0x00, 0x00, 0x00};
  while (rfidContol.getID() != 1) {
    if (keypad.getKey() == 'C') {
      return false;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("2-AgregarPersona");
    lcd.setCursor(0, 1);
    lcd.print("PonerTarjeta");
    delay(500);
  }
  for (uint8_t i = 0; i < 4; i++) {
    personaCard[i] = rfidContol.getTempCard(i);
  }
  rfidContol.resetCard();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("2-AgregarPersona");
  lcd.setCursor(0, 1);
  lcd.print("...OK");
  delay(500);
  //Capturar Huella
  int id = -1;
  int fingerCounter = EEPROM.read(0);
  while (id == -1) {
    id = fingerController.getFingerprintEnroll(fingerCounter);
  }
  if (id == -1) {
    return;
  }
  fingerCounter++;
  Serial.print("fingerCounter=");
  Serial.print(fingerCounter);
  Serial.println();
  EEPROM.write(0, fingerCounter);

  savePersona(fingerCounter, personaCard, pinPersona, id);



}

void savePersona(int counterEEPROM, byte rfidKey[], String pin, int idHuella) {
  //uint8_t end = counterEEPROM * 6;
  //uint8_t start = end - 6;

  //for ( uint8_t j = start; j <= end; j++ ) {   // Loop 4 times
    //EEPROM.write( start + j, a[j] );  // Write the array values to EEPROM in the right position
  //}
}
