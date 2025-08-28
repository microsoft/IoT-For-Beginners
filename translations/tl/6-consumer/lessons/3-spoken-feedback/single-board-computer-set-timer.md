<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T23:09:12+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "tl"
}
-->
# Mag-set ng Timer - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, tatawagin mo ang iyong serverless code upang maunawaan ang speech, at mag-set ng timer sa iyong virtual IoT device o Raspberry Pi base sa mga resulta.

## Mag-set ng Timer

Ang text na bumabalik mula sa speech-to-text call ay kailangang ipadala sa iyong serverless code upang maiproseso ng LUIS, at makuha ang bilang ng segundo para sa timer. Ang bilang ng segundo na ito ay maaaring gamitin upang mag-set ng timer.

Ang mga timer ay maaaring i-set gamit ang Python `threading.Timer` class. Ang class na ito ay tumatanggap ng delay time at isang function, at pagkatapos ng delay time, ang function ay ie-execute.

### Gawain - ipadala ang text sa serverless function

1. Buksan ang proyekto na `smart-timer` sa VS Code, at tiyaking naka-load ang virtual environment sa terminal kung gumagamit ka ng virtual IoT device.

1. Sa itaas ng function na `process_text`, magdeklara ng function na tinatawag na `get_timer_time` upang tawagin ang REST endpoint na iyong ginawa:

    ```python
    def get_timer_time(text):
    ```

1. Idagdag ang sumusunod na code sa function na ito upang tukuyin ang URL na tatawagin:

    ```python
    url = '<URL>'
    ```

    Palitan ang `<URL>` ng URL ng iyong REST endpoint na ginawa sa nakaraang aralin, maaaring nasa iyong computer o nasa cloud.

1. Idagdag ang sumusunod na code upang itakda ang text bilang isang property na ipinapasa bilang JSON sa tawag:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Sa ibaba nito, kunin ang `seconds` mula sa response payload, at ibalik ang 0 kung nabigo ang tawag:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Ang matagumpay na HTTP calls ay nagbabalik ng status code sa 200 range, at ang iyong serverless code ay nagbabalik ng 200 kung ang text ay naproseso at nakilala bilang set timer intent.

### Gawain - mag-set ng timer sa background thread

1. Idagdag ang sumusunod na import statement sa itaas ng file upang i-import ang threading Python library:

    ```python
    import threading
    ```

1. Sa itaas ng function na `process_text`, magdagdag ng function upang magsalita ng response. Sa ngayon, ito ay magsusulat lamang sa console, ngunit sa susunod na bahagi ng aralin, ito ay magsasalita ng text.

    ```python
    def say(text):
        print(text)
    ```

1. Sa ibaba nito, magdagdag ng function na tatawagin ng timer upang ipahayag na tapos na ang timer:

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

    Ang function na ito ay tumatanggap ng bilang ng minuto at segundo para sa timer, at bumubuo ng isang pangungusap upang ipahayag na tapos na ang timer. Sinusuri nito ang bilang ng minuto at segundo, at isinasama lamang ang bawat unit ng oras kung ito ay may halaga. Halimbawa, kung ang bilang ng minuto ay 0, tanging ang segundo lamang ang isasama sa mensahe. Ang pangungusap na ito ay ipinapasa sa `say` function.

1. Sa ibaba nito, idagdag ang sumusunod na `create_timer` function upang lumikha ng timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Ang function na ito ay tumatanggap ng kabuuang bilang ng segundo para sa timer na ipapadala sa command, at kino-convert ito sa minuto at segundo. Pagkatapos, lumilikha at nagsisimula ito ng timer object gamit ang kabuuang bilang ng segundo, ipinapasa ang `announce_timer` function at isang listahan na naglalaman ng minuto at segundo. Kapag natapos ang timer, tatawagin nito ang `announce_timer` function, at ipapasa ang nilalaman ng listahan bilang mga parameter - kaya ang unang item sa listahan ay ipapasa bilang `minutes` parameter, at ang pangalawang item bilang `seconds` parameter.

1. Sa dulo ng `create_timer` function, magdagdag ng ilang code upang bumuo ng mensahe na sasabihin sa user upang ipahayag na nagsisimula na ang timer:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Muli, isinasama lamang nito ang unit ng oras na may halaga. Ang pangungusap na ito ay ipinapasa sa `say` function.

1. Idagdag ang sumusunod sa dulo ng `process_text` function upang makuha ang oras para sa timer mula sa text, pagkatapos ay lumikha ng timer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Ang timer ay nililikha lamang kung ang bilang ng segundo ay higit sa 0.

1. Patakbuhin ang app, at tiyaking tumatakbo rin ang function app. Mag-set ng ilang timer, at ang output ay magpapakita na ang timer ay na-set, at pagkatapos ay magpapakita kapag ito ay natapos:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Makikita mo ang code na ito sa [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) o [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device) folder.

😀 Tagumpay ang iyong timer program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.