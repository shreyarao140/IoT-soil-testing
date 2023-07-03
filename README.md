# IoT-soil-testing

This project utilizes an Arduino board to monitor and display sensor readings on an LCD screen. The code is designed to work with the following sensors:

- NPK (Nitrogen, Phosphorus, Potassium) sensors for soil analysis
- DS18B20 temperature sensor
- Soil moisture sensor

The sensor readings are displayed on a 16x2 LCD screen, providing real-time information about the soil's nutrient levels, temperature, and moisture content.

## Hardware Requirements

To run this project, you will need the following components:

- Arduino board (e.g., Arduino Uno)
- NPK sensors (connected to analog pins A0, A1, and A2)
- DS18B20 temperature sensor (connected to digital pin 13)
- Soil moisture sensor (connected to analog pin A3)
- 16x2 LCD screen (compatible with the LiquidCrystal_I2C library, connected via I2C)

Make sure to properly wire the sensors and LCD screen to the Arduino board before uploading the code.

## Libraries Used

This project utilizes the following libraries:

- LiquidCrystal_I2C: for controlling the LCD screen.
- OneWire: for interfacing with the DS18B20 temperature sensor.
- DallasTemperature: for reading temperature values from the DS18B20 sensor.

Please ensure that these libraries are properly installed in your Arduino IDE before uploading the code.

## Getting Started

1. Connect the sensors and LCD screen to the Arduino board according to the hardware requirements section.
2. Open the Arduino IDE and upload the code to your Arduino board.
3. Open the serial monitor to view the sensor readings (baud rate: 9600).
4. The LCD screen will display the NPK values, temperature, and soil moisture readings in a loop.
5. Interpret the sensor readings and take necessary actions based on the displayed information.

Note: Adjust the values of the `soilWet` and `soilDry` variables according to your soil's moisture levels.

## Contributing

Contributions to this project are welcome. If you find any issues or have any improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- The code was developed based on examples and tutorials from the Arduino community and various sensor manufacturers.
