<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T23:30:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "id"
}
-->
# Konfigurasi mikrofon dan speaker - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan speaker ke Wio Terminal Anda. Wio Terminal sudah memiliki mikrofon bawaan, yang dapat digunakan untuk menangkap suara.

## Perangkat Keras

Wio Terminal sudah memiliki mikrofon bawaan, yang dapat digunakan untuk menangkap audio untuk pengenalan suara.

![Mikrofon pada Wio Terminal](../../../../../translated_images/id/wio-mic.3f8c843dbe8ad917.webp)

Untuk menambahkan speaker, Anda dapat menggunakan [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Ini adalah papan eksternal yang berisi 2 mikrofon MEMS, serta konektor speaker dan soket headphone.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/id/respeaker.f5d19d1c6b14ab16.webp)

Anda perlu menambahkan headphone, speaker dengan jack 3.5mm, atau speaker dengan koneksi JST seperti [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Untuk menghubungkan ReSpeaker 2-Mics Pi Hat, Anda akan membutuhkan kabel jumper 40 pin-to-pin (juga disebut sebagai male-to-male).

> 💁 Jika Anda nyaman dengan menyolder, Anda dapat menggunakan [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) untuk menghubungkan ReSpeaker.

Anda juga akan membutuhkan kartu SD untuk mengunduh dan memutar audio. Wio Terminal hanya mendukung kartu SD hingga ukuran 16GB, dan kartu ini harus diformat sebagai FAT32 atau exFAT.

### Tugas - menghubungkan ReSpeaker Pi Hat

1. Dengan Wio Terminal dalam keadaan mati, hubungkan ReSpeaker 2-Mics Pi Hat ke Wio Terminal menggunakan kabel jumper dan soket GPIO di bagian belakang Wio Terminal:

    Pin harus dihubungkan dengan cara berikut:

    ![Diagram pin](../../../../../translated_images/id/wio-respeaker-wiring-0.767f80aa65081038.webp)

1. Posisikan ReSpeaker dan Wio Terminal dengan soket GPIO menghadap ke atas, dan di sisi kiri.

1. Mulailah dari soket di bagian kiri atas soket GPIO pada ReSpeaker. Hubungkan kabel jumper pin-to-pin dari soket kiri atas ReSpeaker ke soket kiri atas Wio Terminal.

1. Ulangi proses ini hingga ke bawah soket GPIO di sisi kiri. Pastikan pin terpasang dengan kuat.

    ![ReSpeaker dengan pin sisi kiri terhubung ke pin sisi kiri Wio Terminal](../../../../../translated_images/id/wio-respeaker-wiring-1.8d894727f2ba2400.webp)

    ![ReSpeaker dengan pin sisi kiri terhubung ke pin sisi kiri Wio Terminal](../../../../../translated_images/id/wio-respeaker-wiring-2.329e1cbd306e754f.webp)

    > 💁 Jika kabel jumper Anda terhubung dalam bentuk pita, biarkan mereka tetap bersama - ini akan mempermudah memastikan semua kabel terhubung dengan urutan yang benar.

1. Ulangi proses ini menggunakan soket GPIO di sisi kanan pada ReSpeaker dan Wio Terminal. Kabel ini harus melewati kabel yang sudah terpasang.

    ![ReSpeaker dengan pin sisi kanan terhubung ke pin sisi kanan Wio Terminal](../../../../../translated_images/id/wio-respeaker-wiring-3.75b0be447e2fa930.webp)

    ![ReSpeaker dengan pin sisi kanan terhubung ke pin sisi kanan Wio Terminal](../../../../../translated_images/id/wio-respeaker-wiring-4.aa9cd434d8779437.webp)

    > 💁 Jika kabel jumper Anda terhubung dalam bentuk pita, pisahkan menjadi dua pita. Lewatkan masing-masing di sisi kabel yang sudah ada.

    > 💁 Anda dapat menggunakan selotip untuk menahan pin dalam satu blok agar tidak terlepas saat Anda menghubungkan semuanya.
    >
    > ![Pin yang diperbaiki dengan selotip](../../../../../translated_images/id/wio-respeaker-wiring-5.af117c20acf622f3.webp)

1. Anda perlu menambahkan speaker.

    * Jika Anda menggunakan speaker dengan kabel JST, hubungkan ke port JST pada ReSpeaker.

      ![Speaker terhubung ke ReSpeaker dengan kabel JST](../../../../../translated_images/id/respeaker-jst-speaker.a441d177809df945.webp)

    * Jika Anda menggunakan speaker dengan jack 3.5mm, atau headphone, masukkan ke soket jack 3.5mm.

      ![Speaker terhubung ke ReSpeaker melalui soket jack 3.5mm](../../../../../translated_images/id/respeaker-35mm-speaker.ad79ef4f128c7751.webp)

### Tugas - mengatur kartu SD

1. Hubungkan kartu SD ke komputer Anda, menggunakan pembaca eksternal jika komputer Anda tidak memiliki slot kartu SD.

1. Format kartu SD menggunakan alat yang sesuai di komputer Anda, pastikan menggunakan sistem file FAT32 atau exFAT.

1. Masukkan kartu SD ke slot kartu SD di sisi kiri Wio Terminal, tepat di bawah tombol daya. Pastikan kartu masuk sepenuhnya dan terkunci - Anda mungkin memerlukan alat tipis atau kartu SD lain untuk membantu mendorongnya masuk sepenuhnya.

    ![Memasukkan kartu SD ke slot kartu SD di bawah tombol daya](../../../../../translated_images/id/wio-sd-card.acdcbe322fa4ee7f.webp)

    > 💁 Untuk mengeluarkan kartu SD, Anda perlu mendorongnya sedikit dan kartu akan keluar. Anda akan membutuhkan alat tipis seperti obeng pipih atau kartu SD lain untuk melakukannya.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.