# Luokittele kuva - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa lähetät kameran ottaman kuvan Custom Vision -palveluun luokiteltavaksi.

## Lähetä kuvia Custom Vision -palveluun

Custom Vision -palvelulla on Python SDK, jota voit käyttää kuvien luokitteluun.

### Tehtävä - lähetä kuvia Custom Vision -palveluun

1. Avaa `fruit-quality-detector`-kansio VS Codessa. Jos käytät virtuaalista IoT-laitetta, varmista, että virtuaaliympäristö on käynnissä terminaalissa.

1. Python SDK kuvien lähettämiseen Custom Vision -palveluun on saatavilla Pip-pakettina. Asenna se seuraavalla komennolla:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Lisää seuraavat import-lauseet `app.py`-tiedoston alkuun:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Tämä tuo mukaan joitakin moduuleja Custom Vision -kirjastoista: yhden autentikointia varten ennusteen avaimella ja toisen, joka tarjoaa ennusteklienssin luokan Custom Vision -kutsuja varten.

1. Lisää seuraava koodi tiedoston loppuun:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Korvaa `<prediction_url>` URL-osoitteella, jonka kopioit aiemmin tämän oppitunnin *Prediction URL* -valintaikkunasta. Korvaa `<prediction key>` ennusteen avaimella, jonka kopioit samasta valintaikkunasta.

1. *Prediction URL* -valintaikkunan antama ennusteen URL on suunniteltu käytettäväksi suoraan REST-päätepistettä kutsuttaessa. Python SDK käyttää URL-osoitteen osia eri paikoissa. Lisää seuraava koodi hajottaaksesi URL-osoitteen tarvittaviin osiin:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Tämä jakaa URL-osoitteen, poimien päätepisteen `https://<location>.api.cognitive.microsoft.com`, projektin tunnuksen ja julkaistun iteraation nimen.

1. Luo ennustekohde suorittamaan ennuste seuraavalla koodilla:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` käärii ennusteen avaimen. Näitä käytetään sitten luomaan ennusteklienssi-objekti, joka osoittaa päätepisteeseen.

1. Lähetä kuva Custom Vision -palveluun seuraavalla koodilla:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Tämä palauttaa kuvan alkuun ja lähettää sen ennusteklienssille.

1. Näytä lopuksi tulokset seuraavalla koodilla:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Tämä käy läpi kaikki palautetut ennusteet ja näyttää ne terminaalissa. Palautetut todennäköisyydet ovat liukulukuja välillä 0-1, missä 0 tarkoittaa 0 %:n mahdollisuutta täsmätä tunnisteeseen ja 1 tarkoittaa 100 %:n mahdollisuutta.

    > 💁 Kuvanluokittelijat palauttavat prosenttiosuudet kaikille käytetyille tunnisteille. Jokaisella tunnisteella on todennäköisyys, että kuva vastaa kyseistä tunnistetta.

1. Suorita koodisi, kun kamerasi osoittaa hedelmään, sopivaan kuvaan tai hedelmään, joka näkyy verkkokamerassasi, jos käytät virtuaalista IoT-laitteistoa. Näet tulosteen konsolissa:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Voit nähdä otetun kuvan ja nämä arvot **Predictions**-välilehdellä Custom Vision -palvelussa.

    ![Banaani Custom Vision -palvelussa, ennustettu kypsäksi 56,8 % ja raaksi 43,1 %](../../../../../translated_images/fi/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Löydät tämän koodin [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) tai [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device) -kansiosta.

😀 Hedelmän laadun luokittelijaohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.