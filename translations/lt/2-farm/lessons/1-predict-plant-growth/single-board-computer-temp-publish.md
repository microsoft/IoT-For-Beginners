<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T20:39:31+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "lt"
}
-->
# Publikuokite temperatūrą - Virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje publikuosite temperatūros reikšmes, kurias aptinka Raspberry Pi arba virtualus IoT įrenginys, naudodami MQTT, kad vėliau jos galėtų būti naudojamos GDD skaičiavimui.

## Publikuokite temperatūrą

Kai temperatūra yra nuskaityta, ją galima publikuoti per MQTT į tam tikrą „serverio“ kodą, kuris nuskaito reikšmes ir saugo jas, kad vėliau būtų galima naudoti GDD skaičiavimui.

### Užduotis - publikuokite temperatūrą

Užprogramuokite įrenginį publikuoti temperatūros duomenis.

1. Atidarykite `temperature-sensor` programėlės projektą, jei jis dar neatidarytas.

1. Pakartokite veiksmus, kuriuos atlikote 4-oje pamokoje, kad prisijungtumėte prie MQTT ir siųstumėte telemetriją. Naudosite tą patį viešąjį Mosquitto brokerį.

    Veiksmai yra šie:

    - Pridėkite MQTT pip paketą
    - Pridėkite kodą, kad prisijungtumėte prie MQTT brokerio
    - Pridėkite kodą, kad publikuotumėte telemetriją

    > ⚠️ Žr. [instrukcijas, kaip prisijungti prie MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) ir [instrukcijas, kaip siųsti telemetriją](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) iš 4-os pamokos, jei reikia.

1. Įsitikinkite, kad `client_name` atspindi šio projekto pavadinimą:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Telemetrijai, vietoj šviesos reikšmės siųskite temperatūros reikšmę, nuskaitytą iš DHT jutiklio, JSON dokumento savybėje, pavadintoje `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Temperatūros reikšmės nereikia skaityti labai dažnai – ji per trumpą laiką daug nesikeis, todėl nustatykite `time.sleep` į 10 minučių:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funkcija `sleep` priima laiką sekundėmis, todėl, kad būtų lengviau suprasti, reikšmė perduodama kaip skaičiavimo rezultatas. 60 s per minutę, taigi 10 x (60 s per minutę) suteikia 10 minučių uždelsimą.

1. Paleiskite kodą taip pat, kaip paleidote kodą iš ankstesnės užduoties dalies. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad CounterFit programėlė veikia ir drėgmės bei temperatūros jutikliai buvo sukurti tinkamuose kaiščiuose.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Šį kodą galite rasti [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) aplanke arba [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) aplanke.

😀 Jūs sėkmingai publikavote temperatūrą kaip telemetriją iš savo įrenginio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.