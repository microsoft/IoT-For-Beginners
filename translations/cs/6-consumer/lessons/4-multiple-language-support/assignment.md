<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T21:36:02+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "cs"
}
-->
# Vytvořte univerzální překladač

## Pokyny

Univerzální překladač je zařízení, které dokáže překládat mezi různými jazyky, což umožňuje lidem, kteří mluví různými jazyky, komunikovat. Použijte znalosti získané v předchozích lekcích k vytvoření univerzálního překladače pomocí 2 IoT zařízení.

> Pokud nemáte 2 zařízení, postupujte podle kroků v předchozích lekcích a nastavte virtuální IoT zařízení jako jedno z IoT zařízení.

Měli byste nakonfigurovat jedno zařízení pro jeden jazyk a druhé pro jiný. Každé zařízení by mělo přijímat řeč, převést ji na text, poslat ji druhému zařízení přes IoT Hub a Functions aplikaci, poté ji přeložit a přehrát přeloženou řeč.

> 💁 Tip: Při odesílání řeči z jednoho zařízení na druhé pošlete také informaci o jazyku, ve kterém je řeč, což usnadní překlad. Můžete dokonce nechat každé zařízení zaregistrovat se pomocí IoT Hub a Functions aplikace, přičemž předáte jazyk, který podporují, aby byl uložen v Azure Storage. Poté můžete použít Functions aplikaci k provedení překladů a odeslání přeloženého textu na IoT zařízení.

## Hodnocení

| Kritéria | Vynikající | Dostatečné | Vyžaduje zlepšení |
| -------- | ---------- | ---------- | ----------------- |
| Vytvoření univerzálního překladače | Podařilo se vytvořit univerzální překladač, který převádí řeč detekovanou jedním zařízením na řeč přehrávanou druhým zařízením v jiném jazyce | Podařilo se zprovoznit některé komponenty, jako je zachycení řeči nebo překlad, ale nepodařilo se vytvořit kompletní řešení | Nepodařilo se vytvořit žádnou část funkčního univerzálního překladače |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Přestože se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.