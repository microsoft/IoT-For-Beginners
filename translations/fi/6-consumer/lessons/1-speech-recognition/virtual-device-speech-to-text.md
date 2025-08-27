<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T22:36:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "fi"
}
-->
# Puheesta tekstiksi - Virtuaalinen IoT-laite

Tässä osassa oppituntia kirjoitat koodia, joka muuntaa mikrofonistasi tallennetun puheen tekstiksi käyttämällä puhepalvelua.

## Muunna puhe tekstiksi

Windowsilla, Linuxilla ja macOS:llä puhepalveluiden Python SDK:ta voidaan käyttää mikrofonin kuuntelemiseen ja havaitun puheen muuntamiseen tekstiksi. Se kuuntelee jatkuvasti, tunnistaa äänitasot ja lähettää puheen tekstiksi muunnettavaksi, kun äänitaso laskee, esimerkiksi puheblokin lopussa.

### Tehtävä - muunna puhe tekstiksi

1. Luo tietokoneellesi uusi Python-sovellus kansioon nimeltä `smart-timer`, jossa on yksi tiedosto nimeltä `app.py` ja Python-virtuaaliympäristö.

1. Asenna puhepalveluiden Pip-paketti. Varmista, että asennat tämän terminaalista, jossa virtuaaliympäristö on aktivoitu.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Jos saat seuraavan virheen:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Sinun täytyy päivittää Pip. Tee tämä seuraavalla komennolla ja yritä sitten asentaa paketti uudelleen:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Lisää seuraavat tuonnit `app.py`-tiedostoon:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Tämä tuo luokkia, joita käytetään puheen tunnistamiseen.

1. Lisää seuraava koodi määrittääksesi konfiguraation:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Korvaa `<key>` puhepalvelusi API-avaimella. Korvaa `<location>` sijainnilla, jonka valitsit luodessasi puhepalveluresurssin.

    Korvaa `<language>` kielen paikallisella nimellä, jolla aiot puhua, esimerkiksi `en-GB` englannille tai `zn-HK` kantoninkiinaksi. Löydät luettelon tuetuista kielistä ja niiden paikallisista nimistä [Microsoftin dokumentaatiosta kieli- ja äänituen osiossa](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Tämä konfiguraatio luo `SpeechConfig`-objektin, jota käytetään puhepalveluiden konfigurointiin.

1. Lisää seuraava koodi luodaksesi puhetunnistimen:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Puhetunnistin toimii taustasäikeessä, kuunnellen ääntä ja muuntaen havaitun puheen tekstiksi. Voit saada tekstin käyttämällä takaisinsoittotoimintoa (callback function) - toimintoa, jonka määrität ja välität tunnistimelle. Joka kerta, kun puhe havaitaan, takaisinsoittoa kutsutaan. Lisää seuraava koodi määrittääksesi takaisinsoiton ja välitä tämä tunnistimelle sekä määritä toiminto tekstin käsittelyyn ja sen kirjoittamiseen konsoliin:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Tunnistin alkaa kuunnella vain, kun käynnistät sen nimenomaisesti. Lisää seuraava koodi käynnistääksesi tunnistuksen. Tämä toimii taustalla, joten sovelluksesi tarvitsee myös äärettömän silmukan, joka nukkuu pitääkseen sovelluksen käynnissä.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Suorita tämä sovellus. Puhu mikrofoniin, ja ääni muunnetaan tekstiksi, joka tulostetaan konsoliin.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Kokeile erilaisia lauseita sekä lauseita, joissa sanat kuulostavat samalta mutta tarkoittavat eri asioita. Esimerkiksi, jos puhut englantia, sano 'I want to buy two bananas and an apple too' ja huomaa, kuinka se käyttää oikeaa to, two ja too sanan kontekstin, ei vain äänen perusteella.

> 💁 Löydät tämän koodin [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) -kansiosta.

😀 Puheesta tekstiksi -ohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.