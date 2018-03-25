#include <Servo.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define Serial Serial

//*** wifi variables ***//
ESP8266WiFiMulti WiFiMulti;

//*** sensor variables ***//
const int sensorpin=0;
int moisture=0;
int lastWaterVal=0;
#define MOIST 450 // minimum level of satisfactory moisture
#define DRY 350  // maximum level of tolerable dryness
#define SOAKED 600 // minimum desired level after watering
#define WATERING_CRITERIA 100 // minimum change in value that indicates watering

//*** servo variables ***//
Servo myservo;  // create servo object to control a servo
bool ran; //variable to tell if you need to water plant
int analogPin = A0;     // moisture sensor connected to analog pin A0, our ADC pin
                       // outside leads to ground and +5V

//*** setup functions ***//

void setupWifi() {
  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Puppet Guest", "argon4949");
}

void setupSensor() {
  Serial.println("Soil Moisture Module v1: Loaded");
  Serial.println();
}

void setupServo() {
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object 
  ran = true;
}

void getSensorReading() {

  //*** reads the moisture in the soil  ***//
  
  moisture = analogRead(sensorpin);
  Serial.println(moisture);

  //*** sends the reading to the server  ***//
  
  HTTPClient http;
  http.begin("http://10.0.12.192:3000/"); // use your ip address when running server locally
  http.addHeader("Content-Type", "application/json");

  char moistureString [50];
  sprintf(moistureString, "{ \"moisture\": %d }", moisture); // create json object to send to the server
  Serial.printf("%s\n", moistureString);
  int httpCode = http.POST(moistureString);
  
  if(httpCode > 0) {  // check if success, httpCode will be negative on error
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
  
  //*** determines if plant needs water  ***//
  
  if (moisture >= SOAKED  &&  lastWaterVal < MOIST) {
    Serial.println("Thank you for watering me!");  
  }
  else if  (moisture >= SOAKED  &&  lastWaterVal >= MOIST ) {
    Serial.println("You over watered me");
  }
  else if  (moisture < SOAKED  &&  lastWaterVal < MOIST ) {
    Serial.println("You didn't water me enough");
    
    //*** water the plant ***//
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
  }
     
  lastWaterVal = moisture; // record the watering reading for comparison next time this function is called
}








//*** runs at startup ***//
void setup() {
  Serial.begin(115200); //baud rate
  setupWifi();
  setupServo();
}

//*** runs continuously ***//
void loop() {
  getSensorReading();
  delay(5000);
}
