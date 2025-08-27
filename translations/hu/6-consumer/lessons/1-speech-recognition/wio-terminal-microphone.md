<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T21:22:05+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "hu"
}
-->
# Mikrofon és hangszórók konfigurálása - Wio Terminal

Ebben a leckében hozzáadod a hangszórókat a Wio Terminalhoz. A Wio Terminal már rendelkezik beépített mikrofonnal, amelyet beszéd rögzítésére használhatsz.

## Hardver

A Wio Terminal már rendelkezik beépített mikrofonnal, amelyet hangfelvételhez és beszédfelismeréshez használhatsz.

![A Wio Terminal mikrofonja](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.hu.png)

Hangszóró hozzáadásához használhatod a [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) eszközt. Ez egy külső panel, amely 2 MEMS mikrofont, hangszóró csatlakozót és fejhallgató aljzatot tartalmaz.

![A ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.hu.png)

Szükséged lesz fejhallgatóra, 3.5mm jack csatlakozós hangszóróra, vagy JST csatlakozós hangszóróra, például a [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html) típusra.

A ReSpeaker 2-Mics Pi Hat csatlakoztatásához 40 pin-to-pin (férfi-férfi) jumper kábelekre lesz szükséged.

> 💁 Ha jártas vagy a forrasztásban, használhatod a [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) adaptert a ReSpeaker csatlakoztatásához.

Ezen kívül szükséged lesz egy SD kártyára, amelyet hangfelvétel letöltésére és lejátszására használhatsz. A Wio Terminal csak 16GB méretig támogatja az SD kártyákat, és ezeknek FAT32 vagy exFAT formátumúaknak kell lenniük.

### Feladat - csatlakoztasd a ReSpeaker Pi Hat-et

1. Kapcsold ki a Wio Terminalt, majd csatlakoztasd a ReSpeaker 2-Mics Pi Hat-et a Wio Terminalhoz a jumper kábelek és a GPIO csatlakozók segítségével, amelyek a Wio Terminal hátoldalán találhatók:

    A csatlakozókat így kell összekötni:

    ![Pin diagram](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.hu.png)

1. Helyezd el a ReSpeakert és a Wio Terminalt úgy, hogy a GPIO csatlakozók felfelé nézzenek, és bal oldalon legyenek.

1. Kezdd a ReSpeaker GPIO csatlakozójának bal felső sarkában lévő aljzattal. Csatlakoztass egy pin-to-pin jumper kábelt a ReSpeaker bal felső aljzatából a Wio Terminal bal felső aljzatába.

1. Ismételd meg ezt az egész bal oldali GPIO csatlakozónál. Ügyelj arra, hogy a csatlakozók szorosan illeszkedjenek.

    ![A ReSpeaker bal oldali csatlakozói összekötve a Wio Terminal bal oldali csatlakozóival](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.hu.png)

    ![A ReSpeaker bal oldali csatlakozói összekötve a Wio Terminal bal oldali csatlakozóival](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.hu.png)

    > 💁 Ha a jumper kábelek szalagban vannak összekötve, tartsd őket együtt - így könnyebb biztosítani, hogy minden kábelt sorrendben csatlakoztattál.

1. Ismételd meg a folyamatot a ReSpeaker és a Wio Terminal jobb oldali GPIO csatlakozóival. Ezeket a kábeleket az előzőleg csatlakoztatott kábelek körül kell vezetni.

    ![A ReSpeaker jobb oldali csatlakozói összekötve a Wio Terminal jobb oldali csatlakozóival](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.hu.png)

    ![A ReSpeaker jobb oldali csatlakozói összekötve a Wio Terminal jobb oldali csatlakozóival](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.hu.png)

    > 💁 Ha a jumper kábelek szalagban vannak összekötve, oszd őket két szalagra. Vezesd őket az előző kábelek két oldalán.

    > 💁 Használhatsz ragasztószalagot, hogy a csatlakozókat egy blokkban rögzítsd, így megakadályozhatod, hogy a csatlakozók kicsússzanak, miközben mindet csatlakoztatod.
    >
    > ![A csatlakozók rögzítése szalaggal](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.hu.png)

1. Csatlakoztatnod kell egy hangszórót.

    * Ha JST kábellel rendelkező hangszórót használsz, csatlakoztasd a JST porthoz a ReSpeakeren.

      ![JST kábellel csatlakoztatott hangszóró a ReSpeakerhez](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.hu.png)

    * Ha 3.5mm jack csatlakozós hangszórót vagy fejhallgatót használsz, dugd be a 3.5mm jack aljzatba.

      ![3.5mm jack csatlakozón keresztül csatlakoztatott hangszóró a ReSpeakerhez](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.hu.png)

### Feladat - az SD kártya előkészítése

1. Csatlakoztasd az SD kártyát a számítógépedhez, külső olvasót használva, ha nincs SD kártyahelyed.

1. Formázd az SD kártyát a számítógéped megfelelő eszközével, ügyelve arra, hogy FAT32 vagy exFAT fájlrendszert használj.

1. Helyezd be az SD kártyát a Wio Terminal bal oldalán, a bekapcsoló gomb alatt található SD kártyahelyre. Győződj meg róla, hogy a kártya teljesen be van helyezve és kattan - ehhez szükséged lehet egy vékony eszközre vagy egy másik SD kártyára, hogy teljesen benyomd.

    ![Az SD kártya behelyezése az SD kártyahelyre a bekapcsoló gomb alatt](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.hu.png)

    > 💁 Az SD kártya eltávolításához enyhén nyomd be, és ki fog ugrani. Ehhez vékony eszközre lesz szükséged, például egy lapos fejű csavarhúzóra vagy egy másik SD kártyára.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.