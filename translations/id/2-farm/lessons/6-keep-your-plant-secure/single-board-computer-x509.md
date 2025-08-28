<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T22:11:19+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "id"
}
-->
# Gunakan sertifikat X.509 dalam kode perangkat Anda - Perangkat IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menghubungkan perangkat IoT virtual atau Raspberry Pi Anda ke IoT Hub menggunakan sertifikat X.509.

## Hubungkan perangkat Anda ke IoT Hub

Langkah berikutnya adalah menghubungkan perangkat Anda ke IoT Hub menggunakan sertifikat X.509.

### Tugas - hubungkan ke IoT Hub

1. Salin file kunci dan sertifikat ke folder yang berisi kode perangkat IoT Anda. Jika Anda menggunakan Raspberry Pi melalui VS Code Remote SSH dan membuat kunci di PC atau Mac Anda, Anda dapat menyeret dan melepaskan file ke explorer di VS Code untuk menyalinnya.

1. Buka file `app.py`

1. Untuk terhubung menggunakan sertifikat X.509, Anda akan memerlukan nama host dari IoT Hub, dan sertifikat X.509. Mulailah dengan membuat variabel yang berisi nama host dengan menambahkan kode berikut sebelum klien perangkat dibuat:

    ```python
    host_name = "<host_name>"
    ```

    Ganti `<host_name>` dengan nama host IoT Hub Anda. Anda dapat menemukannya di bagian `HostName` dalam `connection_string`. Ini akan menjadi nama IoT Hub Anda, diakhiri dengan `.azure-devices.net`

1. Di bawah ini, deklarasikan variabel dengan ID perangkat:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Anda akan memerlukan instance dari kelas `X509` yang berisi file sertifikat X.509. Tambahkan `X509` ke daftar kelas yang diimpor dari modul `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Buat instance kelas `X509` menggunakan file sertifikat dan kunci Anda dengan menambahkan kode ini di bawah deklarasi `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Ini akan membuat kelas `X509` menggunakan file `soil-moisture-sensor-x509-cert.pem` dan `soil-moisture-sensor-x509-key.pem` yang dibuat sebelumnya.

1. Ganti baris kode yang membuat `device_client` dari string koneksi, dengan yang berikut:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Ini akan terhubung menggunakan sertifikat X.509, bukan string koneksi.
    
1. Hapus baris dengan variabel `connection_string`.

1. Jalankan kode Anda. Pantau pesan yang dikirim ke IoT Hub, dan kirim permintaan metode langsung seperti sebelumnya. Anda akan melihat perangkat terhubung dan mengirimkan pembacaan kelembapan tanah, serta menerima permintaan metode langsung.

> 💁 Anda dapat menemukan kode ini di folder [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) atau [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Program sensor kelembapan tanah Anda telah terhubung ke IoT Hub menggunakan sertifikat X.509!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.