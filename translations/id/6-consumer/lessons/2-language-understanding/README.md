<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T23:04:22+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "id"
}
-->
# Memahami Bahasa

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.id.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Sebelum Pelajaran

[Kuis Sebelum Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Pendahuluan

Pada pelajaran sebelumnya, Anda telah mengubah ucapan menjadi teks. Agar dapat digunakan untuk memprogram pengatur waktu pintar, kode Anda perlu memahami apa yang diucapkan. Anda mungkin berasumsi bahwa pengguna akan mengucapkan frasa tetap, seperti "Setel pengatur waktu 3 menit", dan memparsing ekspresi tersebut untuk mengetahui durasi pengatur waktu. Namun, ini tidak terlalu ramah pengguna. Jika pengguna mengatakan "Setel pengatur waktu selama 3 menit", Anda atau saya akan memahami maksudnya, tetapi kode Anda tidak akan memahaminya karena mengharapkan frasa tetap.

Di sinilah pemahaman bahasa berperan, menggunakan model AI untuk menafsirkan teks dan mengembalikan detail yang diperlukan. Misalnya, model ini dapat memahami baik "Setel pengatur waktu 3 menit" maupun "Setel pengatur waktu selama 3 menit" sebagai permintaan untuk pengatur waktu selama 3 menit.

Dalam pelajaran ini, Anda akan mempelajari tentang model pemahaman bahasa, cara membuatnya, melatihnya, dan menggunakannya dalam kode Anda.

Dalam pelajaran ini, kita akan membahas:

* [Pemahaman bahasa](../../../../../6-consumer/lessons/2-language-understanding)
* [Membuat model pemahaman bahasa](../../../../../6-consumer/lessons/2-language-understanding)
* [Intensi dan entitas](../../../../../6-consumer/lessons/2-language-understanding)
* [Menggunakan model pemahaman bahasa](../../../../../6-consumer/lessons/2-language-understanding)

## Pemahaman Bahasa

Manusia telah menggunakan bahasa untuk berkomunikasi selama ratusan ribu tahun. Kita berkomunikasi dengan kata-kata, suara, atau tindakan dan memahami apa yang diucapkan, baik arti kata-kata, suara, atau tindakan tersebut, maupun konteksnya. Kita memahami ketulusan dan sarkasme, memungkinkan kata-kata yang sama memiliki arti berbeda tergantung pada nada suara kita.

✅ Pikirkan beberapa percakapan yang baru saja Anda lakukan. Seberapa sulit percakapan tersebut untuk dipahami oleh komputer karena membutuhkan konteks?

Pemahaman bahasa, juga disebut pemahaman bahasa alami, adalah bagian dari bidang kecerdasan buatan yang disebut pemrosesan bahasa alami (atau NLP), dan berhubungan dengan pemahaman bacaan, mencoba memahami detail kata atau kalimat. Jika Anda menggunakan asisten suara seperti Alexa atau Siri, Anda telah menggunakan layanan pemahaman bahasa. Layanan AI ini bekerja di balik layar untuk mengubah "Alexa, putar album terbaru Taylor Swift" menjadi anak saya yang menari di ruang tamu dengan lagu favoritnya.

> 💁 Komputer, meskipun telah mengalami banyak kemajuan, masih memiliki jalan panjang untuk benar-benar memahami teks. Ketika kita berbicara tentang pemahaman bahasa pada komputer, kita tidak berbicara tentang sesuatu yang mendekati komunikasi manusia, melainkan mengambil beberapa kata dan mengekstrak detail utama.

Sebagai manusia, kita memahami bahasa tanpa benar-benar memikirkannya. Jika saya meminta seseorang untuk "putar album terbaru Taylor Swift", mereka akan langsung tahu maksud saya. Bagi komputer, ini lebih sulit. Komputer harus mengambil kata-kata, yang telah diubah dari ucapan menjadi teks, dan menentukan informasi berikut:

* Musik perlu diputar
* Musik tersebut adalah karya artis Taylor Swift
* Musik spesifiknya adalah satu album penuh dengan beberapa lagu secara berurutan
* Taylor Swift memiliki banyak album, jadi album tersebut perlu diurutkan berdasarkan kronologi, dan yang paling baru diterbitkan adalah yang dimaksud

✅ Pikirkan beberapa kalimat lain yang Anda ucapkan saat membuat permintaan, seperti memesan kopi atau meminta anggota keluarga untuk memberikan sesuatu. Cobalah untuk memecahnya menjadi potongan informasi yang perlu diekstrak komputer untuk memahami kalimat tersebut.

Model pemahaman bahasa adalah model AI yang dilatih untuk mengekstrak detail tertentu dari bahasa, dan kemudian dilatih untuk tugas tertentu menggunakan pembelajaran transfer, dengan cara yang sama seperti Anda melatih model Custom Vision menggunakan sejumlah kecil gambar. Anda dapat mengambil model, lalu melatihnya menggunakan teks yang ingin Anda pahami.

## Membuat Model Pemahaman Bahasa

![Logo LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.id.png)

Anda dapat membuat model pemahaman bahasa menggunakan LUIS, layanan pemahaman bahasa dari Microsoft yang merupakan bagian dari Cognitive Services.

### Tugas - membuat sumber daya authoring

Untuk menggunakan LUIS, Anda perlu membuat sumber daya authoring.

1. Gunakan perintah berikut untuk membuat sumber daya authoring di grup sumber daya `smart-timer` Anda:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat Grup Sumber Daya.

    > ⚠️ LUIS tidak tersedia di semua wilayah, jadi jika Anda mendapatkan kesalahan berikut:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > pilih wilayah lain.

    Ini akan membuat sumber daya authoring LUIS tingkat gratis.

### Tugas - membuat aplikasi pemahaman bahasa

1. Buka portal LUIS di [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) di browser Anda, dan masuk dengan akun yang sama yang telah Anda gunakan untuk Azure.

1. Ikuti instruksi pada dialog untuk memilih langganan Azure Anda, lalu pilih sumber daya `smart-timer-luis-authoring` yang baru saja Anda buat.

1. Dari daftar *Aplikasi Percakapan*, pilih tombol **Aplikasi Baru** untuk membuat aplikasi baru. Beri nama aplikasi baru tersebut `smart-timer`, dan atur *Budaya* ke bahasa Anda.

    > 💁 Ada bidang untuk sumber daya prediksi. Anda dapat membuat sumber daya kedua hanya untuk prediksi, tetapi sumber daya authoring gratis memungkinkan 1.000 prediksi per bulan yang seharusnya cukup untuk pengembangan, jadi Anda dapat membiarkannya kosong.

1. Baca panduan yang muncul setelah Anda membuat aplikasi untuk memahami langkah-langkah yang perlu Anda ambil untuk melatih model pemahaman bahasa. Tutup panduan ini setelah selesai.

## Intensi dan Entitas

Pemahaman bahasa didasarkan pada *intensi* dan *entitas*. Intensi adalah maksud dari kata-kata tersebut, misalnya memutar musik, menyetel pengatur waktu, atau memesan makanan. Entitas adalah apa yang dirujuk oleh intensi, seperti album, durasi pengatur waktu, atau jenis makanan. Setiap kalimat yang diinterpretasikan oleh model harus memiliki setidaknya satu intensi, dan opsional satu atau lebih entitas.

Beberapa contoh:

| Kalimat                                            | Intensi           | Entitas                                   |
| -------------------------------------------------- | ----------------- | ----------------------------------------- |
| "Putar album terbaru Taylor Swift"                | *putar musik*     | *album terbaru Taylor Swift*             |
| "Setel pengatur waktu 3 menit"                    | *setel pengatur waktu* | *3 menit*                            |
| "Batalkan pengatur waktu saya"                    | *batalkan pengatur waktu* | Tidak ada                          |
| "Pesan 3 pizza besar nanas dan satu salad caesar" | *pesan makanan*   | *3 pizza besar nanas*, *salad caesar*    |

✅ Dengan kalimat yang Anda pikirkan sebelumnya, apa intensi dan entitas dalam kalimat tersebut?

Untuk melatih LUIS, pertama-tama Anda menetapkan entitas. Entitas ini bisa berupa daftar istilah tetap, atau dipelajari dari teks. Misalnya, Anda dapat menyediakan daftar tetap makanan yang tersedia di menu Anda, dengan variasi (atau sinonim) dari setiap kata, seperti *terong* dan *aubergine* sebagai variasi dari *aubergine*. LUIS juga memiliki entitas bawaan yang dapat digunakan, seperti angka dan lokasi.

Untuk menyetel pengatur waktu, Anda dapat memiliki satu entitas menggunakan entitas angka bawaan untuk waktu, dan entitas lain untuk satuan waktu, seperti menit dan detik. Setiap satuan akan memiliki beberapa variasi untuk bentuk tunggal dan jamak - seperti menit dan menit-menit.

Setelah entitas ditentukan, Anda membuat intensi. Intensi ini dipelajari oleh model berdasarkan contoh kalimat yang Anda berikan (disebut *utterances*). Misalnya, untuk intensi *setel pengatur waktu*, Anda dapat memberikan kalimat berikut:

* `setel pengatur waktu 1 detik`
* `setel pengatur waktu selama 1 menit dan 12 detik`
* `setel pengatur waktu selama 3 menit`
* `setel pengatur waktu 9 menit 30 detik`

Kemudian Anda memberi tahu LUIS bagian mana dari kalimat ini yang sesuai dengan entitas:

![Kalimat "setel pengatur waktu selama 1 menit dan 12 detik" dipecah menjadi entitas](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.id.png)

Kalimat `setel pengatur waktu selama 1 menit dan 12 detik` memiliki intensi `setel pengatur waktu`. Kalimat ini juga memiliki 2 entitas dengan masing-masing 2 nilai:

|            | waktu | satuan   |
| ---------- | ----: | -------- |
| 1 menit    | 1     | menit    |
| 12 detik   | 12    | detik    |

Untuk melatih model yang baik, Anda memerlukan berbagai contoh kalimat yang berbeda untuk mencakup berbagai cara seseorang mungkin meminta hal yang sama.

> 💁 Seperti halnya model AI lainnya, semakin banyak data dan semakin akurat data yang Anda gunakan untuk melatih, semakin baik modelnya.

✅ Pikirkan berbagai cara Anda mungkin meminta hal yang sama dan mengharapkan manusia untuk memahaminya.

### Tugas - menambahkan entitas ke model pemahaman bahasa

Untuk pengatur waktu, Anda perlu menambahkan 2 entitas - satu untuk satuan waktu (menit atau detik), dan satu untuk jumlah menit atau detik.

Anda dapat menemukan instruksi untuk menggunakan portal LUIS di [Panduan Cepat: Membangun aplikasi Anda di dokumentasi portal LUIS di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Dari portal LUIS, pilih tab *Entitas* dan tambahkan entitas bawaan *number* dengan memilih tombol **Tambahkan entitas bawaan**, lalu memilih *number* dari daftar.

1. Buat entitas baru untuk satuan waktu menggunakan tombol **Buat**. Beri nama entitas `satuan waktu` dan atur jenisnya menjadi *Daftar*. Tambahkan nilai untuk `menit` dan `detik` ke daftar *Nilai yang Dinormalisasi*, tambahkan bentuk tunggal dan jamak ke daftar *Sinonim*. Tekan `return` setelah menambahkan setiap sinonim untuk menambahkannya ke daftar.

    | Nilai yang Dinormalisasi | Sinonim        |
    | ------------------------- | -------------- |
    | menit                    | menit, menit-menit |
    | detik                    | detik, detik-detik |

### Tugas - menambahkan intensi ke model pemahaman bahasa

1. Dari tab *Intensi*, pilih tombol **Buat** untuk membuat intensi baru. Beri nama intensi ini `setel pengatur waktu`.

1. Dalam contoh, masukkan berbagai cara untuk menyetel pengatur waktu menggunakan menit, detik, dan kombinasi menit dan detik. Contoh dapat berupa:

    * `setel pengatur waktu 1 detik`
    * `setel pengatur waktu 4 menit`
    * `setel pengatur waktu empat menit enam detik`
    * `setel pengatur waktu 9 menit 30 detik`
    * `setel pengatur waktu selama 1 menit dan 12 detik`
    * `setel pengatur waktu selama 3 menit`
    * `setel pengatur waktu selama 3 menit dan 1 detik`
    * `setel pengatur waktu selama tiga menit dan satu detik`
    * `setel pengatur waktu selama 1 menit dan 1 detik`
    * `setel pengatur waktu selama 30 detik`
    * `setel pengatur waktu selama 1 detik`

    Campurkan angka dalam bentuk kata dan numerik agar model belajar menangani keduanya.

1. Saat Anda memasukkan setiap contoh, LUIS akan mulai mendeteksi entitas, dan akan menggarisbawahi serta memberi label pada entitas yang ditemukan.

    ![Contoh dengan angka dan satuan waktu yang digarisbawahi oleh LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.id.png)

### Tugas - melatih dan menguji model

1. Setelah entitas dan intensi dikonfigurasi, Anda dapat melatih model menggunakan tombol **Latih** di menu atas. Pilih tombol ini, dan model akan dilatih dalam beberapa detik. Tombol akan dinonaktifkan selama pelatihan, dan diaktifkan kembali setelah selesai.

1. Pilih tombol **Uji** dari menu atas untuk menguji model pemahaman bahasa. Masukkan teks seperti `setel pengatur waktu selama 5 menit dan 4 detik` dan tekan return. Kalimat akan muncul di kotak di bawah kotak teks tempat Anda mengetiknya, dan di bawahnya akan ada *intensi teratas*, atau intensi yang terdeteksi dengan probabilitas tertinggi. Ini seharusnya `setel pengatur waktu`. Nama intensi akan diikuti oleh probabilitas bahwa intensi yang terdeteksi adalah yang benar.

1. Pilih opsi **Periksa** untuk melihat rincian hasil. Anda akan melihat intensi dengan skor tertinggi beserta persentase probabilitasnya, bersama dengan daftar entitas yang terdeteksi.

1. Tutup panel *Uji* setelah selesai menguji.

### Tugas - menerbitkan model

Untuk menggunakan model ini dari kode, Anda perlu menerbitkannya. Saat menerbitkan dari LUIS, Anda dapat menerbitkan ke lingkungan staging untuk pengujian, atau lingkungan produksi untuk rilis penuh. Dalam pelajaran ini, lingkungan staging sudah cukup.

1. Dari portal LUIS, pilih tombol **Terbitkan** dari menu atas.

1. Pastikan *Slot Staging* dipilih, lalu pilih **Selesai**. Anda akan melihat pemberitahuan saat aplikasi diterbitkan.

1. Anda dapat mengujinya menggunakan curl. Untuk membangun perintah curl, Anda memerlukan tiga nilai - endpoint, ID aplikasi (App ID), dan kunci API. Nilai-nilai ini dapat diakses dari tab **KELOLA** yang dapat dipilih dari menu atas.

    1. Dari bagian *Pengaturan*, salin App ID
1. Dari bagian *Azure Resources*, pilih *Authoring Resource*, lalu salin *Primary Key* dan *Endpoint URL*.

1. Jalankan perintah curl berikut di command prompt atau terminal Anda:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Ganti `<endpoint url>` dengan Endpoint URL dari bagian *Azure Resources*.

    Ganti `<app id>` dengan App ID dari bagian *Settings*.

    Ganti `<primary key>` dengan Primary Key dari bagian *Azure Resources*.

    Ganti `<sentence>` dengan kalimat yang ingin Anda uji.

1. Output dari panggilan ini akan berupa dokumen JSON yang merinci kueri, intent teratas, dan daftar entitas yang dipecah berdasarkan jenisnya.

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

    JSON di atas berasal dari kueri dengan `set a timer for 45 minutes and 12 seconds`:

    * `set timer` adalah intent teratas dengan probabilitas 97%.
    * Dua entitas *number* terdeteksi, yaitu `45` dan `12`.
    * Dua entitas *time-unit* terdeteksi, yaitu `minute` dan `second`.

## Gunakan model pemahaman bahasa

Setelah dipublikasikan, model LUIS dapat dipanggil dari kode. Dalam pelajaran sebelumnya, Anda telah menggunakan IoT Hub untuk menangani komunikasi dengan layanan cloud, mengirimkan telemetri, dan mendengarkan perintah. Ini sangat asinkron - setelah telemetri dikirim, kode Anda tidak menunggu respons, dan jika layanan cloud sedang tidak aktif, Anda tidak akan tahu.

Untuk timer pintar, kita ingin respons langsung, sehingga kita dapat memberi tahu pengguna bahwa timer telah diatur, atau memberi tahu mereka bahwa layanan cloud tidak tersedia. Untuk melakukan ini, perangkat IoT kita akan memanggil endpoint web secara langsung, alih-alih bergantung pada IoT Hub.

Daripada memanggil LUIS langsung dari perangkat IoT, Anda dapat menggunakan kode tanpa server dengan jenis pemicu yang berbeda - pemicu HTTP. Ini memungkinkan aplikasi fungsi Anda untuk mendengarkan permintaan REST dan meresponsnya. Fungsi ini akan menjadi endpoint REST yang dapat dipanggil oleh perangkat Anda.

> 💁 Meskipun Anda dapat memanggil LUIS langsung dari perangkat IoT Anda, lebih baik menggunakan sesuatu seperti kode tanpa server. Dengan cara ini, ketika Anda ingin mengubah aplikasi LUIS yang Anda panggil, misalnya saat Anda melatih model yang lebih baik atau melatih model dalam bahasa yang berbeda, Anda hanya perlu memperbarui kode cloud Anda, bukan menerapkan ulang kode ke ribuan atau jutaan perangkat IoT.

### Tugas - buat aplikasi fungsi tanpa server

1. Buat aplikasi Azure Functions bernama `smart-timer-trigger`, dan buka ini di VS Code.

1. Tambahkan pemicu HTTP ke aplikasi ini bernama `speech-trigger` menggunakan perintah berikut dari dalam terminal VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Ini akan membuat pemicu HTTP bernama `text-to-timer`.

1. Uji pemicu HTTP dengan menjalankan aplikasi fungsi. Saat aplikasi berjalan, Anda akan melihat endpoint terdaftar di output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Uji ini dengan membuka URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) di browser Anda.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Tugas - gunakan model pemahaman bahasa

1. SDK untuk LUIS tersedia melalui paket Pip. Tambahkan baris berikut ke file `requirements.txt` untuk menambahkan dependensi pada paket ini:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Pastikan terminal VS Code memiliki lingkungan virtual yang diaktifkan, dan jalankan perintah berikut untuk menginstal paket Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Jika Anda mendapatkan error, Anda mungkin perlu memperbarui pip dengan perintah berikut:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Tambahkan entri baru ke file `local.settings.json` untuk LUIS API Key, Endpoint URL, dan App ID Anda dari tab **MANAGE** di portal LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Ganti `<endpoint url>` dengan Endpoint URL dari bagian *Azure Resources* di tab **MANAGE**. Ini akan berupa `https://<location>.api.cognitive.microsoft.com/`.

    Ganti `<app id>` dengan App ID dari bagian *Settings* di tab **MANAGE**.

    Ganti `<primary key>` dengan Primary Key dari bagian *Azure Resources* di tab **MANAGE**.

1. Tambahkan impor berikut ke file `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Ini mengimpor beberapa pustaka sistem, serta pustaka untuk berinteraksi dengan LUIS.

1. Hapus isi metode `main`, dan tambahkan kode berikut:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Kode ini memuat nilai yang Anda tambahkan ke file `local.settings.json` untuk aplikasi LUIS Anda, membuat objek kredensial dengan API key Anda, lalu membuat objek klien LUIS untuk berinteraksi dengan aplikasi LUIS Anda.

1. Pemicu HTTP ini akan dipanggil dengan teks yang ingin dipahami sebagai JSON, dengan teks dalam properti bernama `text`. Kode berikut mengekstrak nilai dari body permintaan HTTP dan mencatatnya ke konsol. Tambahkan kode ini ke fungsi `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Prediksi diminta dari LUIS dengan mengirimkan permintaan prediksi - dokumen JSON yang berisi teks untuk diprediksi. Buat ini dengan kode berikut:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Permintaan ini kemudian dapat dikirim ke LUIS, menggunakan slot staging tempat aplikasi Anda dipublikasikan:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Respons prediksi berisi intent teratas - intent dengan skor prediksi tertinggi, bersama dengan entitas. Jika intent teratas adalah `set timer`, maka entitas dapat dibaca untuk mendapatkan waktu yang diperlukan untuk timer:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Entitas `number` akan berupa array angka. Misalnya, jika Anda mengatakan *"Set a four minute 17 second timer."*, maka array `number` akan berisi 2 integer - 4 dan 17.

    Entitas `time unit` akan berupa array array string, dengan setiap unit waktu sebagai array string di dalam array. Misalnya, jika Anda mengatakan *"Set a four minute 17 second timer."*, maka array `time unit` akan berisi 2 array dengan masing-masing satu nilai - `['minute']` dan `['second']`.

    Versi JSON dari entitas ini untuk *"Set a four minute 17 second timer."* adalah:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Kode ini juga mendefinisikan jumlah total waktu untuk timer dalam detik. Ini akan diisi oleh nilai-nilai dari entitas.

1. Entitas tidak terhubung, tetapi kita dapat membuat beberapa asumsi tentang mereka. Mereka akan berada dalam urutan yang diucapkan, sehingga posisi dalam array dapat digunakan untuk menentukan angka mana yang cocok dengan unit waktu mana. Misalnya:

    * *"Set a 30 second timer"* - ini akan memiliki satu angka, `30`, dan satu unit waktu, `second`, sehingga angka tunggal akan cocok dengan unit waktu tunggal.
    * *"Set a 2 minute and 30 second timer"* - ini akan memiliki dua angka, `2` dan `30`, dan dua unit waktu, `minute` dan `second`, sehingga angka pertama akan untuk unit waktu pertama (2 menit), dan angka kedua untuk unit waktu kedua (30 detik).

    Kode berikut mendapatkan jumlah item dalam entitas angka, dan menggunakan itu untuk mengekstrak item pertama dari setiap array, lalu yang kedua, dan seterusnya. Tambahkan ini di dalam blok `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Untuk *"Set a four minute 17 second timer."*, ini akan melakukan loop dua kali, memberikan nilai berikut:

    | jumlah loop | `number` | `time_unit` |
    | ----------- | -------- | ----------- |
    | 0           | 4        | minute      |
    | 1           | 17       | second      |

1. Di dalam loop ini, gunakan angka dan unit waktu untuk menghitung total waktu untuk timer, menambahkan 60 detik untuk setiap menit, dan jumlah detik untuk setiap detik.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Di luar loop melalui entitas, catat total waktu untuk timer:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Jumlah detik perlu dikembalikan dari fungsi sebagai respons HTTP. Di akhir blok `if`, tambahkan yang berikut:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Kode ini membuat payload yang berisi jumlah total detik untuk timer, mengonversinya menjadi string JSON, dan mengembalikannya sebagai hasil HTTP dengan kode status 200, yang berarti panggilan berhasil.

1. Terakhir, di luar blok `if`, tangani jika intent tidak dikenali dengan mengembalikan kode error:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 adalah kode status untuk *not found*.

1. Jalankan aplikasi fungsi dan uji menggunakan curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Ganti `<text>` dengan teks permintaan Anda, misalnya `set a 2 minutes 27 second timer`.

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

    Panggilan ke curl akan mengembalikan yang berikut:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Jumlah detik untuk timer ada di nilai `"seconds"`.

> 💁 Anda dapat menemukan kode ini di folder [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Tugas - buat fungsi Anda tersedia untuk perangkat IoT Anda

1. Agar perangkat IoT Anda dapat memanggil endpoint REST Anda, perangkat tersebut perlu mengetahui URL-nya. Saat Anda mengaksesnya sebelumnya, Anda menggunakan `localhost`, yang merupakan pintasan untuk mengakses endpoint REST di mesin lokal Anda. Untuk memungkinkan perangkat IoT Anda mendapatkan akses, Anda perlu mempublikasikan ke cloud, atau mendapatkan alamat IP Anda untuk mengaksesnya secara lokal.

    > ⚠️ Jika Anda menggunakan Wio Terminal, lebih mudah menjalankan aplikasi fungsi secara lokal, karena akan ada dependensi pada pustaka yang berarti Anda tidak dapat menerapkan aplikasi fungsi dengan cara yang sama seperti sebelumnya. Jalankan aplikasi fungsi secara lokal dan akses melalui alamat IP komputer Anda. Jika Anda ingin menerapkan ke cloud, informasi akan diberikan dalam pelajaran berikutnya tentang cara melakukannya.

    * Publikasikan aplikasi Functions - ikuti instruksi dalam pelajaran sebelumnya untuk mempublikasikan aplikasi fungsi Anda ke cloud. Setelah dipublikasikan, URL akan berupa `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, di mana `<APP_NAME>` adalah nama aplikasi fungsi Anda. Pastikan juga untuk mempublikasikan pengaturan lokal Anda.

      Saat bekerja dengan pemicu HTTP, mereka diamankan secara default dengan kunci aplikasi fungsi. Untuk mendapatkan kunci ini, jalankan perintah berikut:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Salin nilai entri `default` dari bagian `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Kunci ini perlu ditambahkan sebagai parameter kueri ke URL, sehingga URL akhir akan berupa `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, di mana `<APP_NAME>` adalah nama aplikasi fungsi Anda, dan `<FUNCTION_KEY>` adalah kunci fungsi default Anda.

      > 💁 Anda dapat mengubah jenis otorisasi pemicu HTTP menggunakan pengaturan `authlevel` di file `function.json`. Anda dapat membaca lebih lanjut tentang ini di [bagian konfigurasi dokumentasi pemicu HTTP Azure Functions di Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Jalankan aplikasi fungsi secara lokal, dan akses menggunakan alamat IP - Anda dapat mendapatkan alamat IP komputer Anda di jaringan lokal, dan menggunakannya untuk membangun URL.

      Temukan alamat IP Anda:

      * Di Windows 10, ikuti panduan [temukan alamat IP Anda](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Di macOS, ikuti panduan [cara menemukan alamat IP Anda di Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Di Linux, ikuti bagian tentang menemukan alamat IP pribadi Anda di [cara menemukan alamat IP Anda di Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Setelah Anda memiliki alamat IP, Anda akan dapat mengakses fungsi di `http://`.
<ALAMAT_IP>
:7071/api/text-to-timer`, di mana `<IP_ADDRESS>` adalah alamat IP Anda, contohnya `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Perhatikan bahwa ini menggunakan port 7071, jadi setelah alamat IP Anda perlu menambahkan `:7071`.

      > 💁 Ini hanya akan berfungsi jika perangkat IoT Anda berada di jaringan yang sama dengan komputer Anda.

1. Uji endpoint dengan mengaksesnya menggunakan curl.

---

## 🚀 Tantangan

Ada banyak cara untuk meminta hal yang sama, seperti mengatur timer. Pikirkan berbagai cara untuk melakukan ini, dan gunakan sebagai contoh dalam aplikasi LUIS Anda. Uji ini untuk melihat seberapa baik model Anda dapat menangani berbagai cara permintaan timer.

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang LUIS dan kemampuannya di [halaman dokumentasi Language Understanding (LUIS) di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Baca lebih lanjut tentang pemahaman bahasa di [halaman pemahaman bahasa alami di Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Baca lebih lanjut tentang pemicu HTTP di [dokumentasi pemicu HTTP Azure Functions di Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Tugas

[Batalkan timer](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.