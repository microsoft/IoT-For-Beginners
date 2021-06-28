# Set a timer - Virtual IoT Hardware and Raspberry Pi

In this part of the lesson, you will set a timer on your virtual IoT device or Raspberry Pi based off a command from the IoT Hub.

## Set a timer

The text that comes back from the speech to text call needs to be sent to your serverless code to be processed by LUIS, getting back the number of seconds for the timer. This number of seconds can be used to set a timer.

Timers can be set using the Python `threading.Timer` class. This class takes a delay time and a function, and after the delay time, the function is executed.

### Task - send the text to the serverless function

1. Open the `smart-timer` project in VS Code, and ensure the virtual environment is loaded in the terminal if you are using a virtual IoT device.

1. Above the `process_text` function, declare a function called `get_timer_time` to call the REST endpoint you created:

    ```python
    def get_timer_time(text):
    ```

1. Add the following code to this function to define the URL to call:

    ```python
    url = '<URL>'
    ```

    Replace `<URL>` with the URL of your rest endpoint that you built in the last lesson, either on your computer or in the cloud.

1. Add the following code to set the text as a parameter on the URL and make the API call:

    ```python
    params = {
        'text': text
    }
    
    response = requests.post(url, params=params)
    ```

1. Below this, retrieve the `seconds` from the response payload, returning 0 if the call failed:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Successful HTTP calls return a status code in the 200 range, and your serverless code returns 200 if the text was processed and recognized as the set timer intent.

### Task - set a timer on a background thread

1. Add the following import statement at the top of the file to import the threading Python library:

    ```python
    import threading
    ```

1. Above the `process_text` function, add a function to speak a response. Fow now this will just write to the console, but later in this lesson this will speak the text.

    ```python
    def say(text):
        print(text)
    ```

1. Below this add a function that will be called by a timer to announce that the timer is complete:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    This function takes the number of minutes and seconds for the timer, and builds a sentence to say that the timer is complete. It will check the number of minutes and seconds, and only include each time unit if it has a number. For example, if the number of minutes is 0 then only seconds are included in the message. This sentence is then sent to the `say` function.

1. Below this, add the following `create_timer` function to create a timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    This function takes the total number of seconds for the timer that will be sent in the command, and converts this to minutes and seconds. It then creates and starts a timer object using the total number of seconds, passing in the `announce_timer` function and a list containing the minutes and seconds. When the timer elapses, it will call the `announce_timer` function, and pass the contents of this list as the parameters - so the first item in the list gets passes as the `minutes` parameter, and the second item as the `seconds` parameter.

1. To the end of the `create_timer` function, add some code to build a message to be spoken to the user to announce that the timer is starting:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Again, this only includes the time unit that has a value. This sentence is then sent to the `say` function.

1. Add the following to the end of the `process_text` function to get the time for the timer from the text, then create the timer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    The timer is only created if the number of seconds is greater than 0.

1. Run the app, and ensure the function app is also running. Set some timers, and the output will show the timer being set, and then will show when it elapses:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 You can find this code in the [code-timer/pi](code-timer/pi) or [code-timer/virtual-iot-device](code-timer/virtual-iot-device) folder.

😀 Your timer program was a success!
