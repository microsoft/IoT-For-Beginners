<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-25T21:43:19+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "de"
}
-->
# Migrieren Sie Ihre Pflanze in die Cloud

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Diese Lektion wurde als Teil der [IoT für Anfänger Projekt 2 - Serie Digitale Landwirtschaft](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) vom [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) unterrichtet.

[![Verbinden Sie Ihr Gerät mit der Cloud über Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Einführung

In der letzten Lektion haben Sie gelernt, wie Sie Ihre Pflanze mit einem MQTT-Broker verbinden und ein Relais über Servercode steuern, der lokal ausgeführt wird. Dies bildet den Kern eines internetverbundenen automatisierten Bewässerungssystems, das von einzelnen Pflanzen zu Hause bis hin zu kommerziellen Farmen verwendet wird.

Das IoT-Gerät kommunizierte mit einem öffentlichen MQTT-Broker, um die Prinzipien zu demonstrieren, aber dies ist nicht die zuverlässigste oder sicherste Methode. In dieser Lektion lernen Sie die Cloud und die IoT-Funktionen öffentlicher Cloud-Dienste kennen. Außerdem erfahren Sie, wie Sie Ihre Pflanze von einem öffentlichen MQTT-Broker zu einem dieser Cloud-Dienste migrieren können.

In dieser Lektion behandeln wir:

* [Was ist die Cloud?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Erstellen Sie ein Cloud-Abonnement](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloud-IoT-Dienste](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Erstellen Sie einen IoT-Dienst in der Cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kommunizieren Sie mit IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Verbinden Sie Ihr Gerät mit dem IoT-Dienst](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Was ist die Cloud?

Vor der Cloud, wenn ein Unternehmen seinen Mitarbeitern (wie Datenbanken oder Dateispeicher) oder der Öffentlichkeit (wie Websites) Dienste bereitstellen wollte, musste es ein Rechenzentrum bauen und betreiben. Dies reichte von einem Raum mit wenigen Computern bis hin zu einem Gebäude mit vielen Computern. Das Unternehmen musste alles verwalten, einschließlich:

* Kauf von Computern
* Wartung der Hardware
* Stromversorgung und Kühlung
* Netzwerke
* Sicherheit, einschließlich der Sicherung des Gebäudes und der Software auf den Computern
* Installation und Aktualisierung von Software

Das konnte sehr teuer sein, eine breite Palette von qualifizierten Mitarbeitern erfordern und sehr langsam sein, wenn Änderungen nötig waren. Zum Beispiel, wenn ein Online-Shop eine geschäftige Weihnachtszeit planen wollte, musste er Monate im Voraus zusätzliche Hardware kaufen, konfigurieren, installieren und die Software für den Verkaufsprozess installieren. Nach der Weihnachtszeit, wenn die Verkäufe wieder zurückgingen, blieben die gekauften Computer ungenutzt bis zur nächsten geschäftigen Saison.

✅ Glauben Sie, dass dies Unternehmen ermöglicht, schnell zu reagieren? Wenn ein Online-Modehändler plötzlich durch einen Prominenten, der seine Kleidung trägt, populär wird, könnte er schnell genug seine Rechenleistung erhöhen, um den plötzlichen Anstieg der Bestellungen zu bewältigen?

### Der Computer von jemand anderem

Die Cloud wird oft scherzhaft als "der Computer von jemand anderem" bezeichnet. Die ursprüngliche Idee war einfach – anstatt Computer zu kaufen, mietet man die Computer von jemand anderem. Jemand anderes, ein Cloud-Computing-Anbieter, würde riesige Rechenzentren verwalten. Sie wären verantwortlich für den Kauf und die Installation der Hardware, die Verwaltung von Strom und Kühlung, Netzwerken, Gebäudesicherheit, Hardware- und Software-Updates, alles. Als Kunde mietet man die benötigten Computer, mietet mehr, wenn die Nachfrage steigt, und reduziert die Anzahl, wenn die Nachfrage sinkt. Diese Cloud-Rechenzentren befinden sich weltweit.

![Ein Microsoft Cloud-Rechenzentrum](../../../../../translated_images/de/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Geplante Erweiterung eines Microsoft Cloud-Rechenzentrums](../../../../../translated_images/de/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

Diese Rechenzentren können mehrere Quadratkilometer groß sein. Die obigen Bilder wurden vor einigen Jahren in einem Microsoft Cloud-Rechenzentrum aufgenommen und zeigen die ursprüngliche Größe sowie eine geplante Erweiterung. Das für die Erweiterung geräumte Gebiet umfasst über 5 Quadratkilometer.

> 💁 Diese Rechenzentren benötigen so große Mengen an Energie, dass einige ihre eigenen Kraftwerke haben. Aufgrund ihrer Größe und des Investitionsniveaus der Cloud-Anbieter sind sie in der Regel sehr umweltfreundlich. Sie sind effizienter als viele kleine Rechenzentren, laufen überwiegend mit erneuerbarer Energie, und Cloud-Anbieter arbeiten hart daran, Abfall zu reduzieren, den Wasserverbrauch zu senken und Wälder wieder aufzuforsten, die für den Bau von Rechenzentren gerodet wurden. Weitere Informationen darüber, wie ein Cloud-Anbieter an Nachhaltigkeit arbeitet, finden Sie auf der [Azure Nachhaltigkeitsseite](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Recherchieren Sie: Lesen Sie über die großen Clouds wie [Azure von Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) oder [GCP von Google](https://cloud.google.com). Wie viele Rechenzentren haben sie und wo befinden sich diese weltweit?

Die Nutzung der Cloud hält die Kosten für Unternehmen niedrig und ermöglicht es ihnen, sich auf das zu konzentrieren, was sie am besten können, während die Cloud-Computing-Expertise in den Händen des Anbieters bleibt. Unternehmen müssen keine Rechenzentrumsfläche mehr mieten oder kaufen, verschiedene Anbieter für Konnektivität und Strom bezahlen oder Experten einstellen. Stattdessen können sie eine monatliche Rechnung an den Cloud-Anbieter zahlen, der sich um alles kümmert.

Der Cloud-Anbieter kann dann Skaleneffekte nutzen, um die Kosten zu senken, indem er Computer in großen Mengen zu niedrigeren Preisen kauft, in Werkzeuge investiert, um den Wartungsaufwand zu reduzieren, und sogar eigene Hardware entwirft und baut, um sein Cloud-Angebot zu verbessern.

### Microsoft Azure

Azure ist die Entwickler-Cloud von Microsoft, und dies ist die Cloud, die Sie für diese Lektionen verwenden werden. Das folgende Video gibt einen kurzen Überblick über Azure:

[![Übersicht über Azure Video](../../../../../translated_images/de/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Erstellen Sie ein Cloud-Abonnement

Um Dienste in der Cloud zu nutzen, müssen Sie sich bei einem Cloud-Anbieter für ein Abonnement anmelden. Für diese Lektion melden Sie sich für ein Microsoft Azure-Abonnement an. Wenn Sie bereits ein Azure-Abonnement haben, können Sie diese Aufgabe überspringen. Die hier beschriebenen Abonnementdetails sind zum Zeitpunkt des Schreibens korrekt, können sich jedoch ändern.

> 💁 Wenn Sie diese Lektionen über Ihre Schule besuchen, haben Sie möglicherweise bereits ein Azure-Abonnement zur Verfügung. Fragen Sie Ihren Lehrer.

Es gibt zwei verschiedene Arten von kostenlosen Azure-Abonnements, die Sie abschließen können:

* **Azure für Studenten** - Dies ist ein Abonnement, das für Studenten ab 18 Jahren konzipiert ist. Sie benötigen keine Kreditkarte, um sich anzumelden, und verwenden Ihre Schul-E-Mail-Adresse, um zu bestätigen, dass Sie Student sind. Bei der Anmeldung erhalten Sie 100 US-Dollar, die Sie für Cloud-Ressourcen ausgeben können, sowie kostenlose Dienste, einschließlich einer kostenlosen Version eines IoT-Dienstes. Dies gilt für 12 Monate und kann jedes Jahr verlängert werden, solange Sie Student bleiben.

* **Azure kostenloses Abonnement** - Dies ist ein Abonnement für alle, die keine Studenten sind. Sie benötigen eine Kreditkarte, um sich für das Abonnement anzumelden, aber Ihre Karte wird nicht belastet, sie wird nur verwendet, um zu überprüfen, dass Sie ein echter Mensch und kein Bot sind. Sie erhalten 200 US-Dollar Guthaben, das Sie in den ersten 30 Tagen für beliebige Dienste verwenden können, sowie kostenlose Stufen von Azure-Diensten. Sobald Ihr Guthaben aufgebraucht ist, wird Ihre Karte nicht belastet, es sei denn, Sie wechseln zu einem Pay-as-you-go-Abonnement.

> 💁 Microsoft bietet ein Azure für Studenten Starter-Abonnement für Schüler unter 18 Jahren an, aber zum Zeitpunkt des Schreibens unterstützt dieses keine IoT-Dienste.

### Aufgabe - Melden Sie sich für ein kostenloses Cloud-Abonnement an

Wenn Sie ein Student ab 18 Jahren sind, können Sie sich für ein Azure für Studenten-Abonnement anmelden. Sie müssen dies mit einer Schul-E-Mail-Adresse bestätigen. Sie können dies auf zwei Arten tun:

* Melden Sie sich für ein GitHub Student Developer Pack unter [education.github.com/pack](https://education.github.com/pack) an. Dies gibt Ihnen Zugang zu einer Reihe von Tools und Angeboten, einschließlich GitHub und Microsoft Azure. Sobald Sie sich für das Developer Pack angemeldet haben, können Sie das Azure für Studenten-Angebot aktivieren.

* Melden Sie sich direkt für ein Azure für Studenten-Konto unter [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn) an.

> ⚠️ Wenn Ihre Schul-E-Mail-Adresse nicht erkannt wird, erstellen Sie ein [Issue in diesem Repository](https://github.com/Microsoft/IoT-For-Beginners/issues), und wir werden prüfen, ob sie zur Azure für Studenten-Zulassungsliste hinzugefügt werden kann.

Wenn Sie kein Student sind oder keine gültige Schul-E-Mail-Adresse haben, können Sie sich für ein Azure Free-Abonnement anmelden.

* Melden Sie sich für ein Azure Free-Abonnement unter [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn) an.

## Cloud-IoT-Dienste

Der öffentliche Test-MQTT-Broker, den Sie verwendet haben, ist ein großartiges Werkzeug zum Lernen, hat jedoch einige Nachteile, wenn er in einem kommerziellen Umfeld eingesetzt wird:

* Zuverlässigkeit - Es ist ein kostenloser Dienst ohne Garantien und kann jederzeit abgeschaltet werden.
* Sicherheit - Er ist öffentlich, sodass jeder Ihre Telemetrie abhören oder Befehle senden könnte, um Ihre Hardware zu steuern.
* Leistung - Er ist für nur wenige Testnachrichten ausgelegt und würde eine große Menge an Nachrichten nicht bewältigen.
* Erkennung - Es gibt keine Möglichkeit zu wissen, welche Geräte verbunden sind.

IoT-Dienste in der Cloud lösen diese Probleme. Sie werden von großen Cloud-Anbietern betrieben, die stark in Zuverlässigkeit investieren und bereit sind, auftretende Probleme zu beheben. Sie haben Sicherheit integriert, um Hacker daran zu hindern, Ihre Daten zu lesen oder falsche Befehle zu senden. Sie sind auch leistungsstark und können viele Millionen Nachrichten pro Tag verarbeiten, wobei sie die Skalierbarkeit der Cloud nutzen.

> 💁 Obwohl Sie für diese Vorteile eine monatliche Gebühr zahlen, bieten die meisten Cloud-Anbieter eine kostenlose Version ihres IoT-Dienstes mit einer begrenzten Anzahl von Nachrichten pro Tag oder Geräten, die sich verbinden können. Diese kostenlose Version ist normalerweise mehr als ausreichend, damit Entwickler den Dienst kennenlernen können. In dieser Lektion verwenden Sie eine kostenlose Version.

IoT-Geräte verbinden sich entweder über ein Geräte-SDK (eine Bibliothek, die Code für die Funktionen des Dienstes bereitstellt) oder direkt über ein Kommunikationsprotokoll wie MQTT oder HTTP mit einem Cloud-Dienst. Das Geräte-SDK ist normalerweise der einfachste Weg, da es alles für Sie erledigt, wie z. B. die Themen, die veröffentlicht oder abonniert werden sollen, und die Handhabung der Sicherheit.

![Geräte verbinden sich mit einem Dienst über ein Geräte-SDK. Servercode verbindet sich ebenfalls über ein SDK](../../../../../translated_images/de/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

Ihr Gerät kommuniziert dann mit anderen Teilen Ihrer Anwendung über diesen Dienst – ähnlich wie Sie Telemetrie gesendet und Befehle über MQTT empfangen haben. Dies geschieht normalerweise über ein Service-SDK oder eine ähnliche Bibliothek. Nachrichten kommen von Ihrem Gerät zum Dienst, wo andere Komponenten Ihrer Anwendung sie lesen können, und Nachrichten können dann zurück an Ihr Gerät gesendet werden.

![Geräte ohne gültigen geheimen Schlüssel können sich nicht mit dem IoT-Dienst verbinden](../../../../../translated_images/de/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

Diese Dienste implementieren Sicherheit, indem sie alle Geräte kennen, die sich verbinden und Daten senden können, entweder indem die Geräte vorab beim Dienst registriert werden oder indem den Geräten geheime Schlüssel oder Zertifikate gegeben werden, die sie verwenden können, um sich beim ersten Verbindungsaufbau selbst zu registrieren. Unbekannte Geräte können sich nicht verbinden; wenn sie es versuchen, lehnt der Dienst die Verbindung ab und ignoriert die von ihnen gesendeten Nachrichten.

✅ Recherchieren Sie: Was ist der Nachteil eines offenen IoT-Dienstes, bei dem sich jedes Gerät oder jeder Code verbinden kann? Können Sie spezifische Beispiele finden, bei denen Hacker dies ausgenutzt haben?

Andere Komponenten Ihrer Anwendung können sich mit dem IoT-Dienst verbinden und Informationen über alle verbundenen oder registrierten Geräte erhalten sowie direkt mit ihnen kommunizieren, entweder einzeln oder in Gruppen.
💁 IoT-Dienste implementieren auch zusätzliche Funktionen, und die Cloud-Anbieter verfügen über weitere Dienste und Anwendungen, die mit dem Dienst verbunden werden können. Zum Beispiel, wenn Sie alle Telemetrie-Nachrichten, die von allen Geräten gesendet werden, in einer Datenbank speichern möchten, sind dafür in der Regel nur wenige Klicks im Konfigurationstool des Cloud-Anbieters erforderlich, um den Dienst mit einer Datenbank zu verbinden und die Daten zu streamen.
## Erstellen eines IoT-Dienstes in der Cloud

Jetzt, da Sie ein Azure-Abonnement haben, können Sie sich für einen IoT-Dienst anmelden. Der IoT-Dienst von Microsoft heißt Azure IoT Hub.

![Das Azure IoT Hub Logo](../../../../../translated_images/de/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

Das folgende Video gibt einen kurzen Überblick über Azure IoT Hub:

[![Übersicht über Azure IoT Hub Video](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Klicken Sie auf das Bild oben, um das Video anzusehen.

✅ Nehmen Sie sich einen Moment Zeit, um zu recherchieren und lesen Sie die Übersicht über IoT Hub in der [Microsoft IoT Hub Dokumentation](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Die in Azure verfügbaren Cloud-Dienste können über ein webbasiertes Portal oder eine Befehlszeilenschnittstelle (CLI) konfiguriert werden. Für diese Aufgabe verwenden Sie die CLI.

### Aufgabe - Installieren der Azure CLI

Um die Azure CLI zu verwenden, muss sie zuerst auf Ihrem PC oder Mac installiert werden.

1. Folgen Sie den Anweisungen in der [Azure CLI Dokumentation](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn), um die CLI zu installieren.

1. Die Azure CLI unterstützt eine Reihe von Erweiterungen, die zusätzliche Funktionen zur Verwaltung einer Vielzahl von Azure-Diensten hinzufügen. Installieren Sie die IoT-Erweiterung, indem Sie den folgenden Befehl in Ihrer Befehlszeile oder Ihrem Terminal ausführen:

    ```sh
    az extension add --name azure-iot
    ```

1. Führen Sie den folgenden Befehl in Ihrer Befehlszeile oder Ihrem Terminal aus, um sich mit Ihrem Azure-Abonnement über die Azure CLI anzumelden.

    ```sh
    az login
    ```

    Eine Webseite wird in Ihrem Standardbrowser geöffnet. Melden Sie sich mit dem Konto an, das Sie für Ihr Azure-Abonnement verwendet haben. Sobald Sie angemeldet sind, können Sie die Browser-Registerkarte schließen.

1. Wenn Sie mehrere Azure-Abonnements haben, wie z. B. ein von der Schule bereitgestelltes und Ihr eigenes Azure für Studenten-Abonnement, müssen Sie dasjenige auswählen, das Sie verwenden möchten. Führen Sie den folgenden Befehl aus, um alle Abonnements aufzulisten, auf die Sie Zugriff haben:

    ```sh
    az account list --output table
    ```

    Im Output sehen Sie den Namen jedes Abonnements zusammen mit seiner `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Um das Abonnement auszuwählen, das Sie verwenden möchten, verwenden Sie den folgenden Befehl:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Ersetzen Sie `<SubscriptionId>` durch die ID des Abonnements, das Sie verwenden möchten. Nachdem Sie diesen Befehl ausgeführt haben, führen Sie den Befehl erneut aus, um Ihre Konten aufzulisten. Sie werden sehen, dass die Spalte `IsDefault` für das Abonnement, das Sie gerade festgelegt haben, mit `True` markiert ist.

### Aufgabe - Erstellen einer Ressourcengruppe

Azure-Dienste wie IoT Hub-Instanzen, virtuelle Maschinen, Datenbanken oder KI-Dienste werden als **Ressourcen** bezeichnet. Jede Ressource muss in einer **Ressourcengruppe** leben, einer logischen Gruppierung von einer oder mehreren Ressourcen.

> 💁 Mit Ressourcengruppen können Sie mehrere Dienste gleichzeitig verwalten. Zum Beispiel können Sie, nachdem Sie alle Lektionen für dieses Projekt abgeschlossen haben, die Ressourcengruppe löschen, und alle darin enthaltenen Ressourcen werden automatisch gelöscht.

1. Es gibt mehrere Azure-Datenzentren auf der ganzen Welt, die in Regionen unterteilt sind. Wenn Sie eine Azure-Ressource oder Ressourcengruppe erstellen, müssen Sie angeben, wo Sie sie erstellen möchten. Führen Sie den folgenden Befehl aus, um die Liste der Standorte zu erhalten:

    ```sh
    az account list-locations --output table
    ```

    Sie werden eine Liste von Standorten sehen. Diese Liste wird lang sein.

    > 💁 Zum Zeitpunkt des Schreibens gibt es 65 Standorte, zu denen Sie bereitstellen können.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Notieren Sie sich den Wert aus der Spalte `Name` der Region, die Ihnen am nächsten liegt. Sie können die Regionen auf einer Karte auf der [Azure Geographies Seite](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn) finden.

1. Führen Sie den folgenden Befehl aus, um eine Ressourcengruppe namens `soil-moisture-sensor` zu erstellen. Ressourcengruppennamen müssen in Ihrem Abonnement eindeutig sein.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Ersetzen Sie `<location>` durch den Standort, den Sie im vorherigen Schritt ausgewählt haben.

### Aufgabe - Erstellen eines IoT Hub

Sie können jetzt eine IoT Hub-Ressource in Ihrer Ressourcengruppe erstellen.

1. Verwenden Sie den folgenden Befehl, um Ihre IoT Hub-Ressource zu erstellen:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch einen Namen für Ihren Hub. Dieser Name muss weltweit eindeutig sein - das heißt, kein anderer IoT Hub, der von jemandem erstellt wurde, darf denselben Namen haben. Dieser Name wird in einer URL verwendet, die auf den Hub verweist, und muss daher eindeutig sein. Verwenden Sie etwas wie `soil-moisture-sensor-` und fügen Sie am Ende einen eindeutigen Identifikator hinzu, wie einige zufällige Wörter oder Ihren Namen.

    Die Option `--sku F1` gibt an, dass die kostenlose Stufe verwendet werden soll. Die kostenlose Stufe unterstützt 8.000 Nachrichten pro Tag sowie die meisten Funktionen der kostenpflichtigen Stufen.

    > 🎓 Unterschiedliche Preisstufen von Azure-Diensten werden als Tiers bezeichnet. Jede Stufe hat unterschiedliche Kosten und bietet unterschiedliche Funktionen oder Datenvolumen.

    > 💁 Wenn Sie mehr über die Preisgestaltung erfahren möchten, können Sie den [Azure IoT Hub Preisleitfaden](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn) ansehen.

    Die Option `--partition-count 2` definiert, wie viele Datenströme der IoT Hub unterstützt. Mehr Partitionen reduzieren Datenblockierungen, wenn mehrere Dinge vom IoT Hub lesen und schreiben. Partitionen liegen außerhalb des Umfangs dieser Lektionen, aber dieser Wert muss festgelegt werden, um einen kostenlosen IoT Hub zu erstellen.

    > 💁 Sie können pro Abonnement nur einen kostenlosen IoT Hub haben.

Der IoT Hub wird erstellt. Es kann eine Minute oder länger dauern, bis dies abgeschlossen ist.

## Kommunikation mit IoT Hub

In der vorherigen Lektion haben Sie MQTT verwendet und Nachrichten hin und her über verschiedene Themen gesendet, wobei die verschiedenen Themen unterschiedliche Zwecke hatten. Anstatt Nachrichten über verschiedene Themen zu senden, hat IoT Hub eine Reihe von definierten Möglichkeiten, wie das Gerät mit dem Hub kommunizieren kann oder der Hub mit dem Gerät kommunizieren kann.

> 💁 Im Hintergrund kann diese Kommunikation zwischen IoT Hub und Ihrem Gerät MQTT, HTTPS oder AMQP verwenden.

* Device-to-Cloud (D2C)-Nachrichten - Dies sind Nachrichten, die von einem Gerät an IoT Hub gesendet werden, wie Telemetrie. Sie können dann von Ihrem Anwendungscode aus dem IoT Hub gelesen werden.

    > 🎓 Im Hintergrund verwendet IoT Hub einen Azure-Dienst namens [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Wenn Sie Code schreiben, um Nachrichten zu lesen, die an den Hub gesendet werden, werden diese oft als Ereignisse bezeichnet.

* Cloud-to-Device (C2D)-Nachrichten - Dies sind Nachrichten, die von Anwendungscode über einen IoT Hub an ein IoT-Gerät gesendet werden.

* Direkte Methodenanforderungen - Dies sind Nachrichten, die von Anwendungscode über einen IoT Hub an ein IoT-Gerät gesendet werden, um das Gerät zu einer Aktion aufzufordern, wie z. B. die Steuerung eines Aktuators. Diese Nachrichten erfordern eine Antwort, damit Ihr Anwendungscode erkennen kann, ob sie erfolgreich verarbeitet wurden.

* Device Twins - Dies sind JSON-Dokumente, die zwischen dem Gerät und IoT Hub synchronisiert werden und verwendet werden, um Einstellungen oder andere Eigenschaften zu speichern, die entweder vom Gerät gemeldet oder vom IoT Hub auf dem Gerät (als "gewünscht" bezeichnet) festgelegt werden sollen.

IoT Hub kann Nachrichten und direkte Methodenanforderungen für einen konfigurierbaren Zeitraum speichern (standardmäßig einen Tag), sodass ein Gerät oder Anwendungscode, das die Verbindung verliert, nach der Wiederverbindung weiterhin Nachrichten abrufen kann, die während der Offline-Zeit gesendet wurden. Device Twins werden dauerhaft im IoT Hub gespeichert, sodass ein Gerät jederzeit wieder eine Verbindung herstellen und den neuesten Device Twin abrufen kann.

✅ Recherchieren Sie: Lesen Sie mehr über diese Nachrichtentypen in der [Device-to-Cloud-Kommunikationsanleitung](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) und der [Cloud-to-Device-Kommunikationsanleitung](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) in der IoT Hub-Dokumentation.

## Verbinden Sie Ihr Gerät mit dem IoT-Dienst

Sobald der Hub erstellt ist, kann Ihr IoT-Gerät eine Verbindung herstellen. Nur registrierte Geräte können eine Verbindung zu einem Dienst herstellen, daher müssen Sie Ihr Gerät zuerst registrieren. Bei der Registrierung erhalten Sie eine Verbindungszeichenfolge, die das Gerät verwenden kann, um eine Verbindung herzustellen. Diese Verbindungszeichenfolge ist gerätespezifisch und enthält Informationen über den IoT Hub, das Gerät und einen geheimen Schlüssel, der es diesem Gerät ermöglicht, eine Verbindung herzustellen.

> 🎓 Eine Verbindungszeichenfolge ist ein allgemeiner Begriff für ein Textstück, das Verbindungsdetails enthält. Diese werden beim Verbinden mit IoT Hubs, Datenbanken und vielen anderen Diensten verwendet. Sie bestehen normalerweise aus einem Identifikator für den Dienst, wie einer URL, und Sicherheitsinformationen wie einem geheimen Schlüssel. Diese werden an SDKs übergeben, um eine Verbindung zum Dienst herzustellen.

> ⚠️ Verbindungszeichenfolgen sollten sicher aufbewahrt werden! Sicherheit wird in einer zukünftigen Lektion ausführlicher behandelt.

### Aufgabe - Registrieren Ihres IoT-Geräts

Das IoT-Gerät kann mit Ihrem IoT Hub über die Azure CLI registriert werden.

1. Führen Sie den folgenden Befehl aus, um ein Gerät zu registrieren:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen, den Sie für Ihren IoT Hub verwendet haben.

    Dadurch wird ein Gerät mit einer ID von `soil-moisture-sensor` erstellt.

1. Wenn Ihr IoT-Gerät eine Verbindung zu Ihrem IoT Hub über das SDK herstellt, muss es eine Verbindungszeichenfolge verwenden, die die URL des Hubs zusammen mit einem geheimen Schlüssel enthält. Führen Sie den folgenden Befehl aus, um die Verbindungszeichenfolge zu erhalten:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen, den Sie für Ihren IoT Hub verwendet haben.

1. Speichern Sie die Verbindungszeichenfolge, die im Output angezeigt wird, da Sie sie später benötigen.

### Aufgabe - Verbinden Ihres IoT-Geräts mit der Cloud

Arbeiten Sie die entsprechende Anleitung durch, um Ihr IoT-Gerät mit der Cloud zu verbinden:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer-connect-hub.md)

### Aufgabe - Ereignisse überwachen

Für den Moment werden Sie Ihren Servercode nicht aktualisieren. Stattdessen können Sie die Azure CLI verwenden, um Ereignisse von Ihrem IoT-Gerät zu überwachen.

1. Stellen Sie sicher, dass Ihr IoT-Gerät läuft und Telemetriedaten zur Bodenfeuchtigkeit sendet.

1. Führen Sie den folgenden Befehl in Ihrer Eingabeaufforderung oder Ihrem Terminal aus, um Nachrichten zu überwachen, die an Ihren IoT Hub gesendet werden:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen, den Sie für Ihren IoT Hub verwendet haben.

    Sie werden Nachrichten in der Konsolenausgabe sehen, sobald sie von Ihrem IoT-Gerät gesendet werden.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Der Inhalt des `payload` entspricht der Nachricht, die von Ihrem IoT-Gerät gesendet wurde.

    > Zum Zeitpunkt des Schreibens funktioniert die `az iot` Erweiterung nicht vollständig auf Apple Silicon. Wenn Sie ein Apple Silicon-Gerät verwenden, müssen Sie die Nachrichten auf eine andere Weise überwachen, z. B. mit den [Azure IoT Tools für Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Diese Nachrichten haben eine Reihe von Eigenschaften, die automatisch angehängt werden, wie z. B. der Zeitstempel, zu dem sie gesendet wurden. Diese werden als *Anmerkungen* bezeichnet. Um alle Nachrichtenanmerkungen anzuzeigen, verwenden Sie den folgenden Befehl:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen, den Sie für Ihren IoT Hub verwendet haben.

    Sie werden Nachrichten in der Konsolenausgabe sehen, sobald sie von Ihrem IoT-Gerät gesendet werden.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Die Zeitwerte in den Anmerkungen sind in [UNIX-Zeit](https://wikipedia.org/wiki/Unix_time), die die Anzahl der Sekunden seit Mitternacht am 1. Januar 1970 darstellt.

    Beenden Sie den Ereignismonitor, wenn Sie fertig sind.

### Aufgabe - Steuern Ihres IoT-Geräts

Sie können auch die Azure CLI verwenden, um direkte Methoden auf Ihrem IoT-Gerät aufzurufen.

1. Führen Sie den folgenden Befehl in Ihrer Eingabeaufforderung oder Ihrem Terminal aus, um die Methode `relay_on` auf dem IoT-Gerät aufzurufen:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Ersetzen Sie `
<hub_name>
` mit dem Namen, den Sie für Ihren IoT Hub verwendet haben.

    Dies sendet eine direkte Methodenanforderung für die Methode, die durch `method-name` angegeben ist. Direkte Methoden können eine Nutzlast enthalten, die Daten für die Methode enthält, und diese kann im Parameter `method-payload` als JSON angegeben werden.

    Sie werden sehen, wie das Relais eingeschaltet wird, und die entsprechende Ausgabe von Ihrem IoT-Gerät:

    ```output
    Direct method received -  relay_on
    ```

1. Wiederholen Sie den obigen Schritt, aber setzen Sie `--method-name` auf `relay_off`. Sie werden sehen, wie das Relais ausgeschaltet wird, und die entsprechende Ausgabe vom IoT-Gerät.

---

## 🚀 Herausforderung

Die kostenlose Stufe des IoT Hub erlaubt 8.000 Nachrichten pro Tag. Der von Ihnen geschriebene Code sendet alle 10 Sekunden Telemetrie-Nachrichten. Wie viele Nachrichten pro Tag ergeben sich bei einer Nachricht alle 10 Sekunden?

Überlegen Sie, wie oft Bodenfeuchtigkeitsmessungen gesendet werden sollten. Wie können Sie Ihren Code ändern, um innerhalb der kostenlosen Stufe zu bleiben und so oft wie nötig, aber nicht zu oft zu prüfen? Was wäre, wenn Sie ein zweites Gerät hinzufügen wollten?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Rückblick & Selbststudium

Das IoT Hub SDK ist sowohl für Arduino als auch für Python Open Source. In den Code-Repositories auf GitHub gibt es eine Reihe von Beispielen, die zeigen, wie man mit verschiedenen IoT Hub-Funktionen arbeitet.

* Wenn Sie ein Wio Terminal verwenden, schauen Sie sich die [Arduino-Beispiele auf GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples) an.
* Wenn Sie ein Raspberry Pi oder ein virtuelles Gerät verwenden, schauen Sie sich die [Python-Beispiele auf GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples) an.

## Aufgabe

[Erfahren Sie mehr über Cloud-Dienste](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.