<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T21:27:09+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "ms"
}
-->
# Visualisasikan data GDD menggunakan Jupyter Notebook

## Arahan

Dalam pelajaran ini, anda telah mengumpulkan data GDD menggunakan sensor IoT. Untuk mendapatkan data GDD yang baik, anda perlu mengumpulkan data untuk beberapa hari. Untuk membantu memvisualisasikan data suhu dan mengira GDD, anda boleh menggunakan alat seperti [Jupyter Notebooks](https://jupyter.org) untuk menganalisis data tersebut.

Mulakan dengan mengumpulkan data selama beberapa hari. Anda perlu memastikan kod pelayan anda berjalan sepanjang masa peranti IoT anda beroperasi, sama ada dengan menyesuaikan tetapan pengurusan kuasa anda atau menjalankan sesuatu seperti [skrip Python untuk memastikan sistem aktif ini](https://github.com/jaqsparow/keep-system-active).

Setelah anda mempunyai data suhu, anda boleh menggunakan Jupyter Notebook dalam repositori ini untuk memvisualisasikannya dan mengira GDD. Jupyter notebooks menggabungkan kod dan arahan dalam blok yang dipanggil *cells*, selalunya kod dalam Python. Anda boleh membaca arahan, kemudian menjalankan setiap blok kod satu per satu. Anda juga boleh mengedit kod tersebut. Dalam notebook ini, sebagai contoh, anda boleh mengedit suhu asas yang digunakan untuk mengira GDD bagi tanaman anda.

1. Cipta folder bernama `gdd-calculation`

1. Muat turun fail [gdd.ipynb](./code-notebook/gdd.ipynb) dan salin ke dalam folder `gdd-calculation`.

1. Salin fail `temperature.csv` yang dihasilkan oleh pelayan MQTT

1. Cipta persekitaran maya Python baharu dalam folder `gdd-calculation`.

1. Pasang beberapa pakej pip untuk Jupyter notebooks, bersama dengan perpustakaan yang diperlukan untuk mengurus dan memplot data:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Jalankan notebook dalam Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter akan dimulakan dan membuka notebook dalam pelayar anda. Ikuti arahan dalam notebook untuk memvisualisasikan suhu yang diukur, dan mengira growing degree days.

    ![The jupyter notebook](../../../../../translated_images/ms/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Pengumpulan data | Mengumpulkan sekurang-kurangnya 2 hari data lengkap | Mengumpulkan sekurang-kurangnya 1 hari data lengkap | Mengumpulkan sebahagian data |
| Pengiraan GDD | Berjaya menjalankan notebook dan mengira GDD | Berjaya menjalankan notebook | Tidak dapat menjalankan notebook |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.