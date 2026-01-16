<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-27T21:32:40+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "id"
}
-->
# Penyiraman tanaman otomatis

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Pelajaran ini diajarkan sebagai bagian dari [IoT untuk Pemula Proyek 2 - Seri Pertanian Digital](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Penyiraman tanaman otomatis berbasis IoT](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## Kuis sebelum pelajaran

[Kuis sebelum pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## Pendahuluan

Pada pelajaran sebelumnya, Anda telah belajar cara memantau kelembapan tanah. Dalam pelajaran ini, Anda akan belajar cara membangun komponen inti dari sistem penyiraman otomatis yang merespons kelembapan tanah. Anda juga akan mempelajari tentang waktu - bagaimana sensor membutuhkan waktu untuk merespons perubahan, dan bagaimana aktuator membutuhkan waktu untuk mengubah properti yang diukur oleh sensor.

Dalam pelajaran ini kita akan membahas:

* [Mengontrol perangkat berdaya tinggi dari perangkat IoT berdaya rendah](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Mengontrol relay](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Mengontrol tanaman Anda melalui MQTT](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Waktu sensor dan aktuator](../../../../../2-farm/lessons/3-automated-plant-watering)
* [Menambahkan waktu ke server kontrol tanaman Anda](../../../../../2-farm/lessons/3-automated-plant-watering)

## Mengontrol perangkat berdaya tinggi dari perangkat IoT berdaya rendah

Perangkat IoT menggunakan tegangan rendah. Meskipun ini cukup untuk sensor dan aktuator berdaya rendah seperti LED, tegangan ini terlalu rendah untuk mengontrol perangkat keras yang lebih besar, seperti pompa air yang digunakan untuk irigasi. Bahkan pompa kecil yang dapat digunakan untuk tanaman rumah membutuhkan arus terlalu besar untuk kit pengembangan IoT dan dapat merusak papan.

> 🎓 Arus, diukur dalam Ampere (A), adalah jumlah listrik yang bergerak melalui sirkuit. Tegangan memberikan dorongan, arus adalah seberapa banyak yang didorong. Anda dapat membaca lebih lanjut tentang arus di [halaman arus listrik di Wikipedia](https://wikipedia.org/wiki/Electric_current).

Solusinya adalah menghubungkan pompa ke sumber daya eksternal, dan menggunakan aktuator untuk menyalakan pompa, mirip dengan cara Anda menyalakan lampu. Dibutuhkan sedikit daya (dalam bentuk energi dari tubuh Anda) untuk jari Anda membalikkan saklar, dan ini menghubungkan lampu ke listrik utama yang berjalan pada 110v/240v.

![Saklar lampu menyalakan daya ke lampu](../../../../../translated_images/id/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.png)

> 🎓 [Listrik utama](https://wikipedia.org/wiki/Mains_electricity) mengacu pada listrik yang disalurkan ke rumah dan bisnis melalui infrastruktur nasional di banyak bagian dunia.

✅ Perangkat IoT biasanya dapat menyediakan 3.3V atau 5V, dengan arus kurang dari 1 amp (1A). Bandingkan ini dengan listrik utama yang paling sering berada pada 230V (120V di Amerika Utara dan 100V di Jepang), dan dapat menyediakan daya untuk perangkat yang membutuhkan 30A.

Ada sejumlah aktuator yang dapat melakukan ini, termasuk perangkat mekanis yang dapat Anda pasang ke saklar yang ada untuk meniru jari yang menyalakannya. Yang paling populer adalah relay.

### Relay

Relay adalah saklar elektromekanis yang mengubah sinyal listrik menjadi gerakan mekanis yang menyalakan saklar. Inti dari relay adalah elektromagnet.

> 🎓 [Elektromagnet](https://wikipedia.org/wiki/Electromagnet) adalah magnet yang dibuat dengan mengalirkan listrik melalui kumparan kawat. Ketika listrik dinyalakan, kumparan menjadi magnet. Ketika listrik dimatikan, kumparan kehilangan sifat magnetnya.

![Ketika menyala, elektromagnet menciptakan medan magnet, menyalakan saklar untuk sirkuit keluaran](../../../../../translated_images/id/relay-on.4db16a0fd6b66926.webp)

Dalam relay, sirkuit kontrol memberi daya pada elektromagnet. Ketika elektromagnet menyala, ia menarik tuas yang menggerakkan saklar, menutup sepasang kontak dan menyelesaikan sirkuit keluaran.

![Ketika mati, elektromagnet tidak menciptakan medan magnet, mematikan saklar untuk sirkuit keluaran](../../../../../translated_images/id/relay-off.c34a178a2960fecd.webp)

Ketika sirkuit kontrol mati, elektromagnet mati, melepaskan tuas dan membuka kontak, mematikan sirkuit keluaran. Relay adalah aktuator digital - sinyal tinggi ke relay menyalakannya, sinyal rendah mematikannya.

Sirkuit keluaran dapat digunakan untuk memberi daya pada perangkat keras tambahan, seperti sistem irigasi. Perangkat IoT dapat menyalakan relay, menyelesaikan sirkuit keluaran yang memberi daya pada sistem irigasi, dan tanaman mendapatkan air. Perangkat IoT kemudian dapat mematikan relay, memutus daya ke sistem irigasi, mematikan air.

![Relay menyala, menyalakan pompa yang mengirimkan air ke tanaman](../../../../../images/strawberry-pump.gif)

Dalam video di atas, relay dinyalakan. LED pada relay menyala untuk menunjukkan bahwa relay menyala (beberapa papan relay memiliki LED untuk menunjukkan apakah relay menyala atau mati), dan daya dikirim ke pompa, menyalakannya dan memompa air ke tanaman.

> 💁 Relay juga dapat digunakan untuk beralih antara dua sirkuit keluaran daripada menyalakan dan mematikan satu. Saat tuas bergerak, ia memindahkan saklar dari menyelesaikan satu sirkuit keluaran ke menyelesaikan sirkuit keluaran yang berbeda, biasanya berbagi koneksi daya umum, atau koneksi ground umum.

✅ Lakukan penelitian: Ada beberapa jenis relay, dengan perbedaan seperti apakah sirkuit kontrol menyalakan atau mematikan relay saat daya diterapkan, atau beberapa sirkuit keluaran. Cari tahu tentang jenis-jenis ini.

Saat tuas bergerak, Anda biasanya dapat mendengar suara klik yang jelas saat tuas membuat kontak dengan elektromagnet.

> 💁 Relay dapat dihubungkan sehingga membuat koneksi sebenarnya memutus daya ke relay, mematikan relay, yang kemudian mengirimkan daya ke relay menyalakannya kembali, dan seterusnya. Ini berarti relay akan berbunyi klik sangat cepat membuat suara berdengung. Ini adalah cara beberapa bel pintu listrik pertama bekerja.

### Daya relay

Elektromagnet tidak membutuhkan banyak daya untuk mengaktifkan dan menarik tuas, ia dapat dikontrol menggunakan keluaran 3.3V atau 5V dari kit pengembangan IoT. Sirkuit keluaran dapat membawa daya yang jauh lebih besar, tergantung pada relay, termasuk tegangan utama atau bahkan tingkat daya yang lebih tinggi untuk penggunaan industri. Dengan cara ini, kit pengembangan IoT dapat mengontrol sistem irigasi, dari pompa kecil untuk satu tanaman, hingga sistem industri besar untuk seluruh pertanian komersial.

![Relay Grove dengan sirkuit kontrol, sirkuit keluaran, dan relay diberi label](../../../../../translated_images/id/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.png)

Gambar di atas menunjukkan relay Grove. Sirkuit kontrol terhubung ke perangkat IoT dan menyalakan atau mematikan relay menggunakan 3.3V atau 5V. Sirkuit keluaran memiliki dua terminal, salah satunya dapat menjadi daya atau ground. Sirkuit keluaran dapat menangani hingga 250V pada 10A, cukup untuk berbagai perangkat yang menggunakan daya utama. Anda dapat menemukan relay yang dapat menangani tingkat daya yang lebih tinggi.

![Pompa yang dihubungkan melalui relay](../../../../../translated_images/id/pump-wired-to-relay.66c5cfc0d8918990.webp)

Dalam gambar di atas, daya disuplai ke pompa melalui relay. Ada kabel merah yang menghubungkan terminal +5V dari catu daya USB ke salah satu terminal sirkuit keluaran relay, dan kabel merah lainnya menghubungkan terminal lain dari sirkuit keluaran ke pompa. Kabel hitam menghubungkan pompa ke ground pada catu daya USB. Ketika relay menyala, ia menyelesaikan sirkuit, mengirimkan 5V ke pompa, menyalakan pompa.

## Mengontrol relay

Anda dapat mengontrol relay dari kit pengembangan IoT Anda.

### Tugas - mengontrol relay

Ikuti panduan yang relevan untuk mengontrol relay menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [Komputer papan tunggal - Raspberry Pi](pi-relay.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-relay.md)

## Mengontrol tanaman Anda melalui MQTT

Sejauh ini relay Anda dikontrol langsung oleh perangkat IoT berdasarkan satu pembacaan kelembapan tanah. Dalam sistem irigasi komersial, logika kontrol akan terpusat, memungkinkan pengambilan keputusan penyiraman menggunakan data dari beberapa sensor, dan memungkinkan konfigurasi apa pun diubah di satu tempat. Untuk mensimulasikan ini, Anda dapat mengontrol relay melalui MQTT.

### Tugas - mengontrol relay melalui MQTT

1. Tambahkan pustaka/paket pip MQTT yang relevan dan kode ke proyek `soil-moisture-sensor` Anda untuk terhubung ke MQTT. Beri nama ID klien sebagai `soilmoisturesensor_client` dengan awalan ID Anda.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk terhubung ke MQTT di proyek 1, pelajaran 4 jika diperlukan](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt).

1. Tambahkan kode perangkat yang relevan untuk mengirim telemetri dengan pengaturan kelembapan tanah. Untuk pesan telemetri, beri nama properti `soil_moisture`.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk mengirim telemetri ke MQTT di proyek 1, pelajaran 4 jika diperlukan](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device).

1. Buat beberapa kode server lokal untuk berlangganan telemetri dan mengirim perintah untuk mengontrol relay dalam folder bernama `soil-moisture-sensor-server`. Beri nama properti dalam pesan perintah sebagai `relay_on`, dan tetapkan ID klien sebagai `soilmoisturesensor_server` dengan awalan ID Anda. Pertahankan struktur yang sama seperti kode server yang Anda tulis untuk proyek 1, pelajaran 4 karena Anda akan menambahkan kode ini nanti dalam pelajaran ini.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk mengirim telemetri ke MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) dan [mengirim perintah melalui MQTT](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker) di proyek 1, pelajaran 4 jika diperlukan.

1. Tambahkan kode perangkat yang relevan untuk mengontrol relay dari perintah yang diterima, menggunakan properti `relay_on` dari pesan. Kirim true untuk `relay_on` jika `soil_moisture` lebih besar dari 450, jika tidak kirim false, sama seperti logika yang Anda tambahkan untuk perangkat IoT sebelumnya.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk merespons perintah dari MQTT di proyek 1, pelajaran 4 jika diperlukan](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device).

> 💁 Anda dapat menemukan kode ini di folder [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt).

Pastikan kode berjalan di perangkat dan server lokal Anda, dan uji dengan mengubah tingkat kelembapan tanah, baik dengan mengubah nilai yang dikirim oleh sensor virtual, atau dengan mengubah tingkat kelembapan tanah dengan menambahkan air atau mengeluarkan sensor dari tanah.

## Waktu sensor dan aktuator

Pada pelajaran 3, Anda membuat lampu malam - LED yang menyala segera setelah tingkat cahaya rendah terdeteksi oleh sensor cahaya. Sensor cahaya mendeteksi perubahan tingkat cahaya secara instan, dan perangkat dapat merespons dengan cepat, hanya dibatasi oleh panjang penundaan dalam fungsi `loop` atau `while True:`. Sebagai pengembang IoT, Anda tidak selalu dapat mengandalkan umpan balik yang begitu cepat.

### Waktu untuk kelembapan tanah

Jika Anda melakukan pelajaran terakhir tentang kelembapan tanah menggunakan sensor fisik, Anda mungkin memperhatikan bahwa diperlukan beberapa detik untuk pembacaan kelembapan tanah turun setelah Anda menyiram tanaman Anda. Ini bukan karena sensor lambat, tetapi karena air membutuhkan waktu untuk meresap ke dalam tanah.
💁 Jika Anda menyiram terlalu dekat dengan sensor, Anda mungkin melihat pembacaan turun dengan cepat, lalu naik kembali - ini disebabkan oleh air di dekat sensor yang menyebar ke seluruh tanah lainnya, sehingga mengurangi kelembapan tanah di sekitar sensor.
![Pengukuran kelembapan tanah sebesar 658 tidak berubah selama penyiraman, hanya turun menjadi 320 setelah penyiraman ketika air telah meresap ke dalam tanah](../../../../../translated_images/id/soil-moisture-travel.a0e31af222cf1438.webp)

Pada diagram di atas, pembacaan kelembapan tanah menunjukkan angka 658. Tanaman disiram, tetapi pembacaan ini tidak langsung berubah karena air belum mencapai sensor. Penyiraman bahkan bisa selesai sebelum air mencapai sensor dan nilai turun untuk mencerminkan tingkat kelembapan baru.

Jika Anda menulis kode untuk mengontrol sistem irigasi melalui relay berdasarkan tingkat kelembapan tanah, Anda perlu mempertimbangkan penundaan ini dan membangun pengaturan waktu yang lebih cerdas ke dalam perangkat IoT Anda.

✅ Luangkan waktu sejenak untuk memikirkan bagaimana Anda bisa melakukannya.

### Mengontrol waktu sensor dan aktuator

Bayangkan Anda ditugaskan untuk membangun sistem irigasi untuk sebuah lahan pertanian. Berdasarkan jenis tanah, tingkat kelembapan tanah yang ideal untuk tanaman yang ditanam telah ditemukan sesuai dengan pembacaan tegangan analog sebesar 400-450.

Anda bisa memprogram perangkat dengan cara yang sama seperti lampu malam - selama sensor membaca di atas 450, nyalakan relay untuk menyalakan pompa. Masalahnya adalah air membutuhkan waktu untuk mengalir dari pompa, melalui tanah, hingga mencapai sensor. Sensor akan menghentikan air ketika mendeteksi tingkat 450, tetapi tingkat air akan terus turun karena air yang dipompa terus meresap ke dalam tanah. Hasil akhirnya adalah pemborosan air dan risiko kerusakan akar.

✅ Ingat - terlalu banyak air bisa sama buruknya bagi tanaman seperti terlalu sedikit, dan membuang sumber daya yang berharga.

Solusi yang lebih baik adalah memahami bahwa ada penundaan antara aktuator yang menyala dan perubahan properti yang dibaca oleh sensor. Ini berarti tidak hanya sensor harus menunggu beberapa saat sebelum mengukur nilai lagi, tetapi aktuator juga perlu dimatikan untuk sementara waktu sebelum pengukuran sensor berikutnya dilakukan.

Berapa lama relay harus menyala setiap kali? Lebih baik berhati-hati dan hanya menyalakan relay untuk waktu yang singkat, lalu menunggu air meresap, kemudian memeriksa kembali tingkat kelembapan. Bagaimanapun, Anda selalu bisa menyalakan pompa lagi untuk menambahkan lebih banyak air, tetapi Anda tidak bisa mengeluarkan air dari tanah.

> 💁 Pengaturan waktu seperti ini sangat spesifik untuk perangkat IoT yang Anda bangun, properti yang Anda ukur, serta sensor dan aktuator yang digunakan.

![Tanaman stroberi terhubung ke air melalui pompa, dengan pompa terhubung ke relay. Relay dan sensor kelembapan tanah pada tanaman keduanya terhubung ke Raspberry Pi](../../../../../translated_images/id/strawberry-with-pump.b410fc72ac6aabad.webp)

Sebagai contoh, saya memiliki tanaman stroberi dengan sensor kelembapan tanah dan pompa yang dikontrol oleh relay. Saya telah mengamati bahwa ketika saya menambahkan air, dibutuhkan sekitar 20 detik agar pembacaan kelembapan tanah stabil. Ini berarti saya perlu mematikan relay dan menunggu 20 detik sebelum memeriksa tingkat kelembapan. Saya lebih memilih terlalu sedikit air daripada terlalu banyak - saya selalu bisa menyalakan pompa lagi, tetapi saya tidak bisa mengeluarkan air dari tanaman.

![Langkah 1, ambil pengukuran. Langkah 2, tambahkan air. Langkah 3, tunggu air meresap ke dalam tanah. Langkah 4, ambil pengukuran ulang](../../../../../translated_images/id/soil-moisture-delay.865f3fae206db01d.webp)

Ini berarti proses terbaik adalah siklus penyiraman yang seperti ini:

* Nyalakan pompa selama 5 detik
* Tunggu 20 detik
* Periksa kelembapan tanah
* Jika tingkatnya masih di atas yang dibutuhkan, ulangi langkah-langkah di atas

5 detik mungkin terlalu lama untuk pompa, terutama jika tingkat kelembapan hanya sedikit di atas tingkat yang diperlukan. Cara terbaik untuk mengetahui pengaturan waktu yang tepat adalah mencobanya, lalu menyesuaikan berdasarkan data sensor, dengan umpan balik yang terus-menerus. Ini bahkan bisa mengarah pada pengaturan waktu yang lebih rinci, seperti menyalakan pompa selama 1 detik untuk setiap 100 di atas tingkat kelembapan tanah yang diperlukan, daripada waktu tetap 5 detik.

✅ Lakukan penelitian: Apakah ada pertimbangan waktu lainnya? Apakah tanaman bisa disiram kapan saja saat kelembapan tanah terlalu rendah, atau ada waktu tertentu dalam sehari yang baik dan buruk untuk menyiram tanaman?

> 💁 Prediksi cuaca juga bisa dipertimbangkan saat mengontrol sistem penyiraman otomatis untuk tanaman di luar ruangan. Jika hujan diperkirakan akan turun, maka penyiraman bisa ditunda hingga hujan selesai. Pada saat itu, tanah mungkin sudah cukup lembap sehingga tidak perlu disiram, jauh lebih efisien daripada membuang air dengan menyiram tepat sebelum hujan.

## Tambahkan pengaturan waktu ke server kontrol tanaman Anda

Kode server dapat dimodifikasi untuk menambahkan kontrol seputar pengaturan waktu siklus penyiraman, dan menunggu tingkat kelembapan tanah berubah. Logika server untuk mengontrol pengaturan waktu relay adalah:

1. Pesan telemetri diterima
1. Periksa tingkat kelembapan tanah
1. Jika sudah cukup, tidak perlu melakukan apa-apa. Jika pembacaan terlalu tinggi (berarti kelembapan tanah terlalu rendah), maka:
    1. Kirim perintah untuk menyalakan relay
    1. Tunggu selama 5 detik
    1. Kirim perintah untuk mematikan relay
    1. Tunggu selama 20 detik agar tingkat kelembapan tanah stabil

Siklus penyiraman, proses dari menerima pesan telemetri hingga siap memproses tingkat kelembapan tanah lagi, memakan waktu sekitar 25 detik. Kami mengirimkan tingkat kelembapan tanah setiap 10 detik, sehingga ada tumpang tindih di mana pesan diterima saat server sedang menunggu tingkat kelembapan tanah stabil, yang bisa memulai siklus penyiraman lainnya.

Ada dua opsi untuk mengatasi ini:

* Ubah kode perangkat IoT untuk hanya mengirim telemetri setiap menit, dengan cara ini siklus penyiraman akan selesai sebelum pesan berikutnya dikirim
* Berhenti berlangganan telemetri selama siklus penyiraman

Opsi pertama tidak selalu menjadi solusi yang baik untuk lahan pertanian besar. Petani mungkin ingin menangkap tingkat kelembapan tanah saat tanah sedang disiram untuk analisis di kemudian hari, misalnya untuk mengetahui aliran air di berbagai area di lahan pertanian guna memandu penyiraman yang lebih terarah. Opsi kedua lebih baik - kode hanya mengabaikan telemetri saat tidak bisa menggunakannya, tetapi telemetri tetap ada untuk layanan lain yang mungkin berlangganan.

> 💁 Data IoT tidak dikirim dari hanya satu perangkat ke hanya satu layanan, melainkan banyak perangkat dapat mengirim data ke broker, dan banyak layanan dapat mendengarkan data dari broker. Misalnya, satu layanan dapat mendengarkan data kelembapan tanah dan menyimpannya dalam database untuk analisis di kemudian hari. Layanan lain juga dapat mendengarkan telemetri yang sama untuk mengontrol sistem irigasi.

### Tugas - tambahkan pengaturan waktu ke server kontrol tanaman Anda

Perbarui kode server Anda untuk menjalankan relay selama 5 detik, lalu tunggu 20 detik.

1. Buka folder `soil-moisture-sensor-server` di VS Code jika belum terbuka. Pastikan lingkungan virtual diaktifkan.

1. Buka file `app.py`

1. Tambahkan kode berikut ke file `app.py` di bawah impor yang sudah ada:

    ```python
    import threading
    ```

    Pernyataan ini mengimpor `threading` dari pustaka Python, threading memungkinkan Python menjalankan kode lain saat sedang menunggu.

1. Tambahkan kode berikut sebelum fungsi `handle_telemetry` yang menangani pesan telemetri yang diterima oleh kode server:

    ```python
    water_time = 5
    wait_time = 20
    ```

    Ini mendefinisikan berapa lama relay harus berjalan (`water_time`), dan berapa lama harus menunggu setelahnya untuk memeriksa kelembapan tanah (`wait_time`).

1. Di bawah kode ini, tambahkan yang berikut:

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    Kode ini mendefinisikan fungsi bernama `send_relay_command` yang mengirimkan perintah melalui MQTT untuk mengontrol relay. Telemetri dibuat sebagai dictionary, lalu dikonversi menjadi string JSON. Nilai yang diteruskan ke `state` menentukan apakah relay harus menyala atau mati.

1. Setelah fungsi `send_relay_code`, tambahkan kode berikut:

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    Ini mendefinisikan fungsi untuk mengontrol relay berdasarkan pengaturan waktu yang diperlukan. Dimulai dengan berhenti berlangganan telemetri sehingga pesan kelembapan tanah tidak diproses saat penyiraman sedang berlangsung. Selanjutnya, mengirimkan perintah untuk menyalakan relay. Kemudian menunggu selama `water_time` sebelum mengirimkan perintah untuk mematikan relay. Akhirnya, menunggu tingkat kelembapan tanah stabil selama `wait_time` detik. Kemudian berlangganan kembali ke telemetri.

1. Ubah fungsi `handle_telemetry` menjadi berikut:

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    Kode ini memeriksa tingkat kelembapan tanah. Jika lebih besar dari 450, tanah membutuhkan penyiraman, sehingga memanggil fungsi `control_relay`. Fungsi ini dijalankan pada thread terpisah, berjalan di latar belakang.

1. Pastikan perangkat IoT Anda berjalan, lalu jalankan kode ini. Ubah tingkat kelembapan tanah dan amati apa yang terjadi pada relay - relay harus menyala selama 5 detik lalu tetap mati setidaknya selama 20 detik, hanya menyala jika tingkat kelembapan tanah tidak mencukupi.

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    Cara yang baik untuk menguji ini dalam sistem irigasi simulasi adalah menggunakan tanah kering, lalu tuangkan air secara manual saat relay menyala, berhenti menuangkan saat relay mati.

> 💁 Anda dapat menemukan kode ini di folder [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing).

> 💁 Jika Anda ingin menggunakan pompa untuk membangun sistem irigasi nyata, maka Anda dapat menggunakan [pompa air 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) dengan [catu daya terminal USB](https://www.adafruit.com/product/3628). Pastikan daya ke atau dari pompa terhubung melalui relay.

---

## 🚀 Tantangan

Bisakah Anda memikirkan perangkat IoT atau perangkat listrik lainnya yang memiliki masalah serupa di mana dibutuhkan waktu agar hasil dari aktuator mencapai sensor? Anda mungkin memiliki beberapa di rumah atau sekolah Anda.

* Properti apa yang mereka ukur?
* Berapa lama waktu yang dibutuhkan agar properti berubah setelah aktuator digunakan?
* Apakah tidak apa-apa jika properti berubah melewati nilai yang diperlukan?
* Bagaimana cara mengembalikannya ke nilai yang diperlukan jika diperlukan?

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang relay termasuk penggunaannya secara historis dalam pertukaran telepon di [halaman Wikipedia relay](https://wikipedia.org/wiki/Relay).

## Tugas

[Bangun siklus penyiraman yang lebih efisien](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.