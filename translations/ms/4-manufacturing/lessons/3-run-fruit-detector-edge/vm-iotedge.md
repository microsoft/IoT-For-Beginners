<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T22:54:54+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "ms"
}
-->
# Buat mesin maya yang menjalankan IoT Edge

Di Azure, anda boleh mencipta mesin maya - sebuah komputer di awan yang boleh anda konfigurasi mengikut kehendak anda dan menjalankan perisian anda sendiri di atasnya.

> 💁 Anda boleh membaca lebih lanjut tentang mesin maya di [halaman Mesin Maya di Wikipedia](https://wikipedia.org/wiki/Virtual_machine).

## Tugasan - Sediakan mesin maya IoT Edge

1. Jalankan arahan berikut untuk mencipta VM yang telah dipasang Azure IoT Edge:

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

    Gantikan `<vm_name>` dengan nama untuk mesin maya ini. Nama ini perlu unik secara global, jadi gunakan sesuatu seperti `fruit-quality-detector-vm-` dengan nama anda atau nilai lain di hujungnya.

    Gantikan `<username>` dan `<password>` dengan nama pengguna dan kata laluan untuk log masuk ke VM. Nama pengguna dan kata laluan ini perlu agak selamat, jadi anda tidak boleh menggunakan admin/password.

    Gantikan `<connection_string>` dengan string sambungan untuk peranti IoT Edge anda `fruit-quality-detector-edge`.

    Ini akan mencipta VM yang dikonfigurasi sebagai mesin maya `DS1 v2`. Kategori ini menunjukkan betapa kuatnya mesin tersebut, dan oleh itu berapa kosnya. VM ini mempunyai 1 CPU dan 3.5GB RAM.

    > 💰 Anda boleh melihat harga semasa untuk VM ini di [panduan harga Mesin Maya Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Setelah VM dicipta, runtime IoT Edge akan dipasang secara automatik, dan dikonfigurasi untuk menyambung ke IoT Hub anda sebagai peranti `fruit-quality-detector-edge`.

1. Anda memerlukan sama ada alamat IP atau nama DNS VM untuk memanggil pengklasifikasi imej daripadanya. Jalankan arahan berikut untuk mendapatkannya:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Salin sama ada medan `PublicIps` atau medan `Fqdns`.

1. VM memerlukan kos. Pada masa penulisan, VM DS1 berharga kira-kira $0.06 sejam. Untuk mengurangkan kos, anda harus mematikan VM apabila anda tidak menggunakannya, dan memadamkannya apabila anda selesai dengan projek ini.

    Anda boleh mengkonfigurasi VM anda untuk dimatikan secara automatik pada waktu tertentu setiap hari. Ini bermakna jika anda terlupa untuk mematikannya, anda tidak akan dikenakan bil lebih daripada masa sehingga penutupan automatik. Gunakan arahan berikut untuk menetapkan ini:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Gantikan `<vm_name>` dengan nama mesin maya anda.

    Gantikan `<shutdown_time_utc>` dengan waktu UTC yang anda mahu VM dimatikan menggunakan 4 digit sebagai HHMM. Sebagai contoh, jika anda mahu dimatikan pada tengah malam UTC, anda akan menetapkannya kepada `0000`. Untuk 7:30PM di pantai barat Amerika Syarikat, anda akan menggunakan 0230 (7:30PM di pantai barat AS adalah 2:30AM UTC).

1. Pengklasifikasi imej anda akan berjalan pada peranti edge ini, mendengar pada port 80 (port HTTP standard). Secara lalai, mesin maya mempunyai port masuk yang disekat, jadi anda perlu mengaktifkan port 80. Port diaktifkan pada kumpulan keselamatan rangkaian, jadi pertama-tama anda perlu mengetahui nama kumpulan keselamatan rangkaian untuk VM anda, yang boleh anda dapati dengan arahan berikut:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Salin nilai medan `Name`.

1. Jalankan arahan berikut untuk menambah peraturan bagi membuka port 80 pada kumpulan keselamatan rangkaian:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Gantikan `<nsg name>` dengan nama kumpulan keselamatan rangkaian daripada langkah sebelumnya.

### Tugasan - uruskan VM anda untuk mengurangkan kos

1. Apabila anda tidak menggunakan VM anda, anda harus mematikannya. Untuk mematikan VM, gunakan arahan berikut:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Gantikan `<vm_name>` dengan nama mesin maya anda.

    > 💁 Terdapat arahan `az vm stop` yang akan menghentikan VM, tetapi ia mengekalkan komputer diperuntukkan kepada anda, jadi anda masih membayar seolah-olah ia masih berjalan.

1. Untuk memulakan semula VM, gunakan arahan berikut:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Gantikan `<vm_name>` dengan nama mesin maya anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.