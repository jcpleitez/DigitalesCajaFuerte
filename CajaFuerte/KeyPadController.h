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
    String keyPadPin = "1234";
    String tempPin = "\0\0\0\0";
  public:

    void keyPadLoop() {
      char key = keypad.getKey();

      if (isdigit(key)) {
        if (tempPin.length() < 4) {
          tempPin += key;
        }
      } else if (key == '*') {
        resetPin();
      }

    }

    boolean validPin() {
      return keyPadPin == tempPin;
    }

    void resetPin() {
      tempPin = "\0\0\0\0";
    }

    String getTempPin(){
      return tempPin;
    }

};
