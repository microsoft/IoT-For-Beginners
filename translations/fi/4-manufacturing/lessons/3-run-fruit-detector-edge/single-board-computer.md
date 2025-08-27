<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:52:28+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "fi"
}
-->
# Luokittele kuva IoT Edge -pohjaisella kuvantunnistimella - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä osassa oppituntia käytät IoT Edge -laitteella toimivaa kuvantunnistinta.

## Käytä IoT Edge -luokittelijaa

IoT-laite voidaan ohjata käyttämään IoT Edge -kuvantunnistinta. Kuvantunnistimen URL-osoite on `http://<IP-osoite tai nimi>/image`, jossa `<IP-osoite tai nimi>` korvataan IoT Edge -laitetta ajavan tietokoneen IP-osoitteella tai isäntänimellä.

Python-kirjasto Custom Visionille toimii vain pilvessä isännöityjen mallien kanssa, ei IoT Edge -laitteella isännöityjen mallien kanssa. Tämä tarkoittaa, että sinun täytyy käyttää REST API:a kutsuaksesi luokittelijaa.

### Tehtävä - käytä IoT Edge -luokittelijaa

1. Avaa `fruit-quality-detector`-projekti VS Codessa, jos se ei ole jo auki. Jos käytät virtuaalista IoT-laitetta, varmista, että virtuaalinen ympäristö on aktivoitu.

1. Avaa `app.py`-tiedosto ja poista import-lauseet `azure.cognitiveservices.vision.customvision.prediction` ja `msrest.authentication`.

1. Lisää seuraava import-toteutus tiedoston alkuun:

    ```python
    import requests
    ```

1. Poista kaikki koodi sen jälkeen, kun kuva on tallennettu tiedostoon, alkaen kohdasta `image_file.write(image.read())` tiedoston loppuun asti.

1. Lisää seuraava koodi tiedoston loppuun:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Korvaa `<URL>` luokittelijasi URL-osoitteella.

    Tämä koodi tekee REST POST -pyynnön luokittelijalle, lähettäen kuvan pyynnön runkona. Tulokset palautetaan JSON-muodossa, ja ne dekoodataan tulostamaan todennäköisyydet.

1. Suorita koodisi, osoittaen kamerasi hedelmiin, sopivaan kuvasarjaan tai hedelmiin, jotka näkyvät verkkokamerassasi, jos käytät virtuaalista IoT-laitteistoa. Näet tulosteen konsolissa:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Löydät tämän koodin [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) tai [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device) -kansiosta.

😀 Hedelmälaadun luokittelijaohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.