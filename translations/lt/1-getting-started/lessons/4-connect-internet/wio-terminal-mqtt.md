<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T19:56:51+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "lt"
}
-->
# Valdykite savo naktinę lemputę internetu - Wio Terminal

IoT įrenginys turi būti užprogramuotas taip, kad naudotų MQTT protokolą ir bendrautų su *test.mosquitto.org*, siųsdamas telemetrijos duomenis su šviesos jutiklio rodmenimis bei priimdamas komandas LED valdymui.

Šioje pamokos dalyje prijungsite savo Wio Terminal prie MQTT brokerio.

## Įdiekite WiFi ir MQTT Arduino bibliotekas

Norint bendrauti su MQTT brokeriu, reikia įdiegti keletą Arduino bibliotekų, kurios leis naudoti Wio Terminal WiFi lustą ir bendrauti per MQTT. Kurdami Arduino įrenginiams, galite naudoti daugybę bibliotekų, kurios yra atvirojo kodo ir suteikia įvairias funkcijas. Seeed skelbia bibliotekas, leidžiančias Wio Terminal bendrauti per WiFi. Kiti kūrėjai yra paskelbę bibliotekas, skirtas MQTT brokeriams, ir jūs naudosite jas savo įrenginyje.

Šios bibliotekos pateikiamos kaip šaltinio kodas, kurį galima automatiškai importuoti į PlatformIO ir sukompiliuoti jūsų įrenginiui. Tokiu būdu Arduino bibliotekos veiks bet kuriame įrenginyje, palaikančiame Arduino sistemą, jei tik įrenginys turi specifinę aparatūrą, reikalingą tai bibliotekai. Kai kurios bibliotekos, pavyzdžiui, Seeed WiFi bibliotekos, yra skirtos tik tam tikrai aparatūrai.

Bibliotekos gali būti įdiegtos globaliai ir sukompiliuotos, jei reikia, arba konkrečiam projektui. Šiai užduočiai bibliotekos bus įdiegtos į projektą.

