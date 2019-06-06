#define SOLENOIDTIMEOUT 2

class Solenoid {
  private:
    uint8_t _pinSolenoid;
    unsigned long activeTime = 0;
  public:
    Solenoid(uint8_t pinSolenoid) {
      _pinSolenoid = pinSolenoid;
    }

    void begin() {
      pinMode(_pinSolenoid, OUTPUT);
    }

    void active(uint8_t seconds) {
      activeTime = millis() + seconds * 1000;
    }

    void disable() {
      activeTime = 0;
    }

    void solenoidLoop() {
      if (activeTime > millis()) {
        digitalWrite(_pinSolenoid, HIGH);
      } else {
        digitalWrite(_pinSolenoid, LOW);
      }
    }
};
