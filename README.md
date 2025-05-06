# Drawbot - Robot Control Code
# Project Description
- This repository contains the code for Drawbot, a robot that executes drawing sequences (staircase, circle, compass arrow) using a NodeMCU ESP32. The code implements:
- Closed-loop motor control (PID) with encoder feedback.
- Sensor integration (IMU and magnetometer) for navigation.
- Wireless command parsing (e.g., MOVE 20cm, TURN 90deg).

# Key Features
- Motor Control

> PID tuning for precise wheel positioning (motor_control.ino).

 > Encoder pulse counting for distance/angle tracking.
# Wireless Commands

> UART/Bluetooth/Wi-Fi input parsing (commands.ino).

> Example: CIRCLE 10cm draws a 10cm-radius circle.

# Sensor Fusion

> IMU (LSM6DS3) for tilt compensation.

> Magnetometer (LIS3MDL) for north alignment (compass.ino).
