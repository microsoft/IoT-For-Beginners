<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T15:16:41+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "sl"
}
-->
# Merjenje temperature - Wio Terminal

V tem delu lekcije boste dodali temperaturni senzor na vaš Wio Terminal in iz njega prebrali temperaturne vrednosti.

## Strojna oprema

Wio Terminal potrebuje temperaturni senzor.

Senzor, ki ga boste uporabili, je [DHT11 senzor za vlago in temperaturo](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), ki združuje dva senzorja v enem paketu. Ta senzor je precej priljubljen, saj številni komercialno dostopni senzorji združujejo merjenje temperature, vlage in včasih tudi atmosferskega tlaka. Komponenta za merjenje temperature je termistor z negativnim temperaturnim koeficientom (NTC), kar pomeni, da se njegova upornost zmanjšuje z naraščanjem temperature.

To je digitalni senzor, zato ima vgrajen ADC, ki ustvari digitalni signal s podatki o temperaturi in vlagi, ki jih lahko mikrokrmilnik prebere.

### Povežite temperaturni senzor

Grove temperaturni senzor lahko povežete na digitalni priključek Wio Terminala.

#### Naloga - povežite temperaturni senzor

Povežite temperaturni senzor.

![Grove temperaturni senzor](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.sl.png)

1. En konec Grove kabla vstavite v vtičnico na senzorju za vlago in temperaturo. Kabel bo šel v vtičnico le v eni smeri.

1. Ko je Wio Terminal odklopljen od računalnika ali drugega vira napajanja, povežite drugi konec Grove kabla z desno Grove vtičnico na Wio Terminalu, gledano s sprednje strani zaslona. To je vtičnica, ki je najbolj oddaljena od gumba za vklop.

![Grove temperaturni senzor povezan z desno vtičnico](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a.sl.png)

## Programiranje temperaturnega senzorja

Zdaj lahko Wio Terminal programirate za uporabo priključenega temperaturnega senzorja.

### Naloga - programirajte temperaturni senzor

Programirajte napravo.

1. Ustvarite nov projekt za Wio Terminal z uporabo PlatformIO. Projekt poimenujte `temperature-sensor`. Dodajte kodo v funkcijo `setup`, da konfigurirate serijski priključek.

    > ⚠️ Navodila za ustvarjanje PlatformIO projekta najdete v [projektu 1, lekcija 1, če je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Dodajte knjižnično odvisnost za knjižnico Seeed Grove Humidity and Temperature senzorja v datoteko `platformio.ini` projekta:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Navodila za dodajanje knjižnic v PlatformIO projekt najdete v [projektu 1, lekcija 4, če je potrebno](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Na vrh datoteke, pod obstoječo vrstico `#include <Arduino.h>`, dodajte naslednje `#include` direktive:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    To uvozi datoteke, potrebne za interakcijo s senzorjem. Glavna datoteka `DHT.h` vsebuje kodo za sam senzor, medtem ko dodajanje `SPI.h` zagotovi, da je koda za komunikacijo s senzorjem vključena pri prevajanju aplikacije.

1. Pred funkcijo `setup` deklarirajte senzor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    To deklarira instanco razreda `DHT`, ki upravlja **D**igitalni **H**umidity in **T**emperature senzor. Ta je povezan na priključek `D0`, desno Grove vtičnico na Wio Terminalu. Drugi parameter pove kodi, da uporabljate senzor *DHT11* - knjižnica, ki jo uporabljate, podpira tudi druge različice tega senzorja.

1. V funkciji `setup` dodajte kodo za nastavitev serijske povezave:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Na koncu funkcije `setup`, po zadnjem `delay`, dodajte klic za zagon senzorja DHT:

    ```cpp
    dht.begin();
    ```

1. V funkciji `loop` dodajte kodo za klic senzorja in izpis temperature na serijski priključek:

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

    Ta koda deklarira prazen niz dveh plavajočih števil (float) in ga posreduje klicu `readTempAndHumidity` na instanci `DHT`. Ta klic napolni niz z dvema vrednostma - vlaga se shrani v 0. element niza (v C++ so nizi indeksirani z 0, zato je 0. element 'prvi' element), temperatura pa v 1. element.

    Temperatura se prebere iz 1. elementa niza in izpiše na serijski priključek.

    > 🇺🇸 Temperatura je izmerjena v stopinjah Celzija. Za Američane: za pretvorbo v Fahrenheit delite vrednost v Celziju s 5, nato pomnožite z 9 in dodajte 32. Na primer, odčitek temperature 20°C postane ((20/5)*9) + 32 = 68°F.

1. Sestavite in naložite kodo na Wio Terminal.

    > ⚠️ Navodila za ustvarjanje PlatformIO projekta najdete v [projektu 1, lekcija 1, če je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Ko je koda naložena, lahko spremljate temperaturo z uporabo serijskega monitorja:

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

> 💁 To kodo najdete v mapi [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Vaš program za temperaturni senzor je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.