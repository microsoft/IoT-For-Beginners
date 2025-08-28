<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T12:42:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "sr"
}
-->
# Претварање текста у говор - Wio Terminal

У овом делу лекције, претворићете текст у говор како бисте обезбедили звучне повратне информације.

## Претварање текста у говор

SDK за говорне услуге који сте користили у претходној лекцији за претварање говора у текст може се користити и за претварање текста у говор.

## Добијање листе гласова

Када захтевате говор, потребно је да наведете глас који ће се користити, јер се говор може генерисати помоћу различитих гласова. Сваки језик подржава низ различитих гласова, а листу подржаних гласова за сваки језик можете добити из SDK-а за говорне услуге. Овде долазе до изражаја ограничења микроконтролера - позив за добијање листе гласова подржаних од стране услуга за претварање текста у говор је JSON документ величине преко 77KB, што је превелико за обраду на Wio Terminal-у. У време писања, комплетна листа садржи 215 гласова, од којих је сваки дефинисан JSON документом попут следећег:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Овај JSON је за глас **Aria**, који има више стилова гласа. Све што је потребно за претварање текста у говор је кратко име, `en-US-AriaNeural`.

Уместо преузимања и декодирања целе ове листе на вашем микроконтролеру, потребно је да напишете још мало serverless кода како бисте преузели листу гласова за језик који користите и позвали ово са вашег Wio Terminal-а. Ваш код затим може изабрати одговарајући глас са листе, као што је први који пронађе.

### Задатак - креирање serverless функције за добијање листе гласова

1. Отворите свој пројекат `smart-timer-trigger` у VS Code-у и отворите терминал, осигуравајући да је виртуелно окружење активирано. Ако није, угасите и поново креирајте терминал.

1. Отворите датотеку `local.settings.json` и додајте подешавања за API кључ и локацију услуге за говор:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Замените `<key>` са API кључем за ваш ресурс услуге за говор. Замените `<location>` са локацијом коју сте користили приликом креирања ресурса услуге за говор.

1. Додајте нови HTTP тригер овој апликацији под називом `get-voices` користећи следећу команду из терминала у VS Code-у у коренском фолдеру пројекта функција:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Ово ће креирати HTTP тригер под називом `get-voices`.

1. Замените садржај датотеке `__init__.py` у фолдеру `get-voices` следећим:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Овај код прави HTTP захтев ка крајњој тачки за добијање гласова. Листа гласова је велики блок JSON-а са гласовима за све језике, па се гласови за језик који је прослеђен у телу захтева филтрирају, а затим се кратко име извлачи и враћа као JSON листа. Кратко име је вредност потребна за претварање текста у говор, па се враћа само ова вредност.

    > 💁 Можете променити филтер по потреби како бисте изабрали само гласове које желите.

    Ово смањује величину података са 77KB (у време писања) на много мањи JSON документ. На пример, за гласове на енглеском језику из САД-а, ово је 408 бајтова.

1. Покрените своју апликацију функција локално. Затим је можете позвати помоћу алата као што је curl на исти начин као што сте тестирали HTTP тригер `text-to-timer`. Обавезно проследите свој језик као JSON тело:

    ```json
    {
        "language":"<language>"
    }
    ```

    Замените `<language>` са вашим језиком, као што је `en-GB` или `zh-CN`.

