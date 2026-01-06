<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T21:16:40+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "ms"
}
-->
# Mencetuskan pengesanan kualiti buah dari sensor

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.ms.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

## Kuiz sebelum kuliah

[Kuiz sebelum kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Pengenalan

Aplikasi IoT bukan hanya satu peranti yang menangkap data dan menghantarnya ke awan, tetapi lebih sering melibatkan pelbagai peranti yang bekerjasama untuk menangkap data dari dunia fizikal menggunakan sensor, membuat keputusan berdasarkan data tersebut, dan berinteraksi kembali dengan dunia fizikal melalui aktuator atau visualisasi.

Dalam pelajaran ini, anda akan mempelajari lebih lanjut tentang merancang aplikasi IoT yang kompleks, menggabungkan pelbagai sensor, pelbagai perkhidmatan awan untuk menganalisis dan menyimpan data, serta menunjukkan respons melalui aktuator. Anda akan belajar bagaimana merancang prototaip sistem kawalan kualiti buah, termasuk menggunakan sensor jarak untuk mencetuskan aplikasi IoT, dan bagaimana seni bina prototaip ini akan kelihatan.

Dalam pelajaran ini, kita akan membincangkan:

* [Merancang aplikasi IoT yang kompleks](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Mereka bentuk sistem kawalan kualiti buah](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Mencetuskan pemeriksaan kualiti buah dari sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Data yang digunakan untuk pengesan kualiti buah](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Menggunakan peranti pembangun untuk mensimulasikan pelbagai peranti IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Berpindah ke pengeluaran](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Ini adalah pelajaran terakhir dalam projek ini, jadi selepas menyelesaikan pelajaran ini dan tugasan, jangan lupa untuk membersihkan perkhidmatan awan anda. Anda akan memerlukan perkhidmatan tersebut untuk menyelesaikan tugasan, jadi pastikan untuk menyelesaikannya terlebih dahulu.
>
> Rujuk [panduan membersihkan projek anda](../../../clean-up.md) jika perlu untuk arahan tentang cara melakukannya.

## Merancang aplikasi IoT yang kompleks

Aplikasi IoT terdiri daripada banyak komponen. Ini termasuk pelbagai perkara dan perkhidmatan internet.

Aplikasi IoT boleh digambarkan sebagai *peranti* (things) yang menghantar data yang menghasilkan *wawasan* (insights). Wawasan ini menghasilkan *tindakan* (actions) untuk memperbaiki perniagaan atau proses. Sebagai contoh, enjin (peranti) menghantar data suhu. Data ini digunakan untuk menilai sama ada enjin berfungsi seperti yang diharapkan (wawasan). Wawasan ini digunakan untuk memprioritaskan jadual penyelenggaraan enjin secara proaktif (tindakan).

* Peranti yang berbeza mengumpulkan data yang berbeza.
* Perkhidmatan IoT memberikan wawasan terhadap data tersebut, kadang-kadang menambahkannya dengan data dari sumber tambahan.
* Wawasan ini mendorong tindakan, termasuk mengawal aktuator dalam peranti, atau memvisualisasikan data.

### Rujukan seni bina IoT

![Seni bina rujukan IoT](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.ms.png)

Rajah di atas menunjukkan seni bina rujukan IoT.

> 🎓 *Seni bina rujukan* adalah contoh seni bina yang boleh anda gunakan sebagai rujukan semasa mereka bentuk sistem baru. Dalam kes ini, jika anda membina sistem IoT baru, anda boleh mengikuti seni bina rujukan ini, menggantikan peranti dan perkhidmatan anda sendiri di tempat yang sesuai.

* **Peranti** adalah peranti yang mengumpulkan data dari sensor, mungkin berinteraksi dengan perkhidmatan tepi untuk mentafsirkan data tersebut, seperti pengklasifikasi imej untuk mentafsirkan data imej. Data dari peranti dihantar ke perkhidmatan IoT.
* **Wawasan** datang dari aplikasi tanpa pelayan, atau dari analisis yang dijalankan pada data yang disimpan.
* **Tindakan** boleh berupa arahan yang dihantar ke peranti, atau visualisasi data yang membolehkan manusia membuat keputusan.

![Seni bina rujukan IoT](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.ms.png)

Rajah di atas menunjukkan beberapa komponen dan perkhidmatan yang telah dibincangkan dalam pelajaran ini dan bagaimana ia saling berkaitan dalam seni bina rujukan IoT.

* **Peranti** - anda telah menulis kod peranti untuk menangkap data dari sensor, dan menganalisis imej menggunakan Custom Vision yang dijalankan di awan dan pada peranti tepi. Data ini dihantar ke IoT Hub.
* **Wawasan** - anda telah menggunakan Azure Functions untuk bertindak balas terhadap mesej yang dihantar ke IoT Hub, dan menyimpan data untuk analisis kemudian dalam Azure Storage.
* **Tindakan** - anda telah mengawal aktuator berdasarkan keputusan yang dibuat di awan dan arahan yang dihantar ke peranti, dan anda telah memvisualisasikan data menggunakan Azure Maps.

✅ Fikirkan tentang peranti IoT lain yang pernah anda gunakan, seperti peralatan rumah pintar. Apakah peranti, wawasan, dan tindakan yang terlibat dalam peranti tersebut dan perisiannya?

Corak ini boleh diperluaskan sebesar atau sekecil yang anda perlukan, dengan menambah lebih banyak peranti dan perkhidmatan.

### Data dan keselamatan

Semasa anda menentukan seni bina sistem anda, anda perlu sentiasa mempertimbangkan data dan keselamatan.

* Apakah data yang dihantar dan diterima oleh peranti anda?
* Bagaimana data tersebut harus diamankan dan dilindungi?
* Bagaimana akses ke peranti dan perkhidmatan awan harus dikawal?

✅ Fikirkan tentang keselamatan data peranti IoT yang anda miliki. Berapa banyak data tersebut yang bersifat peribadi dan harus dirahsiakan, baik semasa transit mahupun ketika disimpan? Apakah data yang tidak boleh disimpan?

## Mereka bentuk sistem kawalan kualiti buah

Sekarang mari kita ambil idea tentang peranti, wawasan, dan tindakan ini dan menerapkannya pada pengesan kualiti buah untuk mereka bentuk aplikasi hujung ke hujung yang lebih besar.

Bayangkan anda diberi tugas untuk membina pengesan kualiti buah yang akan digunakan di kilang pemprosesan. Buah bergerak di atas sistem tali sawat di mana pekerja kini menghabiskan masa memeriksa buah secara manual dan mengeluarkan buah yang belum masak. Untuk mengurangkan kos, pemilik kilang mahukan sistem automatik.

✅ Salah satu trend dengan kebangkitan IoT (dan teknologi secara umum) adalah pekerjaan manual digantikan oleh mesin. Lakukan sedikit penyelidikan: Berapa banyak pekerjaan yang dianggarkan akan hilang akibat IoT? Berapa banyak pekerjaan baru yang akan dicipta untuk membina peranti IoT?

Anda perlu membina sistem di mana buah dikesan semasa tiba di tali sawat, kemudian difoto dan diperiksa menggunakan model AI yang dijalankan di tepi. Hasilnya kemudian dihantar ke awan untuk disimpan, dan jika buah belum masak, pemberitahuan diberikan supaya buah yang belum masak dapat dikeluarkan.

|   |   |
| - | - |
| **Peranti** | Pengesan untuk buah yang tiba di tali sawat<br>Kamera untuk memfoto dan mengklasifikasikan buah<br>Peranti tepi yang menjalankan pengklasifikasi<br>Peranti untuk memberi pemberitahuan tentang buah yang belum masak |
| **Wawasan** | Memutuskan untuk memeriksa kematangan buah<br>Menyimpan hasil klasifikasi kematangan<br>Menentukan sama ada perlu memberi amaran tentang buah yang belum masak |
| **Tindakan** | Menghantar arahan ke peranti untuk memfoto buah dan memeriksanya dengan pengklasifikasi imej<br>Menghantar arahan ke peranti untuk memberi amaran bahawa buah belum masak |

### Membuat prototaip aplikasi anda

![Seni bina rujukan IoT untuk pemeriksaan kualiti buah](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.ms.png)

Rajah di atas menunjukkan seni bina rujukan untuk aplikasi prototaip ini.

* Peranti IoT dengan sensor jarak mengesan kedatangan buah. Ini menghantar mesej ke awan untuk memberitahu bahawa buah telah dikesan.
* Aplikasi tanpa pelayan di awan menghantar arahan ke peranti lain untuk mengambil foto dan mengklasifikasikan imej.
* Peranti IoT dengan kamera mengambil gambar dan menghantarnya ke pengklasifikasi imej yang dijalankan di tepi. Hasilnya kemudian dihantar ke awan.
* Aplikasi tanpa pelayan di awan menyimpan maklumat ini untuk dianalisis kemudian untuk melihat peratusan buah yang belum masak. Jika buah belum masak, ia menghantar arahan ke peranti IoT lain untuk memberi amaran kepada pekerja kilang tentang buah yang belum masak melalui LED.

> 💁 Seluruh aplikasi IoT ini boleh dilaksanakan sebagai satu peranti, dengan semua logik untuk memulakan klasifikasi imej dan mengawal LED dibina di dalamnya. Ia boleh menggunakan IoT Hub hanya untuk mengesan jumlah buah yang belum masak yang dikesan dan mengkonfigurasi peranti. Dalam pelajaran ini, ia diperluaskan untuk menunjukkan konsep untuk aplikasi IoT berskala besar.

Untuk prototaip, anda akan melaksanakan semua ini pada satu peranti. Jika anda menggunakan mikrokontroler, maka anda akan menggunakan peranti tepi yang berasingan untuk menjalankan pengklasifikasi imej. Anda telah mempelajari kebanyakan perkara yang anda perlukan untuk membina ini.

## Mencetuskan pemeriksaan kualiti buah dari sensor

Peranti IoT memerlukan sejenis pencetus untuk menunjukkan bila buah sedia untuk diklasifikasikan. Salah satu pencetus untuk ini adalah dengan mengukur bila buah berada di lokasi yang betul pada tali sawat dengan mengukur jarak ke sensor.

![Sensor jarak menghantar pancaran laser ke objek seperti pisang dan mengukur masa pantulan kembali](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.ms.png)

Sensor jarak boleh digunakan untuk mengukur jarak dari sensor ke objek. Biasanya, ia memancarkan pancaran radiasi elektromagnet seperti pancaran laser atau cahaya infra-merah, kemudian mengesan radiasi yang memantul dari objek. Masa antara pancaran laser dihantar dan isyarat yang memantul kembali boleh digunakan untuk mengira jarak ke sensor.

> 💁 Anda mungkin pernah menggunakan sensor jarak tanpa menyedarinya. Kebanyakan telefon pintar akan mematikan skrin apabila anda meletakkannya di telinga untuk mengelakkan anda secara tidak sengaja menamatkan panggilan dengan telinga anda, dan ini berfungsi menggunakan sensor jarak, yang mengesan objek dekat dengan skrin semasa panggilan dan melumpuhkan keupayaan sentuhan sehingga telefon berada pada jarak tertentu.

### Tugasan - mencetuskan pengesanan kualiti buah dari sensor jarak

Ikuti panduan yang relevan untuk menggunakan sensor jarak untuk mengesan objek menggunakan peranti IoT anda:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Komputer papan tunggal - Raspberry Pi](pi-proximity.md)
* [Komputer papan tunggal - Peranti maya](virtual-device-proximity.md)

## Data yang digunakan untuk pengesan kualiti buah

Prototaip pengesan buah mempunyai pelbagai komponen yang saling berkomunikasi.

![Komponen yang saling berkomunikasi](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.ms.png)

* Sensor jarak mengukur jarak ke sebiji buah dan menghantarnya ke IoT Hub
* Arahan untuk mengawal kamera datang dari IoT Hub ke peranti kamera
* Hasil klasifikasi imej dihantar ke IoT Hub
* Arahan untuk mengawal LED untuk memberi amaran apabila buah belum masak dihantar dari IoT Hub ke peranti dengan LED

Adalah baik untuk menentukan struktur mesej ini lebih awal, sebelum anda membina aplikasi.

> 💁 Hampir setiap pembangun berpengalaman pada suatu ketika dalam kerjaya mereka pernah menghabiskan berjam-jam, berhari-hari atau bahkan berminggu-minggu mengejar bug yang disebabkan oleh perbezaan dalam data yang dihantar berbanding apa yang diharapkan.

Sebagai contoh - jika anda menghantar maklumat suhu, bagaimana anda akan menentukan JSON? Anda boleh mempunyai medan yang dipanggil `temperature`, atau anda boleh menggunakan singkatan biasa `temp`.

```json
{
    "temperature": 20.7
}
```

berbanding:

```json
{
    "temp": 20.7
}
```

Anda juga perlu mempertimbangkan unit - adakah suhu dalam °C atau °F? Jika anda mengukur suhu menggunakan peranti pengguna dan mereka menukar unit paparan, anda perlu memastikan unit yang dihantar ke awan tetap konsisten.

✅ Lakukan penyelidikan: Bagaimana masalah unit menyebabkan $125 juta Mars Climate Orbiter terhempas?

Fikirkan tentang data yang dihantar untuk pengesan kualiti buah. Bagaimana anda akan menentukan setiap mesej? Di mana anda akan menganalisis data dan membuat keputusan tentang data apa yang akan dihantar?

Sebagai contoh - mencetuskan klasifikasi imej menggunakan sensor jarak. Peranti IoT mengukur jarak, tetapi di mana keputusan dibuat? Adakah peranti memutuskan bahawa buah sudah cukup dekat dan menghantar mesej untuk memberitahu IoT Hub untuk mencetuskan klasifikasi? Atau adakah ia menghantar ukuran jarak dan membiarkan IoT Hub membuat keputusan?

Jawapan kepada soalan seperti ini adalah - ia bergantung. Setiap kes penggunaan adalah berbeza, itulah sebabnya sebagai pembangun IoT anda perlu memahami sistem yang anda bina, bagaimana ia digunakan, dan data yang dikesan.

* Jika keputusan dibuat oleh IoT Hub, anda perlu menghantar pelbagai ukuran jarak.
* Jika anda menghantar terlalu banyak mesej, ia meningkatkan kos IoT Hub, dan jumlah lebar jalur yang diperlukan oleh peranti IoT anda (terutamanya di kilang dengan berjuta-juta peranti). Ia juga boleh memperlahankan peranti anda.
* Jika anda membuat keputusan pada peranti, anda perlu menyediakan cara untuk mengkonfigurasi peranti untuk menyesuaikan mesin.

## Menggunakan peranti pembangun untuk mensimulasikan pelbagai peranti IoT

Untuk membina prototaip anda, anda memerlukan kit pembangunan IoT anda untuk bertindak seperti pelbagai peranti, menghantar telemetri dan bertindak balas terhadap arahan.

### Mensimulasikan pelbagai peranti IoT pada Raspberry Pi atau perkakasan IoT maya

Apabila menggunakan komputer papan tunggal seperti Raspberry Pi, anda boleh menjalankan pelbagai aplikasi sekaligus. Ini bermakna anda boleh mensimulasikan pelbagai peranti IoT dengan mencipta pelbagai aplikasi, satu untuk setiap 'peranti IoT'. Sebagai contoh, anda boleh melaksanakan setiap peranti sebagai fail Python yang berasingan dan menjalankannya dalam sesi terminal yang berbeza.
💁 Sila ambil perhatian bahawa sesetengah perkakasan tidak akan berfungsi apabila diakses oleh beberapa aplikasi yang berjalan serentak.
### Mensimulasikan pelbagai peranti pada mikrokontroler

Mikrokontroler lebih rumit untuk mensimulasikan pelbagai peranti. Tidak seperti komputer papan tunggal, anda tidak boleh menjalankan pelbagai aplikasi secara serentak. Anda perlu memasukkan semua logik untuk semua peranti IoT yang berasingan dalam satu aplikasi.

Beberapa cadangan untuk memudahkan proses ini adalah:

* Cipta satu atau lebih kelas untuk setiap peranti IoT - contohnya kelas yang dipanggil `DistanceSensor`, `ClassifierCamera`, `LEDController`. Setiap satu boleh mempunyai kaedah `setup` dan `loop` sendiri yang dipanggil oleh fungsi `setup` dan `loop` utama.
* Uruskan arahan di satu tempat, dan arahkan arahan tersebut kepada kelas peranti yang berkaitan seperti yang diperlukan.
* Dalam fungsi `loop` utama, anda perlu mempertimbangkan masa untuk setiap peranti yang berbeza. Sebagai contoh, jika anda mempunyai satu kelas peranti yang perlu diproses setiap 10 saat, dan satu lagi yang perlu diproses setiap 1 saat, maka dalam fungsi `loop` utama gunakan kelewatan 1 saat. Setiap panggilan `loop` mencetuskan kod yang relevan untuk peranti yang perlu diproses setiap saat, dan gunakan kaunter untuk mengira setiap gelung, memproses peranti lain apabila kaunter mencapai 10 (dan menetapkan semula kaunter selepas itu).

## Beralih ke pengeluaran

Prototip akan menjadi asas kepada sistem pengeluaran akhir. Beberapa perbezaan apabila anda beralih ke pengeluaran adalah:

* Komponen yang tahan lasak - menggunakan perkakasan yang direka untuk menahan bunyi, haba, getaran, dan tekanan di kilang.
* Menggunakan komunikasi dalaman - beberapa komponen akan berkomunikasi secara langsung tanpa perlu melalui awan, hanya menghantar data ke awan untuk disimpan. Bagaimana ini dilakukan bergantung pada susunan kilang, sama ada melalui komunikasi langsung, atau dengan menjalankan sebahagian daripada perkhidmatan IoT di tepi menggunakan peranti gateway.
* Pilihan konfigurasi - setiap kilang dan kes penggunaan adalah berbeza, jadi perkakasan perlu boleh dikonfigurasi. Sebagai contoh, sensor jarak mungkin perlu mengesan buah yang berbeza pada jarak yang berbeza. Daripada menetapkan jarak secara tetap untuk mencetuskan klasifikasi, anda mungkin mahu ini boleh dikonfigurasi melalui awan, contohnya menggunakan device twin.
* Penyingkiran buah secara automatik - bukannya menggunakan LED untuk memberi amaran bahawa buah tidak masak, peranti automatik akan mengeluarkannya.

✅ Lakukan sedikit penyelidikan: Dalam cara lain apakah peranti pengeluaran berbeza daripada kit pembangun?

---

## 🚀 Cabaran

Dalam pelajaran ini, anda telah mempelajari beberapa konsep yang perlu diketahui tentang cara untuk merancang sistem IoT. Fikirkan kembali kepada projek-projek sebelumnya. Bagaimana mereka sesuai dengan seni bina rujukan yang ditunjukkan di atas?

Pilih salah satu projek yang telah dilakukan dan fikirkan reka bentuk penyelesaian yang lebih rumit dengan menggabungkan pelbagai keupayaan di luar apa yang telah diliputi dalam projek. Lukiskan seni bina dan fikirkan semua peranti dan perkhidmatan yang anda perlukan.

Sebagai contoh - peranti penjejakan kenderaan yang menggabungkan GPS dengan sensor untuk memantau perkara seperti suhu dalam trak berpendingin, masa enjin dihidupkan dan dimatikan, serta identiti pemandu. Apakah peranti yang terlibat, perkhidmatan yang terlibat, data yang dihantar, dan pertimbangan keselamatan serta privasi?

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Ulasan & Kajian Kendiri

* Baca lebih lanjut tentang seni bina IoT dalam [dokumentasi seni bina rujukan Azure IoT di Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Baca lebih lanjut tentang device twins dalam [dokumentasi memahami dan menggunakan device twins di IoT Hub di Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Baca tentang OPC-UA, protokol komunikasi mesin ke mesin yang digunakan dalam automasi industri di [halaman OPC-UA di Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Tugasan

[Bina pengesan kualiti buah](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.