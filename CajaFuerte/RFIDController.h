#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

class RFIDController {
  private:
    byte tempCard[4] = {0x00, 0x00, 0x00, 0x00};
    byte rootCard[4] = {0x00, 0x00, 0x00, 0x00};
    byte currentCard[4] = {0x00, 0x00, 0x00, 0x01};
  public:
    RFIDController() {
    }

    void begin() {
      SPI.begin();           // MFRC522 Hardware uses SPI protocol
      rfid.PCD_Init();    // Initialize MFRC522 Hardware
      //If you set Antenna Gain to Max it will increase reading distance
      //rfid.PCD_SetAntennaGain(rfid.RxGain_max);

      loadRootCard();
    }

    void setCurrentUser(int cU) {
      int end = (cU * 9);
      int start = end - 9;
      int iteration = 0;
      Serial.print("userKey=");
      for ( int j = start; j < end; j++ ) {
        if (iteration == 0) {
        } else if (iteration <= 4) {
        } else if (iteration <= 8) {
          currentCard[iteration - 5] = EEPROM.read(j);
          Serial.print(currentCard[iteration - 5], HEX);
        }
        iteration++;
      }
      Serial.println();
    }

    void loadRootCard() {
      int end = (1 * 9);
      int start = end - 9;
      int iteration = 0;
      for ( int j = start; j < end; j++ ) {
        if (iteration == 0) {
        } else if (iteration <= 4) {
        } else if (iteration <= 8) {
          rootCard[iteration - 5] = EEPROM.read(j);
        }
        iteration++;
      }
      Serial.print("rootCard=");
      for (int i = 0; i < 4; i++) {
        Serial.print(rootCard[i], HEX);
      }
      Serial.println();
    }

    boolean validCard() {
      for (uint8_t k = 0; k < 4; k++) {
        if ( currentCard[k] != tempCard[k] ) {
          return false;
        }
      }
      return true;
    }

    boolean isRootCard() {
      for (uint8_t k = 0; k < 4; k++) {
        if ( rootCard[k] != tempCard[k] ) {
          return false;
        }
      }
      return true;
    }

    byte getTempCard(uint8_t index) {
      return tempCard[index];
    }

    uint8_t getID() {
      if ( ! rfid.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
        return 0;
      }
      if ( ! rfid.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
        return 0;
      }

      for ( uint8_t i = 0; i < 4; i++) {  //
        tempCard[i] = rfid.uid.uidByte[i];
      }
      lcdController.atachNotifi("Card....Leyendo", 2);
      rfid.PICC_HaltA(); // Stop reading
      return 1;
    }

    void resetCard() {
      for ( uint8_t i = 0; i < 4; i++) {  //
        tempCard[i] = 0x00;
      }
    }

    void RIFDLoop() {
      getID();
    }


};
