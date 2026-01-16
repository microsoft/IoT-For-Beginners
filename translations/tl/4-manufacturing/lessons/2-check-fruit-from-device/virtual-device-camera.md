<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T21:03:45+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "tl"
}
-->
# Kunan ng Larawan - Virtual na IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng camera sensor sa iyong virtual na IoT device at magbabasa ng mga larawan mula rito.

## Hardware

Gagamit ang virtual na IoT device ng isang simulated na camera na maaaring magpadala ng mga larawan mula sa mga file o mula sa iyong webcam.

### Idagdag ang Camera sa CounterFit

Upang gumamit ng virtual na camera, kailangan mong magdagdag ng isa sa CounterFit app.

#### Gawain - idagdag ang camera sa CounterFit

Idagdag ang Camera sa CounterFit app.

1. Gumawa ng bagong Python app sa iyong computer sa isang folder na tinatawag na `fruit-quality-detector` na may isang file na tinatawag na `app.py` at isang Python virtual environment, at idagdag ang CounterFit pip packages.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa paggawa at pag-set up ng CounterFit Python project sa aralin 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Mag-install ng karagdagang Pip package upang mag-install ng CounterFit shim na maaaring makipag-usap sa mga Camera sensor sa pamamagitan ng pagsasagawa ng ilang bahagi ng [Picamera Pip package](https://pypi.org/project/picamera/). Siguraduhing ini-install mo ito mula sa terminal na may naka-activate na virtual environment.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng camera:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *Camera*.

    1. Itakda ang *Name* sa `Picamera`.

    1. Piliin ang **Add** button upang gumawa ng camera.

    ![Ang mga setting ng camera](../../../../../translated_images/tl/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Ang camera ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Ang nalikhang camera](../../../../../translated_images/tl/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Iprograma ang Camera

Ngayon ay maaari nang i-program ang virtual na IoT device upang magamit ang virtual na camera.

### Gawain - iprograma ang camera

Iprograma ang device.

1. Siguraduhing bukas ang `fruit-quality-detector` app sa VS Code.

1. Buksan ang file na `app.py`.

1. Idagdag ang sumusunod na code sa itaas ng `app.py` upang ikonekta ang app sa CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Idagdag ang sumusunod na code sa iyong `app.py` file:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Ang code na ito ay nag-i-import ng ilang kinakailangang library, kabilang ang `PiCamera` class mula sa counterfit_shims_picamera library.

1. Idagdag ang sumusunod na code sa ibaba nito upang i-initialize ang camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Ang code na ito ay lumilikha ng isang PiCamera object, itinatakda ang resolution sa 640x480. Bagama't sinusuportahan ang mas mataas na resolution, ang image classifier ay gumagana sa mas maliliit na larawan (227x227) kaya't hindi na kailangang kumuha at magpadala ng mas malalaking larawan.

    Ang linya na `camera.rotation = 0` ay nagtatakda ng rotation ng larawan sa degrees. Kung kailangan mong i-rotate ang larawan mula sa webcam o file, itakda ito nang naaayon. Halimbawa, kung nais mong baguhin ang larawan ng isang saging mula sa webcam sa landscape mode patungo sa portrait, itakda ang `camera.rotation = 90`.

1. Idagdag ang sumusunod na code sa ibaba nito upang makuha ang larawan bilang binary data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ang code na ito ay lumilikha ng isang `BytesIO` object upang mag-imbak ng binary data. Ang larawan ay binabasa mula sa camera bilang isang JPEG file at iniimbak sa object na ito. Ang object na ito ay may position indicator upang malaman kung nasaan ito sa data upang ang karagdagang data ay maaaring isulat sa dulo kung kinakailangan, kaya't ang linya na `image.seek(0)` ay inililipat ang posisyon pabalik sa simula upang mabasa ang lahat ng data mamaya.

1. Sa ibaba nito, idagdag ang sumusunod upang i-save ang larawan sa isang file:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ang code na ito ay nagbubukas ng isang file na tinatawag na `image.jpg` para sa pagsusulat, pagkatapos ay binabasa ang lahat ng data mula sa `BytesIO` object at isinusulat ito sa file.

    > 💁 Maaari mong kunin ang larawan nang direkta sa isang file sa halip na isang `BytesIO` object sa pamamagitan ng pagpasa ng pangalan ng file sa `camera.capture` call. Ang dahilan ng paggamit ng `BytesIO` object ay upang sa susunod na bahagi ng aralin, maaari mong ipadala ang larawan sa iyong image classifier.

1. I-configure ang larawan na kukunin ng camera sa CounterFit. Maaari mong itakda ang *Source* sa *File*, pagkatapos ay mag-upload ng isang image file, o itakda ang *Source* sa *WebCam*, at ang mga larawan ay kukunin mula sa iyong webcam. Siguraduhing piliin ang **Set** button pagkatapos pumili ng larawan o piliin ang iyong webcam.

    ![CounterFit na may file na itinakda bilang image source, at isang webcam na nagpapakita ng tao na may hawak na saging sa preview ng webcam](../../../../../translated_images/tl/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Ang isang larawan ay kukunin at mase-save bilang `image.jpg` sa kasalukuyang folder. Makikita mo ang file na ito sa VS Code explorer. Piliin ang file upang makita ang larawan. Kung kailangan nito ng rotation, i-update ang linya na `camera.rotation = 0` ayon sa kinakailangan at kumuha ng panibagong larawan.

> 💁 Maaari mong makita ang code na ito sa [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) folder.

😀 Tagumpay ang iyong camera program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakatandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi eksaktong salin. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.