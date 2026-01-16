<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-27T20:54:02+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "tl"
}
-->
# Mag-train ng detector ng kalidad ng prutas

![Isang sketchnote overview ng aralin na ito](../../../../../translated_images/tl/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

Ang video na ito ay nagbibigay ng overview ng Azure Custom Vision service, isang serbisyo na tatalakayin sa aralin na ito.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 I-click ang imahe sa itaas para panoorin ang video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Panimula

Ang kamakailang pag-usbong ng Artificial Intelligence (AI) at Machine Learning (ML) ay nagbibigay ng malawak na kakayahan sa mga developer ngayon. Ang mga ML model ay maaaring i-train upang makilala ang iba't ibang bagay sa mga larawan, kabilang ang mga hilaw na prutas, at ito ay maaaring gamitin sa mga IoT device upang makatulong sa pag-aayos ng mga produkto habang inaani o sa panahon ng pagpoproseso sa mga pabrika o warehouse.

Sa aralin na ito, matututunan mo ang tungkol sa image classification - paggamit ng ML models upang makilala ang mga larawan ng iba't ibang bagay. Matututunan mo kung paano mag-train ng image classifier upang makilala ang prutas na maganda, at prutas na hindi maganda, tulad ng hilaw, sobrang hinog, may pasa, o bulok.

Sa aralin na ito, tatalakayin natin:

* [Paggamit ng AI at ML sa pag-aayos ng pagkain](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Image classification gamit ang Machine Learning](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Mag-train ng image classifier](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Subukan ang iyong image classifier](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [I-retrain ang iyong image classifier](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Paggamit ng AI at ML sa pag-aayos ng pagkain

Ang pagpapakain sa pandaigdigang populasyon ay mahirap, lalo na sa presyong abot-kaya para sa lahat. Isa sa pinakamalaking gastos ay ang labor, kaya't ang mga magsasaka ay lalong umaasa sa automation at mga tool tulad ng IoT upang mabawasan ang kanilang gastos sa labor. Ang pag-aani gamit ang kamay ay labor-intensive (at madalas na nakakapagod), at napapalitan na ng makinarya, lalo na sa mga mayayamang bansa. Sa kabila ng pagtitipid sa gastos ng paggamit ng makinarya sa pag-aani, may downside - ang kakayahang mag-ayos ng pagkain habang inaani.

Hindi lahat ng pananim ay sabay-sabay na hinog. Halimbawa, ang mga kamatis ay maaaring may mga berdeng bunga pa sa puno habang ang karamihan ay handa na para anihin. Bagama't sayang na anihin ang mga ito nang maaga, mas mura at mas madali para sa magsasaka na anihin ang lahat gamit ang makinarya at itapon ang mga hilaw na produkto pagkatapos.

✅ Tingnan ang iba't ibang prutas o gulay, alinman sa tumutubo malapit sa iyo sa mga sakahan o sa iyong hardin, o sa mga tindahan. Pare-pareho ba ang kanilang pagkahinog, o may nakikita kang pagkakaiba?

Ang pag-usbong ng automated harvesting ay inilipat ang pag-aayos ng produkto mula sa pag-aani patungo sa pabrika. Ang pagkain ay dumadaan sa mahabang conveyor belts na may mga team ng tao na pumipili sa mga produkto upang alisin ang anumang hindi pumasa sa kinakailangang pamantayan ng kalidad. Mas mura ang pag-aani dahil sa makinarya, ngunit may gastos pa rin sa manual na pag-aayos ng pagkain.

![Kapag natukoy ang pulang kamatis, magpapatuloy ito nang walang abala. Kapag natukoy ang berdeng kamatis, ito ay itinatapon sa basurahan gamit ang lever](../../../../../translated_images/tl/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.png)

Ang susunod na ebolusyon ay ang paggamit ng mga makina sa pag-aayos, alinman sa built-in sa harvester, o sa mga processing plants. Ang unang henerasyon ng mga makinang ito ay gumamit ng optical sensors upang matukoy ang mga kulay, na kumokontrol sa mga actuator upang itulak ang mga berdeng kamatis sa basurahan gamit ang mga lever o puffs ng hangin, habang ang mga pulang kamatis ay nagpapatuloy sa network ng conveyor belts.

Sa video na ito, habang bumabagsak ang mga kamatis mula sa isang conveyor belt patungo sa isa pa, natutukoy ang mga berdeng kamatis at itinatapon sa basurahan gamit ang mga lever.

✅ Anong mga kondisyon ang kakailanganin mo sa isang pabrika o sa isang sakahan para gumana nang maayos ang mga optical sensors na ito?

Ang pinakabagong ebolusyon ng mga sorting machine na ito ay gumagamit ng AI at ML, gamit ang mga model na na-train upang makilala ang magandang produkto mula sa hindi maganda, hindi lamang sa halatang pagkakaiba ng kulay tulad ng berdeng kamatis kumpara sa pula, kundi pati na rin sa mas banayad na pagkakaiba sa hitsura na maaaring magpahiwatig ng sakit o pasa.

## Image classification gamit ang Machine Learning

Ang tradisyunal na programming ay kung saan kinukuha mo ang data, ina-apply ang algorithm sa data, at nakakakuha ng output. Halimbawa, sa huling proyekto, kinuha mo ang GPS coordinates at isang geofence, ina-apply ang algorithm na ibinigay ng Azure Maps, at nakakuha ng resulta kung ang punto ay nasa loob o labas ng geofence. Mag-input ka ng mas maraming data, makakakuha ka ng mas maraming output.

![Ang tradisyunal na development ay kumukuha ng input at algorithm at nagbibigay ng output. Ang machine learning ay gumagamit ng input at output data upang mag-train ng model, at ang model na ito ay maaaring kumuha ng bagong input data upang makabuo ng bagong output](../../../../../translated_images/tl/traditional-vs-ml.5c20c169621fa539.webp)

Ang machine learning ay binabaliktad ito - nagsisimula ka sa data at kilalang outputs, at ang machine learning algorithm ay natututo mula sa data. Maaari mong kunin ang na-train na algorithm, na tinatawag na *machine learning model* o *model*, at mag-input ng bagong data upang makakuha ng bagong output.

> 🎓 Ang proseso ng machine learning algorithm na natututo mula sa data ay tinatawag na *training*. Ang inputs at kilalang outputs ay tinatawag na *training data*.

Halimbawa, maaari kang magbigay ng model ng milyon-milyong larawan ng hilaw na saging bilang input training data, na may training output na `hilaw`, at milyon-milyong larawan ng hinog na saging bilang training data na may output na `hinog`. Ang ML algorithm ay gagawa ng model base sa data na ito. Pagkatapos, magbibigay ka ng bagong larawan ng saging sa model na ito at ito ay magpe-predict kung ang bagong larawan ay hinog o hilaw na saging.

> 🎓 Ang resulta ng ML models ay tinatawag na *predictions*

![2 saging, isang hinog na may prediction na 99.7% hinog, 0.3% hilaw, at isang hilaw na may prediction na 1.4% hinog, 98.6% hilaw](../../../../../translated_images/tl/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.png)

Ang ML models ay hindi nagbibigay ng binary na sagot, sa halip nagbibigay ito ng probabilities. Halimbawa, ang isang model ay maaaring bigyan ng larawan ng saging at mag-predict ng `hinog` sa 99.7% at `hilaw` sa 0.3%. Ang iyong code ay pipili ng pinakamahusay na prediction at magdedesisyon na ang saging ay hinog.

Ang ML model na ginagamit upang matukoy ang mga larawan tulad nito ay tinatawag na *image classifier* - binibigyan ito ng mga labelled images, at pagkatapos ay nagka-classify ng mga bagong larawan base sa mga label na ito.

> 💁 Ito ay isang simpleng paliwanag, at mayroong maraming iba pang paraan upang mag-train ng models na hindi palaging nangangailangan ng labelled outputs, tulad ng unsupervised learning. Kung nais mong matuto pa tungkol sa ML, tingnan ang [ML for beginners, isang 24 na aralin na kurikulum sa Machine Learning](https://aka.ms/ML-beginners).

## Mag-train ng image classifier

Upang matagumpay na mag-train ng image classifier, kailangan mo ng milyon-milyong larawan. Sa kabutihang palad, kapag mayroon ka nang image classifier na na-train sa milyon-milyon o bilyon-bilyong assorted images, maaari mo itong i-reuse at i-retrain gamit ang maliit na set ng images at makakuha ng magagandang resulta, gamit ang proseso na tinatawag na *transfer learning*.

> 🎓 Ang transfer learning ay kung saan inililipat mo ang natutunan mula sa isang existing ML model patungo sa bagong model base sa bagong data.

Kapag ang isang image classifier ay na-train para sa malawak na iba't ibang larawan, ang mga internal nito ay mahusay sa pagkilala ng mga hugis, kulay, at pattern. Ang transfer learning ay nagbibigay-daan sa model na gamitin ang natutunan nito sa pagkilala ng mga bahagi ng larawan, at gamitin ito upang makilala ang mga bagong larawan.

![Kapag kaya mong kilalanin ang mga hugis, maaari itong ilagay sa iba't ibang configuration upang makabuo ng bangka o pusa](../../../../../translated_images/tl/shapes-to-images.1a309f0ea88dd66f.webp)

Maaari mong isipin ito na parang mga libro ng hugis para sa mga bata, kung saan kapag kaya mong kilalanin ang semi-circle, rectangle, at triangle, maaari mong kilalanin ang isang sailboat o pusa depende sa configuration ng mga hugis na ito. Ang image classifier ay maaaring kilalanin ang mga hugis, at ang transfer learning ang nagtuturo dito kung anong kombinasyon ang bumubuo ng bangka o pusa - o hinog na saging.

Mayroong malawak na hanay ng mga tool na makakatulong sa iyo na gawin ito, kabilang ang mga cloud-based services na makakatulong sa iyo na mag-train ng iyong model, pagkatapos ay gamitin ito sa pamamagitan ng web APIs.

> 💁 Ang pag-train ng mga model na ito ay nangangailangan ng maraming computer power, karaniwang sa pamamagitan ng Graphics Processing Units, o GPUs. Ang parehong specialized hardware na nagpapaganda ng mga laro sa iyong Xbox ay maaari ring gamitin upang mag-train ng machine learning models. Sa pamamagitan ng paggamit ng cloud, maaari kang magrenta ng oras sa mga makapangyarihang computer na may GPUs upang mag-train ng mga model na ito, na nagbibigay sa iyo ng access sa computing power na kailangan mo, para lamang sa oras na kailangan mo ito.

## Custom Vision

Ang Custom Vision ay isang cloud-based tool para sa pag-train ng image classifiers. Pinapayagan ka nitong mag-train ng classifier gamit lamang ang maliit na bilang ng mga larawan. Maaari kang mag-upload ng mga larawan sa pamamagitan ng web portal, web API, o SDK, na binibigyan ang bawat larawan ng *tag* na may classification ng larawan. Pagkatapos ay i-train mo ang model, at subukan ito upang makita kung gaano ito kahusay. Kapag nasiyahan ka na sa model, maaari mong i-publish ang mga bersyon nito na maaaring ma-access sa pamamagitan ng web API o SDK.

![Ang Azure Custom Vision logo](../../../../../translated_images/tl/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.png)

> 💁 Maaari kang mag-train ng custom vision model gamit ang hindi bababa sa 5 larawan bawat classification, ngunit mas marami ay mas maganda. Mas maganda ang resulta kung may hindi bababa sa 30 larawan.

Ang Custom Vision ay bahagi ng hanay ng mga AI tools mula sa Microsoft na tinatawag na Cognitive Services. Ito ay mga AI tools na maaaring gamitin alinman nang walang anumang training, o may maliit na training. Kasama dito ang speech recognition at translation, language understanding, at image analysis. Available ang mga ito na may free tier bilang mga serbisyo sa Azure.

> 💁 Ang free tier ay higit pa sa sapat upang lumikha ng model, i-train ito, pagkatapos ay gamitin ito para sa development work. Maaari mong basahin ang tungkol sa mga limitasyon ng free tier sa [Custom Vision Limits and quotas page sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Gawain - gumawa ng cognitive services resource

Upang magamit ang Custom Vision, kailangan mo munang gumawa ng dalawang cognitive services resources sa Azure gamit ang Azure CLI, isa para sa Custom Vision training at isa para sa Custom Vision prediction.

1. Gumawa ng Resource Group para sa proyektong ito na tinatawag na `fruit-quality-detector`

1. Gamitin ang sumusunod na command upang gumawa ng libreng Custom Vision training resource:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Palitan ang `<location>` ng lokasyon na ginamit mo noong gumawa ng Resource Group.

    Ito ay gagawa ng Custom Vision training resource sa iyong Resource Group. Tatawagin itong `fruit-quality-detector-training` at gagamit ng `F0` sku, na siyang free tier. Ang `--yes` na opsyon ay nangangahulugang sumasang-ayon ka sa mga terms and conditions ng cognitive services.

> 💁 Gamitin ang `S0` sku kung mayroon ka nang libreng account na gumagamit ng alinman sa Cognitive Services.

1. Gamitin ang sumusunod na command upang gumawa ng libreng Custom Vision prediction resource:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Palitan ang `<location>` ng lokasyon na ginamit mo noong gumawa ng Resource Group.

    Ito ay gagawa ng Custom Vision prediction resource sa iyong Resource Group. Tatawagin itong `fruit-quality-detector-prediction` at gagamit ng `F0` sku, na siyang free tier. Ang `--yes` na opsyon ay nangangahulugang sumasang-ayon ka sa mga terms and conditions ng cognitive services.

### Gawain - gumawa ng image classifier project

1. I-launch ang Custom Vision portal sa [CustomVision.ai](https://customvision.ai), at mag-sign in gamit ang Microsoft account na ginamit mo para sa iyong Azure account.

1. Sundin ang [create a new Project section ng build a classifier quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) upang gumawa ng bagong Custom Vision project. Ang UI ay maaaring magbago at ang mga docs na ito ang palaging pinaka-up-to-date na reference.

    Tawagin ang iyong project na `fruit-quality-detector`.

    Kapag ginawa mo ang iyong project, siguraduhing gamitin ang `fruit-quality-detector-training` resource na ginawa mo kanina. Gumamit ng *Classification* project type, isang *Multiclass* classification type, at ang *Food* domain.

    ![Ang mga settings para sa custom vision project na may pangalan na fruit-quality-detector, walang description, ang resource na nakatakda sa fruit-quality-detector-training, ang project type na nakatakda sa classification, ang classification types na nakatakda sa multi class at ang domains na nakatakda sa food](../../../../../translated_images/tl/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.png)

✅ Maglaan ng oras upang galugarin ang Custom Vision UI para sa iyong image classifier.

### Gawain - i-train ang iyong image classifier project

Upang mag-train ng image classifier, kakailanganin mo ng maraming larawan ng prutas, parehong maganda at hindi maganda ang kalidad upang i-tag bilang maganda at hindi maganda, tulad ng hinog at sobrang hinog na saging.
💁 Ang mga classifier na ito ay maaaring mag-uri ng mga larawan ng kahit ano, kaya kung wala kang prutas na may iba't ibang kalidad, maaari kang gumamit ng dalawang magkaibang uri ng prutas, o mga pusa at aso!
Ideally, ang bawat larawan ay dapat ipakita lamang ang prutas, na may pare-parehong background o iba't ibang klase ng background. Siguraduhing walang bagay sa background na nagpapakita kung hinog o hilaw ang prutas.

> 💁 Mahalaga na walang partikular na background o mga bagay na hindi kaugnay sa bagay na ikinuklasipika para sa bawat tag. Kung hindi, maaaring magklasipika ang classifier base sa background. May isang classifier para sa skin cancer na sinanay gamit ang mga larawan ng normal at cancerous na nunal. Ang mga cancerous na nunal ay may mga ruler sa tabi upang sukatin ang laki. Lumabas na halos 100% tama ang classifier sa pagtukoy ng ruler sa mga larawan, hindi sa cancerous na nunal.

Ang mga image classifier ay tumatakbo sa napakababang resolusyon. Halimbawa, ang Custom Vision ay maaaring tumanggap ng mga training at prediction images hanggang 10240x10240, ngunit sinasanay at pinapatakbo ang modelo sa mga larawan na 227x227. Ang mas malalaking larawan ay pinaliliit sa sukat na ito, kaya siguraduhing ang bagay na iyong ikinuklasipika ay sumasakop sa malaking bahagi ng larawan. Kung hindi, maaaring masyadong maliit ito sa mas maliit na larawang ginagamit ng classifier.

1. Magtipon ng mga larawan para sa iyong classifier. Kakailanganin mo ng hindi bababa sa 5 larawan para sa bawat label upang sanayin ang classifier, ngunit mas marami, mas mabuti. Kakailanganin mo rin ng ilang karagdagang larawan upang subukan ang classifier. Ang mga larawang ito ay dapat iba-iba ngunit ng parehong bagay. Halimbawa:

    * Gamit ang 2 hinog na saging, kumuha ng ilang larawan ng bawat isa mula sa iba't ibang anggulo, kumuha ng hindi bababa sa 7 larawan (5 para sa training, 2 para sa testing), ngunit mas mainam kung mas marami.

        ![Mga larawan ng 2 magkaibang saging](../../../../../translated_images/tl/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.png)

    * Ulitin ang parehong proseso gamit ang 2 hilaw na saging.

    Dapat kang magkaroon ng hindi bababa sa 10 training images, na may hindi bababa sa 5 hinog at 5 hilaw, at 4 na testing images, 2 hinog, 2 hilaw. Ang iyong mga larawan ay dapat nasa png o jpeg format, mas maliit sa 6MB. Kung gagamit ka ng iPhone halimbawa, maaaring mataas ang resolusyon ng mga larawan (HEIC format), kaya kailangang i-convert at posibleng paliitin. Mas maraming larawan, mas mabuti, at dapat magkapareho ang bilang ng hinog at hilaw.

    Kung wala kang parehong hinog at hilaw na prutas, maaari kang gumamit ng ibang prutas o anumang dalawang bagay na mayroon ka. Maaari ka ring makahanap ng mga halimbawa ng larawan sa [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) folder ng hinog at hilaw na saging na maaari mong gamitin.

1. Sundin ang [upload and tag images section ng build a classifier quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) upang i-upload ang iyong mga training images. I-tag ang hinog na prutas bilang `ripe`, at ang hilaw na prutas bilang `unripe`.

    ![Ang upload dialogs na nagpapakita ng pag-upload ng mga larawan ng hinog at hilaw na saging](../../../../../translated_images/tl/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.png)

1. Sundin ang [train the classifier section ng build a classifier quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) upang sanayin ang image classifier gamit ang iyong mga na-upload na larawan.

    Bibigyan ka ng opsyon para sa uri ng training. Piliin ang **Quick Training**.

Ang classifier ay magsisimulang mag-train. Aabutin ito ng ilang minuto upang makumpleto ang training.

> 🍌 Kung magpasya kang kainin ang iyong prutas habang nagte-train ang classifier, siguraduhing mayroon kang sapat na larawan para sa testing!

## Subukan ang iyong image classifier

Kapag natapos ang training ng iyong classifier, maaari mo itong subukan gamit ang bagong larawan upang maiklasipika.

### Gawain - subukan ang iyong image classifier

1. Sundin ang [test your model documentation sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) upang subukan ang iyong image classifier. Gamitin ang mga testing images na ginawa mo kanina, hindi ang mga larawang ginamit mo para sa training.

    ![Isang hilaw na saging na na-predict bilang hilaw na may 98.9% probability, hinog na may 1.1% probability](../../../../../translated_images/tl/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.png)

1. Subukan ang lahat ng testing images na mayroon ka at obserbahan ang mga probabilities.

## I-retrain ang iyong image classifier

Kapag sinubukan mo ang iyong classifier, maaaring hindi nito maibigay ang mga resulta na iyong inaasahan. Ang mga image classifier ay gumagamit ng machine learning upang gumawa ng mga hula tungkol sa kung ano ang nasa larawan, base sa probabilities na ang partikular na mga katangian ng larawan ay tumutugma sa isang partikular na label. Hindi nito naiintindihan kung ano ang nasa larawan - hindi nito alam kung ano ang saging o naiintindihan kung ano ang nagpapakilala sa saging mula sa bangka. Maaari mong pagbutihin ang iyong classifier sa pamamagitan ng muling pagsasanay gamit ang mga larawang mali ang resulta.

Sa tuwing gagawa ka ng prediction gamit ang quick test option, ang larawan at mga resulta ay naiimbak. Maaari mong gamitin ang mga larawang ito upang muling sanayin ang iyong modelo.

### Gawain - i-retrain ang iyong image classifier

1. Sundin ang [use the predicted image for training documentation sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) upang muling sanayin ang iyong modelo, gamit ang tamang tag para sa bawat larawan.

1. Kapag na-retrain na ang iyong modelo, subukan ito gamit ang mga bagong larawan.

---

## 🚀 Hamon

Ano sa tingin mo ang mangyayari kung gumamit ka ng larawan ng strawberry sa isang modelong sinanay sa saging, o larawan ng inflatable na saging, o tao na nakasuot ng banana suit, o kahit isang dilaw na cartoon character tulad ng isang tauhan mula sa Simpsons?

Subukan ito at tingnan ang mga prediction. Maaari kang maghanap ng mga larawan gamit ang [Bing Image search](https://www.bing.com/images/trending).

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Review at Pag-aaral sa Sarili

* Kapag sinanay mo ang iyong classifier, makikita mo ang mga halaga para sa *Precision*, *Recall*, at *AP* na nagre-rate sa modelong ginawa. Basahin kung ano ang mga halagang ito gamit ang [evaluate the classifier section ng build a classifier quickstart sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Basahin kung paano pagbutihin ang iyong classifier mula sa [how to improve your Custom Vision model sa Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Takdang Aralin

[Sanayin ang iyong classifier para sa iba't ibang prutas at gulay](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.