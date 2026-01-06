<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:44:00+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ms"
}
-->
# Kira stok dari peranti IoT anda - Wio Terminal

Gabungan ramalan dan kotak sempadan mereka boleh digunakan untuk mengira stok dalam imej.

## Kira stok

![4 tin pes tomato dengan kotak sempadan di sekeliling setiap tin](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.ms.jpg)

Dalam imej yang ditunjukkan di atas, kotak sempadan mempunyai sedikit pertindihan. Jika pertindihan ini jauh lebih besar, maka kotak sempadan mungkin menunjukkan objek yang sama. Untuk mengira objek dengan betul, anda perlu mengabaikan kotak dengan pertindihan yang ketara.

### Tugasan - kira stok dengan mengabaikan pertindihan

1. Buka projek `stock-counter` anda jika ia belum dibuka.

1. Di atas fungsi `processPredictions`, tambahkan kod berikut:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Ini menentukan peratusan pertindihan yang dibenarkan sebelum kotak sempadan dianggap sebagai objek yang sama. 0.20 menentukan pertindihan sebanyak 20%.

1. Di bawah ini, dan di atas fungsi `processPredictions`, tambahkan kod berikut untuk mengira pertindihan antara dua segi empat:

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

    Kod ini mentakrifkan struktur `Point` untuk menyimpan titik pada imej, dan struktur `Rect` untuk mentakrifkan segi empat menggunakan koordinat atas kiri dan bawah kanan. Ia kemudian mentakrifkan fungsi `area` yang mengira kawasan segi empat daripada koordinat atas kiri dan bawah kanan.

    Seterusnya, ia mentakrifkan fungsi `overlappingArea` yang mengira kawasan pertindihan 2 segi empat. Jika mereka tidak bertindih, ia mengembalikan 0.

1. Di bawah fungsi `overlappingArea`, isytiharkan fungsi untuk menukar kotak sempadan kepada `Rect`:

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

    Ini mengambil ramalan daripada pengesan objek, mengekstrak kotak sempadan dan menggunakan nilai pada kotak sempadan untuk mentakrifkan segi empat. Bahagian kanan dikira daripada kiri ditambah lebar. Bahagian bawah dikira sebagai atas ditambah tinggi.

1. Ramalan perlu dibandingkan antara satu sama lain, dan jika 2 ramalan mempunyai pertindihan lebih daripada ambang, salah satu daripadanya perlu dipadamkan. Ambang pertindihan adalah peratusan, jadi perlu didarabkan dengan saiz kotak sempadan terkecil untuk memeriksa bahawa pertindihan melebihi peratusan yang diberikan daripada kotak sempadan, bukan peratusan yang diberikan daripada keseluruhan imej. Mulakan dengan memadamkan kandungan fungsi `processPredictions`.

1. Tambahkan yang berikut kepada fungsi `processPredictions` yang kosong:

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

    Kod ini mengisytiharkan vektor untuk menyimpan ramalan yang tidak bertindih. Ia kemudian melangkau semua ramalan, mencipta `Rect` daripada kotak sempadan.

    Seterusnya, kod ini melangkau ramalan yang tinggal, bermula dari satu selepas ramalan semasa. Ini menghentikan ramalan daripada dibandingkan lebih daripada sekali - setelah 1 dan 2 dibandingkan, tidak perlu membandingkan 2 dengan 1, hanya dengan 3, 4, dan sebagainya.

    Untuk setiap pasangan ramalan, kawasan pertindihan dikira. Ini kemudian dibandingkan dengan kawasan kotak sempadan terkecil - jika pertindihan melebihi peratusan ambang kotak sempadan terkecil, ramalan ditandakan sebagai tidak lulus. Jika selepas membandingkan semua pertindihan, ramalan lulus pemeriksaan, ia ditambahkan ke koleksi `passed_predictions`.

    > 💁 Ini adalah cara yang sangat mudah untuk menghapuskan pertindihan, hanya menghapuskan yang pertama dalam pasangan yang bertindih. Untuk kod pengeluaran, anda mungkin ingin meletakkan lebih banyak logik di sini, seperti mempertimbangkan pertindihan antara pelbagai objek, atau jika satu kotak sempadan terkandung oleh yang lain.

1. Selepas ini, tambahkan kod berikut untuk menghantar butiran ramalan yang lulus ke monitor serial:

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

    Kod ini melangkau ramalan yang lulus dan mencetak butiran mereka ke monitor serial.

1. Di bawah ini, tambahkan kod untuk mencetak bilangan item yang dikira ke monitor serial:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Ini kemudian boleh dihantar ke perkhidmatan IoT untuk memberi amaran jika tahap stok rendah.

1. Muat naik dan jalankan kod anda. Arahkan kamera ke objek di rak dan tekan butang C. Cuba laraskan nilai `overlap_threshold` untuk melihat ramalan yang diabaikan.

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

> 💁 Anda boleh menemui kod ini dalam folder [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Program pengira stok anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.