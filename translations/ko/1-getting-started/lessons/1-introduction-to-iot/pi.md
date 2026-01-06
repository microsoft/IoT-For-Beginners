<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-24T23:37:31+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "ko"
}
-->
# 라즈베리 파이

[Raspberry Pi](https://raspberrypi.org)는 단일 보드 컴퓨터입니다. 다양한 장치와 생태계를 사용하여 센서와 액추에이터를 추가할 수 있으며, 이 레슨에서는 [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html)라는 하드웨어 생태계를 사용합니다. Python을 사용하여 Pi를 코딩하고 Grove 센서에 접근할 수 있습니다.

![라즈베리 파이 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.ko.jpg)

## 설정

라즈베리 파이를 IoT 하드웨어로 사용하는 경우 두 가지 선택지가 있습니다. 이 레슨을 진행하며 Pi에서 직접 코딩하거나, '헤드리스' Pi에 원격으로 연결하여 컴퓨터에서 코딩할 수 있습니다.

시작하기 전에 Grove Base Hat을 Pi에 연결해야 합니다.

### 작업 - 설정

Grove Base Hat을 Pi에 설치하고 Pi를 구성하세요.

1. Grove Base Hat을 Pi에 연결하세요. Hat의 소켓은 Pi의 모든 GPIO 핀에 맞게 설계되어 있으며, 핀에 완전히 밀어 넣어 단단히 고정됩니다. Hat은 Pi 위에 덮여 설치됩니다.

    ![Grove Hat 설치](../../../../../images/pi-grove-hat-fitting.gif)

1. Pi를 프로그래밍할 방법을 결정하고 아래의 관련 섹션으로 이동하세요:

    * [Pi에서 직접 작업하기](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Pi를 원격으로 코딩하기](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Pi에서 직접 작업하기

Pi에서 직접 작업하려면 Raspberry Pi OS의 데스크톱 버전을 사용하고 필요한 모든 도구를 설치할 수 있습니다.

#### 작업 - Pi에서 직접 작업하기

개발을 위해 Pi를 설정하세요.

1. [Raspberry Pi 설정 가이드](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up)를 따라 Pi를 설정하고, 키보드/마우스/모니터를 연결하고, WiFi 또는 이더넷 네트워크에 연결하며, 소프트웨어를 업데이트하세요.

Grove 센서와 액추에이터를 사용하여 Pi를 프로그래밍하려면 장치 코드를 작성할 수 있는 편집기와 Grove 하드웨어와 상호작용하는 다양한 라이브러리 및 도구를 설치해야 합니다.

1. Pi가 재부팅되면, 상단 메뉴 바에서 **Terminal** 아이콘을 클릭하거나 *Menu -> Accessories -> Terminal*을 선택하여 터미널을 실행하세요.

1. OS와 설치된 소프트웨어가 최신 상태인지 확인하려면 다음 명령을 실행하세요:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Grove 하드웨어에 필요한 모든 라이브러리를 설치하려면 다음 명령을 실행하세요:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    이 명령은 Git과 Python 패키지를 설치하는 Pip을 설치하는 것으로 시작합니다.

    Python의 강력한 기능 중 하나는 [Pip 패키지](https://pypi.org)를 설치할 수 있다는 점입니다. 이는 다른 사람들이 작성하여 인터넷에 게시한 코드 패키지입니다. 한 명령으로 Pip 패키지를 컴퓨터에 설치한 후 코드에서 사용할 수 있습니다.

    Seeed Grove Python 패키지는 소스에서 설치해야 합니다. 이 명령은 이 패키지의 소스 코드를 포함하는 저장소를 클론한 다음 로컬에 설치합니다.

    > 💁 기본적으로 패키지를 설치하면 컴퓨터 전체에서 사용할 수 있으며, 이는 패키지 버전 문제를 일으킬 수 있습니다. 예를 들어, 한 애플리케이션이 특정 버전에 의존하는데 다른 애플리케이션을 위해 새 버전을 설치하면 문제가 발생할 수 있습니다. 이를 해결하기 위해 [Python 가상 환경](https://docs.python.org/3/library/venv.html)을 사용할 수 있습니다. 이는 전용 폴더에 Python의 복사본을 생성하며, Pip 패키지를 설치하면 해당 폴더에만 설치됩니다. Pi를 사용할 때는 가상 환경을 사용하지 않습니다. Grove 설치 스크립트는 Grove Python 패키지를 전역적으로 설치하므로 가상 환경을 설정한 후 해당 환경 내에서 Grove 패키지를 수동으로 다시 설치해야 합니다. 대부분의 Pi 개발자가 각 프로젝트를 위해 깨끗한 SD 카드를 다시 플래시하기 때문에 전역 패키지를 사용하는 것이 더 쉽습니다.

    마지막으로 I<sup>2</sup>C 인터페이스를 활성화합니다.

1. 메뉴를 사용하거나 터미널에서 다음 명령을 실행하여 Pi를 재부팅하세요:

    ```sh
    sudo reboot
    ```

1. Pi가 재부팅되면 터미널을 다시 실행하고 Python으로 장치 코드를 작성할 편집기로 사용할 [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)를 설치하려면 다음 명령을 실행하세요:

    ```sh
    sudo apt install code
    ```

    설치가 완료되면 VS Code는 상단 메뉴에서 사용할 수 있습니다.

    > 💁 선호하는 Python IDE나 편집기가 있다면 이 레슨에서 자유롭게 사용할 수 있습니다. 하지만 레슨은 VS Code를 사용하는 지침을 제공합니다.

1. Pylance를 설치하세요. 이는 VS Code의 확장 기능으로 Python 언어 지원을 제공합니다. VS Code에서 이 확장을 설치하는 방법은 [Pylance 확장 문서](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)를 참조하세요.

### Pi를 원격으로 코딩하기

Pi에서 직접 코딩하는 대신, 키보드/마우스/모니터에 연결하지 않고 '헤드리스'로 실행하며 컴퓨터에서 Visual Studio Code를 사용하여 구성하고 코딩할 수 있습니다.

#### Pi OS 설정

원격 코딩을 위해 SD 카드에 Pi OS를 설치해야 합니다.

##### 작업 - Pi OS 설정

헤드리스 Pi OS를 설정하세요.

1. [Raspberry Pi OS 소프트웨어 페이지](https://www.raspberrypi.org/software/)에서 **Raspberry Pi Imager**를 다운로드하여 설치하세요.

1. SD 카드를 컴퓨터에 삽입하고 필요하면 어댑터를 사용하세요.

1. Raspberry Pi Imager를 실행하세요.

1. Raspberry Pi Imager에서 **CHOOSE OS** 버튼을 선택한 후 *Raspberry Pi OS (Other)*를 선택하고 *Raspberry Pi OS Lite (32-bit)*를 선택하세요.

    ![Raspberry Pi Imager에서 Raspberry Pi OS Lite 선택](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.ko.png)

    > 💁 Raspberry Pi OS Lite는 데스크톱 UI나 UI 기반 도구가 없는 Raspberry Pi OS 버전입니다. 헤드리스 Pi에는 이러한 도구가 필요하지 않으며 설치 크기를 줄이고 부팅 시간을 단축합니다.

1. **CHOOSE STORAGE** 버튼을 선택한 후 SD 카드를 선택하세요.

1. `Ctrl+Shift+X`를 눌러 **Advanced Options**를 실행하세요. 이 옵션을 통해 Raspberry Pi OS를 SD 카드에 이미지화하기 전에 일부 사전 구성을 할 수 있습니다.

    1. **Enable SSH** 체크박스를 선택하고 `pi` 사용자에 대한 비밀번호를 설정하세요. 이는 나중에 Pi에 로그인할 때 사용할 비밀번호입니다.

    1. Pi를 WiFi로 연결하려는 경우 **Configure WiFi** 체크박스를 선택하고 WiFi SSID와 비밀번호를 입력하며 WiFi 국가를 선택하세요. 이더넷 케이블을 사용할 경우에는 필요하지 않습니다. 연결하는 네트워크가 컴퓨터가 있는 네트워크와 동일한지 확인하세요.

    1. **Set locale settings** 체크박스를 선택하고 국가와 시간대를 설정하세요.

    1. **SAVE** 버튼을 선택하세요.

1. **WRITE** 버튼을 선택하여 OS를 SD 카드에 작성하세요. macOS를 사용하는 경우 디스크 이미지를 작성하는 기본 도구가 권한이 필요한 액세스를 요구하므로 비밀번호를 입력해야 합니다.

OS가 SD 카드에 작성되며 완료되면 OS가 SD 카드를 꺼내고 알림을 제공합니다. SD 카드를 컴퓨터에서 제거하고 Pi에 삽입한 후 Pi를 전원에 연결하고 약 2분 동안 제대로 부팅되기를 기다리세요.

#### Pi에 연결하기

다음 단계는 Pi에 원격으로 접근하는 것입니다. 이를 위해 macOS, Linux 및 최신 Windows 버전에서 사용할 수 있는 `ssh`를 사용할 수 있습니다.

##### 작업 - Pi에 연결하기

Pi에 원격으로 접근하세요.

1. 터미널 또는 명령 프롬프트를 실행하고 다음 명령을 입력하여 Pi에 연결하세요:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Windows의 이전 버전을 사용하며 `ssh`가 설치되지 않은 경우 OpenSSH를 사용할 수 있습니다. 설치 지침은 [OpenSSH 설치 문서](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn)를 참조하세요.

1. 이 명령은 Pi에 연결하고 비밀번호를 요청합니다.

    `<hostname>.local`을 사용하여 네트워크에서 컴퓨터를 찾을 수 있는 기능은 Linux와 Windows에 비교적 최근에 추가되었습니다. Linux 또는 Windows를 사용하며 호스트 이름을 찾을 수 없다는 오류가 발생하면 ZeroConf 네트워킹(Apple에서는 Bonjour라고도 함)을 활성화하기 위해 추가 소프트웨어를 설치해야 합니다:

    1. Linux를 사용하는 경우 다음 명령을 실행하여 Avahi를 설치하세요:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Windows를 사용하는 경우 ZeroConf를 활성화하는 가장 쉬운 방법은 [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999)를 설치하는 것입니다. 또한 [iTunes for Windows](https://www.apple.com/itunes/download/)를 설치하여 더 최신 버전의 유틸리티를 얻을 수 있습니다(단독으로는 제공되지 않음).

    > 💁 `raspberrypi.local`을 사용하여 연결할 수 없는 경우 Pi의 IP 주소를 사용할 수 있습니다. [Raspberry Pi IP 주소 문서](https://www.raspberrypi.org/documentation/remote-access/ip-address.md)를 참조하여 IP 주소를 얻는 여러 방법에 대한 지침을 확인하세요.

1. Raspberry Pi Imager Advanced Options에서 설정한 비밀번호를 입력하세요.

#### Pi에서 소프트웨어 구성하기

Pi에 연결한 후 OS가 최신 상태인지 확인하고 Grove 하드웨어와 상호작용하는 다양한 라이브러리 및 도구를 설치해야 합니다.

##### 작업 - Pi에서 소프트웨어 구성하기

설치된 Pi 소프트웨어를 구성하고 Grove 라이브러리를 설치하세요.

1. `ssh` 세션에서 다음 명령을 실행하여 Pi를 업데이트한 후 재부팅하세요:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi가 업데이트되고 재부팅됩니다. Pi가 재부팅되면 `ssh` 세션이 종료되므로 약 30초 동안 기다린 후 다시 연결하세요.

1. 다시 연결된 `ssh` 세션에서 Grove 하드웨어에 필요한 모든 라이브러리를 설치하려면 다음 명령을 실행하세요:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    이 명령은 Git과 Python 패키지를 설치하는 Pip을 설치하는 것으로 시작합니다.

    Python의 강력한 기능 중 하나는 [Pip 패키지](https://pypi.org)를 설치할 수 있다는 점입니다. 이는 다른 사람들이 작성하여 인터넷에 게시한 코드 패키지입니다. 한 명령으로 Pip 패키지를 컴퓨터에 설치한 후 코드에서 사용할 수 있습니다.

    Seeed Grove Python 패키지는 소스에서 설치해야 합니다. 이 명령은 이 패키지의 소스 코드를 포함하는 저장소를 클론한 다음 로컬에 설치합니다.

    > 💁 기본적으로 패키지를 설치하면 컴퓨터 전체에서 사용할 수 있으며, 이는 패키지 버전 문제를 일으킬 수 있습니다. 예를 들어, 한 애플리케이션이 특정 버전에 의존하는데 다른 애플리케이션을 위해 새 버전을 설치하면 문제가 발생할 수 있습니다. 이를 해결하기 위해 [Python 가상 환경](https://docs.python.org/3/library/venv.html)을 사용할 수 있습니다. 이는 전용 폴더에 Python의 복사본을 생성하며, Pip 패키지를 설치하면 해당 폴더에만 설치됩니다. Pi를 사용할 때는 가상 환경을 사용하지 않습니다. Grove 설치 스크립트는 Grove Python 패키지를 전역적으로 설치하므로 가상 환경을 설정한 후 해당 환경 내에서 Grove 패키지를 수동으로 다시 설치해야 합니다. 대부분의 Pi 개발자가 각 프로젝트를 위해 깨끗한 SD 카드를 다시 플래시하기 때문에 전역 패키지를 사용하는 것이 더 쉽습니다.

    마지막으로 I<sup>2</sup>C 인터페이스를 활성화합니다.

1. 다음 명령을 실행하여 Pi를 재부팅하세요:

    ```sh
    sudo reboot
    ```

    Pi가 재부팅되면 `ssh` 세션이 종료됩니다. 다시 연결할 필요는 없습니다.

#### 원격 액세스를 위한 VS Code 구성

Pi가 구성된 후 컴퓨터에서 Visual Studio Code(VS Code)를 사용하여 Pi에 연결할 수 있습니다. 이는 Python으로 장치 코드를 작성하는 데 사용할 무료 개발자 텍스트 편집기입니다.

##### 작업 - 원격 액세스를 위한 VS Code 구성

필요한 소프트웨어를 설치하고 Pi에 원격으로 연결하세요.

1. [VS Code 문서](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)를 따라 컴퓨터에 VS Code를 설치하세요.

1. [VS Code Remote Development using SSH 문서](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn)를 따라 필요한 구성 요소를 설치하세요.

1. 동일한 지침을 따라 VS Code를 Pi에 연결하세요.

1. 연결된 후 [확장 관리](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) 지침을 따라 [Pylance 확장](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance)을 Pi에 원격으로 설치하세요.

## 헬로 월드
새로운 프로그래밍 언어 또는 기술을 시작할 때, 모든 도구가 올바르게 설정되었는지 확인하기 위해 `"Hello World"`라는 텍스트를 출력하는 작은 애플리케이션을 만드는 것이 전통적입니다.

Pi를 위한 Hello World 앱은 Python과 Visual Studio Code가 올바르게 설치되었는지 확인하는 데 사용됩니다.

이 앱은 `nightlight`라는 폴더에 저장되며, 이후 과제의 다른 부분에서 다양한 코드를 사용하여 야간 조명 애플리케이션을 구축하는 데 재사용될 것입니다.

### 작업 - Hello World

Hello World 앱을 만드세요.

1. VS Code를 실행하세요. Pi에서 직접 실행하거나, Remote SSH 확장을 사용하여 컴퓨터에서 Pi에 연결하여 실행할 수 있습니다.

1. VS Code 터미널을 실행하세요. *Terminal -> New Terminal*을 선택하거나 `` CTRL+` ``를 눌러 실행할 수 있습니다. 터미널은 `pi` 사용자 홈 디렉토리에서 열립니다.

1. 아래 명령어를 실행하여 코드를 저장할 디렉토리를 만들고, 해당 디렉토리 안에 `app.py`라는 Python 파일을 생성하세요:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. VS Code에서 *File -> Open...*을 선택하여 *nightlight* 폴더를 열고 **OK**를 선택하세요.

    ![VS Code 열기 대화창에서 nightlight 폴더를 보여주는 화면](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.ko.png)

1. VS Code 탐색기에서 `app.py` 파일을 열고 아래 코드를 추가하세요:

    ```python
    print('Hello World!')
    ```

    `print` 함수는 전달된 내용을 콘솔에 출력합니다.

1. VS Code 터미널에서 아래 명령어를 실행하여 Python 앱을 실행하세요:

    ```sh
    python app.py
    ```

    > 💁 Python 2가 설치되어 있는 경우, 이 코드를 실행하려면 명시적으로 `python3`를 호출해야 할 수도 있습니다. Python 2가 설치되어 있다면 `python`을 호출하면 Python 2가 실행됩니다. 기본적으로 최신 Raspberry Pi OS 버전에는 Python 3만 설치되어 있습니다.

    터미널에 다음 출력이 나타날 것입니다:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 이 코드는 [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) 폴더에서 찾을 수 있습니다.

😀 'Hello World' 프로그램이 성공적으로 실행되었습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.