<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T21:09:34+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "ms"
}
-->
# Jalankan pengesan buah anda di tepi

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

Video ini memberikan gambaran tentang menjalankan pengklasifikasi imej pada peranti IoT, topik yang dibincangkan dalam pelajaran ini.

[![Custom Vision AI di Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Kuiz sebelum kuliah

[Kuiz sebelum kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Pengenalan

Dalam pelajaran sebelumnya, anda menggunakan pengklasifikasi imej anda untuk mengklasifikasikan buah yang masak dan tidak masak, dengan menghantar imej yang ditangkap oleh kamera pada peranti IoT anda melalui internet ke perkhidmatan awan. Panggilan ini mengambil masa, memerlukan kos, dan bergantung pada jenis data imej yang anda gunakan, mungkin mempunyai implikasi privasi.

Dalam pelajaran ini, anda akan belajar bagaimana menjalankan model pembelajaran mesin (ML) di tepi - pada peranti IoT yang berjalan di rangkaian anda sendiri dan bukannya di awan. Anda akan mempelajari manfaat dan kelemahan pengkomputeran tepi berbanding pengkomputeran awan, cara untuk menyebarkan model AI anda ke tepi, dan cara mengaksesnya dari peranti IoT anda.

Dalam pelajaran ini, kita akan membincangkan:

* [Pengkomputeran tepi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Daftar peranti IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Sediakan peranti IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Eksport model anda](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Sediakan kontena anda untuk penyebaran](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Sebarkan kontena anda](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Gunakan peranti IoT Edge anda](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Pengkomputeran tepi

Pengkomputeran tepi melibatkan penggunaan komputer yang memproses data IoT sedekat mungkin dengan tempat data itu dihasilkan. Daripada memproses data di awan, ia dipindahkan ke tepi awan - rangkaian dalaman anda.

![Rajah seni bina menunjukkan perkhidmatan internet di awan dan peranti IoT di rangkaian tempatan](../../../../../translated_images/ms/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

Dalam pelajaran sebelum ini, anda mempunyai peranti yang mengumpul data dan menghantar data ke awan untuk dianalisis, menjalankan fungsi tanpa pelayan atau model AI di awan.

![Rajah seni bina menunjukkan peranti IoT di rangkaian tempatan yang berhubung dengan peranti tepi, dan peranti tepi tersebut berhubung dengan awan](../../../../../translated_images/ms/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Pengkomputeran tepi melibatkan pemindahan beberapa perkhidmatan awan keluar dari awan dan ke komputer yang berjalan di rangkaian yang sama dengan peranti IoT, hanya berkomunikasi dengan awan jika diperlukan. Sebagai contoh, anda boleh menjalankan model AI pada peranti tepi untuk menganalisis kematangan buah, dan hanya menghantar analitik kembali ke awan, seperti jumlah buah yang masak berbanding yang tidak masak.

✅ Fikirkan tentang aplikasi IoT yang telah anda bina setakat ini. Bahagian mana yang boleh dipindahkan ke tepi.

### Kelebihan

Kelebihan pengkomputeran tepi adalah:

1. **Kelajuan** - pengkomputeran tepi sesuai untuk data yang sensitif masa kerana tindakan dilakukan pada rangkaian yang sama dengan peranti, bukannya membuat panggilan melalui internet. Ini membolehkan kelajuan yang lebih tinggi kerana rangkaian dalaman boleh berjalan pada kelajuan yang jauh lebih tinggi daripada sambungan internet, dengan data bergerak pada jarak yang lebih pendek.

    > 💁 Walaupun kabel optik digunakan untuk sambungan internet yang membolehkan data bergerak pada kelajuan cahaya, data boleh mengambil masa untuk bergerak di seluruh dunia ke penyedia awan. Sebagai contoh, jika anda menghantar data dari Eropah ke perkhidmatan awan di AS, ia mengambil sekurang-kurangnya 28ms untuk data melintasi Atlantik dalam kabel optik, dan itu tidak termasuk masa yang diambil untuk mendapatkan data ke kabel transatlantik, menukar dari isyarat elektrik ke cahaya dan kembali lagi di sisi lain, kemudian dari kabel optik ke penyedia awan.

    Pengkomputeran tepi juga memerlukan trafik rangkaian yang lebih sedikit, mengurangkan risiko data anda menjadi perlahan akibat kesesakan pada jalur lebar yang terhad untuk sambungan internet.

1. **Akses jauh** - pengkomputeran tepi berfungsi apabila anda mempunyai sambungan yang terhad atau tiada sambungan, atau sambungan terlalu mahal untuk digunakan secara berterusan. Sebagai contoh, apabila bekerja di kawasan bencana kemanusiaan di mana infrastruktur adalah terhad, atau di negara membangun.

1. **Kos lebih rendah** - pengumpulan data, penyimpanan, analisis, dan pencetus tindakan pada peranti tepi mengurangkan penggunaan perkhidmatan awan yang boleh mengurangkan kos keseluruhan aplikasi IoT anda. Terdapat peningkatan baru-baru ini dalam peranti yang direka untuk pengkomputeran tepi, seperti papan pemecut AI seperti [Jetson Nano dari NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), yang boleh menjalankan beban kerja AI menggunakan perkakasan berasaskan GPU pada peranti yang berharga kurang daripada US$100.

1. **Privasi dan keselamatan** - dengan pengkomputeran tepi, data kekal di rangkaian anda dan tidak dimuat naik ke awan. Ini sering menjadi pilihan untuk maklumat sensitif dan yang boleh dikenal pasti secara peribadi, terutamanya kerana data tidak perlu disimpan selepas ia dianalisis, yang sangat mengurangkan risiko kebocoran data. Contohnya termasuk data perubatan dan rakaman kamera keselamatan.

1. **Pengendalian peranti yang tidak selamat** - jika anda mempunyai peranti dengan kelemahan keselamatan yang diketahui yang anda tidak mahu sambungkan secara langsung ke rangkaian anda atau internet, maka anda boleh menyambungkannya ke rangkaian berasingan ke peranti gerbang IoT Edge. Peranti tepi ini kemudian juga boleh mempunyai sambungan ke rangkaian yang lebih luas atau internet, dan menguruskan aliran data ke depan dan ke belakang.

1. **Sokongan untuk peranti yang tidak serasi** - jika anda mempunyai peranti yang tidak boleh disambungkan ke IoT Hub, contohnya peranti yang hanya boleh disambungkan menggunakan sambungan HTTP atau peranti yang hanya mempunyai Bluetooth untuk disambungkan, anda boleh menggunakan peranti tepi IoT sebagai peranti gerbang, meneruskan mesej ke IoT Hub.

✅ Lakukan penyelidikan: Apakah kelebihan lain yang mungkin ada untuk pengkomputeran tepi?

### Kelemahan

Terdapat kelemahan pengkomputeran tepi, di mana awan mungkin menjadi pilihan yang lebih baik:

1. **Skala dan fleksibiliti** - pengkomputeran awan boleh menyesuaikan keperluan rangkaian dan data secara masa nyata dengan menambah atau mengurangkan pelayan dan sumber lain. Untuk menambah lebih banyak komputer tepi memerlukan penambahan peranti secara manual.

1. **Kebolehpercayaan dan ketahanan** - pengkomputeran awan menyediakan pelbagai pelayan yang sering berada di pelbagai lokasi untuk redundansi dan pemulihan bencana. Untuk mempunyai tahap redundansi yang sama di tepi memerlukan pelaburan besar dan banyak kerja konfigurasi.

1. **Penyelenggaraan** - penyedia perkhidmatan awan menyediakan penyelenggaraan sistem dan kemas kini.

✅ Lakukan penyelidikan: Apakah kelemahan lain yang mungkin ada untuk pengkomputeran tepi?

Kelemahan ini sebenarnya adalah kebalikan daripada kelebihan menggunakan awan - anda perlu membina dan menguruskan peranti ini sendiri, bukannya bergantung pada kepakaran dan skala penyedia awan.

Beberapa risiko dapat dikurangkan oleh sifat pengkomputeran tepi itu sendiri. Sebagai contoh, jika anda mempunyai peranti tepi yang berjalan di kilang yang mengumpul data dari mesin, anda tidak perlu memikirkan beberapa senario pemulihan bencana. Jika bekalan kuasa ke kilang terputus, maka anda tidak memerlukan peranti tepi sandaran kerana mesin yang menghasilkan data yang diproses oleh peranti tepi juga akan kehilangan kuasa.

Untuk sistem IoT, anda sering memerlukan gabungan pengkomputeran awan dan tepi, memanfaatkan setiap perkhidmatan berdasarkan keperluan sistem, pelanggannya, dan penyelenggaranya.

## Azure IoT Edge

![Logo Azure IoT Edge](../../../../../translated_images/ms/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge adalah perkhidmatan yang dapat membantu anda memindahkan beban kerja keluar dari awan ke tepi. Anda menyediakan peranti sebagai peranti tepi, dan dari awan anda boleh menyebarkan kod ke peranti tepi tersebut. Ini membolehkan anda menggabungkan keupayaan awan dan tepi.

> 🎓 *Beban kerja* adalah istilah untuk sebarang perkhidmatan yang melakukan kerja tertentu, seperti model AI, aplikasi, atau fungsi tanpa pelayan.

Sebagai contoh, anda boleh melatih pengklasifikasi imej di awan, kemudian dari awan menyebarkannya ke peranti tepi. Peranti IoT anda kemudian menghantar imej ke peranti tepi untuk pengklasifikasian, bukannya menghantar imej melalui internet. Jika anda perlu menyebarkan iterasi baru model, anda boleh melatihnya di awan dan menggunakan IoT Edge untuk mengemas kini model pada peranti tepi kepada iterasi baru anda.

> 🎓 Perisian yang disebarkan ke IoT Edge dikenali sebagai *modul*. Secara lalai IoT Edge menjalankan modul yang berkomunikasi dengan IoT Hub, seperti modul `edgeAgent` dan `edgeHub`. Apabila anda menyebarkan pengklasifikasi imej, ini disebarkan sebagai modul tambahan.

IoT Edge dibina ke dalam IoT Hub, jadi anda boleh menguruskan peranti tepi menggunakan perkhidmatan yang sama yang anda gunakan untuk menguruskan peranti IoT, dengan tahap keselamatan yang sama.

IoT Edge menjalankan kod dari *kontena* - aplikasi yang berdiri sendiri yang dijalankan secara terasing daripada aplikasi lain pada komputer anda. Apabila anda menjalankan kontena, ia bertindak seperti komputer berasingan yang berjalan di dalam komputer anda, dengan perisian, perkhidmatan, dan aplikasi sendiri. Kebanyakan masa kontena tidak dapat mengakses apa-apa pada komputer anda kecuali anda memilih untuk berkongsi perkara seperti folder dengan kontena. Kontena kemudian mendedahkan perkhidmatan melalui port terbuka yang boleh anda sambungkan atau dedahkan kepada rangkaian anda.

![Permintaan web dialihkan ke kontena](../../../../../translated_images/ms/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Sebagai contoh, anda boleh mempunyai kontena dengan laman web yang berjalan pada port 80, port HTTP lalai, dan anda kemudian boleh mendedahkannya dari komputer anda juga pada port 80.

✅ Lakukan penyelidikan: Baca tentang kontena dan perkhidmatan seperti Docker atau Moby.

Anda boleh menggunakan Custom Vision untuk memuat turun pengklasifikasi imej dan menyebarkannya sebagai kontena, sama ada berjalan terus ke peranti atau disebarkan melalui IoT Edge. Setelah ia berjalan dalam kontena, ia boleh diakses menggunakan API REST yang sama seperti versi awan, tetapi dengan titik akhir yang menunjuk ke peranti tepi yang menjalankan kontena.

## Daftar peranti IoT Edge

Untuk menggunakan peranti IoT Edge, ia perlu didaftarkan dalam IoT Hub.

### Tugas - daftar peranti IoT Edge

1. Buat IoT Hub dalam kumpulan sumber `fruit-quality-detector`. Berikan nama unik berdasarkan `fruit-quality-detector`.

1. Daftar peranti IoT Edge yang dipanggil `fruit-quality-detector-edge` dalam IoT Hub anda. Perintah untuk melakukan ini adalah serupa dengan yang digunakan untuk mendaftarkan peranti bukan tepi, kecuali anda menambahkan bendera `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Gantikan `<hub_name>` dengan nama IoT Hub anda.

1. Dapatkan string sambungan untuk peranti anda menggunakan perintah berikut:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Gantikan `<hub_name>` dengan nama IoT Hub anda.

    Ambil salinan string sambungan yang ditunjukkan dalam output.

## Sediakan peranti IoT Edge

Setelah anda membuat pendaftaran peranti tepi dalam IoT Hub anda, anda boleh menyediakan peranti tepi.

### Tugas - Pasang dan mulakan IoT Edge Runtime

**IoT Edge runtime hanya menjalankan kontena Linux.** Ia boleh dijalankan pada Linux, atau pada Windows menggunakan Mesin Maya Linux.

* Jika anda menggunakan Raspberry Pi sebagai peranti IoT anda, maka ini menjalankan versi Linux yang disokong dan boleh menjadi hos IoT Edge runtime. Ikuti [panduan memasang Azure IoT Edge untuk Linux di Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) untuk memasang IoT Edge dan menetapkan string sambungan.

    > 💁 Ingat, Raspberry Pi OS adalah varian Debian Linux.

* Jika anda tidak menggunakan Raspberry Pi, tetapi mempunyai komputer Linux, anda boleh menjalankan IoT Edge runtime. Ikuti [panduan memasang Azure IoT Edge untuk Linux di Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) untuk memasang IoT Edge dan menetapkan string sambungan.

* Jika anda menggunakan Windows, anda boleh memasang IoT Edge runtime dalam Mesin Maya Linux dengan mengikuti [bahagian memasang dan memulakan IoT Edge runtime dari panduan cepat menyebarkan modul IoT Edge pertama anda ke peranti Windows di Microsoft docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Anda boleh berhenti apabila mencapai bahagian *Sebarkan modul*.

* Jika anda menggunakan macOS, anda boleh membuat mesin maya (VM) di awan untuk digunakan sebagai peranti IoT Edge anda. Ini adalah komputer yang boleh anda buat di awan dan akses melalui internet. Anda boleh membuat VM Linux yang mempunyai IoT Edge dipasang. Ikuti [panduan membuat mesin maya yang menjalankan IoT Edge](vm-iotedge.md) untuk arahan tentang cara melakukannya.

## Eksport model anda

Untuk menjalankan pengklasifikasi di tepi, ia perlu dieksport dari Custom Vision. Custom Vision boleh menghasilkan dua jenis model - model standard dan model kompak. Model kompak menggunakan pelbagai teknik untuk mengurangkan saiz model, menjadikannya cukup kecil untuk dimuat turun dan disebarkan pada peranti IoT.

Apabila anda membuat pengklasifikasi imej, anda menggunakan domain *Food*, versi model yang dioptimumkan untuk latihan pada imej makanan. Dalam Custom Vision, anda menukar domain projek anda, menggunakan data latihan anda untuk melatih model baru dengan domain baru. Semua domain yang disokong oleh Custom Vision tersedia sebagai standard dan kompak.

### Tugas - latih model anda menggunakan domain Food (kompak)
1. Lancarkan portal Custom Vision di [CustomVision.ai](https://customvision.ai) dan log masuk jika anda belum membukanya. Kemudian buka projek `fruit-quality-detector` anda.

1. Pilih butang **Settings** (ikon ⚙).

1. Dalam senarai *Domains*, pilih *Food (compact)*.

1. Di bawah *Export Capabilities*, pastikan *Basic platforms (Tensorflow, CoreML, ONNX, ...)* dipilih.

1. Di bahagian bawah halaman Settings, pilih **Save Changes**.

1. Latih semula model dengan butang **Train**, pilih *Quick training*.

### Tugasan - eksport model anda

Setelah model dilatih, ia perlu dieksport sebagai kontena.

1. Pilih tab **Performance**, dan cari iterasi terbaru anda yang dilatih menggunakan domain compact.

1. Pilih butang **Export** di bahagian atas.

1. Pilih **DockerFile**, kemudian pilih versi yang sesuai dengan peranti edge anda:

    * Jika anda menjalankan IoT Edge pada komputer Linux, komputer Windows atau Mesin Maya, pilih versi *Linux*.
    * Jika anda menjalankan IoT Edge pada Raspberry Pi, pilih versi *ARM (Raspberry Pi 3)*.

    
> 🎓 Docker adalah salah satu alat paling popular untuk menguruskan kontena, dan DockerFile adalah set arahan tentang cara menyediakan kontena.

1. Pilih **Export** untuk membolehkan Custom Vision mencipta fail yang relevan, kemudian **Download** untuk memuat turun fail tersebut dalam bentuk zip.

1. Simpan fail ke komputer anda, kemudian unzip folder tersebut.

## Sediakan kontena anda untuk deployment

![Kontena dibina kemudian ditolak ke container registry, kemudian dideploy dari container registry ke peranti edge menggunakan IoT Edge](../../../../../translated_images/ms/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Setelah anda memuat turun model anda, ia perlu dibina menjadi kontena, kemudian ditolak ke container registry - lokasi dalam talian di mana anda boleh menyimpan kontena. IoT Edge kemudian boleh memuat turun kontena dari registry dan menolaknya ke peranti anda.

![Logo Azure Container Registry](../../../../../translated_images/ms/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Container registry yang akan anda gunakan untuk pelajaran ini adalah Azure Container Registry. Ini bukan perkhidmatan percuma, jadi untuk menjimatkan wang pastikan anda [membersihkan projek anda](../../../clean-up.md) setelah selesai.

> 💁 Anda boleh melihat kos menggunakan Azure Container Registry di [halaman harga Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Tugasan - pasang Docker

Untuk membina dan deploy classifier, anda mungkin perlu memasang [Docker](https://www.docker.com/).

Anda hanya perlu melakukan ini jika anda merancang untuk membina kontena dari peranti yang berbeza daripada yang anda pasang IoT Edge - sebagai sebahagian daripada pemasangan IoT Edge, Docker dipasang untuk anda.

1. Jika anda membina kontena docker pada peranti yang berbeza daripada peranti IoT Edge anda, ikuti arahan pemasangan Docker di [halaman pemasangan Docker](https://www.docker.com/products/docker-desktop) untuk memasang Docker Desktop atau enjin Docker. Pastikan ia berjalan selepas pemasangan.

### Tugasan - buat sumber container registry

1. Jalankan arahan berikut dari Terminal atau command prompt anda untuk membuat sumber Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Gantikan `<Container registry name>` dengan nama unik untuk container registry anda, menggunakan huruf dan nombor sahaja. Asaskan nama ini kepada `fruitqualitydetector`. Nama ini menjadi sebahagian daripada URL untuk mengakses container registry, jadi ia perlu unik secara global.

1. Log masuk ke Azure Container Registry dengan arahan berikut:

    ```sh
    az acr login --name <Container registry name>
    ```

    Gantikan `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda.

1. Tetapkan container registry ke mod admin supaya anda boleh menjana kata laluan dengan arahan berikut:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Gantikan `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda.

1. Jana kata laluan untuk container registry anda dengan arahan berikut:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Gantikan `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda.

    Ambil salinan nilai `PASSWORD`, kerana anda akan memerlukannya kemudian.

### Tugasan - bina kontena anda

Apa yang anda muat turun dari Custom Vision adalah DockerFile yang mengandungi arahan tentang cara kontena harus dibina, bersama dengan kod aplikasi yang akan dijalankan di dalam kontena untuk menghoskan model Custom Vision anda, bersama dengan REST API untuk memanggilnya. Anda boleh menggunakan Docker untuk membina kontena yang ditag dari DockerFile, kemudian menolaknya ke container registry anda.

> 🎓 Kontena diberikan tag yang menentukan nama dan versi untuknya. Apabila anda perlu mengemas kini kontena, anda boleh membinanya dengan tag yang sama tetapi versi yang lebih baru.

1. Buka terminal atau command prompt anda dan navigasi ke model yang telah di-unzip yang anda muat turun dari Custom Vision.

1. Jalankan arahan berikut untuk membina dan menandai imej:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Gantikan `<platform>` dengan platform yang akan menjalankan kontena ini. Jika anda menjalankan IoT Edge pada Raspberry Pi, tetapkan ini kepada `linux/armhf`, jika tidak tetapkan ini kepada `linux/amd64`.

    > 💁 Jika anda menjalankan arahan ini dari peranti yang anda jalankan IoT Edge, seperti menjalankan ini dari Raspberry Pi anda, anda boleh mengabaikan bahagian `--platform <platform>` kerana ia secara automatik menggunakan platform semasa.

    Gantikan `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda.

    > 💁 Jika anda menjalankan Linux atau Raspberry Pi OS, anda mungkin perlu menggunakan `sudo` untuk menjalankan arahan ini.

    Docker akan membina imej, mengkonfigurasi semua perisian yang diperlukan. Imej kemudian akan ditag sebagai `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Tugasan - tolak kontena anda ke container registry anda

1. Gunakan arahan berikut untuk menolak kontena anda ke container registry anda:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Gantikan `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda.

    > 💁 Jika anda menjalankan Linux, anda mungkin perlu menggunakan `sudo` untuk menjalankan arahan ini.

    Kontena akan ditolak ke container registry.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Untuk mengesahkan penolakan, anda boleh menyenaraikan kontena dalam registry anda dengan arahan berikut:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Gantikan `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Anda akan melihat classifier anda disenaraikan dalam output.

## Deploy kontena anda

Kontena anda kini boleh dideploy ke peranti IoT Edge anda. Untuk deploy, anda perlu menentukan deployment manifest - dokumen JSON yang menyenaraikan modul yang akan dideploy ke peranti edge.

### Tugasan - buat deployment manifest

1. Buat fail baru bernama `deployment.json` di mana-mana lokasi di komputer anda.

1. Tambahkan perkara berikut ke fail ini:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Anda boleh mencari fail ini dalam folder [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Gantikan tiga instance `<Container registry name>` dengan nama yang anda gunakan untuk container registry anda. Satu berada di bahagian modul `ImageClassifier`, dua lagi berada di bahagian `registryCredentials`.

    Gantikan `<Container registry password>` dalam bahagian `registryCredentials` dengan kata laluan container registry anda.

1. Dari folder yang mengandungi deployment manifest anda, jalankan arahan berikut:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Gantikan `<hub_name>` dengan nama IoT Hub anda.

    Modul image classifier akan dideploy ke peranti edge anda.

### Tugasan - sahkan classifier sedang berjalan

1. Sambungkan ke peranti IoT edge:

    * Jika anda menggunakan Raspberry Pi untuk menjalankan IoT Edge, sambungkan menggunakan ssh sama ada dari terminal anda, atau melalui sesi SSH jauh di VS Code.
    * Jika anda menjalankan IoT Edge dalam kontena Linux di Windows, ikuti langkah-langkah dalam [panduan pengesahan konfigurasi berjaya](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) untuk menyambung ke peranti IoT Edge.
    * Jika anda menjalankan IoT Edge pada mesin maya, anda boleh SSH ke mesin menggunakan `adminUsername` dan `password` yang anda tetapkan semasa membuat VM, dan menggunakan sama ada alamat IP atau nama DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Atau:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Masukkan kata laluan anda apabila diminta.

1. Setelah anda disambungkan, jalankan arahan berikut untuk mendapatkan senarai modul IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Anda mungkin perlu menjalankan arahan ini dengan `sudo`.

    Anda akan melihat modul yang sedang berjalan:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Periksa log untuk modul Image classifier dengan arahan berikut:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Anda mungkin perlu menjalankan arahan ini dengan `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Tugasan - uji image classifier

1. Anda boleh menggunakan CURL untuk menguji image classifier menggunakan alamat IP atau nama host komputer yang menjalankan agen IoT Edge. Cari alamat IP:

    * Jika anda berada di mesin yang sama dengan IoT Edge sedang berjalan, anda boleh menggunakan `localhost` sebagai nama host.
    * Jika anda menggunakan VM, anda boleh menggunakan sama ada alamat IP atau nama DNS VM.
    * Jika tidak, anda boleh mendapatkan alamat IP mesin yang menjalankan IoT Edge:
      * Pada Windows 10, ikuti [panduan mencari alamat IP anda](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Pada macOS, ikuti [panduan cara mencari alamat IP anda di Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Pada Linux, ikuti bahagian tentang mencari alamat IP peribadi dalam [panduan cara mencari alamat IP anda di Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Anda boleh menguji kontena dengan fail tempatan dengan menjalankan arahan curl berikut:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Gantikan `<IP address or name>` dengan alamat IP atau nama host komputer yang menjalankan IoT Edge. Gantikan `<file_Name>` dengan nama fail untuk diuji.

    Anda akan melihat hasil ramalan dalam output:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Tidak perlu memberikan kunci ramalan di sini, kerana ini tidak menggunakan sumber Azure. Sebaliknya, keselamatan akan dikonfigurasi pada rangkaian dalaman berdasarkan keperluan keselamatan dalaman, dan bukannya bergantung pada endpoint awam dan kunci API.

## Gunakan peranti IoT Edge anda

Sekarang bahawa Image Classifier anda telah dideploy ke peranti IoT Edge, anda boleh menggunakannya dari peranti IoT anda.

### Tugasan - gunakan peranti IoT Edge anda

Ikuti panduan yang relevan untuk mengklasifikasikan imej menggunakan IoT Edge classifier:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Komputer papan tunggal - Raspberry Pi/Peranti IoT Maya](single-board-computer.md)

### Latihan semula model

Salah satu kelemahan menjalankan image classifier pada IoT Edge adalah ia tidak disambungkan ke projek Custom Vision anda. Jika anda melihat tab **Predictions** dalam Custom Vision, anda tidak akan melihat imej yang diklasifikasikan menggunakan classifier berasaskan Edge.

Ini adalah tingkah laku yang dijangka - imej tidak dihantar ke cloud untuk klasifikasi, jadi ia tidak akan tersedia di cloud. Salah satu kelebihan menggunakan IoT Edge adalah privasi, memastikan imej tidak meninggalkan rangkaian anda, satu lagi adalah dapat bekerja secara offline, jadi tidak bergantung pada memuat naik imej apabila peranti tidak mempunyai sambungan internet. Kelemahannya adalah meningkatkan model anda - anda perlu melaksanakan cara lain untuk menyimpan imej yang boleh diklasifikasikan semula secara manual untuk meningkatkan dan melatih semula image classifier.

✅ Fikirkan cara untuk memuat naik imej bagi melatih semula classifier.

---

## 🚀 Cabaran

Menjalankan model AI pada peranti edge boleh lebih pantas daripada di cloud - jarak jaringan lebih pendek. Ia juga boleh lebih perlahan kerana perkakasan yang menjalankan model mungkin tidak sekuat cloud.

Lakukan pengukuran masa dan bandingkan sama ada panggilan ke peranti edge anda lebih pantas atau lebih perlahan daripada panggilan ke cloud? Fikirkan sebab untuk menjelaskan perbezaan, atau ketiadaan perbezaan. Kajian cara untuk menjalankan model AI lebih pantas di edge menggunakan perkakasan khusus.

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Ulasan & Kajian Kendiri

* Baca lebih lanjut tentang kontena di [halaman virtualisasi peringkat OS di Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Baca lebih lanjut mengenai pengkomputeran tepi, dengan penekanan pada bagaimana 5G boleh membantu mengembangkan pengkomputeran tepi dalam [artikel apa itu pengkomputeran tepi dan mengapa ia penting? di NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Ketahui lebih lanjut tentang menjalankan perkhidmatan AI di IoT Edge dengan menonton [episod belajar cara menggunakan Azure IoT Edge pada perkhidmatan AI sedia bina di Tepi untuk melakukan pengesanan bahasa dalam Learn Live di Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Tugasan

[Jalankan perkhidmatan lain di tepi](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.