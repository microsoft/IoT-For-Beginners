<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-28T13:19:17+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "hr"
}
-->
# Dekodiranje GPS podataka - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije dekodirat ćete NMEA poruke koje čita GPS senzor putem Raspberry Pi uređaja ili Virtualnog IoT uređaja te izvući geografske širine i dužine.

## Dekodiranje GPS podataka

Nakon što se sirovi NMEA podaci pročitaju s serijskog porta, mogu se dekodirati pomoću otvorene NMEA biblioteke.

### Zadatak - dekodiranje GPS podataka

Programirajte uređaj za dekodiranje GPS podataka.

1. Otvorite projekt aplikacije `gps-sensor` ako već nije otvoren.

1. Instalirajte Pip paket `pynmea2`. Ovaj paket sadrži kod za dekodiranje NMEA poruka.

    ```sh
    pip3 install pynmea2
    ```

1. Dodajte sljedeći kod u uvoze u datoteci `app.py` kako biste uvezli modul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Zamijenite sadržaj funkcije `print_gps_data` sljedećim:

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

    Ovaj kod koristi biblioteku `pynmea2` za parsiranje linije pročitane s UART serijskog porta.

    Ako je tip rečenice poruke `GGA`, tada je to poruka o poziciji i obrađuje se. Vrijednosti geografske širine i dužine čitaju se iz poruke i pretvaraju u decimalne stupnjeve iz NMEA formata `(d)ddmm.mmmm`. Funkcija `dm_to_sd` obavlja ovu konverziju.

    Zatim se provjerava smjer geografske širine, i ako je širina južna, vrijednost se pretvara u negativan broj. Isto vrijedi i za geografsku dužinu, ako je zapadna, pretvara se u negativan broj.

    Na kraju se koordinate ispisuju na konzolu, zajedno s brojem satelita korištenih za određivanje lokacije.

1. Pokrenite kod. Ako koristite virtualni IoT uređaj, provjerite je li aplikacija CounterFit pokrenuta i šalje li GPS podatke.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) ili u mapi [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Vaš program za GPS senzor s dekodiranjem podataka bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.