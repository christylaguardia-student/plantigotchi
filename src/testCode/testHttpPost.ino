#include <Servo.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {
  
  USE_SERIAL.begin(115200); //baud rate
  
  for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Puppet Guest", "argon4949");
    
}

void post() {
  String data = "title=foo&body=bar&userId=1";
  USE_SERIAL.println(data);
  
  // make http request
  HTTPClient http;
  http.begin("http://jsonplaceholder.typicode.com/posts");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(data);
  
  // check if success, httpCode will be negative on error
  if(httpCode > 0) {
    USE_SERIAL.printf("[HTTP] POSt... code: %d\n", httpCode);
    
    if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);
      }
    } else {
      USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  
  http.end();
  
}

void loop() {
  post();
  delay(5000);
}
