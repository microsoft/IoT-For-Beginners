<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:42:50+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "sw"
}
-->
# Kugundua ukaribu - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kihisi cha ukaribu kwenye Raspberry Pi yako, na kusoma umbali kutoka kwake.

## Vifaa

Raspberry Pi inahitaji kihisi cha ukaribu.

Kihisi utakachotumia ni [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Kihisi hiki kinatumia moduli ya kupima umbali kwa laser kugundua umbali. Kihisi hiki kina uwezo wa kupima kati ya 10mm hadi 2000mm (1cm - 2m), na kitaripoti thamani kwa usahihi katika kiwango hicho, huku umbali zaidi ya 1000mm ukiripotiwa kama 8109mm.

Kipima umbali cha laser kiko nyuma ya kihisi, upande wa pili wa soketi ya Grove.

Hiki ni kihisi cha I²C.

### Unganisha kihisi cha Time of Flight

Kihisi cha Grove Time of Flight kinaweza kuunganishwa na Raspberry Pi.

#### Kazi - Unganisha kihisi cha Time of Flight

Unganisha kihisi cha Time of Flight.

![Kihisi cha Grove Time of Flight](../../../../../translated_images/sw/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya kihisi cha Time of Flight. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye moja ya soketi za I²C zilizowekwa alama **I²C** kwenye Grove Base hat iliyounganishwa na Pi. Soketi hizi ziko kwenye safu ya chini, upande wa pili wa pini za GPIO na karibu na nafasi ya kebo ya kamera.

![Kihisi cha Grove Time of Flight kimeunganishwa kwenye soketi ya I²C](../../../../../translated_images/sw/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programu ya kihisi cha Time of Flight

Sasa Raspberry Pi inaweza kupangwa kutumia kihisi cha Time of Flight kilichounganishwa.

### Kazi - Programu ya kihisi cha Time of Flight

Programu kifaa.

1. Washa Pi na subiri ianze.

1. Fungua msimbo wa `fruit-quality-detector` kwenye VS Code, ama moja kwa moja kwenye Pi, au unganisha kupitia kiendelezi cha Remote SSH.

1. Sakinisha kifurushi cha rpi-vl53l0x cha Pip, kifurushi cha Python kinachoshirikiana na kihisi cha umbali cha VL53L0X Time of Flight. Sakinisha kwa kutumia amri hii ya pip:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Unda faili mpya kwenye mradi huu inayoitwa `distance-sensor.py`.

    > 💁 Njia rahisi ya kuiga vifaa vingi vya IoT ni kufanya kila moja katika faili tofauti ya Python, kisha kuviendesha kwa wakati mmoja.

1. Ongeza msimbo ufuatao kwenye faili hii:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Hii inaingiza maktaba ya Grove I²C bus, na maktaba ya kihisi kwa vifaa vya msingi vilivyojengwa ndani ya kihisi cha Grove Time of Flight.

1. Chini ya hii, ongeza msimbo ufuatao wa kufikia kihisi:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Msimbo huu unatangaza kihisi cha umbali kwa kutumia Grove I²C bus, kisha kinaanza kihisi.

1. Hatimaye, ongeza kitanzi kisicho na mwisho cha kusoma umbali:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Msimbo huu unasubiri thamani iwe tayari kusomwa kutoka kwa kihisi, kisha inaichapisha kwenye koni.

1. Endesha msimbo huu.

    > 💁 Usisahau faili hii inaitwa `distance-sensor.py`! Hakikisha unaendesha hii kupitia Python, si `app.py`.

1. Utaona vipimo vya umbali vikionekana kwenye koni. Weka vitu karibu na kihisi na utaona kipimo cha umbali:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Kipima umbali kiko nyuma ya kihisi, kwa hivyo hakikisha unatumia upande sahihi unapopima umbali.

    ![Kipima umbali kilicho nyuma ya kihisi cha Time of Flight kikielekezwa kwenye ndizi](../../../../../translated_images/sw/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Programu yako ya kihisi cha ukaribu imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.