
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


// WiFi network
const char* ssid     = ""; // wifi SSID for connect 
const char* password = ""; // PASSWORD

const int pin_r = 15;
const int pin_g = 12;
const int pin_b = 13;


int red = 0;
int green = 0;
int blue = 0;

int flash_time_on = 100;
int flash_time_off = 100;

int dynamic_time = 10;

int led_mode = 0;

int flag_dynamic = 1;

ESP8266WebServer server ( 80 );
char htmlResponse[4400];





void handleRoot() {

  if (server.arg("mode") != "") {
    if (server.arg("mode") == "0") {
      led_mode = 0;
    }
    if (server.arg("mode") == "1") {
      led_mode = 1;
      flag_dynamic=1;
    }
    if (server.arg("mode") == "2") {
      led_mode = 2;
    }
    if (server.arg("mode") == "3") {
      led_mode = 3;
    }
    if (server.arg("mode") == "4") {
      led_mode = 4;
    }
  }


  if (server.arg("r") != "") {
    red = server.arg("r").toInt();
  }

  if (server.arg("g") != "") {
    green = server.arg("g").toInt();

  }

  if (server.arg("b") != "") {
    blue = server.arg("b").toInt();
  }



  if (server.arg("dynamic_time") != "") {
    dynamic_time = server.arg("dynamic_time").toInt();
  }
  if (server.arg("flasher_on") != "") {
    flash_time_on = server.arg("flasher_on").toInt();
  }
  if (server.arg("flasher_off") != "") {
    flash_time_off = server.arg("flasher_off").toInt();
  }






  Serial.print("\n\n");
  Serial.print("ledmode: ");
  Serial.print(led_mode);
  Serial.print("\nred: ");
  Serial.print(red);
  Serial.print("\ngreen: ");
  Serial.print(green);
  Serial.print("\nblue: ");
  Serial.print(blue);
  Serial.print("\nTime Dynamic: ");
  Serial.print(dynamic_time);
  Serial.print("\nTime Flasher On: ");
  Serial.print(flash_time_on);
  Serial.print("\nTime Flasher Off: ");
  Serial.print(flash_time_off);
  Serial.print("\n\n ");



  server.send ( 3800, "text/html", htmlResponse );


}
void handelapi() {

  if (server.arg("mode") != "") {
    if (server.arg("mode") == "0") {
      led_mode = 0;
    }
    if (server.arg("mode") == "1") {
      led_mode = 1;
    }
    if (server.arg("mode") == "2") {
      led_mode = 2;
    }
    if (server.arg("mode") == "3") {
      led_mode = 3;
    }
    if (server.arg("mode") == "4") {
      led_mode = 4;
    }
  }


  if (server.arg("r") != "") {
    red = server.arg("r").toInt();
  }

  if (server.arg("g") != "") {
    green = server.arg("g").toInt();

  }

  if (server.arg("b") != "") {
    blue = server.arg("b").toInt();
  }



  if (server.arg("dynamic_time") != "") {
    dynamic_time = server.arg("dynamic_time").toInt();
  }
  if (server.arg("flasher_on") != "") {
    flash_time_on = server.arg("flasher_on").toInt();
  }
  if (server.arg("flasher_off") != "") {
    flash_time_off = server.arg("flasher_off").toInt();
  }






  Serial.print("\n\n");
  Serial.print("ledmode: ");
  Serial.print(led_mode);
  Serial.print("\nred: ");
  Serial.print(red);
  Serial.print("\ngreen: ");
  Serial.print(green);
  Serial.print("\nblue: ");
  Serial.print(blue);
  Serial.print("\nTime Dynamic: ");
  Serial.print(dynamic_time);
  Serial.print("\nTime Flasher On: ");
  Serial.print(flash_time_on);
  Serial.print("\nTime Flasher Off: ");
  Serial.print(flash_time_off);
  Serial.print("\n\n ");


}


