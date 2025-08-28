<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T01:24:25+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "ms"
}
-->
# Tambah Kawalan Relay Manual

## Arahan

Kod tanpa pelayan boleh dicetuskan oleh pelbagai perkara, termasuk permintaan HTTP. Anda boleh menggunakan pencetus HTTP untuk menambah kawalan manual pada relay anda, membolehkan seseorang menghidupkan atau mematikan relay melalui permintaan web.

Untuk tugasan ini, anda perlu menambah dua pencetus HTTP pada Aplikasi Fungsi anda untuk menghidupkan dan mematikan relay, menggunakan semula apa yang telah anda pelajari daripada pelajaran ini untuk menghantar arahan kepada peranti.

Beberapa petunjuk:

* Anda boleh menambah pencetus HTTP pada Aplikasi Fungsi sedia ada anda dengan arahan berikut:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Gantikan `<trigger name>` dengan nama untuk pencetus HTTP anda. Gunakan sesuatu seperti `relay_on` dan `relay_off`.

* Pencetus HTTP boleh mempunyai kawalan akses. Secara lalai, ia memerlukan kunci API khusus fungsi untuk dihantar bersama URL untuk dijalankan. Untuk tugasan ini, anda boleh menghapuskan sekatan ini supaya sesiapa sahaja boleh menjalankan fungsi tersebut. Untuk melakukannya, kemas kini tetapan `authLevel` dalam fail `function.json` untuk pencetus HTTP kepada yang berikut:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Anda boleh membaca lebih lanjut tentang kawalan akses ini dalam [dokumentasi kunci akses Fungsi](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Pencetus HTTP secara lalai menyokong permintaan GET dan POST. Ini bermakna anda boleh memanggilnya menggunakan pelayar web anda - pelayar web membuat permintaan GET.

    Apabila anda menjalankan Aplikasi Fungsi anda secara tempatan, anda akan melihat URL pencetus:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Tampal URL tersebut ke dalam pelayar anda dan tekan `return`, atau `Ctrl+klik` (`Cmd+klik` pada macOS) pautan dalam tetingkap terminal di VS Code untuk membukanya dalam pelayar lalai anda. Ini akan menjalankan pencetus tersebut.

    > 💁 Perhatikan bahawa URL mempunyai `/api` di dalamnya - pencetus HTTP secara lalai berada dalam subdomain `api`.

* Apabila anda menggunakan Aplikasi Fungsi, URL pencetus HTTP akan menjadi:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Di mana `<functions app name>` adalah nama Aplikasi Fungsi anda, dan `<trigger name>` adalah nama pencetus anda.

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Cipta pencetus HTTP | Mencipta 2 pencetus untuk menghidupkan dan mematikan relay, dengan nama yang sesuai | Mencipta satu pencetus dengan nama yang sesuai | Tidak dapat mencipta sebarang pencetus |
| Kawal relay daripada pencetus HTTP | Berjaya menyambungkan kedua-dua pencetus ke IoT Hub dan mengawal relay dengan betul | Berjaya menyambungkan satu pencetus ke IoT Hub dan mengawal relay dengan betul | Tidak dapat menyambungkan pencetus ke IoT Hub |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.