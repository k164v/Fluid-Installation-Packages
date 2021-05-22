/**
 A Spout example
 You can port the light using the spout
 Written by @k164v 
 https://github.com/k164v/Fluid-Installation-Packages
 As part of the fluid installation project
 **/

import hypermedia.net.*;
import spout.*;

UDP udp;  // define the UDP object
byte[] dmxData = new byte[540];
LightHub outerLight=new LightHub(-PI+1/8*PI, -0.1, 32, 280, 0);

String ip       = "192.168.1.1";  // the remote IP address
int port        = 8088;    // the destination port
boolean isHide=true;

Spout spout;
PGraphics pgr; // Canvas to receive a texture
PImage img; // Image to receive a texture

void setup() {
  size(1280, 800, P3D);
  background(255);
  //Initialize the UDP server
  udp = new UDP( this, 7777 );
  udp.listen( true );
  
  pgr = createGraphics(width, height, PConstants.P2D);
  img = createImage(width, height, ARGB);
  spout = new Spout(this);
}

//process events
void draw() {
  fill(0);
    if(spout.receiveTexture())
        spout.drawTexture();
  textSize(20);
  text("PRESS THE SCREEN ", 50, 50);
  text("TO DISPLAY/HIDE THE LIGHTS", 50, 100);
  textSize(18);
  text("Written by @k164v",10 ,790);

  displayLight();
  updateLED();
  showColour();
}

void showColour() {
  udp.send( new String(dmxData), ip, port );
}

void mousePressed() {
  isHide=!isHide;
}
