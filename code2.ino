#include <NewPing.h>

#include <AFMotor.h>

// Pin connections
const int trigPin = 2;    // Trigger pin of the ultrasonic sensor
const int echoPin = 3;    // Echo pin of the ultrasonic sensor
const int motor1Pin1 = 4; // Motor 1 control pin 1
const int motor1Pin2 = 5; // Motor 1 control pin 2
const int motor2Pin1 = 6; // Motor 2 control pin 1
const int motor2Pin2 = 7; // Motor 2 control pin 2

// Distance thresholds
const int obstacleThreshold = 20;   // Obstacle detection distance in centimeters
const int reverseDuration = 1000;   // Duration for the car to reverse in milliseconds
const int turnDuration = 1000;      // Duration for the car to turn in milliseconds

void setup() {
  // Initialize motor control pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure the distance to the nearest obstacle
  int distance = getDistance();
  
  // Check if an obstacle is detected within the threshold
  if (distance < obstacleThreshold) {
    // Stop the car
    stopCar();
    
    // Reverse the car
    reverseCar();
    
    // Turn the car
    turnCar();
  } else {
    // Move the car forward
    moveForward();
  }
}

int getDistance() {
  // Send a short ultrasonic pulse to start the measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);
  
  // Convert the duration to distance
  int distance = duration * 0.034 / 2;  // Divide by 2 for round trip
  
  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  return distance;
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stopCar() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void reverseCar() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  delay(reverseDuration);
  
  stopCar();
}

void turnCar() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  delay(turnDuration);
  
  stopCar();
}
