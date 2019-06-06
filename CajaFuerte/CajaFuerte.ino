#include "global.h"

void setup() {
  Serial.begin(9600);
  solenoid.begin();
  rfidContol.begin();
  masterKey.begin();
  fingerController.begin();
}

void loop() {

  boolean validPin = keypadControl.validPin();
  boolean validCard = rfidContol.validCard();
  boolean validFinger = fingerController.validFinger();
  boolean validMasterKey = masterKey.status();
  
  if(validPin && validCard && validFinger){
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

}
