# Čtení GPS dat - Wio Terminal

V této části lekce přidáte GPS senzor k vašemu Wio Terminalu a budete z něj číst hodnoty.

## Hardware

Wio Terminal potřebuje GPS senzor.

Senzor, který budete používat, je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Tento senzor se může připojit k více GPS systémům pro rychlé a přesné určení polohy. Senzor se skládá ze dvou částí - hlavní elektroniky senzoru a externí antény připojené tenkým kabelem, která zachycuje rádiové vlny ze satelitů.

Jedná se o UART senzor, takže posílá GPS data přes UART.

### Připojení GPS senzoru

Grove GPS senzor lze připojit k Wio Terminalu.

#### Úkol - připojte GPS senzor

Připojte GPS senzor.

![Grove GPS senzor](../../../../../translated_images/cs/grove-gps-sensor.247943bf69b03f0d.webp)

1. Zasuňte jeden konec Grove kabelu do konektoru na GPS senzoru. Kabel lze zasunout pouze jedním směrem.

1. S Wio Terminalem odpojeným od počítače nebo jiného zdroje napájení připojte druhý konec Grove kabelu do levého Grove konektoru na Wio Terminalu, když se díváte na obrazovku. Tento konektor je nejblíže k tlačítku napájení.

    ![Grove GPS senzor připojený k levému konektoru](../../../../../translated_images/cs/wio-gps-sensor.19fd52b81ce58095.webp)

1. Umístěte GPS senzor tak, aby připojená anténa měla viditelnost na oblohu - ideálně vedle otevřeného okna nebo venku. Je snazší získat jasnější signál, pokud anténě nic nepřekáží.

1. Nyní můžete připojit Wio Terminal k vašemu počítači.

1. GPS senzor má 2 LED diody - modrou LED, která bliká při přenosu dat, a zelenou LED, která bliká každou sekundu při příjmu dat ze satelitů. Ujistěte se, že modrá LED bliká, když zapnete Wio Terminal. Po několika minutách začne blikat zelená LED - pokud ne, možná budete muset přemístit anténu.

## Naprogramování GPS senzoru

Wio Terminal nyní může být naprogramován pro použití připojeného GPS senzoru.

### Úkol - naprogramujte GPS senzor

Naprogramujte zařízení.

1. Vytvořte zcela nový projekt pro Wio Terminal pomocí PlatformIO. Nazvěte tento projekt `gps-sensor`. Přidejte kód do funkce `setup` pro konfiguraci sériového portu.

1. Přidejte následující direktivu `include` na začátek souboru `main.cpp`. Tím zahrnete hlavičkový soubor s funkcemi pro konfiguraci levého Grove portu pro UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Pod tímto přidejte následující řádek kódu pro deklaraci sériového portu připojeného k UART portu:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Musíte přidat nějaký kód pro přesměrování některých interních signalizačních handlerů na tento sériový port. Přidejte následující kód pod deklaraci `Serial3`:

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

1. Ve funkci `setup` pod konfigurací portu `Serial` nakonfigurujte UART sériový port pomocí následujícího kódu:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Pod tímto kódem ve funkci `setup` přidejte následující kód pro připojení Grove pinu k sériovému portu:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Přidejte následující funkci před funkci `loop` pro odesílání GPS dat do sériového monitoru:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Ve funkci `loop` přidejte následující kód pro čtení z UART sériového portu a tisk výstupu do sériového monitoru:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Tento kód čte z UART sériového portu. Funkce `readStringUntil` čte až do terminátorového znaku, v tomto případě nového řádku. Tím se přečte celá NMEA věta (NMEA věty jsou ukončeny znakem nového řádku). Dokud lze číst data z UART sériového portu, jsou čtena a posílána do sériového monitoru prostřednictvím funkce `printGPSData`. Jakmile už nelze číst žádná data, funkce `loop` se zpozdí o 1 sekundu (1 000 ms).

1. Sestavte a nahrajte kód do Wio Terminalu.

1. Po nahrání můžete sledovat GPS data pomocí sériového monitoru.

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

> 💁 Tento kód najdete ve složce [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Programování GPS senzoru bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.