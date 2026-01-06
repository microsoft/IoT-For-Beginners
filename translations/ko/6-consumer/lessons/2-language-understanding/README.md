<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-25T00:02:26+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "ko"
}
-->
# 언어 이해하기

![이 강의의 스케치노트 개요](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.ko.jpg)

> 스케치노트 제공: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## 소개

지난 강의에서는 음성을 텍스트로 변환하는 방법을 배웠습니다. 이를 스마트 타이머를 프로그래밍하는 데 사용하려면, 코드가 사용자가 말한 내용을 이해할 수 있어야 합니다. 사용자가 "3분 타이머 설정"과 같은 고정된 문구를 말할 것이라고 가정하고, 이 표현을 분석하여 타이머 시간을 설정할 수 있습니다. 하지만 이는 사용자 친화적이지 않습니다. 사용자가 "타이머를 3분으로 설정해줘"라고 말한다면, 우리 인간은 그 의미를 이해할 수 있지만, 코드는 고정된 문구를 기대하기 때문에 이를 이해하지 못할 것입니다.

이때 언어 이해가 필요합니다. AI 모델을 사용하여 텍스트를 해석하고 필요한 세부 정보를 반환하는 것입니다. 예를 들어, "3분 타이머 설정"과 "타이머를 3분으로 설정해줘"라는 두 문장을 모두 이해하고, 3분짜리 타이머가 필요하다는 것을 파악하는 것입니다.

이번 강의에서는 언어 이해 모델을 만들고, 훈련시키고, 코드를 통해 사용하는 방법을 배웁니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [언어 이해](../../../../../6-consumer/lessons/2-language-understanding)
* [언어 이해 모델 생성](../../../../../6-consumer/lessons/2-language-understanding)
* [의도와 엔터티](../../../../../6-consumer/lessons/2-language-understanding)
* [언어 이해 모델 사용](../../../../../6-consumer/lessons/2-language-understanding)

## 언어 이해

인간은 수십만 년 동안 언어를 사용해 소통해 왔습니다. 우리는 단어, 소리, 행동으로 소통하며, 단어, 소리, 행동의 의미뿐만 아니라 그 맥락까지 이해합니다. 우리는 진심과 풍자를 구분하며, 같은 단어라도 목소리의 톤에 따라 다른 의미를 가질 수 있다는 것을 알고 있습니다.

✅ 최근에 나눈 대화를 떠올려 보세요. 컴퓨터가 맥락을 이해해야 하기 때문에 이해하기 어려운 대화는 얼마나 있었나요?

언어 이해, 또는 자연어 이해는 자연어 처리(NLP)라는 인공지능 분야의 일부로, 읽기 이해와 단어 또는 문장의 세부 사항을 이해하는 것을 다룹니다. Alexa나 Siri 같은 음성 비서를 사용해 본 적이 있다면, 언어 이해 서비스를 사용해 본 것입니다. 이러한 서비스는 "Alexa, Taylor Swift의 최신 앨범을 틀어줘"를 딸이 거실에서 좋아하는 음악에 맞춰 춤추는 모습으로 변환하는 백그라운드 AI 서비스입니다.

> 💁 컴퓨터는 많은 발전을 이루었지만, 여전히 텍스트를 진정으로 이해하는 데는 갈 길이 멉니다. 컴퓨터의 언어 이해는 인간의 소통처럼 고급스러운 수준이 아니라, 단어를 분석해 핵심 정보를 추출하는 것을 의미합니다.

인간은 언어를 별다른 생각 없이 이해합니다. 만약 제가 다른 사람에게 "Taylor Swift의 최신 앨범을 틀어줘"라고 요청한다면, 그 사람은 본능적으로 제가 무엇을 의미하는지 알 것입니다. 하지만 컴퓨터에게는 더 어렵습니다. 컴퓨터는 음성을 텍스트로 변환한 후, 다음과 같은 정보를 추출해야 합니다:

* 음악을 재생해야 한다는 것
* 음악의 아티스트가 Taylor Swift라는 것
* 특정 음악이 여러 트랙으로 구성된 전체 앨범이라는 것
* Taylor Swift의 앨범이 여러 개 있으므로, 연대순으로 정렬하여 가장 최근에 발매된 앨범이 필요하다는 것

