<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T13:52:56+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "sl"
}
-->
# Nadzorujte svojo nočno lučko prek interneta - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije se boste naročili na ukaze, ki jih MQTT posrednik pošlje vašemu Raspberry Pi ali virtualni IoT napravi.

## Naročanje na ukaze

Naslednji korak je naročanje na ukaze, ki jih pošlje MQTT posrednik, in odzivanje nanje.

### Naloga

Naročite se na ukaze.

1. Odprite projekt nočne lučke v VS Code.

1. Če uporabljate virtualno IoT napravo, poskrbite, da terminal izvaja virtualno okolje. Če uporabljate Raspberry Pi, ne boste uporabljali virtualnega okolja.

1. Dodajte naslednjo kodo za definicijami `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` je MQTT tema, na katero se naprava naroči, da prejme ukaze za LED.

1. Dodajte naslednjo kodo tik nad glavno zanko, za vrstico `mqtt_client.loop_start()`:

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

    Ta koda definira funkcijo `handle_command`, ki bere sporočilo kot JSON dokument in išče vrednost lastnosti `led_on`. Če je nastavljena na `True`, se LED vklopi, sicer se izklopi.

    MQTT odjemalec se naroči na temo, na katero bo strežnik pošiljal sporočila, in nastavi funkcijo `handle_command`, ki se pokliče, ko je sporočilo prejeto.

    > 💁 Funkcija `on_message` se pokliče za vse teme, na katere ste naročeni. Če kasneje napišete kodo, ki posluša več tem, lahko iz objekta `message`, ki se prenese funkciji, pridobite temo, na katero je bilo sporočilo poslano.

1. Zaženite kodo na enak način, kot ste zagnali kodo iz prejšnjega dela naloge. Če uporabljate virtualno IoT napravo, poskrbite, da je aplikacija CounterFit zagnana in da sta senzor svetlobe ter LED ustvarjena na ustreznih pinih.

1. Prilagodite nivoje svetlobe, ki jih zazna vaša fizična ali virtualna naprava. Sporočila, ki jih prejmete, in ukazi, ki jih pošljete, bodo zapisani v terminal. LED se bo prav tako vklopila ali izklopila glede na nivo svetlobe.

> 💁 To kodo lahko najdete v mapi [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) ali v mapi [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Uspešno ste napisali kodo, ki omogoča, da se vaša naprava odziva na ukaze MQTT posrednika.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.