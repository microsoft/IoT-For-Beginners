<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:23:47+00:00",
  "source_file": "hardware.md",
  "language_code": "fi"
}
-->
# Laitteisto

IoT:n **T** tarkoittaa **Things** eli laitteita, jotka vuorovaikuttavat ympäröivän maailman kanssa. Jokainen projekti perustuu todelliseen laitteistoon, joka on saatavilla opiskelijoille ja harrastajille. Meillä on kaksi vaihtoehtoa IoT-laitteistolle, joita voi käyttää henkilökohtaisten mieltymysten, ohjelmointikielitaitojen, oppimistavoitteiden ja saatavuuden mukaan. Lisäksi olemme tarjonneet "virtuaalisen laitteiston" version niille, joilla ei ole pääsyä fyysisiin laitteisiin tai jotka haluavat oppia lisää ennen ostopäätöstä.

> 💁 Sinun ei tarvitse ostaa IoT-laitteistoa tehtävien suorittamiseksi. Kaikki voidaan tehdä virtuaalisen IoT-laitteiston avulla.

Fyysiset laitteistovaihtoehdot ovat Arduino tai Raspberry Pi. Jokaisella alustalla on omat etunsa ja haittansa, jotka käsitellään ensimmäisten oppituntien aikana. Jos et ole vielä päättänyt, mitä laitteistoalustaa haluat käyttää, voit tarkistaa [ensimmäisen projektin toisen oppitunnin](./1-getting-started/lessons/2-deeper-dive/README.md) ja valita sinua eniten kiinnostavan alustan.

Valittu laitteisto on suunniteltu vähentämään oppituntien ja tehtävien monimutkaisuutta. Vaikka muut laitteistot saattavat toimia, emme voi taata, että kaikki tehtävät ovat tuettuja laitteellasi ilman lisälaitteita. Esimerkiksi monet Arduino-laitteet eivät sisällä WiFi-yhteyttä, joka on tarpeen pilveen yhdistämiseksi - Wio Terminal valittiin, koska siinä on sisäänrakennettu WiFi.

Tarvitset myös muutamia ei-teknisiä tarvikkeita, kuten multaa tai huonekasvin sekä hedelmiä tai vihanneksia.

## Osta paketit

![Seeed Studiosin logo](../../translated_images/seeed-logo.74732b6b482b6e8e.fi.png)

Seeed Studios on ystävällisesti koonnut kaikki laitteistot helposti ostettaviksi paketeiksi:

### Arduino - Wio Terminal

**[IoT aloittelijoille Seeedin ja Microsoftin kanssa - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal -laitteistopaketti](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.fi.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT aloittelijoille Seeedin ja Microsoftin kanssa - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi -laitteistopaketti](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.fi.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Kaikki Arduino-laitteiden koodi on kirjoitettu C++-kielellä. Tehtävien suorittamiseksi tarvitset seuraavat:

### Arduino-laitteisto

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Valinnainen* - USB-C-kaapeli tai USB-A–USB-C-sovitin. Wio Terminalissa on USB-C-portti ja mukana tulee USB-C–USB-A-kaapeli. Jos tietokoneessasi tai Macissasi on vain USB-C-portteja, tarvitset USB-C-kaapelin tai USB-A–USB-C-sovittimen.

### Arduino-kohtaiset sensorit ja toimilaitteet

Nämä ovat erityisiä Wio Terminal -Arduino-laitteelle, eivätkä koske Raspberry Pi:tä.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Kuulokkeet tai muu kaiutin, jossa on 3,5 mm liitin, tai JST-kaiutin, kuten:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD-kortti, enintään 16GB, sekä liitin SD-kortin käyttämiseksi tietokoneen kanssa, jos sisäänrakennettua lukijaa ei ole. **HUOM** - Wio Terminal tukee vain SD-kortteja, joiden kapasiteetti on enintään 16GB.

## Raspberry Pi

Kaikki Raspberry Pi -laitteiden koodi on kirjoitettu Pythonilla. Tehtävien suorittamiseksi tarvitset seuraavat:

### Raspberry Pi -laitteisto

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Pi 2B ja uudemmat versiot toimivat näiden oppituntien tehtävien kanssa. Jos aiot käyttää VS Codea suoraan Pi:llä, tarvitset Pi 4:n, jossa on vähintään 2GB RAM-muistia. Jos käytät Pi:tä etänä, mikä tahansa Pi 2B ja uudempi toimii.
* microSD-kortti (Raspberry Pi -paketit sisältävät usein microSD-kortin), sekä liitin SD-kortin käyttämiseksi tietokoneen kanssa, jos sisäänrakennettua lukijaa ei ole.
* USB-virtalähde (Raspberry Pi 4 -paketit sisältävät usein virtalähteen). Jos käytät Raspberry Pi 4:ää, tarvitset USB-C-virtalähteen, aiemmat mallit tarvitsevat micro-USB-virtalähteen.

### Raspberry Pi -kohtaiset sensorit ja toimilaitteet

Nämä ovat erityisiä Raspberry Pi:lle, eivätkä koske Arduino-laitetta.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofoni ja kaiutin:

  Käytä jotakin seuraavista (tai vastaavaa):
  * USB-mikrofoni ja USB-kaiutin, kaiutin 3,5 mm liittimellä, tai HDMI-äänilähtö, jos Raspberry Pi on kytketty näyttöön tai televisioon, jossa on kaiuttimet
  * USB-kuulokkeet, joissa on sisäänrakennettu mikrofoni
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) ja
    * Kuulokkeet tai muu kaiutin, jossa on 3,5 mm liitin, tai JST-kaiutin, kuten:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Sensorit ja toimilaitteet

Suurin osa tarvittavista sensoreista ja toimilaitteista on käytössä sekä Arduino- että Raspberry Pi -oppimispoluilla:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove kosteus- ja lämpötila-anturi](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapasitiivinen maankosteusanturi](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove rele](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Valinnainen laitteisto

Automatisoidun kastelun oppitunnit toimivat releen avulla. Vaihtoehtoisesti voit liittää releen USB-virralla toimivaan vesipumppuun alla listattujen tarvikkeiden avulla.

* [6V vesipumppu](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB-liitin](https://www.adafruit.com/product/3628)
* Silikoniputket
* Punaiset ja mustat johdot
* Pieni litteä ruuvimeisseli

## Virtuaalinen laitteisto

Virtuaalinen laitteistovaihtoehto tarjoaa simulaattoreita sensoreille ja toimilaitteille, jotka on toteutettu Pythonilla. Laitteistosi saatavuudesta riippuen voit käyttää tätä normaalilla kehityslaitteellasi, kuten Macilla, PC:llä, tai Raspberry Pi:llä ja simuloida vain puuttuvat laitteet. Esimerkiksi, jos sinulla on Raspberry Pi -kamera mutta ei Grove-sensoreita, voit ajaa virtuaalista laitteistokoodia Pi:llä ja simuloida Grove-sensorit, mutta käyttää fyysistä kameraa.

Virtuaalinen laitteisto käyttää [CounterFit-projektia](https://github.com/CounterFit-IoT/CounterFit).

Näiden oppituntien suorittamiseksi tarvitset verkkokameran, mikrofonin ja äänilähdön, kuten kaiuttimet tai kuulokkeet. Nämä voivat olla sisäänrakennettuja tai ulkoisia, ja niiden tulee olla käyttöjärjestelmän kanssa yhteensopivia ja käytettävissä kaikissa sovelluksissa.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.