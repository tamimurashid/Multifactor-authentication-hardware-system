import json
import os
from gtts import gTTS
from pydub import AudioSegment
from pydub.playback import play
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

def provide_feedback(message, speed=1.5):
    try:
        tts = gTTS(text=message, lang='en')
        tts.save("temp.mp3")

        # Load the MP3 file and change the playback speed
        audio = AudioSegment.from_mp3("temp.mp3")
        new_sample_rate = int(audio.frame_rate * speed)
        speed_changed_audio = audio._spawn(audio.raw_data, overrides={'frame_rate': new_sample_rate})
        speed_changed_audio = speed_changed_audio.set_frame_rate(audio.frame_rate)

        # Save the modified audio
        speed_changed_audio.export("temp_speed.mp3", format="mp3")

        # Play the modified audio
        play(AudioSegment.from_mp3("temp_speed.mp3"))
    except Exception as e:
        print(f"Error using gTTS: {e}")

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
