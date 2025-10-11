<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-10-11T11:43:49+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "et"
}
-->
# Klassifitseeri pilt IoT Edge-põhise pildiklassifikaatoriga - Wio Terminal

Selles õppetunni osas kasutad IoT Edge seadmel töötavat pildiklassifikaatorit.

## Kasuta IoT Edge klassifikaatorit

IoT seadet saab suunata kasutama IoT Edge pildiklassifikaatorit. Pildiklassifikaatori URL on `http://<IP aadress või nimi>/image`, kus `<IP aadress või nimi>` asendatakse IoT Edge'i käitava arvuti IP-aadressi või hostinimega.

### Ülesanne - kasuta IoT Edge klassifikaatorit

1. Ava `fruit-quality-detector` rakenduse projekt, kui see pole juba avatud.

1. Pildiklassifikaator töötab REST API-na, kasutades HTTP-d, mitte HTTPS-i, seega peab kõne kasutama WiFi klienti, mis töötab ainult HTTP-kõnedega. See tähendab, et sertifikaati pole vaja. Kustuta `CERTIFICATE` failist `config.h`.

1. `config.h` failis tuleb ennustuse URL uuendada uue URL-iga. Samuti võid kustutada `PREDICTION_KEY`, kuna seda pole vaja.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Asenda `<URL>` oma klassifikaatori URL-iga.

1. Failis `main.cpp` muuda WiFi Client Secure'i include direktiivi, et importida standardne HTTP versioon:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Muuda `WiFiClient` deklaratsiooni HTTP versiooniks:

    ```cpp
    WiFiClient client;
    ```

1. Leia rida, mis määrab sertifikaadi WiFi kliendile. Eemalda rida `client.setCACert(CERTIFICATE);` funktsioonist `connectWiFi`.

1. Funktsioonis `classifyImage` eemalda rida `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, mis määrab ennustuse võtme päises.

1. Laadi üles ja käivita oma kood. Suuna kaamera mõnele puuviljale ja vajuta C-nuppu. Väljund kuvatakse seeria monitoris:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Selle koodi leiad kaustast [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Sinu puuvilja kvaliteedi klassifikaatori programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.