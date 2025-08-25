<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T22:40:26+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "de"
}
-->
# Text-zu-Sprache - Virtuelles IoT-Gerät

In diesem Teil der Lektion schreiben Sie Code, um Text mithilfe des Sprachdienstes in Sprache umzuwandeln.

## Text in Sprache umwandeln

Das SDK der Sprachdienste, das Sie in der letzten Lektion verwendet haben, um Sprache in Text umzuwandeln, kann auch verwendet werden, um Text wieder in Sprache umzuwandeln. Beim Anfordern von Sprache müssen Sie die Stimme angeben, die verwendet werden soll, da Sprache mit einer Vielzahl unterschiedlicher Stimmen generiert werden kann.

Jede Sprache unterstützt eine Reihe verschiedener Stimmen, und Sie können die Liste der unterstützten Stimmen für jede Sprache aus dem SDK der Sprachdienste abrufen.

### Aufgabe - Text in Sprache umwandeln

1. Öffnen Sie das Projekt `smart-timer` in VS Code und stellen Sie sicher, dass die virtuelle Umgebung im Terminal geladen ist.

1. Importieren Sie den `SpeechSynthesizer` aus dem Paket `azure.cognitiveservices.speech`, indem Sie ihn zu den bestehenden Imports hinzufügen:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Erstellen Sie oberhalb der Funktion `say` eine Sprachkonfiguration, die mit dem Sprachsynthesizer verwendet werden soll:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Diese verwendet denselben API-Schlüssel, Standort und Sprache, die auch vom Recognizer verwendet wurden.

1. Fügen Sie darunter den folgenden Code hinzu, um eine Stimme zu erhalten und sie in der Sprachkonfiguration festzulegen:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Dies ruft eine Liste aller verfügbaren Stimmen ab und findet dann die erste Stimme, die zur verwendeten Sprache passt.

    > 💁 Sie können die vollständige Liste der unterstützten Stimmen in der [Dokumentation zu Sprach- und Stimmenunterstützung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) finden. Wenn Sie eine bestimmte Stimme verwenden möchten, können Sie diese Funktion entfernen und die Stimme direkt mit dem Namen aus der Dokumentation festlegen. Zum Beispiel:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Aktualisieren Sie den Inhalt der Funktion `say`, um SSML für die Antwort zu generieren:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Fügen Sie darunter Code hinzu, um die Spracherkennung zu stoppen, das SSML zu sprechen und die Erkennung anschließend wieder zu starten:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Die Erkennung wird gestoppt, während der Text gesprochen wird, um zu vermeiden, dass die Ankündigung des Timer-Starts erkannt, an LUIS gesendet und möglicherweise als Anfrage zum Setzen eines neuen Timers interpretiert wird.

    > 💁 Sie können dies testen, indem Sie die Zeilen zum Stoppen und Neustarten der Erkennung auskommentieren. Setzen Sie einen Timer, und Sie werden feststellen, dass die Ankündigung einen neuen Timer setzt, was zu einer neuen Ankündigung führt, die wiederum einen neuen Timer setzt, und so weiter, endlos!

1. Führen Sie die App aus und stellen Sie sicher, dass die Funktions-App ebenfalls läuft. Setzen Sie einige Timer, und Sie werden eine gesprochene Antwort hören, die sagt, dass Ihr Timer gesetzt wurde, und eine weitere gesprochene Antwort, wenn der Timer abgelaufen ist.

> 💁 Sie finden diesen Code im Ordner [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Ihr Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.