<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-28T14:42:58+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "hr"
}
-->
# Mjerenje vlažnosti tla - Wio Terminal

U ovom dijelu lekcije, dodat ćete kapacitivni senzor vlažnosti tla na svoj Wio Terminal i očitavati vrijednosti s njega.

## Hardver

Wio Terminal zahtijeva kapacitivni senzor vlažnosti tla.

Senzor koji ćete koristiti je [Kapacitivni senzor vlažnosti tla](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), koji mjeri vlažnost tla detektiranjem kapaciteta tla, svojstva koje se mijenja ovisno o vlažnosti tla. Kako se vlažnost tla povećava, napon se smanjuje.

Ovo je analogni senzor, pa se povezuje na analogne pinove na Wio Terminalu, koristeći ugrađeni ADC za stvaranje vrijednosti od 0-1,023.

### Povezivanje senzora vlažnosti tla

Grove senzor vlažnosti tla može se povezati na Wio Terminalov konfigurabilni analogni/digitalni port.

#### Zadatak - povezivanje senzora vlažnosti tla

Povežite senzor vlažnosti tla.

![Grove senzor vlažnosti tla](../../../../../translated_images/hr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Umetnite jedan kraj Grove kabela u utičnicu na senzoru vlažnosti tla. Kabel će ući samo na jedan način.

1. Dok je Wio Terminal odspojen od vašeg računala ili drugog izvora napajanja, povežite drugi kraj Grove kabela s desnom Grove utičnicom na Wio Terminalu gledajući prema ekranu. To je utičnica najudaljenija od gumba za napajanje.

![Grove senzor vlažnosti tla povezan s desnom utičnicom](../../../../../translated_images/hr/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Umetnite senzor vlažnosti tla u tlo. Senzor ima 'liniju najvišeg položaja' - bijelu crtu preko senzora. Umetnite senzor do, ali ne preko ove linije.

![Grove senzor vlažnosti tla u tlu](../../../../../translated_images/hr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Sada možete povezati Wio Terminal s vašim računalom.

## Programiranje senzora vlažnosti tla

Wio Terminal sada može biti programiran za korištenje povezanog senzora vlažnosti tla.

### Zadatak - programiranje senzora vlažnosti tla

Programirajte uređaj.

1. Kreirajte potpuno novi projekt za Wio Terminal koristeći PlatformIO. Nazovite ovaj projekt `soil-moisture-sensor`. Dodajte kod u funkciju `setup` za konfiguraciju serijskog porta.

    > ⚠️ Možete se referirati na [upute za kreiranje PlatformIO projekta u projektu 1, lekcija 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Ne postoji biblioteka za ovaj senzor, umjesto toga možete očitavati s analognog pina koristeći ugrađenu Arduino funkciju [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Započnite konfiguriranjem analognog pina za ulaz kako bi se vrijednosti mogle očitavati dodavanjem sljedećeg u funkciju `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Ovo postavlja pin `A0`, kombinirani analogni/digitalni pin, kao ulazni pin s kojeg se može očitavati napon.

1. Dodajte sljedeće u funkciju `loop` za očitavanje napona s ovog pina:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Ispod ovog koda, dodajte sljedeći kod za ispis vrijednosti na serijski port:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Na kraju dodajte pauzu od 10 sekundi:

    ```cpp
    delay(10000);
    ```

1. Izgradite i učitajte kod na Wio Terminal.

    > ⚠️ Možete se referirati na [upute za kreiranje PlatformIO projekta u projektu 1, lekcija 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Nakon učitavanja, možete pratiti vlažnost tla koristeći serijski monitor. Dodajte malo vode u tlo ili uklonite senzor iz tla i promatrajte promjenu vrijednosti.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    U primjeru izlaza iznad, možete vidjeti kako napon opada dok se dodaje voda.

> 💁 Ovaj kod možete pronaći u mapi [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Vaš program za senzor vlažnosti tla bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden korištenjem AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.