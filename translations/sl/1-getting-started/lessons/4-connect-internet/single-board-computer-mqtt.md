<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T13:54:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "sl"
}
-->
# Nadzorujte svojo nočno lučko prek interneta - Virtualna IoT strojna oprema in Raspberry Pi

IoT napravo je treba programirati tako, da komunicira s *test.mosquitto.org* prek MQTT za pošiljanje telemetrijskih vrednosti z odčitki svetlobnega senzorja in prejemanje ukazov za upravljanje LED diode.

V tem delu lekcije boste povezali svoj Raspberry Pi ali virtualno IoT napravo z MQTT posrednikom.

## Namestitev paketa MQTT odjemalca

Za komunikacijo z MQTT posrednikom morate na svojem Pi-ju ali v virtualnem okolju, če uporabljate virtualno napravo, namestiti knjižnico MQTT prek pip paketa.

### Naloga

Namestite pip paket

1. Odprite projekt nočne lučke v VS Code.

1. Če uporabljate virtualno IoT napravo, poskrbite, da terminal izvaja virtualno okolje. Če uporabljate Raspberry Pi, ne boste uporabljali virtualnega okolja.

1. Za namestitev MQTT pip paketa zaženite naslednji ukaz:

    ```sh
    pip3 install paho-mqtt
    ```

## Programiranje naprave

Naprava je pripravljena za programiranje.

### Naloga

Napišite kodo za napravo.

1. Na vrh datoteke `app.py` dodajte naslednji uvoz:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Knjižnica `paho.mqtt.client` omogoča vaši aplikaciji komunikacijo prek MQTT.

1. Po definicijah svetlobnega senzorja in LED dodajte naslednjo kodo:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Zamenjajte `<ID>` z unikatnim ID-jem, ki bo uporabljen kot ime tega odjemalca naprave, kasneje pa tudi za teme, ki jih ta naprava objavlja in na katere se naroča. Posrednik *test.mosquitto.org* je javen in ga uporablja veliko ljudi, vključno z drugimi študenti, ki delajo na tej nalogi. Unikatno ime MQTT odjemalca in tem zagotavlja, da se vaša koda ne bo spopadala s kodo drugih. Ta ID boste potrebovali tudi, ko boste kasneje v tej nalogi ustvarjali strežniško kodo.

    > 💁 Za ustvarjanje unikatnega ID-ja lahko uporabite spletno stran, kot je [GUIDGen](https://www.guidgen.com).

    `client_name` je unikatno ime za tega MQTT odjemalca na posredniku.

1. Pod to novo kodo dodajte naslednjo kodo za ustvarjanje MQTT odjemalca in povezavo z MQTT posrednikom:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Ta koda ustvari objekt odjemalca, se poveže z javnim MQTT posrednikom in zažene obdelovalno zanko, ki teče v ozadju in posluša sporočila na vseh naročenih temah.

1. Zaženite kodo na enak način, kot ste zagnali kodo iz prejšnjega dela naloge. Če uporabljate virtualno IoT napravo, poskrbite, da je aplikacija CounterFit zagnana in da sta svetlobni senzor in LED ustvarjena na pravilnih pinih.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 To kodo lahko najdete v mapi [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) ali v mapi [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Uspešno ste povezali svojo napravo z MQTT posrednikom.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitne nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.