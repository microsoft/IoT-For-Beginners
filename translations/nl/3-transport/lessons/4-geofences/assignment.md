<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T22:48:51+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "nl"
}
-->
# Verstuur meldingen met Twilio

## Instructies

In je code tot nu toe heb je alleen de afstand tot de geofence gelogd. In deze opdracht moet je een melding toevoegen, bijvoorbeeld een sms of een e-mail, wanneer de GPS-coördinaten zich binnen de geofence bevinden.

Azure Functions biedt veel opties voor bindings, waaronder naar externe diensten zoals Twilio, een communicatieplatform.

* Maak een gratis account aan op [Twilio.com](https://www.twilio.com)
* Lees de documentatie over het koppelen van Azure Functions aan Twilio SMS op de [Microsoft docs Twilio binding voor Azure Functions pagina](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lees de documentatie over het koppelen van Azure Functions aan Twilio SendGrid om e-mails te versturen op de [Microsoft docs Azure Functions SendGrid bindings pagina](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Voeg de binding toe aan je Functions-app om meldingen te ontvangen wanneer de GPS-coördinaten zich binnen of buiten de geofence bevinden - niet beide.

## Rubriek

| Criteria | Uitmuntend | Voldoende | Verbetering nodig |
| -------- | ---------- | --------- | ----------------- |
| Configureer de function bindings en ontvang een e-mail of sms | Was in staat om de function bindings te configureren en een e-mail of sms te ontvangen wanneer binnen of buiten de geofence, maar niet beide | Was in staat om de bindings te configureren maar kon geen e-mail of sms versturen, of kon alleen versturen wanneer de coördinaten zowel binnen als buiten waren | Was niet in staat om de bindings te configureren en een e-mail of sms te versturen |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.