<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-27T21:36:23+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "hu"
}
-->
# Szállítás a farmról a gyárba - az IoT használata az élelmiszer-szállítás nyomon követésére

Sok gazda termel élelmiszert eladásra – vagy kereskedelmi gazdálkodók, akik mindent eladnak, amit termelnek, vagy önellátó gazdák, akik a felesleget értékesítik, hogy alapvető szükségleteket vásároljanak. Valahogy az élelmiszernek el kell jutnia a farmról a fogyasztóhoz, és ez általában tömeges szállításon alapul, amely a farmokról a központokba vagy feldolgozóüzemekbe, majd az üzletekbe történik. Például egy paradicsomtermesztő gazda leszüreteli a paradicsomot, dobozokba csomagolja, teherautóra rakja, majd eljuttatja egy feldolgozóüzembe. A paradicsomot ott szétválogatják, majd feldolgozott élelmiszerként, kiskereskedelmi eladásra vagy éttermekben történő fogyasztásra juttatják el a fogyasztókhoz.

Az IoT segíthet ebben az ellátási láncban az élelmiszer szállítás közbeni nyomon követésével – biztosítva, hogy a sofőrök oda menjenek, ahová kell, figyelve a járművek helyzetét, és értesítéseket kapva, amikor a járművek megérkeznek, hogy az élelmiszert kirakhassák, és a feldolgozás minél hamarabb megkezdődhessen.

> 🎓 Az *ellátási lánc* az a tevékenységsorozat, amely valami előállítását és szállítását biztosítja. Például a paradicsomtermesztésben magában foglalja a vetőmag, talaj, műtrágya és vízellátást, a paradicsom termesztését, a paradicsom központi hubba történő szállítását, a szupermarket helyi hubjába történő szállítást, az egyes szupermarketekbe történő szállítást, a polcokra helyezést, majd a fogyasztónak történő eladást és hazavitelét fogyasztásra. Minden lépés olyan, mint egy láncszem a láncban.

> 🎓 Az ellátási lánc szállítási részét *logisztikának* nevezik.

Ebben a 4 leckében megtanulod, hogyan alkalmazd az Internet of Things technológiát az ellátási lánc javítására azáltal, hogy nyomon követed az élelmiszert, miközben azt egy (virtuális) teherautóra rakodják, amelyet követhetsz, ahogy eljut a célállomására. Megtanulod a GPS nyomkövetést, a GPS-adatok tárolását és vizualizálását, valamint azt, hogyan kapj értesítést, amikor egy teherautó megérkezik a célállomására.

> 💁 Ezek a leckék néhány felhőalapú erőforrást használnak. Ha nem fejezed be az összes leckét ebben a projektben, győződj meg róla, hogy [Tisztítsd meg a projektedet](../clean-up.md).

## Témák

1. [Helymeghatározás nyomon követése](lessons/1-location-tracking/README.md)
1. [Helyadatok tárolása](lessons/2-store-location-data/README.md)
1. [Helyadatok vizualizálása](lessons/3-visualize-location-data/README.md)
1. [Geokerítések](lessons/4-geofences/README.md)

## Köszönetnyilvánítás

Minden leckét ♥️-val írt [Jen Looper](https://github.com/jlooper) és [Jim Bennett](https://GitHub.com/JimBobBennett).

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.