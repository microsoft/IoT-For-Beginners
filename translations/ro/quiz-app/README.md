<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-28T10:41:53+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "ro"
}
-->
# Chestionare

Aceste chestionare sunt cele de dinainte și după lecții pentru curriculumul IoT pentru Începători la https://aka.ms/iot-beginners

## Configurarea proiectului

```
npm install
```

### Compilează și reîncarcă automat pentru dezvoltare

```
npm run serve
```

### Compilează și minimizează pentru producție

```
npm run build
```

### Verifică și corectează fișierele

```
npm run lint
```

### Personalizează configurația

Vezi [Referința de Configurare](https://cli.vuejs.org/config/).

Credite: Mulțumiri pentru versiunea originală a acestei aplicații de chestionare: https://github.com/arpan45/simple-quiz-vue


## Implementarea pe Azure

Iată un ghid pas cu pas pentru a te ajuta să începi:

1. Clonează un Repository GitHub
Asigură-te că codul aplicației tale web statice se află în repository-ul tău GitHub. Clonează acest repository.

2. Creează o Aplicație Web Statică pe Azure
- Creează un [cont Azure](http://azure.microsoft.com)
- Accesează [portalul Azure](https://portal.azure.com) 
- Dă clic pe „Create a resource” și caută „Static Web App”.
- Dă clic pe „Create”.

3. Configurează Aplicația Web Statică
- Bazele: Subscription: Selectează abonamentul tău Azure.
- Resource Group: Creează un nou grup de resurse sau folosește unul existent.
- Name: Oferă un nume pentru aplicația ta web statică.
- Region: Alege regiunea cea mai apropiată de utilizatorii tăi.

- #### Detalii de Implementare:
- Source: Selectează „GitHub”.
- GitHub Account: Autorizează Azure să acceseze contul tău GitHub.
- Organization: Selectează organizația ta GitHub.
- Repository: Alege repository-ul care conține aplicația ta web statică.
- Branch: Selectează branch-ul din care vrei să implementezi.

- #### Detalii de Build:
- Build Presets: Alege framework-ul cu care este construită aplicația ta (ex.: React, Angular, Vue, etc.).
- App Location: Specifică folderul care conține codul aplicației tale (ex.: / dacă este în root).
- API Location: Dacă ai un API, specifică locația acestuia (opțional).
- Output Location: Specifică folderul unde este generat output-ul build-ului (ex.: build sau dist).

4. Revizuiește și Creează
Revizuiește setările tale și dă clic pe „Create”. Azure va configura resursele necesare și va crea un workflow GitHub Actions în repository-ul tău.

5. Workflow GitHub Actions
Azure va crea automat un fișier workflow GitHub Actions în repository-ul tău (.github/workflows/azure-static-web-apps-<name>.yml). Acest workflow va gestiona procesul de build și implementare.

6. Monitorizează Implementarea
Accesează tab-ul „Actions” din repository-ul tău GitHub.
Ar trebui să vezi un workflow în desfășurare. Acest workflow va construi și implementa aplicația ta web statică pe Azure.
După ce workflow-ul se finalizează, aplicația ta va fi live pe URL-ul furnizat de Azure.

### Exemplu de Fișier Workflow

Iată un exemplu de cum ar putea arăta fișierul workflow GitHub Actions:
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

### Resurse Suplimentare
- [Documentația Azure Static Web Apps](https://learn.microsoft.com/azure/static-web-apps/getting-started)
- [Documentația GitHub Actions](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.