<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T11:32:36+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "sk"
}
-->
# Vizualizácia údajov GDD pomocou Jupyter Notebooku

## Pokyny

V tejto lekcii ste získali údaje o GDD pomocou IoT senzora. Na získanie kvalitných údajov o GDD je potrebné zbierať údaje počas viacerých dní. Na vizualizáciu údajov o teplote a výpočet GDD môžete použiť nástroje ako [Jupyter Notebooks](https://jupyter.org) na analýzu údajov.

Začnite zbieraním údajov počas niekoľkých dní. Musíte zabezpečiť, aby váš serverový kód bežal nepretržite počas prevádzky vášho IoT zariadenia, buď úpravou nastavení správy napájania, alebo spustením niečoho ako [tento Python skript na udržanie systému aktívneho](https://github.com/jaqsparow/keep-system-active).

Keď budete mať údaje o teplote, môžete použiť Jupyter Notebook v tomto repozitári na ich vizualizáciu a výpočet GDD. Jupyter notebooky kombinujú kód a pokyny v blokoch nazývaných *bunky*, často kód v Pythone. Môžete si prečítať pokyny a potom spustiť každý blok kódu, jeden po druhom. Kód môžete tiež upravovať. Napríklad v tomto notebooku môžete upraviť základnú teplotu použitú na výpočet GDD pre vašu rastlinu.

1. Vytvorte priečinok s názvom `gdd-calculation`

1. Stiahnite súbor [gdd.ipynb](./code-notebook/gdd.ipynb) a skopírujte ho do priečinka `gdd-calculation`.

1. Skopírujte súbor `temperature.csv`, ktorý vytvoril MQTT server.

1. Vytvorte nové virtuálne prostredie Python v priečinku `gdd-calculation`.

1. Nainštalujte niektoré balíčky pip pre Jupyter notebooky spolu s knižnicami potrebnými na správu a vizualizáciu údajov:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Spustite notebook v Jupyteri:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter sa spustí a otvorí notebook vo vašom prehliadači. Prejdite si pokyny v notebooku, aby ste vizualizovali namerané teploty a vypočítali rastové stupne dní (GDD).

    ![Jupyter notebook](../../../../../translated_images/sk/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Hodnotiace kritériá

| Kritérium | Vynikajúce | Dostatočné | Potrebuje zlepšenie |
| --------- | ---------- | ---------- | ------------------- |
| Zber údajov | Zber údajov aspoň za 2 kompletné dni | Zber údajov aspoň za 1 kompletný deň | Zber niektorých údajov |
| Výpočet GDD | Úspešne spustiť notebook a vypočítať GDD | Úspešne spustiť notebook | Nepodarilo sa spustiť notebook |

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.