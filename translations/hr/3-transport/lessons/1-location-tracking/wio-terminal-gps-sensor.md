# Čitanje GPS podataka - Wio Terminal

U ovom dijelu lekcije, dodat ćete GPS senzor na svoj Wio Terminal i očitati vrijednosti s njega.

## Hardver

Wio Terminal zahtijeva GPS senzor.

Senzor koji ćete koristiti je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ovaj senzor može se povezati s više GPS sustava za brzo i precizno određivanje lokacije. Senzor se sastoji od dva dijela - osnovne elektronike senzora i vanjske antene spojene tankim kabelom za primanje radio valova sa satelita.

Ovo je UART senzor, što znači da šalje GPS podatke putem UART-a.

### Povezivanje GPS senzora

Grove GPS senzor može se povezati s Wio Terminalom.

#### Zadatak - povezivanje GPS senzora

Povežite GPS senzor.

![Grove GPS senzor](../../../../../translated_images/hr/grove-gps-sensor.247943bf69b03f0d.webp)

1. Umetnite jedan kraj Grove kabela u utičnicu na GPS senzoru. Kabel će ući samo na jedan način.

1. Dok je Wio Terminal isključen s vašeg računala ili drugog izvora napajanja, spojite drugi kraj Grove kabela na lijevu Grove utičnicu na Wio Terminalu, gledajući prema zaslonu. To je utičnica najbliža gumbu za uključivanje.

    ![Grove GPS senzor povezan s lijevom utičnicom](../../../../../translated_images/hr/wio-gps-sensor.19fd52b81ce58095.webp)

1. Postavite GPS senzor tako da priložena antena ima vidljivost prema nebu - idealno pored otvorenog prozora ili vani. Signal će biti jasniji ako ništa ne ometa antenu.

1. Sada možete spojiti Wio Terminal na svoje računalo.

1. GPS senzor ima dvije LED diode - plavu LED diodu koja treperi kada se podaci prenose i zelenu LED diodu koja treperi svake sekunde kada prima podatke sa satelita. Provjerite treperi li plava LED dioda kada uključite Wio Terminal. Nakon nekoliko minuta, zelena LED dioda će početi treperiti - ako ne, možda ćete trebati premjestiti antenu.

## Programiranje GPS senzora

Wio Terminal sada se može programirati za korištenje priloženog GPS senzora.

### Zadatak - programiranje GPS senzora

Programirajte uređaj.

1. Napravite potpuno novi Wio Terminal projekt koristeći PlatformIO. Nazovite ovaj projekt `gps-sensor`. Dodajte kod u funkciju `setup` za konfiguraciju serijskog porta.

1. Dodajte sljedeću direktivu za uključivanje na vrh datoteke `main.cpp`. Ovo uključuje zaglavlje s funkcijama za konfiguraciju lijevog Grove porta za UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Ispod toga, dodajte sljedeći redak koda za deklaraciju serijske veze s UART portom:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Potrebno je dodati kod za preusmjeravanje nekih internih signalnih rukovatelja na ovaj serijski port. Dodajte sljedeći kod ispod deklaracije `Serial3`:

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

1. U funkciji `setup`, ispod konfiguracije `Serial` porta, konfigurirajte UART serijski port sljedećim kodom:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Ispod ovog koda u funkciji `setup`, dodajte sljedeći kod za povezivanje Grove pina sa serijskim portom:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Dodajte sljedeću funkciju prije funkcije `loop` za slanje GPS podataka na serijski monitor:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. U funkciji `loop`, dodajte sljedeći kod za čitanje s UART serijskog porta i ispis rezultata na serijski monitor:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Ovaj kod čita s UART serijskog porta. Funkcija `readStringUntil` čita do znaka terminatora, u ovom slučaju novog reda. Ovo će pročitati cijelu NMEA rečenicu (NMEA rečenice završavaju znakom novog reda). Dok god se podaci mogu čitati s UART serijskog porta, oni se čitaju i šalju na serijski monitor putem funkcije `printGPSData`. Kada više nema podataka za čitanje, `loop` odgađa za 1 sekundu (1.000 ms).

1. Izgradite i učitajte kod na Wio Terminal.

1. Nakon učitavanja, možete pratiti GPS podatke koristeći serijski monitor.

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

> 💁 Ovaj kod možete pronaći u mapi [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Vaš program za GPS senzor uspješno je završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.