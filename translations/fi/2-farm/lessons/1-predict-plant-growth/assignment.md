<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T21:04:29+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "fi"
}
-->
# Visualisoi GDD-dataa Jupyter Notebookilla

## Ohjeet

Tässä osiossa keräsit GDD-dataa IoT-sensorin avulla. Hyvän GDD-datan saamiseksi sinun tulee kerätä dataa useamman päivän ajalta. Lämpötiladatan visualisointiin ja GDD:n laskemiseen voit käyttää työkaluja, kuten [Jupyter Notebooks](https://jupyter.org), datan analysointiin.

Aloita keräämällä dataa muutaman päivän ajalta. Sinun tulee varmistaa, että palvelinkoodisi on käynnissä koko sen ajan, kun IoT-laitteesi on käynnissä. Tämä onnistuu esimerkiksi säätämällä virranhallinta-asetuksia tai käyttämällä [tällaista Python-skriptiä, joka pitää järjestelmän aktiivisena](https://github.com/jaqsparow/keep-system-active).

Kun sinulla on lämpötiladataa, voit käyttää tämän repositorion Jupyter Notebookia sen visualisointiin ja GDD:n laskemiseen. Jupyter Notebookit yhdistävät koodia ja ohjeita *soluiksi* kutsutuissa lohkoissa, usein Python-koodia. Voit lukea ohjeet ja ajaa koodilohkot yksi kerrallaan. Voit myös muokata koodia. Tässä notebookissa voit esimerkiksi muokata peruslämpötilaa, jota käytetään GDD:n laskemiseen kasvillesi.

1. Luo kansio nimeltä `gdd-calculation`

1. Lataa [gdd.ipynb](./code-notebook/gdd.ipynb) -tiedosto ja kopioi se `gdd-calculation`-kansioon.

1. Kopioi MQTT-palvelimen luoma `temperature.csv` -tiedosto

1. Luo uusi Python-virtuaaliympäristö `gdd-calculation`-kansioon.

1. Asenna pip-paketteja Jupyter Notebookeja varten sekä kirjastot datan hallintaan ja visualisointiin:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Aja notebook Jupyterissa:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter käynnistyy ja avaa notebookin selaimessasi. Käy läpi notebookin ohjeet visualisoidaksesi mitatut lämpötilat ja laskeaksesi kasvukauden astepäivät (GDD).

    ![Jupyter Notebook](../../../../../translated_images/fi/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Arviointikriteerit

| Kriteeri | Erinomainen | Riittävä | Parannettavaa |
| -------- | ----------- | -------- | ------------- |
| Datan kerääminen | Kerää vähintään 2 päivän täydet datat | Kerää vähintään 1 päivän täydet datat | Kerää jonkin verran dataa |
| GDD:n laskeminen | Ajaa notebookin onnistuneesti ja laskee GDD:n | Ajaa notebookin onnistuneesti | Ei pysty ajamaan notebookia |

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa tämän käännöksen käytöstä johtuvista väärinkäsityksistä tai virhetulkinnoista.