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

![A Wio Terminal mikrofonja](../../../../../translated_images/hu/wio-mic.3f8c843dbe8ad917.webp)

Hangszóró hozzáadásához használhatod a [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) eszközt. Ez egy külső panel, amely 2 MEMS mikrofont, hangszóró csatlakozót és fejhallgató aljzatot tartalmaz.

![A ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/hu/respeaker.f5d19d1c6b14ab16.webp)

Szükséged lesz fejhallgatóra, 3.5mm jack csatlakozós hangszóróra, vagy JST csatlakozós hangszóróra, például a [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html) típusra.

A ReSpeaker 2-Mics Pi Hat csatlakoztatásához 40 pin-to-pin (férfi-férfi) jumper kábelekre lesz szükséged.

> 💁 Ha jártas vagy a forrasztásban, használhatod a [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) adaptert a ReSpeaker csatlakoztatásához.

Ezen kívül szükséged lesz egy SD kártyára, amelyet hangfelvétel letöltésére és lejátszására használhatsz. A Wio Terminal csak 16GB méretig támogatja az SD kártyákat, és ezeknek FAT32 vagy exFAT formátumúaknak kell lenniük.

### Feladat - csatlakoztasd a ReSpeaker Pi Hat-et

1. Kapcsold ki a Wio Terminalt, majd csatlakoztasd a ReSpeaker 2-Mics Pi Hat-et a Wio Terminalhoz a jumper kábelek és a GPIO csatlakozók segítségével, amelyek a Wio Terminal hátoldalán találhatók:

    A csatlakozókat így kell összekötni:

    ![Pin diagram](../../../../../translated_images/hu/wio-respeaker-wiring-0.767f80aa65081038.webp)

1. Helyezd el a ReSpeakert és a Wio Terminalt úgy, hogy a GPIO csatlakozók felfelé nézzenek, és bal oldalon legyenek.

1. Kezdd a ReSpeaker GPIO csatlakozójának bal felső sarkában lévő aljzattal. Csatlakoztass egy pin-to-pin jumper kábelt a ReSpeaker bal felső aljzatából a Wio Terminal bal felső aljzatába.

1. Ismételd meg ezt az egész bal oldali GPIO csatlakozónál. Ügyelj arra, hogy a csatlakozók szorosan illeszkedjenek.

    ![A ReSpeaker bal oldali csatlakozói összekötve a Wio Terminal bal oldali csatlakozóival](../../../../../translated_images/hu/wio-respeaker-wiring-1.8d894727f2ba2400.webp)

    ![A ReSpeaker bal oldali csatlakozói összekötve a Wio Terminal bal oldali csatlakozóival](../../../../../translated_images/hu/wio-respeaker-wiring-2.329e1cbd306e754f.webp)

    > 💁 Ha a jumper kábelek szalagban vannak összekötve, tartsd őket együtt - így könnyebb biztosítani, hogy minden kábelt sorrendben csatlakoztattál.

1. Ismételd meg a folyamatot a ReSpeaker és a Wio Terminal jobb oldali GPIO csatlakozóival. Ezeket a kábeleket az előzőleg csatlakoztatott kábelek körül kell vezetni.

    ![A ReSpeaker jobb oldali csatlakozói összekötve a Wio Terminal jobb oldali csatlakozóival](../../../../../translated_images/hu/wio-respeaker-wiring-3.75b0be447e2fa930.webp)

    ![A ReSpeaker jobb oldali csatlakozói összekötve a Wio Terminal jobb oldali csatlakozóival](../../../../../translated_images/hu/wio-respeaker-wiring-4.aa9cd434d8779437.webp)

    > 💁 Ha a jumper kábelek szalagban vannak összekötve, oszd őket két szalagra. Vezesd őket az előző kábelek két oldalán.

    > 💁 Használhatsz ragasztószalagot, hogy a csatlakozókat egy blokkban rögzítsd, így megakadályozhatod, hogy a csatlakozók kicsússzanak, miközben mindet csatlakoztatod.
    >
    > ![A csatlakozók rögzítése szalaggal](../../../../../translated_images/hu/wio-respeaker-wiring-5.af117c20acf622f3.webp)

1. Csatlakoztatnod kell egy hangszórót.

    * Ha JST kábellel rendelkező hangszórót használsz, csatlakoztasd a JST porthoz a ReSpeakeren.

      ![JST kábellel csatlakoztatott hangszóró a ReSpeakerhez](../../../../../translated_images/hu/respeaker-jst-speaker.a441d177809df945.webp)

    * Ha 3.5mm jack csatlakozós hangszórót vagy fejhallgatót használsz, dugd be a 3.5mm jack aljzatba.

      ![3.5mm jack csatlakozón keresztül csatlakoztatott hangszóró a ReSpeakerhez](../../../../../translated_images/hu/respeaker-35mm-speaker.ad79ef4f128c7751.webp)

### Feladat - az SD kártya előkészítése

1. Csatlakoztasd az SD kártyát a számítógépedhez, külső olvasót használva, ha nincs SD kártyahelyed.

1. Formázd az SD kártyát a számítógéped megfelelő eszközével, ügyelve arra, hogy FAT32 vagy exFAT fájlrendszert használj.

1. Helyezd be az SD kártyát a Wio Terminal bal oldalán, a bekapcsoló gomb alatt található SD kártyahelyre. Győződj meg róla, hogy a kártya teljesen be van helyezve és kattan - ehhez szükséged lehet egy vékony eszközre vagy egy másik SD kártyára, hogy teljesen benyomd.

    ![Az SD kártya behelyezése az SD kártyahelyre a bekapcsoló gomb alatt](../../../../../translated_images/hu/wio-sd-card.acdcbe322fa4ee7f.webp)

    > 💁 Az SD kártya eltávolításához enyhén nyomd be, és ki fog ugrani. Ehhez vékony eszközre lesz szükséged, például egy lapos fejű csavarhúzóra vagy egy másik SD kártyára.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.