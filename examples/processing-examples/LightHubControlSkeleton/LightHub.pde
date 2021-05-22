class LightHub {
  ArrayList<SingleLight> lights;

  LightHub (float startPosition, float angleDifference, int totalight, float dia, int startNumber) {
    lights = new ArrayList<SingleLight>();
    for (int i =0; i<totalight; i++) {
      SingleLight ls = new SingleLight(startPosition+angleDifference*i, dia, i+startNumber);
      lights.add(ls);
    }
  }

  void draw() {
    for (int i=0; i<lights.size(); i++) {
      lights.get(i).display();
    }
  }

  void update() {
    for (int i=0; i<lights.size(); i++) {
      lights.get(i).updateDMXdata();
    }
  }
}

class SingleLight {
  PVector location;
  int currentNumber;
  float previousBrightness;

  SingleLight (float radius, float dia, int currentNumber) {
    this.location = new PVector (dia*cos(radius), dia*sin(radius));
    this.currentNumber = currentNumber;
  }

  void display() {
    noFill();
    ellipse(location.x, location.y, 50, 50);
    //textSize(32);
    fill(0);
    //text(currentNumber, location.x, location.y);
    noFill();
  }

  void updateDMXdata() {
    loadPixels();
    color tempColor= pixels[width*int(location.y+height/2)+int(location.x+width/2)];
    dmxData[(currentNumber)*3] = (byte) red(tempColor);
    dmxData[(currentNumber)*3+1] = (byte) green(tempColor);
    dmxData[(currentNumber)*3+2] = (byte) blue(tempColor);
    float currentBrightNess=brightness(tempColor);

    previousBrightness=currentBrightNess;
  }
}

void displayLight() {
  if (!isHide) {
    pushMatrix();
    stroke(0, 15);
    translate(width/2, height/2);
    outerLight.draw();
    popMatrix();
  }
} 

void updateLED() {
  outerLight.update();
}
