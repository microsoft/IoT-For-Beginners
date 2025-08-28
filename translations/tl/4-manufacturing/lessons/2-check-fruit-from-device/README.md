<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T22:59:06+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "tl"
}
-->
# Suriin ang kalidad ng prutas gamit ang IoT device

![Isang sketchnote overview ng araling ito](../../../../../translated_images/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Panimula

Sa nakaraang aralin, natutunan mo ang tungkol sa mga image classifier, at kung paano sanayin ang mga ito upang matukoy ang mabuti at masamang prutas. Upang magamit ang image classifier na ito sa isang IoT application, kailangan mong makuha ang isang imahe gamit ang isang uri ng camera, at ipadala ang imahe na ito sa cloud upang ma-classify.

Sa araling ito, matutunan mo ang tungkol sa mga camera sensor, at kung paano gamitin ang mga ito sa isang IoT device upang makuha ang isang imahe. Matutunan mo rin kung paano tawagin ang image classifier mula sa iyong IoT device.

Sa araling ito, tatalakayin natin:

* [Mga camera sensor](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Kumuha ng imahe gamit ang IoT device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [I-publish ang iyong image classifier](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [I-classify ang mga imahe mula sa iyong IoT device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Pagbutihin ang modelo](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Mga camera sensor

Ang mga camera sensor, tulad ng ipinahihiwatig ng pangalan, ay mga camera na maaari mong ikonekta sa iyong IoT device. Maaari silang kumuha ng mga still image, o mag-capture ng streaming video. Ang ilan ay magbibigay ng raw image data, habang ang iba ay magko-compress ng image data sa isang image file tulad ng JPEG o PNG. Karaniwan, ang mga camera na gumagana sa IoT devices ay mas maliit at mas mababa ang resolution kaysa sa mga nakasanayan mo, ngunit maaari kang makakuha ng mga high-resolution camera na maihahambing sa mga top-end na telepono. Maaari kang makakuha ng iba't ibang uri ng interchangeable lenses, multiple camera setups, infra-red thermal cameras, o UV cameras.

![Ang liwanag mula sa isang eksena ay dumadaan sa isang lens at nakatuon sa isang CMOS sensor](../../../../../translated_images/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.tl.png)

Karamihan sa mga camera sensor ay gumagamit ng image sensors kung saan ang bawat pixel ay isang photodiode. Ang isang lens ay nagpo-focus ng imahe sa image sensor, at libu-libo o milyun-milyong photodiodes ang nagde-detect ng liwanag na bumabagsak sa bawat isa, at nire-record ito bilang pixel data.

> 💁 Ang mga lens ay nag-i-invert ng mga imahe, pagkatapos ay ibinabalik ng camera sensor ang imahe sa tamang posisyon. Ganito rin ang nangyayari sa iyong mga mata - ang nakikita mo ay na-detect nang baligtad sa likod ng iyong mata at itinatama ito ng iyong utak.

> 🎓 Ang image sensor ay kilala bilang Active-Pixel Sensor (APS), at ang pinakasikat na uri ng APS ay ang complementary metal-oxide semiconductor sensor, o CMOS. Maaaring narinig mo na ang terminong CMOS sensor na ginagamit para sa mga camera sensor.

Ang mga camera sensor ay digital sensors, na nagpapadala ng image data bilang digital data, karaniwang sa tulong ng isang library na nagbibigay ng komunikasyon. Ang mga camera ay kumokonekta gamit ang mga protocol tulad ng SPI upang payagan silang magpadala ng malaking dami ng data - ang mga imahe ay mas malaki kaysa sa mga simpleng numero mula sa isang sensor tulad ng temperature sensor.

✅ Ano ang mga limitasyon sa laki ng imahe sa mga IoT device? Isipin ang mga constraint lalo na sa microcontroller hardware.

## Kumuha ng imahe gamit ang IoT device

Maaari mong gamitin ang iyong IoT device upang kumuha ng imahe na ma-classify.

### Gawain - kumuha ng imahe gamit ang IoT device

Sundin ang kaukulang gabay upang kumuha ng imahe gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Single-board computer - Raspberry Pi](pi-camera.md)
* [Single-board computer - Virtual device](virtual-device-camera.md)

## I-publish ang iyong image classifier

Sinanay mo ang iyong image classifier sa nakaraang aralin. Bago mo ito magamit mula sa iyong IoT device, kailangan mong i-publish ang modelo.

### Mga Iteration ng Modelo

Kapag ang iyong modelo ay nagsasanay sa nakaraang aralin, maaaring napansin mo na ang **Performance** tab ay nagpapakita ng mga iteration sa gilid. Kapag una mong sinanay ang modelo, makikita mo ang *Iteration 1* sa training. Kapag pinabuti mo ang modelo gamit ang mga prediction images, makikita mo ang *Iteration 2* sa training.

Tuwing sinasanay mo ang modelo, nakakakuha ka ng bagong iteration. Ito ay isang paraan upang subaybayan ang iba't ibang bersyon ng iyong modelo na sinanay sa iba't ibang data sets. Kapag gumawa ka ng **Quick Test**, mayroong drop-down na maaari mong gamitin upang piliin ang iteration, upang maihambing ang mga resulta sa iba't ibang iteration.

Kapag nasiyahan ka sa isang iteration, maaari mo itong i-publish upang magamit mula sa mga external na application. Sa ganitong paraan, maaari kang magkaroon ng isang published version na ginagamit ng iyong mga device, pagkatapos ay magtrabaho sa isang bagong bersyon sa maraming iteration, pagkatapos ay i-publish ito kapag nasiyahan ka na dito.

### Gawain - i-publish ang isang iteration

Ang mga iteration ay na-publish mula sa Custom Vision portal.

1. Buksan ang Custom Vision portal sa [CustomVision.ai](https://customvision.ai) at mag-sign in kung hindi mo pa ito nabubuksan. Pagkatapos ay buksan ang iyong `fruit-quality-detector` na proyekto.

1. Piliin ang **Performance** tab mula sa mga opsyon sa itaas.

1. Piliin ang pinakabagong iteration mula sa *Iterations* list sa gilid.

1. Piliin ang **Publish** button para sa iteration.

    ![Ang publish button](../../../../../translated_images/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.tl.png)

1. Sa *Publish Model* dialog, itakda ang *Prediction resource* sa `fruit-quality-detector-prediction` resource na ginawa mo sa nakaraang aralin. Iwanan ang pangalan bilang `Iteration2`, at piliin ang **Publish** button.

1. Kapag na-publish na, piliin ang **Prediction URL** button. Ipapakita nito ang mga detalye ng prediction API, at kakailanganin mo ang mga ito upang tawagin ang modelo mula sa iyong IoT device. Ang mas mababang seksyon ay may label na *If you have an image file*, at ito ang mga detalye na kailangan mo. Kumuha ng kopya ng URL na ipinapakita na magiging katulad ng:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Kung saan ang `<location>` ay ang lokasyon na ginamit mo sa paglikha ng iyong custom vision resource, at ang `<id>` ay isang mahabang ID na binubuo ng mga letra at numero.

    Kumuha rin ng kopya ng *Prediction-Key* value. Ito ay isang secure na key na kailangan mong ipasa kapag tinawag mo ang modelo. Tanging ang mga application na nagpapasa ng key na ito ang pinapayagang gamitin ang modelo, ang iba pang mga application ay tinatanggihan.

    ![Ang prediction API dialog na nagpapakita ng URL at key](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.tl.png)

✅ Kapag ang isang bagong iteration ay na-publish, magkakaroon ito ng ibang pangalan. Paano mo sa tingin mababago ang iteration na ginagamit ng isang IoT device?

## I-classify ang mga imahe mula sa iyong IoT device

Maaari mo na ngayong gamitin ang mga detalye ng koneksyon upang tawagin ang image classifier mula sa iyong IoT device.

### Gawain - i-classify ang mga imahe mula sa iyong IoT device

Sundin ang kaukulang gabay upang i-classify ang mga imahe gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-classify-image.md)

## Pagbutihin ang modelo

Maaaring mapansin mo na ang mga resulta na nakukuha mo kapag ginagamit ang camera na nakakonekta sa iyong IoT device ay hindi tumutugma sa inaasahan mo. Ang mga prediction ay hindi palaging kasing-accurate ng paggamit ng mga imahe na na-upload mula sa iyong computer. Ito ay dahil ang modelo ay sinanay sa ibang data kumpara sa ginagamit para sa mga prediction.

Upang makuha ang pinakamahusay na resulta para sa isang image classifier, gusto mong sanayin ang modelo gamit ang mga imahe na kasing katulad ng mga imahe na ginagamit para sa mga prediction hangga't maaari. Halimbawa, kung ginamit mo ang camera ng iyong telepono upang kumuha ng mga imahe para sa training, ang kalidad ng imahe, sharpness, at kulay ay magiging iba sa camera na nakakonekta sa isang IoT device.

![2 larawan ng saging, isang mababa ang resolution na may mahinang ilaw mula sa IoT device, at isang mataas ang resolution na may magandang ilaw mula sa telepono](../../../../../translated_images/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.tl.png)

Sa larawan sa itaas, ang larawan ng saging sa kaliwa ay kinunan gamit ang Raspberry Pi Camera, ang nasa kanan ay kinunan ng parehong saging sa parehong lokasyon gamit ang iPhone. May kapansin-pansing pagkakaiba sa kalidad - ang larawan ng iPhone ay mas malinaw, mas maliwanag ang kulay, at mas mataas ang contrast.

✅ Ano pa ang maaaring magdulot ng maling prediction sa mga imahe na kinunan ng iyong IoT device? Isipin ang kapaligiran kung saan maaaring gamitin ang IoT device, anong mga salik ang maaaring makaapekto sa imahe na kinunan?

Upang mapabuti ang modelo, maaari mo itong muling sanayin gamit ang mga imahe na kinunan mula sa IoT device.

### Gawain - pagbutihin ang modelo

1. I-classify ang maraming imahe ng parehong hinog at hilaw na prutas gamit ang iyong IoT device.

1. Sa Custom Vision portal, muling sanayin ang modelo gamit ang mga imahe sa *Predictions* tab.

    > ⚠️ Maaari mong tingnan ang [mga tagubilin para sa muling pagsasanay ng iyong classifier sa aralin 1 kung kinakailangan](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Kung ang iyong mga imahe ay mukhang napakaiba sa mga orihinal na ginamit para sa training, maaari mong tanggalin ang lahat ng orihinal na imahe sa pamamagitan ng pagpili sa mga ito sa *Training Images* tab at pagpili sa **Delete** button. Upang pumili ng imahe, ilipat ang iyong cursor sa ibabaw nito at lilitaw ang isang tick, piliin ang tick na iyon upang piliin o alisin ang pagpili sa imahe.

1. Sanayin ang bagong iteration ng modelo at i-publish ito gamit ang mga hakbang sa itaas.

1. I-update ang endpoint URL sa iyong code, at i-run muli ang app.

1. Ulitin ang mga hakbang na ito hanggang sa masiyahan ka sa mga resulta ng mga prediction.

---

## 🚀 Hamon

Gaano kalaki ang epekto ng resolution ng imahe o ilaw sa prediction?

Subukang baguhin ang resolution ng mga imahe sa iyong device code at tingnan kung may epekto ito sa kalidad ng mga imahe. Subukan din ang pagbabago ng ilaw.

Kung gagawa ka ng production device na ibebenta sa mga sakahan o pabrika, paano mo masisiguro na nagbibigay ito ng pare-parehong resulta sa lahat ng oras?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Review & Self Study

Sinanay mo ang iyong custom vision model gamit ang portal. Umaasa ito sa pagkakaroon ng mga imahe - at sa totoong mundo, maaaring hindi mo makuha ang training data na tumutugma sa kung ano ang kinukuha ng camera sa iyong device. Maaari mong malampasan ito sa pamamagitan ng pagsasanay nang direkta mula sa iyong device gamit ang training API, upang sanayin ang modelo gamit ang mga imahe na kinunan mula sa iyong IoT device.

* Basahin ang tungkol sa training API sa [using the Custom Vision SDK quick start](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Assignment

[Respond to classification results](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.