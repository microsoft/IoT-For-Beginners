<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T23:07:34+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "cs"
}
-->
# Vytvoření nového IoT zařízení

## Instrukce

Během posledních 6 lekcí jste se naučili o digitálním zemědělství a o tom, jak používat IoT zařízení ke sběru dat pro předpověď růstu rostlin a automatizaci zavlažování na základě měření vlhkosti půdy.

Využijte to, co jste se naučili, k vytvoření nového IoT zařízení s použitím senzoru a aktuátoru dle vašeho výběru. Odesílejte telemetrii do IoT Hubu a použijte ji k ovládání aktuátoru prostřednictvím bezserverového kódu. Můžete použít senzor a aktuátor, které jste již použili v tomto nebo předchozím projektu, nebo pokud máte jiný hardware, vyzkoušejte něco nového.

## Hodnoticí kritéria

| Kritérium | Vynikající | Dostatečné | Potřebuje zlepšení |
| --------- | ---------- | ---------- | ------------------ |
| Naprogramovat IoT zařízení pro použití senzoru a aktuátoru | Naprogramováno IoT zařízení, které funguje se senzorem i aktuátorem | Naprogramováno IoT zařízení, které funguje se senzorem nebo aktuátorem | Nepodařilo se naprogramovat IoT zařízení pro použití senzoru nebo aktuátoru |
| Připojit IoT zařízení k IoT Hubu | Podařilo se nasadit IoT Hub, odesílat do něj telemetrii a přijímat z něj příkazy | Podařilo se nasadit IoT Hub a buď odesílat telemetrii, nebo přijímat příkazy | Nepodařilo se nasadit IoT Hub a komunikovat s ním z IoT zařízení |
| Ovládat aktuátor pomocí bezserverového kódu | Podařilo se nasadit Azure Function pro ovládání zařízení spouštěnou telemetrickými událostmi | Podařilo se nasadit Azure Function spouštěnou telemetrickými událostmi, ale nepodařilo se ovládat aktuátor | Nepodařilo se nasadit Azure Function |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.