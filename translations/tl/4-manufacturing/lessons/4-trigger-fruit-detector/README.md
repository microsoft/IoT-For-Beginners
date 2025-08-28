<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T22:45:16+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "tl"
}
-->
# Pag-trigger ng detection ng kalidad ng prutas mula sa sensor

![Isang sketchnote overview ng aralin na ito](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Panimula

Ang isang IoT application ay hindi lamang isang solong device na kumukuha ng data at ipinapadala ito sa cloud. Madalas, ito ay binubuo ng maraming device na nagtutulungan upang kumuha ng data mula sa pisikal na mundo gamit ang mga sensor, gumawa ng desisyon batay sa data na iyon, at makipag-ugnayan pabalik sa pisikal na mundo sa pamamagitan ng mga actuator o visualizations.

Sa araling ito, matututo ka nang higit pa tungkol sa pagbuo ng mas kumplikadong IoT applications, kabilang ang paggamit ng maraming sensor, iba't ibang cloud services para sa pagsusuri at pag-iimbak ng data, at pagpapakita ng tugon sa pamamagitan ng actuator. Matututo ka kung paano i-architect ang prototype ng sistema ng kontrol sa kalidad ng prutas, kabilang ang paggamit ng proximity sensors upang i-trigger ang IoT application, at kung ano ang magiging arkitektura ng prototype na ito.

Sa araling ito, tatalakayin natin:

* [Pagbuo ng kumplikadong IoT applications](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Pagdisenyo ng sistema ng kontrol sa kalidad ng prutas](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Pag-trigger ng pagsusuri ng kalidad ng prutas mula sa sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Data na ginagamit para sa detector ng kalidad ng prutas](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Paggamit ng developer devices upang gayahin ang maraming IoT devices](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Paglipat sa produksyon](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Ito ang huling aralin sa proyektong ito, kaya pagkatapos makumpleto ang aralin at ang assignment, huwag kalimutang linisin ang iyong cloud services. Kakailanganin mo ang mga serbisyo upang makumpleto ang assignment, kaya tiyaking tapusin muna ito.
>
> Sumangguni sa [ang gabay sa paglilinis ng iyong proyekto](../../../clean-up.md) kung kinakailangan para sa mga tagubilin kung paano ito gawin.

## Pagbuo ng kumplikadong IoT applications

Ang IoT applications ay binubuo ng maraming bahagi. Kasama rito ang iba't ibang bagay at iba't ibang internet services.

Ang IoT applications ay maaaring ilarawan bilang *mga bagay* (devices) na nagpapadala ng data na bumubuo ng *mga insight*. Ang mga *insight* na ito ay bumubuo ng *mga aksyon* upang mapabuti ang isang negosyo o proseso. Halimbawa, isang makina (ang bagay) na nagpapadala ng data ng temperatura. Ang data na ito ay ginagamit upang suriin kung ang makina ay gumagana nang maayos (ang insight). Ang insight ay ginagamit upang ma-prioritize nang maaga ang iskedyul ng maintenance para sa makina (ang aksyon).

* Iba't ibang bagay ang kumukuha ng iba't ibang piraso ng data.
* Ang IoT services ay nagbibigay ng mga insight sa data na iyon, minsan pinapalawak ito gamit ang data mula sa karagdagang mga source.
* Ang mga insight na ito ay nagdudulot ng mga aksyon, kabilang ang pagkontrol sa mga actuator sa mga device, o pag-visualize ng data.

### Reference IoT architecture

![Isang reference IoT architecture](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.tl.png)

Ang diagram sa itaas ay nagpapakita ng isang reference IoT architecture.

> 🎓 Ang *reference architecture* ay isang halimbawa ng arkitektura na maaari mong gamitin bilang gabay kapag nagdidisenyo ng mga bagong sistema. Sa kasong ito, kung ikaw ay gumagawa ng bagong IoT system, maaari mong sundan ang reference architecture, pinapalitan ang iyong sariling mga device at serbisyo kung kinakailangan.

* **Mga Bagay** ay mga device na kumukuha ng data mula sa mga sensor, maaaring makipag-ugnayan sa edge services upang bigyang-kahulugan ang data, tulad ng image classifiers upang bigyang-kahulugan ang data ng imahe. Ang data mula sa mga device ay ipinapadala sa isang IoT service.
* **Mga Insight** ay nagmumula sa serverless applications, o mula sa analytics na tumatakbo sa nakaimbak na data.
* **Mga Aksyon** ay maaaring mga command na ipinapadala sa mga device, o visualization ng data na nagpapahintulot sa mga tao na gumawa ng desisyon.

![Isang reference IoT architecture](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.tl.png)

Ang diagram sa itaas ay nagpapakita ng ilan sa mga bahagi at serbisyo na tinalakay sa mga araling ito at kung paano sila nag-uugnay sa isang reference IoT architecture.

* **Mga Bagay** - nagsulat ka ng device code upang kumuha ng data mula sa mga sensor, at suriin ang mga imahe gamit ang Custom Vision na tumatakbo sa cloud at sa isang edge device. Ang data na ito ay ipinadala sa IoT Hub.
* **Mga Insight** - gumamit ka ng Azure Functions upang tumugon sa mga mensaheng ipinadala sa isang IoT Hub, at nag-imbak ng data para sa pagsusuri sa hinaharap sa Azure Storage.
* **Mga Aksyon** - kinontrol mo ang mga actuator batay sa mga desisyong ginawa sa cloud at mga command na ipinadala sa mga device, at nag-visualize ng data gamit ang Azure Maps.

✅ Pag-isipan ang iba pang IoT devices na nagamit mo, tulad ng mga smart home appliances. Ano ang mga bagay, insight, at aksyon na kasangkot sa device na iyon at sa software nito?

Ang pattern na ito ay maaaring palawakin nang malaki o maliit ayon sa iyong pangangailangan, na nagdaragdag ng mas maraming device at mas maraming serbisyo.

### Data at seguridad

Habang tinutukoy mo ang arkitektura ng iyong sistema, kailangan mong patuloy na isaalang-alang ang data at seguridad.

* Anong data ang ipinapadala at tinatanggap ng iyong device?
* Paano dapat protektahan at siguraduhin ang seguridad ng data na iyon?
* Paano dapat kontrolin ang access sa device at cloud service?

✅ Pag-isipan ang seguridad ng data ng anumang IoT devices na pagmamay-ari mo. Gaano karami sa data na iyon ang personal at dapat panatilihing pribado, parehong habang ipinapadala o kapag nakaimbak? Anong data ang hindi dapat iimbak?

## Pagdisenyo ng sistema ng kontrol sa kalidad ng prutas

Ngayon, gamitin natin ang ideya ng mga bagay, insight, at aksyon upang ilapat ito sa ating fruit quality detector at magdisenyo ng mas malaking end-to-end application.

Isipin na binigyan ka ng gawain na bumuo ng isang fruit quality detector na gagamitin sa isang processing plant. Ang prutas ay dumadaan sa isang conveyor belt system kung saan kasalukuyang sinusuri ng mga empleyado ang prutas nang mano-mano at inaalis ang anumang hindi hinog na prutas habang ito ay dumating. Upang mabawasan ang gastos, nais ng may-ari ng planta ng isang automated na sistema.

✅ Isa sa mga trend sa pag-usbong ng IoT (at teknolohiya sa pangkalahatan) ay ang mga manual na trabaho ay napapalitan ng mga makina. Mag-research: Ilang trabaho ang tinatayang mawawala dahil sa IoT? Ilang bagong trabaho ang malilikha sa paggawa ng IoT devices?

Kailangan mong bumuo ng isang sistema kung saan ang prutas ay natutukoy habang ito ay dumating sa conveyor belt, ito ay kinukunan ng larawan at sinusuri gamit ang isang AI model na tumatakbo sa edge. Ang mga resulta ay ipinapadala sa cloud upang maimbak, at kung ang prutas ay hindi hinog, isang notification ang ibinibigay upang maalis ang hindi hinog na prutas.

|   |   |
| - | - |
| **Mga Bagay** | Detector para sa prutas na dumating sa conveyor belt<br>Camera para kunan ng larawan at i-classify ang prutas<br>Edge device na tumatakbo ang classifier<br>Device para magbigay ng notification sa hindi hinog na prutas |
| **Mga Insight** | Magdesisyon na suriin ang hinog na prutas<br>Mag-imbak ng mga resulta ng ripeness classification<br>Tukuyin kung kailangan ng alerto para sa hindi hinog na prutas |
| **Mga Aksyon** | Magpadala ng command sa isang device upang kunan ng larawan ang prutas at suriin ito gamit ang image classifier<br>Magpadala ng command sa isang device upang magbigay ng alerto na ang prutas ay hindi hinog |

### Pag-prototype ng iyong application

![Isang reference IoT architecture para sa pagsusuri ng kalidad ng prutas](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.tl.png)

Ang diagram sa itaas ay nagpapakita ng isang reference architecture para sa prototype application na ito.

* Ang isang IoT device na may proximity sensor ay natutukoy ang pagdating ng prutas. Ito ay nagpapadala ng mensahe sa cloud upang sabihin na may prutas na natukoy.
* Ang isang serverless application sa cloud ay nagpapadala ng command sa isa pang device upang kunan ng larawan at i-classify ang imahe.
* Ang isang IoT device na may camera ay kumukuha ng larawan at ipinapadala ito sa isang image classifier na tumatakbo sa edge. Ang mga resulta ay ipinapadala sa cloud.
* Ang isang serverless application sa cloud ay nag-iimbak ng impormasyong ito upang ma-analyze sa hinaharap kung anong porsyento ng prutas ang hindi hinog. Kung ang prutas ay hindi hinog, ito ay nagpapadala ng command sa isa pang IoT device upang magbigay ng alerto sa mga manggagawa sa pabrika na may hindi hinog na prutas sa pamamagitan ng LED.

> 💁 Ang buong IoT application na ito ay maaaring ipatupad bilang isang solong device, na may lahat ng logic upang simulan ang image classification at kontrolin ang LED na naka-built in. Maaari itong gumamit ng IoT Hub upang subaybayan ang bilang ng mga hindi hinog na prutas na natukoy at i-configure ang device. Sa araling ito, ito ay pinalawak upang ipakita ang mga konsepto para sa malakihang IoT applications.

Para sa prototype, ipapatupad mo ang lahat ng ito sa isang solong device. Kung gumagamit ka ng microcontroller, gagamit ka ng hiwalay na edge device upang patakbuhin ang image classifier. Natutunan mo na ang karamihan sa mga bagay na kakailanganin mo upang mabuo ito.

## Pag-trigger ng pagsusuri ng kalidad ng prutas mula sa sensor

Ang IoT device ay nangangailangan ng isang uri ng trigger upang ipahiwatig kung kailan handa na ang prutas na i-classify. Ang isang trigger para dito ay ang pagsukat kung ang prutas ay nasa tamang lokasyon sa conveyor belt sa pamamagitan ng pagsukat ng distansya sa sensor.

![Ang mga proximity sensor ay nagpapadala ng laser beams sa mga bagay tulad ng saging at sinusukat ang oras hanggang sa bumalik ang beam](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fea000156233b32fd24fad3707ec69b8bdd8d312b7af85156d.tl.png)

Ang mga proximity sensor ay maaaring gamitin upang sukatin ang distansya mula sa sensor patungo sa isang bagay. Karaniwan silang nagpapadala ng beam ng electromagnetic radiation tulad ng laser beam o infra-red light, pagkatapos ay natutukoy ang radiation na bumabalik mula sa isang bagay. Ang oras sa pagitan ng pagpapadala ng laser beam at ang signal na bumabalik ay maaaring gamitin upang kalkulahin ang distansya sa sensor.

> 💁 Malamang na nagamit mo na ang mga proximity sensor nang hindi mo namamalayan. Karamihan sa mga smartphone ay pinapatay ang screen kapag inilalapit mo ito sa iyong tainga upang maiwasan ang aksidenteng pag-end ng tawag gamit ang iyong earlobe, at ito ay gumagana gamit ang proximity sensor, na natutukoy ang isang bagay na malapit sa screen habang nasa tawag at pinapatay ang touch capabilities hanggang ang telepono ay nasa tiyak na distansya.

### Gawain - pag-trigger ng detection ng kalidad ng prutas mula sa distance sensor

Sundin ang kaukulang gabay upang gamitin ang proximity sensor upang matukoy ang isang bagay gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtual device](virtual-device-proximity.md)

## Data na ginagamit para sa detector ng kalidad ng prutas

Ang prototype fruit detector ay may maraming bahagi na nakikipag-ugnayan sa isa't isa.

![Ang mga bahagi na nakikipag-ugnayan sa isa't isa](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.tl.png)

* Isang proximity sensor na sumusukat sa distansya sa isang piraso ng prutas at ipinapadala ito sa IoT Hub
* Ang command upang kontrolin ang camera na nagmumula sa IoT Hub patungo sa camera device
* Ang mga resulta ng image classification na ipinapadala sa IoT Hub
* Ang command upang kontrolin ang LED upang magbigay ng alerto kapag ang prutas ay hindi hinog na ipinapadala mula sa IoT Hub patungo sa device na may LED

Magandang ideya na tukuyin ang istruktura ng mga mensaheng ito nang maaga, bago mo buuin ang application.

> 💁 Halos lahat ng may karanasan na developer ay sa isang punto sa kanilang karera ay gumugol ng oras, araw, o kahit linggo sa paghahanap ng mga bug na sanhi ng pagkakaiba sa data na ipinapadala kumpara sa inaasahan.

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

✅ Mag-research: Paano nagdulot ng problema sa unit ang pagbagsak ng $125 million Mars Climate Orbiter?

Pag-isipan ang data na ipinapadala para sa fruit quality detector. Paano mo tutukuyin ang bawat mensahe? Saan mo susuriin ang data at gagawa ng desisyon tungkol sa kung anong data ang ipapadala?

Halimbawa - pag-trigger ng image classification gamit ang proximity sensor. Ang IoT device ay sumusukat sa distansya, ngunit saan ginagawa ang desisyon? Ang device ba ang magdedesisyon na ang prutas ay malapit na at magpapadala ng mensahe upang sabihin sa IoT Hub na i-trigger ang classification? O magpapadala ba ito ng mga sukat ng distansya at hayaan ang IoT Hub na magdesisyon?

Ang sagot sa mga tanong na ito ay - depende. Ang bawat use case ay iba, kaya bilang IoT developer, kailangan mong maunawaan ang sistema na iyong binubuo, kung paano ito ginagamit, at ang data na natutukoy.

* Kung ang desisyon ay ginagawa ng IoT Hub, kailangan mong magpadala ng maraming sukat ng distansya.
* Kung magpapadala ka ng masyadong maraming mensahe, tataas ang gastos ng IoT Hub, at ang dami ng bandwidth na kinakailangan ng iyong IoT devices (lalo na sa isang pabrika na may milyon-milyong device). Maaari rin nitong pabagalin ang iyong device.
* Kung gagawin mo ang desisyon sa device, kakailanganin mong magbigay ng paraan upang i-configure ang device para sa fine tuning ng makina.

## Paggamit ng developer devices upang gayahin ang maraming IoT devices

Upang buuin ang iyong prototype, kakailanganin mong ang iyong IoT dev kit ay kumilos na parang maraming device, nagpapadala ng telemetry at tumutugon sa mga command.

### Paggaya ng maraming IoT devices sa Raspberry Pi o virtual IoT hardware

Kapag gumagamit ng single-board computer tulad ng Raspberry Pi, maaari kang magpatakbo ng maraming applications nang sabay-sabay. Nangangahulugan ito na maaari mong gayahin ang maraming IoT devices sa pamamagitan ng paggawa ng maraming applications, isa bawat 'IoT device'. Halimbawa, maaari mong ipatupad ang bawat device bilang isang hiwalay na Python file at patakbuhin ang mga ito sa iba't ibang terminal sessions.
> 💁 Tandaan na may ilang hardware na hindi gagana kapag ina-access ng maraming application na sabay-sabay na tumatakbo.
### Pagsasabay ng Maraming Device sa Isang Microcontroller

Mas komplikado ang pagsasabay ng maraming device sa isang microcontroller. Hindi tulad ng single board computers, hindi mo maaaring patakbuhin ang maraming aplikasyon nang sabay-sabay. Kailangan mong isama ang lahat ng lohika para sa bawat hiwalay na IoT device sa iisang aplikasyon.

Narito ang ilang mungkahi upang gawing mas madali ang prosesong ito:

* Gumawa ng isa o higit pang klase para sa bawat IoT device - halimbawa, mga klase na tinatawag na `DistanceSensor`, `ClassifierCamera`, `LEDController`. Ang bawat isa ay maaaring magkaroon ng sarili nitong mga `setup` at `loop` na mga pamamaraan na tinatawag ng pangunahing `setup` at `loop` na mga function.
* Pangasiwaan ang mga utos sa iisang lugar, at idirekta ang mga ito sa kaukulang klase ng device kung kinakailangan.
* Sa pangunahing `loop` na function, kailangan mong isaalang-alang ang timing para sa bawat iba't ibang device. Halimbawa, kung mayroon kang isang klase ng device na kailangang magproseso tuwing 10 segundo, at isa pang kailangang magproseso tuwing 1 segundo, gamitin ang 1 segundong delay sa iyong pangunahing `loop` na function. Ang bawat tawag sa `loop` ay magti-trigger ng kaukulang code para sa device na kailangang magproseso bawat segundo, at gumamit ng counter upang bilangin ang bawat loop, iproseso ang iba pang device kapag umabot ang counter sa 10 (at i-reset ang counter pagkatapos nito).

## Paglipat sa Produksyon

Ang prototype ang magiging batayan ng panghuling production system. Narito ang ilang pagkakaiba kapag lumipat ka na sa produksyon:

* Mga ruggedized na bahagi - paggamit ng hardware na idinisenyo upang makayanan ang ingay, init, panginginig, at stress sa isang pabrika.
* Paggamit ng internal na komunikasyon - ang ilang mga bahagi ay direktang magkokomunikasyon upang maiwasan ang pagdaan sa cloud, at magpapadala lamang ng data sa cloud para maimbak. Kung paano ito gagawin ay depende sa setup ng pabrika, maaaring sa pamamagitan ng direktang komunikasyon o sa pamamagitan ng pagpapatakbo ng bahagi ng IoT service sa edge gamit ang isang gateway device.
* Mga opsyon sa konfigurasyon - bawat pabrika at use case ay naiiba, kaya kailangang maging configurable ang hardware. Halimbawa, maaaring kailangang mag-detect ng proximity sensor ng iba't ibang prutas sa iba't ibang distansya. Sa halip na i-hard code ang distansya para ma-trigger ang classification, mas mainam na gawing configurable ito sa cloud, halimbawa gamit ang isang device twin.
* Awtomatikong pagtanggal ng prutas - sa halip na gumamit ng LED upang ipaalam na ang prutas ay hilaw, maaaring gumamit ng mga awtomatikong device upang alisin ito.

✅ Mag-research: Sa anong iba pang paraan naiiba ang mga production device mula sa mga developer kit?

---

## 🚀 Hamon

Sa araling ito, natutunan mo ang ilang konsepto na kailangan mong malaman tungkol sa pagdidisenyo ng IoT system. Balikan ang mga nakaraang proyekto. Paano sila umaangkop sa reference architecture na ipinakita sa itaas?

Pumili ng isa sa mga proyekto at isipin ang disenyo ng mas komplikadong solusyon na pinagsasama ang maraming kakayahan na lampas sa saklaw ng mga proyekto. Gumuhit ng arkitektura at isipin ang lahat ng mga device at serbisyo na kakailanganin mo.

Halimbawa - isang device para sa pagsubaybay ng sasakyan na pinagsasama ang GPS sa mga sensor upang subaybayan ang mga bagay tulad ng temperatura sa isang refrigerated truck, ang oras ng pag-on at pag-off ng makina, at ang pagkakakilanlan ng driver. Ano ang mga device na kasangkot, ang mga serbisyong ginagamit, ang data na ipinapadala, at ang mga konsiderasyon sa seguridad at privacy?

## Post-lecture Quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa IoT architecture sa [Azure IoT reference architecture documentation sa Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Magbasa pa tungkol sa device twins sa [understand and use device twins in IoT Hub documentation sa Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Magbasa tungkol sa OPC-UA, isang machine-to-machine communication protocol na ginagamit sa industrial automation sa [OPC-UA page sa Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Gawain

[Magbuo ng fruit quality detector](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakatandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.