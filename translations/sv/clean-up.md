<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:22:08+00:00",
  "source_file": "clean-up.md",
  "language_code": "sv"
}
-->
# Rensa upp ditt projekt

När du har avslutat varje projekt är det bra att ta bort dina molnresurser.

Under lektionerna för varje projekt kan du ha skapat några av följande:

* En resursgrupp
* En IoT Hub
* IoT-enhetsregistreringar
* Ett lagringskonto
* En Functions App
* Ett Azure Maps-konto
* Ett projekt för anpassad vision
* Ett Azure Container Registry
* En resurs för kognitiva tjänster

De flesta av dessa resurser har ingen kostnad – antingen är de helt gratis, eller så använder du en gratisnivå. För tjänster som kräver en betald nivå har du använt dem på en nivå som ingår i gratisutrymmet, eller som bara kostar några ören.

Även med de relativt låga kostnaderna är det värt att ta bort dessa resurser när du är klar. Du kan till exempel bara ha en IoT Hub som använder gratisnivån, så om du vill skapa en till måste du använda en betald nivå.

Alla dina tjänster skapades inom resursgrupper, vilket gör det enklare att hantera. Du kan ta bort resursgruppen, och alla tjänster i den resursgruppen kommer att tas bort samtidigt.

För att ta bort resursgruppen, kör följande kommando i din terminal eller kommandotolk:

```sh
az group delete --name <resource-group-name>
```

Ersätt `<resource-group-name>` med namnet på den resursgrupp du är intresserad av.

En bekräftelse kommer att visas:

```output
Are you sure you want to perform this operation? (y/n): 
```

Skriv `y` för att bekräfta och ta bort resursgruppen.

Det kommer att ta en stund att ta bort alla tjänster.

> 💁 Du kan läsa mer om att ta bort resursgrupper i [dokumentationen om borttagning av resursgrupper och resurser för Azure Resource Manager på Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.