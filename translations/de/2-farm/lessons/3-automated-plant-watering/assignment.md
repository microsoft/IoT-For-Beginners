<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-25T21:26:33+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "de"
}
-->
# Erstellen Sie einen effizienteren Bewässerungszyklus

## Anweisungen

In dieser Lektion wurde behandelt, wie man ein Relais über Sensordaten steuert, und dieses Relais könnte wiederum eine Pumpe für ein Bewässerungssystem steuern. Für eine definierte Menge an Boden sollte das Betreiben einer Pumpe für eine feste Zeitdauer immer denselben Einfluss auf die Bodenfeuchtigkeit haben. Das bedeutet, dass Sie eine Vorstellung davon bekommen können, wie viele Sekunden Bewässerung einem bestimmten Rückgang der Bodenfeuchtigkeitsmessung entsprechen. Mit diesen Daten können Sie ein besser kontrolliertes Bewässerungssystem erstellen.

Für diese Aufgabe berechnen Sie, wie lange die Pumpe laufen sollte, um einen bestimmten Anstieg der Bodenfeuchtigkeit zu erreichen.

> ⚠️ Wenn Sie virtuelle IoT-Hardware verwenden, können Sie diesen Prozess durchlaufen, aber die Ergebnisse simulieren, indem Sie die Bodenfeuchtigkeitsmessung manuell um einen festen Betrag pro Sekunde erhöhen, in der das Relais eingeschaltet ist.

1. Beginnen Sie mit trockenem Boden. Messen Sie die Bodenfeuchtigkeit.

1. Fügen Sie eine feste Menge Wasser hinzu, entweder indem Sie die Pumpe für 1 Sekunde laufen lassen oder eine feste Menge Wasser eingießen.

    > Die Pumpe sollte immer mit einer konstanten Rate laufen, sodass sie jede Sekunde dieselbe Menge Wasser liefert.

1. Warten Sie, bis sich der Bodenfeuchtigkeitswert stabilisiert hat, und nehmen Sie eine Messung vor.

1. Wiederholen Sie dies mehrmals und erstellen Sie eine Tabelle mit den Ergebnissen. Ein Beispiel für diese Tabelle ist unten angegeben.

    | Gesamtzeit der Pumpe | Bodenfeuchtigkeit | Abnahme |
    | --- | --: | -: |
    | Trocken | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Berechnen Sie eine durchschnittliche Zunahme der Bodenfeuchtigkeit pro Sekunde Wasser. Im obigen Beispiel verringert jede Sekunde Wasser die Messung durchschnittlich um 20,3.

1. Verwenden Sie diese Daten, um die Effizienz Ihres Servercodes zu verbessern, indem Sie die Pumpe für die erforderliche Zeit laufen lassen, um die Bodenfeuchtigkeit auf das gewünschte Niveau zu bringen.

## Bewertungskriterien

| Kriterium | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| Erfassen von Bodenfeuchtigkeitsdaten | Kann mehrere Messungen nach dem Hinzufügen fester Wassermengen erfassen | Kann einige Messungen mit festen Wassermengen erfassen | Kann nur eine oder zwei Messungen erfassen oder ist nicht in der Lage, feste Wassermengen zu verwenden |
| Kalibrierung des Servercodes | Kann eine durchschnittliche Abnahme der Bodenfeuchtigkeitsmessung berechnen und den Servercode entsprechend aktualisieren | Kann eine durchschnittliche Abnahme berechnen, aber den Servercode nicht aktualisieren, oder ist nicht in der Lage, eine durchschnittliche Abnahme korrekt zu berechnen, verwendet diesen Wert jedoch, um den Servercode korrekt zu aktualisieren | Ist nicht in der Lage, eine durchschnittliche Abnahme zu berechnen oder den Servercode zu aktualisieren |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.