<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-27T21:52:27+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "tl"
}
-->
C, na binibigkas bilang *I-squared-C*, ay isang multi-controller, multi-peripheral na protocol, kung saan ang anumang nakakonektang device ay maaaring kumilos bilang controller o peripheral na nakikipag-ugnayan sa I²C bus (ang tawag sa isang sistema ng komunikasyon na naglilipat ng data). Ang data ay ipinapadala bilang mga addressed packet, kung saan ang bawat packet ay naglalaman ng address ng nakakonektang device na pinatutunguhan nito.

> 💁 Ang modelong ito ay dating tinatawag na master/slave, ngunit ang terminolohiyang ito ay iniiwasan na dahil sa kaugnayan nito sa pagkaalipin. Ang [Open Source Hardware Association ay nagpatibay ng controller/peripheral](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), ngunit maaari mo pa ring makita ang mga sanggunian sa lumang terminolohiya.

Ang mga device ay may address na ginagamit kapag sila ay kumokonekta sa I²C bus, at karaniwang ito ay hard coded sa device. Halimbawa, ang bawat uri ng Grove sensor mula sa Seeed ay may parehong address, kaya lahat ng light sensors ay may parehong address, lahat ng buttons ay may parehong address na iba sa address ng light sensor. Ang ilang mga device ay may paraan upang baguhin ang address, sa pamamagitan ng pagbabago ng jumper settings o pagsasama ng mga pin sa pamamagitan ng soldering.

Ang I²C ay may bus na binubuo ng 2 pangunahing mga wire, kasama ang 2 power wires:

| Wire | Pangalan | Paglalarawan |
| ---- | --------- | ----------- |
| SDA | Serial Data | Ang wire na ito ay para sa pagpapadala ng data sa pagitan ng mga device. |
| SCL | Serial Clock | Ang wire na ito ay nagpapadala ng clock signal sa bilis na itinakda ng controller. |
| VCC | Voltage common collector | Ang power supply para sa mga device. Ito ay nakakonekta sa SDA at SCL wires upang magbigay ng kanilang power sa pamamagitan ng pull-up resistor na nag-o-off ng signal kapag walang device ang controller. |
| GND | Ground | Nagbibigay ito ng karaniwang ground para sa electrical circuit. |

![I2C bus na may 3 device na nakakonekta sa SDA at SCL wires, na may parehong ground wire](../../../../../translated_images/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.tl.png)

Upang magpadala ng data, ang isang device ay maglalabas ng start condition upang ipakita na ito ay handa nang magpadala ng data. Ito ay magiging controller. Ang controller ay magpapadala ng address ng device na nais nitong makipag-ugnayan, kasama kung nais nitong magbasa o magsulat ng data. Pagkatapos maipadala ang data, ang controller ay magpapadala ng stop condition upang ipahiwatig na ito ay tapos na. Pagkatapos nito, ang ibang device ay maaaring maging controller at magpadala o tumanggap ng data.

2</sup>C ay may mga limitasyon sa bilis, na may 3 iba't ibang mode na tumatakbo sa mga nakatakdang bilis. Ang pinakamabilis ay ang High Speed mode na may maximum na bilis na 3.4Mbps (megabits per second), bagaman kakaunti lamang ang mga device na sumusuporta sa bilis na ito. Halimbawa, ang Raspberry Pi ay limitado sa fast mode na 400Kbps (kilobits per second). Ang Standard mode ay tumatakbo sa 100Kbps.

> 💁 Kung gumagamit ka ng Raspberry Pi na may Grove Base hat bilang iyong IoT hardware, makikita mo ang ilang mga I<sup>2</sup>C socket sa board na maaari mong gamitin upang makipag-ugnayan sa mga I<sup>2</sup>C sensor. Ang mga analog Grove sensor ay gumagamit din ng I<sup>2</sup>C na may ADC upang magpadala ng analog na halaga bilang digital na data, kaya ang light sensor na ginamit mo ay nagsilbing analog pin, na ang halaga ay ipinadala sa I<sup>2</sup>C dahil ang Raspberry Pi ay sumusuporta lamang sa mga digital pin.

### Universal asynchronous receiver-transmitter (UART)

Ang UART ay gumagamit ng pisikal na circuitry na nagpapahintulot sa dalawang device na makipag-ugnayan. Ang bawat device ay may 2 communication pins - transmit (Tx) at receive (Rx), kung saan ang Tx pin ng unang device ay konektado sa Rx pin ng pangalawa, at ang Tx pin ng pangalawa ay konektado sa Rx pin ng una. Pinapayagan nito ang pagpapadala ng data sa parehong direksyon.

