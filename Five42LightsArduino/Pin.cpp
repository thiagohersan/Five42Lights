#include "Pin.h"

Pin::Pin(unsigned short pNum, unsigned char onVal, unsigned char offVal, unsigned int updatePeriod, unsigned char stepVal){
  (*this).setOnOffValue(onVal, offVal);
  (*this).setStepValue(stepVal);
  (*this).setUpdatePeriod(updatePeriod);
  (*this).setPinNumber(pNum);
  _currentValue = 0;
  _lastUpdate = millis();
}

void Pin::setPinNumber(unsigned short pNum){
  // TODO: check if pin number is valid pwm pin
  _pinNumber = pNum;
  pinMode(_pinNumber, OUTPUT);
  analogWrite(_pinNumber, _currentValue);    
}

void Pin::setOnValue(unsigned char onVal){
  setOnOffValue(onVal, _offValue);
}
void Pin::setOffValue(unsigned char offVal){
  setOnOffValue(_onValue, offVal);
}
void Pin::setOnOffValue(unsigned char onVal, unsigned char offVal){
  _onValue = onVal;
  _offValue = offVal;
}

void Pin::setStepValue(unsigned char stepVal){
  _stepValue = stepVal;
}
void Pin::setUpdatePeriod(unsigned int period){
  _updatePeriod = period;
}

void Pin::update(){
  if((millis() - _lastUpdate) > _updatePeriod){
    _currentValue += _stepValue;
    if(_currentValue > _onValue){
      _currentValue = -(_onValue);
    }
    else if(abs(_currentValue) < _offValue){
      _currentValue = _offValue;
    }
    analogWrite(_pinNumber, abs(_currentValue));
    _lastUpdate = millis();
  }
}

