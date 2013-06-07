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
byte RGB[3] = {0,0,0};
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
  if(Serial.available() > 1){
    char c = Serial.read();
    int b = Serial.read();
    while(Serial.available()){
      Serial.read();
    }
    if((c == 'R') || (c == 'r')){
      debugMode = false;
      RGB[0] = b&0xff;
    }
    else if((c == 'G') || (c == 'g')){
      debugMode = false;
      RGB[1] = b&0xff;
    }
    else if((c == 'B') || (c == 'b')){
      debugMode = false;
      RGB[2] = b&0xff;
    }
    else if((c == 'D') || (c == 'd')){
      debugMode = true;
    }
  }

  if(millis()-rgbt > 500){
    if(debugMode){
      rgbv = (rgbv+1)%8;
      digitalWrite(RED, (rgbv>>0)&0x1);
      digitalWrite(GREEN, (rgbv>>1)&0x1);
      digitalWrite(BLUE, (rgbv>>2)&0x1);
    }
    else{
      analogWrite(RED, RGB[0]);
      analogWrite(GREEN, RGB[1]);
      analogWrite(BLUE, RGB[2]);
    }
    rgbt = millis();
  }

  if(millis()-wt > 8){
    wv += 8;
    wv = (wv>255)?(-255):(wv);    
    //analogWrite(WHITE_LEFT, abs(wv));
    //analogWrite(WHITE_RIGHT, abs(wv));
    wt = millis();
  }

}

