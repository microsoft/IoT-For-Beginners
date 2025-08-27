<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T21:53:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "sv"
}
-->
# Styr din nattlampa över Internet - Virtuell IoT-hårdvara och Raspberry Pi

IoT-enheten behöver programmeras för att kommunicera med *test.mosquitto.org* via MQTT för att skicka telemetrivärden med ljussensoravläsningar och ta emot kommandon för att styra LED-lampan.

I denna del av lektionen kommer du att ansluta din Raspberry Pi eller virtuella IoT-enhet till en MQTT-broker.

## Installera MQTT-klientpaketet

För att kommunicera med MQTT-brokern behöver du installera ett MQTT-bibliotek via pip, antingen på din Pi eller i din virtuella miljö om du använder en virtuell enhet.

### Uppgift

Installera pip-paketet

1. Öppna nattlampa-projektet i VS Code.

1. Om du använder en virtuell IoT-enhet, se till att terminalen kör den virtuella miljön. Om du använder en Raspberry Pi kommer du inte att använda en virtuell miljö.

1. Kör följande kommando för att installera MQTT-pip-paketet:

    ```sh
    pip3 install paho-mqtt
    ```

## Programmera enheten

Enheten är redo att programmeras.

### Uppgift

Skriv kod för enheten.

1. Lägg till följande import högst upp i filen `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Biblioteket `paho.mqtt.client` gör att din app kan kommunicera via MQTT.

1. Lägg till följande kod efter definitionerna av ljussensorn och LED-lampan:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Ersätt `<ID>` med ett unikt ID som kommer att användas som namnet på denna enhetsklient och senare för de ämnen som denna enhet publicerar och prenumererar på. Brokern *test.mosquitto.org* är offentlig och används av många människor, inklusive andra studenter som arbetar med denna uppgift. Att ha ett unikt MQTT-klientnamn och ämnesnamn säkerställer att din kod inte kolliderar med någon annans. Du kommer också att behöva detta ID när du skapar serverkoden senare i denna uppgift.

    > 💁 Du kan använda en webbplats som [GUIDGen](https://www.guidgen.com) för att generera ett unikt ID.

    `client_name` är ett unikt namn för denna MQTT-klient på brokern.

1. Lägg till följande kod under denna nya kod för att skapa ett MQTT-klientobjekt och ansluta till MQTT-brokern:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Denna kod skapar klientobjektet, ansluter till den offentliga MQTT-brokern och startar en bearbetningsloop som körs i en bakgrundstråd och lyssnar efter meddelanden på alla prenumererade ämnen.

1. Kör koden på samma sätt som du körde koden från den tidigare delen av uppgiften. Om du använder en virtuell IoT-enhet, se då till att CounterFit-appen körs och att ljussensorn och LED-lampan har skapats på rätt pinnar.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Du kan hitta denna kod i mappen [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) eller mappen [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Du har framgångsrikt anslutit din enhet till en MQTT-broker.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.