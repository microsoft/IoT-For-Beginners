<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-24T23:34:04+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "ko"
}
-->
# 가상 싱글보드 컴퓨터

IoT 디바이스와 센서 및 액추에이터를 구매하는 대신, 컴퓨터를 사용하여 IoT 하드웨어를 시뮬레이션할 수 있습니다. [CounterFit 프로젝트](https://github.com/CounterFit-IoT/CounterFit)를 사용하면 IoT 하드웨어(센서 및 액추에이터)를 시뮬레이션하는 앱을 로컬에서 실행하고, 실제 하드웨어를 사용하는 것처럼 로컬 Python 코드에서 센서와 액추에이터에 접근할 수 있습니다.

## 설정

CounterFit을 사용하려면 컴퓨터에 무료 소프트웨어를 설치해야 합니다.

### 작업

필요한 소프트웨어를 설치하세요.

1. Python을 설치하세요. 최신 버전의 Python을 설치하는 방법은 [Python 다운로드 페이지](https://www.python.org/downloads/)를 참조하세요.

1. Visual Studio Code(VS Code)를 설치하세요. 이는 Python으로 가상 디바이스 코드를 작성할 때 사용할 편집기입니다. VS Code를 설치하는 방법은 [VS Code 문서](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)를 참조하세요.

    > 💁 선호하는 도구가 있다면 이 강의에서 Python IDE나 편집기를 자유롭게 사용할 수 있습니다. 하지만 강의에서는 VS Code를 기준으로 설명합니다.

1. VS Code Pylance 확장을 설치하세요. 이는 VS Code에서 Python 언어 지원을 제공하는 확장입니다. VS Code에서 이 확장을 설치하는 방법은 [Pylance 확장 문서](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)를 참조하세요.

CounterFit 앱을 설치하고 구성하는 방법은 과제 지침에서 적절한 시점에 제공되며, 프로젝트별로 설치됩니다.

## Hello World

새로운 프로그래밍 언어나 기술을 시작할 때 전통적으로 'Hello World' 애플리케이션을 만듭니다. 이는 모든 도구가 올바르게 구성되었는지 확인하기 위해 `"Hello World"`와 같은 텍스트를 출력하는 작은 애플리케이션입니다.

가상 IoT 하드웨어를 위한 Hello World 앱은 Python과 Visual Studio Code가 올바르게 설치되었는지 확인합니다. 또한 CounterFit에 연결하여 가상 IoT 센서와 액추에이터를 테스트합니다. 하드웨어를 사용하지 않고 모든 것이 작동하는지 확인하기 위해 연결만 합니다.

이 앱은 `nightlight`라는 폴더에 저장되며, 이후 과제의 다른 부분에서 야간 조명 애플리케이션을 구축하기 위해 다른 코드와 함께 재사용됩니다.

### Python 가상 환경 구성

Python의 강력한 기능 중 하나는 [Pip 패키지](https://pypi.org)를 설치할 수 있다는 점입니다. 이는 다른 사람들이 작성하여 인터넷에 게시한 코드 패키지입니다. 한 명령어로 Pip 패키지를 컴퓨터에 설치한 후 코드에서 해당 패키지를 사용할 수 있습니다. CounterFit과 통신하기 위해 Pip 패키지를 설치할 것입니다.

기본적으로 패키지를 설치하면 컴퓨터 전체에서 사용할 수 있으며, 이는 패키지 버전 문제를 초래할 수 있습니다. 예를 들어, 한 애플리케이션이 특정 버전의 패키지에 의존하는데 다른 애플리케이션을 위해 새 버전을 설치하면 문제가 발생할 수 있습니다. 이러한 문제를 해결하기 위해 [Python 가상 환경](https://docs.python.org/3/library/venv.html)을 사용할 수 있습니다. 이는 전용 폴더에 Python을 복사한 것으로, Pip 패키지를 설치하면 해당 폴더에만 설치됩니다.

> 💁 Raspberry Pi를 사용하는 경우 Pip 패키지를 관리하기 위해 가상 환경을 설정하지 않았습니다. 대신 글로벌 패키지를 사용하며, Grove 패키지는 설치 스크립트에 의해 글로벌로 설치됩니다.

#### 작업 - Python 가상 환경 구성

Python 가상 환경을 구성하고 CounterFit을 위한 Pip 패키지를 설치하세요.

1. 터미널 또는 명령줄에서 다음 명령을 실행하여 새 디렉터리를 생성하고 해당 디렉터리로 이동하세요:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. `.venv` 폴더에 가상 환경을 생성하려면 다음 명령을 실행하세요:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Python 2가 설치되어 있는 경우 Python 3을 사용하여 가상 환경을 생성해야 합니다. Python 2가 설치되어 있다면 `python`을 호출하면 Python 2가 사용됩니다.

1. 가상 환경을 활성화하세요:

    * Windows에서:
        * 명령 프롬프트 또는 Windows Terminal의 명령 프롬프트를 사용하는 경우 다음을 실행하세요:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell을 사용하는 경우 다음을 실행하세요:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > 스크립트 실행이 시스템에서 비활성화되었다는 오류가 발생하면 적절한 실행 정책을 설정하여 스크립트 실행을 활성화해야 합니다. 관리자 권한으로 PowerShell을 실행한 후 다음 명령을 실행하세요:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            확인 요청 시 `Y`를 입력하세요. 그런 다음 PowerShell을 다시 실행하고 다시 시도하세요.

            필요하면 나중에 실행 정책을 재설정할 수 있습니다. 자세한 내용은 [Microsoft Docs의 실행 정책 페이지](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn)를 참조하세요.

    * macOS 또는 Linux에서 다음을 실행하세요:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 이 명령은 가상 환경을 생성한 위치에서 실행해야 합니다. `.venv` 폴더로 이동할 필요는 없으며, 가상 환경을 활성화하는 명령과 패키지를 설치하거나 코드를 실행하는 명령은 가상 환경을 생성한 폴더에서 실행해야 합니다.

1. 가상 환경이 활성화되면 기본 `python` 명령은 가상 환경을 생성하는 데 사용된 Python 버전을 실행합니다. 다음 명령을 실행하여 버전을 확인하세요:

    ```sh
    python --version
    ```

    출력에는 다음이 포함되어야 합니다:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Python 버전은 다를 수 있습니다. 버전이 3.6 이상이면 괜찮습니다. 그렇지 않으면 이 폴더를 삭제하고 최신 버전의 Python을 설치한 후 다시 시도하세요.

1. CounterFit을 위한 Pip 패키지를 설치하려면 다음 명령을 실행하세요. 이 패키지에는 주요 CounterFit 앱과 Grove 하드웨어를 위한 셈이 포함됩니다. 이 셈을 사용하면 실제 Grove 생태계의 센서와 액추에이터를 사용하는 것처럼 코드를 작성할 수 있습니다.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    이 Pip 패키지는 가상 환경에만 설치되며, 가상 환경 외부에서는 사용할 수 없습니다.

### 코드 작성

Python 가상 환경이 준비되면 'Hello World' 애플리케이션의 코드를 작성할 수 있습니다.

#### 작업 - 코드 작성

콘솔에 `"Hello World"`를 출력하는 Python 애플리케이션을 만드세요.

1. 가상 환경 내에서 터미널 또는 명령줄에서 다음 명령을 실행하여 `app.py`라는 Python 파일을 생성하세요:

    * Windows에서 실행:

        ```cmd
        type nul > app.py
        ```

    * macOS 또는 Linux에서 실행:

        ```cmd
        touch app.py
        ```

1. 현재 폴더를 VS Code에서 열기:

    ```sh
    code .
    ```

    > 💁 macOS에서 터미널이 `command not found`를 반환하면 VS Code가 PATH에 추가되지 않았다는 의미입니다. VS Code를 PATH에 추가하려면 [VS Code 문서의 명령줄에서 실행 섹션](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line)을 참조하여 명령을 실행하세요. Windows와 Linux에서는 기본적으로 VS Code가 PATH에 추가됩니다.

1. VS Code가 실행되면 Python 가상 환경이 활성화됩니다. 선택된 가상 환경은 하단 상태 표시줄에 나타납니다:

    ![VS Code에서 선택된 가상 환경 표시](../../../../../translated_images/ko/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. VS Code 터미널이 이미 실행 중일 때 VS Code가 시작되면 터미널에 가상 환경이 활성화되지 않을 수 있습니다. 가장 쉬운 방법은 **활성 터미널 인스턴스 종료** 버튼을 사용하여 터미널을 종료하는 것입니다:

    ![VS Code 활성 터미널 인스턴스 종료 버튼](../../../../../translated_images/ko/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    터미널에 가상 환경이 활성화되었는지 확인하려면 터미널 프롬프트에 가상 환경 이름이 접두사로 표시됩니다. 예를 들어, 다음과 같을 수 있습니다:

    ```sh
    (.venv) ➜  nightlight
    ```

    프롬프트에 `.venv`가 접두사로 표시되지 않으면 터미널에서 가상 환경이 활성화되지 않은 것입니다.

1. *Terminal -> New Terminal*을 선택하거나 `` CTRL+` ``를 눌러 새 VS Code 터미널을 실행하세요. 새 터미널은 가상 환경을 로드하며, 이를 활성화하는 호출이 터미널에 나타납니다. 프롬프트에는 가상 환경 이름(`.venv`)이 포함됩니다:

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Code 탐색기에서 `app.py` 파일을 열고 다음 코드를 추가하세요:

    ```python
    print('Hello World!')
    ```

    `print` 함수는 전달된 내용을 콘솔에 출력합니다.

1. VS Code 터미널에서 다음 명령을 실행하여 Python 앱을 실행하세요:

    ```sh
    python app.py
    ```

    출력에는 다음이 포함됩니다:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 'Hello World' 프로그램이 성공적으로 실행되었습니다!

### '하드웨어' 연결

두 번째 'Hello World' 단계로 CounterFit 앱을 실행하고 코드에 연결합니다. 이는 IoT 하드웨어를 개발 키트에 연결하는 가상의 작업입니다.

#### 작업 - '하드웨어' 연결

1. VS Code 터미널에서 다음 명령을 실행하여 CounterFit 앱을 시작하세요:

    ```sh
    counterfit
    ```

    앱이 실행되며 웹 브라우저에서 열립니다:

    ![브라우저에서 실행 중인 CounterFit 앱](../../../../../translated_images/ko/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    앱은 *Disconnected*로 표시되며, 오른쪽 상단의 LED가 꺼져 있습니다.

1. `app.py` 파일 상단에 다음 코드를 추가하세요:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    이 코드는 `counterfit_connection` 모듈에서 `CounterFitConnection` 클래스를 가져옵니다. 그런 다음 `127.0.0.1`에서 실행 중인 CounterFit 앱에 연결을 초기화합니다. `127.0.0.1`은 로컬 컴퓨터에 항상 접근할 수 있는 IP 주소로 (*localhost*라고도 함), 포트 5000에서 실행됩니다.

    > 💁 포트 5000에서 실행 중인 다른 앱이 있는 경우 코드를 업데이트하여 포트를 변경하고 `CounterFit --port <port_number>` 명령을 실행하여 `<port_number>`를 원하는 포트로 바꿀 수 있습니다.

1. 현재 터미널에서 CounterFit 앱이 실행 중이므로 **새 통합 터미널 생성** 버튼을 선택하여 새 VS Code 터미널을 실행해야 합니다.

    ![VS Code 새 통합 터미널 생성 버튼](../../../../../translated_images/ko/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. 새 터미널에서 이전과 같이 `app.py` 파일을 실행하세요. CounterFit 상태가 **Connected**로 변경되고 LED가 켜집니다.

    ![CounterFit가 연결된 상태 표시](../../../../../translated_images/ko/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 이 코드는 [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) 폴더에서 찾을 수 있습니다.

😀 하드웨어 연결이 성공적으로 완료되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.