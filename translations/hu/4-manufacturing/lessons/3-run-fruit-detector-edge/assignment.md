<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:51:15+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "hu"
}
-->
# Szolgáltatások futtatása az edge-en

## Útmutató

Nem csak képosztályozók futtathatók az edge-en, hanem bármi, amit konténerbe lehet csomagolni, telepíthető egy IoT Edge eszközre. Az Azure Functions formájában futó szerver nélküli kód, például az előző leckékben létrehozott triggerek, konténerekben futtathatók, így IoT Edge-en is.

Válassz ki egy korábbi leckét, és próbáld meg futtatni az Azure Functions alkalmazást egy IoT Edge konténerben. Találsz egy útmutatót, amely bemutatja, hogyan lehet ezt megtenni egy másik Functions alkalmazás projekttel a [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11) oldalon.

## Értékelési szempontok

| Kritérium | Kiemelkedő | Megfelelő | Fejlesztésre szorul |
| --------- | ---------- | --------- | ------------------- |
| Azure Functions alkalmazás telepítése IoT Edge-re | Sikeresen telepítette az Azure Functions alkalmazást IoT Edge-re, és IoT eszközzel használta, hogy IoT adatokból trigger fusson | Sikeresen telepítette a Functions alkalmazást IoT Edge-re, de nem sikerült elindítani a triggert | Nem sikerült telepíteni a Functions alkalmazást IoT Edge-re |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.