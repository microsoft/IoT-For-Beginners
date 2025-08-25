<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-24T21:01:00+00:00",
  "source_file": "clean-up.md",
  "language_code": "ko"
}
-->
# 프로젝트 정리하기

각 프로젝트를 완료한 후에는 클라우드 리소스를 삭제하는 것이 좋습니다.

각 프로젝트의 강의에서 다음과 같은 리소스를 생성했을 수 있습니다:

* 리소스 그룹
* IoT 허브
* IoT 디바이스 등록
* 스토리지 계정
* Functions 앱
* Azure Maps 계정
* 커스텀 비전 프로젝트
* Azure 컨테이너 레지스트리
* 인공지능 서비스 리소스

이 리소스들 대부분은 비용이 들지 않습니다. 완전히 무료이거나, 무료 계층을 사용하고 있을 가능성이 높습니다. 유료 계층이 필요한 서비스의 경우에도 무료 허용량 내에서 사용했거나, 몇 센트 정도의 비용만 발생했을 것입니다.

비용이 상대적으로 낮더라도, 작업이 끝난 후에는 이러한 리소스를 삭제하는 것이 좋습니다. 예를 들어, 무료 계층을 사용하는 IoT 허브는 하나만 생성할 수 있으므로, 새로 생성하려면 유료 계층을 사용해야 할 수도 있습니다.

모든 서비스는 리소스 그룹 내에서 생성되었으며, 이를 통해 관리가 더 쉬워집니다. 리소스 그룹을 삭제하면 해당 리소스 그룹 내의 모든 서비스가 함께 삭제됩니다.

리소스 그룹을 삭제하려면, 터미널 또는 명령 프롬프트에서 다음 명령을 실행하세요:

```sh
az group delete --name <resource-group-name>
```

`<resource-group-name>`을 삭제하려는 리소스 그룹의 이름으로 바꿔주세요.

확인 메시지가 나타납니다:

```output
Are you sure you want to perform this operation? (y/n): 
```

`y`를 입력하여 리소스 그룹 삭제를 확인하세요.

모든 서비스를 삭제하는 데 시간이 걸릴 수 있습니다.

> 💁 리소스 그룹 삭제에 대한 자세한 내용은 [Microsoft Docs의 Azure Resource Manager 리소스 그룹 및 리소스 삭제 문서](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)에서 확인할 수 있습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.