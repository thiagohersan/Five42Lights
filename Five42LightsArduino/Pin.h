#pragma once

#include "Arduino.h"

class Pin {
public:
  Pin(unsigned short pNum=0, unsigned char onVal=255, unsigned char offVal=0, unsigned int updatePeriod=0, unsigned char stepVal=5);

  void setPinNumber(unsigned short pNum);
  void setOnValue(unsigned char onVal);
  void setOffValue(unsigned char offVal);  
  void setOnOffValue(unsigned char onVal, unsigned char offVal);
  void setStepValue(unsigned char stepVal);
  void setUpdatePeriod(unsigned int period);

  void turnOn(unsigned char val=255);
  void turnOff();

  void update();
private:
  unsigned short _pinNumber;
  unsigned char _onValue, _offValue;
  unsigned int _updatePeriod;
  unsigned char _stepValue;
  unsigned long _lastUpdate;
  unsigned char _currentValue;
};


