<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2026-01-07T01:35:28+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "ml"
}
-->
# ക്വിസുകൾ

ഈ ക്വിസുകൾ https://aka.ms/iot-beginners-ൽ ഉള്ള IoT for Beginners പാഠ്യപദ്ധതിക്കായുള്ള പ്രീ-യും പോസ്റ്റ്-ലെക്ചർ ക്വിസുകളാണ്

## പ്രോജക്ട് സെറ്റ്‌അപ്പ്

```
npm install
```

### വികസനത്തിനായി കമ്മയുചെയ്ത് ഹോട്ട്-റീലോഡ് ചെയ്യുന്നു

```
npm run serve
```

### ഉത്പാദനത്തിനായി കമ്മയുചെയ്തു മിനിഫൈ ചെയ്യുന്നു

```
npm run build
```

### ഫയലുകൾ ലിന്റ് ചെയ്ത് പരിഹരിക്കുന്നു

```
npm run lint
```

### കോൺഫിഗറേഷൻ ഇഷ്ടാനുസൃതമാക്കുക

[Configuration Reference](https://cli.vuejs.org/config/) കാണുക.

ക്രെഡിറ്റുകൾ: ഈ ക്വിസ് ആപ്പിന്റെ മേജ്ജ അഭിപ്രായത്തിന് നന്ദി: https://github.com/arpan45/simple-quiz-vue


## അസ്യൂറിലേക്ക് ഡിപ്ലോയ് ചെയ്യുന്നു

തുടക്കാൻ സഹായിക്കുന്ന ഒരു ഘട്ടം-ഘട്ടത്തിലായുള്ള ഗൈഡ് ഇവിടെ:

1. ഒരു GitHub റീപോസിറ്ററി ഫോർക്ക് ചെയ്യുക
നിങ്ങളുടെ സ്റ്റാറ്റിക് വെബ് ആപ്പ് കോഡ് നിങ്ങളുടെ GitHub റീപോസിറ്ററിയിൽ ഉണ്ടെന്ന് ഉറപ്പാക്കുക. ഈ റീപോസിറ്ററി ഫോർക്ക് ചെയ്യുക.

2. ഒരു Azure Static Web App സൃഷ്ടിക്കുക
- ഒരു [Azure അക്കൗണ്ട്](http://azure.microsoft.com) സൃഷ്ടിക്കുക
- [Azure പോർട്ടൽ](https://portal.azure.com)ൽ പോകുക
- “Create a resource” ബട്ടൺ ക്ലിക്ക് ചെയ്ത് “Static Web App” തിരയുക.
- “Create” ക്ലിക്ക് ചെയ്യുക.

3. സ്റ്റാറ്റിക് വെബ് ആപ്പ് കോൺഫിഗർ ചെയ്യുക
- അടിസ്ഥാനങ്ങൾ: സബ്സ്ക്രിപ്ഷൻ: നിങ്ങളുടെ Azure സബ്സ്ക്രിപ്ഷൻ തിരഞ്ഞെടുക്കുക.
- റിസോഴ്സ് ഗ്രൂപ്പ്: പുതിയൊരു റിസോഴ്സ് ഗ്രൂപ്പ് സൃഷ്ടിക്കുകയോ ഉള്ളതായി ഉപയോഗിക്കുകയോ ചെയ്യുക.
- പേര്: നിങ്ങളുടെ സ്റ്റാറ്റിക് വെബ് ആപ്പിന് പേര് നൽകുക.
- പ്രദേശം: നിങ്ങളുടെ ഉപയോക്താക്കൾക്കു ഏറ്റവും സമീപമുള്ള പ്രദേശം തിരഞ്ഞെടുക്കുക.

- #### ഡിപ്ലോയ്‌മെന്റ് വിശദാംശങ്ങൾ:
- സൂത്രധാരൻ: “GitHub” തിരഞ്ഞെടുക്കുക.
- GitHub അക്കൗണ്ട്: Azure-യ്ക്ക് നിങ്ങളുടെ GitHub അക്കൗണ്ടിൽ പ്രവേശനാനുമതി നൽകുക.
- സംഘടന: നിങ്ങളുടെ GitHub സംഘടന തിരഞ്ഞെടുക്കുക.
- റീപോസിറ്ററി: നിങ്ങളുടെ സ്റ്റാറ്റിക് വെബ് ആപ്പ് ഉൾക്കൊണ്ട റീപോസിറ്ററി തിരഞ്ഞെടുക്കുക.
- ബ്രാഞ്ച്: ഡിപ്ലോയ് ചെയ്യേണ്ട ബ്രാഞ്ച് തിരഞ്ഞെടുക്കുക.

- #### ബിൽഡ് വിശദാംശങ്ങൾ:
- ബിൽഡ് പ്രീസെറ്റ്സ്: നിങ്ങളുടെ ആപ്പ് നിർമ്മിച്ച ഫ്രെയിംവർക്കം തിരഞ്ഞെടുക്കുക (ഉദാ., React, Angular, Vue തുടങ്ങിയവ).
- ആപ്പ് സ്ഥലം: നിങ്ങളുടെ ആപ്പ് കോഡ് അടങ്ങിയ ഫോൾഡർ സ്പെസിഫൈ ചെയ്യുക (ഉദാ., അത് റൂട്ട് ആണ് എങ്കിൽ /).
- API സ്ഥലം: API ഉണ്ടെങ്കിൽ അതിന്റെ സ്ഥലം സ്പെസിഫൈ ചെയ്യുക (ഐച്ഛികം).
- ഔട്ട്പുട്ട് സ്ഥലം: ബിൽഡ് ഔട്ട്പുട്ട് വരുന്നതായ ഫോൾഡർ സ്പെസിഫൈ ചെയ്യുക (ഉദാ., build അല്ലെങ്കിൽ dist).

4. അവലോകനം ചെയ്ത് സൃഷ്ടിക്കുക
നിങ്ങളുടെ സജ്ജീകരണങ്ങൾ പരിശോധിച്ച് “Create” ക്ലിക്കുക. Azure ആവശ്യമായ റിസോഴ്‌സുകൾ സജ്ജമാക്കിയെടുത്ത് GitHub Actions വർക്ക്‌ഫ്ലോ റീപോസിറ്ററിയിൽ സൃഷ്ടിക്കും.

5. GitHub Actions Workflow
Azure ഓട്ടോമാറ്റിക്കായി GitHub Actions workflow ഫയൽ നിങ്ങളുടെ റീപോസിറ്ററിയിൽ സൃഷ്ടിക്കും (.github/workflows/azure-static-web-apps-<name>.yml). ഈ workflow ബിൽഡ്, ഡിപ്ലോയ്‌മെന്റ് പ്രക്രിയ കൈകാര്യം ചെയ്യും.

6. ഡിപ്ലോയ്‌മെന്റ് നിരീക്ഷിക്കുക
നിങ്ങളുടെ GitHub റീപോസിറ്ററിയിലെ “Actions” ടാബിലേക്ക് പോകുക.
ഒരു workflow പ്രവർത്തിക്കുന്നതായി കാണുകയും ചെയ്യും. ഈ workflow നിങ്ങളുടെ സ്റ്റാറ്റിക് വെബ് ആപ്പ് Azure-യിൽ ബിൽഡ് ചെയ്ത് ഡിപ്ലോയ് ചെയ്യും.
Workflow പൂർത്തിയായശേഷം, നൽകപ്പെട്ട Azure URL-ൽ നിങ്ങളുടെ ആപ്പ് ലൈവ് ആയിരിക്കും.

### ഉദാഹരണ വർക്ക്‌ഫ്ലോ ഫയൽ

GitHub Actions workflow ഫയൽ എങ്ങനെയാകാമെന്ന് ഒരു ഉദാഹരണം ഇവിടെ:
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

### അധിക വనറുകൾ
- [Azure Static Web Apps ഡോക്യുമെൻറ്റേഷൻ](https://learn.microsoft.com/azure/static-web-apps/getting-started)
- [GitHub Actions ഡോക്യുമെൻറ്റേഷൻ](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**വിവരണം**:  
ഈ രേഖ AI വിവർത്തന സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് വിവർത്തനം ചെയ്തതാണ്. ഞങ്ങൾ ശുദ്ധതയ്ക്കായി ശ്രമിക്കുന്നതിനിട്ടും, യാന്ത്രിക വിവർത്തനങ്ങളിൽ പിശകുകൾ അല്ലെങ്കിൽ അസത്യതകൾ ഉണ്ടായിരിക്കാമെന്ന点 ശ്രദ്ധിക്കുക. സ്വഭാവഭാഷയിലെ അസൽ രേഖ ആയിട്ടാണ് അധികാരമുള്ള സ്രോതസ്സ് എന്നറിയുക. നിർണായകമായ വിവരങ്ങൾക്ക് പ്രൊഫഷണൽ മാനവ വിവർത്തനം ശുപാർശ ചെയ്യുന്നു. ഈ വിവർത്തനത്തെ ഉപയോഗിച്ച് ഉണ്ടാകുന്ന ഏത് തെറ്റിദ്ധാരണകൾക്കും ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->