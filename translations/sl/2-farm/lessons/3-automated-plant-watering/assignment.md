<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T15:25:37+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "sl"
}
-->
# Ustvarite bolj učinkovit namakalni cikel

## Navodila

Ta lekcija je obravnavala, kako upravljati rele prek podatkov senzorja, pri čemer lahko ta rele upravlja črpalko za namakalni sistem. Za določeno količino zemlje bi moralo delovanje črpalke za določeno časovno obdobje vedno imeti enak vpliv na vlažnost zemlje. To pomeni, da lahko ocenite, koliko sekund namakanja ustreza določenemu padcu odčitka vlažnosti zemlje. Na podlagi teh podatkov lahko ustvarite bolj nadzorovan namakalni sistem.

Pri tej nalogi boste izračunali, kako dolgo naj črpalka deluje za določeno povečanje vlažnosti zemlje.

> ⚠️ Če uporabljate virtualno IoT strojno opremo, lahko sledite temu postopku, vendar simulirajte rezultate tako, da ročno povečate odčitek vlažnosti zemlje za določeno količino na sekundo, ko je rele vklopljen.

1. Začnite s suho zemljo. Izmerite vlažnost zemlje.

1. Dodajte določeno količino vode, bodisi tako, da črpalko zaženete za 1 sekundo ali pa vlijete določeno količino vode.

    > Črpalka naj vedno deluje s konstantno hitrostjo, tako da vsaka sekunda delovanja črpalke zagotovi enako količino vode.

1. Počakajte, da se raven vlažnosti zemlje stabilizira, in opravite odčitek.

1. Postopek večkrat ponovite in ustvarite tabelo rezultatov. Primer takšne tabele je podan spodaj.

    | Skupni čas črpalke | Vlažnost zemlje | Zmanjšanje |
    | --- | --: | -: |
    | Suho | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Izračunajte povprečno povečanje vlažnosti zemlje na sekundo dodane vode. V zgornjem primeru vsaka sekunda vode zmanjša odčitek za povprečno 20,3.

1. Uporabite te podatke za izboljšanje učinkovitosti strežniške kode, tako da črpalko zaženete za potrebno časovno obdobje, da dosežete želeno raven vlažnosti zemlje.

## Merila ocenjevanja

| Merila | Odlično | Zadostno | Potrebna izboljšava |
| -------- | --------- | -------- | ----------------- |
| Zajem podatkov o vlažnosti zemlje | Uspe zajeti več odčitkov po dodajanju določenih količin vode | Uspe zajeti nekaj odčitkov z določenimi količinami vode | Uspe zajeti le enega ali dva odčitka ali ne zna uporabiti določenih količin vode |
| Kalibracija strežniške kode | Uspe izračunati povprečno zmanjšanje odčitka vlažnosti zemlje in posodobiti strežniško kodo za uporabo tega podatka | Uspe izračunati povprečno zmanjšanje, vendar ne zna posodobiti strežniške kode, ali ne zna pravilno izračunati povprečja, vendar uporabi to vrednost za pravilno posodobitev strežniške kode | Ne zna izračunati povprečja ali posodobiti strežniške kode |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da se zavedate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.