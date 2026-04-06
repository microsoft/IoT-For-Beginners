# Spracherkennung mit einem IoT-Gerät

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-21.e34de51354d6606f.webp)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Dieses Video gibt einen Überblick über den Azure-Sprachdienst, ein Thema, das in dieser Lektion behandelt wird:

[![Wie man mit der Cognitive Services Speech-Ressource von Microsoft Azure beginnt](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Klicken Sie auf das obige Bild, um ein Video anzusehen

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Einführung

„Alexa, stelle einen 12-Minuten-Timer.“

„Alexa, Timer-Status.“

„Alexa, stelle einen 8-Minuten-Timer namens Brokkoli dämpfen.“

Smarte Geräte werden immer allgegenwärtiger. Nicht nur als smarte Lautsprecher wie HomePods, Echos und Google Homes, sondern auch eingebettet in unsere Telefone, Uhren und sogar in Lampenfassungen und Thermostate.

> 💁 Ich habe mindestens 19 Geräte in meinem Zuhause, die Sprachassistenten haben, und das sind nur die, von denen ich weiß!

Sprachsteuerung erhöht die Barrierefreiheit, indem sie Menschen mit eingeschränkter Beweglichkeit ermöglicht, mit Geräten zu interagieren. Egal, ob es sich um eine dauerhafte Behinderung handelt, wie das Fehlen von Armen, eine vorübergehende Behinderung wie ein gebrochener Arm, oder einfach die Hände voll mit Einkäufen oder kleinen Kindern – die Möglichkeit, unser Zuhause mit der Stimme statt mit den Händen zu steuern, eröffnet eine Welt voller Möglichkeiten. Ein „Hey Siri, schließe mein Garagentor“ zu rufen, während man mit einem Babywechsel und einem ungestümen Kleinkind beschäftigt ist, kann eine kleine, aber effektive Verbesserung des Alltags sein.

Eine der beliebtesten Anwendungen für Sprachassistenten ist das Stellen von Timern, insbesondere Küchentimern. Mehrere Timer nur mit der Stimme einstellen zu können, ist eine große Hilfe in der Küche – kein Grund, das Kneten von Teig, das Rühren von Suppe oder das Reinigen von Teigtaschenfüllung von den Händen zu unterbrechen, um einen physischen Timer zu bedienen.

In dieser Lektion lernen Sie, wie Sie Spracherkennung in IoT-Geräte integrieren. Sie erfahren, wie Mikrofone als Sensoren funktionieren, wie man Audio von einem Mikrofon, das an ein IoT-Gerät angeschlossen ist, aufnimmt, und wie man KI einsetzt, um das Gehörte in Text umzuwandeln. Im weiteren Verlauf dieses Projekts bauen Sie einen smarten Küchentimer, der Timer in mehreren Sprachen per Sprachbefehl einstellen kann.

In dieser Lektion behandeln wir:

* [Mikrofone](../../../../../6-consumer/lessons/1-speech-recognition)
* [Audio von Ihrem IoT-Gerät aufnehmen](../../../../../6-consumer/lessons/1-speech-recognition)
* [Sprache in Text umwandeln](../../../../../6-consumer/lessons/1-speech-recognition)
* [Sprache in Text konvertieren](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofone

Mikrofone sind analoge Sensoren, die Schallwellen in elektrische Signale umwandeln. Vibrationen in der Luft bewegen Komponenten im Mikrofon minimal, was winzige Änderungen in elektrischen Signalen verursacht. Diese Änderungen werden dann verstärkt, um ein elektrisches Ausgangssignal zu erzeugen.

### Mikrofontypen

Mikrofone gibt es in verschiedenen Typen:

* Dynamisch – Dynamische Mikrofone haben einen Magneten, der an einer beweglichen Membran befestigt ist. Diese bewegt sich in einer Drahtspule und erzeugt so einen elektrischen Strom. Dies ist das Gegenteil der meisten Lautsprecher, die einen elektrischen Strom verwenden, um einen Magneten in einer Drahtspule zu bewegen, wodurch eine Membran Schall erzeugt. Das bedeutet, dass Lautsprecher als dynamische Mikrofone verwendet werden können und umgekehrt. In Geräten wie Gegensprechanlagen, bei denen ein Benutzer entweder zuhört oder spricht, aber nicht beides gleichzeitig, kann ein Gerät sowohl als Lautsprecher als auch als Mikrofon fungieren.

    Dynamische Mikrofone benötigen keine Stromversorgung, das elektrische Signal wird vollständig vom Mikrofon erzeugt.

    ![Patti Smith singt in ein Shure SM58 (dynamisches Kardioid-Mikrofon)](../../../../../translated_images/de/dynamic-mic.8babac890a2d80df.webp)

* Bändchen – Bändchenmikrofone ähneln dynamischen Mikrofonen, haben jedoch ein Metallbändchen anstelle einer Membran. Dieses Bändchen bewegt sich in einem Magnetfeld und erzeugt einen elektrischen Strom. Wie dynamische Mikrofone benötigen auch Bändchenmikrofone keine Stromversorgung.

    ![Edmund Lowe, amerikanischer Schauspieler, steht 1942 an einem Radiomikrofon (gekennzeichnet für das (NBC) Blue Network) und hält ein Skript](../../../../../translated_images/de/ribbon-mic.eacc8e092c7441ca.webp)

* Kondensator – Kondensatormikrofone haben eine dünne Metallmembran und eine feste Metallrückplatte. Elektrizität wird auf beide angewendet, und wenn die Membran vibriert, ändert sich die statische Ladung zwischen den Platten und erzeugt ein Signal. Kondensatormikrofone benötigen Strom, um zu funktionieren – genannt *Phantomspannung*.

    ![C451B Kleinmembran-Kondensatormikrofon von AKG Acoustics](../../../../../translated_images/de/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS – Mikroelektromechanische Systeme (MEMS) sind Mikrofone auf einem Chip. Sie haben eine druckempfindliche Membran, die auf einen Siliziumchip geätzt ist, und funktionieren ähnlich wie ein Kondensatormikrofon. Diese Mikrofone können winzig sein und in Schaltungen integriert werden.

    ![Ein MEMS-Mikrofon auf einer Leiterplatte](../../../../../translated_images/de/mems-microphone.80574019e1f5e4d9.webp)

    Im obigen Bild ist der Chip mit der Aufschrift **LEFT** ein MEMS-Mikrofon mit einer winzigen Membran, die weniger als einen Millimeter breit ist.

✅ Recherchieren Sie: Welche Mikrofone haben Sie in Ihrer Umgebung – sei es in Ihrem Computer, Ihrem Telefon, Ihrem Headset oder in anderen Geräten? Welche Mikrofontypen sind das?

### Digitale Audiodaten

Audio ist ein analoges Signal, das sehr feingranulare Informationen trägt. Um dieses Signal in digitale Daten umzuwandeln, muss das Audio viele tausend Male pro Sekunde abgetastet werden.

> 🎓 Abtastung bedeutet, das Audiosignal in einen digitalen Wert umzuwandeln, der das Signal zu einem bestimmten Zeitpunkt repräsentiert.

![Ein Liniendiagramm, das ein Signal mit diskreten Punkten in festen Intervallen zeigt](../../../../../translated_images/de/sampling.6f4fadb3f2d9dfe7.webp)

Digitales Audio wird mit Puls-Code-Modulation (PCM) abgetastet. PCM liest die Spannung des Signals aus und wählt den nächstgelegenen diskreten Wert zu dieser Spannung basierend auf einer definierten Größe.

> 💁 Sie können sich PCM als die Sensorversion der Pulsweitenmodulation (PWM) vorstellen (PWM wurde bereits in [Lektion 3 des Einsteigerprojekts](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation) behandelt). PCM wandelt ein analoges Signal in ein digitales um, während PWM ein digitales Signal in ein analoges umwandelt.

Zum Beispiel bieten die meisten Streaming-Musikdienste 16-Bit- oder 24-Bit-Audio an. Das bedeutet, dass sie die Spannung in einen Wert umwandeln, der in einen 16-Bit-Integer oder 24-Bit-Integer passt. 16-Bit-Audio umfasst Werte im Bereich von -32.768 bis 32.767, 24-Bit-Audio reicht von −8.388.608 bis 8.388.607. Je mehr Bits, desto näher ist die Abtastung an dem, was unsere Ohren tatsächlich hören.

> 💁 Sie haben vielleicht schon von 8-Bit-Audio gehört, oft als LoFi bezeichnet. Dies ist Audio, das nur mit 8-Bit abgetastet wurde, also -128 bis 127. Die ersten Computeraudios waren aufgrund von Hardwarebeschränkungen auf 8-Bit begrenzt, weshalb dies oft in Retro-Gaming vorkommt.

Diese Abtastungen werden viele tausend Male pro Sekunde durchgeführt, mit gut definierten Abtastraten, die in KHz (tausend Abtastungen pro Sekunde) gemessen werden. Streaming-Musikdienste verwenden für die meisten Audiodaten 48 KHz, aber einige „verlustfreie“ Audiodaten verwenden bis zu 96 KHz oder sogar 192 KHz. Je höher die Abtastrate, desto näher ist das Audio am Original – bis zu einem gewissen Punkt. Es gibt Diskussionen darüber, ob Menschen Unterschiede oberhalb von 48 KHz wahrnehmen können.

✅ Recherchieren Sie: Wenn Sie einen Streaming-Musikdienst nutzen, welche Abtastrate und -größe verwendet dieser? Wenn Sie CDs verwenden, welche Abtastrate und -größe hat CD-Audio?

Es gibt verschiedene Formate für Audiodaten. Sie haben wahrscheinlich schon von MP3-Dateien gehört – Audiodaten, die komprimiert wurden, um sie kleiner zu machen, ohne an Qualität zu verlieren. Unkomprimierte Audiodaten werden oft als WAV-Datei gespeichert – dies ist eine Datei mit 44 Bytes Header-Informationen, gefolgt von den rohen Audiodaten. Der Header enthält Informationen wie die Abtastrate (z. B. 16000 für 16 KHz), die Abtastgröße (16 für 16-Bit) und die Anzahl der Kanäle. Nach dem Header enthält die WAV-Datei die rohen Audiodaten.

> 🎓 Kanäle beziehen sich darauf, wie viele verschiedene Audioströme das Audio ausmachen. Zum Beispiel hätte Stereo-Audio mit links und rechts 2 Kanäle. Für 7.1-Surround-Sound in einem Heimkinosystem wären es 8.

### Größe von Audiodaten

Audiodaten sind relativ groß. Zum Beispiel benötigt die Aufnahme von unkomprimiertem 16-Bit-Audio bei 16 KHz (eine ausreichende Rate für die Verwendung mit einem Sprach-zu-Text-Modell) 32 KB Daten pro Sekunde Audio:

* 16-Bit bedeutet 2 Bytes pro Abtastung (1 Byte = 8 Bit).
* 16 KHz sind 16.000 Abtastungen pro Sekunde.
* 16.000 x 2 Bytes = 32.000 Bytes pro Sekunde.

Das klingt nach einer kleinen Datenmenge, aber wenn Sie einen Mikrocontroller mit begrenztem Speicher verwenden, kann das viel sein. Zum Beispiel hat das Wio Terminal 192 KB Speicher, und dieser muss Programmcode und Variablen speichern. Selbst wenn Ihr Programmcode winzig wäre, könnten Sie nicht mehr als 5 Sekunden Audio aufnehmen.

Mikrocontroller können auf zusätzlichen Speicher zugreifen, wie SD-Karten oder Flash-Speicher. Beim Bau eines IoT-Geräts, das Audio aufnimmt, müssen Sie sicherstellen, dass Sie nicht nur zusätzlichen Speicher haben, sondern dass Ihr Code das vom Mikrofon aufgenommene Audio direkt in diesen Speicher schreibt. Wenn Sie es in die Cloud senden, sollten Sie es aus dem Speicher streamen, anstatt den gesamten Audio-Datenblock auf einmal im Speicher zu halten. So vermeiden Sie, dass Ihnen der Speicher ausgeht.

## Audio von Ihrem IoT-Gerät aufnehmen

Ihr IoT-Gerät kann mit einem Mikrofon verbunden werden, um Audio aufzunehmen, das dann in Text umgewandelt werden kann. Es kann auch mit Lautsprechern verbunden werden, um Audio auszugeben. In späteren Lektionen wird dies verwendet, um akustisches Feedback zu geben, aber es ist nützlich, Lautsprecher jetzt einzurichten, um das Mikrofon zu testen.

### Aufgabe – Mikrofon und Lautsprecher konfigurieren

Arbeiten Sie die entsprechende Anleitung durch, um das Mikrofon und die Lautsprecher für Ihr IoT-Gerät zu konfigurieren:

* [Arduino – Wio Terminal](wio-terminal-microphone.md)
* [Einplatinencomputer – Raspberry Pi](pi-microphone.md)
* [Einplatinencomputer – Virtuelles Gerät](virtual-device-microphone.md)

### Aufgabe – Audio aufnehmen

Arbeiten Sie die entsprechende Anleitung durch, um Audio auf Ihrem IoT-Gerät aufzunehmen:

* [Arduino – Wio Terminal](wio-terminal-audio.md)
* [Einplatinencomputer – Raspberry Pi](pi-audio.md)
* [Einplatinencomputer – Virtuelles Gerät](virtual-device-audio.md)

## Sprache in Text umwandeln

Sprache in Text, oder Spracherkennung, bedeutet, KI zu verwenden, um Wörter in einem Audiosignal in Text umzuwandeln.

### Sprachmodelle

Um Sprache in Text umzuwandeln, werden Abtastungen aus dem Audiosignal gruppiert und in ein maschinelles Lernmodell eingespeist, das auf einem Rekurrenten Neuronalen Netzwerk (RNN) basiert. Dies ist eine Art von maschinellem Lernmodell, das frühere Daten verwenden kann, um Entscheidungen über eingehende Daten zu treffen. Zum Beispiel könnte das RNN einen Block von Audiodaten als den Klang „Hel“ erkennen und, wenn es einen weiteren Block erhält, der wie „lo“ klingt, diese mit dem vorherigen Klang kombinieren, feststellen, dass „Hello“ ein gültiges Wort ist, und dieses als Ergebnis auswählen.

ML-Modelle akzeptieren immer Daten derselben Größe. Der Bildklassifikator, den Sie in einer früheren Lektion erstellt haben, skaliert Bilder auf eine feste Größe und verarbeitet sie. Dasselbe gilt für Sprachmodelle: Sie müssen Audiodaten in festen Größen verarbeiten. Sprachmodelle müssen in der Lage sein, die Ergebnisse mehrerer Vorhersagen zu kombinieren, um die richtige Antwort zu finden, damit sie beispielsweise zwischen „Hi“ und „Highway“ oder „flock“ und „floccinaucinihilipilification“ unterscheiden können.

Sprachmodelle sind auch so fortschrittlich, dass sie den Kontext verstehen und die erkannten Wörter korrigieren können, während mehr Daten verarbeitet werden. Wenn Sie beispielsweise sagen: „Ich ging in die Läden, um zwei Bananen und einen Apfel zu holen“, verwenden Sie drei Wörter, die gleich klingen, aber unterschiedlich geschrieben werden – to, two und too. Sprachmodelle können den Kontext verstehen und die richtige Schreibweise des Wortes verwenden.
💁 Einige Sprachdienste ermöglichen Anpassungen, um besser in lauten Umgebungen wie Fabriken zu funktionieren oder mit branchenspezifischen Begriffen wie chemischen Namen umzugehen. Diese Anpassungen werden durch das Bereitstellen von Beispiel-Audio und einer Transkription trainiert und basieren auf Transferlernen – ähnlich wie Sie zuvor einen Bildklassifikator mit nur wenigen Bildern in einer früheren Lektion trainiert haben.
### Datenschutz

Beim Einsatz von Sprach-zu-Text in einem IoT-Gerät für Verbraucher ist Datenschutz von entscheidender Bedeutung. Diese Geräte hören kontinuierlich Audio, und als Verbraucher möchten Sie nicht, dass alles, was Sie sagen, in die Cloud gesendet und in Text umgewandelt wird. Dies würde nicht nur viel Internetbandbreite verbrauchen, sondern auch erhebliche Datenschutzprobleme mit sich bringen, insbesondere wenn einige Hersteller von Smart-Geräten zufällig Audio auswählen, um [es von Menschen gegen den generierten Text zu validieren, um ihr Modell zu verbessern](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Sie möchten, dass Ihr Smart-Gerät Audio nur dann zur Verarbeitung in die Cloud sendet, wenn Sie es verwenden, und nicht, wenn es Audio in Ihrem Zuhause hört, das private Besprechungen oder intime Interaktionen enthalten könnte. Die meisten Smart-Geräte funktionieren mit einem *Aktivierungswort*, einer Schlüsselphrase wie „Alexa“, „Hey Siri“ oder „OK Google“, die das Gerät dazu bringt, „aufzuwachen“ und zuzuhören, was Sie sagen, bis es eine Pause in Ihrer Sprache erkennt, die darauf hinweist, dass Sie aufgehört haben, mit dem Gerät zu sprechen.

> 🎓 Die Erkennung von Aktivierungswörtern wird auch als *Keyword Spotting* oder *Keyword Recognition* bezeichnet.

Diese Aktivierungswörter werden auf dem Gerät und nicht in der Cloud erkannt. Diese Smart-Geräte verfügen über kleine KI-Modelle, die auf dem Gerät laufen und auf das Aktivierungswort hören. Wenn es erkannt wird, beginnt das Gerät, Audio zur Erkennung in die Cloud zu streamen. Diese Modelle sind sehr spezialisiert und hören nur auf das Aktivierungswort.

> 💁 Einige Technologieunternehmen fügen ihren Geräten mehr Datenschutz hinzu und führen einen Teil der Sprach-zu-Text-Umwandlung direkt auf dem Gerät aus. Apple hat angekündigt, dass sie im Rahmen ihrer Updates für iOS und macOS 2021 die Sprach-zu-Text-Umwandlung auf dem Gerät unterstützen werden und viele Anfragen ohne Nutzung der Cloud bearbeiten können. Dies ist dank leistungsstarker Prozessoren in ihren Geräten möglich, die ML-Modelle ausführen können.

✅ Was denken Sie über die Datenschutz- und ethischen Implikationen der Speicherung von Audio, das in die Cloud gesendet wird? Sollte dieses Audio gespeichert werden, und wenn ja, wie? Halten Sie die Nutzung von Aufnahmen durch Strafverfolgungsbehörden für einen guten Kompromiss im Hinblick auf den Verlust der Privatsphäre?

Die Erkennung von Aktivierungswörtern verwendet normalerweise eine Technik namens TinyML, bei der ML-Modelle so konvertiert werden, dass sie auf Mikrocontrollern laufen können. Diese Modelle sind klein und verbrauchen sehr wenig Energie.

Um die Komplexität des Trainings und der Nutzung eines Aktivierungswort-Modells zu vermeiden, wird der intelligente Timer, den Sie in dieser Lektion bauen, einen Knopf verwenden, um die Spracherkennung zu aktivieren.

> 💁 Wenn Sie ein Modell zur Erkennung von Aktivierungswörtern erstellen möchten, das auf dem Wio Terminal oder Raspberry Pi läuft, sehen Sie sich dieses [Tutorial zur Reaktion auf Ihre Stimme von Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice) an. Wenn Sie Ihren Computer dafür nutzen möchten, können Sie das [Schnellstart-Tutorial für benutzerdefinierte Schlüsselwörter in den Microsoft-Dokumenten](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn) ausprobieren.

## Sprache in Text umwandeln

![Logo der Sprachdienste](../../../../../translated_images/de/azure-speech-logo.a1f08c4befb0159f.webp)

Ähnlich wie bei der Bildklassifikation in einem früheren Projekt gibt es vorgefertigte KI-Dienste, die Sprache als Audiodatei aufnehmen und in Text umwandeln können. Einer dieser Dienste ist der Speech Service, Teil der Cognitive Services, vorgefertigte KI-Dienste, die Sie in Ihren Apps verwenden können.

### Aufgabe - Konfigurieren einer Sprach-KI-Ressource

1. Erstellen Sie eine Ressourcengruppe für dieses Projekt mit dem Namen `smart-timer`.

1. Verwenden Sie den folgenden Befehl, um eine kostenlose Sprachressource zu erstellen:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ersetzen Sie `<location>` durch den Standort, den Sie bei der Erstellung der Ressourcengruppe verwendet haben.

1. Sie benötigen einen API-Schlüssel, um von Ihrem Code aus auf die Sprachressource zuzugreifen. Führen Sie den folgenden Befehl aus, um den Schlüssel zu erhalten:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopieren Sie einen der Schlüssel.

### Aufgabe - Sprache in Text umwandeln

Arbeiten Sie die entsprechende Anleitung durch, um Sprache auf Ihrem IoT-Gerät in Text umzuwandeln:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Einplatinencomputer - Raspberry Pi](pi-speech-to-text.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device-speech-to-text.md)

---

## 🚀 Herausforderung

Spracherkennung gibt es schon lange und sie verbessert sich kontinuierlich. Recherchieren Sie die aktuellen Fähigkeiten und vergleichen Sie, wie sich diese im Laufe der Zeit entwickelt haben, einschließlich der Genauigkeit maschineller Transkriptionen im Vergleich zu menschlichen.

Was glauben Sie, hält die Zukunft für die Spracherkennung bereit?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Überprüfung & Selbststudium

* Lesen Sie über die verschiedenen Mikrofontypen und wie sie funktionieren im Artikel [Was ist der Unterschied zwischen dynamischen und Kondensatormikrofonen auf Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Lesen Sie mehr über den Cognitive Services Speech Service in der [Dokumentation zum Speech Service auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Lesen Sie über Keyword Spotting in der [Dokumentation zur Keyword-Erkennung auf Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Aufgabe

[](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.