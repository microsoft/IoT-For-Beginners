<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T13:10:23+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "hr"
}
-->
# Izgradite univerzalni prevoditelj

## Upute

Univerzalni prevoditelj je uređaj koji može prevoditi između više jezika, omogućujući ljudima koji govore različite jezike da međusobno komuniciraju. Iskoristite ono što ste naučili tijekom prethodnih lekcija kako biste izgradili univerzalni prevoditelj koristeći 2 IoT uređaja.

> Ako nemate 2 uređaja, slijedite korake iz prethodnih lekcija kako biste postavili virtualni IoT uređaj kao jedan od IoT uređaja.

Trebali biste konfigurirati jedan uređaj za jedan jezik, a drugi za drugi. Svaki uređaj treba prihvatiti govor, pretvoriti ga u tekst, poslati ga drugom uređaju putem IoT Hub-a i Functions aplikacije, zatim ga prevesti i reproducirati prevedeni govor.

> 💁 Savjet: Kada šaljete govor s jednog uređaja na drugi, pošaljite i jezik na kojem je govor, što olakšava prijevod. Možete čak omogućiti svakom uređaju da se registrira putem IoT Hub-a i Functions aplikacije, prvo prosljeđujući jezik koji podržavaju kako bi se pohranio u Azure Storage. Zatim možete koristiti Functions aplikaciju za prijevode, šaljući prevedeni tekst IoT uređaju.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | --------- | --------------- | -------------------- |
| Izraditi univerzalni prevoditelj | Uspješno izgrađen univerzalni prevoditelj, pretvarajući govor detektiran od strane jednog uređaja u govor reproduciran na drugom uređaju na drugom jeziku | Uspješno postavljeni neki dijelovi, poput snimanja govora ili prevođenja, ali nije izgrađeno cjelovito rješenje | Nije uspješno izgrađen nijedan dio funkcionalnog univerzalnog prevoditelja |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.