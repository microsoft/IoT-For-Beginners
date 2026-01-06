<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:44:52+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "id"
}
-->
# Hitung stok dari perangkat IoT Anda - Perangkat Keras IoT Virtual dan Raspberry Pi

Kombinasi prediksi dan kotak pembatas dapat digunakan untuk menghitung stok dalam sebuah gambar.

## Tampilkan kotak pembatas

Sebagai langkah debugging yang berguna, Anda tidak hanya dapat mencetak kotak pembatas, tetapi juga menggambarnya pada gambar yang disimpan ke disk saat gambar diambil.

### Tugas - cetak kotak pembatas

1. Pastikan proyek `stock-counter` terbuka di VS Code, dan lingkungan virtual diaktifkan jika Anda menggunakan perangkat IoT virtual.

1. Ubah pernyataan `print` dalam `for` loop menjadi berikut ini untuk mencetak kotak pembatas ke konsol:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Jalankan aplikasi dengan kamera mengarah ke beberapa stok di rak. Kotak pembatas akan dicetak ke konsol, dengan nilai kiri, atas, lebar, dan tinggi dari 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Tugas - gambar kotak pembatas pada gambar

1. Paket Pip [Pillow](https://pypi.org/project/Pillow/) dapat digunakan untuk menggambar pada gambar. Instal dengan perintah berikut:

    ```sh
    pip3 install pillow
    ```

    Jika Anda menggunakan perangkat IoT virtual, pastikan untuk menjalankan ini dari dalam lingkungan virtual yang diaktifkan.

1. Tambahkan pernyataan impor berikut ke bagian atas file `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Ini mengimpor kode yang diperlukan untuk mengedit gambar.

1. Tambahkan kode berikut ke akhir file `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Kode ini membuka gambar yang disimpan sebelumnya untuk diedit. Kemudian, kode ini melakukan loop melalui prediksi untuk mendapatkan kotak pembatas, dan menghitung koordinat kanan bawah menggunakan nilai kotak pembatas dari 0-1. Nilai-nilai ini kemudian dikonversi ke koordinat gambar dengan mengalikan dengan dimensi gambar yang relevan. Sebagai contoh, jika nilai kiri adalah 0.5 pada gambar yang lebarnya 600 piksel, ini akan dikonversi menjadi 300 (0.5 x 600 = 300).

    Setiap kotak pembatas digambar pada gambar menggunakan garis merah. Akhirnya, gambar yang telah diedit disimpan, menggantikan gambar asli.

1. Jalankan aplikasi dengan kamera mengarah ke beberapa stok di rak. Anda akan melihat file `image.jpg` di penjelajah VS Code, dan Anda dapat memilihnya untuk melihat kotak pembatas.

    ![4 kaleng pasta tomat dengan kotak pembatas di sekitar setiap kaleng](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.id.jpg)

## Hitung stok

Dalam gambar yang ditampilkan di atas, kotak pembatas memiliki sedikit tumpang tindih. Jika tumpang tindih ini jauh lebih besar, maka kotak pembatas mungkin menunjukkan objek yang sama. Untuk menghitung objek dengan benar, Anda perlu mengabaikan kotak dengan tumpang tindih yang signifikan.

### Tugas - hitung stok dengan mengabaikan tumpang tindih

1. Paket Pip [Shapely](https://pypi.org/project/Shapely/) dapat digunakan untuk menghitung interseksi. Jika Anda menggunakan Raspberry Pi, Anda perlu menginstal dependensi pustaka terlebih dahulu:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Instal paket Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Jika Anda menggunakan perangkat IoT virtual, pastikan untuk menjalankan ini dari dalam lingkungan virtual yang diaktifkan.

1. Tambahkan pernyataan impor berikut ke bagian atas file `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Ini mengimpor kode yang diperlukan untuk membuat poligon untuk menghitung tumpang tindih.

1. Di atas kode yang menggambar kotak pembatas, tambahkan kode berikut:

    ```python
    overlap_threshold = 0.20
    ```

    Ini mendefinisikan persentase tumpang tindih yang diizinkan sebelum kotak pembatas dianggap sebagai objek yang sama. 0.20 mendefinisikan tumpang tindih 20%.

1. Untuk menghitung tumpang tindih menggunakan Shapely, kotak pembatas perlu dikonversi menjadi poligon Shapely. Tambahkan fungsi berikut untuk melakukannya:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Fungsi ini membuat poligon menggunakan kotak pembatas dari sebuah prediksi.

1. Logika untuk menghapus objek yang tumpang tindih melibatkan membandingkan semua kotak pembatas, dan jika ada pasangan prediksi yang memiliki kotak pembatas yang tumpang tindih lebih dari ambang batas, salah satu prediksi dihapus. Untuk membandingkan semua prediksi, Anda membandingkan prediksi 1 dengan 2, 3, 4, dll., lalu 2 dengan 3, 4, dll. Kode berikut melakukan ini:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Tumpang tindih dihitung menggunakan metode Shapely `Polygon.intersection` yang mengembalikan poligon yang memiliki tumpang tindih. Luas kemudian dihitung dari poligon ini. Ambang batas tumpang tindih ini bukan nilai absolut, tetapi perlu menjadi persentase dari kotak pembatas, sehingga kotak pembatas terkecil ditemukan, dan ambang batas tumpang tindih digunakan untuk menghitung luas yang dapat dimiliki tumpang tindih agar tidak melebihi persentase ambang batas tumpang tindih dari kotak pembatas terkecil. Jika tumpang tindih melebihi ini, prediksi ditandai untuk dihapus.

    Setelah prediksi ditandai untuk dihapus, prediksi tersebut tidak perlu diperiksa lagi, sehingga loop bagian dalam berhenti untuk memeriksa prediksi berikutnya. Anda tidak dapat menghapus item dari daftar saat sedang melakukan iterasi, sehingga kotak pembatas yang tumpang tindih lebih dari ambang batas ditambahkan ke daftar `to_delete`, lalu dihapus di akhir.

    Akhirnya, jumlah stok dicetak ke konsol. Ini kemudian dapat dikirim ke layanan IoT untuk memberi peringatan jika tingkat stok rendah. Semua kode ini berada sebelum kotak pembatas digambar, sehingga Anda akan melihat prediksi stok tanpa tumpang tindih pada gambar yang dihasilkan.

    > 💁 Ini adalah cara yang sangat sederhana untuk menghapus tumpang tindih, hanya menghapus yang pertama dalam pasangan yang tumpang tindih. Untuk kode produksi, Anda mungkin ingin menambahkan lebih banyak logika di sini, seperti mempertimbangkan tumpang tindih antara beberapa objek, atau jika satu kotak pembatas berada di dalam kotak pembatas lainnya.

1. Jalankan aplikasi dengan kamera mengarah ke beberapa stok di rak. Output akan menunjukkan jumlah kotak pembatas tanpa tumpang tindih yang melebihi ambang batas. Cobalah menyesuaikan nilai `overlap_threshold` untuk melihat prediksi yang diabaikan.

> 💁 Anda dapat menemukan kode ini di folder [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) atau [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Program penghitung stok Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.