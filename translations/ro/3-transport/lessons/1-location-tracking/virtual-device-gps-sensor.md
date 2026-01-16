<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-28T09:40:03+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "ro"
}
-->
# Citirea datelor GPS - Hardware IoT Virtual

În această parte a lecției, vei adăuga un senzor GPS la dispozitivul tău IoT virtual și vei citi valorile de la acesta.

## Hardware Virtual

Dispozitivul IoT virtual va folosi un senzor GPS simulat, accesibil prin UART printr-un port serial.

Un senzor GPS fizic va avea o antenă pentru a recepționa undele radio de la sateliții GPS și pentru a converti semnalele GPS în date GPS. Versiunea virtuală simulează acest lucru, permițându-ți să setezi o latitudine și longitudine, să trimiți propoziții NMEA brute sau să încarci un fișier GPX cu locații multiple care pot fi returnate secvențial.

> 🎓 Propozițiile NMEA vor fi acoperite mai târziu în această lecție

### Adăugarea senzorului în CounterFit

Pentru a folosi un senzor GPS virtual, trebuie să adaugi unul în aplicația CounterFit.

#### Sarcină - adaugă senzorul în CounterFit

Adaugă senzorul GPS în aplicația CounterFit.

1. Creează o nouă aplicație Python pe computerul tău într-un folder numit `gps-sensor` cu un singur fișier numit `app.py` și un mediu virtual Python, și adaugă pachetele pip CounterFit.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea și configurarea unui proiect Python CounterFit în lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instalează un pachet Pip suplimentar pentru a instala un shim CounterFit care poate comunica cu senzori bazați pe UART printr-o conexiune serială. Asigură-te că instalezi acest pachet dintr-un terminal cu mediul virtual activat.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Asigură-te că aplicația web CounterFit este pornită.

1. Creează un senzor GPS:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide meniul derulant *Sensor type* și selectează *UART GPS*.

    1. Lasă *Port* setat la */dev/ttyAMA0*.

    1. Selectează butonul **Add** pentru a crea senzorul GPS pe portul `/dev/ttyAMA0`.

    ![Setările senzorului GPS](../../../../../translated_images/ro/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Senzorul GPS va fi creat și va apărea în lista de senzori.

    ![Senzorul GPS creat](../../../../../translated_images/ro/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Programează senzorul GPS

Dispozitivul IoT virtual poate fi acum programat pentru a folosi senzorul GPS virtual.

### Sarcină - programează senzorul GPS

Programează aplicația senzorului GPS.

1. Asigură-te că aplicația `gps-sensor` este deschisă în VS Code.

1. Deschide fișierul `app.py`.

1. Adaugă următorul cod în partea de sus a fișierului `app.py` pentru a conecta aplicația la CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adaugă următorul cod sub acesta pentru a importa câteva biblioteci necesare, inclusiv biblioteca pentru portul serial CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Acest cod importă modulul `serial` din pachetul Pip `counterfit_shims_serial`. Apoi se conectează la portul serial `/dev/ttyAMA0` - aceasta este adresa portului serial pe care senzorul GPS virtual îl folosește pentru portul său UART.

1. Adaugă următorul cod sub acesta pentru a citi de la portul serial și a afișa valorile în consolă:

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

    Este definită o funcție numită `print_gps_data` care afișează linia transmisă către ea în consolă.

    Apoi, codul intră într-un ciclu infinit, citind cât mai multe linii de text de la portul serial în fiecare iterație. Apelează funcția `print_gps_data` pentru fiecare linie.

    După ce toate datele au fost citite, ciclul așteaptă 1 secundă, apoi încearcă din nou.

1. Rulează acest cod, asigurându-te că folosești un terminal diferit de cel în care aplicația CounterFit rulează, astfel încât aplicația CounterFit să rămână activă.

1. Din aplicația CounterFit, schimbă valoarea senzorului GPS. Poți face acest lucru în unul dintre următoarele moduri:

    * Setează **Source** la `Lat/Lon` și setează o latitudine, longitudine și numărul de sateliți folosiți pentru a obține fixarea GPS. Această valoare va fi trimisă o singură dată, așa că bifează caseta **Repeat** pentru ca datele să se repete la fiecare secundă.

      ![Senzorul GPS cu lat lon selectat](../../../../../translated_images/ro/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Setează **Source** la `NMEA` și adaugă câteva propoziții NMEA în caseta de text. Toate aceste valori vor fi trimise, cu o întârziere de 1 secundă înainte ca fiecare propoziție GGA (fixare poziție) nouă să poată fi citită.

      ![Senzorul GPS cu propoziții NMEA setate](../../../../../translated_images/ro/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Poți folosi un instrument precum [nmeagen.org](https://www.nmeagen.org) pentru a genera aceste propoziții desenând pe o hartă. Aceste valori vor fi trimise o singură dată, așa că bifează caseta **Repeat** pentru ca datele să se repete la o secundă după ce toate au fost trimise.

    * Setează **Source** la fișier GPX și încarcă un fișier GPX cu locații de traseu. Poți descărca fișiere GPX de pe o serie de site-uri populare de hărți și drumeții, cum ar fi [AllTrails](https://www.alltrails.com/). Aceste fișiere conțin locații GPS multiple ca traseu, iar senzorul GPS va returna fiecare locație nouă la intervale de 1 secundă.

      ![Senzorul GPS cu fișier GPX setat](../../../../../translated_images/ro/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Aceste valori vor fi trimise o singură dată, așa că bifează caseta **Repeat** pentru ca datele să se repete la o secundă după ce toate au fost trimise.

    După ce ai configurat setările GPS, selectează butonul **Set** pentru a confirma aceste valori pentru senzor.

1. Vei vedea ieșirea brută de la senzorul GPS, ceva de genul:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Poți găsi acest cod în folderul [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Programul senzorului GPS a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.