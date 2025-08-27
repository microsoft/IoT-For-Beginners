<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T22:31:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "fi"
}
-->
# Teksti puheeksi - Virtuaalinen IoT-laite

Tässä osassa oppituntia kirjoitat koodia, joka muuntaa tekstin puheeksi käyttämällä puhepalvelua.

## Muunna teksti puheeksi

Puhepalveluiden SDK, jota käytit viime oppitunnilla muuntaaksesi puheen tekstiksi, voidaan käyttää tekstin muuntamiseen takaisin puheeksi. Kun pyydät puhetta, sinun täytyy määrittää käytettävä ääni, sillä puhetta voidaan tuottaa monilla eri äänillä.

Jokainen kieli tukee useita eri ääniä, ja voit saada listan tuetuista äänistä kullekin kielelle puhepalveluiden SDK:sta.

### Tehtävä - muunna teksti puheeksi

1. Avaa `smart-timer`-projekti VS Codessa ja varmista, että virtuaalinen ympäristö on ladattu terminaaliin.

1. Tuo `SpeechSynthesizer` `azure.cognitiveservices.speech`-paketista lisäämällä se olemassa oleviin tuonteihin:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Luo `say`-funktion yläpuolelle puhekonfiguraatio, jota käytetään puhesyntetisaattorin kanssa:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Tämä käyttää samaa API-avainta, sijaintia ja kieltä, joita käytettiin tunnistimessa.

1. Lisää tämän alle seuraava koodi, joka hakee äänen ja asettaa sen puhekonfiguraatioon:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Tämä hakee listan kaikista saatavilla olevista äänistä ja löytää ensimmäisen äänen, joka vastaa käytettävää kieltä.

    > 💁 Voit saada täydellisen listan tuetuista äänistä [Microsoft Docsin kieli- ja äänitukidokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jos haluat käyttää tiettyä ääntä, voit poistaa tämän funktion ja kovakoodata äänen dokumentaatiosta löytyvän äänen nimen mukaan. Esimerkiksi:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Päivitä `say`-funktion sisältö luomaan SSML vastaukselle:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Lisää tämän alle koodi, joka pysäyttää puhetunnistuksen, puhuu SSML:n ja käynnistää tunnistuksen uudelleen:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Tunnistus pysäytetään tekstin puhumisen ajaksi, jotta ajastimen käynnistymisen ilmoitusta ei havaita, lähetetä LUIS:lle ja mahdollisesti tulkita uuden ajastimen asettamiseksi.

    > 💁 Voit testata tätä kommentoimalla tunnistuksen pysäyttämisen ja uudelleenkäynnistämisen rivit. Aseta yksi ajastin, ja saatat huomata, että ilmoitus asettaa uuden ajastimen, mikä aiheuttaa uuden ilmoituksen, joka asettaa uuden ajastimen, ja niin edelleen loputtomiin!

1. Suorita sovellus ja varmista, että funktiosovellus on myös käynnissä. Aseta ajastimia, ja kuulet puhutun vastauksen, joka kertoo, että ajastimesi on asetettu, ja toisen puhutun vastauksen, kun ajastin on valmis.

> 💁 Löydät tämän koodin [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) -kansiosta.

😀 Ajastinohjelmasi oli menestys!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.