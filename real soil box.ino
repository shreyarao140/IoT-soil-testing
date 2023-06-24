#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  


// NPK TEMP MOISTURE

int N_PIN = A0; // Connect N sensor to Analog Pin A0
int P_PIN = A1; // Connect P sensor to Analog Pin A1
int K_PIN = A2; // Connect K sensor to Analog Pin A2

#define soilWet 50   // Define max value we consider soil 'wet'
#define soilDry 75   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 7
#define sensorPin A3

#include <OneWire.h>
#include <DallasTemperature.h>

const int SENSOR_PIN = 13; // Arduino pin connected to DS18B20 sensor's DQ pin

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library

float tempCelsius;    // temperature in Celsius
float tempFahrenheit; 

void setup() {

    lcd.init();
  lcd.clear();         
  lcd.backlight();

  
  Serial.begin(9600); 
  tempSensor.begin(); // Initialize serial communication
}

void loop() {
  float N_value = analogRead(N_PIN); // Read the analog value from N sensor
  float P_value = analogRead(P_PIN); // Read the analog value from P sensor
  float K_value = analogRead(K_PIN); // Read the analog value from K sensor

  float N_voltage = (N_value * 5.0) / 1023.0; // Convert analog value to voltage for N sensor
  float P_voltage = (P_value * 5.0) / 1023.0; // Convert analog value to voltage for P sensor
  float K_voltage = (K_value * 5.0) / 1023.0; // Convert analog value to voltage for K sensor

  float N_ppm = (N_voltage - 0.4) * 250; // Convert voltage to ppm for N sensor
  float P_ppm = (P_voltage - 0.4) * 250; // Convert voltage to ppm for P sensor
  float K_ppm = (K_voltage - 0.4) * 250; // Convert voltage to ppm for K sensor

  Serial.print("N: ");
  Serial.print(N_ppm);
  Serial.print(" ppm, P: ");
  Serial.print(P_ppm);
  Serial.print(" ppm, K: ");
  Serial.print(K_ppm);
  Serial.println(" ppm");
  lcd.setCursor(0,0);
  lcd.print("N:");
  lcd.setCursor(2,0);
  lcd.print(N_ppm);  
  lcd.print(" ppm");
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(P_ppm);
  lcd.print(" ppm");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("K:");
  lcd.print(K_ppm);
  lcd.print(" ppm");
  delay(1000);
  lcd.clear();

  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  tempFahrenheit = tempCelsius * 9 / 5 + 32; // convert Celsius to Fahrenheit

  Serial.print("Temperature: ");
  Serial.print(tempCelsius);    // print the temperature in Celsius
  Serial.print("°C");
  Serial.print("  ~  ");        // separator between Celsius and Fahrenheit
  Serial.print(tempFahrenheit); // print the temperature in Fahrenheit
  Serial.println("°F");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(tempCelsius);
  lcd.print("C");

  delay(1000);
  //get the reading from the function below and print it
  int moisture = readSensor();
  Serial.print("Moisture: ");
  Serial.println(moisture);
  lcd.setCursor(0,0);
  lcd.print("Moisture: ");
  lcd.print(moisture);
  
  // Determine status of our soil
  if (moisture < soilWet) 
  {
    Serial.println("Status: Soil is too wet");
  } else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Status: Soil moisture is perfect");
  } else {
    Serial.println("Status: Soil is too dry - time to water!");
  }
  
  delay(1000);  // Take a reading every second for testing
          // Normally you should take reading perhaps once or twice a day
  Serial.println();
}

//  This function returns the analog soil moisture measurement
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // Allow power to settle
  int val = analogRead(sensorPin);  // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // Return analog moisture value
}
