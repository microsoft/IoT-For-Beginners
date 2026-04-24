# Čtení GPS dat - Raspberry Pi

V této části lekce přidáte k Raspberry Pi GPS senzor a budete z něj číst hodnoty.

## Hardware

Raspberry Pi potřebuje GPS senzor.

Senzor, který budete používat, je [Grove GPS Air530 senzor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Tento senzor se může připojit k více GPS systémům pro rychlé a přesné určení polohy. Senzor se skládá ze dvou částí - hlavní elektroniky senzoru a externí antény připojené tenkým kabelem, která zachycuje rádiové vlny ze satelitů.

Jedná se o UART senzor, takže posílá GPS data přes UART.

## Připojení GPS senzoru

Grove GPS senzor lze připojit k Raspberry Pi.

### Úkol - připojení GPS senzoru

Připojte GPS senzor.

![Grove GPS senzor](../../../../../translated_images/cs/grove-gps-sensor.247943bf69b03f0d.webp)

1. Zasuňte jeden konec Grove kabelu do konektoru na GPS senzoru. Kabel lze zasunout pouze jedním směrem.

1. S vypnutým Raspberry Pi připojte druhý konec Grove kabelu do konektoru UART označeného **UART** na Grove Base hat připojeném k Pi. Tento konektor se nachází ve střední řadě na straně blíže k slotu na SD kartu, na opačné straně od USB portů a ethernetového konektoru.

    ![Grove GPS senzor připojený k UART konektoru](../../../../../translated_images/cs/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Umístěte GPS senzor tak, aby připojená anténa měla viditelnost na oblohu - ideálně vedle otevřeného okna nebo venku. Je snazší získat jasnější signál, pokud anténě nic nepřekáží.

## Programování GPS senzoru

Raspberry Pi nyní může být naprogramováno pro použití připojeného GPS senzoru.

### Úkol - programování GPS senzoru

Naprogramujte zařízení.

1. Zapněte Pi a počkejte, až se spustí.

1. GPS senzor má 2 LED diody - modrou LED, která bliká při přenosu dat, a zelenou LED, která bliká každou sekundu při příjmu dat ze satelitů. Ujistěte se, že modrá LED bliká při zapnutí Pi. Po několika minutách začne blikat zelená LED - pokud ne, možná budete muset přemístit anténu.

1. Spusťte VS Code, buď přímo na Pi, nebo se připojte přes rozšíření Remote SSH.

    > ⚠️ Můžete se podívat na [instrukce pro nastavení a spuštění VS Code v lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. U novějších verzí Raspberry Pi, které podporují Bluetooth, existuje konflikt mezi sériovým portem používaným pro Bluetooth a tím, který používá Grove UART port. Pro vyřešení tohoto problému postupujte následovně:

    1. Z terminálu VS Code upravte soubor `/boot/config.txt` pomocí `nano`, vestavěného textového editoru terminálu, pomocí následujícího příkazu:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Tento soubor nelze upravovat přímo ve VS Code, protože je potřeba použít `sudo` oprávnění, což je zvýšené oprávnění. VS Code neběží s tímto oprávněním.

    1. Pomocí kurzorových kláves přejděte na konec souboru, poté zkopírujte níže uvedený kód a vložte jej na konec souboru:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Vkládání můžete provést pomocí běžných klávesových zkratek pro vaše zařízení (`Ctrl+v` na Windows, Linux nebo Raspberry Pi OS, `Cmd+v` na macOS).

    1. Uložte tento soubor a ukončete nano stisknutím `Ctrl+x`. Stiskněte `y`, když budete dotázáni, zda chcete uložit upravený buffer, poté stiskněte `enter`, abyste potvrdili přepsání `/boot/config.txt`.

        > Pokud uděláte chybu, můžete ukončit bez uložení a poté tyto kroky zopakovat.

    1. Upravte soubor `/boot/cmdline.txt` v nano pomocí následujícího příkazu:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Tento soubor obsahuje několik dvojic klíč/hodnota oddělených mezerami. Odstraňte všechny dvojice klíč/hodnota pro klíč `console`. Pravděpodobně budou vypadat nějak takto:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Pomocí kurzorových kláves přejděte na tyto položky a poté je smažte pomocí běžných kláves `del` nebo `backspace`.

        Například pokud váš původní soubor vypadá takto:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Nová verze bude:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Postupujte podle výše uvedených kroků pro uložení tohoto souboru a ukončení nano.

    1. Restartujte Pi a poté se znovu připojte ve VS Code, jakmile se Pi restartuje.

1. Z terminálu vytvořte novou složku v domovském adresáři uživatele `pi` nazvanou `gps-sensor`. V této složce vytvořte soubor nazvaný `app.py`.

1. Otevřete tuto složku ve VS Code.

1. GPS modul posílá UART data přes sériový port. Nainstalujte balíček `pyserial` pomocí Pip, abyste mohli komunikovat se sériovým portem z vašeho Python kódu:

    ```sh
    pip3 install pyserial
    ```

1. Přidejte následující kód do vašeho souboru `app.py`:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Tento kód importuje modul `serial` z balíčku `pyserial`. Poté se připojí k sériovému portu `/dev/ttyAMA0` - to je adresa sériového portu, který Grove Pi Base Hat používá pro svůj UART port. Poté vymaže všechna existující data z tohoto sériového připojení.

    Dále je definována funkce `print_gps_data`, která vypisuje předaný řádek do konzole.

    Poté kód běží v nekonečné smyčce, čte co nejvíce řádků textu ze sériového portu v každé iteraci smyčky. Pro každý řádek volá funkci `print_gps_data`.

    Po přečtení všech dat smyčka na 1 sekundu usne a poté se pokusí znovu.

1. Spusťte tento kód. Uvidíte surový výstup z GPS senzoru, něco jako následující:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Pokud při zastavení a opětovném spuštění kódu dostanete jednu z následujících chyb, přidejte blok `try - except` do vaší while smyčky.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Tento kód najdete ve složce [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Programování vašeho GPS senzoru bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro kritické informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.