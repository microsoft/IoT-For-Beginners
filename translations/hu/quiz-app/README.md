<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-27T22:36:07+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "hu"
}
-->
# Kvízek

Ezek a kvízek az IoT kezdőknek tananyag előtti és utáni kvízei, amely elérhető itt: https://aka.ms/iot-beginners

## Projekt beállítása

```
npm install
```

### Fordítás és automatikus újratöltés fejlesztéshez

```
npm run serve
```

### Fordítás és minifikálás éles környezethez

```
npm run build
```

### Fájlok ellenőrzése és javítása

```
npm run lint
```

### Konfiguráció testreszabása

Lásd: [Konfigurációs referencia](https://cli.vuejs.org/config/).

Köszönet: Köszönet a kvíz alkalmazás eredeti verziójáért: https://github.com/arpan45/simple-quiz-vue

## Telepítés Azure-ra

Íme egy lépésről lépésre útmutató, amely segít az indulásban:

1. Forkolj egy GitHub-tárházat  
Győződj meg róla, hogy a statikus webalkalmazásod kódja a GitHub-tárházadban van. Forkold ezt a tárházat.

2. Hozz létre egy Azure Static Web App-ot  
- Hozz létre egy [Azure fiókot](http://azure.microsoft.com)  
- Lépj be az [Azure portálra](https://portal.azure.com)  
- Kattints a „Create a resource” gombra, és keresd meg a „Static Web App” lehetőséget.  
- Kattints a „Create” gombra.

3. Konfiguráld a Static Web App-ot  
- **Alapok**:  
  - Előfizetés: Válaszd ki az Azure előfizetésedet.  
  - Erőforráscsoport: Hozz létre egy új erőforráscsoportot, vagy használd a meglévőt.  
  - Név: Adj nevet a statikus webalkalmazásodnak.  
  - Régió: Válaszd ki a felhasználóidhoz legközelebbi régiót.  

- #### Telepítési részletek:  
  - Forrás: Válaszd a „GitHub” lehetőséget.  
  - GitHub fiók: Engedélyezd az Azure számára a GitHub fiókodhoz való hozzáférést.  
  - Szervezet: Válaszd ki a GitHub szervezetedet.  
  - Tárház: Válaszd ki azt a tárházat, amely tartalmazza a statikus webalkalmazásod.  
  - Ág: Válaszd ki azt az ágat, amelyből telepíteni szeretnél.  

- #### Build részletek:  
  - Build előbeállítások: Válaszd ki azt a keretrendszert, amelyre az alkalmazásod épült (pl. React, Angular, Vue stb.).  
  - Alkalmazás helye: Add meg azt a mappát, amely az alkalmazás kódját tartalmazza (pl. /, ha a gyökérben van).  
  - API helye: Ha van API-d, add meg annak helyét (opcionális).  
  - Kimeneti hely: Add meg azt a mappát, ahol a build kimenete generálódik (pl. build vagy dist).  

4. Áttekintés és létrehozás  
Nézd át a beállításaidat, majd kattints a „Create” gombra. Az Azure beállítja a szükséges erőforrásokat, és létrehoz egy GitHub Actions munkafolyamatot a tárházadban.

5. GitHub Actions munkafolyamat  
Az Azure automatikusan létrehoz egy GitHub Actions munkafolyamat fájlt a tárházadban (.github/workflows/azure-static-web-apps-<név>.yml). Ez a munkafolyamat kezeli a build és telepítési folyamatot.

6. A telepítés figyelemmel kísérése  
Lépj a GitHub tárházad „Actions” fülére.  
Látnod kell egy futó munkafolyamatot. Ez a munkafolyamat felépíti és telepíti a statikus webalkalmazásodat az Azure-ra.  
Amint a munkafolyamat befejeződik, az alkalmazásod élő lesz az Azure által biztosított URL-en.

### Példa munkafolyamat fájl

Íme, hogyan nézhet ki egy GitHub Actions munkafolyamat fájl:
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

### További források
- [Azure Static Web Apps dokumentáció](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions dokumentáció](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.