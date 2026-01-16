<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-27T22:49:42+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "sw"
}
-->
C, inayotamkwa kama *I-squared-C*, ni itifaki ya mawasiliano ya vifaa vingi, ambapo kifaa chochote kilichounganishwa kinaweza kufanya kazi kama kidhibiti au kifaa cha pembeni kinachowasiliana kupitia basi la I²C (jina la mfumo wa mawasiliano unaosafirisha data). Data hutumwa kama pakiti zilizo na anwani, ambapo kila pakiti ina anwani ya kifaa kilichounganishwa ambacho data hiyo inakusudiwa.

> 💁 Mfano huu hapo awali ulijulikana kama master/slave, lakini istilahi hii imeachwa kutokana na uhusiano wake na utumwa. [Chama cha Vifaa vya Chanzo Huria kimepitisha istilahi ya kidhibiti/kifaa cha pembeni](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), lakini bado unaweza kuona marejeo ya istilahi ya zamani.

Vifaa vina anwani inayotumika wakati vinapounganishwa kwenye basi la I²C, na kwa kawaida anwani hii imewekwa moja kwa moja kwenye kifaa. Kwa mfano, kila aina ya kihisi cha Grove kutoka Seeed kina anwani sawa, hivyo vihisi vyote vya mwanga vina anwani sawa, na vifungo vyote vina anwani tofauti na ile ya kihisi cha mwanga. Baadhi ya vifaa vina njia za kubadilisha anwani, kwa kubadilisha mipangilio ya jumper au kwa kuunganisha pini kwa njia ya solder.

I²C ina basi inayojumuisha nyaya kuu 2, pamoja na nyaya 2 za nguvu:

| Waya | Jina | Maelezo |
| ---- | --------- | ----------- |
| SDA | Data ya Seriali | Waya huu ni wa kutuma data kati ya vifaa. |
| SCL | Saa ya Seriali | Waya huu hutuma ishara ya saa kwa kiwango kilichowekwa na kidhibiti. |
| VCC | Voltage common collector | Chanzo cha nguvu kwa vifaa. Hii imeunganishwa na nyaya za SDA na SCL ili kutoa nguvu zao kupitia resistor ya kuvuta juu inayozima ishara wakati hakuna kifaa kinachofanya kazi kama kidhibiti. |
| GND | Ardhi | Hii hutoa ardhi ya kawaida kwa mzunguko wa umeme. |

![Basi la I2C na vifaa 3 vilivyounganishwa kwenye nyaya za SDA na SCL, zikishiriki waya wa ardhi ya kawaida](../../../../../translated_images/sw/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.png)

Ili kutuma data, kifaa kimoja kitaanzisha hali ya kuanza kuonyesha kuwa kiko tayari kutuma data. Kisha kitakuwa kidhibiti. Kidhibiti kitatuma anwani ya kifaa ambacho kinataka kuwasiliana nacho, pamoja na ikiwa kinataka kusoma au kuandika data. Baada ya data kusafirishwa, kidhibiti kitatuma hali ya kusimama kuonyesha kuwa kimekamilisha. Baada ya hapo kifaa kingine kinaweza kuwa kidhibiti na kutuma au kupokea data.

I<sup>2</sup>C ina mipaka ya kasi, ikiwa na hali 3 tofauti zinazofanya kazi kwa kasi maalum. Kasi ya juu zaidi ni hali ya Kasi ya Juu yenye kasi ya juu ya 3.4Mbps (megabiti kwa sekunde), ingawa vifaa vichache sana vinaunga mkono kasi hiyo. Kwa mfano, Raspberry Pi imewekewa kikomo kwenye hali ya kasi ya 400Kbps (kilobiti kwa sekunde). Hali ya kawaida inafanya kazi kwa 100Kbps.

