import serial
import json
import time
import os

# Configure serial connection
ser = serial.Serial('/dev/tty.usbserial-0001', 9600)  # Replace with the correct port for your setup
ser.timeout = 1  # Set timeout to 1 second

# Path to the JSON file
json_file_path = 'data.json'

def initialize_json_file():
    """Initialize the JSON file if it doesn't exist or is empty."""
    if not os.path.exists(json_file_path):
        with open(json_file_path, 'w') as file:
            json.dump({}, file)
    else:
        try:
            with open(json_file_path, 'r') as file:
                json.load(file)
        except (json.JSONDecodeError, FileNotFoundError):
            with open(json_file_path, 'w') as file:
                json.dump({}, file)

def read_from_arduino():
    try:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            return data
    except Exception as e:
        print(f"Error reading from Arduino: {e}")
    return None

def write_to_json(data):
    try:
        # Write the new data to the file, replacing any existing content
        with open(json_file_path, 'w') as file:
            json.dump(data, file, indent=4)
    except Exception as e:
        print(f"Error writing to JSON file: {e}")

def main():
    # Initialize or clear the JSON file if needed
    initialize_json_file()

    print("Starting data collection...")
    while True:
        data = read_from_arduino()
        if data:
            print(f"Received data: {data}")
            # Write the new data to the JSON file, replacing the previous content
            write_to_json({'data': data, 'timestamp': time.time()})
        time.sleep(1)  # Delay before the next read

if __name__ == "__main__":
    main()