> 💁 Овај код можете пронаћи у фолдеру [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Задатак - преузимање гласа са вашег Wio Terminal-а

1. Отворите пројекат `smart-timer` у VS Code-у ако већ није отворен.

1. Отворите хедер датотеку `config.h` и додајте URL за вашу апликацију функција:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` са URL-ом за HTTP тригер `get-voices` на вашој апликацији функција. Ово ће бити исто као вредност за `TEXT_TO_TIMER_FUNCTION_URL`, осим што ће име функције бити `get-voices` уместо `text-to-timer`.

1. Креирајте нову датотеку у фолдеру `src` под називом `text_to_speech.h`. Ова датотека ће се користити за дефинисање класе за претварање текста у говор.

1. Додајте следеће директиве за укључивање на врх нове датотеке `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Испод овога додајте код за декларацију класе `TextToSpeech`, заједно са инстанцом која се може користити у остатку апликације:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Да бисте позвали апликацију функција, потребно је да декларишете WiFi клијент. Додајте следеће у `private` секцију класе:

    ```cpp
    WiFiClient _client;
    ```

1. У `private` секцији додајте поље за изабрани глас:

    ```cpp
    String _voice;
    ```

1. У `public` секцији додајте функцију `init` која ће добити први глас:

    ```cpp
    void init()
    {
    }
    ```

1. Да бисте добили гласове, потребно је послати JSON документ апликацији функција са језиком. Додајте следећи код у функцију `init` за креирање овог JSON документа:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Затим креирајте `HTTPClient`, а затим га користите за позивање апликације функција ради добијања гласова, шаљући JSON документ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Испод овога додајте код за проверу кода одговора, и ако је 200 (успех), извуците листу гласова, преузимајући први са листе:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Након овога, завршите HTTP клијент конекцију:

    ```cpp
    httpClient.end();
    ```

1. Отворите датотеку `main.cpp` и додајте следећу директиву за укључивање на врх како бисте укључили ову нову хедер датотеку:

    ```cpp
    #include "text_to_speech.h"
    ```

1. У функцији `setup`, испод позива `speechToText.init();`, додајте следеће за иницијализацију класе `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Компилирајте овај код, отпремите га на ваш Wio Terminal и тестирајте га преко серијског монитора. Уверите се да ваша апликација функција ради.

    Видећете листу доступних гласова враћених из апликације функција, заједно са изабраним гласом.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Претварање текста у говор

Када имате глас који ћете користити, он се може користити за претварање текста у говор. Иста ограничења меморије са гласовима примењују се и када се говор претвара у текст, па ћете морати да снимите говор на SD картицу како би се репродуковао преко ReSpeaker-а.

> 💁 У ранијим лекцијама у овом пројекту користили сте флеш меморију за чување говора снимљеног са микрофона. Ова лекција користи SD картицу јер је лакше репродуковати аудио са ње користећи Seeed аудио библиотеке.

Такође постоји још једно ограничење које треба узети у обзир, доступни аудио подаци из услуге за говор и формати које Wio Terminal подржава. За разлику од рачунара, аудио библиотеке за микроконтролере могу бити веома ограничене у форматима које подржавају. На пример, Seeed Arduino Audio библиотека која може репродуковати звук преко ReSpeaker-а подржава само аудио са фреквенцијом узорковања од 44.1KHz. Azure услуге за говор могу обезбедити аудио у више формата, али ниједан од њих не користи ову фреквенцију узорковања, већ само 8KHz, 16KHz, 24KHz и 48KHz. То значи да аудио треба поново узорковати на 44.1KHz, што би захтевало више ресурса него што Wio Terminal има, посебно меморије.

Када је потребно манипулисати подацима попут ових, често је боље користити serverless код, посебно ако се подаци добијају преко веб позива. Wio Terminal може позвати serverless функцију, прослеђујући текст за претварање, а serverless функција може и позвати услугу за говор ради претварања текста у говор, као и поново узорковати аудио на потребну фреквенцију узорковања. Затим може вратити аудио у облику који Wio Terminal треба да би га сачувао на SD картици и репродуковао преко ReSpeaker-а.

### Задатак - креирање serverless функције за претварање текста у говор

1. Отворите свој пројекат `smart-timer-trigger` у VS Code-у и отворите терминал, осигуравајући да је виртуелно окружење активирано. Ако није, угасите и поново креирајте терминал.

1. Додајте нови HTTP тригер овој апликацији под називом `text-to-speech` користећи следећу команду из терминала у VS Code-у у коренском фолдеру пројекта функција:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Ово ће креирати HTTP тригер под називом `text-to-speech`.

1. Pip пакет [librosa](https://librosa.org) има функције за поновно узорковање аудио записа, па га додајте у датотеку `requirements.txt`:

    ```sh
    librosa
    ```

    Када ово додате, инсталирајте Pip пакете користећи следећу команду из терминала у VS Code-у:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Ако користите Linux, укључујући Raspberry Pi OS, можда ћете морати да инсталирате `libsndfile` помоћу следеће команде:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Да бисте претворили текст у говор, не можете директно користити API кључ за говор, већ морате затражити приступни токен, користећи API кључ за аутентификацију захтева за приступни токен. Отворите датотеку `__init__.py` из фолдера `text-to-speech` и замените сав код у њој следећим:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ово дефинише константе за локацију и кључ за говор који ће се читати из подешавања. Затим дефинише функцију `get_access_token` која ће преузети приступни токен за услугу за говор.

1. Испод овог кода додајте следеће:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Ово дефинише HTTP тригер који претвара текст у говор. Извлачи текст за претварање, језик и глас из JSON тела послатог у захтеву, гради SSML за захтев за говор, а затим позива одговарајући REST API аутентификујући се помоћу приступног токена. Овај REST API позив враћа аудио кодирани као 16-битни, 48KHz моно WAV фајл, дефинисан вредношћу `playback_format`, која се шаље у REST API позив.

    Ово се затим поново узоркује помоћу `librosa` са фреквенције узорковања од 48KHz на фреквенцију узорковања од 44.1KHz, затим се овај аудио чува у бинарном баферу који се затим враћа.

1. Покрените своју апликацију функција локално или је поставите у облак. Затим је можете позвати помоћу алата као што је curl на исти начин као што сте тестирали HTTP тригер `text-to-timer`. Обавезно проследите језик, глас и текст као JSON тело:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Замените `<language>` са вашим језиком, као што је `en-GB` или `zh-CN`. Замените `<voice>` са гласом који желите да користите. Замените `<text>` са текстом који желите да претворите у говор. Можете сачувати излаз у фајл и репродуковати га помоћу било ког аудио плејера који може репродуковати WAV фајлове.

    На пример, да бисте претворили "Hello" у говор користећи енглески језик из САД-а са гласом Jenny Neural, са апликацијом функција која ради локално, можете користити следећу curl команду:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Ово ће сачувати аудио у `hello.wav` у тренутном директоријуму.

> 💁 Овај код можете пронаћи у фолдеру [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Задатак - преузимање говора са вашег Wio Terminal-а

1. Отворите пројекат `smart-timer` у VS Code-у ако већ није отворен.

1. Отворите хедер датотеку `config.h` и додајте URL за вашу апликацију функција:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Замените `<URL>` са URL-ом за HTTP тригер `text-to-speech` на вашој апликацији функција. Ово ће бити исто као вредност за `TEXT_TO_TIMER_FUNCTION_URL`, осим што ће име функције бити `text-to-speech` уместо `text-to-timer`.

1. Отворите хедер датотеку `text_to_speech.h` и додајте следећи метод у `public` секцију класе `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. У метод `convertTextToSpeech` додајте следећи код за креирање JSON-а који ће се послати апликацији функција:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ово пише језик, глас и текст у JSON документ, а затим га серијализује у стринг.

1. Испод овога додајте следећи код за позивање апликације функција:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ово креира HTTPClient, а затим прави POST захтев користећи JSON документ ка HTTP тригеру за претварање текста у говор.

1. Ако позив успе, сирови бинарни подаци враћени из позива апликације функција могу се стримовати у фајл на SD картици. Додајте следећи код за то:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Овај код проверава одговор, и ако је 200 (успех), бинарни подаци се стримују у фајл у корену SD картице под називом `SPEECH.WAV`.

1. На крају овог метода, затворите HTTP конекцију:

    ```cpp
    httpClient.end();
    ```

1. Текст који треба изговорити сада може бити претворен у аудио. У датотеци `main.cpp`, додајте следећу линију на крај функције `say` како бисте текст за изговор претворили у аудио:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Задатак - пуштање звука са вашег Wio Terminal-а

**Ускоро доступно**

## Деплојовање ваше функцијске апликације у облак

Разлог за покретање функцијске апликације локално је тај што `librosa` Pip пакет на Линуксу има зависност од библиотеке која није подразумевано инсталирана и мора бити инсталирана пре него што функцијска апликација може да ради. Функцијске апликације су серверлес - нема сервера које можете сами управљати, па самим тим нема начина да се ова библиотека унапред инсталира.

Начин да се ово реши је деплојовање ваше функцијске апликације користећи Docker контејнер. Овај контејнер се деплојује у облак кад год је потребно покренути нову инстанцу ваше функцијске апликације (на пример, када потражња премашује доступне ресурсе или ако функцијска апликација није коришћена неко време и затворена је).

Упутства за подешавање функцијске апликације и деплојовање преко Docker-а можете пронаћи у [документацији за креирање функције на Линуксу користећи прилагођени контејнер на Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Када ово буде деплојовано, можете пренети ваш Wio Terminal код како бисте приступили овој функцији:

1. Додајте Azure Functions сертификат у `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Промените све укључене фајлове из `<WiFiClient.h>` у `<WiFiClientSecure.h>`.

1. Промените сва поља типа `WiFiClient` у `WiFiClientSecure`.

1. У свакој класи која има поље типа `WiFiClientSecure`, додајте конструктор и подесите сертификат у том конструктору:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људског преводиоца. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.