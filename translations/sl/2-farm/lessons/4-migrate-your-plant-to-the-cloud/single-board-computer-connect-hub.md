<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T15:03:44+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "sl"
}
-->
# Povežite svojo IoT napravo s cloudom - Virtualna IoT strojna oprema in Raspberry Pi

V tem delu lekcije boste svojo virtualno IoT napravo ali Raspberry Pi povezali z vašim IoT Hubom, da boste lahko pošiljali telemetrijo in prejemali ukaze.

## Povežite svojo napravo z IoT Hubom

Naslednji korak je povezava vaše naprave z IoT Hubom.

### Naloga - povezava z IoT Hubom

1. Odprite mapo `soil-moisture-sensor` v VS Code. Prepričajte se, da je virtualno okolje zagnano v terminalu, če uporabljate virtualno IoT napravo.

1. Namestite nekaj dodatnih Pip paketov:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` je knjižnica za komunikacijo z vašim IoT Hubom.

1. Dodajte naslednje uvoze na vrh datoteke `app.py`, pod obstoječimi uvozi:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Ta koda uvozi SDK za komunikacijo z vašim IoT Hubom.

1. Odstranite vrstico `import paho.mqtt.client as mqtt`, saj ta knjižnica ni več potrebna. Odstranite vso MQTT kodo, vključno z imeni tem, vso kodo, ki uporablja `mqtt_client`, in `handle_command`. Obdržite zanko `while True:`, samo izbrišite vrstico `mqtt_client.publish` iz te zanke.

1. Dodajte naslednjo kodo pod uvoznimi stavki:

    ```python
    connection_string = "<connection string>"
    ```

    Zamenjajte `<connection string>` z naborom za povezavo, ki ste ga pridobili za napravo prej v tej lekciji.

    > 💁 To ni najboljša praksa. Nabori za povezavo nikoli ne bi smeli biti shranjeni v izvorni kodi, saj jih je mogoče vključiti v sistem za nadzor izvorne kode in jih lahko najde kdorkoli. Tukaj to počnemo zaradi enostavnosti. Idealno bi bilo uporabiti nekaj, kot so okoljske spremenljivke, in orodje, kot je [`python-dotenv`](https://pypi.org/project/python-dotenv/). Več o tem boste izvedeli v eni od prihodnjih lekcij.

1. Pod to kodo dodajte naslednje, da ustvarite objekt odjemalca naprave, ki lahko komunicira z IoT Hubom, in ga povežite:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Zaženite to kodo. Videli boste, da se vaša naprava poveže.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Pošiljanje telemetrije

Zdaj, ko je vaša naprava povezana, lahko pošiljate telemetrijo v IoT Hub namesto v MQTT posrednik.

### Naloga - pošiljanje telemetrije

1. Dodajte naslednjo kodo znotraj zanke `while True`, tik pred ukazom za spanje:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Ta koda ustvari IoT Hub `Message`, ki vsebuje odčitek vlažnosti zemlje kot JSON niz, nato pa ga pošlje v IoT Hub kot sporočilo naprava-v-oblak.

## Obdelava ukazov

Vaša naprava mora obdelati ukaz iz strežniške kode za upravljanje releja. To je poslano kot zahteva za neposredno metodo.

## Naloga - obdelava zahteve za neposredno metodo

1. Dodajte naslednjo kodo pred zanko `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ta koda definira metodo `handle_method_request`, ki se bo klicala, ko IoT Hub pokliče neposredno metodo. Vsaka neposredna metoda ima ime, ta koda pa pričakuje metodo z imenom `relay_on` za vklop releja in `relay_off` za izklop releja.

    > 💁 To bi lahko bilo implementirano tudi v eni sami zahtevi za neposredno metodo, kjer bi se želeno stanje releja posredovalo v obliki podatkovnega paketa, ki ga je mogoče posredovati z zahtevo metode in je na voljo iz objekta `request`.

1. Neposredne metode zahtevajo odgovor, da sporočijo klicni kodi, da so bile obdelane. Dodajte naslednjo kodo na konec funkcije `handle_method_request`, da ustvarite odgovor na zahtevo:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Ta koda pošlje odgovor na zahtevo za neposredno metodo s statusno kodo HTTP 200 in ga pošlje nazaj v IoT Hub.

1. Dodajte naslednjo kodo pod definicijo te funkcije:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Ta koda pove IoT Hub odjemalcu, naj pokliče funkcijo `handle_method_request`, ko je klicana neposredna metoda.

> 💁 To kodo lahko najdete v mapi [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) ali [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Vaš program za senzor vlažnosti zemlje je povezan z vašim IoT Hubom!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.