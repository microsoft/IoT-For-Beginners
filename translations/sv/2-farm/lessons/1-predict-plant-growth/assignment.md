<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T22:50:13+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "sv"
}
-->
# Visualisera GDD-data med hjälp av en Jupyter Notebook

## Instruktioner

I den här lektionen samlade du in GDD-data med hjälp av en IoT-sensor. För att få bra GDD-data behöver du samla in data under flera dagar. För att visualisera temperaturdata och beräkna GDD kan du använda verktyg som [Jupyter Notebooks](https://jupyter.org) för att analysera datan.

Börja med att samla in data under några dagar. Du måste se till att din serverkod körs hela tiden medan din IoT-enhet är aktiv, antingen genom att justera dina energihanteringsinställningar eller genom att köra något som [detta Python-skript för att hålla systemet aktivt](https://github.com/jaqsparow/keep-system-active).

När du har temperaturdata kan du använda Jupyter Notebook i detta repo för att visualisera datan och beräkna GDD. Jupyter notebooks kombinerar kod och instruktioner i block som kallas *celler*, ofta med kod i Python. Du kan läsa instruktionerna och sedan köra varje kodblock, ett i taget. Du kan också redigera koden. I den här notebooken kan du till exempel ändra bastemperaturen som används för att beräkna GDD för din växt.

1. Skapa en mapp som heter `gdd-calculation`

1. Ladda ner filen [gdd.ipynb](./code-notebook/gdd.ipynb) och kopiera den till mappen `gdd-calculation`.

1. Kopiera filen `temperature.csv` som skapades av MQTT-servern.

1. Skapa en ny Python-virtuell miljö i mappen `gdd-calculation`.

1. Installera några pip-paket för Jupyter notebooks, tillsammans med bibliotek som behövs för att hantera och visualisera datan:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Kör notebooken i Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter kommer att starta och öppna notebooken i din webbläsare. Följ instruktionerna i notebooken för att visualisera de uppmätta temperaturerna och beräkna växtens tillväxtgrader (GDD).

    ![Jupyter-notebooken](../../../../../translated_images/sv/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Samla in data | Samla in data för minst 2 hela dagar | Samla in data för minst 1 hel dag | Samla in viss data |
| Beräkna GDD | Kör notebooken framgångsrikt och beräkna GDD | Kör notebooken framgångsrikt | Kan inte köra notebooken |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.