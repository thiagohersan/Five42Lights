#include "Pin.h"

Pin::Pin(unsigned short pNum, unsigned char onVal, unsigned char offVal, unsigned int period){
  (*this).setOnOffValue(onVal, offVal);
  (*this).setPeriod(period);
  (*this).setPinNumber(pNum);
  _currentState = false;
  _lastUpdate = millis();
}

void Pin::setPinNumber(unsigned short pNum){
  // TODO: check if pin number is valid pwm pin
  _pinNumber = pNum;
  pinMode(_pinNumber, OUTPUT);
  analogWrite(_pinNumber, _currentState);    
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

void Pin::setPeriod(unsigned int period){
  _period = period;
}

void Pin::update(){
  if((millis() - _lastUpdate) > _period){
    _currentState = !_currentState;
    analogWrite(_pinNumber, _currentState?(_onValue):(_offValue));
    _lastUpdate = millis();
  }
}


