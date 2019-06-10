#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte rowPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

class KeyPadController {
  private:
    char key = '\0';
    String currentPin = "";
    String rootPin = "";
    String tempPin = "\0\0\0\0";
  public:

    void keyPadLoop() {
      key = keypad.getKey();

      if (isdigit(key)) {
        if (tempPin.length() < 4) {
          tempPin += key;
          if (currentPin == tempPin) {
            lcdController.atachNotifi("Pin....OK", 2);
          }
        }
      } else if (key == '*') {
        resetPin();
      }

    }

    void setCurrentUser(int cU) {
      currentPin = "";
      int end = (cU * 9);
      int start = end - 9;
      int iteration = 0;
      for ( int j = start; j < end; j++ ) {
        if (iteration == 0) {
        } else if (iteration <= 4) {
          currentPin += (char) EEPROM.read(j);
        } else if (iteration <= 8) {
        }
        iteration++;
      }
      Serial.println(currentPin);
    }

    void loadRootPin() {
      currentPin = "";
      int end = (1 * 9);
      int start = end - 9;
      int iteration = 0;
      for ( int j = start; j < end; j++ ) {
        if (iteration == 0) {
        } else if (iteration <= 4) {
          rootPin += (char) EEPROM.read(j);
        } else if (iteration <= 8) {
        }
        iteration++;
      }
      Serial.print("rootPin=");
      Serial.println(rootPin);
    }

    void begin(){
      loadRootPin();
    }

    boolean validPin() {
      return currentPin == tempPin;
    }

    boolean isRootPin() {
      return rootPin == tempPin;
    }

    void resetPin() {
      key = '\0';
      tempPin = "\0\0\0\0";
    }

    String getTempPin() {
      return tempPin;
    }

    char getKey() {
      return key;
    }

};
