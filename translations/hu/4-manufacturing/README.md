<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:35:08+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "hu"
}
-->
# Gyártás és feldolgozás - Az IoT használata az élelmiszer-feldolgozás javítására

Amikor az élelmiszer eljut egy központi elosztóhelyre vagy feldolgozóüzembe, nem mindig kerül azonnal a szupermarketekbe. Gyakran több feldolgozási lépésen megy keresztül, például minőség szerinti válogatáson. Ez korábban manuális folyamat volt - a mezőn kezdődött, ahol a szedők csak az érett gyümölcsöket szedték le, majd a gyárban a gyümölcsök futószalagon haladtak, és az alkalmazottak kézzel távolították el a sérült vagy rothadt gyümölcsöket. Magam is szedtem és válogattam epret nyári diákmunkaként, így tanúsíthatom, hogy ez nem egy szórakoztató munka.

A modernebb rendszerek az IoT-t használják a válogatáshoz. Az egyik legkorábbi eszköz, például a [Weco](https://wecotek.com) válogatói optikai érzékelőket használnak a termény minőségének észlelésére, például elutasítva a zöld paradicsomokat. Ezeket a farmon, a betakarítógépekben vagy a feldolgozóüzemekben is lehet alkalmazni.

Ahogy az előrelépések történnek a Mesterséges Intelligencia (AI) és a Gépi Tanulás (ML) területén, ezek a gépek egyre fejlettebbé válhatnak, ML modelleket használva, amelyek képesek megkülönböztetni a gyümölcsöt és az idegen tárgyakat, például köveket, földet vagy rovarokat. Ezeket a modelleket arra is lehet tanítani, hogy ne csak a sérült gyümölcsöket, hanem a betegségek korai jeleit vagy más terményproblémákat is felismerjék.

> 🎓 Az *ML modell* kifejezés arra utal, hogy a gépi tanulási szoftvert egy adathalmazon képezték ki. Például ki lehet képezni egy ML modellt arra, hogy megkülönböztesse az érett és éretlen paradicsomokat, majd az új képeken alkalmazva megállapítható, hogy a paradicsom érett-e vagy sem.

Ebben a 4 leckében megtanulhatod, hogyan képezz ki képalapú AI modelleket a gyümölcsminőség észlelésére, hogyan használd ezeket egy IoT eszközről, és hogyan futtasd ezeket az eszközön - azaz egy IoT eszközön, nem pedig a felhőben.

> 💁 Ezek a leckék néhány felhőalapú erőforrást fognak használni. Ha nem fejezed be az összes leckét ebben a projektben, győződj meg róla, hogy [takarítsd el a projektet](../clean-up.md).

## Témák

1. [Gyümölcsminőség-érzékelő kiképzése](./lessons/1-train-fruit-detector/README.md)
1. [Gyümölcsminőség ellenőrzése IoT eszközről](./lessons/2-check-fruit-from-device/README.md)
1. [Gyümölcsminőség-érzékelő futtatása az eszközön](./lessons/3-run-fruit-detector-edge/README.md)
1. [Gyümölcsminőség-érzékelés indítása érzékelőről](./lessons/4-trigger-fruit-detector/README.md)

## Köszönetnyilvánítás

Az összes leckét ♥️-vel írta [Jen Fox](https://github.com/jenfoxbot) és [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.