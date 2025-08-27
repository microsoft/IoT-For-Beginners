<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T21:38:33+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "fi"
}
-->
# Käytä X.509-sertifikaattia laitteesi koodissa - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä osassa oppituntia yhdistät virtuaalisen IoT-laitteesi tai Raspberry Pi:n IoT Hubiin X.509-sertifikaatin avulla.

## Yhdistä laitteesi IoT Hubiin

Seuraava vaihe on yhdistää laitteesi IoT Hubiin X.509-sertifikaattien avulla.

### Tehtävä - yhdistä IoT Hubiin

1. Kopioi avain- ja sertifikaattitiedostot kansioon, jossa IoT-laitteesi koodi sijaitsee. Jos käytät Raspberry Pi:tä VS Code Remote SSH:n kautta ja loit avaimet PC:lläsi tai Macillasi, voit vetää ja pudottaa tiedostot VS Code -tiedostonhallintaan kopioidaksesi ne.

1. Avaa tiedosto `app.py`

1. Jotta voit yhdistää X.509-sertifikaatin avulla, tarvitset IoT Hubin isäntänimen ja X.509-sertifikaatin. Aloita luomalla muuttuja, joka sisältää isäntänimen, lisäämällä seuraava koodi ennen laitteen asiakasohjelman luomista:

    ```python
    host_name = "<host_name>"
    ```

    Korvaa `<host_name>` IoT Hubisi isäntänimellä. Löydät sen `HostName`-kohdasta `connection_string`-muuttujassa. Se on IoT Hubisi nimi, joka päättyy `.azure-devices.net`.

1. Tämän alle, määritä muuttuja laitteen ID:lle:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Tarvitset `X509`-luokan instanssin, joka sisältää X.509-tiedostot. Lisää `X509` niiden luokkien listaan, jotka tuodaan `azure.iot.device`-moduulista:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Luo `X509`-luokan instanssi sertifikaatti- ja avaintiedostojesi avulla lisäämällä tämä koodi `host_name`-määrittelyn alle:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Tämä luo `X509`-luokan käyttäen tiedostoja `soil-moisture-sensor-x509-cert.pem` ja `soil-moisture-sensor-x509-key.pem`, jotka loit aiemmin.

1. Korvaa koodirivi, joka luo `device_client`-instanssin yhteysmerkkijonosta, seuraavalla:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Tämä yhdistää X.509-sertifikaatin avulla yhteysmerkkijonon sijaan.

1. Poista rivi, jossa määritellään `connection_string`-muuttuja.

1. Suorita koodisi. Seuraa IoT Hubiin lähetettyjä viestejä ja lähetä suoria metodipyyntöjä kuten aiemmin. Näet laitteen yhdistyvän ja lähettävän maaperän kosteuden lukemia sekä vastaanottavan suoria metodipyyntöjä.

> 💁 Löydät tämän koodin [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) tai [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) -kansiosta.

😀 Maaperän kosteusanturin ohjelmasi on yhdistetty IoT Hubiin X.509-sertifikaatin avulla!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.