<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:59:26+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "cs"
}
-->
# Reakce na výsledky klasifikace

## Pokyny

Vaše zařízení klasifikovalo obrázky a má hodnoty pro předpovědi. Vaše zařízení může tyto informace využít k nějaké akci – může je například odeslat do IoT Hubu k dalšímu zpracování jinými systémy, nebo může ovládat akční člen, jako je LED dioda, která se rozsvítí, když je ovoce nezralé.

Přidejte do svého zařízení kód, který bude reagovat podle vašeho výběru – buď odesílejte data do IoT Hubu, ovládejte akční člen, nebo zkombinujte obojí a odesílejte data do IoT Hubu s bezserverovým kódem, který určí, zda je ovoce zralé, a pošle zpět příkaz k ovládání akčního členu.

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Vyžaduje zlepšení |
| -------- | ---------- | --------- | ----------------- |
| Reakce na předpovědi | Bylo možné implementovat reakci na předpovědi, která konzistentně funguje s předpověďmi stejné hodnoty. | Bylo možné implementovat reakci, která není závislá na předpovědích, například pouze odesílání surových dat do IoT Hubu. | Nebylo možné naprogramovat zařízení tak, aby reagovalo na předpovědi. |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.