<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-25T21:12:33+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "de"
}
-->
# Baue einen Fruchtqualitätsdetektor

## Anweisungen

Baue den Fruchtqualitätsdetektor!

Nutze alles, was du bisher gelernt hast, und entwickle den Prototyp eines Fruchtqualitätsdetektors. Löse die Bildklassifikation basierend auf der Nähe aus, indem du ein KI-Modell am Edge ausführst, speichere die Ergebnisse der Klassifikation in einem Speicher und steuere eine LED basierend auf der Reife der Frucht.

Du solltest in der Lage sein, dies mithilfe des Codes zusammenzusetzen, den du in allen bisherigen Lektionen geschrieben hast.

## Bewertungskriterien

| Kriterien | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| Alle Dienste konfigurieren | War in der Lage, einen IoT Hub, eine Azure Functions-Anwendung und Azure Storage einzurichten | War in der Lage, den IoT Hub einzurichten, aber nicht die Azure Functions-Anwendung oder Azure Storage | War nicht in der Lage, irgendeinen IoT-Dienst einzurichten |
| Nähe überwachen und die Daten an den IoT Hub senden, wenn ein Objekt näher als eine vordefinierte Distanz ist, und die Kamera per Befehl auslösen | War in der Lage, die Distanz zu messen und eine Nachricht an den IoT Hub zu senden, wenn ein Objekt nah genug ist, und einen Befehl zu senden, um die Kamera auszulösen | War in der Lage, die Nähe zu messen und an den IoT Hub zu senden, aber nicht in der Lage, einen Befehl an die Kamera zu senden | War nicht in der Lage, die Distanz zu messen und eine Nachricht an den IoT Hub zu senden oder einen Befehl auszulösen |
| Ein Bild aufnehmen, klassifizieren und die Ergebnisse an den IoT Hub senden | War in der Lage, ein Bild aufzunehmen, es mit einem Edge-Gerät zu klassifizieren und die Ergebnisse an den IoT Hub zu senden | War in der Lage, das Bild zu klassifizieren, aber nicht mit einem Edge-Gerät, oder war nicht in der Lage, die Ergebnisse an den IoT Hub zu senden | War nicht in der Lage, ein Bild zu klassifizieren |
| Die LED je nach Klassifikationsergebnis mit einem Befehl an ein Gerät ein- oder ausschalten | War in der Lage, eine LED per Befehl einzuschalten, wenn die Frucht unreif war | War in der Lage, den Befehl an das Gerät zu senden, aber nicht die LED zu steuern | War nicht in der Lage, einen Befehl zu senden, um die LED zu steuern |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.