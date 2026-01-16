<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T20:39:48+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "ms"
}
-->
# Panggil pengesan objek anda dari peranti IoT - Perkakasan IoT Maya dan Raspberry Pi

Setelah pengesan objek anda diterbitkan, ia boleh digunakan dari peranti IoT anda.

## Salin projek pengklasifikasi imej

Sebahagian besar pengesan stok anda adalah sama seperti pengklasifikasi imej yang anda cipta dalam pelajaran sebelumnya.

### Tugasan - salin projek pengklasifikasi imej

1. Buat folder bernama `stock-counter` sama ada di komputer anda jika anda menggunakan peranti IoT maya, atau di Raspberry Pi anda. Jika anda menggunakan peranti IoT maya pastikan anda menyediakan persekitaran maya.

1. Sediakan perkakasan kamera.

    * Jika anda menggunakan Raspberry Pi, anda perlu memasang PiCamera. Anda mungkin juga ingin menetapkan kamera dalam satu kedudukan tetap, contohnya, dengan menggantung kabel di atas kotak atau tin, atau melekatkan kamera pada kotak menggunakan pita dua muka.
    * Jika anda menggunakan peranti IoT maya, anda perlu memasang CounterFit dan CounterFit PyCamera shim. Jika anda akan menggunakan imej pegun, tangkap beberapa imej yang belum dilihat oleh pengesan objek anda. Jika anda akan menggunakan kamera web, pastikan ia diposisikan dengan cara yang dapat melihat stok yang anda sedang kesan.

1. Ulangi langkah dari [pelajaran 2 projek pembuatan](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) untuk menangkap imej dari kamera.

1. Ulangi langkah dari [pelajaran 2 projek pembuatan](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) untuk memanggil pengklasifikasi imej. Sebahagian besar kod ini akan digunakan semula untuk mengesan objek.

## Tukar kod daripada pengklasifikasi kepada pengesan imej

Kod yang anda gunakan untuk mengklasifikasi imej sangat mirip dengan kod untuk mengesan objek. Perbezaan utama adalah kaedah yang dipanggil pada Custom Vision SDK, dan hasil panggilan tersebut.

### Tugasan - tukar kod daripada pengklasifikasi kepada pengesan imej

1. Padamkan tiga baris kod yang mengklasifikasi imej dan memproses ramalan:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Padamkan tiga baris ini.

1. Tambahkan kod berikut untuk mengesan objek dalam imej:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Kod ini memanggil kaedah `detect_image` pada predictor untuk menjalankan pengesan objek. Ia kemudian mengumpulkan semua ramalan dengan kebarangkalian di atas ambang, mencetaknya ke konsol.

    Tidak seperti pengklasifikasi imej yang hanya mengembalikan satu hasil bagi setiap tag, pengesan objek akan mengembalikan pelbagai hasil, jadi mana-mana dengan kebarangkalian rendah perlu ditapis keluar.

1. Jalankan kod ini dan ia akan menangkap imej, menghantarnya ke pengesan objek, dan mencetak objek yang dikesan. Jika anda menggunakan peranti IoT maya, pastikan anda mempunyai imej yang sesuai ditetapkan dalam CounterFit, atau kamera web anda dipilih. Jika anda menggunakan Raspberry Pi, pastikan kamera anda menghala ke objek di rak.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Anda mungkin perlu menyesuaikan `threshold` kepada nilai yang sesuai untuk imej anda.

    Anda akan dapat melihat imej yang diambil, dan nilai-nilai ini dalam tab **Predictions** di Custom Vision.

    ![4 tin pes tomato di rak dengan ramalan untuk 4 pengesanan masing-masing 35.8%, 33.5%, 25.7% dan 16.6%](../../../../../translated_images/ms/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Anda boleh menemui kod ini dalam folder [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) atau [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Program pengesan stok anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.