<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T23:07:26+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "hu"
}
-->
# Építs egy új IoT eszközt

## Útmutató

Az elmúlt 6 leckében megtanultad, hogyan alkalmazd a digitális mezőgazdaságot, és hogyan használj IoT eszközöket adatok gyűjtésére a növénynövekedés előrejelzéséhez, valamint az öntözés automatizálásához a talajnedvesség mérései alapján.

Használd fel a tanultakat, hogy építs egy új IoT eszközt egy általad választott szenzorral és aktuátorral. Küldj telemetriát egy IoT Hubba, és használd azt az aktuátor vezérlésére szerver nélküli kód segítségével. Használhatsz olyan szenzort és aktuátort, amelyet már használtál ebben vagy az előző projektben, vagy ha van más hardvered, próbálj ki valami újat.

## Értékelési szempontok

| Kritérium | Kiemelkedő | Megfelelő | Fejlesztésre szorul |
| --------- | ---------- | --------- | ------------------- |
| IoT eszköz kódolása szenzorral és aktuátorral | Olyan IoT eszközt kódolt, amely működik szenzorral és aktuátorral | Olyan IoT eszközt kódolt, amely működik szenzorral vagy aktuátorral | Nem sikerült olyan IoT eszközt kódolni, amely működik szenzorral vagy aktuátorral |
| IoT eszköz csatlakoztatása IoT Hubhoz | Sikeresen telepített egy IoT Hubot, küldött telemetriát, és fogadott parancsokat | Sikeresen telepített egy IoT Hubot, és telemetriát küldött vagy parancsokat fogadott | Nem sikerült telepíteni egy IoT Hubot, és kommunikálni vele IoT eszközről |
| Aktuátor vezérlése szerver nélküli kóddal | Sikeresen telepített egy Azure Function-t, amely telemetriai események által vezérli az eszközt | Sikeresen telepített egy Azure Function-t, amely telemetriai események által aktiválódik, de nem sikerült vezérelni az aktuátort | Nem sikerült telepíteni egy Azure Function-t |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.