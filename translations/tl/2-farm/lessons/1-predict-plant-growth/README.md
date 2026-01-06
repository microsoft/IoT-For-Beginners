<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T21:25:27+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "tl"
}
-->
## Hulaan ang paglago ng halaman gamit ang IoT

![Isang sketchnote overview ng aralin na ito](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Panimula

Ang mga halaman ay nangangailangan ng ilang bagay upang lumago - tubig, carbon dioxide, sustansya, liwanag, at init. Sa aralin na ito, matututuhan mo kung paano kalkulahin ang bilis ng paglago at pagkahinog ng mga halaman sa pamamagitan ng pagsukat ng temperatura ng hangin.

Sa aralin na ito, tatalakayin natin:

* [Digital agriculture](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Bakit mahalaga ang temperatura sa pagsasaka?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Sukatin ang temperatura ng paligid](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Growing degree days (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Kalkulahin ang GDD gamit ang data ng temperature sensor](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digital agriculture

Ang Digital Agriculture ay binabago ang paraan ng pagsasaka gamit ang mga tool upang mangolekta, mag-imbak, at mag-analyze ng data mula sa pagsasaka. Tayo ay nasa panahon na tinatawag na 'Fourth Industrial Revolution' ng World Economic Forum, at ang pag-usbong ng digital agriculture ay tinatawag na 'Fourth Agricultural Revolution', o 'Agriculture 4.0'.

> 🎓 Ang terminong Digital Agriculture ay kasama rin ang buong 'agriculture value chain', na tumutukoy sa buong proseso mula sa sakahan hanggang sa hapag-kainan. Kasama dito ang pagsubaybay sa kalidad ng ani habang ito ay ipinapadala at pinoproseso, mga sistema ng warehouse at e-commerce, pati na rin ang mga app para sa pagrenta ng traktora!

Ang mga pagbabagong ito ay nagbibigay-daan sa mga magsasaka na pataasin ang ani, gumamit ng mas kaunting pataba at pestisidyo, at mas epektibong magpatubig. Bagama't pangunahing ginagamit sa mas mayayamang bansa, ang mga sensor at iba pang mga device ay unti-unting bumababa ang presyo, kaya mas nagiging accessible sa mga umuunlad na bansa.

Ilan sa mga teknik na pinapagana ng digital agriculture ay:

* Pagsukat ng temperatura - ang pagsukat ng temperatura ay nagbibigay-daan sa mga magsasaka na hulaan ang paglago at pagkahinog ng halaman.
* Automated na pagdidilig - ang pagsukat ng moisture ng lupa at pag-on ng mga sistema ng irigasyon kapag ang lupa ay masyadong tuyo, sa halip na nakatakdang oras ng pagdidilig. Ang nakatakdang pagdidilig ay maaaring magresulta sa kulang na tubig sa mga pananim sa panahon ng mainit at tuyong panahon, o sobrang tubig sa panahon ng ulan. Sa pamamagitan ng pagdidilig lamang kapag kailangan ng lupa, maaaring ma-optimize ng mga magsasaka ang paggamit ng tubig.
* Kontrol sa peste - maaaring gumamit ang mga magsasaka ng mga camera sa mga automated na robot o drone upang suriin ang mga peste, pagkatapos ay maglagay ng pestisidyo lamang kung saan kinakailangan, na nagbabawas sa dami ng pestisidyo na ginagamit at nagbabawas ng pag-agos ng pestisidyo sa lokal na suplay ng tubig.

✅ Mag-research. Anong iba pang mga teknik ang ginagamit upang mapabuti ang ani ng pagsasaka?

> 🎓 Ang terminong 'Precision Agriculture' ay tumutukoy sa pagmamasid, pagsukat, at pagtugon sa mga pananim sa bawat field, o kahit sa mga bahagi ng field. Kasama dito ang pagsukat ng tubig, sustansya, at antas ng peste at ang tumpak na pagtugon, tulad ng pagdidilig lamang sa isang maliit na bahagi ng field.

## Bakit mahalaga ang temperatura sa pagsasaka?

Kapag pinag-aaralan ang mga halaman, kadalasang itinuturo sa mga estudyante ang kahalagahan ng tubig, liwanag, carbon dioxide, at sustansya. Ang mga halaman ay nangangailangan din ng init upang lumago - ito ang dahilan kung bakit namumulaklak ang mga halaman sa tagsibol kapag tumataas ang temperatura, kung bakit ang mga snowdrop o daffodil ay maaaring tumubo nang maaga dahil sa maikling mainit na panahon, at kung bakit ang mga hothouse at greenhouse ay napakahusay sa pagpapalago ng mga halaman.

> 🎓 Ang mga hothouse at greenhouse ay gumagawa ng magkatulad na trabaho, ngunit may mahalagang pagkakaiba. Ang mga hothouse ay pinapainit nang artipisyal at nagbibigay-daan sa mga magsasaka na kontrolin ang temperatura nang mas tumpak, ang mga greenhouse ay umaasa sa araw para sa init at kadalasang ang tanging kontrol ay mga bintana o iba pang mga bukas upang palabasin ang init.

Ang mga halaman ay may base o minimum na temperatura, optimal na temperatura, at maximum na temperatura, lahat ay batay sa pang-araw-araw na average na temperatura.

* Base temperature - ito ang minimum na pang-araw-araw na average na temperatura na kailangan ng isang halaman upang lumago.
* Optimum temperature - ito ang pinakamahusay na pang-araw-araw na average na temperatura upang makamit ang pinakamabilis na paglago.
* Maximum temperature - ito ang maximum na temperatura na kayang tiisin ng isang halaman. Kapag lumampas dito, titigil ang halaman sa paglago nito upang magtipid ng tubig at manatiling buhay.

> 💁 Ito ay mga average na temperatura, na kinukuha mula sa pang-araw-araw at panggabing temperatura. Ang mga halaman ay nangangailangan din ng iba't ibang temperatura sa araw at gabi upang mas mahusay na mag-photosynthesize at magtipid ng enerhiya sa gabi.

Ang bawat uri ng halaman ay may iba't ibang halaga para sa kanilang base, optimal, at maximum. Ito ang dahilan kung bakit ang ilang mga halaman ay umuunlad sa maiinit na bansa, at ang iba naman sa malamig na bansa.

✅ Mag-research. Para sa anumang mga halaman na mayroon ka sa iyong hardin, paaralan, o lokal na parke, tingnan kung maaari mong mahanap ang base temperature.

![Isang graph na nagpapakita ng bilis ng paglago na tumataas habang tumataas ang temperatura, pagkatapos ay bumababa kapag masyadong mataas ang temperatura](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.tl.png)

Ang graph sa itaas ay nagpapakita ng isang halimbawa ng graph ng bilis ng paglago sa temperatura. Hanggang sa base temperature, walang paglago. Ang bilis ng paglago ay tumataas hanggang sa optimum temperature, pagkatapos ay bumababa pagkatapos maabot ang peak na ito. 

Ang hugis ng graph na ito ay nag-iiba mula sa bawat uri ng halaman. Ang ilan ay may mas matarik na pagbaba pagkatapos ng optimum, ang ilan ay may mas mabagal na pagtaas mula sa base hanggang sa optimum.

> 💁 Para sa isang magsasaka na makuha ang pinakamahusay na paglago, kailangan nilang malaman ang tatlong halaga ng temperatura at maunawaan ang hugis ng mga graph para sa mga halaman na kanilang itinatanim.

Kung ang isang magsasaka ay may kontrol sa temperatura, halimbawa sa isang komersyal na hothouse, maaari nilang i-optimize para sa kanilang mga halaman. Ang isang komersyal na hothouse na nagtatanim ng mga kamatis, halimbawa, ay may temperatura na nakatakda sa humigit-kumulang 25°C sa araw at 20°C sa gabi upang makamit ang pinakamabilis na paglago.

> 🍅 Sa pamamagitan ng pagsasama ng mga temperaturang ito sa artipisyal na ilaw, pataba, at kontroladong antas ng CO
Ang code na ito ay nagbubukas ng CSV file, pagkatapos ay nagdaragdag ng bagong row sa dulo. Ang row ay naglalaman ng kasalukuyang petsa at oras na naka-format sa paraang madaling maunawaan, kasunod ng temperatura na natanggap mula sa IoT device. Ang data ay naka-imbak sa [ISO 8601 format](https://wikipedia.org/wiki/ISO_8601) kasama ang timezone, ngunit walang microseconds.

1. Patakbuhin ang code na ito tulad ng dati, siguraduhing nagpapadala ng data ang iyong IoT device. Ang isang CSV file na tinatawag na `temperature.csv` ay malilikha sa parehong folder. Kapag binuksan mo ito, makikita mo ang mga petsa/oras at mga sukat ng temperatura:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Patakbuhin ang code na ito nang ilang oras upang makuha ang data. Mas mainam na patakbuhin ito nang buong araw upang makalikom ng sapat na data para sa GDD calculations.

    
> 💁 Kung gumagamit ka ng Virtual IoT Device, piliin ang random checkbox at magtakda ng saklaw upang maiwasan ang pagkuha ng parehong temperatura tuwing ibinabalik ang halaga ng temperatura.
    ![Piliin ang random checkbox at magtakda ng saklaw](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.tl.png) 

    > 💁 Kung nais mong patakbuhin ito nang buong araw, siguraduhin na ang computer kung saan tumatakbo ang iyong server code ay hindi mag-sleep, alinman sa pamamagitan ng pagbabago ng iyong power settings, o paggamit ng isang bagay tulad ng [this keep system active Python script](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Makikita mo ang code na ito sa [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server) folder.

### Gawain - kalkulahin ang GDD gamit ang naka-imbak na data

Kapag nakakuha na ang server ng data ng temperatura, maaaring kalkulahin ang GDD para sa isang halaman.

Ang mga hakbang upang gawin ito nang manu-mano ay:

1. Hanapin ang base temperature para sa halaman. Halimbawa, para sa strawberries ang base temperature ay 10°C.

1. Mula sa `temperature.csv`, hanapin ang pinakamataas at pinakamababang temperatura para sa araw.

1. Gamitin ang GDD calculation na ibinigay kanina upang kalkulahin ang GDD.

Halimbawa, kung ang pinakamataas na temperatura para sa araw ay 25°C, at ang pinakamababa ay 12°C:

![GDD = 25 + 12 divided by 2, pagkatapos ay ibawas ang 10 mula sa resulta na nagbibigay ng 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.tl.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Samakatuwid, ang strawberries ay nakatanggap ng **8.5** GDD. Ang strawberries ay nangangailangan ng humigit-kumulang 250 GDD upang magbunga, kaya medyo matagal pa.

---

## 🚀 Hamon

Ang mga halaman ay nangangailangan ng higit pa sa init upang lumago. Ano pa ang mga kinakailangan?

Para sa mga ito, hanapin kung may mga sensors na maaaring sukatin ang mga ito. Paano naman ang mga actuators upang kontrolin ang mga antas na ito? Paano mo bubuuin ang isa o higit pang IoT devices upang i-optimize ang paglago ng halaman?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa digital agriculture sa [Digital Agriculture Wikipedia page](https://wikipedia.org/wiki/Digital_agriculture). Basahin din ang tungkol sa precision agriculture sa [Precision Agriculture Wikipedia page](https://wikipedia.org/wiki/Precision_agriculture).
* Ang buong growing degree days calculation ay mas kumplikado kaysa sa simpleng ibinigay dito. Magbasa pa tungkol sa mas kumplikadong equation at kung paano harapin ang mga temperatura na mas mababa sa baseline sa [Growing Degree Day Wikipedia page](https://wikipedia.org/wiki/Growing_degree-day).
* Ang pagkain ay maaaring maging limitado sa hinaharap kung patuloy nating gagamitin ang parehong pamamaraan ng pagsasaka. Alamin ang higit pa tungkol sa mga hi-tech farming techniques sa [Hi-Tech Farms of Future video on YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Takdang-Aralin

[Visualize GDD data using a Jupyter Notebook](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.