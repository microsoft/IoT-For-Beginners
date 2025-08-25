<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-24T21:45:19+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "ko"
}
-->
# 엣지에서 다른 서비스 실행하기

## 지침

엣지에서 실행할 수 있는 것은 이미지 분류기만이 아닙니다. 컨테이너로 패키징할 수 있는 모든 것은 IoT Edge 디바이스에 배포할 수 있습니다. 이전 강의에서 생성한 트리거와 같은 Azure Functions로 실행되는 서버리스 코드도 컨테이너에서 실행할 수 있으며, 따라서 IoT Edge에서 실행할 수 있습니다.

이전 강의 중 하나를 선택하여 Azure Functions 앱을 IoT Edge 컨테이너에서 실행해 보세요. 다른 Functions 앱 프로젝트를 사용하여 이를 수행하는 방법을 보여주는 가이드는 [튜토리얼: Azure Functions을 IoT Edge 모듈로 배포하기 (Microsoft Docs)](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11)에서 찾을 수 있습니다.

## 평가 기준

| 기준 | 우수 | 적절 | 개선 필요 |
| ---- | ---- | ---- | -------- |
| Azure Functions 앱을 IoT Edge에 배포 | Azure Functions 앱을 IoT Edge에 성공적으로 배포하고 IoT 디바이스와 함께 사용하여 IoT 데이터에서 트리거를 실행할 수 있었음 | Functions 앱을 IoT Edge에 배포할 수 있었으나 트리거를 실행시키는 데 실패함 | Functions 앱을 IoT Edge에 배포하지 못함 |

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.