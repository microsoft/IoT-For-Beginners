<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-27T23:53:25+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "id"
}
-->
# Data Lokasi Toko

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.id.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Pendahuluan

Pada pelajaran sebelumnya, Anda telah mempelajari cara menggunakan sensor GPS untuk menangkap data lokasi. Untuk menggunakan data ini dalam memvisualisasikan lokasi truk yang membawa makanan dan perjalanannya, data tersebut perlu dikirim ke layanan IoT di cloud, lalu disimpan di suatu tempat.

Dalam pelajaran ini, Anda akan mempelajari berbagai cara untuk menyimpan data IoT, serta cara menyimpan data dari layanan IoT Anda menggunakan kode tanpa server.

Dalam pelajaran ini, kita akan membahas:

* [Data terstruktur dan tidak terstruktur](../../../../../3-transport/lessons/2-store-location-data)
* [Mengirim data GPS ke IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Jalur panas, hangat, dan dingin](../../../../../3-transport/lessons/2-store-location-data)
* [Menangani peristiwa GPS menggunakan kode tanpa server](../../../../../3-transport/lessons/2-store-location-data)
* [Akun Penyimpanan Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Menghubungkan kode tanpa server ke penyimpanan](../../../../../3-transport/lessons/2-store-location-data)

## Data Terstruktur dan Tidak Terstruktur

Sistem komputer menangani data, dan data ini hadir dalam berbagai bentuk dan ukuran. Data dapat berupa angka tunggal, teks dalam jumlah besar, video dan gambar, hingga data IoT. Data biasanya dapat dibagi menjadi dua kategori - *data terstruktur* dan *data tidak terstruktur*.

* **Data terstruktur** adalah data dengan struktur yang jelas dan kaku yang tidak berubah, biasanya berupa tabel data dengan hubungan tertentu. Contohnya adalah detail seseorang seperti nama, tanggal lahir, dan alamat.

* **Data tidak terstruktur** adalah data tanpa struktur yang jelas dan kaku, termasuk data yang sering berubah strukturnya. Contohnya adalah dokumen seperti dokumen tertulis atau spreadsheet.

✅ Lakukan penelitian: Bisakah Anda memikirkan contoh lain dari data terstruktur dan tidak terstruktur?

> 💁 Ada juga data semi-terstruktur yang memiliki struktur tetapi tidak sesuai dengan tabel data yang tetap.

Data IoT biasanya dianggap sebagai data tidak terstruktur.

Bayangkan Anda menambahkan perangkat IoT ke armada kendaraan untuk sebuah pertanian komersial besar. Anda mungkin ingin menggunakan perangkat yang berbeda untuk jenis kendaraan yang berbeda. Misalnya:

* Untuk kendaraan pertanian seperti traktor, Anda ingin data GPS untuk memastikan mereka bekerja di ladang yang benar.
* Untuk truk pengiriman yang mengangkut makanan ke gudang, Anda ingin data GPS serta data kecepatan dan percepatan untuk memastikan pengemudi mengemudi dengan aman, serta data identitas pengemudi dan waktu mulai/berhenti untuk memastikan kepatuhan terhadap undang-undang kerja setempat.
* Untuk truk berpendingin, Anda juga ingin data suhu untuk memastikan makanan tidak terlalu panas atau dingin sehingga rusak selama perjalanan.

Data ini dapat berubah secara konstan. Misalnya, jika perangkat IoT berada di kabin truk, maka data yang dikirimkan dapat berubah saat trailer berubah, misalnya hanya mengirimkan data suhu saat trailer berpendingin digunakan.

✅ Data IoT apa lagi yang mungkin dapat ditangkap? Pikirkan tentang jenis muatan yang dapat dibawa oleh truk, serta data perawatan.

Data ini bervariasi dari kendaraan ke kendaraan, tetapi semuanya dikirim ke layanan IoT yang sama untuk diproses. Layanan IoT perlu dapat memproses data tidak terstruktur ini, menyimpannya dengan cara yang memungkinkan pencarian atau analisis, tetapi tetap dapat bekerja dengan struktur data yang berbeda.

