<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ccdc1faa676a485c4c6ecbddb9f9067",
  "translation_date": "2025-08-25T01:00:11+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/assignment.md",
  "language_code": "ko"
}
-->
# 앱 배포하기

## 지침

앱을 배포하여 세상과 공유할 수 있는 여러 가지 방법이 있습니다. GitHub Pages를 사용하거나 다양한 서비스 제공업체 중 하나를 이용할 수 있습니다. 정말 훌륭한 방법 중 하나는 Azure Static Web Apps를 사용하는 것입니다. 이번 과제에서는 웹 앱을 빌드하고 [이 지침](https://github.com/Azure/static-web-apps-cli)을 따르거나 [이 동영상](https://www.youtube.com/watch?v=ADVGIXciYn8&list=PLlrxD0HtieHgMPeBaDQFx9yNuFxx6S1VG&index=3)을 시청하여 클라우드에 배포하세요.  
Azure Static Web Apps를 사용하면 API 키를 포털에서 숨길 수 있다는 장점이 있습니다. 이 기회를 활용하여 subscriptionKey를 변수로 리팩터링하고 클라우드에 저장하세요.

## 평가 기준

| 기준      | 우수                                                                                                                                    | 적절                                                                                                                | 개선 필요                                         |
| --------- | --------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------ |
|           | subscriptionKey가 클라우드에 저장되고 변수를 통해 호출되는 문서화된 GitHub 저장소에서 작동하는 웹 앱이 제공됨                              | subscriptionKey가 클라우드에 저장되지 않았지만 문서화된 GitHub 저장소에서 작동하는 웹 앱이 제공됨                     | 웹 앱에 버그가 있거나 제대로 작동하지 않음       |

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생할 수 있는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.