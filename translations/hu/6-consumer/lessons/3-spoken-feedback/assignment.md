<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da5d9360fe02fdcc1e91a725016c846d",
  "translation_date": "2025-08-27T21:15:59+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/assignment.md",
  "language_code": "hu"
}
-->
# Törölje az időzítőt

## Útmutató

Az előző lecke feladatában hozzáadott egy időzítő törlése szándékot a LUIS-hoz. Ehhez a feladathoz kezelnie kell ezt a szándékot a serverless kódban, küldenie kell egy parancsot az IoT eszköznek, majd törölnie kell az időzítőt.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| A szándék kezelése a serverless kódban és parancs küldése | Sikerült kezelni a szándékot és parancsot küldeni az eszköznek | Sikerült kezelni a szándékot, de nem sikerült parancsot küldeni az eszköznek | Nem sikerült kezelni a szándékot |
| Az időzítő törlése az eszközön | Sikerült fogadni a parancsot és törölni az időzítőt | Sikerült fogadni a parancsot, de nem sikerült törölni az időzítőt | Nem sikerült fogadni a parancsot |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.