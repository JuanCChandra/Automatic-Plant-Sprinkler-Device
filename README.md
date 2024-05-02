# Automatic Plant Sprinkler Device

This project is a simulation tool for automatic plant watering using a microcontroller and sensors. Here, I use Arduino and a micro servo as a substitute for a water pump. So, when the micro servo position changes, it indicates whether the water pump is on or off. In this tool, the condition for watering the soil depends on soil moisture and temperature. So, when the soil moisture and temperature meet the preset conditions, this tool will water the soil (the micro servo will change position). Additionally, there are 2 LED lights (1 representing moisture and 1 representing temperature) as indicators that will light up when the conditions of soil moisture or temperature are met. This tool also has an LCD that displays the current conditions. Furthermore, there is a push button for manual watering.

Here are the tools used:
1. Sensors: 1 Moisture Sensor, 1 Temperature Sensor
2. Actuators: 1 Micro Servo, 2 LED Lights
3. Circuit components: 2 Arduinos, 1 Breadboard, 2 Resistors 220Ω, 1 Push Button, 1 LCD I2C, 25 Jumper Wires

This tool uses 2 Arduinos, one Master Arduino and one Slave Arduino. Additionally, there is also a database using SQL to store data such as temperature, humidity, servo position, and LED light conditions every second.

How the tool works:
1. The temperature sensor and soil moisture sensor will obtain data received by the Master Arduino. After that, the data obtained from the temperature sensor will be converted into degrees Celsius and the data obtained from the soil moisture sensor will be converted into the percentage of soil moisture level. Then, the processed data will be sent to the Slave Arduino via I2C communication.
2. After the data is received by the Slave Arduino, if the temperature and humidity levels meet the predetermined watering criteria (in this case, the watering criteria are when the temperature ranges from > 15°C to < 30°C and the humidity level is below 50%), then the servo will move from position 0° to position 90° (the servo is used as a water pump simulation. When the servo is at 90°, it means the water pump is running).
3. To know that the watering criteria have been met, the LED connected to the Slave Arduino will light up. The green LED lights up to represent the fulfillment of the temperature criteria and the red LED lights up to represent the fulfillment of the humidity level criteria.
4. The current temperature status, humidity level, and servo position are displayed through the LCD I2C.
5. Then, if you want to water manually, you can press the push button connected to the Master Arduino.

Here is the Tinkercad link for the circuit simulation: https://www.tinkercad.com/things/4vsM53XRPHj
