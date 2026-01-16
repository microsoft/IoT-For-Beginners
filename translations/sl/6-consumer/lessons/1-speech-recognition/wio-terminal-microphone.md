<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T12:56:03+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "sl"
}
-->
# Konfigurirajte mikrofon in zvočnike - Wio Terminal

V tem delu lekcije boste dodali zvočnike na vaš Wio Terminal. Wio Terminal že ima vgrajen mikrofon, ki ga lahko uporabite za zajem govora.

## Strojna oprema

Wio Terminal že ima vgrajen mikrofon, ki ga lahko uporabite za zajem zvoka za prepoznavanje govora.

![Mikrofon na Wio Terminalu](../../../../../translated_images/sl/wio-mic.3f8c843dbe8ad917.png)

Za dodajanje zvočnika lahko uporabite [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). To je zunanja plošča, ki vsebuje 2 MEMS mikrofona, priključek za zvočnik in vtičnico za slušalke.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/sl/respeaker.f5d19d1c6b14ab16.png)

Potrebovali boste slušalke, zvočnik s priključkom 3,5 mm ali zvočnik z JST priključkom, kot je [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Za povezavo ReSpeaker 2-Mics Pi Hat boste potrebovali 40 pin-to-pin (imenovane tudi moški-moški) povezovalne kable.

> 💁 Če ste vešči spajkanja, lahko uporabite [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) za povezavo ReSpeaker.

Prav tako boste potrebovali SD kartico za prenos in predvajanje zvoka. Wio Terminal podpira SD kartice do velikosti 16 GB, ki morajo biti formatirane kot FAT32 ali exFAT.

### Naloga - povežite ReSpeaker Pi Hat

1. Ko je Wio Terminal izklopljen, povežite ReSpeaker 2-Mics Pi Hat z Wio Terminalom z uporabo povezovalnih kablov in GPIO vtičnic na zadnji strani Wio Terminala:

    Povezave pinov morajo biti izvedene na naslednji način:

    ![Diagram pinov](../../../../../translated_images/sl/wio-respeaker-wiring-0.767f80aa65081038.png)

1. Postavite ReSpeaker in Wio Terminal tako, da so GPIO vtičnice obrnjene navzgor in na levi strani.

1. Začnite z vtičnico na zgornji levi strani GPIO vtičnice na ReSpeaker. Povežite pin-to-pin kabel iz zgornje leve vtičnice na ReSpeaker v zgornjo levo vtičnico na Wio Terminalu.

1. Postopek ponovite po celotni levi strani GPIO vtičnic. Prepričajte se, da so pini trdno povezani.

    ![ReSpeaker z levo stranjo pinov povezanih z levo stranjo pinov na Wio Terminalu](../../../../../translated_images/sl/wio-respeaker-wiring-1.8d894727f2ba2400.png)

    ![ReSpeaker z levo stranjo pinov povezanih z levo stranjo pinov na Wio Terminalu](../../../../../translated_images/sl/wio-respeaker-wiring-2.329e1cbd306e754f.png)

    > 💁 Če so vaši povezovalni kabli združeni v trakove, jih pustite skupaj - to olajša preverjanje, da so vsi kabli povezani v pravilnem vrstnem redu.

1. Postopek ponovite z desno stranjo GPIO vtičnic na ReSpeaker in Wio Terminalu. Ti kabli morajo iti okoli že povezanih kablov.

    ![ReSpeaker z desno stranjo pinov povezanih z desno stranjo pinov na Wio Terminalu](../../../../../translated_images/sl/wio-respeaker-wiring-3.75b0be447e2fa930.png)

    ![ReSpeaker z desno stranjo pinov povezanih z desno stranjo pinov na Wio Terminalu](../../../../../translated_images/sl/wio-respeaker-wiring-4.aa9cd434d8779437.png)

    > 💁 Če so vaši povezovalni kabli združeni v trakove, jih razdelite na dva trakova. En trak naj gre na vsako stran obstoječih kablov.

    > 💁 Uporabite lepilni trak, da pritrdite pine v blok, kar pomaga preprečiti, da bi se kateri od njih iztaknil med povezovanjem.
    >
    > ![Pini pritrjeni z lepilnim trakom](../../../../../translated_images/sl/wio-respeaker-wiring-5.af117c20acf622f3.png)

1. Dodati boste morali zvočnik.

    * Če uporabljate zvočnik z JST kablom, ga povežite z JST priključkom na ReSpeaker.

      ![Zvočnik povezan z ReSpeaker z JST kablom](../../../../../translated_images/sl/respeaker-jst-speaker.a441d177809df945.png)

    * Če uporabljate zvočnik s priključkom 3,5 mm ali slušalke, jih vstavite v vtičnico 3,5 mm.

      ![Zvočnik povezan z ReSpeaker preko vtičnice 3,5 mm](../../../../../translated_images/sl/respeaker-35mm-speaker.ad79ef4f128c7751.png)

### Naloga - nastavite SD kartico

1. Povežite SD kartico z računalnikom, pri čemer uporabite zunanji bralnik, če vaš računalnik nima reže za SD kartice.

1. Formatirajte SD kartico z ustreznim orodjem na vašem računalniku, pri čemer poskrbite, da uporabite datotečni sistem FAT32 ali exFAT.

1. Vstavite SD kartico v režo za SD kartico na levi strani Wio Terminala, tik pod gumbom za vklop. Prepričajte se, da je kartica popolnoma vstavljena in klikne - morda boste potrebovali tanek pripomoček ali drugo SD kartico, da jo potisnete povsem noter.

    ![Vstavljanje SD kartice v režo za SD kartico pod gumbom za vklop](../../../../../translated_images/sl/wio-sd-card.acdcbe322fa4ee7f.png)

    > 💁 Za izmet SD kartice jo rahlo potisnite noter, da se iztisne. Za to boste potrebovali tanek pripomoček, kot je izvijač z ravno glavo ali druga SD kartica.

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.