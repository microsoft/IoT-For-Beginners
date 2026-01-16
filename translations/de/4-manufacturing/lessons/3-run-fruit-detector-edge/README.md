<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-25T21:05:13+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "de"
}
-->
# Führen Sie Ihren Fruchtdetektor am Edge aus

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Dieses Video gibt einen Überblick darüber, wie Bildklassifikatoren auf IoT-Geräten ausgeführt werden, das Thema dieser Lektion.

[![Custom Vision AI auf Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Einführung

In der letzten Lektion haben Sie Ihren Bildklassifikator verwendet, um reife und unreife Früchte zu klassifizieren, indem Sie ein Bild, das von der Kamera Ihres IoT-Geräts aufgenommen wurde, über das Internet an einen Cloud-Dienst gesendet haben. Diese Anfragen benötigen Zeit, kosten Geld und können je nach Art der verwendeten Bilddaten Datenschutzprobleme mit sich bringen.

In dieser Lektion lernen Sie, wie Sie Machine-Learning-Modelle (ML) am Edge ausführen – auf IoT-Geräten, die in Ihrem eigenen Netzwerk und nicht in der Cloud laufen. Sie erfahren die Vorteile und Nachteile des Edge-Computings im Vergleich zum Cloud-Computing, wie Sie Ihr KI-Modell am Edge bereitstellen und wie Sie darauf von Ihrem IoT-Gerät aus zugreifen können.

In dieser Lektion behandeln wir:

* [Edge-Computing](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registrieren eines IoT-Edge-Geräts](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Einrichten eines IoT-Edge-Geräts](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Exportieren Ihres Modells](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Vorbereiten Ihres Containers für die Bereitstellung](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Bereitstellen Ihres Containers](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Verwenden Ihres IoT-Edge-Geräts](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Edge-Computing

Edge-Computing bedeutet, dass Computer IoT-Daten so nah wie möglich an der Stelle verarbeiten, an der die Daten generiert werden. Anstatt diese Verarbeitung in der Cloud durchzuführen, wird sie an den Rand der Cloud – Ihr internes Netzwerk – verlagert.

![Ein Architekturdiagramm, das Internetdienste in der Cloud und IoT-Geräte in einem lokalen Netzwerk zeigt](../../../../../translated_images/de/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

In den bisherigen Lektionen haben Sie Geräte verwendet, die Daten sammeln und diese zur Analyse an die Cloud senden, wobei serverlose Funktionen oder KI-Modelle in der Cloud ausgeführt werden.

![Ein Architekturdiagramm, das IoT-Geräte in einem lokalen Netzwerk zeigt, die mit Edge-Geräten verbunden sind, und diese Edge-Geräte sind mit der Cloud verbunden](../../../../../translated_images/de/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Edge-Computing verlagert einige der Cloud-Dienste aus der Cloud auf Computer, die im selben Netzwerk wie die IoT-Geräte laufen, und kommuniziert nur bei Bedarf mit der Cloud. Beispielsweise können Sie KI-Modelle auf Edge-Geräten ausführen, um die Reife von Früchten zu analysieren, und nur Analysen wie die Anzahl reifer gegenüber unreifer Früchte an die Cloud senden.

✅ Denken Sie über die IoT-Anwendungen nach, die Sie bisher erstellt haben. Welche Teile davon könnten an den Edge verlagert werden?

### Vorteile

Die Vorteile des Edge-Computings sind:

1. **Geschwindigkeit** – Edge-Computing ist ideal für zeitkritische Daten, da Aktionen im selben Netzwerk wie das Gerät ausgeführt werden, anstatt Anfragen über das Internet zu stellen. Dies ermöglicht höhere Geschwindigkeiten, da interne Netzwerke wesentlich schneller als Internetverbindungen laufen können und die Daten eine viel kürzere Strecke zurücklegen.

    > 💁 Obwohl optische Kabel für Internetverbindungen verwendet werden und Daten mit Lichtgeschwindigkeit übertragen können, kann es Zeit kosten, Daten rund um die Welt zu Cloud-Anbietern zu senden. Beispielsweise dauert es mindestens 28 ms, um Daten von Europa zu Cloud-Diensten in den USA über ein transatlantisches Kabel zu senden, und das berücksichtigt nicht die Zeit, die benötigt wird, um die Daten zum Kabel zu bringen, elektrische Signale in Licht umzuwandeln und umgekehrt, sowie die Übertragung vom Kabel zum Cloud-Anbieter.

    Edge-Computing erfordert auch weniger Netzwerkverkehr, wodurch das Risiko verringert wird, dass Ihre Daten aufgrund von Überlastung der begrenzten Bandbreite einer Internetverbindung langsamer werden.

1. **Fernzugriff** – Edge-Computing funktioniert, wenn Sie nur begrenzte oder keine Konnektivität haben oder wenn die Konnektivität zu teuer ist, um sie kontinuierlich zu nutzen. Beispielsweise in humanitären Katastrophengebieten, in denen die Infrastruktur begrenzt ist, oder in Entwicklungsländern.

1. **Geringere Kosten** – Das Sammeln, Speichern, Analysieren und Auslösen von Aktionen auf Edge-Geräten reduziert die Nutzung von Cloud-Diensten, was die Gesamtkosten Ihrer IoT-Anwendung senken kann. Es gibt einen aktuellen Anstieg von Geräten, die für Edge-Computing entwickelt wurden, wie z. B. KI-Beschleunigerkarten wie die [Jetson Nano von NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), die KI-Workloads mit GPU-basierter Hardware auf Geräten ausführen können, die weniger als 100 US-Dollar kosten.

1. **Datenschutz und Sicherheit** – Mit Edge-Computing bleiben Daten in Ihrem Netzwerk und werden nicht in die Cloud hochgeladen. Dies wird oft für sensible und persönlich identifizierbare Informationen bevorzugt, insbesondere weil Daten nach der Analyse nicht gespeichert werden müssen, was das Risiko von Datenlecks erheblich reduziert. Beispiele sind medizinische Daten und Sicherheitskameraaufnahmen.

1. **Umgang mit unsicheren Geräten** – Wenn Sie Geräte mit bekannten Sicherheitslücken haben, die Sie nicht direkt mit Ihrem Netzwerk oder dem Internet verbinden möchten, können Sie diese mit einem separaten Netzwerk zu einem Gateway-IoT-Edge-Gerät verbinden. Dieses Edge-Gerät kann dann auch eine Verbindung zu Ihrem größeren Netzwerk oder dem Internet haben und die Datenflüsse hin und her verwalten.

1. **Unterstützung für inkompatible Geräte** – Wenn Sie Geräte haben, die keine Verbindung zu IoT Hub herstellen können, beispielsweise Geräte, die nur HTTP-Verbindungen unterstützen oder Geräte, die nur Bluetooth haben, können Sie ein IoT-Edge-Gerät als Gateway-Gerät verwenden, das Nachrichten an IoT Hub weiterleitet.

✅ Recherchieren Sie: Welche weiteren Vorteile könnte Edge-Computing haben?

### Nachteile

Es gibt Nachteile beim Edge-Computing, bei denen die Cloud möglicherweise die bevorzugte Option ist:

1. **Skalierbarkeit und Flexibilität** – Cloud-Computing kann Netzwerk- und Datenanforderungen in Echtzeit anpassen, indem Server und andere Ressourcen hinzugefügt oder reduziert werden. Um mehr Edge-Computer hinzuzufügen, ist das manuelle Hinzufügen weiterer Geräte erforderlich.

1. **Zuverlässigkeit und Widerstandsfähigkeit** – Cloud-Computing bietet mehrere Server, oft an mehreren Standorten, für Redundanz und Katastrophenwiederherstellung. Um das gleiche Maß an Redundanz am Edge zu erreichen, sind große Investitionen und viel Konfigurationsarbeit erforderlich.

1. **Wartung** – Cloud-Dienstanbieter bieten Systemwartung und Updates.

✅ Recherchieren Sie: Welche weiteren Nachteile könnte Edge-Computing haben?

Die Nachteile sind im Grunde das Gegenteil der Vorteile der Nutzung der Cloud – Sie müssen diese Geräte selbst erstellen und verwalten, anstatt sich auf die Expertise und Skalierung der Cloud-Anbieter zu verlassen.

Einige der Risiken werden durch die Natur des Edge-Computings selbst gemildert. Wenn Sie beispielsweise ein Edge-Gerät in einer Fabrik betreiben, das Daten von Maschinen sammelt, müssen Sie nicht über einige Szenarien zur Katastrophenwiederherstellung nachdenken. Wenn der Strom in der Fabrik ausfällt, benötigen Sie kein Backup-Edge-Gerät, da die Maschinen, die die Daten generieren, die das Edge-Gerät verarbeitet, ebenfalls keinen Strom haben werden.

Für IoT-Systeme möchten Sie oft eine Mischung aus Cloud- und Edge-Computing, wobei Sie jeden Dienst basierend auf den Anforderungen des Systems, seiner Kunden und seiner Wartung nutzen.

## Azure IoT Edge

![Das Azure IoT Edge-Logo](../../../../../translated_images/de/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge ist ein Dienst, der Ihnen helfen kann, Workloads aus der Cloud an den Edge zu verlagern. Sie richten ein Gerät als Edge-Gerät ein und können von der Cloud aus Code auf dieses Edge-Gerät bereitstellen. Dies ermöglicht Ihnen, die Fähigkeiten der Cloud und des Edge zu kombinieren.

> 🎓 *Workloads* ist ein Begriff für jeden Dienst, der irgendeine Art von Arbeit ausführt, wie KI-Modelle, Anwendungen oder serverlose Funktionen.

Beispielsweise können Sie einen Bildklassifikator in der Cloud trainieren und ihn dann von der Cloud aus auf ein Edge-Gerät bereitstellen. Ihr IoT-Gerät sendet dann Bilder an das Edge-Gerät zur Klassifikation, anstatt die Bilder über das Internet zu senden. Wenn Sie eine neue Iteration des Modells bereitstellen müssen, können Sie es in der Cloud trainieren und IoT Edge verwenden, um das Modell auf dem Edge-Gerät auf Ihre neue Iteration zu aktualisieren.

> 🎓 Software, die auf IoT Edge bereitgestellt wird, wird als *Module* bezeichnet. Standardmäßig führt IoT Edge Module aus, die mit IoT Hub kommunizieren, wie die Module `edgeAgent` und `edgeHub`. Wenn Sie einen Bildklassifikator bereitstellen, wird dieser als zusätzliches Modul bereitgestellt.

IoT Edge ist in IoT Hub integriert, sodass Sie Edge-Geräte mit demselben Dienst verwalten können, den Sie zur Verwaltung von IoT-Geräten verwenden würden, mit dem gleichen Sicherheitsniveau.

IoT Edge führt Code aus *Containern* aus – eigenständige Anwendungen, die isoliert vom Rest der Anwendungen auf Ihrem Computer ausgeführt werden. Wenn Sie einen Container ausführen, verhält er sich wie ein separater Computer, der in Ihrem Computer läuft, mit eigener Software, eigenen Diensten und Anwendungen. Meistens können Container auf nichts auf Ihrem Computer zugreifen, es sei denn, Sie entscheiden sich, Dinge wie einen Ordner mit dem Container zu teilen. Der Container stellt dann Dienste über einen offenen Port bereit, auf den Sie zugreifen oder den Sie Ihrem Netzwerk aussetzen können.

![Eine Webanfrage, die an einen Container weitergeleitet wird](../../../../../translated_images/de/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Beispielsweise können Sie einen Container mit einer Website haben, die auf Port 80 läuft, dem Standard-HTTP-Port, und Sie können ihn dann auch auf Port 80 von Ihrem Computer aus zugänglich machen.

✅ Recherchieren Sie: Lesen Sie über Container und Dienste wie Docker oder Moby.

Sie können Custom Vision verwenden, um Bildklassifikatoren herunterzuladen und sie als Container bereitzustellen, entweder direkt auf einem Gerät oder über IoT Edge. Sobald sie in einem Container laufen, können sie über dieselbe REST-API wie die Cloud-Version aufgerufen werden, jedoch mit dem Endpunkt, der auf das Edge-Gerät zeigt, das den Container ausführt.

## Registrieren eines IoT-Edge-Geräts

Um ein IoT-Edge-Gerät zu verwenden, muss es in IoT Hub registriert werden.

### Aufgabe – Registrieren eines IoT-Edge-Geräts

1. Erstellen Sie einen IoT Hub in der Ressourcengruppe `fruit-quality-detector`. Geben Sie ihm einen eindeutigen Namen, der auf `fruit-quality-detector` basiert.

1. Registrieren Sie ein IoT-Edge-Gerät namens `fruit-quality-detector-edge` in Ihrem IoT Hub. Der Befehl dazu ist ähnlich wie der zur Registrierung eines Nicht-Edge-Geräts, außer dass Sie das Flag `--edge-enabled` übergeben.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen Ihres IoT Hub.

1. Holen Sie sich die Verbindungszeichenfolge für Ihr Gerät mit dem folgenden Befehl:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen Ihres IoT Hub.

    Kopieren Sie die Verbindungszeichenfolge, die in der Ausgabe angezeigt wird.

## Einrichten eines IoT-Edge-Geräts

Sobald Sie die Registrierung des Edge-Geräts in Ihrem IoT Hub erstellt haben, können Sie das Edge-Gerät einrichten.

### Aufgabe – Installieren und Starten der IoT-Edge-Laufzeit

**Die IoT-Edge-Laufzeit führt nur Linux-Container aus.** Sie kann unter Linux oder unter Windows mit Linux-VMs ausgeführt werden.

* Wenn Sie einen Raspberry Pi als Ihr IoT-Gerät verwenden, läuft dieser mit einer unterstützten Version von Linux und kann die IoT-Edge-Laufzeit hosten. Folgen Sie der [Installationsanleitung für Azure IoT Edge für Linux in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn), um IoT Edge zu installieren und die Verbindungszeichenfolge einzurichten.

    > 💁 Denken Sie daran, dass Raspberry Pi OS eine Variante von Debian Linux ist.

* Wenn Sie keinen Raspberry Pi verwenden, aber einen Linux-Computer haben, können Sie die IoT-Edge-Laufzeit ausführen. Folgen Sie der [Installationsanleitung für Azure IoT Edge für Linux in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn), um IoT Edge zu installieren und die Verbindungszeichenfolge einzurichten.

* Wenn Sie Windows verwenden, können Sie die IoT-Edge-Laufzeit in einer Linux-VM installieren, indem Sie der [Installations- und Startanleitung für die IoT-Edge-Laufzeit im Abschnitt „Ihr erstes IoT-Edge-Modul auf einem Windows-Gerät bereitstellen“ in der Microsoft-Dokumentation](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime) folgen. Sie können aufhören, wenn Sie den Abschnitt *Ein Modul bereitstellen* erreichen.

* Wenn Sie macOS verwenden, können Sie eine virtuelle Maschine (VM) in der Cloud erstellen, die Sie für Ihr IoT-Edge-Gerät verwenden können. Dies sind Computer, die Sie in der Cloud erstellen und über das Internet darauf zugreifen können. Sie können eine Linux-VM erstellen, die IoT Edge installiert hat. Folgen Sie der [Anleitung zum Erstellen einer virtuellen Maschine mit IoT Edge](vm-iotedge.md) für Anweisungen dazu.

## Exportieren Ihres Modells

Um den Klassifikator am Edge auszuführen, muss er aus Custom Vision exportiert werden. Custom Vision kann zwei Arten von Modellen generieren – Standardmodelle und kompakte Modelle. Kompakte Modelle verwenden verschiedene Techniken, um die Größe des Modells zu reduzieren, sodass es klein genug ist, um heruntergeladen und auf IoT-Geräten bereitgestellt zu werden.

Als Sie den Bildklassifikator erstellt haben, haben Sie die *Food*-Domäne verwendet, eine Version des Modells, die für das Training mit Bildern von Lebensmitteln optimiert ist. In Custom Vision ändern Sie die Domäne Ihres Projekts und verwenden Ihre Trainingsdaten, um ein neues Modell mit der neuen Domäne zu trainieren. Alle von Custom Vision unterstützten Domänen sind als Standard- und kompakte Versionen verfügbar.

### Aufgabe – Trainieren Ihres Modells mit der Food (kompakt)-Domäne
1. Öffnen Sie das Custom Vision-Portal unter [CustomVision.ai](https://customvision.ai) und melden Sie sich an, falls Sie es nicht bereits geöffnet haben. Öffnen Sie anschließend Ihr Projekt `fruit-quality-detector`.

1. Wählen Sie die Schaltfläche **Einstellungen** (das ⚙-Symbol).

1. Wählen Sie in der Liste *Domains* die Option *Food (compact)*.

1. Stellen Sie unter *Exportfähigkeiten* sicher, dass *Basic platforms (Tensorflow, CoreML, ONNX, ...)* ausgewählt ist.

1. Wählen Sie unten auf der Einstellungsseite **Änderungen speichern**.

1. Trainieren Sie das Modell erneut mit der Schaltfläche **Train**, indem Sie *Quick training* auswählen.

### Aufgabe - Exportieren Sie Ihr Modell

Sobald das Modell trainiert wurde, muss es als Container exportiert werden.

1. Wählen Sie die Registerkarte **Performance** und suchen Sie die neueste Iteration, die mit der kompakten Domain trainiert wurde.

1. Wählen Sie oben die Schaltfläche **Exportieren**.

1. Wählen Sie **DockerFile** und dann eine Version, die zu Ihrem Edge-Gerät passt:

    * Wenn Sie IoT Edge auf einem Linux-Computer, einem Windows-Computer oder einer virtuellen Maschine ausführen, wählen Sie die *Linux*-Version.
    * Wenn Sie IoT Edge auf einem Raspberry Pi ausführen, wählen Sie die Version *ARM (Raspberry Pi 3)*.

> 🎓 Docker ist eines der beliebtesten Tools zur Verwaltung von Containern, und ein DockerFile ist eine Reihe von Anweisungen, wie der Container eingerichtet werden soll.

1. Wählen Sie **Exportieren**, um Custom Vision die relevanten Dateien erstellen zu lassen, und anschließend **Herunterladen**, um sie als ZIP-Datei herunterzuladen.

1. Speichern Sie die Dateien auf Ihrem Computer und entpacken Sie den Ordner.

## Bereiten Sie Ihren Container für die Bereitstellung vor

![Container werden erstellt, dann in ein Container-Registry hochgeladen und von dort aus auf ein Edge-Gerät bereitgestellt](../../../../../translated_images/de/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Nachdem Sie Ihr Modell heruntergeladen haben, muss es in einen Container eingebaut und dann in ein Container-Registry hochgeladen werden – einen Online-Speicherort, an dem Sie Container speichern können. IoT Edge kann den Container dann aus dem Registry herunterladen und auf Ihr Gerät übertragen.

![Das Logo des Azure Container Registry](../../../../../translated_images/de/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Das Container-Registry, das Sie für diese Lektion verwenden, ist Azure Container Registry. Dies ist kein kostenloser Dienst, daher sollten Sie zur Kosteneinsparung sicherstellen, dass Sie [Ihr Projekt bereinigen](../../../clean-up.md), sobald Sie fertig sind.

> 💁 Die Kosten für die Nutzung eines Azure Container Registry können Sie auf der [Azure Container Registry-Preisseite](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn) einsehen.

### Aufgabe - Docker installieren

Um den Klassifikator zu erstellen und bereitzustellen, müssen Sie möglicherweise [Docker](https://www.docker.com/) installieren.

Dies ist nur erforderlich, wenn Sie Ihren Container auf einem anderen Gerät erstellen möchten als dem, auf dem Sie IoT Edge installiert haben – Docker wird als Teil der IoT Edge-Installation automatisch installiert.

1. Wenn Sie den Docker-Container auf einem anderen Gerät als Ihrem IoT Edge-Gerät erstellen, folgen Sie den Installationsanweisungen auf der [Docker-Installationsseite](https://www.docker.com/products/docker-desktop), um Docker Desktop oder die Docker-Engine zu installieren. Stellen Sie sicher, dass Docker nach der Installation läuft.

### Aufgabe - Erstellen Sie eine Container-Registry-Ressource

1. Führen Sie den folgenden Befehl in Ihrem Terminal oder Ihrer Eingabeaufforderung aus, um eine Azure Container Registry-Ressource zu erstellen:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Ersetzen Sie `<Container registry name>` durch einen eindeutigen Namen für Ihre Container-Registry, der nur Buchstaben und Zahlen enthält. Basieren Sie diesen Namen auf `fruitqualitydetector`. Dieser Name wird Teil der URL, um auf die Container-Registry zuzugreifen, und muss global eindeutig sein.

1. Melden Sie sich mit dem folgenden Befehl bei der Azure Container Registry an:

    ```sh
    az acr login --name <Container registry name>
    ```

    Ersetzen Sie `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben.

1. Aktivieren Sie den Admin-Modus für die Container-Registry, um ein Passwort zu generieren, mit dem folgenden Befehl:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Ersetzen Sie `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben.

1. Generieren Sie Passwörter für Ihre Container-Registry mit dem folgenden Befehl:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Ersetzen Sie `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben.

    Kopieren Sie den Wert von `PASSWORD`, da Sie ihn später benötigen.

### Aufgabe - Erstellen Sie Ihren Container

Was Sie von Custom Vision heruntergeladen haben, war ein DockerFile mit Anweisungen, wie der Container erstellt werden soll, sowie Anwendungs-Code, der innerhalb des Containers ausgeführt wird, um Ihr Custom Vision-Modell zu hosten, zusammen mit einer REST-API, die aufgerufen werden kann. Sie können Docker verwenden, um einen markierten Container aus dem DockerFile zu erstellen und ihn dann in Ihre Container-Registry hochzuladen.

> 🎓 Container erhalten ein Tag, das einen Namen und eine Version definiert. Wenn Sie einen Container aktualisieren müssen, können Sie ihn mit demselben Tag, aber einer neueren Version erstellen.

1. Öffnen Sie Ihr Terminal oder Ihre Eingabeaufforderung und navigieren Sie zu dem entpackten Modell, das Sie von Custom Vision heruntergeladen haben.

1. Führen Sie den folgenden Befehl aus, um das Image zu erstellen und zu markieren:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Ersetzen Sie `<platform>` durch die Plattform, auf der dieser Container ausgeführt wird. Wenn Sie IoT Edge auf einem Raspberry Pi ausführen, setzen Sie dies auf `linux/armhf`, andernfalls setzen Sie es auf `linux/amd64`.

    > 💁 Wenn Sie diesen Befehl von dem Gerät aus ausführen, auf dem Sie IoT Edge ausführen, wie z. B. von Ihrem Raspberry Pi, können Sie den Teil `--platform <platform>` weglassen, da er standardmäßig auf die aktuelle Plattform gesetzt ist.

    Ersetzen Sie `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben.

    > 💁 Wenn Sie Linux oder Raspberry Pi OS verwenden, müssen Sie möglicherweise `sudo` verwenden, um diesen Befehl auszuführen.

    Docker wird das Image erstellen und alle benötigte Software konfigurieren. Das Image wird dann als `classifier:v1` markiert.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Aufgabe - Laden Sie Ihren Container in Ihre Container-Registry hoch

1. Verwenden Sie den folgenden Befehl, um Ihren Container in Ihre Container-Registry hochzuladen:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Ersetzen Sie `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben.

    > 💁 Wenn Sie Linux verwenden, müssen Sie möglicherweise `sudo` verwenden, um diesen Befehl auszuführen.

    Der Container wird in die Container-Registry hochgeladen.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Um den Upload zu überprüfen, können Sie die Container in Ihrer Registry mit dem folgenden Befehl auflisten:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Ersetzen Sie `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Sie werden Ihren Klassifikator in der Ausgabe sehen.

## Bereitstellen Ihres Containers

Ihr Container kann jetzt auf Ihrem IoT Edge-Gerät bereitgestellt werden. Um die Bereitstellung durchzuführen, müssen Sie ein Bereitstellungsmanifest erstellen – ein JSON-Dokument, das die Module auflistet, die auf dem Edge-Gerät bereitgestellt werden sollen.

### Aufgabe - Erstellen Sie das Bereitstellungsmanifest

1. Erstellen Sie eine neue Datei namens `deployment.json` irgendwo auf Ihrem Computer.

1. Fügen Sie Folgendes in diese Datei ein:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Sie finden diese Datei im Ordner [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Ersetzen Sie die drei Instanzen von `<Container registry name>` durch den Namen, den Sie für Ihre Container-Registry verwendet haben. Eine befindet sich im Abschnitt `ImageClassifier`-Modul, die anderen beiden im Abschnitt `registryCredentials`.

    Ersetzen Sie `<Container registry password>` im Abschnitt `registryCredentials` durch Ihr Container-Registry-Passwort.

1. Führen Sie den folgenden Befehl aus dem Ordner aus, der Ihr Bereitstellungsmanifest enthält:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen Ihres IoT Hub.

    Das Image-Klassifikator-Modul wird auf Ihrem Edge-Gerät bereitgestellt.

### Aufgabe - Überprüfen Sie, ob der Klassifikator läuft

1. Verbinden Sie sich mit dem IoT Edge-Gerät:

    * Wenn Sie einen Raspberry Pi verwenden, um IoT Edge auszuführen, verbinden Sie sich über SSH entweder von Ihrem Terminal aus oder über eine Remote-SSH-Sitzung in VS Code.
    * Wenn Sie IoT Edge in einem Linux-Container unter Windows ausführen, folgen Sie den Schritten im [Leitfaden zur erfolgreichen Konfiguration](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration), um sich mit dem IoT Edge-Gerät zu verbinden.
    * Wenn Sie IoT Edge auf einer virtuellen Maschine ausführen, können Sie sich mit dem `adminUsername` und `password`, die Sie beim Erstellen der VM festgelegt haben, sowie der IP-Adresse oder dem DNS-Namen per SSH in die Maschine einloggen:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Oder:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Geben Sie Ihr Passwort ein, wenn Sie dazu aufgefordert werden.

1. Sobald Sie verbunden sind, führen Sie den folgenden Befehl aus, um die Liste der IoT Edge-Module abzurufen:

    ```sh
    iotedge list
    ```

    > 💁 Möglicherweise müssen Sie diesen Befehl mit `sudo` ausführen.

    Sie werden die laufenden Module sehen:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Überprüfen Sie die Logs für das Image-Klassifikator-Modul mit dem folgenden Befehl:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Möglicherweise müssen Sie diesen Befehl mit `sudo` ausführen.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Aufgabe - Testen Sie den Image-Klassifikator

1. Sie können CURL verwenden, um den Image-Klassifikator mit der IP-Adresse oder dem Hostnamen des Computers zu testen, auf dem der IoT Edge-Agent läuft. Finden Sie die IP-Adresse:

    * Wenn Sie sich auf demselben Gerät befinden, auf dem IoT Edge läuft, können Sie `localhost` als Hostnamen verwenden.
    * Wenn Sie eine VM verwenden, können Sie entweder die IP-Adresse oder den DNS-Namen der VM verwenden.
    * Andernfalls können Sie die IP-Adresse des Geräts abrufen, auf dem IoT Edge läuft:
      * Unter Windows 10 folgen Sie dem [Leitfaden zum Finden Ihrer IP-Adresse](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Unter macOS folgen Sie dem [Leitfaden zum Finden Ihrer IP-Adresse auf einem Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Unter Linux folgen Sie dem Abschnitt zum Finden Ihrer privaten IP-Adresse im [Leitfaden zum Finden Ihrer IP-Adresse in Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Sie können den Container mit einer lokalen Datei testen, indem Sie den folgenden CURL-Befehl ausführen:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Ersetzen Sie `<IP address or name>` durch die IP-Adresse oder den Hostnamen des Computers, auf dem IoT Edge läuft. Ersetzen Sie `<file_Name>` durch den Namen der Datei, die getestet werden soll.

    Sie werden die Vorhersageergebnisse in der Ausgabe sehen:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Es ist hier nicht erforderlich, einen Vorhersageschlüssel bereitzustellen, da dies keine Azure-Ressource verwendet. Stattdessen würde die Sicherheit im internen Netzwerk basierend auf den internen Sicherheitsanforderungen konfiguriert, anstatt sich auf einen öffentlichen Endpunkt und einen API-Schlüssel zu verlassen.

## Verwenden Sie Ihr IoT Edge-Gerät

Nachdem Ihr Image-Klassifikator auf einem IoT Edge-Gerät bereitgestellt wurde, können Sie ihn von Ihrem IoT-Gerät aus verwenden.

### Aufgabe - Verwenden Sie Ihr IoT Edge-Gerät

Arbeiten Sie den entsprechenden Leitfaden durch, um Bilder mit dem IoT Edge-Klassifikator zu klassifizieren:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Einplatinencomputer - Raspberry Pi/virtuelles IoT-Gerät](single-board-computer.md)

### Modell-Neutraining

Ein Nachteil beim Ausführen von Bildklassifikatoren auf IoT Edge ist, dass sie nicht mit Ihrem Custom Vision-Projekt verbunden sind. Wenn Sie die Registerkarte **Predictions** in Custom Vision öffnen, werden Sie die Bilder, die mit dem Edge-basierten Klassifikator klassifiziert wurden, nicht sehen.

Dies ist das erwartete Verhalten – Bilder werden nicht zur Klassifikation in die Cloud gesendet, daher sind sie in der Cloud nicht verfügbar. Ein Vorteil der Verwendung von IoT Edge ist die Privatsphäre, da sichergestellt wird, dass Bilder Ihr Netzwerk nicht verlassen. Ein weiterer Vorteil ist die Möglichkeit, offline zu arbeiten, sodass keine Abhängigkeit vom Hochladen von Bildern besteht, wenn das Gerät keine Internetverbindung hat. Der Nachteil ist die Verbesserung Ihres Modells – Sie müssten eine andere Möglichkeit implementieren, Bilder zu speichern, die manuell neu klassifiziert werden können, um den Bildklassifikator zu verbessern und neu zu trainieren.

✅ Überlegen Sie sich Möglichkeiten, Bilder hochzuladen, um den Klassifikator neu zu trainieren.

---

## 🚀 Herausforderung

Das Ausführen von KI-Modellen auf Edge-Geräten kann schneller sein als in der Cloud – der Netzwerk-Hop ist kürzer. Es kann jedoch auch langsamer sein, da die Hardware, die das Modell ausführt, möglicherweise nicht so leistungsstark ist wie die Cloud.

Führen Sie Zeitmessungen durch und vergleichen Sie, ob der Aufruf Ihres Edge-Geräts schneller oder langsamer ist als der Aufruf der Cloud? Überlegen Sie sich Gründe, um den Unterschied oder das Fehlen eines Unterschieds zu erklären. Recherchieren Sie Möglichkeiten, KI-Modelle schneller auf Edge-Geräten auszuführen, indem Sie spezialisierte Hardware verwenden.

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Überprüfung & Selbststudium

* Lesen Sie mehr über Container auf der [Seite zur OS-Level-Virtualisierung auf Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization)
* Lesen Sie mehr über Edge Computing, mit einem Schwerpunkt darauf, wie 5G dazu beitragen kann, Edge Computing zu erweitern, im [Artikel "Was ist Edge Computing und warum ist es wichtig?" auf NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html).
* Erfahren Sie mehr über das Ausführen von KI-Diensten in IoT Edge, indem Sie die [Episode "Erfahren Sie, wie Sie Azure IoT Edge auf einem vorgefertigten KI-Dienst am Edge für die Spracherkennung verwenden" von Learn Live auf Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn) ansehen.

## Aufgabe

[Andere Dienste am Edge ausführen](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.