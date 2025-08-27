<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T21:07:47+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "cs"
}
-->
# Zrušení časovače

## Pokyny

V této lekci jste dosud naučili model rozpoznávat nastavení časovače. Další užitečnou funkcí je zrušení časovače – například když je váš chléb hotový a může být vyndán z trouby dříve, než časovač doběhne.

Přidejte nový záměr do své LUIS aplikace pro zrušení časovače. Nebude potřebovat žádné entity, ale bude vyžadovat několik příkladových vět. Zpracujte tento záměr ve svém serverless kódu, pokud je to hlavní záměr, zaznamenejte, že byl rozpoznán, a vraťte odpovídající reakci.

## Hodnocení

| Kritérium | Vynikající | Přiměřené | Vyžaduje zlepšení |
| --------- | ---------- | --------- | ----------------- |
| Přidání záměru pro zrušení časovače do LUIS aplikace | Záměr byl úspěšně přidán a model byl natrénován | Záměr byl přidán, ale model nebyl natrénován | Záměr nebyl přidán ani model nebyl natrénován |
| Zpracování záměru v serverless aplikaci | Záměr byl rozpoznán jako hlavní záměr a byl zaznamenán | Záměr byl rozpoznán jako hlavní záměr | Záměr nebyl rozpoznán jako hlavní záměr |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.