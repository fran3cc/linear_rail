from flask import Flask, request, jsonify
import RPi.GPIO as GPIO
import time

app = Flask(__name__)

# GPIO Pins setup, adjust according to your wiring
dirPin = 17
stepPin = 27
enablePin = 22

# Stepper motor parameters
stepsPerRevolution = 200
microsteps = 4
stepsPerCircle = stepsPerRevolution * microsteps

# Setup GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(dirPin, GPIO.OUT)
GPIO.setup(stepPin, GPIO.OUT)
GPIO.setup(enablePin, GPIO.OUT)
GPIO.output(enablePin, GPIO.HIGH)  # Disable stepper motor by default

def move_stepper(currentPos, targetPos, rpm):
    moveDistance = targetPos - currentPos
    stepsToMove = int(moveDistance * stepsPerCircle)
    
    stepDelay = (60.0 * 1000000.0) / (rpm * stepsPerRevolution * microsteps)  # in microseconds
    
    GPIO.output(enablePin, GPIO.LOW)  # Enable stepper motor
    
    if stepsToMove < 0:
        GPIO.output(dirPin, GPIO.LOW)
        stepsToMove = -stepsToMove
    else:
        GPIO.output(dirPin, GPIO.HIGH)
    
    for i in range(stepsToMove):
        GPIO.output(stepPin, GPIO.HIGH)
        time.sleep(stepDelay / 2000000.0)  # Convert to seconds and divide by 2 for HIGH and LOW
        GPIO.output(stepPin, GPIO.LOW)
        time.sleep(stepDelay / 2000000.0)
    
    GPIO.output(enablePin, GPIO.HIGH)  # Disable stepper motor after movement

@app.route('/move', methods=['POST'])
def move():
    data = request.get_json()
    currentPos = data.get('currentPos', 0)
    targetPos = data.get('targetPos', 0)
    rpm = data.get('rpm', 0)
    
    move_stepper(currentPos, targetPos, rpm)
    
    return jsonify({"message": "Position reached"}), 200

if __name__ == '__main__':
    try:
        app.run(host='0.0.0.0', port=5000, debug=True)
    finally:
        GPIO.cleanup()
