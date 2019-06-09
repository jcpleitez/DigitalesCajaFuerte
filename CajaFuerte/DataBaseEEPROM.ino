void savePersona(int p, byte rfidKey[], String pin) {
  int end = (p * 9);
  int start = end - 9;
  int iteration = 0;
  String cadena = "";
  for ( int j = start; j < end; j++ ) {
    if (iteration == 0) {
      EEPROM.write( j, p );
    } else if (iteration <= 4) {
      EEPROM.write(j, pin.charAt(iteration - 1));
    } else if (iteration <= 8) {
      EEPROM.write( j, rfidKey[iteration - 5] );
    }
    iteration++;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Persona");
  lcd.setCursor(0, 1);
  lcd.print("Guardada");
  delay(2000);
}

void borrarPersona(int idPersona) {
  if (idPersona == -1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cancelando");
    lcd.setCursor(0, 1);
    lcd.print("Cerrando");
    delay(2000);
  } else if (idPersona == 1 || idPersona == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error:No se puede");
    lcd.setCursor(0, 1);
    lcd.print("Borrar Administrador");
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BorrandoPersona");
    lcd.setCursor(0, 1);
    lcd.print(idPersona);
    int end = idPersona * 9;
    int start = end - 9;
    for ( int j = start; j <= end; j++ ) {
      EEPROM.write( j, 0);
    }
    fingerController.deleteFingerprint(idPersona);
    delay(2000);
  }
}
