<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-28T19:21:15+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "lt"
}
-->
# Nustatykite laikmatį - Wio Terminal

Šioje pamokos dalyje jūs iškviesite savo serverless kodą, kad atpažintumėte kalbą, ir nustatytumėte laikmatį savo Wio Terminal įrenginyje pagal gautus rezultatus.

## Nustatykite laikmatį

Tekstas, grįžtantis iš kalbos į tekstą konvertavimo, turi būti išsiųstas į jūsų serverless kodą, kad būtų apdorotas naudojant LUIS, kuris grąžins laikmačio sekundžių skaičių. Šis sekundžių skaičius gali būti naudojamas laikmačiui nustatyti.

Mikrovaldikliai natūraliai nepalaiko kelių gijų „Arduino“ aplinkoje, todėl nėra standartinių laikmačių klasių, kaip, pavyzdžiui, programavime su Python ar kitomis aukštesnio lygio kalbomis. Vietoj to, galite naudoti laikmačių bibliotekas, kurios veikia matuodamos praėjusį laiką funkcijoje `loop` ir iškviesdamos funkcijas, kai laikas baigiasi.

### Užduotis - išsiųskite tekstą į serverless funkciją

1. Atidarykite projektą `smart-timer` VS Code aplinkoje, jei jis dar neatidarytas.

1. Atidarykite antraštės failą `config.h` ir pridėkite savo funkcijos programos URL:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Pakeiskite `<URL>` į savo funkcijos programos URL, kurį gavote paskutiniame ankstesnės pamokos žingsnyje, nurodydami savo vietinio kompiuterio IP adresą, kuriame veikia funkcijos programa.

1. Sukurkite naują failą aplanke `src`, pavadintą `language_understanding.h`. Jis bus naudojamas klasei apibrėžti, kuri išsiųs atpažintą kalbą į jūsų funkcijos programą, kad ji būtų konvertuota į sekundes naudojant LUIS.

1. Pridėkite šį kodą failo viršuje:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Tai įtraukia reikalingus antraštės failus.

1. Apibrėžkite klasę `LanguageUnderstanding` ir deklaruokite šios klasės egzempliorių:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Norėdami iškviesti savo funkcijos programą, turite deklaruoti „WiFi“ klientą. Pridėkite šį kodą prie klasės `private` sekcijos:

    ```cpp
    WiFiClient _client;
    ```

1. Klasės `public` sekcijoje deklaruokite metodą `GetTimerDuration`, kuris iškvies funkcijos programą:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Metode `GetTimerDuration` pridėkite šį kodą, kad sukurtumėte JSON, kuris bus išsiųstas į funkcijos programą:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tai konvertuoja tekstą, perduotą į metodą `GetTimerDuration`, į šį JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    kur `<text>` yra tekstas, perduotas funkcijai.

1. Po to pridėkite šį kodą, kad iškviestumėte funkcijos programą:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tai atlieka POST užklausą į funkcijos programą, perduodant JSON turinį ir gaunant atsakymo kodą.

1. Pridėkite šį kodą po to:

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

    Šis kodas patikrina atsakymo kodą. Jei jis yra 200 (sėkmė), tada iš atsakymo turinio gaunamas laikmačio sekundžių skaičius. Priešingu atveju klaida siunčiama į serijinį monitorių, o sekundžių skaičius nustatomas į 0.

1. Pridėkite šį kodą metodo pabaigoje, kad uždarytumėte HTTP ryšį ir grąžintumėte sekundžių skaičių:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Pagrindiniame faile `main.cpp` įtraukite šią naują antraštę:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Funkcijos `processAudio` pabaigoje iškvieskite metodą `GetTimerDuration`, kad gautumėte laikmačio trukmę:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Tai konvertuoja tekstą iš `SpeechToText` klasės iškvietimo į laikmačio sekundžių skaičių.

### Užduotis - nustatykite laikmatį

Sekundžių skaičius gali būti naudojamas laikmačiui nustatyti.

1. Pridėkite šią bibliotekos priklausomybę į failą `platformio.ini`, kad pridėtumėte laikmačio biblioteką:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Pridėkite šios bibliotekos įtraukimo direktyvą į failą `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Virš funkcijos `processAudio` pridėkite šį kodą:

    ```cpp
    auto timer = timer_create_default();
    ```

    Šis kodas deklaruoja laikmatį, pavadintą `timer`.

1. Po to pridėkite šį kodą:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Funkcija `say` galiausiai konvertuos tekstą į kalbą, tačiau šiuo metu ji tiesiog rašys perduotą tekstą į serijinį monitorių.

1. Po funkcijos `say` pridėkite šį kodą:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Tai yra atgalinio iškvietimo funkcija, kuri bus iškviečiama, kai laikmatis baigsis. Jai perduodama žinutė, kurią reikia pasakyti, kai laikmatis baigiasi. Laikmačiai gali kartotis, ir tai galima valdyti grąžinimo reikšme - ši funkcija grąžina `false`, kad laikmatis nebūtų paleistas iš naujo.

1. Pridėkite šį kodą funkcijos `processAudio` pabaigoje:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Šis kodas patikrina bendrą sekundžių skaičių, ir jei jis yra 0, grąžina funkcijos iškvietimą, kad laikmačiai nebūtų nustatyti. Tada jis konvertuoja bendrą sekundžių skaičių į minutes ir sekundes.

1. Po šio kodo pridėkite šį kodą, kad sukurtumėte žinutę, kurią reikia pasakyti, kai laikmatis pradedamas:

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

1. Po to pridėkite panašų kodą, kad sukurtumėte žinutę, kurią reikia pasakyti, kai laikmatis baigiasi:

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

1. Po to pasakykite žinutę apie laikmačio pradžią:

    ```cpp
    say(begin_message);
    ```

1. Funkcijos pabaigoje paleiskite laikmatį:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Tai paleidžia laikmatį. Laikmatis nustatomas naudojant milisekundes, todėl bendras sekundžių skaičius padauginamas iš 1,000, kad būtų konvertuotas į milisekundes. Funkcija `timerExpired` perduodama kaip atgalinio iškvietimo funkcija, o `end_message` perduodama kaip argumentas, kuris bus perduotas atgalinio iškvietimo funkcijai. Ši funkcija priima tik `void *` argumentus, todėl eilutė tinkamai konvertuojama.

1. Galiausiai laikmatis turi „tikėti“, ir tai atliekama funkcijoje `loop`. Pridėkite šį kodą funkcijos `loop` pabaigoje:

    ```cpp
    timer.tick();
    ```

1. Sukompiliuokite šį kodą, įkelkite jį į savo Wio Terminal ir išbandykite per serijinį monitorių. Kai serijiniame monitoriuje pamatysite „Ready“, paspauskite C mygtuką (esantį kairėje pusėje, arčiausiai maitinimo jungiklio) ir kalbėkite. Bus užfiksuota 4 sekundžių trukmės garso įrašas, konvertuotas į tekstą, išsiųstas į jūsų funkcijos programą, ir bus nustatytas laikmatis. Įsitikinkite, kad jūsų funkcijos programa veikia lokaliai.

    Pamatysite, kada laikmatis pradedamas ir kada jis baigiasi.

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

> 💁 Šį kodą galite rasti aplanke [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Jūsų laikmačio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.