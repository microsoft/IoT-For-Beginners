<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T23:30:39+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "ms"
}
-->
# Konfigurasi mikrofon dan pembesar suara - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah pembesar suara pada Wio Terminal anda. Wio Terminal sudah mempunyai mikrofon terbina dalam, dan ini boleh digunakan untuk menangkap suara.

## Perkakasan

Wio Terminal sudah mempunyai mikrofon terbina dalam, dan ini boleh digunakan untuk menangkap audio bagi pengecaman suara.

![Mikrofon pada Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.ms.png)

Untuk menambah pembesar suara, anda boleh menggunakan [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Ini adalah papan luaran yang mengandungi 2 mikrofon MEMS, serta penyambung pembesar suara dan soket fon kepala.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.ms.png)

Anda perlu menambah sama ada fon kepala, pembesar suara dengan jack 3.5mm, atau pembesar suara dengan sambungan JST seperti [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Untuk menyambungkan ReSpeaker 2-Mics Pi Hat, anda memerlukan kabel jumper 40 pin-to-pin (juga dikenali sebagai male-to-male).

> 💁 Jika anda selesa dengan kerja menyolder, anda boleh menggunakan [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) untuk menyambungkan ReSpeaker.

Anda juga memerlukan kad SD untuk memuat turun dan memainkan audio. Wio Terminal hanya menyokong Kad SD sehingga 16GB, dan kad ini perlu diformat sebagai FAT32 atau exFAT.

### Tugas - sambungkan ReSpeaker Pi Hat

1. Dengan Wio Terminal dimatikan, sambungkan ReSpeaker 2-Mics Pi Hat ke Wio Terminal menggunakan kabel jumper dan soket GPIO di bahagian belakang Wio Terminal:

    Pin perlu disambungkan dengan cara ini:

    ![Diagram pin](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.ms.png)

1. Letakkan ReSpeaker dan Wio Terminal dengan soket GPIO menghadap ke atas, dan di sebelah kiri.

1. Mulakan dari soket di bahagian atas kiri soket GPIO pada ReSpeaker. Sambungkan kabel jumper pin-to-pin dari soket atas kiri ReSpeaker ke soket atas kiri Wio Terminal.

1. Ulangi proses ini sepanjang soket GPIO di sebelah kiri. Pastikan pin dimasukkan dengan kukuh.

    ![ReSpeaker dengan pin sebelah kiri disambungkan ke pin sebelah kiri Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.ms.png)

    ![ReSpeaker dengan pin sebelah kiri disambungkan ke pin sebelah kiri Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.ms.png)

    > 💁 Jika kabel jumper anda disambungkan dalam bentuk pita, pastikan semuanya bersama - ini memudahkan anda memastikan semua kabel disambungkan mengikut urutan.

1. Ulangi proses menggunakan soket GPIO sebelah kanan pada ReSpeaker dan Wio Terminal. Kabel ini perlu melalui kabel yang sudah disambungkan.

    ![ReSpeaker dengan pin sebelah kanan disambungkan ke pin sebelah kanan Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.ms.png)

    ![ReSpeaker dengan pin sebelah kanan disambungkan ke pin sebelah kanan Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.ms.png)

    > 💁 Jika kabel jumper anda disambungkan dalam bentuk pita, pisahkan menjadi dua pita. Letakkan satu di setiap sisi kabel yang sudah ada.

    > 💁 Anda boleh menggunakan pita pelekat untuk memegang pin dalam satu blok untuk membantu mengelakkan pin terkeluar semasa anda menyambungkannya.
    >
    > ![Pin dipasang dengan pita pelekat](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.ms.png)

1. Anda perlu menambah pembesar suara.

    * Jika anda menggunakan pembesar suara dengan kabel JST, sambungkan ke port JST pada ReSpeaker.

      ![Pembesar suara disambungkan ke ReSpeaker dengan kabel JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.ms.png)

    * Jika anda menggunakan pembesar suara dengan jack 3.5mm, atau fon kepala, masukkan ke dalam soket jack 3.5mm.

      ![Pembesar suara disambungkan ke ReSpeaker melalui soket jack 3.5mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.ms.png)

### Tugas - sediakan kad SD

1. Sambungkan Kad SD ke komputer anda, menggunakan pembaca luaran jika anda tidak mempunyai slot Kad SD.

1. Format Kad SD menggunakan alat yang sesuai pada komputer anda, pastikan menggunakan sistem fail FAT32 atau exFAT.

1. Masukkan Kad SD ke dalam slot Kad SD di sebelah kiri Wio Terminal, tepat di bawah butang kuasa. Pastikan kad dimasukkan sepenuhnya dan klik masuk - anda mungkin memerlukan alat nipis atau Kad SD lain untuk membantu menolaknya sepenuhnya.

    ![Memasukkan Kad SD ke dalam slot Kad SD di bawah suis kuasa](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.ms.png)

    > 💁 Untuk mengeluarkan Kad SD, anda perlu menolaknya sedikit dan ia akan keluar. Anda memerlukan alat nipis seperti pemutar skru kepala rata atau Kad SD lain untuk melakukannya.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.