#include <Arduino.h>

const int dirPin = 2;   // Direction control pin
const int stepPin = 4;  // Step (pulse) control pin
const int enablePin = 7; // Enable control pin

const float stepsPerRevolution = 200; // Adjust this based on your stepper motor's steps per revolution
// Assuming microstepping setting on the driver, adjust the microstep setting below
const float microsteps = 16; // Example: 16 microsteps per step for the driver setting
const float stepsPerCircle = stepsPerRevolution * microsteps; // Total steps per circle considering microstepping

void setup() {
  Serial.begin(9600);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH); // Disable stepper motor by default
}

void loop() {
  if (Serial.available()) {
    long currentPos = Serial.parseInt(); // Read current position in circles
    long targetPos = Serial.parseInt();  // Read target position in circles
    int rpm = Serial.parseInt();         // Read speed in RPM
    
    long moveDistance = targetPos - currentPos; // Calculate move distance in circles
    long stepsToMove = moveDistance * stepsPerCircle; // Convert distance to steps
    
    // Calculate delay between steps for desired RPM
    float stepDelay = (60.0 * 1000000.0) / (rpm * stepsPerRevolution * microsteps);

    // Enable stepper motor
    digitalWrite(enablePin, LOW);
    
    // Set direction
    if (stepsToMove < 0) {
      digitalWrite(dirPin, LOW);
      stepsToMove = -stepsToMove; // Make steps to move positive
    } else {
      digitalWrite(dirPin, HIGH);
    }
    
    // Move the stepper motor
    for (long i = 0; i < stepsToMove; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepDelay / 2);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepDelay / 2);
    }
    
    // Optionally, disable the stepper motor after movement to save power
    digitalWrite(enablePin, HIGH);
    
    // Wait for a bit before the next command
    delay(1000);
  }
}
