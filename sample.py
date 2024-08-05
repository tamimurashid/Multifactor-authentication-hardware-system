from gtts import gTTS
import os

def provide_feedback(message):
    try:
        tts = gTTS(text=message, lang='en')
        tts.save("temp.mp3")
        os.system("afplay temp.mp3")  # For macOS
    except Exception as e:
        print(f"Error using gTTS: {e}")

provide_feedback("Hello, this is a test.")
