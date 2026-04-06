# Măsurarea umidității solului - Wio Terminal

În această parte a lecției, vei adăuga un senzor capacitiv de umiditate a solului la Wio Terminal și vei citi valorile de la acesta.

## Hardware

Wio Terminal necesită un senzor capacitiv de umiditate a solului.

Senzorul pe care îl vei folosi este un [Senzor Capacitiv de Umiditate a Solului](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), care măsoară umiditatea solului detectând capacitatea acestuia, o proprietate care se schimbă odată cu variația umidității solului. Pe măsură ce umiditatea solului crește, tensiunea scade.

Acesta este un senzor analogic, deci se conectează la pini analogici pe Wio Terminal, folosind un ADC integrat pentru a crea o valoare între 0-1.023.

### Conectarea senzorului de umiditate a solului

Senzorul Grove de umiditate a solului poate fi conectat la portul analogic/digital configurabil al Wio Terminal.

#### Sarcină - conectează senzorul de umiditate a solului

Conectează senzorul de umiditate a solului.

![Un senzor Grove de umiditate a solului](../../../../../translated_images/ro/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Introdu un capăt al cablului Grove în soclul senzorului de umiditate a solului. Acesta va intra doar într-un singur mod.

1. Cu Wio Terminal deconectat de la computer sau altă sursă de alimentare, conectează celălalt capăt al cablului Grove la soclul din dreapta al Wio Terminal, așa cum privești ecranul. Acesta este soclul cel mai îndepărtat de butonul de alimentare.

![Senzorul Grove de umiditate a solului conectat la soclul din dreapta](../../../../../translated_images/ro/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Introdu senzorul de umiditate a solului în pământ. Acesta are o 'linie de poziție maximă' - o linie albă pe senzor. Introdu senzorul până la această linie, dar nu mai departe.

![Senzorul Grove de umiditate a solului în pământ](../../../../../translated_images/ro/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Acum poți conecta Wio Terminal la computerul tău.

## Programează senzorul de umiditate a solului

Wio Terminal poate fi acum programat pentru a utiliza senzorul de umiditate a solului atașat.

### Sarcină - programează senzorul de umiditate a solului

Programează dispozitivul.

1. Creează un proiect nou pentru Wio Terminal folosind PlatformIO. Denumește acest proiect `soil-moisture-sensor`. Adaugă cod în funcția `setup` pentru a configura portul serial.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui proiect PlatformIO în proiectul 1, lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Nu există o bibliotecă pentru acest senzor, dar poți citi de la pinul analogic folosind funcția integrată Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Începe prin configurarea pinului analogic pentru intrare, astfel încât valorile să poată fi citite de la acesta, adăugând următorul cod în funcția `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Acest cod setează pinul `A0`, pinul combinat analogic/digital, ca pin de intrare de la care poate fi citită tensiunea.

1. Adaugă următorul cod în funcția `loop` pentru a citi tensiunea de la acest pin:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Sub acest cod, adaugă următorul cod pentru a afișa valoarea pe portul serial:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. În final, adaugă o întârziere de 10 secunde la sfârșit:

    ```cpp
    delay(10000);
    ```

1. Construiește și încarcă codul pe Wio Terminal.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea unui proiect PlatformIO în proiectul 1, lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. După ce codul a fost încărcat, poți monitoriza umiditatea solului folosind monitorul serial. Adaugă apă în sol sau scoate senzorul din sol și observă cum se schimbă valoarea.

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

    În exemplul de mai sus, poți vedea cum tensiunea scade pe măsură ce se adaugă apă.

> 💁 Poți găsi acest cod în folderul [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Programul pentru senzorul de umiditate a solului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.