<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T21:32:16+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "da"
}
-->
# Send notifikationer ved hjælp af Twilio

## Instruktioner

I din kode indtil videre har du kun logget afstanden til geofencen. I denne opgave skal du tilføje en notifikation, enten en tekstbesked eller en e-mail, når GPS-koordinaterne er inden for geofencen.

Azure Functions har mange muligheder for bindings, herunder til tredjepartstjenester som Twilio, en kommunikationsplatform.

* Opret en gratis konto på [Twilio.com](https://www.twilio.com)
* Læs dokumentationen om at binde Azure Functions til Twilio SMS på [Microsoft docs Twilio binding for Azure Functions-siden](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Læs dokumentationen om at binde Azure Functions til Twilio SendGrid for at sende e-mails på [Microsoft docs Azure Functions SendGrid bindings-siden](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Tilføj bindingen til din Functions-app for at blive notificeret om GPS-koordinater enten inden for eller uden for geofencen - ikke begge dele.

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkeligt | Kræver forbedring |
| --------- | ----------- | -------------- | ----------------- |
| Konfigurer bindings for funktioner og modtag en e-mail eller SMS | Kunne konfigurere bindings for funktioner og modtage en e-mail eller SMS, når koordinaterne er inden for eller uden for geofencen, men ikke begge dele | Kunne konfigurere bindings, men kunne ikke sende e-mail eller SMS, eller kunne kun sende, når koordinaterne var både inden for og uden for geofencen | Kunne ikke konfigurere bindings og sende en e-mail eller SMS |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.