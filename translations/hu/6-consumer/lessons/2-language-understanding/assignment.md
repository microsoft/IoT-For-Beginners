<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T21:07:39+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "hu"
}
-->
# Törölje az időzítőt

## Útmutató

Eddig ebben a leckében megtanítottad a modellt arra, hogyan állítson be egy időzítőt. Egy másik hasznos funkció az időzítő törlése - például ha a kenyér elkészült, és kiveheted a sütőből, mielőtt az időzítő lejárna.

Adj hozzá egy új szándékot a LUIS alkalmazásodhoz az időzítő törléséhez. Ehhez nem lesz szükség entitásokra, de néhány példamondatra igen. Kezeld ezt a szerver nélküli kódodban, ha ez a legvalószínűbb szándék, naplózva, hogy a szándékot felismerte, és egy megfelelő választ visszaadva.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| Az időzítő törlésére szolgáló szándék hozzáadása a LUIS alkalmazáshoz | Sikerült hozzáadni a szándékot és betanítani a modellt | Sikerült hozzáadni a szándékot, de nem sikerült betanítani a modellt | Nem sikerült hozzáadni a szándékot és betanítani a modellt |
| A szándék kezelése a szerver nélküli alkalmazásban | Sikerült felismerni a szándékot, mint a legvalószínűbb szándékot, és naplózni azt | Sikerült felismerni a szándékot, mint a legvalószínűbb szándékot | Nem sikerült felismerni a szándékot, mint a legvalószínűbb szándékot |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.