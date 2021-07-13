#include <VarSpeedServo.h> // download this libragy from external source "google it "
// Pins initialization
#define echoPin 8 // ultrasonic sensor pins configuration "echo and trigger"
#define trigPin 10
#define echoPin1 11
#define trigPin1 7
#define led1Pin 4
#define led2Pin 5
#define led3Pin 6
#define servoPin 9

VarSpeedServo servo; // Servo object for servo control with variable speed

void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  servo.attach(servoPin); // initialize servo to output pin
  servo.write(0); // default position of servo

  Serial.begin (9600); // Set 9600 baud rate in serial monitor
}

int detect_hand() // returns distance between hand and dustbin in centimeter
{ long duration;
  int hand_distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  hand_distance = (duration / 2) / 29.1;
  return hand_distance;
}

int detect_garbage() // returns garbage level in centimeter
{
  long duration;
  int garbage_level;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  garbage_level = (duration / 2) / 29.1;
  return garbage_level;
}
void loop()
{
  int garbage_level = detect_garbage(); // get hthe sensor data 
  int hand_distance = detect_hand();
  // print data in serial monitor
  Serial.println("Hand distance: " + String(hand_distance) + " Garbage Level: " + String(garbage_level) );

  // these numeric values are in centimeter "cm" and represents object distance from the sensor
  // comparison for garbage level detection
  {
  if (garbage_level <= 15 && garbage_level > 10) 
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
    Serial.println("One led on");
  }
  else if (garbage_level <= 10 && garbage_level > 4)
  {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    Serial.println("Two led on");
  }
  else if (garbage_level <= 4 && garbage_level > 0) // glow 3 leds
  {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    Serial.println("Three led on");
  }
  else
  {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    Serial.println("Led off");
  }

  // opens lid when somethig is closer then 30 cm from the dustbin top
  if ( hand_distance < 30 )
  {
    servo.write(100, 70);
    delay(5000);
    Serial.println("Lid up");
  }
  else
  {
    servo.write(0, 50);
    Serial.println("Lid down");
  }
}