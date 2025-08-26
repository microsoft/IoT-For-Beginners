<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-25T22:27:51+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "de"
}
-->
# Erstelle einen universellen Übersetzer

## Anweisungen

Ein universeller Übersetzer ist ein Gerät, das zwischen mehreren Sprachen übersetzen kann, sodass Menschen, die unterschiedliche Sprachen sprechen, miteinander kommunizieren können. Nutze das, was du in den letzten Lektionen gelernt hast, um einen universellen Übersetzer mit 2 IoT-Geräten zu erstellen.

> Wenn du keine 2 Geräte hast, folge den Schritten in den letzten Lektionen, um ein virtuelles IoT-Gerät als eines der IoT-Geräte einzurichten.

Du solltest ein Gerät für eine Sprache und das andere für eine andere Sprache konfigurieren. Jedes Gerät sollte Spracheingaben akzeptieren, diese in Text umwandeln, den Text über IoT Hub und eine Functions-App an das andere Gerät senden, ihn übersetzen und die übersetzte Sprache abspielen.

> 💁 Tipp: Wenn du die Sprache von einem Gerät zum anderen sendest, sende auch die Sprache mit, in der sie vorliegt, um die Übersetzung zu erleichtern. Du könntest sogar jedes Gerät zuerst über IoT Hub und eine Functions-App registrieren lassen, wobei die unterstützte Sprache in Azure Storage gespeichert wird. Anschließend könntest du eine Functions-App verwenden, um die Übersetzungen durchzuführen und den übersetzten Text an das IoT-Gerät zu senden.

## Bewertungskriterien

| Kriterium | Vorbildlich | Ausreichend | Verbesserungswürdig |
| --------- | ----------- | ----------- | -------------------- |
| Universellen Übersetzer erstellen | Hat es geschafft, einen universellen Übersetzer zu bauen, der Sprache, die von einem Gerät erkannt wird, in Sprache auf einem anderen Gerät in einer anderen Sprache umwandelt | Hat es geschafft, einige Komponenten zum Laufen zu bringen, wie z. B. die Spracherfassung oder die Übersetzung, konnte aber keine vollständige End-to-End-Lösung erstellen | War nicht in der Lage, funktionierende Teile eines universellen Übersetzers zu erstellen |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.