* Ang Device 1 ay nagpapadala ng data mula sa kanyang Tx pin, na tinatanggap ng Device 2 sa kanyang Rx pin
* Ang Device 1 ay tumatanggap ng data sa kanyang Rx pin na ipinapadala ng Device 2 mula sa kanyang Tx pin

![UART na may Tx pin sa isang chip na konektado sa Rx pin ng isa pa, at kabaliktaran](../../../../../translated_images/uart.d0dbd3fb9e3728c6.tl.png)

> 🎓 Ang data ay ipinapadala nang paisa-isang bit, at ito ay kilala bilang *serial* na komunikasyon. Karamihan sa mga operating system at microcontroller ay may *serial ports*, na mga koneksyon na maaaring magpadala at tumanggap ng serial data na magagamit ng iyong code.

Ang mga UART device ay may [baud rate](https://wikipedia.org/wiki/Symbol_rate) (kilala rin bilang Symbol rate), na siyang bilis ng pagpapadala at pagtanggap ng data sa bits per second. Ang karaniwang baud rate ay 9,600, na nangangahulugang 9,600 bits (0s at 1s) ng data ang ipinapadala bawat segundo.

Ang UART ay gumagamit ng start at stop bits - nagpapadala ito ng start bit upang ipahiwatig na magsisimula na itong magpadala ng isang byte (8 bits) ng data, pagkatapos ay isang stop bit matapos maipadala ang 8 bits.

Ang bilis ng UART ay nakadepende sa hardware, ngunit kahit na ang pinakamabilis na implementasyon ay hindi lalampas sa 6.5 Mbps (megabits per second, o milyon-milyong bits, 0 o 1, na ipinapadala bawat segundo).

Maaari mong gamitin ang UART sa GPIO pins - maaari mong itakda ang isang pin bilang Tx at ang isa pa bilang Rx, pagkatapos ay ikonekta ang mga ito sa isa pang device.

> 💁 Kung gumagamit ka ng Raspberry Pi na may Grove Base hat bilang iyong IoT hardware, makikita mo ang isang UART socket sa board na maaari mong gamitin upang makipag-ugnayan sa mga sensor na gumagamit ng UART protocol.

### Serial Peripheral Interface (SPI)

Ang SPI ay idinisenyo para sa komunikasyon sa maikling distansya, tulad ng sa isang microcontroller na nakikipag-usap sa isang storage device tulad ng flash memory. Ito ay batay sa isang controller/peripheral na modelo na may isang controller (karaniwang ang processor ng IoT device) na nakikipag-ugnayan sa maraming peripherals. Ang controller ang may kontrol sa lahat sa pamamagitan ng pagpili ng isang peripheral at pagpapadala o paghingi ng data.

> 💁 Tulad ng I<sup>2</sup>C, ang mga terminong controller at peripheral ay mga kamakailang pagbabago, kaya maaari mo pa ring makita ang mga lumang termino na ginagamit.

Ang mga SPI controller ay gumagamit ng 3 wires, kasama ang 1 dagdag na wire bawat peripheral. Ang mga peripheral ay gumagamit ng 4 wires. Ang mga wire na ito ay:

| Wire | Pangalan | Paglalarawan |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | Ang wire na ito ay para sa pagpapadala ng data mula sa controller papunta sa peripheral. |
| CIPO | Controller Input, Peripheral Output | Ang wire na ito ay para sa pagpapadala ng data mula sa peripheral papunta sa controller. |
| SCLK | Serial Clock | Ang wire na ito ay nagpapadala ng clock signal sa bilis na itinakda ng controller. |
| CS   | Chip Select | Ang controller ay may maraming wires, isa bawat peripheral, at bawat wire ay konektado sa CS wire ng kaukulang peripheral. |

![SPI na may isang controller at dalawang peripherals](../../../../../translated_images/spi.297431d6f98b386b.tl.png)

Ang CS wire ay ginagamit upang i-activate ang isang peripheral sa bawat pagkakataon, na nakikipag-ugnayan sa mga COPI at CIPO wires. Kapag kailangang baguhin ng controller ang peripheral, i-deactivate nito ang CS wire na konektado sa kasalukuyang aktibong peripheral, pagkatapos ay i-activate ang wire na konektado sa peripheral na nais nitong makipag-ugnayan.

Ang SPI ay *full-duplex*, na nangangahulugang ang controller ay maaaring magpadala at tumanggap ng data nang sabay mula sa parehong peripheral gamit ang COPI at CIPO wires. Ang SPI ay gumagamit ng clock signal sa SCLK wire upang panatilihing naka-sync ang mga device, kaya hindi nito kailangan ng start at stop bits tulad ng sa UART.

Walang itinakdang limitasyon sa bilis para sa SPI, na may mga implementasyon na madalas kayang magpadala ng maraming megabytes ng data bawat segundo.

Ang mga IoT developer kit ay madalas na sumusuporta sa SPI sa ilan sa mga GPIO pins. Halimbawa, sa isang Raspberry Pi maaari mong gamitin ang GPIO pins 19, 21, 23, 24, at 26 para sa SPI.

### Wireless

Ang ilang mga sensor ay maaaring makipag-ugnayan gamit ang mga karaniwang wireless protocol, tulad ng Bluetooth (karaniwang Bluetooth Low Energy, o BLE), LoRaWAN (isang **Lo**ng **Ra**nge low power networking protocol), o WiFi. Pinapayagan nito ang mga remote sensor na hindi pisikal na konektado sa isang IoT device.

Isa sa mga halimbawa nito ay ang mga commercial soil moisture sensor. Ang mga ito ay sumusukat ng moisture sa lupa sa isang field, pagkatapos ay ipinapadala ang data sa pamamagitan ng LoRaWAN sa isang hub device, na magpoproseso ng data o magpapadala nito sa Internet. Pinapayagan nito ang sensor na malayo sa IoT device na nagma-manage ng data, binabawasan ang konsumo ng kuryente at ang pangangailangan para sa malalaking WiFi network o mahabang kable.

Ang BLE ay popular para sa mga advanced sensor tulad ng mga fitness tracker na ginagamit sa pulso. Ang mga ito ay pinagsasama ang maraming sensor at ipinapadala ang data ng sensor sa isang IoT device tulad ng iyong telepono sa pamamagitan ng BLE.

✅ Mayroon ka bang anumang bluetooth sensor sa iyong sarili, sa iyong bahay, o sa iyong paaralan? Maaaring kabilang dito ang mga temperature sensor, occupancy sensor, device tracker, at fitness device.

Ang isang popular na paraan para sa mga commercial device na kumonekta ay ang Zigbee. Ang Zigbee ay gumagamit ng WiFi upang bumuo ng mesh networks sa pagitan ng mga device, kung saan ang bawat device ay kumokonekta sa maraming kalapit na device hangga't maaari, na bumubuo ng maraming koneksyon tulad ng sapot ng gagamba. Kapag ang isang device ay nais magpadala ng mensahe sa Internet, maaari nitong ipadala ito sa pinakamalapit na mga device, na pagkatapos ay ipapasa ito sa iba pang kalapit na mga device at iba pa, hanggang sa maabot nito ang isang coordinator at maipadala sa Internet.

> 🐝 Ang pangalan na Zigbee ay tumutukoy sa sayaw ng mga pukyutan pagkatapos nilang bumalik sa kanilang pugad.

## Sukatin ang antas ng moisture sa lupa

Maaari mong sukatin ang antas ng moisture sa lupa gamit ang isang soil moisture sensor, isang IoT device, at isang house plant o kalapit na bahagi ng lupa.

### Gawain - sukatin ang soil moisture

Sundin ang kaukulang gabay upang sukatin ang soil moisture gamit ang iyong IoT device:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Single-board computer - Raspberry Pi](pi-soil-moisture.md)
* [Single-board computer - Virtual device](virtual-device-soil-moisture.md)

