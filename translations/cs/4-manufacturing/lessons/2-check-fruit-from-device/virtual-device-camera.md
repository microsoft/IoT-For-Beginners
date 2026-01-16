<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T20:56:30+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "cs"
}
-->
# Zachycení obrázku - Virtuální IoT hardware

V této části lekce přidáte kamerový senzor do svého virtuálního IoT zařízení a budete z něj číst obrázky.

## Hardware

Virtuální IoT zařízení bude používat simulovanou kameru, která posílá buď obrázky ze souborů, nebo z vaší webové kamery.

### Přidání kamery do CounterFit

Pro použití virtuální kamery je potřeba ji přidat do aplikace CounterFit.

#### Úkol - přidání kamery do CounterFit

Přidejte kameru do aplikace CounterFit.

1. Vytvořte novou Python aplikaci na svém počítači ve složce nazvané `fruit-quality-detector` s jediným souborem nazvaným `app.py` a Python virtuálním prostředím, a přidejte CounterFit pip balíčky.

    > ⚠️ Můžete se podívat na [instrukce pro vytvoření a nastavení CounterFit Python projektu v lekci 1, pokud je to potřeba](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Nainstalujte další Pip balíček, který přidá CounterFit shim, jenž dokáže komunikovat s kamerovými senzory simulací některých funkcí [Picamera Pip balíčku](https://pypi.org/project/picamera/). Ujistěte se, že instalaci provádíte z terminálu s aktivovaným virtuálním prostředím.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Ujistěte se, že webová aplikace CounterFit běží.

1. Vytvořte kameru:

    1. V poli *Create sensor* v panelu *Sensors* rozbalte pole *Sensor type* a vyberte *Camera*.

    1. Nastavte *Name* na `Picamera`.

    1. Vyberte tlačítko **Add** pro vytvoření kamery.

    ![Nastavení kamery](../../../../../translated_images/cs/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Kamera bude vytvořena a objeví se v seznamu senzorů.

    ![Vytvořená kamera](../../../../../translated_images/cs/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Programování kamery

Virtuální IoT zařízení nyní může být naprogramováno pro použití virtuální kamery.

### Úkol - programování kamery

Naprogramujte zařízení.

1. Ujistěte se, že aplikace `fruit-quality-detector` je otevřená ve VS Code.

1. Otevřete soubor `app.py`.

1. Přidejte následující kód na začátek souboru `app.py` pro připojení aplikace k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Přidejte následující kód do souboru `app.py`:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Tento kód importuje některé potřebné knihovny, včetně třídy `PiCamera` z knihovny counterfit_shims_picamera.

1. Přidejte následující kód pod tento pro inicializaci kamery:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Tento kód vytvoří objekt PiCamera, nastaví rozlišení na 640x480. Ačkoliv jsou podporována vyšší rozlišení, klasifikátor obrázků pracuje s mnohem menšími obrázky (227x227), takže není potřeba zachytávat a posílat větší obrázky.

    Řádek `camera.rotation = 0` nastavuje rotaci obrázku ve stupních. Pokud potřebujete otočit obrázek z webové kamery nebo souboru, nastavte tuto hodnotu podle potřeby. Například pokud chcete změnit obrázek banánu na webové kameře v režimu na šířku na režim na výšku, nastavte `camera.rotation = 90`.

1. Přidejte následující kód pod tento pro zachycení obrázku jako binárních dat:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Tento kód vytvoří objekt `BytesIO` pro uložení binárních dat. Obrázek je přečten z kamery jako JPEG soubor a uložen do tohoto objektu. Tento objekt má ukazatel pozice, který určuje, kde se nachází v datech, aby bylo možné přidávat další data na konec, pokud je to potřeba, takže řádek `image.seek(0)` posune tento ukazatel zpět na začátek, aby bylo možné později přečíst všechna data.

1. Pod tento kód přidejte následující pro uložení obrázku do souboru:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Tento kód otevře soubor nazvaný `image.jpg` pro zápis, poté přečte všechna data z objektu `BytesIO` a zapíše je do souboru.

    > 💁 Obrázek můžete zachytit přímo do souboru místo objektu `BytesIO` předáním názvu souboru do volání `camera.capture`. Důvodem použití objektu `BytesIO` je, že později v této lekci můžete obrázek poslat do svého klasifikátoru obrázků.

1. Nakonfigurujte obrázek, který kamera v CounterFit zachytí. Můžete buď nastavit *Source* na *File*, poté nahrát obrázkový soubor, nebo nastavit *Source* na *WebCam*, a obrázky budou zachyceny z vaší webové kamery. Ujistěte se, že po výběru obrázku nebo webové kamery stisknete tlačítko **Set**.

    ![CounterFit s nastaveným souborem jako zdrojem obrázku a webovou kamerou zobrazující osobu držící banán v náhledu webové kamery](../../../../../translated_images/cs/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Obrázek bude zachycen a uložen jako `image.jpg` v aktuální složce. Tento soubor uvidíte v průzkumníku VS Code. Vyberte soubor pro zobrazení obrázku. Pokud je potřeba rotace, upravte řádek `camera.rotation = 0` podle potřeby a pořiďte další snímek.

> 💁 Tento kód najdete ve složce [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Programování kamery bylo úspěšné!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.