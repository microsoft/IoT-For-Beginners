<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-25T22:53:49+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "de"
}
-->
# Geofences

![Eine Sketchnote-Übersicht dieser Lektion](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.de.jpg)

> Sketchnote von [Nitya Narasimhan](https://github.com/nitya). Klicken Sie auf das Bild für eine größere Version.

Dieses Video gibt einen Überblick über Geofences und deren Verwendung in Azure Maps, Themen, die in dieser Lektion behandelt werden:

[![Geofencing mit Azure Maps aus der Microsoft Developer IoT Show](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Klicken Sie auf das Bild oben, um das Video anzusehen

## Quiz vor der Lektion

[Quiz vor der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Einführung

In den letzten drei Lektionen haben Sie IoT verwendet, um die LKWs zu lokalisieren, die Ihre Produkte von Ihrer Farm zu einem Verarbeitungszentrum transportieren. Sie haben GPS-Daten erfasst, in der Cloud gespeichert und auf einer Karte visualisiert. Der nächste Schritt zur Steigerung der Effizienz Ihrer Lieferkette besteht darin, eine Benachrichtigung zu erhalten, wenn ein LKW kurz vor der Ankunft im Verarbeitungszentrum steht, damit das Team, das für das Entladen benötigt wird, mit Gabelstaplern und anderen Geräten bereit ist, sobald das Fahrzeug ankommt. Auf diese Weise kann das Entladen schnell erfolgen, und Sie zahlen nicht für einen LKW und Fahrer, der warten muss.

In dieser Lektion lernen Sie Geofences kennen – definierte geographische Regionen wie ein Bereich innerhalb einer 2 km langen Fahrt zu einem Verarbeitungszentrum – und wie Sie testen können, ob GPS-Koordinaten innerhalb oder außerhalb eines Geofence liegen, damit Sie sehen können, ob Ihr GPS-Sensor ein Gebiet erreicht oder verlassen hat.

In dieser Lektion behandeln wir:

* [Was sind Geofences](../../../../../3-transport/lessons/4-geofences)
* [Definieren eines Geofence](../../../../../3-transport/lessons/4-geofences)
* [Testen von Punkten gegen einen Geofence](../../../../../3-transport/lessons/4-geofences)
* [Verwendung von Geofences aus serverlosem Code](../../../../../3-transport/lessons/4-geofences)

> 🗑 Dies ist die letzte Lektion in diesem Projekt. Vergessen Sie nach Abschluss dieser Lektion und der Aufgabe nicht, Ihre Cloud-Dienste aufzuräumen. Sie benötigen die Dienste, um die Aufgabe abzuschließen, stellen Sie also sicher, dass Sie diese zuerst abschließen.
>
> Konsultieren Sie bei Bedarf [den Leitfaden zum Aufräumen Ihres Projekts](../../../clean-up.md) für Anweisungen, wie Sie dies tun können.

## Was sind Geofences

Ein Geofence ist ein virtueller Umkreis für eine reale geografische Region. Geofences können Kreise sein, die als Punkt und Radius definiert sind (zum Beispiel ein Kreis mit einem Durchmesser von 100 m um ein Gebäude), oder ein Polygon, das einen Bereich wie eine Schulzone, Stadtgrenzen oder einen Universitäts- oder Bürocampus abdeckt.

![Einige Beispiele für Geofences, die einen kreisförmigen Geofence um den Microsoft Company Store und einen polygonalen Geofence um den Microsoft West Campus zeigen](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.de.png)

> 💁 Möglicherweise haben Sie bereits Geofences verwendet, ohne es zu wissen. Wenn Sie eine Erinnerung mit der iOS-Erinnerungs-App oder Google Keep basierend auf einem Standort eingerichtet haben, haben Sie einen Geofence verwendet. Diese Apps richten basierend auf dem angegebenen Standort einen Geofence ein und benachrichtigen Sie, wenn Ihr Telefon den Geofence betritt.

Es gibt viele Gründe, warum Sie wissen möchten, ob ein Fahrzeug innerhalb oder außerhalb eines Geofence ist:

* Vorbereitung für das Entladen – Eine Benachrichtigung, dass ein Fahrzeug vor Ort angekommen ist, ermöglicht es einem Team, sich auf das Entladen des Fahrzeugs vorzubereiten, wodurch die Wartezeit des Fahrzeugs reduziert wird. Dies kann es einem Fahrer ermöglichen, an einem Tag mehr Lieferungen mit weniger Wartezeit durchzuführen.
* Steuerkonformität – Einige Länder, wie Neuseeland, erheben Straßensteuern für Dieselfahrzeuge basierend auf dem Fahrzeuggewicht, wenn sie nur auf öffentlichen Straßen fahren. Mit Geofences können Sie die gefahrenen Kilometer auf öffentlichen Straßen im Vergleich zu privaten Straßen auf Grundstücken wie Farmen oder Holzgebieten verfolgen.
* Diebstahlüberwachung – Wenn ein Fahrzeug nur in einem bestimmten Bereich wie einer Farm bleiben sollte und den Geofence verlässt, könnte es gestohlen worden sein.
* Standortkonformität – Einige Teile eines Arbeitsplatzes, einer Farm oder einer Fabrik können für bestimmte Fahrzeuge gesperrt sein, wie z. B. das Fernhalten von Fahrzeugen, die künstliche Düngemittel und Pestizide transportieren, von Feldern, auf denen biologisch angebaut wird. Wenn ein Geofence betreten wird, befindet sich ein Fahrzeug außerhalb der Konformität, und der Fahrer kann benachrichtigt werden.

✅ Können Sie sich andere Verwendungszwecke für Geofences vorstellen?

Azure Maps, der Dienst, den Sie in der letzten Lektion verwendet haben, um GPS-Daten zu visualisieren, ermöglicht es Ihnen, Geofences zu definieren und dann zu testen, ob ein Punkt innerhalb oder außerhalb des Geofence liegt.

## Definieren eines Geofence

Geofences werden mit GeoJSON definiert, genau wie die Punkte, die in der vorherigen Lektion zur Karte hinzugefügt wurden. In diesem Fall handelt es sich jedoch nicht um eine `FeatureCollection` von `Point`-Werten, sondern um eine `FeatureCollection`, die ein `Polygon` enthält.

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Jeder Punkt des Polygons wird als Längen- und Breitengradpaar in einem Array definiert, und diese Punkte befinden sich in einem Array, das als `coordinates` festgelegt ist. In einem `Point` in der letzten Lektion war `coordinates` ein Array, das 2 Werte enthielt, Breitengrad und Längengrad. Für ein `Polygon` ist es ein Array von Arrays, die jeweils 2 Werte enthalten, Längengrad und Breitengrad.

> 💁 Denken Sie daran, GeoJSON verwendet `Längengrad, Breitengrad` für Punkte, nicht `Breitengrad, Längengrad`.

Das Polygon-Koordinaten-Array hat immer einen Eintrag mehr als die Anzahl der Punkte des Polygons, wobei der letzte Eintrag derselbe ist wie der erste, um das Polygon zu schließen. Zum Beispiel hätte ein Rechteck 5 Punkte.

![Ein Rechteck mit Koordinaten](../../../../../translated_images/polygon-points.302193da381cb415.de.png)

Im obigen Bild gibt es ein Rechteck. Die Polygon-Koordinaten beginnen oben links bei 47,-122, bewegen sich dann nach rechts zu 47,-121, dann nach unten zu 46,-121, dann nach links zu 46,-122 und schließlich wieder nach oben zum Startpunkt bei 47,-122. Dies ergibt 5 Punkte für das Polygon – oben links, oben rechts, unten rechts, unten links und dann oben links, um es zu schließen.

✅ Versuchen Sie, ein GeoJSON-Polygon um Ihr Zuhause oder Ihre Schule zu erstellen. Verwenden Sie ein Tool wie [GeoJSON.io](https://geojson.io/).

### Aufgabe – Geofence definieren

Um einen Geofence in Azure Maps zu verwenden, muss er zuerst in Ihrem Azure Maps-Konto hochgeladen werden. Nach dem Hochladen erhalten Sie eine eindeutige ID, die Sie verwenden können, um einen Punkt gegen den Geofence zu testen. Um Geofences in Azure Maps hochzuladen, müssen Sie die Maps-Web-API verwenden. Sie können die Azure Maps-Web-API mit einem Tool namens [curl](https://curl.se) aufrufen.

> 🎓 Curl ist ein Befehlszeilentool, um Anfragen an Web-Endpunkte zu stellen.

1. Wenn Sie Linux, macOS oder eine aktuelle Version von Windows 10 verwenden, haben Sie curl wahrscheinlich bereits installiert. Führen Sie den folgenden Befehl in Ihrem Terminal oder Ihrer Befehlszeile aus, um dies zu überprüfen:

    ```sh
    curl --version
    ```

    Wenn Sie keine Versionsinformationen für curl sehen, müssen Sie es von der [curl-Downloadseite](https://curl.se/download.html) installieren.

    > 💁 Wenn Sie Erfahrung mit Postman haben, können Sie stattdessen dieses Tool verwenden, wenn Sie möchten.

1. Erstellen Sie eine GeoJSON-Datei, die ein Polygon enthält. Sie werden dies mit Ihrem GPS-Sensor testen, erstellen Sie also ein Polygon um Ihren aktuellen Standort. Sie können entweder eines manuell erstellen, indem Sie das oben gegebene GeoJSON-Beispiel bearbeiten, oder ein Tool wie [GeoJSON.io](https://geojson.io) verwenden.

    Das GeoJSON muss eine `FeatureCollection` enthalten, die ein `Feature` mit einer `geometry` vom Typ `Polygon` enthält.

    Sie **MÜSSEN** auch ein `properties`-Element auf derselben Ebene wie das `geometry`-Element hinzufügen, und dieses muss ein `geometryId` enthalten:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Wenn Sie [GeoJSON.io](https://geojson.io) verwenden, müssen Sie dieses Element manuell zum leeren `properties`-Element hinzufügen, entweder nach dem Herunterladen der JSON-Datei oder im JSON-Editor der App.

    Dieses `geometryId` muss in dieser Datei eindeutig sein. Sie können mehrere Geofences als mehrere `Features` in der `FeatureCollection` in derselben GeoJSON-Datei hochladen, solange jedes eine andere `geometryId` hat. Polygone können dieselbe `geometryId` haben, wenn sie aus einer anderen Datei zu einem anderen Zeitpunkt hochgeladen werden.

1. Speichern Sie diese Datei als `geofence.json` und navigieren Sie zu dem Speicherort in Ihrem Terminal oder Ihrer Konsole.

1. Führen Sie den folgenden curl-Befehl aus, um den Geofence zu erstellen:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Ersetzen Sie `<subscription_key>` in der URL durch den API-Schlüssel für Ihr Azure Maps-Konto.

    Die URL wird verwendet, um Kartendaten über die `https://atlas.microsoft.com/mapData/upload`-API hochzuladen. Der Aufruf enthält einen `api-version`-Parameter, um anzugeben, welche Azure Maps-API verwendet werden soll. Dies dient dazu, der API zu ermöglichen, sich im Laufe der Zeit zu ändern, während die Abwärtskompatibilität erhalten bleibt. Das hochgeladene Datenformat wird auf `geojson` gesetzt.

    Dies führt die POST-Anfrage an die Upload-API aus und gibt eine Liste von Antwort-Headern zurück, die einen Header namens `location` enthält:

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Beim Aufruf eines Web-Endpunkts können Sie Parameter an den Aufruf übergeben, indem Sie ein `?` gefolgt von Schlüssel-Wert-Paaren als `key=value` hinzufügen, wobei die Schlüssel-Wert-Paare durch ein `&` getrennt werden.

1. Azure Maps verarbeitet dies nicht sofort, daher müssen Sie überprüfen, ob die Upload-Anfrage abgeschlossen ist, indem Sie die URL verwenden, die im `location`-Header angegeben ist. Führen Sie eine GET-Anfrage an diesen Standort aus, um den Status zu sehen. Sie müssen Ihren Abonnement-Schlüssel am Ende der `location`-URL hinzufügen, indem Sie `&subscription-key=<subscription_key>` hinzufügen, wobei `<subscription_key>` durch den API-Schlüssel für Ihr Azure Maps-Konto ersetzt wird. Führen Sie den folgenden Befehl aus:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Ersetzen Sie `<location>` durch den Wert des `location`-Headers und `<subscription_key>` durch den API-Schlüssel für Ihr Azure Maps-Konto.

1. Überprüfen Sie den Wert von `status` in der Antwort. Wenn er nicht `Succeeded` ist, warten Sie eine Minute und versuchen Sie es erneut.

1. Sobald der Status als `Succeeded` zurückkommt, sehen Sie sich den `resourceLocation` aus der Antwort an. Dieser enthält Details zur eindeutigen ID (bekannt als UDID) für das GeoJSON-Objekt. Die UDID ist der Wert nach `metadata/` und nicht einschließlich der `api-version`. Zum Beispiel, wenn der `resourceLocation` war:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Dann wäre die UDID `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Bewahren Sie eine Kopie dieser UDID auf, da Sie sie benötigen, um den Geofence zu testen.

## Testen von Punkten gegen einen Geofence

Sobald das Polygon in Azure Maps hochgeladen wurde, können Sie einen Punkt testen, um zu sehen, ob er innerhalb oder außerhalb des Geofence liegt. Dies geschieht durch eine Web-API-Anfrage, bei der die UDID des Geofence sowie der Breitengrad und Längengrad des zu testenden Punktes übergeben werden.

Wenn Sie diese Anfrage stellen, können Sie auch einen Wert namens `searchBuffer` übergeben. Dieser gibt an, wie genau die Ergebnisse zurückgegeben werden sollen. Der Grund dafür ist, dass GPS nicht perfekt genau ist und manchmal Standorte um Meter oder mehr abweichen können. Der Standardwert für den Suchpuffer beträgt 50 m, aber Sie können Werte von 0 m bis 500 m festlegen.

Wenn Ergebnisse von der API-Anfrage zurückgegeben werden, ist einer der Teile des Ergebnisses eine `distance`, die bis zum nächstgelegenen Punkt am Rand des Geofence gemessen wird, mit einem positiven Wert, wenn der Punkt außerhalb des Geofence liegt, und einem negativen Wert, wenn er innerhalb des Geofence liegt. Wenn diese Entfernung kleiner als der Suchpuffer ist, wird die tatsächliche Entfernung in Metern zurückgegeben, andernfalls beträgt der Wert 999 oder -999. 999 bedeutet, dass der Punkt mehr als den Suchpuffer außerhalb des Geofence liegt, -999 bedeutet, dass er mehr als den Suchpuffer innerhalb des Geofence liegt.

![Ein Geofence mit einem 50m-Suchpuffer darum](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.de.png)

Im obigen Bild hat der Geofence einen 50m-Suchpuffer.

* Ein Punkt in der Mitte des Geofence, weit innerhalb des Suchpuffers, hat eine Entfernung von **-999**.
* Ein Punkt weit außerhalb des Suchpuffers hat eine Entfernung von **999**.
* Ein Punkt innerhalb des Geofence und innerhalb des Suchpuffers, 6 m vom Geofence entfernt, hat eine Entfernung von **6 m**.
* Ein Punkt außerhalb des Geofence und innerhalb des Suchpuffers, 39 m vom Geofence entfernt, hat eine Entfernung von **39 m**.

Es ist wichtig, die Entfernung zum Rand des Geofence zu kennen und diese mit anderen Informationen wie anderen GPS-Messungen, Geschwindigkeit und Straßendaten zu kombinieren, wenn Entscheidungen basierend auf dem Standort eines Fahrzeugs getroffen werden.

Zum Beispiel stellen Sie sich GPS-Messungen vor, die zeigen, dass ein Fahrzeug auf einer Straße fährt, die neben einem Geofence verläuft. Wenn ein einzelner GPS-Wert ungenau ist und das Fahrzeug innerhalb des Geofence platziert, obwohl es keinen Fahrzeugzugang gibt, kann dies ignoriert werden.

![Eine GPS-Spur, die zeigt, wie ein Fahrzeug den Microsoft Campus auf der 520 passiert, mit GPS-Messungen entlang der Straße, außer einer auf dem Campus, innerhalb eines Geofence](../../../../../translated_images/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.de.png)
Auf dem obigen Bild ist ein Geofence über einem Teil des Microsoft-Campus zu sehen. Die rote Linie zeigt einen LKW, der entlang der 520 fährt, mit Kreisen, die die GPS-Messungen darstellen. Die meisten dieser Messungen sind genau und entlang der 520, mit einer ungenauen Messung innerhalb des Geofence. Es ist unmöglich, dass diese Messung korrekt ist – es gibt keine Straßen, auf denen der LKW plötzlich von der 520 auf den Campus abbiegen und dann wieder zurück auf die 520 fahren könnte. Der Code, der diesen Geofence überprüft, muss die vorherigen Messungen berücksichtigen, bevor er auf die Ergebnisse des Geofence-Tests reagiert.

✅ Welche zusätzlichen Daten würden Sie benötigen, um zu überprüfen, ob eine GPS-Messung als korrekt angesehen werden kann?

### Aufgabe – Punkte gegen einen Geofence testen

1. Beginnen Sie mit dem Aufbau der URL für die Web-API-Abfrage. Das Format lautet:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Ersetzen Sie `<subscription_key>` durch den API-Schlüssel für Ihr Azure Maps-Konto.

    Ersetzen Sie `<UDID>` durch die UDID des Geofence aus der vorherigen Aufgabe.

    Ersetzen Sie `<lat>` und `<lon>` durch die Breiten- und Längengrade, die Sie testen möchten.

    Diese URL verwendet die API `https://atlas.microsoft.com/spatial/geofence/json`, um einen Geofence abzufragen, der mit GeoJSON definiert wurde. Sie zielt auf die API-Version `1.0` ab. Der Parameter `deviceId` ist erforderlich und sollte der Name des Geräts sein, von dem die Breiten- und Längengrade stammen.

    Der Standard-Suchpuffer beträgt 50 m, und Sie können diesen ändern, indem Sie einen zusätzlichen Parameter `searchBuffer=<distance>` übergeben, wobei `<distance>` die Suchpufferdistanz in Metern ist, von 0 bis 500.

1. Verwenden Sie curl, um eine GET-Anfrage an diese URL zu senden:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Wenn Sie einen Antwortcode von `BadRequest` mit einem Fehler erhalten:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > dann fehlt Ihrem GeoJSON der Abschnitt `properties` mit der `geometryId`. Sie müssen Ihr GeoJSON korrigieren, dann die obigen Schritte wiederholen, um es erneut hochzuladen und eine neue UDID zu erhalten.

1. Die Antwort enthält eine Liste von `geometries`, eine für jedes Polygon, das im GeoJSON definiert ist, das den Geofence erstellt hat. Jedes Geometry hat drei interessante Felder: `distance`, `nearestLat` und `nearestLon`.

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` und `nearestLon` sind die Breiten- und Längengrade eines Punktes am Rand des Geofence, der dem getesteten Standort am nächsten liegt.

    * `distance` ist die Entfernung vom getesteten Standort zum nächstgelegenen Punkt am Rand des Geofence. Negative Zahlen bedeuten innerhalb des Geofence, positive außerhalb. Dieser Wert wird weniger als 50 (der Standard-Suchpuffer) oder 999 sein.

1. Wiederholen Sie dies mehrmals mit Standorten innerhalb und außerhalb des Geofence.

## Geofences aus serverlosem Code verwenden

Sie können nun einen neuen Trigger zu Ihrer Functions-App hinzufügen, um die GPS-Ereignisdaten des IoT-Hubs gegen den Geofence zu testen.

### Consumer Groups

Wie Sie sich aus früheren Lektionen erinnern, ermöglicht der IoT-Hub das Wiedergeben von Ereignissen, die vom Hub empfangen, aber nicht verarbeitet wurden. Aber was passiert, wenn mehrere Trigger verbunden sind? Wie weiß der Hub, welcher Trigger welche Ereignisse verarbeitet hat?

Die Antwort lautet: Er weiß es nicht! Stattdessen können Sie mehrere separate Verbindungen definieren, um Ereignisse zu lesen, und jede kann die Wiedergabe von ungelesenen Nachrichten verwalten. Diese werden *Consumer Groups* genannt. Wenn Sie sich mit dem Endpunkt verbinden, können Sie angeben, welche Consumer Group Sie verwenden möchten. Jede Komponente Ihrer Anwendung wird sich mit einer anderen Consumer Group verbinden.

![Ein IoT-Hub mit 3 Consumer Groups, die dieselben Nachrichten an 3 verschiedene Functions-Apps verteilen](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.de.png)

Theoretisch können bis zu 5 Anwendungen mit jeder Consumer Group verbunden werden, und sie erhalten alle Nachrichten, wenn diese eintreffen. Es ist jedoch Best Practice, dass nur eine Anwendung auf jede Consumer Group zugreift, um doppelte Nachrichtenverarbeitung zu vermeiden und sicherzustellen, dass beim Neustart alle wartenden Nachrichten korrekt verarbeitet werden. Wenn Sie beispielsweise Ihre Functions-App lokal starten und gleichzeitig in der Cloud ausführen, würden beide Nachrichten verarbeiten, was zu doppelten Blobs im Speicher führt.

Wenn Sie die Datei `function.json` für den IoT-Hub-Trigger überprüfen, den Sie in einer früheren Lektion erstellt haben, sehen Sie die Consumer Group im Abschnitt der Event-Hub-Trigger-Bindung:

```json
"consumerGroup": "$Default"
```

Wenn Sie einen IoT-Hub erstellen, wird die Consumer Group `$Default` standardmäßig erstellt. Wenn Sie einen zusätzlichen Trigger hinzufügen möchten, können Sie dies mit einer neuen Consumer Group tun.

> 💁 In dieser Lektion verwenden Sie eine andere Funktion, um den Geofence zu testen, als die, die die GPS-Daten speichert. Dies dient dazu, zu zeigen, wie Consumer Groups verwendet werden und wie der Code getrennt werden kann, um ihn leichter lesbar und verständlich zu machen. In einer Produktionsanwendung gibt es viele Möglichkeiten, dies zu gestalten – beide in einer Funktion zu kombinieren, einen Trigger im Speicheraccount zu verwenden, um eine Funktion auszuführen, die den Geofence überprüft, oder mehrere Funktionen zu verwenden. Es gibt keinen „richtigen Weg“, es hängt von der restlichen Anwendung und Ihren Anforderungen ab.

### Aufgabe – eine neue Consumer Group erstellen

1. Führen Sie den folgenden Befehl aus, um eine neue Consumer Group namens `geofence` für Ihren IoT-Hub zu erstellen:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen, den Sie für Ihren IoT-Hub verwendet haben.

1. Wenn Sie alle Consumer Groups für einen IoT-Hub anzeigen möchten, führen Sie den folgenden Befehl aus:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Ersetzen Sie `<hub_name>` durch den Namen, den Sie für Ihren IoT-Hub verwendet haben. Dies listet alle Consumer Groups auf.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Als Sie den IoT-Hub-Ereignismonitor in einer früheren Lektion ausgeführt haben, hat er sich mit der Consumer Group `$Default` verbunden. Aus diesem Grund können Sie den Ereignismonitor und einen Ereignistrigger nicht gleichzeitig ausführen. Wenn Sie beide ausführen möchten, können Sie andere Consumer Groups für alle Ihre Functions-Apps verwenden und `$Default` für den Ereignismonitor behalten.

### Aufgabe – einen neuen IoT-Hub-Trigger erstellen

1. Fügen Sie Ihrer `gps-trigger`-Functions-App, die Sie in einer früheren Lektion erstellt haben, einen neuen IoT-Hub-Ereignistrigger hinzu. Nennen Sie diese Funktion `geofence-trigger`.

    > ⚠️ Sie können [die Anweisungen zum Erstellen eines IoT-Hub-Ereignistriggers aus Projekt 2, Lektion 5 bei Bedarf nachlesen](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Konfigurieren Sie die IoT-Hub-Verbindungszeichenfolge in der Datei `function.json`. Die Datei `local.settings.json` wird zwischen allen Triggern in der Functions-App geteilt.

1. Aktualisieren Sie den Wert von `consumerGroup` in der Datei `function.json`, um auf die neue Consumer Group `geofence` zu verweisen:

    ```json
    "consumerGroup": "geofence"
    ```

1. Sie benötigen den Abonnement-Schlüssel für Ihr Azure Maps-Konto in diesem Trigger, also fügen Sie der Datei `local.settings.json` einen neuen Eintrag namens `MAPS_KEY` hinzu.

1. Führen Sie die Functions-App aus, um sicherzustellen, dass sie Nachrichten empfängt und verarbeitet. Der `iot-hub-trigger` aus der früheren Lektion wird ebenfalls ausgeführt und Blobs in den Speicher hochladen.

    > Um doppelte GPS-Messungen im Blob-Speicher zu vermeiden, können Sie die Functions-App, die Sie in der Cloud ausführen, stoppen. Verwenden Sie dazu den folgenden Befehl:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Ersetzen Sie `<functions_app_name>` durch den Namen, den Sie für Ihre Functions-App verwendet haben.
    >
    > Sie können sie später mit dem folgenden Befehl neu starten:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Ersetzen Sie `<functions_app_name>` durch den Namen, den Sie für Ihre Functions-App verwendet haben.

### Aufgabe – den Geofence vom Trigger aus testen

Früher in dieser Lektion haben Sie curl verwendet, um einen Geofence abzufragen und zu sehen, ob ein Punkt sich innerhalb oder außerhalb befindet. Sie können eine ähnliche Web-Anfrage aus Ihrem Trigger heraus machen.

1. Um den Geofence abzufragen, benötigen Sie dessen UDID. Fügen Sie der Datei `local.settings.json` einen neuen Eintrag namens `GEOFENCE_UDID` mit diesem Wert hinzu.

1. Öffnen Sie die Datei `__init__.py` aus dem neuen Trigger `geofence-trigger`.

1. Fügen Sie die folgende Import-Anweisung oben in der Datei hinzu:

    ```python
    import json
    import os
    import requests
    ```

    Das Paket `requests` ermöglicht es Ihnen, Web-API-Aufrufe zu machen. Azure Maps hat kein Python-SDK, Sie müssen Web-API-Aufrufe verwenden, um es aus Python-Code zu nutzen.

1. Fügen Sie die folgenden zwei Zeilen am Anfang der Methode `main` hinzu, um den Maps-Abonnement-Schlüssel zu erhalten:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Innerhalb der Schleife `for event in events` fügen Sie Folgendes hinzu, um die Breiten- und Längengrade aus jedem Ereignis zu erhalten:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Dieser Code konvertiert das JSON aus dem Ereigniskörper in ein Dictionary und extrahiert dann die `lat` und `lon` aus dem Feld `gps`.

1. Wenn Sie `requests` verwenden, können Sie anstelle einer langen URL, wie Sie es mit curl gemacht haben, nur den URL-Teil verwenden und die Parameter als Dictionary übergeben. Fügen Sie den folgenden Code hinzu, um die URL zu definieren und die Parameter zu konfigurieren:

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    Die Elemente im Dictionary `params` entsprechen den Schlüssel-Wert-Paaren, die Sie beim Aufruf der Web-API über curl verwendet haben.

1. Fügen Sie die folgenden Zeilen Code hinzu, um die Web-API aufzurufen:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Dies ruft die URL mit den Parametern auf und gibt ein Antwortobjekt zurück.

1. Fügen Sie den folgenden Code darunter hinzu:

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    Dieser Code geht von einem Geometry aus und extrahiert die Entfernung von diesem einzelnen Geometry. Anschließend werden verschiedene Nachrichten basierend auf der Entfernung protokolliert.

1. Führen Sie diesen Code aus. Sie sehen in der Protokollausgabe, ob die GPS-Koordinaten innerhalb oder außerhalb des Geofence liegen, mit einer Entfernung, wenn der Punkt innerhalb von 50 m liegt. Testen Sie diesen Code mit verschiedenen Geofences basierend auf dem Standort Ihres GPS-Sensors, versuchen Sie, den Sensor zu bewegen (z. B. über WLAN von einem Mobiltelefon oder mit verschiedenen Koordinaten auf dem virtuellen IoT-Gerät), um diese Änderung zu sehen.

1. Wenn Sie bereit sind, stellen Sie diesen Code in Ihrer Functions-App in der Cloud bereit. Vergessen Sie nicht, die neuen Anwendungseinstellungen hochzuladen.

    > ⚠️ Sie können [die Anweisungen zum Hochladen von Anwendungseinstellungen aus Projekt 2, Lektion 5 bei Bedarf nachlesen](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Sie können [die Anweisungen zum Bereitstellen Ihrer Functions-App aus Projekt 2, Lektion 5 bei Bedarf nachlesen](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Sie finden diesen Code im Ordner [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Herausforderung

In dieser Lektion haben Sie einen Geofence mit einer GeoJSON-Datei mit einem einzigen Polygon hinzugefügt. Sie können mehrere Polygone gleichzeitig hochladen, solange sie unterschiedliche `geometryId`-Werte im Abschnitt `properties` haben.

Versuchen Sie, eine GeoJSON-Datei mit mehreren Polygonen hochzuladen, und passen Sie Ihren Code an, um herauszufinden, welches Polygon den GPS-Koordinaten am nächsten liegt oder in welchem sie sich befinden.

## Quiz nach der Lektion

[Quiz nach der Lektion](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Überprüfung & Selbststudium

* Lesen Sie mehr über Geofences und einige ihrer Anwendungsfälle auf der [Geofencing-Seite auf Wikipedia](https://de.wikipedia.org/wiki/Geo-Fence).
* Lesen Sie mehr über die Azure Maps Geofencing-API in der [Microsoft Azure Maps Spatial - Get Geofence-Dokumentation](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Lesen Sie mehr über Consumer Groups in der [Features and terminology in Azure Event Hubs - Event consumers-Dokumentation auf Microsoft Docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Aufgabe

[Benachrichtigungen mit Twilio senden](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.