<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T22:55:40+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "cs"
}
-->
# Kalibrace vašeho senzoru

## Pokyny

V této lekci jste získali hodnoty z čidla vlhkosti půdy, měřené jako hodnoty od 0 do 1023. Abyste je mohli převést na skutečné hodnoty vlhkosti půdy, je potřeba senzor kalibrovat. To můžete udělat tak, že odeberete vzorky půdy, provedete měření a vypočítáte gravimetrický obsah vlhkosti půdy z těchto vzorků.

Tyto kroky budete muset opakovat několikrát, pokaždé s různou vlhkostí půdy, abyste získali potřebná měření.

1. Proveďte měření vlhkosti půdy pomocí senzoru vlhkosti půdy. Zapište si tuto hodnotu.

1. Odeberte vzorek půdy a zvažte jej. Zapište si tuto hmotnost.

1. Vysušte půdu – nejlepším způsobem je teplá trouba na 110 °C (230 °F) po několik hodin. Můžete ji také sušit na slunci nebo ji umístit na teplé, suché místo, dokud nebude půda zcela suchá. Měla by být práškovitá a sypká.

    > 💁 V laboratoři pro co nejpřesnější výsledky byste půdu sušili v troubě 48–72 hodin. Pokud máte ve škole sušicí trouby, zjistěte, zda je můžete použít k delšímu sušení. Čím déle, tím sušší vzorek a tím přesnější výsledky.

1. Zvažte půdu znovu.

    > 🔥 Pokud jste ji sušili v troubě, ujistěte se, že nejprve vychladla!

Gravimetrická vlhkost půdy se vypočítá jako:

![vlhkost půdy % je hmotnost mokré půdy minus hmotnost suché půdy, děleno hmotností suché půdy, krát 100](../../../../../translated_images/cs/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W  
- hmotnost mokré půdy  
* W  
- hmotnost suché půdy  

Například, máte vzorek půdy, který váží 212 g mokrý a 197 g suchý.

![Vyplněný výpočet](../../../../../translated_images/cs/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212 g  
* W = 197 g  
* 212 - 197 = 15  
* 15 / 197 = 0,076  
* 0,076 * 100 = 7,6 %

V tomto příkladu má půda gravimetrickou vlhkost 7,6 %.

Jakmile budete mít hodnoty alespoň pro 3 vzorky, vytvořte graf vlhkosti půdy % vůči hodnotám senzoru vlhkosti půdy a přidejte čáru, která nejlépe odpovídá bodům. Poté můžete použít tento graf k výpočtu gravimetrického obsahu vlhkosti půdy pro danou hodnotu senzoru tím, že přečtete hodnotu z čáry.

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Potřebuje zlepšení |
| -------- | ---------- | --------- | ------------------ |
| Shromáždění kalibračních dat | Získání alespoň 3 kalibračních vzorků | Získání alespoň 2 kalibračních vzorků | Získání alespoň 1 kalibračního vzorku |
| Provedení kalibrovaného měření | Úspěšné vytvoření kalibračního grafu, provedení měření senzorem a převod na gravimetrický obsah vlhkosti půdy | Úspěšné vytvoření kalibračního grafu | Neschopnost vytvořit graf |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.