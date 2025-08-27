<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T21:48:40+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "hu"
}
-->
# Értesítések küldése Twilio segítségével

## Útmutató

A kódodban eddig csak a geokerítéshez mért távolságot naplóztad. Ebben a feladatban értesítést kell hozzáadnod, akár szöveges üzenet, akár e-mail formájában, amikor a GPS koordináták a geokerítésen belül vannak.

Az Azure Functions számos lehetőséget kínál a kötéshez, beleértve harmadik fél szolgáltatásait, például a Twilio-t, egy kommunikációs platformot.

* Regisztrálj egy ingyenes fiókot a [Twilio.com](https://www.twilio.com) oldalon.
* Olvasd el az Azure Functions Twilio SMS kötéséről szóló dokumentációt a [Microsoft docs Twilio binding for Azure Functions oldalán](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Olvasd el az Azure Functions Twilio SendGrid kötéséről szóló dokumentációt e-mailek küldéséhez a [Microsoft docs Azure Functions SendGrid bindings oldalán](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Add hozzá a kötést a Functions alkalmazásodhoz, hogy értesítést kapj a GPS koordinátákról, amelyek a geokerítésen belül vagy kívül vannak - de ne mindkettőről.

## Értékelési szempontok

| Kritérium | Kiemelkedő | Megfelelő | Fejlesztésre szorul |
| --------- | ---------- | --------- | ------------------- |
| A funkciók kötéseinek konfigurálása és e-mail vagy SMS fogadása | Sikeresen konfigurálta a funkciók kötéseit, és kapott e-mailt vagy SMS-t, amikor a koordináták a geokerítésen belül vagy kívül voltak, de nem mindkettő esetén | Sikeresen konfigurálta a kötéseket, de nem tudott e-mailt vagy SMS-t küldeni, vagy csak akkor tudott küldeni, amikor a koordináták mind a geokerítésen belül, mind kívül voltak | Nem sikerült konfigurálni a kötéseket és e-mailt vagy SMS-t küldeni |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.