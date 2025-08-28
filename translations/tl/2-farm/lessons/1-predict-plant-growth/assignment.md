<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T01:46:03+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "tl"
}
-->
# Ipakita ang GDD data gamit ang Jupyter Notebook

## Mga Instruksyon

Sa araling ito, nangolekta ka ng GDD data gamit ang isang IoT sensor. Para makakuha ng maayos na GDD data, kailangan mong mangolekta ng data sa loob ng ilang araw. Para matulungan kang makita ang temperatura at kalkulahin ang GDD, maaari kang gumamit ng mga tool tulad ng [Jupyter Notebooks](https://jupyter.org) para suriin ang data.

Simulan sa pangongolekta ng data sa loob ng ilang araw. Kailangan mong tiyakin na ang iyong server code ay tumatakbo sa lahat ng oras na ang IoT device mo ay gumagana, alinman sa pamamagitan ng pag-aayos ng iyong power management settings o paggamit ng isang bagay tulad ng [Python script na ito para panatilihing aktibo ang sistema](https://github.com/jaqsparow/keep-system-active).

Kapag mayroon ka nang temperature data, maaari mong gamitin ang Jupyter Notebook sa repo na ito para ipakita ito at kalkulahin ang GDD. Ang Jupyter notebooks ay pinagsasama ang code at mga instruksiyon sa mga bloke na tinatawag na *cells*, kadalasang code sa Python. Maaari mong basahin ang mga instruksiyon, pagkatapos ay patakbuhin ang bawat bloke ng code, isa-isa. Maaari mo ring i-edit ang code. Sa notebook na ito halimbawa, maaari mong i-edit ang base temperature na ginagamit para kalkulahin ang GDD para sa iyong halaman.

1. Gumawa ng folder na tinatawag na `gdd-calculation`

1. I-download ang [gdd.ipynb](./code-notebook/gdd.ipynb) file at kopyahin ito sa `gdd-calculation` folder.

1. Kopyahin ang `temperature.csv` file na ginawa ng MQTT server

1. Gumawa ng bagong Python virtual environment sa `gdd-calculation` folder.

1. Mag-install ng ilang pip packages para sa Jupyter notebooks, kasama ang mga library na kailangan para pamahalaan at ipakita ang data:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Patakbuhin ang notebook sa Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Magsisimula ang Jupyter at bubuksan ang notebook sa iyong browser. Sundan ang mga instruksiyon sa notebook para ipakita ang mga sukat na temperatura, at kalkulahin ang growing degree days.

    ![Ang jupyter notebook](../../../../../translated_images/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.tl.png)

## Rubric

| Pamantayan | Napakahusay | Katamtaman | Kailangan ng Pagpapabuti |
| ---------- | ----------- | ---------- | ------------------------ |
| Pangongolekta ng data | Nakakolekta ng hindi bababa sa 2 kumpletong araw ng data | Nakakolekta ng hindi bababa sa 1 kumpletong araw ng data | Nakakolekta ng ilang data |
| Pagkalkula ng GDD | Matagumpay na napatakbo ang notebook at nakalkula ang GDD | Matagumpay na napatakbo ang notebook | Hindi napatakbo ang notebook |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.