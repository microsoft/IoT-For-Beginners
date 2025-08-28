<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-28T12:31:07+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "sl"
}
-->
# Odziv na rezultate klasifikacije

## Navodila

Vaša naprava je klasificirala slike in ima vrednosti za napovedi. Naprava lahko te informacije uporabi za določene akcije - lahko jih pošlje v IoT Hub za obdelavo v drugih sistemih ali pa upravlja aktuator, kot je LED lučka, ki se prižge, ko je sadje nezrelo.

Dodajte kodo na svojo napravo, da se odzove na način po vaši izbiri - bodisi pošljite podatke v IoT Hub, upravljajte aktuator ali pa združite oboje in pošljite podatke v IoT Hub z nekaj strežniške kode, ki določi, ali je sadje zrelo ali ne, ter pošlje nazaj ukaz za upravljanje aktuatorja.

## Merila

| Merilo | Odlično | Zadostno | Potrebna izboljšava |
| ------ | -------- | -------- | ------------------- |
| Odziv na napovedi | Uspešno implementiran odziv na napovedi, ki dosledno deluje z enakimi vrednostmi napovedi. | Uspešno implementiran odziv, ki ni odvisen od napovedi, na primer samo pošiljanje surovih podatkov v IoT Hub. | Naprave ni bilo mogoče programirati za odziv na napovedi. |

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve AI za prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.