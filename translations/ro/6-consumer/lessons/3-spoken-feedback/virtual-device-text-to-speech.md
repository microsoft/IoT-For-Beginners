<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T08:56:44+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ro"
}
-->
# Text to speech - Dispozitiv IoT virtual

În această parte a lecției, vei scrie cod pentru a converti textul în vorbire folosind serviciul de vorbire.

## Conversia textului în vorbire

SDK-ul serviciilor de vorbire pe care l-ai utilizat în lecția anterioară pentru a converti vorbirea în text poate fi folosit și pentru a converti textul înapoi în vorbire. Când soliciți generarea vorbirii, trebuie să specifici vocea care va fi utilizată, deoarece vorbirea poate fi generată folosind o varietate de voci diferite.

Fiecare limbă acceptă o gamă de voci diferite, iar lista vocilor disponibile pentru fiecare limbă poate fi obținută din SDK-ul serviciilor de vorbire.

### Sarcină - conversia textului în vorbire

1. Deschide proiectul `smart-timer` în VS Code și asigură-te că mediul virtual este încărcat în terminal.

1. Importează `SpeechSynthesizer` din pachetul `azure.cognitiveservices.speech` adăugându-l la importurile existente:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Deasupra funcției `say`, creează o configurație de vorbire pentru a fi utilizată cu sintetizatorul de vorbire:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Aceasta folosește aceeași cheie API, locație și limbă care au fost utilizate de recunoașterea vocală.

1. Sub aceasta, adaugă următorul cod pentru a obține o voce și a o seta în configurația de vorbire:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Acest cod recuperează o listă cu toate vocile disponibile, apoi găsește prima voce care se potrivește cu limba utilizată.

    > 💁 Poți obține lista completă a vocilor acceptate din [documentația despre suportul pentru limbi și voci pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Dacă dorești să utilizezi o voce specifică, poți elimina această funcție și seta manual vocea folosind numele vocii din această documentație. De exemplu:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Actualizează conținutul funcției `say` pentru a genera SSML pentru răspuns:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Sub aceasta, oprește recunoașterea vocală, redă SSML-ul, apoi pornește din nou recunoașterea:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Recunoașterea este oprită în timp ce textul este redat pentru a evita ca anunțul despre pornirea cronometrului să fie detectat, trimis către LUIS și interpretat posibil ca o cerere de a seta un nou cronometru.

    > 💁 Poți testa acest lucru comentând liniile care opresc și repornesc recunoașterea. Setează un cronometru și este posibil să descoperi că anunțul setează un nou cronometru, ceea ce duce la un nou anunț, care setează un alt cronometru, și așa mai departe la nesfârșit!

1. Rulează aplicația și asigură-te că aplicația funcțională rulează de asemenea. Setează câțiva timpi, iar răspunsurile vorbite vor confirma că cronometrul tău a fost setat, urmate de un alt răspuns vorbit când cronometrul se finalizează.

> 💁 Poți găsi acest cod în folderul [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Programul tău pentru cronometru a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.