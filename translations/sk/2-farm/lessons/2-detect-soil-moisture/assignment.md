<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-28T11:03:55+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "sk"
}
-->
# Kalibrujte svoj senzor

## Pokyny

V tejto lekcii ste získali údaje zo senzora vlhkosti pôdy, merané ako hodnoty od 0 do 1023. Aby ste tieto hodnoty premenili na skutočné údaje o vlhkosti pôdy, musíte senzor kalibrovať. To môžete urobiť tak, že odoberiete vzorky pôdy, potom vypočítate gravimetrický obsah vlhkosti pôdy z týchto vzoriek.

Tieto kroky budete musieť zopakovať viackrát, aby ste získali potrebné údaje, pričom zakaždým použijete pôdu s rôznou vlhkosťou.

1. Zmerajte vlhkosť pôdy pomocou senzora vlhkosti pôdy. Zapíšte si túto hodnotu.

1. Odoberte vzorku pôdy a odvážte ju. Zapíšte si túto hmotnosť.

1. Pôdu vysušte – najlepším spôsobom je teplá rúra na 110 °C (230 °F) na niekoľko hodín. Môžete to urobiť aj na slnku alebo ju umiestniť na teplé, suché miesto, kým nebude úplne suchá. Mala by byť práškovitá a sypká.

    > 💁 V laboratóriu, pre najpresnejšie výsledky, by ste ju sušili v rúre 48-72 hodín. Ak máte v škole sušiace rúry, zistite, či ich môžete použiť na dlhšie sušenie. Čím dlhšie, tým suchšia vzorka a tým presnejšie výsledky.

1. Znovu odvážte pôdu.

    > 🔥 Ak ste ju sušili v rúre, uistite sa, že najprv vychladla!

Gravimetrická vlhkosť pôdy sa vypočíta ako:

![vlhkosť pôdy % je hmotnosť mokrej pôdy mínus hmotnosť suchej pôdy, delené hmotnosťou suchej pôdy, krát 100](../../../../../translated_images/sk/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - hmotnosť mokrej pôdy
* W - hmotnosť suchej pôdy

Napríklad, povedzme, že máte vzorku pôdy, ktorá váži 212 g mokrá a 197 g suchá.

![Vyplnený výpočet](../../../../../translated_images/sk/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212 g
* W = 197 g
* 212 - 197 = 15
* 15 / 197 = 0,076
* 0,076 * 100 = 7,6 %

V tomto príklade má pôda gravimetrickú vlhkosť 7,6 %.

Keď budete mať údaje aspoň z 3 vzoriek, vykreslite graf percentuálnej vlhkosti pôdy voči údajom zo senzora vlhkosti pôdy a pridajte čiaru, ktorá najlepšie vystihuje body. Potom môžete tento graf použiť na výpočet gravimetrického obsahu vlhkosti pôdy pre daný údaj zo senzora tak, že hodnotu odčítate z čiary.

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Zber kalibračných údajov | Získajte aspoň 3 kalibračné vzorky | Získajte aspoň 2 kalibračné vzorky | Získajte aspoň 1 kalibračnú vzorku |
| Vykonanie kalibrovaného merania | Úspešne vykreslite kalibračný graf, vykonajte meranie zo senzora a prepočítajte ho na gravimetrický obsah vlhkosti pôdy | Úspešne vykreslite kalibračný graf | Nie je možné vykresliť graf |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za záväzný zdroj. Pre dôležité informácie odporúčame profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.