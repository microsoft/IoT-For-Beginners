<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-28T01:44:04+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "tl"
}
-->
## Hulaan ang paglaki ng halaman gamit ang IoT

![Isang sketchnote overview ng araling ito](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Panimula

Ang mga halaman ay nangangailangan ng ilang bagay upang lumaki - tubig, carbon dioxide, sustansya, liwanag, at init. Sa araling ito, matututunan mo kung paano kalkulahin ang bilis ng paglaki at pagkahinog ng mga halaman sa pamamagitan ng pagsukat ng temperatura ng hangin.

Sa araling ito, tatalakayin natin:

* [Digital agriculture](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Bakit mahalaga ang temperatura sa pagsasaka?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Sukatin ang temperatura ng paligid](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Growing degree days (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Kalkulahin ang GDD gamit ang data mula sa temperature sensor](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digital agriculture

Ang Digital Agriculture ay binabago ang paraan ng pagsasaka gamit ang mga kasangkapan upang mangolekta, mag-imbak, at mag-analisa ng data mula sa pagsasaka. Tayo ay nasa panahon na tinatawag na 'Fourth Industrial Revolution' ng World Economic Forum, at ang pag-usbong ng digital agriculture ay tinatawag na 'Fourth Agricultural Revolution', o 'Agriculture 4.0'.

> 🎓 Ang terminong Digital Agriculture ay kasama rin ang buong 'agriculture value chain', na tumutukoy sa buong proseso mula sa sakahan hanggang sa hapag-kainan. Kasama dito ang pagsubaybay sa kalidad ng ani habang ito ay ipinapadala at pinoproseso, mga sistema ng warehouse at e-commerce, pati na rin ang mga app para sa pagrenta ng traktora!

Ang mga pagbabagong ito ay nagbibigay-daan sa mga magsasaka na pataasin ang ani, gumamit ng mas kaunting pataba at pestisidyo, at mas epektibong magpatubig. Bagamat pangunahing ginagamit sa mas mayayamang bansa, ang mga sensor at iba pang mga aparato ay unti-unting bumababa ang presyo, kaya mas nagiging abot-kaya sa mga umuunlad na bansa.

Ilan sa mga teknik na pinapagana ng digital agriculture ay:

* Pagsukat ng temperatura - ang pagsukat ng temperatura ay nagbibigay-daan sa mga magsasaka na hulaan ang paglaki at pagkahinog ng halaman.
* Automated na pagdidilig - ang pagsukat ng moisture sa lupa at pag-on ng irrigation system kapag ang lupa ay masyadong tuyo, sa halip na nakatakdang oras ng pagdidilig. Ang nakatakdang oras ng pagdidilig ay maaaring magresulta sa kulang na tubig sa mga pananim sa panahon ng mainit at tuyo na panahon, o sobrang tubig sa panahon ng ulan. Sa pamamagitan ng pagdidilig lamang kapag kailangan ng lupa, maaaring ma-optimize ng mga magsasaka ang paggamit ng tubig.
* Kontrol sa peste - maaaring gumamit ang mga magsasaka ng mga camera sa mga automated na robot o drone upang suriin ang mga peste, pagkatapos ay maglagay ng pestisidyo kung saan lamang kinakailangan, na nagbabawas sa dami ng pestisidyo na ginagamit at nagbabawas ng pag-agos ng pestisidyo sa lokal na suplay ng tubig.

✅ Mag-research. Anong iba pang mga teknik ang ginagamit upang mapabuti ang ani sa pagsasaka?

> 🎓 Ang terminong 'Precision Agriculture' ay tumutukoy sa pagmamasid, pagsukat, at pagtugon sa mga pananim sa bawat field, o kahit sa mga bahagi ng field. Kasama dito ang pagsukat ng tubig, sustansya, at antas ng peste at ang tumpak na pagtugon, tulad ng pagdidilig lamang sa isang maliit na bahagi ng field.

## Bakit mahalaga ang temperatura sa pagsasaka?

Kapag natututo tungkol sa mga halaman, kadalasang itinuturo sa mga mag-aaral ang kahalagahan ng tubig, liwanag, carbon dioxide, at sustansya. Ang mga halaman ay nangangailangan din ng init upang lumaki - ito ang dahilan kung bakit namumulaklak ang mga halaman sa tagsibol habang tumataas ang temperatura, kung bakit ang mga snowdrop o daffodil ay maaaring tumubo nang maaga dahil sa maikling mainit na panahon, at kung bakit ang mga hothouse at greenhouse ay napakahusay sa pagpapalago ng mga halaman.

> 🎓 Ang mga hothouse at greenhouse ay gumagawa ng magkatulad na trabaho, ngunit may mahalagang pagkakaiba. Ang mga hothouse ay pinapainit nang artipisyal at nagbibigay-daan sa mga magsasaka na kontrolin ang temperatura nang mas tumpak, ang mga greenhouse ay umaasa sa araw para sa init at karaniwang ang tanging kontrol ay mga bintana o iba pang mga bukas upang palabasin ang init.

Ang mga halaman ay may base o minimum na temperatura, optimal na temperatura, at maximum na temperatura, lahat ay batay sa pang-araw-araw na average na temperatura.

* Base temperature - ito ang minimum na pang-araw-araw na average na temperatura na kailangan ng isang halaman upang lumaki.
* Optimum temperature - ito ang pinakamahusay na pang-araw-araw na average na temperatura upang makamit ang pinakamabilis na paglaki.
* Maximum temperature - ito ang maximum na temperatura na kayang tiisin ng isang halaman. Kapag lumampas dito, titigil ang halaman sa paglaki upang magtipid ng tubig at manatiling buhay.

> 💁 Ito ay mga average na temperatura, na kinukuha mula sa pang-araw-araw at panggabing temperatura. Ang mga halaman ay nangangailangan din ng iba't ibang temperatura sa araw at gabi upang mas epektibong mag-photosynthesize at magtipid ng enerhiya sa gabi.

Ang bawat uri ng halaman ay may iba't ibang halaga para sa kanilang base, optimal, at maximum. Ito ang dahilan kung bakit ang ilang mga halaman ay umuunlad sa maiinit na bansa, at ang iba naman sa malamig na bansa.

✅ Mag-research. Para sa anumang halaman na mayroon ka sa iyong hardin, paaralan, o lokal na parke, tingnan kung maaari mong mahanap ang base temperature nito.

![Isang graph na nagpapakita ng bilis ng paglaki na tumataas habang tumataas ang temperatura, pagkatapos bumababa kapag masyadong mataas ang temperatura](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca832baa8dcb8d4adcbb67304074ce50e94ac8faae95975177f9.tl.png)

Ang graph sa itaas ay nagpapakita ng halimbawa ng bilis ng paglaki kaugnay ng temperatura. Hanggang sa base temperature, walang paglaki. Ang bilis ng paglaki ay tumataas hanggang sa optimal na temperatura, pagkatapos ay bumababa pagkatapos maabot ang peak na ito. 

Ang hugis ng graph na ito ay nag-iiba mula sa isang uri ng halaman patungo sa isa pa. Ang ilan ay may mas matarik na pagbaba pagkatapos ng optimal, ang iba ay may mas mabagal na pagtaas mula sa base patungo sa optimal.

> 💁 Para sa isang magsasaka na makamit ang pinakamahusay na paglaki, kailangan nilang malaman ang tatlong halaga ng temperatura at maunawaan ang hugis ng mga graph para sa mga halaman na kanilang itinatanim.

Kung ang isang magsasaka ay may kontrol sa temperatura, halimbawa sa isang komersyal na hothouse, maaari nilang i-optimize ito para sa kanilang mga halaman. Ang isang komersyal na hothouse na nagtatanim ng mga kamatis, halimbawa, ay itatakda ang temperatura sa humigit-kumulang 25°C sa araw at 20°C sa gabi upang makamit ang pinakamabilis na paglaki.

> 🍅 Sa pamamagitan ng pagsasama ng mga temperaturang ito sa artipisyal na ilaw, pataba, at kontroladong antas ng CO
Ang code na ito ay nagbubukas ng CSV file, pagkatapos ay nagdadagdag ng bagong row sa dulo. Ang row ay naglalaman ng kasalukuyang petsa at oras na naka-format sa paraang madaling basahin ng tao, kasunod ng temperatura na natanggap mula sa IoT device. Ang data ay naka-imbak sa [ISO 8601 format](https://wikipedia.org/wiki/ISO_8601) kasama ang timezone, ngunit walang microseconds.

1. Patakbuhin ang code na ito tulad ng dati, siguraduhing nagpapadala ng data ang iyong IoT device. Ang isang CSV file na tinatawag na `temperature.csv` ay malilikha sa parehong folder. Kapag binuksan mo ito, makikita mo ang mga petsa/oras at mga sukat ng temperatura:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Patakbuhin ang code na ito nang mas matagal upang makakuha ng data. Mas mainam na patakbuhin ito nang buong araw upang makalikom ng sapat na data para sa GDD calculations.

    
> 💁 Kung gumagamit ka ng Virtual IoT Device, piliin ang random checkbox at magtakda ng saklaw upang maiwasang makuha ang parehong temperatura tuwing ibinabalik ang halaga ng temperatura.
    ![Piliin ang random checkbox at magtakda ng saklaw](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f8c76616b10c7c23a6592321bb1a6310e0b481e72f97d23b3.tl.png) 

    > 💁 Kung nais mong patakbuhin ito nang buong araw, siguraduhin na ang computer kung saan tumatakbo ang iyong server code ay hindi matutulog, alinman sa pamamagitan ng pagbabago ng iyong power settings, o pagpapatakbo ng isang bagay tulad ng [itong keep system active Python script](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Makikita mo ang code na ito sa [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server) folder.

### Gawain - kalkulahin ang GDD gamit ang naka-imbak na data

Kapag nakakuha na ang server ng data ng temperatura, maaaring kalkulahin ang GDD para sa isang halaman.

Ang mga hakbang upang gawin ito nang manu-mano ay:

1. Hanapin ang base temperature para sa halaman. Halimbawa, para sa strawberries ang base temperature ay 10°C.

1. Mula sa `temperature.csv`, hanapin ang pinakamataas at pinakamababang temperatura para sa araw.

1. Gamitin ang GDD calculation na ibinigay kanina upang kalkulahin ang GDD.

Halimbawa, kung ang pinakamataas na temperatura para sa araw ay 25°C, at ang pinakamababa ay 12°C:

![GDD = 25 + 12 hinati sa 2, pagkatapos ay ibawas ang 10 mula sa resulta na nagbibigay ng 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.tl.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Samakatuwid, ang strawberries ay nakatanggap ng **8.5** GDD. Ang strawberries ay nangangailangan ng humigit-kumulang 250 GDD upang magbunga, kaya medyo matagal pa.

---

## 🚀 Hamon

Ang mga halaman ay nangangailangan ng higit pa sa init upang lumago. Ano pa ang mga kinakailangan?

Para sa mga ito, alamin kung may mga sensors na maaaring sukatin ang mga ito. Paano naman ang mga actuators upang kontrolin ang mga antas na ito? Paano mo pagsasama-samahin ang isa o higit pang IoT devices upang i-optimize ang paglago ng halaman?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa digital agriculture sa [Digital Agriculture Wikipedia page](https://wikipedia.org/wiki/Digital_agriculture). Basahin din ang tungkol sa precision agriculture sa [Precision Agriculture Wikipedia page](https://wikipedia.org/wiki/Precision_agriculture).
* Ang buong growing degree days calculation ay mas kumplikado kaysa sa pinasimpleng bersyon na ibinigay dito. Magbasa pa tungkol sa mas kumplikadong equation at kung paano harapin ang mga temperatura na mas mababa sa baseline sa [Growing Degree Day Wikipedia page](https://wikipedia.org/wiki/Growing_degree-day).
* Maaaring maging limitado ang pagkain sa hinaharap kung patuloy nating gagamitin ang parehong mga pamamaraan sa pagsasaka. Alamin ang higit pa tungkol sa mga hi-tech na pamamaraan ng pagsasaka sa [Hi-Tech Farms of Future video sa YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Takdang-Aralin

[I-visualize ang GDD data gamit ang isang Jupyter Notebook](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.