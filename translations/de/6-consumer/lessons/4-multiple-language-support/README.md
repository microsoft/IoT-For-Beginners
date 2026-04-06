# Unterstützung mehrerer Sprachen

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-24.4246968ed058510a.webp)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Dieses Video gibt einen Überblick über die Azure-Sprachdienste und behandelt die Themen Sprache-zu-Text und Text-zu-Sprache aus den vorherigen Lektionen sowie die Übersetzung von Sprache, ein Thema, das in dieser Lektion behandelt wird:

[![Spracherkennung mit wenigen Zeilen Python von Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klicken Sie auf das Bild oben, um das Video anzusehen

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Einführung

In den letzten drei Lektionen haben Sie gelernt, wie man Sprache in Text umwandelt, Sprache versteht und Text in Sprache umwandelt – alles durch KI unterstützt. Ein weiteres Gebiet der menschlichen Kommunikation, bei dem KI helfen kann, ist die Sprachübersetzung – die Umwandlung von einer Sprache in eine andere, wie zum Beispiel von Englisch nach Französisch.

In dieser Lektion lernen Sie, wie Sie KI nutzen können, um Text zu übersetzen, sodass Ihr intelligenter Timer mit Benutzern in mehreren Sprachen interagieren kann.

In dieser Lektion behandeln wir:

* [Text übersetzen](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Übersetzungsdienste](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Erstellen einer Übersetzungsressource](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Unterstützung mehrerer Sprachen in Anwendungen mit Übersetzungen](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Text mit einem KI-Dienst übersetzen](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Dies ist die letzte Lektion in diesem Projekt. Vergessen Sie nach Abschluss dieser Lektion und der Aufgabe nicht, Ihre Cloud-Dienste aufzuräumen. Sie benötigen die Dienste, um die Aufgabe abzuschließen, stellen Sie also sicher, dass Sie diese zuerst abschließen.
>
> Falls erforderlich, lesen Sie [die Anleitung zum Aufräumen Ihres Projekts](../../../clean-up.md) für Anweisungen dazu.

## Text übersetzen

Die Textübersetzung ist ein Problem der Informatik, das seit über 70 Jahren erforscht wird. Erst jetzt, dank Fortschritten in der KI und Rechenleistung, ist sie so weit fortgeschritten, dass sie fast so gut wie menschliche Übersetzer ist.

> 💁 Die Ursprünge reichen noch weiter zurück, bis zu [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), einem arabischen Kryptografen des 9. Jahrhunderts, der Techniken zur Sprachübersetzung entwickelte.

### Maschinelle Übersetzungen

Die Textübersetzung begann als eine Technologie, die als Maschinelle Übersetzung (MT) bekannt ist und zwischen verschiedenen Sprachpaaren übersetzen kann. MT funktioniert, indem Wörter einer Sprache durch Wörter einer anderen Sprache ersetzt werden, wobei Techniken hinzugefügt werden, um die richtigen Möglichkeiten zur Übersetzung von Phrasen oder Satzteilen auszuwählen, wenn eine einfache Wort-für-Wort-Übersetzung keinen Sinn ergibt.

> 🎓 Wenn Übersetzer die Übersetzung zwischen einer Sprache und einer anderen unterstützen, werden diese als *Sprachpaare* bezeichnet. Verschiedene Tools unterstützen unterschiedliche Sprachpaare, und diese sind möglicherweise nicht vollständig. Zum Beispiel könnte ein Übersetzer Englisch nach Spanisch als Sprachpaar unterstützen und Spanisch nach Italienisch als Sprachpaar, aber nicht Englisch nach Italienisch.

Zum Beispiel kann die Übersetzung von "Hello world" aus dem Englischen ins Französische durch eine Ersetzung durchgeführt werden – "Bonjour" für "Hello" und "le monde" für "world", was zur korrekten Übersetzung "Bonjour le monde" führt.

Ersetzungen funktionieren nicht, wenn verschiedene Sprachen unterschiedliche Möglichkeiten haben, dasselbe auszudrücken. Zum Beispiel wird der englische Satz "My name is Jim" ins Französische übersetzt als "Je m'appelle Jim" – wörtlich "Ich nenne mich Jim". "Je" ist Französisch für "Ich", "moi" ist "mich", wird aber mit dem Verb zusammengezogen, da es mit einem Vokal beginnt, und wird zu "m'", "appelle" bedeutet "rufen", und "Jim" wird nicht übersetzt, da es ein Name ist und kein Wort, das übersetzt werden kann. Auch die Wortreihenfolge wird zum Problem – eine einfache Ersetzung von "Je m'appelle Jim" wird zu "I myself call Jim", mit einer anderen Wortreihenfolge als im Englischen.

> 💁 Einige Wörter werden nie übersetzt – mein Name ist Jim, unabhängig davon, welche Sprache verwendet wird, um mich vorzustellen. Wenn in Sprachen übersetzt wird, die unterschiedliche Alphabete verwenden oder unterschiedliche Buchstaben für unterschiedliche Laute verwenden, können Wörter *transliteriert* werden, das heißt, es werden Buchstaben oder Zeichen ausgewählt, die den entsprechenden Laut erzeugen, um wie das ursprüngliche Wort zu klingen.

Auch Redewendungen sind ein Problem für die Übersetzung. Dies sind Phrasen, die eine verstandene Bedeutung haben, die sich von einer direkten Interpretation der Wörter unterscheidet. Zum Beispiel bezieht sich die englische Redewendung "I've got ants in my pants" nicht wörtlich darauf, Ameisen in der Kleidung zu haben, sondern darauf, unruhig zu sein. Wenn Sie dies ins Deutsche übersetzen, würden Sie den Zuhörer verwirren, da die deutsche Version "Ich habe Hummeln im Hintern" lautet.

> 💁 Unterschiedliche Regionen bringen unterschiedliche Komplexitäten mit sich. Bei der Redewendung "ants in your pants" bezieht sich "pants" im amerikanischen Englisch auf Oberbekleidung, im britischen Englisch auf Unterwäsche.

✅ Wenn Sie mehrere Sprachen sprechen, denken Sie an einige Phrasen, die nicht direkt übersetzt werden können.

Maschinelle Übersetzungssysteme basieren auf großen Datenbanken von Regeln, die beschreiben, wie bestimmte Phrasen und Redewendungen übersetzt werden können, sowie auf statistischen Methoden, um die geeigneten Übersetzungen aus möglichen Optionen auszuwählen. Diese statistischen Methoden verwenden riesige Datenbanken von Werken, die von Menschen in mehrere Sprachen übersetzt wurden, um die wahrscheinlichste Übersetzung auszuwählen, eine Technik, die als *statistische maschinelle Übersetzung* bezeichnet wird. Einige dieser Systeme verwenden Zwischenrepräsentationen der Sprache, die es ermöglichen, eine Sprache in die Zwischenrepräsentation zu übersetzen und dann von der Zwischenrepräsentation in eine andere Sprache. Auf diese Weise erfordert das Hinzufügen weiterer Sprachen Übersetzungen zu und von der Zwischenrepräsentation, nicht zu und von allen anderen Sprachen.

### Neuronale Übersetzungen

Neuronale Übersetzungen nutzen die Leistungsfähigkeit der KI, um zu übersetzen, typischerweise ganze Sätze mit einem Modell. Diese Modelle werden mit riesigen Datensätzen trainiert, die von Menschen übersetzt wurden, wie Webseiten, Bücher und Dokumentationen der Vereinten Nationen.

Neuronale Übersetzungsmodelle sind in der Regel kleiner als maschinelle Übersetzungsmodelle, da sie keine riesigen Datenbanken von Phrasen und Redewendungen benötigen. Moderne KI-Dienste, die Übersetzungen anbieten, kombinieren oft mehrere Techniken, indem sie statistische maschinelle Übersetzung und neuronale Übersetzung mischen.

Es gibt keine 1:1-Übersetzung für ein beliebiges Sprachpaar. Unterschiedliche Übersetzungsmodelle liefern leicht unterschiedliche Ergebnisse, abhängig von den Daten, die zum Trainieren des Modells verwendet wurden. Übersetzungen sind nicht immer symmetrisch – das heißt, wenn Sie einen Satz von einer Sprache in eine andere übersetzen und dann zurück in die erste Sprache, erhalten Sie möglicherweise einen leicht anderen Satz als Ergebnis.

✅ Probieren Sie verschiedene Online-Übersetzer wie [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) oder die Apple-Übersetzungs-App aus. Vergleichen Sie die übersetzten Versionen einiger Sätze. Versuchen Sie auch, in einem zu übersetzen und dann in einem anderen zurück zu übersetzen.

## Übersetzungsdienste

Es gibt eine Reihe von KI-Diensten, die von Ihren Anwendungen genutzt werden können, um Sprache und Text zu übersetzen.

### Cognitive Services Sprachdienst

![Das Logo des Sprachdienstes](../../../../../translated_images/de/azure-speech-logo.a1f08c4befb0159f.webp)

Der Sprachdienst, den Sie in den letzten Lektionen verwendet haben, verfügt über Übersetzungsfunktionen für die Spracherkennung. Wenn Sie Sprache erkennen, können Sie nicht nur den Text der Sprache in derselben Sprache anfordern, sondern auch in anderen Sprachen.

> 💁 Dies ist nur über das Speech SDK verfügbar, die REST-API hat keine integrierten Übersetzungen.

### Cognitive Services Übersetzungsdienst

![Das Logo des Übersetzungsdienstes](../../../../../translated_images/de/azure-translator-logo.c6ed3a4a433edfd2.webp)

Der Übersetzungsdienst ist ein dedizierter Übersetzungsdienst, der Text von einer Sprache in eine oder mehrere Zielsprachen übersetzen kann. Neben der Übersetzung unterstützt er eine Vielzahl zusätzlicher Funktionen, einschließlich der Maskierung von Obszönitäten. Er ermöglicht es Ihnen auch, eine spezifische Übersetzung für ein bestimmtes Wort oder einen bestimmten Satz bereitzustellen, um mit Begriffen zu arbeiten, die Sie nicht übersetzen möchten, oder eine spezifische, bekannte Übersetzung zu verwenden.

Zum Beispiel, wenn Sie den Satz "I have a Raspberry Pi", der sich auf den Einplatinencomputer bezieht, in eine andere Sprache wie Französisch übersetzen, möchten Sie den Namen "Raspberry Pi" beibehalten und nicht übersetzen, sodass "J’ai un Raspberry Pi" statt "J’ai une pi aux framboises" entsteht.

## Erstellen einer Übersetzungsressource

Für diese Lektion benötigen Sie eine Übersetzungsressource. Sie werden die REST-API verwenden, um Text zu übersetzen.

### Aufgabe – Erstellen einer Übersetzungsressource

1. Führen Sie in Ihrem Terminal oder Ihrer Eingabeaufforderung den folgenden Befehl aus, um eine Übersetzungsressource in Ihrer `smart-timer`-Ressourcengruppe zu erstellen.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ersetzen Sie `<location>` durch den Standort, den Sie beim Erstellen der Ressourcengruppe verwendet haben.

1. Holen Sie sich den Schlüssel für den Übersetzungsdienst:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopieren Sie einen der Schlüssel.

## Unterstützung mehrerer Sprachen in Anwendungen mit Übersetzungen

In einer idealen Welt sollte Ihre gesamte Anwendung so viele verschiedene Sprachen wie möglich verstehen, von der Spracherkennung über das Sprachverständnis bis hin zur Antwort mit Sprache. Dies ist viel Arbeit, daher können Übersetzungsdienste die Zeit bis zur Bereitstellung Ihrer Anwendung verkürzen.

![Eine Architektur eines intelligenten Timers, der Japanisch ins Englische übersetzt, die Verarbeitung auf Englisch durchführt und dann zurück ins Japanische übersetzt](../../../../../translated_images/de/translated-smart-timer.08ac20057fdc5c37.webp)

Stellen Sie sich vor, Sie bauen einen intelligenten Timer, der durchgehend Englisch verwendet, gesprochenes Englisch versteht und in Text umwandelt, das Sprachverständnis auf Englisch durchführt, Antworten auf Englisch erstellt und mit englischer Sprache antwortet. Wenn Sie Unterstützung für Japanisch hinzufügen möchten, könnten Sie damit beginnen, gesprochenes Japanisch in englischen Text zu übersetzen, dann den Kern der Anwendung gleich lassen und die Antworttexte ins Japanische übersetzen, bevor Sie die Antwort sprechen. Dies würde es Ihnen ermöglichen, schnell Unterstützung für Japanisch hinzuzufügen, und Sie können später vollständige End-to-End-Unterstützung für Japanisch bereitstellen.

> 💁 Der Nachteil der Abhängigkeit von maschinellen Übersetzungen ist, dass verschiedene Sprachen und Kulturen unterschiedliche Möglichkeiten haben, dasselbe auszudrücken, sodass die Übersetzung möglicherweise nicht der erwarteten Ausdrucksweise entspricht.

Maschinelle Übersetzungen eröffnen auch Möglichkeiten für Apps und Geräte, die benutzergenerierte Inhalte während ihrer Erstellung übersetzen können. Science-Fiction zeigt regelmäßig "universelle Übersetzer", Geräte, die von außerirdischen Sprachen in (typischerweise) amerikanisches Englisch übersetzen können. Diese Geräte sind weniger Science-Fiction, sondern eher wissenschaftliche Realität, wenn man den außerirdischen Teil ignoriert. Es gibt bereits Apps und Geräte, die Echtzeitübersetzungen von Sprache und geschriebenem Text bieten, indem sie Kombinationen aus Sprach- und Übersetzungsdiensten verwenden.

Ein Beispiel ist die [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn)-App für Mobiltelefone, die in diesem Video demonstriert wird:

[![Microsoft Translator Live-Funktion in Aktion](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klicken Sie auf das Bild oben, um das Video anzusehen

Stellen Sie sich vor, Sie hätten ein solches Gerät zur Verfügung, insbesondere beim Reisen oder bei der Interaktion mit Menschen, deren Sprache Sie nicht kennen. Automatische Übersetzungsgeräte in Flughäfen oder Krankenhäusern würden dringend benötigte Verbesserungen der Barrierefreiheit bieten.

✅ Recherchieren Sie: Gibt es kommerziell verfügbare IoT-Übersetzungsgeräte? Was ist mit Übersetzungsfunktionen, die in intelligente Geräte integriert sind?

> 👽 Obwohl es keine echten universellen Übersetzer gibt, die es uns ermöglichen, mit Außerirdischen zu sprechen, unterstützt der [Microsoft Translator tatsächlich Klingonisch](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Text mit einem KI-Dienst übersetzen

Sie können einen KI-Dienst nutzen, um diese Übersetzungsfunktionalität zu Ihrem intelligenten Timer hinzuzufügen.

### Aufgabe – Text mit einem KI-Dienst übersetzen

Arbeiten Sie die entsprechende Anleitung durch, um Text auf Ihrem IoT-Gerät zu übersetzen:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Einplatinencomputer - Raspberry Pi](pi-translate-speech.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device-translate-speech.md)

---

## 🚀 Herausforderung

Wie können maschinelle Übersetzungen anderen IoT-Anwendungen über intelligente Geräte hinaus zugutekommen? Denken Sie an verschiedene Möglichkeiten, wie Übersetzungen helfen können, nicht nur bei gesprochenen Wörtern, sondern auch bei Text.

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Überprüfung & Selbststudium

* Lesen Sie mehr über maschinelle Übersetzung auf der [Seite zur maschinellen Übersetzung auf Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Lesen Sie mehr über neuronale maschinelle Übersetzung auf der [Seite zur neuronalen maschinellen Übersetzung auf Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Sehen Sie sich die Liste der unterstützten Sprachen für die Microsoft-Sprachdienste in der [Dokumentation zur Sprach- und Sprachunterstützung für den Sprachdienst auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn) an

## Aufgabe

[Erstellen Sie einen universellen Übersetzer](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.