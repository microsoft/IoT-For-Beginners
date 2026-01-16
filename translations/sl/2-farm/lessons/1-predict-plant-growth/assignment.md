<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T15:13:39+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "sl"
}
-->
# Vizualizirajte podatke GDD z uporabo Jupyter Notebooka

## Navodila

V tej lekciji ste z IoT senzorjem zbrali podatke GDD. Da bi pridobili dobre podatke GDD, morate zbirati podatke več dni. Za pomoč pri vizualizaciji temperaturnih podatkov in izračunu GDD lahko uporabite orodja, kot je [Jupyter Notebooks](https://jupyter.org), za analizo podatkov.

Začnite z zbiranjem podatkov za nekaj dni. Poskrbeti morate, da bo vaša strežniška koda ves čas delovanja vaše IoT naprave aktivna, bodisi z nastavitvijo upravljanja porabe energije bodisi z zagonom nečesa, kot je [ta Python skripta za ohranjanje sistema aktivnega](https://github.com/jaqsparow/keep-system-active).

Ko imate temperaturne podatke, lahko uporabite Jupyter Notebook v tem repozitoriju za njihovo vizualizacijo in izračun GDD. Jupyter notebooki združujejo kodo in navodila v blokih, imenovanih *celice*, pogosto s kodo v Pythonu. Preberete lahko navodila in nato zaženete vsak blok kode, blok za blokom. Kodo lahko tudi urejate. V tem notebooku lahko na primer uredite osnovno temperaturo, uporabljeno za izračun GDD za vašo rastlino.

1. Ustvarite mapo z imenom `gdd-calculation`.

1. Prenesite datoteko [gdd.ipynb](./code-notebook/gdd.ipynb) in jo kopirajte v mapo `gdd-calculation`.

1. Kopirajte datoteko `temperature.csv`, ki jo je ustvaril MQTT strežnik.

1. Ustvarite novo virtualno okolje Python v mapi `gdd-calculation`.

1. Namestite nekaj pip paketov za Jupyter notebooke, skupaj z knjižnicami, potrebnimi za upravljanje in prikaz podatkov:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Zaženite notebook v Jupyterju:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter se bo zagnal in odprl notebook v vašem brskalniku. Sledite navodilom v notebooku za vizualizacijo izmerjenih temperatur in izračun rastnih stopinj dni (GDD).

    ![Jupyter notebook](../../../../../translated_images/sl/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrika

| Merila | Odlično | Zadostno | Potrebno izboljšanje |
| ------- | -------- | -------- | -------------------- |
| Zbiranje podatkov | Zberite vsaj 2 popolna dneva podatkov | Zberite vsaj 1 popoln dan podatkov | Zberite nekaj podatkov |
| Izračun GDD | Uspešno zaženite notebook in izračunajte GDD | Uspešno zaženite notebook | Ne morete zagnati notebooka |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni prevod s strani človeka. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.