<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T23:05:35+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "ms"
}
-->
# Fahami Bahasa

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.ms.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

## Kuiz Pra-Kuliah

[Kuiz Pra-Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Pengenalan

Dalam pelajaran sebelum ini, anda telah menukar ucapan kepada teks. Untuk menggunakan ini dalam memprogramkan pemasa pintar, kod anda perlu memahami apa yang telah dikatakan. Anda mungkin mengandaikan pengguna akan menyebut frasa tetap, seperti "Set a 3 minute timer", dan menganalisis ungkapan itu untuk mendapatkan tempoh pemasa, tetapi ini tidak mesra pengguna. Jika pengguna berkata "Set a timer for 3 minutes", anda atau saya akan memahami maksudnya, tetapi kod anda tidak akan, kerana ia menjangkakan frasa tetap.

Di sinilah pemahaman bahasa memainkan peranan, menggunakan model AI untuk mentafsir teks dan mengembalikan butiran yang diperlukan, contohnya dapat memahami kedua-dua "Set a 3 minute timer" dan "Set a timer for 3 minutes", dan mengetahui bahawa pemasa diperlukan selama 3 minit.

Dalam pelajaran ini, anda akan mempelajari tentang model pemahaman bahasa, cara menciptanya, melatihnya, dan menggunakannya dalam kod anda.

Dalam pelajaran ini, kita akan membincangkan:

* [Pemahaman bahasa](../../../../../6-consumer/lessons/2-language-understanding)
* [Cipta model pemahaman bahasa](../../../../../6-consumer/lessons/2-language-understanding)
* [Niat dan entiti](../../../../../6-consumer/lessons/2-language-understanding)
* [Gunakan model pemahaman bahasa](../../../../../6-consumer/lessons/2-language-understanding)

## Pemahaman Bahasa

Manusia telah menggunakan bahasa untuk berkomunikasi selama ratusan ribu tahun. Kita berkomunikasi dengan kata-kata, bunyi, atau tindakan dan memahami apa yang dikatakan, bukan sahaja maksud kata-kata, bunyi, atau tindakan itu, tetapi juga konteksnya. Kita memahami keikhlasan dan sindiran, membolehkan kata-kata yang sama membawa maksud yang berbeza bergantung pada nada suara kita.

✅ Fikirkan tentang beberapa perbualan yang anda lakukan baru-baru ini. Berapa banyak daripada perbualan itu yang sukar untuk komputer fahami kerana ia memerlukan konteks?

Pemahaman bahasa, juga dikenali sebagai pemahaman bahasa semula jadi, adalah sebahagian daripada bidang kecerdasan buatan yang dipanggil pemprosesan bahasa semula jadi (atau NLP), dan berkaitan dengan kefahaman membaca, cuba memahami butiran kata-kata atau ayat. Jika anda menggunakan pembantu suara seperti Alexa atau Siri, anda telah menggunakan perkhidmatan pemahaman bahasa. Ini adalah perkhidmatan AI di belakang tabir yang menukar "Alexa, mainkan album terbaru Taylor Swift" kepada anak perempuan saya menari di ruang tamu dengan lagu kegemarannya.

> 💁 Komputer, walaupun dengan semua kemajuan mereka, masih mempunyai perjalanan yang panjang untuk benar-benar memahami teks. Apabila kita merujuk kepada pemahaman bahasa dengan komputer, kita tidak bermaksud apa-apa yang hampir setanding dengan komunikasi manusia, sebaliknya kita bermaksud mengambil beberapa kata dan mengekstrak butiran utama.

Sebagai manusia, kita memahami bahasa tanpa perlu berfikir panjang. Jika saya meminta manusia lain untuk "mainkan album terbaru Taylor Swift", mereka akan secara naluri tahu apa yang saya maksudkan. Bagi komputer, ini lebih sukar. Ia perlu mengambil kata-kata, yang telah ditukar daripada ucapan kepada teks, dan menentukan maklumat berikut:

* Muzik perlu dimainkan
* Muzik itu adalah oleh artis Taylor Swift
* Muzik tertentu adalah satu album penuh dengan beberapa lagu dalam urutan
* Taylor Swift mempunyai banyak album, jadi album tersebut perlu disusun mengikut urutan kronologi dan yang paling baru diterbitkan adalah yang diperlukan

✅ Fikirkan beberapa ayat lain yang anda gunakan semasa membuat permintaan, seperti memesan kopi atau meminta ahli keluarga untuk memberikan sesuatu. Cuba pecahkan kepada maklumat yang perlu diekstrak oleh komputer untuk memahami ayat tersebut.

Model pemahaman bahasa adalah model AI yang dilatih untuk mengekstrak butiran tertentu daripada bahasa, dan kemudian dilatih untuk tugas tertentu menggunakan pembelajaran pemindahan, sama seperti anda melatih model Custom Vision menggunakan set kecil imej. Anda boleh mengambil model, kemudian melatihnya menggunakan teks yang anda mahu ia fahami.

## Cipta Model Pemahaman Bahasa

![Logo LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.ms.png)

Anda boleh mencipta model pemahaman bahasa menggunakan LUIS, perkhidmatan pemahaman bahasa daripada Microsoft yang merupakan sebahagian daripada Cognitive Services.

### Tugas - Cipta sumber pengarang

Untuk menggunakan LUIS, anda perlu mencipta sumber pengarang.

1. Gunakan arahan berikut untuk mencipta sumber pengarang dalam kumpulan sumber `smart-timer` anda:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Gantikan `<location>` dengan lokasi yang anda gunakan semasa mencipta Kumpulan Sumber.

    > ⚠️ LUIS tidak tersedia di semua wilayah, jadi jika anda mendapat ralat berikut:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > pilih wilayah lain.

    Ini akan mencipta sumber pengarang LUIS peringkat percuma.

### Tugas - Cipta aplikasi pemahaman bahasa

1. Buka portal LUIS di [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) dalam pelayar anda, dan log masuk menggunakan akaun yang sama yang anda gunakan untuk Azure.

1. Ikuti arahan pada dialog untuk memilih langganan Azure anda, kemudian pilih sumber `smart-timer-luis-authoring` yang baru anda cipta.

1. Dari senarai *Aplikasi Perbualan*, pilih butang **Aplikasi Baru** untuk mencipta aplikasi baru. Namakan aplikasi baru `smart-timer`, dan tetapkan *Budaya* kepada bahasa anda.

    > 💁 Terdapat medan untuk sumber ramalan. Anda boleh mencipta sumber kedua hanya untuk ramalan, tetapi sumber pengarang percuma membenarkan 1,000 ramalan sebulan yang sepatutnya mencukupi untuk pembangunan, jadi anda boleh biarkan ini kosong.

1. Baca panduan yang muncul selepas anda mencipta aplikasi untuk memahami langkah-langkah yang perlu diambil untuk melatih model pemahaman bahasa. Tutup panduan ini apabila anda selesai.

## Niat dan Entiti

Pemahaman bahasa berasaskan kepada *niat* dan *entiti*. Niat adalah tujuan kata-kata, contohnya memainkan muzik, menetapkan pemasa, atau memesan makanan. Entiti adalah apa yang dirujuk oleh niat, seperti album, tempoh pemasa, atau jenis makanan. Setiap ayat yang ditafsirkan oleh model sepatutnya mempunyai sekurang-kurangnya satu niat, dan secara opsional satu atau lebih entiti.

Beberapa contoh:

| Ayat                                              | Niat             | Entiti                                     |
| ------------------------------------------------- | ---------------- | ------------------------------------------ |
| "Play the latest album by Taylor Swift"           | *mainkan muzik*  | *album terbaru oleh Taylor Swift*          |
| "Set a 3 minute timer"                            | *tetapkan pemasa*| *3 minit*                                  |
| "Cancel my timer"                                 | *batalkan pemasa*| Tiada                                     |
| "Order 3 large pineapple pizzas and a caesar salad" | *pesan makanan* | *3 pizza besar nanas*, *salad caesar*      |

✅ Dengan ayat-ayat yang anda fikirkan sebelum ini, apakah niat dan entiti dalam ayat tersebut?

Untuk melatih LUIS, pertama anda menetapkan entiti. Ini boleh menjadi senarai tetap istilah, atau dipelajari daripada teks. Sebagai contoh, anda boleh menyediakan senarai tetap makanan yang tersedia dalam menu anda, dengan variasi (atau sinonim) setiap perkataan, seperti *terung* dan *aubergine* sebagai variasi *aubergine*. LUIS juga mempunyai entiti pra-bina yang boleh digunakan, seperti nombor dan lokasi.

Untuk menetapkan pemasa, anda boleh mempunyai satu entiti menggunakan entiti nombor pra-bina untuk masa, dan satu lagi untuk unit, seperti minit dan saat. Setiap unit akan mempunyai pelbagai variasi untuk merangkumi bentuk tunggal dan jamak - seperti minit dan minit-minit.

Setelah entiti ditentukan, anda mencipta niat. Ini dipelajari oleh model berdasarkan ayat contoh yang anda sediakan (dikenali sebagai ucapan). Sebagai contoh, untuk niat *tetapkan pemasa*, anda mungkin menyediakan ayat berikut:

* `set a 1 second timer`
* `set a timer for 1 minute and 12 seconds`
* `set a timer for 3 minutes`
* `set a 9 minute 30 second timer`

Anda kemudian memberitahu LUIS bahagian mana dalam ayat ini yang memetakan kepada entiti:

![Ayat "set a timer for 1 minute and 12 seconds" dipecahkan kepada entiti](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.ms.png)

Ayat `set a timer for 1 minute and 12 seconds` mempunyai niat `set timer`. Ia juga mempunyai 2 entiti dengan 2 nilai setiap satu:

|            | masa | unit   |
| ---------- | ---: | ------ |
| 1 minute   | 1    | minute |
| 12 seconds | 12   | second |

Untuk melatih model yang baik, anda memerlukan pelbagai ayat contoh yang berbeza untuk merangkumi pelbagai cara seseorang mungkin meminta perkara yang sama.

> 💁 Seperti mana-mana model AI, lebih banyak data dan lebih tepat data yang anda gunakan untuk melatih, lebih baik model tersebut.

✅ Fikirkan tentang pelbagai cara anda mungkin meminta perkara yang sama dan mengharapkan manusia untuk memahaminya.

### Tugas - Tambah entiti kepada model pemahaman bahasa

Untuk pemasa, anda perlu menambah 2 entiti - satu untuk unit masa (minit atau saat), dan satu lagi untuk bilangan minit atau saat.

Anda boleh mendapatkan arahan untuk menggunakan portal LUIS dalam [Dokumentasi Quickstart: Bina aplikasi anda di portal LUIS di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Dari portal LUIS, pilih tab *Entities* dan tambahkan entiti pra-bina *number* dengan memilih butang **Add prebuilt entity**, kemudian memilih *number* daripada senarai.

1. Cipta entiti baru untuk unit masa menggunakan butang **Create**. Namakan entiti `time unit` dan tetapkan jenis kepada *List*. Tambahkan nilai untuk `minute` dan `second` kepada senarai *Normalized values*, menambahkan bentuk tunggal dan jamak kepada senarai *synonyms*. Tekan `return` selepas menambahkan setiap sinonim untuk menambahkannya ke senarai.

    | Nilai Normalisasi | Sinonim         |
    | ----------------- | --------------- |
    | minute            | minute, minutes |
    | second            | second, seconds |

### Tugas - Tambah niat kepada model pemahaman bahasa

1. Dari tab *Intents*, pilih butang **Create** untuk mencipta niat baru. Namakan niat ini `set timer`.

1. Dalam contoh, masukkan pelbagai cara untuk menetapkan pemasa menggunakan minit, saat, dan gabungan minit dan saat. Contoh boleh jadi:

    * `set a 1 second timer`
    * `set a 4 minute timer`
    * `set a four minute six second timer`
    * `set a 9 minute 30 second timer`
    * `set a timer for 1 minute and 12 seconds`
    * `set a timer for 3 minutes`
    * `set a timer for 3 minutes and 1 second`
    * `set a timer for three minutes and one second`
    * `set a timer for 1 minute and 1 second`
    * `set a timer for 30 seconds`
    * `set a timer for 1 second`

    Campurkan nombor dalam bentuk perkataan dan angka supaya model belajar menangani kedua-duanya.

1. Semasa anda memasukkan setiap contoh, LUIS akan mula mengesan entiti, dan akan menggariskan serta melabelkan mana-mana yang ditemui.

    ![Contoh dengan nombor dan unit masa digariskan oleh LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.ms.png)

### Tugas - Latih dan uji model

1. Setelah entiti dan niat dikonfigurasi, anda boleh melatih model menggunakan butang **Train** pada menu atas. Pilih butang ini, dan model sepatutnya dilatih dalam beberapa saat. Butang akan kelihatan kelabu semasa latihan, dan akan diaktifkan semula setelah selesai.

1. Pilih butang **Test** dari menu atas untuk menguji model pemahaman bahasa. Masukkan teks seperti `set a timer for 5 minutes and 4 seconds` dan tekan return. Ayat akan muncul dalam kotak di bawah kotak teks yang anda taipkan, dan di bawah itu akan ada *top intent*, atau niat yang dikesan dengan kebarangkalian tertinggi. Ini sepatutnya `set timer`. Nama niat akan diikuti oleh kebarangkalian bahawa niat yang dikesan adalah betul.

1. Pilih pilihan **Inspect** untuk melihat pecahan hasil. Anda akan melihat niat dengan skor tertinggi bersama kebarangkalian peratusannya, bersama senarai entiti yang dikesan.

1. Tutup panel *Test* apabila anda selesai menguji.

### Tugas - Terbitkan model

Untuk menggunakan model ini daripada kod, anda perlu menerbitkannya. Apabila menerbitkan daripada LUIS, anda boleh menerbitkan sama ada ke persekitaran pementasan untuk ujian, atau persekitaran produk untuk pelepasan penuh. Dalam pelajaran ini, persekitaran pementasan sudah mencukupi.

1. Dari portal LUIS, pilih butang **Publish** dari menu atas.

1. Pastikan *Staging slot* dipilih, kemudian pilih **Done**. Anda akan melihat pemberitahuan apabila aplikasi diterbitkan.

1. Anda boleh mengujinya menggunakan curl. Untuk membina arahan curl, anda memerlukan tiga nilai - titik akhir, ID aplikasi (App ID) dan kunci API. Nilai-nilai ini boleh diakses dari tab **MANAGE** yang boleh dipilih dari menu atas.

    1. Dari bahagian *Settings*, salin App ID.
1. Dari bahagian *Azure Resources*, pilih *Authoring Resource*, dan salin *Primary Key* dan *Endpoint URL*.

1. Jalankan arahan curl berikut dalam command prompt atau terminal anda:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Gantikan `<endpoint url>` dengan Endpoint URL dari bahagian *Azure Resources*.

    Gantikan `<app id>` dengan App ID dari bahagian *Settings*.

    Gantikan `<primary key>` dengan Primary Key dari bahagian *Azure Resources*.

    Gantikan `<sentence>` dengan ayat yang ingin anda uji.

1. Output daripada panggilan ini akan menjadi dokumen JSON yang memperincikan pertanyaan, intent utama, dan senarai entiti yang dipecahkan mengikut jenis.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    JSON di atas berasal daripada pertanyaan dengan `set a timer for 45 minutes and 12 seconds`:

    * `set timer` adalah intent utama dengan kebarangkalian 97%.
    * Dua entiti *number* dikesan, `45` dan `12`.
    * Dua entiti *time-unit* dikesan, `minute` dan `second`.

## Gunakan model pemahaman bahasa

Setelah diterbitkan, model LUIS boleh dipanggil dari kod. Dalam pelajaran sebelumnya, anda telah menggunakan IoT Hub untuk mengendalikan komunikasi dengan perkhidmatan awan, menghantar telemetri dan mendengar arahan. Ini sangat tidak segerak - setelah telemetri dihantar, kod anda tidak menunggu respons, dan jika perkhidmatan awan tidak berfungsi, anda tidak akan tahu.

Untuk pemasa pintar, kami mahukan respons segera supaya kami boleh memberitahu pengguna bahawa pemasa telah ditetapkan, atau memberi amaran kepada mereka bahawa perkhidmatan awan tidak tersedia. Untuk melakukan ini, peranti IoT kami akan memanggil endpoint web secara langsung, bukannya bergantung pada IoT Hub.

Daripada memanggil LUIS dari peranti IoT, anda boleh menggunakan kod tanpa pelayan dengan jenis trigger yang berbeza - trigger HTTP. Ini membolehkan aplikasi fungsi anda mendengar permintaan REST dan memberi respons kepada mereka. Fungsi ini akan menjadi endpoint REST yang boleh dipanggil oleh peranti anda.

> 💁 Walaupun anda boleh memanggil LUIS secara langsung dari peranti IoT anda, adalah lebih baik menggunakan sesuatu seperti kod tanpa pelayan. Dengan cara ini, apabila anda ingin menukar aplikasi LUIS yang anda panggil, contohnya apabila anda melatih model yang lebih baik atau melatih model dalam bahasa yang berbeza, anda hanya perlu mengemas kini kod awan anda, bukan menyebarkan semula kod kepada ribuan atau jutaan peranti IoT.

### Tugasan - buat aplikasi fungsi tanpa pelayan

1. Buat aplikasi Azure Functions bernama `smart-timer-trigger`, dan buka ini dalam VS Code.

1. Tambahkan trigger HTTP ke aplikasi ini bernama `speech-trigger` menggunakan arahan berikut dari dalam terminal VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Ini akan membuat trigger HTTP bernama `text-to-timer`.

1. Uji trigger HTTP dengan menjalankan aplikasi fungsi. Apabila ia berjalan, anda akan melihat endpoint disenaraikan dalam output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Uji ini dengan memuatkan URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) dalam pelayar anda.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Tugasan - gunakan model pemahaman bahasa

1. SDK untuk LUIS tersedia melalui pakej Pip. Tambahkan baris berikut ke fail `requirements.txt` untuk menambahkan kebergantungan pada pakej ini:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Pastikan terminal VS Code mempunyai persekitaran maya diaktifkan, dan jalankan arahan berikut untuk memasang pakej Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Jika anda mendapat ralat, anda mungkin perlu menaik taraf pip dengan arahan berikut:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Tambahkan entri baru ke fail `local.settings.json` untuk LUIS API Key, Endpoint URL, dan App ID anda dari tab **MANAGE** di portal LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Gantikan `<endpoint url>` dengan Endpoint URL dari bahagian *Azure Resources* tab **MANAGE**. Ini akan menjadi `https://<location>.api.cognitive.microsoft.com/`.

    Gantikan `<app id>` dengan App ID dari bahagian *Settings* tab **MANAGE**.

    Gantikan `<primary key>` dengan Primary Key dari bahagian *Azure Resources* tab **MANAGE**.

1. Tambahkan import berikut ke fail `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Ini mengimport beberapa perpustakaan sistem, serta perpustakaan untuk berinteraksi dengan LUIS.

1. Padamkan kandungan kaedah `main`, dan tambahkan kod berikut:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Ini memuat nilai yang anda tambahkan ke fail `local.settings.json` untuk aplikasi LUIS anda, mencipta objek kelayakan dengan API key anda, kemudian mencipta objek klien LUIS untuk berinteraksi dengan aplikasi LUIS anda.

1. Trigger HTTP ini akan dipanggil dengan teks untuk difahami sebagai JSON, dengan teks dalam properti bernama `text`. Kod berikut mengekstrak nilai dari badan permintaan HTTP, dan mencatatnya ke konsol. Tambahkan kod ini ke fungsi `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Ramalan diminta dari LUIS dengan menghantar permintaan ramalan - dokumen JSON yang mengandungi teks untuk diramalkan. Cipta ini dengan kod berikut:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Permintaan ini kemudian boleh dihantar ke LUIS, menggunakan slot staging yang aplikasi anda diterbitkan:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Respons ramalan mengandungi intent utama - intent dengan skor ramalan tertinggi, bersama dengan entiti. Jika intent utama adalah `set timer`, maka entiti boleh dibaca untuk mendapatkan masa yang diperlukan untuk pemasa:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Entiti `number` akan menjadi array nombor. Contohnya, jika anda berkata *"Set a four minute 17 second timer."*, maka array `number` akan mengandungi 2 integer - 4 dan 17.

    Entiti `time unit` akan menjadi array array string, dengan setiap unit masa sebagai array string di dalam array. Contohnya, jika anda berkata *"Set a four minute 17 second timer."*, maka array `time unit` akan mengandungi 2 array dengan satu nilai setiap satu - `['minute']` dan `['second']`.

    Versi JSON entiti ini untuk *"Set a four minute 17 second timer."* adalah:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Kod ini juga mentakrifkan kiraan untuk jumlah masa untuk pemasa dalam saat. Ini akan diisi oleh nilai dari entiti.

1. Entiti tidak dihubungkan, tetapi kita boleh membuat beberapa andaian tentang mereka. Mereka akan berada dalam urutan yang disebut, jadi kedudukan dalam array boleh digunakan untuk menentukan nombor mana yang sepadan dengan unit masa mana. Contohnya:

    * *"Set a 30 second timer"* - ini akan mempunyai satu nombor, `30`, dan satu unit masa, `second` jadi nombor tunggal akan sepadan dengan unit masa tunggal.
    * *"Set a 2 minute and 30 second timer"* - ini akan mempunyai dua nombor, `2` dan `30`, dan dua unit masa, `minute` dan `second` jadi nombor pertama akan untuk unit masa pertama (2 minit), dan nombor kedua untuk unit masa kedua (30 saat).

    Kod berikut mendapatkan kiraan item dalam entiti nombor, dan menggunakannya untuk mengekstrak item pertama dari setiap array, kemudian yang kedua dan seterusnya. Tambahkan ini di dalam blok `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Untuk *"Set a four minute 17 second timer."*, ini akan mengulang dua kali, memberikan nilai berikut:

    | kiraan ulang | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Di dalam gelung ini, gunakan nombor dan unit masa untuk mengira jumlah masa untuk pemasa, menambahkan 60 saat untuk setiap minit, dan jumlah saat untuk sebarang saat.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Di luar gelung melalui entiti, catat jumlah masa untuk pemasa:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Jumlah saat perlu dikembalikan dari fungsi sebagai respons HTTP. Di akhir blok `if`, tambahkan yang berikut:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Kod ini mencipta payload yang mengandungi jumlah saat untuk pemasa, menukarnya kepada string JSON dan mengembalikannya sebagai hasil HTTP dengan kod status 200, yang bermaksud panggilan berjaya.

1. Akhirnya, di luar blok `if`, tangani jika intent tidak dikenali dengan mengembalikan kod ralat:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 adalah kod status untuk *tidak dijumpai*.

1. Jalankan aplikasi fungsi dan uji menggunakan curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Gantikan `<text>` dengan teks permintaan anda, contohnya `set a 2 minutes 27 second timer`.

    Anda akan melihat output berikut dari aplikasi fungsi:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    Panggilan curl akan mengembalikan yang berikut:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Jumlah saat untuk pemasa ada dalam nilai `"seconds"`.

> 💁 Anda boleh menemui kod ini dalam folder [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Tugasan - buat fungsi anda tersedia untuk peranti IoT anda

1. Untuk peranti IoT anda memanggil endpoint REST anda, ia perlu mengetahui URL. Apabila anda mengaksesnya sebelum ini, anda menggunakan `localhost`, yang merupakan pintasan untuk mengakses endpoint REST pada mesin tempatan anda. Untuk membolehkan peranti IoT anda mendapatkan akses, anda perlu sama ada menerbitkan ke awan, atau mendapatkan alamat IP anda untuk mengaksesnya secara tempatan.

    > ⚠️ Jika anda menggunakan Wio Terminal, adalah lebih mudah untuk menjalankan aplikasi fungsi secara tempatan, kerana akan ada kebergantungan pada perpustakaan yang bermaksud anda tidak boleh menerbitkan aplikasi fungsi dengan cara yang sama seperti yang anda lakukan sebelum ini. Jalankan aplikasi fungsi secara tempatan dan aksesnya melalui alamat IP komputer anda. Jika anda ingin menerbitkan ke awan, maklumat akan diberikan dalam pelajaran kemudian tentang cara melakukannya.

    * Terbitkan aplikasi Functions - ikuti arahan dalam pelajaran sebelumnya untuk menerbitkan aplikasi fungsi anda ke awan. Setelah diterbitkan, URL akan menjadi `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, di mana `<APP_NAME>` akan menjadi nama aplikasi fungsi anda. Pastikan juga menerbitkan tetapan tempatan anda.

      Apabila bekerja dengan trigger HTTP, mereka dilindungi secara lalai dengan kunci aplikasi fungsi. Untuk mendapatkan kunci ini, jalankan arahan berikut:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Salin nilai entri `default` dari bahagian `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Kunci ini perlu ditambahkan sebagai parameter pertanyaan ke URL, jadi URL akhir akan menjadi `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, di mana `<APP_NAME>` akan menjadi nama aplikasi fungsi anda, dan `<FUNCTION_KEY>` akan menjadi kunci fungsi lalai anda.

      > 💁 Anda boleh menukar jenis kebenaran trigger HTTP menggunakan tetapan `authlevel` dalam fail `function.json`. Anda boleh membaca lebih lanjut tentang ini dalam [bahagian konfigurasi dokumentasi trigger HTTP Azure Functions di Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Jalankan aplikasi fungsi secara tempatan, dan akses menggunakan alamat IP - anda boleh mendapatkan alamat IP komputer anda di rangkaian tempatan, dan menggunakannya untuk membina URL.

      Cari alamat IP anda:

      * Pada Windows 10, ikuti panduan [cari alamat IP anda](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Pada macOS, ikuti panduan [cara mencari alamat IP anda di Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Pada Linux, ikuti bahagian tentang mencari alamat IP peribadi anda dalam panduan [cara mencari alamat IP anda di Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Setelah anda mempunyai alamat IP anda, anda akan dapat mengakses fungsi di `http://`.

:7071/api/text-to-timer`, di mana `<IP_ADDRESS>` adalah alamat IP anda, contohnya `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Perhatikan bahawa ini menggunakan port 7071, jadi selepas alamat IP anda perlu menambah `:7071`.

      > 💁 Ini hanya akan berfungsi jika peranti IoT anda berada dalam rangkaian yang sama dengan komputer anda.

1. Uji endpoint dengan mengaksesnya menggunakan curl.

---

## 🚀 Cabaran

Terdapat banyak cara untuk meminta perkara yang sama, seperti menetapkan pemasa. Fikirkan pelbagai cara untuk melakukannya, dan gunakan cara-cara tersebut sebagai contoh dalam aplikasi LUIS anda. Uji cara-cara ini untuk melihat sejauh mana model anda dapat menangani pelbagai cara untuk meminta pemasa.

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Ulasan & Kajian Kendiri

* Baca lebih lanjut tentang LUIS dan keupayaannya di [halaman dokumentasi Language Understanding (LUIS) di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Baca lebih lanjut tentang pemahaman bahasa di [halaman pemahaman bahasa semula jadi di Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Baca lebih lanjut tentang pencetus HTTP dalam [dokumentasi pencetus HTTP Azure Functions di Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Tugasan

[Batalkan pemasa](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.