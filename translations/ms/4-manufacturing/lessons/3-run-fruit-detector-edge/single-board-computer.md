<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T22:56:11+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ms"
}
-->
# Klasifikasikan imej menggunakan pengklasifikasi imej berasaskan IoT Edge - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menggunakan Pengklasifikasi Imej yang berjalan pada peranti IoT Edge.

## Gunakan pengklasifikasi IoT Edge

Peranti IoT boleh diarahkan semula untuk menggunakan pengklasifikasi imej IoT Edge. URL untuk Pengklasifikasi Imej ialah `http://<IP address or name>/image`, menggantikan `<IP address or name>` dengan alamat IP atau nama hos komputer yang menjalankan IoT Edge.

Perpustakaan Python untuk Custom Vision hanya berfungsi dengan model yang dihoskan di awan, bukan model yang dihoskan di IoT Edge. Ini bermakna anda perlu menggunakan REST API untuk memanggil pengklasifikasi.

### Tugasan - gunakan pengklasifikasi IoT Edge

1. Buka projek `fruit-quality-detector` dalam VS Code jika ia belum dibuka. Jika anda menggunakan peranti IoT maya, pastikan persekitaran maya diaktifkan.

1. Buka fail `app.py`, dan keluarkan pernyataan import dari `azure.cognitiveservices.vision.customvision.prediction` dan `msrest.authentication`.

1. Tambahkan import berikut di bahagian atas fail:

    ```python
    import requests
    ```

1. Padamkan semua kod selepas imej disimpan ke fail, dari `image_file.write(image.read())` hingga ke akhir fail.

1. Tambahkan kod berikut di akhir fail:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Gantikan `<URL>` dengan URL untuk pengklasifikasi anda.

    Kod ini membuat permintaan REST POST kepada pengklasifikasi, menghantar imej sebagai badan permintaan. Hasilnya akan kembali dalam bentuk JSON, dan ini akan dinyahkod untuk mencetak kebarangkalian.

1. Jalankan kod anda, dengan kamera anda menghala ke beberapa buah-buahan, atau set imej yang sesuai, atau buah-buahan yang kelihatan pada webcam anda jika menggunakan perkakasan IoT maya. Anda akan melihat output di konsol:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) atau [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Program pengklasifikasi kualiti buah anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.