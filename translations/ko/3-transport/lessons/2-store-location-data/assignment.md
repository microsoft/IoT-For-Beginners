<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T01:07:45+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ko"
}
-->
# 함수 바인딩 조사

## 지침

함수 바인딩을 사용하면 `main` 함수에서 반환된 데이터를 블롭 스토리지에 저장할 수 있습니다. Azure Storage 계정, 컬렉션 및 기타 세부 사항은 `function.json` 파일에서 구성됩니다.

Azure 또는 기타 Microsoft 기술을 다룰 때 가장 신뢰할 수 있는 정보 출처는 [Microsoft 문서 docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn)입니다. 이 과제에서는 Azure Functions 바인딩 문서를 읽고 출력 바인딩을 설정하는 방법을 알아내야 합니다.

시작하기 위해 참고할 만한 페이지는 다음과 같습니다:

* [Azure Functions 트리거 및 바인딩 개념](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Functions용 Azure Blob 스토리지 바인딩 개요](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Functions용 Azure Blob 스토리지 출력 바인딩](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## 평가 기준

| 기준 | 우수 | 적절 | 개선 필요 |
| ---- | ---- | ---- | -------- |
| 블롭 스토리지 출력 바인딩 구성 | 출력 바인딩을 성공적으로 구성하고, 블롭을 반환하며 블롭 스토리지에 저장할 수 있었음 | 출력 바인딩을 구성하거나 블롭을 반환할 수 있었으나 블롭 스토리지에 저장하지 못했음 | 출력 바인딩을 구성하지 못했음 |

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보에 대해서는 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.