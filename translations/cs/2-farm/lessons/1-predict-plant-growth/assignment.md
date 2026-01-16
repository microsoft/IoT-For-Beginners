<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T23:21:10+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "cs"
}
-->
# Vizualizace dat GDD pomocí Jupyter Notebooku

## Instrukce

V této lekci jste získali data GDD pomocí IoT senzoru. Abyste získali kvalitní data GDD, je potřeba sbírat data po několik dní. K vizualizaci teplotních dat a výpočtu GDD můžete použít nástroje jako [Jupyter Notebooks](https://jupyter.org) k analýze dat.

Začněte sběrem dat po několik dní. Musíte zajistit, aby váš serverový kód běžel po celou dobu, kdy je vaše IoT zařízení aktivní, buď úpravou nastavení správy napájení, nebo spuštěním něčeho jako [tento Python skript pro udržení systému aktivního](https://github.com/jaqsparow/keep-system-active).

Jakmile máte teplotní data, můžete použít Jupyter Notebook v tomto repozitáři k jejich vizualizaci a výpočtu GDD. Jupyter notebooky kombinují kód a instrukce v blocích nazývaných *buňky*, často s kódem v Pythonu. Můžete si přečíst instrukce a poté spustit každý blok kódu, jeden po druhém. Kód můžete také upravovat. Například v tomto notebooku můžete upravit základní teplotu použitou k výpočtu GDD pro vaši rostlinu.

1. Vytvořte složku nazvanou `gdd-calculation`

1. Stáhněte soubor [gdd.ipynb](./code-notebook/gdd.ipynb) a zkopírujte jej do složky `gdd-calculation`.

1. Zkopírujte soubor `temperature.csv`, který vytvořil MQTT server.

1. Vytvořte nový Python virtuální prostředí ve složce `gdd-calculation`.

1. Nainstalujte pomocí pip balíčky pro Jupyter notebooky spolu s knihovnami potřebnými pro správu a vizualizaci dat:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Spusťte notebook v Jupyteru:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter se spustí a otevře notebook ve vašem prohlížeči. Projděte si instrukce v notebooku, vizualizujte naměřené teploty a vypočítejte růstové stupně (GDD).

    ![Jupyter notebook](../../../../../translated_images/cs/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Hodnocení

| Kritéria | Vynikající | Přiměřené | Vyžaduje zlepšení |
| -------- | ---------- | --------- | ----------------- |
| Sběr dat | Získání alespoň 2 kompletních dnů dat | Získání alespoň 1 kompletního dne dat | Získání nějakých dat |
| Výpočet GDD | Úspěšné spuštění notebooku a výpočet GDD | Úspěšné spuštění notebooku | Neschopnost spustit notebook |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby AI pro překlady [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatizované překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.