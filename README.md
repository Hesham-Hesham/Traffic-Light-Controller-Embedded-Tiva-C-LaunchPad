#  Traffic Light Control System - Tiva C LaunchPad

This project comprises of a traffic light control system that manages two car traffic lights (North-South and East-West) and two pedestrian traffic lights, one for each car traffic light. The system is equipped with push buttons for pedestrians to press and safely cross the street.
The project leverages the TM4C123GH6PM LaunchPad evaluation kit which is based on the Arm Cortex-M4F microcontroller. This system is also designed based on a layered architecture model for maxiumum efficiency and modular functionality.

## Table of Contents

- [System Overview](#system-overview)
- [Requirements](#requirements)
- [Drivers Requirements](#drivers-requirements)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Usage](#usage)


## Key Features

Interrupt Handling: The system can handle interruptions caused by pedestrian crossings without disrupting the overall traffic flow.
1. Pedestrian Crossing:
- Push Button Activation: Pedestrian lights are activated by push buttons. Pressing the button interrupts the active car traffic light and initiates the pedestrian crossing phase.
- Time Management: Pedestrian lights remain Green for 2 seconds, allowing safe crossing. After this period, they turn Red, and the interrupted car traffic light resumes its sequence.

2. Delayed Crossing:
- Intelligent Delay: If the pedestrian button is pressed within 1 second of the end of the pedestrian crossing period, the system intelligently delays the pedestrian request, ensuring synchronization with the traffic light sequence.

## Requirements

For the full detailed system sequence and components requirements, check [The Project requirements file](https://github.com/Hesham-Hesham/Traffic-Light-Controller-Embedded-Tiva-C-LaunchPad/blob/main/Requirements.pdf)

## Drivers Requirements

### HAL
- LEDs Driver
- Push Buttons Driver
- Delay Driver

### MCAL

- External Interrupts Driver
- GPIO Driver
- Systick Timer Driver


### Layered Architecture
- 

## Components


1. **Tiva C LaunchPad Evaluation Kit:**
   - To be used for its GPIO pins, timers, and interrupt capabilities.

2. **LEDs:**
   - Red, yellow, and green LEDs for both car traffic lights (2 sets) + Red and green LEDs for pedestrian traffic lights (2 sets).

3. **Push Buttons:**
   - Two push buttons for pedestrian crossings, one for each direction.

4. **Resistors:**
   - Current-limiting resistors for the LEDs to prevent them from 

5. **Power Supply:**
   - A stable power supply (a 9V battery) for the LEDs.

6. **BC549 Transistors:**  
    - Used as gates for the LED current. (Check the electric circuit section)

7. **Voltage Regulator:**
    - To provide a stable 5V to the systems




## Circuit Diagram



<br/><br/>

---


