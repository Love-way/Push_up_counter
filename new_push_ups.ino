#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal.h> // include LCD library
#define BLUE 12 // define RGB-led pins
#define RED 10

  LiquidCrystal_I2C lcd(0x27,16, 2); // set lcd pins

const int trigPin = 8; //set pins for the ultrasonic sensor, button and buzzer
const int echoPin = 9;
const int buttonPin = A0;
const int b = 13;

long duration; // set integers
int distance;
int i;
int buttonState = 0;
int x = 0;
int y = 0;

void setup() {
  Serial.begin(9600); // begin in 9600 baud 
  Wire.begin();
  lcd.begin(); // begin lcd, define scale of lcd (16 places in a row, 2 rows)
  lcd.backlight();
  
  
  pinMode(trigPin, OUTPUT); //set pin modes
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(b, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  
  lcd.print("Push Ups:");
  Serial.print("Push Ups:");
}

void loop() {
  digitalWrite(trigPin, HIGH); // send out an ultra sonic sound for 10 microseconds and measure the time it took for the sound to go from the trigpin to the echo pin
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  distance = duration * 0.034/2; //convert the time the signal took to travel to distance in cm

  if (distance >= 20) {digitalWrite(RED, HIGH); //configure RGB-led to burn red, magenta or blue depending on distance
                       digitalWrite(BLUE, LOW);}
  if (distance <= 20) {digitalWrite(BLUE, HIGH);}
  if (distance <= 10) {digitalWrite(RED, LOW);}

  if (i == (10 * y) && x == (1 * y)) { //this if statement plays a sound every ten pushups
                 tone(b, 146.8);
                 delay(50);
                 noTone(b);
                 delay(100);
                 tone(b, 146.8);
                 delay(50);
                 noTone(b);
                 delay(50);
                 tone(b, 293.7);
                 delay(100);
                 noTone(b);
                 x ++;
                 y ++;
  }
  else if (distance <= 10) {delay(150);} //this if else statement makes sure that the time between pushup-readings always stay the same
  
  buttonState = digitalRead(buttonPin); //these lines of code resets every integer and the lcd to the original state by the press of a button
  if (buttonState == HIGH) {
    i = 0;
    x = 1;
    y = 1;
    Serial.print("0      ");
    lcd.setCursor(0,1);
    lcd.print("0      "); } 
    
    lcd.setCursor(0, 1); // set cursor on the second row
  
  if (distance >= 10 ) {i ++;} //print a point if a pushup has been done
  Serial.print(i,DEC);
   lcd.print(i,DEC);                 
         
  while (distance >= 10) { //if the distance stays smaller then ten for a while, this piece of code makes sure that only one point is given for one pushup
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034/2;
  delay(100);
  }
}
