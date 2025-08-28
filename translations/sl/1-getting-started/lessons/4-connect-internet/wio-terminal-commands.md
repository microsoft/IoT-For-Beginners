<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T13:49:44+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "sl"
}
-->
# Nadzorujte svojo nočno lučko prek interneta - Wio Terminal

V tem delu lekcije se boste naročili na ukaze, ki jih pošilja MQTT posrednik, in jih prejeli na vaš Wio Terminal.

## Naročanje na ukaze

Naslednji korak je naročanje na ukaze, ki jih pošilja MQTT posrednik, in ustrezno odzivanje nanje.

### Naloga

Naročite se na ukaze.

1. Odprite projekt nočne lučke v programu VS Code.

1. Na dno datoteke `config.h` dodajte naslednjo kodo, da določite ime teme za ukaze:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` je tema, na katero se bo naprava naročila, da prejme ukaze za LED.

1. Na konec funkcije `reconnectMQTTClient` dodajte naslednjo vrstico, da se naročite na temo ukazov, ko se MQTT odjemalec ponovno poveže:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Pod funkcijo `reconnectMQTTClient` dodajte naslednjo kodo.

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

    Ta funkcija bo povratni klic, ki ga bo MQTT odjemalec izvedel, ko prejme sporočilo s strežnika.

    Sporočilo je prejeto kot niz nepodpisanih 8-bitnih celih števil, zato ga je treba pretvoriti v niz znakov, da ga lahko obravnavamo kot besedilo.

    Sporočilo vsebuje JSON dokument, ki je dekodiran z uporabo knjižnice ArduinoJson. Lastnost `led_on` v JSON dokumentu se prebere, in glede na njeno vrednost se LED vklopi ali izklopi.

1. V funkcijo `createMQTTClient` dodajte naslednjo kodo:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Ta koda nastavi `clientCallback` kot povratni klic, ki se izvede, ko MQTT posrednik pošlje sporočilo.

    > 💁 Povratni klic `clientCallback` se izvede za vse teme, na katere ste naročeni. Če kasneje napišete kodo, ki posluša več tem, lahko iz parametra `topic`, ki je posredovan funkciji povratnega klica, pridobite temo, na katero je bilo sporočilo poslano.

1. Naložite kodo na vaš Wio Terminal in uporabite serijski monitor, da vidite, kako se svetlobne ravni pošiljajo MQTT posredniku.

1. Prilagodite svetlobne ravni, ki jih zazna vaša fizična ali virtualna naprava. V terminalu boste videli prejeta sporočila in poslane ukaze. Prav tako boste videli, kako se LED vklaplja in izklaplja glede na raven svetlobe.

> 💁 To kodo lahko najdete v mapi [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Uspešno ste napisali kodo, s katero se vaša naprava odziva na ukaze MQTT posrednika.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.