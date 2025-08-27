<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:44:46+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "cs"
}
-->
# Vytvořte detektor kvality ovoce

## Pokyny

Vytvořte detektor kvality ovoce!

Využijte vše, co jste se dosud naučili, a sestavte prototyp detektoru kvality ovoce. Spusťte klasifikaci obrazu na základě blízkosti pomocí AI modelu běžícího na edge zařízení, uložte výsledky klasifikace do úložiště a ovládejte LED diodu na základě zralosti ovoce.

Měli byste být schopni to sestavit pomocí kódu, který jste napsali ve všech předchozích lekcích.

## Hodnocení

| Kritéria | Vynikající | Dostatečné | Potřebuje zlepšení |
| -------- | ---------- | ---------- | ------------------ |
| Nastavení všech služeb | Byl schopen nastavit IoT Hub, aplikaci Azure Functions a úložiště Azure | Byl schopen nastavit IoT Hub, ale ne aplikaci Azure Functions nebo úložiště Azure | Nebyl schopen nastavit žádné internetové IoT služby |
| Monitorování blízkosti a odesílání dat do IoT Hub, pokud je objekt blíže než předem definovaná vzdálenost, a spuštění kamery pomocí příkazu | Byl schopen měřit vzdálenost a odeslat zprávu do IoT Hub, když byl objekt dostatečně blízko, a odeslat příkaz ke spuštění kamery | Byl schopen měřit blízkost a odeslat data do IoT Hub, ale nebyl schopen odeslat příkaz ke spuštění kamery | Nebyl schopen měřit vzdálenost a odeslat zprávu do IoT Hub ani spustit příkaz |
| Zachycení obrazu, jeho klasifikace a odeslání výsledků do IoT Hub | Byl schopen zachytit obraz, klasifikovat jej pomocí edge zařízení a odeslat výsledky do IoT Hub | Byl schopen klasifikovat obraz, ale ne pomocí edge zařízení, nebo nebyl schopen odeslat výsledky do IoT Hub | Nebyl schopen klasifikovat obraz |
| Zapnutí nebo vypnutí LED diody v závislosti na výsledcích klasifikace pomocí příkazu odeslaného do zařízení | Byl schopen zapnout LED diodu pomocí příkazu, pokud bylo ovoce nezralé | Byl schopen odeslat příkaz do zařízení, ale ne ovládat LED diodu | Nebyl schopen odeslat příkaz k ovládání LED diody |

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Přestože se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.