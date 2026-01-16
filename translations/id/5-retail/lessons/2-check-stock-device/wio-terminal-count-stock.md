<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:43:44+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "id"
}
-->
# Hitung stok dari perangkat IoT Anda - Wio Terminal

Kombinasi prediksi dan kotak pembatas dapat digunakan untuk menghitung stok dalam sebuah gambar.

## Hitung stok

![4 kaleng pasta tomat dengan kotak pembatas di sekitar setiap kaleng](../../../../../translated_images/id/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Pada gambar di atas, kotak pembatas memiliki sedikit tumpang tindih. Jika tumpang tindih ini jauh lebih besar, maka kotak pembatas mungkin menunjukkan objek yang sama. Untuk menghitung objek dengan benar, Anda perlu mengabaikan kotak dengan tumpang tindih yang signifikan.

### Tugas - hitung stok dengan mengabaikan tumpang tindih

1. Buka proyek `stock-counter` Anda jika belum terbuka.

1. Di atas fungsi `processPredictions`, tambahkan kode berikut:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Ini mendefinisikan persentase tumpang tindih yang diizinkan sebelum kotak pembatas dianggap sebagai objek yang sama. 0.20 mendefinisikan tumpang tindih sebesar 20%.

1. Di bawah ini, dan di atas fungsi `processPredictions`, tambahkan kode berikut untuk menghitung tumpang tindih antara dua persegi panjang:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Kode ini mendefinisikan struct `Point` untuk menyimpan titik-titik pada gambar, dan struct `Rect` untuk mendefinisikan persegi panjang menggunakan koordinat kiri atas dan kanan bawah. Kemudian mendefinisikan fungsi `area` yang menghitung luas persegi panjang dari koordinat kiri atas dan kanan bawah.

    Selanjutnya, kode ini mendefinisikan fungsi `overlappingArea` yang menghitung luas tumpang tindih dari 2 persegi panjang. Jika tidak ada tumpang tindih, fungsi ini mengembalikan nilai 0.

1. Di bawah fungsi `overlappingArea`, deklarasikan fungsi untuk mengonversi kotak pembatas menjadi `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Fungsi ini mengambil prediksi dari pendeteksi objek, mengekstrak kotak pembatas, dan menggunakan nilai-nilai pada kotak pembatas untuk mendefinisikan persegi panjang. Sisi kanan dihitung dari sisi kiri ditambah lebar. Bagian bawah dihitung sebagai bagian atas ditambah tinggi.

1. Prediksi perlu dibandingkan satu sama lain, dan jika 2 prediksi memiliki tumpang tindih lebih dari ambang batas, salah satu dari mereka perlu dihapus. Ambang batas tumpang tindih adalah persentase, sehingga perlu dikalikan dengan ukuran kotak pembatas terkecil untuk memeriksa apakah tumpang tindih melebihi persentase tertentu dari kotak pembatas, bukan persentase tertentu dari seluruh gambar. Mulailah dengan menghapus konten fungsi `processPredictions`.

1. Tambahkan berikut ini ke fungsi `processPredictions` yang kosong:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Kode ini mendeklarasikan vektor untuk menyimpan prediksi yang tidak tumpang tindih. Kemudian kode ini melakukan iterasi melalui semua prediksi, membuat `Rect` dari kotak pembatas.

    Selanjutnya, kode ini melakukan iterasi melalui prediksi yang tersisa, dimulai dari prediksi setelah prediksi saat ini. Ini mencegah prediksi dibandingkan lebih dari sekali - setelah 1 dan 2 dibandingkan, tidak perlu membandingkan 2 dengan 1, hanya dengan 3, 4, dan seterusnya.

    Untuk setiap pasangan prediksi, luas tumpang tindih dihitung. Ini kemudian dibandingkan dengan luas kotak pembatas terkecil - jika tumpang tindih melebihi persentase ambang batas dari kotak pembatas terkecil, prediksi ditandai sebagai tidak lolos. Jika setelah membandingkan semua tumpang tindih, prediksi lolos pemeriksaan, prediksi tersebut ditambahkan ke koleksi `passed_predictions`.

    > 💁 Ini adalah cara yang sangat sederhana untuk menghapus tumpang tindih, hanya menghapus yang pertama dalam pasangan yang tumpang tindih. Untuk kode produksi, Anda mungkin ingin menambahkan lebih banyak logika di sini, seperti mempertimbangkan tumpang tindih antara beberapa objek, atau jika satu kotak pembatas berada di dalam kotak pembatas lainnya.

1. Setelah ini, tambahkan kode berikut untuk mengirimkan detail prediksi yang lolos ke monitor serial:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Kode ini melakukan iterasi melalui prediksi yang lolos dan mencetak detailnya ke monitor serial.

1. Di bawah ini, tambahkan kode untuk mencetak jumlah item yang dihitung ke monitor serial:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Ini kemudian dapat dikirim ke layanan IoT untuk memberikan peringatan jika tingkat stok rendah.

1. Unggah dan jalankan kode Anda. Arahkan kamera ke objek di rak dan tekan tombol C. Cobalah menyesuaikan nilai `overlap_threshold` untuk melihat prediksi yang diabaikan.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Program penghitung stok Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.