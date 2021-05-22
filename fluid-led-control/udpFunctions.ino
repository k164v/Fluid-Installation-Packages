void getUDPServerReady() {
  if (udp.listen(8088)) {
    udp.onPacket([](AsyncUDPPacket packet) {
      updateColor(packet.data(), packet.length());
      packet.printf("Got %u bytes of data", packet.length());
    });
  }
}

void updateColor(byte dataLength[], int info) {
  if (info == 540) {

    udp_counter = 20000;
    for (int i = 0; i < 180; i++) { // For each pixel in strip...
      strip.setPixelColor(i * 3 + 0, strip.Color(dataLength[i * 3 + 1],   dataLength[i * 3],   dataLength[i * 3 + 2])); //  Set pixel's color (in RAM)
      strip.setPixelColor(i * 3 + 1, strip.Color(dataLength[i * 3 + 1],   dataLength[i * 3],   dataLength[i * 3 + 2])); //  Set pixel's color (in RAM)
      strip.setPixelColor(i * 3 + 2, strip.Color(dataLength[i * 3 + 1],   dataLength[i * 3 ],   dataLength[i * 3 + 2])); //  Set pixel's color (in RAM)
    }
    strip.show();                          //  Update strip to match

  } else if (info == 3) {
    udp_counter = 20000;
    for (int i = 0; i < LED_COUNT; i++) { // For each pixel in strip...
      strip.setPixelColor(i, strip.Color(dataLength[1],   dataLength[0],   dataLength[2]));         //  Set pixel's color (in RAM)
    }
    strip.show();                          //  Update strip to match
  }
}
