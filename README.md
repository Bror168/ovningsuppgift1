# Arduino OLED & Servo Temperature and Time Display

This Arduino project uses an OLED display, DS3231 real-time clock (RTC), and a servo motor to create a dynamic display. The project allows you to toggle between two modes:
1. Displaying the current time on the OLED and mapping temperature readings to the servo position.
2. Displaying temperature on the OLED and mapping the current time (seconds) to the servo position.

## Table of Contents
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
- [Code Overview](#code-overview)
- [Usage](#usage)
- [License](#license)

## Hardware Requirements
- Arduino (Uno, Nano, etc.)
- DS3231 Real-Time Clock (RTC) module
- SSD1306 OLED Display (128x64 pixels, I2C)
- Servo motor (connected to pin 2)
- Thermistor (connected to analog pin A1)
- Push button (connected to pin 8)

## Software Requirements
- Arduino IDE
- **Libraries**:
  - [U8glib](https://github.com/olikraus/u8glib) (for OLED display)
  - [RTClib](https://github.com/adafruit/RTClib) (for RTC DS3231)
  - [Servo](https://www.arduino.cc/en/Reference/Servo) (for servo motor)

## Setup Instructions
1. **Connect the OLED display** to the Arduino using I2C (SDA to A4, SCL to A5 on an Uno).
2. **Connect the DS3231 RTC** module via I2C.
3. **Attach the servo motor** to digital pin 2.
4. **Connect the thermistor** to analog pin A1, with a 10kΩ resistor for voltage division.
5. **Connect the button** to digital pin 8, with a pull-down or pull-up resistor as needed.

## Code Overview
The project code is organized as follows:

- **Mode Toggling**: A button press toggles between two display modes:
  - **Mode 1**: Displays the time on the OLED, and maps temperature to the servo angle.
  - **Mode 2**: Displays temperature on the OLED, and maps seconds (time) to the servo angle.
  
- **Display Functions**:
  - `text(int x, int y, String ord)`: Displays text on the OLED.
  
- **Temperature Calculation**:
  - `temp()`: Reads temperature in Celsius from the thermistor using a Steinhart-Hart equation.

- **Servo Angle Mapping**:
  - `vo()`: Maps temperature to a servo position between 0° and 180°.

## Usage
1. Upload the code to your Arduino.
2. Press the button connected to pin 8 to toggle between display modes:
   - **Mode 1**: Shows time on the OLED and temperature on the servo.
   - **Mode 2**: Shows temperature on the OLED and time on the servo.
3. The servo position will update based on either temperature (in Mode 1) or seconds (in Mode 2), with the OLED displaying relevant information.

## Example Output
**Mode 1**: OLED displays current time, while the servo points to the temperature.
