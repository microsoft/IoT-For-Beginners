<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-25T21:40:06+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "de"
}
-->
# Kalibriere deinen Sensor

## Anleitung

In dieser Lektion hast du Messwerte des Bodenfeuchtigkeitssensors gesammelt, die als Werte von 0-1023 gemessen werden. Um diese in tatsächliche Bodenfeuchtigkeitswerte umzuwandeln, musst du deinen Sensor kalibrieren. Dies kannst du tun, indem du Messungen von Bodenproben vornimmst und anschließend den gravimetrischen Bodenfeuchtigkeitsgehalt aus diesen Proben berechnest.

Du musst diese Schritte mehrfach wiederholen, um die benötigten Messwerte zu erhalten, wobei der Boden jedes Mal unterschiedlich feucht sein sollte.

1. Nimm eine Bodenfeuchtigkeitsmessung mit dem Bodenfeuchtigkeitssensor vor. Notiere diesen Wert.

1. Nimm eine Bodenprobe und wiege sie. Notiere dieses Gewicht.

1. Trockne den Boden – ein warmer Ofen bei 110°C (230°F) für ein paar Stunden ist die beste Methode. Du kannst dies auch in der Sonne tun oder den Boden an einem warmen, trockenen Ort platzieren, bis er vollständig trocken ist. Der Boden sollte pulverig und locker sein.

    > 💁 In einem Labor würdest du für die genauesten Ergebnisse den Boden 48-72 Stunden lang in einem Ofen trocknen. Wenn deine Schule Trocknungsöfen hat, frage, ob du diese länger nutzen kannst. Je länger, desto trockener die Probe und desto genauer die Ergebnisse.

1. Wiege den Boden erneut.

    > 🔥 Wenn du ihn in einem Ofen getrocknet hast, stelle sicher, dass er zuerst abgekühlt ist!

Der gravimetrische Bodenfeuchtigkeitsgehalt wird wie folgt berechnet:

![Bodenfeuchtigkeit % ist Gewicht nass minus Gewicht trocken, geteilt durch Gewicht trocken, mal 100](../../../../../translated_images/de/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W
- das Gewicht des nassen Bodens
* W
- das Gewicht des trockenen Bodens

Zum Beispiel: Angenommen, du hast eine Bodenprobe, die 212g nass und 197g trocken wiegt.

![Die ausgefüllte Berechnung](../../../../../translated_images/de/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g
* W = 197g
* 212 - 197 = 15
* 15 / 197 = 0,076
* 0,076 * 100 = 7,6%

In diesem Beispiel hat der Boden eine gravimetrische Bodenfeuchtigkeit von 7,6%.

Sobald du die Messwerte für mindestens 3 Proben hast, erstelle ein Diagramm mit der Bodenfeuchtigkeit % im Vergleich zu den Messwerten des Bodenfeuchtigkeitssensors und füge eine Linie hinzu, die die Punkte am besten verbindet. Du kannst diese Linie dann verwenden, um den gravimetrischen Bodenfeuchtigkeitsgehalt für einen bestimmten Sensorwert abzulesen.

## Bewertungskriterien

| Kriterium | Hervorragend | Angemessen | Verbesserungswürdig |
| --------- | ------------ | ---------- | -------------------- |
| Kalibrierungsdaten sammeln | Mindestens 3 Kalibrierungsproben erfassen | Mindestens 2 Kalibrierungsproben erfassen | Mindestens 1 Kalibrierungsprobe erfassen |
| Kalibrierte Messung durchführen | Erfolgreich das Kalibrierungsdiagramm erstellen, eine Messung vom Sensor vornehmen und in gravimetrischen Bodenfeuchtigkeitsgehalt umwandeln | Erfolgreich das Kalibrierungsdiagramm erstellen | Nicht in der Lage, das Diagramm zu erstellen |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.