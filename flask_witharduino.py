from flask import Flask, request, jsonify
import serial
import struct
import os

app = Flask(__name__)

# Serial port configuration
ser = serial.Serial('/dev/cu.usbserial-A10N2CGN', 9600, timeout=1)
ser.flush()

position_file = 'position.txt'  # Position storage file

def init_or_load_position():
    if not os.path.exists(position_file):
        with open(position_file, 'w') as f:  # Change 'wb' to 'w' for text mode
            f.write('0')  # Write position as text
    with open(position_file, 'r') as f:  # Change 'rb' to 'r' for text mode
        return int(f.read())  # Convert text back to integer

def update_position(new_position):
    with open(position_file, 'w') as f:  # Change 'wb' to 'w' for text mode
        f.write(str(new_position))  # Convert position to string and write

@app.route('/')
def index():
    return "Welcome to the Stepper Motor Control API!"

@app.route('/control', methods=['POST'])
def control_motor():
    data = request.json
    target_position = data.get('position', 0)
    speed = data.get('speed', 0)
    current_position = init_or_load_position()
    print("current position: {current_position}")
    print("target position: {target_position}")
    
    message = f"{current_position},{target_position},{speed}\n" #current rev, target rev, speed(rpm)
    ser.write(message.encode('utf-8'))
    print("waiting for the position to be update")
    
    
# Wait for the "position reached" message from Arduino
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line == "position reached":
                break  # Exit the loop when the expected message is received
            else:
                print("Received unexpected message: " + line)
                
    update_position(target_position)
    
    return jsonify({"status": target_position, "message": "position changed successfully!"})

if __name__ == '__main__':
    app.run(debug=True, host='127.0.0.1', port=5000)

