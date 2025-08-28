<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-28T13:25:57+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "hr"
}
-->
# Slanje obavijesti pomoću Twilio

## Upute

U svom kodu do sada ste samo bilježili udaljenost do geoograde. U ovom zadatku trebate dodati obavijest, bilo putem SMS poruke ili e-pošte, kada su GPS koordinate unutar geoograde.

Azure Functions nudi mnoge opcije za povezivanje, uključujući i usluge trećih strana poput Twilio, platforme za komunikaciju.

* Registrirajte se za besplatan račun na [Twilio.com](https://www.twilio.com)
* Pročitajte dokumentaciju o povezivanju Azure Functions s Twilio SMS-om na [Microsoft docs stranici o Twilio povezivanju za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Pročitajte dokumentaciju o povezivanju Azure Functions s Twilio SendGrid-om za slanje e-pošte na [Microsoft docs stranici o SendGrid povezivanju za Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Dodajte povezivanje svojoj Functions aplikaciji kako biste bili obaviješteni o GPS koordinatama unutar ili izvan geoograde - ali ne za oba slučaja.

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | -------- | --------------- | -------------------- |
| Konfiguracija povezivanja funkcija i primanje e-pošte ili SMS-a | Uspješno konfigurirano povezivanje funkcija i primljena e-pošta ili SMS kada su koordinate unutar ili izvan geoograde, ali ne za oba slučaja | Uspješno konfigurirano povezivanje, ali nije bilo moguće poslati e-poštu ili SMS, ili je bilo moguće poslati samo kada su koordinate bile i unutar i izvan geoograde | Nije bilo moguće konfigurirati povezivanje i poslati e-poštu ili SMS |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.