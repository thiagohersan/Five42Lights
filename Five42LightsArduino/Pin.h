#pragma once

#include "Arduino.h"

class Pin {
public:
  Pin(unsigned short pNum=0, unsigned char onVal=255, unsigned char offVal=0, unsigned int period=0);

  void setPinNumber(unsigned short pNum);
  void setOnValue(unsigned char onVal);
  void setOffValue(unsigned char offVal);  
  void setOnOffValue(unsigned char onVal, unsigned char offVal);
  void setPeriod(unsigned int period);

  void update();
private:
  unsigned short _pinNumber;
  unsigned char _onValue, _offValue;
  unsigned int _period;
  unsigned long _lastUpdate;
  boolean _currentState;
};


