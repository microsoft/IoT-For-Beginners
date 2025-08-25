<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-24T22:28:16+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "ko"
}
-->
# 수동 릴레이 제어 추가

## 지침

서버리스 코드는 HTTP 요청을 포함하여 다양한 방식으로 트리거될 수 있습니다. HTTP 트리거를 사용하여 릴레이 제어에 수동 오버라이드를 추가하면 웹 요청을 통해 릴레이를 켜거나 끌 수 있습니다.

이 과제에서는 Functions App에 두 개의 HTTP 트리거를 추가하여 릴레이를 켜고 끄는 작업을 수행해야 합니다. 이 과정에서 배운 내용을 활용하여 장치에 명령을 보내세요.

몇 가지 힌트:

* 기존 Functions App에 HTTP 트리거를 추가하려면 다음 명령을 사용할 수 있습니다:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    `<trigger name>`을 HTTP 트리거의 이름으로 바꾸세요. `relay_on`과 `relay_off` 같은 이름을 사용하세요.

* HTTP 트리거는 액세스 제어를 가질 수 있습니다. 기본적으로 URL과 함께 함수별 API 키를 전달해야 실행됩니다. 이 과제에서는 이 제한을 제거하여 누구나 함수를 실행할 수 있도록 설정하세요. 이를 위해 HTTP 트리거의 `function.json` 파일에서 `authLevel` 설정을 다음과 같이 업데이트하세요:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 이 액세스 제어에 대한 자세한 내용은 [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys)에서 확인할 수 있습니다.

* HTTP 트리거는 기본적으로 GET 및 POST 요청을 지원합니다. 즉, 웹 브라우저를 사용하여 호출할 수 있습니다. 웹 브라우저는 GET 요청을 만듭니다.

    Functions App을 로컬에서 실행하면 트리거의 URL이 표시됩니다:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    URL을 브라우저에 붙여넣고 `Enter` 키를 누르거나, VS Code의 터미널 창에서 링크를 `Ctrl+클릭`(macOS에서는 `Cmd+클릭`)하여 기본 브라우저에서 열어보세요. 이렇게 하면 트리거가 실행됩니다.

    > 💁 URL에 `/api`가 포함되어 있는 것을 확인하세요 - HTTP 트리거는 기본적으로 `api` 하위 도메인에 있습니다.

* Functions App을 배포하면 HTTP 트리거 URL은 다음과 같습니다:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    여기서 `<functions app name>`은 Functions App의 이름이고, `<trigger name>`은 트리거의 이름입니다.

## 평가 기준

| 기준 | 우수 | 적절 | 개선 필요 |
| ---- | ---- | ---- | -------- |
| HTTP 트리거 생성 | 릴레이를 켜고 끄는 두 개의 트리거를 적절한 이름으로 생성함 | 적절한 이름으로 하나의 트리거를 생성함 | 트리거를 생성하지 못함 |
| HTTP 트리거로 릴레이 제어 | 두 트리거를 IoT Hub에 연결하고 릴레이를 적절히 제어함 | 하나의 트리거를 IoT Hub에 연결하고 릴레이를 적절히 제어함 | 트리거를 IoT Hub에 연결하지 못함 |

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전이 권위 있는 출처로 간주되어야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.