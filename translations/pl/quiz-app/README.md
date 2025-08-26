<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-26T07:37:27+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "pl"
}
-->
# Quizy

Te quizy to quizy przed i po wykładach w ramach programu nauczania IoT dla Początkujących dostępnego na https://aka.ms/iot-beginners

## Konfiguracja projektu

```
npm install
```

### Kompilacja i automatyczne przeładowanie podczas rozwoju

```
npm run serve
```

### Kompilacja i minimalizacja dla produkcji

```
npm run build
```

### Lintowanie i naprawa plików

```
npm run lint
```

### Dostosowanie konfiguracji

Zobacz [Odnośnik do konfiguracji](https://cli.vuejs.org/config/).

Podziękowania: Podziękowania dla twórców oryginalnej wersji tej aplikacji quizowej: https://github.com/arpan45/simple-quiz-vue


## Wdrażanie na platformie Azure

Oto przewodnik krok po kroku, który pomoże Ci zacząć:

1. Sforkuj repozytorium GitHub  
Upewnij się, że kod Twojej aplikacji statycznej znajduje się w Twoim repozytorium GitHub. Sforkuj to repozytorium.

2. Utwórz statyczną aplikację internetową na platformie Azure  
- Załóż [konto Azure](http://azure.microsoft.com)  
- Przejdź do [portalu Azure](https://portal.azure.com)  
- Kliknij „Utwórz zasób” i wyszukaj „Static Web App”.  
- Kliknij „Utwórz”.

3. Skonfiguruj statyczną aplikację internetową  
- Podstawy: Subskrypcja: Wybierz swoją subskrypcję Azure.  
- Grupa zasobów: Utwórz nową grupę zasobów lub użyj istniejącej.  
- Nazwa: Podaj nazwę dla swojej statycznej aplikacji internetowej.  
- Region: Wybierz region najbliższy Twoim użytkownikom.

- #### Szczegóły wdrożenia:  
- Źródło: Wybierz „GitHub”.  
- Konto GitHub: Autoryzuj Azure do uzyskania dostępu do Twojego konta GitHub.  
- Organizacja: Wybierz swoją organizację GitHub.  
- Repozytorium: Wybierz repozytorium zawierające Twoją statyczną aplikację internetową.  
- Gałąź: Wybierz gałąź, z której chcesz wdrożyć.

- #### Szczegóły kompilacji:  
- Presety kompilacji: Wybierz framework, na którym zbudowana jest Twoja aplikacja (np. React, Angular, Vue, itp.).  
- Lokalizacja aplikacji: Określ folder zawierający kod Twojej aplikacji (np. / jeśli znajduje się w katalogu głównym).  
- Lokalizacja API: Jeśli masz API, określ jego lokalizację (opcjonalne).  
- Lokalizacja wynikowa: Określ folder, w którym generowane są wyniki kompilacji (np. build lub dist).

4. Przegląd i utworzenie  
Przejrzyj swoje ustawienia i kliknij „Utwórz”. Azure skonfiguruje niezbędne zasoby i utworzy plik workflow GitHub Actions w Twoim repozytorium.

5. Workflow GitHub Actions  
Azure automatycznie utworzy plik workflow GitHub Actions w Twoim repozytorium (.github/workflows/azure-static-web-apps-<name>.yml). Ten workflow zajmie się procesem budowania i wdrażania.

6. Monitorowanie wdrożenia  
Przejdź do zakładki „Actions” w swoim repozytorium GitHub.  
Powinieneś zobaczyć uruchomiony workflow. Ten workflow zbuduje i wdroży Twoją statyczną aplikację internetową na platformie Azure.  
Po zakończeniu workflow Twoja aplikacja będzie dostępna pod podanym adresem URL Azure.

### Przykładowy plik workflow

Oto przykład, jak może wyglądać plik workflow GitHub Actions:  
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

### Dodatkowe zasoby  
- [Dokumentacja Azure Static Web Apps](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [Dokumentacja GitHub Actions](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.