✅ 커피를 주문하거나 가족에게 무언가를 건네달라고 요청할 때 했던 문장을 떠올려 보세요. 컴퓨터가 문장을 이해하려면 어떤 정보를 추출해야 할지 나눠 보세요.

언어 이해 모델은 언어에서 특정 세부 정보를 추출하도록 훈련된 AI 모델입니다. 이 모델은 Custom Vision 모델을 소량의 이미지로 훈련시킨 것처럼, 전이 학습을 사용해 특정 작업에 맞게 훈련됩니다. 모델을 가져와서 이해하고자 하는 텍스트로 훈련시킬 수 있습니다.

## 언어 이해 모델 생성

![LUIS 로고](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.ko.png)

LUIS는 Microsoft의 언어 이해 서비스로, Cognitive Services의 일부입니다. 이를 사용해 언어 이해 모델을 생성할 수 있습니다.

### 작업 - 작성 리소스 생성

LUIS를 사용하려면 작성 리소스를 생성해야 합니다.

1. 다음 명령어를 사용해 `smart-timer` 리소스 그룹에 작성 리소스를 생성하세요:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>`을 리소스 그룹을 생성할 때 사용한 위치로 바꾸세요.

    > ⚠️ LUIS는 모든 지역에서 사용할 수 없습니다. 다음과 같은 오류가 발생하면:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > 다른 지역을 선택하세요.

    이 명령어는 무료 등급의 LUIS 작성 리소스를 생성합니다.

### 작업 - 언어 이해 앱 생성

1. 브라우저에서 [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) 포털을 열고, Azure에서 사용 중인 동일한 계정으로 로그인하세요.

1. 대화 상자의 지침에 따라 Azure 구독을 선택한 다음, 방금 생성한 `smart-timer-luis-authoring` 리소스를 선택하세요.

1. *Conversation apps* 목록에서 **New app** 버튼을 선택해 새 애플리케이션을 생성하세요. 새 앱의 이름을 `smart-timer`로 지정하고, *Culture*를 자신의 언어로 설정하세요.

    > 💁 예측 리소스를 위한 필드가 있습니다. 예측만을 위한 별도의 리소스를 생성할 수도 있지만, 무료 작성 리소스는 한 달에 1,000번의 예측을 제공하므로 개발에는 충분합니다. 따라서 이 필드는 비워둘 수 있습니다.

1. 앱을 생성한 후 나타나는 가이드를 읽고, 언어 이해 모델을 훈련시키기 위해 필요한 단계를 이해하세요. 완료 후 가이드를 닫으세요.

## 의도와 엔터티

언어 이해는 *의도*와 *엔터티*를 중심으로 이루어집니다. 의도는 단어의 목적을 나타내며, 예를 들어 음악 재생, 타이머 설정, 음식 주문 등이 있습니다. 엔터티는 의도가 참조하는 대상을 나타내며, 예를 들어 앨범, 타이머의 길이, 음식 종류 등이 있습니다. 모델이 해석하는 각 문장은 최소 하나의 의도와 선택적으로 하나 이상의 엔터티를 가질 수 있습니다.

몇 가지 예를 들어보겠습니다:

| 문장                                                | 의도             | 엔터티                                     |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| "Taylor Swift의 최신 앨범을 틀어줘"                 | *음악 재생*      | *Taylor Swift의 최신 앨범*                 |
| "3분 타이머 설정"                                   | *타이머 설정*    | *3분*                                      |
| "내 타이머 취소"                                    | *타이머 취소*    | 없음                                       |
| "파인애플 피자 3판과 시저 샐러드 주문"              | *음식 주문*      | *파인애플 피자 3판*, *시저 샐러드*         |

✅ 앞서 생각했던 문장들에서, 해당 문장의 의도와 엔터티는 무엇일지 생각해 보세요.

LUIS를 훈련시키려면 먼저 엔터티를 설정해야 합니다. 엔터티는 고정된 용어 목록이거나 텍스트에서 학습될 수 있습니다. 예를 들어, 메뉴에 있는 음식의 고정된 목록을 제공하고, 각 단어의 변형(또는 동의어)을 추가할 수 있습니다. 예를 들어, *egg plant*와 *aubergine*은 *aubergine*의 변형입니다. LUIS에는 숫자와 위치와 같은 사전 구축된 엔터티도 있습니다.

타이머를 설정하려면, 시간 단위(분 또는 초)를 위한 엔터티 하나와 분 또는 초의 숫자를 위한 엔터티 하나가 필요합니다. 각 단위는 단수형과 복수형을 포함한 여러 변형을 가져야 합니다. 예를 들어, minute와 minutes.

엔터티를 정의한 후에는 의도를 생성합니다. 의도는 제공된 예문(utterances)을 기반으로 모델이 학습합니다. 예를 들어, *타이머 설정* 의도에 대해 다음과 같은 문장을 제공할 수 있습니다:

* `1초 타이머 설정`
* `1분 12초 타이머 설정`
* `3분 타이머 설정`
* `9분 30초 타이머 설정`

이 문장들에서 어떤 부분이 엔터티에 해당하는지 LUIS에 알려줍니다:

![1분 12초 타이머 설정 문장이 엔터티로 나뉜 모습](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.ko.png)

문장 `1분 12초 타이머 설정`의 의도는 `타이머 설정`입니다. 또한 2개의 엔터티와 각각의 값이 있습니다:

|            | 시간 | 단위   |
| ---------- | ---: | ------ |
| 1분        | 1    | 분     |
| 12초       | 12   | 초     |

좋은 모델을 훈련시키려면, 동일한 요청을 표현하는 다양한 문장을 포함해야 합니다.

> 💁 모든 AI 모델과 마찬가지로, 훈련에 사용하는 데이터가 많고 정확할수록 모델이 더 좋아집니다.

✅ 동일한 요청을 인간이 이해할 수 있는 다양한 표현 방법을 생각해 보세요.

### 작업 - 언어 이해 모델에 엔터티 추가

타이머를 위해 2개의 엔터티를 추가해야 합니다. 하나는 시간 단위(분 또는 초)를 위한 것이고, 다른 하나는 분 또는 초의 숫자를 위한 것입니다.

LUIS 포털 사용 방법에 대한 지침은 [Microsoft Docs의 LUIS 포털에서 앱 빌드 빠른 시작 가이드](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn)에서 확인할 수 있습니다.

1. LUIS 포털에서 *Entities* 탭을 선택하고 **Add prebuilt entity** 버튼을 선택해 *number* 사전 구축 엔터티를 추가하세요.

1. **Create** 버튼을 사용해 시간 단위를 위한 새 엔터티를 생성하세요. 엔터티 이름을 `time unit`으로 지정하고, 유형을 *List*로 설정하세요. *Normalized values* 목록에 `minute`과 `second` 값을 추가하고, *synonyms* 목록에 단수형과 복수형 변형을 추가하세요. 각 동의어를 추가한 후 `return` 키를 눌러 목록에 추가하세요.

    | 정규화된 값 | 동의어          |
    | ----------- | --------------- |
    | minute      | minute, minutes |
    | second      | second, seconds |

### 작업 - 언어 이해 모델에 의도 추가

1. *Intents* 탭에서 **Create** 버튼을 선택해 새 의도를 생성하세요. 이 의도의 이름을 `set timer`로 지정하세요.

1. 예제에 분, 초, 분과 초를 조합한 타이머 설정 방법을 다양하게 입력하세요. 예제는 다음과 같을 수 있습니다:

    * `1초 타이머 설정`
    * `4분 타이머 설정`
    * `4분 6초 타이머 설정`
    * `9분 30초 타이머 설정`
    * `1분 12초 타이머 설정`
    * `3분 타이머 설정`
    * `3분 1초 타이머 설정`
    * `3분 1초 타이머 설정`
    * `1분 1초 타이머 설정`
    * `30초 타이머 설정`
    * `1초 타이머 설정`

    숫자를 단어와 숫자로 혼합하여 모델이 둘 다 처리할 수 있도록 학습시키세요.

1. 각 예제를 입력할 때, LUIS는 엔터티를 감지하기 시작하며, 감지된 엔터티를 밑줄로 표시하고 레이블을 붙입니다.

    ![LUIS가 숫자와 시간 단위를 밑줄로 표시한 예제](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.ko.png)

### 작업 - 모델 훈련 및 테스트

1. 엔터티와 의도가 구성되면, 상단 메뉴의 **Train** 버튼을 사용해 모델을 훈련시킬 수 있습니다. 이 버튼을 선택하면 모델이 몇 초 안에 훈련됩니다. 훈련 중에는 버튼이 비활성화되며, 완료되면 다시 활성화됩니다.

1. 상단 메뉴의 **Test** 버튼을 선택해 언어 이해 모델을 테스트하세요. `5분 4초 타이머 설정`과 같은 텍스트를 입력하고 Enter 키를 누르세요. 입력한 텍스트는 텍스트 상자 아래에 나타나며, 그 아래에는 *최상위 의도* 또는 가장 높은 확률로 감지된 의도가 표시됩니다. 이 의도는 `set timer`여야 합니다. 의도 이름 뒤에는 해당 의도가 올바르게 감지되었을 확률이 표시됩니다.

1. **Inspect** 옵션을 선택해 결과를 세부적으로 확인하세요. 최상위 의도와 그 확률, 감지된 엔터티 목록을 볼 수 있습니다.

1. 테스트 창을 닫으세요.

### 작업 - 모델 게시

코드에서 이 모델을 사용하려면 게시해야 합니다. LUIS에서 게시할 때는 테스트를 위한 스테이징 환경이나 전체 릴리스를 위한 프로덕션 환경 중 하나를 선택할 수 있습니다. 이번 강의에서는 스테이징 환경으로 충분합니다.

1. LUIS 포털에서 상단 메뉴의 **Publish** 버튼을 선택하세요.

1. *Staging slot*이 선택되어 있는지 확인한 후 **Done**을 선택하세요. 앱이 게시되면 알림이 표시됩니다.

1. curl을 사용해 이를 테스트할 수 있습니다. curl 명령어를 작성하려면 엔드포인트, 애플리케이션 ID(App ID), API 키의 세 가지 값이 필요합니다. 이 값들은 상단 메뉴에서 선택할 수 있는 **MANAGE** 탭에서 확인할 수 있습니다.

    1. *Settings* 섹션에서 App ID를 복사하세요.
1. *Azure Resources* 섹션에서 *Authoring Resource*를 선택하고, *Primary Key*와 *Endpoint URL*을 복사합니다.

1. 명령 프롬프트 또는 터미널에서 다음 curl 명령을 실행합니다:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    `<endpoint url>`을 *Azure Resources* 섹션에서 복사한 Endpoint URL로 바꿉니다.

    `<app id>`를 *Settings* 섹션에서 복사한 App ID로 바꿉니다.

    `<primary key>`를 *Azure Resources* 섹션에서 복사한 Primary Key로 바꿉니다.

    `<sentence>`를 테스트할 문장으로 바꿉니다.

1. 이 호출의 출력은 쿼리, 최상위 의도(top intent), 그리고 유형별로 분류된 엔티티 목록을 상세히 보여주는 JSON 문서가 될 것입니다.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    위 JSON은 `set a timer for 45 minutes and 12 seconds`라는 쿼리에서 생성되었습니다:

    * `set timer`가 97%의 확률로 최상위 의도로 감지되었습니다.
    * 두 개의 *number* 엔티티 `45`와 `12`가 감지되었습니다.
    * 두 개의 *time-unit* 엔티티 `minute`와 `second`가 감지되었습니다.

## 언어 이해 모델 사용하기

LUIS 모델이 게시되면 코드에서 호출할 수 있습니다. 이전 레슨에서는 IoT Hub를 사용하여 클라우드 서비스와 통신을 처리하고, 텔레메트리를 보내고 명령을 수신했습니다. 이는 매우 비동기적입니다. 텔레메트리를 보낸 후에는 응답을 기다리지 않으며, 클라우드 서비스가 다운되었을 경우 이를 알 수 없습니다.

스마트 타이머의 경우 즉각적인 응답이 필요합니다. 이를 통해 사용자가 타이머가 설정되었음을 알거나 클라우드 서비스가 사용 불가능하다는 경고를 받을 수 있습니다. 이를 위해 IoT 장치가 IoT Hub를 사용하는 대신 웹 엔드포인트를 직접 호출하게 됩니다.

IoT 장치에서 LUIS를 직접 호출하는 대신, HTTP 트리거와 같은 다른 유형의 트리거를 사용하는 서버리스 코드를 활용할 수 있습니다. 이를 통해 함수 앱이 REST 요청을 수신하고 이에 응답할 수 있습니다. 이 함수는 IoT 장치가 호출할 수 있는 REST 엔드포인트가 됩니다.

> 💁 IoT 장치에서 LUIS를 직접 호출할 수도 있지만, 서버리스 코드를 사용하는 것이 더 좋습니다. 이렇게 하면 더 나은 모델을 훈련하거나 다른 언어로 모델을 훈련할 때 호출할 LUIS 앱을 변경해야 할 경우 클라우드 코드만 업데이트하면 되며, 수천 또는 수백만 개의 IoT 장치에 코드를 다시 배포할 필요가 없습니다.

### 작업 - 서버리스 함수 앱 생성하기

1. `smart-timer-trigger`라는 Azure Functions 앱을 생성하고 이를 VS Code에서 엽니다.

1. VS Code 터미널 내부에서 다음 명령을 사용하여 이 앱에 `speech-trigger`라는 HTTP 트리거를 추가합니다:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    이 명령은 `text-to-timer`라는 HTTP 트리거를 생성합니다.

1. 함수 앱을 실행하여 HTTP 트리거를 테스트합니다. 실행하면 출력에 엔드포인트가 표시됩니다:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    브라우저에서 [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL을 로드하여 테스트합니다.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### 작업 - 언어 이해 모델 사용하기

1. LUIS SDK는 Pip 패키지를 통해 제공됩니다. `requirements.txt` 파일에 다음 줄을 추가하여 이 패키지에 대한 의존성을 추가합니다:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. VS Code 터미널에서 가상 환경이 활성화되어 있는지 확인하고 다음 명령을 실행하여 Pip 패키지를 설치합니다:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 오류가 발생하면 다음 명령을 사용하여 pip를 업그레이드해야 할 수도 있습니다:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. LUIS 포털의 **MANAGE** 탭에서 LUIS API Key, Endpoint URL, App ID에 대한 새 항목을 `local.settings.json` 파일에 추가합니다:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    `<endpoint url>`을 **MANAGE** 탭의 *Azure Resources* 섹션에서 복사한 Endpoint URL로 바꿉니다. 이는 `https://<location>.api.cognitive.microsoft.com/` 형식입니다.

    `<app id>`를 **MANAGE** 탭의 *Settings* 섹션에서 복사한 App ID로 바꿉니다.

    `<primary key>`를 **MANAGE** 탭의 *Azure Resources* 섹션에서 복사한 Primary Key로 바꿉니다.

