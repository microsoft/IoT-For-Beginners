<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T21:22:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "cs"
}
-->
# Nastavení mikrofonu a reproduktorů - Wio Terminal

V této části lekce přidáte reproduktory k vašemu Wio Terminalu. Wio Terminal již má vestavěný mikrofon, který lze použít k zachycení řeči.

## Hardware

Wio Terminal má již vestavěný mikrofon, který lze použít k zachycení zvuku pro rozpoznávání řeči.

![Mikrofon na Wio Terminalu](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.cs.png)

Pro přidání reproduktoru můžete použít [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Jedná se o externí desku, která obsahuje 2 MEMS mikrofony, konektor pro reproduktor a sluchátkový výstup.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.cs.png)

Budete potřebovat připojit buď sluchátka, reproduktor s 3,5mm jackem, nebo reproduktor s JST konektorem, například [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Pro připojení ReSpeaker 2-Mics Pi Hat budete potřebovat 40 pin-to-pin (také označované jako samec-samec) propojovací kabely.

> 💁 Pokud umíte pájet, můžete použít [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) pro připojení ReSpeakeru.

Budete také potřebovat SD kartu pro stahování a přehrávání zvuku. Wio Terminal podporuje pouze SD karty do velikosti 16 GB, které musí být naformátovány jako FAT32 nebo exFAT.

### Úkol - připojení ReSpeaker Pi Hat

1. S vypnutým Wio Terminalem připojte ReSpeaker 2-Mics Pi Hat k Wio Terminalu pomocí propojovacích kabelů a GPIO konektorů na zadní straně Wio Terminalu:

    Piny musí být připojeny tímto způsobem:

    ![Schéma zapojení pinů](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.cs.png)

1. Umístěte ReSpeaker a Wio Terminal tak, aby GPIO konektory směřovaly nahoru a byly na levé straně.

1. Začněte od konektoru v levém horním rohu GPIO konektoru na ReSpeakeru. Připojte propojovací kabel z levého horního konektoru ReSpeakeru do levého horního konektoru Wio Terminalu.

1. Opakujte tento postup po celé délce GPIO konektorů na levé straně. Ujistěte se, že jsou piny pevně zasunuty.

    ![ReSpeaker s připojenými levými piny k levým pinům Wio Terminalu](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.cs.png)

    ![ReSpeaker s připojenými levými piny k levým pinům Wio Terminalu](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.cs.png)

    > 💁 Pokud jsou vaše propojovací kabely spojeny do pásků, nechte je pohromadě – usnadní to zajištění správného pořadí připojení všech kabelů.

1. Opakujte proces s pravými GPIO konektory na ReSpeakeru a Wio Terminalu. Tyto kabely musí obcházet již připojené kabely.

    ![ReSpeaker s připojenými pravými piny k pravým pinům Wio Terminalu](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.cs.png)

    ![ReSpeaker s připojenými pravými piny k pravým pinům Wio Terminalu](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.cs.png)

    > 💁 Pokud jsou vaše propojovací kabely spojeny do pásků, rozdělte je na dva pásky. Jeden veďte na každé straně již připojených kabelů.

    > 💁 Můžete použít lepicí pásku k upevnění pinů do bloku, aby se zabránilo jejich uvolnění během připojování.
    >
    > ![Piny upevněné páskou](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.cs.png)

1. Budete muset připojit reproduktor.

    * Pokud používáte reproduktor s JST kabelem, připojte jej k JST portu na ReSpeakeru.

      ![Reproduktor připojený k ReSpeakeru pomocí JST kabelu](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.cs.png)

    * Pokud používáte reproduktor s 3,5mm jackem nebo sluchátka, zasuňte je do 3,5mm jack konektoru.

      ![Reproduktor připojený k ReSpeakeru přes 3,5mm jack konektor](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.cs.png)

### Úkol - nastavení SD karty

1. Připojte SD kartu k počítači, použijte externí čtečku, pokud nemáte slot na SD kartu.

1. Naformátujte SD kartu pomocí vhodného nástroje na vašem počítači, ujistěte se, že používáte souborový systém FAT32 nebo exFAT.

1. Vložte SD kartu do slotu na SD kartu na levé straně Wio Terminalu, těsně pod tlačítkem napájení. Ujistěte se, že karta je zcela zasunuta a zacvakne – možná budete potřebovat tenký nástroj nebo jinou SD kartu, abyste ji zcela zasunuli.

    ![Vkládání SD karty do slotu pod vypínačem](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.cs.png)

    > 💁 Pro vysunutí SD karty ji musíte mírně zatlačit, aby se vysunula. Budete potřebovat tenký nástroj, například plochý šroubovák nebo jinou SD kartu.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.