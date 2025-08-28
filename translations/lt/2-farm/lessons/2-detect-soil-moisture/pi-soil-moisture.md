<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-28T20:18:55+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "lt"
}
-->
# Matuokite dirvožemio drėgmę - Raspberry Pi

Šioje pamokos dalyje pridėsite talpinį dirvožemio drėgmės jutiklį prie Raspberry Pi ir nuskaitysite jo duomenis.

## Aparatūra

Raspberry Pi reikalingas talpinis dirvožemio drėgmės jutiklis.

Naudojamas jutiklis yra [Talpinis dirvožemio drėgmės jutiklis](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), kuris matuoja dirvožemio drėgmę aptikdamas dirvožemio talpą – savybę, kuri keičiasi priklausomai nuo drėgmės kiekio. Didėjant dirvožemio drėgmei, įtampa mažėja.

Tai yra analoginis jutiklis, todėl jis naudoja analoginį piną ir 10 bitų ADC, esantį Grove Base Hat ant Pi, kad konvertuotų įtampą į skaitmeninį signalą nuo 1 iki 1,023. Tada šis signalas perduodamas per I

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.