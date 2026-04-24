# Citirea datelor GPS - Wio Terminal

În această parte a lecției, vei adăuga un senzor GPS la Wio Terminal și vei citi valorile de la acesta.

## Hardware

Wio Terminal are nevoie de un senzor GPS.

Senzorul pe care îl vei folosi este [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Acest senzor se poate conecta la mai multe sisteme GPS pentru o localizare rapidă și precisă. Senzorul este format din 2 părți - componentele electronice de bază ale senzorului și o antenă externă conectată printr-un fir subțire pentru a recepționa undele radio de la sateliți.

Acesta este un senzor UART, deci transmite datele GPS prin UART.

### Conectarea senzorului GPS

Senzorul Grove GPS poate fi conectat la Wio Terminal.

#### Sarcină - conectarea senzorului GPS

Conectează senzorul GPS.

![Un senzor Grove GPS](../../../../../translated_images/ro/grove-gps-sensor.247943bf69b03f0d.webp)

1. Introdu un capăt al cablului Grove în soclul senzorului GPS. Acesta va intra doar într-un singur mod.

1. Cu Wio Terminal deconectat de la computer sau de la altă sursă de alimentare, conectează celălalt capăt al cablului Grove la soclul Grove din partea stângă a Wio Terminal, așa cum privești ecranul. Acesta este soclul cel mai apropiat de butonul de alimentare.

    ![Senzorul Grove GPS conectat la soclul din stânga](../../../../../translated_images/ro/wio-gps-sensor.19fd52b81ce58095.webp)

1. Poziționează senzorul GPS astfel încât antena atașată să aibă vizibilitate către cer - ideal lângă o fereastră deschisă sau afară. Este mai ușor să obții un semnal clar fără obstacole în calea antenei.

1. Acum poți conecta Wio Terminal la computerul tău.

1. Senzorul GPS are 2 LED-uri - un LED albastru care clipește când datele sunt transmise și un LED verde care clipește la fiecare secundă când primește date de la sateliți. Asigură-te că LED-ul albastru clipește când pornești Wio Terminal. După câteva minute, LED-ul verde va începe să clipească - dacă nu, poate fi necesar să repoziționezi antena.

## Programarea senzorului GPS

Acum Wio Terminal poate fi programat pentru a utiliza senzorul GPS atașat.

### Sarcină - programarea senzorului GPS

Programează dispozitivul.

1. Creează un proiect nou pentru Wio Terminal folosind PlatformIO. Denumește acest proiect `gps-sensor`. Adaugă cod în funcția `setup` pentru a configura portul serial.

1. Adaugă următoarea directivă de includere în partea de sus a fișierului `main.cpp`. Aceasta include un fișier header cu funcții pentru configurarea portului Grove din stânga pentru UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Sub aceasta, adaugă următoarea linie de cod pentru a declara o conexiune de port serial la portul UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Trebuie să adaugi ceva cod pentru a redirecționa câțiva handleri de semnale interne către acest port serial. Adaugă următorul cod sub declarația `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. În funcția `setup`, sub configurarea portului `Serial`, configurează portul serial UART cu următorul cod:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Sub acest cod din funcția `setup`, adaugă următorul cod pentru a conecta pinul Grove la portul serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Adaugă următoarea funcție înainte de funcția `loop` pentru a trimite datele GPS către monitorul serial:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. În funcția `loop`, adaugă următorul cod pentru a citi de la portul serial UART și a afișa rezultatul pe monitorul serial:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Acest cod citește de la portul serial UART. Funcția `readStringUntil` citește până la un caracter terminator, în acest caz un caracter de linie nouă. Aceasta va citi o propoziție completă NMEA (propozițiile NMEA sunt terminate cu un caracter de linie nouă). Atâta timp cât datele pot fi citite de la portul serial UART, acestea sunt citite și trimise către monitorul serial prin funcția `printGPSData`. Odată ce nu mai pot fi citite date, `loop` întârzie pentru 1 secundă (1.000ms).

1. Construiește și încarcă codul pe Wio Terminal.

1. După ce codul a fost încărcat, poți monitoriza datele GPS folosind monitorul serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Poți găsi acest cod în folderul [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Programul senzorului GPS a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.