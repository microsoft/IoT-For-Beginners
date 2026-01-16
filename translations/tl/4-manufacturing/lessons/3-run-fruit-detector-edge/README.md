<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T21:10:45+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "tl"
}
-->
# Patakbuhin ang iyong fruit detector sa edge

![Isang sketchnote overview ng araling ito](../../../../../translated_images/tl/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

Ang video na ito ay nagbibigay ng overview kung paano patakbuhin ang image classifiers sa mga IoT device, ang paksang tatalakayin sa araling ito.

[![Custom Vision AI sa Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Panimula

Sa nakaraang aralin, ginamit mo ang iyong image classifier upang tukuyin ang hinog at hilaw na prutas, gamit ang isang imahe na kinunan ng camera sa iyong IoT device at ipinadala ito sa internet patungo sa cloud service. Ang mga tawag na ito ay nangangailangan ng oras, may gastos, at depende sa uri ng data ng imahe na iyong ginagamit, maaaring may mga implikasyon sa privacy.

Sa araling ito, matututuhan mo kung paano patakbuhin ang machine learning (ML) models sa edge - sa mga IoT device na tumatakbo sa iyong sariling network sa halip na sa cloud. Malalaman mo ang mga benepisyo at limitasyon ng edge computing kumpara sa cloud computing, kung paano i-deploy ang iyong AI model sa edge, at kung paano ito ma-access mula sa iyong IoT device.

Sa araling ito, tatalakayin natin ang:

* [Edge computing](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Magrehistro ng IoT Edge device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [I-set up ang IoT Edge device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [I-export ang iyong modelo](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Ihanda ang iyong container para sa deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [I-deploy ang iyong container](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Gamitin ang iyong IoT Edge device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Edge computing

Ang edge computing ay tumutukoy sa pagkakaroon ng mga computer na nagpoproseso ng IoT data nang mas malapit hangga't maaari sa lugar kung saan ito nabuo. Sa halip na gawin ang pagpoproseso sa cloud, ito ay inilipat sa edge ng cloud - sa iyong internal network.

![Isang diagram ng arkitektura na nagpapakita ng internet services sa cloud at IoT devices sa lokal na network](../../../../../translated_images/tl/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

Sa mga nakaraang aralin, ang iyong mga device ay nangongolekta ng data at ipinapadala ito sa cloud upang ma-analisa, gamit ang serverless functions o AI models sa cloud.

![Isang diagram ng arkitektura na nagpapakita ng IoT devices sa lokal na network na kumokonekta sa edge devices, at ang mga edge devices na ito ay kumokonekta sa cloud](../../../../../translated_images/tl/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Ang edge computing ay naglalaman ng paglipat ng ilang cloud services mula sa cloud patungo sa mga computer na tumatakbo sa parehong network ng mga IoT device, at nakikipag-ugnayan lamang sa cloud kung kinakailangan. Halimbawa, maaari kang magpatakbo ng AI models sa edge devices upang suriin ang hinog na prutas, at ipadala lamang ang analytics pabalik sa cloud, tulad ng bilang ng hinog na prutas kumpara sa hilaw.

✅ Pag-isipan ang mga IoT application na iyong nagawa sa ngayon. Alin sa mga bahagi nito ang maaaring ilipat sa edge?

### Mga Benepisyo

Ang mga benepisyo ng edge computing ay:

1. **Bilis** - ang edge computing ay perpekto para sa time-sensitive na data dahil ang mga aksyon ay ginagawa sa parehong network ng device, sa halip na magpadala ng tawag sa internet. Nagbibigay ito ng mas mataas na bilis dahil ang internal networks ay maaaring tumakbo nang mas mabilis kaysa sa internet connections, at ang data ay naglalakbay ng mas maikling distansya.

    > 💁 Kahit na ang optical cables ay ginagamit para sa internet connections na nagpapahintulot sa data na maglakbay sa bilis ng liwanag, ang data ay maaaring tumagal ng oras upang maglakbay sa buong mundo patungo sa cloud providers. Halimbawa, kung nagpapadala ka ng data mula sa Europa patungo sa cloud services sa US, aabutin ng hindi bababa sa 28ms para sa data na tumawid sa Atlantic sa isang optical cable, at hindi pa kasama ang oras na kinakailangan upang makarating ang data sa transatlantic cable, mag-convert mula electrical patungo sa light signals at pabalik muli sa kabilang panig, at mula sa optical cable patungo sa cloud provider.

    Ang edge computing ay nangangailangan din ng mas kaunting network traffic, na binabawasan ang panganib ng pagbagal ng data dahil sa congestion sa limitadong bandwidth ng internet connection.

1. **Remote accessibility** - ang edge compute ay gumagana kahit na may limitadong connectivity o walang connectivity, o kung ang connectivity ay masyadong mahal upang gamitin nang tuloy-tuloy. Halimbawa, sa mga lugar ng humanitarian disaster kung saan limitado ang imprastraktura, o sa mga umuunlad na bansa.

1. **Mas mababang gastos** - ang paggawa ng data collection, storage, analysis, at pag-trigger ng actions sa edge device ay binabawasan ang paggamit ng cloud services na maaaring magpababa ng kabuuang gastos ng iyong IoT application. Kamakailan lamang, tumaas ang mga device na idinisenyo para sa edge computing, tulad ng AI accelerator boards gaya ng [Jetson Nano mula sa NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), na maaaring magpatakbo ng AI workloads gamit ang GPU-based hardware sa mga device na mas mababa sa US$100 ang halaga.

1. **Privacy at seguridad** - sa edge compute, ang data ay nananatili sa iyong network at hindi ina-upload sa cloud. Mas pinipili ito para sa sensitibo at personal na impormasyon, lalo na dahil ang data ay hindi kailangang iimbak pagkatapos ma-analisa, na lubos na binabawasan ang panganib ng data leaks. Halimbawa nito ay ang medical data at security camera footage.

1. **Pag-handle ng insecure devices** - kung mayroon kang mga device na may kilalang security flaws na ayaw mong direktang ikonekta sa iyong network o sa internet, maaari mo itong ikonekta sa isang hiwalay na network patungo sa isang gateway IoT Edge device. Ang edge device na ito ay maaari ring magkaroon ng koneksyon sa iyong mas malawak na network o sa internet, at pamahalaan ang daloy ng data pabalik at pasulong.

1. **Suporta para sa mga hindi compatible na device** - kung mayroon kang mga device na hindi maaaring kumonekta sa IoT Hub, halimbawa mga device na maaari lamang kumonekta gamit ang HTTP connections o mga device na may Bluetooth lamang, maaari mong gamitin ang isang IoT edge device bilang isang gateway device, na nagpapasa ng mga mensahe patungo sa IoT Hub.

✅ Mag-research: Ano pang ibang benepisyo ang maaaring mayroon sa edge computing?

### Mga Limitasyon

May mga limitasyon ang edge computing, kung saan maaaring mas mainam ang cloud:

1. **Saklaw at flexibility** - ang cloud computing ay maaaring mag-adjust sa network at data needs sa real-time sa pamamagitan ng pagdaragdag o pagbawas ng mga server at iba pang resources. Ang pagdaragdag ng mas maraming edge computers ay nangangailangan ng manual na pagdaragdag ng mga device.

1. **Reliability at resiliency** - ang cloud computing ay nagbibigay ng maraming server na madalas nasa iba't ibang lokasyon para sa redundancy at disaster recovery. Ang pagkakaroon ng parehong antas ng redundancy sa edge ay nangangailangan ng malaking investment at maraming configuration work.

1. **Maintenance** - ang mga cloud service provider ay nagbibigay ng system maintenance at updates.

✅ Mag-research: Ano pang ibang limitasyon ang maaaring mayroon sa edge computing?

Ang mga limitasyon ay karaniwang kabaligtaran ng mga benepisyo ng paggamit ng cloud - kailangan mong bumuo at pamahalaan ang mga device na ito nang mag-isa, sa halip na umasa sa expertise at saklaw ng cloud providers.

Ang ilan sa mga panganib ay nababawasan dahil sa mismong kalikasan ng edge computing. Halimbawa, kung mayroon kang edge device na tumatakbo sa isang pabrika na nangongolekta ng data mula sa mga makina, hindi mo kailangang mag-isip tungkol sa ilang disaster recovery scenarios. Kung mawalan ng kuryente ang pabrika, hindi mo na kailangan ng backup edge device dahil ang mga makina na gumagawa ng data na pinoproseso ng edge device ay mawawalan din ng kuryente.

Para sa mga IoT system, madalas mong gugustuhin ang kumbinasyon ng cloud at edge computing, gamit ang bawat serbisyo batay sa pangangailangan ng sistema, ng mga customer nito, at ng mga tagapamahala nito.

## Azure IoT Edge

![Ang Azure IoT Edge logo](../../../../../translated_images/tl/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Ang Azure IoT Edge ay isang serbisyo na makakatulong sa iyo na ilipat ang workloads mula sa cloud patungo sa edge. Maaari kang mag-set up ng isang device bilang edge device, at mula sa cloud maaari kang mag-deploy ng code sa edge device na iyon. Pinapayagan ka nitong pagsamahin ang mga kakayahan ng cloud at edge.

> 🎓 *Workloads* ay isang termino para sa anumang serbisyo na gumagawa ng isang uri ng trabaho, tulad ng AI models, applications, o serverless functions.

Halimbawa, maaari kang mag-train ng isang image classifier sa cloud, pagkatapos mula sa cloud i-deploy ito sa isang edge device. Ang iyong IoT device ay magpapadala ng mga imahe sa edge device para sa classification, sa halip na ipadala ang mga imahe sa internet. Kung kailangan mong mag-deploy ng bagong bersyon ng modelo, maaari mo itong i-train sa cloud at gamitin ang IoT Edge upang i-update ang modelo sa edge device sa iyong bagong bersyon.

> 🎓 Ang software na na-deploy sa IoT Edge ay kilala bilang *modules*. Sa default, ang IoT Edge ay nagpapatakbo ng mga modules na nakikipag-ugnayan sa IoT Hub, tulad ng `edgeAgent` at `edgeHub` modules. Kapag nag-deploy ka ng isang image classifier, ito ay na-deploy bilang karagdagang module.

Ang IoT Edge ay naka-built-in sa IoT Hub, kaya maaari mong pamahalaan ang mga edge device gamit ang parehong serbisyo na ginagamit mo upang pamahalaan ang mga IoT device, na may parehong antas ng seguridad.

Ang IoT Edge ay nagpapatakbo ng code mula sa *containers* - mga self-contained applications na tumatakbo nang hiwalay mula sa iba pang mga application sa iyong computer. Kapag nagpapatakbo ka ng container, ito ay parang isang hiwalay na computer na tumatakbo sa loob ng iyong computer, na may sariling software, serbisyo, at mga application. Kadalasan, ang mga container ay hindi maaaring ma-access ang anumang bagay sa iyong computer maliban kung pipiliin mong ibahagi ang mga bagay tulad ng isang folder sa container. Ang container ay naglalabas ng mga serbisyo sa pamamagitan ng isang open port na maaari mong i-connect o i-expose sa iyong network.

![Isang web request na na-redirect sa isang container](../../../../../translated_images/tl/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Halimbawa, maaari kang magkaroon ng isang container na may web site na tumatakbo sa port 80, ang default na HTTP port, at maaari mo itong i-expose mula sa iyong computer din sa port 80.

✅ Mag-research: Magbasa tungkol sa containers at mga serbisyo tulad ng Docker o Moby.

Maaari mong gamitin ang Custom Vision upang i-download ang mga image classifiers at i-deploy ang mga ito bilang containers, alinman sa direktang pagpapatakbo sa isang device o pag-deploy sa pamamagitan ng IoT Edge. Kapag tumatakbo na ang mga ito sa isang container, maaari silang ma-access gamit ang parehong REST API tulad ng cloud version, ngunit ang endpoint ay tumutukoy sa Edge device na nagpapatakbo ng container.

## Magrehistro ng IoT Edge device

Upang magamit ang isang IoT Edge device, kailangan itong mairehistro sa IoT Hub.

### Gawain - magrehistro ng IoT Edge device

1. Gumawa ng IoT Hub sa `fruit-quality-detector` resource group. Bigyan ito ng natatanging pangalan na may kaugnayan sa `fruit-quality-detector`.

1. Magrehistro ng IoT Edge device na tinatawag na `fruit-quality-detector-edge` sa iyong IoT Hub. Ang command upang gawin ito ay katulad ng ginamit upang magrehistro ng non-edge device, maliban na kailangan mong ipasa ang `--edge-enabled` flag.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan ng iyong IoT Hub.

1. Kunin ang connection string para sa iyong device gamit ang sumusunod na command:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan ng iyong IoT Hub.

    Kopyahin ang connection string na ipinapakita sa output.

## I-set up ang IoT Edge device

Kapag nagawa mo na ang edge device registration sa iyong IoT Hub, maaari mo nang i-set up ang edge device.

### Gawain - I-install at simulan ang IoT Edge Runtime

**Ang IoT Edge runtime ay tumatakbo lamang sa Linux containers.** Maaari itong patakbuhin sa Linux, o sa Windows gamit ang Linux Virtual Machines.

* Kung gumagamit ka ng Raspberry Pi bilang iyong IoT device, ito ay tumatakbo sa isang suportadong bersyon ng Linux at maaaring mag-host ng IoT Edge runtime. Sundin ang [install Azure IoT Edge for Linux guide sa Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) upang i-install ang IoT Edge at i-set ang connection string.

    > 💁 Tandaan, ang Raspberry Pi OS ay isang variant ng Debian Linux.

* Kung hindi ka gumagamit ng Raspberry Pi, ngunit may Linux computer, maaari mong patakbuhin ang IoT Edge runtime. Sundin ang [install Azure IoT Edge for Linux guide sa Microsoft docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) upang i-install ang IoT Edge at i-set ang connection string.

* Kung gumagamit ka ng Windows, maaari mong i-install ang IoT Edge runtime sa isang Linux Virtual Machine sa pamamagitan ng pagsunod sa [install and start the IoT Edge runtime section ng deploy your first IoT Edge module to a Windows device quickstart sa Microsoft docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Maaari kang huminto kapag naabot mo na ang *Deploy a module* section.

* Kung gumagamit ka ng macOS, maaari kang lumikha ng virtual machine (VM) sa cloud upang magamit bilang iyong IoT Edge device. Ang mga ito ay mga computer na maaari mong likhain sa cloud at ma-access sa internet. Maaari kang lumikha ng Linux VM na may naka-install na IoT Edge. Sundin ang [create a virtual machine running IoT Edge guide](vm-iotedge.md) para sa mga tagubilin kung paano ito gawin.

## I-export ang iyong modelo

Upang patakbuhin ang classifier sa edge, kailangan itong i-export mula sa Custom Vision. Ang Custom Vision ay maaaring lumikha ng dalawang uri ng mga modelo - standard models at compact models. Ang compact models ay gumagamit ng iba't ibang teknolohiya upang mabawasan ang laki ng modelo, ginagawa itong sapat na maliit upang ma-download at ma-deploy sa mga IoT device.

Kapag nilikha mo ang image classifier, ginamit mo ang *Food* domain, isang bersyon ng modelo na na-optimize para sa training sa mga food images. Sa Custom Vision, maaari mong baguhin ang domain ng iyong proyekto, gamit ang iyong training data upang mag-train ng bagong modelo gamit ang bagong domain. Lahat ng domain na sinusuportahan ng Custom Vision ay available bilang standard at compact.

### Gawain - i-train ang iyong modelo gamit ang Food (compact) domain
1. Buksan ang Custom Vision portal sa [CustomVision.ai](https://customvision.ai) at mag-sign in kung hindi pa ito bukas. Pagkatapos, buksan ang iyong proyekto na `fruit-quality-detector`.

1. Piliin ang **Settings** button (ang ⚙ icon).

1. Sa listahan ng *Domains*, piliin ang *Food (compact)*.

1. Sa ilalim ng *Export Capabilities*, tiyaking napili ang *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. Sa ibaba ng Settings page, piliin ang **Save Changes**.

1. I-retrain ang model gamit ang **Train** button, at piliin ang *Quick training*.

### Gawain - i-export ang iyong model

Kapag na-train na ang model, kailangan itong i-export bilang isang container.

1. Piliin ang **Performance** tab, at hanapin ang pinakabagong iteration na na-train gamit ang compact domain.

1. Piliin ang **Export** button sa itaas.

1. Piliin ang **DockerFile**, pagkatapos pumili ng bersyon na tugma sa iyong edge device:

    * Kung gumagamit ka ng IoT Edge sa isang Linux computer, Windows computer, o Virtual Machine, piliin ang bersyong *Linux*.
    * Kung gumagamit ka ng IoT Edge sa isang Raspberry Pi, piliin ang bersyong *ARM (Raspberry Pi 3)*.

> 🎓 Ang Docker ay isa sa mga pinakasikat na tool para sa pamamahala ng containers, at ang DockerFile ay isang set ng mga instruksyon kung paano i-set up ang container.

1. Piliin ang **Export** para hayaan ang Custom Vision na gumawa ng mga kaukulang file, pagkatapos ay piliin ang **Download** para i-download ang mga ito bilang zip file.

1. I-save ang mga file sa iyong computer, pagkatapos i-unzip ang folder.

## Ihanda ang iyong container para sa deployment

![Ang mga containers ay binubuo, pagkatapos ay ipinapadala sa isang container registry, at pagkatapos ay dine-deploy mula sa container registry papunta sa edge device gamit ang IoT Edge](../../../../../translated_images/tl/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Kapag na-download mo na ang iyong model, kailangan itong gawing container, pagkatapos ay i-push sa isang container registry - isang online na lokasyon kung saan maaari kang mag-imbak ng containers. Ang IoT Edge ay maaaring mag-download ng container mula sa registry at i-push ito sa iyong device.

![Logo ng Azure Container Registry](../../../../../translated_images/tl/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Ang container registry na gagamitin mo para sa araling ito ay Azure Container Registry. Hindi ito libreng serbisyo, kaya para makatipid, tiyaking [linisin ang iyong proyekto](../../../clean-up.md) kapag natapos ka na.

> 💁 Makikita mo ang mga gastos sa paggamit ng Azure Container Registry sa [Azure Container Registry pricing page](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Gawain - i-install ang Docker

Para mabuo at ma-deploy ang classifier, maaaring kailanganin mong i-install ang [Docker](https://www.docker.com/).

Kailangan mo lang gawin ito kung plano mong buuin ang container mula sa ibang device kaysa sa device kung saan mo in-install ang IoT Edge - bilang bahagi ng pag-install ng IoT Edge, ang Docker ay naka-install na para sa iyo.

1. Kung binubuo mo ang docker container sa ibang device mula sa iyong IoT Edge device, sundin ang mga instruksyon sa pag-install ng Docker sa [Docker install page](https://www.docker.com/products/docker-desktop) para i-install ang Docker Desktop o ang Docker engine. Tiyaking tumatakbo ito pagkatapos ng pag-install.

### Gawain - gumawa ng container registry resource

1. Patakbuhin ang sumusunod na command mula sa iyong Terminal o command prompt para gumawa ng Azure Container Registry resource:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Palitan ang `<Container registry name>` ng isang natatanging pangalan para sa iyong container registry, gamit ang mga letra at numero lamang. Basehan ito sa `fruitqualitydetector`. Ang pangalan na ito ay magiging bahagi ng URL para ma-access ang container registry, kaya kailangang globally unique.

1. Mag-log in sa Azure Container Registry gamit ang sumusunod na command:

    ```sh
    az acr login --name <Container registry name>
    ```

    Palitan ang `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry.

1. I-set ang container registry sa admin mode para makabuo ng password gamit ang sumusunod na command:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Palitan ang `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry.

1. Bumuo ng mga password para sa iyong container registry gamit ang sumusunod na command:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Palitan ang `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry.

    Kopyahin ang halaga ng `PASSWORD`, dahil kakailanganin mo ito mamaya.

### Gawain - buuin ang iyong container

Ang na-download mo mula sa Custom Vision ay isang DockerFile na naglalaman ng mga instruksyon kung paano dapat buuin ang container, kasama ang application code na tatakbo sa loob ng container para i-host ang iyong custom vision model, kasama ang isang REST API para tawagin ito. Maaari mong gamitin ang Docker para bumuo ng isang tagged container mula sa DockerFile, pagkatapos ay i-push ito sa iyong container registry.

> 🎓 Ang mga containers ay binibigyan ng tag na tumutukoy sa pangalan at bersyon para sa kanila. Kapag kailangan mong i-update ang isang container, maaari mo itong buuin gamit ang parehong tag ngunit mas bagong bersyon.

1. Buksan ang iyong terminal o command prompt at mag-navigate sa unzipped model na na-download mo mula sa Custom Vision.

1. Patakbuhin ang sumusunod na command para buuin at i-tag ang image:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Palitan ang `<platform>` ng platform kung saan tatakbo ang container na ito. Kung gumagamit ka ng IoT Edge sa isang Raspberry Pi, itakda ito sa `linux/armhf`, kung hindi, itakda ito sa `linux/amd64`.

    > 💁 Kung pinapatakbo mo ang command na ito mula sa device kung saan mo pinapatakbo ang IoT Edge, tulad ng Raspberry Pi, maaari mong alisin ang `--platform <platform>` na bahagi dahil default ito sa kasalukuyang platform.

    Palitan ang `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry.

    > 💁 Kung gumagamit ka ng Linux o Raspberry Pi OS, maaaring kailanganin mong gamitin ang `sudo` para patakbuhin ang command na ito.

    Ang Docker ay bubuo ng image, na-configure ang lahat ng kinakailangang software. Ang image ay tatag bilang `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Gawain - i-push ang iyong container sa iyong container registry

1. Gamitin ang sumusunod na command para i-push ang iyong container sa iyong container registry:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Palitan ang `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry.

    > 💁 Kung gumagamit ka ng Linux, maaaring kailanganin mong gamitin ang `sudo` para patakbuhin ang command na ito.

    Ang container ay ipapadala sa container registry.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Para i-verify ang push, maaari mong i-lista ang mga containers sa iyong registry gamit ang sumusunod na command:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Palitan ang `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Makikita mo ang iyong classifier na nakalista sa output.

## I-deploy ang iyong container

Ang iyong container ay maaari nang i-deploy sa iyong IoT Edge device. Para i-deploy, kailangan mong gumawa ng deployment manifest - isang JSON document na naglilista ng mga modules na ide-deploy sa edge device.

### Gawain - gumawa ng deployment manifest

1. Gumawa ng bagong file na tinatawag na `deployment.json` sa isang lugar sa iyong computer.

1. Idagdag ang sumusunod sa file na ito:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Makikita mo ang file na ito sa [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) folder.

    Palitan ang tatlong instance ng `<Container registry name>` ng pangalan na ginamit mo para sa iyong container registry. Isa ay nasa `ImageClassifier` module section, ang dalawa pa ay nasa `registryCredentials` section.

    Palitan ang `<Container registry password>` sa `registryCredentials` section ng iyong container registry password.

1. Mula sa folder na naglalaman ng iyong deployment manifest, patakbuhin ang sumusunod na command:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan ng iyong IoT Hub.

    Ang image classifier module ay ide-deploy sa iyong edge device.

### Gawain - i-verify na tumatakbo ang classifier

1. Kumonekta sa IoT edge device:

    * Kung gumagamit ka ng Raspberry Pi para patakbuhin ang IoT Edge, kumonekta gamit ang ssh mula sa iyong terminal, o sa pamamagitan ng remote SSH session sa VS Code.
    * Kung pinapatakbo mo ang IoT Edge sa isang Linux container sa Windows, sundin ang mga hakbang sa [verify successful configuration guide](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) para kumonekta sa IoT Edge device.
    * Kung pinapatakbo mo ang IoT Edge sa isang virtual machine, maaari kang mag-SSH sa machine gamit ang `adminUsername` at `password` na itinakda mo noong ginawa ang VM, at gamit ang IP address o DNS name:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        O:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Ipasok ang iyong password kapag na-prompt.

1. Kapag nakakonekta na, patakbuhin ang sumusunod na command para makuha ang listahan ng IoT Edge modules:

    ```sh
    iotedge list
    ```

    > 💁 Maaaring kailanganin mong patakbuhin ang command na ito gamit ang `sudo`.

    Makikita mo ang mga tumatakbong modules:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Tingnan ang logs para sa Image classifier module gamit ang sumusunod na command:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Maaaring kailanganin mong patakbuhin ang command na ito gamit ang `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Gawain - subukan ang image classifier

1. Maaari mong gamitin ang CURL para subukan ang image classifier gamit ang IP address o host name ng computer na nagpapatakbo ng IoT Edge agent. Hanapin ang IP address:

    * Kung nasa parehong machine ka na nagpapatakbo ng IoT Edge, maaari mong gamitin ang `localhost` bilang host name.
    * Kung gumagamit ka ng VM, maaari mong gamitin ang IP address o DNS name ng VM.
    * Kung hindi, maaari mong makuha ang IP address ng machine na nagpapatakbo ng IoT Edge:
      * Sa Windows 10, sundin ang [find your IP address guide](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Sa macOS, sundin ang [how to find your IP address on a Mac guide](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Sa Linux, sundin ang seksyon sa paghahanap ng iyong private IP address sa [how to find your IP address in Linux guide](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Maaari mong subukan ang container gamit ang isang lokal na file sa pamamagitan ng pagpapatakbo ng sumusunod na curl command:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Palitan ang `<IP address or name>` ng IP address o host name ng computer na nagpapatakbo ng IoT Edge. Palitan ang `<file_Name>` ng pangalan ng file na susubukan.

    Makikita mo ang prediction results sa output:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Walang kailangang ibigay na prediction key dito, dahil hindi ito gumagamit ng Azure resource. Sa halip, ang seguridad ay iko-configure sa internal network base sa internal security needs, sa halip na umasa sa isang public endpoint at API key.

## Gamitin ang iyong IoT Edge device

Ngayon na ang iyong Image Classifier ay na-deploy na sa isang IoT Edge device, maaari mo na itong gamitin mula sa iyong IoT device.

### Gawain - gamitin ang iyong IoT Edge device

Sundin ang kaukulang gabay para mag-classify ng mga imahe gamit ang IoT Edge classifier:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer.md)

### Model retraining

Isa sa mga downside ng pagpapatakbo ng image classifiers sa IoT Edge ay hindi sila konektado sa iyong Custom Vision project. Kung titingnan mo ang **Predictions** tab sa Custom Vision, hindi mo makikita ang mga imahe na na-classify gamit ang Edge-based classifier.

Ito ang inaasahang behavior - ang mga imahe ay hindi ipinapadala sa cloud para sa classification, kaya hindi sila magiging available sa cloud. Isa sa mga benepisyo ng paggamit ng IoT Edge ay privacy, na tinitiyak na ang mga imahe ay hindi umaalis sa iyong network, isa pa ay ang kakayahang magtrabaho offline, kaya hindi umaasa sa pag-upload ng mga imahe kapag ang device ay walang internet connection. Ang downside ay ang pagpapabuti ng iyong model - kailangan mong magpatupad ng ibang paraan ng pag-iimbak ng mga imahe na maaaring manu-manong ma-reclassify para mapabuti at ma-retrain ang image classifier.

✅ Mag-isip ng mga paraan para mag-upload ng mga imahe upang ma-retrain ang classifier.

---

## 🚀 Hamon

Ang pagpapatakbo ng AI models sa edge devices ay maaaring mas mabilis kaysa sa cloud - mas maikli ang network hop. Maaari rin itong mas mabagal dahil ang hardware na nagpapatakbo ng model ay maaaring hindi kasing lakas ng cloud.

Gumawa ng mga timing at ikumpara kung ang tawag sa iyong edge device ay mas mabilis o mas mabagal kaysa sa tawag sa cloud? Mag-isip ng mga dahilan para ipaliwanag ang pagkakaiba, o kawalan ng pagkakaiba. Mag-research ng mga paraan para patakbuhin ang AI models nang mas mabilis sa edge gamit ang specialized hardware.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Review & Self Study

* Magbasa pa tungkol sa containers sa [OS-level virtualization page on Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Magbasa pa tungkol sa edge computing, na may diin sa kung paano makakatulong ang 5G sa pagpapalawak ng edge computing sa [ano ang edge computing at bakit ito mahalaga? artikulo sa NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Alamin pa ang tungkol sa pagpapatakbo ng AI services sa IoT Edge sa pamamagitan ng panonood ng [alamin kung paano gamitin ang Azure IoT Edge sa isang pre-built AI service sa Edge para sa language detection episode ng Learn Live sa Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Takdang-Aralin

[Patakbuhin ang iba pang mga serbisyo sa edge](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.