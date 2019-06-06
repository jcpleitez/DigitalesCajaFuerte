#include "global.h"

void setup() {
  Serial.begin(9600);
  solenoid.begin();
  rfidContol.begin();
  masterKey.begin();
}

void loop() {

  boolean validPin = keypadControl.validPin();
  boolean validCard = rfidContol.validCard();
  boolean validMasterKey = masterKey.status();
  
  if(validPin && validCard){
    rfidContol.resetCard();    
    keypadControl.resetPin();
    solenoid.active(SOLENOIDTIMEOUT);
  }else if(validMasterKey){
    solenoid.active(SOLENOIDTIMEOUT);
  }

  rfidContol.RIFDLoop();
  keypadControl.keyPadLoop();
  solenoid.solenoidLoop();
  masterKey.MKLoop();

}
