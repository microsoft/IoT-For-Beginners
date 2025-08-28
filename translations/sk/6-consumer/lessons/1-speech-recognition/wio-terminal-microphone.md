<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T09:14:07+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "sk"
}
-->
# Nastavte mikrofón a reproduktory - Wio Terminal

V tejto časti lekcie pridáte reproduktory k vášmu Wio Terminal. Wio Terminal už má zabudovaný mikrofón, ktorý môžete použiť na zachytávanie reči.

## Hardvér

Wio Terminal už má zabudovaný mikrofón, ktorý môžete použiť na zachytávanie zvuku pre rozpoznávanie reči.

![Mikrofón na Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.sk.png)

Na pridanie reproduktora môžete použiť [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Ide o externú dosku, ktorá obsahuje 2 MEMS mikrofóny, konektor na reproduktor a konektor na slúchadlá.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.sk.png)

Budete potrebovať pripojiť buď slúchadlá, reproduktor s 3,5mm jackom, alebo reproduktor s JST konektorom, ako napríklad [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Na pripojenie ReSpeaker 2-Mics Pi Hat budete potrebovať 40 pin-to-pin (tiež označované ako samec-samec) prepojovacie káble.

> 💁 Ak ste zruční v spájkovaní, môžete použiť [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) na pripojenie ReSpeaker.

Budete tiež potrebovať SD kartu na sťahovanie a prehrávanie zvuku. Wio Terminal podporuje SD karty do veľkosti 16GB, ktoré musia byť naformátované ako FAT32 alebo exFAT.

### Úloha - pripojenie ReSpeaker Pi Hat

1. Pri vypnutom Wio Terminal pripojte ReSpeaker 2-Mics Pi Hat k Wio Terminal pomocou prepojovacích káblov a GPIO konektorov na zadnej strane Wio Terminal:

    Piny musia byť pripojené týmto spôsobom:

    ![Schéma pinov](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.sk.png)

1. Umiestnite ReSpeaker a Wio Terminal tak, aby GPIO konektory smerovali nahor a boli na ľavej strane.

1. Začnite od konektora v ľavom hornom rohu GPIO konektora na ReSpeaker. Pripojte prepojovací kábel z ľavého horného konektora ReSpeaker do ľavého horného konektora Wio Terminal.

1. Pokračujte týmto spôsobom po celej ľavej strane GPIO konektorov. Uistite sa, že piny sú pevne zasunuté.

    ![ReSpeaker s ľavými pinmi pripojenými k ľavým pinom Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.sk.png)

    ![ReSpeaker s ľavými pinmi pripojenými k ľavým pinom Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.sk.png)

    > 💁 Ak sú vaše prepojovacie káble spojené do pásov, nechajte ich spolu - uľahčí to zabezpečenie správneho pripojenia všetkých káblov.

1. Opakujte proces pomocou pravých GPIO konektorov na ReSpeaker a Wio Terminal. Tieto káble musia obísť už pripojené káble.

    ![ReSpeaker s pravými pinmi pripojenými k pravým pinom Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.sk.png)

    ![ReSpeaker s pravými pinmi pripojenými k pravým pinom Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.sk.png)

    > 💁 Ak sú vaše prepojovacie káble spojené do pásov, rozdeľte ich na dva pásy. Jeden preveďte na každú stranu existujúcich káblov.

    > 💁 Na upevnenie pinov do bloku môžete použiť lepiacu pásku, aby ste zabránili ich vypadnutiu počas pripojenia.
    >
    > ![Piny upevnené páskou](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.sk.png)

1. Budete musieť pridať reproduktor.

    * Ak používate reproduktor s JST káblom, pripojte ho k JST portu na ReSpeaker.

      ![Reproduktor pripojený k ReSpeaker pomocou JST kábla](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.sk.png)

    * Ak používate reproduktor s 3,5mm jackom alebo slúchadlá, vložte ich do konektora 3,5mm jack.

      ![Reproduktor pripojený k ReSpeaker cez konektor 3,5mm jack](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.sk.png)

### Úloha - nastavenie SD karty

1. Pripojte SD kartu k vášmu počítaču, pomocou externého čítača, ak nemáte slot na SD kartu.

1. Naformátujte SD kartu pomocou vhodného nástroja na vašom počítači, pričom sa uistite, že používate súborový systém FAT32 alebo exFAT.

1. Vložte SD kartu do slotu na SD kartu na ľavej strane Wio Terminal, tesne pod tlačidlom napájania. Uistite sa, že karta je úplne zasunutá a zacvakne - možno budete potrebovať tenký nástroj alebo inú SD kartu na jej úplné zasunutie.

    ![Vkladanie SD karty do slotu na SD kartu pod vypínačom](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.sk.png)

    > 💁 Na vysunutie SD karty ju musíte mierne zatlačiť, aby sa vysunula. Budete potrebovať tenký nástroj, ako je plochý skrutkovač alebo inú SD kartu.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.