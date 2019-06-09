class MasterKey{
  private:
    uint8_t _pinMasterKey;
    boolean enable = false;
  public:
    MasterKey(uint8_t pinMK){
      _pinMasterKey = pinMK;
    }

    void begin(){
      pinMode(_pinMasterKey, INPUT_PULLUP);
    }

    boolean status(){
      if(digitalRead(_pinMasterKey) == LOW && enable == false){
        lcdController.atachNotifi("LlaveMaestra..OK", 2);
        enable = true;
        return true;
      }
      return false;
    }

    void MKLoop(){
      if(digitalRead(_pinMasterKey) == HIGH){
        enable = false;        
      }
    }
};
