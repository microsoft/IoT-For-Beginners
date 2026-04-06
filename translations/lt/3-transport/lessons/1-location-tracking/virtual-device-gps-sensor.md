# Skaitykite GPS duomenis - Virtuali IoT Aparatūra

Šioje pamokos dalyje pridėsite GPS jutiklį prie savo virtualaus IoT įrenginio ir skaitysite jo duomenis.

## Virtuali Aparatūra

Virtualus IoT įrenginys naudos imituotą GPS jutiklį, kuris yra pasiekiamas per UART naudojant nuoseklųjį prievadą.

Fizinis GPS jutiklis turi anteną, kuri priima radijo bangas iš GPS palydovų ir paverčia GPS signalus į GPS duomenis. Virtuali versija tai imituoja, leidžiant nustatyti platumą ir ilgumą, siųsti neapdorotas NMEA eilutes arba įkelti GPX failą su keliais vietos taškais, kurie gali būti grąžinami paeiliui.

> 🎓 NMEA eilutės bus aptartos vėliau šioje pamokoje

### Pridėkite jutiklį prie CounterFit

Norėdami naudoti virtualų GPS jutiklį, turite jį pridėti prie CounterFit programos.

#### Užduotis - pridėkite jutiklį prie CounterFit

Pridėkite GPS jutiklį prie CounterFit programos.

1. Sukurkite naują Python programą savo kompiuteryje aplanke, pavadintame `gps-sensor`, su vienu failu, pavadintu `app.py`, ir Python virtualią aplinką, tada pridėkite CounterFit pip paketus.

    > ⚠️ Jei reikia, galite pasinaudoti [instrukcijomis, kaip sukurti ir nustatyti CounterFit Python projektą 1-oje pamokoje](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Įdiekite papildomą Pip paketą, kuris leidžia naudoti CounterFit shim, galintį bendrauti su UART pagrįstais jutikliais per nuoseklųjį ryšį. Įsitikinkite, kad tai darote terminale su aktyvuota virtualia aplinka.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Įsitikinkite, kad CounterFit žiniatinklio programa veikia.

1. Sukurkite GPS jutiklį:

    1. Laukelyje *Create sensor* skiltyje *Sensors* išskleidžiamajame meniu *Sensor type* pasirinkite *UART GPS*.

    1. Palikite *Port* nustatytą kaip */dev/ttyAMA0*.

    1. Pasirinkite mygtuką **Add**, kad sukurtumėte GPS jutiklį prievade `/dev/ttyAMA0`.

    ![GPS jutiklio nustatymai](../../../../../translated_images/lt/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    GPS jutiklis bus sukurtas ir pasirodys jutiklių sąraše.

    ![Sukurtas GPS jutiklis](../../../../../translated_images/lt/counterfit-gps-sensor.3fbb15af0a536756.webp)

## Užprogramuokite GPS jutiklį

Dabar virtualus IoT įrenginys gali būti užprogramuotas naudoti virtualų GPS jutiklį.

### Užduotis - užprogramuokite GPS jutiklį

Užprogramuokite GPS jutiklio programą.

1. Įsitikinkite, kad `gps-sensor` programa yra atidaryta VS Code.

1. Atidarykite `app.py` failą.

1. Pridėkite šį kodą į `app.py` viršų, kad prijungtumėte programą prie CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridėkite šį kodą žemiau, kad importuotumėte reikalingas bibliotekas, įskaitant biblioteką CounterFit nuosekliajam prievadui:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Šis kodas importuoja `serial` modulį iš `counterfit_shims_serial` Pip paketo. Tada jis prisijungia prie `/dev/ttyAMA0` nuosekliojo prievado - tai yra nuosekliojo prievado adresas, kurį naudoja virtualus GPS jutiklis savo UART prievadui.

1. Pridėkite šį kodą žemiau, kad skaitytumėte iš nuosekliojo prievado ir spausdintumėte reikšmes į konsolę:

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

    Apibrėžiama funkcija `print_gps_data`, kuri spausdina perduotą eilutę į konsolę.

    Toliau kodas vykdo begalinį ciklą, skaitydamas tiek teksto eilučių, kiek gali, iš nuosekliojo prievado kiekviename cikle. Jis kviečia funkciją `print_gps_data` kiekvienai eilutei.

    Kai visi duomenys yra perskaityti, ciklas laukia 1 sekundę ir bando dar kartą.

1. Paleiskite šį kodą, užtikrindami, kad naudojate kitą terminalą nei tą, kuriame veikia CounterFit programa, kad CounterFit programa liktų aktyvi.

1. CounterFit programoje pakeiskite GPS jutiklio reikšmę. Tai galite padaryti vienu iš šių būdų:

    * Nustatykite **Source** kaip `Lat/Lon` ir įveskite konkrečią platumą, ilgumą bei palydovų skaičių, naudojamą GPS fiksavimui. Ši reikšmė bus siunčiama tik vieną kartą, todėl pažymėkite **Repeat**, kad duomenys būtų kartojami kas sekundę.

      ![GPS jutiklis su pasirinktu lat lon](../../../../../translated_images/lt/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Nustatykite **Source** kaip `NMEA` ir pridėkite keletą NMEA eilučių į teksto laukelį. Visos šios reikšmės bus siunčiamos, su 1 sekundės pertrauka prieš kiekvieną naują GGA (vietos fiksavimo) eilutę.

      ![GPS jutiklis su nustatytomis NMEA eilutėmis](../../../../../translated_images/lt/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Galite naudoti tokius įrankius kaip [nmeagen.org](https://www.nmeagen.org), kad sugeneruotumėte šias eilutes, piešdami žemėlapyje. Šios reikšmės bus siunčiamos tik vieną kartą, todėl pažymėkite **Repeat**, kad duomenys būtų kartojami kas sekundę po to, kai viskas bus išsiųsta.

    * Nustatykite **Source** kaip GPX failą ir įkelkite GPX failą su maršruto vietomis. GPX failus galite atsisiųsti iš daugelio populiarių žemėlapių ir žygių svetainių, tokių kaip [AllTrails](https://www.alltrails.com/). Šie failai turi kelias GPS vietas kaip maršrutą, o GPS jutiklis grąžins kiekvieną naują vietą kas 1 sekundę.

      ![GPS jutiklis su nustatytu GPX failu](../../../../../translated_images/lt/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Šios reikšmės bus siunčiamos tik vieną kartą, todėl pažymėkite **Repeat**, kad duomenys būtų kartojami kas sekundę po to, kai viskas bus išsiųsta.

    Kai sukonfigūruosite GPS nustatymus, pasirinkite mygtuką **Set**, kad patvirtintumėte šias reikšmes jutikliui.

1. Matysite neapdorotą GPS jutiklio išvestį, panašią į šią:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Šį kodą galite rasti [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) aplanke.

😀 Jūsų GPS jutiklio programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.