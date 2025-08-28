<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T21:12:57+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "id"
}
-->
# Membuat Mesin Virtual yang Menjalankan IoT Edge

Di Azure, Anda dapat membuat mesin virtual - sebuah komputer di cloud yang dapat Anda konfigurasi sesuai keinginan dan menjalankan perangkat lunak Anda sendiri di dalamnya.

> 💁 Anda dapat membaca lebih lanjut tentang mesin virtual di [halaman Mesin Virtual di Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Tugas - Menyiapkan mesin virtual IoT Edge

1. Jalankan perintah berikut untuk membuat VM yang sudah memiliki Azure IoT Edge terinstal sebelumnya:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Ganti `<vm_name>` dengan nama untuk mesin virtual ini. Nama ini harus unik secara global, jadi gunakan sesuatu seperti `fruit-quality-detector-vm-` dengan nama Anda atau nilai lain di akhir.

    Ganti `<username>` dan `<password>` dengan nama pengguna dan kata sandi untuk masuk ke VM. Nama pengguna dan kata sandi ini harus cukup aman, jadi Anda tidak bisa menggunakan admin/password.

    Ganti `<connection_string>` dengan string koneksi dari perangkat IoT Edge Anda `fruit-quality-detector-edge`.

    Ini akan membuat VM yang dikonfigurasi sebagai mesin virtual `DS1 v2`. Kategori ini menunjukkan seberapa kuat mesin tersebut, dan oleh karena itu berapa biayanya. VM ini memiliki 1 CPU dan RAM sebesar 3.5GB.

    > 💰 Anda dapat melihat harga terkini untuk VM ini di [panduan harga Mesin Virtual Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Setelah VM dibuat, runtime IoT Edge akan secara otomatis diinstal dan dikonfigurasi untuk terhubung ke IoT Hub Anda sebagai perangkat `fruit-quality-detector-edge`.

1. Anda akan membutuhkan alamat IP atau nama DNS dari VM untuk memanggil pengklasifikasi gambar dari sana. Jalankan perintah berikut untuk mendapatkannya:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Salin salah satu nilai dari bidang `PublicIps` atau bidang `Fqdns`.

1. VM memerlukan biaya. Pada saat penulisan, VM DS1 berharga sekitar $0.06 per jam. Untuk mengurangi biaya, Anda sebaiknya mematikan VM saat tidak digunakan, dan menghapusnya setelah selesai dengan proyek ini.

    Anda dapat mengonfigurasi VM Anda untuk secara otomatis mati pada waktu tertentu setiap hari. Ini berarti jika Anda lupa mematikannya, Anda tidak akan dikenakan biaya lebih dari waktu hingga pemadaman otomatis. Gunakan perintah berikut untuk mengaturnya:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Ganti `<vm_name>` dengan nama mesin virtual Anda.

    Ganti `<shutdown_time_utc>` dengan waktu UTC yang Anda inginkan untuk mematikan VM menggunakan 4 digit sebagai HHMM. Misalnya, jika Anda ingin mematikan pada tengah malam UTC, Anda akan mengatur ini ke `0000`. Untuk pukul 7:30 malam di pantai barat AS, Anda akan menggunakan 0230 (7:30 malam di pantai barat AS adalah 2:30 pagi UTC).

1. Pengklasifikasi gambar Anda akan berjalan di perangkat edge ini, mendengarkan di port 80 (port HTTP standar). Secara default, mesin virtual memiliki port masuk yang diblokir, jadi Anda perlu mengaktifkan port 80. Port diaktifkan pada grup keamanan jaringan, jadi pertama-tama Anda perlu mengetahui nama grup keamanan jaringan untuk VM Anda, yang dapat Anda temukan dengan perintah berikut:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Salin nilai dari bidang `Name`.

1. Jalankan perintah berikut untuk menambahkan aturan untuk membuka port 80 ke grup keamanan jaringan:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Ganti `<nsg name>` dengan nama grup keamanan jaringan dari langkah sebelumnya.

### Tugas - mengelola VM Anda untuk mengurangi biaya

1. Saat Anda tidak menggunakan VM Anda, Anda sebaiknya mematikannya. Untuk mematikan VM, gunakan perintah berikut:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Ganti `<vm_name>` dengan nama mesin virtual Anda.

    > 💁 Ada perintah `az vm stop` yang akan menghentikan VM, tetapi ini tetap menjaga komputer dialokasikan untuk Anda, sehingga Anda tetap membayar seolah-olah masih berjalan.

1. Untuk memulai ulang VM, gunakan perintah berikut:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Ganti `<vm_name>` dengan nama mesin virtual Anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.