## Kalibrasyon ng Sensor

Ang mga sensor ay umaasa sa pagsukat ng mga electrical properties tulad ng resistance o capacitance.

> 🎓 Ang Resistance, na sinusukat sa ohms (Ω), ay kung gaano kalaki ang pagtutol sa electric current na dumadaloy sa isang bagay. Kapag ang boltahe ay inilapat sa isang materyal, ang dami ng kuryenteng dumadaan dito ay nakadepende sa resistance ng materyal. Maaari kang magbasa pa sa [electrical resistance page sa Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Ang Capacitance, na sinusukat sa farads (F), ay ang kakayahan ng isang component o circuit na mangolekta at mag-imbak ng electrical energy. Maaari kang magbasa pa tungkol sa capacitance sa [capacitance page sa Wikipedia](https://wikipedia.org/wiki/Capacitance).

Ang mga sukat na ito ay hindi palaging kapaki-pakinabang - isipin ang isang temperature sensor na nagbibigay sa iyo ng sukat na 22.5KΩ! Sa halip, ang halaga na sinusukat ay kailangang ma-convert sa isang kapaki-pakinabang na unit sa pamamagitan ng kalibrasyon - ibig sabihin, pagtutugma ng mga halagang sinusukat sa dami na sinusukat upang payagan ang mga bagong sukat na ma-convert sa tamang unit.

Ang ilang mga sensor ay dumating na pre-calibrated. Halimbawa, ang temperature sensor na ginamit mo sa nakaraang aralin ay naka-calibrate na upang maibalik nito ang sukat ng temperatura sa °C. Sa pabrika, ang unang sensor na ginawa ay ilalantad sa hanay ng mga kilalang temperatura at ang resistance ay susukatin. Ito ay gagamitin upang bumuo ng isang kalkulasyon na maaaring mag-convert mula sa halagang sinusukat sa Ω (ang unit ng resistance) patungo sa °C.

> 💁 Ang formula upang kalkulahin ang resistance mula sa temperatura ay tinatawag na [Steinhart–Hart equation](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Kalibrasyon ng Soil Moisture Sensor

Ang soil moisture ay sinusukat gamit ang gravimetric o volumetric water content.

* Ang Gravimetric ay ang timbang ng tubig sa isang unit na timbang ng lupa na sinusukat, bilang bilang ng kilo ng tubig bawat kilo ng tuyong lupa
* Ang Volumetric ay ang dami ng tubig sa isang unit na dami ng lupa na sinusukat, bilang bilang ng metro kubiko ng tubig bawat metro kubiko ng tuyong lupa

> 🇺🇸 Para sa mga Amerikano, dahil sa pagkakapareho ng mga unit, ang mga ito ay maaaring sukatin sa pounds sa halip na kilo o cubic feet sa halip na cubic meters.

Ang mga soil moisture sensor ay sumusukat ng electrical resistance o capacitance - hindi lamang ito nagbabago ayon sa soil moisture, kundi pati na rin sa uri ng lupa dahil ang mga sangkap sa lupa ay maaaring magbago ng mga electrical characteristics nito. Sa ideal na sitwasyon, ang mga sensor ay dapat i-calibrate - ibig sabihin, kumuha ng mga sukat mula sa sensor at ihambing ang mga ito sa mga sukat na nakuha gamit ang mas siyentipikong pamamaraan. Halimbawa, ang isang laboratoryo ay maaaring kalkulahin ang gravimetric soil moisture gamit ang mga sample ng isang partikular na field na kinuha ng ilang beses sa isang taon, at ang mga numerong ito ay maaaring gamitin upang i-calibrate ang sensor, pagtutugma ng sensor reading sa gravimetric soil moisture.

![Isang graph ng boltahe laban sa nilalaman ng soil moisture](../../../../../translated_images/soil-moisture-to-voltage.df86d80cda158700.tl.png)

Ang graph sa itaas ay nagpapakita kung paano i-calibrate ang isang sensor. Ang boltahe ay kinukuha para sa isang soil sample na pagkatapos ay sinusukat sa isang laboratoryo sa pamamagitan ng paghahambing ng timbang na basa sa timbang na tuyo (sa pamamagitan ng pagsukat ng timbang na basa, pagkatapos ay pagpapatuyo sa oven at pagsukat ng tuyong timbang). Kapag ang ilang mga sukat ay nakuha, ito ay maaaring i-plot sa isang graph at isang linya ang maaaring itugma sa mga puntos. Ang linyang ito ay maaaring gamitin upang i-convert ang mga soil moisture sensor readings na kinuha ng isang IoT device sa aktwal na mga sukat ng soil moisture.

💁 Para sa mga resistive soil moisture sensor, ang boltahe ay tumataas habang tumataas ang soil moisture. Para sa mga capacitive soil moisture sensor, ang boltahe ay bumababa habang tumataas ang soil moisture, kaya ang mga graph para dito ay magiging pababa, hindi pataas.

![Isang soil moisture value na interpolated mula sa graph](../../../../../translated_images/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.tl.png)

Ang graph sa itaas ay nagpapakita ng isang boltahe reading mula sa isang soil moisture sensor, at sa pamamagitan ng pagsunod nito sa linya sa graph, ang aktwal na soil moisture ay maaaring kalkulahin.

Ang pamamaraang ito ay nangangahulugan na ang magsasaka ay kailangan lamang kumuha ng ilang laboratory measurements para sa isang field, pagkatapos ay maaari nilang gamitin ang mga IoT device upang sukatin ang soil moisture - lubos na pinapabilis ang oras ng pagkuha ng mga sukat.

---

## 🚀 Hamon

Ang mga resistive at capacitive soil moisture sensor ay may ilang pagkakaiba. Ano ang mga pagkakaibang ito, at alin sa mga ito (kung mayroon man) ang pinakamainam para sa isang magsasaka na gamitin? Nagbabago ba ang sagot na ito sa pagitan ng mga umuunlad at maunlad na bansa?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Review at Pag-aaral sa Sarili

Magbasa tungkol sa hardware at mga protocol na ginagamit ng mga sensor at actuator:

* [GPIO Wikipedia page](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia page](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia page](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia page](https://wikipedia.org/wiki/I²C)
* [Zigbee Wikipedia page](https://wikipedia.org/wiki/Zigbee)

## Takdang Aralin

[Calibrate your sensor](assignment.md)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang orihinal na wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.