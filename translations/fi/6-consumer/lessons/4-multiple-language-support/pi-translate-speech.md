# Käännä puhe - Raspberry Pi

Tässä osassa oppituntia kirjoitat koodia tekstin kääntämiseen käyttäen käännöspalvelua.

## Muunna teksti puheeksi käännöspalvelun avulla

Puhepalvelun REST API ei tue suoria käännöksiä, mutta voit käyttää Translator-palvelua kääntämään tekstin, joka on luotu puheesta tekstiksi -palvelulla, sekä puhuttujen vastausten tekstiä. Tämä palvelu tarjoaa REST API:n, jota voit käyttää tekstin kääntämiseen.

### Tehtävä - käytä käännösresurssia tekstin kääntämiseen

1. Älykäs ajastimesi käyttää kahta kieltä - palvelimen kieltä, jota käytettiin LUIS:n kouluttamiseen (sama kieli käytetään myös käyttäjälle puhuttavien viestien luomiseen), ja käyttäjän puhumaa kieltä. Päivitä `language`-muuttuja käyttäjän puhumaksi kieleksi ja lisää uusi muuttuja nimeltä `server_language` LUIS:n koulutuksessa käytetylle kielelle:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Korvaa `<user language>` kielen paikallisella nimellä, esimerkiksi `fr-FR` ranskalle tai `zn-HK` kantoninkiinalle.

    Korvaa `<server language>` LUIS:n koulutuksessa käytetyn kielen paikallisella nimellä.

    Löydät tuettujen kielten ja niiden paikalliset nimet [Microsoftin dokumentaatiosta kieli- ja äänitukisivulta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jos et puhu useita kieliä, voit käyttää palvelua kuten [Bing Translate](https://www.bing.com/translator) tai [Google Translate](https://translate.google.com) kääntääksesi suosikkikielestäsi valitsemaasi kieleen. Nämä palvelut voivat myös toistaa käännetyn tekstin äänenä.
    >
    > Esimerkiksi, jos koulutat LUIS:n englanniksi mutta haluat käyttää ranskaa käyttäjän kielenä, voit kääntää lauseita kuten "set a 2 minute and 27 second timer" englannista ranskaksi Bing Translaten avulla ja käyttää **Kuuntele käännös** -painiketta puhuaksesi käännöksen mikrofoniin.
    >
    > ![Kuuntele käännös -painike Bing Translatessa](../../../../../translated_images/fi/bing-translate.348aa796d6efe2a9.webp)

1. Lisää käännöspalvelun API-avain `speech_api_key`-muuttujan alle:

    ```python
    translator_api_key = '<key>'
    ```

    Korvaa `<key>` käännöspalveluresurssisi API-avaimella.

1. Määritä `say`-funktion yläpuolelle `translate_text`-funktio, joka kääntää tekstiä palvelinkielestä käyttäjän kieleen:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Funktiolle välitetään lähde- ja kohdekielet - sovelluksesi täytyy muuntaa käyttäjän kielestä palvelinkieleen puheen tunnistamisessa ja palvelinkielestä käyttäjän kieleen puhuttua palautetta varten.

1. Määritä funktion sisällä URL ja otsikot REST API -kutsua varten:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Tämän API:n URL ei ole sijaintikohtainen, vaan sijainti välitetään otsikkona. API-avain käytetään suoraan, joten toisin kuin puhepalvelussa, ei tarvitse hankkia käyttöoikeustunnusta tokenin myöntäjä API:lta.

1. Määritä tämän alle kutsun parametrit ja runko:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` määrittää API-kutsulle välitettävät parametrit, joissa välitetään lähde- ja kohdekielet. Tämä kutsu kääntää tekstin `from`-kielestä `to`-kieleen.

    `body` sisältää käännettävän tekstin. Tämä on taulukko, sillä samaan kutsuun voidaan kääntää useita tekstilohkoja.

1. Tee REST API -kutsu ja hae vastaus:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Palautettu vastaus on JSON-taulukko, jossa on yksi kohde, joka sisältää käännökset. Tämä kohde sisältää taulukon kaikista kutsun rungossa välitetyistä käännöksistä.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Palauta ensimmäisen kohteen ensimmäisen käännöksen `test`-ominaisuus:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Päivitä `while True` -silmukka kääntämään käyttäjän kielellä puhutun tekstin `convert_speech_to_text`-kutsusta palvelinkielelle:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Tämä koodi tulostaa myös alkuperäisen ja käännetyn tekstin konsoliin.

1. Päivitä `say`-funktio kääntämään palvelinkielellä puhuttava teksti käyttäjän kielelle:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Tämä koodi tulostaa myös alkuperäisen ja käännetyn tekstin konsoliin.

1. Suorita koodisi. Varmista, että funktiosovelluksesi on käynnissä, ja pyydä ajastinta käyttäjän kielellä joko puhumalla itse kyseistä kieltä tai käyttämällä käännössovellusta.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Eri kielten erilaiset ilmaisutavat voivat johtaa käännöksiin, jotka poikkeavat hieman LUIS:lle antamistasi esimerkeistä. Jos näin käy, lisää LUIS:lle enemmän esimerkkejä, kouluta malli uudelleen ja julkaise se uudelleen.

> 💁 Löydät tämän koodin [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) -kansiosta.

😀 Monikielinen ajastinohjelmasi oli menestys!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Pyrimme tarkkuuteen, mutta huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulee pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskääntämistä. Emme ole vastuussa tämän käännöksen käytöstä aiheutuvista väärinkäsityksistä tai virhetulkinnoista.