<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T19:57:52+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "lt"
}
-->
# Valdykite savo naktinę lemputę internetu – virtuali IoT įranga ir Raspberry Pi

Šioje pamokos dalyje jūs prenumeruosite komandas, siunčiamas iš MQTT brokerio į jūsų Raspberry Pi arba virtualų IoT įrenginį.

## Prenumeruokite komandas

Kitas žingsnis – prenumeruoti komandas, siunčiamas iš MQTT brokerio, ir į jas reaguoti.

### Užduotis

Prenumeruokite komandas.

1. Atidarykite naktinės lemputės projektą VS Code programoje.

1. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad terminale veikia virtuali aplinka. Jei naudojate Raspberry Pi, virtualios aplinkos naudoti nereikės.

1. Pridėkite šį kodą po `client_telemetry_topic` apibrėžimų:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` yra MQTT tema, kurią įrenginys prenumeruos, kad gautų LED komandas.

1. Pridėkite šį kodą tiesiai virš pagrindinio ciklo, po `mqtt_client.loop_start()` eilutės:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Šis kodas apibrėžia funkciją `handle_command`, kuri nuskaito pranešimą kaip JSON dokumentą ir ieško `led_on` savybės reikšmės. Jei ji nustatyta į `True`, LED įjungiamas, kitu atveju – išjungiamas.

    MQTT klientas prenumeruoja temą, kuria serveris siųs pranešimus, ir nustato, kad funkcija `handle_command` būtų iškviečiama, kai gaunamas pranešimas.

    > 💁 `on_message` apdorotojas yra iškviečiamas visoms prenumeruojamoms temoms. Jei vėliau rašysite kodą, kuris klausosi kelių temų, galite gauti temą, kuriai buvo išsiųstas pranešimas, iš `message` objekto, perduoto apdorotojo funkcijai.

1. Paleiskite kodą taip pat, kaip paleidote kodą iš ankstesnės užduoties dalies. Jei naudojate virtualų IoT įrenginį, įsitikinkite, kad veikia CounterFit programa ir šviesos jutiklis bei LED yra sukurti tinkamuose kaiščiuose.

1. Reguliuokite šviesos lygį, kurį aptinka jūsų fizinis arba virtualus įrenginys. Terminale bus rašomi gaunami pranešimai ir siunčiamos komandos. LED taip pat bus įjungiamas ir išjungiamas priklausomai nuo šviesos lygio.

> 💁 Šį kodą galite rasti [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) aplanke arba [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) aplanke.

😀 Jūs sėkmingai užkodavote savo įrenginį, kad jis reaguotų į komandas iš MQTT brokerio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar neteisingus aiškinimus, atsiradusius dėl šio vertimo naudojimo.