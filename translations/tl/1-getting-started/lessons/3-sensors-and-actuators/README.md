<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-27T22:29:06+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "tl"
}
-->
# Makipag-ugnayan sa pisikal na mundo gamit ang mga sensor at actuator

![Isang sketchnote overview ng araling ito](../../../../../translated_images/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang imahe para sa mas malaking bersyon.

Ang araling ito ay itinuro bilang bahagi ng [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) mula sa [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Ang aralin ay itinuro sa 2 video - isang 1 oras na leksyon, at isang 1 oras na office hour na mas malalim na tinalakay ang mga bahagi ng aralin at sinagot ang mga tanong.

[![Aralin 3: Makipag-ugnayan sa Pisikal na Mundo gamit ang mga Sensor at Actuator](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Aralin 3: Makipag-ugnayan sa Pisikal na Mundo gamit ang mga Sensor at Actuator - Office hours](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 I-click ang mga imahe sa itaas para mapanood ang mga video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Panimula

Ang araling ito ay nagpapakilala ng dalawang mahalagang konsepto para sa iyong IoT device - mga sensor at actuator. Magkakaroon ka rin ng hands-on na karanasan sa pareho, magdadagdag ng light sensor sa iyong IoT project, at maglalagay ng LED na kontrolado ng light levels, na epektibong bumubuo ng isang nightlight.

Sa araling ito, tatalakayin natin:

* [Ano ang mga sensor?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Gumamit ng sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Mga uri ng sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Ano ang mga actuator?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Gumamit ng actuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Mga uri ng actuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Ano ang mga sensor?

Ang mga sensor ay mga hardware device na nakakaramdam sa pisikal na mundo - sinusukat nila ang isa o higit pang mga katangian sa kanilang paligid at ipinapadala ang impormasyon sa isang IoT device. Ang mga sensor ay sumasaklaw sa napakaraming uri ng device dahil napakaraming bagay ang maaaring sukatin, mula sa natural na mga katangian tulad ng temperatura ng hangin hanggang sa pisikal na interaksyon tulad ng paggalaw.

Ilan sa mga karaniwang sensor ay:

* Mga temperature sensor - nararamdaman ang temperatura ng hangin o ang temperatura ng kung saan sila nakalubog. Para sa mga hobbyist at developer, kadalasang pinagsasama ang mga ito sa air pressure at humidity sa isang sensor.
* Mga button - nararamdaman kung kailan sila pinindot.
* Mga light sensor - nakikita ang antas ng liwanag at maaaring para sa partikular na mga kulay, UV light, IR light, o pangkalahatang nakikitang liwanag.
* Mga camera - nararamdaman ang visual na representasyon ng mundo sa pamamagitan ng pagkuha ng litrato o streaming video.
* Mga accelerometer - nararamdaman ang paggalaw sa iba't ibang direksyon.
* Mga mikropono - nararamdaman ang tunog, alinman sa pangkalahatang antas ng tunog o direksyunal na tunog.

✅ Mag-research. Anong mga sensor ang mayroon sa iyong telepono?

Ang lahat ng sensor ay may isang bagay na pareho - kino-convert nila ang anumang nararamdaman nila sa isang electrical signal na maaaring ma-interpret ng isang IoT device. Kung paano ito na-interpret ay nakadepende sa sensor, pati na rin sa communication protocol na ginagamit upang makipag-ugnayan sa IoT device.

## Gumamit ng sensor

Sundin ang kaukulang gabay sa ibaba upang magdagdag ng sensor sa iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Single-board computer - Raspberry Pi](pi-sensor.md)
* [Single-board computer - Virtual device](virtual-device-sensor.md)

## Mga uri ng sensor

Ang mga sensor ay maaaring analog o digital.

### Analog sensor

Ang ilan sa mga pinaka-basic na sensor ay analog sensor. Ang mga sensor na ito ay tumatanggap ng boltahe mula sa IoT device, ina-adjust ng mga component ng sensor ang boltahe, at ang boltahe na ibinabalik mula sa sensor ay sinusukat upang makuha ang halaga ng sensor.

> 🎓 Ang boltahe ay isang sukat kung gaano kalakas ang "tulak" upang ilipat ang kuryente mula sa isang lugar patungo sa isa pa, tulad ng mula sa positibong terminal ng baterya patungo sa negatibong terminal. Halimbawa, ang isang standard na AA battery ay 1.5V (V ang simbolo para sa volts) at maaaring itulak ang kuryente gamit ang lakas na 1.5V mula sa positibong terminal nito patungo sa negatibong terminal. Ang iba't ibang electrical hardware ay nangangailangan ng iba't ibang boltahe upang gumana, halimbawa, ang isang LED ay maaaring magliwanag sa pagitan ng 2-3V, ngunit ang isang 100W filament lightbulb ay mangangailangan ng 240V. Maaari kang magbasa pa tungkol sa boltahe sa [Voltage page sa Wikipedia](https://wikipedia.org/wiki/Voltage).

Isang halimbawa nito ay ang potentiometer. Ito ay isang dial na maaari mong paikutin sa pagitan ng dalawang posisyon at sinusukat ng sensor ang pag-ikot.

![Isang potentiometer na nakatakda sa mid point na pinapadalhan ng 5 volts na nagbabalik ng 3.8 volts](../../../../../translated_images/potentiometer.35a348b9ce22f6ec.tl.png)

Ang IoT device ay magpapadala ng electrical signal sa potentiometer sa isang boltahe, tulad ng 5 volts (5V). Habang ina-adjust ang potentiometer, binabago nito ang boltahe na lumalabas sa kabilang panig. Halimbawa, isipin mo na mayroon kang potentiometer na may label bilang isang dial na mula 0 hanggang [11](https://wikipedia.org/wiki/Up_to_eleven), tulad ng volume knob sa isang amplifier. Kapag ang potentiometer ay nasa full off position (0), 0V (0 volts) ang lalabas. Kapag ito ay nasa full on position (11), 5V (5 volts) ang lalabas.

> 🎓 Ito ay isang oversimplification, at maaari kang magbasa pa tungkol sa potentiometer at variable resistors sa [potentiometer Wikipedia page](https://wikipedia.org/wiki/Potentiometer).

Ang boltahe na lumalabas sa sensor ay binabasa ng IoT device, at ang device ay maaaring tumugon dito. Depende sa sensor, ang boltahe na ito ay maaaring arbitraryong halaga o maaaring i-map sa isang standard na unit. Halimbawa, ang isang analog temperature sensor na batay sa [thermistor](https://wikipedia.org/wiki/Thermistor) ay nagbabago ng resistance nito depende sa temperatura. Ang output voltage ay maaaring i-convert sa temperatura sa Kelvin, at kaukulang sa °C o °F, sa pamamagitan ng mga kalkulasyon sa code.

✅ Ano sa tingin mo ang mangyayari kung ang sensor ay magbalik ng mas mataas na boltahe kaysa sa ipinadala (halimbawa mula sa isang external power supply)? ⛔️ HUWAG subukan ito.

#### Analog to digital conversion

Ang mga IoT device ay digital - hindi sila gumagana sa analog na mga halaga, gumagana lamang sila sa 0s at 1s. Nangangahulugan ito na ang mga analog sensor value ay kailangang i-convert sa digital signal bago ito ma-proseso. Maraming IoT device ang may analog-to-digital converters (ADCs) upang i-convert ang analog inputs sa digital na representasyon ng kanilang halaga. Ang mga sensor ay maaari ring gumana sa ADCs sa pamamagitan ng connector board. Halimbawa, sa Seeed Grove ecosystem gamit ang Raspberry Pi, ang mga analog sensor ay kumokonekta sa mga partikular na port sa isang 'hat' na nakapatong sa Pi na nakakonekta sa GPIO pins ng Pi, at ang hat na ito ay may ADC upang i-convert ang boltahe sa digital signal na maaaring ipadala mula sa GPIO pins ng Pi.

Halimbawa, isipin mo na mayroon kang analog light sensor na nakakonekta sa isang IoT device na gumagamit ng 3.3V at nagbabalik ng halaga na 1V. Ang 1V na ito ay walang kahulugan sa digital na mundo, kaya kailangang i-convert. Ang boltahe ay iko-convert sa analog na halaga gamit ang isang scale depende sa device at sensor. Isang halimbawa ay ang Seeed Grove light sensor na naglalabas ng mga halaga mula 0 hanggang 1,023. Para sa sensor na ito na tumatakbo sa 3.3V, ang 1V output ay magiging halaga na 300. Ang IoT device ay hindi kayang hawakan ang 300 bilang analog na halaga, kaya ang halaga ay iko-convert sa `0000000100101100`, ang binary na representasyon ng 300 ng Grove hat. Ito ay ipoproseso ng IoT device.

✅ Kung hindi mo alam ang binary, mag-research ng kaunti upang matutunan kung paano nire-represent ang mga numero gamit ang 0s at 1s. Ang [BBC Bitesize introduction to binary lesson](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) ay isang magandang lugar upang magsimula.

Mula sa coding perspective, ang lahat ng ito ay karaniwang hinahawakan ng mga library na kasama ng mga sensor, kaya hindi mo kailangang alalahanin ang conversion na ito. Para sa Grove light sensor, gagamitin mo ang Python library at tatawagin ang `light` property, o gagamitin ang Arduino library at tatawagin ang `analogRead` upang makakuha ng halaga na 300.

### Digital sensor

Ang mga digital sensor, tulad ng analog sensor, ay nakakakita sa mundo sa paligid nila gamit ang mga pagbabago sa electrical voltage. Ang pagkakaiba ay naglalabas sila ng digital signal, alinman sa pamamagitan ng pagsukat lamang ng dalawang estado o sa pamamagitan ng paggamit ng built-in na ADC. Ang mga digital sensor ay nagiging mas karaniwan upang maiwasan ang pangangailangan na gumamit ng ADC alinman sa connector board o sa IoT device mismo.

Ang pinakasimpleng digital sensor ay isang button o switch. Ito ay isang sensor na may dalawang estado, on o off.

![Isang button na pinapadalhan ng 5 volts. Kapag hindi pinindot, nagbabalik ito ng 0 volts, kapag pinindot, nagbabalik ito ng 5 volts](../../../../../translated_images/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.tl.png)

Ang mga pin sa IoT device tulad ng GPIO pins ay maaaring direktang sukatin ang signal na ito bilang 0 o 1. Kung ang boltahe na ipinadala ay pareho sa boltahe na ibinalik, ang halaga na nabasa ay 1, kung hindi, ang halaga na nabasa ay 0. Walang pangangailangan na i-convert ang signal, maaari lamang itong maging 1 o 0.

> 💁 Ang mga boltahe ay hindi kailanman eksakto lalo na dahil ang mga component sa isang sensor ay may resistance, kaya karaniwang may tolerance. Halimbawa, ang GPIO pins sa isang Raspberry Pi ay gumagana sa 3.3V, at nagbabasa ng return signal na higit sa 1.8V bilang 1, mas mababa sa 1.8V bilang 0.

* 3.3V ang pumapasok sa button. Ang button ay naka-off kaya 0V ang lumalabas, nagbibigay ng halaga na 0
* 3.3V ang pumapasok sa button. Ang button ay naka-on kaya 3.3V ang lumalabas, nagbibigay ng halaga na 1

Ang mas advanced na digital sensor ay nagbabasa ng analog na mga halaga, pagkatapos ay kino-convert ang mga ito gamit ang on-board ADCs sa digital signal. Halimbawa, ang isang digital temperature sensor ay gagamit pa rin ng thermocouple sa parehong paraan tulad ng analog sensor, at susukatin pa rin ang pagbabago sa boltahe na dulot ng resistance ng thermocouple sa kasalukuyang temperatura. Sa halip na magbalik ng analog na halaga at umasa sa device o connector board upang i-convert sa digital signal, ang ADC na built-in sa sensor ay iko-convert ang halaga at ipapadala ito bilang serye ng 0s at 1s sa IoT device. Ang mga 0s at 1s na ito ay ipinapadala sa parehong paraan tulad ng digital signal para sa button na may 1 bilang full voltage at 0 bilang 0v.

![Isang digital temperature sensor na nagko-convert ng analog reading sa binary data na may 0 bilang 0 volts at 1 bilang 5 volts bago ipadala ito sa IoT device](../../../../../translated_images/temperature-as-digital.85004491b977bae1.tl.png)

Ang pagpapadala ng digital na data ay nagpapahintulot sa mga sensor na maging mas kumplikado at magpadala ng mas detalyadong data, kahit na encrypted na data para sa mga secure na sensor. Isang halimbawa ay ang camera. Ito ay isang sensor na kumukuha ng imahe at ipinapadala ito bilang digital na data na naglalaman ng imahe, kadalasan sa compressed format tulad ng JPEG, upang mabasa ng IoT device. Maaari rin itong mag-stream ng video sa pamamagitan ng pagkuha ng mga imahe at pagpapadala ng alinman sa kumpletong imahe frame by frame o isang compressed video stream.

## Ano ang mga actuator?

Ang mga actuator ay kabaligtaran ng mga sensor - kino-convert nila ang electrical signal mula sa iyong IoT device sa isang interaksyon sa pisikal na mundo tulad ng paglabas ng liwanag o tunog, o paggalaw ng motor.

Ilan sa mga karaniwang actuator ay:

* LED - naglalabas ng liwanag kapag naka-on
* Speaker - naglalabas ng tunog batay sa signal na ipinadala sa kanila, mula sa simpleng buzzer hanggang sa audio speaker na maaaring magpatugtog ng musika
* Stepper motor - kino-convert ang signal sa isang tiyak na dami ng pag-ikot, tulad ng pag-ikot ng dial ng 90°
* Relay - mga switch na maaaring i-on o i-off gamit ang electrical signal. Pinapayagan nila ang maliit na boltahe mula sa IoT device na i-on ang mas malaking boltahe.
* Mga screen - mas kumplikadong actuator na nagpapakita ng impormasyon sa multi-segment display. Ang mga screen ay nag-iiba mula sa simpleng LED display hanggang sa high-resolution na video monitor.

✅ Mag-research. Anong mga actuator ang mayroon sa iyong telepono?

## Gumamit ng actuator

Sundin ang kaukulang gabay sa ibaba upang magdagdag ng actuator sa iyong IoT device, na kontrolado ng sensor, upang bumuo ng IoT nightlight. Kukunin nito ang light levels mula sa light sensor, at gagamit ng actuator sa anyo ng LED upang maglabas ng liwanag kapag masyadong mababa ang natukoy na light level.

![Isang flow chart ng assignment na nagpapakita ng light levels na binabasa at sinusuri, at ang LED na kinokontrol](../../../../../translated_images/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.tl.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Single-board computer - Raspberry Pi](pi-actuator.md)
* [Single-board computer - Virtual device](virtual-device-actuator.md)

## Mga uri ng actuator

Tulad ng mga sensor, ang mga actuator ay maaaring analog o digital.

### Analog actuator

Ang mga analog actuator ay tumatanggap ng analog signal at kino-convert ito sa isang uri ng interaksyon, kung saan ang interaksyon ay nagbabago batay sa boltahe na ibinibigay.

Isang halimbawa ay ang dimmable light, tulad ng mga ilaw na maaaring mayroon ka sa iyong bahay. Ang dami ng boltahe na ibinibigay sa ilaw ang nagtatakda kung gaano ito kaliwanag.
![Isang ilaw na dimmed sa mababang boltahe at mas maliwanag sa mas mataas na boltahe](../../../../../translated_images/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.tl.png)

Tulad ng mga sensor, ang aktwal na IoT device ay gumagana gamit ang digital na signal, hindi analog. Ibig sabihin, upang magpadala ng analog na signal, kailangan ng IoT device ng digital to analog converter (DAC), alinman direkta sa IoT device o sa isang connector board. Ito ang magko-convert ng mga 0s at 1s mula sa IoT device patungo sa analog na boltahe na magagamit ng actuator.

✅ Ano sa tingin mo ang mangyayari kung magpadala ang IoT device ng mas mataas na boltahe kaysa sa kayang hawakan ng actuator?  
⛔️ HUWAG subukan ito.

#### Pulse-Width Modulation

Isa pang opsyon para i-convert ang digital na signal mula sa isang IoT device patungo sa analog na signal ay ang pulse-width modulation. Kasama rito ang pagpapadala ng maraming maikling digital na pulso na kumikilos na parang analog na signal.

Halimbawa, maaari mong gamitin ang PWM upang kontrolin ang bilis ng isang motor.

Isipin mong kinokontrol mo ang isang motor na may 5V na supply. Magpapadala ka ng maikling pulso sa iyong motor, na nagbabago ng boltahe sa mataas (5V) sa loob ng dalawang daang bahagi ng isang segundo (0.02s). Sa panahong iyon, maaaring umikot ang iyong motor ng isang ikasampung bahagi ng isang ikot, o 36°. Pagkatapos ay titigil ang signal sa loob ng dalawang daang bahagi ng isang segundo (0.02s), nagpapadala ng mababang signal (0V). Ang bawat cycle ng on at off ay tumatagal ng 0.04s. Pagkatapos ay inuulit ang cycle.

![Pulse width modulation rotation ng isang motor sa 150 RPM](../../../../../translated_images/pwm-motor-150rpm.83347ac04ca38482.tl.png)

Ibig sabihin, sa isang segundo mayroon kang 25 5V pulses na may tagal na 0.02s na umiikot sa motor, bawat isa ay sinusundan ng 0.02s na pause na 0V na hindi umiikot ang motor. Ang bawat pulso ay umiikot sa motor ng isang ikasampung bahagi ng isang ikot, ibig sabihin ang motor ay nakakumpleto ng 2.5 ikot bawat segundo. Ginamit mo ang isang digital na signal upang paikutin ang motor sa 2.5 ikot bawat segundo, o 150 [revolutions per minute](https://wikipedia.org/wiki/Revolutions_per_minute) (isang hindi karaniwang sukat ng bilis ng pag-ikot).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Kapag ang isang PWM signal ay naka-on sa kalahati ng oras, at naka-off sa kalahati, ito ay tinatawag na [50% duty cycle](https://wikipedia.org/wiki/Duty_cycle). Ang mga duty cycle ay sinusukat bilang porsyento ng oras na ang signal ay nasa on state kumpara sa off state.

![Pulse width modulation rotation ng isang motor sa 75 RPM](../../../../../translated_images/pwm-motor-75rpm.a5e4c939934b6e14.tl.png)

Maaari mong baguhin ang bilis ng motor sa pamamagitan ng pagbabago ng laki ng mga pulso. Halimbawa, gamit ang parehong motor, maaari mong panatilihin ang parehong cycle time na 0.04s, na may on pulse na kalahati (0.01s), at ang off pulse ay tataas sa 0.03s. Mayroon kang parehong bilang ng mga pulso bawat segundo (25), ngunit ang bawat on pulse ay kalahati ng haba. Ang kalahating haba ng pulso ay umiikot lamang sa motor ng isang ikadalawampung bahagi ng isang ikot, at sa 25 pulso bawat segundo ay makukumpleto ang 1.25 ikot bawat segundo o 75rpm. Sa pamamagitan ng pagbabago ng bilis ng pulso ng isang digital na signal, nabawasan mo ang bilis ng isang analog na motor sa kalahati.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Paano mo mapapanatili ang maayos na pag-ikot ng motor, lalo na sa mababang bilis? Gagamit ka ba ng maliit na bilang ng mahahabang pulso na may mahabang pause o maraming napakaikling pulso na may napakaikling pause?

> 💁 Ang ilang mga sensor ay gumagamit din ng PWM upang i-convert ang analog na signal sa digital na signal.

> 🎓 Maaari kang magbasa pa tungkol sa pulse-width modulation sa [pulse-width modulation page sa Wikipedia](https://wikipedia.org/wiki/Pulse-width_modulation).

### Digital na actuator

Ang mga digital na actuator, tulad ng mga digital na sensor, ay may dalawang estado na kinokontrol ng mataas o mababang boltahe o may built-in na DAC kaya maaaring i-convert ang isang digital na signal sa analog.

Isang simpleng digital na actuator ay isang LED. Kapag ang isang device ay nagpadala ng digital na signal na 1, isang mataas na boltahe ang ipinapadala na nagpapailaw sa LED. Kapag ang isang digital na signal na 0 ay ipinadala, ang boltahe ay bumababa sa 0V at ang LED ay namamatay.

![Isang LED na naka-off sa 0 volts at naka-on sa 5V](../../../../../translated_images/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.tl.png)

✅ Ano pang ibang simpleng 2-state actuator ang naiisip mo? Isang halimbawa ay isang solenoid, na isang electromagnet na maaaring i-activate upang gumawa ng mga bagay tulad ng paggalaw ng bolt ng pinto para sa pag-lock/pag-unlock ng pinto.

Ang mas advanced na digital na actuator, tulad ng mga screen, ay nangangailangan ng digital na data na maipadala sa mga partikular na format. Karaniwan silang may kasamang mga library na nagpapadali sa pagpapadala ng tamang data upang makontrol ang mga ito.

---

## 🚀 Hamon

Ang hamon sa huling dalawang aralin ay ilista ang pinakamaraming IoT device na makikita mo sa iyong bahay, paaralan, o lugar ng trabaho at tukuyin kung ang mga ito ay binuo gamit ang microcontrollers o single-board computers, o kumbinasyon ng dalawa.

Para sa bawat device na nailista mo, anong mga sensor at actuator ang nakakonekta sa mga ito? Ano ang layunin ng bawat sensor at actuator na nakakonekta sa mga device na ito?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Review at Pag-aaral sa Sarili

* Magbasa tungkol sa kuryente at mga circuit sa [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Magbasa tungkol sa iba't ibang uri ng temperature sensors sa [Seeed Studios Temperature Sensors guide](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)  
* Magbasa tungkol sa LEDs sa [Wikipedia LED page](https://wikipedia.org/wiki/Light-emitting_diode)  

## Takdang Aralin

[Mag-research tungkol sa sensors at actuators](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.