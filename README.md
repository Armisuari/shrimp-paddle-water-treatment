# Shrimp Pond Water Treatment - IoT Monitoring and Control System

Welcome to the README repository for the Shrimp Pond Water Treatment project, an IoT system designed for monitoring water quality parameters, managing water levels, and optimizing shrimp paddle control in a shrimp pond. This project is built on the ESP32 platform and utilizes fuzzy algorithms for decision-making. The system consists of two main components: the Water Quality Monitoring Device and the Shrimp Paddle Control Device.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Hardware Components](#hardware-components)
4. [Software Components](#software-components)
5. [Integration with ThingsBoard IoT Platform](#integration-with-thingsboard-iot-platform)
6. [Installation and Setup](#installation-and-setup)
7. [Usage](#usage)
8. [Configuration](#configuration)
9. [Communication Protocol](#communication-protocol)
10. [Contributing](#contributing)
11. [License](#license)

## 1. Introduction

The Shrimp Pond Water Treatment project aims to create an intelligent and efficient system for monitoring water quality in a shrimp pond. The system leverages IoT technologies to provide real-time data on Dissolved Oxygen (DO), pH, Electrical Conductivity (EC), Temperature, and water height levels. Based on this data, the system employs fuzzy algorithms to trigger notifications for water changes and optimize the state of the shrimp paddle.

## 2. Features

- Real-time monitoring of water quality parameters (DO, pH, EC, Temperature, and water height).
- Fuzzy logic-based decision-making for water change notifications.
- Shrimp paddle control based on fuzzy logic and DO levels.
- Local communication between devices via TCP/IP on the ESP32 platform.
- Push notifications for water change alerts.
- Integration with ThingsBoard IoT Platform for remote monitoring and manual control.

## 3. Hardware Components

### Water Quality Monitoring Device
- ESP32 microcontroller.
- Sensors for DO, pH, EC, Temperature.
- Ultrasonic sensor for water height measurement.
- Wi-Fi module for internet connectivity.
- Power supply components.

### Shrimp Paddle Control Device
- ESP32 microcontroller.
- Shrimp paddle control mechanism.
- Wi-Fi module for internet connectivity.
- Power supply components.

## 4. Software Components

The project consists of two main software components:

### Water Quality Monitoring Device
- Firmware for ESP32.
- Data acquisition and processing.
- Fuzzy logic algorithms for water change alerts.

### Shrimp Paddle Control Device
- Firmware for ESP32.
- Shrimp paddle control logic.
- Fuzzy logic algorithms for optimizing shrimp paddle state.

## 5. Integration with ThingsBoard IoT Platform

Both the Water Quality Monitoring Device and the Shrimp Paddle Control Device are integrated with the ThingsBoard IoT Platform. This integration allows you to:

- Monitor real-time data on water quality parameters and shrimp paddle status remotely through the ThingsBoard dashboard.
- Perform manual control of the shrimp paddle state via the dashboard.
- Set up alarms and notifications within ThingsBoard based on the received data.
- Collect historical data for analysis and decision-making.

## 6. Installation and Setup

1. Clone this repository.
2. Configure the hardware components as per the provided schematics.
3. Flash the ESP32 devices with their respective firmware.
4. Set up Wi-Fi connectivity.
5. Configure device communication settings.
6. Connect the devices to the ThingsBoard IoT Platform.

## 7. Usage

1. The Water Quality Monitoring Device will continuously collect data.
2. The Shrimp Paddle Control Device will adjust the paddle state based on the DO levels.
3. Monitor and control the devices remotely using the ThingsBoard IoT Platform.

## 8. Configuration

- Configuration files and settings can be found in the respective firmware directories.
- Adjust thresholds and fuzzy logic rules as needed for your specific shrimp pond conditions.
- Configure ThingsBoard integration settings in the firmware.

## 9. Communication Protocol

The two devices communicate using a custom TCP/IP-based protocol. Refer to the documentation for details on message formats and commands.