void process_dynamic_color() {


  if (flag_dynamic == 1) { //red up
    
    if (red >= 0 && red < 255) {
      red++;

    } else if ( red == 255 && blue == 255) {
      flag_dynamic = 6;
    } else {
      flag_dynamic = 2;
        Serial.print(flag_dynamic);
    }

  } else if (flag_dynamic == 2) { //green up
    if (green >= 0 && green < 255) {
      green++;
    } else if ( green == 255) {
      flag_dynamic = 4;
              Serial.print(flag_dynamic);

    }

  } else if (flag_dynamic == 3) { // blue up
    if (blue >= 0 && blue < 255) {
      blue++;
    } else if ( blue == 255) {
      flag_dynamic = 5;
              Serial.print(flag_dynamic);

    }

  } else if (flag_dynamic == 4) { //red down

    if (red <= 255 && red > 0) {
      red--;
    } else if ( red == 0) {
      flag_dynamic = 3;
              Serial.print(flag_dynamic);

    }

  } else if (flag_dynamic == 5) { //green down
    if (green <= 255 && green > 0) {
      green--;
    } else if ( green == 0) {
      flag_dynamic = 1;
              Serial.print(flag_dynamic);

    }
  } else if (flag_dynamic == 6) { //blue down
    if (blue <= 255 && blue > 0) {
      blue--;
    } else if ( blue == 0) {
      flag_dynamic = 2;
              Serial.print(flag_dynamic);

    }


  }

}





void setup() {

  // Start serial
  Serial.begin(9600);
  snprintf ( htmlResponse, 3800, "<!DOCTYPE html><html lang=\'en\'><head> <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-iYQeCzEYFbKjA/T2uDLTpkwGzCiq6soy8tYaI1GyVh/UjpbCx/TYkiZhlZB6+fzT\" crossorigin=\"anonymous\"></head><body class=\"bg-dark container\"> <br><br><br><br> <div id=\"login card \"> <div class=\"column\"> <div class=\"row \"> <div class=\"col\"> <div class=\"card bg-secondary\"> <div class=\"card-body\"> <h5 class=\"card-title\">Mode</h5> <div class=\"row\"> <a href=\"?mode=0\" class=\"btn btn-dark col m-2\">Static</a> <a href=\"?mode=1\" class=\"btn btn-dark col m-2\">Dynamic</a> </div> <div class=\"row\"> <a href=\"?mode=2\" class=\"btn btn-dark col m-2\">Flasher</a> <a href=\"?mode=3\" class=\"btn btn-dark col m-2\">Flasher RGB </a> <a href=\"?mode=4\" class=\"btn btn-dark col m-2\">Flasher FullColor</a> </div> </div> </div> </div> </div> <br> <form method=\"get\"> <div class=\"row\"> <div class=\"col\"> <div class=\"card bg-secondary\"> <div class=\"card-body\"> <h5 class=\"card-title\">Time</h5> <div class=\"column\"> <div class=\"row col m-2\"> <label> Time Color Dynamic</label> </div> <div class=\"row col m-2\"> <label class=\"p-2\">1 ms</label> <input type=\"range\" min=\"1\" max=\"100\" value=\"10\" class=\"col\" name=\"dynamic_time\"> <label class=\"p-2\">100 ms</label> </div> </div> <hr class=\"bg-dark \"> <div class=\"column\"> <div class=\"row col m-2\"> <label> Time Flasher ON</label> </div> <div class=\"row col m-2\"> <label class=\"p-2\">1 ms</label> <input type=\"range\" min=\"1\" max=\"1000\" value=\"100\" class=\"col\" name=\"flasher_on\"> <label class=\"p-2\">1000 ms</label> </div> </div> <hr class=\"bg-dark \"> <div class=\"column\"> <div class=\"row col m-2\"> <label> Time Flasher OFF</label> </div> <div class=\"row col m-2\"> <label class=\"p-2\">1 ms</label> <input type=\"range\" min=\"1\" max=\"1000\" value=\"100\" class=\"col\" name=\"flasher_off\"> <label class=\"p-2\">1000 ms</label> </div> </div> <div class=\"row\"> <input type=\"submit\" class=\"btn btn-dark col m-2\" value=\"Submit\"> </div> </div> </div> </div> </div> </form> <br> <form method=\"get\"> <div class=\"row \"> <div class=\"col\"> <div class=\"card bg-secondary\"> <div class=\"card-body \"> <h5 class=\"card-title\">Color</h5> <div class=\"row\"> <a href=\"?r=255&g=0&b=0\" class=\"btn btn-danger col m-2\">Red</a> <a href=\"?r=0&g=255&b=0\" class=\"btn btn-success col m-2\">Green</a> <a href=\"?r=0&g=0&b=255\" class=\"btn btn-primary col m-2\">Blue</a> </div> <div class=\"row\"> <a href=\"?r=0&g=0&b=0\" class=\"btn btn-dark col m-2\">OFF</a> <a href=\"?r=255&g=255&b=255\" class=\"btn btn-light col m-2\">ON</a> </div> <hr> <div class=\"column\"> <div class=\"column\"> <div class=\"row col m-2\"> <label> Red</label> </div> <div class=\"row col m-2\"> <label class=\"p-2\">0</label> <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"col\" name=\"r\"> <label class=\"p-2\">255</label> </div> </div> <hr> <div class=\"column\"> <div class=\"row col m-2\"> <label> Green</label> </div> <div class=\"row col m-2\"> <label class=\"p-2\">0</label> <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"col\" name=\"g\"> <label class=\"p-2\">255</label> </div> </div> <hr> <div class=\"column\"> <div class=\"row col m-2\"> <label> Blue</label> </div> <div class=\"row col m-2\"> <label class=\"p-2\">0</label> <input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"col\" name=\"b\"> <label class=\"p-2\">255</label> </div> </div> <div class=\"row\"> <input type=\"submit\" class=\"btn btn-warning col m-2\" value=\"Submit\"> </div> </div> </div> </div> </div> </div> </form> </div> </div></body></html>");

  pinMode(pin_r, OUTPUT);
  pinMode(pin_g, OUTPUT);
  pinMode(pin_b, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }



  server.on ( "/", handleRoot );
  server.on ( "/api", handelapi );

  server.begin();


}

