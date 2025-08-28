<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-28T14:56:47+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "sl"
}
-->
# Izdelava nove naprave IoT

## Navodila

V zadnjih šestih lekcijah ste se naučili o digitalnem kmetijstvu in kako uporabljati naprave IoT za zbiranje podatkov za napovedovanje rasti rastlin ter avtomatizacijo zalivanja na podlagi odčitkov vlažnosti tal.

Uporabite pridobljeno znanje za izdelavo nove naprave IoT z uporabo senzorja in aktuatorja po vaši izbiri. Pošiljajte telemetrijo v IoT Hub in jo uporabite za nadzor aktuatorja prek strežniške kode. Uporabite senzor in aktuator, ki ste ju že uporabili v tem ali prejšnjem projektu, ali pa, če imate drugo strojno opremo, preizkusite nekaj novega.

## Merila ocenjevanja

| Merilo | Odlično | Zadostno | Potrebna izboljšava |
| ------- | -------- | -------- | ------------------- |
| Programiranje naprave IoT za uporabo senzorja in aktuatorja | Naprava IoT je bila programirana za delovanje s senzorjem in aktuatorjem | Naprava IoT je bila programirana za delovanje s senzorjem ali aktuatorjem | Naprave IoT ni bilo mogoče programirati za uporabo senzorja ali aktuatorja |
| Povezava naprave IoT z IoT Hub | Uspelo je vzpostaviti IoT Hub, pošiljati telemetrijo vanj in prejemati ukaze iz njega | Uspelo je vzpostaviti IoT Hub ter pošiljati telemetrijo ali prejemati ukaze | Ni uspelo vzpostaviti IoT Hub in komunicirati z njim prek naprave IoT |
| Nadzor aktuatorja z uporabo strežniške kode | Uspelo je vzpostaviti Azure Function za nadzor naprave, sprožene z dogodki telemetrije | Uspelo je vzpostaviti Azure Function, sproženo z dogodki telemetrije, vendar ni uspelo nadzorovati aktuatorja | Ni uspelo vzpostaviti Azure Function |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.