### Penyimpanan SQL vs NoSQL

Database adalah layanan yang memungkinkan Anda menyimpan dan melakukan kueri data. Database terbagi menjadi dua jenis - SQL dan NoSQL.

#### Database SQL

Database pertama adalah Sistem Manajemen Database Relasional (RDBMS), atau database relasional. Database ini juga dikenal sebagai database SQL karena menggunakan Structured Query Language (SQL) untuk menambahkan, menghapus, memperbarui, atau melakukan kueri data. Database ini terdiri dari skema - serangkaian tabel data yang terdefinisi dengan baik, mirip dengan spreadsheet. Setiap tabel memiliki beberapa kolom bernama. Ketika Anda memasukkan data, Anda menambahkan baris ke tabel, menempatkan nilai ke dalam setiap kolom. Ini menjaga data dalam struktur yang sangat kaku - meskipun Anda dapat membiarkan kolom kosong, jika Anda ingin menambahkan kolom baru, Anda harus melakukannya di database, mengisi nilai untuk baris yang sudah ada. Database ini bersifat relasional - di mana satu tabel dapat memiliki hubungan dengan tabel lain.

![Database relasional dengan ID tabel Pengguna yang berhubungan dengan kolom ID pengguna di tabel pembelian, dan ID tabel produk yang berhubungan dengan ID produk di tabel pembelian](../../../../../translated_images/sql-database.be160f12bfccefd3.id.png)

Sebagai contoh, jika Anda menyimpan detail pribadi pengguna dalam tabel, Anda akan memiliki semacam ID unik internal per pengguna yang digunakan dalam baris di tabel yang berisi nama dan alamat pengguna. Jika Anda kemudian ingin menyimpan detail lain tentang pengguna tersebut, seperti pembelian mereka, dalam tabel lain, Anda akan memiliki satu kolom di tabel baru untuk ID pengguna tersebut. Ketika Anda mencari pengguna, Anda dapat menggunakan ID mereka untuk mendapatkan detail pribadi dari satu tabel, dan pembelian mereka dari tabel lain.

Database SQL sangat ideal untuk menyimpan data terstruktur, dan untuk memastikan data sesuai dengan skema Anda.

