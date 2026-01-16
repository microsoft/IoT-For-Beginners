<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-27T20:48:57+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "tl"
}
-->
# Mag-train ng stock detector

![Isang sketchnote overview ng araling ito](../../../../../translated_images/tl/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

Ang video na ito ay nagbibigay ng overview ng Object Detection gamit ang Azure Custom Vision service, isang serbisyo na tatalakayin sa araling ito.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 I-click ang imahe sa itaas para panoorin ang video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Panimula

Sa nakaraang proyekto, gumamit ka ng AI upang mag-train ng isang image classifier - isang modelo na maaaring magsabi kung ang isang imahe ay naglalaman ng isang bagay, tulad ng hinog na prutas o hindi hinog na prutas. Ang isa pang uri ng AI model na maaaring gamitin sa mga imahe ay object detection. Ang mga modelong ito ay hindi nagka-classify ng imahe gamit ang mga tag, sa halip ay sinasanay sila upang makilala ang mga bagay, at mahanap ang mga ito sa mga imahe, hindi lamang natutukoy kung ang imahe ay naroroon, kundi natutukoy kung saan sa imahe ito naroroon. Pinapayagan ka nitong bilangin ang mga bagay sa mga imahe.

Sa araling ito, matututunan mo ang tungkol sa object detection, kabilang kung paano ito magagamit sa retail. Matututunan mo rin kung paano mag-train ng object detector sa cloud.

Sa araling ito, tatalakayin natin:

* [Object detection](../../../../../5-retail/lessons/1-train-stock-detector)
* [Paggamit ng object detection sa retail](../../../../../5-retail/lessons/1-train-stock-detector)
* [Mag-train ng object detector](../../../../../5-retail/lessons/1-train-stock-detector)
* [Subukan ang iyong object detector](../../../../../5-retail/lessons/1-train-stock-detector)
* [I-retrain ang iyong object detector](../../../../../5-retail/lessons/1-train-stock-detector)

## Object detection

Ang object detection ay tumutukoy sa pag-detect ng mga bagay sa mga imahe gamit ang AI. Hindi tulad ng image classifier na na-train mo sa nakaraang proyekto, ang object detection ay hindi tungkol sa pag-predict ng pinakamahusay na tag para sa buong imahe, kundi sa paghahanap ng isa o higit pang mga bagay sa isang imahe.

### Object detection vs image classification

Ang image classification ay tungkol sa pag-classify ng buong imahe - ano ang mga posibilidad na ang buong imahe ay tumutugma sa bawat tag. Makakakuha ka ng mga probabilities para sa bawat tag na ginamit upang i-train ang modelo.

![Image classification ng cashew nuts at tomato paste](../../../../../translated_images/tl/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

Sa halimbawa sa itaas, dalawang imahe ang na-classify gamit ang isang modelong na-train upang i-classify ang mga tub ng cashew nuts o mga lata ng tomato paste. Ang unang imahe ay isang tub ng cashew nuts, at may dalawang resulta mula sa image classifier:

| Tag            | Probability |
| -------------- | ----------: |
| `cashew nuts`  | 98.4%       |
| `tomato paste` | 1.6%        |

Ang pangalawang imahe ay isang lata ng tomato paste, at ang mga resulta ay:

| Tag            | Probability |
| -------------- | ----------: |
| `cashew nuts`  | 0.7%        |
| `tomato paste` | 99.3%       |

Maaari mong gamitin ang mga value na ito gamit ang threshold percentage upang i-predict kung ano ang nasa imahe. Ngunit paano kung ang isang imahe ay naglalaman ng maraming lata ng tomato paste, o parehong cashew nuts at tomato paste? Malamang na hindi ibibigay ng mga resulta ang gusto mo. Dito pumapasok ang object detection.

Ang object detection ay tumutukoy sa pag-train ng isang modelo upang makilala ang mga bagay. Sa halip na bigyan ito ng mga imahe na naglalaman ng bagay at sabihin na ang bawat imahe ay isang tag o iba pa, i-highlight mo ang bahagi ng imahe na naglalaman ng partikular na bagay, at i-tag iyon. Maaari kang mag-tag ng isang bagay sa isang imahe o marami. Sa ganitong paraan, natututo ang modelo kung ano ang hitsura ng mismong bagay, hindi lamang kung ano ang hitsura ng mga imahe na naglalaman ng bagay.

Kapag ginamit mo ito upang mag-predict ng mga imahe, sa halip na makakuha ng listahan ng mga tag at porsyento, makakakuha ka ng listahan ng mga na-detect na bagay, kasama ang kanilang bounding box at ang posibilidad na ang bagay ay tumutugma sa na-assign na tag.

> 🎓 *Bounding boxes* ay ang mga kahon sa paligid ng isang bagay.

![Object detection ng cashew nuts at tomato paste](../../../../../translated_images/tl/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

Ang imahe sa itaas ay naglalaman ng parehong tub ng cashew nuts at tatlong lata ng tomato paste. Na-detect ng object detector ang cashew nuts, na nagbalik ng bounding box na naglalaman ng cashew nuts kasama ang porsyento ng posibilidad na ang bounding box ay naglalaman ng bagay, sa kasong ito 97.6%. Na-detect din ng object detector ang tatlong lata ng tomato paste, at nagbibigay ng tatlong magkakahiwalay na bounding boxes, isa para sa bawat na-detect na lata, at bawat isa ay may porsyento ng posibilidad na ang bounding box ay naglalaman ng lata ng tomato paste.

✅ Mag-isip ng ilang iba't ibang sitwasyon kung saan maaaring gusto mong gumamit ng mga image-based AI models. Alin sa mga ito ang mangangailangan ng classification, at alin ang mangangailangan ng object detection?

### Paano gumagana ang object detection

Ang object detection ay gumagamit ng mga kumplikadong ML models. Ang mga modelong ito ay gumagana sa pamamagitan ng paghahati ng imahe sa maraming cells, pagkatapos ay sinusuri kung ang sentro ng bounding box ay ang sentro ng isang imahe na tumutugma sa isa sa mga imahe na ginamit upang i-train ang modelo. Maaari mong isipin ito na parang nagpapatakbo ng isang image classifier sa iba't ibang bahagi ng imahe upang maghanap ng mga tugma.

> 💁 Ito ay isang labis na pag-simplify. Maraming mga teknik para sa object detection, at maaari mong basahin ang higit pa tungkol sa mga ito sa [Object detection page sa Wikipedia](https://wikipedia.org/wiki/Object_detection).

Mayroong iba't ibang mga modelo na maaaring gumawa ng object detection. Ang isa sa mga kilalang modelo ay [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), na napakabilis at maaaring mag-detect ng 20 iba't ibang klase ng mga bagay, tulad ng tao, aso, bote, at kotse.

✅ Basahin ang tungkol sa YOLO model sa [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Ang mga object detection models ay maaaring ma-retrain gamit ang transfer learning upang mag-detect ng custom na mga bagay.

## Paggamit ng object detection sa retail

Ang object detection ay may maraming gamit sa retail. Ilan sa mga ito ay:

* **Pag-check at pagbibilang ng stock** - pagkilala kung kailan mababa ang stock sa mga shelves. Kung mababa ang stock, maaaring magpadala ng mga notification sa mga staff o robot upang mag-restock ng shelves.
* **Pag-detect ng mask** - sa mga tindahan na may mask policies sa panahon ng mga pampublikong health events, maaaring makilala ng object detection ang mga tao na may suot na mask at ang mga wala.
* **Automated billing** - pag-detect ng mga item na kinuha mula sa mga shelves sa automated stores at pagbibigay ng tamang bayarin sa mga customer.
* **Pag-detect ng hazard** - pagkilala sa mga sirang bagay sa sahig, o mga natapon na likido, at pag-alerto sa mga cleaning crew.

✅ Mag-research: Ano pa ang ibang mga gamit ng object detection sa retail?

## Mag-train ng object detector

Maaari kang mag-train ng object detector gamit ang Custom Vision, sa katulad na paraan kung paano ka nag-train ng isang image classifier.

### Gawain - gumawa ng object detector

1. Gumawa ng Resource Group para sa proyektong ito na tinatawag na `stock-detector`

1. Gumawa ng libreng Custom Vision training resource, at isang libreng Custom Vision prediction resource sa `stock-detector` resource group. Pangalanan ang mga ito `stock-detector-training` at `stock-detector-prediction`.

    > 💁 Maaari ka lamang magkaroon ng isang libreng training at prediction resource, kaya siguraduhing nalinis mo ang iyong proyekto mula sa mga naunang aralin.

    > ⚠️ Maaari mong tingnan ang [mga instruksyon para sa paggawa ng training at prediction resources mula sa project 4, lesson 1 kung kinakailangan](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. I-launch ang Custom Vision portal sa [CustomVision.ai](https://customvision.ai), at mag-sign in gamit ang Microsoft account na ginamit mo para sa iyong Azure account.

1. Sundin ang [Create a new Project section ng Build an object detector quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) upang gumawa ng bagong Custom Vision project. Ang UI ay maaaring magbago at ang mga docs na ito ay palaging ang pinaka-up-to-date na reference.

    Tawagin ang iyong proyekto na `stock-detector`.

    Kapag ginawa mo ang iyong proyekto, siguraduhing gamitin ang `stock-detector-training` resource na ginawa mo kanina. Gamitin ang *Object Detection* project type, at ang *Products on Shelves* domain.

    ![Ang mga setting para sa custom vision project na may pangalan na fruit-quality-detector, walang description, ang resource ay nakatakda sa fruit-quality-detector-training, ang project type ay nakatakda sa classification, ang classification types ay nakatakda sa multi class at ang domains ay nakatakda sa food](../../../../../translated_images/tl/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ Ang products on shelves domain ay partikular na nakatuon para sa pag-detect ng stock sa mga store shelves. Basahin ang higit pa tungkol sa iba't ibang domains sa [Select a domain documentation sa Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Maglaan ng oras upang galugarin ang Custom Vision UI para sa iyong object detector.

### Gawain - i-train ang iyong object detector

Upang i-train ang iyong modelo, kakailanganin mo ng set ng mga imahe na naglalaman ng mga bagay na nais mong i-detect.

1. Magtipon ng mga imahe na naglalaman ng bagay na i-detect. Kakailanganin mo ng hindi bababa sa 15 imahe na naglalaman ng bawat bagay na i-detect mula sa iba't ibang anggulo at sa iba't ibang kondisyon ng ilaw, ngunit mas marami, mas maganda. Ang object detector na ito ay gumagamit ng *Products on shelves* domain, kaya subukang i-set up ang mga bagay na parang nasa store shelf. Kakailanganin mo rin ng ilang mga imahe upang i-test ang modelo. Kung ikaw ay nag-detect ng higit sa isang bagay, kakailanganin mo ng ilang testing images na naglalaman ng lahat ng mga bagay.

    > 💁 Ang mga imahe na may maraming iba't ibang bagay ay binibilang patungo sa 15 image minimum para sa lahat ng mga bagay sa imahe.

    Ang iyong mga imahe ay dapat png o jpegs, mas maliit sa 6MB. Kung ginawa mo ang mga ito gamit ang isang iPhone halimbawa, maaaring sila ay high-resolution HEIC images, kaya kakailanganin silang i-convert at posibleng paliitin. Mas marami ang mga imahe, mas maganda, at dapat kang magkaroon ng katulad na bilang ng hinog at hindi hinog.

    Ang modelo ay dinisenyo para sa mga produkto sa shelves, kaya subukang kunan ng larawan ang mga bagay sa shelves.

    Maaari kang makahanap ng ilang mga halimbawa ng imahe na maaari mong gamitin sa [images](../../../../../5-retail/lessons/1-train-stock-detector/images) folder ng cashew nuts at tomato paste na maaari mong gamitin.

1. Sundin ang [Upload and tag images section ng Build an object detector quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) upang i-upload ang iyong mga training images. Gumawa ng mga kaugnay na tag depende sa mga uri ng mga bagay na nais mong i-detect.

    ![Ang upload dialogs na nagpapakita ng pag-upload ng ripe at unripe banana pictures](../../../../../translated_images/tl/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    Kapag nag-draw ka ng bounding boxes para sa mga bagay, panatilihin itong masikip sa paligid ng bagay. Maaaring tumagal ng ilang oras upang i-outline ang lahat ng mga imahe, ngunit ang tool ay mag-detect kung ano ang sa tingin nito ay ang mga bounding boxes, na ginagawang mas mabilis.

    ![Pag-tag ng ilang tomato paste](../../../../../translated_images/tl/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 Kung mayroon kang higit sa 15 imahe para sa bawat bagay, maaari kang mag-train pagkatapos ng 15 at gamitin ang **Suggested tags** feature. Gagamitin nito ang na-train na modelo upang i-detect ang mga bagay sa untagged image. Maaari mong kumpirmahin ang mga na-detect na bagay, o tanggihan at muling i-draw ang mga bounding boxes. Ito ay maaaring makatipid ng *maraming* oras.

1. Sundin ang [Train the detector section ng Build an object detector quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) upang i-train ang object detector sa iyong mga tagged images.

    Bibigyan ka ng pagpipilian ng training type. Piliin ang **Quick Training**.

Ang object detector ay magta-train. Aabutin ng ilang minuto para makumpleto ang training.

## Subukan ang iyong object detector

Kapag na-train na ang iyong object detector, maaari mo itong subukan sa pamamagitan ng pagbibigay ng mga bagong imahe upang i-detect ang mga bagay.

### Gawain - subukan ang iyong object detector

1. Gamitin ang **Quick Test** button upang i-upload ang mga testing images at i-verify kung na-detect ang mga bagay. Gamitin ang mga testing images na ginawa mo kanina, hindi ang anumang mga imahe na ginamit mo para sa training.

    ![3 lata ng tomato paste na na-detect na may probabilities na 38%, 35.5% at 34.6%](../../../../../translated_images/tl/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.png)

1. Subukan ang lahat ng testing images na mayroon ka at obserbahan ang mga probabilities.

## I-retrain ang iyong object detector

Kapag sinubukan mo ang iyong object detector, maaaring hindi ito magbigay ng mga resulta na inaasahan mo, katulad ng sa mga image classifiers sa nakaraang proyekto. Maaari mong pagbutihin ang iyong object detector sa pamamagitan ng pag-retrain nito gamit ang mga imahe na mali ang resulta.

Tuwing gagawa ka ng prediction gamit ang quick test option, ang imahe at mga resulta ay naka-store. Maaari mong gamitin ang mga imahe na ito upang i-retrain ang iyong modelo.

1. Gamitin ang **Predictions** tab upang hanapin ang mga imahe na ginamit mo para sa testing.

1. Kumpirmahin ang anumang tamang detections, tanggalin ang mga maling resulta, at idagdag ang anumang nawawalang mga bagay.

1. I-retrain at muling i-test ang modelo.

---

## 🚀 Hamon

Ano ang mangyayari kung ginamit mo ang object detector sa mga item na magkamukha, tulad ng parehong brand ng lata ng tomato paste at chopped tomatoes?

Kung mayroon kang mga item na magkamukha, subukan ito sa pamamagitan ng pagdaragdag ng mga imahe ng mga ito sa iyong object detector.

## Post-lecture quiz
[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Review & Pag-aaral sa Sarili

* Kapag sinanay mo ang iyong object detector, makikita mo ang mga halaga para sa *Precision*, *Recall*, at *mAP* na nagre-rate sa modelong ginawa. Magbasa tungkol sa kung ano ang mga halagang ito gamit ang [Evaluate the detector section ng Build an object detector quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Magbasa pa tungkol sa object detection sa [Object detection page sa Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Takdang Aralin

[Compare domains](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.