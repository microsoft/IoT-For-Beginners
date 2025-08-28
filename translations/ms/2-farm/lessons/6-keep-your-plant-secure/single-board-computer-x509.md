<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T22:11:29+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "ms"
}
-->
# Gunakan sijil X.509 dalam kod peranti anda - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menyambungkan peranti IoT maya atau Raspberry Pi anda ke IoT Hub menggunakan sijil X.509.

## Sambungkan peranti anda ke IoT Hub

Langkah seterusnya adalah menyambungkan peranti anda ke IoT Hub menggunakan sijil X.509.

### Tugasan - sambungkan ke IoT Hub

1. Salin fail kunci dan sijil ke folder yang mengandungi kod peranti IoT anda. Jika anda menggunakan Raspberry Pi melalui VS Code Remote SSH dan mencipta kunci di PC atau Mac anda, anda boleh seret dan lepaskan fail ke dalam explorer di VS Code untuk menyalinnya.

1. Buka fail `app.py`

1. Untuk menyambung menggunakan sijil X.509, anda memerlukan nama hos IoT Hub dan sijil X.509. Mulakan dengan mencipta pemboleh ubah yang mengandungi nama hos dengan menambah kod berikut sebelum klien peranti dicipta:

    ```python
    host_name = "<host_name>"
    ```

    Gantikan `<host_name>` dengan nama hos IoT Hub anda. Anda boleh mendapatkannya dari bahagian `HostName` dalam `connection_string`. Ia akan menjadi nama IoT Hub anda, diakhiri dengan `.azure-devices.net`

1. Di bawah ini, isytiharkan pemboleh ubah dengan ID peranti:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Anda memerlukan satu instance kelas `X509` yang mengandungi fail sijil X.509. Tambahkan `X509` ke senarai kelas yang diimport dari modul `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Cipta instance kelas `X509` menggunakan fail sijil dan kunci anda dengan menambah kod ini di bawah deklarasi `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Ini akan mencipta kelas `X509` menggunakan fail `soil-moisture-sensor-x509-cert.pem` dan `soil-moisture-sensor-x509-key.pem` yang telah dicipta sebelum ini.

1. Gantikan baris kod yang mencipta `device_client` daripada connection string dengan yang berikut:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Ini akan menyambung menggunakan sijil X.509 dan bukannya connection string.
    
1. Padamkan baris dengan pemboleh ubah `connection_string`.

1. Jalankan kod anda. Pantau mesej yang dihantar ke IoT Hub, dan hantar permintaan kaedah langsung seperti sebelumnya. Anda akan melihat peranti menyambung dan menghantar bacaan kelembapan tanah, serta menerima permintaan kaedah langsung.

> 💁 Anda boleh menemui kod ini dalam folder [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) atau [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Program sensor kelembapan tanah anda kini disambungkan ke IoT Hub menggunakan sijil X.509!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.