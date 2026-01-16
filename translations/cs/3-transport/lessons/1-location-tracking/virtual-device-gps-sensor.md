<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T21:43:45+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "cs"
}
-->
# Čtení GPS dat - Virtuální IoT zařízení

V této části lekce přidáte GPS senzor do svého virtuálního IoT zařízení a budete z něj číst hodnoty.

## Virtuální hardware

Virtuální IoT zařízení bude používat simulovaný GPS senzor, který je přístupný přes UART prostřednictvím sériového portu.

Fyzický GPS senzor má anténu, která zachycuje rádiové vlny z GPS satelitů a převádí GPS signály na GPS data. Virtuální verze toto simuluje tím, že vám umožňuje buď nastavit zeměpisnou šířku a délku, poslat surové NMEA věty, nebo nahrát GPX soubor s více lokacemi, které mohou být vráceny postupně.

> 🎓 NMEA věty budou pokryty později v této lekci

### Přidání senzoru do CounterFit

Pro použití virtuálního GPS senzoru je potřeba jej přidat do aplikace CounterFit.

#### Úkol - přidání senzoru do CounterFit

Přidejte GPS senzor do aplikace CounterFit.

1. Vytvořte novou Python aplikaci na svém počítači ve složce `gps-sensor` s jediným souborem `app.py` a Python virtuálním prostředím, a přidejte CounterFit pip balíčky.

    > ⚠️ Pokud potřebujete, můžete se podívat na [instrukce pro vytvoření a nastavení CounterFit Python projektu v lekci 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Nainstalujte další Pip balíček pro instalaci CounterFit shim, který dokáže komunikovat se senzory založenými na UART přes sériové připojení. Ujistěte se, že instalujete z terminálu s aktivovaným virtuálním prostředím.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Ujistěte se, že webová aplikace CounterFit běží.

1. Vytvořte GPS senzor:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte pole *Sensor type* a vyberte *UART GPS*.

    1. Nechte *Port* nastavený na */dev/ttyAMA0*.

    1. Vyberte tlačítko **Add** pro vytvoření GPS senzoru na portu `/dev/ttyAMA0`.

    ![Nastavení GPS senzoru](../../../../../translated_images/cs/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    GPS senzor bude vytvořen a objeví se v seznamu senzorů.

    ![Vytvořený GPS senzor](../../../../../translated_images/cs/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Programování GPS senzoru

Virtuální IoT zařízení nyní může být naprogramováno pro použití virtuálního GPS senzoru.

### Úkol - programování GPS senzoru

Naprogramujte aplikaci GPS senzoru.

1. Ujistěte se, že aplikace `gps-sensor` je otevřená ve VS Code.

1. Otevřete soubor `app.py`.

1. Přidejte následující kód na začátek `app.py` pro připojení aplikace k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Přidejte následující kód pod tento pro import potřebných knihoven, včetně knihovny pro CounterFit sériový port:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Tento kód importuje modul `serial` z Pip balíčku `counterfit_shims_serial`. Poté se připojuje k sériovému portu `/dev/ttyAMA0` - to je adresa sériového portu, který virtuální GPS senzor používá pro svůj UART port.

1. Přidejte následující kód pod tento pro čtení ze sériového portu a tisk hodnot do konzole:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Funkce `print_gps_data` je definována tak, aby tiskla řádek, který jí byl předán, do konzole.

    Poté kód běží v nekonečné smyčce, čte co nejvíce textových řádků ze sériového portu v každé iteraci smyčky. Pro každý řádek volá funkci `print_gps_data`.

    Po přečtení všech dat smyčka na 1 sekundu usne a poté se pokusí znovu.

1. Spusťte tento kód, ujistěte se, že používáte jiný terminál než ten, ve kterém běží aplikace CounterFit, aby aplikace CounterFit zůstala spuštěná.

1. Z aplikace CounterFit změňte hodnotu GPS senzoru. Můžete to udělat jedním z následujících způsobů:

    * Nastavte **Source** na `Lat/Lon` a zadejte konkrétní zeměpisnou šířku, délku a počet satelitů použitých k získání GPS fixu. Tato hodnota bude odeslána pouze jednou, takže zaškrtněte políčko **Repeat**, aby se data opakovala každou sekundu.

      ![GPS senzor s vybraným lat lon](../../../../../translated_images/cs/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Nastavte **Source** na `NMEA` a přidejte některé NMEA věty do textového pole. Všechny tyto hodnoty budou odeslány, s prodlevou 1 sekundy před každou novou větou GGA (fixace polohy).

      ![GPS senzor s nastavenými NMEA větami](../../../../../translated_images/cs/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Můžete použít nástroj jako [nmeagen.org](https://www.nmeagen.org) k vytvoření těchto vět nakreslením na mapě. Tyto hodnoty budou odeslány pouze jednou, takže zaškrtněte políčko **Repeat**, aby se data opakovala jednu sekundu poté, co byla všechna odeslána.

    * Nastavte **Source** na GPX soubor a nahrajte GPX soubor s trasovými lokacemi. GPX soubory můžete stáhnout z řady populárních mapovacích a turistických webů, jako je [AllTrails](https://www.alltrails.com/). Tyto soubory obsahují více GPS lokací jako trasu a GPS senzor vrátí každou novou lokaci v intervalech 1 sekundy.

      ![GPS senzor s nastaveným GPX souborem](../../../../../translated_images/cs/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Tyto hodnoty budou odeslány pouze jednou, takže zaškrtněte políčko **Repeat**, aby se data opakovala jednu sekundu poté, co byla všechna odeslána.

    Jakmile nastavíte GPS hodnoty, vyberte tlačítko **Set** pro potvrzení těchto hodnot na senzoru.

1. Uvidíte surový výstup z GPS senzoru, něco jako následující:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Tento kód najdete ve složce [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Vaše programování GPS senzoru bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.