✅ Jika Anda belum pernah menggunakan SQL sebelumnya, luangkan waktu untuk membaca tentangnya di [halaman SQL di Wikipedia](https://wikipedia.org/wiki/SQL).

Beberapa database SQL yang terkenal adalah Microsoft SQL Server, MySQL, dan PostgreSQL.

✅ Lakukan penelitian: Bacalah tentang beberapa database SQL ini dan kemampuannya.

#### Database NoSQL

Database NoSQL disebut NoSQL karena tidak memiliki struktur kaku seperti database SQL. Database ini juga dikenal sebagai database dokumen karena dapat menyimpan data tidak terstruktur seperti dokumen.

> 💁 Meskipun namanya NoSQL, beberapa database NoSQL memungkinkan Anda menggunakan SQL untuk melakukan kueri data.

![Dokumen dalam folder di database NoSQL](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.id.png)

Database NoSQL tidak memiliki skema yang telah ditentukan sebelumnya yang membatasi cara data disimpan, melainkan Anda dapat memasukkan data tidak terstruktur apa pun, biasanya menggunakan dokumen JSON. Dokumen-dokumen ini dapat diatur ke dalam folder, mirip dengan file di komputer Anda. Setiap dokumen dapat memiliki bidang yang berbeda dari dokumen lainnya - misalnya jika Anda menyimpan data IoT dari kendaraan pertanian Anda, beberapa mungkin memiliki bidang untuk data akselerometer dan kecepatan, sementara yang lain mungkin memiliki bidang untuk suhu di trailer. Jika Anda menambahkan jenis truk baru, seperti yang memiliki timbangan bawaan untuk melacak berat hasil panen yang dibawa, maka perangkat IoT Anda dapat menambahkan bidang baru ini dan dapat disimpan tanpa perubahan pada database.

Beberapa database NoSQL yang terkenal termasuk Azure CosmosDB, MongoDB, dan CouchDB.

✅ Lakukan penelitian: Bacalah tentang beberapa database NoSQL ini dan kemampuannya.

Dalam pelajaran ini, Anda akan menggunakan penyimpanan NoSQL untuk menyimpan data IoT.

## Mengirim Data GPS ke IoT Hub

Pada pelajaran sebelumnya, Anda telah menangkap data GPS dari sensor GPS yang terhubung ke perangkat IoT Anda. Untuk menyimpan data IoT ini di cloud, Anda perlu mengirimkannya ke layanan IoT. Sekali lagi, Anda akan menggunakan Azure IoT Hub, layanan IoT cloud yang sama yang Anda gunakan dalam proyek sebelumnya.

![Mengirim telemetri GPS dari perangkat IoT ke IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.id.png)

### Tugas - Mengirim Data GPS ke IoT Hub

1. Buat IoT Hub baru menggunakan tier gratis.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat IoT Hub dari proyek 2, pelajaran 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) jika diperlukan.

    Ingatlah untuk membuat Resource Group baru. Beri nama Resource Group baru `gps-sensor`, dan IoT Hub baru dengan nama unik berdasarkan `gps-sensor`, seperti `gps-sensor-<nama Anda>`.

    > 💁 Jika Anda masih memiliki IoT Hub dari proyek sebelumnya, Anda dapat menggunakannya kembali. Ingatlah untuk menggunakan nama IoT Hub ini dan Resource Group tempat ia berada saat membuat layanan lain.

1. Tambahkan perangkat baru ke IoT Hub. Beri nama perangkat ini `gps-sensor`. Ambil string koneksi untuk perangkat tersebut.

1. Perbarui kode perangkat Anda untuk mengirim data GPS ke IoT Hub baru menggunakan string koneksi perangkat dari langkah sebelumnya.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk menghubungkan perangkat Anda ke IoT dari proyek 2, pelajaran 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) jika diperlukan.

1. Saat Anda mengirim data GPS, lakukan dalam format JSON berikut:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Kirim data GPS setiap menit agar tidak melebihi alokasi pesan harian Anda.

Jika Anda menggunakan Wio Terminal, ingatlah untuk menambahkan semua pustaka yang diperlukan, dan mengatur waktu menggunakan server NTP. Kode Anda juga perlu memastikan bahwa semua data telah dibaca dari port serial sebelum mengirim lokasi GPS, menggunakan kode yang ada dari pelajaran sebelumnya. Gunakan kode berikut untuk membuat dokumen JSON:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Jika Anda menggunakan perangkat IoT Virtual, ingatlah untuk menginstal semua pustaka yang diperlukan menggunakan lingkungan virtual.

