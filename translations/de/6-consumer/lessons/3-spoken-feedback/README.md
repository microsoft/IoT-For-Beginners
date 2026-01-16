<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-25T22:35:11+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "de"
}
-->
# Stelle einen Timer ein und gib mündliches Feedback

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicke auf das Bild für eine größere Version.

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Einführung

Smarte Assistenten sind keine Einweg-Kommunikationsgeräte. Du sprichst mit ihnen, und sie antworten:

„Alexa, stelle einen 3-Minuten-Timer ein.“

„Ok, dein Timer ist auf 3 Minuten gestellt.“

In den letzten zwei Lektionen hast du gelernt, wie man Sprache in Text umwandelt und dann eine Timer-Anfrage aus diesem Text extrahiert. In dieser Lektion lernst du, wie du den Timer auf dem IoT-Gerät einstellst, dem Nutzer mit gesprochenen Worten bestätigst, dass der Timer gestellt wurde, und ihn benachrichtigst, wenn der Timer abgelaufen ist.

In dieser Lektion behandeln wir:

* [Text-zu-Sprache](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Den Timer einstellen](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Text in Sprache umwandeln](../../../../../6-consumer/lessons/3-spoken-feedback)

## Text-zu-Sprache

Text-zu-Sprache, wie der Name schon sagt, ist der Prozess, Text in Audio umzuwandeln, das die Wörter als gesprochene Sprache enthält. Das Grundprinzip besteht darin, die Wörter im Text in ihre Bestandteile (sogenannte Phoneme) zu zerlegen und Audio für diese Laute zusammenzusetzen, entweder mit vorab aufgezeichnetem Audio oder mit Audio, das von KI-Modellen generiert wird.

![Die drei Phasen typischer Text-zu-Sprache-Systeme](../../../../../translated_images/de/tts-overview.193843cf3f5ee09f.webp)

Text-zu-Sprache-Systeme haben typischerweise 3 Phasen:

* Textanalyse
* Linguistische Analyse
* Wellenform-Generierung

### Textanalyse

Die Textanalyse umfasst die Verarbeitung des bereitgestellten Textes und die Umwandlung in Wörter, die zur Spracherzeugung verwendet werden können. Zum Beispiel: Wenn du „Hallo Welt“ umwandelst, ist keine Textanalyse erforderlich, da die beiden Wörter direkt in Sprache umgewandelt werden können. Wenn du jedoch „1234“ hast, muss dies möglicherweise in „Eintausendzweihundertvierunddreißig“ oder „Eins, zwei, drei, vier“ umgewandelt werden, je nach Kontext. Für „Ich habe 1234 Äpfel“ wäre es „Eintausendzweihundertvierunddreißig“, aber für „Das Kind zählte 1234“ wäre es „Eins, zwei, drei, vier“.

Die erzeugten Wörter variieren nicht nur je nach Sprache, sondern auch je nach Region dieser Sprache. Zum Beispiel: Im amerikanischen Englisch wäre 120 „One hundred twenty“, im britischen Englisch „One hundred and twenty“, wobei das „and“ nach den Hunderten verwendet wird.

✅ Einige weitere Beispiele, die eine Textanalyse erfordern, sind „in“ als Abkürzung für Zoll und „st“ als Abkürzung für Sankt oder Straße. Fallen dir in deiner Sprache weitere Beispiele für Wörter ein, die ohne Kontext mehrdeutig sind?

Sobald die Wörter definiert sind, werden sie zur linguistischen Analyse weitergeleitet.

### Linguistische Analyse

Die linguistische Analyse zerlegt die Wörter in Phoneme. Phoneme basieren nicht nur auf den verwendeten Buchstaben, sondern auch auf den anderen Buchstaben im Wort. Zum Beispiel ist im Englischen der Laut des Buchstabens „a“ in „car“ und „care“ unterschiedlich. Die englische Sprache hat 44 verschiedene Phoneme für die 26 Buchstaben des Alphabets, von denen einige von verschiedenen Buchstaben geteilt werden, wie das gleiche Phonem am Anfang von „circle“ und „serpent“.

✅ Recherchiere: Welche Phoneme gibt es in deiner Sprache?

Sobald die Wörter in Phoneme umgewandelt wurden, benötigen diese Phoneme zusätzliche Daten, um Intonation zu unterstützen, indem der Ton oder die Dauer je nach Kontext angepasst wird. Ein Beispiel: Im Englischen kann eine Erhöhung der Tonhöhe verwendet werden, um einen Satz in eine Frage umzuwandeln. Eine erhöhte Tonhöhe beim letzten Wort deutet auf eine Frage hin.

Zum Beispiel: Der Satz „You have an apple“ ist eine Aussage, die besagt, dass du einen Apfel hast. Wenn die Tonhöhe am Ende steigt, insbesondere beim Wort „apple“, wird daraus die Frage „You have an apple?“, die fragt, ob du einen Apfel hast. Die linguistische Analyse muss das Fragezeichen am Ende verwenden, um die Tonhöhe zu erhöhen.

Sobald die Phoneme generiert wurden, können sie zur Wellenform-Generierung weitergeleitet werden, um die Audioausgabe zu erzeugen.

### Wellenform-Generierung

