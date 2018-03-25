#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
bool ran; //variable to tell if you need to water plant
int analogPin = A0;     // moisture sensor connected to analog pin A0, our ADC pin
                       // outside leads to ground and +5V
int val;       // variable to store the value read

 

void setup() 
{ 
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object 
  ran = true;
  Serial.begin(9600);              //  setup serial
} 
 
void loop() {
//code for the moisture detector
 val = analogRead(analogPin);     // read the input pin
 Serial.println(val);             // debug value
 delay(1000);

 if (val > 1000) {
  ran = false;
 }

//code for servo
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
