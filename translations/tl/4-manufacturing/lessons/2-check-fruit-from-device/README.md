<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:57:21+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "tl"
}
-->
# Suriin ang Kalidad ng Prutas gamit ang isang IoT Device

![Isang sketchnote overview ng araling ito](../../../../../translated_images/tl/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture Quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Panimula

Sa nakaraang aralin, natutunan mo ang tungkol sa mga image classifier at kung paano sanayin ang mga ito upang matukoy ang mabuti at masamang prutas. Upang magamit ang image classifier na ito sa isang IoT application, kailangan mong makunan ng larawan gamit ang isang uri ng kamera at ipadala ang larawang ito sa cloud upang ma-classify.

Sa araling ito, matututo ka tungkol sa mga camera sensor at kung paano gamitin ang mga ito sa isang IoT device upang makunan ng larawan. Matututo ka rin kung paano tawagan ang image classifier mula sa iyong IoT device.

Sa araling ito, tatalakayin natin ang:

* [Mga Camera Sensor](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Pagkuha ng Larawan gamit ang isang IoT Device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [I-publish ang Iyong Image Classifier](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [I-classify ang mga Larawan mula sa Iyong IoT Device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Pagbutihin ang Modelo](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Mga Camera Sensor

Ang mga camera sensor, tulad ng ipinapahiwatig ng pangalan, ay mga kamera na maaari mong ikonekta sa iyong IoT device. Maaari silang kumuha ng mga still image o mag-capture ng streaming video. Ang ilan ay magbibigay ng raw image data, habang ang iba ay nagko-compress ng image data sa isang image file tulad ng JPEG o PNG. Karaniwan, ang mga kamera na gumagana sa IoT devices ay mas maliit at may mas mababang resolution kaysa sa nakasanayan mo, ngunit maaari kang makakuha ng mga high-resolution camera na maihahambing sa mga high-end na telepono. Maaari ka ring makakuha ng iba't ibang interchangeable lenses, multiple camera setups, infra-red thermal cameras, o UV cameras.

![Ang liwanag mula sa isang eksena ay dumadaan sa isang lente at nakatuon sa isang CMOS sensor](../../../../../translated_images/tl/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Karamihan sa mga camera sensor ay gumagamit ng image sensors kung saan ang bawat pixel ay isang photodiode. Ang isang lente ay nagpo-focus ng imahe sa image sensor, at libu-libo o milyun-milyong photodiodes ang nagde-detect ng liwanag na tumatama sa bawat isa at nire-record ito bilang pixel data.

> 💁 Ang mga lente ay nag-i-invert ng mga imahe, at ang camera sensor ang nagbabalik ng imahe sa tamang posisyon. Ganito rin ang nangyayari sa iyong mga mata - ang nakikita mo ay na-dedetect nang baligtad sa likod ng iyong mata at ang iyong utak ang nagko-correct nito.

> 🎓 Ang image sensor ay kilala bilang isang Active-Pixel Sensor (APS), at ang pinakasikat na uri ng APS ay isang complementary metal-oxide semiconductor sensor, o CMOS. Maaaring narinig mo na ang terminong CMOS sensor na ginagamit para sa mga camera sensor.

Ang mga camera sensor ay digital sensors na nagpapadala ng image data bilang digital data, karaniwang sa tulong ng isang library na nagbibigay ng komunikasyon. Ang mga kamera ay kumokonekta gamit ang mga protocol tulad ng SPI upang maipadala ang malaking dami ng data - ang mga imahe ay mas malaki kaysa sa mga simpleng numero mula sa isang sensor tulad ng temperature sensor.

✅ Ano ang mga limitasyon sa laki ng imahe sa mga IoT device? Isaalang-alang ang mga limitasyon lalo na sa hardware ng microcontroller.

## Pagkuha ng Larawan gamit ang isang IoT Device

Maaari mong gamitin ang iyong IoT device upang kumuha ng larawan na iko-classify.

### Gawain - kumuha ng larawan gamit ang isang IoT device

Sundin ang kaukulang gabay upang kumuha ng larawan gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Single-board computer - Raspberry Pi](pi-camera.md)
* [Single-board computer - Virtual device](virtual-device-camera.md)

## I-publish ang Iyong Image Classifier

Na-train mo na ang iyong image classifier sa nakaraang aralin. Bago mo ito magamit mula sa iyong IoT device, kailangan mong i-publish ang modelo.

### Mga Iteration ng Modelo

Habang tine-train ang iyong modelo sa nakaraang aralin, maaaring napansin mo na ang **Performance** tab ay nagpapakita ng mga iteration sa gilid. Kapag una mong tine-train ang modelo, makikita mo ang *Iteration 1* sa training. Kapag pinabuti mo ang modelo gamit ang prediction images, makikita mo ang *Iteration 2* sa training.

Sa tuwing tine-train mo ang modelo, nagkakaroon ka ng bagong iteration. Ito ay isang paraan upang subaybayan ang iba't ibang bersyon ng iyong modelo na na-train sa iba't ibang data sets. Kapag gumawa ka ng **Quick Test**, mayroong drop-down na maaari mong gamitin upang piliin ang iteration, kaya maaari mong ihambing ang mga resulta sa iba't ibang iteration.

Kapag nasiyahan ka na sa isang iteration, maaari mo itong i-publish upang magamit mula sa mga external na application. Sa ganitong paraan, maaari kang magkaroon ng isang published na bersyon na ginagamit ng iyong mga device, pagkatapos ay magtrabaho sa isang bagong bersyon sa maraming iteration, at i-publish ito kapag nasiyahan ka na.

### Gawain - i-publish ang isang iteration

Ang mga iteration ay na-publish mula sa Custom Vision portal.

1. Buksan ang Custom Vision portal sa [CustomVision.ai](https://customvision.ai) at mag-sign in kung hindi mo pa ito nabubuksan. Pagkatapos, buksan ang iyong `fruit-quality-detector` na proyekto.

1. Piliin ang **Performance** tab mula sa mga opsyon sa itaas.

1. Piliin ang pinakabagong iteration mula sa *Iterations* list sa gilid.

1. Piliin ang **Publish** button para sa iteration.

    ![Ang publish button](../../../../../translated_images/tl/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Sa *Publish Model* dialog, itakda ang *Prediction resource* sa `fruit-quality-detector-prediction` na resource na ginawa mo sa nakaraang aralin. Iwanan ang pangalan bilang `Iteration2`, at piliin ang **Publish** button.

1. Kapag na-publish na, piliin ang **Prediction URL** button. Ipapakita nito ang mga detalye ng prediction API, at kakailanganin mo ang mga ito upang tawagan ang modelo mula sa iyong IoT device. Ang mas mababang bahagi ay may label na *If you have an image file*, at ito ang mga detalye na kailangan mo. Kopyahin ang URL na ipinapakita na magiging katulad ng:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Kung saan ang `<location>` ay ang lokasyon na ginamit mo noong nilikha ang iyong custom vision resource, at ang `<id>` ay isang mahabang ID na binubuo ng mga letra at numero.

    Kopyahin din ang *Prediction-Key* value. Ito ay isang secure na key na kailangan mong ipasa kapag tinawag mo ang modelo. Tanging ang mga application na nagpapasa ng key na ito ang pinapayagang gumamit ng modelo, ang iba pang mga application ay tinatanggihan.

    ![Ang prediction API dialog na nagpapakita ng URL at key](../../../../../translated_images/tl/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Kapag ang isang bagong iteration ay na-publish, magkakaroon ito ng ibang pangalan. Paano mo sa tingin babaguhin ang iteration na ginagamit ng isang IoT device?

## I-classify ang mga Larawan mula sa Iyong IoT Device

Maaari mo nang gamitin ang mga detalye ng koneksyon na ito upang tawagan ang image classifier mula sa iyong IoT device.

### Gawain - i-classify ang mga larawan mula sa iyong IoT device

Sundin ang kaukulang gabay upang i-classify ang mga larawan gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-classify-image.md)

## Pagbutihin ang Modelo

Maaaring mapansin mo na ang mga resulta na nakukuha mo kapag ginagamit ang kamera na nakakonekta sa iyong IoT device ay hindi tumutugma sa inaasahan mo. Ang mga prediction ay hindi laging kasing-accurate ng paggamit ng mga larawang in-upload mula sa iyong computer. Ito ay dahil ang modelo ay na-train sa ibang data kaysa sa ginagamit para sa mga prediction.

Upang makuha ang pinakamahusay na resulta para sa isang image classifier, nais mong sanayin ang modelo gamit ang mga larawang halos kapareho ng mga larawang ginagamit para sa mga prediction. Halimbawa, kung ginamit mo ang camera ng iyong telepono upang kumuha ng mga larawan para sa training, ang kalidad ng imahe, sharpness, at kulay ay magiging iba sa isang kamera na nakakonekta sa isang IoT device.

![2 larawan ng saging, isang mababang resolution na may mahinang ilaw mula sa isang IoT device, at isang mataas na resolution na may magandang ilaw mula sa isang telepono](../../../../../translated_images/tl/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Sa larawan sa itaas, ang larawan ng saging sa kaliwa ay kinuha gamit ang isang Raspberry Pi Camera, habang ang nasa kanan ay kinuha ng parehong saging sa parehong lokasyon gamit ang isang iPhone. Mayroong kapansin-pansing pagkakaiba sa kalidad - ang larawan mula sa iPhone ay mas malinaw, may mas matingkad na kulay, at mas mataas ang contrast.

✅ Ano pa kaya ang maaaring magdulot ng maling prediction sa mga larawang kinukuha ng iyong IoT device? Isipin ang kapaligiran kung saan maaaring gamitin ang isang IoT device, anong mga salik ang maaaring makaapekto sa larawang kinukuha?

Upang mapabuti ang modelo, maaari mo itong i-retrain gamit ang mga larawang kinuha mula sa IoT device.

### Gawain - pagbutihin ang modelo

1. I-classify ang maraming larawan ng parehong hinog at hilaw na prutas gamit ang iyong IoT device.

1. Sa Custom Vision portal, i-retrain ang modelo gamit ang mga larawan sa *Predictions* tab.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa retraining ng iyong classifier sa lesson 1 kung kinakailangan](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Kung ang iyong mga larawan ay mukhang ibang-iba sa mga orihinal na ginamit para sa training, maaari mong tanggalin ang lahat ng orihinal na larawan sa pamamagitan ng pagpili sa mga ito sa *Training Images* tab at pagpili sa **Delete** button. Upang pumili ng larawan, ilipat ang iyong cursor dito at lilitaw ang isang tick, piliin ang tick upang piliin o alisin ang pagpili sa larawan.

1. Mag-train ng bagong iteration ng modelo at i-publish ito gamit ang mga hakbang sa itaas.

1. I-update ang endpoint URL sa iyong code, at i-re-run ang app.

1. Ulitin ang mga hakbang na ito hanggang sa masiyahan ka sa mga resulta ng mga prediction.

---

## 🚀 Hamon

Gaano kalaki ang epekto ng resolution ng imahe o ilaw sa prediction?

Subukang baguhin ang resolution ng mga imahe sa iyong device code at tingnan kung may epekto ito sa kalidad ng mga imahe. Subukan din ang pagbabago ng ilaw.

Kung gagawa ka ng isang production device na ibebenta sa mga sakahan o pabrika, paano mo masisiguro na nagbibigay ito ng pare-parehong resulta sa lahat ng oras?

## Post-lecture Quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Review at Pag-aaral sa Sarili

Na-train mo ang iyong custom vision model gamit ang portal. Ang prosesong ito ay umaasa sa pagkakaroon ng mga larawan - at sa totoong mundo, maaaring hindi mo makuha ang training data na tumutugma sa mga larawang kinukuha ng kamera sa iyong device. Maaari mong malampasan ito sa pamamagitan ng pag-train nang direkta mula sa iyong device gamit ang training API, upang mag-train ng modelo gamit ang mga larawang kinukuha mula sa iyong IoT device.

* Basahin ang tungkol sa training API sa [using the Custom Vision SDK quick start](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Takdang Aralin

[Tumugon sa mga resulta ng classification](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.