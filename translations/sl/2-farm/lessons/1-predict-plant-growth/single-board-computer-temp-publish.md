<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T15:14:27+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "sl"
}
-->
# Objavljanje temperature - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste objavili vrednosti temperature, ki jih zazna Raspberry Pi ali virtualna IoT naprava prek MQTT, da jih boste lahko kasneje uporabili za izračun GDD.

## Objavite temperaturo

Ko je temperatura prebrana, jo lahko objavite prek MQTT na neko 'strežniško' kodo, ki bo prebrala vrednosti in jih shranila za uporabo pri izračunu GDD.

### Naloga - objavite temperaturo

Programirajte napravo, da objavi podatke o temperaturi.

1. Odprite projekt aplikacije `temperature-sensor`, če še ni odprt.

1. Ponovite korake, ki ste jih izvedli v lekciji 4, da se povežete z MQTT in pošljete telemetrijo. Uporabili boste isti javni Mosquitto posrednik.

    Koraki za to so:

    - Dodajte pip paket za MQTT
    - Dodajte kodo za povezavo z MQTT posrednikom
    - Dodajte kodo za objavo telemetrije

    > ⚠️ Oglejte si [navodila za povezavo z MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) in [navodila za pošiljanje telemetrije](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) iz lekcije 4, če je potrebno.

1. Prepričajte se, da `client_name` odraža ime tega projekta:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Za telemetrijo namesto pošiljanja vrednosti svetlobe pošljite vrednost temperature, prebrano s senzorja DHT, v lastnosti JSON dokumenta, imenovani `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Vrednosti temperature ni treba brati zelo pogosto - v kratkem času se ne bo veliko spremenila, zato nastavite `time.sleep` na 10 minut:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funkcija `sleep` sprejme čas v sekundah, zato je za lažje branje vrednost podana kot rezultat izračuna. 60 sekund v minuti, torej 10 x (60 sekund v minuti) daje 10-minutno zakasnitev.

1. Zaženite kodo na enak način, kot ste zagnali kodo iz prejšnjega dela naloge. Če uporabljate virtualno IoT napravo, se prepričajte, da je aplikacija CounterFit zagnana in da so senzorji za vlago in temperaturo ustvarjeni na pravilnih pinih.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 To kodo lahko najdete v mapi [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) ali v mapi [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Uspešno ste objavili temperaturo kot telemetrijo iz vaše naprave.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.