Untuk Raspberry Pi dan perangkat IoT Virtual, gunakan kode yang ada dari pelajaran sebelumnya untuk mendapatkan nilai lintang dan bujur, lalu kirimkan dalam format JSON yang benar dengan kode berikut:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Anda dapat menemukan kode ini di folder [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi), atau [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Jalankan kode perangkat Anda dan pastikan pesan mengalir ke IoT Hub menggunakan perintah CLI `az iot hub monitor-events`.

## Jalur Panas, Hangat, dan Dingin

Data yang mengalir dari perangkat IoT ke cloud tidak selalu diproses secara real-time. Beberapa data perlu diproses secara real-time, data lainnya dapat diproses beberapa saat kemudian, dan data lainnya dapat diproses jauh lebih lama kemudian. Aliran data ke berbagai layanan yang memproses data pada waktu yang berbeda ini disebut jalur panas, hangat, dan dingin.

### Jalur Panas

Jalur panas mengacu pada data yang perlu diproses secara real-time atau hampir real-time. Anda akan menggunakan data jalur panas untuk peringatan, seperti mendapatkan peringatan bahwa kendaraan mendekati depot, atau bahwa suhu di truk berpendingin terlalu tinggi.

Untuk menggunakan data jalur panas, kode Anda akan merespons peristiwa segera setelah diterima oleh layanan cloud Anda.

### Jalur Hangat

Jalur hangat mengacu pada data yang dapat diproses beberapa saat setelah diterima, misalnya untuk pelaporan atau analitik jangka pendek. Anda akan menggunakan data jalur hangat untuk laporan harian tentang jarak tempuh kendaraan, menggunakan data yang dikumpulkan pada hari sebelumnya.

Data jalur hangat disimpan setelah diterima oleh layanan cloud di dalam beberapa jenis penyimpanan yang dapat diakses dengan cepat.

### Jalur Dingin

Jalur dingin mengacu pada data historis, menyimpan data untuk jangka panjang agar dapat diproses kapan pun diperlukan. Misalnya, Anda dapat menggunakan jalur dingin untuk mendapatkan laporan jarak tempuh tahunan kendaraan, atau menjalankan analitik pada rute untuk menemukan rute yang paling optimal untuk mengurangi biaya bahan bakar.

Data jalur dingin disimpan di gudang data - database yang dirancang untuk menyimpan sejumlah besar data yang tidak akan pernah berubah dan dapat dikueri dengan cepat dan mudah. Biasanya, Anda akan memiliki pekerjaan reguler dalam aplikasi cloud Anda yang akan berjalan pada waktu tertentu setiap hari, minggu, atau bulan untuk memindahkan data dari penyimpanan jalur hangat ke gudang data.

✅ Pikirkan tentang data yang telah Anda tangkap sejauh ini dalam pelajaran ini. Apakah itu data jalur panas, hangat, atau dingin?

## Menangani Peristiwa GPS Menggunakan Kode Tanpa Server

Setelah data mengalir ke IoT Hub Anda, Anda dapat menulis beberapa kode tanpa server untuk mendengarkan peristiwa yang diterbitkan ke endpoint yang kompatibel dengan Event Hub. Ini adalah jalur hangat - data ini akan disimpan dan digunakan dalam pelajaran berikutnya untuk pelaporan perjalanan.

![Mengirim telemetri GPS dari perangkat IoT ke IoT Hub, lalu ke Azure Functions melalui pemicu event hub](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.id.png)

### Tugas - Menangani Peristiwa GPS Menggunakan Kode Tanpa Server

1. Buat aplikasi Azure Functions menggunakan Azure Functions CLI. Gunakan runtime Python, dan buat di folder bernama `gps-trigger`, serta gunakan nama yang sama untuk nama proyek Functions App. Pastikan Anda membuat lingkungan virtual untuk ini.
> ⚠️ Anda dapat merujuk ke [instruksi untuk membuat Proyek Azure Functions dari proyek 2, pelajaran 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) jika diperlukan.
1. Tambahkan pemicu acara IoT Hub yang menggunakan endpoint kompatibel Event Hub dari IoT Hub.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat pemicu acara IoT Hub dari proyek 2, pelajaran 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) jika diperlukan.

1. Atur string koneksi endpoint kompatibel Event Hub di file `local.settings.json`, dan gunakan kunci untuk entri tersebut di file `function.json`.

1. Gunakan aplikasi Azurite sebagai emulator penyimpanan lokal.

1. Jalankan aplikasi fungsi Anda untuk memastikan bahwa aplikasi tersebut menerima acara dari perangkat GPS Anda. Pastikan perangkat IoT Anda juga berjalan dan mengirimkan data GPS.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Akun Penyimpanan Azure

![Logo Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.id.png)

Akun Penyimpanan Azure adalah layanan penyimpanan serbaguna yang dapat menyimpan data dalam berbagai cara. Anda dapat menyimpan data sebagai blob, dalam antrean, dalam tabel, atau sebagai file, dan semuanya dapat dilakukan secara bersamaan.

