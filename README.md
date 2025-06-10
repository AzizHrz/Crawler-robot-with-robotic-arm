# Crawler Robot with Robotic Arm

This repository contains the Arduino code for the "Crawler Robot with Robotic Arm" project, engineered as a remotely controlled robot via RF (nRF24L01) to access small, risky zones during natural disasters. Designed to navigate challenging terrains using two motors (one per crawler side) and manipulate objects with a stepper motor and servo motor, this project showcases a smart, efficient solution. Despite limited financial resources and hardware, we’ve crafted an optimized design to maximize performance with available tools.

## Features
- Controls robot navigation with two motors, each driving a crawler side (left and right).
- Operates a stepper motor (NEMA17) and servo motor for robotic arm functionality.
- Utilizes wireless communication via the NRF24L01 module for remote control.
- Supports PS1/PS2 controller inputs for intuitive operation.
- Implements PWM and digital control for precise motor movements.

## Benefits of NRF24L01
- **Low Power Consumption**: Ideal for battery-powered projects, extending operational time.
- **Wireless Range**: Offers a reliable range.
- **Cost-Effective**: Affordable solution for wireless communication, fitting within budget constraints.
- **Multi-Channel Support**: Enables multiple robots or controllers to operate simultaneously without interference.
- **Ease of Integration**: Seamlessly integrates with Arduino using the Mirf library, simplifying development.

## Hardware Requirements
- Arduino board (e.g., Arduin Mega)
- PS1/PS2 controller
- Two DC motors (one per crawler side)
- NEMA17 stepper motor
- Servo motor
- Two NRF24L01 modules (one for transmitter, one for receiver)
- L298N and L293d or similar motor driver for DC motors
- Jumper wires, breadboard, and power supply (e.g., battery pack)

## Pin Configuration
- **NRF24L01 Pins:**
  - `csnPin`: 49
  - `cePin`: 48
  - and default SPI pins for your board (MISO, MOSI, SCK)
- **Servo Motor:**
  - `Servo_PWM`: 10
- **Stepper Motor (NEMA17):**
  - `i1`: A8
  - `i2`: A9
  - `i3`: A10
  - `i4`: A11
- **Motor R (Right Crawler):**
  - `Ren`: 3
  - `Rin1`: A0
  - `Rin2`: A1
- **Motor L (Left Crawler):**
  - `Len`: 2
  - `Lin1`: A2
  - `Lin2`: A3
- **Center Motor (Robotic Arm):**
  - `Cen`: 6
  - `Cin`: 4

## Installation
1. Install the Arduino IDE.
2. Install the following libraries via the Library Manager or manually:
   - `Mirf` (for NRF24L01)
   - `nRF24L01`
   - `MirfHardwareSpiDriver`
   - `Servo`
   - `Stepper`
3. Connect the hardware according to the pin configuration.
4. Upload the code to your Arduino board.
5. Pair the NRF24L01 modules (transmitter and receiver).

## Usage
- Connect the PS1/PS2 controller to the transmitter Arduino with an NRF24L01 module.
- Power the robot with the receiver Arduino and attached motors.
- Use the following PS1/PS2 controller inputs:
  - **D-Pad Up**: Move forward
  - **D-Pad Down**: Move backward
  - **D-Pad Left**: Turn left
  - **D-Pad Right**: Turn right
  - **Square ([])**: Activate axial motor clockwise
  - **X**: Rotate stepper motor clockwise
  - **Circle (O)**: Activate center motor counterclockwise
  - **Triangle (/\)**: (Reserved for future use)
  - **R1**: (Reserved for future use)
  - **L1**: (Reserved for future use)
  - **R2**: (Reserved for servo down adjustment)
  - **L2**: (Reserved for servo up adjustment)
- The robot stops when no commands are received for 100ms.

## Challenges and Approach
- **Limited Resources**: We lack the financial means and full hardware suite, so we optimize existing components and leverage open-source solutions.
- **Innovative Design**: The use of NRF24L01 and repurposed motors demonstrates a commitment to creating a functional robot despite constraints.

## Dependencies
- `Mirf.h` and `nRF24L01.h` for wireless communication
- `Servo.h` for servo motor control
- `Stepper.h` for stepper motor control

