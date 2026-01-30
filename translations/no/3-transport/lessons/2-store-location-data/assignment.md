# Undersøk funksjonsbindinger

## Instruksjoner

Funksjonsbindinger lar koden din lagre blobs i blob-lagring ved å returnere dem fra `main`-funksjonen. Azure Storage-kontoen, samlingen og andre detaljer er konfigurert i `function.json`-filen.

Når du arbeider med Azure eller andre Microsoft-teknologier, er den beste informasjonskilden [Microsoft-dokumentasjonen på docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). I denne oppgaven må du lese dokumentasjonen om Azure Functions-bindinger for å finne ut hvordan du setter opp utdata-bindingen.

Noen sider du kan se på for å komme i gang er:

* [Azure Functions triggere og bindinger – konsepter](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob-lagringsbindinger for Azure Functions – oversikt](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob-lagrings utdata-binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Vurderingskriterier

| Kriterier | Eksemplarisk | Tilfredsstillende | Trenger forbedring |
| --------- | ------------ | ----------------- | ------------------ |
| Konfigurere blob-lagrings utdata-binding | Klarte å konfigurere utdata-bindingen, returnere bloben og få den lagret i blob-lagring | Klarte å konfigurere utdata-bindingen, eller returnere bloben, men klarte ikke å få den lagret i blob-lagring | Klarte ikke å konfigurere utdata-bindingen |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.