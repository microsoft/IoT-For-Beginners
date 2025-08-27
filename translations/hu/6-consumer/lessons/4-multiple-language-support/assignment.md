<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T21:35:53+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "hu"
}
-->
# Univerzális fordító készítése

## Útmutató

Az univerzális fordító egy olyan eszköz, amely több nyelv között képes fordítani, lehetővé téve, hogy különböző nyelveket beszélő emberek kommunikálni tudjanak egymással. Használd fel az elmúlt néhány leckében tanultakat, hogy két IoT eszköz segítségével megépítsd az univerzális fordítót.

> Ha nincs két eszközöd, kövesd az előző néhány leckében leírt lépéseket, hogy egy virtuális IoT eszközt állíts be az egyik IoT eszközként.

Konfiguráld az egyik eszközt az egyik nyelvre, a másikat pedig egy másik nyelvre. Mindkét eszköznek képesnek kell lennie a beszéd fogadására, szöveggé alakítására, majd az IoT Hubon és egy Functions alkalmazáson keresztül elküldeni a másik eszköznek, lefordítani, és lejátszani a fordított beszédet.

> 💁 Tipp: Amikor az egyik eszközről a másikra küldöd a beszédet, küldd el azt is, hogy milyen nyelven van, így könnyebb lesz lefordítani. Akár azt is megteheted, hogy minden eszköz először regisztrál az IoT Hubon és egy Functions alkalmazáson keresztül, megadva a támogatott nyelvet, amelyet az Azure Storage-ban tárolsz. Ezután egy Functions alkalmazás végezheti el a fordítást, és küldheti el a fordított szöveget az IoT eszköznek.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| Univerzális fordító létrehozása | Sikerült univerzális fordítót készíteni, amely az egyik eszköz által érzékelt beszédet egy másik eszközön egy másik nyelven lejátszott beszéddé alakítja | Sikerült néhány komponenst működésre bírni, például a beszéd rögzítését vagy fordítását, de nem sikerült az elejétől a végéig működő megoldást készíteni | Nem sikerült egyetlen működő részt sem létrehozni az univerzális fordítóból |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.