<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T23:31:13+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "cs"
}
-->
# Vytvořte efektivnější zavlažovací cyklus

## Pokyny

Tato lekce se zabývala ovládáním relé pomocí dat ze senzorů, přičemž toto relé může ovládat čerpadlo pro zavlažovací systém. Pro definované množství půdy by provoz čerpadla po pevně stanovenou dobu měl mít vždy stejný vliv na vlhkost půdy. To znamená, že si můžete udělat představu o tom, kolik sekund zavlažování odpovídá určitému poklesu hodnoty vlhkosti půdy. Pomocí těchto dat můžete vytvořit lépe kontrolovaný zavlažovací systém.

V tomto úkolu vypočítáte, jak dlouho by mělo čerpadlo běžet, aby se dosáhlo určitého zvýšení vlhkosti půdy.

> ⚠️ Pokud používáte virtuální IoT hardware, můžete tento proces projít, ale simulujte výsledky manuálním zvýšením hodnoty vlhkosti půdy o pevné množství za sekundu, kdy je relé zapnuté.

1. Začněte se suchou půdou. Změřte vlhkost půdy.

1. Přidejte pevné množství vody, buď spuštěním čerpadla na 1 sekundu, nebo nalitím pevného množství vody.

    > Čerpadlo by mělo vždy běžet konstantní rychlostí, takže každou sekundu, kdy čerpadlo běží, by mělo dodat stejné množství vody.

1. Počkejte, až se úroveň vlhkosti půdy stabilizuje, a proveďte měření.

1. Opakujte tento proces několikrát a vytvořte tabulku výsledků. Příklad takové tabulky je uveden níže.

    | Celkový čas čerpadla | Vlhkost půdy | Pokles |
    | --- | --: | -: |
    | Suché | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Vypočítejte průměrné zvýšení vlhkosti půdy za sekundu přidané vody. V uvedeném příkladu každá sekunda vody snižuje hodnotu o průměrně 20,3.

1. Použijte tato data ke zlepšení efektivity serverového kódu, aby čerpadlo běželo po dobu potřebnou k dosažení požadované úrovně vlhkosti půdy.

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Vyžaduje zlepšení |
| -------- | --------- | -------- | ----------------- |
| Zaznamenání dat o vlhkosti půdy | Dokáže zaznamenat více měření po přidání pevného množství vody | Dokáže zaznamenat některá měření s pevným množstvím vody | Dokáže zaznamenat pouze jedno nebo dvě měření, nebo není schopen použít pevné množství vody |
| Kalibrace serverového kódu | Dokáže vypočítat průměrný pokles hodnoty vlhkosti půdy a aktualizovat serverový kód, aby to využil | Dokáže vypočítat průměrný pokles, ale nedokáže aktualizovat serverový kód, nebo není schopen správně vypočítat průměr, ale tuto hodnotu správně použije k aktualizaci serverového kódu | Není schopen vypočítat průměr nebo aktualizovat serverový kód |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.