Die ersten elektronischen Text-zu-Sprache-Systeme verwendeten einzelne Audioaufnahmen für jedes Phonem, was zu sehr monotonen, robotischen Stimmen führte. Die linguistische Analyse erzeugte Phoneme, diese wurden aus einer Datenbank von Klängen geladen und zusammengesetzt, um das Audio zu erstellen.

✅ Recherchiere: Finde einige Audioaufnahmen von frühen Sprachsynthesesystemen. Vergleiche sie mit moderner Sprachsynthese, wie sie in smarten Assistenten verwendet wird.

Moderne Wellenform-Generierung verwendet ML-Modelle, die mit Deep Learning (sehr großen neuronalen Netzwerken, die ähnlich wie Neuronen im Gehirn funktionieren) erstellt wurden, um natürlichere Stimmen zu erzeugen, die von menschlichen Stimmen nicht zu unterscheiden sind.

> 💁 Einige dieser ML-Modelle können mithilfe von Transfer-Learning neu trainiert werden, um wie echte Personen zu klingen. Das bedeutet, dass die Verwendung von Stimmen als Sicherheitssystem, wie es Banken zunehmend versuchen, keine gute Idee mehr ist, da jeder mit einer Aufnahme von nur wenigen Minuten deiner Stimme dich imitieren kann.

Diese großen ML-Modelle werden darauf trainiert, alle drei Schritte zu kombinieren und End-to-End-Sprachsynthesizer zu erstellen.

## Den Timer einstellen

Um den Timer einzustellen, muss dein IoT-Gerät den REST-Endpunkt aufrufen, den du mit serverlosem Code erstellt hast, und dann die resultierende Anzahl von Sekunden verwenden, um einen Timer einzustellen.

### Aufgabe – Die serverlose Funktion aufrufen, um die Timerzeit zu erhalten

Folge der entsprechenden Anleitung, um den REST-Endpunkt von deinem IoT-Gerät aus aufzurufen und einen Timer für die erforderliche Zeit einzustellen:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer-set-timer.md)

## Text in Sprache umwandeln

Der gleiche Sprachdienst, den du verwendet hast, um Sprache in Text umzuwandeln, kann auch verwendet werden, um Text wieder in Sprache umzuwandeln. Diese kann dann über einen Lautsprecher auf deinem IoT-Gerät abgespielt werden. Der zu konvertierende Text wird an den Sprachdienst gesendet, zusammen mit dem gewünschten Audioformat (z. B. der Abtastrate), und binäre Daten, die das Audio enthalten, werden zurückgegeben.

Wenn du diese Anfrage sendest, verwendest du *Speech Synthesis Markup Language* (SSML), eine XML-basierte Auszeichnungssprache für Sprachsyntheseanwendungen. Diese definiert nicht nur den zu konvertierenden Text, sondern auch die Sprache des Textes, die zu verwendende Stimme und kann sogar verwendet werden, um Geschwindigkeit, Lautstärke und Tonhöhe für einige oder alle Wörter im Text zu definieren.

Zum Beispiel definiert dieses SSML eine Anfrage, um den Text „Your 3 minute 5 second time has been set“ in Sprache umzuwandeln, wobei eine britische englische Stimme namens `en-GB-MiaNeural` verwendet wird:

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Die meisten Text-zu-Sprache-Systeme haben mehrere Stimmen für verschiedene Sprachen, mit entsprechenden Akzenten, wie eine britische englische Stimme mit englischem Akzent und eine neuseeländische englische Stimme mit neuseeländischem Akzent.

### Aufgabe – Text in Sprache umwandeln

Arbeite die entsprechende Anleitung durch, um Text in Sprache mit deinem IoT-Gerät umzuwandeln:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Einplatinencomputer - Raspberry Pi](pi-text-to-speech.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device-text-to-speech.md)

---

## 🚀 Herausforderung

SSML bietet Möglichkeiten, wie Wörter gesprochen werden, zu verändern, z. B. durch das Hinzufügen von Betonung auf bestimmte Wörter, das Einfügen von Pausen oder das Ändern der Tonhöhe. Probiere einige dieser Optionen aus, indem du verschiedene SSML-Anfragen von deinem IoT-Gerät sendest und die Ausgabe vergleichst. Du kannst mehr über SSML erfahren, einschließlich der Anpassung der Aussprache von Wörtern, in der [Speech Synthesis Markup Language (SSML) Version 1.1 Spezifikation des World Wide Web Consortiums](https://www.w3.org/TR/speech-synthesis11/).

## Quiz nach der Lektion

[Quiz nach der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Rückblick & Selbststudium

* Lies mehr über Sprachsynthese auf der [Wikipedia-Seite zur Sprachsynthese](https://wikipedia.org/wiki/Speech_synthesis).
* Erfahre mehr darüber, wie Kriminelle Sprachsynthese nutzen, um zu stehlen, in der [BBC-News-Story über gefälschte Stimmen](https://www.bbc.com/news/technology-48908736).
* Erfahre mehr über die Risiken für Synchronsprecher durch synthetisierte Versionen ihrer Stimmen im [Artikel auf Vice über eine TikTok-Klage](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors).

## Aufgabe

[Den Timer abbrechen](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.