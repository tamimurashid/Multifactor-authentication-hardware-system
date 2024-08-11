import serial
import time

# Configure serial connection
ser = serial.Serial('/dev/tty.usbserial-0001', 9600)  # Replace 'COM3' with the appropriate port for your setup
ser.timeout = 1  # Set timeout to 1 second

def send_command(command):
    try:
        # Send command to Arduino
        ser.write((command + '\n').encode('utf-8'))
        print(f"Sent command: {command}")
    except Exception as e:
        print(f"Error sending command: {e}")

def main():
    while True:
        # Prompt user for command
        command = input("Enter command to send to Arduino (ENROLL, AUTH, DELETE, EXIT): ").strip()
        
        if command in ["ENROLL", "1", "2", "4", "AUTH", "DELETE", "EXIT", "s"]:
            send_command(command)
        else:
            print("Invalid command. Please try again.")
        
        time.sleep(1)  # Delay before the next prompt

if __name__ == "__main__":
    main()
