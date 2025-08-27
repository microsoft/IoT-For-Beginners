<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T23:30:58+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "hu"
}
-->
# Hatékonyabb öntözési ciklus kialakítása

## Útmutató

Ebben a leckében azt tanultuk, hogyan lehet egy relét szenzoradatok alapján vezérelni, amely relé egy szivattyút irányíthat egy öntözőrendszerben. Egy meghatározott talajmennyiség esetén, ha a szivattyút egy fix ideig működtetjük, az mindig ugyanazt a hatást gyakorolja a talaj nedvességtartalmára. Ez azt jelenti, hogy meg tudjuk becsülni, hány másodpercnyi öntözés felel meg a talajnedvesség adott mértékű csökkenésének. Ezen adatok alapján egy szabályozottabb öntözőrendszert lehet kialakítani.

Ebben a feladatban ki kell számítania, hogy a szivattyúnak mennyi ideig kell működnie a talajnedvesség adott mértékű növeléséhez.

> ⚠️ Ha virtuális IoT hardvert használ, végigmehet ezen a folyamaton, de az eredményeket szimulálhatja úgy, hogy manuálisan növeli a talajnedvesség értékét egy fix mennyiséggel másodpercenként, amíg a relé be van kapcsolva.

1. Kezdje száraz talajjal. Mérje meg a talaj nedvességtartalmát.

1. Adjon hozzá egy fix mennyiségű vizet, akár úgy, hogy a szivattyút 1 másodpercig működteti, akár úgy, hogy egy meghatározott mennyiséget önt a talajra.

    > A szivattyúnak mindig állandó sebességgel kell működnie, így minden másodpercben ugyanannyi vizet kell szállítania.

1. Várja meg, amíg a talajnedvesség szintje stabilizálódik, majd végezzen mérést.

1. Ismételje meg ezt többször, és készítsen egy táblázatot az eredményekről. Az alábbiakban egy példa táblázat látható.

    | Összes szivattyúzási idő | Talajnedvesség | Csökkenés |
    | --- | --: | -: |
    | Száraz | 643 |  0 |
    | 1 mp  | 621 | 22 |
    | 2 mp  | 601 | 20 |
    | 3 mp  | 579 | 22 |
    | 4 mp  | 560 | 19 |
    | 5 mp  | 539 | 21 |
    | 6 mp  | 521 | 18 |

1. Számolja ki az átlagos talajnedvesség-növekedést másodpercenkénti vízmennyiség alapján. A fenti példában minden másodpercnyi víz átlagosan 20,3-mal csökkenti az értéket.

1. Használja fel ezeket az adatokat a szerver kódjának hatékonyabbá tételéhez, úgy, hogy a szivattyút a szükséges ideig működtesse, hogy a talajnedvesség elérje a kívánt szintet.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| Talajnedvesség adatainak rögzítése | Több mérést is képes rögzíteni fix mennyiségű víz hozzáadása után | Néhány mérést képes rögzíteni fix mennyiségű víz hozzáadása után | Csak egy-két mérést tud rögzíteni, vagy nem képes fix mennyiségű vizet használni |
| Szerver kód kalibrálása | Képes kiszámítani az átlagos talajnedvesség-csökkenést, és frissíteni a szerver kódját ennek alapján | Képes kiszámítani az átlagos csökkenést, de nem tudja frissíteni a szerver kódját, vagy helytelenül számolja ki az átlagot, de ennek értékét helyesen használja a szerver kód frissítéséhez | Nem képes kiszámítani az átlagot, vagy frissíteni a szerver kódját |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget az ebből a fordításból eredő félreértésekért vagy téves értelmezésekért.