1. `__init__.py` 파일에 다음 import를 추가합니다:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    이는 시스템 라이브러리와 LUIS와 상호작용하기 위한 라이브러리를 가져옵니다.

1. `main` 메서드의 내용을 삭제하고 다음 코드를 추가합니다:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    이는 LUIS 앱에 대한 값을 `local.settings.json` 파일에서 로드하고, API 키로 자격 증명 객체를 생성한 다음, LUIS 앱과 상호작용하기 위한 LUIS 클라이언트 객체를 생성합니다.

1. 이 HTTP 트리거는 JSON으로 전달된 텍스트를 이해하기 위해 호출됩니다. 텍스트는 `text`라는 속성에 포함됩니다. HTTP 요청 본문에서 값을 추출하고 이를 콘솔에 기록하는 다음 코드를 `main` 함수에 추가합니다:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. 예측 요청은 예측할 텍스트를 포함하는 JSON 문서를 보내는 방식으로 LUIS에 요청됩니다. 다음 코드를 사용하여 이를 생성합니다:

    ```python
    prediction_request = { 'query' : text }
    ```

1. 이 요청은 앱이 게시된 스테이징 슬롯을 사용하여 LUIS에 보낼 수 있습니다:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. 예측 응답에는 최상위 의도와 엔티티가 포함됩니다. 최상위 의도가 `set timer`인 경우, 엔티티를 읽어 타이머에 필요한 시간을 가져올 수 있습니다:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` 엔티티는 숫자 배열입니다. 예를 들어, *"Set a four minute 17 second timer."*라고 말하면 `number` 배열에는 두 개의 정수 - 4와 17이 포함됩니다.

    `time unit` 엔티티는 문자열 배열의 배열입니다. 예를 들어, *"Set a four minute 17 second timer."*라고 말하면 `time unit` 배열에는 각각 단일 값을 가진 두 개의 배열 - `['minute']`와 `['second']`가 포함됩니다.

    *"Set a four minute 17 second timer."*에 대한 엔티티의 JSON 버전은 다음과 같습니다:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    이 코드는 또한 타이머의 총 시간을 초 단위로 정의합니다. 이는 엔티티의 값으로 채워집니다.

1. 엔티티는 연결되어 있지 않지만 몇 가지 가정을 할 수 있습니다. 엔티티는 말한 순서대로 배열에 포함되므로 배열의 위치를 사용하여 어떤 숫자가 어떤 시간 단위와 일치하는지 결정할 수 있습니다. 예를 들어:

    * *"Set a 30 second timer"* - 숫자 `30`과 시간 단위 `second`가 하나씩 있으므로 단일 숫자가 단일 시간 단위와 일치합니다.
    * *"Set a 2 minute and 30 second timer"* - 숫자 `2`와 `30`, 시간 단위 `minute`과 `second`가 각각 두 개씩 있으므로 첫 번째 숫자는 첫 번째 시간 단위(2분)와, 두 번째 숫자는 두 번째 시간 단위(30초)와 일치합니다.

    다음 코드는 숫자 엔티티의 항목 수를 가져와 각 배열에서 첫 번째 항목, 두 번째 항목 등을 추출합니다. 이를 `if` 블록 내부에 추가합니다.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    *"Set a four minute 17 second timer."*의 경우, 이는 두 번 반복되며 다음 값을 제공합니다:

    | 반복 횟수 | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. 이 루프 내부에서 숫자와 시간 단위를 사용하여 타이머의 총 시간을 계산하고, 분당 60초를 추가하며 초 단위로 계산합니다.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. 엔티티를 반복하는 루프 외부에서 타이머의 총 시간을 기록합니다:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. 초 단위의 시간을 HTTP 응답으로 함수에서 반환해야 합니다. `if` 블록 끝에 다음을 추가합니다:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    이 코드는 타이머의 총 초 수를 포함하는 페이로드를 생성하고 이를 JSON 문자열로 변환하여 상태 코드 200과 함께 HTTP 결과로 반환합니다. 상태 코드 200은 호출이 성공했음을 의미합니다.

1. 마지막으로, 의도가 인식되지 않은 경우를 처리하기 위해 `if` 블록 외부에서 오류 코드를 반환합니다:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404는 *찾을 수 없음* 상태 코드입니다.

1. 함수 앱을 실행하고 curl을 사용하여 테스트합니다.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    `<text>`를 요청 텍스트로 바꿉니다. 예를 들어 `set a 2 minutes 27 second timer`.

    함수 앱에서 다음 출력이 표시됩니다:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    curl 호출은 다음을 반환합니다:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    타이머의 초 수는 `"seconds"` 값에 포함됩니다.

> 💁 이 코드는 [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) 폴더에서 찾을 수 있습니다.

### 작업 - IoT 장치에서 함수 사용 가능하게 만들기

1. IoT 장치가 REST 엔드포인트를 호출하려면 URL을 알아야 합니다. 이전에 액세스할 때 `localhost`를 사용했는데, 이는 로컬 머신에서 REST 엔드포인트에 액세스하기 위한 바로가기입니다. IoT 장치가 액세스할 수 있도록 하려면 클라우드에 게시하거나 로컬로 액세스할 수 있는 IP 주소를 가져와야 합니다.

    > ⚠️ Wio Terminal을 사용하는 경우, 함수 앱을 로컬에서 실행하는 것이 더 쉽습니다. 이는 이전에 배포한 방식과 다르게 함수 앱을 배포할 수 없게 만드는 라이브러리 의존성이 있기 때문입니다. 함수 앱을 로컬에서 실행하고 컴퓨터의 IP 주소를 통해 액세스하세요. 클라우드에 배포하려는 경우, 이후 레슨에서 이를 수행하는 방법에 대한 정보가 제공될 것입니다.

    * 함수 앱 게시 - 이전 레슨의 지침을 따라 함수 앱을 클라우드에 게시합니다. 게시된 후 URL은 `https://<APP_NAME>.azurewebsites.net/api/text-to-timer` 형식이 됩니다. 여기서 `<APP_NAME>`은 함수 앱의 이름입니다. 로컬 설정도 함께 게시해야 합니다.

      HTTP 트리거를 사용할 때 기본적으로 함수 앱 키로 보호됩니다. 이 키를 얻으려면 다음 명령을 실행합니다:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      `functionKeys` 섹션의 `default` 항목 값을 복사합니다.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      이 키는 URL에 쿼리 매개변수로 추가해야 하므로 최종 URL은 `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>` 형식이 됩니다. 여기서 `<APP_NAME>`은 함수 앱의 이름이고 `<FUNCTION_KEY>`는 기본 함수 키입니다.

      > 💁 HTTP 트리거의 인증 유형은 `function.json` 파일의 `authlevel` 설정을 사용하여 변경할 수 있습니다. 이에 대한 자세한 내용은 [Microsoft 문서의 Azure Functions HTTP 트리거 문서의 구성 섹션](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration)에서 확인할 수 있습니다.

    * 함수 앱을 로컬에서 실행하고 IP 주소를 사용하여 액세스 - 로컬 네트워크에서 컴퓨터의 IP 주소를 가져와 이를 사용하여 URL을 생성합니다.

      IP 주소를 찾는 방법:

      * Windows 10에서는 [IP 주소 찾기 가이드](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)를 따르세요.
      * macOS에서는 [Mac에서 IP 주소 찾는 방법 가이드](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)를 따르세요.
      * Linux에서는 [Linux에서 IP 주소 찾는 방법 가이드](https://opensource.com/article/18/5/how-find-ip-address-linux)의 개인 IP 주소 찾기 섹션을 따르세요.

      IP 주소를 얻은 후, 함수에 `http://`

:7071/api/text-to-timer`, 여기서 `<IP_ADDRESS>`는 사용자의 IP 주소를 의미하며, 예를 들어 `http://192.168.1.10:7071/api/text-to-timer`와 같이 입력합니다.

      > 💁 이 포트는 7071을 사용하므로, IP 주소 뒤에 `:7071`을 추가해야 합니다.

      > 💁 이 기능은 사용자의 IoT 기기가 컴퓨터와 동일한 네트워크에 있을 때만 작동합니다.

1. curl을 사용하여 엔드포인트를 테스트합니다.

---

## 🚀 도전 과제

타이머를 설정하는 것처럼 동일한 요청을 여러 방식으로 할 수 있습니다. 이를 다양한 방법으로 생각해보고, LUIS 앱에서 예제로 사용하세요. 이러한 방법들을 테스트하여 모델이 다양한 요청 방식에 얼마나 잘 대응할 수 있는지 확인해보세요.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## 복습 및 자기 학습

* LUIS와 그 기능에 대해 더 알아보려면 [Microsoft 문서의 Language Understanding (LUIS) 페이지](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)를 읽어보세요.
* 언어 이해에 대해 더 알아보려면 [Wikipedia의 자연어 이해 페이지](https://wikipedia.org/wiki/Natural-language_understanding)를 읽어보세요.
* HTTP 트리거에 대해 더 알아보려면 [Microsoft 문서의 Azure Functions HTTP 트리거 페이지](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)를 읽어보세요.

## 과제

[타이머 취소하기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.