<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:51:40+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "sv"
}
-->
# Styr din nattlampa över Internet - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att skicka telemetri med ljusnivåer från din Raspberry Pi eller virtuella IoT-enhet till en MQTT-broker.

## Publicera telemetri

Nästa steg är att skapa ett JSON-dokument med telemetri och skicka det till MQTT-brokern.

### Uppgift

Publicera telemetri till MQTT-brokern.

1. Öppna nattlampa-projektet i VS Code.

1. Om du använder en virtuell IoT-enhet, se till att terminalen kör den virtuella miljön. Om du använder en Raspberry Pi behöver du inte använda en virtuell miljö.

1. Lägg till följande import högst upp i filen `app.py`:

    ```python
    import json
    ```

    Biblioteket `json` används för att koda telemetrin som ett JSON-dokument.

1. Lägg till följande efter deklarationen av `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` är MQTT-ämnet som enheten kommer att publicera ljusnivåerna till.

1. Ersätt innehållet i loopen `while True:` i slutet av filen med följande:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Den här koden paketerar ljusnivån i ett JSON-dokument och publicerar det till MQTT-brokern. Därefter pausas programmet för att minska frekvensen av skickade meddelanden.

1. Kör koden på samma sätt som du körde koden i den tidigare delen av uppgiften. Om du använder en virtuell IoT-enhet, se då till att CounterFit-appen körs och att ljussensorn och LED-lampan har skapats på rätt pinnar.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Du kan hitta den här koden i mappen [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) eller mappen [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Du har framgångsrikt skickat telemetri från din enhet.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.