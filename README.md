# Balancing Robot

This repository contains the code for a self-balancing robot project using Arduino and an MPU6050 sensor. The robot's main goal is to maintain its balance by adjusting the motor speeds based on the tilt angle measured by the MPU6050 sensor.

## Dependencies

Before running the code on your Arduino board, make sure you have the following libraries installed:

- LMotorController: This library provides functions to control the motors of the robot.
- I2Cdev: A library for I2C communication with the MPU6050 sensor.
- MPU6050_tockn: This library enables easy interfacing with the MPU6050 sensor.

## Hardware Requirements

1. Arduino board
2. MPU6050 sensor
3. Motor driver (LMotorController)
4. Two DC motors with encoders
5. Wheels and chassis for the robot

## Circuit Diagram

![Circuit Diagram](/path/to/circuit_diagram.png)

[Include a circuit diagram here, showing how the Arduino, MPU6050, motor driver, and motors are connected.]

## Installation and Setup

1. Clone this repository to your local machine or download the ZIP file and extract it.
2. Make sure you have installed the required libraries as mentioned in the Dependencies section.
3. Connect the hardware components as shown in the Circuit Diagram section.
4. Open the `main.ino` file using the Arduino IDE.
5. Compile the code and upload it to your Arduino board.

## Configuration

The following constants can be adjusted in the `main.ino` file to fine-tune the robot's behavior:

- `min_speed`: The minimum motor speed (PWM value) allowed for the robot's movement.
- `max_speed`: The maximum motor speed (PWM value) allowed for the robot's movement.
- `motorSpeedFactorLeft`: A scaling factor for the left motor's speed. This can be adjusted to balance the robot's movement.
- `motorSpeedFactorRight`: A scaling factor for the right motor's speed. This can be adjusted to balance the robot's movement.
- `Kp`, `Ki`, and `Kd`: The proportional, integral, and derivative constants for the PID control loop. These values control how the robot responds to tilt angle changes and can be tweaked for optimal performance.

## How It Works

The robot uses the MPU6050 sensor to measure its tilt angle along the X-axis. Based on this angle, a PID control loop is used to adjust the motor speeds and keep the robot balanced. If the robot's tilt angle is within a specific range (near vertical), it stops moving to prevent falling. Otherwise, the PID controller calculates the appropriate motor speed to maintain balance.

## Contributing

Contributions to this project are welcome. If you find any bugs or have suggestions for improvement, please feel free to open an issue or submit a pull request.

## License

[Include the license information for the project here. For example, if the code is under an open-source license like MIT or Apache 2.0, mention that here with a link to the license file.]
