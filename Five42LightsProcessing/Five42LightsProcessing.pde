import processing.serial.*;

Serial mBT;
PImage colorPalette; 

void setup() {
  size(640, 480);
  String[] serialList = Serial.list();
  // look for candidate
  // connect  
  //mBT = new Serial(this, Serial.list()[4], 57600);

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
}

