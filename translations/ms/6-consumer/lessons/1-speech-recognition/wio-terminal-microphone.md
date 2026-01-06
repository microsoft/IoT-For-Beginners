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

![Mikrofon pada Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.ms.png)

Untuk menambah pembesar suara, anda boleh menggunakan [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Ini adalah papan luaran yang mengandungi 2 mikrofon MEMS, serta penyambung pembesar suara dan soket fon kepala.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.ms.png)

Anda perlu menambah sama ada fon kepala, pembesar suara dengan jack 3.5mm, atau pembesar suara dengan sambungan JST seperti [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Untuk menyambungkan ReSpeaker 2-Mics Pi Hat, anda memerlukan kabel jumper 40 pin-to-pin (juga dikenali sebagai male-to-male).

> 💁 Jika anda selesa dengan kerja menyolder, anda boleh menggunakan [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) untuk menyambungkan ReSpeaker.

Anda juga memerlukan kad SD untuk memuat turun dan memainkan audio. Wio Terminal hanya menyokong Kad SD sehingga 16GB, dan kad ini perlu diformat sebagai FAT32 atau exFAT.

### Tugas - sambungkan ReSpeaker Pi Hat

1. Dengan Wio Terminal dimatikan, sambungkan ReSpeaker 2-Mics Pi Hat ke Wio Terminal menggunakan kabel jumper dan soket GPIO di bahagian belakang Wio Terminal:

    Pin perlu disambungkan dengan cara ini:

    ![Diagram pin](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.ms.png)

1. Letakkan ReSpeaker dan Wio Terminal dengan soket GPIO menghadap ke atas, dan di sebelah kiri.

1. Mulakan dari soket di bahagian atas kiri soket GPIO pada ReSpeaker. Sambungkan kabel jumper pin-to-pin dari soket atas kiri ReSpeaker ke soket atas kiri Wio Terminal.

1. Ulangi proses ini sepanjang soket GPIO di sebelah kiri. Pastikan pin dimasukkan dengan kukuh.

    ![ReSpeaker dengan pin sebelah kiri disambungkan ke pin sebelah kiri Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.ms.png)

    ![ReSpeaker dengan pin sebelah kiri disambungkan ke pin sebelah kiri Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.ms.png)

    > 💁 Jika kabel jumper anda disambungkan dalam bentuk pita, pastikan semuanya bersama - ini memudahkan anda memastikan semua kabel disambungkan mengikut urutan.

1. Ulangi proses menggunakan soket GPIO sebelah kanan pada ReSpeaker dan Wio Terminal. Kabel ini perlu melalui kabel yang sudah disambungkan.

    ![ReSpeaker dengan pin sebelah kanan disambungkan ke pin sebelah kanan Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.ms.png)

    ![ReSpeaker dengan pin sebelah kanan disambungkan ke pin sebelah kanan Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.ms.png)

    > 💁 Jika kabel jumper anda disambungkan dalam bentuk pita, pisahkan menjadi dua pita. Letakkan satu di setiap sisi kabel yang sudah ada.

    > 💁 Anda boleh menggunakan pita pelekat untuk memegang pin dalam satu blok untuk membantu mengelakkan pin terkeluar semasa anda menyambungkannya.
    >
    > ![Pin dipasang dengan pita pelekat](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.ms.png)

1. Anda perlu menambah pembesar suara.

    * Jika anda menggunakan pembesar suara dengan kabel JST, sambungkan ke port JST pada ReSpeaker.

      ![Pembesar suara disambungkan ke ReSpeaker dengan kabel JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.ms.png)

    * Jika anda menggunakan pembesar suara dengan jack 3.5mm, atau fon kepala, masukkan ke dalam soket jack 3.5mm.

      ![Pembesar suara disambungkan ke ReSpeaker melalui soket jack 3.5mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.ms.png)

### Tugas - sediakan kad SD

1. Sambungkan Kad SD ke komputer anda, menggunakan pembaca luaran jika anda tidak mempunyai slot Kad SD.

1. Format Kad SD menggunakan alat yang sesuai pada komputer anda, pastikan menggunakan sistem fail FAT32 atau exFAT.

1. Masukkan Kad SD ke dalam slot Kad SD di sebelah kiri Wio Terminal, tepat di bawah butang kuasa. Pastikan kad dimasukkan sepenuhnya dan klik masuk - anda mungkin memerlukan alat nipis atau Kad SD lain untuk membantu menolaknya sepenuhnya.

    ![Memasukkan Kad SD ke dalam slot Kad SD di bawah suis kuasa](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.ms.png)

    > 💁 Untuk mengeluarkan Kad SD, anda perlu menolaknya sedikit dan ia akan keluar. Anda memerlukan alat nipis seperti pemutar skru kepala rata atau Kad SD lain untuk melakukannya.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.