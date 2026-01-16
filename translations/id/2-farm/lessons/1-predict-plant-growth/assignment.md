<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T21:26:58+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "id"
}
-->
# Visualisasikan Data GDD Menggunakan Jupyter Notebook

## Instruksi

Dalam pelajaran ini, Anda telah mengumpulkan data GDD menggunakan sensor IoT. Untuk mendapatkan data GDD yang baik, Anda perlu mengumpulkan data selama beberapa hari. Untuk membantu memvisualisasikan data suhu dan menghitung GDD, Anda dapat menggunakan alat seperti [Jupyter Notebooks](https://jupyter.org) untuk menganalisis data tersebut.

Mulailah dengan mengumpulkan data selama beberapa hari. Anda perlu memastikan kode server Anda berjalan sepanjang waktu perangkat IoT Anda aktif, baik dengan menyesuaikan pengaturan manajemen daya Anda atau menjalankan sesuatu seperti [skrip Python untuk menjaga sistem tetap aktif ini](https://github.com/jaqsparow/keep-system-active).

Setelah Anda memiliki data suhu, Anda dapat menggunakan Jupyter Notebook dalam repositori ini untuk memvisualisasikannya dan menghitung GDD. Jupyter Notebook menggabungkan kode dan instruksi dalam blok yang disebut *cell*, sering kali menggunakan kode Python. Anda dapat membaca instruksi, lalu menjalankan setiap blok kode satu per satu. Anda juga dapat mengedit kode tersebut. Dalam notebook ini, misalnya, Anda dapat mengedit suhu dasar yang digunakan untuk menghitung GDD untuk tanaman Anda.

1. Buat folder bernama `gdd-calculation`

1. Unduh file [gdd.ipynb](./code-notebook/gdd.ipynb) dan salin ke dalam folder `gdd-calculation`.

1. Salin file `temperature.csv` yang dibuat oleh server MQTT

1. Buat lingkungan virtual Python baru di folder `gdd-calculation`.

1. Instal beberapa paket pip untuk Jupyter Notebook, bersama dengan pustaka yang diperlukan untuk mengelola dan memplot data:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Jalankan notebook di Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter akan mulai dan membuka notebook di browser Anda. Ikuti instruksi dalam notebook untuk memvisualisasikan suhu yang diukur, dan menghitung growing degree days.

    ![The jupyter notebook](../../../../../translated_images/id/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Mengumpulkan data | Mengumpulkan data lengkap setidaknya selama 2 hari | Mengumpulkan data lengkap setidaknya selama 1 hari | Mengumpulkan sebagian data |
| Menghitung GDD | Berhasil menjalankan notebook dan menghitung GDD | Berhasil menjalankan notebook | Tidak dapat menjalankan notebook |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.