<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-25T20:40:14+00:00",
  "source_file": "clean-up.md",
  "language_code": "de"
}
-->
# Bereinigen Sie Ihr Projekt

Nachdem Sie jedes Projekt abgeschlossen haben, ist es sinnvoll, Ihre Cloud-Ressourcen zu löschen.

In den Lektionen zu jedem Projekt haben Sie möglicherweise einige der folgenden Ressourcen erstellt:

* Eine Ressourcengruppe
* Ein IoT Hub
* IoT-Geräteregistrierungen
* Ein Speicherkonto
* Eine Functions-App
* Ein Azure Maps-Konto
* Ein Custom Vision-Projekt
* Ein Azure Container Registry
* Eine Cognitive Services-Ressource

Die meisten dieser Ressourcen verursachen keine Kosten – entweder sind sie komplett kostenlos oder Sie nutzen eine kostenlose Stufe. Für Dienste, die eine kostenpflichtige Stufe erfordern, haben Sie diese auf einem Niveau genutzt, das in der kostenlosen Nutzung enthalten ist, oder sie kosten nur ein paar Cent.

Auch bei den relativ niedrigen Kosten lohnt es sich, diese Ressourcen zu löschen, wenn Sie fertig sind. Sie können beispielsweise nur einen IoT Hub mit der kostenlosen Stufe haben. Wenn Sie einen weiteren erstellen möchten, müssen Sie eine kostenpflichtige Stufe verwenden.

Alle Ihre Dienste wurden innerhalb von Ressourcengruppen erstellt, was die Verwaltung erleichtert. Sie können die Ressourcengruppe löschen, und alle Dienste in dieser Ressourcengruppe werden ebenfalls gelöscht.

Um die Ressourcengruppe zu löschen, führen Sie den folgenden Befehl in Ihrem Terminal oder Ihrer Eingabeaufforderung aus:

```sh
az group delete --name <resource-group-name>
```

Ersetzen Sie `<resource-group-name>` durch den Namen der Ressourcengruppe, die Sie löschen möchten.

Es erscheint eine Bestätigung:

```output
Are you sure you want to perform this operation? (y/n): 
```

Geben Sie `y` ein, um die Ressourcengruppe zu bestätigen und zu löschen.

Es wird eine Weile dauern, bis alle Dienste gelöscht sind.

> 💁 Weitere Informationen zum Löschen von Ressourcengruppen finden Sie in der [Dokumentation zur Ressourcengruppen- und Ressourcenlöschung im Azure Resource Manager auf Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.