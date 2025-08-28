<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T19:58:35+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "lt"
}
-->
# Valdykite savo naktinę lemputę internetu - Virtuali IoT įranga ir Raspberry Pi

IoT įrenginys turi būti užprogramuotas taip, kad naudotųsi *test.mosquitto.org* per MQTT protokolą, siųsdamas telemetrijos duomenis su šviesos jutiklio rodmenimis ir priimdamas komandas LED valdymui.

Šioje pamokos dalyje prijungsite savo Raspberry Pi arba virtualų IoT įrenginį prie MQTT brokerio.

## Įdiekite MQTT kliento paketą

Norėdami bendrauti su MQTT brokeriu, turite įdiegti MQTT bibliotekos pip paketą savo Pi arba virtualioje aplinkoje, jei naudojate virtualų įrenginį.

### Užduotis

Įdiekite pip paketą

1. Atidarykite naktinės lemputės projektą VS Code programoje.

1. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad terminale veikia virtuali aplinka. Jei naudojate Raspberry Pi, virtualios aplinkos nereikės.

1. Paleiskite šią komandą, kad įdiegtumėte MQTT pip paketą:

    ```sh
    pip3 install paho-mqtt
    ```

## Užprogramuokite įrenginį

Įrenginys paruoštas programavimui.

### Užduotis

Parašykite įrenginio kodą.

1. Pridėkite šį importą į `app.py` failo viršų:

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` biblioteka leidžia jūsų programai bendrauti per MQTT.

1. Pridėkite šį kodą po šviesos jutiklio ir LED apibrėžimų:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Pakeiskite `<ID>` į unikalų ID, kuris bus naudojamas kaip šio įrenginio kliento pavadinimas, o vėliau ir kaip temos, kurias šis įrenginys publikuoja ir prenumeruoja, pavadinimai. *test.mosquitto.org* brokeris yra viešas ir juo naudojasi daugybė žmonių, įskaitant kitus studentus, dirbančius su šia užduotimi. Unikalus MQTT kliento pavadinimas ir temų pavadinimai užtikrina, kad jūsų kodas nesikirs su kitų. Šio ID jums taip pat reikės, kai vėliau kursite serverio kodą šioje užduotyje.

    > 💁 Galite naudoti tokią svetainę kaip [GUIDGen](https://www.guidgen.com), kad sugeneruotumėte unikalų ID.

    `client_name` yra unikalus šio MQTT kliento pavadinimas brokeriui.

1. Pridėkite šį kodą žemiau naujojo kodo, kad sukurtumėte MQTT kliento objektą ir prisijungtumėte prie MQTT brokerio:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Šis kodas sukuria kliento objektą, prisijungia prie viešojo MQTT brokerio ir paleidžia apdorojimo ciklą, kuris veikia fono gijoje ir klausosi pranešimų iš bet kurių prenumeruojamų temų.

1. Paleiskite kodą taip pat, kaip paleidote kodą iš ankstesnės užduoties dalies. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad CounterFit programa veikia ir šviesos jutiklis bei LED yra sukurti tinkamuose pin'uose.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Šį kodą galite rasti [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) aplanke arba [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) aplanke.

😀 Jūs sėkmingai prijungėte savo įrenginį prie MQTT brokerio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.