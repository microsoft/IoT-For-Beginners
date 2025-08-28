<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-28T14:19:35+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "sr"
}
-->
# Квизови

Ови квизови су предавања пре и после лекција у оквиру наставног плана и програма IoT за почетнике на https://aka.ms/iot-beginners

## Подешавање пројекта

```
npm install
```

### Компилација и аутоматско освежавање за развој

```
npm run serve
```

### Компилација и минимизација за продукцију

```
npm run build
```

### Провера и исправљање датотека

```
npm run lint
```

### Прилагођавање конфигурације

Погледајте [Референцу за конфигурацију](https://cli.vuejs.org/config/).

Заслуге: Захваљујемо се оригиналној верзији ове апликације за квиз: https://github.com/arpan45/simple-quiz-vue

## Деплојовање на Azure

Ево корак-по-корак водича који ће вам помоћи да започнете:

1. Форкујте GitHub репозиторијум  
Уверите се да је ваш код за статичну веб апликацију у вашем GitHub репозиторијуму. Форкујте овај репозиторијум.

2. Креирајте Azure статичну веб апликацију  
- Направите [Azure налог](http://azure.microsoft.com)  
- Идите на [Azure портал](https://portal.azure.com)  
- Кликните на „Create a resource“ и потражите „Static Web App“.  
- Кликните „Create“.  

3. Конфигуришите статичну веб апликацију  
- Основно:  
  - Subscription: Изаберите вашу Azure претплату.  
  - Resource Group: Креирајте нову групу ресурса или користите постојећу.  
  - Name: Унесите назив за вашу статичну веб апликацију.  
  - Region: Изаберите регион најближи вашим корисницима.  

- #### Детаљи о деплојовању:  
  - Source: Изаберите „GitHub“.  
  - GitHub Account: Овластите Azure да приступи вашем GitHub налогу.  
  - Organization: Изаберите вашу GitHub организацију.  
  - Repository: Изаберите репозиторијум који садржи вашу статичну веб апликацију.  
  - Branch: Изаберите грану са које желите да деплојујете.  

- #### Детаљи о изградњи:  
  - Build Presets: Изаберите оквир у коме је ваша апликација направљена (нпр. React, Angular, Vue, итд.).  
  - App Location: Наведите фасциклу која садржи код ваше апликације (нпр. / ако је у корену).  
  - API Location: Ако имате API, наведите његову локацију (опционо).  
  - Output Location: Наведите фасциклу у којој се генерише излаз изградње (нпр. build или dist).  

4. Преглед и креирање  
Прегледајте ваша подешавања и кликните „Create“. Azure ће подесити неопходне ресурсе и креирати GitHub Actions workflow у вашем репозиторијуму.

5. GitHub Actions Workflow  
Azure ће аутоматски креирати GitHub Actions workflow датотеку у вашем репозиторијуму (.github/workflows/azure-static-web-apps-<name>.yml). Овај workflow ће управљати процесом изградње и деплојовања.

6. Праћење деплојовања  
Идите на картицу „Actions“ у вашем GitHub репозиторијуму.  
Требало би да видите workflow који се извршава. Овај workflow ће изградити и деплојовати вашу статичну веб апликацију на Azure.  
Када workflow буде завршен, ваша апликација ће бити доступна на обезбеђеном Azure URL-у.

### Пример датотеке за Workflow

Ево примера како би GitHub Actions workflow датотека могла изгледати:  
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

### Додатни ресурси  
- [Документација за Azure статичне веб апликације](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [Документација за GitHub Actions](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако тежимо тачности, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не сносимо одговорност за било каква неспоразумевања или погрешна тумачења која могу произаћи из коришћења овог превода.