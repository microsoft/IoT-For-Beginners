<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-24T21:43:20+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "ko"
}
-->
# 엣지에서 과일 감지기 실행하기

![이 강의의 스케치노트 개요](../../../../../translated_images/ko/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> 스케치노트: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

이 비디오는 IoT 디바이스에서 이미지 분류기를 실행하는 방법에 대한 개요를 제공합니다. 이 강의에서 다룰 주제입니다.

[![Azure IoT Edge에서 Custom Vision AI](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## 소개

지난 강의에서는 이미지 분류기를 사용하여 익은 과일과 덜 익은 과일을 분류하고, IoT 디바이스의 카메라로 촬영한 이미지를 인터넷을 통해 클라우드 서비스로 전송했습니다. 이러한 호출은 시간이 걸리고 비용이 들며, 사용하는 이미지 데이터의 종류에 따라 프라이버시 문제가 발생할 수 있습니다.

이번 강의에서는 클라우드가 아닌 자체 네트워크에서 실행되는 IoT 디바이스에서 머신러닝(ML) 모델을 실행하는 방법을 배웁니다. 엣지 컴퓨팅과 클라우드 컴퓨팅의 장단점, AI 모델을 엣지에 배포하는 방법, IoT 디바이스에서 이를 액세스하는 방법을 배우게 됩니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [엣지 컴퓨팅](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge 디바이스 등록](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge 디바이스 설정](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [모델 내보내기](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [배포를 위한 컨테이너 준비](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [컨테이너 배포](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge 디바이스 사용](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## 엣지 컴퓨팅

엣지 컴퓨팅은 IoT 데이터가 생성되는 위치에 최대한 가까운 곳에서 데이터를 처리하는 것을 의미합니다. 클라우드에서 처리하는 대신, 클라우드의 엣지, 즉 내부 네트워크로 처리 위치를 이동합니다.

![클라우드에서 인터넷 서비스를 제공하고 로컬 네트워크에서 IoT 디바이스가 작동하는 아키텍처 다이어그램](../../../../../translated_images/ko/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

지금까지의 강의에서는 디바이스가 데이터를 수집하고 클라우드로 전송하여 서버리스 함수나 AI 모델을 실행해 분석하는 방식을 사용했습니다.

![로컬 네트워크에서 IoT 디바이스가 엣지 디바이스에 연결되고, 엣지 디바이스가 클라우드에 연결되는 아키텍처 다이어그램](../../../../../translated_images/ko/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

엣지 컴퓨팅은 일부 클라우드 서비스를 클라우드에서 제거하고 IoT 디바이스와 동일한 네트워크에서 실행되는 컴퓨터로 이동하는 것을 포함합니다. 예를 들어, 엣지 디바이스에서 AI 모델을 실행하여 과일의 익은 정도를 분석하고, 익은 과일과 덜 익은 과일의 개수와 같은 분석 결과만 클라우드로 전송할 수 있습니다.

✅ 지금까지 구축한 IoT 애플리케이션을 생각해 보세요. 그 중 어떤 부분을 엣지로 이동할 수 있을까요?

### 장점

엣지 컴퓨팅의 장점은 다음과 같습니다:

1. **속도** - 엣지 컴퓨팅은 시간에 민감한 데이터에 이상적입니다. 작업이 디바이스와 동일한 네트워크에서 수행되므로 인터넷을 통해 호출하는 것보다 더 빠르게 처리됩니다. 내부 네트워크는 인터넷 연결보다 훨씬 빠른 속도로 실행될 수 있으며, 데이터가 이동하는 거리가 짧아집니다.

    > 💁 광케이블을 사용한 인터넷 연결은 데이터가 빛의 속도로 이동할 수 있지만, 데이터가 클라우드 제공업체로 이동하는 데는 시간이 걸립니다. 예를 들어, 유럽에서 미국의 클라우드 서비스로 데이터를 전송하는 경우, 데이터가 대서양을 가로지르는 데 최소 28ms가 걸립니다. 이는 데이터가 대서양 케이블로 이동하고, 전기 신호에서 빛 신호로 변환된 후 다시 클라우드 제공업체로 이동하는 시간을 제외한 것입니다.

    엣지 컴퓨팅은 네트워크 트래픽도 줄여주어 인터넷 연결의 제한된 대역폭으로 인해 데이터가 느려질 위험을 줄입니다.

1. **원격 접근성** - 엣지 컴퓨팅은 연결이 제한적이거나 아예 없는 경우, 또는 연결 비용이 지속적으로 사용하기에 너무 비싼 경우에도 작동합니다. 예를 들어, 인프라가 제한된 인도적 재난 지역이나 개발도상국에서 유용합니다.

1. **비용 절감** - 데이터 수집, 저장, 분석 및 작업 트리거를 엣지 디바이스에서 수행하면 클라우드 서비스 사용량이 줄어들어 IoT 애플리케이션의 전체 비용을 줄일 수 있습니다. 최근에는 [NVIDIA의 Jetson Nano](https://developer.nvidia.com/embedded/jetson-nano-developer-kit)와 같은 AI 가속 보드처럼 엣지 컴퓨팅을 위해 설계된 디바이스가 증가하고 있으며, 이러한 디바이스는 100달러 미만의 비용으로 GPU 기반 하드웨어를 사용해 AI 작업을 실행할 수 있습니다.

1. **프라이버시와 보안** - 엣지 컴퓨팅을 사용하면 데이터가 네트워크 내에 머물며 클라우드로 업로드되지 않습니다. 이는 민감하거나 개인 식별이 가능한 정보에 대해 선호되는 방식입니다. 데이터가 분석된 후 저장할 필요가 없으므로 데이터 유출 위험이 크게 줄어듭니다. 예로는 의료 데이터와 보안 카메라 영상이 있습니다.

1. **보안이 취약한 디바이스 처리** - 보안 결함이 알려진 디바이스를 네트워크나 인터넷에 직접 연결하고 싶지 않은 경우, 별도의 네트워크에 연결하여 게이트웨이 IoT Edge 디바이스를 사용할 수 있습니다. 이 엣지 디바이스는 더 넓은 네트워크나 인터넷에 연결할 수 있으며, 데이터 흐름을 관리합니다.

1. **호환되지 않는 디바이스 지원** - HTTP 연결만 가능하거나 블루투스만 지원하는 디바이스처럼 IoT Hub에 직접 연결할 수 없는 디바이스의 경우, IoT Edge 디바이스를 게이트웨이 디바이스로 사용하여 메시지를 IoT Hub로 전달할 수 있습니다.

✅ 조사해 보세요: 엣지 컴퓨팅의 다른 장점은 무엇이 있을까요?

### 단점

엣지 컴퓨팅의 단점은 다음과 같습니다. 이 경우 클라우드가 더 나은 선택일 수 있습니다:

1. **확장성과 유연성** - 클라우드 컴퓨팅은 네트워크와 데이터 요구 사항에 따라 실시간으로 서버와 기타 리소스를 추가하거나 줄일 수 있습니다. 엣지 컴퓨터를 추가하려면 수동으로 디바이스를 추가해야 합니다.

1. **신뢰성과 복원력** - 클라우드 컴퓨팅은 종종 여러 위치에 있는 여러 서버를 통해 중복성과 재해 복구를 제공합니다. 엣지에서 동일한 수준의 중복성을 제공하려면 많은 투자와 구성이 필요합니다.

1. **유지보수** - 클라우드 서비스 제공업체는 시스템 유지보수와 업데이트를 제공합니다.

✅ 조사해 보세요: 엣지 컴퓨팅의 다른 단점은 무엇이 있을까요?

단점은 클라우드 사용의 장점과 반대되는 경우가 많습니다. 클라우드 제공업체의 전문성과 규모에 의존하는 대신, 디바이스를 직접 구축하고 관리해야 합니다.

일부 위험은 엣지 컴퓨팅의 본질에 의해 완화됩니다. 예를 들어, 공장에서 기계 데이터를 수집하는 엣지 디바이스가 있는 경우, 특정 재해 복구 시나리오를 고려할 필요가 없습니다. 공장에 전원이 끊기면 데이터를 생성하는 기계도 전원이 끊기므로 백업 엣지 디바이스가 필요하지 않습니다.

IoT 시스템에서는 시스템, 고객, 유지보수자의 요구에 따라 클라우드와 엣지 컴퓨팅을 혼합하여 사용하는 것이 일반적입니다.

## Azure IoT Edge

![Azure IoT Edge 로고](../../../../../translated_images/ko/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge는 작업 부하를 클라우드에서 엣지로 이동하는 데 도움을 줄 수 있는 서비스입니다. 디바이스를 엣지 디바이스로 설정하고, 클라우드에서 해당 엣지 디바이스로 코드를 배포할 수 있습니다. 이를 통해 클라우드와 엣지의 기능을 혼합할 수 있습니다.

> 🎓 *작업 부하*는 AI 모델, 애플리케이션, 서버리스 함수와 같이 어떤 종류의 작업을 수행하는 서비스를 의미합니다.

예를 들어, 클라우드에서 이미지 분류기를 학습시킨 다음, 클라우드에서 엣지 디바이스로 배포할 수 있습니다. IoT 디바이스는 이미지를 인터넷으로 전송하는 대신 엣지 디바이스로 전송하여 분류를 수행합니다. 모델의 새 버전을 배포해야 하는 경우, 클라우드에서 학습시키고 IoT Edge를 사용하여 엣지 디바이스의 모델을 새 버전으로 업데이트할 수 있습니다.

> 🎓 IoT Edge에 배포된 소프트웨어는 *모듈*이라고 합니다. 기본적으로 IoT Edge는 `edgeAgent` 및 `edgeHub` 모듈과 같이 IoT Hub와 통신하는 모듈을 실행합니다. 이미지 분류기를 배포하면 추가 모듈로 배포됩니다.

IoT Edge는 IoT Hub에 내장되어 있으므로 IoT 디바이스를 관리하는 데 사용하는 동일한 서비스를 사용하여 엣지 디바이스를 관리할 수 있으며, 동일한 수준의 보안을 제공합니다.

IoT Edge는 *컨테이너*에서 코드를 실행합니다. 컨테이너는 컴퓨터의 다른 애플리케이션과 격리된 상태로 실행되는 독립적인 애플리케이션입니다. 컨테이너를 실행하면 컴퓨터 내부에서 별도의 컴퓨터처럼 작동하며, 자체 소프트웨어, 서비스 및 애플리케이션을 실행합니다. 대부분의 경우 컨테이너는 사용자가 폴더와 같은 항목을 공유하도록 선택하지 않는 한 컴퓨터의 다른 항목에 액세스할 수 없습니다. 컨테이너는 네트워크에 연결하거나 노출할 수 있는 열린 포트를 통해 서비스를 제공합니다.

![컨테이너로 리디렉션된 웹 요청](../../../../../translated_images/ko/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

예를 들어, 포트 80(기본 HTTP 포트)에서 실행되는 웹 사이트가 있는 컨테이너를 생성하고, 이를 컴퓨터에서도 포트 80으로 노출할 수 있습니다.

✅ 조사해 보세요: 컨테이너와 Docker 또는 Moby와 같은 서비스에 대해 읽어보세요.

Custom Vision을 사용하여 이미지 분류기를 다운로드하고 컨테이너로 배포할 수 있습니다. 이를 디바이스에 직접 실행하거나 IoT Edge를 통해 배포할 수 있습니다. 컨테이너에서 실행되면 클라우드 버전과 동일한 REST API를 사용하여 액세스할 수 있지만, 엔드포인트는 컨테이너를 실행하는 엣지 디바이스를 가리킵니다.

## IoT Edge 디바이스 등록

IoT Edge 디바이스를 사용하려면 IoT Hub에 등록해야 합니다.

### 작업 - IoT Edge 디바이스 등록

1. `fruit-quality-detector` 리소스 그룹에 IoT Hub를 생성합니다. `fruit-quality-detector`를 기반으로 고유한 이름을 지정하세요.

1. IoT Hub에 `fruit-quality-detector-edge`라는 이름의 IoT Edge 디바이스를 등록합니다. 이를 수행하는 명령은 엣지 디바이스가 아닌 디바이스를 등록할 때 사용한 명령과 유사하지만, `--edge-enabled` 플래그를 추가로 전달합니다.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub의 이름으로 바꾸세요.

1. 다음 명령을 사용하여 디바이스의 연결 문자열을 가져옵니다:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub의 이름으로 바꾸세요.

    출력에 표시된 연결 문자열을 복사해 두세요.

## IoT Edge 디바이스 설정

엣지 디바이스 등록을 IoT Hub에서 생성한 후, 엣지 디바이스를 설정할 수 있습니다.

### 작업 - IoT Edge 런타임 설치 및 시작

**IoT Edge 런타임은 Linux 컨테이너만 실행합니다.** Linux에서 실행하거나, Windows에서 Linux 가상 머신을 사용하여 실행할 수 있습니다.

* IoT 디바이스로 Raspberry Pi를 사용하는 경우, 이는 지원되는 Linux 버전을 실행하며 IoT Edge 런타임을 호스팅할 수 있습니다. [Microsoft 문서의 Azure IoT Edge for Linux 설치 가이드](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn)를 따라 IoT Edge를 설치하고 연결 문자열을 설정하세요.

    > 💁 Raspberry Pi OS는 Debian Linux의 변형입니다.

* Raspberry Pi를 사용하지 않고 Linux 컴퓨터를 사용하는 경우, IoT Edge 런타임을 실행할 수 있습니다. [Microsoft 문서의 Azure IoT Edge for Linux 설치 가이드](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn)를 따라 IoT Edge를 설치하고 연결 문자열을 설정하세요.

* Windows를 사용하는 경우, [Microsoft 문서의 Windows 디바이스에 IoT Edge 모듈 배포 빠른 시작](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn)의 *IoT Edge 런타임 설치 및 시작* 섹션을 따라 Linux 가상 머신에서 IoT Edge 런타임을 설치할 수 있습니다. *모듈 배포* 섹션에 도달하면 중지하세요.

* macOS를 사용하는 경우, 클라우드에서 IoT Edge 디바이스로 사용할 가상 머신(VM)을 생성할 수 있습니다. 이는 인터넷을 통해 액세스할 수 있는 컴퓨터입니다. IoT Edge가 설치된 Linux VM을 생성할 수 있습니다. [IoT Edge를 실행하는 가상 머신 생성 가이드](vm-iotedge.md)를 따라 이를 설정하세요.

## 모델 내보내기

엣지에서 분류기를 실행하려면 Custom Vision에서 모델을 내보내야 합니다. Custom Vision은 표준 모델과 컴팩트 모델 두 가지 유형의 모델을 생성할 수 있습니다. 컴팩트 모델은 모델 크기를 줄이는 다양한 기술을 사용하여 IoT 디바이스에 다운로드 및 배포할 수 있을 만큼 작습니다.

이미지 분류기를 생성할 때, 음식 이미지 학습에 최적화된 모델 버전인 *Food* 도메인을 사용했습니다. Custom Vision에서 프로젝트의 도메인을 변경하여 학습 데이터를 사용해 새 도메인으로 새 모델을 학습시킬 수 있습니다. Custom Vision에서 지원하는 모든 도메인은 표준 및 컴팩트 버전으로 제공됩니다.

### 작업 - Food (compact) 도메인을 사용하여 모델 학습
1. [CustomVision.ai](https://customvision.ai) 포털을 열고 로그인합니다. 이미 열려 있지 않다면 로그인 후 `fruit-quality-detector` 프로젝트를 엽니다.

1. **Settings** 버튼(⚙ 아이콘)을 선택합니다.

1. *Domains* 목록에서 *Food (compact)*를 선택합니다.

1. *Export Capabilities* 아래에서 *Basic platforms (Tensorflow, CoreML, ONNX, ...)*가 선택되어 있는지 확인합니다.

1. Settings 페이지 하단에서 **Save Changes**를 선택합니다.

1. **Train** 버튼을 사용해 모델을 재학습시킵니다. *Quick training*을 선택합니다.

### 작업 - 모델 내보내기

모델 학습이 완료되면 컨테이너로 내보내야 합니다.

1. **Performance** 탭을 선택하고, compact 도메인을 사용해 학습된 최신 반복(iteration)을 찾습니다.

1. 상단의 **Export** 버튼을 선택합니다.

1. **DockerFile**을 선택한 후, 엣지 디바이스에 맞는 버전을 선택합니다:
    * Linux 컴퓨터, Windows 컴퓨터 또는 가상 머신에서 IoT Edge를 실행 중이라면 *Linux* 버전을 선택합니다.
    * Raspberry Pi에서 IoT Edge를 실행 중이라면 *ARM (Raspberry Pi 3)* 버전을 선택합니다.

> 🎓 Docker는 컨테이너 관리를 위한 가장 인기 있는 도구 중 하나이며, DockerFile은 컨테이너를 설정하는 방법에 대한 지침 세트입니다.

1. **Export**를 선택하여 Custom Vision이 관련 파일을 생성하도록 한 후, **Download**를 선택하여 zip 파일로 다운로드합니다.

1. 파일을 컴퓨터에 저장한 후, 폴더를 압축 해제합니다.

## 배포를 위한 컨테이너 준비

![컨테이너는 빌드된 후 컨테이너 레지스트리에 푸시되고, IoT Edge를 사용하여 엣지 디바이스로 배포됩니다.](../../../../../translated_images/ko/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

모델을 다운로드한 후, 컨테이너로 빌드한 다음 컨테이너 레지스트리에 푸시해야 합니다. 컨테이너 레지스트리는 컨테이너를 저장할 수 있는 온라인 위치입니다. IoT Edge는 레지스트리에서 컨테이너를 다운로드한 후 디바이스로 푸시할 수 있습니다.

![Azure Container Registry 로고](../../../../../translated_images/ko/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

이 레슨에서 사용할 컨테이너 레지스트리는 Azure Container Registry입니다. 이 서비스는 무료가 아니므로, 완료 후 [프로젝트 정리](../../../clean-up.md)를 통해 비용을 절약하세요.

> 💁 Azure Container Registry 사용 비용은 [Azure Container Registry 가격 페이지](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn)에서 확인할 수 있습니다.

### 작업 - Docker 설치

분류기를 빌드하고 배포하려면 [Docker](https://www.docker.com/)를 설치해야 할 수 있습니다.

IoT Edge를 설치한 디바이스와 다른 디바이스에서 컨테이너를 빌드하려는 경우에만 Docker를 설치해야 합니다. IoT Edge 설치 과정에서 Docker가 함께 설치됩니다.

1. IoT Edge 디바이스와 다른 디바이스에서 Docker 컨테이너를 빌드하려는 경우, [Docker 설치 페이지](https://www.docker.com/products/docker-desktop)의 지침에 따라 Docker Desktop 또는 Docker 엔진을 설치합니다. 설치 후 Docker가 실행 중인지 확인하세요.

### 작업 - 컨테이너 레지스트리 리소스 생성

1. 터미널 또는 명령 프롬프트에서 다음 명령을 실행하여 Azure Container Registry 리소스를 생성합니다:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    `<Container registry name>`을 컨테이너 레지스트리의 고유 이름으로 바꿉니다. 이름은 `fruitqualitydetector`를 기반으로 하며, 문자와 숫자만 사용할 수 있습니다. 이 이름은 컨테이너 레지스트리에 액세스하기 위한 URL의 일부가 되므로 전 세계적으로 고유해야 합니다.

1. 다음 명령을 사용하여 Azure Container Registry에 로그인합니다:

    ```sh
    az acr login --name <Container registry name>
    ```

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다.

1. 다음 명령을 사용하여 컨테이너 레지스트리를 관리자 모드로 설정하여 비밀번호를 생성합니다:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다.

1. 다음 명령을 사용하여 컨테이너 레지스트리의 비밀번호를 생성합니다:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다.

    `PASSWORD` 값의 복사본을 저장하세요. 나중에 필요합니다.

### 작업 - 컨테이너 빌드

Custom Vision에서 다운로드한 파일은 컨테이너를 빌드하는 방법에 대한 지침이 포함된 DockerFile과, 사용자 정의 비전 모델을 호스팅하고 REST API를 호출하는 애플리케이션 코드입니다. Docker를 사용하여 DockerFile에서 태그가 지정된 컨테이너를 빌드한 다음 컨테이너 레지스트리에 푸시할 수 있습니다.

> 🎓 컨테이너는 이름과 버전을 정의하는 태그를 가집니다. 컨테이너를 업데이트해야 할 때 동일한 태그를 사용하되 새 버전으로 빌드할 수 있습니다.

1. 터미널 또는 명령 프롬프트를 열고 Custom Vision에서 다운로드한 압축 해제된 모델로 이동합니다.

1. 다음 명령을 실행하여 이미지를 빌드하고 태그를 지정합니다:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    `<platform>`을 컨테이너가 실행될 플랫폼으로 바꿉니다. Raspberry Pi에서 IoT Edge를 실행 중이라면 `linux/armhf`로 설정하고, 그렇지 않으면 `linux/amd64`로 설정합니다.

    > 💁 이 명령을 IoT Edge를 실행 중인 디바이스에서 실행하는 경우, 예를 들어 Raspberry Pi에서 실행하는 경우 `--platform <platform>` 부분을 생략할 수 있습니다. 기본적으로 현재 플랫폼으로 설정됩니다.

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다.

    > 💁 Linux 또는 Raspberry Pi OS에서 실행 중인 경우, 이 명령을 실행하려면 `sudo`가 필요할 수 있습니다.

    Docker는 필요한 모든 소프트웨어를 구성하여 이미지를 빌드합니다. 그런 다음 이미지는 `classifier:v1`로 태그가 지정됩니다.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### 작업 - 컨테이너를 컨테이너 레지스트리에 푸시

1. 다음 명령을 사용하여 컨테이너를 컨테이너 레지스트리에 푸시합니다:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다.

    > 💁 Linux를 실행 중인 경우, 이 명령을 실행하려면 `sudo`가 필요할 수 있습니다.

    컨테이너가 컨테이너 레지스트리에 푸시됩니다.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. 푸시를 확인하려면 다음 명령을 사용하여 레지스트리의 컨테이너 목록을 확인합니다:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    출력에서 분류기가 나열된 것을 볼 수 있습니다.

## 컨테이너 배포

이제 컨테이너를 IoT Edge 디바이스에 배포할 수 있습니다. 배포하려면 배포 매니페스트를 정의해야 합니다. 이는 엣지 디바이스에 배포될 모듈을 나열하는 JSON 문서입니다.

### 작업 - 배포 매니페스트 생성

1. 컴퓨터에 `deployment.json`이라는 새 파일을 생성합니다.

1. 이 파일에 다음 내용을 추가합니다:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 이 파일은 [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) 폴더에서 찾을 수 있습니다.

    `<Container registry name>`을 컨테이너 레지스트리 이름으로 바꿉니다. `ImageClassifier` 모듈 섹션에 하나, `registryCredentials` 섹션에 두 개가 있습니다.

    `registryCredentials` 섹션의 `<Container registry password>`를 컨테이너 레지스트리 비밀번호로 바꿉니다.

1. 배포 매니페스트가 포함된 폴더에서 다음 명령을 실행합니다:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub 이름으로 바꿉니다.

    이미지 분류기 모듈이 엣지 디바이스에 배포됩니다.

### 작업 - 분류기가 실행 중인지 확인

1. IoT Edge 디바이스에 연결합니다:
    * Raspberry Pi에서 IoT Edge를 실행 중이라면 터미널에서 ssh를 사용하거나 VS Code에서 원격 SSH 세션을 통해 연결합니다.
    * Windows에서 Linux 컨테이너로 IoT Edge를 실행 중이라면 [성공적인 구성 확인 가이드](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration)를 따라 IoT Edge 디바이스에 연결합니다.
    * 가상 머신에서 IoT Edge를 실행 중이라면 VM 생성 시 설정한 `adminUsername`과 `password`를 사용하여 IP 주소 또는 DNS 이름으로 SSH를 통해 연결합니다:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        또는:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        비밀번호를 입력하라는 메시지가 표시되면 입력합니다.

1. 연결 후, 다음 명령을 실행하여 IoT Edge 모듈 목록을 확인합니다:

    ```sh
    iotedge list
    ```

    > 💁 이 명령을 실행하려면 `sudo`가 필요할 수 있습니다.

    실행 중인 모듈을 볼 수 있습니다:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. 이미지 분류기 모듈의 로그를 확인하려면 다음 명령을 실행합니다:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 이 명령을 실행하려면 `sudo`가 필요할 수 있습니다.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### 작업 - 이미지 분류기 테스트

1. CURL을 사용하여 IoT Edge 에이전트를 실행 중인 컴퓨터의 IP 주소 또는 호스트 이름을 사용해 이미지 분류기를 테스트할 수 있습니다. IP 주소를 찾으세요:
    * IoT Edge가 실행 중인 동일한 머신에 있다면 호스트 이름으로 `localhost`를 사용할 수 있습니다.
    * VM을 사용하는 경우, VM의 IP 주소 또는 DNS 이름을 사용할 수 있습니다.
    * 그렇지 않으면 IoT Edge를 실행 중인 머신의 IP 주소를 확인하세요:
      * Windows 10에서는 [IP 주소 찾기 가이드](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)를 따르세요.
      * macOS에서는 [Mac에서 IP 주소 찾기 가이드](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)를 따르세요.
      * Linux에서는 [Linux에서 IP 주소 찾기 가이드](https://opensource.com/article/18/5/how-find-ip-address-linux)의 개인 IP 주소 찾기 섹션을 따르세요.

1. 로컬 파일로 컨테이너를 테스트하려면 다음 curl 명령을 실행합니다:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    `<IP address or name>`을 IoT Edge를 실행 중인 컴퓨터의 IP 주소 또는 호스트 이름으로 바꿉니다. `<file_Name>`을 테스트할 파일 이름으로 바꿉니다.

    출력에서 예측 결과를 볼 수 있습니다:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 여기서는 Azure 리소스를 사용하지 않으므로 예측 키를 제공할 필요가 없습니다. 대신 내부 네트워크의 보안 요구 사항에 따라 내부 보안이 구성됩니다. 이는 공용 엔드포인트와 API 키에 의존하지 않습니다.

## IoT Edge 디바이스 사용

이제 이미지 분류기가 IoT Edge 디바이스에 배포되었으므로 IoT 디바이스에서 이를 사용할 수 있습니다.

### 작업 - IoT Edge 디바이스 사용

다음 가이드를 따라 IoT Edge 분류기를 사용하여 이미지를 분류하세요:

* [Arduino - Wio Terminal](wio-terminal.md)
* [단일 보드 컴퓨터 - Raspberry Pi/가상 IoT 디바이스](single-board-computer.md)

### 모델 재학습

IoT Edge에서 이미지 분류기를 실행하는 단점 중 하나는 Custom Vision 프로젝트와 연결되지 않는다는 점입니다. Custom Vision의 **Predictions** 탭에서 Edge 기반 분류기를 사용해 분류된 이미지를 볼 수 없습니다.

이는 예상된 동작입니다. 이미지는 분류를 위해 클라우드로 전송되지 않으므로 클라우드에서 사용할 수 없습니다. IoT Edge를 사용하는 장점 중 하나는 프라이버시를 보장하여 이미지가 네트워크를 벗어나지 않도록 하는 것이며, 또 다른 장점은 오프라인으로 작업할 수 있다는 점입니다. 즉, 디바이스에 인터넷 연결이 없을 때 이미지를 업로드할 필요가 없습니다. 단점은 모델을 개선하는 것입니다. 이미지를 수동으로 재분류하여 이미지 분류기를 개선하고 재학습시키는 다른 방법을 구현해야 합니다.

✅ 분류기를 재학습시키기 위해 이미지를 업로드하는 방법을 생각해 보세요.

---

## 🚀 도전 과제

엣지 디바이스에서 AI 모델을 실행하면 네트워크 홉이 짧아져 클라우드보다 더 빠를 수 있습니다. 하지만 모델을 실행하는 하드웨어가 클라우드만큼 강력하지 않을 수 있어 더 느릴 수도 있습니다.

엣지 디바이스 호출이 클라우드 호출보다 빠른지 또는 느린지 비교하고, 차이의 이유를 생각해 보세요. 또는 차이가 없는 이유를 설명해 보세요. 엣지에서 AI 모델을 더 빠르게 실행할 수 있는 특수 하드웨어를 연구해 보세요.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## 복습 및 자습

* [Wikipedia의 OS 수준 가상화 페이지](https://wikipedia.org/wiki/OS-level_virtualization)에서 컨테이너에 대해 더 읽어보세요.
* 5G가 엣지 컴퓨팅을 확장하는 데 어떻게 기여할 수 있는지에 중점을 두고, [NetworkWorld의 "엣지 컴퓨팅이란 무엇이며 왜 중요한가?" 기사](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)를 읽어보세요.
* IoT Edge에서 AI 서비스를 실행하는 방법에 대해 더 알아보려면, [Microsoft Channel9의 Learn Live 에피소드 "엣지에서 사전 구축된 AI 서비스를 사용하여 언어 감지를 수행하는 방법 배우기"](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)를 시청하세요.

## 과제

[엣지에서 다른 서비스 실행하기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.