import serial
import sqlite3
import datetime

# Connect to the database file
conn = sqlite3.connect('database-directory\project_database.db')
c = conn.cursor()
             
# Open serial connection to Arduino
ser = serial.Serial("COM4", 9600)
ser.readline()

prev_data = 0

# Read data from Arduino and insert into database
while True:
    current_time = datetime.datetime.now()
    formatted_time = current_time.strftime("%Y-%m-%d %H:%M:%S")

    data = ser.readline().decode().strip() # read data from serial and remove newline

    if data != prev_data:
        try:
            temperature, moisture, temp_LED, moist_LED, servo = data.split(',')
        except ValueError:
            continue
        
        print(temperature, moisture, temp_LED, moist_LED, servo)
        
        c.execute("INSERT into circuit_status (waktu, suhu, kelembapan, led_suhu, led_kelembapan, posisi_servo) VALUES (?,?,?,?,?,?)", (formatted_time, temperature, moisture, temp_LED, moist_LED, servo))
        conn.commit()
        print("Data inserted into the database.\n")
        prev_data = data