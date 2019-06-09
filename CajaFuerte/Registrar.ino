void RegistrarPersona() {
  //Definir su ID
  int position = SeleccionarID("2-AgregarPersona", "Defina su ID");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("2-AgregarPersona");
  lcd.setCursor(0, 1);
  lcd.print("...OK");
  delay(500);

  //Capturar su Pin
  String pinPersona = "";
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
  int fingerId = -1;
  while (fingerId == -1) {
    fingerId = fingerController.getFingerprintEnroll(position);
  }
  if (fingerId == -1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("2-AgregarPersona");
    lcd.setCursor(0, 1);
    lcd.print("Error Registrando");
    delay(2000);
    return;
  }
  
  savePersona(position, personaCard, pinPersona);

}

int SeleccionarID(String m1, String m2) {
  int select = -1;
  while (select == -1) {
    char c = keypad.getKey();
    if (c == 'C') {
      return -1;
    } else if (isdigit(c)) {
      String cadena = "";
      cadena += c;
      return cadena.toInt();
    }

    if (millis() % 1000 == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(m1);
      lcd.setCursor(0, 1);
      lcd.print(m2);
    }
  }
}
