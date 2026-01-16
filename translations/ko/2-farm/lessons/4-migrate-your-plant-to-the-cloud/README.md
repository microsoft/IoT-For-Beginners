<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-24T22:46:41+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "ko"
}
-->
# 클라우드로 식물 시스템 이전하기

![이 강의의 스케치노트 개요](../../../../../translated_images/ko/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.jpg)

> 스케치노트: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

이 강의는 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn)의 [IoT for Beginners 프로젝트 2 - 디지털 농업 시리즈](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) 일부로 진행되었습니다.

[![Azure IoT Hub로 디바이스를 클라우드에 연결하기](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## 소개

지난 강의에서는 식물을 MQTT 브로커에 연결하고 로컬에서 실행되는 서버 코드를 통해 릴레이를 제어하는 방법을 배웠습니다. 이는 가정에서 개별 식물부터 상업용 농장까지 사용되는 인터넷 연결 자동 급수 시스템의 핵심을 형성합니다.

IoT 디바이스는 원리를 설명하기 위해 공용 MQTT 브로커와 통신했지만, 이는 가장 신뢰할 수 있거나 안전한 방법은 아닙니다. 이번 강의에서는 클라우드와 공용 클라우드 서비스가 제공하는 IoT 기능에 대해 배우고, 공용 MQTT 브로커에서 이러한 클라우드 서비스 중 하나로 식물을 이전하는 방법을 배울 것입니다.

이번 강의에서는 다음 내용을 다룹니다:

* [클라우드란 무엇인가?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [클라우드 구독 생성하기](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [클라우드 IoT 서비스](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [클라우드에서 IoT 서비스 생성하기](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [IoT Hub와 통신하기](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [디바이스를 IoT 서비스에 연결하기](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## 클라우드란 무엇인가?

클라우드 이전에는 회사가 직원들에게 데이터베이스나 파일 저장소 같은 서비스를 제공하거나, 대중에게 웹사이트 같은 서비스를 제공하려면 데이터 센터를 구축하고 운영해야 했습니다. 이는 소수의 컴퓨터가 있는 방에서부터 수많은 컴퓨터가 있는 건물까지 다양했습니다. 회사는 다음과 같은 모든 것을 관리해야 했습니다:

* 컴퓨터 구매
* 하드웨어 유지보수
* 전력 및 냉각
* 네트워킹
* 보안 (건물 보안 및 컴퓨터 소프트웨어 보안 포함)
* 소프트웨어 설치 및 업데이트

이 과정은 매우 비용이 많이 들고, 다양한 기술을 가진 직원이 필요하며, 필요에 따라 빠르게 변경하기 어렵습니다. 예를 들어, 온라인 상점이 바쁜 휴가 시즌을 계획하려면 몇 달 전에 하드웨어를 추가로 구매하고, 이를 구성하고, 소프트웨어를 설치해야 했습니다. 휴가 시즌이 끝나고 판매량이 감소하면, 구매한 컴퓨터는 다음 바쁜 시즌까지 유휴 상태로 남게 됩니다.

✅ 이런 방식이 회사가 빠르게 움직이는 것을 가능하게 할까요? 예를 들어, 한 온라인 의류 소매점이 유명인이 그들의 옷을 입은 덕분에 갑자기 인기를 얻었다면, 갑작스러운 주문 증가를 지원하기 위해 컴퓨팅 파워를 충분히 빠르게 늘릴 수 있을까요?

### 다른 사람의 컴퓨터

클라우드는 종종 농담으로 '다른 사람의 컴퓨터'라고 불립니다. 초기 아이디어는 간단했습니다 - 컴퓨터를 구매하는 대신, 다른 사람의 컴퓨터를 임대하는 것입니다. 클라우드 컴퓨팅 제공업체가 거대한 데이터 센터를 관리하며, 하드웨어 구매 및 설치, 전력 및 냉각 관리, 네트워킹, 건물 보안, 하드웨어 및 소프트웨어 업데이트 등을 책임집니다. 고객은 필요에 따라 컴퓨터를 임대하고, 수요가 증가하면 더 많이 임대하며, 수요가 감소하면 임대 수를 줄일 수 있습니다. 이러한 클라우드 데이터 센터는 전 세계에 분포해 있습니다.

![Microsoft 클라우드 데이터 센터](../../../../../translated_images/ko/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.png)
![Microsoft 클라우드 데이터 센터 확장 계획](../../../../../translated_images/ko/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.png)

이 데이터 센터는 수 킬로미터에 달하는 크기를 가질 수 있습니다. 위 이미지는 몇 년 전 Microsoft 클라우드 데이터 센터에서 촬영된 것으로, 초기 크기와 확장 계획을 보여줍니다. 확장을 위해 정리된 지역은 5제곱킬로미터가 넘습니다.

> 💁 이러한 데이터 센터는 매우 많은 전력을 필요로 하기 때문에 일부는 자체 발전소를 보유하고 있습니다. 클라우드 제공업체의 투자 수준과 규모로 인해, 이들은 일반적으로 매우 환경 친화적입니다. 소규모 데이터 센터보다 더 효율적이며, 대부분 재생 가능 에너지로 운영되고, 폐기물 감소, 물 사용 절감, 데이터 센터 건설을 위해 벌목된 숲을 복원하는 데 힘씁니다. 클라우드 제공업체가 지속 가능성을 위해 노력하는 방법에 대해 더 알고 싶다면 [Azure 지속 가능성 사이트](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn)를 참조하세요.

✅ 조사해보세요: [Microsoft의 Azure](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn)나 [Google의 GCP](https://cloud.google.com) 같은 주요 클라우드에 대해 읽어보세요. 이들이 몇 개의 데이터 센터를 보유하고 있으며, 어디에 위치해 있는지 알아보세요.

클라우드를 사용하면 회사의 비용을 절감하고, 클라우드 컴퓨팅 전문성을 제공업체에 맡기면서 본업에 집중할 수 있습니다. 회사는 더 이상 데이터 센터 공간을 임대하거나 구매할 필요가 없으며, 연결 및 전력을 위해 여러 제공업체에 비용을 지불하거나 전문가를 고용할 필요가 없습니다. 대신, 클라우드 제공업체에 월별 요금을 지불하면 모든 것이 처리됩니다.

클라우드 제공업체는 대량 구매를 통해 비용을 절감하고, 유지보수를 위한 도구에 투자하며, 심지어 자체 하드웨어를 설계하고 제작하여 클라우드 서비스를 개선합니다.

### Microsoft Azure

Azure는 Microsoft의 개발자 클라우드로, 이번 강의에서 사용할 클라우드입니다. 아래 영상은 Azure에 대한 간단한 개요를 제공합니다:

[![Azure 개요 영상](../../../../../translated_images/ko/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## 클라우드 구독 생성하기

클라우드 서비스를 사용하려면 클라우드 제공업체와 구독을 등록해야 합니다. 이번 강의에서는 Microsoft Azure 구독을 등록할 것입니다. 이미 Azure 구독이 있다면 이 작업을 건너뛸 수 있습니다. 여기 설명된 구독 세부 정보는 작성 시점 기준으로 정확하지만, 변경될 수 있습니다.

> 💁 학교를 통해 이 강의를 수강 중이라면, 이미 Azure 구독이 제공될 수 있습니다. 담당 교사에게 확인하세요.

Azure 구독에는 두 가지 무료 옵션이 있습니다:

* **Azure for Students** - 18세 이상의 학생을 위한 구독입니다. 신용카드가 필요 없으며, 학교 이메일 주소를 사용해 학생임을 인증합니다. 가입 시 클라우드 리소스에 사용할 수 있는 미화 $100와 IoT 서비스의 무료 버전을 제공합니다. 이 구독은 12개월 동안 유효하며, 학생 신분이 유지되는 한 매년 갱신할 수 있습니다.

* **Azure 무료 구독** - 학생이 아닌 모든 사람을 위한 구독입니다. 구독 등록 시 신용카드가 필요하지만, 이는 본인 인증을 위한 것이며 요금이 청구되지는 않습니다. 가입 시 첫 30일 동안 사용할 수 있는 $200 크레딧과 Azure 서비스의 무료 티어를 제공합니다. 크레딧이 소진되면, 유료 구독으로 전환하지 않는 한 요금이 청구되지 않습니다.

> 💁 Microsoft는 18세 미만 학생을 위한 Azure for Students Starter 구독을 제공하지만, 작성 시점 기준으로 IoT 서비스를 지원하지 않습니다.

### 작업 - 무료 클라우드 구독 등록하기

18세 이상의 학생이라면 Azure for Students 구독에 가입할 수 있습니다. 학교 이메일 주소로 인증해야 합니다. 두 가지 방법 중 하나를 선택할 수 있습니다:

* [education.github.com/pack](https://education.github.com/pack)에서 GitHub 학생 개발자 팩에 가입하세요. 이 팩은 GitHub 및 Microsoft Azure를 포함한 다양한 도구와 혜택을 제공합니다. 개발자 팩에 가입한 후, Azure for Students 혜택을 활성화할 수 있습니다.

* [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn)에서 Azure for Students 계정에 직접 가입하세요.

> ⚠️ 학교 이메일 주소가 인식되지 않는 경우, [이 저장소에 이슈를 제기](https://github.com/Microsoft/IoT-For-Beginners/issues)하여 Azure for Students 허용 목록에 추가할 수 있는지 확인하세요.

학생이 아니거나 유효한 학교 이메일 주소가 없는 경우, Azure 무료 구독에 가입할 수 있습니다.

* [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)에서 Azure 무료 구독에 가입하세요.

## 클라우드 IoT 서비스

지금까지 사용한 공용 테스트 MQTT 브로커는 학습용으로 훌륭한 도구이지만, 상업적 환경에서 사용하기에는 몇 가지 단점이 있습니다:

* 신뢰성 - 무료 서비스로 보장이 없으며, 언제든 종료될 수 있습니다.
* 보안 - 공용이므로 누구나 텔레메트리를 듣거나 하드웨어를 제어하는 명령을 보낼 수 있습니다.
* 성능 - 소수의 테스트 메시지만 처리하도록 설계되어, 대량의 메시지를 처리하기 어렵습니다.
* 디스커버리 - 연결된 디바이스를 확인할 방법이 없습니다.

클라우드 IoT 서비스는 이러한 문제를 해결합니다. 대규모 클라우드 제공업체가 유지보수를 담당하며, 신뢰성을 높이고 발생할 수 있는 문제를 해결합니다. 보안이 기본적으로 포함되어 있어 해커가 데이터를 읽거나 잘못된 명령을 보내는 것을 방지합니다. 또한, 클라우드의 확장성을 활용하여 하루에 수백만 개의 메시지를 처리할 수 있는 높은 성능을 제공합니다.

> 💁 이러한 장점은 월별 요금으로 제공되지만, 대부분의 클라우드 제공업체는 하루 메시지 수나 연결 가능한 디바이스 수에 제한이 있는 무료 IoT 서비스 버전을 제공합니다. 이 무료 버전은 개발자가 서비스를 학습하기에 충분합니다. 이번 강의에서는 무료 버전을 사용할 것입니다.

IoT 디바이스는 디바이스 SDK(서비스 기능과 작업하는 코드를 제공하는 라이브러리)를 사용하거나, MQTT 또는 HTTP와 같은 통신 프로토콜을 통해 클라우드 서비스에 연결합니다. 디바이스 SDK는 일반적으로 가장 쉬운 방법으로, 보안 처리, 게시 및 구독할 주제 관리 등을 자동으로 처리합니다.

![디바이스는 디바이스 SDK를 사용해 서비스에 연결합니다. 서버 코드는 SDK를 통해 서비스에 연결합니다.](../../../../../translated_images/ko/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.png)

디바이스는 이후 서비스와 통신하며, 이는 MQTT를 통해 텔레메트리를 보내고 명령을 받는 방식과 유사합니다. 서비스 SDK 또는 유사한 라이브러리를 사용해 애플리케이션의 다른 구성 요소가 디바이스와 통신합니다. 디바이스에서 서비스로 메시지가 전송되면, 애플리케이션의 다른 구성 요소가 이를 읽고, 다시 디바이스로 메시지를 보낼 수 있습니다.

![유효한 비밀 키가 없는 디바이스는 IoT 서비스에 연결할 수 없습니다.](../../../../../translated_images/ko/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.png)

이러한 서비스는 연결하거나 데이터를 전송할 수 있는 모든 디바이스를 사전에 등록하거나, 디바이스가 처음 연결할 때 자신을 등록할 수 있는 비밀 키나 인증서를 제공함으로써 보안을 구현합니다. 등록되지 않은 디바이스는 연결할 수 없으며, 서비스는 이들의 연결 시도를 거부하고 보낸 메시지를 무시합니다.

✅ 조사해보세요: 모든 디바이스나 코드가 연결할 수 있는 개방형 IoT 서비스를 운영하는 단점은 무엇일까요? 해커가 이를 악용한 구체적인 사례를 찾아보세요.

애플리케이션의 다른 구성 요소는 IoT 서비스에 연결하여 연결되거나 등록된 모든 디바이스를 확인하고, 개별적으로 또는 대량으로 직접 통신할 수 있습니다.
💁 IoT 서비스는 추가적인 기능도 구현하며, 클라우드 제공업체는 서비스에 연결할 수 있는 추가 서비스와 애플리케이션을 제공합니다. 예를 들어, 모든 디바이스에서 전송된 텔레메트리 메시지를 데이터베이스에 저장하고 싶다면, 클라우드 제공업체의 설정 도구에서 몇 번의 클릭만으로 서비스를 데이터베이스에 연결하고 데이터를 스트리밍할 수 있습니다.
## 클라우드에서 IoT 서비스 생성하기

이제 Azure 구독을 보유하고 있으니, IoT 서비스를 등록할 수 있습니다. Microsoft의 IoT 서비스는 Azure IoT Hub라고 불립니다.

![Azure IoT Hub 로고](../../../../../translated_images/ko/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.png)

아래 영상은 Azure IoT Hub에 대한 간단한 개요를 제공합니다:

[![Azure IoT Hub 개요 영상](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 위 이미지를 클릭하여 영상을 시청하세요

✅ 시간을 내어 [Microsoft IoT Hub 문서](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn)에서 IoT Hub 개요를 읽고 조사해 보세요.

Azure에서 제공되는 클라우드 서비스는 웹 기반 포털이나 명령줄 인터페이스(CLI)를 통해 구성할 수 있습니다. 이번 과제에서는 CLI를 사용합니다.

### 과제 - Azure CLI 설치하기

Azure CLI를 사용하려면 먼저 PC나 Mac에 설치해야 합니다.

1. [Azure CLI 문서](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn)의 지침을 따라 CLI를 설치하세요.

1. Azure CLI는 다양한 Azure 서비스를 관리할 수 있는 기능을 추가하는 여러 확장을 지원합니다. 명령줄 또는 터미널에서 다음 명령어를 실행하여 IoT 확장을 설치하세요:

    ```sh
    az extension add --name azure-iot
    ```

1. 명령줄 또는 터미널에서 다음 명령어를 실행하여 Azure CLI를 통해 Azure 구독에 로그인하세요.

    ```sh
    az login
    ```

    기본 브라우저에서 웹 페이지가 열립니다. Azure 구독에 가입할 때 사용한 계정으로 로그인하세요. 로그인 후 브라우저 탭을 닫을 수 있습니다.

1. 학교에서 제공된 구독이나 개인 Azure for Students 구독 등 여러 Azure 구독이 있는 경우, 사용할 구독을 선택해야 합니다. 다음 명령어를 실행하여 접근 가능한 모든 구독을 나열하세요:

    ```sh
    az account list --output table
    ```

    출력에서 각 구독의 이름과 `SubscriptionId`를 확인할 수 있습니다.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    사용할 구독을 선택하려면 다음 명령어를 사용하세요:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    `<SubscriptionId>`를 사용하려는 구독의 Id로 바꾸세요. 이 명령어를 실행한 후 계정을 나열하는 명령어를 다시 실행하면, `IsDefault` 열이 `True`로 표시된 구독이 방금 설정한 구독임을 확인할 수 있습니다.

### 과제 - 리소스 그룹 생성하기

Azure 서비스(예: IoT Hub 인스턴스, 가상 머신, 데이터베이스, AI 서비스 등)는 **리소스**라고 합니다. 모든 리소스는 하나 이상의 리소스를 논리적으로 그룹화한 **리소스 그룹**에 속해야 합니다.

> 💁 리소스 그룹을 사용하면 여러 서비스를 한 번에 관리할 수 있습니다. 예를 들어, 이 프로젝트의 모든 수업을 마친 후 리소스 그룹을 삭제하면 해당 그룹 내의 모든 리소스가 자동으로 삭제됩니다.

1. Azure 데이터 센터는 전 세계에 여러 지역으로 나뉘어 있습니다. Azure 리소스나 리소스 그룹을 생성할 때, 생성할 위치를 지정해야 합니다. 다음 명령어를 실행하여 위치 목록을 확인하세요:

    ```sh
    az account list-locations --output table
    ```

    위치 목록이 표시됩니다. 이 목록은 길게 나올 수 있습니다.

    > 💁 작성 시점 기준으로, 배포 가능한 위치는 65곳입니다.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    자신과 가장 가까운 지역의 `Name` 열 값을 기록하세요. 지역은 [Azure 지리적 위치 페이지](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn)에서 지도로 확인할 수 있습니다.

1. `soil-moisture-sensor`라는 이름의 리소스 그룹을 생성하려면 다음 명령어를 실행하세요. 리소스 그룹 이름은 구독 내에서 고유해야 합니다.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    `<location>`을 이전 단계에서 선택한 위치로 바꾸세요.

### 과제 - IoT Hub 생성하기

이제 리소스 그룹에 IoT Hub 리소스를 생성할 수 있습니다.

1. 다음 명령어를 사용하여 IoT Hub 리소스를 생성하세요:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    `<hub_name>`을 허브 이름으로 바꾸세요. 이 이름은 전 세계적으로 고유해야 하며, 다른 사람이 생성한 IoT Hub와 동일한 이름을 사용할 수 없습니다. 이 이름은 허브를 가리키는 URL에 사용되므로 고유해야 합니다. 예를 들어 `soil-moisture-sensor-` 뒤에 고유 식별자(랜덤 단어 또는 이름)를 추가하세요.

    `--sku F1` 옵션은 무료 계층을 사용하도록 지정합니다. 무료 계층은 하루 8,000개의 메시지를 지원하며, 유료 계층의 대부분의 기능을 제공합니다.

    > 🎓 Azure 서비스의 다양한 가격 수준은 계층(tiers)으로 불립니다. 각 계층은 비용과 제공하는 기능 또는 데이터 용량이 다릅니다.

    > 💁 가격에 대해 더 알고 싶다면 [Azure IoT Hub 가격 가이드](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn)를 확인하세요.

    `--partition-count 2` 옵션은 IoT Hub가 지원하는 데이터 스트림 수를 정의합니다. 더 많은 파티션은 여러 장치가 IoT Hub에서 데이터를 읽고 쓸 때 데이터 차단을 줄여줍니다. 파티션은 이 수업의 범위를 벗어나지만, 무료 계층 IoT Hub를 생성하려면 이 값을 설정해야 합니다.

    > 💁 구독당 하나의 무료 계층 IoT Hub만 생성할 수 있습니다.

IoT Hub가 생성됩니다. 완료까지 1분 정도 소요될 수 있습니다.

## IoT Hub와 통신하기

이전 수업에서는 MQTT를 사용하여 서로 다른 주제로 메시지를 주고받았습니다. IoT Hub는 주제를 나누는 대신, 장치와 허브 간 통신을 위한 여러 정의된 방법을 제공합니다.

> 💁 IoT Hub와 장치 간의 통신은 MQTT, HTTPS 또는 AMQP를 사용할 수 있습니다.

* 장치에서 클라우드로(D2C) 메시지 - 장치에서 IoT Hub로 전송되는 메시지(예: 텔레메트리). 애플리케이션 코드에서 IoT Hub의 메시지를 읽을 수 있습니다.

    > 🎓 IoT Hub는 내부적으로 [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn)라는 Azure 서비스를 사용합니다. 허브로 전송된 메시지를 읽는 코드를 작성할 때, 이를 이벤트라고 부르는 경우가 많습니다.

* 클라우드에서 장치로(C2D) 메시지 - 애플리케이션 코드에서 IoT Hub를 통해 IoT 장치로 전송되는 메시지

* 직접 메서드 요청 - 애플리케이션 코드에서 IoT Hub를 통해 IoT 장치로 전송되어 장치가 특정 작업(예: 액추에이터 제어)을 수행하도록 요청하는 메시지. 이 메시지는 응답이 필요하며, 애플리케이션 코드에서 성공적으로 처리되었는지 확인할 수 있습니다.

* 장치 트윈 - JSON 문서로, 장치와 IoT Hub 간 동기화되며, 장치에서 보고된 설정이나 IoT Hub에서 장치에 설정해야 할 속성(원하는 값)을 저장하는 데 사용됩니다.

IoT Hub는 메시지와 직접 메서드 요청을 구성 가능한 기간 동안 저장할 수 있습니다(기본값은 하루). 따라서 장치나 애플리케이션 코드가 연결이 끊어져도, 다시 연결되었을 때 오프라인 상태에서 전송된 메시지를 검색할 수 있습니다. 장치 트윈은 IoT Hub에 영구적으로 저장되므로, 장치는 언제든 다시 연결하여 최신 장치 트윈을 가져올 수 있습니다.

✅ 조사해 보세요: IoT Hub 문서의 [장치에서 클라우드로 통신 가이드](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn)와 [클라우드에서 장치로 통신 가이드](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn)를 읽어보세요.

## IoT 장치를 IoT 서비스에 연결하기

허브가 생성되면 IoT 장치가 허브에 연결할 수 있습니다. 등록된 장치만 서비스에 연결할 수 있으므로, 먼저 장치를 등록해야 합니다. 등록 후 장치가 연결에 사용할 수 있는 연결 문자열을 받을 수 있습니다. 이 연결 문자열은 장치별로 고유하며, IoT Hub, 장치, 비밀 키에 대한 정보를 포함합니다.

> 🎓 연결 문자열은 연결 세부 정보를 포함하는 텍스트 조각을 나타내는 일반적인 용어입니다. 이는 IoT Hub, 데이터베이스 및 기타 여러 서비스에 연결할 때 사용됩니다. 일반적으로 서비스 식별자(예: URL)와 비밀 키와 같은 보안 정보를 포함합니다. SDK에 전달하여 서비스에 연결합니다.

> ⚠️ 연결 문자열은 안전하게 보관해야 합니다! 보안에 대한 자세한 내용은 이후 수업에서 다룹니다.

### 과제 - IoT 장치 등록하기

IoT 장치는 Azure CLI를 사용하여 IoT Hub에 등록할 수 있습니다.

1. 다음 명령어를 실행하여 장치를 등록하세요:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꾸세요.

    이 명령어는 `soil-moisture-sensor`라는 ID를 가진 장치를 생성합니다.

1. IoT 장치가 SDK를 사용하여 IoT Hub에 연결할 때, 허브의 URL과 비밀 키를 포함한 연결 문자열이 필요합니다. 다음 명령어를 실행하여 연결 문자열을 가져오세요:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꾸세요.

1. 출력에 표시된 연결 문자열을 저장하세요. 나중에 필요합니다.

### 과제 - IoT 장치를 클라우드에 연결하기

IoT 장치를 클라우드에 연결하는 관련 가이드를 따라 작업하세요:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [싱글 보드 컴퓨터 - Raspberry Pi/가상 IoT 장치](single-board-computer-connect-hub.md)

### 과제 - 이벤트 모니터링하기

현재는 서버 코드를 업데이트하지 않습니다. 대신 Azure CLI를 사용하여 IoT 장치에서 전송된 이벤트를 모니터링할 수 있습니다.

1. IoT 장치가 실행 중이며 토양 수분 텔레메트리 값을 전송하고 있는지 확인하세요.

1. 명령 프롬프트 또는 터미널에서 다음 명령어를 실행하여 IoT Hub로 전송된 메시지를 모니터링하세요:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꾸세요.

    IoT 장치에서 전송된 메시지가 콘솔 출력에 나타납니다.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    `payload`의 내용은 IoT 장치에서 전송된 메시지와 일치합니다.

    > 작성 시점 기준으로, Apple Silicon에서 `az iot` 확장이 완전히 작동하지 않을 수 있습니다. Apple Silicon 장치를 사용하는 경우, [Visual Studio Code용 Azure IoT 도구](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging)를 사용하여 메시지를 모니터링하는 등 다른 방법을 사용해야 합니다.

1. 이러한 메시지에는 자동으로 첨부된 여러 속성(예: 전송된 타임스탬프)이 있습니다. 이를 *주석(annotations)*이라고 합니다. 모든 메시지 주석을 보려면 다음 명령어를 사용하세요:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꾸세요.

    IoT 장치에서 전송된 메시지가 콘솔 출력에 나타납니다.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    주석의 시간 값은 [UNIX 시간](https://wikipedia.org/wiki/Unix_time)으로, 1970년 1월 1일 자정 이후의 초를 나타냅니다.

    작업이 끝나면 이벤트 모니터를 종료하세요.

### 과제 - IoT 장치 제어하기

Azure CLI를 사용하여 IoT 장치에서 직접 메서드를 호출할 수도 있습니다.

1. 명령 프롬프트 또는 터미널에서 다음 명령어를 실행하여 IoT 장치에서 `relay_on` 메서드를 호출하세요:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    `
<hub_name>
`를 사용하여 IoT Hub의 이름을 입력하세요.

이 명령은 `method-name`으로 지정된 메서드에 대한 직접 메서드 요청을 보냅니다. 직접 메서드는 메서드에 필요한 데이터를 포함하는 페이로드를 받을 수 있으며, 이는 JSON 형식으로 `method-payload` 매개변수에 지정할 수 있습니다.

릴레이가 켜지는 것을 확인할 수 있으며, IoT 디바이스에서 해당 출력이 표시됩니다:

```output
    Direct method received -  relay_on
    ```

1. 위 단계를 반복하되, `--method-name`을 `relay_off`로 설정하세요. 릴레이가 꺼지는 것을 확인할 수 있으며, IoT 디바이스에서 해당 출력이 표시됩니다.

---

## 🚀 도전 과제

IoT Hub의 무료 요금제는 하루에 8,000개의 메시지를 허용합니다. 작성한 코드는 10초마다 텔레메트리 메시지를 전송합니다. 10초마다 한 번씩 메시지를 전송하면 하루에 몇 개의 메시지가 전송될까요?

토양 수분 측정을 얼마나 자주 전송해야 할지 생각해 보세요. 무료 요금제 내에서 필요한 만큼 자주 확인하되 너무 자주 확인하지 않도록 코드를 어떻게 변경할 수 있을까요? 두 번째 디바이스를 추가하고 싶다면 어떻게 해야 할까요?

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## 복습 및 자기 학습

IoT Hub SDK는 Arduino와 Python 모두에 대해 오픈 소스로 제공됩니다. GitHub의 코드 저장소에는 다양한 IoT Hub 기능을 사용하는 방법을 보여주는 여러 샘플이 있습니다.

* Wio Terminal을 사용하는 경우, [GitHub의 Arduino 샘플](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)을 확인하세요.
* Raspberry Pi 또는 가상 디바이스를 사용하는 경우, [GitHub의 Python 샘플](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)을 확인하세요.

## 과제

[클라우드 서비스에 대해 배우기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.