<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T21:32:48+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "fi"
}
-->
# Yhdistä IoT-laitteesi pilveen - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa yhdistät virtuaalisen IoT-laitteesi tai Raspberry Pi:n IoT Hubiin, jotta voit lähettää telemetriatietoja ja vastaanottaa komentoja.

## Yhdistä laite IoT Hubiin

Seuraava vaihe on yhdistää laite IoT Hubiin.

### Tehtävä - yhdistä IoT Hubiin

1. Avaa `soil-moisture-sensor`-kansio VS Codessa. Varmista, että virtuaalinen ympäristö on käynnissä terminaalissa, jos käytät virtuaalista IoT-laitetta.

1. Asenna joitakin lisäpaketteja Pipin avulla:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` on kirjasto, joka mahdollistaa kommunikoinnin IoT Hubin kanssa.

1. Lisää seuraavat tuontilauseet `app.py`-tiedoston alkuun, olemassa olevien tuontien alapuolelle:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Tämä koodi tuo SDK:n, joka mahdollistaa kommunikoinnin IoT Hubin kanssa.

1. Poista `import paho.mqtt.client as mqtt` -rivi, sillä tätä kirjastoa ei enää tarvita. Poista kaikki MQTT-koodi, mukaan lukien aiheen nimet, kaikki koodi, joka käyttää `mqtt_client`-objektia, sekä `handle_command`. Säilytä `while True:` -silmukka, mutta poista `mqtt_client.publish` -rivi tästä silmukasta.

1. Lisää seuraava koodi tuontilauseiden alapuolelle:

    ```python
    connection_string = "<connection string>"
    ```

    Korvaa `<connection string>` yhteysmerkkijonolla, jonka hankit laitteelle aiemmin tässä oppitunnissa.

    > 💁 Tämä ei ole paras käytäntö. Yhteysmerkkijonoja ei koskaan pitäisi tallentaa lähdekoodiin, sillä ne voivat päätyä versionhallintaan ja olla kaikkien saatavilla. Teemme näin yksinkertaisuuden vuoksi. Ihanteellisesti sinun tulisi käyttää esimerkiksi ympäristömuuttujaa ja työkalua kuten [`python-dotenv`](https://pypi.org/project/python-dotenv/). Opit tästä lisää tulevassa oppitunnissa.

1. Lisää tämän koodin alapuolelle seuraava koodi, joka luo laiteasiakasobjektin IoT Hubin kanssa kommunikointia varten ja yhdistää sen:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Suorita tämä koodi. Näet laitteen yhdistyvän.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Lähetä telemetriatietoja

Nyt kun laite on yhdistetty, voit lähettää telemetriatietoja IoT Hubiin MQTT-välittäjän sijaan.

### Tehtävä - lähetä telemetriatietoja

1. Lisää seuraava koodi `while True` -silmukan sisään, juuri ennen `sleep`-komentoa:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Tämä koodi luo IoT Hubin `Message`-objektin, joka sisältää maaperän kosteuden lukeman JSON-merkkijonona, ja lähettää sen IoT Hubiin laitteesta pilveen -viestinä.

## Käsittele komentoja

Laitteesi täytyy käsitellä palvelinkoodista tuleva komento releen ohjaamiseksi. Tämä lähetetään suoran metodipyynnön muodossa.

## Tehtävä - käsittele suora metodipyyntö

1. Lisää seuraava koodi ennen `while True` -silmukkaa:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Tämä määrittää metodin, `handle_method_request`, joka kutsutaan, kun IoT Hub lähettää suoran metodipyynnön. Jokaisella suoralla metodilla on nimi, ja tämä koodi odottaa metodeja nimeltä `relay_on` releen kytkemiseksi päälle ja `relay_off` releen kytkemiseksi pois päältä.

    > 💁 Tämä voitaisiin toteuttaa myös yhdellä suoralla metodipyynnöllä, jossa haluttu releen tila välitetään metodipyynnön mukana ja on saatavilla `request`-objektista.

1. Suorat metodit vaativat vastauksen, joka kertoo kutsuvalle koodille, että ne on käsitelty. Lisää seuraava koodi `handle_method_request`-funktion loppuun, jotta voit luoda vastauksen pyyntöön:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Tämä koodi lähettää vastauksen suoraan metodipyyntöön HTTP-tilakoodilla 200 ja palauttaa sen IoT Hubiin.

1. Lisää seuraava koodi tämän funktion määrittelyn alapuolelle:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Tämä koodi kertoo IoT Hub -asiakasobjektille, että sen tulee kutsua `handle_method_request`-funktiota, kun suora metodi kutsutaan.

> 💁 Löydät tämän koodin [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi)- tai [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device)-kansiosta.

😀 Maaperän kosteusanturin ohjelma on yhdistetty IoT Hubiin!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.