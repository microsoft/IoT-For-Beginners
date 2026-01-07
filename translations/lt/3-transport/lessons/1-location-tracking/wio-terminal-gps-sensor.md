<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-28T19:38:10+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "lt"
}
-->
# Skaitykite GPS duomenis - Wio Terminal

Šioje pamokos dalyje pridėsite GPS jutiklį prie savo Wio Terminal ir nuskaitysite jo duomenis.

## Aparatinė įranga

Wio Terminal reikalingas GPS jutiklis.

Jutiklis, kurį naudosite, yra [Grove GPS Air530 jutiklis](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Šis jutiklis gali prisijungti prie kelių GPS sistemų, kad greitai ir tiksliai nustatytų vietą. Jutiklis sudarytas iš dviejų dalių – pagrindinės elektronikos ir išorinės antenos, prijungtos plonu laidu, kad galėtų priimti radijo bangas iš palydovų.

Tai yra UART jutiklis, todėl GPS duomenis perduoda per UART.

### Prijunkite GPS jutiklį

Grove GPS jutiklis gali būti prijungtas prie Wio Terminal.

#### Užduotis - prijunkite GPS jutiklį

Prijunkite GPS jutiklį.

![Grove GPS jutiklis](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.lt.png)

1. Įstatykite vieną Grove kabelio galą į GPS jutiklio lizdą. Kabelis įsistatys tik viena kryptimi.

1. Kai Wio Terminal atjungtas nuo kompiuterio ar kito maitinimo šaltinio, prijunkite kitą Grove kabelio galą prie kairiojo Grove lizdo Wio Terminal, žiūrint į ekraną. Tai yra lizdas, esantis arčiausiai maitinimo mygtuko.

    ![Grove GPS jutiklis prijungtas prie kairiojo lizdo](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.lt.png)

1. Padėkite GPS jutiklį taip, kad prijungta antena turėtų matomumą į dangų – idealiai šalia atviro lango arba lauke. Antenai lengviau gauti aiškų signalą, kai nėra kliūčių.

1. Dabar galite prijungti Wio Terminal prie savo kompiuterio.

1. GPS jutiklis turi 2 LED lemputes – mėlyną LED, kuris mirksi, kai perduodami duomenys, ir žalią LED, kuris mirksi kas sekundę, kai gaunami duomenys iš palydovų. Įsitikinkite, kad mėlyna LED mirksi, kai įjungiate Wio Terminal. Po kelių minučių žalia LED turėtų pradėti mirksėti – jei ne, gali tekti perkelti anteną.

## Programuokite GPS jutiklį

Dabar Wio Terminal galima programuoti, kad naudotų prijungtą GPS jutiklį.

### Užduotis - programuokite GPS jutiklį

Programuokite įrenginį.

1. Sukurkite visiškai naują Wio Terminal projektą naudodami PlatformIO. Pavadinkite šį projektą `gps-sensor`. Pridėkite kodą į `setup` funkciją, kad sukonfigūruotumėte nuoseklųjį prievadą.

1. Pridėkite šį `include` direktyvą failo `main.cpp` viršuje. Tai įtraukia antraštės failą su funkcijomis, skirtomis konfigūruoti kairįjį Grove prievadą UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Po to pridėkite šią kodo eilutę, kad deklaruotumėte nuosekliojo prievado ryšį su UART prievadu:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Jums reikia pridėti šiek tiek kodo, kad nukreiptumėte kai kuriuos vidinius signalų apdorojimo įrenginius į šį nuoseklųjį prievadą. Pridėkite šį kodą po `Serial3` deklaracijos:

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

1. `setup` funkcijoje, po to, kai sukonfigūruotas `Serial` prievadas, sukonfigūruokite UART nuoseklųjį prievadą naudodami šį kodą:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Po šio kodo `setup` funkcijoje pridėkite šį kodą, kad prijungtumėte Grove piną prie nuosekliojo prievado:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Pridėkite šią funkciją prieš `loop` funkciją, kad išsiųstumėte GPS duomenis į nuosekliojo monitorių:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` funkcijoje pridėkite šį kodą, kad nuskaitytumėte iš UART nuosekliojo prievado ir išvestumėte duomenis į nuosekliojo monitorių:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Šis kodas nuskaito iš UART nuosekliojo prievado. Funkcija `readStringUntil` nuskaito iki terminatoriaus simbolio, šiuo atveju naujos eilutės. Tai nuskaito visą NMEA sakinį (NMEA sakiniai baigiasi naujos eilutės simboliu). Kol galima nuskaityti duomenis iš UART nuosekliojo prievado, jie nuskaitomi ir siunčiami į nuosekliojo monitorių per funkciją `printGPSData`. Kai daugiau duomenų nuskaityti neįmanoma, `loop` funkcija uždelsia 1 sekundę (1,000ms).

1. Sukurkite ir įkelkite kodą į Wio Terminal.

1. Įkėlus kodą, galite stebėti GPS duomenis naudodami nuosekliojo monitorių.

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

> 💁 Šį kodą galite rasti [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) aplanke.

😀 Jūsų GPS jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.