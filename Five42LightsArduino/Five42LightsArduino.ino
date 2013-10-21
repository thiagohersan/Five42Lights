#define WHITE_RIGHT 5
#define WHITE_LEFT  6

#define RED    9
#define GREEN 10
#define BLUE  11

template <typename T, size_t N>
inline size_t sizeOf(T(&array)[N]) {
  return N;
}

unsigned int allPins[] = {
  WHITE_RIGHT, WHITE_LEFT, RED, GREEN, BLUE};

int rgbv,wv;
byte RGB[3] = {
  0,0,0};
long rgbt,wt;
boolean debugMode;

void setup(){
  Serial.begin(57600);
  debugMode = true;

  // set pin modes
  for(unsigned int i=0; i<sizeOf(allPins); ++i){
    pinMode(allPins[i], OUTPUT);
  }

  wv = rgbv = 0;
  wt = rgbt = millis();
}

void loop(){
  while(Serial.available() > 1){
    char c = Serial.read();
    int b = Serial.read();

    debugMode = ((c == 'D') || (c == 'd'));

    if((c == 'R') || (c == 'r')){
      RGB[0] = b&0xff;
    }
    else if((c == 'G') || (c == 'g')){
      RGB[1] = b&0xff;
    }
    else if((c == 'B') || (c == 'b')){
      RGB[2] = b&0xff;
    }
  }

  if((debugMode) && (millis()-rgbt > 10)){
    rgbv = (rgbv+1)%256;
    uint32_t mrgb = Wheel((uint32_t)rgbv);

    analogWrite(RED, (mrgb>>16)&0xff);
    analogWrite(GREEN, (mrgb>>8)&0xff);
    analogWrite(BLUE, (mrgb>>0)&0xff);
    rgbt = millis();
  }
  else if(!debugMode){
    analogWrite(RED, RGB[0]);
    analogWrite(GREEN, RGB[1]);
    analogWrite(BLUE, RGB[2]);
  }

  if(millis()-wt > 8){
    wv += 8;
    wv = (wv>255)?(-255):(wv);    
    //analogWrite(WHITE_LEFT, abs(wv));
    //analogWrite(WHITE_RIGHT, abs(wv));
    wt = millis();
  }
}

uint32_t Wheel(uint32_t WheelPos) {
  if(WheelPos < 85) {
    return (((3*WheelPos)<<16)&0xff0000) | (((255 - 3*WheelPos)<<8)&0xff00);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return (((255 - 3*WheelPos)<<16)&0xff0000) | ((3*WheelPos)&0xff);
  } 
  else {
    WheelPos -= 170;
    return (((3*WheelPos)<<8)&0xff00) | ((255 - 3*WheelPos)&0xff);
  }
}


