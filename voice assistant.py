import speech_recognition as sr  # recognise speech
from gtts import gTTS  # google text to speech
import random
import pyttsx3
from time import ctime  # get time details
import webbrowser  # open browser
import time
import serial  # control arduino
import wikipedia as wiki  # Webscrapes wikipedia content.

# connect with UNO board over serial communication
try:
    port = serial.Serial("COM6", 9600)
    print("Physical body, connected.")
except:
    print("Unable to connect to my physical body")

listener = sr.Recognizer()
engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[1].id)


def there_exists(terms):
    for term in terms:
        if term in voice_data:
            return True


r = sr.Recognizer()  # initialise a recogniser


# listen for audio and convert it to text:
def record_audio(ask=False):
    with sr.Microphone() as source:  # microphone as source
        if ask:
            speak(ask)

        audio = r.listen(source)  # listen for the audio via source
        voice_data = ''
        try:
            voice_data = r.recognize_google(audio)  # convert audio to text
        except sr.UnknownValueError:  # error: recognizer does not understand
            speak('I did not get that')
        except sr.RequestError:
            speak('Sorry, the service is down')  # error: recognizer is not connected
        print(f">> {voice_data.lower()}")  # print what user said
        return voice_data.lower()


# get string and make a audio file to be played
def speak(audio_string):
    engine.say(audio_string)
    engine.runAndWait()


speak('Welcome Proffessor Programmer!')
port.write(b'p')


def respond(voice_data):
    # 1: greeting
    if there_exists(['hey', 'hi', 'hello']):
        port.write(b'p')
        greetings = [f"hey, how can I help you Professor"]

        speak(greetings)

    # 3: greeting
    if there_exists(["how are you", "how are you doing"]):
        speak(f"I'm very well, thanks for asking Professsor")

    # 4: time
    if there_exists(["what's the time", "tell me the time", "what time is it"]):
        port.write(b'u')
        time = ctime().split(" ")[3].split(":")[0:2]
        if time[0] == "00":
            hours = '12'
        else:
            hours = time[0]
        minutes = time[1]
        time = f'{hours} {minutes}'
        speak(time)

    # 5: search google
    if there_exists(["search for"]) and 'youtube' not in voice_data:
        port.write(b'u')
        port.write(b'l')
        search_term = voice_data.split("for")[-1]
        url = f"https://google.com/search?q={search_term}"
        webbrowser.get().open(url)
        speak(f'Here is what I found for {search_term} on google')

    # 6: search youtube
    if there_exists(["play"]):
        port.write(b'l')
        port.write(b'u')
        search_term = voice_data.split("play")[-1]
        url = f"https://www.youtube.com/results?search_query={search_term}"
        webbrowser.get().open(url)
        speak(f'Here is what I found for {search_term} on youtube')

    # 7: wikipedia summary
    if there_exists(['summarise']):
        port.write(b'u')
        port.write(b'l')

        search_term = voice_data.split("summarise")[-1]
        speak(wiki.summary(search_term, sentences=5))

    if there_exists(['summarize']):
        port.write(b'u')
        port.write(b'l')

        search_term = voice_data.split("summarize")[-1]
        speak(wiki.summary(search_term, sentences=5))

    if there_exists(["combat mode"]):
        speak('uppercut')
        port.write(b'U')
        speak('Jarvis smash!')
        port.write(b's')
        speak('yessir')

    # shutdown program
    if there_exists(["exit", "quit", "goodbye"]):
        speak("going offline")
        port.write(b'u')
        exit()


time.sleep(1)

while (1):
    voice_data = record_audio()  # get the voice input
    respond(voice_data)  # respond