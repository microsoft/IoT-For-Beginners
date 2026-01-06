<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:45:12+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "ms"
}
-->
# Kira stok dari peranti IoT anda - Perkakasan IoT Maya dan Raspberry Pi

Gabungan ramalan dan kotak sempadan mereka boleh digunakan untuk mengira stok dalam imej.

## Paparkan kotak sempadan

Sebagai langkah penyahpepijatan yang berguna, anda bukan sahaja boleh mencetak kotak sempadan, tetapi juga melukisnya pada imej yang ditulis ke cakera apabila imej ditangkap.

### Tugasan - cetak kotak sempadan

1. Pastikan projek `stock-counter` dibuka dalam VS Code, dan persekitaran maya diaktifkan jika anda menggunakan peranti IoT maya.

1. Tukar pernyataan `print` dalam gelung `for` kepada yang berikut untuk mencetak kotak sempadan ke konsol:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Jalankan aplikasi dengan kamera menghala ke beberapa stok di rak. Kotak sempadan akan dicetak ke konsol, dengan nilai kiri, atas, lebar dan tinggi dari 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Tugasan - lukis kotak sempadan pada imej

1. Pakej Pip [Pillow](https://pypi.org/project/Pillow/) boleh digunakan untuk melukis pada imej. Pasang pakej ini dengan arahan berikut:

    ```sh
    pip3 install pillow
    ```

    Jika anda menggunakan peranti IoT maya, pastikan untuk menjalankan ini dari dalam persekitaran maya yang diaktifkan.

1. Tambahkan pernyataan import berikut di bahagian atas fail `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Ini mengimport kod yang diperlukan untuk mengedit imej.

1. Tambahkan kod berikut di akhir fail `app.py`:

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

    Kod ini membuka imej yang disimpan sebelum ini untuk diedit. Ia kemudian mengulangi ramalan untuk mendapatkan kotak sempadan, dan mengira koordinat kanan bawah menggunakan nilai kotak sempadan dari 0-1. Nilai-nilai ini kemudian ditukar kepada koordinat imej dengan mendarabkan dengan dimensi imej yang berkaitan. Sebagai contoh, jika nilai kiri adalah 0.5 pada imej yang lebarnya 600 piksel, ini akan menukarnya kepada 300 (0.5 x 600 = 300).

    Setiap kotak sempadan dilukis pada imej menggunakan garis merah. Akhirnya, imej yang telah diedit disimpan, menimpa imej asal.

1. Jalankan aplikasi dengan kamera menghala ke beberapa stok di rak. Anda akan melihat fail `image.jpg` dalam penjelajah VS Code, dan anda boleh memilihnya untuk melihat kotak sempadan.

    ![4 tin pes tomato dengan kotak sempadan di sekeliling setiap tin](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.ms.jpg)

## Kira stok

Dalam imej yang ditunjukkan di atas, kotak sempadan mempunyai sedikit pertindihan. Jika pertindihan ini jauh lebih besar, maka kotak sempadan mungkin menunjukkan objek yang sama. Untuk mengira objek dengan betul, anda perlu mengabaikan kotak dengan pertindihan yang ketara.

### Tugasan - kira stok dengan mengabaikan pertindihan

1. Pakej Pip [Shapely](https://pypi.org/project/Shapely/) boleh digunakan untuk mengira persilangan. Jika anda menggunakan Raspberry Pi, anda perlu memasang kebergantungan perpustakaan terlebih dahulu:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Pasang pakej Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Jika anda menggunakan peranti IoT maya, pastikan untuk menjalankan ini dari dalam persekitaran maya yang diaktifkan.

1. Tambahkan pernyataan import berikut di bahagian atas fail `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Ini mengimport kod yang diperlukan untuk mencipta poligon bagi mengira pertindihan.

1. Di atas kod yang melukis kotak sempadan, tambahkan kod berikut:

    ```python
    overlap_threshold = 0.20
    ```

    Ini mentakrifkan peratusan pertindihan yang dibenarkan sebelum kotak sempadan dianggap sebagai objek yang sama. 0.20 mentakrifkan pertindihan 20%.

1. Untuk mengira pertindihan menggunakan Shapely, kotak sempadan perlu ditukar menjadi poligon Shapely. Tambahkan fungsi berikut untuk melakukannya:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Ini mencipta poligon menggunakan kotak sempadan daripada ramalan.

1. Logik untuk menghapuskan objek yang bertindih melibatkan membandingkan semua kotak sempadan, dan jika mana-mana pasangan ramalan mempunyai kotak sempadan yang bertindih lebih daripada ambang, salah satu ramalan akan dipadamkan. Untuk membandingkan semua ramalan, anda membandingkan ramalan 1 dengan 2, 3, 4, dan seterusnya, kemudian 2 dengan 3, 4, dan seterusnya. Kod berikut melakukannya:

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

    Pertindihan dikira menggunakan kaedah `Polygon.intersection` Shapely yang mengembalikan poligon yang mempunyai pertindihan. Kawasan kemudian dikira daripada poligon ini. Ambang pertindihan ini bukan nilai mutlak, tetapi perlu menjadi peratusan daripada kotak sempadan, jadi kotak sempadan terkecil dicari, dan ambang pertindihan digunakan untuk mengira kawasan yang boleh bertindih tanpa melebihi ambang peratusan pertindihan kotak sempadan terkecil. Jika pertindihan melebihi ini, ramalan ditandakan untuk dipadamkan.

    Setelah ramalan ditandakan untuk dipadamkan, ia tidak perlu diperiksa lagi, jadi gelung dalaman keluar untuk memeriksa ramalan seterusnya. Anda tidak boleh memadamkan item daripada senarai semasa mengulanginya, jadi kotak sempadan yang bertindih lebih daripada ambang ditambahkan ke senarai `to_delete`, kemudian dipadamkan pada akhir.

    Akhirnya, kiraan stok dicetak ke konsol. Ini kemudian boleh dihantar ke perkhidmatan IoT untuk memberi amaran jika tahap stok rendah. Semua kod ini berada sebelum kotak sempadan dilukis, jadi anda akan melihat ramalan stok tanpa pertindihan pada imej yang dihasilkan.

    > 💁 Ini adalah cara yang sangat ringkas untuk menghapuskan pertindihan, hanya menghapuskan yang pertama dalam pasangan yang bertindih. Untuk kod pengeluaran, anda mungkin ingin menambah lebih banyak logik di sini, seperti mempertimbangkan pertindihan antara pelbagai objek, atau jika satu kotak sempadan terkandung dalam kotak sempadan lain.

1. Jalankan aplikasi dengan kamera menghala ke beberapa stok di rak. Output akan menunjukkan bilangan kotak sempadan tanpa pertindihan yang melebihi ambang. Cuba laraskan nilai `overlap_threshold` untuk melihat ramalan yang diabaikan.

> 💁 Anda boleh menemui kod ini dalam folder [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) atau [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Program pengira stok anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.