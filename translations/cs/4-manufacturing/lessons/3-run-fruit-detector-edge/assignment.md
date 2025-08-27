<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:51:22+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "cs"
}
-->
# Spouštění dalších služeb na okraji

## Pokyny

Na okraji lze spouštět nejen klasifikátory obrázků, ale vše, co lze zabalit do kontejneru, může být nasazeno na zařízení IoT Edge. Bezkódové řešení, jako jsou Azure Functions, například trigery, které jste vytvořili v předchozích lekcích, mohou běžet v kontejnerech, a tedy i na IoT Edge.

Vyberte jednu z předchozích lekcí a zkuste spustit aplikaci Azure Functions v kontejneru IoT Edge. Návod, jak to provést s jiným projektem aplikace Functions, najdete v [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Vyžaduje zlepšení |
| -------- | ---------- | --------- | ----------------- |
| Nasazení aplikace Azure Functions na IoT Edge | Podařilo se nasadit aplikaci Azure Functions na IoT Edge a použít ji s IoT zařízením k aktivaci triggeru z IoT dat | Podařilo se nasadit aplikaci Functions na IoT Edge, ale nepodařilo se aktivovat trigger | Nepodařilo se nasadit aplikaci Functions na IoT Edge |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.