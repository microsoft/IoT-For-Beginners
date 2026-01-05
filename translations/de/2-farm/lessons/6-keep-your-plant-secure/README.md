<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-25T21:49:41+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "de"
}
-->
# Halten Sie Ihre Pflanze sicher

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.de.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Einführung

In den letzten Lektionen haben Sie ein IoT-Gerät zur Bodenüberwachung erstellt und mit der Cloud verbunden. Aber was, wenn Hacker, die für einen konkurrierenden Landwirt arbeiten, die Kontrolle über Ihre IoT-Geräte übernehmen? Was, wenn sie hohe Bodenfeuchtigkeitswerte senden, sodass Ihre Pflanzen nie bewässert werden, oder Ihr Bewässerungssystem ständig laufen lassen, wodurch Ihre Pflanzen durch Überbewässerung sterben und Sie ein kleines Vermögen für Wasser verlieren?

In dieser Lektion lernen Sie, wie Sie IoT-Geräte sichern können. Da dies die letzte Lektion für dieses Projekt ist, lernen Sie auch, wie Sie Ihre Cloud-Ressourcen bereinigen, um potenzielle Kosten zu reduzieren.

In dieser Lektion behandeln wir:

* [Warum müssen Sie IoT-Geräte sichern?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kryptographie](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Sichern Sie Ihre IoT-Geräte](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Erstellen und verwenden Sie ein X.509-Zertifikat](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Dies ist die letzte Lektion in diesem Projekt. Vergessen Sie nach Abschluss dieser Lektion und der Aufgabe nicht, Ihre Cloud-Dienste zu bereinigen. Sie benötigen die Dienste, um die Aufgabe abzuschließen, stellen Sie also sicher, dass Sie diese zuerst abschließen.
>
> Konsultieren Sie bei Bedarf [den Leitfaden zur Projektbereinigung](../../../clean-up.md) für Anweisungen, wie Sie dies tun können.

## Warum müssen Sie IoT-Geräte sichern?

IoT-Sicherheit bedeutet sicherzustellen, dass nur erwartete Geräte eine Verbindung zu Ihrem Cloud-IoT-Dienst herstellen und Telemetrie senden können, und dass nur Ihr Cloud-Dienst Befehle an Ihre Geräte senden kann. IoT-Daten können auch persönlich sein, einschließlich medizinischer oder intimer Daten, sodass Ihre gesamte Anwendung die Sicherheit berücksichtigen muss, um ein Leaken dieser Daten zu verhindern.

Wenn Ihre IoT-Anwendung nicht sicher ist, gibt es eine Reihe von Risiken:

* Ein gefälschtes Gerät könnte falsche Daten senden, wodurch Ihre Anwendung falsch reagiert. Zum Beispiel könnten sie ständig hohe Bodenfeuchtigkeitswerte senden, sodass Ihr Bewässerungssystem nie eingeschaltet wird und Ihre Pflanzen aufgrund von Wassermangel sterben.
* Unbefugte Benutzer könnten Daten von IoT-Geräten lesen, einschließlich persönlicher oder geschäftskritischer Daten.
* Hacker könnten Befehle senden, um ein Gerät auf eine Weise zu steuern, die das Gerät oder angeschlossene Hardware beschädigen könnte.
* Durch die Verbindung zu einem IoT-Gerät könnten Hacker zusätzliche Netzwerke nutzen, um Zugang zu privaten Systemen zu erhalten.
* Böswillige Benutzer könnten auf persönliche Daten zugreifen und diese für Erpressung verwenden.

Dies sind reale Szenarien, die ständig passieren. Einige Beispiele wurden in früheren Lektionen gegeben, aber hier sind einige weitere:

* Im Jahr 2018 nutzten Hacker einen offenen WLAN-Zugangspunkt an einem Thermostat für ein Fischbecken, um Zugang zum Netzwerk eines Casinos zu erhalten und Daten zu stehlen. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* Im Jahr 2016 startete das Mirai-Botnetz einen Denial-of-Service-Angriff auf Dyn, einen Internetdienstanbieter, und legte große Teile des Internets lahm. Dieses Botnetz nutzte Malware, um sich mit IoT-Geräten wie DVRs und Kameras zu verbinden, die Standard-Benutzernamen und -Passwörter verwendeten, und startete von dort aus den Angriff. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys hatte eine Datenbank von Benutzern ihrer CloudPets verbundenen Spielzeuge öffentlich über das Internet verfügbar. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava markierte Läufer, die Sie überholten, und zeigte ihre Routen, sodass Fremde effektiv sehen konnten, wo Sie wohnen. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Machen Sie eine Recherche: Suchen Sie nach weiteren Beispielen für IoT-Hacks und Datenverletzungen bei IoT-Geräten, insbesondere bei persönlichen Gegenständen wie internetverbundenen Zahnbürsten oder Waagen. Denken Sie über die Auswirkungen dieser Hacks auf die Opfer oder Kunden nach.

> 💁 Sicherheit ist ein riesiges Thema, und diese Lektion wird nur einige der Grundlagen rund um die Verbindung Ihres Geräts mit der Cloud behandeln. Andere Themen, die nicht behandelt werden, umfassen die Überwachung von Datenänderungen während der Übertragung, das direkte Hacken von Geräten oder Änderungen an Gerätekonfigurationen. IoT-Hacking ist eine so große Bedrohung, dass Tools wie [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) entwickelt wurden. Diese Tools sind ähnlich wie die Antiviren- und Sicherheitsprogramme, die Sie möglicherweise auf Ihrem Computer haben, nur für kleine, stromsparende IoT-Geräte konzipiert.

## Kryptographie

Wenn ein Gerät eine Verbindung zu einem IoT-Dienst herstellt, verwendet es eine ID, um sich zu identifizieren. Das Problem ist, dass diese ID geklont werden kann – ein Hacker könnte ein bösartiges Gerät einrichten, das dieselbe ID wie ein echtes Gerät verwendet, aber falsche Daten sendet.

![Sowohl gültige als auch bösartige Geräte könnten dieselbe ID verwenden, um Telemetrie zu senden](../../../../../translated_images/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.de.png)

Die Lösung besteht darin, die gesendeten Daten in ein verschlüsseltes Format umzuwandeln, wobei ein Wert verwendet wird, der nur dem Gerät und der Cloud bekannt ist. Dieser Prozess wird *Verschlüsselung* genannt, und der Wert, der zur Verschlüsselung der Daten verwendet wird, wird als *Verschlüsselungsschlüssel* bezeichnet.

![Wenn Verschlüsselung verwendet wird, werden nur verschlüsselte Nachrichten akzeptiert, andere werden abgelehnt](../../../../../translated_images/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.de.png)

Der Cloud-Dienst kann die Daten dann mit einem Prozess namens *Entschlüsselung* wieder in ein lesbares Format umwandeln, entweder mit demselben Verschlüsselungsschlüssel oder einem *Entschlüsselungsschlüssel*. Wenn die verschlüsselte Nachricht nicht mit dem Schlüssel entschlüsselt werden kann, wurde das Gerät gehackt und die Nachricht wird abgelehnt.

Die Technik zur Durchführung von Verschlüsselung und Entschlüsselung wird als *Kryptographie* bezeichnet.

### Frühe Kryptographie

Die frühesten Arten der Kryptographie waren Substitutionschiffren, die bis vor 3.500 Jahren zurückreichen. Substitutionschiffren beinhalten das Ersetzen eines Buchstabens durch einen anderen. Zum Beispiel beinhaltet die [Caesar-Chiffre](https://wikipedia.org/wiki/Caesar_cipher) das Verschieben des Alphabets um eine definierte Anzahl, wobei nur der Sender der verschlüsselten Nachricht und der beabsichtigte Empfänger wissen, wie viele Buchstaben verschoben werden müssen.

Die [Vigenère-Chiffre](https://wikipedia.org/wiki/Vigenère_cipher) ging noch weiter, indem Wörter verwendet wurden, um Text zu verschlüsseln, sodass jeder Buchstabe im ursprünglichen Text um eine andere Anzahl verschoben wurde, anstatt immer um dieselbe Anzahl von Buchstaben.

Kryptographie wurde für eine Vielzahl von Zwecken verwendet, wie zum Beispiel den Schutz eines Töpferglasurrezepts im alten Mesopotamien, das Schreiben geheimer Liebesbriefe in Indien oder das Geheimhalten von magischen Zaubersprüchen im alten Ägypten.

### Moderne Kryptographie

Moderne Kryptographie ist viel fortschrittlicher und schwerer zu knacken als frühe Methoden. Sie verwendet komplizierte Mathematik, um Daten zu verschlüsseln, mit viel zu vielen möglichen Schlüsseln, um Brute-Force-Angriffe möglich zu machen.

Kryptographie wird auf viele verschiedene Arten für sichere Kommunikation verwendet. Wenn Sie diese Seite auf GitHub lesen, werden Sie möglicherweise bemerken, dass die Website-Adresse mit *HTTPS* beginnt, was bedeutet, dass die Kommunikation zwischen Ihrem Browser und den Webservern von GitHub verschlüsselt ist. Wenn jemand den Internetverkehr zwischen Ihrem Browser und GitHub lesen könnte, könnte er die Daten nicht lesen, da sie verschlüsselt sind. Ihr Computer könnte sogar alle Daten auf Ihrer Festplatte verschlüsseln, sodass, wenn jemand sie stiehlt, er keine Ihrer Daten ohne Ihr Passwort lesen könnte.

> 🎓 HTTPS steht für HyperText Transfer Protocol **Secure**

Leider ist nicht alles sicher. Einige Geräte haben keine Sicherheit, andere sind mit leicht zu knackenden Schlüsseln gesichert, oder manchmal verwenden sogar alle Geräte desselben Typs denselben Schlüssel. Es gibt Berichte über sehr persönliche IoT-Geräte, die alle dasselbe Passwort haben, um sich über WLAN oder Bluetooth zu verbinden. Wenn Sie sich mit Ihrem eigenen Gerät verbinden können, können Sie sich auch mit dem eines anderen verbinden. Sobald Sie verbunden sind, könnten Sie auf sehr private Daten zugreifen oder die Kontrolle über deren Gerät übernehmen.

> 💁 Trotz der Komplexität moderner Kryptographie und der Behauptungen, dass das Knacken von Verschlüsselung Milliarden von Jahren dauern könnte, hat der Aufstieg des Quantencomputings die Möglichkeit eröffnet, alle bekannten Verschlüsselungen in sehr kurzer Zeit zu brechen!

### Symmetrische und asymmetrische Schlüssel

Verschlüsselung gibt es in zwei Typen – symmetrisch und asymmetrisch.

**Symmetrische** Verschlüsselung verwendet denselben Schlüssel, um die Daten zu verschlüsseln und zu entschlüsseln. Sowohl der Sender als auch der Empfänger müssen denselben Schlüssel kennen. Dies ist die am wenigsten sichere Art, da der Schlüssel irgendwie geteilt werden muss. Damit ein Sender eine verschlüsselte Nachricht an einen Empfänger senden kann, muss der Sender dem Empfänger zuerst den Schlüssel senden.

![Symmetrische Schlüsselverschlüsselung verwendet denselben Schlüssel, um eine Nachricht zu verschlüsseln und zu entschlüsseln](../../../../../translated_images/send-message-symmetric-key.a2e8ad0d495896ff.de.png)

Wenn der Schlüssel während der Übertragung gestohlen wird oder der Sender oder Empfänger gehackt wird und der Schlüssel gefunden wird, kann die Verschlüsselung geknackt werden.

![Symmetrische Schlüsselverschlüsselung ist nur sicher, wenn ein Hacker den Schlüssel nicht erhält – wenn doch, kann er die Nachricht abfangen und entschlüsseln](../../../../../translated_images/send-message-symmetric-key-hacker.e7cb53db1707adfb.de.png)

**Asymmetrische** Verschlüsselung verwendet 2 Schlüssel – einen Verschlüsselungsschlüssel und einen Entschlüsselungsschlüssel, die als öffentliches/privates Schlüsselpaar bezeichnet werden. Der öffentliche Schlüssel wird verwendet, um die Nachricht zu verschlüsseln, kann aber nicht verwendet werden, um sie zu entschlüsseln. Der private Schlüssel wird verwendet, um die Nachricht zu entschlüsseln, kann aber nicht verwendet werden, um sie zu verschlüsseln.

![Asymmetrische Verschlüsselung verwendet unterschiedliche Schlüssel zum Verschlüsseln und Entschlüsseln. Der Verschlüsselungsschlüssel wird an alle Nachrichtensender gesendet, damit sie eine Nachricht verschlüsseln können, bevor sie sie an den Empfänger senden, der die Schlüssel besitzt](../../../../../translated_images/send-message-asymmetric.7abe327c62615b8c.de.png)

Der Empfänger teilt seinen öffentlichen Schlüssel, und der Sender verwendet diesen, um die Nachricht zu verschlüsseln. Sobald die Nachricht gesendet wird, entschlüsselt der Empfänger sie mit seinem privaten Schlüssel. Asymmetrische Verschlüsselung ist sicherer, da der private Schlüssel vom Empfänger privat gehalten und niemals geteilt wird. Jeder kann den öffentlichen Schlüssel haben, da er nur zum Verschlüsseln von Nachrichten verwendet werden kann.

Symmetrische Verschlüsselung ist schneller als asymmetrische Verschlüsselung, asymmetrische ist sicherer. Einige Systeme verwenden beide – asymmetrische Verschlüsselung, um den symmetrischen Schlüssel zu verschlüsseln und zu teilen, und dann den symmetrischen Schlüssel, um alle Daten zu verschlüsseln. Dies macht es sicherer, den symmetrischen Schlüssel zwischen Sender und Empfänger zu teilen, und schneller beim Verschlüsseln und Entschlüsseln von Daten.

## Sichern Sie Ihre IoT-Geräte

IoT-Geräte können mit symmetrischer oder asymmetrischer Verschlüsselung gesichert werden. Symmetrisch ist einfacher, aber weniger sicher.

### Symmetrische Schlüssel

Als Sie Ihr IoT-Gerät eingerichtet haben, um mit IoT Hub zu interagieren, haben Sie eine Verbindungszeichenfolge verwendet. Eine Beispiel-Verbindungszeichenfolge ist:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Diese Verbindungszeichenfolge besteht aus drei Teilen, die durch Semikolons getrennt sind, wobei jeder Teil ein Schlüssel und ein Wert ist:

| Schlüssel | Wert | Beschreibung |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | Die URL des IoT Hub |
| DeviceId | `soil-moisture-sensor` | Die eindeutige ID des Geräts |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Ein symmetrischer Schlüssel, der dem Gerät und dem IoT Hub bekannt ist |

Der letzte Teil dieser Verbindungszeichenfolge, der `SharedAccessKey`, ist der symmetrische Schlüssel, der sowohl dem Gerät als auch dem IoT Hub bekannt ist. Dieser Schlüssel wird niemals vom Gerät an die Cloud oder von der Cloud an das Gerät gesendet. Stattdessen wird er verwendet, um gesendete oder empfangene Daten zu verschlüsseln.

✅ Machen Sie ein Experiment. Was denken Sie, wird passieren, wenn Sie den `SharedAccessKey`-Teil der Verbindungszeichenfolge ändern, wenn Sie Ihr IoT-Gerät verbinden? Probieren Sie es aus.

Wenn das Gerät zum ersten Mal versucht, eine Verbindung herzustellen, sendet es ein Shared Access Signature (SAS)-Token, das aus der URL des IoT Hub, einem Zeitstempel, zu dem die Zugriffssignatur abläuft (normalerweise 1 Tag ab der aktuellen Zeit), und einer Signatur besteht. Diese Signatur besteht aus der URL und der Ablaufzeit, die mit dem Shared Access Key aus der Verbindungszeichenfolge verschlüsselt wurden.

Der IoT Hub entschlüsselt diese Signatur mit dem Shared Access Key, und wenn der entschlüsselte Wert mit der URL und dem Ablauf übereinstimmt, darf das Gerät eine Verbindung herstellen. Es überprüft auch, ob die aktuelle Zeit vor dem Ablauf liegt, um zu verhindern, dass ein bösartiges Gerät das SAS-Token eines echten Geräts erfasst und verwendet.

Dies ist eine elegante Möglichkeit, den Sender zu verifizieren. Durch das Senden einiger bekannter Daten sowohl in entschlüsselter als auch verschlüsselter Form kann der Server das Gerät verifizieren, indem er sicherstellt, dass beim Entschlüsseln der verschlüsselten Daten das Ergebnis mit der entschlüsselten Version übereinstimmt, die gesendet wurde. Wenn es übereinstimmt, haben sowohl der Sender als auch der Empfänger denselben symmetrischen Verschlüsselungsschlüssel.
💁 Aufgrund der Ablaufzeit muss Ihr IoT-Gerät die genaue Uhrzeit kennen, die normalerweise von einem [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-Server abgerufen wird. Wenn die Uhrzeit nicht korrekt ist, schlägt die Verbindung fehl.
Nach der Verbindung werden alle Daten, die vom Gerät an den IoT Hub oder vom IoT Hub an das Gerät gesendet werden, mit dem gemeinsam genutzten Zugriffsschlüssel verschlüsselt.

✅ Was denkst du, was passiert, wenn mehrere Geräte denselben Verbindungsstring verwenden?

> 💁 Es ist eine schlechte Sicherheitspraktik, diesen Schlüssel im Code zu speichern. Wenn ein Hacker Zugriff auf deinen Quellcode erhält, kann er den Schlüssel stehlen. Außerdem wird es schwieriger, den Code zu veröffentlichen, da du den Schlüssel für jedes Gerät aktualisieren und neu kompilieren müsstest. Es ist besser, diesen Schlüssel aus einem Hardware-Sicherheitsmodul zu laden – einem Chip auf dem IoT-Gerät, der verschlüsselte Werte speichert, die von deinem Code gelesen werden können.
>
> Beim Erlernen von IoT ist es oft einfacher, den Schlüssel im Code zu speichern, wie du es in einer früheren Lektion getan hast. Du musst jedoch sicherstellen, dass dieser Schlüssel nicht in öffentlichen Quellcodekontrollsystemen eingecheckt wird.

Geräte haben 2 Schlüssel und 2 entsprechende Verbindungsstrings. Dies ermöglicht es, die Schlüssel zu rotieren – also von einem Schlüssel auf einen anderen zu wechseln, falls der erste kompromittiert wird, und den ersten Schlüssel neu zu generieren.

### X.509-Zertifikate

Wenn du asymmetrische Verschlüsselung mit einem öffentlichen/privaten Schlüsselpaar verwendest, musst du deinen öffentlichen Schlüssel jedem zur Verfügung stellen, der dir Daten senden möchte. Das Problem ist: Wie kann der Empfänger deines Schlüssels sicher sein, dass es tatsächlich dein öffentlicher Schlüssel ist und nicht jemand, der sich als dich ausgibt? Anstatt einen Schlüssel bereitzustellen, kannst du deinen öffentlichen Schlüssel in einem Zertifikat bereitstellen, das von einer vertrauenswürdigen dritten Partei, einem sogenannten X.509-Zertifikat, verifiziert wurde.

X.509-Zertifikate sind digitale Dokumente, die den öffentlichen Schlüsselteil des öffentlichen/privaten Schlüsselpaares enthalten. Sie werden normalerweise von einer Reihe vertrauenswürdiger Organisationen, den sogenannten [Zertifizierungsstellen](https://wikipedia.org/wiki/Certificate_authority) (CAs), ausgestellt und digital von der CA signiert, um anzuzeigen, dass der Schlüssel gültig ist und von dir stammt. Du vertraust dem Zertifikat und dem öffentlichen Schlüssel, weil du der CA vertraust – ähnlich wie du einem Reisepass oder Führerschein vertraust, weil du dem ausstellenden Land vertraust. Zertifikate kosten Geld, daher kannst du auch ein "selbstsigniertes" Zertifikat erstellen, das von dir selbst signiert wurde, z. B. für Testzwecke.

> 💁 Du solltest niemals ein selbstsigniertes Zertifikat für eine Produktionsumgebung verwenden.

Diese Zertifikate enthalten eine Reihe von Feldern, darunter Informationen darüber, von wem der öffentliche Schlüssel stammt, Details zur ausstellenden CA, die Gültigkeitsdauer und den öffentlichen Schlüssel selbst. Bevor du ein Zertifikat verwendest, ist es eine gute Praxis, es zu überprüfen, indem du sicherstellst, dass es von der ursprünglichen CA signiert wurde.

✅ Eine vollständige Liste der Felder im Zertifikat findest du im [Microsoft-Tutorial zu X.509-Zertifikaten](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Bei der Verwendung von X.509-Zertifikaten haben sowohl der Sender als auch der Empfänger ihre eigenen öffentlichen und privaten Schlüssel sowie X.509-Zertifikate, die den öffentlichen Schlüssel enthalten. Sie tauschen dann irgendwie X.509-Zertifikate aus, verwenden die öffentlichen Schlüssel des jeweils anderen, um die gesendeten Daten zu verschlüsseln, und ihren eigenen privaten Schlüssel, um die empfangenen Daten zu entschlüsseln.

![Anstatt einen öffentlichen Schlüssel zu teilen, kannst du ein Zertifikat teilen. Der Nutzer des Zertifikats kann überprüfen, dass es von dir stammt, indem er bei der Zertifizierungsstelle nachfragt, die es signiert hat.](../../../../../translated_images/send-message-certificate.9cc576ac1e46b76e.de.png)

Ein großer Vorteil der Verwendung von X.509-Zertifikaten ist, dass sie zwischen Geräten geteilt werden können. Du kannst ein Zertifikat erstellen, es in den IoT Hub hochladen und für alle deine Geräte verwenden. Jedes Gerät muss dann nur den privaten Schlüssel kennen, um die Nachrichten zu entschlüsseln, die es vom IoT Hub erhält.

Das Zertifikat, das dein Gerät verwendet, um Nachrichten zu verschlüsseln, die es an den IoT Hub sendet, wird von Microsoft veröffentlicht. Es ist dasselbe Zertifikat, das viele Azure-Dienste verwenden, und ist manchmal in die SDKs integriert.

> 💁 Denke daran: Ein öffentlicher Schlüssel ist genau das – öffentlich. Der öffentliche Schlüssel von Azure kann nur verwendet werden, um Daten zu verschlüsseln, die an Azure gesendet werden, nicht um sie zu entschlüsseln. Daher kann er überall geteilt werden, auch im Quellcode. Zum Beispiel kannst du ihn im [Azure IoT C SDK Quellcode](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c) sehen.

✅ Es gibt viele Fachbegriffe im Zusammenhang mit X.509-Zertifikaten. Du kannst die Definitionen einiger Begriffe im [Leitfaden für X.509-Zertifikatsjargon für Laien](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn) nachlesen.

## X.509-Zertifikat erstellen und verwenden

Die Schritte zur Erstellung eines X.509-Zertifikats sind:

1. Erstelle ein öffentliches/privates Schlüsselpaar. Einer der am häufigsten verwendeten Algorithmen zur Erstellung eines solchen Schlüsselpaares ist [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem)) (RSA).

1. Reiche den öffentlichen Schlüssel mit zugehörigen Daten zur Signierung ein, entweder bei einer CA oder durch Selbstsignierung.

Die Azure CLI bietet Befehle, um eine neue Geräteidentität im IoT Hub zu erstellen und automatisch das öffentliche/privates Schlüsselpaar zu generieren sowie ein selbstsigniertes Zertifikat zu erstellen.

> 💁 Wenn du die Schritte im Detail sehen möchtest, anstatt die Azure CLI zu verwenden, findest du sie im [OpenSSL-Tutorial zur Erstellung selbstsignierter Zertifikate in der Microsoft IoT Hub-Dokumentation](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Aufgabe – Geräteidentität mit einem X.509-Zertifikat erstellen

1. Führe den folgenden Befehl aus, um die neue Geräteidentität zu registrieren und automatisch die Schlüssel und Zertifikate zu generieren:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Ersetze `<hub_name>` durch den Namen, den du für deinen IoT Hub verwendet hast.

    Dadurch wird ein Gerät mit der ID `soil-moisture-sensor-x509` erstellt, um es von der Geräteidentität zu unterscheiden, die du in der letzten Lektion erstellt hast. Dieser Befehl erstellt außerdem 2 Dateien im aktuellen Verzeichnis:

    * `soil-moisture-sensor-x509-key.pem` – diese Datei enthält den privaten Schlüssel für das Gerät.
    * `soil-moisture-sensor-x509-cert.pem` – dies ist die X.509-Zertifikatsdatei für das Gerät.

    Bewahre diese Dateien sicher auf! Die Datei mit dem privaten Schlüssel sollte nicht in öffentliche Quellcodekontrollsysteme eingecheckt werden.

### Aufgabe – Verwende das X.509-Zertifikat in deinem Gerätekode

Arbeite die entsprechende Anleitung durch, um dein IoT-Gerät mit dem X.509-Zertifikat mit der Cloud zu verbinden:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer-x509.md)

---

## 🚀 Herausforderung

Es gibt mehrere Möglichkeiten, Azure-Dienste wie Ressourcengruppen und IoT Hubs zu erstellen, zu verwalten und zu löschen. Eine Möglichkeit ist das [Azure-Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) – eine webbasierte Oberfläche, die dir eine GUI zur Verwaltung deiner Azure-Dienste bietet.

Gehe zu [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) und erkunde das Portal. Versuche, einen IoT Hub über das Portal zu erstellen und ihn anschließend zu löschen.

**Tipp** – Wenn du Dienste über das Portal erstellst, musst du nicht im Voraus eine Ressourcengruppe erstellen. Eine Ressourcengruppe kann während der Diensterstellung erstellt werden. Stelle sicher, dass du sie löschst, wenn du fertig bist!

Du findest viele Dokumentationen, Tutorials und Anleitungen zum Azure-Portal in der [Azure-Portal-Dokumentation](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Rückblick & Selbststudium

* Lies die Geschichte der Kryptographie auf der [Wikipedia-Seite zur Geschichte der Kryptographie](https://wikipedia.org/wiki/History_of_cryptography).
* Informiere dich über X.509-Zertifikate auf der [Wikipedia-Seite zu X.509](https://wikipedia.org/wiki/X.509).

## Aufgabe

[Erstelle ein neues IoT-Gerät](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.