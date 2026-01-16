<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T21:42:47+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "sw"
}
-->
# Soma Data za GPS - Vifaa vya IoT vya Kijumlisha

Katika sehemu hii ya somo, utaongeza kihisi cha GPS kwenye kifaa chako cha IoT cha kijumlisha, na kusoma thamani kutoka kwake.

## Vifaa vya Kijumlisha

Kifaa cha IoT cha kijumlisha kitatumia kihisi cha GPS kilichosimuliwa ambacho kinapatikana kupitia UART kupitia bandari ya serial.

Kihisi halisi cha GPS kitakuwa na antena ya kupokea mawimbi ya redio kutoka kwa satelaiti za GPS, na kubadilisha mawimbi ya GPS kuwa data ya GPS. Toleo la kijumlisha linasimulia hili kwa kukuruhusu kuweka latitudo na longitudo, kutuma sentensi za NMEA mbichi, au kupakia faili ya GPX yenye maeneo mengi ambayo yanaweza kurudishwa kwa mfululizo.

> 🎓 Sentensi za NMEA zitajadiliwa baadaye katika somo hili

### Ongeza kihisi kwenye CounterFit

Ili kutumia kihisi cha GPS cha kijumlisha, unahitaji kuongeza moja kwenye programu ya CounterFit.

#### Kazi - ongeza kihisi kwenye CounterFit

Ongeza kihisi cha GPS kwenye programu ya CounterFit.

1. Unda programu mpya ya Python kwenye kompyuta yako ndani ya folda inayoitwa `gps-sensor` yenye faili moja inayoitwa `app.py` na mazingira ya kijumlisha ya Python, na ongeza vifurushi vya pip vya CounterFit.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda na kusanidi mradi wa Python wa CounterFit katika somo la 1 ikiwa inahitajika](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Sakinisha kifurushi cha ziada cha Pip ili kusakinisha shim ya CounterFit inayoweza kuzungumza na vihisi vya UART kupitia muunganisho wa serial. Hakikisha unasanikisha hii kutoka kwa terminal yenye mazingira ya kijumlisha yamewashwa.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Hakikisha programu ya wavuti ya CounterFit inaendelea kufanya kazi.

1. Unda kihisi cha GPS:

    1. Katika kisanduku cha *Create sensor* kwenye paneli ya *Sensors*, shusha kisanduku cha *Sensor type* na uchague *UART GPS*.

    1. Acha *Port* iwe imewekwa kwa */dev/ttyAMA0*

    1. Chagua kitufe cha **Add** ili kuunda kihisi cha GPS kwenye bandari `/dev/ttyAMA0`.

    ![Mipangilio ya kihisi cha GPS](../../../../../translated_images/sw/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Kihisi cha GPS kitaundwa na kitaonekana kwenye orodha ya vihisi.

    ![Kihisi cha GPS kimeundwa](../../../../../translated_images/sw/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Programu ya Kihisi cha GPS

Kifaa cha IoT cha kijumlisha sasa kinaweza kupangwa kutumia kihisi cha GPS cha kijumlisha.

### Kazi - panga kihisi cha GPS

Panga programu ya kihisi cha GPS.

1. Hakikisha programu ya `gps-sensor` imefunguliwa kwenye VS Code.

1. Fungua faili ya `app.py`.

1. Ongeza msimbo ufuatao juu ya `app.py` ili kuunganisha programu na CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Ongeza msimbo ufuatao chini ya huu ili kuingiza maktaba zinazohitajika, ikijumuisha maktaba ya bandari ya serial ya CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Msimbo huu unaingiza moduli ya `serial` kutoka kwenye kifurushi cha Pip cha `counterfit_shims_serial`. Kisha inaunganisha na bandari ya serial `/dev/ttyAMA0` - hii ni anwani ya bandari ya serial ambayo kihisi cha GPS cha kijumlisha hutumia kwa bandari yake ya UART.

1. Ongeza msimbo ufuatao chini ya huu ili kusoma kutoka kwenye bandari ya serial na kuchapisha thamani kwenye console:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Kazi inayoitwa `print_gps_data` inafafanuliwa ambayo inachapisha mstari uliopitishwa kwake kwenye console.

    Kisha msimbo unazunguka milele, ukisoma mistari mingi ya maandishi kadri inavyoweza kutoka kwenye bandari ya serial katika kila mzunguko. Inaita kazi ya `print_gps_data` kwa kila mstari.

    Baada ya data yote kusomwa, mzunguko unalala kwa sekunde 1, kisha unajaribu tena.

1. Endesha msimbo huu, ukihakikisha unatumia terminal tofauti na ile ambayo programu ya CounterFit inaendelea kufanya kazi, ili programu ya CounterFit iendelee kufanya kazi.

1. Kutoka kwenye programu ya CounterFit, badilisha thamani ya kihisi cha GPS. Unaweza kufanya hivi kwa njia moja kati ya hizi:

    * Weka **Source** kuwa `Lat/Lon`, na weka latitudo, longitudo, na idadi ya satelaiti zinazotumika kupata GPS fix. Thamani hii itatumwa mara moja tu, kwa hivyo angalia kisanduku cha **Repeat** ili data irudiwe kila sekunde.

      ![Kihisi cha GPS kikiwa na lat lon kimechaguliwa](../../../../../translated_images/sw/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Weka **Source** kuwa `NMEA` na ongeza sentensi za NMEA kwenye kisanduku cha maandishi. Thamani hizi zote zitatumwa, na kuchelewa kwa sekunde 1 kabla ya kila sentensi mpya ya GGA (position fix) kusomwa.

      ![Kihisi cha GPS kikiwa na sentensi za NMEA zimewekwa](../../../../../translated_images/sw/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Unaweza kutumia zana kama [nmeagen.org](https://www.nmeagen.org) kuzalisha sentensi hizi kwa kuchora kwenye ramani. Thamani hizi zitatumwa mara moja tu, kwa hivyo angalia kisanduku cha **Repeat** ili data irudiwe sekunde moja baada ya yote kutumwa.

    * Weka **Source** kuwa faili ya GPX, na pakia faili ya GPX yenye maeneo ya njia. Unaweza kupakua faili za GPX kutoka kwa tovuti maarufu za ramani na kupanda mlima, kama [AllTrails](https://www.alltrails.com/). Faili hizi zina maeneo mengi ya GPS kama njia, na kihisi cha GPS kitarudisha kila eneo jipya kwa vipindi vya sekunde 1.

      ![Kihisi cha GPS kikiwa na faili ya GPX imewekwa](../../../../../translated_images/sw/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Thamani hizi zitatumwa mara moja tu, kwa hivyo angalia kisanduku cha **Repeat** ili data irudiwe sekunde moja baada ya yote kutumwa.

    Mara tu unapopanga mipangilio ya GPS, chagua kitufe cha **Set** ili kuhifadhi thamani hizi kwenye kihisi.

1. Utaona matokeo ghafi kutoka kwa kihisi cha GPS, kitu kama hiki:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Programu yako ya kihisi cha GPS imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.