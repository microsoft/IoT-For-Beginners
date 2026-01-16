<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-25T23:04:01+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "de"
}
-->
# Standortdaten visualisieren

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/de/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Dieses Video gibt einen Überblick über Azure Maps mit IoT, einen Dienst, der in dieser Lektion behandelt wird.

[![Azure Maps - Die Microsoft Azure Enterprise Location Platform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klicken Sie auf das Bild oben, um das Video anzusehen

## Quiz vor der Vorlesung

[Quiz vor der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Einführung

In der letzten Lektion haben Sie gelernt, wie Sie GPS-Daten von Ihren Sensoren abrufen und mit serverlosem Code in einem Speichercontainer in der Cloud speichern können. Jetzt erfahren Sie, wie Sie diese Punkte auf einer Azure-Karte visualisieren können. Sie lernen, wie Sie eine Karte auf einer Webseite erstellen, das GeoJSON-Datenformat verstehen und es verwenden, um alle erfassten GPS-Punkte auf Ihrer Karte darzustellen.

In dieser Lektion behandeln wir:

* [Was ist Datenvisualisierung](../../../../../3-transport/lessons/3-visualize-location-data)
* [Kartendienste](../../../../../3-transport/lessons/3-visualize-location-data)
* [Erstellen einer Azure Maps-Ressource](../../../../../3-transport/lessons/3-visualize-location-data)
* [Eine Karte auf einer Webseite anzeigen](../../../../../3-transport/lessons/3-visualize-location-data)
* [Das GeoJSON-Format](../../../../../3-transport/lessons/3-visualize-location-data)
* [GPS-Daten mit GeoJSON auf einer Karte darstellen](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Diese Lektion beinhaltet eine kleine Menge HTML und JavaScript. Wenn Sie mehr über Webentwicklung mit HTML und JavaScript erfahren möchten, schauen Sie sich [Webentwicklung für Anfänger](https://github.com/microsoft/Web-Dev-For-Beginners) an.

## Was ist Datenvisualisierung

Datenvisualisierung bedeutet, Daten so darzustellen, dass sie für Menschen leichter verständlich sind. Sie wird oft mit Diagrammen und Grafiken in Verbindung gebracht, umfasst jedoch jede Form der bildlichen Darstellung von Daten, die Menschen hilft, die Daten besser zu verstehen und Entscheidungen zu treffen.

Ein einfaches Beispiel: Im Farmprojekt haben Sie Bodenfeuchtigkeitswerte erfasst. Eine Tabelle mit Bodenfeuchtigkeitsdaten, die jede Stunde am 1. Juni 2021 erfasst wurden, könnte wie folgt aussehen:

| Datum            | Messwert |
| ---------------- | -------: |
| 01.06.2021 00:00 |     257  |
| 01.06.2021 01:00 |     268  |
| 01.06.2021 02:00 |     295  |
| 01.06.2021 03:00 |     305  |
| 01.06.2021 04:00 |     325  |
| 01.06.2021 05:00 |     359  |
| 01.06.2021 06:00 |     398  |
| 01.06.2021 07:00 |     410  |
| 01.06.2021 08:00 |     429  |
| 01.06.2021 09:00 |     451  |
| 01.06.2021 10:00 |     460  |
| 01.06.2021 11:00 |     452  |
| 01.06.2021 12:00 |     420  |
| 01.06.2021 13:00 |     408  |
| 01.06.2021 14:00 |     431  |
| 01.06.2021 15:00 |     462  |
| 01.06.2021 16:00 |     432  |
| 01.06.2021 17:00 |     402  |
| 01.06.2021 18:00 |     387  |
| 01.06.2021 19:00 |     360  |
| 01.06.2021 20:00 |     358  |
| 01.06.2021 21:00 |     354  |
| 01.06.2021 22:00 |     356  |
| 01.06.2021 23:00 |     362  |

Für einen Menschen ist es schwierig, diese Daten zu verstehen. Es ist eine Wand aus Zahlen ohne Bedeutung. Als erster Schritt zur Visualisierung dieser Daten können sie in einem Liniendiagramm dargestellt werden:

![Ein Liniendiagramm der obigen Daten](../../../../../translated_images/de/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Dies kann weiter verbessert werden, indem eine Linie hinzugefügt wird, die anzeigt, wann das automatische Bewässerungssystem bei einem Bodenfeuchtigkeitswert von 450 eingeschaltet wurde:

![Ein Liniendiagramm der Bodenfeuchtigkeit mit einer Linie bei 450](../../../../../translated_images/de/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Dieses Diagramm zeigt sehr schnell nicht nur die Bodenfeuchtigkeitswerte, sondern auch die Punkte, an denen das Bewässerungssystem eingeschaltet wurde.

Diagramme sind nicht das einzige Werkzeug zur Visualisierung von Daten. IoT-Geräte, die Wetterbedingungen erfassen, können Web- oder mobile Apps haben, die Wetterbedingungen mit Symbolen visualisieren, wie z. B. einem Wolkensymbol für bewölkte Tage, einer Regenwolke für Regentage usw. Es gibt eine Vielzahl von Möglichkeiten, Daten zu visualisieren, einige ernsthaft, andere unterhaltsam.

✅ Denken Sie an Möglichkeiten, wie Sie Daten visualisiert gesehen haben. Welche Methoden waren am klarsten und haben Ihnen am schnellsten Entscheidungen ermöglicht?

Die besten Visualisierungen ermöglichen es Menschen, schnell Entscheidungen zu treffen. Beispielsweise ist es schwierig, eine Wand voller Anzeigen mit allen möglichen Messwerten von Industriemaschinen zu verarbeiten, aber ein blinkendes rotes Licht, wenn etwas schiefgeht, ermöglicht es einem Menschen, eine Entscheidung zu treffen. Manchmal ist die beste Visualisierung ein blinkendes Licht!

Beim Arbeiten mit GPS-Daten kann die klarste Visualisierung darin bestehen, die Daten auf einer Karte darzustellen. Eine Karte, die beispielsweise Lieferwagen zeigt, kann Mitarbeitern in einer Verarbeitungsanlage helfen, zu sehen, wann die Lieferwagen ankommen. Wenn diese Karte nicht nur Bilder von Lieferwagen an ihren aktuellen Standorten zeigt, sondern auch Informationen über den Inhalt eines Lieferwagens gibt, können die Mitarbeiter der Anlage entsprechend planen – wenn sie einen Kühlwagen in der Nähe sehen, wissen sie, dass sie Platz in einem Kühlschrank vorbereiten müssen.

## Kartendienste

Die Arbeit mit Karten ist eine interessante Übung, und es gibt viele Optionen wie Bing Maps, Leaflet, Open Street Maps und Google Maps. In dieser Lektion lernen Sie [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) kennen und wie Sie damit Ihre GPS-Daten anzeigen können.

![Das Azure Maps-Logo](../../../../../translated_images/de/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps ist "eine Sammlung von Geodiensten und SDKs, die aktuelle Kartendaten verwenden, um geografischen Kontext für Web- und mobile Anwendungen bereitzustellen." Entwicklern werden Tools zur Verfügung gestellt, um schöne, interaktive Karten zu erstellen, die Dinge wie empfohlene Verkehrswege, Informationen zu Verkehrsvorfällen, Indoor-Navigation, Suchfunktionen, Höheninformationen, Wetterdienste und mehr bieten können.

✅ Experimentieren Sie mit einigen [Codebeispielen für Karten](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Sie können die Karten als leere Leinwand, Kacheln, Satellitenbilder, Satellitenbilder mit überlagerten Straßen, verschiedene Arten von Graustufen-Karten, Karten mit Schattierungen zur Darstellung von Höhen, Nachtansichtskarten und eine kontrastreiche Karte anzeigen. Sie können Echtzeit-Updates auf Ihren Karten erhalten, indem Sie sie mit [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn) integrieren. Sie können das Verhalten und Aussehen Ihrer Karten steuern, indem Sie verschiedene Steuerungen aktivieren, die es der Karte ermöglichen, auf Ereignisse wie Pinch, Drag und Click zu reagieren. Um das Aussehen Ihrer Karte zu steuern, können Sie Ebenen hinzufügen, die Blasen, Linien, Polygone, Heatmaps und mehr enthalten. Welche Art von Karte Sie implementieren, hängt von Ihrer Wahl des SDK ab.

Sie können auf Azure Maps-APIs zugreifen, indem Sie die [REST-API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), das [Web-SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) oder, wenn Sie eine mobile App erstellen, das [Android-SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android) nutzen.

In dieser Lektion verwenden Sie das Web-SDK, um eine Karte zu zeichnen und den GPS-Standortpfad Ihres Sensors anzuzeigen.

## Erstellen einer Azure Maps-Ressource

Ihr erster Schritt besteht darin, ein Azure Maps-Konto zu erstellen.

### Aufgabe - Erstellen einer Azure Maps-Ressource

1. Führen Sie den folgenden Befehl in Ihrem Terminal oder der Eingabeaufforderung aus, um eine Azure Maps-Ressource in Ihrer Ressourcengruppe `gps-sensor` zu erstellen:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Dadurch wird eine Azure Maps-Ressource namens `gps-sensor` erstellt. Die verwendete Stufe ist `S1`, eine kostenpflichtige Stufe, die eine Reihe von Funktionen umfasst, aber mit einer großzügigen Anzahl kostenloser Aufrufe.

    > 💁 Um die Kosten für die Nutzung von Azure Maps zu sehen, besuchen Sie die [Azure Maps-Preisseite](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Sie benötigen einen API-Schlüssel für die Kartenressource. Verwenden Sie den folgenden Befehl, um diesen Schlüssel zu erhalten:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Kopieren Sie den Wert von `PrimaryKey`.

## Eine Karte auf einer Webseite anzeigen

Nun können Sie den nächsten Schritt machen, nämlich Ihre Karte auf einer Webseite anzeigen. Wir verwenden nur eine `html`-Datei für Ihre kleine Web-App; bedenken Sie, dass Ihre Web-App in einer Produktions- oder Teamumgebung wahrscheinlich mehr Bestandteile haben wird!

### Aufgabe - Eine Karte auf einer Webseite anzeigen

1. Erstellen Sie eine Datei namens index.html in einem Ordner auf Ihrem lokalen Computer. Fügen Sie HTML-Markup hinzu, um eine Karte zu halten:

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    Die Karte wird im `myMap`-`div` geladen. Einige Styles ermöglichen es ihr, die Breite und Höhe der Seite zu füllen.

    > 🎓 Ein `div` ist ein Abschnitt einer Webseite, der benannt und gestaltet werden kann.

1. Fügen Sie unter dem öffnenden `<head>`-Tag ein externes Stylesheet hinzu, um die Kartendarstellung zu steuern, und ein externes Skript aus dem Web-SDK, um ihr Verhalten zu verwalten:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Dieses Stylesheet enthält die Einstellungen für das Aussehen der Karte, und die Skriptdatei enthält Code, um die Karte zu laden. Das Hinzufügen dieses Codes ist ähnlich wie das Einfügen von C++-Header-Dateien oder das Importieren von Python-Modulen.

1. Fügen Sie unter diesem Skript einen Skriptblock hinzu, um die Karte zu starten.

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    Ersetzen Sie `<subscription_key>` durch den API-Schlüssel für Ihr Azure Maps-Konto.

    Wenn Sie Ihre `index.html`-Seite in einem Webbrowser öffnen, sollten Sie eine Karte sehen, die auf den Bereich Seattle fokussiert ist.

    ![Eine Karte, die Seattle, eine Stadt im Bundesstaat Washington, USA, zeigt](../../../../../translated_images/de/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Experimentieren Sie mit den Zoom- und Center-Parametern, um Ihre Kartendarstellung zu ändern. Sie können verschiedene Koordinaten entsprechend der Breite und Länge Ihrer Daten hinzufügen, um die Karte neu zu zentrieren.

> 💁 Eine bessere Möglichkeit, mit Web-Apps lokal zu arbeiten, ist die Installation von [http-server](https://www.npmjs.com/package/http-server). Sie benötigen [node.js](https://nodejs.org/) und [npm](https://www.npmjs.com/) vor der Verwendung dieses Tools. Sobald diese Tools installiert sind, können Sie zu dem Speicherort Ihrer `index.html`-Datei navigieren und `http-server` eingeben. Die Web-App wird auf einem lokalen Webserver [http://127.0.0.1:8080/](http://127.0.0.1:8080/) geöffnet.

## Das GeoJSON-Format

Jetzt, da Sie Ihre Web-App mit der angezeigten Karte eingerichtet haben, müssen Sie GPS-Daten aus Ihrem Speicherkonto extrahieren und in einer Ebene von Markern über der Karte anzeigen. Bevor wir das tun, werfen wir einen Blick auf das [GeoJSON](https://wikipedia.org/wiki/GeoJSON)-Format, das von Azure Maps benötigt wird.

[GeoJSON](https://geojson.org/) ist ein offener Standard für JSON-Spezifikationen mit spezieller Formatierung, die für geografische Daten entwickelt wurde. Sie können mehr darüber erfahren, indem Sie Beispieldaten mit [geojson.io](https://geojson.io) testen, das auch ein nützliches Tool zum Debuggen von GeoJSON-Dateien ist.

Beispieldaten im GeoJSON-Format sehen wie folgt aus:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

Besonders interessant ist die Art und Weise, wie die Daten als `Feature` innerhalb einer `FeatureCollection` verschachtelt sind. Innerhalb dieses Objekts befindet sich `geometry` mit den `coordinates`, die Breite und Länge angeben.

✅ Achten Sie beim Erstellen Ihres GeoJSON darauf, in welcher Reihenfolge `latitude` und `longitude` im Objekt angegeben sind, sonst erscheinen Ihre Punkte nicht dort, wo sie sollten! GeoJSON erwartet Daten in der Reihenfolge `lon,lat` für Punkte, nicht `lat,lon`.

`Geometry` kann verschiedene Typen haben, wie z. B. einen einzelnen Punkt oder ein Polygon. In diesem Beispiel handelt es sich um einen Punkt mit zwei angegebenen Koordinaten, der Länge und der Breite.
✅ Azure Maps unterstützt standardmäßiges GeoJSON sowie einige [erweiterte Funktionen](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), einschließlich der Möglichkeit, Kreise und andere Geometrien zu zeichnen.

## GPS-Daten mit GeoJSON auf einer Karte darstellen

Jetzt bist du bereit, die Daten aus dem Speicher zu nutzen, den du in der vorherigen Lektion erstellt hast. Zur Erinnerung: Die Daten werden als mehrere Dateien im Blob-Speicher gespeichert. Du musst die Dateien abrufen und analysieren, damit Azure Maps die Daten verwenden kann.

### Aufgabe - Speicher für den Zugriff von einer Webseite konfigurieren

Wenn du eine Anfrage an deinen Speicher sendest, um die Daten abzurufen, könntest du überrascht sein, Fehler in der Konsole deines Browsers zu sehen. Das liegt daran, dass du Berechtigungen für [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) in diesem Speicher festlegen musst, um externen Webanwendungen den Zugriff auf die Daten zu ermöglichen.

> 🎓 CORS steht für "Cross-Origin Resource Sharing" und muss in Azure aus Sicherheitsgründen normalerweise explizit eingestellt werden. Es verhindert, dass unerwartete Websites auf deine Daten zugreifen können.

1. Führe den folgenden Befehl aus, um CORS zu aktivieren:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Ersetze `<storage_name>` durch den Namen deines Speicherkontos. Ersetze `<key1>` durch den Kontoschlüssel deines Speicherkontos.

    Dieser Befehl erlaubt jeder Website (das Platzhalterzeichen `*` bedeutet jede), eine *GET*-Anfrage zu stellen, also Daten von deinem Speicherkonto abzurufen. Das `--services b` bedeutet, dass diese Einstellung nur für Blobs gilt.

### Aufgabe - GPS-Daten aus dem Speicher laden

1. Ersetze den gesamten Inhalt der `init`-Funktion durch den folgenden Code:

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    Ersetze `<storage_name>` durch den Namen deines Speicherkontos. Ersetze `<subscription_key>` durch den API-Schlüssel deines Azure Maps-Kontos.

    Hier passiert einiges. Zuerst ruft der Code deine GPS-Daten aus deinem Blob-Container über einen URL-Endpunkt ab, der mit deinem Speicherkontonamen erstellt wurde. Diese URL ruft Daten aus `gps-data` ab, was darauf hinweist, dass der Ressourcentyp ein Container ist (`restype=container`), und listet Informationen über alle Blobs auf. Diese Liste gibt nicht die Blobs selbst zurück, sondern eine URL für jedes Blob, die verwendet werden kann, um die Blob-Daten zu laden.

    > 💁 Du kannst diese URL in deinen Browser eingeben, um Details zu allen Blobs in deinem Container zu sehen. Jedes Element hat eine `Url`-Eigenschaft, die du ebenfalls in deinem Browser laden kannst, um den Inhalt des Blobs zu sehen.

    Dieser Code lädt dann jedes Blob, indem er eine `loadJSON`-Funktion aufruft, die als Nächstes erstellt wird. Anschließend wird die Kartensteuerung erstellt und Code zum `ready`-Ereignis hinzugefügt. Dieses Ereignis wird aufgerufen, wenn die Karte auf der Webseite angezeigt wird.

    Das `ready`-Ereignis erstellt eine Azure Maps-Datenquelle - einen Container, der GeoJSON-Daten enthält, die später befüllt werden. Diese Datenquelle wird dann verwendet, um eine Bubble-Schicht zu erstellen - also eine Reihe von Kreisen auf der Karte, die über jedem Punkt im GeoJSON zentriert sind.

1. Füge die `loadJSON`-Funktion in deinen Skriptblock unterhalb der `init`-Funktion ein:

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    Diese Funktion wird von der Abrufroutine aufgerufen, um die JSON-Daten zu analysieren und sie in Längen- und Breitengradkoordinaten als GeoJSON zu konvertieren. 
    Nach der Analyse werden die Daten als Teil eines GeoJSON-`Feature` festgelegt. Die Karte wird initialisiert, und kleine Kreise erscheinen entlang des Pfads, den deine Daten darstellen:

1. Lade die HTML-Seite in deinem Browser. Sie wird die Karte laden, dann alle GPS-Daten aus dem Speicher abrufen und sie auf der Karte darstellen.

    ![Eine Karte des Saint Edward State Park in der Nähe von Seattle, mit Kreisen, die einen Pfad entlang des Parkrands zeigen](../../../../../translated_images/de/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Du findest diesen Code im [code](../../../../../3-transport/lessons/3-visualize-location-data/code)-Ordner.

---

## 🚀 Herausforderung

Es ist schön, statische Daten als Marker auf einer Karte anzuzeigen. Kannst du diese Webanwendung erweitern, um Animationen hinzuzufügen und den Pfad der Marker im Laufe der Zeit anzuzeigen, indem du die JSON-Dateien mit Zeitstempeln verwendest? Hier sind [einige Beispiele](https://azuremapscodesamples.azurewebsites.net/) für die Verwendung von Animationen in Karten.

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Rückblick & Selbststudium

Azure Maps ist besonders nützlich für die Arbeit mit IoT-Geräten.

* Recherchiere einige der Einsatzmöglichkeiten in der [Azure Maps-Dokumentation auf Microsoft Docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Vertiefe dein Wissen über Kartenerstellung und Wegpunkte mit dem [Lernmodul "Erstelle deine erste Routenfindungs-App mit Azure Maps" auf Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Aufgabe

[Stelle deine App bereit](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.