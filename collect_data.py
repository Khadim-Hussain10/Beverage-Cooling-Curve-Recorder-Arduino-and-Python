import serial
import time
import csv

ser = serial.Serial('COM3', 9600)

# Opening a CSV file to store data
filename = 'temperature_data.csv'
with open(filename, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Trial Number", "Time (s)", "Temperature (°C)"])  # headers

    # Collect data until the process is stopped
    while True:
        line = ser.readline().decode('utf-8').strip()  # Read a line from the serial port

        # Check for trial number and temperature data in the line
        if "Trial" in line:
            trial_number = line.split(' ')[1]  # Extract trial number

        if "Temperature" in line:
            # Extract time and temperature values
            time_data = line.split(",")[1].split("s")[0].strip()  # Elapsed time in seconds
            temp_data = line.split("Temperature: ")[1].strip()  # Temperature value

            # Log the data into the CSV file
            writer.writerow([trial_number, time_data, temp_data])

            # Print the data to the console for monitoring
            print(f"Trial {trial_number}, Time: {time_data}s, Temperature: {temp_data}°C")

        time.sleep(10)  # Wait 10 seconds before reading next data
