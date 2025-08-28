<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T09:39:15+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "ro"
}
-->
# Decodifică datele GPS - Hardware IoT Virtual și Raspberry Pi

În această parte a lecției, vei decodifica mesajele NMEA citite de senzorul GPS de către Raspberry Pi sau Dispozitivul IoT Virtual și vei extrage latitudinea și longitudinea.

## Decodifică datele GPS

După ce datele brute NMEA au fost citite de pe portul serial, acestea pot fi decodificate folosind o bibliotecă NMEA open source.

### Sarcină - decodifică datele GPS

Programează dispozitivul pentru a decodifica datele GPS.

1. Deschide proiectul aplicației `gps-sensor` dacă nu este deja deschis.

1. Instalează pachetul Pip `pynmea2`. Acest pachet conține cod pentru decodificarea mesajelor NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Adaugă următorul cod la importurile din fișierul `app.py` pentru a importa modulul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Înlocuiește conținutul funcției `print_gps_data` cu următorul cod:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Acest cod va folosi biblioteca `pynmea2` pentru a analiza linia citită de pe portul serial UART.

    Dacă tipul propoziției mesajului este `GGA`, atunci acesta este un mesaj de fixare a poziției și este procesat. Valorile de latitudine și longitudine sunt citite din mesaj și convertite în grade zecimale din formatul NMEA `(d)ddmm.mmmm`. Funcția `dm_to_sd` realizează această conversie.

    Direcția latitudinii este apoi verificată, iar dacă latitudinea este sudică, valoarea este convertită într-un număr negativ. La fel și pentru longitudine, dacă este vestică, aceasta este convertită într-un număr negativ.

    În final, coordonatele sunt afișate pe consolă, împreună cu numărul de sateliți folosiți pentru a obține locația.

1. Rulează codul. Dacă folosești un dispozitiv IoT virtual, asigură-te că aplicația CounterFit este pornită și datele GPS sunt trimise.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Poți găsi acest cod în folderul [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) sau în folderul [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Programul senzorului GPS cu decodificarea datelor a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus utilizând serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să aveți în vedere că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.