<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:56:55+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "fi"
}
-->
# Tunnista etäisyys - Wio Terminal

Tässä oppitunnin osassa lisäät Wio Terminaliin etäisyyssensorin ja luet sen avulla etäisyyksiä.

## Laitteisto

Wio Terminal tarvitsee etäisyyssensorin.

Käytettävä sensori on [Grove Time of Flight -etäisyyssensori](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Tämä sensori käyttää lasermittaustekniikkaa etäisyyden havaitsemiseen. Sensorin mittausalue on 10 mm - 2000 mm (1 cm - 2 m), ja se raportoi arvot tällä alueella melko tarkasti. Yli 1000 mm:n etäisyydet raportoidaan arvolla 8109 mm.

Laseretäisyysmittari sijaitsee sensorin takapuolella, vastakkaisella puolella Grove-liitintä.

Tämä on I2C-sensori.

### Yhdistä Time of Flight -sensori

Grove Time of Flight -sensori voidaan liittää Wio Terminaliin.

#### Tehtävä - yhdistä Time of Flight -sensori

Yhdistä Time of Flight -sensori.

![Grove Time of Flight -sensori](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.fi.png)

1. Työnnä Grove-kaapelin toinen pää Time of Flight -sensorin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Wio Terminal ei ole kytketty tietokoneeseen tai muuhun virtalähteeseen, liitä Grove-kaapelin toinen pää Wio Terminalin vasemmanpuoleiseen Grove-liittimeen, kun katsot näyttöä. Tämä liitin on lähimpänä virtapainiketta. Tämä on yhdistetty digitaalinen ja I2C-liitin.

![Grove Time of Flight -sensori liitettynä vasempaan liittimeen](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.fi.png)

1. Nyt voit liittää Wio Terminalin tietokoneeseesi.

## Ohjelmoi Time of Flight -sensori

Wio Terminal voidaan nyt ohjelmoida käyttämään liitettyä Time of Flight -sensoria.

### Tehtävä - ohjelmoi Time of Flight -sensori

1. Luo uusi Wio Terminal -projekti PlatformIO:lla. Nimeä projekti `distance-sensor`. Lisää koodia `setup`-funktioon sarjaportin konfiguroimiseksi.

1. Lisää projektin `platformio.ini`-tiedostoon kirjastoriippuvuus Seeed Grove Time of Flight -etäisyyssensorikirjastolle:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Lisää `main.cpp`-tiedostoon seuraava olemassa olevien include-direktiivien alle, jotta voit luoda `Seeed_vl53l0x`-luokan instanssin Time of Flight -sensorin kanssa toimimista varten:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Lisää seuraava `setup`-funktion loppuun sensorin alustamiseksi:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Lue arvo sensorista `loop`-funktiossa:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Tämä koodi alustaa tietorakenteen, johon data luetaan, ja välittää sen `PerformSingleRangingMeasurement`-metodille, joka täyttää sen etäisyysmittauksella.

1. Kirjoita tämän alle etäisyysmittaus ja viivytä 1 sekunti:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Rakenna, lataa ja suorita tämä koodi. Näet etäisyysmittaukset sarjamonitorissa. Aseta esineitä sensorin lähelle ja näet etäisyysmittauksen:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Etäisyysmittari sijaitsee sensorin takapuolella, joten varmista, että käytät oikeaa puolta etäisyyden mittaamiseen.

    ![Time of Flight -sensorin takapuolen etäisyysmittari osoittaa banaania](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.fi.png)

> 💁 Löydät tämän koodin [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) -kansiosta.

😀 Proximity-sensoriohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.