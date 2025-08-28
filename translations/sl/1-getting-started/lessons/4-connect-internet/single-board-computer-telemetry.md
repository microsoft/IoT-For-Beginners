<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T13:52:15+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "sl"
}
-->
# Nadzorujte svojo nočno lučko prek interneta - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste poslali telemetrijo z ravnmi svetlobe iz svojega Raspberry Pi ali virtualne IoT naprave na MQTT posrednik.

## Pošiljanje telemetrije

Naslednji korak je ustvariti JSON dokument s telemetrijo in ga poslati na MQTT posrednik.

### Naloga

Pošljite telemetrijo na MQTT posrednik.

1. Odprite projekt nočne lučke v VS Code.

1. Če uporabljate virtualno IoT napravo, poskrbite, da terminal izvaja virtualno okolje. Če uporabljate Raspberry Pi, ne boste uporabljali virtualnega okolja.

1. Na vrh datoteke `app.py` dodajte naslednji uvoz:

    ```python
    import json
    ```

    Knjižnica `json` se uporablja za kodiranje telemetrije kot JSON dokumenta.

1. Dodajte naslednje za deklaracijo `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` je MQTT tema, na katero bo naprava objavljala ravni svetlobe.

1. Zamenjajte vsebino zanke `while True:` na koncu datoteke z naslednjim:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Ta koda zapakira raven svetlobe v JSON dokument in ga objavi na MQTT posrednik. Nato naredi premor, da zmanjša pogostost pošiljanja sporočil.

1. Zaženite kodo na enak način, kot ste zagnali kodo iz prejšnjega dela naloge. Če uporabljate virtualno IoT napravo, poskrbite, da je aplikacija CounterFit zagnana in da sta senzor svetlobe ter LED ustvarjena na ustreznih pinih.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 To kodo lahko najdete v mapi [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ali v mapi [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Uspešno ste poslali telemetrijo iz svoje naprave.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.