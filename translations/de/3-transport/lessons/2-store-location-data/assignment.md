<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T23:10:09+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "de"
}
-->
# Untersuchen von Funktionsbindungen

## Anweisungen

Funktionsbindungen ermöglichen es Ihrem Code, Blobs im Blob-Speicher zu speichern, indem sie aus der `main`-Funktion zurückgegeben werden. Das Azure Storage-Konto, die Sammlung und andere Details werden in der Datei `function.json` konfiguriert.

Wenn Sie mit Azure oder anderen Microsoft-Technologien arbeiten, ist die beste Informationsquelle [die Microsoft-Dokumentation auf docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). In dieser Aufgabe müssen Sie die Dokumentation zu Azure Functions-Bindungen lesen, um herauszufinden, wie die Ausgabe-Bindung eingerichtet wird.

Einige Seiten, die Sie sich ansehen können, um zu beginnen, sind:

* [Konzepte zu Azure Functions-Triggers und -Bindings](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Übersicht über Azure Blob Storage-Bindungen für Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob Storage-Ausgabe-Bindung für Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Bewertungskriterien

| Kriterium | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| Konfiguration der Blob Storage-Ausgabe-Bindung | Konnte die Ausgabe-Bindung konfigurieren, das Blob zurückgeben und erfolgreich im Blob-Speicher speichern | Konnte die Ausgabe-Bindung konfigurieren oder das Blob zurückgeben, war jedoch nicht in der Lage, es erfolgreich im Blob-Speicher zu speichern | Konnte die Ausgabe-Bindung nicht konfigurieren |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.