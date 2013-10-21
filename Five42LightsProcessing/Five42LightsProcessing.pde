import processing.serial.*;

Serial mBT = null;
PImage colorPalette; 

void setup() {
  size(640, 480);

  // serial-ness
  String[] serialList = Serial.list();

  // look for candidate
  String btCand = "";
  for (int i=0; i<serialList.length; ++i) {
    if (serialList[i].toLowerCase().contains("tty")) {
      if ((serialList[i].toLowerCase().contains("rn42")) 
        || (serialList[i].toLowerCase().contains("usbmodem"))
        || (serialList[i].toLowerCase().contains("ive42")) 
        || (serialList[i].toLowerCase().contains("usbserial"))) {
        btCand = serialList[i];
        break;
      }
    }
  }
  // see if candidate
  if (!btCand.equals("")) {
    println("Trying to connect to: "+btCand);
    mBT = new Serial(this, btCand, 57600);
  }

  // create color map/palette
  colorMode(HSB, 1.0, 1.0, 1.0, 255.0);
  colorPalette = createImage(width, height, ARGB);
  colorPalette.loadPixels();

  for (int i=0;i<colorPalette.height;++i) {
    for (int j=0;j<colorPalette.width;++j) {
      // treat x,y as Lightness and Hue
      float L = 1.0f-(float(j)/float(colorPalette.width));
      float H = (float(i)/float(colorPalette.height));
      float S = (L<0.5)?(L):(1-L);
      float LS = L+S;
      colorPalette.pixels[i*colorPalette.width+j] = color(H*1.0, 2.0*S/LS, LS);
    }
  }
  colorPalette.updatePixels();
}

void draw() {
  background(0);
  image(colorPalette, 0, 0);
}

void mouseReleased() {
  float L = 1.0f-(float(mouseX)/float(colorPalette.width));
  float H = (float(mouseY)/float(colorPalette.height));
  float S = (L<0.5)?(L):(1-L);
  float LS = L+S;

  color pickedColor = color(H*1.0, 2.0*S/LS, LS);
  println("HSB: "+hue(pickedColor)+" "+saturation(pickedColor)+" "+brightness(pickedColor));
  println("RGB: "+red(pickedColor)+" "+green(pickedColor)+" "+blue(pickedColor));

  int R = int(red(pickedColor)*255.0)&0xff;
  int G = int(green(pickedColor)*255.0)&0xff;
  int B = int(blue(pickedColor)*255.0)&0xff;

  if (mBT != null) {
    mBT.write('R');
    mBT.write(char(R));
    mBT.write('G');
    mBT.write(char(G));
    mBT.write('B');
    mBT.write(char(B));
  }
}

