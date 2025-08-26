<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-25T20:52:02+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "de"
}
-->
# Herstellung und Verarbeitung – IoT zur Verbesserung der Lebensmittelverarbeitung nutzen

Sobald Lebensmittel ein zentrales Lager oder eine Verarbeitungsanlage erreichen, werden sie nicht immer direkt an Supermärkte geliefert. Oft durchlaufen sie mehrere Verarbeitungsschritte, wie zum Beispiel die Sortierung nach Qualität. Dies war früher ein manueller Prozess – er begann auf dem Feld, wo Pflücker nur reife Früchte ernteten, und setzte sich in der Fabrik fort, wo die Früchte auf einem Förderband transportiert wurden und Mitarbeiter beschädigte oder verdorbene Früchte manuell aussortierten. Da ich selbst während der Schulzeit als Sommerjob Erdbeeren gepflückt und sortiert habe, kann ich bestätigen, dass dies kein angenehmer Job ist.

Moderne Systeme setzen zunehmend auf IoT zur Sortierung. Einige der frühesten Geräte, wie die Sortierer von [Weco](https://wecotek.com), verwenden optische Sensoren, um die Qualität von Produkten zu erkennen, und sortieren beispielsweise grüne Tomaten aus. Diese können direkt auf Erntemaschinen auf dem Feld oder in Verarbeitungsanlagen eingesetzt werden.

Mit Fortschritten in Künstlicher Intelligenz (KI) und Maschinellem Lernen (ML) können diese Maschinen immer leistungsfähiger werden. Sie nutzen ML-Modelle, die darauf trainiert sind, zwischen Früchten und Fremdkörpern wie Steinen, Erde oder Insekten zu unterscheiden. Diese Modelle können auch darauf trainiert werden, die Qualität der Früchte zu erkennen – nicht nur beschädigte Früchte, sondern auch frühe Anzeichen von Krankheiten oder anderen Problemen bei der Ernte.

> 🎓 Der Begriff *ML-Modell* bezieht sich auf das Ergebnis des Trainings von maschineller Lernsoftware mit einem Datensatz. Zum Beispiel kann man ein ML-Modell trainieren, um zwischen reifen und unreifen Tomaten zu unterscheiden, und das Modell dann auf neue Bilder anwenden, um festzustellen, ob die Tomaten reif sind oder nicht.

In diesen 4 Lektionen lernst du, wie man bildbasierte KI-Modelle trainiert, um die Qualität von Früchten zu erkennen, wie man diese auf einem IoT-Gerät verwendet und wie man sie am Edge ausführt – also direkt auf einem IoT-Gerät statt in der Cloud.

> 💁 Diese Lektionen nutzen einige Cloud-Ressourcen. Wenn du nicht alle Lektionen in diesem Projekt abschließt, stelle sicher, dass du [dein Projekt bereinigst](../clean-up.md).

## Themen

1. [Einen Fruchtqualitätsdetektor trainieren](./lessons/1-train-fruit-detector/README.md)
1. [Fruchtqualität von einem IoT-Gerät überprüfen](./lessons/2-check-fruit-from-device/README.md)
1. [Deinen Fruchtqualitätsdetektor am Edge ausführen](./lessons/3-run-fruit-detector-edge/README.md)
1. [Fruchtqualitätsprüfung durch einen Sensor auslösen](./lessons/4-trigger-fruit-detector/README.md)

## Credits

Alle Lektionen wurden mit ♥️ von [Jen Fox](https://github.com/jenfoxbot) und [Jim Bennett](https://GitHub.com/JimBobBennett) geschrieben.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.