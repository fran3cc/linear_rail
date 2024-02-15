// #include <Arduino.h>

// const int dirPin = 2;
// const int stepPin = 4;
// const int enablePin = 7;

// const float stepsPerRevolution = 200;
// const float microsteps = 4;
// const float stepsPerCircle = stepsPerRevolution * microsteps;

// void setup() {
//   Serial.begin(9600);
//   pinMode(dirPin, OUTPUT);
//   pinMode(stepPin, OUTPUT);
//   pinMode(enablePin, OUTPUT);
//   digitalWrite(enablePin, HIGH); // Disable stepper motor by default
// }

// void loop() {
//   if (Serial.available() > 0) {
//     long currentPos = Serial.parseInt();
//     long targetPos = Serial.parseInt();
//     int rpm = Serial.parseInt();
    
//     Serial.flush(); // Clear the serial buffer to ensure no leftover data
    
//     long moveDistance = targetPos - currentPos;
//     long stepsToMove = moveDistance * stepsPerCircle;
    
//     float stepDelay = (60.0 * 1000.0) / (rpm * stepsPerRevolution * microsteps);
    
//     digitalWrite(enablePin, LOW);
    
//     if (stepsToMove < 0) {
//       digitalWrite(dirPin, LOW);
//       stepsToMove = -stepsToMove;
//     } else {
//       digitalWrite(dirPin, HIGH);
//     }
    
//     for (long i = 0; i < stepsToMove; i++) {
//       digitalWrite(stepPin, HIGH);
//       delayMicroseconds(stepDelay / 2);
//       digitalWrite(stepPin, LOW);
//       delayMicroseconds(stepDelay / 2);
//     }
    
//     digitalWrite(enablePin, HIGH);
    
//     Serial.println("position reached"); // Send confirmation message
    
//     delay(1000); // Optional delay before processing next command
//   }
// }


void setup() {
  // 将数字引脚8设置为输出模式
  pinMode(4, OUTPUT);
}

void loop() {
  // 将引脚8设置为高电平，输出5V
  digitalWrite(4, HIGH);
  
  // 这里没有其他的循环代码，所以引脚8会一直保持在5V
}
