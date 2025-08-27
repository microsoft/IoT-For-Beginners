<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T21:32:24+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "no"
}
-->
# Send varsler med Twilio

## Instruksjoner

I koden din så langt har du bare logget avstanden til geofencen. I denne oppgaven må du legge til et varsel, enten en tekstmelding eller en e-post, når GPS-koordinatene er innenfor geofencen.

Azure Functions har mange alternativer for bindings, inkludert til tredjepartstjenester som Twilio, en kommunikasjonsplattform.

* Registrer deg for en gratis konto på [Twilio.com](https://www.twilio.com)
* Les dokumentasjonen om hvordan man binder Azure Functions til Twilio SMS på [Microsoft docs Twilio binding for Azure Functions-siden](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Les dokumentasjonen om hvordan man binder Azure Functions til Twilio SendGrid for å sende e-poster på [Microsoft docs Azure Functions SendGrid bindings-siden](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Legg til bindingen i din Functions-app for å bli varslet om GPS-koordinatene enten er innenfor eller utenfor geofencen - ikke begge.

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Konfigurer funksjonsbindingene og motta en e-post eller SMS | Klarte å konfigurere funksjonsbindingene og motta en e-post eller SMS når innenfor eller utenfor geofencen, men ikke begge | Klarte å konfigurere bindingene, men klarte ikke å sende e-post eller SMS, eller klarte kun å sende når koordinatene var både innenfor og utenfor | Klarte ikke å konfigurere bindingene og sende en e-post eller SMS |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.