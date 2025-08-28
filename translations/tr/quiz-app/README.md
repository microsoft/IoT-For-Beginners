<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-28T03:45:59+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "tr"
}
-->
# Quizler

Bu quizler, IoT for Beginners müfredatındaki ders öncesi ve sonrası quizlerdir: https://aka.ms/iot-beginners

## Proje Kurulumu

```
npm install
```

### Geliştirme için derler ve anında yeniden yükler

```
npm run serve
```

### Üretim için derler ve küçültür

```
npm run build
```

### Dosyaları kontrol eder ve düzeltir

```
npm run lint
```

### Yapılandırmayı özelleştirme

[Configuration Reference](https://cli.vuejs.org/config/) adresine bakın.

Teşekkürler: Bu quiz uygulamasının orijinal versiyonu için teşekkürler: https://github.com/arpan45/simple-quiz-vue

## Azure'a Dağıtım

Başlamak için adım adım bir rehber:

1. Bir GitHub Deposu Çatallayın  
Statik web uygulamanızın kodunun GitHub deponuzda olduğundan emin olun. Bu depoyu çatallayın.

2. Bir Azure Statik Web Uygulaması Oluşturun  
- Bir [Azure hesabı](http://azure.microsoft.com) oluşturun.  
- [Azure portalına](https://portal.azure.com) gidin.  
- “Create a resource” (Kaynak oluştur) seçeneğine tıklayın ve “Static Web App” arayın.  
- “Create” (Oluştur) seçeneğine tıklayın.  

3. Statik Web Uygulamasını Yapılandırın  
- Temel Bilgiler:  
  - Abonelik: Azure aboneliğinizi seçin.  
  - Kaynak Grubu: Yeni bir kaynak grubu oluşturun veya mevcut birini kullanın.  
  - Ad: Statik web uygulamanız için bir ad belirleyin.  
  - Bölge: Kullanıcılarınıza en yakın bölgeyi seçin.  

- #### Dağıtım Detayları:  
  - Kaynak: “GitHub” seçeneğini seçin.  
  - GitHub Hesabı: Azure'un GitHub hesabınıza erişmesine izin verin.  
  - Organizasyon: GitHub organizasyonunuzu seçin.  
  - Depo: Statik web uygulamanızı içeren depoyu seçin.  
  - Dal: Hangi daldan dağıtım yapılacağını seçin.  

- #### Derleme Detayları:  
  - Derleme Ön Ayarları: Uygulamanızın hangi çerçeveyle oluşturulduğunu seçin (ör. React, Angular, Vue, vb.).  
  - Uygulama Konumu: Uygulama kodunuzu içeren klasörü belirtin (ör. kökteyse /).  
  - API Konumu: Bir API'niz varsa, konumunu belirtin (isteğe bağlı).  
  - Çıktı Konumu: Derleme çıktısının oluşturulduğu klasörü belirtin (ör. build veya dist).  

4. Gözden Geçir ve Oluştur  
Ayarlarınızı gözden geçirin ve “Create” (Oluştur) seçeneğine tıklayın. Azure, gerekli kaynakları ayarlayacak ve deponuzda bir GitHub Actions iş akışı oluşturacaktır.

5. GitHub Actions İş Akışı  
Azure, deponuzda otomatik olarak bir GitHub Actions iş akışı dosyası oluşturacaktır (.github/workflows/azure-static-web-apps-<name>.yml). Bu iş akışı, derleme ve dağıtım sürecini yönetecektir.

6. Dağıtımı İzleme  
GitHub deponuzdaki “Actions” sekmesine gidin.  
Bir iş akışının çalıştığını görmelisiniz. Bu iş akışı, statik web uygulamanızı Azure'a derleyecek ve dağıtacaktır.  
İş akışı tamamlandığında, uygulamanız sağlanan Azure URL'sinde canlı olacaktır.

### Örnek İş Akışı Dosyası

GitHub Actions iş akışı dosyasının nasıl görünebileceğine dair bir örnek:  
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

### Ek Kaynaklar  
- [Azure Statik Web Uygulamaları Belgeleri](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [GitHub Actions Belgeleri](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul edilmez.