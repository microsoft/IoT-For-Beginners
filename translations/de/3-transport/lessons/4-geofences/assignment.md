<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T22:56:19+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "de"
}
-->
# Senden von Benachrichtigungen mit Twilio

## Anweisungen

Bisher haben Sie in Ihrem Code nur die Entfernung zum Geofence protokolliert. In dieser Aufgabe müssen Sie eine Benachrichtigung hinzufügen, entweder eine SMS oder eine E-Mail, wenn sich die GPS-Koordinaten innerhalb des Geofence befinden.

Azure Functions bietet viele Optionen für Bindungen, einschließlich zu Drittanbieterdiensten wie Twilio, einer Kommunikationsplattform.

* Registrieren Sie sich für ein kostenloses Konto auf [Twilio.com](https://www.twilio.com)
* Lesen Sie die Dokumentation zur Bindung von Azure Functions an Twilio SMS auf der [Microsoft-Dokumentationsseite zur Twilio-Bindung für Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lesen Sie die Dokumentation zur Bindung von Azure Functions an Twilio SendGrid, um E-Mails zu senden, auf der [Microsoft-Dokumentationsseite zu Azure Functions SendGrid-Bindungen](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Fügen Sie die Bindung zu Ihrer Functions-App hinzu, um bei GPS-Koordinaten entweder innerhalb oder außerhalb des Geofence benachrichtigt zu werden – aber nicht bei beiden.

## Bewertungskriterien

| Kriterium | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| Konfiguration der Functions-Bindungen und Empfang einer E-Mail oder SMS | War in der Lage, die Functions-Bindungen zu konfigurieren und eine E-Mail oder SMS zu erhalten, wenn sich die Koordinaten innerhalb oder außerhalb des Geofence befinden, aber nicht bei beiden | War in der Lage, die Bindungen zu konfigurieren, konnte jedoch keine E-Mail oder SMS senden, oder konnte nur senden, wenn sich die Koordinaten sowohl innerhalb als auch außerhalb des Geofence befanden | War nicht in der Lage, die Bindungen zu konfigurieren und eine E-Mail oder SMS zu senden |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.