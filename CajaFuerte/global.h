#include <EEPROM.h>

#include "LCDController.h"
LCDController lcdController;

#include <SPI.h>
#include "RFIDController.h"
RFIDController rfidContol;

#include "FingerPrintController.h"
FingerPrintController fingerController;

#include "KeyPadController.h"
KeyPadController keypadControl;

#include "Solenoid.h"
#define pinSolenoid A2
Solenoid solenoid(pinSolenoid);

#include "LlaveMaestra.h"
#define pinMKey 0
MasterKey masterKey(pinMKey);

boolean isRoot = false;
unsigned long suTimer = 0;

#define pinResetRoot A7

void(* resetFunc) (void) = 0;
