/**
 * Written by k164v
 * 
 * kenny.2312
 * 
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#include <AsyncUDP.h>

#define LED_PIN    19

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 540

/* Put your SSID & Password */
const char* ssid = "fluid-away";  // Enter SSID here
const char* password = "kkkk8888";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

AsyncUDP udp;
AsyncWebServer  server(80);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);



bool isMove = true;
bool isInte = true;
int delayTime = 30;

int a_color[3] = {255, 0, 0};
int b_color[3] = {0, 0, 255};

int udp_counter = 0;

void setup() {

  //Get Wifi Ready
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  getLEDReady();
  gethtmlServerReady();
  getUDPServerReady();
}



void loop() {
  if (udp_counter > 0) {
    udp_counter--;
  } else {
    updateLedColorBasedOnHTML();
  }
}
