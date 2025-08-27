<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T21:32:06+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "sv"
}
-->
# Skicka aviseringar med Twilio

## Instruktioner

I din kod hittills har du bara loggat avståndet till geofencen. I denna uppgift behöver du lägga till en avisering, antingen ett textmeddelande eller ett e-postmeddelande, när GPS-koordinaterna befinner sig inom geofencen.

Azure Functions har många alternativ för bindningar, inklusive till tredjepartstjänster som Twilio, en kommunikationsplattform.

* Registrera ett gratis konto på [Twilio.com](https://www.twilio.com)
* Läs dokumentationen om hur man binder Azure Functions till Twilio SMS på [Microsofts dokumentsida för Twilio-bindning för Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Läs dokumentationen om hur man binder Azure Functions till Twilio SendGrid för att skicka e-post på [Microsofts dokumentsida för Azure Functions SendGrid-bindningar](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Lägg till bindningen till din Functions-app för att bli notifierad om GPS-koordinaterna är antingen inom eller utanför geofencen – inte båda.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Konfigurera funktionens bindningar och ta emot ett e-postmeddelande eller SMS | Kunde konfigurera funktionens bindningar och ta emot ett e-postmeddelande eller SMS när koordinaterna var inom eller utanför geofencen, men inte båda | Kunde konfigurera bindningarna men kunde inte skicka e-post eller SMS, eller kunde bara skicka när koordinaterna var både inom och utanför | Kunde inte konfigurera bindningarna och skicka ett e-postmeddelande eller SMS |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.