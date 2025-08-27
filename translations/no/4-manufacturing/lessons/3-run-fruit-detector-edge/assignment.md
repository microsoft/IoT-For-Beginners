<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:38:51+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "no"
}
-->
# Kjør andre tjenester på kanten

## Instruksjoner

Det er ikke bare bildegjenkjenningsmodeller som kan kjøres på kanten; alt som kan pakkes inn i en container kan distribueres til en IoT Edge-enhet. Serverløs kode som kjører som Azure Functions, slik som triggerne du har opprettet i tidligere leksjoner, kan kjøres i containere og dermed på IoT Edge.

Velg en av de tidligere leksjonene og prøv å kjøre Azure Functions-appen i en IoT Edge-container. Du finner en veiledning som viser hvordan du gjør dette ved å bruke et annet Functions-app-prosjekt i [Opplæring: Distribuer Azure Functions som IoT Edge-moduler på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Vurderingskriterier

| Kriterier | Eksemplarisk | Tilfredsstillende | Trenger forbedring |
| --------- | ------------ | ----------------- | ------------------ |
| Distribuer en Azure Functions-app til IoT Edge | Klarte å distribuere en Azure Functions-app til IoT Edge og bruke den med en IoT-enhet for å kjøre en trigger fra IoT-data | Klarte å distribuere en Functions-app til IoT Edge, men klarte ikke å få triggeren til å utløses | Klarte ikke å distribuere en Functions-app til IoT Edge |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.