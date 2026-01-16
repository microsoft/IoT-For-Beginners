<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-26T06:42:40+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "pl"
}
-->
# Wizualizacja danych GDD za pomocą Jupyter Notebook

## Instrukcje

W tej lekcji zebrałeś dane GDD za pomocą czujnika IoT. Aby uzyskać dobre dane GDD, musisz zbierać dane przez kilka dni. Aby pomóc w wizualizacji danych dotyczących temperatury i obliczaniu GDD, możesz użyć narzędzi takich jak [Jupyter Notebooks](https://jupyter.org) do analizy danych.

Zacznij od zbierania danych przez kilka dni. Musisz upewnić się, że kod serwera działa przez cały czas, gdy Twoje urządzenie IoT jest aktywne, albo dostosowując ustawienia zarządzania energią, albo uruchamiając coś w rodzaju [tego skryptu Python, który utrzymuje system aktywny](https://github.com/jaqsparow/keep-system-active).

Gdy już masz dane dotyczące temperatury, możesz użyć Jupyter Notebook z tego repozytorium, aby je zwizualizować i obliczyć GDD. Jupyter Notebooks łączą kod i instrukcje w blokach zwanych *komórkami*, często z kodem w Pythonie. Możesz przeczytać instrukcje, a następnie uruchamiać każdy blok kodu, blok po bloku. Możesz także edytować kod. W tym notatniku, na przykład, możesz zmienić temperaturę bazową używaną do obliczania GDD dla Twojej rośliny.

1. Utwórz folder o nazwie `gdd-calculation`.

1. Pobierz plik [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) i skopiuj go do folderu `gdd-calculation`.

1. Skopiuj plik `temperature.csv` utworzony przez serwer MQTT.

1. Utwórz nowe wirtualne środowisko Pythona w folderze `gdd-calculation`.

1. Zainstaluj kilka pakietów pip dla Jupyter Notebooks oraz biblioteki potrzebne do zarządzania i wizualizacji danych:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Uruchom notatnik w Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter uruchomi się i otworzy notatnik w Twojej przeglądarce. Pracuj zgodnie z instrukcjami w notatniku, aby zwizualizować zmierzone temperatury i obliczyć dni stopni wzrostu (GDD).

    ![Notatnik Jupyter](../../../../../translated_images/pl/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Kryteria oceny

| Kryterium | Wzorowe | Zadowalające | Wymaga poprawy |
| --------- | -------- | ------------ | -------------- |
| Zbieranie danych | Zebrano dane z co najmniej 2 pełnych dni | Zebrano dane z co najmniej 1 pełnego dnia | Zebrano część danych |
| Obliczanie GDD | Pomyślnie uruchomiono notatnik i obliczono GDD | Pomyślnie uruchomiono notatnik | Nie udało się uruchomić notatnika |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.