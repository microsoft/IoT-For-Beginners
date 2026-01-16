<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T21:17:34+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "tl"
}
-->
# I-trigger ang pagtukoy ng kalidad ng prutas mula sa isang sensor

![Isang sketchnote na buod ng araling ito](../../../../../translated_images/tl/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Panimula

Ang isang IoT application ay hindi lamang isang solong device na kumukuha ng data at nagpapadala nito sa cloud. Kadalasan, ito ay binubuo ng maraming device na nagtutulungan upang kumuha ng data mula sa pisikal na mundo gamit ang mga sensor, gumawa ng mga desisyon batay sa data na iyon, at makipag-ugnayan pabalik sa pisikal na mundo sa pamamagitan ng mga actuator o visualizations.

Sa araling ito, matututo ka nang higit pa tungkol sa pagdidisenyo ng masalimuot na IoT applications, pagsasama ng maraming sensor, iba't ibang cloud services para sa pagsusuri at pag-iimbak ng data, at pagpapakita ng tugon sa pamamagitan ng isang actuator. Matututo ka ring magdisenyo ng prototype para sa isang sistema ng kontrol sa kalidad ng prutas, kabilang ang paggamit ng mga proximity sensor upang i-trigger ang IoT application, at kung ano ang magiging arkitektura ng prototype na ito.

Sa araling ito, tatalakayin natin ang:

* [Pagdidisenyo ng masalimuot na IoT applications](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Pagdidisenyo ng sistema ng kontrol sa kalidad ng prutas](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Pag-trigger ng pagsusuri ng kalidad ng prutas mula sa isang sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Data na ginagamit para sa isang fruit quality detector](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Paggamit ng developer devices upang gayahin ang maraming IoT devices](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Paglipat sa produksyon](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Ito ang huling aralin sa proyektong ito, kaya pagkatapos makumpleto ang aralin at ang assignment, huwag kalimutang linisin ang iyong cloud services. Kakailanganin mo ang mga serbisyo upang makumpleto ang assignment, kaya tiyaking tapusin muna iyon.
>
> Sumangguni sa [ang gabay sa paglilinis ng iyong proyekto](../../../clean-up.md) kung kinakailangan para sa mga tagubilin kung paano ito gawin.

## Pagdidisenyo ng masalimuot na IoT applications

Ang mga IoT application ay binubuo ng maraming bahagi. Kasama rito ang iba't ibang bagay at iba't ibang internet services.

Ang mga IoT application ay maaaring ilarawan bilang *mga bagay* (devices) na nagpapadala ng data na bumubuo ng *mga insight*. Ang mga *insight* na ito ay bumubuo ng *mga aksyon* upang mapabuti ang isang negosyo o proseso. Halimbawa, isang makina (ang bagay) na nagpapadala ng data ng temperatura. Ang data na ito ay ginagamit upang suriin kung ang makina ay gumagana nang maayos (ang insight). Ang insight ay ginagamit upang maagap na unahin ang iskedyul ng maintenance para sa makina (ang aksyon).

* Iba't ibang bagay ang kumukuha ng iba't ibang piraso ng data.
* Ang mga IoT services ay nagbibigay ng mga insight mula sa data na iyon, minsan ay pinapalawak ito gamit ang data mula sa karagdagang mga mapagkukunan.
* Ang mga insight na ito ay nagtutulak ng mga aksyon, kabilang ang pagkontrol sa mga actuator sa mga device, o pag-visualize ng data.

### Reference IoT architecture

![Isang reference na IoT architecture](../../../../../translated_images/tl/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.png)

Ang diagram sa itaas ay nagpapakita ng isang reference na IoT architecture.

> 🎓 Ang *reference architecture* ay isang halimbawa ng arkitektura na maaari mong gamitin bilang gabay kapag nagdidisenyo ng mga bagong sistema. Sa kasong ito, kung ikaw ay gumagawa ng bagong IoT system, maaari mong sundin ang reference architecture, pinapalitan ang iyong sariling mga device at serbisyo kung kinakailangan.

* **Mga Bagay** ay mga device na kumukuha ng data mula sa mga sensor, maaaring nakikipag-ugnayan sa mga edge services upang bigyang-kahulugan ang data na iyon, tulad ng mga image classifier upang bigyang-kahulugan ang data ng imahe. Ang data mula sa mga device ay ipinapadala sa isang IoT service.
* **Mga Insight** ay nagmumula sa mga serverless applications, o mula sa analytics na tumatakbo sa nakaimbak na data.
* **Mga Aksyon** ay maaaring mga utos na ipinapadala sa mga device, o visualization ng data na nagpapahintulot sa mga tao na gumawa ng mga desisyon.

![Isang reference na IoT architecture](../../../../../translated_images/tl/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.png)

Ang diagram sa itaas ay nagpapakita ng ilan sa mga bahagi at serbisyo na natalakay na sa mga araling ito at kung paano sila nag-uugnay sa isang reference na IoT architecture.

* **Mga Bagay** - nagsulat ka ng device code upang kumuha ng data mula sa mga sensor, at suriin ang mga imahe gamit ang Custom Vision na tumatakbo sa cloud at sa isang edge device. Ang data na ito ay ipinadala sa IoT Hub.
* **Mga Insight** - gumamit ka ng Azure Functions upang tumugon sa mga mensaheng ipinadala sa isang IoT Hub, at nag-imbak ng data para sa karagdagang pagsusuri sa Azure Storage.
* **Mga Aksyon** - kinontrol mo ang mga actuator batay sa mga desisyong ginawa sa cloud at mga utos na ipinadala sa mga device, at nag-visualize ng data gamit ang Azure Maps.

✅ Isipin ang iba pang IoT devices na nagamit mo, tulad ng mga smart home appliances. Ano ang mga bagay, insight, at aksyon na kasangkot sa device na iyon at sa software nito?

Ang pattern na ito ay maaaring palakihin nang malaki o maliit ayon sa iyong pangangailangan, nagdaragdag ng mas maraming device at mas maraming serbisyo.

### Data at seguridad

Habang tinutukoy mo ang arkitektura ng iyong sistema, kailangan mong patuloy na isaalang-alang ang data at seguridad.

* Anong data ang ipinapadala at natatanggap ng iyong device?
* Paano dapat ma-secure at maprotektahan ang data na iyon?
* Paano dapat kontrolin ang access sa device at cloud service?

✅ Isipin ang seguridad ng data ng anumang IoT devices na pagmamay-ari mo. Gaano karami sa data na iyon ang personal at dapat panatilihing pribado, parehong habang ipinapadala o kapag nakaimbak? Anong data ang hindi dapat iimbak?

## Pagdidisenyo ng sistema ng kontrol sa kalidad ng prutas

Ngayon, ilapat natin ang ideya ng mga bagay, insight, at aksyon sa ating fruit quality detector upang magdisenyo ng mas malaking end-to-end na application.

Isipin na binigyan ka ng gawain na bumuo ng isang fruit quality detector na gagamitin sa isang processing plant. Ang mga prutas ay dumadaan sa isang conveyor belt system kung saan kasalukuyang sinusuri ng mga empleyado ang mga prutas nang mano-mano at inaalis ang mga hindi pa hinog na prutas habang dumarating ang mga ito. Upang mabawasan ang gastos, nais ng may-ari ng planta ng isang automated na sistema.

✅ Isa sa mga trend sa pag-usbong ng IoT (at teknolohiya sa pangkalahatan) ay ang pagpapalit ng mga manual na trabaho ng mga makina. Mag-research: Ilang trabaho ang tinatayang mawawala dahil sa IoT? Ilang bagong trabaho ang malilikha sa paggawa ng IoT devices?

Kailangan mong bumuo ng isang sistema kung saan ang prutas ay natutukoy habang dumarating ito sa conveyor belt, ito ay kinukunan ng larawan at sinusuri gamit ang isang AI model na tumatakbo sa edge. Ang mga resulta ay ipinapadala sa cloud upang maimbak, at kung ang prutas ay hindi pa hinog, isang abiso ang ibinibigay upang maalis ang hindi pa hinog na prutas.

|   |   |
| - | - |
| **Mga Bagay** | Detector para sa prutas na dumarating sa conveyor belt<br>Camera para kunan ng larawan at i-classify ang prutas<br>Edge device na nagpapatakbo ng classifier<br>Device para magbigay ng abiso sa hindi pa hinog na prutas |
| **Mga Insight** | Magdesisyon na suriin ang hinog na prutas<br>Mag-imbak ng mga resulta ng ripeness classification<br>Tukuyin kung may pangangailangan na mag-abiso tungkol sa hindi pa hinog na prutas |
| **Mga Aksyon** | Magpadala ng utos sa isang device upang kunan ng larawan ang prutas at suriin ito gamit ang isang image classifier<br>Magpadala ng utos sa isang device upang mag-abiso na ang prutas ay hindi pa hinog |

### Pag-prototype ng iyong application

![Isang reference na IoT architecture para sa pagsusuri ng kalidad ng prutas](../../../../../translated_images/tl/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.png)

Ang diagram sa itaas ay nagpapakita ng isang reference na arkitektura para sa prototype application na ito.

* Isang IoT device na may proximity sensor ang nakakakita ng pagdating ng prutas. Nagpapadala ito ng mensahe sa cloud upang ipaalam na may prutas na natukoy.
* Isang serverless application sa cloud ang nagpapadala ng utos sa isa pang device upang kunan ng larawan at i-classify ang imahe.
* Isang IoT device na may camera ang kumukuha ng larawan at ipinapadala ito sa isang image classifier na tumatakbo sa edge. Ang mga resulta ay ipinapadala sa cloud.
* Isang serverless application sa cloud ang nag-iimbak ng impormasyong ito upang masuri sa hinaharap kung ilang porsyento ng prutas ang hindi pa hinog. Kung ang prutas ay hindi pa hinog, nagpapadala ito ng utos sa isa pang IoT device upang mag-abiso sa mga manggagawa sa pabrika sa pamamagitan ng isang LED.

> 💁 Ang buong IoT application na ito ay maaaring ipatupad bilang isang solong device, na may lahat ng lohika upang simulan ang image classification at kontrolin ang LED na nakapaloob. Maaari itong gumamit ng IoT Hub upang subaybayan lamang ang bilang ng mga hindi pa hinog na prutas na natukoy at i-configure ang device. Sa araling ito, pinalawak ito upang ipakita ang mga konsepto para sa malakihang IoT applications.

Para sa prototype, ipapatupad mo ang lahat ng ito sa isang solong device. Kung gumagamit ka ng microcontroller, gagamit ka ng hiwalay na edge device upang patakbuhin ang image classifier. Natutunan mo na ang karamihan sa mga bagay na kakailanganin mo upang mabuo ito.

## Pag-trigger ng pagsusuri ng kalidad ng prutas mula sa isang sensor

Ang IoT device ay nangangailangan ng isang uri ng trigger upang ipahiwatig kung kailan handa na ang prutas na ma-classify. Ang isang trigger para dito ay ang pagsukat kung kailan ang prutas ay nasa tamang lokasyon sa conveyor belt sa pamamagitan ng pagsukat ng distansya sa isang sensor.

![Ang mga proximity sensor ay nagpapadala ng laser beams sa mga bagay tulad ng saging at sinusukat ang oras bago bumalik ang beam](../../../../../translated_images/tl/proximity-sensor.f5cd752c77fb62fe.webp)

Ang mga proximity sensor ay maaaring gamitin upang sukatin ang distansya mula sa sensor patungo sa isang bagay. Karaniwan silang nagpapadala ng isang beam ng electromagnetic radiation tulad ng laser beam o infra-red light, pagkatapos ay natutukoy ang radiation na bumabalik mula sa isang bagay. Ang oras sa pagitan ng pagpapadala ng laser beam at pagbabalik ng signal ay maaaring gamitin upang kalkulahin ang distansya sa sensor.

> 💁 Malamang na nagamit mo na ang mga proximity sensor nang hindi mo namamalayan. Karamihan sa mga smartphone ay pinapatay ang screen kapag inilapit mo ito sa iyong tainga upang maiwasan ang aksidenteng pagputol ng tawag gamit ang iyong earlobe. Ginagawa ito gamit ang isang proximity sensor, na natutukoy ang isang bagay na malapit sa screen habang nasa tawag at pinapatay ang touch capabilities hanggang ang telepono ay nasa isang tiyak na distansya.

### Gawain - i-trigger ang pagtukoy ng kalidad ng prutas gamit ang isang distance sensor

Sundin ang kaukulang gabay upang gumamit ng proximity sensor upang matukoy ang isang bagay gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtual device](virtual-device-proximity.md)

## Data na ginagamit para sa isang fruit quality detector

Ang prototype fruit detector ay may maraming bahagi na nakikipag-ugnayan sa isa't isa.

![Ang mga bahagi na nakikipag-ugnayan sa isa't isa](../../../../../translated_images/tl/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.png)

* Isang proximity sensor na sumusukat sa distansya sa isang piraso ng prutas at nagpapadala nito sa IoT Hub
* Ang utos upang kontrolin ang camera na nagmumula sa IoT Hub patungo sa camera device
* Ang mga resulta ng image classification na ipinapadala sa IoT Hub
* Ang utos upang kontrolin ang isang LED upang mag-abiso kapag ang prutas ay hindi pa hinog na ipinapadala mula sa IoT Hub patungo sa device na may LED

Magandang ideya na tukuyin ang istruktura ng mga mensaheng ito bago mo buuin ang application.

> 💁 Halos lahat ng bihasang developer ay sa isang punto ng kanilang karera ay gumugol ng oras, araw, o kahit linggo sa paghahanap ng mga bug na dulot ng pagkakaiba sa data na ipinapadala kumpara sa inaasahan.

Halimbawa - kung nagpapadala ka ng impormasyon sa temperatura, paano mo ito tutukuyin sa JSON? Maaari kang magkaroon ng field na tinatawag na `temperature`, o maaari mong gamitin ang karaniwang abbreviation na `temp`.

```json
{
    "temperature": 20.7
}
```

kumpara sa:

```json
{
    "temp": 20.7
}
```

Kailangan mo ring isaalang-alang ang mga unit - ang temperatura ba ay nasa °C o °F? Kung sinusukat mo ang temperatura gamit ang isang consumer device at binago nila ang display units, kailangan mong tiyakin na ang mga unit na ipinapadala sa cloud ay nananatiling pare-pareho.

✅ Mag-research: Paano nagdulot ng problema sa $125 million Mars Climate Orbiter ang mga isyu sa unit?

Isipin ang data na ipinapadala para sa fruit quality detector. Paano mo tutukuyin ang bawat mensahe? Saan mo susuriin ang data at gagawa ng mga desisyon tungkol sa kung anong data ang ipapadala?

Halimbawa - pag-trigger ng image classification gamit ang proximity sensor. Ang IoT device ay sumusukat sa distansya, ngunit saan ginagawa ang desisyon? Ang device ba ang nagdedesisyon na ang prutas ay sapat na malapit at nagpapadala ng mensahe upang sabihin sa IoT Hub na i-trigger ang classification? O nagpapadala ba ito ng mga sukat ng distansya at hinahayaan ang IoT Hub na magdesisyon?

Ang sagot sa mga tanong na ito ay - depende. Ang bawat use case ay iba, kaya bilang isang IoT developer, kailangan mong maunawaan ang sistema na iyong binubuo, kung paano ito ginagamit, at ang data na natutukoy.

* Kung ang desisyon ay ginagawa ng IoT Hub, kailangan mong magpadala ng maraming sukat ng distansya.
* Kung magpapadala ka ng masyadong maraming mensahe, tataas ang gastos ng IoT Hub, at ang dami ng bandwidth na kinakailangan ng iyong IoT devices (lalo na sa isang pabrika na may milyun-milyong device). Maaari rin nitong pabagalin ang iyong device.
* Kung gagawin mo ang desisyon sa device, kakailanganin mong magbigay ng paraan upang i-configure ang device upang ma-fine tune ang makina.

## Paggamit ng developer devices upang gayahin ang maraming IoT devices

Upang mabuo ang iyong prototype, kakailanganin mong gamitin ang iyong IoT dev kit upang kumilos na parang maraming device, nagpapadala ng telemetry at tumutugon sa mga utos.

### Paggaya ng maraming IoT devices sa isang Raspberry Pi o virtual na IoT hardware

Kapag gumagamit ng single-board computer tulad ng Raspberry Pi, maaari kang magpatakbo ng maraming application nang sabay-sabay. Nangangahulugan ito na maaari kang gumaya ng maraming IoT devices sa pamamagitan ng paggawa ng maraming application, isa bawat 'IoT device'. Halimbawa, maaari mong ipatupad ang bawat device bilang isang hiwalay na Python file at patakbuhin ang mga ito sa iba't ibang terminal sessions.
> 💁 Tandaan na may ilang hardware na hindi gagana kapag ina-access ng maraming application na sabay-sabay na tumatakbo.
### Pagsasabay ng maraming device sa isang microcontroller

Mas mahirap magsabay ng maraming device sa microcontrollers. Hindi tulad ng single board computers, hindi ka maaaring magpatakbo ng maraming application nang sabay-sabay. Kailangan mong isama ang lahat ng lohika para sa bawat hiwalay na IoT device sa isang application.

Narito ang ilang mga mungkahi upang gawing mas madali ang prosesong ito:

* Gumawa ng isa o higit pang klase para sa bawat IoT device - halimbawa, mga klase na tinatawag na `DistanceSensor`, `ClassifierCamera`, `LEDController`. Ang bawat isa ay maaaring magkaroon ng sariling `setup` at `loop` na mga method na tinatawag ng pangunahing `setup` at `loop` na mga function.
* Pamahalaan ang mga utos sa isang lugar, at idirekta ang mga ito sa kaukulang klase ng device kung kinakailangan.
* Sa pangunahing `loop` na function, kailangan mong isaalang-alang ang timing para sa bawat iba't ibang device. Halimbawa, kung mayroon kang isang klase ng device na kailangang magproseso tuwing 10 segundo, at isa pang kailangang magproseso tuwing 1 segundo, sa pangunahing `loop` na function gumamit ng 1 segundo na delay. Ang bawat tawag sa `loop` ay nagti-trigger ng kaukulang code para sa device na kailangang magproseso tuwing isang segundo, at gumamit ng counter upang bilangin ang bawat loop, pinoproseso ang ibang device kapag umabot ang counter sa 10 (at i-reset ang counter pagkatapos).

## Paglipat sa produksyon

Ang prototype ang magiging batayan ng panghuling production system. Ang ilang mga pagkakaiba kapag lumipat ka sa produksyon ay:

* Mas matibay na mga bahagi - paggamit ng hardware na dinisenyo upang makayanan ang ingay, init, panginginig, at stress sa isang pabrika.
* Paggamit ng internal na komunikasyon - ang ilang mga bahagi ay direktang magkokonekta nang hindi dumadaan sa cloud, magpapadala lamang ng data sa cloud para maimbak. Kung paano ito gagawin ay depende sa setup ng pabrika, maaaring sa pamamagitan ng direktang komunikasyon, o sa pamamagitan ng pagpapatakbo ng bahagi ng IoT service sa edge gamit ang isang gateway device.
* Mga opsyon sa configuration - bawat pabrika at use case ay naiiba, kaya ang hardware ay kailangang ma-configure. Halimbawa, ang proximity sensor ay maaaring kailangang makakita ng iba't ibang prutas sa iba't ibang distansya. Sa halip na i-hard code ang distansya para mag-trigger ng classification, mas mainam na gawing configurable ito sa cloud, halimbawa gamit ang device twin.
* Awtomatikong pagtanggal ng prutas - sa halip na LED para mag-alerto na ang prutas ay hindi pa hinog, awtomatikong tatanggalin ito ng mga device.

✅ Mag-research: Sa anong iba pang paraan maaaring magkaiba ang production devices mula sa developer kits?

---

## 🚀 Hamon

Sa araling ito, natutunan mo ang ilang mga konsepto na kailangan mong malaman tungkol sa pagdidisenyo ng IoT system. Balikan ang mga nakaraang proyekto. Paano sila magkasya sa reference architecture na ipinakita sa itaas?

Pumili ng isa sa mga proyekto at mag-isip ng disenyo ng mas komplikadong solusyon na pinagsasama ang maraming kakayahan na lampas sa saklaw ng mga proyekto. Gumuhit ng architecture at isipin ang lahat ng mga device at serbisyo na kakailanganin mo.

Halimbawa - isang device para sa pagsubaybay sa sasakyan na pinagsasama ang GPS sa mga sensor upang subaybayan ang mga bagay tulad ng temperatura sa isang refrigerated truck, ang oras ng pag-on at pag-off ng makina, at ang pagkakakilanlan ng driver. Ano ang mga device na kasangkot, ang mga serbisyo na ginagamit, ang data na ipinapadala, at ang mga konsiderasyon sa seguridad at privacy?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Review at Pag-aaral ng Sarili

* Magbasa pa tungkol sa IoT architecture sa [Azure IoT reference architecture documentation sa Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Magbasa pa tungkol sa device twins sa [understand and use device twins in IoT Hub documentation sa Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Magbasa tungkol sa OPC-UA, isang machine-to-machine communication protocol na ginagamit sa industrial automation sa [OPC-UA page sa Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Takdang Aralin

[Build a fruit quality detector](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.