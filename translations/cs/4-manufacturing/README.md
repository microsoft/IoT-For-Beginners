<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:35:24+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "cs"
}
-->
# Výroba a zpracování - využití IoT ke zlepšení zpracování potravin

Jakmile potraviny dorazí do centrálního skladu nebo zpracovatelského závodu, ne vždy jsou ihned odeslány do supermarketů. Často procházejí několika kroky zpracování, například tříděním podle kvality. Tento proces býval manuální – začínal na poli, kde sběrači vybírali pouze zralé ovoce, a poté ve výrobním závodě ovoce putovalo po dopravním pásu, kde zaměstnanci ručně odstraňovali otlučené nebo shnilé plody. Sama jsem během letní brigády ve škole sbírala a třídila jahody, takže mohu potvrdit, že to není zrovna zábavná práce.

Modernější systémy se při třídění spoléhají na IoT. Některá z prvních zařízení, jako jsou třídiče od [Weco](https://wecotek.com), využívají optické senzory k detekci kvality plodin, například k vyřazení zelených rajčat. Tato zařízení mohou být nasazena přímo na farmách v kombajnech nebo ve zpracovatelských závodech.

S pokroky v oblasti umělé inteligence (AI) a strojového učení (ML) se tyto stroje mohou stát ještě pokročilejšími, přičemž využívají ML modely trénované k rozlišení mezi ovocem a cizími předměty, jako jsou kameny, hlína nebo hmyz. Tyto modely mohou být také trénovány k detekci kvality ovoce, nejen otlučených plodů, ale i k včasnému odhalení nemocí nebo jiných problémů s úrodou.

> 🎓 Termín *ML model* označuje výsledek trénování softwaru pro strojové učení na určité sadě dat. Například můžete natrénovat ML model, aby rozlišoval mezi zralými a nezralými rajčaty, a poté tento model použít na nové obrázky k určení, zda jsou rajčata zralá nebo ne.

V těchto 4 lekcích se naučíte, jak trénovat AI modely založené na obrazech k detekci kvality ovoce, jak je používat na IoT zařízení a jak je spouštět na okraji sítě – tedy přímo na IoT zařízení místo v cloudu.

> 💁 Tyto lekce budou využívat některé cloudové zdroje. Pokud neabsolvujete všechny lekce v tomto projektu, nezapomeňte [vyčistit svůj projekt](../clean-up.md).

## Témata

1. [Natrénujte detektor kvality ovoce](./lessons/1-train-fruit-detector/README.md)
1. [Zkontrolujte kvalitu ovoce z IoT zařízení](./lessons/2-check-fruit-from-device/README.md)
1. [Spusťte svůj detektor ovoce na okraji sítě](./lessons/3-run-fruit-detector-edge/README.md)
1. [Spusťte detekci kvality ovoce pomocí senzoru](./lessons/4-trigger-fruit-detector/README.md)

## Poděkování

Všechny lekce byly napsány s ♥️ [Jen Fox](https://github.com/jenfoxbot) a [Jimem Bennettem](https://GitHub.com/JimBobBennett).

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.