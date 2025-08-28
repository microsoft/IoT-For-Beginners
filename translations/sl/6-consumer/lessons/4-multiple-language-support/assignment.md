<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T13:10:33+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "sl"
}
-->
# Zgradite univerzalni prevajalnik

## Navodila

Univerzalni prevajalnik je naprava, ki lahko prevaja med več jeziki, kar omogoča ljudem, ki govorijo različne jezike, da komunicirajo. Uporabite znanje, pridobljeno v preteklih lekcijah, za izdelavo univerzalnega prevajalnika z uporabo dveh IoT naprav.

> Če nimate dveh naprav, sledite korakom iz prejšnjih lekcij, da nastavite virtualno IoT napravo kot eno od IoT naprav.

Nastavite eno napravo za en jezik in drugo za drug jezik. Vsaka naprava naj sprejme govor, ga pretvori v besedilo, pošlje drugi napravi prek IoT Hub in Functions aplikacije, nato pa ga prevede in predvaja prevedeni govor.

> 💁 Nasvet: Ko pošiljate govor z ene naprave na drugo, pošljite tudi jezik, v katerem je govor, da bo prevajanje lažje. Lahko celo omogočite, da se vsaka naprava najprej registrira prek IoT Hub in Functions aplikacije, pri čemer posreduje jezik, ki ga podpira, za shranjevanje v Azure Storage. Nato lahko uporabite Functions aplikacijo za prevajanje in pošiljanje prevedenega besedila na IoT napravo.

## Merila

| Merilo | Odlično | Zadostno | Potrebna izboljšava |
| ------- | -------- | -------- | ------------------- |
| Ustvarite univerzalni prevajalnik | Uspešno zgrajen univerzalni prevajalnik, ki pretvori govor, zaznan z eno napravo, v govor, predvajan na drugi napravi v drugem jeziku | Uspešno delovanje nekaterih komponent, kot je zajem govora ali prevajanje, vendar ni uspelo zgraditi celotne rešitve od začetka do konca | Ni uspelo zgraditi nobenega dela delujočega univerzalnega prevajalnika |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.