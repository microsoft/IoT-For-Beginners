<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T21:41:24+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "id"
}
-->
# Migrasikan Logika Aplikasi Anda ke Cloud

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Pelajaran ini diajarkan sebagai bagian dari [Proyek IoT untuk Pemula - Seri Pertanian Digital](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Kontrol perangkat IoT Anda dengan kode tanpa server](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Pendahuluan

Pada pelajaran sebelumnya, Anda telah belajar cara menghubungkan pemantauan kelembapan tanah tanaman dan kontrol relay ke layanan IoT berbasis cloud. Langkah berikutnya adalah memindahkan kode server yang mengontrol waktu relay ke cloud. Dalam pelajaran ini, Anda akan belajar cara melakukannya menggunakan fungsi tanpa server.

Dalam pelajaran ini kita akan membahas:

* [Apa itu tanpa server?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Membuat aplikasi tanpa server](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Membuat pemicu acara IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Mengirim permintaan metode langsung dari kode tanpa server](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Menyebarkan kode tanpa server Anda ke cloud](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Apa itu tanpa server?

Tanpa server, atau komputasi tanpa server, melibatkan pembuatan blok kode kecil yang dijalankan di cloud sebagai respons terhadap berbagai jenis acara. Ketika acara terjadi, kode Anda dijalankan dan diberikan data tentang acara tersebut. Acara ini dapat berasal dari berbagai hal, termasuk permintaan web, pesan yang dimasukkan ke dalam antrean, perubahan data dalam database, atau pesan yang dikirim ke layanan IoT oleh perangkat IoT.

![Acara yang dikirim dari layanan IoT ke layanan tanpa server, semuanya diproses secara bersamaan oleh beberapa fungsi yang dijalankan](../../../../../translated_images/id/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 Jika Anda pernah menggunakan pemicu database sebelumnya, Anda dapat menganggap ini sebagai hal yang sama, yaitu kode yang dipicu oleh acara seperti memasukkan baris.

![Ketika banyak acara dikirim secara bersamaan, layanan tanpa server meningkat untuk menjalankan semuanya secara bersamaan](../../../../../translated_images/id/serverless-scaling.f8c769adf0413fd1.webp)

Kode Anda hanya dijalankan ketika acara terjadi, tidak ada yang menjaga kode Anda tetap aktif di waktu lain. Acara terjadi, kode Anda dimuat dan dijalankan. Ini membuat tanpa server sangat skalabel - jika banyak acara terjadi secara bersamaan, penyedia cloud dapat menjalankan fungsi Anda sebanyak yang Anda butuhkan secara bersamaan di berbagai server yang tersedia. Kekurangannya adalah jika Anda perlu berbagi informasi antar acara, Anda harus menyimpannya di tempat lain seperti database daripada menyimpannya di memori.

Kode Anda ditulis sebagai fungsi yang mengambil detail tentang acara sebagai parameter. Anda dapat menggunakan berbagai bahasa pemrograman untuk menulis fungsi tanpa server ini.

> 🎓 Tanpa server juga disebut sebagai Functions as a Service (FaaS) karena setiap pemicu acara diimplementasikan sebagai fungsi dalam kode.

Meskipun namanya tanpa server, sebenarnya menggunakan server. Penamaan ini karena Anda sebagai pengembang tidak perlu peduli tentang server yang diperlukan untuk menjalankan kode Anda, yang Anda pedulikan hanyalah bahwa kode Anda dijalankan sebagai respons terhadap acara. Penyedia cloud memiliki *runtime* tanpa server yang mengelola alokasi server, jaringan, penyimpanan, CPU, memori, dan semua hal lain yang diperlukan untuk menjalankan kode Anda. Model ini berarti Anda tidak dapat membayar per server untuk layanan tersebut, karena tidak ada server. Sebaliknya, Anda membayar untuk waktu kode Anda berjalan dan jumlah memori yang digunakan.

> 💰 Tanpa server adalah salah satu cara termurah untuk menjalankan kode di cloud. Misalnya, pada saat penulisan, satu penyedia cloud memungkinkan semua fungsi tanpa server Anda dijalankan sebanyak 1.000.000 kali per bulan sebelum mereka mulai mengenakan biaya, dan setelah itu mereka mengenakan biaya US$0,20 untuk setiap 1.000.000 eksekusi. Ketika kode Anda tidak berjalan, Anda tidak membayar.

Sebagai pengembang IoT, model tanpa server sangat ideal. Anda dapat menulis fungsi yang dipanggil sebagai respons terhadap pesan yang dikirim dari perangkat IoT mana pun yang terhubung ke layanan IoT yang dihosting di cloud. Kode Anda akan menangani semua pesan yang dikirim, tetapi hanya berjalan saat diperlukan.

✅ Lihat kembali kode yang Anda tulis sebagai kode server yang mendengarkan pesan melalui MQTT. Bagaimana ini dapat berjalan di cloud menggunakan tanpa server? Bagaimana menurut Anda kode tersebut mungkin perlu diubah untuk mendukung komputasi tanpa server?

> 💁 Model tanpa server sedang bergerak ke layanan cloud lainnya selain menjalankan kode. Misalnya, database tanpa server tersedia di cloud menggunakan model harga tanpa server di mana Anda membayar per permintaan yang dilakukan terhadap database, seperti kueri atau penyisipan, biasanya menggunakan harga berdasarkan seberapa banyak pekerjaan yang dilakukan untuk melayani permintaan tersebut. Misalnya, satu perintah select untuk satu baris terhadap kunci utama akan lebih murah daripada operasi yang rumit yang menggabungkan banyak tabel dan mengembalikan ribuan baris.

## Membuat aplikasi tanpa server

Layanan komputasi tanpa server dari Microsoft disebut Azure Functions.

![Logo Azure Functions](../../../../../translated_images/id/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

Video pendek di bawah ini memberikan gambaran tentang Azure Functions.

[![Video gambaran Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Klik gambar di atas untuk menonton video

✅ Luangkan waktu untuk melakukan penelitian dan baca gambaran umum Azure Functions di [dokumentasi Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Untuk menulis Azure Functions, Anda memulai dengan aplikasi Azure Functions dalam bahasa pilihan Anda. Secara default, Azure Functions mendukung Python, JavaScript, TypeScript, C#, F#, Java, dan Powershell. Dalam pelajaran ini, Anda akan belajar cara menulis aplikasi Azure Functions dalam Python.

> 💁 Azure Functions juga mendukung custom handlers sehingga Anda dapat menulis fungsi Anda dalam bahasa apa pun yang mendukung permintaan HTTP, termasuk bahasa lama seperti COBOL.

Aplikasi fungsi terdiri dari satu atau lebih *pemicu* - fungsi yang merespons acara. Anda dapat memiliki beberapa pemicu dalam satu aplikasi fungsi, semuanya berbagi konfigurasi umum. Misalnya, dalam file konfigurasi untuk aplikasi Functions Anda, Anda dapat memiliki detail koneksi IoT Hub Anda, dan semua fungsi dalam aplikasi dapat menggunakan ini untuk terhubung dan mendengarkan acara.

### Tugas - instal alat Azure Functions

> Pada saat penulisan, alat kode Azure Functions belum sepenuhnya berfungsi pada Apple Silicon dengan proyek Python. Anda perlu menggunakan Mac berbasis Intel, PC Windows, atau PC Linux sebagai gantinya.

Salah satu fitur hebat dari Azure Functions adalah Anda dapat menjalankannya secara lokal. Runtime yang sama yang digunakan di cloud dapat dijalankan di komputer Anda, memungkinkan Anda menulis kode yang merespons pesan IoT dan menjalankannya secara lokal. Anda bahkan dapat melakukan debug kode Anda saat acara ditangani. Setelah Anda puas dengan kode Anda, kode tersebut dapat disebarkan ke cloud.

Alat Azure Functions tersedia sebagai CLI, yang dikenal sebagai Azure Functions Core Tools.

1. Instal alat inti Azure Functions dengan mengikuti petunjuk di [dokumentasi Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Instal ekstensi Azure Functions untuk VS Code. Ekstensi ini menyediakan dukungan untuk membuat, melakukan debug, dan menyebarkan fungsi Azure. Lihat [dokumentasi ekstensi Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) untuk petunjuk tentang cara menginstal ekstensi ini di VS Code.

Ketika Anda menyebarkan aplikasi Azure Functions Anda ke cloud, aplikasi tersebut perlu menggunakan sedikit penyimpanan cloud untuk menyimpan hal-hal seperti file aplikasi dan file log. Ketika Anda menjalankan aplikasi Functions Anda secara lokal, Anda tetap perlu terhubung ke penyimpanan cloud, tetapi alih-alih menggunakan penyimpanan cloud yang sebenarnya, Anda dapat menggunakan emulator penyimpanan yang disebut [Azurite](https://github.com/Azure/Azurite). Emulator ini berjalan secara lokal tetapi bertindak seperti penyimpanan cloud.

> 🎓 Di Azure, penyimpanan yang digunakan Azure Functions adalah Azure Storage Account. Akun ini dapat menyimpan file, blob, data dalam tabel, atau data dalam antrean. Anda dapat berbagi satu akun penyimpanan antara banyak aplikasi, seperti aplikasi Functions dan aplikasi web.

1. Azurite adalah aplikasi Node.js, jadi Anda perlu menginstal Node.js. Anda dapat menemukan unduhan dan petunjuk instalasi di [situs web Node.js](https://nodejs.org/). Jika Anda menggunakan Mac, Anda juga dapat menginstalnya dari [Homebrew](https://formulae.brew.sh/formula/node).

1. Instal Azurite menggunakan perintah berikut (`npm` adalah alat yang diinstal saat Anda menginstal Node.js):

    ```sh
    npm install -g azurite
    ```

1. Buat folder bernama `azurite` untuk digunakan Azurite menyimpan data:

    ```sh
    mkdir azurite
    ```

1. Jalankan Azurite, dengan memberikan folder baru ini:

    ```sh
    azurite --location azurite
    ```

    Emulator penyimpanan Azurite akan diluncurkan dan siap untuk runtime Functions lokal untuk terhubung.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Tugas - buat proyek Azure Functions

CLI Azure Functions dapat digunakan untuk membuat aplikasi Functions baru.

1. Buat folder untuk aplikasi Functions Anda dan navigasikan ke dalamnya. Beri nama `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Buat lingkungan virtual Python di dalam folder ini:

    ```sh
    python3 -m venv .venv
    ```

1. Aktifkan lingkungan virtual:

    * Di Windows:
        * Jika Anda menggunakan Command Prompt, atau Command Prompt melalui Windows Terminal, jalankan:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jika Anda menggunakan PowerShell, jalankan:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Di macOS atau Linux, jalankan:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Perintah ini harus dijalankan dari lokasi yang sama di mana Anda menjalankan perintah untuk membuat lingkungan virtual. Anda tidak perlu pernah menavigasi ke dalam folder `.venv`, Anda harus selalu menjalankan perintah aktivasi dan perintah apa pun untuk menginstal paket atau menjalankan kode dari folder tempat Anda berada saat membuat lingkungan virtual.

1. Jalankan perintah berikut untuk membuat aplikasi Functions di dalam folder ini:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Ini akan membuat tiga file di dalam folder saat ini:

    * `host.json` - dokumen JSON ini berisi pengaturan untuk aplikasi Functions Anda. Anda tidak perlu memodifikasi pengaturan ini.
    * `local.settings.json` - dokumen JSON ini berisi pengaturan yang akan digunakan aplikasi Anda saat berjalan secara lokal, seperti string koneksi untuk IoT Hub Anda. Pengaturan ini hanya lokal, dan tidak boleh ditambahkan ke kontrol kode sumber. Ketika Anda menyebarkan aplikasi ke cloud, pengaturan ini tidak disebarkan, melainkan pengaturan Anda dimuat dari pengaturan aplikasi. Ini akan dibahas lebih lanjut dalam pelajaran ini.
    * `requirements.txt` - ini adalah [file persyaratan Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) yang berisi paket Pip yang diperlukan untuk menjalankan aplikasi Functions Anda.

1. File `local.settings.json` memiliki pengaturan untuk akun penyimpanan yang akan digunakan aplikasi Functions. Ini default ke pengaturan kosong, jadi perlu diatur. Untuk terhubung ke emulator penyimpanan lokal Azurite, atur nilai ini ke:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Instal paket Pip yang diperlukan menggunakan file persyaratan:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Paket Pip yang diperlukan harus ada di file ini, sehingga ketika aplikasi Functions disebarkan ke cloud, runtime dapat memastikan bahwa ia menginstal paket yang benar.

1. Untuk menguji apakah semuanya berfungsi dengan benar, Anda dapat memulai runtime Functions. Jalankan perintah berikut untuk melakukannya:

    ```sh
    func start
    ```

    Anda akan melihat runtime mulai dan melaporkan bahwa ia tidak menemukan fungsi pekerjaan apa pun (pemicu).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Jika Anda menerima pemberitahuan firewall, berikan akses karena aplikasi `func` perlu dapat membaca dan menulis ke jaringan Anda.
> ⚠️ Jika Anda menggunakan macOS, mungkin ada peringatan dalam output:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Anda dapat mengabaikannya selama aplikasi Functions berjalan dengan benar dan menampilkan fungsi yang sedang berjalan. Seperti yang disebutkan dalam [pertanyaan ini di Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), peringatan ini dapat diabaikan.

1. Hentikan aplikasi Functions dengan menekan `ctrl+c`.

1. Buka folder saat ini di VS Code, baik dengan membuka VS Code lalu membuka folder ini, atau dengan menjalankan perintah berikut:

    ```sh
    code .
    ```

    VS Code akan mendeteksi proyek Functions Anda dan menampilkan notifikasi yang mengatakan:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Notifikasi](../../../../../translated_images/id/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Pilih **Yes** dari notifikasi ini.

1. Pastikan lingkungan virtual Python berjalan di terminal VS Code. Hentikan dan mulai ulang jika diperlukan.

## Membuat Trigger Event IoT Hub

Aplikasi Functions adalah kerangka kerja untuk kode serverless Anda. Untuk merespons event IoT Hub, Anda dapat menambahkan trigger IoT Hub ke aplikasi ini. Trigger ini perlu terhubung ke aliran pesan yang dikirim ke IoT Hub dan meresponsnya. Untuk mendapatkan aliran pesan ini, trigger Anda perlu terhubung ke *event hub compatible endpoint* dari IoT Hub.

IoT Hub didasarkan pada layanan Azure lain yang disebut Azure Event Hubs. Event Hubs adalah layanan yang memungkinkan Anda mengirim dan menerima pesan, sementara IoT Hub memperluasnya dengan menambahkan fitur untuk perangkat IoT. Cara Anda terhubung untuk membaca pesan dari IoT Hub sama seperti jika Anda menggunakan Event Hubs.

✅ Lakukan penelitian: Baca ikhtisar Event Hubs di [dokumentasi Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Bagaimana fitur dasarnya dibandingkan dengan IoT Hub?

Agar perangkat IoT dapat terhubung ke IoT Hub, perangkat tersebut harus menggunakan kunci rahasia yang memastikan hanya perangkat yang diizinkan yang dapat terhubung. Hal yang sama berlaku saat terhubung untuk membaca pesan; kode Anda memerlukan string koneksi yang berisi kunci rahasia, bersama dengan detail IoT Hub.

> 💁 String koneksi default yang Anda dapatkan memiliki izin **iothubowner**, yang memberikan kode apa pun yang menggunakannya izin penuh pada IoT Hub. Idealnya, Anda harus terhubung dengan tingkat izin terendah yang diperlukan. Ini akan dibahas dalam pelajaran berikutnya.

Setelah trigger Anda terhubung, kode di dalam fungsi akan dipanggil untuk setiap pesan yang dikirim ke IoT Hub, terlepas dari perangkat mana yang mengirimnya. Trigger akan menerima pesan sebagai parameter.

### Tugas - mendapatkan string koneksi endpoint Event Hub compatible

1. Dari terminal VS Code, jalankan perintah berikut untuk mendapatkan string koneksi untuk endpoint Event Hub compatible dari IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Ganti `<hub_name>` dengan nama yang Anda gunakan untuk IoT Hub Anda.

1. Di VS Code, buka file `local.settings.json`. Tambahkan nilai tambahan berikut di dalam bagian `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Ganti `<connection string>` dengan nilai dari langkah sebelumnya. Anda perlu menambahkan koma setelah baris di atas agar ini menjadi JSON yang valid.

### Tugas - membuat trigger event

Sekarang Anda siap untuk membuat trigger event.

1. Dari terminal VS Code, jalankan perintah berikut dari dalam folder `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Ini akan membuat Fungsi baru bernama `iot-hub-trigger`. Trigger ini akan terhubung ke endpoint Event Hub compatible di IoT Hub, sehingga Anda dapat menggunakan trigger event hub. Tidak ada trigger khusus untuk IoT Hub.

Ini akan membuat folder di dalam folder `soil-moisture-trigger` bernama `iot-hub-trigger` yang berisi fungsi ini. Folder ini akan memiliki file berikut di dalamnya:

* `__init__.py` - ini adalah file kode Python yang berisi trigger, menggunakan konvensi penamaan file Python standar untuk mengubah folder ini menjadi modul Python.

    File ini akan berisi kode berikut:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Inti dari trigger adalah fungsi `main`. Fungsi inilah yang dipanggil dengan event dari IoT Hub. Fungsi ini memiliki parameter bernama `event` yang berisi `EventHubEvent`. Setiap kali pesan dikirim ke IoT Hub, fungsi ini dipanggil dengan pesan tersebut sebagai `event`, bersama dengan properti yang sama seperti anotasi yang Anda lihat di pelajaran sebelumnya.

    Inti dari fungsi ini adalah mencatat event.

* `function.json` - ini berisi konfigurasi untuk trigger. Konfigurasi utama ada di bagian bernama `bindings`. Binding adalah istilah untuk koneksi antara Azure Functions dan layanan Azure lainnya. Fungsi ini memiliki input binding ke event hub - ia terhubung ke event hub dan menerima data.

    > 💁 Anda juga dapat memiliki output binding sehingga output dari fungsi dikirim ke layanan lain. Misalnya, Anda dapat menambahkan output binding ke database dan mengembalikan event IoT Hub dari fungsi, dan itu akan secara otomatis dimasukkan ke dalam database.

    ✅ Lakukan penelitian: Baca tentang binding di [dokumentasi konsep triggers dan bindings Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Bagian `bindings` mencakup konfigurasi untuk binding. Nilai-nilai yang menarik adalah:

  * `"type": "eventHubTrigger"` - ini memberi tahu fungsi bahwa ia perlu mendengarkan event dari Event Hub
  * `"name": "events"` - ini adalah nama parameter untuk event Event Hub. Ini sesuai dengan nama parameter dalam fungsi `main` di kode Python.
  * `"direction": "in"` - ini adalah input binding, data dari event hub masuk ke fungsi
  * `"connection": ""` - ini mendefinisikan nama pengaturan untuk membaca string koneksi. Saat berjalan secara lokal, ini akan membaca pengaturan ini dari file `local.settings.json`.

    > 💁 String koneksi tidak dapat disimpan di file `function.json`, harus dibaca dari pengaturan. Ini untuk mencegah Anda secara tidak sengaja mengekspos string koneksi Anda.

1. Karena [bug dalam template Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), file `function.json` memiliki nilai yang salah untuk field `cardinality`. Perbarui field ini dari `many` menjadi `one`:

    ```json
    "cardinality": "one",
    ```

1. Perbarui nilai `"connection"` di file `function.json` untuk menunjuk ke nilai baru yang Anda tambahkan ke file `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Ingat - ini harus menunjuk ke pengaturan, bukan berisi string koneksi sebenarnya.

1. String koneksi berisi nilai `eventHubName`, jadi nilai ini di file `function.json` perlu dikosongkan. Perbarui nilai ini menjadi string kosong:

    ```json
    "eventHubName": "",
    ```

### Tugas - menjalankan trigger event

1. Pastikan Anda tidak menjalankan monitor event IoT Hub. Jika ini berjalan bersamaan dengan aplikasi Functions, aplikasi Functions tidak akan dapat terhubung dan mengonsumsi event.

    > 💁 Beberapa aplikasi dapat terhubung ke endpoint IoT Hub menggunakan *consumer groups* yang berbeda. Ini akan dibahas dalam pelajaran berikutnya.

1. Untuk menjalankan aplikasi Functions, jalankan perintah berikut dari terminal VS Code:

    ```sh
    func start
    ```

    Aplikasi Functions akan mulai, dan akan mendeteksi fungsi `iot-hub-trigger`. Aplikasi ini kemudian akan memproses event apa pun yang telah dikirim ke IoT Hub dalam satu hari terakhir.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Setiap panggilan ke fungsi akan dikelilingi oleh blok `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` di output, sehingga Anda dapat melihat berapa banyak pesan yang diproses dalam setiap panggilan fungsi.

1. Pastikan perangkat IoT Anda berjalan. Anda akan melihat pesan kelembapan tanah baru muncul di aplikasi Functions.

1. Hentikan dan mulai ulang aplikasi Functions. Anda akan melihat bahwa aplikasi ini tidak akan memproses pesan sebelumnya lagi, hanya pesan baru yang akan diproses.

> 💁 VS Code juga mendukung debugging untuk Functions Anda. Anda dapat menetapkan breakpoint dengan mengklik pada tepi di awal setiap baris kode, atau meletakkan kursor pada baris kode dan memilih *Run -> Toggle breakpoint*, atau menekan `F9`. Anda dapat meluncurkan debugger dengan memilih *Run -> Start debugging*, menekan `F5`, atau memilih panel *Run and debug* dan memilih tombol **Start debugging**. Dengan melakukan ini, Anda dapat melihat detail dari event yang sedang diproses.

#### Pemecahan Masalah

* Jika Anda mendapatkan error berikut:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Periksa apakah Azurite berjalan dan Anda telah menetapkan `AzureWebJobsStorage` di file `local.settings.json` ke `UseDevelopmentStorage=true`.

* Jika Anda mendapatkan error berikut:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Periksa apakah Anda telah menetapkan `cardinality` di file `function.json` ke `one`.

* Jika Anda mendapatkan error berikut:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Periksa apakah Anda telah menetapkan `eventHubName` di file `function.json` ke string kosong.

## Mengirim Permintaan Metode Langsung dari Kode Serverless

Sejauh ini, aplikasi Functions Anda mendengarkan pesan dari IoT Hub menggunakan endpoint Event Hub compatible. Sekarang Anda perlu mengirim perintah ke perangkat IoT. Ini dilakukan dengan menggunakan koneksi berbeda ke IoT Hub melalui *Registry Manager*. Registry Manager adalah alat yang memungkinkan Anda melihat perangkat apa saja yang terdaftar di IoT Hub, dan berkomunikasi dengan perangkat-perangkat tersebut dengan mengirim pesan cloud-to-device, permintaan metode langsung, atau memperbarui device twin. Anda juga dapat menggunakannya untuk mendaftarkan, memperbarui, atau menghapus perangkat IoT dari IoT Hub.

Untuk terhubung ke Registry Manager, Anda memerlukan string koneksi.

### Tugas - mendapatkan string koneksi Registry Manager

1. Untuk mendapatkan string koneksi, jalankan perintah berikut:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Ganti `<hub_name>` dengan nama yang Anda gunakan untuk IoT Hub Anda.

    String koneksi diminta untuk kebijakan *ServiceConnect* menggunakan parameter `--policy-name service`. Saat Anda meminta string koneksi, Anda dapat menentukan izin apa yang akan diizinkan oleh string koneksi tersebut. Kebijakan ServiceConnect memungkinkan kode Anda terhubung dan mengirim pesan ke perangkat IoT.

    ✅ Lakukan penelitian: Baca tentang kebijakan yang berbeda di [dokumentasi izin IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Di VS Code, buka file `local.settings.json`. Tambahkan nilai tambahan berikut di dalam bagian `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Ganti `<connection string>` dengan nilai dari langkah sebelumnya. Anda perlu menambahkan koma setelah baris di atas agar ini menjadi JSON yang valid.

### Tugas - mengirim permintaan metode langsung ke perangkat

1. SDK untuk Registry Manager tersedia melalui paket Pip. Tambahkan baris berikut ke file `requirements.txt` untuk menambahkan dependensi pada paket ini:

    ```sh
    azure-iot-hub
    ```

1. Pastikan terminal VS Code memiliki lingkungan virtual yang diaktifkan, dan jalankan perintah berikut untuk menginstal paket Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Tambahkan impor berikut ke file `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Ini mengimpor beberapa pustaka sistem, serta pustaka untuk berinteraksi dengan Registry Manager dan mengirim permintaan metode langsung.

1. Hapus kode dari dalam metode `main`, tetapi pertahankan metode itu sendiri.

1. Dalam metode `main`, tambahkan kode berikut:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Kode ini mengekstrak isi dari event yang berisi pesan JSON yang dikirim oleh perangkat IoT.

    Kemudian mendapatkan ID perangkat dari anotasi yang diteruskan bersama pesan. Isi dari event berisi pesan yang dikirim sebagai telemetri, sedangkan kamus `iothub_metadata` berisi properti yang diatur oleh IoT Hub seperti ID perangkat pengirim dan waktu pengiriman pesan.

    Informasi ini kemudian dicatat. Anda akan melihat pencatatan ini di terminal saat Anda menjalankan aplikasi Function secara lokal.

1. Di bawah ini, tambahkan kode berikut:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Kode ini mendapatkan kelembapan tanah dari pesan. Kemudian memeriksa kelembapan tanah, dan tergantung pada nilainya, membuat kelas pembantu untuk permintaan metode langsung untuk metode `relay_on` atau `relay_off`. Permintaan metode tidak memerlukan payload, jadi dokumen JSON kosong dikirim.

1. Di bawah ini tambahkan kode berikut:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Kode ini memuat `REGISTRY_MANAGER_CONNECTION_STRING` dari file `local.settings.json`. Nilai-nilai dalam file ini tersedia sebagai variabel lingkungan, dan dapat dibaca menggunakan fungsi `os.environ`, sebuah fungsi yang mengembalikan dictionary dari semua variabel lingkungan.

> 💁 Ketika kode ini diterapkan ke cloud, nilai-nilai dalam file `local.settings.json` akan diatur sebagai *Application Settings*, dan dapat dibaca dari variabel lingkungan.

Kode kemudian membuat instance dari kelas pembantu Registry Manager menggunakan connection string.

1. Tambahkan kode berikut di bawah ini:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Kode ini memberi tahu registry manager untuk mengirim permintaan metode langsung ke perangkat yang mengirimkan telemetry.

    > 💁 Pada versi aplikasi yang Anda buat di pelajaran sebelumnya menggunakan MQTT, perintah kontrol relay dikirim ke semua perangkat. Kode tersebut mengasumsikan Anda hanya memiliki satu perangkat. Versi kode ini mengirimkan permintaan metode ke satu perangkat, sehingga akan berfungsi jika Anda memiliki beberapa pengaturan sensor kelembaban tanah dan relay, mengirimkan permintaan metode langsung yang tepat ke perangkat yang tepat.

1. Jalankan aplikasi Functions, dan pastikan perangkat IoT Anda mengirimkan data. Anda akan melihat pesan diproses dan permintaan metode langsung dikirim. Pindahkan sensor kelembaban tanah masuk dan keluar dari tanah untuk melihat nilai berubah dan relay menyala dan mati.

> 💁 Anda dapat menemukan kode ini di folder [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Terapkan kode serverless Anda ke cloud

Kode Anda sekarang berfungsi secara lokal, jadi langkah berikutnya adalah menerapkan aplikasi Functions ke cloud.

### Tugas - buat sumber daya cloud

Aplikasi Functions Anda perlu diterapkan ke sumber daya Functions App di Azure, yang berada di dalam Resource Group yang Anda buat untuk IoT Hub Anda. Anda juga perlu membuat Storage Account di Azure untuk menggantikan emulator yang Anda jalankan secara lokal.

1. Jalankan perintah berikut untuk membuat storage account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Ganti `<storage_name>` dengan nama untuk storage account Anda. Nama ini harus unik secara global karena menjadi bagian dari URL yang digunakan untuk mengakses storage account. Anda hanya dapat menggunakan huruf kecil dan angka untuk nama ini, tanpa karakter lain, dan dibatasi hingga 24 karakter. Gunakan sesuatu seperti `sms` dan tambahkan pengidentifikasi unik di akhir, seperti beberapa kata acak atau nama Anda.

    Opsi `--sku Standard_LRS` memilih tingkat harga, memilih akun tujuan umum dengan biaya terendah. Tidak ada tingkat gratis untuk penyimpanan, dan Anda membayar sesuai penggunaan. Biaya relatif rendah, dengan penyimpanan paling mahal kurang dari US$0.05 per bulan per gigabyte yang disimpan.

    ✅ Baca lebih lanjut tentang harga di [halaman harga Azure Storage Account](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Jalankan perintah berikut untuk membuat Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat Resource Group di pelajaran sebelumnya.

    Ganti `<storage_name>` dengan nama storage account yang Anda buat di langkah sebelumnya.

    Ganti `<functions_app_name>` dengan nama unik untuk Functions App Anda. Nama ini harus unik secara global karena menjadi bagian dari URL yang dapat digunakan untuk mengakses Functions App. Gunakan sesuatu seperti `soil-moisture-sensor-` dan tambahkan pengidentifikasi unik di akhir, seperti beberapa kata acak atau nama Anda.

    Opsi `--functions-version 3` mengatur versi Azure Functions yang akan digunakan. Versi 3 adalah versi terbaru.

    Opsi `--os-type Linux` memberi tahu runtime Functions untuk menggunakan Linux sebagai OS untuk menjalankan fungsi-fungsi ini. Functions dapat dijalankan di Linux atau Windows, tergantung pada bahasa pemrograman yang digunakan. Aplikasi Python hanya didukung di Linux.

### Tugas - unggah pengaturan aplikasi Anda

Saat Anda mengembangkan Functions App Anda, Anda menyimpan beberapa pengaturan di file `local.settings.json` untuk connection string ke IoT Hub Anda. Pengaturan ini perlu ditulis ke Application Settings di Functions App Anda di Azure agar dapat digunakan oleh kode Anda.

> 🎓 File `local.settings.json` hanya untuk pengaturan pengembangan lokal, dan tidak boleh dimasukkan ke dalam kontrol kode sumber, seperti GitHub. Ketika diterapkan ke cloud, Application Settings digunakan. Application Settings adalah pasangan key/value yang di-host di cloud dan dibaca dari variabel lingkungan baik di dalam kode Anda atau oleh runtime saat menghubungkan kode Anda ke IoT Hub.

1. Jalankan perintah berikut untuk mengatur pengaturan `IOT_HUB_CONNECTION_STRING` di Application Settings Functions App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Ganti `<functions_app_name>` dengan nama yang Anda gunakan untuk Functions App Anda.

    Ganti `<connection string>` dengan nilai `IOT_HUB_CONNECTION_STRING` dari file `local.settings.json` Anda.

1. Ulangi langkah di atas, tetapi atur nilai `REGISTRY_MANAGER_CONNECTION_STRING` ke nilai yang sesuai dari file `local.settings.json` Anda.

Ketika Anda menjalankan perintah ini, mereka juga akan menghasilkan daftar semua Application Settings untuk Functions App. Anda dapat menggunakan ini untuk memeriksa apakah nilai-nilai Anda diatur dengan benar.

> 💁 Anda akan melihat nilai yang sudah diatur untuk `AzureWebJobsStorage`. Di file `local.settings.json` Anda, ini diatur ke nilai untuk menggunakan emulator penyimpanan lokal. Ketika Anda membuat Functions App, Anda memberikan storage account sebagai parameter, dan ini diatur secara otomatis dalam pengaturan ini.

### Tugas - terapkan Functions App Anda ke cloud

Sekarang Functions App sudah siap, kode Anda dapat diterapkan.

1. Jalankan perintah berikut dari terminal VS Code untuk mempublikasikan Functions App Anda:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Ganti `<functions_app_name>` dengan nama yang Anda gunakan untuk Functions App Anda.

Kode akan dikemas dan dikirim ke Functions App, di mana kode tersebut akan diterapkan dan dijalankan. Akan ada banyak output konsol, diakhiri dengan konfirmasi penerapan dan daftar fungsi yang diterapkan. Dalam kasus ini, daftar hanya akan berisi trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Pastikan perangkat IoT Anda berjalan. Ubah tingkat kelembaban dengan menyesuaikan kelembaban tanah, atau memindahkan sensor masuk dan keluar dari tanah. Anda akan melihat relay menyala dan mati saat kelembaban tanah berubah.

---

## 🚀 Tantangan

Pada pelajaran sebelumnya, Anda mengelola waktu untuk relay dengan berhenti berlangganan dari pesan MQTT saat relay menyala, dan untuk beberapa saat setelah relay dimatikan. Anda tidak dapat menggunakan metode ini di sini - Anda tidak dapat berhenti berlangganan dari trigger IoT Hub Anda.

Pikirkan cara berbeda yang dapat Anda gunakan untuk menangani ini di Functions App Anda.

## Kuis setelah pelajaran

[Kuis setelah pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Tinjauan & Studi Mandiri

* Baca tentang komputasi serverless di [halaman Serverless Computing di Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Baca tentang penggunaan serverless di Azure termasuk beberapa contoh lainnya di [posting blog Azure Go serverless for your IoT needs](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Pelajari lebih lanjut tentang Azure Functions di [saluran YouTube Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Tugas

[Tambahkan kontrol relay manual](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.