<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2026-01-07T01:34:53+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "te"
}
-->
# ప్రశ్నోత్తరాలు

ఈ ప్రశ్నోత్తరాలు https://aka.ms/iot-beginners వద్ద ఉన్న IoT ఫర్ బిగినర్స్ పాఠ్యాంశానికి సంబంధించిన ప్రీ- మరియు పోస్ట్-లెక్చర్ ప్రశ్నోత్తరాలు.

## ప్రాజెక్ట్ సెటప్

```
npm install
```

### అభివృద్ధికి కంపైల్స్ చేసి హాట్-రిలోడ్ చేస్తుంది

```
npm run serve
```

### ఉత్పత్తికి కంపైల్స్ చేసి మినిఫై చేస్తుంది

```
npm run build
```

### లింట్ చేసి ఫైళ్ళను సరిచేస్తుంది

```
npm run lint
```

### కాన్ఫిగరేషన్ ఆనుకూలీకరించండి

[Configuration Reference](https://cli.vuejs.org/config/) ను చూడండి.

కృతజ్ఞతలు: ఈ ქ్విజ్ యాప్ ఒరిజినల్ వెర్షన్ కి ధన్యవాదాలు: https://github.com/arpan45/simple-quiz-vue

## Azure లో డిప్లాయ్ చేయడం

ప్రారంభించడానికి దశలవారీ గైడ్ ఇక్కడ ఉంది:

1. GitHub రెపోను ఫోర్క్ చేయండి  
మీ స్టాటిక్ వెబ్ యాప్ కోడ్ GitHub రెపోలో ఉండాలి. ఈ రెపోను ఫోర్క్ చేయండి.

2. Azure స్టాటిక్ వెబ్ యాప్ సృష్టించండి  
- [Azure ఖాతా](http://azure.microsoft.com) సృష్టించుకోండి  
- [Azure పోర్టల్](https://portal.azure.com) కు వెళ్లండి  
- “Create a resource” పై క్లిక్ చేసి “Static Web App” కోసం శోధించండి.  
- “Create” పై క్లిక్ చేయండి.

3. స్టాటిక్ వెబ్ యాప్ కాన్ఫిగర్ చేయండి  
- బేసిక్స్: సబ్స్క్రిప్షన్: మీ Azure సబ్స్క్రిప్షన్ ను ఎంచుకోండి.  
- రیسోర్స్ గ్రూప్: కొత్త రిసోర్స్ గ్రూప్ సృష్టించండి లేదా ఉన్నది ఉపయోగించండి.  
- పేరు: మీ స్టాటిక్ వెబ్ యాప్ కు ఒక పేరు ఇవ్వండి.  
- ప్రాంతం: మీ వినియోగదారులకు దగ్గరగా ఉన్న ప్రాంతాన్ని ఎంచుకోండి.

- #### డిప్లాయ్‌మెంట్ వివరాలు:  
- సోర్స్: “GitHub” ను ఎంచుకోండి.  
- GitHub అకౌంట్: Azure కు మీ GitHub అకౌంట్ యాక్సెస్ ఇజాజత ఇవ్వండి.  
- ఆర్గనైజేషన్: మీ GitHub ఆర్గనైజేషన్ ఎంచుకోండి.  
- రెపోసిటరీ: మీ స్టాటిక్ వెబ్ యాప్ ఉన్న రెపోసిటరీ ఎంచుకోండి.  
- బ్రాంచ్: మీరు డిప్లాయ్ చేయదలచుకున్న బ్రాంచ్ ఎంచుకోండి.

- #### బిల్డ్ వివరాలు:  
- బిల్డ్ ప్రీసెట్స్: మీ యాప్ ఏ ఫ్రేమ్‌వర్క్‌తో తయారవిందో ఎంచుకోండి (ఉదా: React, Angular, Vue మొదలైనవి).  
- యాప్ లొకేషన్: మీ యాప్ కోడ్ ఉన్న ఫోల్డర్‌ని పేర్కొనండి (ఉదా: మౌలిక డైరక్టరీ లో అయితే /).  
- API లొకేషన్: మీ దగ్గర API ఉన్నట్లయితే దాని లొకేషన్ (ఐచ్ఛికం) ను తెలియజేయండి.  
- ఔట్‌పుట్ లొకేషన్: బిల్డ్ అవుట్‌పుట్ ఉత్పత్తి అయ్యే ఫోల్డర్ (ఉదా: build లేదా dist).

4. సమీక్షించి సృష్టించండి  
మీ సెట్టింగ్స్ సమీక్షించి “Create” క్లిక్ చేయండి. Azure అవసరమైన వనరులను సెట్ చేసి మీ రెపోలో GitHub Actions వర్క్‌ఫ్లోని సృష్టిస్తుంది.

5. GitHub Actions వర్క్‌ఫ్లో  
Azure స్వయంచాలకంగా మీ రెపోలో (.github/workflows/azure-static-web-apps-<name>.yml) GitHub Actions వర్క్‌ఫ్లో ఫైల్ సృష్టిస్తుంది. ఈ వర్క్‌ఫ్లో బిల్డ్ మరియు డిప్లాయ్‌మెంట్ ప్రక్రియను నిర్వహిస్తుంది.

6. డిప్లాయ్‌మెంట్ ను పర్యవేక్షించండి  
మీ GitHub రెపోలో “Actions” ట్యాబ్ కు వెళ్లండి.  
ఏదైనా వర్క్‌ఫ్లో నడుస్తుండగా మీరు చూడగలుగుతారు. ఈ వర్క్‌ఫ్లో మీ స్టాటిక్ వెబ్ యాప్‌ ను Azure లో డిప్లాయ్ చేస్తుంది.  
వర్క్‌ఫ్లో పూర్తయ్యాక, మీ యాప్ ఇచ్చిన Azure URL లో లైవ్ గా ఉంటుంది.

### ఉదాహరణ వర్క్‌ఫ్లో ఫైల్

GitHub Actions వర్క్‌ఫ్లో ఫైల్ ఎలా ఉండొచ్చో ఉదాహరణ ఇక్కడ ఉంది:  
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

### అదనపు వనరులు  
- [Azure Static Web Apps Documentation](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions Documentation](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**తప్పు అనుమతించ లేదు**:  
ఈ దస్త్రాన్ని AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించాము. మేము ఖచ్చితత్వానికి ప్రయత్నించినప్పటికీ, ఆటోమేటిక్ అనువాదాలలో తప్పులు లేదా లోపాలు ఉండవచ్చు. మూలపాఠం మీ స్థానిక భాషలో ఉన్న డాక్యుమెంట్‌ను అధికారిక మూలంగా పరిగణించాలి. ముఖ్యమైన సమాచారం కోసం, నిపుణుల చేత మానవ అనువాదం చేయడం మంచిది. ఈ అనువాదం వలన ఏవైనా అపార్థాలు లేదా తప్పుదోవలకు మేము బాధ్యతాయుతులము కాదు.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->