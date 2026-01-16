<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T21:08:19+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "id"
}
-->
# Jalankan Detektor Buah Anda di Perangkat Edge

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran tentang menjalankan pengklasifikasi gambar pada perangkat IoT, topik yang dibahas dalam pelajaran ini.

[![Custom Vision AI di Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Pendahuluan

Pada pelajaran sebelumnya, Anda menggunakan pengklasifikasi gambar untuk mengklasifikasikan buah matang dan belum matang, dengan mengirimkan gambar yang diambil oleh kamera pada perangkat IoT Anda melalui internet ke layanan cloud. Proses ini memakan waktu, memerlukan biaya, dan tergantung pada jenis data gambar yang Anda gunakan, dapat memiliki implikasi privasi.

Dalam pelajaran ini, Anda akan belajar cara menjalankan model pembelajaran mesin (ML) di perangkat edge - pada perangkat IoT yang berjalan di jaringan Anda sendiri, bukan di cloud. Anda akan mempelajari manfaat dan kekurangan komputasi edge dibandingkan komputasi cloud, cara menerapkan model AI Anda ke perangkat edge, dan cara mengaksesnya dari perangkat IoT Anda.

Dalam pelajaran ini, kita akan membahas:

* [Komputasi Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Mendaftarkan perangkat IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Menyiapkan perangkat IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Ekspor model Anda](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Persiapkan kontainer Anda untuk penerapan](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Terapkan kontainer Anda](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Gunakan perangkat IoT Edge Anda](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Komputasi Edge

Komputasi edge melibatkan penggunaan komputer yang memproses data IoT sedekat mungkin dengan tempat data tersebut dihasilkan. Alih-alih memproses data di cloud, proses ini dipindahkan ke tepi cloud - jaringan internal Anda.

![Diagram arsitektur yang menunjukkan layanan internet di cloud dan perangkat IoT di jaringan lokal](../../../../../translated_images/id/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

Dalam pelajaran sejauh ini, Anda telah memiliki perangkat yang mengumpulkan data dan mengirimkannya ke cloud untuk dianalisis, menjalankan fungsi serverless atau model AI di cloud.

![Diagram arsitektur yang menunjukkan perangkat IoT di jaringan lokal yang terhubung ke perangkat edge, dan perangkat edge tersebut terhubung ke cloud](../../../../../translated_images/id/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Komputasi edge melibatkan pemindahan beberapa layanan cloud dari cloud ke komputer yang berjalan di jaringan yang sama dengan perangkat IoT, hanya berkomunikasi dengan cloud jika diperlukan. Sebagai contoh, Anda dapat menjalankan model AI pada perangkat edge untuk menganalisis kematangan buah, dan hanya mengirimkan analitik kembali ke cloud, seperti jumlah buah matang dibandingkan buah yang belum matang.

✅ Pikirkan tentang aplikasi IoT yang telah Anda bangun sejauh ini. Bagian mana dari aplikasi tersebut yang dapat dipindahkan ke edge?

### Keuntungan

Keuntungan dari komputasi edge adalah:

1. **Kecepatan** - komputasi edge ideal untuk data yang sensitif terhadap waktu karena tindakan dilakukan di jaringan yang sama dengan perangkat, bukan melalui panggilan internet. Ini memungkinkan kecepatan yang lebih tinggi karena jaringan internal dapat berjalan jauh lebih cepat daripada koneksi internet, dengan data yang menempuh jarak yang jauh lebih pendek.

    > 💁 Meskipun kabel optik digunakan untuk koneksi internet yang memungkinkan data bergerak dengan kecepatan cahaya, data dapat memakan waktu untuk bergerak di seluruh dunia ke penyedia cloud. Sebagai contoh, jika Anda mengirim data dari Eropa ke layanan cloud di AS, setidaknya diperlukan 28ms untuk data melintasi Atlantik melalui kabel optik, dan itu belum termasuk waktu yang dibutuhkan untuk mengirim data ke kabel transatlantik, mengonversi dari sinyal listrik ke cahaya dan kembali lagi di sisi lain, lalu dari kabel optik ke penyedia cloud.

    Komputasi edge juga membutuhkan lalu lintas jaringan yang lebih sedikit, mengurangi risiko data Anda melambat karena kemacetan pada bandwidth terbatas yang tersedia untuk koneksi internet.

1. **Aksesibilitas jarak jauh** - komputasi edge bekerja ketika Anda memiliki konektivitas yang terbatas atau tidak ada sama sekali, atau konektivitas terlalu mahal untuk digunakan secara terus-menerus. Sebagai contoh, ketika bekerja di daerah bencana kemanusiaan di mana infrastruktur terbatas, atau di negara berkembang.

1. **Biaya lebih rendah** - pengumpulan data, penyimpanan, analisis, dan pemicu tindakan pada perangkat edge mengurangi penggunaan layanan cloud yang dapat mengurangi biaya keseluruhan aplikasi IoT Anda. Baru-baru ini, ada peningkatan perangkat yang dirancang untuk komputasi edge, seperti papan akselerator AI seperti [Jetson Nano dari NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), yang dapat menjalankan beban kerja AI menggunakan perangkat keras berbasis GPU pada perangkat yang harganya kurang dari US$100.

1. **Privasi dan keamanan** - dengan komputasi edge, data tetap berada di jaringan Anda dan tidak diunggah ke cloud. Hal ini sering kali lebih disukai untuk informasi yang sensitif dan dapat diidentifikasi secara pribadi, terutama karena data tidak perlu disimpan setelah dianalisis, yang sangat mengurangi risiko kebocoran data. Contohnya termasuk data medis dan rekaman kamera keamanan.

1. **Penanganan perangkat yang tidak aman** - jika Anda memiliki perangkat dengan kelemahan keamanan yang diketahui yang tidak ingin Anda sambungkan langsung ke jaringan atau internet Anda, maka Anda dapat menghubungkannya ke jaringan terpisah ke perangkat gateway IoT Edge. Perangkat edge ini kemudian juga dapat memiliki koneksi ke jaringan yang lebih luas atau internet Anda, dan mengelola aliran data bolak-balik.

1. **Dukungan untuk perangkat yang tidak kompatibel** - jika Anda memiliki perangkat yang tidak dapat terhubung ke IoT Hub, misalnya perangkat yang hanya dapat terhubung menggunakan koneksi HTTP atau perangkat yang hanya memiliki Bluetooth untuk terhubung, Anda dapat menggunakan perangkat IoT edge sebagai perangkat gateway, meneruskan pesan ke IoT Hub.

✅ Lakukan penelitian: Apa keuntungan lain yang mungkin ada dari komputasi edge?

### Kekurangan

Ada kekurangan dari komputasi edge, di mana cloud mungkin menjadi pilihan yang lebih disukai:

1. **Skalabilitas dan fleksibilitas** - komputasi cloud dapat menyesuaikan kebutuhan jaringan dan data secara real-time dengan menambah atau mengurangi server dan sumber daya lainnya. Untuk menambahkan lebih banyak komputer edge memerlukan penambahan perangkat secara manual.

1. **Keandalan dan ketahanan** - komputasi cloud menyediakan beberapa server yang sering kali berada di beberapa lokasi untuk redundansi dan pemulihan bencana. Untuk memiliki tingkat redundansi yang sama di edge memerlukan investasi besar dan banyak pekerjaan konfigurasi.

1. **Pemeliharaan** - penyedia layanan cloud menyediakan pemeliharaan dan pembaruan sistem.

✅ Lakukan penelitian: Apa kekurangan lain yang mungkin ada dari komputasi edge?

Kekurangan ini sebenarnya adalah kebalikan dari keuntungan menggunakan cloud - Anda harus membangun dan mengelola perangkat ini sendiri, daripada mengandalkan keahlian dan skala penyedia cloud.

Beberapa risiko dapat diminimalkan oleh sifat komputasi edge itu sendiri. Sebagai contoh, jika Anda memiliki perangkat edge yang berjalan di pabrik yang mengumpulkan data dari mesin, Anda tidak perlu memikirkan beberapa skenario pemulihan bencana. Jika listrik di pabrik mati, maka Anda tidak memerlukan perangkat edge cadangan karena mesin yang menghasilkan data yang diproses perangkat edge juga akan kehilangan daya.

Untuk sistem IoT, Anda sering kali menginginkan kombinasi komputasi cloud dan edge, memanfaatkan setiap layanan berdasarkan kebutuhan sistem, pelanggan, dan pemeliharanya.

## Azure IoT Edge

![Logo Azure IoT Edge](../../../../../translated_images/id/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge adalah layanan yang dapat membantu Anda memindahkan beban kerja dari cloud ke edge. Anda mengatur perangkat sebagai perangkat edge, dan dari cloud Anda dapat menerapkan kode ke perangkat edge tersebut. Ini memungkinkan Anda menggabungkan kemampuan cloud dan edge.

> 🎓 *Beban kerja* adalah istilah untuk layanan apa pun yang melakukan pekerjaan tertentu, seperti model AI, aplikasi, atau fungsi serverless.

Sebagai contoh, Anda dapat melatih pengklasifikasi gambar di cloud, lalu dari cloud menerapkannya ke perangkat edge. Perangkat IoT Anda kemudian mengirimkan gambar ke perangkat edge untuk diklasifikasikan, daripada mengirimkan gambar melalui internet. Jika Anda perlu menerapkan iterasi baru dari model, Anda dapat melatihnya di cloud dan menggunakan IoT Edge untuk memperbarui model di perangkat edge ke iterasi baru Anda.

> 🎓 Perangkat lunak yang diterapkan ke IoT Edge dikenal sebagai *modul*. Secara default, IoT Edge menjalankan modul yang berkomunikasi dengan IoT Hub, seperti modul `edgeAgent` dan `edgeHub`. Ketika Anda menerapkan pengklasifikasi gambar, ini diterapkan sebagai modul tambahan.

IoT Edge terintegrasi dengan IoT Hub, sehingga Anda dapat mengelola perangkat edge menggunakan layanan yang sama yang Anda gunakan untuk mengelola perangkat IoT, dengan tingkat keamanan yang sama.

IoT Edge menjalankan kode dari *kontainer* - aplikasi mandiri yang dijalankan secara terisolasi dari aplikasi lain di komputer Anda. Ketika Anda menjalankan kontainer, itu bertindak seperti komputer terpisah yang berjalan di dalam komputer Anda, dengan perangkat lunak, layanan, dan aplikasi sendiri yang berjalan. Sebagian besar waktu, kontainer tidak dapat mengakses apa pun di komputer Anda kecuali Anda memilih untuk berbagi hal-hal seperti folder dengan kontainer. Kontainer kemudian mengekspos layanan melalui port terbuka yang dapat Anda hubungkan atau ekspos ke jaringan Anda.

![Permintaan web dialihkan ke kontainer](../../../../../translated_images/id/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Sebagai contoh, Anda dapat memiliki kontainer dengan situs web yang berjalan di port 80, port HTTP default, dan Anda kemudian dapat mengeksposnya dari komputer Anda juga di port 80.

✅ Lakukan penelitian: Baca tentang kontainer dan layanan seperti Docker atau Moby.

Anda dapat menggunakan Custom Vision untuk mengunduh pengklasifikasi gambar dan menerapkannya sebagai kontainer, baik langsung ke perangkat atau diterapkan melalui IoT Edge. Setelah berjalan di kontainer, mereka dapat diakses menggunakan API REST yang sama seperti versi cloud, tetapi dengan endpoint yang mengarah ke perangkat Edge yang menjalankan kontainer.

## Mendaftarkan perangkat IoT Edge

Untuk menggunakan perangkat IoT Edge, perangkat tersebut perlu didaftarkan di IoT Hub.

### Tugas - mendaftarkan perangkat IoT Edge

1. Buat IoT Hub di grup sumber daya `fruit-quality-detector`. Berikan nama unik berdasarkan `fruit-quality-detector`.

1. Daftarkan perangkat IoT Edge bernama `fruit-quality-detector-edge` di IoT Hub Anda. Perintah untuk melakukan ini mirip dengan perintah yang digunakan untuk mendaftarkan perangkat non-edge, kecuali Anda menambahkan flag `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Ganti `<hub_name>` dengan nama IoT Hub Anda.

1. Dapatkan string koneksi untuk perangkat Anda menggunakan perintah berikut:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Ganti `<hub_name>` dengan nama IoT Hub Anda.

    Salin string koneksi yang ditampilkan di output.

## Menyiapkan perangkat IoT Edge

Setelah Anda membuat pendaftaran perangkat edge di IoT Hub Anda, Anda dapat menyiapkan perangkat edge.

### Tugas - Instal dan mulai IoT Edge Runtime

**IoT Edge runtime hanya menjalankan kontainer Linux.** Ini dapat dijalankan di Linux, atau di Windows menggunakan Mesin Virtual Linux.

* Jika Anda menggunakan Raspberry Pi sebagai perangkat IoT Anda, maka ini menjalankan versi Linux yang didukung dan dapat menjadi host IoT Edge runtime. Ikuti [panduan instalasi Azure IoT Edge untuk Linux di dokumen Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) untuk menginstal IoT Edge dan mengatur string koneksi.

    > 💁 Ingat, Raspberry Pi OS adalah varian dari Debian Linux.

* Jika Anda tidak menggunakan Raspberry Pi, tetapi memiliki komputer Linux, Anda dapat menjalankan IoT Edge runtime. Ikuti [panduan instalasi Azure IoT Edge untuk Linux di dokumen Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) untuk menginstal IoT Edge dan mengatur string koneksi.

* Jika Anda menggunakan Windows, Anda dapat menginstal IoT Edge runtime di Mesin Virtual Linux dengan mengikuti [bagian instal dan mulai IoT Edge runtime dari panduan cepat menerapkan modul IoT Edge pertama Anda ke perangkat Windows di dokumen Microsoft](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Anda dapat berhenti ketika mencapai bagian *Deploy a module*.

* Jika Anda menggunakan macOS, Anda dapat membuat mesin virtual (VM) di cloud untuk digunakan sebagai perangkat IoT Edge Anda. Ini adalah komputer yang dapat Anda buat di cloud dan akses melalui internet. Anda dapat membuat VM Linux yang memiliki IoT Edge terinstal. Ikuti [panduan membuat mesin virtual yang menjalankan IoT Edge](vm-iotedge.md) untuk instruksi tentang cara melakukannya.

## Ekspor model Anda

Untuk menjalankan pengklasifikasi di edge, model tersebut perlu diekspor dari Custom Vision. Custom Vision dapat menghasilkan dua jenis model - model standar dan model compact. Model compact menggunakan berbagai teknik untuk mengurangi ukuran model, membuatnya cukup kecil untuk diunduh dan diterapkan pada perangkat IoT.

Ketika Anda membuat pengklasifikasi gambar, Anda menggunakan domain *Food*, versi model yang dioptimalkan untuk pelatihan pada gambar makanan. Di Custom Vision, Anda dapat mengubah domain proyek Anda, menggunakan data pelatihan Anda untuk melatih model baru dengan domain baru. Semua domain yang didukung oleh Custom Vision tersedia sebagai standar dan compact.

### Tugas - latih model Anda menggunakan domain Food (compact)
1. Buka portal Custom Vision di [CustomVision.ai](https://customvision.ai) dan masuk jika belum membukanya. Kemudian buka proyek `fruit-quality-detector` Anda.

1. Pilih tombol **Settings** (ikon ⚙).

1. Dalam daftar *Domains*, pilih *Food (compact)*.

1. Di bawah *Export Capabilities*, pastikan *Basic platforms (Tensorflow, CoreML, ONNX, ...)* dipilih.

1. Di bagian bawah halaman Settings, pilih **Save Changes**.

1. Latih ulang model dengan tombol **Train**, pilih *Quick training*.

### Tugas - ekspor model Anda

Setelah model dilatih, model tersebut perlu diekspor sebagai container.

1. Pilih tab **Performance**, dan temukan iterasi terbaru yang dilatih menggunakan domain compact.

1. Pilih tombol **Export** di bagian atas.

1. Pilih **DockerFile**, lalu pilih versi yang sesuai dengan perangkat edge Anda:

    * Jika Anda menjalankan IoT Edge di komputer Linux, komputer Windows, atau Virtual Machine, pilih versi *Linux*.
    * Jika Anda menjalankan IoT Edge di Raspberry Pi, pilih versi *ARM (Raspberry Pi 3)*.

    
> 🎓 Docker adalah salah satu alat paling populer untuk mengelola container, dan DockerFile adalah serangkaian instruksi tentang cara mengatur container.

1. Pilih **Export** untuk membuat file yang relevan di Custom Vision, lalu **Download** untuk mengunduhnya dalam file zip.

1. Simpan file ke komputer Anda, lalu ekstrak foldernya.

## Persiapkan container Anda untuk deployment

![Container dibuat lalu didorong ke container registry, kemudian diterapkan dari container registry ke perangkat edge menggunakan IoT Edge](../../../../../translated_images/id/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Setelah Anda mengunduh model Anda, model tersebut perlu dibangun ke dalam container, lalu didorong ke container registry - lokasi online tempat Anda dapat menyimpan container. IoT Edge kemudian dapat mengunduh container dari registry dan mendorongnya ke perangkat Anda.

![Logo Azure Container Registry](../../../../../translated_images/id/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Container registry yang akan Anda gunakan untuk pelajaran ini adalah Azure Container Registry. Ini bukan layanan gratis, jadi untuk menghemat uang pastikan Anda [membersihkan proyek Anda](../../../clean-up.md) setelah selesai.

> 💁 Anda dapat melihat biaya penggunaan Azure Container Registry di [halaman harga Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Tugas - instal Docker

Untuk membangun dan menerapkan classifier, Anda mungkin perlu menginstal [Docker](https://www.docker.com/).

Anda hanya perlu melakukannya jika Anda berencana membangun container dari perangkat yang berbeda dengan perangkat tempat Anda menginstal IoT Edge - sebagai bagian dari instalasi IoT Edge, Docker sudah diinstal untuk Anda.

1. Jika Anda membangun container Docker di perangkat yang berbeda dari perangkat IoT Edge Anda, ikuti instruksi instalasi Docker di [halaman instal Docker](https://www.docker.com/products/docker-desktop) untuk menginstal Docker Desktop atau Docker engine. Pastikan Docker berjalan setelah instalasi.

### Tugas - buat resource container registry

1. Jalankan perintah berikut dari Terminal atau command prompt Anda untuk membuat resource Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Ganti `<Container registry name>` dengan nama unik untuk container registry Anda, menggunakan huruf dan angka saja. Dasarkan nama ini pada `fruitqualitydetector`. Nama ini menjadi bagian dari URL untuk mengakses container registry, sehingga harus unik secara global.

1. Masuk ke Azure Container Registry dengan perintah berikut:

    ```sh
    az acr login --name <Container registry name>
    ```

    Ganti `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda.

1. Aktifkan mode admin pada container registry agar Anda dapat menghasilkan password dengan perintah berikut:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Ganti `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda.

1. Hasilkan password untuk container registry Anda dengan perintah berikut:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Ganti `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda.

    Salin nilai `PASSWORD`, karena Anda akan membutuhkannya nanti.

### Tugas - bangun container Anda

Apa yang Anda unduh dari Custom Vision adalah DockerFile yang berisi instruksi tentang cara membangun container, bersama dengan kode aplikasi yang akan dijalankan di dalam container untuk meng-host model Custom Vision Anda, serta REST API untuk memanggilnya. Anda dapat menggunakan Docker untuk membangun container yang diberi tag dari DockerFile, lalu mendorongnya ke container registry Anda.

> 🎓 Container diberi tag yang mendefinisikan nama dan versi untuk mereka. Ketika Anda perlu memperbarui container, Anda dapat membangunnya dengan tag yang sama tetapi versi yang lebih baru.

1. Buka terminal atau command prompt Anda dan navigasikan ke model yang telah diekstrak yang Anda unduh dari Custom Vision.

1. Jalankan perintah berikut untuk membangun dan memberi tag pada image:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Ganti `<platform>` dengan platform tempat container ini akan dijalankan. Jika Anda menjalankan IoT Edge di Raspberry Pi, atur ini ke `linux/armhf`, jika tidak, atur ini ke `linux/amd64`.

    > 💁 Jika Anda menjalankan perintah ini dari perangkat tempat Anda menjalankan IoT Edge, seperti menjalankan ini dari Raspberry Pi Anda, Anda dapat menghilangkan bagian `--platform <platform>` karena secara default akan menggunakan platform saat ini.

    Ganti `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda.

    > 💁 Jika Anda menjalankan di Linux atau Raspberry Pi OS, Anda mungkin perlu menggunakan `sudo` untuk menjalankan perintah ini.

    Docker akan membangun image, mengonfigurasi semua perangkat lunak yang diperlukan. Image kemudian akan diberi tag sebagai `classifier:v1`.

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

### Tugas - dorong container Anda ke container registry Anda

1. Gunakan perintah berikut untuk mendorong container Anda ke container registry Anda:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Ganti `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda.

    > 💁 Jika Anda menjalankan Linux, Anda mungkin perlu menggunakan `sudo` untuk menjalankan perintah ini.

    Container akan didorong ke container registry.

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

1. Untuk memverifikasi push, Anda dapat mencantumkan container di registry Anda dengan perintah berikut:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Ganti `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Anda akan melihat classifier Anda terdaftar dalam output.

## Terapkan container Anda

Container Anda sekarang dapat diterapkan ke perangkat IoT Edge Anda. Untuk menerapkan, Anda perlu mendefinisikan deployment manifest - dokumen JSON yang mencantumkan modul yang akan diterapkan ke perangkat edge.

### Tugas - buat deployment manifest

1. Buat file baru bernama `deployment.json` di suatu tempat di komputer Anda.

1. Tambahkan berikut ini ke file tersebut:

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

    > 💁 Anda dapat menemukan file ini di folder [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Ganti tiga instance `<Container registry name>` dengan nama yang Anda gunakan untuk container registry Anda. Satu ada di bagian modul `ImageClassifier`, dua lainnya ada di bagian `registryCredentials`.

    Ganti `<Container registry password>` di bagian `registryCredentials` dengan password container registry Anda.

1. Dari folder yang berisi deployment manifest Anda, jalankan perintah berikut:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Ganti `<hub_name>` dengan nama IoT Hub Anda.

    Modul image classifier akan diterapkan ke perangkat edge Anda.

### Tugas - verifikasi classifier berjalan

1. Hubungkan ke perangkat IoT Edge:

    * Jika Anda menggunakan Raspberry Pi untuk menjalankan IoT Edge, hubungkan menggunakan ssh baik dari terminal Anda, atau melalui sesi SSH jarak jauh di VS Code.
    * Jika Anda menjalankan IoT Edge dalam container Linux di Windows, ikuti langkah-langkah dalam [panduan verifikasi konfigurasi yang berhasil](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) untuk terhubung ke perangkat IoT Edge.
    * Jika Anda menjalankan IoT Edge di virtual machine, Anda dapat SSH ke mesin menggunakan `adminUsername` dan `password` yang Anda tetapkan saat membuat VM, dan menggunakan alamat IP atau nama DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Atau:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Masukkan password Anda saat diminta.

1. Setelah Anda terhubung, jalankan perintah berikut untuk mendapatkan daftar modul IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Anda mungkin perlu menjalankan perintah ini dengan `sudo`.

    Anda akan melihat modul yang berjalan:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Periksa log untuk modul Image classifier dengan perintah berikut:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Anda mungkin perlu menjalankan perintah ini dengan `sudo`.

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

### Tugas - uji image classifier

1. Anda dapat menggunakan CURL untuk menguji image classifier menggunakan alamat IP atau nama host komputer yang menjalankan agen IoT Edge. Temukan alamat IP:

    * Jika Anda berada di mesin yang sama dengan IoT Edge berjalan, Anda dapat menggunakan `localhost` sebagai nama host.
    * Jika Anda menggunakan VM, Anda dapat menggunakan alamat IP atau nama DNS VM.
    * Jika tidak, Anda dapat memperoleh alamat IP mesin yang menjalankan IoT Edge:
      * Di Windows 10, ikuti [panduan menemukan alamat IP Anda](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Di macOS, ikuti [panduan cara menemukan alamat IP Anda di Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Di Linux, ikuti bagian tentang menemukan alamat IP pribadi Anda di [panduan cara menemukan alamat IP Anda di Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Anda dapat menguji container dengan file lokal dengan menjalankan perintah curl berikut:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Ganti `<IP address or name>` dengan alamat IP atau nama host komputer yang menjalankan IoT Edge. Ganti `<file_Name>` dengan nama file untuk diuji.

    Anda akan melihat hasil prediksi dalam output:

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

    > 💁 Tidak perlu memberikan kunci prediksi di sini, karena ini tidak menggunakan resource Azure. Sebagai gantinya, keamanan akan dikonfigurasi di jaringan internal berdasarkan kebutuhan keamanan internal, daripada mengandalkan endpoint publik dan kunci API.

## Gunakan perangkat IoT Edge Anda

Sekarang Image Classifier Anda telah diterapkan ke perangkat IoT Edge, Anda dapat menggunakannya dari perangkat IoT Anda.

### Tugas - gunakan perangkat IoT Edge Anda

Ikuti panduan yang relevan untuk mengklasifikasikan gambar menggunakan classifier IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Komputer papan tunggal - Raspberry Pi/Virtual IoT device](single-board-computer.md)

### Pelatihan ulang model

Salah satu kekurangan menjalankan image classifier di IoT Edge adalah mereka tidak terhubung ke proyek Custom Vision Anda. Jika Anda melihat tab **Predictions** di Custom Vision, Anda tidak akan melihat gambar yang diklasifikasikan menggunakan classifier berbasis Edge.

Ini adalah perilaku yang diharapkan - gambar tidak dikirim ke cloud untuk diklasifikasikan, sehingga tidak akan tersedia di cloud. Salah satu keuntungan menggunakan IoT Edge adalah privasi, memastikan gambar tidak meninggalkan jaringan Anda, keuntungan lainnya adalah dapat bekerja offline, sehingga tidak bergantung pada pengunggahan gambar saat perangkat tidak memiliki koneksi internet. Kekurangannya adalah meningkatkan model Anda - Anda perlu menerapkan cara lain untuk menyimpan gambar yang dapat diklasifikasikan ulang secara manual untuk meningkatkan dan melatih ulang image classifier.

✅ Pikirkan cara untuk mengunggah gambar guna melatih ulang classifier.

---

## 🚀 Tantangan

Menjalankan model AI di perangkat edge bisa lebih cepat daripada di cloud - lompatan jaringan lebih pendek. Namun, bisa juga lebih lambat karena perangkat keras yang menjalankan model mungkin tidak sekuat cloud.

Lakukan pengukuran waktu dan bandingkan apakah panggilan ke perangkat edge Anda lebih cepat atau lebih lambat daripada panggilan ke cloud? Pikirkan alasan untuk menjelaskan perbedaan, atau tidak adanya perbedaan. Teliti cara menjalankan model AI lebih cepat di edge menggunakan perangkat keras khusus.

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang container di [halaman virtualisasi tingkat OS di Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Baca lebih lanjut tentang komputasi edge, dengan penekanan pada bagaimana 5G dapat membantu memperluas komputasi edge dalam [artikel apa itu komputasi edge dan mengapa itu penting? di NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Pelajari lebih lanjut tentang menjalankan layanan AI di IoT Edge dengan menonton [pelajari cara menggunakan Azure IoT Edge pada layanan AI yang sudah dibuat di Edge untuk mendeteksi bahasa dalam episode Learn Live di Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Tugas

[Jalankan layanan lain di edge](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.