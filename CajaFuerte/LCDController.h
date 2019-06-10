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

    void LCDLoop(String mainText) {
      if (millis() - screenTime > 500) {
        screenTime = millis();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(mainText);
        lcd.setCursor(0, 1);
        if (notificationTime > millis()) {
          lcd.print(notification);          
        } else {
          notification = "";
          lcd.print(message);
        }
      }
    }

    void show(String text) {
      if(text.length() > 0){
        message = text;
      }else{
        message = "Ingrese PIN";        
      }
    }

    void atachNotifi(String noti, uint8_t t) {
      if (noti.length() > 0) {
        notificationTime = millis() + (t * 1000);
        notification = noti;
      }
    }




};
