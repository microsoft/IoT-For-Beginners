<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T20:39:08+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "lt"
}
-->
# Vizualizuokite GDD duomenis naudodami Jupyter Notebook

## Instrukcijos

Šioje pamokoje jūs surinkote GDD duomenis naudodami IoT jutiklį. Norint gauti gerus GDD duomenis, reikia rinkti duomenis kelias dienas. Kad galėtumėte vizualizuoti temperatūros duomenis ir apskaičiuoti GDD, galite naudoti tokias priemones kaip [Jupyter Notebooks](https://jupyter.org), kad analizuotumėte duomenis.

Pradėkite rinkdami duomenis kelias dienas. Turite užtikrinti, kad jūsų serverio kodas veiktų visą laiką, kol veikia jūsų IoT įrenginys, arba koreguodami energijos valdymo nustatymus, arba paleisdami kažką panašaus į [šį Python skriptą, kuris palaiko sistemą aktyvią](https://github.com/jaqsparow/keep-system-active).

Kai turėsite temperatūros duomenis, galite naudoti Jupyter Notebook iš šio repo, kad juos vizualizuotumėte ir apskaičiuotumėte GDD. Jupyter Notebook sujungia kodą ir instrukcijas blokais, vadinamais *celėmis*, dažniausiai Python kodu. Galite perskaityti instrukcijas, tada vykdyti kiekvieną kodo bloką po vieną. Taip pat galite redaguoti kodą. Pavyzdžiui, šiame užrašų knygelėje galite redaguoti bazinę temperatūrą, naudojamą GDD skaičiavimui jūsų augalui.

1. Sukurkite aplanką pavadinimu `gdd-calculation`

1. Atsisiųskite [gdd.ipynb](./code-notebook/gdd.ipynb) failą ir nukopijuokite jį į aplanką `gdd-calculation`.

1. Nukopijuokite `temperature.csv` failą, sukurtą MQTT serverio.

1. Sukurkite naują Python virtualią aplinką aplanke `gdd-calculation`.

1. Įdiekite keletą pip paketų, skirtų Jupyter Notebook, kartu su bibliotekomis, reikalingomis duomenų valdymui ir vizualizavimui:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Paleiskite užrašų knygelę Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter paleis ir atidarys užrašų knygelę jūsų naršyklėje. Vykdykite užrašų knygelės instrukcijas, kad vizualizuotumėte išmatuotas temperatūras ir apskaičiuotumėte augimo laipsnių dienas.

    ![Jupyter užrašų knygelė](../../../../../translated_images/lt/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Vertinimo kriterijai

| Kriterijai | Puikiai | Pakankamai | Reikia patobulinimų |
| ---------- | ------- | ---------- | ------------------- |
| Duomenų rinkimas | Surinkti bent 2 pilnų dienų duomenys | Surinkti bent 1 pilnos dienos duomenys | Surinkti kai kurie duomenys |
| GDD skaičiavimas | Sėkmingai paleisti užrašų knygelę ir apskaičiuoti GDD | Sėkmingai paleisti užrašų knygelę | Nepavyko paleisti užrašų knygelės |

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.