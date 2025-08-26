<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-25T21:34:06+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "de"
}
-->
# Manuelle Relaissteuerung hinzufügen

## Anweisungen

Serverlose Codeausführung kann durch viele verschiedene Ereignisse ausgelöst werden, einschließlich HTTP-Anfragen. Sie können HTTP-Trigger verwenden, um eine manuelle Steuerung für Ihr Relais hinzuzufügen, sodass jemand das Relais über eine Webanfrage ein- oder ausschalten kann.

Für diese Aufgabe müssen Sie zwei HTTP-Trigger zu Ihrer Functions App hinzufügen, um das Relais ein- und auszuschalten. Nutzen Sie dabei das Gelernte aus dieser Lektion, um Befehle an das Gerät zu senden.

Einige Hinweise:

* Sie können einen HTTP-Trigger zu Ihrer bestehenden Functions App mit folgendem Befehl hinzufügen:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Ersetzen Sie `<trigger name>` durch den Namen Ihres HTTP-Triggers. Verwenden Sie beispielsweise `relay_on` und `relay_off`.

* HTTP-Trigger können Zugriffskontrollen haben. Standardmäßig erfordern sie einen funktionsspezifischen API-Schlüssel, der mit der URL übergeben werden muss, um ausgeführt zu werden. Für diese Aufgabe können Sie diese Einschränkung entfernen, sodass jeder die Funktion ausführen kann. Ändern Sie dazu die Einstellung `authLevel` in der Datei `function.json` für die HTTP-Trigger wie folgt:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Weitere Informationen zu dieser Zugriffskontrolle finden Sie in der [Dokumentation zu Funktionszugriffsschlüsseln](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-Trigger unterstützen standardmäßig GET- und POST-Anfragen. Das bedeutet, dass Sie sie mit Ihrem Webbrowser aufrufen können – Webbrowser führen GET-Anfragen aus.

    Wenn Sie Ihre Functions App lokal ausführen, sehen Sie die URL des Triggers:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Fügen Sie die URL in Ihren Browser ein und drücken Sie `Return`, oder `Strg+Klick` (`Cmd+Klick` auf macOS) auf den Link im Terminalfenster in VS Code, um ihn in Ihrem Standardbrowser zu öffnen. Dadurch wird der Trigger ausgeführt.

    > 💁 Beachten Sie, dass die URL `/api` enthält – HTTP-Trigger befinden sich standardmäßig in der Subdomain `api`.

* Wenn Sie die Functions App bereitstellen, lautet die URL des HTTP-Triggers:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Dabei ist `<functions app name>` der Name Ihrer Functions App und `<trigger name>` der Name Ihres Triggers.

## Bewertungskriterien

| Kriterien | Vorbildlich | Angemessen | Verbesserungswürdig |
| --------- | ----------- | ---------- | -------------------- |
| HTTP-Trigger erstellen | Zwei Trigger erstellt, um das Relais ein- und auszuschalten, mit passenden Namen | Einen Trigger mit passendem Namen erstellt | Keine Trigger erstellt |
| Relais über HTTP-Trigger steuern | Beide Trigger erfolgreich mit IoT Hub verbunden und Relais korrekt gesteuert | Einen Trigger erfolgreich mit IoT Hub verbunden und Relais korrekt gesteuert | Trigger konnten nicht mit IoT Hub verbunden werden |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.