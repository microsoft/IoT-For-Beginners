<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T21:46:37+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "id"
}
-->
# Tambahkan Kontrol Manual untuk Relay

## Instruksi

Kode serverless dapat dipicu oleh berbagai hal, termasuk permintaan HTTP. Anda dapat menggunakan pemicu HTTP untuk menambahkan pengendalian manual pada relay Anda, memungkinkan seseorang untuk menyalakan atau mematikan relay melalui permintaan web.

Untuk tugas ini, Anda perlu menambahkan dua pemicu HTTP ke Functions App Anda untuk menyalakan dan mematikan relay, dengan memanfaatkan apa yang telah Anda pelajari dari pelajaran ini untuk mengirim perintah ke perangkat.

Beberapa petunjuk:

* Anda dapat menambahkan pemicu HTTP ke Functions App yang sudah ada dengan perintah berikut:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Ganti `<trigger name>` dengan nama untuk pemicu HTTP Anda. Gunakan sesuatu seperti `relay_on` dan `relay_off`.

* Pemicu HTTP dapat memiliki kontrol akses. Secara default, mereka memerlukan kunci API khusus fungsi yang harus disertakan dengan URL untuk dijalankan. Untuk tugas ini, Anda dapat menghapus pembatasan ini sehingga siapa pun dapat menjalankan fungsi tersebut. Untuk melakukannya, perbarui pengaturan `authLevel` di file `function.json` untuk pemicu HTTP menjadi:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Anda dapat membaca lebih lanjut tentang kontrol akses ini di [dokumentasi kunci akses Function](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Pemicu HTTP secara default mendukung permintaan GET dan POST. Ini berarti Anda dapat memanggilnya menggunakan browser web - browser web membuat permintaan GET.

    Ketika Anda menjalankan Functions App secara lokal, Anda akan melihat URL dari pemicu:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Tempelkan URL tersebut ke browser Anda dan tekan `return`, atau `Ctrl+klik` (`Cmd+klik` pada macOS) tautan di jendela terminal di VS Code untuk membukanya di browser default Anda. Ini akan menjalankan pemicu tersebut.

    > 💁 Perhatikan bahwa URL memiliki `/api` di dalamnya - pemicu HTTP secara default berada di subdomain `api`.

* Ketika Anda menerapkan Functions App, URL pemicu HTTP akan menjadi:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Di mana `<functions app name>` adalah nama Functions App Anda, dan `<trigger name>` adalah nama pemicu Anda.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Membuat pemicu HTTP | Membuat 2 pemicu untuk menyalakan dan mematikan relay, dengan nama yang sesuai | Membuat satu pemicu dengan nama yang sesuai | Tidak dapat membuat pemicu apa pun |
| Mengontrol relay dari pemicu HTTP | Berhasil menghubungkan kedua pemicu ke IoT Hub dan mengontrol relay dengan benar | Berhasil menghubungkan satu pemicu ke IoT Hub dan mengontrol relay dengan benar | Tidak dapat menghubungkan pemicu ke IoT Hub |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.