> 💁 Ikiwa unatumia Raspberry Pi na Grove Base hat kama vifaa vyako vya IoT, utaweza kuona idadi ya soketi za I<sup>2</sup>C kwenye bodi unazoweza kutumia kuwasiliana na sensa za I<sup>2</sup>C. Sensa za Analog Grove pia hutumia I<sup>2</sup>C na ADC kutuma thamani za analogi kama data ya kidijitali, kwa hivyo sensa ya mwanga uliyotumia ilionyesha pini ya analogi, na thamani hiyo ilitumwa kupitia I<sup>2</sup>C kwa kuwa Raspberry Pi inaunga mkono pini za kidijitali pekee.

### Kipokezi-kisambazaji cha ulimwengu wote (UART)

UART inahusisha mzunguko wa kimwili unaoruhusu vifaa viwili kuwasiliana. Kila kifaa kina pini 2 za mawasiliano - kusambaza (Tx) na kupokea (Rx), ambapo pini ya Tx ya kifaa cha kwanza imeunganishwa na pini ya Rx ya kifaa cha pili, na pini ya Tx ya kifaa cha pili imeunganishwa na pini ya Rx ya kifaa cha kwanza. Hii inaruhusu data kutumwa katika pande zote mbili.

* Kifaa cha 1 kinatuma data kutoka pini yake ya Tx, ambayo inapokelewa na kifaa cha 2 kwenye pini yake ya Rx
* Kifaa cha 1 kinapokea data kwenye pini yake ya Rx ambayo imetumwa na kifaa cha 2 kutoka pini yake ya Tx

