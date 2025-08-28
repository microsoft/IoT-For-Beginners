<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-28T14:33:55+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "sl"
}
-->
# Merjenje vlažnosti tal - Raspberry Pi

V tem delu lekcije boste dodali kapacitivni senzor vlažnosti tal na Raspberry Pi in prebrali vrednosti iz njega.

## Strojna oprema

Raspberry Pi potrebuje kapacitivni senzor vlažnosti tal.

Senzor, ki ga boste uporabili, je [Kapacitivni senzor vlažnosti tal](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ki meri vlažnost tal z zaznavanjem kapacitivnosti tal, lastnosti, ki se spreminja glede na vlažnost tal. Ko se vlažnost tal poveča, se napetost zmanjša.

To je analogni senzor, ki uporablja analogni pin in 10-bitni ADC v Grove Base Hat na Pi-ju za pretvorbo napetosti v digitalni signal od 1 do 1.023. Ta signal se nato pošilja prek I

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.