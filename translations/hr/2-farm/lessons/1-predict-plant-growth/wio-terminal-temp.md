<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T15:16:14+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "hr"
}
-->
# Mjerenje temperature - Wio Terminal

U ovom dijelu lekcije, dodat ćete senzor temperature na svoj Wio Terminal i očitavati vrijednosti temperature s njega.

## Hardver

Wio Terminal treba senzor temperature.

Senzor koji ćete koristiti je [DHT11 senzor za vlagu i temperaturu](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), koji kombinira 2 senzora u jednom paketu. Ovo je prilično popularan senzor, a postoji mnogo komercijalno dostupnih senzora koji kombiniraju mjerenje temperature, vlage, a ponekad i atmosferskog tlaka. Komponenta za mjerenje temperature je termistor s negativnim temperaturnim koeficijentom (NTC), što znači da se otpor smanjuje kako temperatura raste.

Ovo je digitalni senzor, što znači da ima ugrađeni ADC koji stvara digitalni signal s podacima o temperaturi i vlazi koje mikrokontroler može očitati.

### Povezivanje senzora temperature

Grove senzor temperature može se povezati na digitalni port Wio Terminala.

#### Zadatak - povezivanje senzora temperature

Povežite senzor temperature.

![Grove senzor temperature](../../../../../translated_images/hr/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Umetnite jedan kraj Grove kabela u utičnicu na senzoru za vlagu i temperaturu. Kabel će se moći umetnuti samo na jedan način.

1. Dok je Wio Terminal isključen s vašeg računala ili drugog izvora napajanja, spojite drugi kraj Grove kabela na desnu Grove utičnicu na Wio Terminalu, gledajući prema ekranu. To je utičnica koja je najudaljenija od gumba za uključivanje.

![Grove senzor temperature povezan na desnu utičnicu](../../../../../translated_images/hr/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programiranje senzora temperature

Sada možete programirati Wio Terminal za korištenje povezanog senzora temperature.

### Zadatak - programiranje senzora temperature

Programirajte uređaj.

1. Napravite potpuno novi projekt za Wio Terminal koristeći PlatformIO. Nazovite ovaj projekt `temperature-sensor`. Dodajte kod u funkciju `setup` za konfiguraciju serijskog porta.

    > ⚠️ Možete se pozvati na [upute za stvaranje PlatformIO projekta u projektu 1, lekcija 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Dodajte ovisnost o biblioteci za Seeed Grove senzor vlage i temperature u datoteku `platformio.ini` projekta:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Možete se pozvati na [upute za dodavanje biblioteka u PlatformIO projekt u projektu 1, lekcija 4 ako je potrebno](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Dodajte sljedeće `#include` direktive na vrh datoteke, ispod postojećeg `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Ovo uključuje datoteke potrebne za interakciju sa senzorom. Zaglavlje `DHT.h` sadrži kod za sam senzor, a dodavanje zaglavlja `SPI.h` osigurava da je kod potreban za komunikaciju sa senzorom povezan prilikom kompilacije aplikacije.

1. Prije funkcije `setup`, deklarirajte DHT senzor:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Ovo deklarira instancu klase `DHT` koja upravlja **D**igitalnim **H**umidity i **T**emperature senzorom. Ovaj je povezan na port `D0`, desnu Grove utičnicu na Wio Terminalu. Drugi parametar govori kodu da se koristi senzor *DHT11* - biblioteka koju koristite podržava i druge varijante ovog senzora.

1. U funkciji `setup`, dodajte kod za postavljanje serijske veze:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Na kraju funkcije `setup`, nakon posljednjeg `delay`, dodajte poziv za pokretanje DHT senzora:

    ```cpp
    dht.begin();
    ```

1. U funkciji `loop`, dodajte kod za pozivanje senzora i ispis temperature na serijski port:

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

    Ovaj kod deklarira prazan niz od 2 broja s pomičnim zarezom (float) i prosljeđuje ga pozivu `readTempAndHumidity` na instanci `DHT`. Ovaj poziv popunjava niz s 2 vrijednosti - vlaga ide u 0. stavku niza (zapamtite, u C++ nizovima brojanje počinje od 0, tako da je 0. stavka 'prva' stavka u nizu), a temperatura ide u 1. stavku.

    Temperatura se očitava iz 1. stavke niza i ispisuje na serijski port.

    > 🇺🇸 Temperatura se očitava u Celzijusima. Za Amerikance, da biste je pretvorili u Fahrenheite, podijelite očitanu vrijednost u Celzijusima s 5, zatim pomnožite s 9 i dodajte 32. Na primjer, očitanje temperature od 20°C postaje ((20/5)*9) + 32 = 68°F.

1. Izgradite i učitajte kod na Wio Terminal.

    > ⚠️ Možete se pozvati na [upute za stvaranje PlatformIO projekta u projektu 1, lekcija 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Nakon učitavanja, možete pratiti temperaturu pomoću serijskog monitora:

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

> 💁 Ovaj kod možete pronaći u mapi [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Vaš program za senzor temperature je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.