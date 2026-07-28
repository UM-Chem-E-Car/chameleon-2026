import serial
from datetime import datetime



# Adjust 'COM3' to your Arduino port and 9600 to your baud rate
arduino_port = "COM5" 
baud_rate = 9600


fileNumber = 0
with open("test/persistentData.dat") as persistent:
    fileNumber = int(persistent.read())
    persistent.close()
    
ser = serial.Serial(arduino_port, baud_rate)
print(f"Connected to Arduino port: {arduino_port}")
filename = "data/Run"
extension = ".csv"


# Create and open the file
with open(filename+str(fileNumber)+extension, "w", encoding="utf-8") as file:
    formatted_dt = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    # file.write("------------------ Data Log: " + formatted_dt + " Run #: " + str(fileNumber) + " ------------------")
    # print("------------------ Data Log: " + formatted_dt + " Run #: " + str(fileNumber) + " ------------------")
    while True:
        try:
            # Read a line of data from the Arduino
            data_line = ser.readline().decode('utf-8').strip()
            print(data_line) # Print to computer console
            file.write(data_line + "\n") # Save to the text/csv file
        except KeyboardInterrupt:
            print("Data logging stopped.")
            break
        except UnicodeDecodeError:
            continue

with open("test/persistentData.dat", "w") as persistent:
    persistent.write(str(fileNumber + 1))
    persistent.close()
ser.close()

