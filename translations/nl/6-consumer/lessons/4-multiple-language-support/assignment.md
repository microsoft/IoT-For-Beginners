<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T22:16:30+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "nl"
}
-->
# Bouw een universele vertaler

## Instructies

Een universele vertaler is een apparaat dat kan vertalen tussen meerdere talen, waardoor mensen die verschillende talen spreken met elkaar kunnen communiceren. Gebruik wat je hebt geleerd in de afgelopen lessen om een universele vertaler te bouwen met behulp van 2 IoT-apparaten.

> Als je geen 2 apparaten hebt, volg dan de stappen in de vorige lessen om een virtueel IoT-apparaat in te stellen als een van de IoT-apparaten.

Je moet één apparaat configureren voor de ene taal en het andere voor een andere taal. Elk apparaat moet spraak accepteren, dit omzetten naar tekst, het via IoT Hub en een Functions-app naar het andere apparaat sturen, het vertalen en de vertaalde spraak afspelen.

> 💁 Tip: Wanneer je de spraak van het ene apparaat naar het andere stuurt, stuur dan ook de taal waarin het is, zodat het gemakkelijker te vertalen is. Je kunt zelfs elk apparaat laten registreren via IoT Hub en een Functions-app, waarbij de ondersteunde taal wordt doorgegeven om in Azure Storage te worden opgeslagen. Vervolgens kun je een Functions-app gebruiken om de vertalingen uit te voeren en de vertaalde tekst naar het IoT-apparaat te sturen.

## Rubric

| Criteria | Uitmuntend | Voldoende | Verbetering nodig |
| -------- | ---------- | --------- | ----------------- |
| Maak een universele vertaler | Was in staat om een universele vertaler te bouwen, waarbij spraak gedetecteerd door het ene apparaat werd omgezet in spraak afgespeeld door een ander apparaat in een andere taal | Was in staat om enkele componenten werkend te krijgen, zoals het vastleggen van spraak of vertalen, maar kon geen end-to-end oplossing bouwen | Was niet in staat om enige onderdelen van een werkende universele vertaler te bouwen |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.