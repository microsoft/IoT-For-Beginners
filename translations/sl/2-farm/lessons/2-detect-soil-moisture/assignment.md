<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-28T14:42:18+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "sl"
}
-->
# Umerite svoj senzor

## Navodila

V tej lekciji ste zbrali odčitke senzorja za merjenje vlažnosti tal, izražene kot vrednosti od 0 do 1023. Da bi te vrednosti pretvorili v dejanske odčitke vlažnosti tal, morate senzor umeriti. To lahko storite tako, da vzamete odčitke iz vzorcev tal in nato izračunate gravimetrično vsebnost vlage v teh vzorcih.

Te korake boste morali večkrat ponoviti, da pridobite potrebne odčitke, pri čemer naj bodo tla vsakič različno vlažna.

1. Z merilnikom vlažnosti tal izmerite vlažnost tal. Zapišite ta odčitek.

1. Vzemite vzorec tal in ga stehtajte. Zapišite to težo.

1. Posušite tla – najboljši način je v topli pečici pri 110 °C (230 °F) za nekaj ur. To lahko storite tudi na soncu ali pa jih postavite na toplo in suho mesto, dokler tla niso popolnoma suha. Tla morajo biti praškasta in rahla.

    > 💁 V laboratoriju bi za najbolj natančne rezultate tla sušili v pečici 48–72 ur. Če imate v šoli sušilne pečice, preverite, ali jih lahko uporabite za daljše sušenje. Daljše sušenje pomeni bolj suhe vzorce in natančnejše rezultate.

1. Tla ponovno stehtajte.

    > 🔥 Če ste jih sušili v pečici, se prepričajte, da so se najprej ohladila!

Gravimetrična vlažnost tal se izračuna kot:

![vlažnost tal % je teža mokrih tal minus teža suhih tal, deljeno s težo suhih tal, pomnoženo s 100](../../../../../translated_images/sl/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - teža mokrih tal  
* W - teža suhih tal  

Na primer, recimo, da imate vzorec tal, ki tehta 212 g mokro in 197 g suho.

![Izpolnjen izračun](../../../../../translated_images/sl/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212 g  
* W = 197 g  
* 212 - 197 = 15  
* 15 / 197 = 0,076  
* 0,076 * 100 = 7,6 %

V tem primeru imajo tla gravimetrično vlažnost 7,6 %.

Ko imate odčitke za vsaj 3 vzorce, narišite graf vlažnosti tal % glede na odčitke senzorja za vlažnost tal in dodajte premico, ki najbolje ustreza točkam. Nato lahko to uporabite za izračun gravimetrične vlažnosti tal za določen odčitek senzorja, tako da vrednost preberete s premice.

## Rubrika

| Merila | Odlično | Zadostno | Potrebna izboljšava |
| ------ | ------- | -------- | ------------------- |
| Zbiranje podatkov za umerjanje | Zajeti vsaj 3 vzorce za umerjanje | Zajeti vsaj 2 vzorca za umerjanje | Zajeti vsaj 1 vzorec za umerjanje |
| Izvedba umerjenega odčitka | Uspešno narisan graf za umerjanje in izveden odčitek s senzorja, pretvorjen v gravimetrično vlažnost tal | Uspešno narisan graf za umerjanje | Graf ni narisan |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.