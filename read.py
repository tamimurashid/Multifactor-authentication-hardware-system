import json
import os
import pyttsx3
import time

# Path to the JSON file
json_file_path = 'data.json'

def read_from_json():
    try:
        with open(json_file_path, 'r') as file:
            json_data = json.load(file)
            return json_data if json_data else None
    except FileNotFoundError:
        return None
    except json.JSONDecodeError:
        return None

def provide_feedback(message, speed=150):
    try:
        engine = pyttsx3.init()
        engine.setProperty('rate', speed)  # Set the speed of the speech
        engine.say(message)
        engine.runAndWait()
    except Exception as e:
        print(f"Error using pyttsx3: {e}")

def main():
    while True:
        data = read_from_json()
        if data:
            print(f"Read data: {data}")
            # Assuming 'data' contains a 'data' field which indicates success/failure
            # This is a placeholder; adapt it based on the actual data structure
            if 'Found a print match!' in data:
                provide_feedback("Authentication successful")
            elif 'Did not find a match' in data:
                provide_feedback("Authentication failed")
            else:
                provide_feedback("Unknown result")
            
        time.sleep(5)  # Delay before checking the JSON file again

if __name__ == "__main__":
    main()
