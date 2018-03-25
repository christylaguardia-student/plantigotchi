#include <Servo.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

Servo myservo;  // create servo object to control a servo
bool ran; //variable to tell if you need to water plant
int analogPin = A0;     // moisture sensor connected to analog pin A0, our ADC pin
                       // outside leads to ground and +5V
int analogReadValue;       // variable to store the value read

void setupWifi() {
  USE_SERIAL.begin(115200); //baud rate
  
  for(uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Puppet Guest", "argon4949");
}

void setupServo() {
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object 
  ran = true;
  Serial.begin(9600);              //  setup serial
}

void recordReading() {
  // make http POST request
  HTTPClient http;
  http.begin("http://10.0.13.63:3000/");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String analogReadValueAsString = String(analogReadValue);
  int httpCode = http.POST(analogReadValueAsString);
  
  // check if success, httpCode will be negative on error
  if(httpCode > 0) {
    USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);
    
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      USE_SERIAL.println(payload);
    }
  } else {
    USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

void moveServo() {
  if (!ran) {
    int pos;
  
    for(pos = 0; pos <= 100; pos += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    for(pos = 100; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    ran = true;
    delay(5000);
  }
}

void detectMoisture() {
  analogReadValue = analogRead(analogPin);     // read the input pin
  Serial.println(analogReadValue);             // debug value
  delay(1000);

  recordReading();

 if (analogReadValue > 1000) {
  ran = false;
 }

 moveServo();
}



//*** runs at startup ***//
void setup() {
  setupWifi();
  setupServo();
}

//*** runs continuously ***//
void loop() {
  detectMoisture();
  delay(5000);
}