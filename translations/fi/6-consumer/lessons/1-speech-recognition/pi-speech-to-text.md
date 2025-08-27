<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T22:43:03+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "fi"
}
-->
# Puhe tekstiksi - Raspberry Pi

Tässä osassa oppituntia kirjoitat koodia, joka muuntaa tallennetun äänen puheen tekstiksi käyttämällä puhepalvelua.

## Lähetä ääni puhepalveluun

Ääni voidaan lähettää puhepalveluun REST-rajapinnan avulla. Käyttääksesi puhepalvelua, sinun täytyy ensin pyytää käyttöoikeustunnus ja käyttää sitä REST-rajapinnan käyttämiseen. Nämä käyttöoikeustunnukset vanhenevat 10 minuutin kuluttua, joten koodisi tulisi pyytää niitä säännöllisesti varmistaakseen, että ne ovat aina ajan tasalla.

### Tehtävä - hanki käyttöoikeustunnus

1. Avaa `smart-timer`-projekti Pi-laitteellasi.

1. Poista `play_audio`-funktio. Sitä ei enää tarvita, koska et halua älykkään ajastimen toistavan takaisin sitä, mitä sanoit.

1. Lisää seuraava tuonti `app.py`-tiedoston alkuun:

    ```python
    import requests
    ```

1. Lisää seuraava koodi `while True`-silmukan yläpuolelle määrittääksesi puhepalvelun asetukset:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Korvaa `<key>` puhepalveluresurssisi API-avaimella. Korvaa `<location>` sijainnilla, jonka käytit luodessasi puhepalveluresurssin.

    Korvaa `<language>` kielen paikallisella nimellä, jolla aiot puhua, esimerkiksi `en-GB` englannille tai `zn-HK` kantoninkiin. Löydät listan tuetuista kielistä ja niiden paikallisista nimistä [Microsoftin dokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Lisää tämän alle seuraava funktio käyttöoikeustunnuksen hankkimiseksi:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Tämä kutsuu tunnuksen myöntämispisteen, välittäen API-avaimen otsikkona. Tämä kutsu palauttaa käyttöoikeustunnuksen, jota voidaan käyttää puhepalvelujen kutsumiseen.

1. Lisää tämän alle funktio, joka muuntaa tallennetun äänen puheen tekstiksi REST-rajapinnan avulla:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Määritä tässä funktiossa REST-rajapinnan URL ja otsikot:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Tämä rakentaa URL:n käyttäen puhepalveluresurssin sijaintia. Se täyttää otsikot käyttöoikeustunnuksella `get_access_token`-funktiosta sekä näytteenottotaajuudella, jota käytettiin äänen tallentamiseen. Lopuksi se määrittää joitakin parametreja, jotka välitetään URL:n mukana sisältäen äänen kielen.

1. Lisää tämän alle seuraava koodi REST-rajapinnan kutsumiseksi ja tekstin palauttamiseksi:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Tämä kutsuu URL:n ja dekoodaa JSON-arvon, joka tulee vastauksessa. Vastauksen `RecognitionStatus`-arvo osoittaa, onnistuiko puheen muuntaminen tekstiksi, ja jos arvo on `Success`, teksti palautetaan funktiosta, muuten palautetaan tyhjä merkkijono.

1. Määritä `while True:`-silmukan yläpuolelle funktio, joka käsittelee puheesta tekstiksi -palvelun palauttaman tekstin. Tämä funktio tulostaa tekstin konsoliin toistaiseksi.

    ```python
    def process_text(text):
        print(text)
    ```

1. Korvaa lopuksi `while True`-silmukan `play_audio`-kutsu `convert_speech_to_text`-funktion kutsulla, välittäen tekstin `process_text`-funktiolle:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Suorita koodi. Paina painiketta ja puhu mikrofoniin. Vapauta painike, kun olet valmis, ja ääni muunnetaan tekstiksi ja tulostetaan konsoliin.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Kokeile erilaisia lauseita sekä lauseita, joissa sanat kuulostavat samalta mutta tarkoittavat eri asioita. Esimerkiksi, jos puhut englantia, sano 'I want to buy two bananas and an apple too', ja huomaa, kuinka se käyttää oikeaa to, two ja too sanan kontekstin perusteella, ei pelkästään sen äänen perusteella.

> 💁 Löydät tämän koodin [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) -kansiosta.

😀 Puhe tekstiksi -ohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.