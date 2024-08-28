#include <Servo.h>

const int trigPin1 = 9;   // Trigger pin for sensor 1 (outside)
const int echoPin1 = 10;  // Echo pin for sensor 1 (outside)
const int trigPin2 = 7;   // Trigger pin for sensor 2 (inside)
const int echoPin2 = 8;   // Echo pin for sensor 2 (inside)
const int servoPin = 3;   // Servo motor pin
Servo servo;

long duration1, duration2;
int distance1, distance2;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  servo.attach(servoPin);
  servo.write(0); // Initial position (closed lid)
  Serial.begin(9600);
}

void loop() {
  // Send pulse for sensor 1 (outside)
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the echo time for sensor 1
  duration1 = pulseIn(echoPin1, HIGH);
  
  // Calculate the distance for sensor 1
  distance1 = duration1 * 0.034 / 2;

  // Send pulse for sensor 2 (inside)
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Read the echo time for sensor 2
  duration2 = pulseIn(echoPin2, HIGH);
  
  // Calculate the distance for sensor 2
  distance2 = duration2 * 0.034 / 2;

  // Print distances to Serial Monitor
  Serial.print("Outside Distance: ");
  Serial.print(distance1);
  Serial.print(" cm, Inside Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Check if an object is within 30 cm for sensor 1 (outside)
  if (distance1 <= 30) {
    servo.write(270);  // Open lid
    delay(2000);       // Wait 2 seconds (adjust as needed)
    servo.write(90);   // Close lid
  }

  // Check if the trash is filled up to 15 cm from the bottom
  if (distance2 <= 15) {
    Serial.println("Alert: Trash bin is full!");
    
  }

  delay(100);
}

