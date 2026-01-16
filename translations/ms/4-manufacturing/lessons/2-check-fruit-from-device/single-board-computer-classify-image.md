<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T21:00:46+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "ms"
}
-->
# Klasifikasikan imej - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menghantar imej yang ditangkap oleh kamera ke perkhidmatan Custom Vision untuk mengklasifikasikannya.

## Hantar imej ke Custom Vision

Perkhidmatan Custom Vision mempunyai SDK Python yang boleh anda gunakan untuk mengklasifikasikan imej.

### Tugasan - hantar imej ke Custom Vision

1. Buka folder `fruit-quality-detector` dalam VS Code. Jika anda menggunakan peranti IoT maya, pastikan persekitaran maya berjalan di terminal.

1. SDK Python untuk menghantar imej ke Custom Vision tersedia sebagai pakej Pip. Pasang ia dengan arahan berikut:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Tambahkan pernyataan import berikut di bahagian atas fail `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Ini membawa masuk beberapa modul daripada perpustakaan Custom Vision, satu untuk pengesahan dengan prediction key, dan satu lagi untuk menyediakan kelas klien ramalan yang boleh memanggil Custom Vision.

1. Tambahkan kod berikut di penghujung fail:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Gantikan `<prediction_url>` dengan URL yang anda salin daripada dialog *Prediction URL* sebelum ini dalam pelajaran ini. Gantikan `<prediction key>` dengan prediction key yang anda salin daripada dialog yang sama.

1. Prediction URL yang disediakan oleh dialog *Prediction URL* direka untuk digunakan apabila memanggil REST endpoint secara langsung. SDK Python menggunakan bahagian-bahagian URL ini di tempat yang berbeza. Tambahkan kod berikut untuk memecahkan URL ini kepada bahagian-bahagian yang diperlukan:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Ini memecahkan URL, mengekstrak endpoint `https://<location>.api.cognitive.microsoft.com`, ID projek, dan nama iterasi yang diterbitkan.

1. Cipta objek predictor untuk melakukan ramalan dengan kod berikut:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` membungkus prediction key. Ini kemudian digunakan untuk mencipta objek klien ramalan yang menunjuk ke endpoint.

1. Hantar imej ke Custom Vision menggunakan kod berikut:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Ini mengembalikan imej ke permulaan, kemudian menghantarnya ke klien ramalan.

1. Akhir sekali, paparkan hasil dengan kod berikut:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ini akan mengulang semua ramalan yang telah dikembalikan dan memaparkannya di terminal. Kebarangkalian yang dikembalikan adalah nombor titik terapung dari 0-1, dengan 0 bermaksud 0% peluang untuk sepadan dengan tag, dan 1 bermaksud 100% peluang.

    > 💁 Pengelas imej akan mengembalikan peratusan untuk semua tag yang telah digunakan. Setiap tag akan mempunyai kebarangkalian bahawa imej sepadan dengan tag tersebut.

1. Jalankan kod anda, dengan kamera anda menghadap beberapa buah-buahan, atau set imej yang sesuai, atau buah-buahan yang kelihatan pada webcam anda jika menggunakan perkakasan IoT maya. Anda akan melihat output di konsol:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Anda akan dapat melihat imej yang diambil, dan nilai-nilai ini dalam tab **Predictions** di Custom Vision.

    ![Sebuah pisang dalam Custom Vision diramalkan matang pada 56.8% dan tidak matang pada 43.1%](../../../../../translated_images/ms/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Anda boleh menemui kod ini dalam folder [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) atau [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Program pengelas kualiti buah-buahan anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.