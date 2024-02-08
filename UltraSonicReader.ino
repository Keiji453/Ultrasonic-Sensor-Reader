// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int trigPin = 9;  // Pin 9 -> pwm trigger pint
const int echoPin = 10; // Pin 10 -> echo read pin

float duration, distance, time; // global variables for echo duration, and distance.

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Idle Message");

  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  

  Serial.begin(115200);
  Serial.println("Time(s),Distance(cm)"); // send general info through serial
}

void loop() {
  time = millis(); // get the current time of the loop

  // these 5 lines pulse the sensor
	digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH); // This kinda waits until the reciever gets feedback

  distance = (duration*.0343)/2;  // calculation for the distance to the object, 0.0343 = speed of sound in cm/us

  Serial.print(time); // Serial << time
  Serial.print(" ");
  Serial.print(distance); // Serial << distance
  Serial.println();
}
