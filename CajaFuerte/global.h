#include <SPI.h>
#include "RFIDController.h"
RFIDController rfidContol;

#include "KeyPadController.h"
KeyPadController keypadControl;

#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#include "Solenoid.h"
#define pinSolenoid A2
Solenoid solenoid(pinSolenoid);

#include "LlaveMaestra.h"
#define pinMKey 1
MasterKey masterKey(pinMKey);
