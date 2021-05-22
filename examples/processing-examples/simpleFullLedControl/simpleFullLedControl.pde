/**
  Very simple control example to demostrate the control of the led lights with the basic control mode
  Written by @k164v 
  https://github.com/k164v/Fluid-Installation-Packages
  As part of the fluid installation project
**/

import hypermedia.net.*;
UDP udp;  // define the UDP object


void setup() {
  size(255, 255);
  //Initial 
  udp = new UDP( this, 7777 );
  udp.listen( true );
}

//process events
void draw() {
  background(mouseX, mouseY, 0);
  sendColour(mouseX, mouseY, 0);
}

void sendColour(int xx, int yy, int zz) {
  char[] tempInfo = new char[3];
  String ip       = "192.168.1.1";	// the remote IP address
  int port        = 8088;		// the destination port

  tempInfo[0]=char(xx);
  tempInfo[1]=char(yy);
  tempInfo[2]=char(zz);
  
  udp.send( new String(tempInfo), ip, port );
}
