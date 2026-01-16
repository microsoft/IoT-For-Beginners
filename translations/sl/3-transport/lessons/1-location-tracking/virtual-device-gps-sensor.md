<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-28T13:20:32+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "sl"
}
-->
# Branje GPS podatkov - Virtualna IoT strojna oprema

V tem delu lekcije boste svoji virtualni IoT napravi dodali GPS senzor in prebrali vrednosti iz njega.

## Virtualna strojna oprema

Virtualna IoT naprava bo uporabljala simuliran GPS senzor, ki je dostopen prek UART preko serijskega porta.

Fizični GPS senzor ima anteno za sprejemanje radijskih valov iz GPS satelitov in pretvarjanje GPS signalov v GPS podatke. Virtualna različica to simulira tako, da omogoča nastavitev zemljepisne širine in dolžine, pošiljanje surovih NMEA stavkov ali nalaganje GPX datoteke z več lokacijami, ki se lahko vračajo zaporedno.

> 🎓 NMEA stavki bodo obravnavani kasneje v tej lekciji

### Dodajanje senzorja v CounterFit

Za uporabo virtualnega GPS senzorja ga morate dodati v aplikacijo CounterFit.

#### Naloga - dodajte senzor v CounterFit

Dodajte GPS senzor v aplikacijo CounterFit.

1. Ustvarite novo Python aplikacijo na svojem računalniku v mapi `gps-sensor` z eno datoteko `app.py` in Python virtualnim okoljem ter dodajte CounterFit pip pakete.

    > ⚠️ Lahko se sklicujete na [navodila za ustvarjanje in nastavitev CounterFit Python projekta v lekciji 1, če je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Namestite dodatni Pip paket za namestitev CounterFit shima, ki lahko komunicira s senzorji na osnovi UART preko serijske povezave. Prepričajte se, da to nameščate iz terminala z aktiviranim virtualnim okoljem.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Prepričajte se, da je CounterFit spletna aplikacija zagnana.

1. Ustvarite GPS senzor:

    1. V polju *Create sensor* v podoknu *Sensors* izberite *Sensor type* in izberite *UART GPS*.

    1. Pustite *Port* nastavljen na */dev/ttyAMA0*.

    1. Izberite gumb **Add**, da ustvarite GPS senzor na portu `/dev/ttyAMA0`.

    ![Nastavitve GPS senzorja](../../../../../translated_images/sl/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    GPS senzor bo ustvarjen in se bo pojavil na seznamu senzorjev.

    ![Ustvarjen GPS senzor](../../../../../translated_images/sl/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Programiranje GPS senzorja

Virtualna IoT naprava je zdaj pripravljena za programiranje za uporabo virtualnega GPS senzorja.

### Naloga - programirajte GPS senzor

Programirajte aplikacijo za GPS senzor.

1. Prepričajte se, da je aplikacija `gps-sensor` odprta v VS Code.

1. Odprite datoteko `app.py`.

1. Dodajte naslednjo kodo na vrh datoteke `app.py`, da povežete aplikacijo s CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodajte naslednjo kodo pod to, da uvozite nekaj potrebnih knjižnic, vključno s knjižnico za CounterFit serijski port:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Ta koda uvozi modul `serial` iz Pip paketa `counterfit_shims_serial`. Nato se poveže na serijski port `/dev/ttyAMA0` - to je naslov serijskega porta, ki ga virtualni GPS senzor uporablja za svoj UART port.

1. Dodajte naslednjo kodo pod to, da preberete iz serijskega porta in izpišete vrednosti v konzolo:

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

    Definirana je funkcija `print_gps_data`, ki izpiše vrstico, posredovano vanjo, v konzolo.

    Nato koda neskončno zanko bere toliko vrstic besedila, kolikor jih lahko prebere iz serijskega porta v vsakem zagonu zanke. Za vsako vrstico pokliče funkcijo `print_gps_data`.

    Ko so vsi podatki prebrani, zanka spi 1 sekundo, nato poskusi znova.

1. Zaženite to kodo, pri čemer uporabite drug terminal kot tistega, na katerem teče aplikacija CounterFit, da aplikacija CounterFit ostane zagnana.

1. V aplikaciji CounterFit spremenite vrednost GPS senzorja. To lahko storite na enega od naslednjih načinov:

    * Nastavite **Source** na `Lat/Lon` in določite natančno zemljepisno širino, dolžino in število satelitov, uporabljenih za GPS fiks. Ta vrednost bo poslana samo enkrat, zato označite polje **Repeat**, da se podatki ponavljajo vsako sekundo.

      ![GPS senzor z izbrano možnostjo lat lon](../../../../../translated_images/sl/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Nastavite **Source** na `NMEA` in dodajte nekaj NMEA stavkov v besedilno polje. Vse te vrednosti bodo poslane, z zamikom 1 sekunde pred vsakim novim GGA (pozicijski fiks) stavkom.

      ![GPS senzor z nastavljenimi NMEA stavki](../../../../../translated_images/sl/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Uporabite lahko orodje, kot je [nmeagen.org](https://www.nmeagen.org), za generiranje teh stavkov z risanjem na zemljevidu. Te vrednosti bodo poslane samo enkrat, zato označite polje **Repeat**, da se podatki ponavljajo eno sekundo po tem, ko so vsi poslani.

    * Nastavite **Source** na GPX datoteko in naložite GPX datoteko z lokacijami poti. GPX datoteke lahko prenesete z različnih priljubljenih spletnih mest za zemljevide in pohodništvo, kot je [AllTrails](https://www.alltrails.com/). Te datoteke vsebujejo več GPS lokacij kot pot, GPS senzor pa bo vrnil vsako novo lokacijo v intervalih po 1 sekundo.

      ![GPS senzor z nastavljeno GPX datoteko](../../../../../translated_images/sl/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Te vrednosti bodo poslane samo enkrat, zato označite polje **Repeat**, da se podatki ponavljajo eno sekundo po tem, ko so vsi poslani.

    Ko konfigurirate nastavitve GPS, izberite gumb **Set**, da te vrednosti shranite v senzor.

1. Videli boste surov izhod iz GPS senzorja, nekaj takega:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 To kodo lahko najdete v mapi [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Vaš program za GPS senzor je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.