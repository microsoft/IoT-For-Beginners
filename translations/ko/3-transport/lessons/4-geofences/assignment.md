<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-25T00:43:54+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "ko"
}
-->
# Twilio를 사용하여 알림 보내기

## 지침

현재 코드에서는 지오펜스까지의 거리를 로그로 기록하기만 했습니다. 이번 과제에서는 GPS 좌표가 지오펜스 내부에 있을 때 문자 메시지 또는 이메일로 알림을 추가해야 합니다.

Azure Functions는 Twilio와 같은 타사 서비스와의 바인딩을 포함하여 다양한 바인딩 옵션을 제공합니다.

* [Twilio.com](https://www.twilio.com)에서 무료 계정을 등록하세요.
* [Microsoft docs Twilio binding for Azure Functions page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python)에서 Azure Functions를 Twilio SMS에 바인딩하는 방법에 대한 문서를 읽어보세요.
* [Microsoft docs Azure Functions SendGrid bindings page](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python)에서 Azure Functions를 Twilio SendGrid에 바인딩하여 이메일을 보내는 방법에 대한 문서를 읽어보세요.
* GPS 좌표가 지오펜스 내부 또는 외부에 있을 때 알림을 받을 수 있도록 Functions 앱에 바인딩을 추가하세요. 단, 두 경우 모두 알림을 받는 것은 제외합니다.

## 평가 기준

| 기준 | 우수 | 적절 | 개선 필요 |
| -------- | --------- | -------- | ----------------- |
| 함수 바인딩을 구성하고 이메일 또는 SMS를 수신 | 함수 바인딩을 구성하고 지오펜스 내부 또는 외부에 있을 때 이메일 또는 SMS를 성공적으로 수신했으나, 두 경우 모두는 아님 | 바인딩을 구성했으나 이메일 또는 SMS를 보내는 데 실패했거나, 좌표가 내부와 외부 모두일 때만 보낼 수 있었음 | 바인딩을 구성하고 이메일 또는 SMS를 보내는 데 실패 |

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.