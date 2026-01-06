<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-27T22:01:44+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "tl"
}
-->
# Ilipat ang iyong halaman sa cloud

![Isang sketchnote na buod ng araling ito](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang larawan para sa mas malaking bersyon.

Ang araling ito ay itinuro bilang bahagi ng [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) mula sa [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Ikonekta ang iyong device sa cloud gamit ang Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Panimula

Sa nakaraang aralin, natutunan mo kung paano ikonekta ang iyong halaman sa isang MQTT broker at kontrolin ang isang relay mula sa server code na tumatakbo nang lokal. Ito ang pangunahing bahagi ng isang internet-connected automated watering system na ginagamit mula sa mga indibidwal na halaman sa bahay hanggang sa mga komersyal na sakahan.

Ang IoT device ay nakipag-ugnayan sa isang pampublikong MQTT broker bilang paraan upang ipakita ang mga prinsipyo, ngunit hindi ito ang pinaka-maaasahan o ligtas na paraan. Sa araling ito, matututo ka tungkol sa cloud at ang mga kakayahan ng IoT na ibinibigay ng mga pampublikong cloud services. Matututo ka rin kung paano ilipat ang iyong halaman sa isa sa mga cloud services na ito mula sa pampublikong MQTT broker.

Sa araling ito, tatalakayin natin ang:

* [Ano ang cloud?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Gumawa ng cloud subscription](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Mga serbisyo ng Cloud IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Gumawa ng IoT service sa cloud](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Makipag-ugnayan sa IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Ikonekta ang iyong device sa IoT service](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Ano ang cloud?

Bago ang cloud, kapag ang isang kumpanya ay gustong magbigay ng mga serbisyo sa kanilang mga empleyado (tulad ng mga database o file storage), o sa publiko (tulad ng mga website), sila ay magtatayo at magpapatakbo ng data center. Ito ay maaaring isang silid na may kaunting mga computer, o isang gusali na may maraming computer. Ang kumpanya ang nangangasiwa sa lahat, kabilang ang:

* Pagbili ng mga computer
* Pagpapanatili ng hardware
* Kuryente at pagpapalamig
* Networking
* Seguridad, kabilang ang seguridad ng gusali at seguridad ng software sa mga computer
* Pag-install at pag-update ng software

Napakamahal nito, nangangailangan ng malawak na hanay ng mga bihasang empleyado, at napakabagal baguhin kapag kinakailangan. Halimbawa, kung ang isang online store ay kailangang magplano para sa abalang holiday season, kailangan nilang magplano ng ilang buwan nang maaga upang bumili ng mas maraming hardware, i-configure ito, i-install ito, at i-install ang software upang patakbuhin ang kanilang proseso ng pagbebenta. Pagkatapos ng holiday season at bumaba ang mga benta, maiiwan silang may mga computer na binayaran nila ngunit hindi nagagamit hanggang sa susunod na abalang panahon.

✅ Sa tingin mo ba ay magpapahintulot ito sa mga kumpanya na mabilis na makakilos? Kung ang isang online na tindahan ng damit ay biglang sumikat dahil sa isang sikat na tao na nakitang suot ang kanilang damit, magagawa ba nilang mabilis na dagdagan ang kanilang computing power upang suportahan ang biglaang pagdami ng mga order?

### Computer ng iba

Ang cloud ay madalas na tinutukoy nang pabiro bilang 'computer ng iba'. Ang pangunahing ideya ay simple - sa halip na bumili ng mga computer, magrenta ka ng computer ng iba. Ang ibang tao, isang cloud computing provider, ang magpapatakbo ng malalaking data center. Sila ang bahala sa pagbili at pag-install ng hardware, pamamahala ng kuryente at pagpapalamig, networking, seguridad ng gusali, mga update sa hardware at software, lahat. Bilang isang customer, magrerenta ka ng mga computer na kailangan mo, magrerenta ng mas marami kapag tumaas ang demand, at babawasan ang bilang na nirenta kapag bumaba ang demand. Ang mga cloud data center na ito ay matatagpuan sa buong mundo.

![Isang Microsoft cloud data center](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.tl.png)
![Isang planong pagpapalawak ng Microsoft cloud data center](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.tl.png)

Ang mga data center na ito ay maaaring umabot ng ilang kilometro kuwadrado ang laki. Ang mga larawan sa itaas ay kuha ilang taon na ang nakalipas sa isang Microsoft cloud data center, at ipinapakita ang orihinal na laki, kasama ang planong pagpapalawak. Ang lugar na nilinis para sa pagpapalawak ay higit sa 5 kilometro kuwadrado.

> 💁 Ang mga data center na ito ay nangangailangan ng napakalaking dami ng kuryente kaya ang ilan ay may sariling mga power station. Dahil sa kanilang laki at antas ng pamumuhunan mula sa mga cloud provider, karaniwan silang napaka-environmentally friendly. Mas mahusay sila kaysa sa napakaraming maliliit na data center, tumatakbo sila karamihan sa renewable energy, at ang mga cloud provider ay nagsusumikap na bawasan ang basura, bawasan ang paggamit ng tubig, at magtanim muli ng mga kagubatan upang palitan ang mga pinutol para magbigay ng espasyo para sa pagtatayo ng data center. Maaari kang magbasa pa tungkol sa kung paano nagtatrabaho ang isang cloud provider sa sustainability sa [Azure sustainability site](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Mag-research: Magbasa tungkol sa mga pangunahing cloud tulad ng [Azure mula sa Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) o [GCP mula sa Google](https://cloud.google.com). Ilan ang kanilang mga data center, at saan matatagpuan ang mga ito sa mundo?

Ang paggamit ng cloud ay nakakatipid ng gastos para sa mga kumpanya, at nagbibigay-daan sa kanila na mag-focus sa kanilang ginagawa nang pinakamahusay, iniiwan ang cloud computing expertise sa kamay ng provider. Hindi na kailangang magrenta o bumili ng espasyo sa data center, magbayad sa iba't ibang provider para sa koneksyon at kuryente, o mag-empleyo ng mga eksperto. Sa halip, maaari silang magbayad ng isang buwanang bayarin sa cloud provider upang maasikaso ang lahat.

Ang cloud provider naman ay maaaring gumamit ng economies of scale upang mapababa ang mga gastos, bumili ng mga computer nang maramihan sa mas mababang presyo, mamuhunan sa mga tool upang mabawasan ang kanilang workload para sa maintenance, at kahit magdisenyo at magtayo ng sarili nilang hardware upang mapabuti ang kanilang cloud offering.

### Microsoft Azure

Ang Azure ay ang developer cloud mula sa Microsoft, at ito ang cloud na gagamitin mo para sa mga araling ito. Ang video sa ibaba ay nagbibigay ng maikling buod ng Azure:

[![Buod ng Azure video](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.tl.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Gumawa ng cloud subscription

Upang magamit ang mga serbisyo sa cloud, kailangan mong mag-sign up para sa isang subscription sa isang cloud provider. Para sa araling ito, mag-sign up ka para sa isang Microsoft Azure subscription. Kung mayroon ka nang Azure subscription, maaari mong laktawan ang gawaing ito. Ang mga detalye ng subscription na inilarawan dito ay tama sa oras ng pagsulat, ngunit maaaring magbago.

> 💁 Kung ina-access mo ang mga araling ito sa pamamagitan ng iyong paaralan, maaaring mayroon ka nang Azure subscription na magagamit. Kumonsulta sa iyong guro.

Mayroong dalawang uri ng libreng Azure subscription na maaari mong i-sign up:

* **Azure for Students** - Isang subscription na idinisenyo para sa mga estudyanteng 18+. Hindi mo kailangan ng credit card upang mag-sign up, at gagamitin mo ang iyong school email address upang ma-validate na ikaw ay isang estudyante. Kapag nag-sign up ka, makakakuha ka ng US$100 na magagamit sa mga cloud resources, kasama ang mga libreng serbisyo kabilang ang isang libreng bersyon ng IoT service. Tumagal ito ng 12 buwan, at maaari mong i-renew bawat taon na ikaw ay nananatiling estudyante.

* **Azure free subscription** - Isang subscription para sa sinumang hindi estudyante. Kakailanganin mo ng credit card upang mag-sign up para sa subscription, ngunit ang iyong card ay hindi sisingilin, ito ay ginagamit lamang upang i-verify na ikaw ay isang totoong tao, hindi isang bot. Makakakuha ka ng $200 na credit na magagamit sa unang 30 araw sa anumang serbisyo, kasama ang mga libreng tier ng Azure services. Kapag nagamit na ang iyong credit, ang iyong card ay hindi sisingilin maliban kung iko-convert mo ito sa isang pay-as-you-go subscription.

> 💁 Nag-aalok ang Microsoft ng Azure for Students Starter subscription para sa mga estudyanteng wala pang 18, ngunit sa oras ng pagsulat, hindi nito sinusuportahan ang anumang IoT services.

### Gawain - mag-sign up para sa isang libreng cloud subscription

Kung ikaw ay isang estudyanteng 18+, maaari kang mag-sign up para sa isang Azure for Students subscription. Kakailanganin mong mag-validate gamit ang isang school email address. Maaari mo itong gawin sa dalawang paraan:

* Mag-sign up para sa isang GitHub student developer pack sa [education.github.com/pack](https://education.github.com/pack). Bibigyan ka nito ng access sa iba't ibang mga tool at alok, kabilang ang GitHub at Microsoft Azure. Kapag nag-sign up ka para sa developer pack, maaari mong i-activate ang Azure for Students offer.

* Mag-sign up nang direkta para sa isang Azure for Students account sa [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Kung ang iyong school email address ay hindi kinikilala, mag-raise ng [issue sa repo na ito](https://github.com/Microsoft/IoT-For-Beginners/issues) at titingnan namin kung maaari itong maidagdag sa Azure for Students allow list.

Kung hindi ka estudyante, o wala kang valid na school email address, maaari kang mag-sign up para sa isang Azure Free subscription.

* Mag-sign up para sa isang Azure Free Subscription sa [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Mga serbisyo ng Cloud IoT

Ang pampublikong test MQTT broker na ginagamit mo ay isang mahusay na tool kapag nag-aaral, ngunit may ilang mga kakulangan bilang isang tool na gagamitin sa isang komersyal na setting:

* **Kahusayan** - ito ay isang libreng serbisyo na walang garantiya, at maaaring patayin anumang oras
* **Seguridad** - ito ay pampubliko, kaya maaaring makinig ang sinuman sa iyong telemetry o magpadala ng mga utos upang kontrolin ang iyong hardware
* **Pagganap** - ito ay idinisenyo para lamang sa ilang test messages, kaya hindi nito kayang suportahan ang malaking dami ng mga mensahe
* **Pagtuklas** - walang paraan upang malaman kung anong mga device ang nakakonekta

Ang mga IoT services sa cloud ay nilulutas ang mga problemang ito. Pinapanatili ito ng malalaking cloud provider na malaki ang pamumuhunan sa kahusayan at handang ayusin ang anumang mga isyu na maaaring lumitaw. Mayroon silang built-in na seguridad upang pigilan ang mga hacker na basahin ang iyong data o magpadala ng mga maling utos. Mataas din ang kanilang pagganap, kayang hawakan ang maraming milyong mensahe araw-araw, gamit ang cloud upang mag-scale ayon sa pangangailangan.

> 💁 Bagama't may bayad ang mga benepisyong ito sa isang buwanang bayarin, karamihan sa mga cloud provider ay nag-aalok ng libreng bersyon ng kanilang IoT service na may limitadong dami ng mga mensahe bawat araw o mga device na maaaring kumonekta. Ang libreng bersyon na ito ay karaniwang higit pa sa sapat para sa isang developer upang matutunan ang serbisyo. Sa araling ito, gagamit ka ng libreng bersyon.

Ang mga IoT device ay kumokonekta sa isang cloud service alinman sa pamamagitan ng isang device SDK (isang library na nagbibigay ng code upang gumana sa mga tampok ng serbisyo), o direkta sa pamamagitan ng isang communication protocol tulad ng MQTT o HTTP. Ang device SDK ay karaniwang pinakamadaling ruta dahil ito ang bahala sa lahat, tulad ng pag-alam kung anong mga topic ang ipo-publish o susubaybayan, at kung paano hahawakan ang seguridad.

![Ang mga device ay kumokonekta sa isang serbisyo gamit ang isang device SDK. Ang server code ay kumokonekta rin sa serbisyo sa pamamagitan ng isang SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.tl.png)

Ang iyong device ay nakikipag-ugnayan sa iba pang bahagi ng iyong application sa pamamagitan ng serbisyong ito - katulad ng kung paano ka nagpadala ng telemetry at tumanggap ng mga utos sa pamamagitan ng MQTT. Karaniwan itong ginagawa gamit ang isang service SDK o isang katulad na library. Ang mga mensahe ay nagmumula sa iyong device patungo sa serbisyo kung saan mababasa ito ng iba pang bahagi ng iyong application, at ang mga mensahe ay maaaring ipadala pabalik sa iyong device.

![Ang mga device na walang wastong secret key ay hindi makakonekta sa IoT service](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.tl.png)

Ang mga serbisyong ito ay nagpapatupad ng seguridad sa pamamagitan ng pag-alam sa lahat ng mga device na maaaring kumonekta at magpadala ng data, alinman sa pamamagitan ng pre-registration ng mga device sa serbisyo, o sa pamamagitan ng pagbibigay sa mga device ng mga secret key o certificate na maaari nilang gamitin upang irehistro ang kanilang sarili sa serbisyo sa unang pagkakataon na sila ay kumonekta. Ang mga hindi kilalang device ay hindi makakonekta; kung susubukan nila, tatanggihan ng serbisyo ang koneksyon at babalewalain ang mga mensaheng ipinadala nila.

✅ Mag-research: Ano ang downside ng pagkakaroon ng isang open IoT service kung saan maaaring kumonekta ang anumang device o code? Makakahanap ka ba ng mga partikular na halimbawa ng mga hacker na sinasamantala ito?

Ang iba pang bahagi ng iyong application ay maaaring kumonekta sa IoT service at malaman ang tungkol sa lahat ng mga device na nakakonekta o nakarehistro, at makipag-ugnayan sa kanila nang direkta, sa maramihan o paisa-isa.
💁 Ang mga serbisyo ng IoT ay nag-aalok din ng karagdagang kakayahan, at ang mga cloud provider ay may mga karagdagang serbisyo at aplikasyon na maaaring ikonekta sa serbisyo. Halimbawa, kung nais mong iimbak ang lahat ng telemetry na mensahe na ipinadala ng lahat ng mga device sa isang database, kadalasan ay ilang click lamang sa tool ng configuration ng cloud provider upang ikonekta ang serbisyo sa isang database at i-stream ang data papasok.
## Gumawa ng IoT service sa cloud

Ngayon na mayroon ka nang Azure subscription, maaari kang mag-sign up para sa isang IoT service. Ang IoT service mula sa Microsoft ay tinatawag na Azure IoT Hub.

![Ang logo ng Azure IoT Hub](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.tl.png)

Ang video sa ibaba ay nagbibigay ng maikling overview ng Azure IoT Hub:

[![Overview ng Azure IoT Hub video](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 I-click ang imahe sa itaas para panoorin ang video

✅ Maglaan ng oras para mag-research at basahin ang overview ng IoT Hub sa [Microsoft IoT Hub documentation](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Ang mga cloud services na available sa Azure ay maaaring i-configure gamit ang web-based portal, o sa pamamagitan ng command-line interface (CLI). Para sa task na ito, gagamitin mo ang CLI.

### Task - i-install ang Azure CLI

Para magamit ang Azure CLI, kailangan muna itong i-install sa iyong PC o Mac.

1. Sundin ang mga tagubilin sa [Azure CLI documentation](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) para i-install ang CLI.

1. Ang Azure CLI ay sumusuporta sa iba't ibang extensions na nagdadagdag ng kakayahan para pamahalaan ang malawak na hanay ng Azure services. I-install ang IoT extension sa pamamagitan ng pag-run ng sumusunod na command mula sa iyong command line o terminal:

    ```sh
    az extension add --name azure-iot
    ```

1. Mula sa iyong command line o terminal, i-run ang sumusunod na command para mag-log in sa iyong Azure subscription gamit ang Azure CLI.

    ```sh
    az login
    ```

    Magbubukas ang isang web page sa iyong default browser. Mag-log in gamit ang account na ginamit mo para mag-sign up sa iyong Azure subscription. Kapag naka-log in ka na, maaari mong isara ang browser tab.

1. Kung mayroon kang maraming Azure subscriptions, tulad ng isang school-provided subscription at ang iyong sariling Azure for Students subscription, kailangan mong piliin ang subscription na gusto mong gamitin. I-run ang sumusunod na command para makita ang lahat ng subscriptions na mayroon kang access:

    ```sh
    az account list --output table
    ```

    Sa output, makikita mo ang pangalan ng bawat subscription kasama ang `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Para piliin ang subscription na gusto mong gamitin, gamitin ang sumusunod na command:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Palitan ang `<SubscriptionId>` ng Id ng subscription na gusto mong gamitin. Pagkatapos i-run ang command na ito, i-run muli ang command para makita ang iyong mga accounts. Makikita mo na ang `IsDefault` column ay naka-mark bilang `True` para sa subscription na kakapili mo lang.

### Task - gumawa ng resource group

Ang mga Azure services, tulad ng IoT Hub instances, virtual machines, databases, o AI services, ay tinatawag na **resources**. Ang bawat resource ay kailangang nasa loob ng isang **Resource Group**, isang lohikal na grupo ng isa o higit pang resources.

> 💁 Ang paggamit ng resource groups ay nangangahulugan na maaari mong pamahalaan ang maraming services nang sabay-sabay. Halimbawa, kapag natapos mo na ang lahat ng lessons para sa proyektong ito, maaari mong i-delete ang resource group, at lahat ng resources sa loob nito ay awtomatikong made-delete.

1. Mayroong maraming Azure data centers sa buong mundo, na hinati sa mga rehiyon. Kapag gumagawa ka ng Azure resource o resource group, kailangan mong tukuyin kung saan mo ito gustong gawin. I-run ang sumusunod na command para makuha ang listahan ng mga lokasyon:

    ```sh
    az account list-locations --output table
    ```

    Makikita mo ang listahan ng mga lokasyon. Mahaba ang listahan na ito.

    > 💁 Sa oras ng pagsulat, mayroong 65 lokasyon kung saan maaari kang mag-deploy.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Tandaan ang value mula sa `Name` column ng rehiyon na pinakamalapit sa iyo. Maaari mong makita ang mga rehiyon sa mapa sa [Azure geographies page](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. I-run ang sumusunod na command para gumawa ng resource group na tinatawag na `soil-moisture-sensor`. Ang mga pangalan ng resource group ay kailangang unique sa iyong subscription.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Palitan ang `<location>` ng lokasyon na pinili mo sa nakaraang hakbang.

### Task - gumawa ng IoT Hub

Ngayon ay maaari ka nang gumawa ng IoT Hub resource sa iyong resource group.

1. Gamitin ang sumusunod na command para gumawa ng IoT Hub resource:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan para sa iyong hub. Ang pangalan na ito ay kailangang globally unique - ibig sabihin, walang ibang IoT Hub na ginawa ng kahit sino ang maaaring magkaroon ng parehong pangalan. Ang pangalan na ito ay ginagamit sa isang URL na tumutukoy sa hub, kaya kailangang unique. Gumamit ng isang bagay tulad ng `soil-moisture-sensor-` at magdagdag ng unique identifier sa dulo, tulad ng ilang random na salita o ang iyong pangalan.

    Ang `--sku F1` option ay nagsasabi na gamitin ang free tier. Ang free tier ay sumusuporta sa 8,000 messages kada araw kasama ang karamihan sa mga features ng full-price tiers.

    > 🎓 Ang iba't ibang pricing levels ng Azure services ay tinatawag na tiers. Ang bawat tier ay may iba't ibang halaga at nagbibigay ng iba't ibang features o data volumes.

    > 💁 Kung gusto mong matuto pa tungkol sa pricing, maaari mong tingnan ang [Azure IoT Hub pricing guide](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Ang `--partition-count 2` option ay nagde-define kung ilang streams ng data ang sinusuportahan ng IoT Hub, mas maraming partitions ang nagbabawas ng data blocking kapag maraming bagay ang nagbabasa at nagsusulat mula sa IoT Hub. Ang partitions ay labas sa saklaw ng mga lessons na ito, ngunit ang value na ito ay kailangang i-set para makagawa ng free tier IoT Hub.

    > 💁 Maaari ka lamang magkaroon ng isang free tier IoT Hub kada subscription.

Ang IoT Hub ay gagawin. Maaaring tumagal ng isang minuto o higit pa para makumpleto ito.

## Makipag-ugnayan sa IoT Hub

Sa nakaraang lesson, ginamit mo ang MQTT at nagpadala ng mga mensahe pabalik-balik sa iba't ibang topics, na may iba't ibang layunin ang bawat topic. Sa halip na magpadala ng mga mensahe sa iba't ibang topics, ang IoT Hub ay may ilang defined na paraan para makipag-ugnayan ang device sa Hub, o ang Hub sa device.

> 💁 Sa ilalim ng hood, ang komunikasyon sa pagitan ng IoT Hub at ng iyong device ay maaaring gumamit ng MQTT, HTTPS, o AMQP.

* Mga mensahe mula sa device papunta sa cloud (D2C) - ito ay mga mensahe na ipinapadala mula sa isang device papunta sa IoT Hub, tulad ng telemetry. Maaari itong basahin mula sa IoT Hub ng iyong application code.

    > 🎓 Sa ilalim ng hood, ang IoT Hub ay gumagamit ng Azure service na tinatawag na [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Kapag nagsusulat ka ng code para basahin ang mga mensaheng ipinadala sa hub, madalas itong tinatawag na events.

* Mga mensahe mula sa cloud papunta sa device (C2D) - ito ay mga mensahe na ipinapadala mula sa application code, sa pamamagitan ng IoT Hub papunta sa IoT device.

* Mga direct method requests - ito ay mga mensahe na ipinapadala mula sa application code sa pamamagitan ng IoT Hub papunta sa IoT device para hilingin na gawin ng device ang isang bagay, tulad ng pag-control sa actuator. Ang mga mensaheng ito ay nangangailangan ng response para malaman ng iyong application code kung ito ay matagumpay na naiproseso.

* Device twins - ito ay mga JSON documents na synchronized sa pagitan ng device at IoT Hub, at ginagamit para mag-store ng settings o iba pang properties na ini-report ng device, o dapat i-set sa device (tinatawag na desired) ng IoT Hub.

Ang IoT Hub ay maaaring mag-store ng mga mensahe at direct method requests para sa isang configurable na panahon (default ay isang araw), kaya kung ang isang device o application code ay nawalan ng koneksyon, maaari pa rin nitong makuha ang mga mensaheng ipinadala habang offline ito kapag nag-reconnect. Ang device twins ay permanenteng naka-store sa IoT Hub, kaya anumang oras ay maaaring mag-reconnect ang device at makuha ang pinakabagong device twin.

✅ Mag-research: Basahin ang higit pa tungkol sa mga uri ng mensahe sa [Device-to-cloud communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn), at ang [Cloud-to-device communications guidance](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) sa IoT Hub documentation.

## Ikonekta ang iyong device sa IoT service

Kapag nagawa na ang hub, maaari nang kumonekta ang iyong IoT device dito. Ang mga registered devices lamang ang maaaring kumonekta sa service, kaya kailangan mo munang i-register ang iyong device. Kapag nag-register ka, makakakuha ka ng connection string na magagamit ng device para kumonekta. Ang connection string na ito ay specific sa device, at naglalaman ng impormasyon tungkol sa IoT Hub, sa device, at isang secret key na magpapahintulot sa device na kumonekta.

> 🎓 Ang connection string ay isang generic na term para sa isang piraso ng text na naglalaman ng connection details. Ginagamit ang mga ito kapag kumokonekta sa IoT Hubs, databases, at maraming iba pang services. Karaniwan itong binubuo ng identifier para sa service, tulad ng URL, at security information tulad ng secret key. Ang mga ito ay ipinapasa sa SDKs para kumonekta sa service.

> ⚠️ Ang connection strings ay dapat panatilihing secure! Ang seguridad ay tatalakayin nang mas detalyado sa susunod na lesson.

### Task - i-register ang iyong IoT device

Ang IoT device ay maaaring i-register sa iyong IoT Hub gamit ang Azure CLI.

1. I-run ang sumusunod na command para i-register ang isang device:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

    Ito ay gagawa ng device na may ID na `soil-moisture-sensor`.

1. Kapag kumonekta ang iyong IoT device sa iyong IoT Hub gamit ang SDK, kailangan nitong gumamit ng connection string na nagbibigay ng URL ng hub, kasama ang secret key. I-run ang sumusunod na command para makuha ang connection string:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

1. I-store ang connection string na ipinakita sa output dahil kakailanganin mo ito mamaya.

### Task - ikonekta ang iyong IoT device sa cloud

Sundin ang kaukulang guide para ikonekta ang iyong IoT device sa cloud:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-connect-hub.md)

### Task - i-monitor ang events

Sa ngayon, hindi mo muna ia-update ang iyong server code. Sa halip, maaari mong gamitin ang Azure CLI para i-monitor ang events mula sa iyong IoT device.

1. Siguraduhin na ang iyong IoT device ay tumatakbo at nagpapadala ng soil moisture telemetry values.

1. I-run ang sumusunod na command sa iyong command prompt o terminal para i-monitor ang mga mensaheng ipinadala sa iyong IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

    Makikita mo ang mga mensahe na lumalabas sa console output habang ipinapadala ito ng iyong IoT device.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Ang nilalaman ng `payload` ay magmamatch sa mensaheng ipinadala ng iyong IoT device.

    > Sa oras ng pagsulat, ang `az iot` extension ay hindi pa ganap na gumagana sa Apple Silicon. Kung gumagamit ka ng Apple Silicon device, kailangan mong i-monitor ang mga mensahe sa ibang paraan, tulad ng paggamit ng [Azure IoT Tools para sa Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Ang mga mensaheng ito ay may ilang properties na awtomatikong naka-attach sa kanila, tulad ng timestamp kung kailan sila ipinadala. Ang mga ito ay tinatawag na *annotations*. Para makita ang lahat ng message annotations, gamitin ang sumusunod na command:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Palitan ang `<hub_name>` ng pangalan na ginamit mo para sa iyong IoT Hub.

    Makikita mo ang mga mensahe na lumalabas sa console output habang ipinapadala ito ng iyong IoT device.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Ang mga time values sa annotations ay nasa [UNIX time](https://wikipedia.org/wiki/Unix_time), na kumakatawan sa bilang ng mga segundo mula sa hatinggabi noong 1<sup>st</sup> Enero 1970.

    Lumabas sa event monitor kapag tapos ka na.

### Task - kontrolin ang iyong IoT device

Maaari mo ring gamitin ang Azure CLI para tawagin ang direct methods sa iyong IoT device.

1. I-run ang sumusunod na command sa iyong command prompt o terminal para i-invoke ang `relay_on` method sa IoT device:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Palitan ang `
<hub_name>
` gamit ang pangalan na ginamit mo para sa iyong IoT Hub.

    Ito ay nagpapadala ng direktang kahilingan para sa method na tinukoy sa `method-name`. Ang mga direktang method ay maaaring magdala ng payload na naglalaman ng data para sa method, at ito ay maaaring tukuyin sa parameter na `method-payload` bilang JSON.

    Makikita mo ang relay na magbukas, at ang kaukulang output mula sa iyong IoT device:

    ```output
    Direct method received -  relay_on
    ```

1. Ulitin ang hakbang sa itaas, ngunit itakda ang `--method-name` sa `relay_off`. Makikita mo ang relay na magsara at ang kaukulang output mula sa IoT device.

---

## 🚀 Hamon

Ang libreng tier ng IoT Hub ay nagpapahintulot ng 8,000 mensahe kada araw. Ang code na ginawa mo ay nagpapadala ng telemetry messages tuwing 10 segundo. Ilang mensahe ang maipapadala sa isang araw kung ang isang mensahe ay ipinapadala tuwing 10 segundo?

Pag-isipan kung gaano kadalas dapat ipadala ang mga sukat ng soil moisture? Paano mo mababago ang iyong code upang manatili sa loob ng libreng tier at masuri nang madalas ngunit hindi sobra? Paano kung gusto mong magdagdag ng pangalawang device?

## Quiz pagkatapos ng lektura

[Quiz pagkatapos ng lektura](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Review at Pag-aaral sa Sarili

Ang IoT Hub SDK ay open source para sa parehong Arduino at Python. Sa mga code repos sa GitHub, mayroong iba't ibang mga halimbawa na nagpapakita kung paano gamitin ang iba't ibang tampok ng IoT Hub.

* Kung gumagamit ka ng Wio Terminal, tingnan ang [Arduino samples sa GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Kung gumagamit ka ng Raspberry Pi o Virtual device, tingnan ang [Python samples sa GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Takdang Aralin

[Alamin ang tungkol sa cloud services](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.