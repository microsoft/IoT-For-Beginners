<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-25T21:08:22+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "de"
}
-->
# Erstellen Sie eine virtuelle Maschine mit IoT Edge

In Azure können Sie eine virtuelle Maschine erstellen – einen Computer in der Cloud, den Sie nach Belieben konfigurieren und auf dem Sie Ihre eigene Software ausführen können.

> 💁 Weitere Informationen zu virtuellen Maschinen finden Sie auf der [Wikipedia-Seite zu virtuellen Maschinen](https://wikipedia.org/wiki/Virtual_machine).

## Aufgabe – Einrichten einer IoT Edge-VM

1. Führen Sie den folgenden Befehl aus, um eine VM zu erstellen, auf der Azure IoT Edge bereits vorinstalliert ist:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Ersetzen Sie `<vm_name>` durch einen Namen für diese virtuelle Maschine. Dieser muss weltweit eindeutig sein, daher sollten Sie etwas wie `fruit-quality-detector-vm-` mit Ihrem Namen oder einem anderen Wert am Ende verwenden.

    Ersetzen Sie `<username>` und `<password>` durch einen Benutzernamen und ein Passwort, mit denen Sie sich bei der VM anmelden können. Diese müssen relativ sicher sein, daher können Sie nicht admin/password verwenden.

    Ersetzen Sie `<connection_string>` durch die Verbindungszeichenfolge Ihres `fruit-quality-detector-edge` IoT Edge-Geräts.

    Dadurch wird eine VM erstellt, die als `DS1 v2` virtuelle Maschine konfiguriert ist. Diese Kategorien geben an, wie leistungsstark die Maschine ist und wie viel sie daher kostet. Diese VM verfügt über 1 CPU und 3,5 GB RAM.

    > 💰 Die aktuellen Preise für diese VMs finden Sie im [Azure Virtual Machine-Preishandbuch](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    Sobald die VM erstellt wurde, wird die IoT Edge-Laufzeit automatisch installiert und so konfiguriert, dass sie sich mit Ihrem IoT Hub als Ihr `fruit-quality-detector-edge` Gerät verbindet.

1. Sie benötigen entweder die IP-Adresse oder den DNS-Namen der VM, um den Bildklassifikator von dort aus aufzurufen. Führen Sie den folgenden Befehl aus, um diese zu erhalten:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Kopieren Sie entweder das Feld `PublicIps` oder das Feld `Fqdns`.

1. VMs kosten Geld. Zum Zeitpunkt der Erstellung dieses Dokuments kostet eine DS1-VM etwa 0,06 $ pro Stunde. Um die Kosten niedrig zu halten, sollten Sie die VM herunterfahren, wenn Sie sie nicht verwenden, und sie löschen, wenn Sie mit diesem Projekt fertig sind.

    Sie können Ihre VM so konfigurieren, dass sie zu einer bestimmten Zeit jeden Tag automatisch heruntergefahren wird. Das bedeutet, dass Sie, falls Sie vergessen, sie herunterzufahren, nicht für mehr Zeit als bis zum automatischen Herunterfahren abgerechnet werden. Verwenden Sie den folgenden Befehl, um dies einzustellen:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Ersetzen Sie `<vm_name>` durch den Namen Ihrer virtuellen Maschine.

    Ersetzen Sie `<shutdown_time_utc>` durch die UTC-Zeit, zu der die VM heruntergefahren werden soll, und verwenden Sie dabei 4 Ziffern im Format HHMM. Wenn Sie beispielsweise möchten, dass die VM um Mitternacht UTC heruntergefahren wird, setzen Sie dies auf `0000`. Für 19:30 Uhr an der Westküste der USA würden Sie `0230` verwenden (19:30 Uhr an der US-Westküste entspricht 2:30 Uhr UTC).

1. Ihr Bildklassifikator wird auf diesem Edge-Gerät ausgeführt und auf Port 80 (dem Standard-HTTP-Port) lauschen. Standardmäßig sind bei virtuellen Maschinen eingehende Ports blockiert, daher müssen Sie Port 80 aktivieren. Ports werden in Netzwerksicherheitsgruppen aktiviert, daher müssen Sie zuerst den Namen der Netzwerksicherheitsgruppe Ihrer VM kennen, den Sie mit dem folgenden Befehl herausfinden können:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Kopieren Sie den Wert des Feldes `Name`.

1. Führen Sie den folgenden Befehl aus, um eine Regel hinzuzufügen, die Port 80 in der Netzwerksicherheitsgruppe öffnet:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Ersetzen Sie `<nsg name>` durch den Namen der Netzwerksicherheitsgruppe aus dem vorherigen Schritt.

### Aufgabe – Verwalten Sie Ihre VM, um Kosten zu reduzieren

1. Wenn Sie Ihre VM nicht verwenden, sollten Sie sie herunterfahren. Verwenden Sie den folgenden Befehl, um die VM herunterzufahren:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Ersetzen Sie `<vm_name>` durch den Namen Ihrer virtuellen Maschine.

    > 💁 Es gibt einen Befehl `az vm stop`, der die VM stoppt, aber der Computer bleibt Ihnen zugewiesen, sodass Sie weiterhin zahlen, als ob sie noch laufen würde.

1. Um die VM neu zu starten, verwenden Sie den folgenden Befehl:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Ersetzen Sie `<vm_name>` durch den Namen Ihrer virtuellen Maschine.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.