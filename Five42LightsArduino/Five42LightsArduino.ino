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
long rgbt,wt;

void setup(){
  Serial.begin(57600);

  // set pin modes
  for(unsigned int i=0; i<sizeOf(allPins); ++i){
    pinMode(allPins[i], OUTPUT);
  }

  wv = rgbv = 0;
  wt = rgbt = millis();
}

void loop(){
  if(Serial.available() > 2){
  }
  
  if(millis()-rgbt > 500){
    rgbv = (rgbv+1)%8;
    digitalWrite(RED, (rgbv>>0)&0x1);
    digitalWrite(GREEN, (rgbv>>1)&0x1);
    digitalWrite(BLUE, (rgbv>>2)&0x1);
    rgbt = millis();
  }

  if(millis()-wt > 8){
    wv += 8;
    wv = (wv>255)?(-255):(wv);    
    analogWrite(WHITE_LEFT, abs(wv));
    analogWrite(WHITE_RIGHT, abs(wv));
    wt = millis();
  }

}




