<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d93ee76fac4c2199973689ecd05baaf9",
  "translation_date": "2025-08-27T22:40:57+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/assignment.md",
  "language_code": "hu"
}
-->
# Hasonlítsd össze a domaineket

## Útmutató

Amikor létrehoztad az objektumdetektorodat, több domain közül választhattál. Hasonlítsd össze, hogy ezek közül melyik működik a legjobban a készleted detektorához, és írd le, melyik ad jobb eredményeket.

A domain megváltoztatásához válaszd ki a **Beállítások** gombot a felső menüben, válassz egy új domaint, kattints a **Változtatások mentése** gombra, majd tanítsd újra a modellt. Ügyelj arra, hogy az új domainnel betanított modell új iterációját teszteld.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| A modell betanítása egy másik domainnel | Sikerült megváltoztatni a domaint és újra betanítani a modellt | Sikerült megváltoztatni a domaint és újra betanítani a modellt | Nem sikerült megváltoztatni a domaint vagy újra betanítani a modellt |
| A modell tesztelése és az eredmények összehasonlítása | Sikerült a modellt különböző domainekkel tesztelni, az eredményeket összehasonlítani, és leírni, melyik a jobb | Sikerült a modellt különböző domainekkel tesztelni, de nem sikerült az eredményeket összehasonlítani és leírni, melyik a jobb | Nem sikerült a modellt különböző domainekkel tesztelni |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.