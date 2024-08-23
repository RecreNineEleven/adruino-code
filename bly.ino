/*************************************************************

  This sketch shows how to write values to Virtual Pins

  NOTE:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  App dashboard setup:
    Value Display widget attached to Virtual Pin V5
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6cjjmE04n"
#define BLYNK_TEMPLATE_NAME "Cumlord"
#define BLYNK_AUTH_TOKEN "kxH6Odf178GgY-wdu21znVPPHOaGpNT1"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ec";
char pass[] = "12345678";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
int h = 0;
int bom = 2;
int tudong = 0;
int dieukhien = 0;
void myTimerEvent() {
  // You can send any value at any time.
  // Please don't send  more that 10 values per second.
  h = analogRead(A0);
  //map(h,0,1024,0,100);
  h = h * 100;
  h = h / 1024;
  h = 100 - h;
  h = h * 2;
  Blynk.virtualWrite(V5, h);
}
BLYNK_WRITE(V0) {
  tudong = param.asInt();  // assigning incoming value from pin V1 to a variable

  // process received value
}
BLYNK_WRITE(V1) {
  dieukhien = param.asInt();  // assigning incoming value from pin V1 to a variable

  // process received value
}

void setup() {
  pinMode(bom, OUTPUT);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  if (tudong == 1) {
    if (h < 50) {
      digitalWrite(bom, 1);
    } else if (h > 50) {
      digitalWrite(bom, 0);
    }
  }
  if (tudong == 0) {
    digitalWrite(bom, dieukhien);
  }

  Blynk.run();
  timer.run();  // Initiates BlynkTimer
}
