# Zachytenie obrázku - Virtuálny IoT hardvér

V tejto časti lekcie pridáte k svojmu virtuálnemu IoT zariadeniu kamerový senzor a prečítate z neho obrázky.

## Hardvér

Virtuálne IoT zariadenie bude používať simulovanú kameru, ktorá posiela obrázky buď zo súborov, alebo z vašej webkamery.

### Pridanie kamery do CounterFit

Ak chcete použiť virtuálnu kameru, musíte ju pridať do aplikácie CounterFit.

#### Úloha - pridanie kamery do CounterFit

Pridajte kameru do aplikácie CounterFit.

1. Vytvorte novú Python aplikáciu na svojom počítači v priečinku s názvom `fruit-quality-detector` s jediným súborom `app.py` a Python virtuálnym prostredím. Pridajte balíčky CounterFit cez pip.

    > ⚠️ Ak potrebujete, môžete sa odvolať na [pokyny na vytvorenie a nastavenie CounterFit Python projektu v lekcii 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Nainštalujte ďalší balíček cez pip na inštaláciu CounterFit shim, ktorý dokáže komunikovať s kamerovými senzormi simulovaním niektorých funkcií [Picamera Pip balíčka](https://pypi.org/project/picamera/). Uistite sa, že inštalujete tento balíček z terminálu s aktivovaným virtuálnym prostredím.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Uistite sa, že webová aplikácia CounterFit je spustená.

1. Vytvorte kameru:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *Camera*.

    1. Nastavte *Name* na `Picamera`.

    1. Vyberte tlačidlo **Add**, aby ste vytvorili kameru.

    ![Nastavenia kamery](../../../../../translated_images/sk/counterfit-create-camera.a5de97f59c0bd3cb.webp)

    Kamera bude vytvorená a zobrazí sa v zozname senzorov.

    ![Vytvorená kamera](../../../../../translated_images/sk/counterfit-camera.001ec52194c8ee5d.webp)

## Naprogramovanie kamery

Virtuálne IoT zariadenie teraz môže byť naprogramované na používanie virtuálnej kamery.

### Úloha - naprogramovanie kamery

Naprogramujte zariadenie.

1. Uistite sa, že aplikácia `fruit-quality-detector` je otvorená vo VS Code.

1. Otvorte súbor `app.py`.

1. Pridajte nasledujúci kód na začiatok súboru `app.py`, aby ste pripojili aplikáciu k CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridajte nasledujúci kód do súboru `app.py`:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Tento kód importuje niektoré potrebné knižnice, vrátane triedy `PiCamera` z knižnice counterfit_shims_picamera.

1. Pridajte nasledujúci kód pod tento na inicializáciu kamery:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Tento kód vytvorí objekt PiCamera a nastaví rozlíšenie na 640x480. Aj keď sú podporované vyššie rozlíšenia, klasifikátor obrázkov pracuje s oveľa menšími obrázkami (227x227), takže nie je potrebné zachytávať a posielať väčšie obrázky.

    Riadok `camera.rotation = 0` nastavuje rotáciu obrázku v stupňoch. Ak potrebujete otočiť obrázok z webkamery alebo súboru, nastavte túto hodnotu podľa potreby. Napríklad, ak chcete zmeniť obrázok banánu na webkamere v režime na šírku na režim na výšku, nastavte `camera.rotation = 90`.

1. Pridajte nasledujúci kód pod tento na zachytenie obrázku ako binárnych dát:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Tento kód vytvorí objekt `BytesIO` na uloženie binárnych dát. Obrázok sa načíta z kamery ako JPEG súbor a uloží sa do tohto objektu. Tento objekt má ukazovateľ polohy, ktorý určuje, kde sa nachádza v dátach, aby bolo možné neskôr zapisovať ďalšie dáta. Riadok `image.seek(0)` presunie tento ukazovateľ späť na začiatok, aby bolo možné neskôr prečítať všetky dáta.

1. Pod tento kód pridajte nasledujúci kód na uloženie obrázku do súboru:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Tento kód otvorí súbor s názvom `image.jpg` na zápis, potom prečíta všetky dáta z objektu `BytesIO` a zapíše ich do súboru.

    > 💁 Obrázok môžete zachytiť priamo do súboru namiesto objektu `BytesIO` tým, že názov súboru odovzdáte volaniu `camera.capture`. Dôvodom použitia objektu `BytesIO` je, že neskôr v tejto lekcii môžete obrázok poslať do klasifikátora obrázkov.

1. Nastavte obrázok, ktorý kamera v CounterFit zachytí. Môžete nastaviť *Source* na *File* a nahrať obrázkový súbor, alebo nastaviť *Source* na *WebCam*, a obrázky budú zachytávané z vašej webkamery. Uistite sa, že po výbere obrázku alebo webkamery stlačíte tlačidlo **Set**.

    ![CounterFit s nastaveným súborom ako zdrojom obrázku a webkamerou zobrazujúcou osobu držiacu banán v náhľade webkamery](../../../../../translated_images/sk/counterfit-camera-options.eb3bd5150a8e7dff.webp)

1. Obrázok bude zachytený a uložený ako `image.jpg` v aktuálnom priečinku. Tento súbor uvidíte v prieskumníkovi VS Code. Vyberte súbor, aby ste si obrázok prezreli. Ak je potrebné rotovať, aktualizujte riadok `camera.rotation = 0` podľa potreby a urobte ďalší obrázok.

> 💁 Tento kód nájdete v priečinku [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Programovanie vašej kamery bolo úspešné!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.