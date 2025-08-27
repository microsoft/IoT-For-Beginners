<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-27T22:12:31+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "da"
}
-->
# Quizzer

Disse quizzer er for- og efterforelæsningsquizzer til IoT for Beginners-kurset på https://aka.ms/iot-beginners

## Projektopsætning

```
npm install
```

### Kompilerer og genindlæser automatisk til udvikling

```
npm run serve
```

### Kompilerer og minimerer til produktion

```
npm run build
```

### Linter og retter filer

```
npm run lint
```

### Tilpas konfiguration

Se [Konfigurationsreference](https://cli.vuejs.org/config/).

Kreditering: Tak til den oprindelige version af denne quiz-app: https://github.com/arpan45/simple-quiz-vue


## Udrulning til Azure

Her er en trin-for-trin guide til at hjælpe dig i gang:

1. Fork et GitHub-repository  
Sørg for, at din statiske webapp-kode er i dit GitHub-repository. Fork dette repository.

2. Opret en Azure Static Web App  
- Opret en [Azure-konto](http://azure.microsoft.com)  
- Gå til [Azure-portalen](https://portal.azure.com)  
- Klik på "Opret en ressource" og søg efter "Static Web App".  
- Klik på "Opret".  

3. Konfigurer den statiske webapp  
- **Grundlæggende:**  
  - Abonnement: Vælg dit Azure-abonnement.  
  - Ressourcegruppe: Opret en ny ressourcegruppe eller brug en eksisterende.  
  - Navn: Angiv et navn til din statiske webapp.  
  - Region: Vælg den region, der er tættest på dine brugere.  

- #### Implementeringsdetaljer:  
  - Kilde: Vælg "GitHub".  
  - GitHub-konto: Autoriser Azure til at få adgang til din GitHub-konto.  
  - Organisation: Vælg din GitHub-organisation.  
  - Repository: Vælg det repository, der indeholder din statiske webapp.  
  - Gren: Vælg den gren, du vil udrulle fra.  

- #### Bygningsdetaljer:  
  - Byggeforudindstillinger: Vælg det framework, din app er bygget med (f.eks. React, Angular, Vue osv.).  
  - App-placering: Angiv mappen, der indeholder din app-kode (f.eks. / hvis den er i roden).  
  - API-placering: Hvis du har en API, angiv dens placering (valgfrit).  
  - Output-placering: Angiv mappen, hvor byggeoutputtet genereres (f.eks. build eller dist).  

4. Gennemgå og opret  
Gennemgå dine indstillinger, og klik på "Opret". Azure vil opsætte de nødvendige ressourcer og oprette en GitHub Actions workflow i dit repository.

5. GitHub Actions workflow  
Azure opretter automatisk en GitHub Actions workflow-fil i dit repository (.github/workflows/azure-static-web-apps-<name>.yml). Denne workflow håndterer bygge- og udrulningsprocessen.

6. Overvåg udrulningen  
Gå til fanen "Actions" i dit GitHub-repository.  
Du bør se en workflow køre. Denne workflow vil bygge og udrulle din statiske webapp til Azure.  
Når workflowen er færdig, vil din app være live på den angivne Azure-URL.

### Eksempel på workflow-fil

Her er et eksempel på, hvordan GitHub Actions workflow-filen kan se ud:  
name: Azure Static Web Apps CI/CD  
```
on:
  push:
    branches:
      - main
  pull_request:
    types: [opened, synchronize, reopened, closed]
    branches:
      - main

jobs:
  build_and_deploy_job:
    runs-on: ubuntu-latest
    name: Build and Deploy Job
    steps:
      - uses: actions/checkout@v2
      - name: Build And Deploy
        id: builddeploy
        uses: Azure/static-web-apps-deploy@v1
        with:
          azure_static_web_apps_api_token: ${{ secrets.AZURE_STATIC_WEB_APPS_API_TOKEN }}
          repo_token: ${{ secrets.GITHUB_TOKEN }}
          action: "upload"
          app_location: "quiz-app" #App source code path
          api_location: ""API source code path optional
          output_location: "dist" #Built app content directory - optional
```

### Yderligere ressourcer  
- [Azure Static Web Apps Dokumentation](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions Dokumentation](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.