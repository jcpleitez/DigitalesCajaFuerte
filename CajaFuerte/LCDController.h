#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

class LCDController {
  private:
    String message = "";
    String notification = "";
    unsigned long screenTime = 0;
    unsigned long notificationTime = 0;

  public:
    LCDController() {
    }

    void begin() {
      lcd.init();
      //Encender la luz de fondo.
      lcd.backlight();
      lcd.setCursor(0, 0);      
    }

    void LCDLoop() {
      if (millis() - screenTime > 500) {
        screenTime = millis();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Caja Fuerte");
        lcd.setCursor(0, 1);        
        if (notificationTime > millis() && notification.length() > 0) {
          lcd.print(notification);
          notification = "";
        } else {
          lcd.print(message);
        }
      }
    }

    void show(String text) {
      message = text;
    }

    void atachNotifi(String noti, uint8_t t) {
      notificationTime = millis() + (t * 1000);
      notification = noti;
    }




};
