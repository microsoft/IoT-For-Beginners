<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T22:50:25+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "da"
}
-->
# Visualiser GDD-data ved hjælp af en Jupyter Notebook

## Instruktioner

I denne lektion har du indsamlet GDD-data ved hjælp af en IoT-sensor. For at få gode GDD-data skal du indsamle data over flere dage. For at hjælpe med at visualisere temperaturdata og beregne GDD kan du bruge værktøjer som [Jupyter Notebooks](https://jupyter.org) til at analysere dataene.

Start med at indsamle data i et par dage. Du skal sikre dig, at din serverkode kører hele tiden, mens din IoT-enhed er aktiv, enten ved at justere dine strømstyringsindstillinger eller ved at køre noget som [denne Python-script til at holde systemet aktivt](https://github.com/jaqsparow/keep-system-active).

Når du har temperaturdata, kan du bruge Jupyter Notebook i dette repo til at visualisere dem og beregne GDD. Jupyter Notebooks blander kode og instruktioner i blokke kaldet *celler*, ofte kode i Python. Du kan læse instruktionerne og derefter køre hver kodeblok, blok for blok. Du kan også redigere koden. I denne notebook kan du for eksempel redigere basistemperaturen, der bruges til at beregne GDD for din plante.

1. Opret en mappe kaldet `gdd-calculation`

1. Download filen [gdd.ipynb](./code-notebook/gdd.ipynb) og kopier den ind i mappen `gdd-calculation`.

1. Kopier filen `temperature.csv`, der blev oprettet af MQTT-serveren.

1. Opret et nyt Python-virtuelt miljø i mappen `gdd-calculation`.

1. Installer nogle pip-pakker til Jupyter Notebooks sammen med biblioteker, der er nødvendige for at håndtere og plotte data:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Kør notebooken i Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter starter op og åbner notebooken i din browser. Arbejd dig igennem instruktionerne i notebooken for at visualisere de målte temperaturer og beregne vækstdage (GDD).

    ![Jupyter Notebook](../../../../../translated_images/da/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Vurderingskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Indsamling af data | Indsamler mindst 2 komplette dages data | Indsamler mindst 1 komplet dags data | Indsamler nogle data |
| Beregning af GDD | Kører notebooken med succes og beregner GDD | Kører notebooken med succes | Kan ikke køre notebooken |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.