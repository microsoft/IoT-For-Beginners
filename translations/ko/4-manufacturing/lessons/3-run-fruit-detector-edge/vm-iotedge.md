<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-24T21:46:26+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "ko"
}
-->
# IoT Edge 가상 머신 생성하기

Azure에서는 가상 머신을 생성할 수 있습니다. 가상 머신은 클라우드에 있는 컴퓨터로, 원하는 대로 구성하고 소프트웨어를 실행할 수 있습니다.

> 💁 가상 머신에 대한 자세한 내용은 [위키백과의 가상 머신 페이지](https://wikipedia.org/wiki/Virtual_machine)에서 확인할 수 있습니다.

## 작업 - IoT Edge 가상 머신 설정하기

1. Azure IoT Edge가 미리 설치된 VM을 생성하려면 다음 명령어를 실행하세요:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    `<vm_name>`을 이 가상 머신의 이름으로 바꾸세요. 이 이름은 전 세계적으로 고유해야 하므로, `fruit-quality-detector-vm-` 뒤에 본인의 이름이나 다른 값을 추가하여 사용하세요.

    `<username>`과 `<password>`를 VM에 로그인할 때 사용할 사용자 이름과 비밀번호로 바꾸세요. 이 값들은 비교적 안전해야 하므로, admin/password와 같은 간단한 값은 사용할 수 없습니다.

    `<connection_string>`을 `fruit-quality-detector-edge` IoT Edge 디바이스의 연결 문자열로 바꾸세요.

    이 명령어는 `DS1 v2` 가상 머신으로 구성된 VM을 생성합니다. 이 카테고리는 머신의 성능과 비용을 나타냅니다. 이 VM은 1개의 CPU와 3.5GB의 RAM을 가지고 있습니다.

    > 💰 현재 VM의 가격은 [Azure 가상 머신 가격 가이드](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)에서 확인할 수 있습니다.

    VM이 생성되면 IoT Edge 런타임이 자동으로 설치되고, `fruit-quality-detector-edge` 디바이스로 IoT Hub에 연결되도록 구성됩니다.

1. 이미지 분류기를 호출하려면 VM의 IP 주소나 DNS 이름이 필요합니다. 다음 명령어를 실행하여 이를 확인하세요:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` 필드 또는 `Fqdns` 필드의 값을 복사하세요.

1. VM은 비용이 발생합니다. 작성 시점 기준으로 DS1 VM은 시간당 약 $0.06의 비용이 듭니다. 비용을 절감하려면 사용하지 않을 때 VM을 종료하고, 프로젝트가 끝나면 삭제하세요.

    VM이 매일 특정 시간에 자동으로 종료되도록 설정할 수 있습니다. 이렇게 하면 종료를 깜빡하더라도 자동 종료 시간까지만 비용이 청구됩니다. 다음 명령어를 사용하여 이를 설정하세요:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>`을 가상 머신의 이름으로 바꾸세요.

    `<shutdown_time_utc>`를 VM이 종료되길 원하는 UTC 시간으로 바꾸세요. 시간은 HHMM 형식의 4자리 숫자로 입력해야 합니다. 예를 들어, UTC 기준 자정에 종료하려면 `0000`으로 설정하세요. 미국 서부 시간으로 오후 7시 30분에 종료하려면 `0230`을 사용하세요 (미국 서부 시간 오후 7시 30분은 UTC 기준 오전 2시 30분입니다).

1. 이 엣지 디바이스에서 이미지 분류기가 실행되며, 기본적으로 포트 80(표준 HTTP 포트)을 사용합니다. 기본적으로 가상 머신은 인바운드 포트를 차단하므로, 포트 80을 활성화해야 합니다. 포트는 네트워크 보안 그룹에서 활성화되므로, 먼저 다음 명령어를 실행하여 VM의 네트워크 보안 그룹 이름을 확인하세요:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` 필드의 값을 복사하세요.

1. 다음 명령어를 실행하여 네트워크 보안 그룹에 포트 80을 여는 규칙을 추가하세요:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>`을 이전 단계에서 확인한 네트워크 보안 그룹 이름으로 바꾸세요.

### 작업 - 비용 절감을 위한 VM 관리

1. VM을 사용하지 않을 때는 종료해야 합니다. VM을 종료하려면 다음 명령어를 사용하세요:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>`을 가상 머신의 이름으로 바꾸세요.

    > 💁 `az vm stop` 명령어도 있지만, 이 명령어는 VM을 종료하면서도 컴퓨터를 계속 할당된 상태로 유지하므로, 여전히 실행 중인 것처럼 비용이 청구됩니다.

1. VM을 다시 시작하려면 다음 명령어를 사용하세요:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>`을 가상 머신의 이름으로 바꾸세요.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.