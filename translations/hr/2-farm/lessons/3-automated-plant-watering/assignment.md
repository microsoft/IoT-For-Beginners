<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T15:25:23+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "hr"
}
-->
# Izgradite učinkovitiji ciklus zalijevanja

## Upute

Ova lekcija obuhvatila je kako upravljati relejem putem podataka senzora, a taj relej može upravljati pumpom za sustav navodnjavanja. Za određeni volumen tla, rad pumpe tijekom fiksnog vremenskog razdoblja uvijek bi trebao imati isti učinak na vlažnost tla. To znači da možete dobiti ideju o tome koliko sekundi navodnjavanja odgovara određenom padu očitanja vlažnosti tla. Koristeći te podatke, možete izgraditi kontroliraniji sustav navodnjavanja.

Za ovaj zadatak izračunat ćete koliko dugo pumpa treba raditi za određeni porast vlažnosti tla.

> ⚠️ Ako koristite virtualni IoT hardver, možete proći kroz ovaj proces, ali simulirajte rezultate ručno povećavajući očitanje vlažnosti tla za fiksni iznos po sekundi dok je relej uključen.

1. Započnite s suhim tlom. Izmjerite vlažnost tla.

1. Dodajte fiksnu količinu vode, bilo pokretanjem pumpe na 1 sekundu ili ulijevanjem fiksne količine vode.

    > Pumpa bi uvijek trebala raditi konstantnom brzinom, tako da svaka sekunda rada pumpe isporučuje istu količinu vode.

1. Pričekajte dok se razina vlažnosti tla ne stabilizira i zabilježite očitanje.

1. Ponovite ovo više puta i stvorite tablicu rezultata. Primjer takve tablice dan je u nastavku.

    | Ukupno vrijeme rada pumpe | Vlažnost tla | Pad |
    | --- | --: | -: |
    | Suho | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Izračunajte prosječni porast vlažnosti tla po sekundi dodane vode. U gornjem primjeru, svaka sekunda dodane vode smanjuje očitanje za prosječno 20.3.

1. Koristite ove podatke za poboljšanje učinkovitosti koda na serveru, pokrećući pumpu za potrebno vrijeme kako biste postigli željenu razinu vlažnosti tla.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | --------- | -------- | ----------------- |
| Prikupljanje podataka o vlažnosti tla | Uspijeva prikupiti više očitanja nakon dodavanja fiksnih količina vode | Uspijeva prikupiti neka očitanja s fiksnim količinama vode | Može prikupiti samo jedno ili dva očitanja, ili ne uspijeva koristiti fiksne količine vode |
| Kalibracija koda na serveru | Uspijeva izračunati prosječni pad očitanja vlažnosti tla i ažurirati kod na serveru koristeći te podatke | Uspijeva izračunati prosječni pad, ali ne može ažurirati kod na serveru, ili ne uspijeva ispravno izračunati prosjek, ali koristi tu vrijednost za ispravno ažuriranje koda na serveru | Ne uspijeva izračunati prosjek ili ažurirati kod na serveru |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.