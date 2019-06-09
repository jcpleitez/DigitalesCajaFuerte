#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(A1, A0);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

class FingerPrintController {
  private:
    boolean active = false;
    int mainId = 1;
    int tempId = 0;
  public:
    FingerPrintController() {
    }

    void begin() {
      // set the data rate for the sensor serial port
      finger.begin(57600);

      if (finger.verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
      } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) {
          delay(1);
        }
      }
      finger.getTemplateCount();
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
    }

    uint8_t getFingerprintID() {
      uint8_t p = finger.getImage();
      switch (p) {
        case FINGERPRINT_OK:
          Serial.println("Image taken");
          break;
        case FINGERPRINT_NOFINGER:
          Serial.println("No finger detected");
          return p;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println("Communication error");
          return p;
        case FINGERPRINT_IMAGEFAIL:
          Serial.println("Imaging error");
          return p;
        default:
          Serial.println("Unknown error");
          return p;
      }

      // OK success!

      p = finger.image2Tz();
      switch (p) {
        case FINGERPRINT_OK:
          Serial.println("Image converted");
          break;
        case FINGERPRINT_IMAGEMESS:
          Serial.println("Image too messy");
          return p;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println("Communication error");
          return p;
        case FINGERPRINT_FEATUREFAIL:
          Serial.println("Could not find fingerprint features");
          return p;
        case FINGERPRINT_INVALIDIMAGE:
          Serial.println("Could not find fingerprint features");
          return p;
        default:
          Serial.println("Unknown error");
          return p;
      }

      // OK converted!
      p = finger.fingerFastSearch();
      if (p == FINGERPRINT_OK) {
        Serial.println("Found a print match!");
      } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println("Communication error");
        return p;
      } else if (p == FINGERPRINT_NOTFOUND) {
        Serial.println("Did not find a match");
        return p;
      } else {
        Serial.println("Unknown error");
        return p;
      }

      // found a match!
      Serial.print("Found ID #"); Serial.print(finger.fingerID);
      Serial.print(" with confidence of "); Serial.println(finger.confidence);

      return finger.fingerID;
    }

    // returns -1 if failed, otherwise returns ID #
    int getFingerprintIDez() {
      uint8_t p = finger.getImage();
      if (p != FINGERPRINT_OK)  return -1;

      p = finger.image2Tz();
      if (p != FINGERPRINT_OK)  return -1;

      p = finger.fingerFastSearch();
      if (p != FINGERPRINT_OK)  return -1;

      // found a match!
      Serial.print("Found ID #"); Serial.print(finger.fingerID);
      Serial.print(" with confidence of "); Serial.println(finger.confidence);
      return finger.fingerID;
    }

    boolean validFinger() {
      return active;
    }

    void resetTemFinger() {
      active = false;
      tempId = 0;
    }

    void FingerLoop() {
      tempId = getFingerprintIDez();
      if (tempId == mainId) {
        lcdController.atachNotifi("Huella..OK", 2);
        active = true;
      }

    }

    uint8_t getFingerprintEnroll(int id) {

      int p = -1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2-AgregarPersona");
      lcd.setCursor(0, 1);
      lcd.print("PonerHuella");
      while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        switch (p) {
          case FINGERPRINT_OK:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("2-AgregarPersona");
            lcd.setCursor(0, 1);
            lcd.print("...OK");
            Serial.println(F("Image taken"));
            break;
          case FINGERPRINT_NOFINGER:
            Serial.println(".");
            break;
          case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println(F("Communication error"));
            break;
          case FINGERPRINT_IMAGEFAIL:
            Serial.println(F("Imaging error"));
            break;
          default:
            Serial.println(F("Unknown error"));
            break;
        }
      }

      // OK success!

      p = finger.image2Tz(1);
      switch (p) {
        case FINGERPRINT_OK:
          Serial.println(F("Image converted"));
          break;
        case FINGERPRINT_IMAGEMESS:
          Serial.println(F("Image too messy"));
          return p;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println(F("Communication error"));
          return p;
        case FINGERPRINT_FEATUREFAIL:
          Serial.println(F("Could not find fingerprint features"));
          return p;
        case FINGERPRINT_INVALIDIMAGE:
          Serial.println(F("Could not find fingerprint features"));
          return p;
        default:
          Serial.println(F("Unknown error"));
          return p;
      }

      Serial.println(F("Remove finger"));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2-AgregarPersona");
      lcd.setCursor(0, 1);
      lcd.print("QuitalHuella");
      delay(2000);
      p = 0;
      while (p != FINGERPRINT_NOFINGER) {
        p = finger.getImage();
      }
      Serial.print("ID "); Serial.println(id);
      p = -1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2-AgregarPersona");
      lcd.setCursor(0, 1);
      lcd.print("PonerOtraVez");
      Serial.println(F("Place same finger again"));

      while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        switch (p) {
          case FINGERPRINT_OK:
            Serial.println(F("Image taken"));
            break;
          case FINGERPRINT_NOFINGER:
            Serial.print(F("."));
            break;
          case FINGERPRINT_PACKETRECIEVEERR:
            Serial.println(F("Communication error"));
            break;
          case FINGERPRINT_IMAGEFAIL:
            Serial.println(F("Imaging error"));
            break;
          default:
            Serial.println(F("Unknown error"));
            break;
        }
      }

      // OK success!

      p = finger.image2Tz(2);
      switch (p) {
        case FINGERPRINT_OK:
          Serial.println(F("Image converted"));
          break;
        case FINGERPRINT_IMAGEMESS:
          Serial.println(F("Image too messy"));
          return p;
        case FINGERPRINT_PACKETRECIEVEERR:
          Serial.println(F("Communication error"));
          return p;
        case FINGERPRINT_FEATUREFAIL:
          Serial.println(F("Could not find fingerprint features"));
          return p;
        case FINGERPRINT_INVALIDIMAGE:
          Serial.println(F("Could not find fingerprint features"));
          return p;
        default:
          Serial.println(F("Unknown error"));
          return p;
      }

      // OK converted!
      Serial.print(F("Creating model for #"));  Serial.println(id);

      p = finger.createModel();
      if (p == FINGERPRINT_OK) {
        Serial.println(F("Prints matched!"));
      } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println(F("Communication error"));
        return p;
      } else if (p == FINGERPRINT_ENROLLMISMATCH) {
        Serial.println(F("Fingerprints did not match"));
        return p;
      } else {
        Serial.println(F("Unknown error"));
        return p;
      }

      Serial.print(F("ID ")); Serial.println(id);
      p = finger.storeModel(id);
      if (p == FINGERPRINT_OK) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("2-AgregarPersona");
        lcd.setCursor(0, 1);
        lcd.print("...OK");        
        Serial.println(F("Stored!"));
      } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
        Serial.println(F("Communication error"));
        return p;
      } else if (p == FINGERPRINT_BADLOCATION) {
        Serial.println(F("Could not store in that location"));
        return p;
      } else if (p == FINGERPRINT_FLASHERR) {
        Serial.println(F("Error writing to flash"));
        return p;
      } else {
        Serial.println(F("Unknown error"));
        return p;
      }
    }


};
