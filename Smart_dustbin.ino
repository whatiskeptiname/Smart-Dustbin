#include <VarSpeedServo.h>

#define echoPin 8
#define trigPin 10
#define echoPin1 11
#define trigPin1 7
#define led1Pin 4
#define led2Pin 5
#define led3Pin 6
#define servoPin 9

VarSpeedServo servo;

long duration, dist, distance;

void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  servo.attach(servoPin);
  servo.write(0);

  Serial.begin (9600);
}

void measure()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;
}

void measure1()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = (duration / 2) / 29.1;
}
void loop()
{
  measure();
  measure1();
  Serial.println("Hand distance: " + String(dist) + " Garbage Distance: " + String(distance) );

  if (distance <= 15 && distance > 10)
  {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
    Serial.println("One led on");
  }
  else if (distance <= 10 && distance > 4)
  {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    Serial.println("Two led on");
  }
  else if (distance <= 4 && distance > 0)
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
  if ( dist < 30 )
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
