<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-28T17:32:16+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "my"
}
-->
# မေးခွန်းများ

ဒီမေးခွန်းများဟာ IoT for Beginners သင်ခန်းစာများအတွက် သင်ခန်းစာမတိုင်မီနှင့် သင်ခန်းစာပြီးနောက် မေးခွန်းများဖြစ်ပါတယ်။ https://aka.ms/iot-beginners မှာ Curriculum ကိုကြည့်နိုင်ပါတယ်။

## Project setup

```
npm install
```

### Development အတွက် Compiles နှင့် hot-reloads

```
npm run serve
```

### Production အတွက် Compiles နှင့် minifies

```
npm run build
```

### Files များကို Lints နှင့် fixes

```
npm run lint
```

### Configuration ကို Customize လုပ်ခြင်း

[Configuration Reference](https://cli.vuejs.org/config/) ကိုကြည့်ပါ။

Credit: ဒီ quiz app ရဲ့ original version ကို ဖန်တီးသူ https://github.com/arpan45/simple-quiz-vue ကို ကျေးဇူးတင်ပါတယ်။

## Azure သို့ Deploy လုပ်ခြင်း

ဒီအဆင့်ဆင့်လမ်းညွှန်ကို အသုံးပြုပြီး စတင်နိုင်ပါပြီ-

1. GitHub Repository ကို Fork လုပ်ပါ  
သင့် static web app code ကို GitHub repository မှာရှိအောင်လုပ်ပါ။ ဒီ repository ကို Fork လုပ်ပါ။

2. Azure Static Web App တစ်ခု Create လုပ်ပါ  
- [Azure account](http://azure.microsoft.com) တစ်ခု Create လုပ်ပါ  
- [Azure portal](https://portal.azure.com) ကိုသွားပါ  
- “Create a resource” ကိုနှိပ်ပြီး “Static Web App” ကို ရှာပါ။  
- “Create” ကိုနှိပ်ပါ။

3. Static Web App ကို Configure လုပ်ပါ  
- Basics: Subscription: သင့် Azure subscription ကို ရွေးပါ။  
- Resource Group: Resource group အသစ်တစ်ခု Create လုပ်ပါ၊ ဒါမှမဟုတ် ရှိပြီးသား Resource group ကို အသုံးပြုပါ။  
- Name: သင့် static web app အတွက် နာမည်ပေးပါ။  
- Region: သင့် user များနီးစပ်ရာ Region ကို ရွေးပါ။

- #### Deployment Details:
- Source: “GitHub” ကို ရွေးပါ။  
- GitHub Account: Azure ကို သင့် GitHub account ကို access လုပ်ခွင့်ပေးပါ။  
- Organization: သင့် GitHub organization ကို ရွေးပါ။  
- Repository: သင့် static web app ရှိတဲ့ repository ကို ရွေးပါ။  
- Branch: Deploy လုပ်ချင်တဲ့ branch ကို ရွေးပါ။

- #### Build Details:
- Build Presets: သင့် app ဖန်တီးထားတဲ့ framework ကို ရွေးပါ (ဥပမာ React, Angular, Vue, စသည်တို့)။  
- App Location: သင့် app code ရှိတဲ့ folder ကို သတ်မှတ်ပါ (ဥပမာ / အကွက်မှာ root မှာရှိရင်)။  
- API Location: API ရှိရင်၊ အဲဒီ location ကို သတ်မှတ်ပါ (optional)။  
- Output Location: Build output ဖိုင်များ ရှိတဲ့ folder ကို သတ်မှတ်ပါ (ဥပမာ build သို့မဟုတ် dist)။

4. Review နှင့် Create  
သင့် settings များကို ပြန်လည်ကြည့်ရှုပြီး “Create” ကိုနှိပ်ပါ။ Azure သင့် resource များကို setup လုပ်ပြီး GitHub Actions workflow ကို သင့် repository မှာ Create လုပ်ပါမည်။

5. GitHub Actions Workflow  
Azure သင့် repository မှာ GitHub Actions workflow ဖိုင် (.github/workflows/azure-static-web-apps-<name>.yml) ကို အလိုအလျောက် Create လုပ်ပါမည်။ ဒီ workflow က build နှင့် deployment process ကို စီမံပါမည်။

6. Deployment ကို Monitor လုပ်ပါ  
GitHub repository ရဲ့ “Actions” tab ကိုသွားပါ။  
Workflow တစ်ခု run ဖြစ်နေသည်ကို တွေ့ရပါမည်။ ဒီ workflow က သင့် static web app ကို Azure သို့ build နှင့် deploy လုပ်ပါမည်။  
Workflow ပြီးဆုံးပြီးနောက် သင့် app ကို Azure URL မှာ live ဖြစ်နေပါမည်။

### Example Workflow File

GitHub Actions workflow ဖိုင်ရဲ့ ဥပမာကို အောက်မှာကြည့်နိုင်ပါတယ်-  
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

### အပိုဆောင်း Resources  
- [Azure Static Web Apps Documentation](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions Documentation](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းစာရွက်စာတမ်းကို ၎င်း၏ မူရင်းဘာသာစကားဖြင့် အာဏာတရားရှိသော အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။