<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-28T13:21:06+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "hr"
}
-->
# Istražite druge GPS podatke

## Upute

NMEA rečenice koje dolaze s vašeg GPS senzora sadrže i druge podatke osim lokacije. Istražite dodatne podatke i iskoristite ih u svom IoT uređaju.

Na primjer - možete li dobiti trenutni datum i vrijeme? Ako koristite mikrokontroler, možete li postaviti sat koristeći GPS podatke na isti način kao što ste ga postavili koristeći NTP signale u prethodnom projektu? Možete li dobiti nadmorsku visinu (vašu visinu iznad razine mora) ili trenutnu brzinu?

Ako koristite virtualni IoT uređaj, neke od ovih podataka možete dobiti slanjem NMEA rečenica generiranih pomoću alata [nmeagen.org](https://www.nmeagen.org).

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | --------- | --------------- | -------------------- |
| Dobivanje više GPS podataka | Uspijeva dobiti i koristiti više GPS podataka, bilo kao telemetriju ili za postavljanje IoT uređaja | Uspijeva dobiti više GPS podataka, ali ih ne može koristiti | Ne uspijeva dobiti više GPS podataka |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.