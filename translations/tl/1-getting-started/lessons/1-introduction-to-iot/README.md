<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-28T00:32:03+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "tl"
}
-->
# Panimula sa IoT

![Isang sketchnote overview ng araling ito](../../../../../translated_images/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.tl.jpg)

> Sketchnote ni [Nitya Narasimhan](https://github.com/nitya). I-click ang larawan para sa mas malaking bersyon.

Ang araling ito ay itinuro bilang bahagi ng [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) mula sa [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Ang aralin ay itinuro sa 2 video - isang 1 oras na leksyon, at isang 1 oras na office hour na mas malalim na tinalakay ang mga bahagi ng aralin at sinagot ang mga tanong.

[![Aralin 1: Panimula sa IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Aralin 1: Panimula sa IoT - Office hours](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 I-click ang mga larawan sa itaas upang panoorin ang mga video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Panimula

Ang araling ito ay sumasaklaw sa ilang mga panimulang paksa tungkol sa Internet of Things, at gagabayan ka sa pag-set up ng iyong hardware.

Sa araling ito, tatalakayin natin ang:

* [Ano ang 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Mga IoT device](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [I-set up ang iyong device](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Mga aplikasyon ng IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Mga halimbawa ng IoT device na maaaring nasa paligid mo](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Ano ang 'Internet of Things'?

Ang terminong 'Internet of Things' ay unang ginamit ni [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) noong 1999, upang tukuyin ang pagkonekta ng Internet sa pisikal na mundo gamit ang mga sensor. Simula noon, ang terminong ito ay ginamit upang ilarawan ang anumang device na nakikipag-ugnayan sa pisikal na mundo sa paligid nito, alinman sa pamamagitan ng pagkolekta ng data mula sa mga sensor, o pagbibigay ng mga interaksyon sa totoong mundo gamit ang mga actuator (mga device na gumagawa ng isang bagay tulad ng pag-on ng switch o pagpapailaw ng LED), na karaniwang konektado sa iba pang mga device o sa Internet.

> **Sensors** ay nangongolekta ng impormasyon mula sa mundo, tulad ng pagsukat ng bilis, temperatura, o lokasyon.
>
> **Actuators** ay nagko-convert ng mga electrical signal sa mga interaksyon sa totoong mundo tulad ng pag-trigger ng switch, pag-on ng ilaw, paggawa ng tunog, o pagpapadala ng mga control signal sa iba pang hardware, halimbawa, upang i-on ang isang power socket.

Ang IoT bilang isang teknolohiyang larangan ay higit pa sa mga device - kasama rin dito ang mga cloud-based na serbisyo na maaaring magproseso ng data mula sa mga sensor, o magpadala ng mga kahilingan sa mga actuator na konektado sa mga IoT device. Kasama rin dito ang mga device na walang o hindi nangangailangan ng koneksyon sa Internet, na madalas tawaging edge devices. Ang mga ito ay mga device na maaaring magproseso at tumugon sa data ng sensor mismo, karaniwang gamit ang mga AI model na sinanay sa cloud.

Ang IoT ay isang mabilis na lumalagong teknolohiyang larangan. Tinatayang sa pagtatapos ng 2020, 30 bilyong IoT device ang na-deploy at konektado sa Internet. Sa hinaharap, tinatayang sa 2025, ang mga IoT device ay mangongolekta ng halos 80 zettabytes ng data o 80 trilyong gigabytes. Napakaraming data niyan!

![Isang graph na nagpapakita ng aktibong IoT device sa paglipas ng panahon, na may pataas na trend mula sa mas mababa sa 5 bilyon noong 2015 hanggang higit sa 30 bilyon noong 2025](../../../../../images/connected-iot-devices.svg)

✅ Mag-research ng kaunti: Gaano karami sa data na nalilikha ng mga IoT device ang talagang nagagamit, at gaano karami ang nasasayang? Bakit napakaraming data ang hindi napapansin?

Ang data na ito ang susi sa tagumpay ng IoT. Upang maging matagumpay na IoT developer, kailangan mong maunawaan ang data na kailangan mong kolektahin, kung paano ito kokolektahin, kung paano gumawa ng mga desisyon batay dito, at kung paano gamitin ang mga desisyong iyon upang makipag-ugnayan sa pisikal na mundo kung kinakailangan.

## Mga IoT device

Ang **T** sa IoT ay nangangahulugang **Things** - mga device na nakikipag-ugnayan sa pisikal na mundo sa paligid nila alinman sa pamamagitan ng pagkolekta ng data mula sa mga sensor o pagbibigay ng mga interaksyon sa totoong mundo gamit ang mga actuator.

Ang mga device para sa produksyon o komersyal na paggamit, tulad ng mga consumer fitness tracker, o mga industrial machine controller, ay karaniwang custom-made. Gumagamit ang mga ito ng mga custom circuit board, at minsan pati mga custom processor, na idinisenyo upang matugunan ang mga pangangailangan ng isang partikular na gawain, maging ito man ay sapat na maliit upang magkasya sa pulso, o matibay upang gumana sa mataas na temperatura, mataas na stress, o mataas na vibration na kapaligiran ng pabrika.

Bilang isang developer na nag-aaral tungkol sa IoT o gumagawa ng prototype ng device, kakailanganin mong magsimula sa isang developer kit. Ang mga ito ay mga general-purpose IoT device na idinisenyo para sa mga developer, madalas na may mga tampok na hindi mo makikita sa isang production device, tulad ng isang set ng external pins upang ikonekta ang mga sensor o actuator, hardware para sa debugging, o karagdagang mga resources na magpapataas ng gastos sa isang malaking manufacturing run.

Ang mga developer kit na ito ay karaniwang nahahati sa dalawang kategorya - microcontrollers at single-board computers. Ipapakilala ang mga ito dito, at tatalakayin nang mas detalyado sa susunod na aralin.

> 💁 Ang iyong telepono ay maaari ring ituring na isang general-purpose IoT device, na may mga sensor at actuator na built-in, na ginagamit ng iba't ibang app sa iba't ibang paraan kasama ang iba't ibang cloud services. Maaari ka ring makahanap ng ilang IoT tutorial na gumagamit ng phone app bilang IoT device.

### Microcontrollers

Ang microcontroller (tinatawag ding MCU, maikli para sa microcontroller unit) ay isang maliit na computer na binubuo ng:

🧠 Isa o higit pang central processing units (CPUs) - ang 'utak' ng microcontroller na nagpapatakbo ng iyong programa

💾 Memorya (RAM at program memory) - kung saan nakaimbak ang iyong programa, data, at mga variable

🔌 Programmable input/output (I/O) connections - upang makipag-usap sa mga external peripherals (mga nakakonektang device) tulad ng mga sensor at actuator

Ang mga microcontroller ay karaniwang mababa ang halaga, na may average na presyo para sa mga ginagamit sa custom hardware na bumababa sa humigit-kumulang US$0.50, at ang ilan ay kasing mura ng US$0.03. Ang mga developer kit ay maaaring magsimula sa halagang US$4, na tumataas ang gastos habang nadaragdagan ang mga tampok. Ang [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), isang microcontroller developer kit mula sa [Seeed studios](https://www.seeedstudio.com) na may mga sensor, actuator, WiFi, at screen ay nagkakahalaga ng humigit-kumulang US$30.

![Isang Wio Terminal](../../../../../translated_images/wio-terminal.b8299ee16587db9aa9e05fabf9721bccd9eb8fb541b7c1a8267241282d81b603.tl.png)

> 💁 Kapag naghahanap sa Internet ng mga microcontroller, mag-ingat sa paghahanap gamit ang terminong **MCU** dahil magdadala ito ng maraming resulta tungkol sa Marvel Cinematic Universe, hindi microcontrollers.

Ang mga microcontroller ay idinisenyo upang ma-program para sa limitadong bilang ng mga napaka-espesipikong gawain, sa halip na maging general-purpose computers tulad ng mga PC o Mac. Maliban sa napaka-espesipikong mga sitwasyon, hindi mo maaaring ikonekta ang isang monitor, keyboard, at mouse upang gamitin ang mga ito para sa mga general-purpose na gawain.

Ang mga microcontroller developer kit ay karaniwang may kasamang karagdagang mga sensor at actuator na naka-built-in. Karamihan sa mga board ay may isa o higit pang mga LED na maaari mong i-program, kasama ang iba pang mga device tulad ng mga standard plugs para sa pagdaragdag ng higit pang mga sensor o actuator gamit ang iba't ibang ecosystem ng mga manufacturer o mga built-in sensor (karaniwang ang pinakapopular tulad ng mga temperature sensor). Ang ilang mga microcontroller ay may built-in na wireless connectivity tulad ng Bluetooth o WiFi o may karagdagang microcontroller sa board upang magdagdag ng connectivity na ito.

> 💁 Ang mga microcontroller ay karaniwang na-program gamit ang C/C++.

### Single-board computers

Ang single-board computer ay isang maliit na computing device na may lahat ng elemento ng isang kumpletong computer na nakapaloob sa isang maliit na board. Ang mga ito ay mga device na may mga specification na malapit sa isang desktop o laptop PC o Mac, nagpapatakbo ng isang buong operating system, ngunit maliit, mas mababa ang konsumo sa kuryente, at mas mura.

![Isang Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456db1327e86b395ddcd735513267aafd4879ea2785f7792eac.tl.jpg)

Ang Raspberry Pi ay isa sa mga pinakasikat na single-board computers.

Tulad ng microcontroller, ang single-board computers ay may CPU, memorya, at input/output pins, ngunit mayroon silang karagdagang mga tampok tulad ng graphics chip upang payagan kang ikonekta ang mga monitor, audio outputs, at USB ports upang ikonekta ang mga keyboard, mouse, at iba pang standard USB devices tulad ng webcams o external storage. Ang mga programa ay nakaimbak sa SD cards o hard drives kasama ang operating system, sa halip na isang memory chip na built-in sa board.

> 🎓 Maaari mong isipin ang single-board computer bilang isang mas maliit, mas murang bersyon ng PC o Mac na binabasa mo ngayon, na may karagdagang GPIO (general-purpose input/output) pins upang makipag-ugnayan sa mga sensor at actuator.

Ang single-board computers ay mga fully-featured computers, kaya maaaring i-program sa anumang wika. Ang mga IoT device ay karaniwang na-program gamit ang Python.

### Mga pagpipilian sa hardware para sa natitirang mga aralin

Ang lahat ng mga susunod na aralin ay may kasamang mga assignment gamit ang isang IoT device upang makipag-ugnayan sa pisikal na mundo at makipag-usap sa cloud. Ang bawat aralin ay sumusuporta sa 3 pagpipilian ng device - Arduino (gamit ang Seeed Studios Wio Terminal), o isang single-board computer, alinman sa isang pisikal na device (isang Raspberry Pi 4) o isang virtual single-board computer na tumatakbo sa iyong PC o Mac.

Maaari mong basahin ang tungkol sa hardware na kinakailangan upang makumpleto ang lahat ng mga assignment sa [hardware guide](../../../hardware.md).

> 💁 Hindi mo kailangang bumili ng anumang IoT hardware upang makumpleto ang mga assignment, maaari mong gawin ang lahat gamit ang isang virtual single-board computer.

Ang pagpili ng hardware ay nakasalalay sa iyo - depende ito sa kung ano ang mayroon ka sa bahay o sa iyong paaralan, at kung anong programming language ang alam mo o plano mong matutunan. Parehong hardware variants ay gagamit ng parehong sensor ecosystem, kaya kung magsisimula ka sa isang landas, maaari kang lumipat sa isa pa nang hindi kailangang palitan ang karamihan sa kit. Ang virtual single-board computer ay magiging katumbas ng pag-aaral sa isang Raspberry Pi, na may karamihan sa code na maaaring ilipat sa Pi kung sa kalaunan ay makakakuha ka ng device at mga sensor.

### Arduino developer kit

Kung interesado kang matutunan ang microcontroller development, maaari mong kumpletuhin ang mga assignment gamit ang isang Arduino device. Kakailanganin mo ng pangunahing kaalaman sa C/C++ programming, dahil ang mga aralin ay magtuturo lamang ng code na may kaugnayan sa Arduino framework, mga sensor at actuator na ginagamit, at mga library na nakikipag-ugnayan sa cloud.

Ang mga assignment ay gagamit ng [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) kasama ang [PlatformIO extension para sa microcontroller development](https://platformio.org). Maaari mo ring gamitin ang Arduino IDE kung sanay ka na sa tool na ito, dahil hindi ibibigay ang mga instruksyon.

### Single-board computer developer kit

Kung interesado kang matutunan ang IoT development gamit ang single-board computers, maaari mong kumpletuhin ang mga assignment gamit ang isang Raspberry Pi, o isang virtual device na tumatakbo sa iyong PC o Mac.

Kakailanganin mo ng pangunahing kaalaman sa Python programming, dahil ang mga aralin ay magtuturo lamang ng code na may kaugnayan sa mga sensor at actuator na ginagamit, at mga library na nakikipag-ugnayan sa cloud.

> 💁 Kung nais mong matutong mag-code sa Python, tingnan ang sumusunod na dalawang video series:
>
> * [Python para sa mga baguhan](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Higit pang Python para sa mga baguhan](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Ang mga assignment ay gagamit ng [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Kung gumagamit ka ng Raspberry Pi, maaari mong patakbuhin ang iyong Pi gamit ang buong desktop na bersyon ng Raspberry Pi OS, at gawin ang lahat ng coding nang direkta sa Pi gamit ang [bersyon ng Raspberry Pi OS ng VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), o patakbuhin ang iyong Pi bilang isang headless device at mag-code mula sa iyong PC o Mac gamit ang VS Code kasama ang [Remote SSH extension](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) na nagpapahintulot sa iyo na kumonekta sa iyong Pi at mag-edit, mag-debug, at magpatakbo ng code na parang nagko-code ka nang direkta dito.

Kung gagamitin mo ang virtual device na opsyon, magko-code ka nang direkta sa iyong computer. Sa halip na ma-access ang mga sensor at actuator, gagamit ka ng tool upang i-simulate ang hardware na ito na nagbibigay ng mga sensor value na maaari mong tukuyin, at ipinapakita ang mga resulta ng actuator sa screen.

## I-set up ang iyong device

Bago ka makapagsimula sa pag-program ng iyong IoT device, kakailanganin mong gawin ang kaunting setup. Sundin ang mga kaukulang instruksyon sa ibaba depende sa kung aling device ang gagamitin mo.
💁 Kung wala ka pang device, tingnan ang [hardware guide](../../../hardware.md) para makatulong sa pagpili kung anong device ang gagamitin mo, at kung anong karagdagang hardware ang kailangan mong bilhin. Hindi mo kailangang bumili ng hardware, dahil lahat ng proyekto ay maaaring patakbuhin gamit ang virtual hardware.
Ang mga tagubilin na ito ay naglalaman ng mga link sa mga third-party na website mula sa mga tagalikha ng hardware o tools na gagamitin mo. Ito ay upang matiyak na palagi kang gumagamit ng pinakabagong mga tagubilin para sa iba't ibang tools at hardware.

Sundin ang kaukulang gabay upang i-set up ang iyong device at kumpletuhin ang isang 'Hello World' na proyekto. Ito ang magiging unang hakbang sa paglikha ng isang IoT nightlight sa loob ng 4 na leksyon sa bahaging ito ng pagsisimula.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi](pi.md)
* [Single-board computer - Virtual device](virtual-device.md)

✅ Gagamitin mo ang VS Code para sa parehong Arduino at Single-board computers. Kung hindi mo pa ito nagagamit, basahin ang higit pa tungkol dito sa [VS Code site](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Mga Aplikasyon ng IoT

Ang IoT ay sumasaklaw sa napakalaking hanay ng mga use case, sa ilang malawak na grupo:

* Consumer IoT
* Commercial IoT
* Industrial IoT
* Infrastructure IoT

✅ Mag-research ng kaunti: Para sa bawat lugar na inilarawan sa ibaba, maghanap ng isang konkretong halimbawa na hindi binanggit sa teksto.

### Consumer IoT

Ang Consumer IoT ay tumutukoy sa mga IoT device na binibili at ginagamit ng mga consumer sa kanilang tahanan. Ang ilan sa mga device na ito ay napaka-kapaki-pakinabang, tulad ng smart speakers, smart heating systems, at robotic vacuum cleaners. Ang iba naman ay may pagdududa sa kanilang pakinabang, tulad ng voice-controlled taps na hindi mo ma-off dahil hindi maririnig ng voice control ang iyong boses sa tunog ng umaagos na tubig.

Ang mga Consumer IoT device ay nagbibigay kapangyarihan sa mga tao na makamit ang higit pa sa kanilang kapaligiran, lalo na ang 1 bilyong tao na may kapansanan. Ang mga robotic vacuum cleaners ay maaaring magbigay ng malinis na sahig sa mga taong may mobility issues na hindi makapaglinis ng sahig nang mag-isa, ang mga voice-controlled ovens ay nagbibigay-daan sa mga taong may limitadong paningin o motor control na painitin ang kanilang oven gamit lamang ang kanilang boses, at ang mga health monitors ay nagbibigay-daan sa mga pasyente na subaybayan ang kanilang mga chronic conditions nang mas regular at mas detalyado. Ang mga device na ito ay nagiging napaka-karaniwan na kahit ang mga bata ay ginagamit na ito bilang bahagi ng kanilang pang-araw-araw na buhay, halimbawa, ang mga estudyante na gumagawa ng virtual schooling noong pandemya ng COVID ay nagse-set ng timers sa mga smart home devices upang subaybayan ang kanilang schoolwork o alarms upang ipaalala sa kanila ang mga paparating na klase.

✅ Anong mga Consumer IoT device ang mayroon ka sa iyong sarili o sa iyong tahanan?

### Commercial IoT

Ang Commercial IoT ay sumasaklaw sa paggamit ng IoT sa lugar ng trabaho. Sa isang opisina, maaaring may mga occupancy sensors at motion detectors upang pamahalaan ang ilaw at heating upang panatilihing naka-off ang mga ito kapag hindi kailangan, na nagbabawas ng gastos at carbon emissions. Sa isang pabrika, ang mga IoT device ay maaaring mag-monitor ng mga panganib sa kaligtasan tulad ng mga manggagawa na hindi nagsusuot ng hard hats o ingay na umabot sa mapanganib na antas. Sa retail, ang mga IoT device ay maaaring sukatin ang temperatura ng cold storage, na nag-aalerto sa may-ari ng tindahan kung ang isang fridge o freezer ay nasa labas ng kinakailangang temperature range, o maaari nilang subaybayan ang mga item sa mga shelves upang idirekta ang mga empleyado na mag-refill ng mga produkto na nabili na. Ang industriya ng transportasyon ay lalong umaasa sa IoT upang subaybayan ang lokasyon ng mga sasakyan, subaybayan ang mileage sa kalsada para sa road user charging, subaybayan ang oras ng driver at pagsunod sa break, o mag-notify sa mga staff kapag ang isang sasakyan ay papalapit sa depot upang maghanda para sa loading o unloading.

✅ Anong mga Commercial IoT device ang mayroon sa iyong paaralan o lugar ng trabaho?

### Industrial IoT (IIoT)

Ang Industrial IoT, o IIoT, ay ang paggamit ng mga IoT device upang kontrolin at pamahalaan ang mga makinarya sa malakihang antas. Saklaw nito ang malawak na hanay ng mga use case, mula sa mga pabrika hanggang sa digital agriculture.

Ang mga pabrika ay gumagamit ng IoT device sa maraming iba't ibang paraan. Ang mga makinarya ay maaaring i-monitor gamit ang maraming sensors upang subaybayan ang mga bagay tulad ng temperatura, vibration, at bilis ng pag-ikot. Ang data na ito ay maaaring i-monitor upang pahintulutan ang makina na itigil kung ito ay lumampas sa ilang mga tolerances - halimbawa, kung ito ay masyadong mainit at kailangang i-shut down. Ang data na ito ay maaari ring kolektahin at suriin sa paglipas ng panahon upang gawin ang predictive maintenance, kung saan ang mga AI models ay titingin sa data bago ang isang failure, at gagamitin ito upang hulaan ang iba pang mga failure bago ito mangyari.

Ang digital agriculture ay mahalaga upang mapakain ang lumalaking populasyon, lalo na para sa 2 bilyong tao sa 500 milyong kabahayan na umaasa sa [subsistence farming](https://wikipedia.org/wiki/Subsistence_agriculture). Ang digital agriculture ay maaaring saklaw mula sa ilang murang sensors hanggang sa malalaking commercial setups. Ang isang magsasaka ay maaaring magsimula sa pag-monitor ng temperatura at paggamit ng [growing degree days](https://wikipedia.org/wiki/Growing_degree-day) upang hulaan kung kailan magiging handa ang ani para sa pag-aani. Maaari nilang ikonekta ang soil moisture monitoring sa automated watering systems upang bigyan ang kanilang mga halaman ng tamang dami ng tubig na kailangan, ngunit hindi sobra upang matiyak na ang kanilang mga pananim ay hindi matutuyo nang hindi nasasayang ang tubig. Ang mga magsasaka ay mas pinapalawak pa ito gamit ang drones, satellite data, at AI upang subaybayan ang paglago ng pananim, sakit, at kalidad ng lupa sa malalaking lugar ng sakahan.

✅ Anong iba pang IoT device ang maaaring makatulong sa mga magsasaka?

### Infrastructure IoT

Ang Infrastructure IoT ay ang pag-monitor at pagkontrol sa lokal at pandaigdigang imprastraktura na ginagamit ng mga tao araw-araw.

Ang [Smart Cities](https://wikipedia.org/wiki/Smart_city) ay mga urban area na gumagamit ng IoT device upang mangolekta ng data tungkol sa lungsod at gamitin ito upang mapabuti kung paano tumatakbo ang lungsod. Ang mga lungsod na ito ay karaniwang pinapatakbo sa pakikipagtulungan ng mga lokal na pamahalaan, akademya, at lokal na negosyo, na sinusubaybayan at pinamamahalaan ang mga bagay mula sa transportasyon hanggang sa parking at polusyon. Halimbawa, sa Copenhagen, Denmark, mahalaga ang air pollution sa mga lokal na residente, kaya ito ay sinusukat at ang data ay ginagamit upang magbigay ng impormasyon sa pinakamalinis na ruta para sa pagbibisikleta at jogging.

Ang [Smart power grids](https://wikipedia.org/wiki/Smart_grid) ay nagbibigay-daan sa mas mahusay na analytics ng power demand sa pamamagitan ng pagkolekta ng usage data sa antas ng bawat tahanan. Ang data na ito ay maaaring magbigay ng gabay sa mga desisyon sa antas ng bansa, kabilang ang kung saan magtatayo ng mga bagong power stations, at sa personal na antas sa pamamagitan ng pagbibigay sa mga user ng insights sa kung gaano karaming power ang kanilang ginagamit, kailan nila ito ginagamit, at kahit mga mungkahi kung paano bawasan ang gastos, tulad ng pag-charge ng electric cars sa gabi.

✅ Kung maaari kang magdagdag ng IoT device upang sukatin ang anumang bagay kung saan ka nakatira, ano ito?

## Mga Halimbawa ng IoT device na maaaring nasa paligid mo

Magugulat ka kung gaano karaming IoT device ang nasa paligid mo. Isinusulat ko ito mula sa bahay at mayroon akong mga sumusunod na device na konektado sa Internet na may mga smart features tulad ng app control, voice control, o kakayahang magpadala ng data sa akin sa pamamagitan ng aking telepono:

* Maraming smart speakers
* Refrigerator, dishwasher, oven, at microwave
* Monitor ng kuryente para sa solar panels
* Smart plugs
* Video doorbell at security cameras
* Smart thermostat na may maraming smart room sensors
* Garage door opener
* Home entertainment systems at voice-controlled TVs
* Ilaw
* Fitness at health trackers

Ang lahat ng mga uri ng device na ito ay may sensors at/o actuators at nakikipag-usap sa Internet. Malalaman ko mula sa aking telepono kung bukas ang aking garage door, at maaari kong hilingin sa aking smart speaker na isara ito para sa akin. Maaari ko pa itong i-set sa timer upang kung bukas pa rin ito sa gabi, ito ay awtomatikong magsasara. Kapag tumunog ang aking doorbell, makikita ko mula sa aking telepono kung sino ang naroon kahit nasaan ako sa mundo, at makipag-usap sa kanila sa pamamagitan ng speaker at mikropono na naka-built-in sa doorbell. Maaari kong subaybayan ang aking blood glucose, heart rate, at sleep patterns, naghahanap ng mga pattern sa data upang mapabuti ang aking kalusugan. Maaari kong kontrolin ang aking mga ilaw sa pamamagitan ng cloud, at maupo sa dilim kapag bumaba ang koneksyon sa Internet.

---

## 🚀 Hamon

Maglista ng maraming IoT device hangga't maaari na nasa iyong tahanan, paaralan, o lugar ng trabaho - maaaring mas marami ito kaysa sa inaakala mo!

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Review & Self Study

Magbasa tungkol sa mga benepisyo at kabiguan ng mga consumer IoT projects. Maghanap ng mga artikulo sa mga news sites tungkol sa mga pagkakataon kung kailan ito nagkamali, tulad ng mga isyu sa privacy, problema sa hardware, o mga problemang dulot ng kawalan ng koneksyon.

Mga halimbawa:

* Tingnan ang Twitter account **[Internet of Sh*t](https://twitter.com/internetofshit)** *(babala sa masamang pananalita)* para sa ilang magagandang halimbawa ng mga kabiguan sa consumer IoT.
* [c|net - My Apple Watch saved my life: 5 people share their stories](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT technician pleads guilty to spying on customer camera feeds for years](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(babala sa sensitibong paksa - hindi kusang-loob na voyeurism)*

## Assignment

[Investigate an IoT project](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.