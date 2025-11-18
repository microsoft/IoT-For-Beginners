<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-11-18T19:13:35+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "pcm"
}
-->
# Set timer - Virtual IoT Hardware and Raspberry Pi

For dis part of di lesson, you go call your serverless code to sabi di speech, and set timer for your virtual IoT device or Raspberry Pi based on di result.

## Set timer

Di text wey go come back from di speech to text call need to dey send go your serverless code make e process am with LUIS, wey go return di number of seconds for di timer. Dis number of seconds fit dey use to set timer.

You fit set timer using Python `threading.Timer` class. Dis class dey take delay time and one function, and after di delay time, di function go run.

### Task - send di text go di serverless function

1. Open di `smart-timer` project for VS Code, and make sure say di virtual environment dey load for di terminal if you dey use virtual IoT device.

1. For di top of di `process_text` function, declare one function wey dem go call `get_timer_time` to call di REST endpoint wey you create:

    ```python
    def get_timer_time(text):
    ```

1. Add di code wey dey below to dis function to define di URL wey you go call:

    ```python
    url = '<URL>'
    ```

    Change `<URL>` to di URL of your REST endpoint wey you build for di last lesson, whether e dey for your computer or for di cloud.

1. Add di code wey dey below to set di text as property wey dem go pass as JSON for di call:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. For di bottom of dis, collect di `seconds` from di response payload, return 0 if di call no work:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Successful HTTP calls dey return status code for di 200 range, and your serverless code dey return 200 if di text dey process and dem recognize am as di set timer intent.

### Task - set timer for background thread

1. Add di import statement wey dey below for di top of di file to import di threading Python library:

    ```python
    import threading
    ```

1. For di top of di `process_text` function, add one function to talk response. For now, e go just write for di console, but later for dis lesson e go talk di text.

    ```python
    def say(text):
        print(text)
    ```

1. For di bottom of dis, add one function wey timer go call to announce say di timer don finish:

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

    Dis function dey take di number of minutes and seconds for di timer, and e go build one sentence to talk say di timer don finish. E go check di number of minutes and seconds, and e go only include each time unit if e get number. For example, if di number of minutes na 0, e go only include seconds for di message. Dis sentence go then dey send go di `say` function.

1. For di bottom of dis, add di `create_timer` function wey dey below to create timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Dis function dey take di total number of seconds for di timer wey dem go send for di command, and e go convert am to minutes and seconds. E go then create and start timer object using di total number of seconds, pass di `announce_timer` function and one list wey get di minutes and seconds. When di timer finish, e go call di `announce_timer` function, and e go pass di content of dis list as di parameters - so di first item for di list go dey pass as di `minutes` parameter, and di second item as di `seconds` parameter.

1. For di end of di `create_timer` function, add some code to build one message wey dem go talk to di user to announce say di timer dey start:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Again, e go only include di time unit wey get value. Dis sentence go then dey send go di `say` function.

1. Add di code wey dey below to di end of di `process_text` function to collect di time for di timer from di text, then create di timer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Di timer go only dey create if di number of seconds big pass 0.

1. Run di app, and make sure say di function app dey run too. Set some timers, and di output go show say di timer dey set, and e go show when e finish:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 You fit find dis code for di [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) or [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) folder.

😀 Your timer program work well!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transleshion service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transleshion. Even as we dey try make am correct, abeg make you sabi say transleshion wey machine do fit get mistake or no dey accurate well. Di original dokyument for im native language na di one wey you go take as di correct source. For important mata, e good make you use professional human transleshion. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transleshion.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->