<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T22:17:40+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "fi"
}
-->
# Käännä puhe - Virtuaalinen IoT-laite

Tässä oppitunnin osassa kirjoitat koodia, joka kääntää puheen tekstiksi puhepalvelun avulla, ja sen jälkeen kääntää tekstin Translator-palvelun avulla ennen kuin luodaan puhuttu vastaus.

## Käytä puhepalvelua puheen kääntämiseen

Puhepalvelu voi ottaa puheen ja muuntaa sen tekstiksi samalla kielellä, mutta myös kääntää tuloksen muille kielille.

### Tehtävä - käytä puhepalvelua puheen kääntämiseen

1. Avaa `smart-timer`-projekti VS Codessa ja varmista, että virtuaalinen ympäristö on ladattu terminaaliin.

1. Lisää seuraavat tuontilauseet olemassa olevien tuontien alle:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Tämä tuo luokat, joita käytetään puheen kääntämiseen, sekä `requests`-kirjaston, jota käytetään myöhemmin tässä oppitunnissa Translator-palvelun kutsumiseen.

1. Älykäs ajastimesi käyttää kahta kieltä - palvelimen kieltä, jota käytettiin LUIS:n kouluttamiseen (sama kieli käytetään myös käyttäjälle puhuttavien viestien rakentamiseen), ja käyttäjän puhumaa kieltä. Päivitä `language`-muuttuja käyttäjän puhumaksi kieleksi ja lisää uusi muuttuja nimeltä `server_language` LUIS:n koulutuksessa käytetylle kielelle:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Korvaa `<user language>` kielen paikallisella nimellä, esimerkiksi `fr-FR` ranskalle tai `zn-HK` kantoninkiinalle.

    Korvaa `<server language>` LUIS:n koulutuksessa käytetyn kielen paikallisella nimellä.

    Löydät tuettujen kielten ja niiden paikalliset nimet [Microsoftin dokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jos et puhu useita kieliä, voit käyttää palvelua kuten [Bing Translate](https://www.bing.com/translator) tai [Google Translate](https://translate.google.com) kääntääksesi suosikkikielestäsi valitsemaasi kieleen. Nämä palvelut voivat myös toistaa käännetyn tekstin äänenä. Huomaa, että puhetunnistin saattaa ohittaa osan laitteesi äänilähdöstä, joten saatat tarvita lisälaitteen käännetyn tekstin toistamiseen.
    >
    > Esimerkiksi, jos koulutat LUIS:n englanniksi mutta haluat käyttää ranskaa käyttäjän kielenä, voit kääntää lauseita kuten "set a 2 minute and 27 second timer" englannista ranskaksi Bing Translaten avulla ja käyttää **Kuuntele käännös**-painiketta puhuaksesi käännöksen mikrofoniin.
    >
    > ![Kuuntele käännös -painike Bing Translatessa](../../../../../translated_images/fi/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Korvaa `recognizer_config` ja `recognizer`-määrittelyt seuraavilla:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Tämä luo käännöskonfiguraation, joka tunnistaa puheen käyttäjän kielellä ja luo käännöksiä käyttäjän ja palvelimen kielellä. Se käyttää tätä konfiguraatiota luodakseen käännöstunnistimen - puhetunnistimen, joka voi kääntää puhetunnistuksen tuloksen useille kielille.

    > 💁 Alkuperäinen kieli täytyy määrittää `target_languages`-asetuksessa, muuten et saa käännöksiä.

1. Päivitä `recognized`-funktio korvaamalla funktion sisältö seuraavalla:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Tämä koodi tarkistaa, tapahtuiko tunnistustapahtuma puheen kääntämisen vuoksi (tapahtuma voi tapahtua muulloinkin, kuten silloin kun puhe tunnistetaan mutta ei käännetä). Jos puhe käännettiin, se löytää käännöksen `args.result.translations`-sanakirjasta, joka vastaa palvelimen kieltä.

    `args.result.translations`-sanakirja käyttää avaimena paikallisasetuksen kieliosaa, ei koko asetusta. Esimerkiksi, jos pyydät käännöstä `fr-FR` ranskaksi, sanakirjassa on merkintä `fr`, ei `fr-FR`.

    Käännetty teksti lähetetään sitten IoT Hubiin.

1. Suorita tämä koodi testataksesi käännöksiä. Varmista, että funktiosovelluksesi on käynnissä, ja pyydä ajastinta käyttäjän kielellä joko puhumalla itse tai käyttämällä käännössovellusta.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Käännä teksti Translator-palvelun avulla

Puhepalvelu ei tue tekstin kääntämistä takaisin puheeksi, sen sijaan voit käyttää Translator-palvelua tekstin kääntämiseen. Tämä palvelu tarjoaa REST-rajapinnan, jota voit käyttää tekstin kääntämiseen.

### Tehtävä - käytä Translator-resurssia tekstin kääntämiseen

1. Lisää Translator-API-avain `speech_api_key`-avaimen alle:

    ```python
    translator_api_key = '<key>'
    ```

    Korvaa `<key>` Translator-palveluresurssisi API-avaimella.

1. Määritä `say`-funktion yläpuolelle `translate_text`-funktio, joka kääntää tekstin palvelimen kielestä käyttäjän kielelle:

    ```python
    def translate_text(text):
    ```

1. Määritä tämän funktion sisällä URL ja otsikot REST-rajapinnan kutsua varten:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Tämän API:n URL ei ole sijaintikohtainen, vaan sijainti välitetään otsikkona. API-avain käytetään suoraan, joten toisin kuin puhepalvelussa, ei tarvitse hankkia käyttöoikeustunnusta tokenin myöntäjä-API:sta.

1. Määritä tämän alle kutsun parametrit ja runko:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` määrittää parametrit, jotka välitetään API-kutsuun, välittäen lähde- ja kohdekielet. Tämä kutsu kääntää tekstin `from`-kielestä `to`-kieleen.

    `body` sisältää käännettävän tekstin. Tämä on taulukko, koska useita tekstilohkoja voidaan kääntää samassa kutsussa.

1. Tee REST-rajapinnan kutsu ja hanki vastaus:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Vastaus, joka saapuu, on JSON-taulukko, jossa on yksi kohde, joka sisältää käännökset. Tämä kohde sisältää taulukon kaikista rungossa välitettyjen kohteiden käännöksistä.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Palauta ensimmäisen kohteen ensimmäisen käännöksen `text`-ominaisuus:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Päivitä `say`-funktio kääntämään sanottava teksti ennen SSML:n luomista:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Tämä koodi myös tulostaa alkuperäisen ja käännetyn tekstin konsoliin.

1. Suorita koodisi. Varmista, että funktiosovelluksesi on käynnissä, ja pyydä ajastinta käyttäjän kielellä joko puhumalla itse tai käyttämällä käännössovellusta.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Eri kielten erilaisista ilmaisutavoista johtuen saatat saada käännöksiä, jotka poikkeavat hieman LUIS:lle antamistasi esimerkeistä. Jos näin käy, lisää LUIS:lle enemmän esimerkkejä, kouluta malli uudelleen ja julkaise se uudelleen.

> 💁 Löydät tämän koodin [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) -kansiosta.

😀 Monikielinen ajastinohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.