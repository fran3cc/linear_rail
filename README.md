### Linear Rail System Project Report

#### Steps to setup the raspi system
1. setup the wifi connection
2. install git, conda etc env
3. test the flask app on raspi
4. modify the startup process (look below for Appendix A)

#### Introduction
This report provides an overview of the newly designed linear rail system, focusing on its key components, operational flow, and specific technical considerations. The system utilizes a Raspberry Pi (RasPi) interfaced with an Arduino to control a stepper motor via a stepper driver. The integration is achieved through a Flask web application, which serves as the command and control interface. The linear motion is restricted and calibrated by switches located at both ends of the rail.

#### System Overview
The linear rail system operates by coordinating several hardware components through software control, enabling precise linear movement for various applications such as automation and robotics. Below is a detailed description of the components and their interconnectivity.

##### Components:
- **Raspberry Pi**: Acts as the central control unit running Flask to manage the web interface and handle the logical operations.
- **Arduino**: Interfaces with the stepper motor driver, receiving signals from the Raspberry Pi to control the motor's movements.
- **Stepper Motor Driver**: Receives signals from the Arduino to drive the stepper motor accordingly.
- **Stepper Motor**: Provides the actual linear motion along the rail.
- **Limit Switches**: Located at both ends of the rail, these switches provide boundary limits and calibration points for the motor's movement.

#### Connectivity and Control Flow
1. **Flask Application**: Hosted on the Raspberry Pi, it provides a user interface to control the stepper motor's position and receives user inputs for movement commands.
2. **Signal Transmission**: When a command is issued via Flask, the Raspberry Pi sends the appropriate signals to the Arduino.
3. **Arduino Programming**: Upon startup, the Raspberry Pi automatically flashes the Arduino with the necessary code to interpret and relay commands to the stepper motor driver.
4. **Stepper Driver Activation**: The Arduino processes commands and transmits them as voltage signals to the stepper motor driver, which then controls the motor’s movements.
5. **Calibration and Safety**: The limit switches are engaged to prevent the stepper motor from moving beyond the designated rail length, providing a safety cutoff and allowing for system recalibration.

#### Micro Stepping Control with the Stepper Driver

##### Overview
The stepper driver in our linear rail system features micro stepping capabilities, which allows for finer control over the stepper motor's movements. This functionality is critical for applications requiring precise positioning and smooth motion.

##### Integration with the Code
To fully utilize the micro stepping capabilities of the stepper driver, the software controlling the Arduino must include specific instructions that match the configuration settings of the driver. This ensures that the motor can execute movements at the desired resolution.

#### Technical Implementation
1. **Driver Configuration**: The stepper driver must be correctly configured to enable micro stepping. This typically involves setting specific pins on the driver to define the micro stepping resolution (e.g., full step, half step, quarter step).

2. **Code Synchronization**:
   - **Arduino Code**: The Arduino code needs to include commands that correspond to the micro stepping settings of the stepper driver. This ensures that each pulse sent from the Arduino correctly translates into the intended movement increment of the stepper motor.
   - **Raspberry Pi Coordination**: The Flask application on the Raspberry Pi should offer user controls that correspond to the micro stepping capabilities. This might include options for adjusting the step resolution in real-time based on user requirements.

3. **Calibration and Testing**: It is essential to calibrate and test the system to ensure that the micro stepping functionality works as expected. This involves running the motor through its paces at all configured step resolutions and verifying that the movement matches the expected increments.

#### Recommendations
- **Documentation and Configuration**: Ensure that the stepper driver's documentation is thoroughly reviewed to correctly set the micro stepping pins.
- **Software Updates**: Update both the Raspberry Pi and Arduino software to include options and support for adjusting and utilizing micro stepping settings.
- **Testing Protocol**: Develop a comprehensive testing protocol to check the stepper motor’s performance at various micro stepping settings to ensure accuracy and reliability in operation.

By addressing these additional details regarding micro stepping, the linear rail system can achieve greater precision and adaptability in its applications. The careful integration and testing of these features will enhance the overall functionality and performance of the system.

#### Technical Considerations
- **Voltage Compatibility**: The Arduino GPIO outputs a maximum of 3V, insufficient for the stepper driver that requires a minimum input of 4.5V. To address this, the following solutions are considered:
  - **Use of a MOSFET**: A MOSFET can be used to boost the 3V output from the Arduino to a higher voltage suitable for the stepper driver.
  - **Direct Raspberry Pi GPIO Control**: Alternatively, leveraging the Raspberry Pi’s GPIO, which can output a higher voltage, may eliminate the need for additional components like a MOSFET.

#### Conclusion
The linear rail system effectively integrates multiple technologies to achieve precise control over stepper motor-driven linear motion. By using a Flask application hosted on a Raspberry Pi and interfacing with an Arduino, the system provides a versatile and scalable solution for various linear motion applications. However, attention must be paid to voltage compatibility between the Arduino and the stepper driver to ensure reliable operation. Future improvements might include more robust voltage conversion solutions or direct integration of higher voltage GPIO options.

To modify the Raspberry Pi's startup process to automatically run a Flask application and flash Arduino code via UART, you can follow these steps:

#### Appendix A: Raspi Startup Modify
### Step 1: Prepare Your Flask Application
Ensure that your Flask application is fully developed and functional on your Raspberry Pi. Assume your Flask application is located at `/home/pi/myflaskapp/app.py`.

### Step 2: Create a Shell Script
Create a shell script on the Raspberry Pi that will execute on startup, which will start the Flask application and flash the Arduino.

1. Open a text editor and create a new shell script file:
   ```bash
   nano /home/pi/startup.sh
   ```
2. Add the following content to this script:
   ```bash
   #!/bin/bash
   # Start the Flask application
   export FLASK_APP=/home/pi/myflaskapp/app.py
   flask run --host=0.0.0.0

   # Flash Arduino via UART
   avrdude -p atmega328p -c arduino -P /dev/ttyAMA0 -b 115200 -U flash:w:/path/to/your/Arduino/code.hex
   ```
   Replace `/path/to/your/Arduino/code.hex` with the actual path to your Arduino firmware.

3. Save and close the file.
4. Make the script executable:
   ```bash
   chmod +x /home/pi/startup.sh
   ```

### Step 3: Configure the Script to Run at Boot
To ensure the script runs at startup, you need to add it to the Raspberry Pi’s crontab or use `rc.local`.

#### Using Crontab:
1. Open the crontab editor:
   ```bash
   crontab -e
   ```
2. Add the following line at the end of the crontab file:
   ```bash
   @reboot /home/pi/startup.sh
   ```
3. Save and exit the editor.

#### Using rc.local:
1. Open the `rc.local` file:
   ```bash
   sudo nano /etc/rc.local
   ```
2. Before the `exit 0` line, add the path to your script:
   ```bash
   /home/pi/startup.sh &
   ```
3. Save and exit the file.

### Step 4: Test Your Setup
Reboot your Raspberry Pi to ensure that the script runs correctly at startup. Check that the Flask app is running and that the Arduino is being flashed as expected.

By following these steps, your Raspberry Pi will automatically start the Flask application and flash the Arduino code via UART when powered on. This setup is ideal for projects requiring automation and minimal manual intervention.
