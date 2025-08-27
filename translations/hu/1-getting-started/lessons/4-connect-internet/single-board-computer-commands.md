<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T22:13:26+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "hu"
}
-->
# Vezéreld az éjszakai fényedet az interneten keresztül - Virtuális IoT eszköz és Raspberry Pi

A lecke ezen részében feliratkozol az MQTT broker által küldött parancsokra, hogy azokat a Raspberry Pi vagy virtuális IoT eszközöd fogadja.

## Feliratkozás parancsokra

A következő lépés az, hogy feliratkozz az MQTT broker által küldött parancsokra, és válaszolj rájuk.

### Feladat

Iratkozz fel a parancsokra.

1. Nyisd meg az éjszakai fény projektet a VS Code-ban.

1. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a terminál a virtuális környezetet futtatja. Ha Raspberry Pi-t használsz, akkor nem fogsz virtuális környezetet használni.

1. Add hozzá a következő kódot a `client_telemetry_topic` definíciói után:

    ```python
    server_command_topic = id + '/commands'
    ```

    A `server_command_topic` az az MQTT téma, amelyre az eszköz feliratkozik, hogy LED parancsokat fogadjon.

1. Add hozzá a következő kódot közvetlenül a fő ciklus fölé, a `mqtt_client.loop_start()` sor után:

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

    Ez a kód egy `handle_command` nevű függvényt definiál, amely egy üzenetet JSON dokumentumként olvas be, és megkeresi benne az `led_on` tulajdonság értékét. Ha az érték `True`, akkor a LED bekapcsol, ellenkező esetben kikapcsol.

    Az MQTT kliens feliratkozik arra a témára, amelyre a szerver üzeneteket küld, és beállítja, hogy a `handle_command` függvény fusson le, amikor egy üzenet érkezik.

    > 💁 Az `on_message` kezelő minden feliratkozott témára lefut. Ha később olyan kódot írsz, amely több témát figyel, az üzenet objektumból, amelyet a kezelő függvény kap, kiolvashatod, hogy melyik témára érkezett az üzenet.

1. Futtasd a kódot ugyanúgy, ahogy a feladat előző részében futtattad. Ha virtuális IoT eszközt használsz, győződj meg róla, hogy a CounterFit alkalmazás fut, és a fényérzékelő és LED a megfelelő lábakon lett létrehozva.

1. Állítsd be a fizikai vagy virtuális eszközöd által érzékelt fény szintjét. Az érkező üzenetek és küldött parancsok megjelennek a terminálban. A LED a fény szintjétől függően be- és kikapcsol.

> 💁 Ezt a kódot megtalálod a [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) mappában vagy a [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) mappában.

😀 Sikeresen megírtad a kódot, amely lehetővé teszi, hogy az eszközöd reagáljon az MQTT broker parancsaira.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.