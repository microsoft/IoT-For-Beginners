# Matuokite temperatūrą - Wio Terminal

Šioje pamokos dalyje pridėsite temperatūros jutiklį prie savo Wio Terminal ir nuskaitysite temperatūros reikšmes iš jo.

## Aparatūra

Wio Terminal reikalingas temperatūros jutiklis.

Jutiklis, kurį naudosite, yra [DHT11 drėgmės ir temperatūros jutiklis](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), kuris sujungia 2 jutiklius viename pakete. Tai gana populiarus jutiklis, kurį galima rasti įvairiuose komerciškai prieinamuose modeliuose, sujungiančiuose temperatūrą, drėgmę ir kartais atmosferos slėgį. Temperatūros jutiklio komponentas yra termistorius su neigiamu temperatūros koeficientu (NTC), kurio varža mažėja, kai temperatūra didėja.

Tai yra skaitmeninis jutiklis, todėl jis turi integruotą ADC, kuris sukuria skaitmeninį signalą, turintį temperatūros ir drėgmės duomenis, kuriuos mikrovaldiklis gali nuskaityti.

### Prijunkite temperatūros jutiklį

Grove temperatūros jutiklis gali būti prijungtas prie Wio Terminal skaitmeninio prievado.

#### Užduotis - prijunkite temperatūros jutiklį

Prijunkite temperatūros jutiklį.

![Grove temperatūros jutiklis](../../../../../translated_images/lt/grove-dht11.07f8eafceee17004.webp)

1. Įstatykite vieną Grove kabelio galą į lizdą ant drėgmės ir temperatūros jutiklio. Kabelis įsistatys tik viena kryptimi.

1. Kai Wio Terminal yra atjungtas nuo kompiuterio ar kito maitinimo šaltinio, prijunkite kitą Grove kabelio galą prie dešiniojo Grove lizdo Wio Terminal, žiūrint į ekraną. Tai yra lizdas, esantis toliausiai nuo maitinimo mygtuko.

![Grove temperatūros jutiklis prijungtas prie dešiniojo lizdo](../../../../../translated_images/lt/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programuokite temperatūros jutiklį

Dabar Wio Terminal galima programuoti, kad naudotų prijungtą temperatūros jutiklį.

### Užduotis - programuokite temperatūros jutiklį

Programuokite įrenginį.

1. Sukurkite naują Wio Terminal projektą naudodami PlatformIO. Pavadinkite šį projektą `temperature-sensor`. Pridėkite kodą `setup` funkcijoje, kad sukonfigūruotumėte serijinį prievadą.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti PlatformIO projektą 1 projekte, 1 pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Pridėkite bibliotekos priklausomybę Seeed Grove drėgmės ir temperatūros jutiklio bibliotekai į projekto `platformio.ini` failą:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip pridėti bibliotekas į PlatformIO projektą 1 projekte, 4 pamokoje](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Pridėkite šiuos `#include` direktyvas failo viršuje, po esamo `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Tai importuoja failus, reikalingus sąveikai su jutikliu. `DHT.h` antraštės failas turi kodą, skirtą pačiam jutikliui, o `SPI.h` antraštės pridėjimas užtikrina, kad kodas, reikalingas sąveikai su jutikliu, bus susietas, kai programa bus kompiliuojama.

1. Prieš `setup` funkciją deklaruokite DHT jutiklį:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Tai deklaruoja `DHT` klasės egzempliorių, kuris valdo **D**igital **H**umidity ir **T**emperature jutiklį. Jis prijungtas prie prievado `D0`, dešiniojo Grove lizdo Wio Terminal. Antrasis parametras nurodo, kad naudojamas *DHT11* jutiklis - biblioteka, kurią naudojate, palaiko kitus šio jutiklio variantus.

1. `setup` funkcijoje pridėkite kodą, kad nustatytumėte serijinį ryšį:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. `setup` funkcijos pabaigoje, po paskutinio `delay`, pridėkite iškvietimą, kad paleistumėte DHT jutiklį:

    ```cpp
    dht.begin();
    ```

1. `loop` funkcijoje pridėkite kodą, kad iškviestumėte jutiklį ir atspausdintumėte temperatūrą į serijinį prievadą:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Šis kodas deklaruoja tuščią 2 plaukiojančių taškų masyvą ir perduoda jį `readTempAndHumidity` iškvietimui `DHT` egzemplioriuje. Šis iškvietimas užpildo masyvą 2 reikšmėmis - drėgmė įrašoma į 0-ąjį masyvo elementą (prisiminkite, kad C++ masyvai yra 0 pagrindo, todėl 0-asis elementas yra „pirmasis“ masyvo elementas), o temperatūra įrašoma į 1-ąjį elementą.

    Temperatūra nuskaitoma iš 1-ojo masyvo elemento ir atspausdinama į serijinį prievadą.

    > 🇺🇸 Temperatūra nuskaitoma Celsijaus laipsniais. Amerikiečiams, norint konvertuoti ją į Farenheito laipsnius, padalykite Celsijaus reikšmę iš 5, tada padauginkite iš 9 ir pridėkite 32. Pavyzdžiui, temperatūros reikšmė 20°C tampa ((20/5)*9) + 32 = 68°F.

1. Sukurkite ir įkelkite kodą į Wio Terminal.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti PlatformIO projektą 1 projekte, 1 pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Įkėlus, galite stebėti temperatūrą naudodami serijinį monitorių:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Šį kodą galite rasti [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) aplanke.

😀 Jūsų temperatūros jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Dėl svarbios informacijos rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.