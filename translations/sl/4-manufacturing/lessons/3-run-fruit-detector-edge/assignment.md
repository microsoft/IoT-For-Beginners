<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-28T12:21:57+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "sl"
}
-->
# Zagon drugih storitev na robu

## Navodila

Na robu ni mogoče izvajati le klasifikatorjev slik, temveč lahko vse, kar je mogoče zapakirati v kontejner, namestite na napravo IoT Edge. Strežniška koda, ki se izvaja kot Azure Functions, kot so sprožilci, ki ste jih ustvarili v prejšnjih lekcijah, se lahko izvaja v kontejnerjih in posledično na IoT Edge.

Izberite eno od prejšnjih lekcij in poskusite zagnati aplikacijo Azure Functions v kontejnerju IoT Edge. Vodnik, ki prikazuje, kako to storiti z drugim projektom aplikacije Functions, najdete v [Vadnici: Namestitev Azure Functions kot modulov IoT Edge na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Merila ocenjevanja

| Merilo | Odlično | Zadostno | Potrebne izboljšave |
| ------- | -------- | -------- | ------------------- |
| Namestitev aplikacije Azure Functions na IoT Edge | Uspelo je namestiti aplikacijo Azure Functions na IoT Edge in jo uporabiti z napravo IoT za zagon sprožilca iz podatkov IoT | Uspelo je namestiti aplikacijo Functions na IoT Edge, vendar sprožilec ni deloval | Ni uspelo namestiti aplikacije Functions na IoT Edge |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.