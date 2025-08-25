<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-25T20:57:38+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "de"
}
-->
# Reagieren auf Klassifikationsergebnisse

## Anweisungen

Ihr Gerät hat Bilder klassifiziert und verfügt über die Werte für die Vorhersagen. Ihr Gerät könnte diese Informationen nutzen, um etwas zu tun – es könnte sie an IoT Hub senden, damit andere Systeme sie verarbeiten, oder es könnte einen Aktuator wie eine LED steuern, die aufleuchtet, wenn die Frucht unreif ist.

Fügen Sie Ihrem Gerät Code hinzu, um auf eine von Ihnen gewählte Weise zu reagieren – entweder Daten an einen IoT Hub senden, einen Aktuator steuern oder beides kombinieren und Daten an einen IoT Hub senden, der mit serverlosem Code bestimmt, ob die Frucht reif ist oder nicht, und einen Befehl zurücksendet, um einen Aktuator zu steuern.

## Bewertungskriterien

| Kriterium | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| Reaktion auf Vorhersagen | War in der Lage, eine Reaktion auf Vorhersagen zu implementieren, die bei Vorhersagen mit demselben Wert konsistent funktioniert. | War in der Lage, eine Reaktion zu implementieren, die nicht von den Vorhersagen abhängt, wie z. B. das bloße Senden von Rohdaten an einen IoT Hub. | War nicht in der Lage, das Gerät so zu programmieren, dass es auf die Vorhersagen reagiert. |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.