![UART na pini ya Tx kwenye chip moja imeunganishwa na pini ya Rx kwenye chip nyingine, na kinyume chake](../../../../../translated_images/sw/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Data inatumwa kidogo moja kwa wakati, na hii inajulikana kama mawasiliano ya *serial*. Mfumo wa uendeshaji na mikrokontroller nyingi zina *bandari za serial*, yaani miunganisho inayoweza kutuma na kupokea data ya serial inayopatikana kwa msimbo wako.

Vifaa vya UART vina [kiwango cha baud](https://wikipedia.org/wiki/Symbol_rate) (pia kinajulikana kama kiwango cha alama), ambacho ni kasi ambayo data itatumwa na kupokelewa kwa biti kwa sekunde. Kiwango cha baud cha kawaida ni 9,600, ikimaanisha biti 9,600 (0s na 1s) za data zinatumwa kila sekunde.

UART hutumia biti za kuanza na kusimama - yaani inatuma biti ya kuanza kuonyesha kwamba iko karibu kutuma byte (biti 8) za data, kisha biti ya kusimama baada ya kutuma biti 8.

Kasi ya UART inategemea vifaa, lakini hata utekelezaji wa kasi zaidi hauzidi 6.5 Mbps (megabiti kwa sekunde, au mamilioni ya biti, 0 au 1, zinazotumwa kwa sekunde).

Unaweza kutumia UART kupitia pini za GPIO - unaweza kuweka pini moja kama Tx na nyingine kama Rx, kisha kuziunganisha na kifaa kingine.

> 💁 Ikiwa unatumia Raspberry Pi na Grove Base hat kama vifaa vyako vya IoT, utaweza kuona soketi ya UART kwenye bodi unayoweza kutumia kuwasiliana na sensa zinazotumia itifaki ya UART.

### Kiolesura cha Serial Peripheral (SPI)

SPI imeundwa kwa mawasiliano ya umbali mfupi, kama vile kwenye mikrokontroller kuzungumza na kifaa cha kuhifadhi kama kumbukumbu ya flash. Inategemea mfano wa kidhibiti/kifaa cha pembeni na kidhibiti kimoja (kawaida processor ya kifaa cha IoT) kinachoshirikiana na vifaa vingi vya pembeni. Kidhibiti kinadhibiti kila kitu kwa kuchagua kifaa cha pembeni na kutuma au kuomba data.

> 💁 Kama I<sup>2</sup>C, maneno kidhibiti na kifaa cha pembeni ni mabadiliko ya hivi karibuni, kwa hivyo unaweza kuona maneno ya zamani bado yanatumika.

Vidhibiti vya SPI hutumia nyaya 3, pamoja na waya 1 wa ziada kwa kila kifaa cha pembeni. Vifaa vya pembeni hutumia nyaya 4. Nyaya hizi ni:

| Waya | Jina | Maelezo |
| ---- | --------- | ----------- |
| COPI | Kidhibiti Tokeo, Kifaa cha Pembeni Ingizo | Waya huu ni wa kutuma data kutoka kwa kidhibiti kwenda kwa kifaa cha pembeni. |
| CIPO | Kidhibiti Ingizo, Kifaa cha Pembeni Tokeo | Waya huu ni wa kutuma data kutoka kwa kifaa cha pembeni kwenda kwa kidhibiti. |
| SCLK | Saa ya Serial | Waya huu hutuma ishara ya saa kwa kiwango kilichowekwa na kidhibiti. |
| CS   | Chagua Chipu | Kidhibiti kina waya nyingi, moja kwa kila kifaa cha pembeni, na kila waya inaunganishwa na waya ya CS kwenye kifaa cha pembeni kinacholingana. |

![SPI na kidhibiti kimoja na vifaa viwili vya pembeni](../../../../../translated_images/sw/spi.297431d6f98b386b.webp)

Waya ya CS hutumika kuamsha kifaa kimoja cha pembeni kwa wakati mmoja, kuwasiliana kupitia nyaya za COPI na CIPO. Wakati kidhibiti kinahitaji kubadilisha kifaa cha pembeni, kinazima waya ya CS iliyounganishwa na kifaa cha pembeni kinachotumika kwa sasa, kisha kinaamsha waya iliyounganishwa na kifaa cha pembeni kinachotaka kuwasiliana nacho.

SPI ni *full-duplex*, ikimaanisha kidhibiti kinaweza kutuma na kupokea data kwa wakati mmoja kutoka kwa kifaa cha pembeni kimoja kwa kutumia nyaya za COPI na CIPO. SPI hutumia ishara ya saa kwenye waya ya SCLK kuweka vifaa katika usawazishaji, kwa hivyo tofauti na kutuma moja kwa moja kupitia UART haitaji biti za kuanza na kusimama.

Hakuna mipaka ya kasi iliyofafanuliwa kwa SPI, na utekelezaji mara nyingi unaweza kusambaza megabaiti nyingi za data kwa sekunde.

Vifaa vya maendeleo vya IoT mara nyingi vinaunga mkono SPI kupitia baadhi ya pini za GPIO. Kwa mfano, kwenye Raspberry Pi unaweza kutumia pini za GPIO 19, 21, 23, 24 na 26 kwa SPI.

### Bila waya

Baadhi ya sensa zinaweza kuwasiliana kupitia itifaki za kawaida za bila waya, kama vile Bluetooth (hasa Bluetooth Low Energy, au BLE), LoRaWAN (itifaki ya mtandao wa nguvu ya chini ya **Lo**ng **Ra**nge), au WiFi. Hizi huruhusu sensa za mbali ambazo hazijaunganishwa kimwili na kifaa cha IoT.

Mfano mmoja ni sensa za unyevu wa udongo za kibiashara. Hizi hupima unyevu wa udongo kwenye shamba, kisha kutuma data kupitia LoRaWan kwa kifaa cha hub, ambacho kitachakata data au kuituma kupitia mtandao. Hii inaruhusu sensa kuwa mbali na kifaa cha IoT kinachosimamia data, kupunguza matumizi ya nguvu na hitaji la mitandao mikubwa ya WiFi au nyaya ndefu.

BLE ni maarufu kwa sensa za hali ya juu kama vile vifaa vya kufuatilia mazoezi vinavyovaliwa mkononi. Hizi huunganisha sensa nyingi na kutuma data ya sensa kwa kifaa cha IoT kwa njia ya simu yako kupitia BLE.

✅ Je, una sensa za Bluetooth kwenye mwili wako, nyumbani kwako au shuleni kwako? Hizi zinaweza kujumuisha sensa za joto, sensa za uwepo, vifaa vya kufuatilia na vifaa vya mazoezi.

Njia maarufu kwa vifaa vya kibiashara kuunganishwa ni Zigbee. Zigbee hutumia WiFi kuunda mitandao ya mesh kati ya vifaa, ambapo kila kifaa kinaunganishwa na vifaa vingi vya karibu iwezekanavyo, na kuunda idadi kubwa ya miunganisho kama mtandao wa buibui. Wakati kifaa kimoja kinataka kutuma ujumbe kwa mtandao, kinaweza kuutuma kwa vifaa vya karibu, ambavyo kisha vinausambaza kwa vifaa vingine vya karibu na kadhalika, hadi kufikia mratibu na kutumwa kwa mtandao.

> 🐝 Jina Zigbee linahusu dansi ya mzunguko wa nyuki wa asali baada ya kurudi kwenye mzinga.

## Pima viwango vya unyevu wa udongo

Unaweza kupima kiwango cha unyevu wa udongo kwa kutumia sensa ya unyevu wa udongo, kifaa cha IoT, na mmea wa nyumbani au sehemu ya udongo iliyo karibu.

### Kazi - pima unyevu wa udongo

Fanya kazi kupitia mwongozo husika kupima unyevu wa udongo kwa kutumia kifaa chako cha IoT:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Kompyuta ya bodi moja - Raspberry Pi](pi-soil-moisture.md)
* [Kompyuta ya bodi moja - Kifaa cha virtual](virtual-device-soil-moisture.md)

## Urekebishaji wa sensa

Sensa zinategemea kupima mali za umeme kama vile upinzani au kapasitansi.

> 🎓 Upinzani, unaopimwa kwa ohms (Ω) ni kiasi cha upinzani kwa mkondo wa umeme unaosafiri kupitia kitu. Wakati voltage inatumika kwa nyenzo, kiasi cha mkondo kinachopita kupitia nyenzo hiyo kinategemea upinzani wa nyenzo hiyo. Unaweza kusoma zaidi kwenye [ukurasa wa upinzani wa umeme kwenye Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Kapasitansi, inayopimwa kwa farads (F), ni uwezo wa sehemu au mzunguko kukusanya na kuhifadhi nishati ya umeme. Unaweza kusoma zaidi kuhusu kapasitansi kwenye [ukurasa wa kapasitansi kwenye Wikipedia](https://wikipedia.org/wiki/Capacitance).

Vipimo hivi si mara zote vinafaa - fikiria sensa ya joto inayokupa kipimo cha 22.5KΩ! Badala yake thamani iliyopimwa inahitaji kubadilishwa kuwa kitengo kinachofaa kwa kurekebishwa - yaani kulinganisha thamani zilizopimwa na kiasi kilichopimwa ili kuruhusu vipimo vipya kubadilishwa kuwa kitengo sahihi.

Baadhi ya sensa huja zikiwa tayari zimesahihishwa. Kwa mfano, sensa ya joto uliyotumia katika somo la mwisho ilikuwa tayari imesahihishwa ili iweze kurudisha kipimo cha joto kwa °C. Kiwandani sensa ya kwanza iliyoundwa ingewekwa kwenye joto mbalimbali yanayojulikana na upinzani kupimwa. Hii ingekuwa kisha kutumika kujenga hesabu inayoweza kubadilisha kutoka thamani iliyopimwa kwa Ω (kitengo cha upinzani) hadi °C.

> 💁 Hesabu ya kuhesabu upinzani kutoka joto inaitwa [mchoro wa Steinhart–Hart](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Urekebishaji wa sensa ya unyevu wa udongo

Unyevu wa udongo unapimwa kwa kutumia maudhui ya maji ya gravimetriki au volumetriki.

* Gravimetriki ni uzito wa maji katika uzito wa udongo unaopimwa, kama idadi ya kilo za maji kwa kilo ya udongo mkavu
* Volumetriki ni kiasi cha maji katika kiasi cha udongo unaopimwa, kama idadi ya mita za ujazo za maji kwa mita za ujazo za udongo mkavu

> 🇺🇸 Kwa Wamarekani, kwa sababu ya uthabiti wa vitengo, hivi vinaweza kupimwa kwa paundi badala ya kilo au futi za ujazo badala ya mita za ujazo.

Sensa za unyevu wa udongo hupima upinzani wa umeme au kapasitansi - hii haibadiliki tu kwa unyevu wa udongo, lakini pia aina ya udongo kwa kuwa vipengele katika udongo vinaweza kubadilisha sifa zake za umeme. Kwa kawaida sensa zinapaswa kurekebishwa - yaani kuchukua vipimo kutoka sensa na kuvilinganisha na vipimo vilivyopatikana kwa kutumia mbinu ya kisayansi zaidi. Kwa mfano, maabara inaweza kuhesabu unyevu wa udongo wa gravimetriki kwa kutumia sampuli za shamba maalum zilizochukuliwa mara kadhaa kwa mwaka, na nambari hizi zikitumika kurekebisha sensa, kulinganisha kipimo cha sensa na unyevu wa udongo wa gravimetriki.

![Mchoro wa voltage dhidi ya maudhui ya unyevu wa udongo](../../../../../translated_images/sw/soil-moisture-to-voltage.df86d80cda158700.webp)

Mchoro hapo juu unaonyesha jinsi ya kurekebisha sensa. Voltage inachukuliwa kwa sampuli ya udongo ambayo kisha inapimwa maabara kwa kulinganisha uzito wa unyevu na uzito wa mkavu (kwa kupima uzito ukiwa unyevu, kisha kukausha kwenye oveni na kupima ukiwa mkavu). Mara vipimo vichache vinapochukuliwa, vinaweza kuwekwa kwenye mchoro na mstari kufaa kwa alama. Mstari huu unaweza kisha kutumika kubadilisha vipimo vya sensa ya unyevu wa udongo vilivyopimwa na kifaa cha IoT kuwa vipimo halisi vya unyevu wa udongo.

💁 Kwa sensa za unyevu wa udongo za upinzani, voltage huongezeka kadri unyevu wa udongo unavyoongezeka. Kwa sensa za unyevu wa udongo za kapasitansi, voltage hupungua kadri unyevu wa udongo unavyoongezeka, kwa hivyo michoro ya hizi ingekuwa na mwelekeo wa chini, si juu.

![Thamani ya unyevu wa udongo iliyokadiriwa kutoka mchoro](../../../../../translated_images/sw/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Mchoro hapo juu unaonyesha kipimo cha voltage kutoka sensa ya unyevu wa udongo, na kwa kufuata mstari kwenye mchoro, unyevu halisi wa udongo unaweza kuhesabiwa.

Njia hii inamaanisha mkulima anahitaji tu kupata vipimo vichache vya maabara kwa shamba, kisha anaweza kutumia vifaa vya IoT kupima unyevu wa udongo - kuharakisha sana muda wa kuchukua vipimo.

---

## 🚀 Changamoto

Sensa za unyevu wa udongo za upinzani na kapasitansi zina tofauti kadhaa. Je, tofauti hizi ni zipi, na ni aina gani (ikiwa ipo) ni bora kwa mkulima kutumia? Je, jibu hili linabadilika kati ya nchi zinazoendelea na zilizoendelea?

## Maswali ya baada ya somo

[Maswali ya baada ya somo](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Mapitio na Kujisomea

Soma kuhusu vifaa na itifaki zinazotumiwa na sensa na aktueta:

* [Ukurasa wa Wikipedia wa GPIO](https://wikipedia.org/wiki/General-purpose_input/output)
* [Ukurasa wa Wikipedia wa UART](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [Ukurasa wa Wikipedia wa SPI](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [Ukurasa wa Wikipedia wa I<sup>2</sup>C](https://wikipedia.org/wiki/I²C)
* [Ukurasa wa Wikipedia wa Zigbee](https://wikipedia.org/wiki/Zigbee)

## Kazi

[Rekebisha sensa yako](assignment.md)

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.