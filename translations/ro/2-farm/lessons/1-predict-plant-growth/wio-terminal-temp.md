<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-28T11:35:38+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "ro"
}
-->
# Măsurarea temperaturii - Wio Terminal

În această parte a lecției, vei adăuga un senzor de temperatură la Wio Terminal și vei citi valorile de temperatură de la acesta.

## Hardware

Wio Terminal are nevoie de un senzor de temperatură.

Senzorul pe care îl vei folosi este un [senzor de umiditate și temperatură DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), care combină 2 senzori într-un singur pachet. Acesta este destul de popular, existând numeroși senzori disponibili comercial care combină temperatura, umiditatea și, uneori, presiunea atmosferică. Componenta senzorului de temperatură este un termistor cu coeficient negativ de temperatură (NTC), un termistor a cărui rezistență scade pe măsură ce temperatura crește.

Acesta este un senzor digital, având un ADC integrat pentru a crea un semnal digital care conține datele de temperatură și umiditate pe care microcontrolerul le poate citi.

### Conectarea senzorului de temperatură

Senzorul de temperatură Grove poate fi conectat la portul digital al Wio Terminal.

#### Sarcină - conectarea senzorului de temperatură

Conectează senzorul de temperatură.

![Un senzor de temperatură Grove](../../../../../translated_images/ro/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Introdu un capăt al cablului Grove în soclul senzorului de umiditate și temperatură. Acesta va intra doar într-un singur sens.

1. Cu Wio Terminal deconectat de la computer sau altă sursă de alimentare, conectează celălalt capăt al cablului Grove la soclul Grove din partea dreaptă a Wio Terminal, așa cum privești ecranul. Acesta este soclul cel mai îndepărtat de butonul de alimentare.

![Senzorul de temperatură Grove conectat la soclul din dreapta](../../../../../translated_images/ro/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programarea senzorului de temperatură

Acum, Wio Terminal poate fi programat pentru a utiliza senzorul de temperatură atașat.

### Sarcină - programarea senzorului de temperatură

Programează dispozitivul.

1. Creează un proiect nou pentru Wio Terminal folosind PlatformIO. Denumește acest proiect `temperature-sensor`. Adaugă cod în funcția `setup` pentru a configura portul serial.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui proiect PlatformIO în proiectul 1, lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Adaugă o dependență de bibliotecă pentru biblioteca Seeed Grove Humidity and Temperature sensor în fișierul `platformio.ini` al proiectului:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Poți consulta [instrucțiunile pentru adăugarea bibliotecilor într-un proiect PlatformIO în proiectul 1, lecția 4, dacă este necesar](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Adaugă următoarele directive `#include` în partea de sus a fișierului, sub `#include <Arduino.h>` existent:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Acestea importă fișierele necesare pentru a interacționa cu senzorul. Fișierul header `DHT.h` conține codul pentru senzorul propriu-zis, iar adăugarea header-ului `SPI.h` asigură că codul necesar pentru comunicarea cu senzorul este inclus atunci când aplicația este compilată.

1. Înainte de funcția `setup`, declară senzorul DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Aceasta declară o instanță a clasei `DHT` care gestionează senzorul digital de umiditate și temperatură. Acesta este conectat la portul `D0`, soclul Grove din partea dreaptă a Wio Terminal. Al doilea parametru indică faptul că senzorul utilizat este *DHT11* - biblioteca pe care o folosești suportă și alte variante ale acestui senzor.

1. În funcția `setup`, adaugă cod pentru configurarea conexiunii seriale:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. La sfârșitul funcției `setup`, după ultimul `delay`, adaugă un apel pentru a porni senzorul DHT:

    ```cpp
    dht.begin();
    ```

1. În funcția `loop`, adaugă cod pentru a apela senzorul și a afișa temperatura pe portul serial:

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

    Acest cod declară un array gol de 2 valori de tip float și îl transmite apelului `readTempAndHumidity` pe instanța `DHT`. Acest apel populează array-ul cu 2 valori - umiditatea este plasată în elementul 0 al array-ului (reține că în C++ array-urile sunt indexate de la 0, astfel încât elementul 0 este 'primul' element), iar temperatura este plasată în elementul 1.

    Temperatura este citită din elementul 1 al array-ului și afișată pe portul serial.

    > 🇺🇸 Temperatura este citită în Celsius. Pentru americani, pentru a converti această valoare în Fahrenheit, împarte valoarea Celsius citită la 5, apoi înmulțește cu 9 și adaugă 32. De exemplu, o citire de temperatură de 20°C devine ((20/5)*9) + 32 = 68°F.

1. Compilează și încarcă codul pe Wio Terminal.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui proiect PlatformIO în proiectul 1, lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. După ce codul a fost încărcat, poți monitoriza temperatura folosind monitorul serial:

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

> 💁 Poți găsi acest cod în folderul [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Programul senzorului de temperatură a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus utilizând serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.