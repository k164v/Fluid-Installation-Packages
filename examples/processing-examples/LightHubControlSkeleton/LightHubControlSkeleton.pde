/**
 A re-construction example
 Written by @k164v 
 Graphic example Inspired by Richard Bourne https://openprocessing.org/sketch/1156864
 https://github.com/k164v/Fluid-Installation-Packages
 As part of the fluid installation project
 **/

import hypermedia.net.*;

UDP udp;  // define the UDP object
byte[] dmxData = new byte[540];
LightHub outerLight=new LightHub(-PI+1/8*PI, -0.1, 32, 280, 0);

String ip       = "192.168.1.1";  // the remote IP address
int port        = 8088;    // the destination port
boolean isHide=true;

void setup() {
  size(1280, 800, P3D);
  background(255);
  //Initialize the UDP server
  udp = new UDP( this, 7777 );
  udp.listen( true );
}

//process events
void draw() {
  fill(0);
  textSize(20);
  text("PRESS THE SCREEN ", 50, 50);
  text("TO DISPLAY/HIDE THE LIGHTS", 50, 100);
  textSize(18);
  text("Written by @k164v, inspired by Richard Bourne",10 ,790);
  colorRun(500);
  displayLight();
  updateLED();
  showColour();
}

void showColour() {
  udp.send( new String(dmxData), ip, port );
}



void colorRun(float n) {
  float t = millis()/float(1000);
  noStroke();
  for (int i = 0; i < n; i++) {
    float rad = 200+sin(t+((i/n)*TWO_PI*4))*175;

    float f = (i/n)*TWO_PI;
    float r = sin(f + 0) * 127 + 128;
    float g = sin(f + 2) * 127 + 128;
    float b = sin(f + 4) * 127 + 128;

    fill(r, g, b, 15);
    float d = sin((i/n)*TWO_PI*8)*10+20;

    if (d > 0) ellipse((width/2)+rad*sin(t+TWO_PI*(i/n)), (height/2)+rad*cos(t+TWO_PI*(i/n)), d, d);
  }
}

void mousePressed() {
  isHide=!isHide;
}
