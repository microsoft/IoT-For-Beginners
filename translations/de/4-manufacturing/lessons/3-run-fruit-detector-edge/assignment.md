<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-25T21:07:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "de"
}
-->
# Andere Dienste am Edge ausführen

## Anweisungen

Es sind nicht nur Bildklassifikatoren, die am Edge ausgeführt werden können. Alles, was in einem Container verpackt werden kann, kann auf einem IoT Edge-Gerät bereitgestellt werden. Serverlose Codeausführungen wie Azure Functions, beispielsweise die Trigger, die Sie in früheren Lektionen erstellt haben, können in Containern ausgeführt werden und somit auch auf IoT Edge.

Wählen Sie eine der vorherigen Lektionen aus und versuchen Sie, die Azure Functions-App in einem IoT Edge-Container auszuführen. Eine Anleitung, wie dies mit einem anderen Functions-App-Projekt durchgeführt werden kann, finden Sie im [Tutorial: Azure Functions als IoT Edge-Module bereitstellen auf Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Bewertungskriterien

| Kriterium | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| Eine Azure Functions-App auf IoT Edge bereitstellen | Konnte eine Azure Functions-App auf IoT Edge bereitstellen und sie mit einem IoT-Gerät verwenden, um einen Trigger aus IoT-Daten auszulösen | Konnte eine Functions-App auf IoT Edge bereitstellen, aber der Trigger wurde nicht ausgelöst | Konnte keine Functions-App auf IoT Edge bereitstellen |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.