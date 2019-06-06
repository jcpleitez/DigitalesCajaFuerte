#include "global.h"

void setup() {
  Serial.begin(9600);
  solenoid.begin();  
  masterKey.begin();
  rfidContol.begin();
  lcdController.begin();
  fingerController.begin();
}

void loop() {
 
  boolean validPin = keypadControl.validPin();
  boolean validCard = rfidContol.validCard();
  boolean validFinger = fingerController.validFinger();
  boolean validMasterKey = masterKey.status();

  lcdController.show(keypadControl.getTempPin());

   
  if(validPin && validCard && validFinger){
    lcdController.atachNotifi("Abriendo Caja", 2);
    rfidContol.resetCard();    
    keypadControl.resetPin();
    fingerController.resetTemFinger();
    solenoid.active(SOLENOIDTIMEOUT);
  }else if(validMasterKey){
    solenoid.active(SOLENOIDTIMEOUT);
  }

  rfidContol.RIFDLoop();
  keypadControl.keyPadLoop();  
  masterKey.MKLoop();
  fingerController.FingerLoop();
  solenoid.solenoidLoop();
  lcdController.LCDLoop();

}
