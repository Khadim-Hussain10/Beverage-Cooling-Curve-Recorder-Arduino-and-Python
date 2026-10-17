#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Creating LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Data wire from Temp Sensor is plugged into digital pin 2
#define ONE_WIRE_BUS 2

// Thresholds
float start_threshold = 55.0;
float stop_threshold = 36.0;

// Setup a oneWire instance
OneWire oneWire(ONE_WIRE_BUS);

// Passing oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// Creating Variables
int trial_number = 1;          // Start at trial 1
int total_trials = 5;          // Total number of trials
bool logging_started = false;  // Data logging
unsigned long start_time = 0;  // Variable to track trial start time

void setup(void)
{
  sensors.begin();
  lcd.begin(16, 2);    // Initialize LCD
  lcd.backlight();     // Turn on backlight
  Serial.begin(9600);  // Start serial communication for user input

  Serial.println("Starting 5 trials...");
}

void loop(void)
{
  // Check if any trail is left
  if (trial_number <= total_trials) {
    // Read temperature data
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);

    // Display the temperature and trail number on the LCD
    lcd.setCursor(0, 0);
    lcd.print("Trial: ");
    lcd.print(trial_number);
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperatureC);
    lcd.print((char)223);
    lcd.print("C");

    // Start logging when temperature crosses the start threshold
    if (temperatureC >= start_threshold && !logging_started) {
      start_time = millis();
      logging_started = true;
      Serial.print("Trial ");
      Serial.print(trial_number);
      Serial.println(" started. Logging temperature data...");
    }

    if (logging_started) {
      // Send temperature data to Serial Monitor for logging in Python
      unsigned long elapsed_time = (millis() - start_time) / 1000;  // Time in seconds
      Serial.print("Trial ");
      Serial.print(trial_number);
      Serial.print(", Time: ");
      Serial.print(elapsed_time);
      Serial.print("s, Temperature: ");
      Serial.println(temperatureC);

      // Stop logging when temperature reaches drinkable threshold
      if (temperatureC <= stop_threshold) {
        Serial.print("Trial ");
        Serial.print(trial_number);
        Serial.println(" completed. Drinkable temperature reached!");
        logging_started = false;  // Stop logging
        trial_number++;           // Move to the next trial
      }
    }

    // Wait for 10 seconds before reading again
    delay(10000);
  } else {
    // End the trials after completing the required number of trials
    Serial.println("All trials completed.");
    lcd.clear();
    lcd.print("Trials Completed");
    delay(2000);
  }
}