<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T21:27:20+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "tl"
}
-->
# I-visualize ang GDD Data gamit ang Jupyter Notebook

## Mga Instruksyon

Sa araling ito, nangolekta ka ng GDD data gamit ang isang IoT sensor. Upang makakuha ng maayos na GDD data, kailangan mong mangolekta ng data sa loob ng ilang araw. Upang matulungan kang i-visualize ang temperature data at kalkulahin ang GDD, maaari kang gumamit ng mga tool tulad ng [Jupyter Notebooks](https://jupyter.org) upang suriin ang data.

Magsimula sa pamamagitan ng pangongolekta ng data sa loob ng ilang araw. Kailangan mong tiyakin na ang iyong server code ay tumatakbo sa lahat ng oras na tumatakbo ang iyong IoT device, alinman sa pamamagitan ng pag-aayos ng iyong power management settings o paggamit ng isang bagay tulad ng [script na ito para panatilihing aktibo ang system](https://github.com/jaqsparow/keep-system-active).

Kapag mayroon ka nang temperature data, maaari mong gamitin ang Jupyter Notebook sa repo na ito upang i-visualize ito at kalkulahin ang GDD. Ang Jupyter notebooks ay naghalo ng code at mga instruksiyon sa mga bloke na tinatawag na *cells*, kadalasang code sa Python. Maaari mong basahin ang mga instruksiyon, pagkatapos ay patakbuhin ang bawat bloke ng code, isa-isa. Maaari mo ring i-edit ang code. Halimbawa, sa notebook na ito, maaari mong i-edit ang base temperature na ginagamit upang kalkulahin ang GDD para sa iyong halaman.

1. Gumawa ng folder na tinatawag na `gdd-calculation`

1. I-download ang [gdd.ipynb](./code-notebook/gdd.ipynb) na file at kopyahin ito sa folder na `gdd-calculation`.

1. Kopyahin ang `temperature.csv` na file na ginawa ng MQTT server.

1. Gumawa ng bagong Python virtual environment sa folder na `gdd-calculation`.

1. Mag-install ng ilang pip packages para sa Jupyter notebooks, kasama ang mga library na kailangan upang pamahalaan at i-plot ang data:

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

    Magsisimula ang Jupyter at bubuksan ang notebook sa iyong browser. Sundin ang mga instruksiyon sa notebook upang i-visualize ang mga sukat na temperatura, at kalkulahin ang growing degree days.

    ![Ang jupyter notebook](../../../../../translated_images/tl/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubric

| Pamantayan | Napakahusay | Katanggap-tanggap | Kailangan ng Pagpapabuti |
| ---------- | ----------- | ----------------- | ------------------------ |
| Pangongolekta ng data | Nakakolekta ng hindi bababa sa 2 kumpletong araw ng data | Nakakolekta ng hindi bababa sa 1 kumpletong araw ng data | Nakakolekta ng ilang data |
| Pagkalkula ng GDD | Matagumpay na napapatakbo ang notebook at nakalkula ang GDD | Matagumpay na napapatakbo ang notebook | Hindi napapatakbo ang notebook |

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.