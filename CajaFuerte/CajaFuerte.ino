#include "global.h"

void setup() {
  Serial.begin(9600);
  solenoid.begin();
  masterKey.begin();
  rfidContol.begin();
  keypadControl.begin();
  lcdController.begin();
  fingerController.begin();
}

void loop() {

  int idUsuario = mainSelectID("  Caja Fuerte", "Ingrese su ID");
  fingerController.setCurrentUser(idUsuario);
  keypadControl.setCurrentUser(idUsuario);
  rfidContol.setCurrentUser(idUsuario);

  boolean validMasterKey = masterKey.status();

  while (idUsuario != -1) {

    boolean stop = false;

    boolean validPin = keypadControl.validPin();
    boolean validCard = rfidContol.validCard();
    boolean validFinger = fingerController.validFinger();    

    if (keypadControl.getKey() == 'C') {
      stop = true;
    }

    Serial.print("validPin=");
    Serial.print(validPin);
    Serial.print(" validCard=");
    Serial.print(validCard);
    Serial.print(" validFinger=");
    Serial.print(validFinger);
    Serial.println();


    lcdController.show(keypadControl.getTempPin());

    if (validPin && validCard && validFinger) {
      rfidContol.resetCard();
      keypadControl.resetPin();
      fingerController.resetTemFinger();
      solenoid.active(SOLENOIDTIMEOUT);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Caja Fuerte");
      lcd.setCursor(0, 1);
      lcd.print("Abriendo Caja");
      stop = true;
    } else if (validMasterKey) {
      stop = true;
      solenoid.active(SOLENOIDTIMEOUT);
    }

    rfidContol.RIFDLoop();
    keypadControl.keyPadLoop();    
    fingerController.FingerLoop();
    solenoid.solenoidLoop();
    lcdController.LCDLoop("  Caja Fuerte");

    if (stop) {
      RootClean();
      delay(2000);
      break;
    }

  }
  masterKey.MKLoop();
  solenoid.solenoidLoop();

}
