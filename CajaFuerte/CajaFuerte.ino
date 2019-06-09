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

  Serial.print("validPin=");
  Serial.print(validPin);
  Serial.print(" validCard=");
  Serial.print(validCard);
  Serial.print(" validFinger=");
  Serial.print(validFinger);
  Serial.println();
  

  lcdController.show(keypadControl.getTempPin());  
   
  if(validPin && validCard && validFinger){
    rfidContol.resetCard();    
    keypadControl.resetPin();
    fingerController.resetTemFinger();
    solenoid.active(SOLENOIDTIMEOUT);
    lcdController.atachNotifi("Abriendo Caja", 3);
  }else if(validMasterKey){
    solenoid.active(SOLENOIDTIMEOUT);
  }

  rfidContol.RIFDLoop();
  keypadControl.keyPadLoop();  
  masterKey.MKLoop();
  fingerController.FingerLoop();
  solenoid.solenoidLoop();
  lcdController.LCDLoop("  Caja Fuerte");

}