### Penyimpanan Blob

Kata *Blob* berarti objek biner besar, tetapi telah menjadi istilah untuk data tidak terstruktur. Anda dapat menyimpan data apa pun di penyimpanan blob, mulai dari dokumen JSON yang berisi data IoT, hingga file gambar dan film. Penyimpanan blob memiliki konsep *container*, yaitu wadah bernama tempat Anda dapat menyimpan data, mirip dengan tabel dalam basis data relasional. Container ini dapat memiliki satu atau lebih folder untuk menyimpan blob, dan setiap folder dapat berisi folder lain, mirip dengan cara file disimpan di hard disk komputer Anda.

Anda akan menggunakan penyimpanan blob dalam pelajaran ini untuk menyimpan data IoT.

✅ Lakukan penelitian: Baca tentang [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Penyimpanan Tabel

Penyimpanan tabel memungkinkan Anda menyimpan data semi-terstruktur. Penyimpanan tabel sebenarnya adalah basis data NoSQL, sehingga tidak memerlukan set tabel yang telah ditentukan sebelumnya, tetapi dirancang untuk menyimpan data dalam satu atau lebih tabel, dengan kunci unik untuk mendefinisikan setiap baris.

✅ Lakukan penelitian: Baca tentang [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Penyimpanan Antrean

Penyimpanan antrean memungkinkan Anda menyimpan pesan hingga ukuran 64KB dalam antrean. Anda dapat menambahkan pesan ke bagian belakang antrean, dan membacanya dari bagian depan. Antrean menyimpan pesan tanpa batas waktu selama masih ada ruang penyimpanan, sehingga memungkinkan pesan disimpan dalam jangka panjang, lalu dibaca saat diperlukan. Misalnya, jika Anda ingin menjalankan pekerjaan bulanan untuk memproses data GPS, Anda dapat menambahkannya ke antrean setiap hari selama sebulan, lalu di akhir bulan memproses semua pesan dari antrean.

✅ Lakukan penelitian: Baca tentang [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Penyimpanan File

Penyimpanan file adalah penyimpanan file di cloud, dan aplikasi atau perangkat apa pun dapat terhubung menggunakan protokol standar industri. Anda dapat menulis file ke penyimpanan file, lalu memasangnya sebagai drive di PC atau Mac Anda.

✅ Lakukan penelitian: Baca tentang [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Hubungkan kode serverless Anda ke penyimpanan

Aplikasi fungsi Anda sekarang perlu terhubung ke penyimpanan blob untuk menyimpan pesan dari IoT Hub. Ada 2 cara untuk melakukannya:

* Di dalam kode fungsi, terhubung ke penyimpanan blob menggunakan SDK Python penyimpanan blob dan tulis data sebagai blob.
* Gunakan pengikatan fungsi output untuk mengikat nilai pengembalian fungsi ke penyimpanan blob dan secara otomatis menyimpan blob.

Dalam pelajaran ini, Anda akan menggunakan SDK Python untuk melihat cara berinteraksi dengan penyimpanan blob.

![Mengirim telemetri GPS dari perangkat IoT ke IoT Hub, lalu ke Azure Functions melalui pemicu event hub, kemudian menyimpannya ke penyimpanan blob](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.id.png)

Data akan disimpan sebagai blob JSON dengan format berikut:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Tugas - hubungkan kode serverless Anda ke penyimpanan

1. Buat akun Penyimpanan Azure. Beri nama seperti `gps<nama Anda>`.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat akun penyimpanan dari proyek 2, pelajaran 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) jika diperlukan.

    Jika Anda masih memiliki akun penyimpanan dari proyek sebelumnya, Anda dapat menggunakan kembali akun tersebut.

    > 💁 Anda akan dapat menggunakan akun penyimpanan yang sama untuk menerapkan aplikasi Azure Functions Anda nanti dalam pelajaran ini.

1. Jalankan perintah berikut untuk mendapatkan string koneksi untuk akun penyimpanan:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Ganti `<storage_name>` dengan nama akun penyimpanan yang Anda buat pada langkah sebelumnya.

1. Tambahkan entri baru ke file `local.settings.json` untuk string koneksi akun penyimpanan Anda, menggunakan nilai dari langkah sebelumnya. Beri nama `STORAGE_CONNECTION_STRING`.

1. Tambahkan yang berikut ke file `requirements.txt` untuk menginstal paket Pip penyimpanan Azure:

    ```sh
    azure-storage-blob
    ```

    Instal paket dari file ini di lingkungan virtual Anda.

    > Jika Anda mendapatkan kesalahan, maka tingkatkan versi Pip Anda di lingkungan virtual ke versi terbaru dengan perintah berikut, lalu coba lagi:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Di file `__init__.py` untuk `iot-hub-trigger`, tambahkan pernyataan impor berikut:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Modul sistem `json` akan digunakan untuk membaca dan menulis JSON, modul sistem `os` akan digunakan untuk membaca string koneksi, modul sistem `uuid` akan digunakan untuk menghasilkan ID unik untuk pembacaan GPS.

    Paket `azure.storage.blob` berisi SDK Python untuk bekerja dengan penyimpanan blob.

1. Sebelum metode `main`, tambahkan fungsi pembantu berikut:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    SDK blob Python tidak memiliki metode pembantu untuk membuat container jika tidak ada. Kode ini akan memuat string koneksi dari file `local.settings.json` (atau Pengaturan Aplikasi setelah diterapkan ke cloud), lalu membuat kelas `BlobServiceClient` dari ini untuk berinteraksi dengan akun penyimpanan blob. Kemudian kode ini akan melakukan loop melalui semua container untuk akun penyimpanan blob, mencari satu dengan nama yang disediakan - jika ditemukan, kode akan mengembalikan kelas `ContainerClient` yang dapat berinteraksi dengan container untuk membuat blob. Jika tidak ditemukan, maka container akan dibuat dan klien untuk container baru akan dikembalikan.

    Saat container baru dibuat, akses publik diberikan untuk melakukan query terhadap blob di container. Ini akan digunakan dalam pelajaran berikutnya untuk memvisualisasikan data GPS di peta.

1. Tidak seperti kelembapan tanah, dengan kode ini kita ingin menyimpan setiap acara, jadi tambahkan kode berikut di dalam loop `for event in events:` di fungsi `main`, di bawah pernyataan `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Kode ini mendapatkan ID perangkat dari metadata acara, lalu menggunakannya untuk membuat nama blob. Blob dapat disimpan dalam folder, dan ID perangkat akan digunakan untuk nama folder, sehingga setiap perangkat akan memiliki semua acara GPS-nya dalam satu folder. Nama blob adalah folder ini, diikuti oleh nama dokumen, dipisahkan dengan garis miring, mirip dengan jalur Linux dan macOS (mirip dengan Windows juga, tetapi Windows menggunakan garis miring terbalik). Nama dokumen adalah ID unik yang dihasilkan menggunakan modul Python `uuid`, dengan tipe file `json`.

    Misalnya, untuk ID perangkat `gps-sensor`, nama blob mungkin `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Tambahkan kode berikut di bawah ini:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Kode ini mendapatkan klien container menggunakan kelas pembantu `get_or_create_container`, dan kemudian mendapatkan objek klien blob menggunakan nama blob. Klien blob ini dapat merujuk ke blob yang ada, atau seperti dalam kasus ini, ke blob baru.

1. Tambahkan kode berikut setelah ini:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Kode ini membangun isi blob yang akan ditulis ke penyimpanan blob. Ini adalah dokumen JSON yang berisi ID perangkat, waktu telemetri dikirim ke IoT Hub, dan koordinat GPS dari telemetri.

    > 💁 Penting untuk menggunakan waktu antrean pesan sebagai lawan dari waktu saat ini untuk mendapatkan waktu pesan dikirim. Pesan mungkin berada di hub untuk sementara waktu sebelum diambil jika Aplikasi Functions tidak berjalan.

1. Tambahkan yang berikut di bawah kode ini:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Kode ini mencatat bahwa sebuah blob akan ditulis dengan detailnya, lalu mengunggah isi blob sebagai konten blob baru.

1. Jalankan aplikasi Functions. Anda akan melihat blob ditulis untuk semua acara GPS di output:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Pastikan Anda tidak menjalankan pemantau acara IoT Hub pada saat yang sama.

> 💁 Anda dapat menemukan kode ini di folder [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Tugas - verifikasi blob yang diunggah

1. Untuk melihat blob yang dibuat, Anda dapat menggunakan [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), alat gratis yang memungkinkan Anda melihat dan mengelola akun penyimpanan Anda, atau dari CLI.

    1. Untuk menggunakan CLI, pertama-tama Anda memerlukan kunci akun. Jalankan perintah berikut untuk mendapatkan kunci ini:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Ganti `<storage_name>` dengan nama akun penyimpanan.

        Salin nilai `key1`.

    1. Jalankan perintah berikut untuk mencantumkan blob dalam container:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Ganti `<storage_name>` dengan nama akun penyimpanan, dan `<key1>` dengan nilai `key1` yang Anda salin pada langkah terakhir.

        Ini akan mencantumkan semua blob dalam container:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Unduh salah satu blob menggunakan perintah berikut:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Ganti `<storage_name>` dengan nama akun penyimpanan, dan `<key1>` dengan nilai `key1` yang Anda salin pada langkah sebelumnya.

        Ganti `<blob_name>` dengan nama lengkap dari kolom `Name` pada output langkah sebelumnya, termasuk nama folder. Ganti `<file_name>` dengan nama file lokal untuk menyimpan blob.

    Setelah diunduh, Anda dapat membuka file JSON di VS Code, dan Anda akan melihat blob berisi detail lokasi GPS:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Tugas - terapkan aplikasi Functions Anda ke cloud

Sekarang aplikasi Functions Anda berfungsi, Anda dapat menerapkannya ke cloud.

1. Buat aplikasi Azure Functions baru, menggunakan akun penyimpanan yang Anda buat sebelumnya. Beri nama seperti `gps-sensor-` dan tambahkan pengidentifikasi unik di akhir, seperti beberapa kata acak atau nama Anda.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat aplikasi Functions dari proyek 2, pelajaran 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) jika diperlukan.

1. Unggah nilai `IOT_HUB_CONNECTION_STRING` dan `STORAGE_CONNECTION_STRING` ke Pengaturan Aplikasi.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk mengunggah Pengaturan Aplikasi dari proyek 2, pelajaran 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) jika diperlukan.

1. Terapkan aplikasi Functions lokal Anda ke cloud.
> ⚠️ Anda dapat merujuk ke [instruksi untuk menerapkan aplikasi Functions Anda dari proyek 2, pelajaran 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) jika diperlukan.
---

## 🚀 Tantangan

Data GPS tidak sepenuhnya akurat, dan lokasi yang terdeteksi bisa meleset beberapa meter, bahkan lebih, terutama di terowongan dan area dengan gedung-gedung tinggi.

Pikirkan bagaimana navigasi satelit dapat mengatasi masalah ini? Data apa yang dimiliki sat-nav Anda yang memungkinkan untuk membuat prediksi lokasi yang lebih baik?

## Kuis Pasca-Kuliah

[Kuis Pasca-Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Tinjauan & Studi Mandiri

* Bacalah tentang data terstruktur di [halaman model data di Wikipedia](https://wikipedia.org/wiki/Data_model)
* Bacalah tentang data semi-terstruktur di [halaman data semi-terstruktur di Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Bacalah tentang data tidak terstruktur di [halaman data tidak terstruktur di Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Pelajari lebih lanjut tentang Azure Storage dan berbagai jenis penyimpanan di [dokumentasi Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Tugas

[Selidiki fungsi bindings](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.