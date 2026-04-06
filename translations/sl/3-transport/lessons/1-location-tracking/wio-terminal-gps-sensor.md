# Branje GPS podatkov - Wio Terminal

V tem delu lekcije boste dodali GPS senzor na vaš Wio Terminal in prebrali vrednosti iz njega.

## Strojna oprema

Wio Terminal potrebuje GPS senzor.

Senzor, ki ga boste uporabili, je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ta senzor se lahko poveže z več GPS sistemi za hitro in natančno določanje lokacije. Senzor je sestavljen iz dveh delov - osnovne elektronike senzorja in zunanje antene, ki je povezana s tankim kablom za sprejem radijskih valov s satelitov.

To je UART senzor, kar pomeni, da pošilja GPS podatke prek UART.

### Povežite GPS senzor

Grove GPS senzor lahko povežete z Wio Terminalom.

#### Naloga - povežite GPS senzor

Povežite GPS senzor.

![Grove GPS senzor](../../../../../translated_images/sl/grove-gps-sensor.247943bf69b03f0d.webp)

1. Vstavite en konec Grove kabla v vtičnico na GPS senzorju. Kabel bo šel v vtičnico samo v eni smeri.

1. Ko je Wio Terminal odklopljen od računalnika ali drugega vira napajanja, povežite drugi konec Grove kabla z levo Grove vtičnico na Wio Terminalu, ko gledate zaslon. To je vtičnica, ki je najbližje gumbu za vklop.

    ![Grove GPS senzor povezan z levo vtičnico](../../../../../translated_images/sl/wio-gps-sensor.19fd52b81ce58095.webp)

1. Postavite GPS senzor tako, da ima pritrjena antena vidljivost do neba - idealno ob odprtem oknu ali zunaj. Lažje je dobiti jasen signal, če anteni nič ne stoji na poti.

1. Zdaj lahko povežete Wio Terminal z računalnikom.

1. GPS senzor ima 2 LED lučki - modro LED, ki utripa, ko se prenašajo podatki, in zeleno LED, ki utripa vsako sekundo, ko prejema podatke s satelitov. Prepričajte se, da modra LED utripa, ko vklopite Wio Terminal. Po nekaj minutah bo začela utripati zelena LED - če ne, boste morda morali premakniti anteno.

## Programiranje GPS senzorja

Zdaj lahko Wio Terminal programirate za uporabo pritrjenega GPS senzorja.

### Naloga - programirajte GPS senzor

Programirajte napravo.

1. Ustvarite povsem nov projekt za Wio Terminal z uporabo PlatformIO. Poimenujte ta projekt `gps-sensor`. Dodajte kodo v funkcijo `setup`, da konfigurirate serijski port.

1. Na vrh datoteke `main.cpp` dodajte naslednjo direktivo za vključitev. Ta vključuje glavno datoteko s funkcijami za konfiguracijo leve Grove vtičnice za UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Pod to vrstico dodajte naslednjo vrstico kode za deklaracijo serijske povezave z UART portom:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Dodati morate nekaj kode za preusmeritev nekaterih notranjih signalnih obdelovalcev na ta serijski port. Dodajte naslednjo kodo pod deklaracijo `Serial3`:

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

1. V funkciji `setup`, pod konfiguracijo `Serial` porta, konfigurirajte UART serijski port z naslednjo kodo:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Pod to kodo v funkciji `setup` dodajte naslednjo kodo za povezavo Grove pina s serijskim portom:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Pred funkcijo `loop` dodajte naslednjo funkcijo za pošiljanje GPS podatkov na serijski monitor:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. V funkciji `loop` dodajte naslednjo kodo za branje iz UART serijskega porta in izpis na serijski monitor:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Ta koda bere iz UART serijskega porta. Funkcija `readStringUntil` bere do znaka za zaključek, v tem primeru nove vrstice. To bo prebralo celoten NMEA stavek (NMEA stavki se zaključijo z znakom nove vrstice). Dokler je mogoče brati podatke iz UART serijskega porta, se ti berejo in pošiljajo na serijski monitor prek funkcije `printGPSData`. Ko ni več podatkov za branje, funkcija `loop` počaka 1 sekundo (1.000 ms).

1. Sestavite in naložite kodo na Wio Terminal.

1. Ko je koda naložena, lahko spremljate GPS podatke z uporabo serijskega monitorja.

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

> 💁 To kodo lahko najdete v mapi [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Vaš program za GPS senzor je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.