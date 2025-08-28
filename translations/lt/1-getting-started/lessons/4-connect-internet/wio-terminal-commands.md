<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T19:56:19+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "lt"
}
-->
# Valdykite savo naktinę lemputę internetu - Wio Terminal

Šioje pamokos dalyje jūs prenumeruosite komandas, siunčiamas iš MQTT brokerio į jūsų Wio Terminal.

## Prenumeruokite komandas

Kitas žingsnis – prenumeruoti komandas, siunčiamas iš MQTT brokerio, ir į jas reaguoti.

### Užduotis

Prenumeruokite komandas.

1. Atidarykite naktinės lemputės projektą VS Code.

1. Pridėkite šį kodą į `config.h` failo apačią, kad apibrėžtumėte komandų temos pavadinimą:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` yra tema, kurią įrenginys prenumeruos, kad gautų LED komandas.

1. Pridėkite šią eilutę į `reconnectMQTTClient` funkcijos pabaigą, kad prenumeruotumėte komandų temą, kai MQTT klientas bus vėl prijungtas:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Pridėkite šį kodą žemiau `reconnectMQTTClient` funkcijos.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Ši funkcija bus atgalinis iškvietimas (callback), kurį MQTT klientas iškvies, kai gaus pranešimą iš serverio.

    Pranešimas gaunamas kaip nesigned 8 bitų sveikųjų skaičių masyvas, todėl jį reikia konvertuoti į simbolių masyvą, kad būtų galima apdoroti kaip tekstą.

    Pranešime yra JSON dokumentas, kuris dekoduojamas naudojant ArduinoJson biblioteką. JSON dokumento `led_on` savybė yra perskaitoma, ir priklausomai nuo jos reikšmės LED įjungiamas arba išjungiamas.

1. Pridėkite šį kodą į `createMQTTClient` funkciją:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Šis kodas nustato `clientCallback` kaip atgalinį iškvietimą, kuris bus iškviečiamas, kai MQTT brokeris atsiųs pranešimą.

    > 💁 `clientCallback` apdorojimo funkcija yra iškviečiama visoms prenumeruojamoms temoms. Jei vėliau rašysite kodą, kuris klausosi kelių temų, galite gauti temą, kuriai buvo išsiųstas pranešimas, iš `topic` parametro, perduoto atgalinio iškvietimo funkcijai.

1. Įkelkite kodą į savo Wio Terminal ir naudokite Serial Monitor, kad matytumėte šviesos lygius, siunčiamus į MQTT brokerį.

1. Pakeiskite šviesos lygius, kuriuos aptinka jūsų fizinis arba virtualus įrenginys. Terminale matysite gaunamus pranešimus ir siunčiamas komandas. Taip pat matysite, kaip LED įsijungia arba išsijungia priklausomai nuo šviesos lygio.

> 💁 Šį kodą galite rasti [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) aplanke.

😀 Jūs sėkmingai užkodavote savo įrenginį, kad jis reaguotų į komandas iš MQTT brokerio.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.