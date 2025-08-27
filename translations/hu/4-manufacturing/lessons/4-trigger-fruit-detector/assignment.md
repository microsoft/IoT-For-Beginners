<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:44:35+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "hu"
}
-->
# Építs egy gyümölcsminőség-ellenőrzőt

## Útmutató

Építsd meg a gyümölcsminőség-ellenőrzőt!

Használd fel mindazt, amit eddig tanultál, és készítsd el a prototípus gyümölcsminőség-ellenőrzőt. Indítsd el a képosztályozást közelség alapján egy peremhálózaton futó AI modell segítségével, tárold az osztályozás eredményeit, és irányíts egy LED-et a gyümölcs érettségi állapota alapján.

Ezt össze tudod állítani az eddigi leckékben írt kódok felhasználásával.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| Az összes szolgáltatás konfigurálása | Sikerült beállítani egy IoT Hubot, egy Azure Functions alkalmazást és egy Azure tárhelyet | Sikerült beállítani az IoT Hubot, de az Azure Functions alkalmazást vagy az Azure tárhelyet nem | Nem sikerült beállítani egyetlen IoT szolgáltatást sem |
| A közelség figyelése és az adatok küldése az IoT Hubba, ha egy objektum egy előre meghatározott távolságnál közelebb van, valamint a kamera indítása egy parancs segítségével | Sikerült a távolságot mérni, üzenetet küldeni az IoT Hubba, ha egy objektum elég közel van, és egy parancsot küldeni a kamera indításához | Sikerült a közelséget mérni és elküldeni az IoT Hubba, de nem sikerült parancsot küldeni a kamerának | Nem sikerült a távolságot mérni, üzenetet küldeni az IoT Hubba, vagy parancsot küldeni |
| Kép rögzítése, osztályozása és az eredmények küldése az IoT Hubba | Sikerült egy képet rögzíteni, azt egy peremhálózati eszközzel osztályozni, és az eredményeket elküldeni az IoT Hubba | Sikerült a képet osztályozni, de nem peremhálózati eszközzel, vagy nem sikerült az eredményeket elküldeni az IoT Hubba | Nem sikerült a képet osztályozni |
| A LED be- vagy kikapcsolása az osztályozás eredményei alapján egy eszköznek küldött parancs segítségével | Sikerült egy parancs segítségével bekapcsolni a LED-et, ha a gyümölcs éretlen volt | Sikerült parancsot küldeni az eszköznek, de nem sikerült irányítani a LED-et | Nem sikerült parancsot küldeni a LED irányításához |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.