✅ Daugiau apie bibliotekų valdymą ir kaip jas rasti bei įdiegti galite sužinoti [PlatformIO bibliotekų dokumentacijoje](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Užduotis - įdiekite WiFi ir MQTT Arduino bibliotekas

Įdiekite Arduino bibliotekas.

1. Atidarykite naktinės lemputės projektą VS Code.

1. Pridėkite šį kodą į `platformio.ini` failo pabaigą:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Tai importuoja Seeed WiFi bibliotekas. Sintaksė `@ <number>` nurodo specifinę bibliotekos versiją.

    > 💁 Galite pašalinti `@ <number>`, kad visada naudotumėte naujausią bibliotekos versiją, tačiau nėra garantijos, kad naujesnės versijos veiks su žemiau pateiktu kodu. Šis kodas buvo išbandytas su šia bibliotekos versija.

    Tai viskas, ką reikia padaryti norint pridėti bibliotekas. Kitą kartą, kai PlatformIO kompiliuos projektą, jis atsisiųs šių bibliotekų šaltinio kodą ir įtrauks jį į jūsų projektą.

1. Pridėkite šį kodą į `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Tai importuoja [PubSubClient](https://github.com/knolleary/pubsubclient), Arduino MQTT klientą.

## Prisijunkite prie WiFi

Dabar Wio Terminal gali būti prijungtas prie WiFi.

### Užduotis - prisijunkite prie WiFi

Prijunkite Wio Terminal prie WiFi.

1. Sukurkite naują failą `src` aplanke, pavadintą `config.h`. Tai galite padaryti pasirinkę `src` aplanką arba `main.cpp` failą viduje ir paspaudę **Naujo failo** mygtuką naršyklėje. Šis mygtukas pasirodo tik tada, kai jūsų žymeklis yra virš naršyklės.

    ![Naujo failo mygtukas](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.lt.png)

1. Pridėkite šį kodą į failą, kad apibrėžtumėte konstantas savo WiFi prisijungimo duomenims:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Pakeiskite `<SSID>` savo WiFi SSID. Pakeiskite `<PASSWORD>` savo WiFi slaptažodžiu.

1. Atidarykite `main.cpp` failą.

1. Pridėkite šias `#include` direktyvas failo viršuje:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Tai įtraukia antraštinius failus bibliotekoms, kurias pridėjote anksčiau, taip pat konfigūracijos antraštinį failą. Šie antraštiniai failai reikalingi, kad PlatformIO įtrauktų bibliotekų kodą. Jei šių antraštinių failų aiškiai neįtrauksite, kai kurie kodai nebus sukompiliuoti ir gausite kompiliavimo klaidų.

1. Pridėkite šį kodą virš `setup` funkcijos:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Šis kodas kartoja, kol įrenginys neprisijungia prie WiFi, ir bando prisijungti naudodamas SSID ir slaptažodį iš konfigūracijos antraštinio failo.

1. Pridėkite šios funkcijos iškvietimą `setup` funkcijos apačioje, po to, kai sukonfigūruojami pinai.

    ```cpp
    connectWiFi();
    ```

1. Įkelkite šį kodą į savo įrenginį, kad patikrintumėte, ar WiFi ryšys veikia. Tai turėtumėte matyti serijiniame monitoriuje.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Prisijunkite prie MQTT

Kai Wio Terminal prisijungia prie WiFi, jis gali prisijungti prie MQTT brokerio.

### Užduotis - prisijunkite prie MQTT

Prisijunkite prie MQTT brokerio.

1. Pridėkite šį kodą į `config.h` failo apačią, kad apibrėžtumėte prisijungimo duomenis MQTT brokeriui:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Pakeiskite `<ID>` unikaliu ID, kuris bus naudojamas kaip šio įrenginio kliento pavadinimas ir vėliau kaip temos, kurias šis įrenginys publikuoja ir prenumeruoja, pavadinimai. *test.mosquitto.org* brokeris yra viešas ir naudojamas daugelio žmonių, įskaitant kitus studentus, dirbančius su šia užduotimi. Turėdami unikalų MQTT kliento pavadinimą ir temos pavadinimus, užtikrinsite, kad jūsų kodas nesikirs su kitų žmonių kodu. Šio ID jums taip pat reikės, kai vėliau kursite serverio kodą šiai užduočiai.

    > 💁 Galite naudoti tokią svetainę kaip [GUIDGen](https://www.guidgen.com), kad sugeneruotumėte unikalų ID.

    `BROKER` yra MQTT brokerio URL.

    `CLIENT_NAME` yra unikalus šio MQTT kliento pavadinimas brokeriui.

1. Atidarykite `main.cpp` failą ir pridėkite šį kodą po `connectWiFi` funkcijos ir virš `setup` funkcijos:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Šis kodas sukuria WiFi klientą, naudodamas Wio Terminal WiFi bibliotekas, ir naudoja jį MQTT klientui sukurti.

1. Po šio kodo pridėkite:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Ši funkcija tikrina ryšį su MQTT brokeriu ir prisijungia iš naujo, jei ryšys nutrūksta. Ji kartoja, kol nėra prisijungusi, ir bando prisijungti naudodama unikalų kliento pavadinimą, apibrėžtą konfigūracijos antraštiniame faile.

    Jei prisijungimas nepavyksta, bandoma iš naujo po 5 sekundžių.

1. Pridėkite šį kodą po `reconnectMQTTClient` funkcijos:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Šis kodas nustato MQTT brokerį klientui, taip pat nustato atgalinio iškvietimo funkciją, kai gaunama žinutė. Tada bandoma prisijungti prie brokerio.

1. Iškvieskite `createMQTTClient` funkciją `setup` funkcijoje po to, kai prisijungiama prie WiFi.

1. Pakeiskite visą `loop` funkciją šiuo kodu:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Šis kodas pradeda nuo prisijungimo prie MQTT brokerio patikrinimo. Šie ryšiai gali lengvai nutrūkti, todėl verta reguliariai tikrinti ir prisijungti iš naujo, jei reikia. Tada jis iškviečia `loop` metodą MQTT kliente, kad apdorotų bet kokias žinutes, kurios ateina į prenumeruojamą temą. Ši programa yra vienos gijos, todėl žinutės negali būti gaunamos fone, todėl pagrindinėje gijoje reikia skirti laiko laukiančių žinučių apdorojimui.

    Galiausiai, 2 sekundžių uždelsimas užtikrina, kad šviesos lygiai nebūtų siunčiami per dažnai ir sumažina įrenginio energijos suvartojimą.

1. Įkelkite kodą į savo Wio Terminal ir naudokite serijinį monitorių, kad pamatytumėte, kaip įrenginys prisijungia prie WiFi ir MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Šį kodą galite rasti [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) aplanke.

😀 Jūs sėkmingai prijungėte savo įrenginį prie MQTT brokerio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Dėl svarbios informacijos rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.