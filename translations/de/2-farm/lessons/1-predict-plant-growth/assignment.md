<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-25T21:18:58+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "de"
}
-->
# Visualisiere GDD-Daten mit einem Jupyter Notebook

## Anleitung

In dieser Lektion hast du GDD-Daten mit einem IoT-Sensor gesammelt. Um gute GDD-Daten zu erhalten, musst du Daten über mehrere Tage hinweg sammeln. Um Temperaturdaten zu visualisieren und GDD zu berechnen, kannst du Tools wie [Jupyter Notebooks](https://jupyter.org) verwenden, um die Daten zu analysieren.

Beginne damit, Daten für einige Tage zu sammeln. Du musst sicherstellen, dass dein Servercode die ganze Zeit läuft, während dein IoT-Gerät aktiv ist. Dies kannst du entweder durch Anpassung der Energieverwaltungseinstellungen oder durch die Verwendung eines Skripts wie [dieses Python-Skript, das das System aktiv hält](https://github.com/jaqsparow/keep-system-active) erreichen.

Sobald du Temperaturdaten hast, kannst du das Jupyter Notebook in diesem Repository verwenden, um die Daten zu visualisieren und GDD zu berechnen. Jupyter Notebooks kombinieren Code und Anweisungen in Blöcken, die *Zellen* genannt werden, oft mit Code in Python. Du kannst die Anweisungen lesen und dann jeden Codeblock Schritt für Schritt ausführen. Du kannst den Code auch bearbeiten. In diesem Notebook kannst du beispielsweise die Basistemperatur ändern, die zur Berechnung der GDD für deine Pflanze verwendet wird.

1. Erstelle einen Ordner namens `gdd-calculation`.

1. Lade die Datei [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) herunter und kopiere sie in den Ordner `gdd-calculation`.

1. Kopiere die Datei `temperature.csv`, die vom MQTT-Server erstellt wurde.

1. Erstelle eine neue Python-Umgebung im Ordner `gdd-calculation`.

1. Installiere einige Pip-Pakete für Jupyter Notebooks sowie Bibliotheken, die benötigt werden, um die Daten zu verwalten und zu visualisieren:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Starte das Notebook in Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter wird gestartet und öffnet das Notebook in deinem Browser. Arbeite die Anweisungen im Notebook durch, um die gemessenen Temperaturen zu visualisieren und die Growing Degree Days zu berechnen.

    ![Das Jupyter Notebook](../../../../../translated_images/de/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Bewertungskriterien

| Kriterien | Hervorragend | Ausreichend | Verbesserungswürdig |
| --------- | ------------ | ----------- | ------------------- |
| Datenerfassung | Erfasse mindestens 2 vollständige Tage Daten | Erfasse mindestens 1 vollständigen Tag Daten | Erfasse einige Daten |
| GDD-Berechnung | Notebook erfolgreich ausführen und GDD berechnen | Notebook erfolgreich ausführen | Notebook nicht ausführbar |

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.