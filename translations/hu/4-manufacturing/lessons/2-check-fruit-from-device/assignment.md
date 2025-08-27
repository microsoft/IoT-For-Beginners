<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:59:12+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "hu"
}
-->
# Reagálás a besorolási eredményekre

## Útmutató

Az eszközöd képeket osztályozott, és rendelkezik az előrejelzések értékeivel. Az eszközöd felhasználhatja ezeket az információkat valamilyen művelet végrehajtására - például elküldheti az IoT Hubnak további rendszerek feldolgozására, vagy vezérelhet egy aktuátort, például egy LED-et, amely akkor világít, ha a gyümölcs éretlen.

Adj hozzá kódot az eszközödhöz, hogy az általad választott módon reagáljon - például küldjön adatokat egy IoT Hubnak, vezéreljen egy aktuátort, vagy kombináld a kettőt, és küldj adatokat egy IoT Hubnak olyan szerver nélküli kóddal, amely meghatározza, hogy a gyümölcs érett-e vagy sem, és visszaküld egy parancsot az aktuátor vezérlésére.

## Értékelési szempontok

| Kritérium | Kiemelkedő | Megfelelő | Fejlesztésre szorul |
| --------- | ---------- | --------- | ------------------- |
| Reagálás az előrejelzésekre | Sikeresen megvalósított egy olyan reakciót az előrejelzésekre, amely következetesen működik azonos értékű előrejelzésekkel. | Sikeresen megvalósított egy reakciót, amely nem függ az előrejelzésektől, például csak nyers adatokat küld egy IoT Hubnak. | Nem sikerült az eszközt úgy programozni, hogy reagáljon az előrejelzésekre. |

---

**Felelősségkizárás**:  
Ezt a dokumentumot az [Co-op Translator](https://github.com/Azure/co-op-translator) AI fordítószolgáltatás segítségével fordítottuk le. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy téves értelmezésekért.