void loop() {
  server.handleClient();


  if (led_mode == 0) {

    analogWrite(pin_r, red);
    analogWrite(pin_g, green);
    analogWrite(pin_b, blue);

  } else if (led_mode == 1) {

    process_dynamic_color();
    analogWrite(pin_r, red);
    analogWrite(pin_g, green);
    analogWrite(pin_b, blue);
    delay(dynamic_time);

  
} else if (led_mode == 2) {

  digitalWrite(pin_r, HIGH);
  digitalWrite(pin_g, HIGH);
  digitalWrite(pin_b, HIGH);
  delay(flash_time_on);
  digitalWrite(pin_r, LOW);
  digitalWrite(pin_g, LOW);
  digitalWrite(pin_b, LOW);
  delay(flash_time_off);

} else if (led_mode == 3) {

  int ran = random(0, 4);
  if (ran == 1) {
    analogWrite(pin_r, 255);
    analogWrite(pin_g, 0);
    analogWrite(pin_b, 0);
  } else if (ran == 2) {
    analogWrite(pin_r, 0);
    analogWrite(pin_g, 255);
    analogWrite(pin_b, 0);
  } else if (ran == 3) {
    analogWrite(pin_r, 0);
    analogWrite(pin_g, 0);
    analogWrite(pin_b, 255);
  }

  delay(flash_time_on);

  analogWrite(pin_r, 0);
  analogWrite(pin_g, 0);
  analogWrite(pin_b, 0);

  delay(flash_time_off);

} else if (led_mode == 4) {

  analogWrite(pin_r, random(0, 255));
  analogWrite(pin_g, random(0, 255));
  analogWrite(pin_b, random(0, 255));
  delay(flash_time_on);
  analogWrite(pin_r, 0);
  analogWrite(pin_g, 0);
  analogWrite(pin_b, 0);
  delay(flash_time_off);

}

}
