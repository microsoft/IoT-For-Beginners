<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-27T23:30:19+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "hu"
}
-->
# Relé vezérlése - Wio Terminal

A lecke ezen részében egy relét fogsz hozzáadni a Wio Terminalhoz a talajnedvesség-érzékelő mellett, és a talajnedvesség szintje alapján vezérled azt.

## Hardver

A Wio Terminalhoz szükség van egy relére.

A relé, amit használni fogsz, egy [Grove relé](https://www.seeedstudio.com/Grove-Relay.html), egy alapállapotban nyitott relé (ami azt jelenti, hogy a kimeneti áramkör nyitott, vagyis nincs összekapcsolva, ha nem érkezik jel a reléhez), amely akár 250V és 10A kimeneti áramköröket is kezelni tud.

Ez egy digitális aktuátor, így a Wio Terminal digitális lábaihoz csatlakozik. A kombinált analóg/digitális port már használatban van a talajnedvesség-érzékelővel, így ez a másik portba csatlakozik, amely egy kombinált I

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.