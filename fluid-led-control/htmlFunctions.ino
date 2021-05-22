void gethtmlServerReady(){

    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {

    int paramsNr = request->params();
    if (request->hasArg("move")) {
      if (request->getParam("move")->value().toInt() == 0) {
        isMove = false;
      } else {
        isMove = true;
      }
    }

    if (request->hasArg("color")) {
      String tempColorString = request->getParam("color")->value();
      a_color[0] = stringSplitHelper(tempColorString, '-', 0).toInt();
      a_color[1] = stringSplitHelper(tempColorString, '-', 1).toInt();
      a_color[2] = stringSplitHelper(tempColorString, '-', 2).toInt();
    }

    if (request->hasArg("trans")) {
      String tempColorString = request->getParam("trans")->value();
      b_color[0] = stringSplitHelper(tempColorString, '-', 0).toInt();
      b_color[1] = stringSplitHelper(tempColorString, '-', 1).toInt();
      b_color[2] = stringSplitHelper(tempColorString, '-', 2).toInt();
    }

    if (request->hasArg("delaytime")) {
      // String tempColorString = request->getParam("trans")->value();
      delayTime = request->getParam("delaytime")->value().toInt();
    }

    request->send(200, "text/html", SendHTML());
  });


  server.begin();
}


String SendHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">   \n";
  ptr += "<meta charset=\"UTF-8\">   \n";

  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; height : 100%;}\n";

  ptr += "body{margin-top: 80px; height: 100%;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  if (isMove)
  {
    ptr += "body{background-image: linear-gradient(" + constructRGBAstr(a_color) + "," + constructRGBAstr(b_color) + ");}";
  } else {
    ptr += "body{background-image: linear-gradient(" + constructRGBAstr(a_color) + "," + constructRGBAstr(a_color) + ");}";
  }
  //ptr += "body{background-image: linear-gradient("+constructRGBAstr(a_color)+","+constructRGBAstr(b_color)+");}";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>柔软友好颜色改变器</h1>\n";
  ptr += "<h3>Friendly Color Changer</h3>\n";
  ptr += "<h3>超级友好</h3>\n";

  String colorHexString = "#" + digitfy(String(a_color[0], HEX)) + digitfy(String(a_color[1], HEX)) + digitfy(String(a_color[2], HEX));
  String tempColorString = "\"" + colorHexString + "\"";


  //Serial.println(tempColorString + "   " + digitfy(String(255, HEX)) + digitfy(String(0, HEX)) + digitfy(String(0, HEX)));
  ptr += "<input type=\"color\" id=\"color\" name=\"favcolor\" value=" + tempColorString + ">\n";

  ptr += "<script>function hexToRgb(a){var e=/^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i.exec(a);return e?{r:parseInt(e[1],16),g:parseInt(e[2],16),b:parseInt(e[3],16)}:null}document.getElementById(\"color\").onchange = function() {console.log(this.value); console.log(hexToRgb(this.value));window.location=\"?color=\"+hexToRgb(this.value).r+\"-\"+hexToRgb(this.value).g+\"-\"+hexToRgb(this.value).b}</script>";

  if (isMove)
  {
    String colorTHexString = "#" + digitfy(String(b_color[0], HEX)) + digitfy(String(b_color[1], HEX)) + digitfy(String(b_color[2], HEX));
    String tempColorTString = "\"" + colorTHexString + "\"";
    ptr += "<input type=\"color\" id=\"color_transform\" name=\"favcolor\" value=" + tempColorTString + ">\n";
    ptr += "<p>MOVE</p><a class=\"button button-on\" href=\"/?move=0\">ON</a>\n";
    ptr += "<script>function hexToRgb(a){var e=/^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i.exec(a);return e?{r:parseInt(e[1],16),g:parseInt(e[2],16),b:parseInt(e[3],16)}:null}document.getElementById(\"color_transform\").onchange = function() {console.log(this.value); console.log(hexToRgb(this.value));window.location=\"?trans=\"+hexToRgb(this.value).r+\"-\"+hexToRgb(this.value).g+\"-\"+hexToRgb(this.value).b}</script>";
    ptr += "<input type=\"range\" id=\"speed\" name=\"change_speed\" min=\"3\" max=\"50\" value=\"" + String(delayTime) + "\" step=\"1\">";
    ptr +=  "<script>document.getElementById(\"speed\").onchange = function() {window.location=\"?delaytime=\"+this.value}</script>";
  }
  else
  {
    ptr += "<p>MOVE</p><a class=\"button button-off\" href=\"/?move=1\">OFF</a>\n";
    //ptr += "<p>Interpolate: OFF</p><a class=\"button button-on\" href=\"/moveoff\">ON</a>\n";
  }


  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

/*
   A very unefficient function to transfer array

*/
String digitfy(String inputArray) {

  if (inputArray.length() < 2) {
    return "0" + inputArray;
  } else {
    return  inputArray;
  }
}


/*

   Function to split hex string into string

*/
String HexString2ASCIIString(String hexstring) {
  String temp = "", sub = "", result;
  char buf[3];
  for (int i = 0; i < hexstring.length(); i += 2) {
    sub = hexstring.substring(i, i + 2);
    sub.toCharArray(buf, 3);
    char b = (char)strtol(buf, 0, 16);
    if (b == '\0')
      break;
    temp += b;
  }
  return temp;
}


/**

  Helper Function to split String value


*/

String stringSplitHelper(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


/*
   Function used for construct RGBA string, ready for the call

*/
String constructRGBAstr(int inputColor[]) {
  return "rgba(" + String(inputColor[0]) + "," + String(inputColor[1]) + ',' + String(inputColor[2]) + ",0.1)";
}
