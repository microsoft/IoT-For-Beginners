<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T21:13:45+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "sw"
}
-->
# Weka Kipaswidi - Wio Terminal

Katika sehemu hii ya somo, utaita msimbo wako wa serverless ili kuelewa sauti, na kuweka kipaswidi kwenye Wio Terminal yako kulingana na matokeo.

## Weka Kipaswidi

Maandishi yanayorudi kutoka kwenye simu ya sauti hadi maandishi yanahitaji kutumwa kwa msimbo wako wa serverless ili kushughulikiwa na LUIS, na kurudisha idadi ya sekunde za kipaswidi. Idadi hii ya sekunde inaweza kutumika kuweka kipaswidi.

Microcontrollers hazina msaada wa asili kwa nyuzi nyingi (threads) katika Arduino, kwa hivyo hakuna madarasa ya kawaida ya kipaswidi kama unavyoweza kupata unapopanga kwa Python au lugha nyingine za kiwango cha juu. Badala yake, unaweza kutumia maktaba za kipaswidi zinazofanya kazi kwa kupima muda uliopita katika kazi ya `loop`, na kuita kazi fulani wakati muda unamalizika.

### Kazi - tuma maandishi kwa kazi ya serverless

1. Fungua mradi wa `smart-timer` kwenye VS Code ikiwa haujafunguliwa tayari.

1. Fungua faili ya kichwa `config.h` na ongeza URL ya programu yako ya kazi:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Badilisha `<URL>` na URL ya programu yako ya kazi uliyoipata katika hatua ya mwisho ya somo lililopita, ikielekeza kwenye anwani ya IP ya mashine yako ya ndani inayotumia programu ya kazi.

1. Unda faili mpya kwenye folda ya `src` inayoitwa `language_understanding.h`. Hii itatumika kufafanua darasa la kutuma sauti iliyotambuliwa kwa programu yako ya kazi ili kubadilishwa kuwa sekunde kwa kutumia LUIS.

1. Ongeza yafuatayo juu ya faili hii:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Hii inajumuisha baadhi ya faili za kichwa zinazohitajika.

1. Fafanua darasa linaloitwa `LanguageUnderstanding`, na tangaza mfano wa darasa hili:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Ili kuita programu yako ya kazi, unahitaji kutangaza mteja wa WiFi. Ongeza yafuatayo kwenye sehemu ya `private` ya darasa:

    ```cpp
    WiFiClient _client;
    ```

1. Katika sehemu ya `public`, tangaza njia inayoitwa `GetTimerDuration` ili kuita programu ya kazi:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Katika njia ya `GetTimerDuration`, ongeza msimbo ufuatao ili kujenga JSON ya kutumwa kwa programu ya kazi:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Hii inabadilisha maandishi yaliyopitishwa kwa njia ya `GetTimerDuration` kuwa JSON ifuatayo:

    ```json
    {
        "text" : "<text>"
    }
    ```

    ambapo `<text>` ni maandishi yaliyopitishwa kwa kazi.

1. Chini ya hii, ongeza msimbo ufuatao ili kufanya simu ya programu ya kazi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Hii inafanya ombi la POST kwa programu ya kazi, ikipitisha mwili wa JSON na kupata msimbo wa majibu.

1. Ongeza msimbo ufuatao chini ya hii:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Msimbo huu unakagua msimbo wa majibu. Ikiwa ni 200 (mafanikio), basi idadi ya sekunde za kipaswidi inapatikana kutoka kwa mwili wa majibu. Vinginevyo, kosa linatumwa kwa mfuatiliaji wa serial na idadi ya sekunde inakuwa 0.

1. Ongeza msimbo ufuatao mwishoni mwa njia hii ili kufunga muunganisho wa HTTP na kurudisha idadi ya sekunde:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Katika faili ya `main.cpp`, jumuisha kichwa hiki kipya:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Mwishoni mwa kazi ya `processAudio`, ita njia ya `GetTimerDuration` ili kupata muda wa kipaswidi:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Hii inabadilisha maandishi kutoka kwenye simu ya darasa la `SpeechToText` kuwa idadi ya sekunde za kipaswidi.

### Kazi - weka kipaswidi

Idadi ya sekunde inaweza kutumika kuweka kipaswidi.

1. Ongeza utegemezi wa maktaba ifuatayo kwenye faili ya `platformio.ini` ili kuongeza maktaba ya kuweka kipaswidi:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Ongeza maagizo ya kujumuisha maktaba hii kwenye faili ya `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Juu ya kazi ya `processAudio`, ongeza msimbo ufuatao:

    ```cpp
    auto timer = timer_create_default();
    ```

    Msimbo huu unatangaza kipaswidi kinachoitwa `timer`.

1. Chini ya hii, ongeza msimbo ufuatao:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Kazi hii ya `say` hatimaye itabadilisha maandishi kuwa sauti, lakini kwa sasa itaandika tu maandishi yaliyopitishwa kwenye mfuatiliaji wa serial.

1. Chini ya kazi ya `say`, ongeza msimbo ufuatao:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Hii ni kazi ya callback ambayo itaitwa wakati kipaswidi kinamalizika. Inapokea ujumbe wa kusema wakati kipaswidi kinamalizika. Vipaswidi vinaweza kurudia, na hii inaweza kudhibitiwa na thamani ya kurudi ya callback hii - hii inarudisha `false`, kuambia kipaswidi kisirudie tena.

1. Ongeza msimbo ufuatao mwishoni mwa kazi ya `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Msimbo huu unakagua jumla ya idadi ya sekunde, na ikiwa ni 0, inarudi kutoka kwenye simu ya kazi ili hakuna vipaswidi vinavyowekwa. Kisha inabadilisha jumla ya idadi ya sekunde kuwa dakika na sekunde.

1. Chini ya msimbo huu, ongeza yafuatayo ili kuunda ujumbe wa kusema wakati kipaswidi kinaanza:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Chini ya hii, ongeza msimbo sawa ili kuunda ujumbe wa kusema wakati kipaswidi kimeisha:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Baada ya hii, sema ujumbe wa kuanza kipaswidi:

    ```cpp
    say(begin_message);
    ```

1. Mwishoni mwa kazi hii, anzisha kipaswidi:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Hii inachochea kipaswidi. Kipaswidi kimewekwa kwa kutumia milisekunde, kwa hivyo jumla ya idadi ya sekunde inazidishwa na 1,000 kubadilisha kuwa milisekunde. Kazi ya `timerExpired` inapewa kama callback, na `end_message` inapewa kama hoja ya kupitisha kwa callback. Callback hii inachukua tu hoja za `void *`, kwa hivyo kamba inabadilishwa ipasavyo.

1. Hatimaye, kipaswidi kinahitaji *kutikisa*, na hii inafanywa katika kazi ya `loop`. Ongeza msimbo ufuatao mwishoni mwa kazi ya `loop`:

    ```cpp
    timer.tick();
    ```

1. Jenga msimbo huu, pakia kwenye Wio Terminal yako na ujaribu kupitia mfuatiliaji wa serial. Mara tu unapoona `Ready` kwenye mfuatiliaji wa serial, bonyeza kitufe cha C (kile kilicho upande wa kushoto, karibu na swichi ya nguvu), na uzungumze. Sekunde 4 za sauti zitakamatwa, kubadilishwa kuwa maandishi, kisha kutumwa kwa programu yako ya kazi, na kipaswidi kitawekwa. Hakikisha programu yako ya kazi inafanya kazi kwa ndani.

    Utaona wakati kipaswidi kinaanza, na wakati kinamalizika.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Programu yako ya kipaswidi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.