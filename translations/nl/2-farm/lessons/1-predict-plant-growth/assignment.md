<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T21:04:40+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "nl"
}
-->
# Visualiseer GDD-gegevens met een Jupyter Notebook

## Instructies

In deze les heb je GDD-gegevens verzameld met een IoT-sensor. Om goede GDD-gegevens te verkrijgen, moet je gegevens verzamelen over meerdere dagen. Om temperatuurgegevens te visualiseren en GDD te berekenen, kun je tools zoals [Jupyter Notebooks](https://jupyter.org) gebruiken om de gegevens te analyseren.

Begin met het verzamelen van gegevens over een paar dagen. Je moet ervoor zorgen dat je servercode continu draait terwijl je IoT-apparaat actief is, door bijvoorbeeld je energiebeheerinstellingen aan te passen of iets te gebruiken zoals [dit Python-script om het systeem actief te houden](https://github.com/jaqsparow/keep-system-active).

Zodra je temperatuurgegevens hebt, kun je het Jupyter Notebook in deze repository gebruiken om ze te visualiseren en GDD te berekenen. Jupyter Notebooks combineren code en instructies in blokken die *cells* worden genoemd, vaak met code in Python. Je kunt de instructies lezen en vervolgens elk codeblok één voor één uitvoeren. Je kunt de code ook aanpassen. In dit notebook kun je bijvoorbeeld de basistemperatuur aanpassen die wordt gebruikt om de GDD voor jouw plant te berekenen.

1. Maak een map genaamd `gdd-calculation`

1. Download het bestand [gdd.ipynb](./code-notebook/gdd.ipynb) en kopieer het naar de map `gdd-calculation`.

1. Kopieer het bestand `temperature.csv` dat is aangemaakt door de MQTT-server.

1. Maak een nieuwe Python virtuele omgeving in de map `gdd-calculation`.

1. Installeer enkele pip-pakketten voor Jupyter Notebooks, samen met bibliotheken die nodig zijn om de gegevens te beheren en te plotten:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Start het notebook in Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter zal starten en het notebook openen in je browser. Doorloop de instructies in het notebook om de gemeten temperaturen te visualiseren en de groeigraaddagen te berekenen.

    ![Het Jupyter Notebook](../../../../../translated_images/nl/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubriek

| Criteria | Uitmuntend | Voldoende | Verbetering nodig |
| -------- | ---------- | --------- | ----------------- |
| Gegevens verzamelen | Verzamel minstens 2 volledige dagen aan gegevens | Verzamel minstens 1 volledige dag aan gegevens | Verzamel enkele gegevens |
| GDD berekenen | Voer het notebook succesvol uit en bereken GDD | Voer het notebook succesvol uit | Niet in staat om het notebook uit te voeren |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.