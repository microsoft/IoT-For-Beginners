<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T19:57:32+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "lt"
}
-->
# Valdykite savo naktinę lempą internetu – virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje siųsite telemetrijos duomenis apie šviesos lygį iš savo Raspberry Pi arba virtualaus IoT įrenginio į MQTT brokerį.

## Telemetrijos publikavimas

Kitas žingsnis – sukurti JSON dokumentą su telemetrijos duomenimis ir išsiųsti jį į MQTT brokerį.

### Užduotis

Publikuokite telemetriją MQTT brokeriui.

1. Atidarykite naktinės lempos projektą VS Code programoje.

1. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad terminale veikia virtuali aplinka. Jei naudojate Raspberry Pi, virtualios aplinkos naudoti nereikės.

1. Pridėkite šį importą į `app.py` failo viršų:

    ```python
    import json
    ```

    Biblioteka `json` naudojama telemetrijos duomenims užkoduoti kaip JSON dokumentą.

1. Pridėkite šį kodą po `client_name` deklaracijos:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` yra MQTT tema, į kurią įrenginys publikuos šviesos lygius.

1. Pakeiskite `while True:` ciklo turinį failo pabaigoje šiuo kodu:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Šis kodas supakuoja šviesos lygį į JSON dokumentą ir publikuoja jį MQTT brokeriui. Po to programa padaro pauzę, kad sumažintų siunčiamų pranešimų dažnį.

1. Paleiskite kodą taip pat, kaip paleidote kodą iš ankstesnės užduoties dalies. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad CounterFit programa veikia ir šviesos jutiklis bei LED yra sukurti tinkamuose kaiščiuose.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Šį kodą galite rasti [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) aplanke arba [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) aplanke.

😀 Jūs sėkmingai išsiuntėte telemetrijos duomenis iš savo įrenginio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.