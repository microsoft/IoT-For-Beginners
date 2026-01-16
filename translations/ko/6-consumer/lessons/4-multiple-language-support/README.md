<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-24T23:53:11+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "ko"
}
-->
# 여러 언어 지원

![이 강의의 스케치노트 개요](../../../../../translated_images/ko/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> 스케치노트: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

이 비디오는 Azure 음성 서비스에 대한 개요를 제공하며, 이전 강의에서 다룬 음성을 텍스트로 변환하고 텍스트를 음성으로 변환하는 내용뿐만 아니라 이번 강의에서 다룰 음성 번역에 대한 내용을 포함합니다:

[![Microsoft Build 2020에서 몇 줄의 Python으로 음성을 인식하는 방법](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 위 이미지를 클릭하여 비디오를 시청하세요

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## 소개

지난 3개의 강의에서는 AI를 활용하여 음성을 텍스트로 변환하고, 언어를 이해하며, 텍스트를 음성으로 변환하는 방법을 배웠습니다. AI가 인간의 의사소통을 돕는 또 다른 영역은 언어 번역입니다. 이는 영어를 프랑스어로 변환하는 것처럼 한 언어를 다른 언어로 변환하는 것을 의미합니다.

이번 강의에서는 AI를 사용하여 텍스트를 번역하는 방법을 배우고, 스마트 타이머가 여러 언어로 사용자와 상호작용할 수 있도록 만드는 방법을 배웁니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [텍스트 번역](../../../../../6-consumer/lessons/4-multiple-language-support)
* [번역 서비스](../../../../../6-consumer/lessons/4-multiple-language-support)
* [번역 리소스 생성](../../../../../6-consumer/lessons/4-multiple-language-support)
* [번역을 통해 애플리케이션에서 여러 언어 지원](../../../../../6-consumer/lessons/4-multiple-language-support)
* [AI 서비스를 사용하여 텍스트 번역](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 이번 프로젝트의 마지막 강의입니다. 강의와 과제를 완료한 후에는 클라우드 서비스를 정리하는 것을 잊지 마세요. 과제를 완료하려면 서비스가 필요하니 먼저 과제를 완료하세요.
>
> 필요하다면 [프로젝트 정리 가이드](../../../clean-up.md)를 참조하여 정리 방법을 확인하세요.

## 텍스트 번역

텍스트 번역은 70년 이상 연구되어 온 컴퓨터 과학 문제로, AI와 컴퓨터 성능의 발전 덕분에 이제 인간 번역가와 거의 비슷한 수준으로 해결될 수 있는 단계에 이르렀습니다.

> 💁 그 기원은 9세기 아랍 암호학자인 [알킨디](https://wikipedia.org/wiki/Al-Kindi)로 거슬러 올라갑니다. 그는 언어 번역을 위한 기술을 개발했습니다.

### 기계 번역

텍스트 번역은 처음에 기계 번역(MT)이라는 기술로 시작되었습니다. 이는 서로 다른 언어 쌍 간의 번역을 수행할 수 있는 기술입니다. MT는 한 언어의 단어를 다른 언어로 대체하고, 단순한 단어 대 단어 번역이 의미가 없을 때 문구나 문장의 일부를 올바르게 번역하는 방법을 선택하는 기술을 추가하여 작동합니다.

> 🎓 번역기가 한 언어에서 다른 언어로 번역을 지원할 때 이를 *언어 쌍*이라고 합니다. 다양한 도구가 서로 다른 언어 쌍을 지원하며, 이들 모두가 완벽하지는 않습니다. 예를 들어, 번역기가 영어에서 스페인어로 번역하는 언어 쌍과 스페인어에서 이탈리아어로 번역하는 언어 쌍을 지원할 수 있지만, 영어에서 이탈리아어로 번역하는 언어 쌍은 지원하지 않을 수 있습니다.

예를 들어, "Hello world"를 영어에서 프랑스어로 번역하는 경우 "Hello"는 "Bonjour"로, "world"는 "le monde"로 대체하여 "Bonjour le monde"라는 올바른 번역을 얻을 수 있습니다.

단순 대체는 다른 언어가 동일한 의미를 표현하는 데 다른 방법을 사용하는 경우에는 작동하지 않습니다. 예를 들어, 영어 문장 "My name is Jim"은 프랑스어로 "Je m'appelle Jim"으로 번역됩니다. 이는 문자 그대로 "나는 나 자신을 Jim이라고 부른다"는 뜻입니다. "Je"는 프랑스어로 "I"를 의미하고, "moi"는 "me"를 의미하지만 모음으로 시작하는 동사와 결합되어 "m'"이 됩니다. "appelle"는 "to call"을 의미하며, "Jim"은 이름이기 때문에 번역되지 않습니다. 단어 순서도 문제가 됩니다. "Je m'appelle Jim"을 단순히 대체하면 "I myself call Jim"이 되어 영어와 다른 단어 순서를 가지게 됩니다.

> 💁 일부 단어는 절대 번역되지 않습니다. 내 이름은 Jim이며, 어떤 언어로 소개하든 동일합니다. 다른 알파벳을 사용하는 언어로 번역할 때는 단어를 *음역*하여 적절한 소리를 선택해 원래 단어와 동일하게 들리도록 할 수 있습니다.

관용구도 번역에서 문제가 됩니다. 관용구는 단어의 직접적인 해석과는 다른 의미를 가진 문구입니다. 예를 들어, 영어 관용구 "I've got ants in my pants"는 문자 그대로 옷에 개미가 있다는 뜻이 아니라, 불안하거나 안절부절못하는 상태를 의미합니다. 이를 독일어로 번역하면 청자를 혼란스럽게 할 수 있습니다. 독일어 버전은 "I have bumble bees in the bottom"입니다.

> 💁 지역에 따라 복잡성이 추가됩니다. "ants in your pants"라는 관용구에서 미국 영어에서 "pants"는 겉옷을 의미하지만, 영국 영어에서는 "pants"가 속옷을 의미합니다.

✅ 여러 언어를 구사한다면 직접 번역되지 않는 문구를 생각해 보세요.

기계 번역 시스템은 특정 문구와 관용구를 번역하는 방법을 설명하는 대규모 규칙 데이터베이스와 가능한 옵션 중에서 적절한 번역을 선택하는 통계적 방법에 의존합니다. 이러한 통계적 방법은 인간이 여러 언어로 번역한 방대한 데이터베이스를 사용하여 가장 가능성이 높은 번역을 선택하는 *통계적 기계 번역*이라는 기술을 사용합니다. 일부 시스템은 언어의 중간 표현을 사용하여 한 언어를 중간 표현으로 번역한 다음 중간 표현에서 다른 언어로 번역합니다. 이렇게 하면 더 많은 언어를 추가할 때 중간 표현으로의 번역과 중간 표현에서의 번역만 필요하며, 모든 다른 언어로의 번역은 필요하지 않습니다.

### 신경 번역

신경 번역은 AI의 힘을 활용하여 번역을 수행하며, 일반적으로 하나의 모델을 사용하여 전체 문장을 번역합니다. 이러한 모델은 웹 페이지, 책, 유엔 문서와 같이 인간이 번역한 방대한 데이터 세트를 기반으로 학습됩니다.

신경 번역 모델은 대규모 문구와 관용구 데이터베이스가 필요하지 않기 때문에 기계 번역 모델보다 일반적으로 더 작습니다. 현대 AI 서비스는 종종 통계적 기계 번역과 신경 번역을 혼합하여 번역을 제공합니다.

어떤 언어 쌍에도 1:1 번역은 없습니다. 사용된 데이터에 따라 번역 모델이 약간 다른 결과를 생성할 수 있습니다. 번역은 항상 대칭적이지 않습니다. 즉, 한 언어에서 다른 언어로 문장을 번역한 다음 다시 첫 번째 언어로 번역하면 약간 다른 문장이 결과로 나올 수 있습니다.

✅ [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com), 또는 Apple 번역 앱과 같은 다양한 온라인 번역기를 사용해 보세요. 몇 개의 문장을 번역한 결과를 비교해 보세요. 또한 하나의 번역기에서 번역한 후 다른 번역기로 다시 번역해 보세요.

## 번역 서비스

애플리케이션에서 음성과 텍스트를 번역하기 위해 사용할 수 있는 여러 AI 서비스가 있습니다.

### Cognitive Services 음성 서비스

![음성 서비스 로고](../../../../../translated_images/ko/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

지난 몇 강의 동안 사용한 음성 서비스는 음성 인식을 위한 번역 기능을 제공합니다. 음성을 인식할 때 동일한 언어의 텍스트뿐만 아니라 다른 언어의 텍스트도 요청할 수 있습니다.

> 💁 이는 음성 SDK에서만 사용할 수 있으며, REST API에는 번역 기능이 내장되어 있지 않습니다.

### Cognitive Services 번역기 서비스

![번역기 서비스 로고](../../../../../translated_images/ko/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

번역기 서비스는 한 언어에서 하나 이상의 대상 언어로 텍스트를 번역할 수 있는 전용 번역 서비스입니다. 번역 외에도 욕설 마스킹을 포함한 다양한 추가 기능을 지원합니다. 또한 특정 단어 또는 문구에 대해 특정 번역을 제공하여 번역하지 않거나 잘 알려진 번역을 제공할 수 있습니다.

예를 들어, 단일 보드 컴퓨터를 나타내는 "I have a Raspberry Pi"라는 문장을 프랑스어와 같은 다른 언어로 번역할 때 "Raspberry Pi"라는 이름을 그대로 유지하고 번역하지 않기를 원할 것입니다. 이 경우 "J’ai un Raspberry Pi"가 "J’ai une pi aux framboises" 대신 올바른 번역이 됩니다.

## 번역 리소스 생성

이번 강의에서는 번역기 리소스가 필요합니다. REST API를 사용하여 텍스트를 번역할 것입니다.

### 작업 - 번역기 리소스 생성

1. 터미널 또는 명령 프롬프트에서 다음 명령을 실행하여 `smart-timer` 리소스 그룹에 번역기 리소스를 생성하세요.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>`을 리소스 그룹을 생성할 때 사용한 위치로 바꾸세요.

1. 번역기 서비스의 키를 가져오세요:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    키 중 하나를 복사하세요.

## 번역을 통해 애플리케이션에서 여러 언어 지원

이상적인 상황에서는 애플리케이션 전체가 가능한 한 많은 언어를 이해해야 합니다. 음성을 듣고, 언어를 이해하며, 음성으로 응답하는 것까지 포함됩니다. 이는 많은 작업이 필요하지만 번역 서비스는 애플리케이션의 배포 시간을 단축할 수 있습니다.

![일본어를 영어로 번역하고, 영어로 처리한 후 다시 일본어로 번역하는 스마트 타이머 아키텍처](../../../../../translated_images/ko/translated-smart-timer.08ac20057fdc5c37.webp)

스마트 타이머를 영어로만 사용한다고 가정해 보세요. 영어로 음성을 이해하고 텍스트로 변환하며, 영어로 언어를 이해하고, 영어로 응답을 작성한 후 영어 음성으로 응답합니다. 일본어 지원을 추가하고 싶다면 일본어 음성을 영어 텍스트로 번역하는 것으로 시작할 수 있습니다. 그런 다음 애플리케이션의 핵심은 동일하게 유지하고 응답 텍스트를 일본어로 번역한 후 일본어 음성으로 응답합니다. 이렇게 하면 일본어 지원을 빠르게 추가할 수 있으며, 나중에 전체적으로 일본어를 지원하도록 확장할 수 있습니다.

> 💁 기계 번역에 의존하면 다른 언어와 문화가 동일한 표현을 다르게 표현하기 때문에 번역이 예상한 표현과 일치하지 않을 수 있습니다.

기계 번역은 사용자가 콘텐츠를 생성하는 즉시 번역할 수 있는 앱과 장치를 개발할 가능성을 열어줍니다. 공상 과학 소설에서는 종종 '유니버설 번역기'가 등장하며, 이는 외계 언어를 (대개) 미국 영어로 번역할 수 있는 장치입니다. 이러한 장치는 외계 부분을 제외하면 더 이상 공상 과학이 아니라 과학적 사실에 가까워졌습니다. 이미 음성과 텍스트를 실시간으로 번역하는 앱과 장치가 존재하며, 음성 및 번역 서비스를 결합하여 작동합니다.

한 예로 [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) 모바일 앱이 있습니다. 이 앱은 다음 비디오에서 시연됩니다:

[![Microsoft Translator 실시간 기능 시연](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 위 이미지를 클릭하여 비디오를 시청하세요

특히 여행 중이거나 모르는 언어를 사용하는 사람들과 상호작용할 때 이러한 장치가 있다면 얼마나 유용할지 상상해 보세요. 공항이나 병원에서 자동 번역 장치를 사용하면 접근성을 크게 개선할 수 있습니다.

✅ 조사해 보세요: 상업적으로 이용 가능한 번역 IoT 장치가 있나요? 스마트 장치에 내장된 번역 기능은 어떤가요?

> 👽 외계인과 대화할 수 있는 진정한 유니버설 번역기는 없지만, [Microsoft Translator는 클링온어를 지원합니다](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## AI 서비스를 사용하여 텍스트 번역

스마트 타이머에 번역 기능을 추가하려면 AI 서비스를 사용할 수 있습니다.

### 작업 - AI 서비스를 사용하여 텍스트 번역

IoT 장치에서 텍스트를 번역하는 관련 가이드를 따라 작업하세요:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [단일 보드 컴퓨터 - Raspberry Pi](pi-translate-speech.md)
* [단일 보드 컴퓨터 - 가상 장치](virtual-device-translate-speech.md)

---

## 🚀 도전 과제

기계 번역이 스마트 장치 외의 다른 IoT 애플리케이션에 어떻게 도움이 될 수 있을까요? 번역이 음성뿐만 아니라 텍스트에도 어떻게 도움이 될 수 있을지 다양한 방법을 생각해 보세요.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## 복습 및 자기 학습

* [Wikipedia의 기계 번역 페이지](https://wikipedia.org/wiki/Machine_translation)에서 기계 번역에 대해 더 읽어보세요.
* [Wikipedia의 신경 기계 번역 페이지](https://wikipedia.org/wiki/Neural_machine_translation)에서 신경 기계 번역에 대해 더 읽어보세요.
* Microsoft 음성 서비스의 지원 언어 목록을 [Microsoft Docs의 음성 서비스 문서](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)에서 확인하세요.

## 과제

[유니버설 번역기 만들기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.