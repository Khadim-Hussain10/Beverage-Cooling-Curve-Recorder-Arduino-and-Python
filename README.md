# Beverage Cooling Curve Recorder (Arduino and Python)

An Arduino and Python project that records how a hot beverage cools and uses
polynomial regression to predict how long it takes to reach a drinkable
temperature (40 °C).

Semester project for PDS, Fall 2025, Quaid-i-Azam University, Islamabad.

**Python libraries:** pyserial, csv, pandas, NumPy, Matplotlib, Seaborn, scikit-learn.

## How it works
1. **Arduino** reads a DS18B20 temperature sensor every 10 seconds, shows the
   temperature on a 16x2 I2C LCD and prints it over serial. Logging starts
   when the temperature rises above 55 °C and each trial ends at 36 °C.
   5 trials in total.
2. **Python** reads the serial port (COM3, 9600 baud) and saves the trial
   number, time (s) and temperature (°C) to a CSV file.
3. **Data processing and EDA:** null readings are removed, the data is
   reformatted, and the cooling curve of each trial is plotted
   (Matplotlib, Seaborn).
4. **Model:** a 3rd-degree polynomial regression (scikit-learn) trained on
   Trial 5 predicts the time needed to cool to 40 °C.

![Experimental setup](images/setup_photo.png)

## Hardware
- Arduino Uno
- Breadboard and jumper wires
- DS18B20 temperature sensor (data pin on digital pin 2)
- 10 kΩ resistor
- 16x2 LCD with I2C module

Arduino libraries: OneWire, DallasTemperature, Wire, LiquidCrystal_I2C.

![Circuit setup](images/circuit_diagram.png)

## Results
- Mean squared error: 0.01
- R²: 1.00 (on the training trial)
- Predicted time to cool to 40 °C:

| Initial temperature | Predicted time |
|---|---|
| 60 °C | 36.37 min |
| 65 °C | 43.55 min |
| 70 °C | 50.20 min |

![Polynomial fit](images/polynomial_fit.png)

## Limitations
- Readings can be affected by room conditions and airflow, and only one
  sensor was used.
- The model was trained on a single trial, so it does not capture
  trial-to-trial variation.
- The metrics are measured on the same trial used for training (no held-out
  test set).
- Predictions from 65 °C and 70 °C go beyond the temperature range of the
  training data (about 63 °C down to 36 °C), so they are extrapolations.
- Cup material and beverage type were not varied, and the model assumes
  consistent initial conditions.

## Repository structure
```
├── arduino/    Arduino sketch (.ino)
├── python/     Data collection script and regression notebook
├── data/       Temperature data for the 5 trials
├── images/     Circuit diagram, setup photo and plots
└── docs/       Project presentation (PDF)
```

## How to run
1. Wire the circuit as shown in `images/circuit_diagram.png` and upload the
   sketch in `arduino/` to the Arduino Uno.
2. Set the correct serial port in the data collection script, then run it
   to record the trials into a CSV file.
3. Run the notebook in `python/` to plot the cooling curves, train the
   model and get the predictions.

## Authors
- Khadim Hussain
