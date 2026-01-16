<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-27T23:44:14+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "tl"
}
-->
# Pagsubaybay sa Lokasyon

![Isang sketchnote overview ng araling ito](../../../../../translated_images/tl/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Panimula

Ang pangunahing proseso ng pagdadala ng pagkain mula sa magsasaka patungo sa konsumer ay kinabibilangan ng paglo-load ng mga kahon ng ani sa mga trak, barko, eroplano, o iba pang komersyal na sasakyang pang-transportasyon, at paghahatid ng pagkain sa isang lugar - maaaring direkta sa isang customer, o sa isang sentral na hub o bodega para sa pagproseso. Ang buong proseso mula sa sakahan hanggang sa konsumer ay bahagi ng tinatawag na *supply chain*. Ang video sa ibaba mula sa W. P. Carey School of Business ng Arizona State University ay nagpapaliwanag ng ideya ng supply chain at kung paano ito pinamamahalaan nang mas detalyado.

[![Ano ang Supply Chain Management? Isang video mula sa W. P. Carey School of Business ng Arizona State University](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 I-click ang imahe sa itaas upang panoorin ang video

Ang pagdaragdag ng mga IoT device ay maaaring lubos na mapabuti ang iyong supply chain, na nagbibigay-daan sa iyo upang pamahalaan kung nasaan ang mga item, mas mahusay na magplano ng transportasyon at paghawak ng mga kalakal, at mas mabilis na tumugon sa mga problema.

Kapag namamahala ng isang fleet ng mga sasakyan tulad ng mga trak, mahalagang malaman kung nasaan ang bawat sasakyan sa isang partikular na oras. Ang mga sasakyan ay maaaring lagyan ng GPS sensors na nagpapadala ng kanilang lokasyon sa mga IoT system, na nagbibigay-daan sa mga may-ari na matukoy ang kanilang lokasyon, makita ang ruta na kanilang tinahak, at malaman kung kailan sila darating sa kanilang destinasyon. Karamihan sa mga sasakyan ay gumagana sa labas ng saklaw ng WiFi, kaya gumagamit sila ng cellular networks upang magpadala ng ganitong uri ng data. Minsan ang GPS sensor ay naka-embed sa mas kumplikadong IoT device tulad ng mga electronic log books. Ang mga device na ito ay sumusubaybay kung gaano katagal ang isang trak sa biyahe upang matiyak na ang mga driver ay sumusunod sa mga lokal na batas sa oras ng trabaho.

Sa araling ito, matututuhan mo kung paano subaybayan ang lokasyon ng mga sasakyan gamit ang Global Positioning System (GPS) sensor.

Sa araling ito, tatalakayin natin:

* [Mga konektadong sasakyan](../../../../../3-transport/lessons/1-location-tracking)
* [Geospatial coordinates](../../../../../3-transport/lessons/1-location-tracking)
* [Global Positioning Systems (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Pagbasa ng GPS sensor data](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS data](../../../../../3-transport/lessons/1-location-tracking)
* [Pag-decode ng GPS sensor data](../../../../../3-transport/lessons/1-location-tracking)

## Mga konektadong sasakyan

Binabago ng IoT ang paraan ng pagdadala ng mga kalakal sa pamamagitan ng paglikha ng mga fleet ng *mga konektadong sasakyan*. Ang mga sasakyang ito ay konektado sa mga sentral na IT system na nag-uulat ng impormasyon tungkol sa kanilang lokasyon, at iba pang sensor data. Ang pagkakaroon ng fleet ng mga konektadong sasakyan ay may malawak na hanay ng benepisyo:

* Pagsubaybay sa lokasyon - maaari mong matukoy kung nasaan ang isang sasakyan anumang oras, na nagbibigay-daan sa iyo upang:

  * Makakuha ng mga alerto kapag ang isang sasakyan ay malapit nang dumating sa destinasyon upang maghanda ng crew para sa pag-unload
  * Hanapin ang mga ninakaw na sasakyan
  * Pagsamahin ang data ng lokasyon at ruta sa mga problema sa trapiko upang payagan kang mag-redirect ng mga sasakyan sa gitna ng biyahe
  * Sumunod sa buwis. Ang ilang mga bansa ay naniningil ng buwis sa mga sasakyan batay sa dami ng milyahe na tinahak sa mga pampublikong kalsada (tulad ng [New Zealand's RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), kaya ang pag-alam kung kailan ang isang sasakyan ay nasa pampublikong kalsada kumpara sa pribadong kalsada ay nagpapadali sa pagkalkula ng buwis na dapat bayaran.
  * Malaman kung saan magpapadala ng mga maintenance crew sakaling magkaroon ng breakdown

* Telemetry ng driver - matiyak na ang mga driver ay sumusunod sa mga limitasyon ng bilis, lumiliko sa naaangkop na bilis, maagang nagpreno nang mahusay, at nagmamaneho nang ligtas. Ang mga konektadong sasakyan ay maaari ring magkaroon ng mga camera upang i-record ang mga insidente. Maaari itong maiugnay sa insurance, na nagbibigay ng mas mababang rate para sa mga magagaling na driver.

* Pagsunod sa oras ng driver - matiyak na ang mga driver ay nagmamaneho lamang sa kanilang legal na pinapayagang oras batay sa mga oras na binuksan at isinara ang makina.

Ang mga benepisyong ito ay maaaring pagsamahin - halimbawa, pagsamahin ang pagsunod sa oras ng driver sa pagsubaybay sa lokasyon upang i-redirect ang mga driver kung hindi nila maabot ang kanilang destinasyon sa loob ng kanilang pinapayagang oras ng pagmamaneho. Ang mga ito ay maaari ding pagsamahin sa iba pang telemetry na partikular sa sasakyan, tulad ng data ng temperatura mula sa mga trak na may kontrol sa temperatura, na nagpapahintulot sa mga sasakyan na i-redirect kung ang kanilang kasalukuyang ruta ay nangangahulugan na ang mga kalakal ay hindi mapapanatili sa tamang temperatura.

> 🎓 Ang logistics ay ang proseso ng pagdadala ng mga kalakal mula sa isang lugar patungo sa isa pa, tulad ng mula sa sakahan patungo sa supermarket sa pamamagitan ng isa o higit pang mga bodega. Ang isang magsasaka ay nag-iimpake ng mga kahon ng kamatis na ikinakarga sa isang trak, dinadala sa isang sentral na bodega, at inilalagay sa isang pangalawang trak na maaaring maglaman ng halo ng iba't ibang uri ng ani na pagkatapos ay ihahatid sa isang supermarket.

Ang pangunahing bahagi ng pagsubaybay sa sasakyan ay ang GPS - mga sensor na maaaring matukoy ang kanilang lokasyon saanman sa mundo. Sa araling ito, matututuhan mo kung paano gumamit ng GPS sensor, simula sa pag-aaral kung paano tukuyin ang lokasyon sa mundo.

## Geospatial coordinates

Ang mga geospatial coordinates ay ginagamit upang tukuyin ang mga punto sa ibabaw ng mundo, katulad ng kung paano ginagamit ang mga coordinates upang gumuhit sa isang pixel sa screen ng computer o iposisyon ang mga tahi sa cross stitch. Para sa isang solong punto, mayroon kang pares ng mga coordinates. Halimbawa, ang Microsoft Campus sa Redmond, Washington, USA ay matatagpuan sa 47.6423109, -122.1390293.

### Latitude at longitude

Ang mundo ay isang globo - isang three-dimensional na bilog. Dahil dito, ang mga punto ay tinutukoy sa pamamagitan ng paghahati nito sa 360 degrees, katulad ng geometry ng mga bilog. Ang latitude ay sumusukat sa bilang ng mga degree mula hilaga hanggang timog, ang longitude ay sumusukat sa bilang ng mga degree mula silangan hanggang kanluran.

> 💁 Walang tiyak na nakakaalam ng orihinal na dahilan kung bakit ang mga bilog ay hinati sa 360 degrees. Ang [degree (angle) page sa Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) ay sumasaklaw sa ilan sa mga posibleng dahilan.

![Mga linya ng latitude mula 90° sa North Pole, 45° sa pagitan ng North Pole at equator, 0° sa equator, -45° sa pagitan ng equator at South Pole, at -90° sa South Pole](../../../../../translated_images/tl/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

Ang latitude ay sinusukat gamit ang mga linya na umiikot sa mundo at tumatakbo nang parallel sa equator, na hinahati ang Northern at Southern Hemispheres sa 90° bawat isa. Ang equator ay nasa 0°, ang North Pole ay 90°, na kilala rin bilang 90° North, at ang South Pole ay nasa -90°, o 90° South.

Ang longitude ay sinusukat bilang bilang ng mga degree na sinusukat silangan at kanluran. Ang 0° origin ng longitude ay tinatawag na *Prime Meridian*, at itinakda noong 1884 bilang isang linya mula sa North hanggang South Pole na dumadaan sa [British Royal Observatory sa Greenwich, England](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Mga linya ng longitude mula -180° sa kanluran ng Prime Meridian, hanggang 0° sa Prime Meridian, hanggang 180° sa silangan ng Prime Meridian](../../../../../translated_images/tl/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Ang meridian ay isang imahinaryong tuwid na linya na dumadaan mula sa North Pole hanggang South Pole, na bumubuo ng kalahating bilog.

Upang sukatin ang longitude ng isang punto, sinusukat mo ang bilang ng mga degree sa paligid ng equator mula sa Prime Meridian patungo sa isang meridian na dumadaan sa puntong iyon. Ang longitude ay mula -180°, o 180° West, hanggang 0° sa Prime Meridian, hanggang 180°, o 180° East. Ang 180° at -180° ay tumutukoy sa parehong punto, ang antimeridian o 180th meridian. Ito ay isang meridian sa kabaligtaran ng mundo mula sa Prime Meridian.

> 💁 Ang antimeridian ay hindi dapat malito sa International Date Line, na nasa halos parehong posisyon, ngunit hindi isang tuwid na linya at nag-iiba upang umangkop sa mga geo-political boundaries.

✅ Mag-research: Subukang hanapin ang latitude at longitude ng iyong kasalukuyang lokasyon.

### Degrees, minutes at seconds vs decimal degrees

Tradisyonal, ang mga sukat ng degrees ng latitude at longitude ay ginagawa gamit ang sexagesimal numbering, o base-60, isang sistema ng pagbilang na ginamit ng mga Sinaunang Babylonian na unang nagsukat at nagrekord ng oras at distansya. Ginagamit mo ang sexagesimal araw-araw marahil nang hindi mo namamalayan - ang paghahati ng oras sa 60 minuto at minuto sa 60 segundo.

Ang longitude at latitude ay sinusukat sa degrees, minutes at seconds, kung saan ang isang minuto ay 1/60 ng degree, at 1 segundo ay 1/60 minuto.

Halimbawa, sa equator:

* Ang 1° ng latitude ay **111.3 kilometro**
* Ang 1 minuto ng latitude ay 111.3/60 = **1.855 kilometro**
* Ang 1 segundo ng latitude ay 1.855/60 = **0.031 kilometro**

Ang simbolo para sa minuto ay isang single quote, para sa segundo ay isang double quote. Halimbawa, ang 2 degrees, 17 minutes, at 43 seconds ay isusulat bilang 2°17'43". Ang bahagi ng segundo ay ibinibigay bilang decimal, halimbawa kalahating segundo ay 0°0'0.5".

Ang mga computer ay hindi gumagana sa base-60, kaya ang mga coordinates na ito ay ibinibigay bilang decimal degrees kapag gumagamit ng GPS data sa karamihan ng mga computer system. Halimbawa, ang 2°17'43" ay 2.295277. Karaniwang inaalis ang degree symbol.

Ang mga coordinates para sa isang punto ay palaging ibinibigay bilang `latitude, longitude`, kaya ang halimbawa kanina ng Microsoft Campus sa 47.6423109,-122.117198 ay may:

* Latitude na 47.6423109 (47.6423109 degrees hilaga ng equator)
* Longitude na -122.1390293 (122.1390293 degrees kanluran ng Prime Meridian).

![Ang Microsoft Campus sa 47.6423109,-122.117198](../../../../../translated_images/tl/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Global Positioning Systems (GPS)

Ang mga GPS system ay gumagamit ng maraming satellite na umiikot sa mundo upang matukoy ang iyong lokasyon. Marahil ay nagamit mo na ang mga GPS system nang hindi mo namamalayan - upang hanapin ang iyong lokasyon sa isang mapping app sa iyong telepono tulad ng Apple Maps o Google Maps, o upang makita kung nasaan ang iyong ride sa isang ride hailing app tulad ng Uber o Lyft, o kapag gumagamit ng satellite navigation (sat-nav) sa iyong sasakyan.

> 🎓 Ang mga satellite sa 'satellite navigation' ay mga GPS satellite!

Ang mga GPS system ay gumagana sa pamamagitan ng pagkakaroon ng ilang satellite na nagpapadala ng signal na may kasalukuyang posisyon ng bawat satellite, at isang eksaktong timestamp. Ang mga signal na ito ay ipinapadala sa pamamagitan ng radio waves at natatanggap ng antenna sa GPS sensor. Ang GPS sensor ay makakakita ng mga signal na ito, at gamit ang kasalukuyang oras ay sinusukat kung gaano katagal bago dumating ang signal mula sa satellite patungo sa sensor. Dahil ang bilis ng radio waves ay pare-pareho, magagamit ng GPS sensor ang timestamp na ipinadala upang malaman kung gaano kalayo ang sensor mula sa satellite. Sa pamamagitan ng pagsasama-sama ng data mula sa hindi bababa sa 3 satellite na may mga posisyong ipinadala, ang GPS sensor ay maaaring matukoy ang lokasyon nito sa mundo.

> 💁 Ang mga GPS sensor ay nangangailangan ng mga antenna upang makita ang mga radio waves. Ang mga antenna na naka-embed sa mga trak at sasakyan na may on-board GPS ay nakaposisyon upang makakuha ng magandang signal, karaniwang sa windshield o bubong. Kung gumagamit ka ng hiwalay na GPS system, tulad ng smartphone o IoT device, kailangan mong tiyakin na ang antenna na naka-embed sa GPS system o telepono ay may malinaw na tanawin ng kalangitan, tulad ng pag-mount sa iyong windshield.

![Sa pamamagitan ng pag-alam sa distansya mula sa sensor patungo sa maraming satellite, maaaring kalkulahin ang lokasyon](../../../../../translated_images/tl/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

Ang mga GPS satellite ay umiikot sa mundo, hindi sa isang nakapirming punto sa itaas ng sensor, kaya ang data ng lokasyon ay kinabibilangan ng altitude sa itaas ng sea level pati na rin ang latitude at longitude.

Ang GPS ay dating may mga limitasyon sa katumpakan na ipinatupad ng militar ng US, na nililimitahan ang katumpakan sa humigit-kumulang 5 metro. Ang limitasyong ito ay inalis noong 2000, na nagpapahintulot sa katumpakan na 30 sentimetro. Ang pagkuha ng katumpakan na ito ay hindi palaging posible dahil sa interference sa mga signal.

✅ Kung mayroon kang smartphone, buksan ang mapping app at tingnan kung gaano katumpak ang iyong lokasyon. Maaaring tumagal ng kaunting oras para sa iyong telepono na makakita ng maraming satellite upang makakuha ng mas tumpak na lokasyon.
💁 Ang mga satellite ay may dalang mga atomic clock na napaka-eksakto, ngunit nagkakaroon ito ng paglihis na 38 microseconds (0.0000038 segundo) bawat araw kumpara sa mga atomic clock sa Earth, dahil sa pagbagal ng oras habang tumataas ang bilis, ayon sa mga teorya ni Einstein ng espesyal at pangkalahatang relativity - mas mabilis ang paggalaw ng mga satellite kaysa sa pag-ikot ng Earth. Ang paglihis na ito ay ginamit upang patunayan ang mga hula ng espesyal at pangkalahatang relativity, at kailangang isaayos ito sa disenyo ng mga GPS system. Literal na mas mabagal ang takbo ng oras sa isang GPS satellite.
Ang mga GPS system ay binuo at inilunsad ng iba't ibang bansa at unyon pampulitika kabilang ang US, Russia, Japan, India, EU, at China. Ang mga modernong GPS sensor ay maaaring kumonekta sa karamihan ng mga sistemang ito upang makakuha ng mas mabilis at mas tumpak na lokasyon.

> 🎓 Ang mga grupo ng mga satellite sa bawat deployment ay tinatawag na mga konstelasyon.

## Basahin ang data mula sa GPS sensor

Karamihan sa mga GPS sensor ay nagpapadala ng data sa pamamagitan ng UART.

> ⚠️ Tinalakay ang UART sa [project 2, lesson 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Balikan ang araling iyon kung kinakailangan.

Maaari mong gamitin ang GPS sensor sa iyong IoT device upang makakuha ng GPS data.

### Gawain - ikonekta ang GPS sensor at basahin ang GPS data

Sundin ang kaukulang gabay upang basahin ang GPS data gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Single-board computer - Raspberry Pi](pi-gps-sensor.md)
* [Single-board computer - Virtual device](virtual-device-gps-sensor.md)

## NMEA GPS data

Kapag pinatakbo mo ang iyong code, maaaring nakita mo ang tila walang kabuluhang output. Ito ay aktwal na standard na GPS data, at bawat bahagi nito ay may kahulugan.

Ang mga GPS sensor ay naglalabas ng data gamit ang mga NMEA message, ayon sa NMEA 0183 standard. Ang NMEA ay nangangahulugang [National Marine Electronics Association](https://www.nmea.org), isang organisasyong pangkalakalan sa US na nagtatakda ng mga pamantayan para sa komunikasyon sa pagitan ng mga elektronikong pangdagat.

> 💁 Ang standard na ito ay proprietary at nagkakahalaga ng hindi bababa sa US$2,000, ngunit sapat na impormasyon tungkol dito ang nasa pampublikong domain kaya karamihan sa standard ay na-reverse engineer at maaaring gamitin sa open source at iba pang non-commercial na code.

Ang mga mensaheng ito ay batay sa teksto. Ang bawat mensahe ay binubuo ng isang *pangungusap* na nagsisimula sa karakter na `$`, kasunod ng 2 karakter upang ipahiwatig ang pinagmulan ng mensahe (hal. GP para sa US GPS system, GN para sa GLONASS, ang Russian GPS system), at 3 karakter upang ipahiwatig ang uri ng mensahe. Ang natitirang bahagi ng mensahe ay mga field na pinaghihiwalay ng mga kuwit, na nagtatapos sa isang bagong linya.

Ilan sa mga uri ng mensahe na maaaring matanggap ay:

| Uri | Paglalarawan |
| ---- | ----------- |
| GGA | GPS Fix Data, kabilang ang latitude, longitude, at altitude ng GPS sensor, pati na rin ang bilang ng mga satellite na nasa view upang makalkula ang lokasyon. |
| ZDA | Ang kasalukuyang petsa at oras, kabilang ang lokal na time zone |
| GSV | Mga detalye ng mga satellite na nasa view - tinukoy bilang mga satellite na kayang ma-detect ng GPS sensor |

> 💁 Kasama sa GPS data ang mga time stamp, kaya maaaring makuha ng iyong IoT device ang oras mula sa GPS sensor kung kinakailangan, sa halip na umasa sa isang NTP server o internal real-time clock.

Ang GGA message ay kasama ang kasalukuyang lokasyon gamit ang format na `(dd)dmm.mmmm`, kasama ang isang karakter upang ipahiwatig ang direksyon. Ang `d` sa format ay degrees, ang `m` ay minutes, at ang seconds ay nasa decimal ng minutes. Halimbawa, ang 2°17'43" ay magiging 217.716666667 - 2 degrees, 17.716666667 minutes.

Ang direksyon ay maaaring `N` o `S` para sa latitude upang ipahiwatig ang hilaga o timog, at `E` o `W` para sa longitude upang ipahiwatig ang silangan o kanluran. Halimbawa, ang latitude na 2°17'43" ay magkakaroon ng direksyon na `N`, habang ang -2°17'43" ay magkakaroon ng direksyon na `S`.

Halimbawa - ang NMEA sentence na `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Ang bahagi ng latitude ay `4738.538654,N`, na nagko-convert sa 47.6423109 sa decimal degrees. Ang `4738.538654` ay 47.6423109, at ang direksyon ay `N` (hilaga), kaya ito ay positibong latitude.

* Ang bahagi ng longitude ay `12208.341758,W`, na nagko-convert sa -122.1390293 sa decimal degrees. Ang `12208.341758` ay 122.1390293°, at ang direksyon ay `W` (kanluran), kaya ito ay negatibong longitude.

## I-decode ang GPS sensor data

Sa halip na gamitin ang raw NMEA data, mas mainam na i-decode ito sa mas kapaki-pakinabang na format. Maraming open-source na library na maaari mong gamitin upang makatulong na kunin ang mahalagang data mula sa raw NMEA messages.

### Gawain - i-decode ang GPS sensor data

Sundin ang kaukulang gabay upang i-decode ang GPS sensor data gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-gps-decode.md)

---

## 🚀 Hamon

Sumulat ng sarili mong NMEA decoder! Sa halip na umasa sa mga third-party library upang i-decode ang mga NMEA sentence, kaya mo bang gumawa ng sarili mong decoder upang kunin ang latitude at longitude mula sa mga NMEA sentence?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Review at Pag-aaral sa Sarili

* Magbasa pa tungkol sa Geospatial Coordinates sa [Geographic coordinate system page sa Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Magbasa tungkol sa Prime Meridians sa iba pang celestial bodies bukod sa Earth sa [Prime Meridian page sa Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies)
* Mag-research tungkol sa iba't ibang GPS system mula sa iba't ibang gobyerno at unyon pampulitika tulad ng EU, Japan, Russia, India, at US.

## Takdang Aralin

[Pag-aralan ang iba pang GPS data](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.