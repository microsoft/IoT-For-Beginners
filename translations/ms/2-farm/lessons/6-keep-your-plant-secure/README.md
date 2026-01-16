<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-27T22:08:38+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "ms"
}
-->
# Pastikan Tumbuhan Anda Selamat

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

## Kuiz Pra-Pelajaran

[Kuiz Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Pengenalan

Dalam beberapa pelajaran terakhir, anda telah mencipta peranti IoT untuk memantau kelembapan tanah dan menyambungkannya ke awan. Tetapi bagaimana jika penggodam yang bekerja untuk petani pesaing berjaya mengawal peranti IoT anda? Bagaimana jika mereka menghantar bacaan kelembapan tanah yang tinggi sehingga tumbuhan anda tidak pernah disiram, atau menghidupkan sistem penyiraman anda sepanjang masa sehingga tumbuhan anda mati akibat terlalu banyak air dan anda mengalami kerugian besar dalam kos air?

Dalam pelajaran ini, anda akan belajar tentang cara melindungi peranti IoT. Sebagai pelajaran terakhir untuk projek ini, anda juga akan belajar cara membersihkan sumber awan anda, mengurangkan sebarang kos yang berpotensi.

Dalam pelajaran ini, kita akan membincangkan:

* [Mengapa anda perlu melindungi peranti IoT?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kriptografi](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Lindungi peranti IoT anda](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Hasilkan dan gunakan sijil X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Ini adalah pelajaran terakhir dalam projek ini, jadi selepas menyelesaikan pelajaran dan tugasan, jangan lupa untuk membersihkan perkhidmatan awan anda. Anda akan memerlukan perkhidmatan tersebut untuk menyelesaikan tugasan, jadi pastikan anda menyelesaikannya terlebih dahulu.
>
> Rujuk [panduan membersihkan projek anda](../../../clean-up.md) jika perlu untuk arahan tentang cara melakukannya.

## Mengapa anda perlu melindungi peranti IoT?

Keselamatan IoT melibatkan memastikan hanya peranti yang dijangka boleh menyambung ke perkhidmatan awan IoT anda dan menghantar telemetri, dan hanya perkhidmatan awan anda boleh menghantar arahan kepada peranti anda. Data IoT juga boleh bersifat peribadi, termasuk data perubatan atau intim, jadi keseluruhan aplikasi anda perlu mempertimbangkan keselamatan untuk menghentikan kebocoran data ini.

Jika aplikasi IoT anda tidak selamat, terdapat beberapa risiko:

* Peranti palsu boleh menghantar data yang salah, menyebabkan aplikasi anda bertindak balas dengan tidak betul. Sebagai contoh, mereka boleh menghantar bacaan kelembapan tanah yang tinggi secara berterusan, menyebabkan sistem pengairan anda tidak pernah dihidupkan dan tumbuhan anda mati akibat kekurangan air.
* Pengguna yang tidak sah boleh membaca data daripada peranti IoT termasuk data peribadi atau data penting perniagaan.
* Penggodam boleh menghantar arahan untuk mengawal peranti dengan cara yang boleh menyebabkan kerosakan pada peranti atau perkakasan yang disambungkan.
* Dengan menyambung ke peranti IoT, penggodam boleh menggunakan ini untuk mengakses rangkaian tambahan untuk mendapatkan akses kepada sistem peribadi.
* Pengguna berniat jahat boleh mengakses data peribadi dan menggunakannya untuk pemerasan.

Ini adalah senario dunia sebenar, dan berlaku sepanjang masa. Beberapa contoh telah diberikan dalam pelajaran sebelumnya, tetapi berikut adalah beberapa lagi:

* Pada tahun 2018, penggodam menggunakan titik akses WiFi terbuka pada termostat akuarium untuk mendapatkan akses ke rangkaian kasino dan mencuri data. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* Pada tahun 2016, Mirai Botnet melancarkan serangan penafian perkhidmatan terhadap Dyn, penyedia perkhidmatan Internet, menyebabkan sebahagian besar Internet terganggu. Botnet ini menggunakan perisian hasad untuk menyambung ke peranti IoT seperti DVR dan kamera yang menggunakan nama pengguna dan kata laluan lalai, dan dari situ melancarkan serangan. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys mempunyai pangkalan data pengguna mainan CloudPets mereka yang disambungkan secara terbuka di Internet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava menandakan pelari yang anda lalui dan menunjukkan laluan mereka, membolehkan orang asing melihat di mana anda tinggal. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Lakukan penyelidikan: Cari lebih banyak contoh penggodaman IoT dan kebocoran data IoT, terutamanya dengan barangan peribadi seperti berus gigi atau penimbang yang disambungkan ke Internet. Fikirkan tentang kesan penggodaman ini terhadap mangsa atau pelanggan.

> 💁 Keselamatan adalah topik yang sangat besar, dan pelajaran ini hanya akan menyentuh beberapa asas tentang menyambungkan peranti anda ke awan. Topik lain yang tidak akan dibincangkan termasuk pemantauan perubahan data semasa penghantaran, penggodaman peranti secara langsung, atau perubahan kepada konfigurasi peranti. Penggodaman IoT adalah ancaman yang besar, alat seperti [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) telah dibangunkan. Alat ini serupa dengan alat antivirus dan keselamatan yang mungkin anda miliki di komputer anda, tetapi direka untuk peranti IoT kecil dan berkuasa rendah.

## Kriptografi

Apabila peranti menyambung ke perkhidmatan IoT, ia menggunakan ID untuk mengenal pasti dirinya. Masalahnya ialah ID ini boleh digandakan - penggodam boleh menyediakan peranti berniat jahat yang menggunakan ID yang sama seperti peranti sebenar tetapi menghantar data palsu.

![Kedua-dua peranti sah dan berniat jahat boleh menggunakan ID yang sama untuk menghantar telemetri](../../../../../translated_images/ms/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.png)

Cara untuk mengatasi masalah ini adalah dengan menukar data yang dihantar ke format yang dikodkan, menggunakan nilai tertentu yang hanya diketahui oleh peranti dan awan. Proses ini dipanggil *penyulitan*, dan nilai yang digunakan untuk menyulitkan data dipanggil *kunci penyulitan*.

![Jika penyulitan digunakan, hanya mesej yang disulitkan akan diterima, yang lain akan ditolak](../../../../../translated_images/ms/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.png)

Perkhidmatan awan kemudian boleh menukar data kembali ke format yang boleh dibaca, menggunakan proses yang dipanggil *penyahulitan*, sama ada menggunakan kunci penyulitan yang sama, atau *kunci penyahulitan*. Jika mesej yang disulitkan tidak dapat dinyahulitkan oleh kunci, peranti telah digodam dan mesej ditolak.

Teknik untuk melakukan penyulitan dan penyahulitan dipanggil *kriptografi*.

### Kriptografi Awal

Jenis kriptografi yang paling awal adalah cipher penggantian, yang wujud sejak 3,500 tahun yang lalu. Cipher penggantian melibatkan penggantian satu huruf dengan huruf lain. Sebagai contoh, [Caesar cipher](https://wikipedia.org/wiki/Caesar_cipher) melibatkan peralihan abjad dengan jumlah yang ditentukan, dengan hanya pengirim mesej yang disulitkan dan penerima yang dimaksudkan mengetahui berapa banyak huruf untuk beralih.

[Cipher Vigenère](https://wikipedia.org/wiki/Vigenère_cipher) membawa ini lebih jauh dengan menggunakan kata-kata untuk menyulitkan teks, sehingga setiap huruf dalam teks asal dialihkan dengan jumlah yang berbeza, bukannya selalu beralih dengan jumlah huruf yang sama.

Kriptografi digunakan untuk pelbagai tujuan, seperti melindungi resipi glaz tembikar di Mesopotamia kuno, menulis nota cinta rahsia di India, atau menyimpan mantra ajaib Mesir kuno secara rahsia.

### Kriptografi Moden

Kriptografi moden jauh lebih maju, menjadikannya lebih sukar untuk dipecahkan daripada kaedah awal. Kriptografi moden menggunakan matematik yang rumit untuk menyulitkan data dengan terlalu banyak kemungkinan kunci untuk membuat serangan brute force menjadi mustahil.

Kriptografi digunakan dalam pelbagai cara untuk komunikasi yang selamat. Jika anda membaca halaman ini di GitHub, anda mungkin perasan alamat laman web bermula dengan *HTTPS*, yang bermaksud komunikasi antara pelayar anda dan pelayan web GitHub disulitkan. Jika seseorang dapat membaca trafik internet yang mengalir antara pelayar anda dan GitHub, mereka tidak akan dapat membaca data kerana ia disulitkan. Komputer anda mungkin juga menyulitkan semua data pada cakera keras anda sehingga jika seseorang mencurinya, mereka tidak akan dapat membaca sebarang data anda tanpa kata laluan anda.

> 🎓 HTTPS bermaksud HyperText Transfer Protocol **Secure**

Malangnya, tidak semua perkara selamat. Sesetengah peranti tidak mempunyai keselamatan, yang lain dilindungi menggunakan kunci yang mudah dipecahkan, atau kadang-kadang semua peranti jenis yang sama menggunakan kunci yang sama. Terdapat laporan tentang peranti IoT yang sangat peribadi yang semuanya mempunyai kata laluan yang sama untuk menyambung ke mereka melalui WiFi atau Bluetooth. Jika anda boleh menyambung ke peranti anda sendiri, anda boleh menyambung ke peranti orang lain. Setelah disambungkan, anda boleh mengakses data yang sangat peribadi, atau mengawal peranti mereka.

> 💁 Walaupun kerumitan kriptografi moden dan dakwaan bahawa memecahkan penyulitan boleh mengambil masa berbilion tahun, kemunculan pengkomputeran kuantum telah membawa kepada kemungkinan memecahkan semua penyulitan yang diketahui dalam masa yang sangat singkat!

### Kunci Simetri dan Asimetri

Penyulitan datang dalam dua jenis - simetri dan asimetri.

**Simetri** menggunakan kunci yang sama untuk menyulitkan dan menyahulitkan data. Pengirim dan penerima perlu mengetahui kunci yang sama. Ini adalah jenis yang paling kurang selamat, kerana kunci perlu dikongsi dengan cara tertentu. Untuk pengirim menghantar mesej yang disulitkan kepada penerima, pengirim mungkin perlu menghantar kunci kepada penerima terlebih dahulu.

![Penyulitan kunci simetri menggunakan kunci yang sama untuk menyulitkan dan menyahulitkan mesej](../../../../../translated_images/ms/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Jika kunci dicuri semasa penghantaran, atau pengirim atau penerima digodam dan kunci ditemui, penyulitan boleh dipecahkan.

![Penyulitan kunci simetri hanya selamat jika penggodam tidak mendapat kunci - jika ya, mereka boleh memintas dan menyahulitkan mesej](../../../../../translated_images/ms/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asimetri** menggunakan 2 kunci - kunci penyulitan dan kunci penyahulitan, yang dirujuk sebagai pasangan kunci awam/peribadi. Kunci awam digunakan untuk menyulitkan mesej, tetapi tidak boleh digunakan untuk menyahulitkannya, kunci peribadi digunakan untuk menyahulitkan mesej tetapi tidak boleh digunakan untuk menyulitkannya.

![Penyulitan asimetri menggunakan kunci yang berbeza untuk menyulitkan dan menyahulitkan. Kunci penyulitan dihantar kepada pengirim mesej supaya mereka boleh menyulitkan mesej sebelum menghantarnya kepada penerima yang memiliki kunci](../../../../../translated_images/ms/send-message-asymmetric.7abe327c62615b8c.webp)

Penerima berkongsi kunci awam mereka, dan pengirim menggunakan ini untuk menyulitkan mesej. Setelah mesej dihantar, penerima menyahulitkannya dengan kunci peribadi mereka. Penyulitan asimetri lebih selamat kerana kunci peribadi disimpan secara peribadi oleh penerima dan tidak pernah dikongsi. Sesiapa sahaja boleh memiliki kunci awam kerana ia hanya boleh digunakan untuk menyulitkan mesej.

Penyulitan simetri lebih pantas daripada penyulitan asimetri, asimetri lebih selamat. Sesetengah sistem akan menggunakan kedua-duanya - menggunakan penyulitan asimetri untuk menyulitkan dan berkongsi kunci simetri, kemudian menggunakan kunci simetri untuk menyulitkan semua data. Ini menjadikannya lebih selamat untuk berkongsi kunci simetri antara pengirim dan penerima, dan lebih pantas semasa menyulitkan dan menyahulitkan data.

## Lindungi peranti IoT anda

Peranti IoT boleh dilindungi menggunakan penyulitan simetri atau asimetri. Simetri lebih mudah, tetapi kurang selamat.

### Kunci Simetri

Apabila anda menyediakan peranti IoT anda untuk berinteraksi dengan IoT Hub, anda menggunakan rentetan sambungan. Contoh rentetan sambungan adalah:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Rentetan sambungan ini terdiri daripada tiga bahagian yang dipisahkan oleh titik koma, dengan setiap bahagian adalah kunci dan nilai:

| Kunci | Nilai | Penerangan |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL IoT Hub |
| DeviceId | `soil-moisture-sensor` | ID unik peranti |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Kunci simetri yang diketahui oleh peranti dan IoT Hub |

Bahagian terakhir rentetan sambungan ini, `SharedAccessKey`, adalah kunci simetri yang diketahui oleh kedua-dua peranti dan IoT Hub. Kunci ini tidak pernah dihantar dari peranti ke awan, atau dari awan ke peranti. Sebaliknya, ia digunakan untuk menyulitkan data yang dihantar atau diterima.

✅ Lakukan eksperimen. Apa yang anda fikir akan berlaku jika anda menukar bahagian `SharedAccessKey` dalam rentetan sambungan semasa menyambungkan peranti IoT anda? Cuba dan lihat.

Apabila peranti mula-mula cuba menyambung, ia menghantar token tandatangan akses bersama (SAS) yang terdiri daripada URL IoT Hub, cap masa apabila tandatangan akses akan tamat (biasanya 1 hari dari masa semasa), dan tandatangan. Tandatangan ini terdiri daripada URL dan masa tamat yang disulitkan dengan kunci akses bersama dari rentetan sambungan.

IoT Hub menyahulitkan tandatangan ini dengan kunci akses bersama, dan jika nilai yang dinyahulitkan sepadan dengan URL dan masa tamat, peranti dibenarkan untuk menyambung. Ia juga mengesahkan bahawa masa semasa adalah sebelum masa tamat, untuk menghentikan peranti berniat jahat daripada menangkap token SAS peranti sebenar dan menggunakannya.

Ini adalah cara yang elegan untuk mengesahkan bahawa pengirim adalah peranti yang betul. Dengan menghantar beberapa data yang diketahui dalam bentuk yang tidak disulitkan dan disulitkan, pelayan boleh mengesahkan peranti dengan memastikan apabila ia menyahulitkan data yang disulitkan, hasilnya sepadan dengan versi yang tidak disulitkan yang dihantar. Jika ia sepadan, maka pengirim dan penerima mempunyai kunci penyulitan simetri yang sama.
💁 Oleh kerana masa tamat tempoh, peranti IoT anda perlu mengetahui masa yang tepat, biasanya dibaca dari pelayan [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Jika masa tidak tepat, sambungan akan gagal.
Selepas sambungan dibuat, semua data yang dihantar ke IoT Hub dari peranti, atau ke peranti dari IoT Hub akan dienkripsi menggunakan kunci akses bersama.

✅ Apa yang anda fikir akan berlaku jika beberapa peranti berkongsi string sambungan yang sama?

> 💁 Ia adalah amalan keselamatan yang buruk untuk menyimpan kunci ini dalam kod. Jika penggodam mendapat kod sumber anda, mereka boleh mendapatkan kunci anda. Ia juga lebih sukar apabila melepaskan kod kerana anda perlu menyusun semula dengan kunci yang dikemas kini untuk setiap peranti. Adalah lebih baik untuk memuatkan kunci ini dari modul keselamatan perkakasan - cip pada peranti IoT yang menyimpan nilai yang dienkripsi yang boleh dibaca oleh kod anda.
>
> Semasa belajar IoT, sering kali lebih mudah untuk meletakkan kunci dalam kod, seperti yang anda lakukan dalam pelajaran sebelumnya, tetapi anda mesti memastikan kunci ini tidak dimasukkan ke dalam kawalan kod sumber awam.

Peranti mempunyai 2 kunci, dan 2 string sambungan yang sepadan. Ini membolehkan anda memutar kunci - iaitu beralih dari satu kunci ke kunci lain jika kunci pertama dikompromi, dan menjana semula kunci pertama.

### Sijil X.509

Apabila anda menggunakan enkripsi asimetrik dengan pasangan kunci awam/peribadi, anda perlu memberikan kunci awam anda kepada sesiapa yang ingin menghantar data kepada anda. Masalahnya ialah, bagaimana penerima kunci anda boleh yakin bahawa ia benar-benar kunci awam anda, bukan orang lain yang berpura-pura menjadi anda? Sebaliknya memberikan kunci, anda boleh memberikan kunci awam anda di dalam sijil yang telah disahkan oleh pihak ketiga yang dipercayai, yang dipanggil sijil X.509.

Sijil X.509 adalah dokumen digital yang mengandungi bahagian kunci awam dari pasangan kunci awam/peribadi. Ia biasanya dikeluarkan oleh salah satu daripada beberapa organisasi yang dipercayai yang dipanggil [Pihak Berkuasa Pensijilan](https://wikipedia.org/wiki/Certificate_authority) (CAs), dan ditandatangani secara digital oleh CA untuk menunjukkan bahawa kunci itu sah dan berasal dari anda. Anda mempercayai sijil dan bahawa kunci awam itu berasal dari siapa sijil itu mengatakan ia berasal, kerana anda mempercayai CA, sama seperti anda mempercayai pasport atau lesen memandu kerana anda mempercayai negara yang mengeluarkannya. Sijil memerlukan kos, jadi anda juga boleh 'menandatangani sendiri', iaitu membuat sijil sendiri yang ditandatangani oleh anda, untuk tujuan ujian.

> 💁 Anda tidak seharusnya menggunakan sijil yang ditandatangani sendiri untuk pelepasan produksi.

Sijil-sijil ini mempunyai beberapa medan di dalamnya, termasuk siapa kunci awam itu berasal, butiran CA yang mengeluarkannya, berapa lama ia sah, dan kunci awam itu sendiri. Sebelum menggunakan sijil, adalah amalan yang baik untuk mengesahkannya dengan memeriksa bahawa ia ditandatangani oleh CA asal.

✅ Anda boleh membaca senarai penuh medan dalam sijil di [Tutorial Memahami Sijil Kunci Awam X.509 Microsoft](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)

Apabila menggunakan sijil X.509, kedua-dua penghantar dan penerima akan mempunyai kunci awam dan peribadi mereka sendiri, serta kedua-duanya mempunyai sijil X.509 yang mengandungi kunci awam. Mereka kemudian bertukar sijil X.509 dengan cara tertentu, menggunakan kunci awam masing-masing untuk mengenkripsi data yang mereka hantar, dan kunci peribadi mereka sendiri untuk mendekripsi data yang mereka terima.

![Daripada berkongsi kunci awam, anda boleh berkongsi sijil. Pengguna sijil boleh mengesahkan bahawa ia berasal dari anda dengan memeriksa dengan pihak berkuasa sijil yang menandatanganinya.](../../../../../translated_images/ms/send-message-certificate.9cc576ac1e46b76e.webp)

Satu kelebihan besar menggunakan sijil X.509 ialah ia boleh dikongsi antara peranti. Anda boleh membuat satu sijil, memuat naiknya ke IoT Hub, dan menggunakannya untuk semua peranti anda. Setiap peranti hanya perlu mengetahui kunci peribadi untuk mendekripsi mesej yang diterima dari IoT Hub.

Sijil yang digunakan oleh peranti anda untuk mengenkripsi mesej yang dihantar ke IoT Hub diterbitkan oleh Microsoft. Ia adalah sijil yang sama yang digunakan oleh banyak perkhidmatan Azure, dan kadang-kadang dibina ke dalam SDK.

> 💁 Ingat, kunci awam hanyalah itu - awam. Kunci awam Azure hanya boleh digunakan untuk mengenkripsi data yang dihantar ke Azure, bukan untuk mendekripsinya, jadi ia boleh dikongsi di mana-mana, termasuk dalam kod sumber. Sebagai contoh, anda boleh melihatnya dalam [Kod Sumber SDK IoT Azure C](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Terdapat banyak istilah dengan sijil X.509. Anda boleh membaca definisi beberapa istilah yang mungkin anda temui dalam [Panduan awam kepada istilah sijil X.509](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)

## Menjana dan menggunakan sijil X.509

Langkah-langkah untuk menjana sijil X.509 adalah:

1. Buat pasangan kunci awam/peribadi. Salah satu algoritma yang paling banyak digunakan untuk menjana pasangan kunci awam/peribadi dipanggil [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Hantar kunci awam dengan data yang berkaitan untuk ditandatangani, sama ada oleh CA, atau dengan menandatangani sendiri.

Azure CLI mempunyai arahan untuk mencipta identiti peranti baharu dalam IoT Hub, dan secara automatik menjana pasangan kunci awam/peribadi serta mencipta sijil yang ditandatangani sendiri.

> 💁 Jika anda ingin melihat langkah-langkah secara terperinci, daripada menggunakan Azure CLI, anda boleh menemukannya dalam [Tutorial Menggunakan OpenSSL untuk mencipta sijil yang ditandatangani sendiri dalam dokumentasi Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)

### Tugasan - mencipta identiti peranti menggunakan sijil X.509

1. Jalankan arahan berikut untuk mendaftar identiti peranti baharu, secara automatik menjana kunci dan sijil:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Gantikan `<hub_name>` dengan nama yang anda gunakan untuk IoT Hub anda.

    Ini akan mencipta peranti dengan ID `soil-moisture-sensor-x509` untuk membezakan daripada identiti peranti yang anda cipta dalam pelajaran sebelumnya. Arahan ini juga akan mencipta 2 fail dalam direktori semasa:

    * `soil-moisture-sensor-x509-key.pem` - fail ini mengandungi kunci peribadi untuk peranti.
    * `soil-moisture-sensor-x509-cert.pem` - ini adalah fail sijil X.509 untuk peranti.

    Simpan fail-fail ini dengan selamat! Fail kunci peribadi tidak boleh dimasukkan ke dalam kawalan kod sumber awam.

### Tugasan - menggunakan sijil X.509 dalam kod peranti anda

Ikuti panduan yang relevan untuk menyambungkan peranti IoT anda ke awan menggunakan sijil X.509:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Komputer papan tunggal - Raspberry Pi/Peranti IoT Maya](single-board-computer-x509.md)

---

## 🚀 Cabaran

Terdapat pelbagai cara untuk mencipta, mengurus dan memadam perkhidmatan Azure seperti Resource Groups dan IoT Hubs. Salah satu cara adalah melalui [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - antara muka berasaskan web yang memberikan anda GUI untuk mengurus perkhidmatan Azure anda.

Pergi ke [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) dan selidiki portal tersebut. Lihat jika anda boleh mencipta IoT Hub menggunakan portal, kemudian memadamnya.

**Petunjuk** - apabila mencipta perkhidmatan melalui portal, anda tidak perlu mencipta Resource Group terlebih dahulu, satu boleh dicipta semasa anda mencipta perkhidmatan. Pastikan anda memadamnya apabila anda selesai!

Anda boleh menemui banyak dokumentasi, tutorial dan panduan tentang Azure Portal dalam [Dokumentasi portal Azure](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Ulasan & Kajian Kendiri

* Baca tentang sejarah kriptografi di [Halaman Sejarah Kriptografi di Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Baca tentang sijil X.509 di [Halaman X.509 di Wikipedia](https://wikipedia.org/wiki/X.509).

## Tugasan

[Bina peranti IoT baharu](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.