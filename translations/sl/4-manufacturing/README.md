<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T12:03:50+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "sl"
}
-->
# Proizvodnja in predelava - uporaba IoT za izboljšanje predelave hrane

Ko hrana prispe v centralno skladišče ali predelovalni obrat, se ne pošlje vedno neposredno v supermarkete. Pogosto hrana preide skozi več predelovalnih korakov, kot je na primer razvrščanje po kakovosti. To je bil proces, ki je bil nekoč ročen - začel se je na polju, kjer so nabiralci pobirali le zrelo sadje, nato pa je v tovarni sadje potovalo po tekočem traku, kjer so zaposleni ročno odstranjevali poškodovano ali gnilo sadje. Ker sem sam med šolskimi počitnicami kot poletno delo nabiral in razvrščal jagode, lahko potrdim, da to ni zabavno delo.

Sodobnejše postavitve se za razvrščanje zanašajo na IoT. Nekatere najzgodnejše naprave, kot so sortirniki podjetja [Weco](https://wecotek.com), uporabljajo optične senzorje za zaznavanje kakovosti pridelkov, na primer zavračanje zelenih paradižnikov. Te naprave je mogoče uporabiti na kombajnih na samem polju ali v predelovalnih obratih.

Z napredkom umetne inteligence (AI) in strojnega učenja (ML) lahko te naprave postanejo še bolj napredne, saj uporabljajo ML modele, ki so usposobljeni za razlikovanje med sadjem in tujki, kot so kamni, zemlja ali insekti. Ti modeli se lahko usposobijo tudi za zaznavanje kakovosti sadja, ne le poškodovanega sadja, temveč tudi za zgodnje odkrivanje bolezni ali drugih težav s pridelki.

> 🎓 Izraz *ML model* se nanaša na rezultat usposabljanja programske opreme za strojno učenje na naboru podatkov. Na primer, lahko usposobite ML model za razlikovanje med zrelimi in nezrelimi paradižniki, nato pa uporabite model na novih slikah, da preverite, ali so paradižniki zreli ali ne.

V teh 4 lekcijah se boste naučili, kako usposobiti modele umetne inteligence na podlagi slik za zaznavanje kakovosti sadja, kako jih uporabiti na IoT napravi in kako jih zagnati na robu - torej na IoT napravi namesto v oblaku.

> 💁 Te lekcije bodo uporabljale nekatere oblačne vire. Če ne dokončate vseh lekcij v tem projektu, poskrbite, da [počistite svoj projekt](../clean-up.md).

## Teme

1. [Usposobite detektor kakovosti sadja](./lessons/1-train-fruit-detector/README.md)
1. [Preverite kakovost sadja z IoT napravo](./lessons/2-check-fruit-from-device/README.md)
1. [Zaženite svoj detektor sadja na robu](./lessons/3-run-fruit-detector-edge/README.md)
1. [Senzor sproži zaznavanje kakovosti sadja](./lessons/4-trigger-fruit-detector/README.md)

## Avtorji

Vse lekcije so bile napisane z ♥️ s strani [Jen Fox](https://github.com/jenfoxbot) in [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.