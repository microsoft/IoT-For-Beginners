<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-10-11T11:18:05+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "ta"
}
-->
# கேள்விகள்

இந்த கேள்விகள் IoT for Beginners பாடத்திட்டத்தின் முன் மற்றும் பின்-வகுப்பு கேள்விகள் ஆகும். https://aka.ms/iot-beginners

## திட்ட அமைப்பு

```
npm install
```

### மேம்பாட்டிற்காக தொகுத்து, தானாக மீண்டும் ஏற்றுகிறது

```
npm run serve
```

### உற்பத்திக்காக தொகுத்து, சுருக்குகிறது

```
npm run build
```

### கோப்புகளை சரிசெய்து, பிழைகளை திருத்துகிறது

```
npm run lint
```

### அமைப்பை தனிப்பயனாக்க

[Configuration Reference](https://cli.vuejs.org/config/) ஐப் பார்க்கவும்.

கிரெடிட்ஸ்: இந்த கேள்வி பயன்பாட்டின் முதன்மை பதிப்புக்கு நன்றி: https://github.com/arpan45/simple-quiz-vue


## Azure-க்கு வெளியிடுதல்

இங்கே ஆரம்பிக்க உதவும் படிப்படியாக வழிகாட்டி உள்ளது:

1. GitHub Repository ஐ Fork செய்யவும்  
உங்கள் நிலையான வலை பயன்பாட்டு குறியீடு உங்கள் GitHub repository-யில் இருக்க வேண்டும். இந்த repository ஐ Fork செய்யவும்.

2. Azure Static Web App ஐ உருவாக்கவும்  
- [Azure account](http://azure.microsoft.com) ஐ உருவாக்கவும்  
- [Azure portal](https://portal.azure.com) க்கு செல்லவும்  
- “Create a resource” ஐ கிளிக் செய்து “Static Web App” ஐ தேடவும்.  
- “Create” ஐ கிளிக் செய்யவும்.  

3. Static Web App ஐ அமைக்கவும்  
- அடிப்படைகள்:  
  - Subscription: உங்கள் Azure சந்தாவைத் தேர்ந்தெடுக்கவும்.  
  - Resource Group: புதிய resource group ஐ உருவாக்கவும் அல்லது ஏற்கனவே உள்ள ஒன்றைப் பயன்படுத்தவும்.  
  - Name: உங்கள் Static Web App-க்கு ஒரு பெயரை வழங்கவும்.  
  - Region: உங்கள் பயனர்களுக்கு அருகிலுள்ள பகுதியைத் தேர்ந்தெடுக்கவும்.  

- #### Deployment விவரங்கள்:  
  - Source: “GitHub” ஐத் தேர்ந்தெடுக்கவும்.  
  - GitHub Account: Azure-க்கு உங்கள் GitHub கணக்கை அணுக அனுமதி அளிக்கவும்.  
  - Organization: உங்கள் GitHub அமைப்பைத் தேர்ந்தெடுக்கவும்.  
  - Repository: உங்கள் Static Web App உள்ள repository ஐத் தேர்ந்தெடுக்கவும்.  
  - Branch: வெளியிட விரும்பும் branch ஐத் தேர்ந்தெடுக்கவும்.  

- #### Build விவரங்கள்:  
  - Build Presets: உங்கள் பயன்பாடு உருவாக்கப்பட்ட framework ஐத் தேர்ந்தெடுக்கவும் (எ.கா., React, Angular, Vue, முதலியவை).  
  - App Location: உங்கள் பயன்பாட்டு குறியீடு உள்ள கோப்புறையை குறிப்பிடவும் (எ.கா., / இது root-ல் இருந்தால்).  
  - API Location: API இருந்தால், அதன் இடத்தை குறிப்பிடவும் (விருப்பம்).  
  - Output Location: build output உருவாக்கப்படும் கோப்புறையை குறிப்பிடவும் (எ.கா., build அல்லது dist).  

4. Review மற்றும் Create  
உங்கள் அமைப்புகளை மதிப்பாய்வு செய்து “Create” ஐ கிளிக் செய்யவும். Azure தேவையான வளங்களை அமைத்து, உங்கள் repository-யில் GitHub Actions workflow ஐ உருவாக்கும்.  

5. GitHub Actions Workflow  
Azure உங்கள் repository-யில் (.github/workflows/azure-static-web-apps-<name>.yml) GitHub Actions workflow கோப்பை தானாக உருவாக்கும். இந்த workflow build மற்றும் deployment செயல்முறையை நிர்வகிக்கும்.  

6. Deployment ஐ கண்காணிக்கவும்  
உங்கள் GitHub repository-யில் “Actions” tab-க்கு செல்லவும்.  
நீங்கள் ஒரு workflow இயங்குவதைப் பார்க்க வேண்டும். இந்த workflow உங்கள் Static Web App ஐ Azure-க்கு build செய்து வெளியிடும்.  
Workflow முடிந்தவுடன், உங்கள் பயன்பாடு வழங்கப்பட்ட Azure URL-ல் நேரடியாக இருக்கும்.  

### உதாரண Workflow கோப்பு

GitHub Actions workflow கோப்பு எப்படி இருக்கும் என்பதற்கான உதாரணம்:  
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
  
### கூடுதல் வளங்கள்  
- [Azure Static Web Apps Documentation](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions Documentation](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியக்க மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை தயவுசெய்து கவனத்தில் கொள்ளுங்கள். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.