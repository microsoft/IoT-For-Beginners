<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-24T22:26:09+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "ko"
}
-->
# 애플리케이션 로직을 클라우드로 마이그레이션하기

![이 강의의 스케치노트 개요](../../../../../translated_images/ko/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> 스케치노트: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

이 강의는 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn)의 [IoT for Beginners Project 2 - Digital Agriculture 시리즈](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) 일부로 진행되었습니다.

[![서버리스 코드로 IoT 디바이스 제어하기](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## 소개

지난 강의에서는 식물의 토양 수분 모니터링과 릴레이 제어를 클라우드 기반 IoT 서비스에 연결하는 방법을 배웠습니다. 다음 단계는 릴레이의 타이밍을 제어하는 서버 코드를 클라우드로 이동하는 것입니다. 이번 강의에서는 서버리스 함수를 사용하여 이를 수행하는 방법을 배웁니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [서버리스란 무엇인가?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [서버리스 애플리케이션 생성하기](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [IoT Hub 이벤트 트리거 생성하기](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [서버리스 코드에서 직접 메서드 요청 보내기](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [서버리스 코드를 클라우드에 배포하기](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## 서버리스란 무엇인가?

서버리스 또는 서버리스 컴퓨팅은 다양한 이벤트에 반응하여 클라우드에서 실행되는 작은 코드 블록을 만드는 것을 포함합니다. 이벤트가 발생하면 코드가 실행되며, 이벤트에 대한 데이터가 전달됩니다. 이러한 이벤트는 웹 요청, 큐에 추가된 메시지, 데이터베이스의 데이터 변경, 또는 IoT 디바이스가 IoT 서비스에 보낸 메시지 등 다양한 것에서 발생할 수 있습니다.

![IoT 서비스에서 서버리스 서비스로 이벤트가 전송되고, 여러 함수가 동시에 처리되는 모습](../../../../../translated_images/ko/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 데이터베이스 트리거를 사용해본 적이 있다면, 이를 이벤트(예: 행 삽입)에 의해 트리거되는 코드와 같은 것으로 생각할 수 있습니다.

![많은 이벤트가 동시에 전송될 때, 서버리스 서비스가 확장되어 모든 이벤트를 동시에 처리하는 모습](../../../../../translated_images/ko/serverless-scaling.f8c769adf0413fd1.webp)

코드는 이벤트가 발생할 때만 실행되며, 다른 시간에는 코드가 활성 상태로 유지되지 않습니다. 이벤트가 발생하면 코드가 로드되고 실행됩니다. 이는 서버리스가 매우 확장 가능하다는 것을 의미합니다. 많은 이벤트가 동시에 발생하면 클라우드 제공자가 필요한 만큼의 함수를 여러 서버에서 동시에 실행할 수 있습니다. 단점은 이벤트 간에 정보를 공유해야 할 경우, 메모리에 저장하는 대신 데이터베이스와 같은 곳에 저장해야 한다는 점입니다.

코드는 이벤트에 대한 세부 정보를 매개변수로 받는 함수로 작성됩니다. 서버리스 함수는 다양한 프로그래밍 언어로 작성할 수 있습니다.

> 🎓 서버리스는 Functions as a Service (FaaS)라고도 불리며, 각 이벤트 트리거가 코드에서 함수로 구현됩니다.

서버리스라는 이름에도 불구하고 실제로는 서버를 사용합니다. 이 이름은 개발자가 코드를 실행하는 데 필요한 서버에 대해 신경 쓰지 않고, 이벤트에 반응하여 코드가 실행된다는 점에 초점을 맞추기 때문입니다. 클라우드 제공자는 서버리스 *런타임*을 통해 서버, 네트워킹, 스토리지, CPU, 메모리 등 코드를 실행하는 데 필요한 모든 것을 관리합니다. 이 모델에서는 서버 단위로 비용을 지불하지 않고, 코드가 실행되는 시간과 사용된 메모리 양에 따라 비용을 지불합니다.

> 💰 서버리스는 클라우드에서 코드를 실행하는 가장 저렴한 방법 중 하나입니다. 예를 들어, 작성 시점 기준으로 한 클라우드 제공자는 모든 서버리스 함수가 한 달에 총 1,000,000번 실행되기 전까지 비용을 청구하지 않으며, 이후에는 1,000,000번 실행당 US$0.20를 청구합니다. 코드가 실행되지 않을 때는 비용이 발생하지 않습니다.

IoT 개발자로서 서버리스 모델은 이상적입니다. 클라우드에 연결된 IoT 디바이스가 보낸 메시지에 반응하여 호출되는 함수를 작성할 수 있습니다. 코드는 보낸 모든 메시지를 처리하지만 필요할 때만 실행됩니다.

✅ MQTT를 통해 메시지를 수신하는 서버 코드를 작성했던 것을 다시 살펴보세요. 이 코드가 서버리스로 클라우드에서 실행된다면 어떻게 될까요? 서버리스 컴퓨팅을 지원하기 위해 코드가 어떻게 변경될 수 있을지 생각해보세요.

> 💁 서버리스 모델은 코드 실행 외에도 다른 클라우드 서비스로 확장되고 있습니다. 예를 들어, 서버리스 데이터베이스는 요청당 비용을 지불하는 서버리스 가격 모델을 사용하여 클라우드에서 사용할 수 있습니다. 요청은 데이터베이스에 대한 쿼리 또는 삽입과 같은 작업을 포함하며, 요청을 처리하는 데 필요한 작업량에 따라 가격이 책정됩니다. 예를 들어, 기본 키를 기준으로 한 행을 선택하는 단순한 쿼리는 여러 테이블을 조인하고 수천 개의 행을 반환하는 복잡한 작업보다 비용이 적게 듭니다.

## 서버리스 애플리케이션 생성하기

Microsoft의 서버리스 컴퓨팅 서비스는 Azure Functions입니다.

![Azure Functions 로고](../../../../../translated_images/ko/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

아래 짧은 영상은 Azure Functions에 대한 개요를 제공합니다.

[![Azure Functions 개요 영상](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 위 이미지를 클릭하여 영상을 시청하세요.

✅ 잠시 시간을 내어 [Microsoft Azure Functions 문서](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn)에서 Azure Functions 개요를 읽어보세요.

Azure Functions를 작성하려면 원하는 언어로 Azure Functions 앱을 시작해야 합니다. Azure Functions는 기본적으로 Python, JavaScript, TypeScript, C#, F#, Java, Powershell을 지원합니다. 이번 강의에서는 Python으로 Azure Functions 앱을 작성하는 방법을 배웁니다.

> 💁 Azure Functions는 HTTP 요청을 지원하는 모든 언어로 함수를 작성할 수 있는 커스텀 핸들러도 지원합니다. 여기에는 COBOL과 같은 오래된 언어도 포함됩니다.

Functions 앱은 하나 이상의 *트리거*로 구성됩니다. 트리거는 이벤트에 반응하는 함수입니다. 하나의 Functions 앱 안에 여러 트리거를 포함할 수 있으며, 모두 공통 설정을 공유합니다. 예를 들어, Functions 앱의 설정 파일에 IoT Hub의 연결 정보를 포함할 수 있으며, 앱의 모든 함수가 이를 사용하여 연결하고 이벤트를 수신할 수 있습니다.

### 작업 - Azure Functions 도구 설치하기

> 작성 시점 기준으로, Apple Silicon에서 Python 프로젝트와 함께 Azure Functions 코드 도구가 완전히 작동하지 않습니다. Intel 기반 Mac, Windows PC 또는 Linux PC를 사용해야 합니다.

Azure Functions의 훌륭한 기능 중 하나는 로컬에서 실행할 수 있다는 점입니다. 클라우드에서 사용되는 동일한 런타임을 컴퓨터에서 실행할 수 있어, IoT 메시지에 반응하는 코드를 작성하고 로컬에서 실행할 수 있습니다. 이벤트가 처리되는 동안 코드를 디버깅할 수도 있습니다. 코드가 만족스러우면 클라우드에 배포할 수 있습니다.

Azure Functions 도구는 CLI로 제공되며, Azure Functions Core Tools로 알려져 있습니다.

1. [Azure Functions Core Tools 문서](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn)를 참고하여 Azure Functions Core Tools를 설치하세요.

1. VS Code용 Azure Functions 확장을 설치하세요. 이 확장은 Azure Functions 생성, 디버깅 및 배포를 지원합니다. [Azure Functions 확장 문서](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions)를 참고하여 VS Code에 이 확장을 설치하세요.

Azure Functions 앱을 클라우드에 배포할 때, 애플리케이션 파일과 로그 파일 같은 것을 저장하기 위해 소량의 클라우드 스토리지가 필요합니다. Functions 앱을 로컬에서 실행할 때는 실제 클라우드 스토리지를 사용하는 대신 [Azurite](https://github.com/Azure/Azurite)라는 스토리지 에뮬레이터를 사용할 수 있습니다. 이는 로컬에서 실행되지만 클라우드 스토리지처럼 작동합니다.

> 🎓 Azure에서 Azure Functions가 사용하는 스토리지는 Azure Storage Account입니다. 이 계정은 파일, 블롭, 테이블의 데이터 또는 큐의 데이터를 저장할 수 있습니다. 하나의 스토리지 계정을 Functions 앱과 웹 앱 같은 여러 앱에서 공유할 수 있습니다.

1. Azurite는 Node.js 앱이므로 Node.js를 설치해야 합니다. [Node.js 웹사이트](https://nodejs.org/)에서 다운로드 및 설치 지침을 확인하세요. Mac을 사용하는 경우 [Homebrew](https://formulae.brew.sh/formula/node)를 통해 설치할 수도 있습니다.

1. 다음 명령을 사용하여 Azurite를 설치하세요 (`npm`은 Node.js를 설치하면 함께 설치됩니다):

    ```sh
    npm install -g azurite
    ```

1. Azurite가 데이터를 저장할 폴더를 `azurite`라는 이름으로 생성하세요:

    ```sh
    mkdir azurite
    ```

1. Azurite를 실행하고 새 폴더를 전달하세요:

    ```sh
    azurite --location azurite
    ```

    Azurite 스토리지 에뮬레이터가 실행되며 로컬 Functions 런타임이 연결할 준비가 됩니다.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### 작업 - Azure Functions 프로젝트 생성하기

Azure Functions CLI를 사용하여 새 Functions 앱을 생성할 수 있습니다.

1. Functions 앱을 위한 폴더를 생성하고 해당 폴더로 이동하세요. 폴더 이름은 `soil-moisture-trigger`로 설정하세요.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. 이 폴더 안에 Python 가상 환경을 생성하세요:

    ```sh
    python3 -m venv .venv
    ```

1. 가상 환경을 활성화하세요:

    * Windows에서:
        * Command Prompt 또는 Windows Terminal의 Command Prompt를 사용하는 경우 다음 명령을 실행하세요:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell을 사용하는 경우 다음 명령을 실행하세요:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS 또는 Linux에서는 다음 명령을 실행하세요:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 이러한 명령은 가상 환경을 생성한 동일한 위치에서 실행해야 합니다. `.venv` 폴더로 이동할 필요는 없으며, 항상 가상 환경을 활성화하는 명령과 패키지 설치 또는 코드 실행 명령을 가상 환경을 생성한 폴더에서 실행해야 합니다.

1. 다음 명령을 실행하여 이 폴더에 Functions 앱을 생성하세요:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    이 명령은 현재 폴더에 세 개의 파일을 생성합니다:

    * `host.json` - 이 JSON 문서는 Functions 앱의 설정을 포함합니다. 이 설정을 수정할 필요는 없습니다.
    * `local.settings.json` - 이 JSON 문서는 IoT Hub의 연결 문자열과 같은 로컬 실행 시 앱이 사용할 설정을 포함합니다. 이 설정은 로컬에서만 사용되며 소스 코드 관리에 추가되지 않아야 합니다. 앱을 클라우드에 배포할 때 이 설정은 배포되지 않으며, 대신 애플리케이션 설정에서 로드됩니다. 이는 이후 강의에서 다룰 예정입니다.
    * `requirements.txt` - 이 파일은 [Pip 요구사항 파일](https://pip.pypa.io/en/stable/user_guide/#requirements-files)로, Functions 앱을 실행하는 데 필요한 Pip 패키지를 포함합니다.

1. `local.settings.json` 파일에는 Functions 앱이 사용할 스토리지 계정 설정이 포함되어 있습니다. 기본값은 빈 설정이므로 설정해야 합니다. Azurite 로컬 스토리지 에뮬레이터에 연결하려면 이 값을 다음으로 설정하세요:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. 요구사항 파일을 사용하여 필요한 Pip 패키지를 설치하세요:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 필요한 Pip 패키지는 이 파일에 있어야 하며, Functions 앱이 클라우드에 배포될 때 런타임이 올바른 패키지를 설치할 수 있도록 보장합니다.

1. 모든 것이 제대로 작동하는지 테스트하려면 Functions 런타임을 시작할 수 있습니다. 다음 명령을 실행하여 런타임을 시작하세요:

    ```sh
    func start
    ```

    런타임이 시작되고 작업 함수(트리거)를 찾지 못했다는 메시지가 표시됩니다.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ 방화벽 알림이 나타나면 액세스를 허용하세요. `func` 애플리케이션이 네트워크에 읽기 및 쓰기 권한을 필요로 하기 때문입니다.
> ⚠️ macOS를 사용하는 경우 출력에 경고가 표시될 수 있습니다:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Functions 앱이 올바르게 시작되고 실행 중인 함수가 나열되면 이러한 경고는 무시해도 됩니다. [Microsoft Docs Q&A의 이 질문](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn)에 언급된 대로 무시해도 괜찮습니다.

1. `ctrl+c`를 눌러 Functions 앱을 중지합니다.

1. 현재 폴더를 VS Code에서 엽니다. VS Code를 열고 이 폴더를 열거나 다음 명령을 실행하여 열 수 있습니다:

    ```sh
    code .
    ```

    VS Code는 Functions 프로젝트를 감지하고 다음과 같은 알림을 표시합니다:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![알림](../../../../../translated_images/ko/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    이 알림에서 **Yes**를 선택합니다.

1. VS Code 터미널에서 Python 가상 환경이 실행 중인지 확인합니다. 필요하면 종료 후 다시 시작하세요.

## IoT Hub 이벤트 트리거 생성

Functions 앱은 서버리스 코드를 실행하는 껍데기 역할을 합니다. IoT Hub 이벤트에 응답하려면 이 앱에 IoT Hub 트리거를 추가할 수 있습니다. 이 트리거는 IoT Hub로 전송된 메시지 스트림에 연결하고 이에 응답해야 합니다. 메시지 스트림을 얻으려면 트리거가 IoT Hub의 *Event Hub 호환 엔드포인트*에 연결해야 합니다.

IoT Hub는 Azure Event Hubs라는 또 다른 Azure 서비스를 기반으로 합니다. Event Hubs는 메시지를 송수신할 수 있는 서비스이며, IoT Hub는 IoT 디바이스를 위한 기능을 추가하여 이를 확장합니다. IoT Hub에서 메시지를 읽는 방식은 Event Hubs를 사용하는 방식과 동일합니다.

✅ 연구해보기: [Azure Event Hubs 문서](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn)에서 Event Hubs 개요를 읽어보세요. 기본 기능이 IoT Hub와 어떻게 비교되는지 확인하세요.

IoT 디바이스가 IoT Hub에 연결하려면 비밀 키를 사용해야 하며, 이를 통해 허용된 디바이스만 연결할 수 있습니다. 메시지를 읽기 위해 연결할 때도 마찬가지로, 코드에는 비밀 키와 IoT Hub 세부 정보가 포함된 연결 문자열이 필요합니다.

> 💁 기본적으로 제공되는 연결 문자열은 **iothubowner** 권한을 가지며, 이를 사용하는 코드는 IoT Hub에 대한 전체 권한을 갖게 됩니다. 이상적으로는 필요한 최소 권한으로 연결해야 합니다. 이는 다음 강의에서 다룹니다.

트리거가 연결되면 IoT Hub로 전송된 모든 메시지에 대해 함수 내부의 코드가 호출됩니다. 메시지는 매개변수로 트리거에 전달됩니다.

### 작업 - Event Hub 호환 엔드포인트 연결 문자열 가져오기

1. VS Code 터미널에서 다음 명령을 실행하여 IoT Hub의 Event Hub 호환 엔드포인트에 대한 연결 문자열을 가져옵니다:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꿉니다.

1. VS Code에서 `local.settings.json` 파일을 엽니다. `Values` 섹션에 다음 값을 추가합니다:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>`을 이전 단계에서 얻은 값으로 바꿉니다. 유효한 JSON을 만들기 위해 위 줄 뒤에 쉼표를 추가해야 합니다.

### 작업 - 이벤트 트리거 생성

이제 이벤트 트리거를 생성할 준비가 되었습니다.

1. VS Code 터미널에서 `soil-moisture-trigger` 폴더 내부에서 다음 명령을 실행합니다:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    이는 `iot-hub-trigger`라는 새 Function을 생성합니다. 이 트리거는 IoT Hub의 Event Hub 호환 엔드포인트에 연결하므로 Event Hub 트리거를 사용할 수 있습니다. 특정 IoT Hub 트리거는 없습니다.

이 작업은 `soil-moisture-trigger` 폴더 내부에 `iot-hub-trigger`라는 폴더를 생성하며, 이 폴더에는 다음 파일이 포함됩니다:

* `__init__.py` - 트리거를 포함하는 Python 코드 파일로, 이 폴더를 Python 모듈로 변환하기 위해 표준 Python 파일 이름 규칙을 따릅니다.

    이 파일에는 다음 코드가 포함됩니다:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    트리거의 핵심은 `main` 함수입니다. 이 함수는 IoT Hub에서 발생하는 이벤트와 함께 호출됩니다. 이 함수는 `event`라는 매개변수를 가지며, 이는 `EventHubEvent`를 포함합니다. IoT Hub로 메시지가 전송될 때마다 이 함수가 호출되어 메시지를 `event`로 전달받고, 이전 강의에서 본 주석과 동일한 속성을 포함합니다.

    이 함수의 핵심은 이벤트를 로깅하는 것입니다.

* `function.json` - 트리거에 대한 구성을 포함합니다. 주요 구성은 `bindings`라는 섹션에 있습니다. 바인딩은 Azure Functions와 다른 Azure 서비스 간의 연결을 나타내는 용어입니다. 이 함수는 Event Hub에 대한 입력 바인딩을 가지며, Event Hub에 연결하여 데이터를 수신합니다.

    > 💁 출력 바인딩도 추가할 수 있습니다. 예를 들어, 함수의 출력을 데이터베이스로 보내도록 설정할 수 있으며, IoT Hub 이벤트를 함수에서 반환하면 자동으로 데이터베이스에 삽입됩니다.

    ✅ 연구해보기: [Azure Functions 트리거 및 바인딩 개념 문서](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)에서 바인딩에 대해 읽어보세요.

    `bindings` 섹션에는 바인딩에 대한 구성이 포함됩니다. 주요 값은 다음과 같습니다:

  * `"type": "eventHubTrigger"` - 함수가 Event Hub의 이벤트를 수신해야 함을 나타냅니다.
  * `"name": "events"` - Event Hub 이벤트에 사용할 매개변수 이름입니다. 이는 Python 코드의 `main` 함수에서 매개변수 이름과 일치합니다.
  * `"direction": "in"` - 입력 바인딩으로, Event Hub에서 함수로 데이터가 들어옵니다.
  * `"connection": ""` - 연결 문자열을 읽을 설정 이름을 정의합니다. 로컬에서 실행할 때는 `local.settings.json` 파일에서 이 설정을 읽습니다.

    > 💁 연결 문자열은 `function.json` 파일에 저장될 수 없으며, 설정에서 읽어야 합니다. 이는 연결 문자열이 실수로 노출되는 것을 방지하기 위함입니다.

1. [Azure Functions 템플릿의 버그](https://github.com/Azure/azure-functions-templates/issues/1250)로 인해 `function.json` 파일의 `cardinality` 필드 값이 잘못되어 있습니다. 이 값을 `many`에서 `one`으로 업데이트합니다:

    ```json
    "cardinality": "one",
    ```

1. `function.json` 파일에서 `"connection"` 값을 `local.settings.json` 파일에 추가한 새 값으로 업데이트합니다:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 기억하세요 - 이 값은 설정을 가리켜야 하며, 실제 연결 문자열을 포함해서는 안 됩니다.

1. 연결 문자열에는 `eventHubName` 값이 포함되어 있으므로, `function.json` 파일의 이 값을 비워야 합니다. 이 값을 빈 문자열로 업데이트합니다:

    ```json
    "eventHubName": "",
    ```

### 작업 - 이벤트 트리거 실행

1. IoT Hub 이벤트 모니터가 실행 중이지 않은지 확인하세요. Functions 앱과 동시에 실행되면 Functions 앱이 연결하여 이벤트를 소비할 수 없습니다.

    > 💁 여러 앱이 서로 다른 *소비자 그룹*을 사용하여 IoT Hub 엔드포인트에 연결할 수 있습니다. 이는 이후 강의에서 다룹니다.

1. Functions 앱을 실행하려면 VS Code 터미널에서 다음 명령을 실행합니다:

    ```sh
    func start
    ```

    Functions 앱이 시작되며, `iot-hub-trigger` 함수를 발견합니다. 이후 지난 하루 동안 IoT Hub로 전송된 모든 이벤트를 처리합니다.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    각 함수 호출은 출력에서 `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` 블록으로 둘러싸여 있어, 각 함수 호출에서 처리된 메시지 수를 확인할 수 있습니다.

1. IoT 디바이스가 실행 중인지 확인하세요. Functions 앱에서 새로운 토양 습도 메시지가 나타나는 것을 볼 수 있습니다.

1. Functions 앱을 중지하고 다시 시작하세요. 이전 메시지는 다시 처리되지 않고, 새 메시지만 처리됩니다.

> 💁 VS Code는 Functions 디버깅도 지원합니다. 코드 줄 시작 부분의 테두리를 클릭하거나, 코드 줄에 커서를 놓고 *Run -> Toggle breakpoint*를 선택하거나 `F9`를 눌러 중단점을 설정할 수 있습니다. *Run -> Start debugging*을 선택하거나 `F5`를 누르거나 *Run and debug* 창에서 **Start debugging** 버튼을 선택하여 디버거를 실행할 수 있습니다. 이를 통해 처리 중인 이벤트의 세부 정보를 확인할 수 있습니다.

#### 문제 해결

* 다음 오류가 발생하면:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Azurite가 실행 중인지 확인하고, `local.settings.json` 파일에서 `AzureWebJobsStorage`를 `UseDevelopmentStorage=true`로 설정했는지 확인하세요.

* 다음 오류가 발생하면:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    `function.json` 파일에서 `cardinality`를 `one`으로 설정했는지 확인하세요.

* 다음 오류가 발생하면:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    `function.json` 파일에서 `eventHubName`을 빈 문자열로 설정했는지 확인하세요.

## 서버리스 코드에서 직접 메서드 요청 보내기

지금까지 Functions 앱은 Event Hub 호환 엔드포인트를 사용하여 IoT Hub의 메시지를 수신하고 있었습니다. 이제 IoT 디바이스로 명령을 보내야 합니다. 이는 *Registry Manager*를 통해 IoT Hub에 다른 연결을 사용하여 수행됩니다. Registry Manager는 IoT Hub에 등록된 디바이스를 확인하고, 클라우드에서 디바이스로 메시지 전송, 직접 메서드 요청 또는 디바이스 트윈 업데이트를 수행할 수 있는 도구입니다. 또한 IoT Hub에서 IoT 디바이스를 등록, 업데이트 또는 삭제하는 데 사용할 수도 있습니다.

Registry Manager에 연결하려면 연결 문자열이 필요합니다.

### 작업 - Registry Manager 연결 문자열 가져오기

1. 연결 문자열을 얻으려면 다음 명령을 실행합니다:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꿉니다.

    연결 문자열은 `--policy-name service` 매개변수를 사용하여 *ServiceConnect* 정책에 대해 요청됩니다. 연결 문자열을 요청할 때, 해당 연결 문자열이 허용할 권한을 지정할 수 있습니다. ServiceConnect 정책은 코드가 연결하여 IoT 디바이스로 메시지를 보낼 수 있도록 허용합니다.

    ✅ 연구해보기: [IoT Hub 권한 문서](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)에서 다양한 정책에 대해 읽어보세요.

1. VS Code에서 `local.settings.json` 파일을 엽니다. `Values` 섹션에 다음 값을 추가합니다:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>`을 이전 단계에서 얻은 값으로 바꿉니다. 유효한 JSON을 만들기 위해 위 줄 뒤에 쉼표를 추가해야 합니다.

### 작업 - 디바이스에 직접 메서드 요청 보내기

1. Registry Manager SDK는 Pip 패키지를 통해 사용할 수 있습니다. `requirements.txt` 파일에 다음 줄을 추가하여 이 패키지에 대한 종속성을 추가합니다:

    ```sh
    azure-iot-hub
    ```

1. VS Code 터미널에서 가상 환경이 활성화되어 있는지 확인하고, 다음 명령을 실행하여 Pip 패키지를 설치합니다:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` 파일에 다음 import를 추가합니다:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    이는 시스템 라이브러리와 Registry Manager와 직접 메서드 요청을 처리하기 위한 라이브러리를 가져옵니다.

1. `main` 메서드 내부의 코드를 제거하되, 메서드 자체는 유지합니다.

1. `main` 메서드에 다음 코드를 추가합니다:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    이 코드는 IoT 디바이스에서 전송된 JSON 메시지를 포함하는 이벤트 본문을 추출합니다.

    그런 다음 메시지와 함께 전달된 주석에서 디바이스 ID를 가져옵니다. 이벤트 본문에는 원격 측정으로 전송된 메시지가 포함되어 있으며, `iothub_metadata` 딕셔너리에는 IoT Hub에서 설정한 속성(예: 보낸 디바이스의 ID 및 메시지가 전송된 시간)이 포함되어 있습니다.

    이 정보는 로깅됩니다. Functions 앱을 로컬에서 실행할 때 이 로깅을 터미널에서 확인할 수 있습니다.

1. 이 아래에 다음 코드를 추가합니다:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    이 코드는 메시지에서 토양 습도 값을 가져옵니다. 그런 다음 습도 값을 확인하고, 값에 따라 `relay_on` 또는 `relay_off` 직접 메서드 요청을 위한 헬퍼 클래스를 생성합니다. 메서드 요청에는 페이로드가 필요하지 않으므로 빈 JSON 문서를 전송합니다.

1. 이 아래에 다음 코드를 추가합니다:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
이 코드는 `local.settings.json` 파일에서 `REGISTRY_MANAGER_CONNECTION_STRING`을 로드합니다. 이 파일의 값은 환경 변수로 제공되며, `os.environ` 함수를 사용하여 읽을 수 있습니다. 이 함수는 모든 환경 변수의 딕셔너리를 반환합니다.

> 💁 이 코드를 클라우드에 배포하면, `local.settings.json` 파일의 값이 *Application Settings*로 설정되며, 환경 변수에서 읽을 수 있습니다.

그 후, 코드는 연결 문자열을 사용하여 Registry Manager 헬퍼 클래스의 인스턴스를 생성합니다.

1. 아래에 다음 코드를 추가하세요:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    이 코드는 레지스트리 매니저에게 텔레메트리를 보낸 디바이스에 직접 메서드 요청을 보내도록 지시합니다.

    > 💁 이전 레슨에서 MQTT를 사용하여 만든 앱 버전에서는 릴레이 제어 명령이 모든 디바이스에 전송되었습니다. 코드는 디바이스가 하나만 있을 것이라고 가정했습니다. 이 버전의 코드는 단일 디바이스에 메서드 요청을 보내므로, 여러 개의 수분 센서와 릴레이를 설정한 경우에도 올바른 디바이스에 올바른 직접 메서드 요청을 보낼 수 있습니다.

1. Functions 앱을 실행하고 IoT 디바이스가 데이터를 보내고 있는지 확인하세요. 메시지가 처리되고 직접 메서드 요청이 전송되는 것을 볼 수 있습니다. 토양 수분 센서를 흙 안팎으로 이동하여 값이 변경되고 릴레이가 켜지고 꺼지는 것을 확인하세요.

> 💁 이 코드는 [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) 폴더에서 찾을 수 있습니다.

## 서버리스 코드를 클라우드에 배포하기

코드가 로컬에서 작동하므로 다음 단계는 Functions 앱을 클라우드에 배포하는 것입니다.

### 작업 - 클라우드 리소스 생성

Functions 앱은 Azure의 Functions App 리소스에 배포되어야 하며, 이는 IoT Hub를 위해 생성한 Resource Group 안에 있어야 합니다. 또한 로컬에서 실행 중인 에뮬레이터를 대체할 Azure에서 생성된 Storage Account가 필요합니다.

1. 다음 명령을 실행하여 Storage Account를 생성하세요:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>`을 Storage Account 이름으로 바꾸세요. 이 이름은 URL의 일부로 사용되므로 전 세계적으로 고유해야 합니다. 소문자와 숫자만 사용할 수 있으며, 다른 문자는 사용할 수 없습니다. 이름은 24자 이내로 제한됩니다. `sms`와 고유 식별자를 추가하여 이름을 만드세요. 예를 들어, 랜덤 단어 또는 본인의 이름을 사용할 수 있습니다.

    `--sku Standard_LRS`는 가격 책정 계층을 선택하며, 가장 저렴한 일반 계정을 선택합니다. 무료 계층은 없으며 사용한 만큼 비용을 지불합니다. 비용은 비교적 저렴하며, 가장 비싼 저장소도 기가바이트당 월 US$0.05 미만입니다.

    ✅ [Azure Storage Account 가격 페이지](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)에서 가격 정보를 확인하세요.

1. 다음 명령을 실행하여 Function App을 생성하세요:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>`을 이전 레슨에서 Resource Group을 생성할 때 사용한 위치로 바꾸세요.

    `<storage_name>`을 이전 단계에서 생성한 Storage Account 이름으로 바꾸세요.

    `<functions_app_name>`을 Functions App의 고유 이름으로 바꾸세요. 이 이름은 URL의 일부로 사용되므로 전 세계적으로 고유해야 합니다. `soil-moisture-sensor-`와 고유 식별자를 추가하여 이름을 만드세요. 예를 들어, 랜덤 단어 또는 본인의 이름을 사용할 수 있습니다.

    `--functions-version 3` 옵션은 사용할 Azure Functions 버전을 설정합니다. 버전 3은 최신 버전입니다.

    `--os-type Linux`는 Functions 런타임이 Linux를 OS로 사용하도록 설정합니다. Functions는 사용된 프로그래밍 언어에 따라 Linux 또는 Windows에서 호스팅될 수 있습니다. Python 앱은 Linux에서만 지원됩니다.

### 작업 - 애플리케이션 설정 업로드

Functions 앱을 개발할 때 IoT Hub의 연결 문자열을 위한 설정을 `local.settings.json` 파일에 저장했습니다. 이러한 설정은 Azure의 Function App의 Application Settings에 작성되어야 하며, 코드에서 사용할 수 있습니다.

> 🎓 `local.settings.json` 파일은 로컬 개발 설정용이며, GitHub과 같은 소스 코드 관리에 체크인하면 안 됩니다. 클라우드에 배포되면 Application Settings가 사용됩니다. Application Settings는 클라우드에 호스팅된 키/값 쌍이며, 코드에서 또는 런타임에서 환경 변수로 읽을 수 있습니다.

1. 다음 명령을 실행하여 Functions App Application Settings에서 `IOT_HUB_CONNECTION_STRING` 설정을 설정하세요:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>`을 Functions App 이름으로 바꾸세요.

    `<connection string>`을 `local.settings.json` 파일에서 `IOT_HUB_CONNECTION_STRING` 값으로 바꾸세요.

1. 위 단계를 반복하여 `REGISTRY_MANAGER_CONNECTION_STRING` 값을 `local.settings.json` 파일의 해당 값으로 설정하세요.

이 명령을 실행하면 Functions 앱의 모든 Application Settings 목록이 출력됩니다. 이를 사용하여 값이 올바르게 설정되었는지 확인할 수 있습니다.

> 💁 `AzureWebJobsStorage`에 이미 설정된 값을 볼 수 있습니다. `local.settings.json` 파일에서는 로컬 저장소 에뮬레이터를 사용하도록 설정되었습니다. Functions 앱을 생성할 때 Storage Account를 매개변수로 전달하면 이 설정이 자동으로 설정됩니다.

### 작업 - Functions 앱을 클라우드에 배포

Functions 앱이 준비되었으므로 코드를 배포할 수 있습니다.

1. VS Code 터미널에서 다음 명령을 실행하여 Functions 앱을 게시하세요:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>`을 Functions App 이름으로 바꾸세요.

코드가 패키징되어 Functions 앱으로 전송되고 배포 및 시작됩니다. 많은 콘솔 출력이 표시되며, 배포 확인과 배포된 함수 목록으로 끝납니다. 이 경우 목록에는 트리거만 포함됩니다.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

IoT 디바이스가 실행 중인지 확인하세요. 토양 수분을 조정하거나 센서를 흙 안팎으로 이동하여 수분 수준을 변경하세요. 토양 수분이 변경됨에 따라 릴레이가 켜지고 꺼지는 것을 볼 수 있습니다.

---

## 🚀 도전 과제

이전 레슨에서는 릴레이가 켜져 있는 동안 MQTT 메시지 구독을 취소하고 꺼진 후 잠시 동안 구독을 취소하여 릴레이 타이밍을 관리했습니다. 여기서는 이 방법을 사용할 수 없습니다 - IoT Hub 트리거를 취소할 수 없습니다.

Functions 앱에서 이를 처리할 수 있는 다른 방법을 생각해 보세요.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## 복습 및 자기 학습

* [Wikipedia의 서버리스 컴퓨팅 페이지](https://wikipedia.org/wiki/Serverless_computing)에서 서버리스 컴퓨팅에 대해 읽어보세요.
* Azure에서 서버리스를 사용하는 방법과 몇 가지 예제를 포함한 [Go serverless for your IoT needs Azure 블로그 게시물](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)을 읽어보세요.
* [Azure Functions YouTube 채널](https://www.youtube.com/c/AzureFunctions)에서 Azure Functions에 대해 더 알아보세요.

## 과제

[수동 릴레이 제어 추가](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전이 권위 있는 출처로 간주되어야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.