<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T22:50:35+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "no"
}
-->
# Visualiser GDD-data ved bruk av en Jupyter Notebook

## Instruksjoner

I denne leksjonen samlet du inn GDD-data ved hjelp av en IoT-sensor. For å få gode GDD-data, må du samle inn data over flere dager. For å hjelpe deg med å visualisere temperaturdata og beregne GDD, kan du bruke verktøy som [Jupyter Notebooks](https://jupyter.org) til å analysere dataene.

Start med å samle inn data over noen dager. Du må sørge for at serverkoden din kjører hele tiden mens IoT-enheten din er aktiv, enten ved å justere innstillingene for strømstyring eller ved å kjøre noe som [denne Python-skriptet for å holde systemet aktivt](https://github.com/jaqsparow/keep-system-active).

Når du har temperaturdata, kan du bruke Jupyter Notebook i dette repoet til å visualisere dem og beregne GDD. Jupyter Notebooks kombinerer kode og instruksjoner i blokker kalt *celler*, ofte med kode skrevet i Python. Du kan lese instruksjonene og deretter kjøre hver kodeblokk, blokk for blokk. Du kan også redigere koden. I denne notebooken kan du for eksempel endre basistemperaturen som brukes til å beregne GDD for planten din.

1. Opprett en mappe kalt `gdd-calculation`

1. Last ned [gdd.ipynb](./code-notebook/gdd.ipynb)-filen og kopier den inn i `gdd-calculation`-mappen.

1. Kopier `temperature.csv`-filen som ble opprettet av MQTT-serveren.

1. Opprett et nytt Python-virtuelt miljø i `gdd-calculation`-mappen.

1. Installer noen pip-pakker for Jupyter Notebooks, sammen med biblioteker som trengs for å håndtere og visualisere dataene:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Kjør notebooken i Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter vil starte opp og åpne notebooken i nettleseren din. Arbeid deg gjennom instruksjonene i notebooken for å visualisere de målte temperaturene og beregne vekstgrad-dagene.

    ![Jupyter-notebooken](../../../../../translated_images/no/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Samle inn data | Samle inn minst 2 komplette dager med data | Samle inn minst 1 komplett dag med data | Samle inn noe data |
| Beregne GDD | Kjøre notebooken og beregne GDD med suksess | Kjøre notebooken med suksess | Ikke i stand til å kjøre notebooken |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.