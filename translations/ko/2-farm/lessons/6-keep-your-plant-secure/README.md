<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "81c437c568eee1b0dda1f04e88150d37",
  "translation_date": "2025-08-24T22:55:27+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/README.md",
  "language_code": "ko"
}
-->
# 식물을 안전하게 보호하세요

![이 강의의 스케치노트 개요](../../../../../translated_images/lesson-10.829c86b80b9403bb770929ee553a1d293afe50dc23121aaf9be144673ae012cc.ko.jpg)

> 스케치노트 제공: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## 소개

지난 몇 강의에서 토양 모니터링 IoT 장치를 만들고 이를 클라우드에 연결하는 방법을 배웠습니다. 그런데 만약 경쟁 농부를 위해 일하는 해커가 여러분의 IoT 장치를 장악한다면 어떻게 될까요? 그들이 높은 토양 수분 데이터를 보내 식물이 물을 전혀 받지 못하게 하거나, 물을 너무 많이 주어 식물이 과습으로 죽고 물 비용이 크게 증가하게 만들 수도 있습니다.

이번 강의에서는 IoT 장치를 안전하게 보호하는 방법을 배웁니다. 또한, 이번 프로젝트의 마지막 강의이므로 클라우드 리소스를 정리하여 잠재적인 비용을 줄이는 방법도 배울 것입니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [왜 IoT 장치를 보호해야 할까요?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [암호화](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [IoT 장치 보호하기](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [X.509 인증서 생성 및 사용](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 이번 강의는 프로젝트의 마지막 강의이므로 강의와 과제를 완료한 후 클라우드 서비스를 정리하는 것을 잊지 마세요. 과제를 완료하려면 서비스가 필요하니 먼저 과제를 완료하세요.
>
> 필요하다면 [프로젝트 정리 가이드](../../../clean-up.md)를 참조하여 정리 방법을 확인하세요.

## 왜 IoT 장치를 보호해야 할까요?

IoT 보안은 예상된 장치만이 클라우드 IoT 서비스에 연결하고 텔레메트리를 보낼 수 있도록 하며, 클라우드 서비스만이 장치에 명령을 보낼 수 있도록 보장하는 것을 포함합니다. IoT 데이터는 의료 정보나 개인적인 데이터를 포함할 수 있으므로, 애플리케이션 전체가 이러한 데이터가 유출되지 않도록 보안을 고려해야 합니다.

IoT 애플리케이션이 안전하지 않다면 다음과 같은 위험이 있습니다:

* 가짜 장치가 잘못된 데이터를 보내 애플리케이션이 잘못된 반응을 하게 만들 수 있습니다. 예를 들어, 지속적으로 높은 토양 수분 데이터를 보내 관개 시스템이 작동하지 않아 식물이 물 부족으로 죽을 수 있습니다.
* 승인되지 않은 사용자가 IoT 장치의 데이터를 읽어 개인 정보나 중요한 비즈니스 데이터를 유출할 수 있습니다.
* 해커가 장치를 제어하는 명령을 보내 장치나 연결된 하드웨어에 손상을 줄 수 있습니다.
* IoT 장치에 연결하여 추가 네트워크에 접근해 개인 시스템에 침투할 수 있습니다.
* 악의적인 사용자가 개인 데이터를 접근하여 이를 이용해 협박할 수 있습니다.

이러한 상황은 실제로 발생하며, 항상 일어날 가능성이 있습니다. 이전 강의에서 몇 가지 사례를 소개했지만, 추가 사례를 아래에 제시합니다:

* 2018년, 해커가 물고기 탱크 온도 조절기의 열린 WiFi 액세스 포인트를 이용해 카지노 네트워크에 침투하여 데이터를 훔쳤습니다. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* 2016년, Mirai Botnet이 Dyn이라는 인터넷 서비스 제공업체를 대상으로 서비스 거부 공격을 실행하여 인터넷의 큰 부분을 다운시켰습니다. 이 봇넷은 DVR과 카메라 같은 IoT 장치의 기본 사용자 이름과 비밀번호를 이용해 연결한 후 공격을 실행했습니다. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys는 CloudPets 연결 장난감 사용자 데이터베이스를 인터넷에 공개적으로 노출시켰습니다. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava는 지나가는 러너를 태그하고 그들의 경로를 보여주어 낯선 사람이 사용자의 집 위치를 알 수 있게 했습니다. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ 연구해보세요: IoT 해킹 및 데이터 유출 사례를 더 찾아보세요. 특히 인터넷에 연결된 칫솔이나 체중계 같은 개인 물품과 관련된 사례를 찾아보세요. 이러한 해킹이 피해자나 고객에게 어떤 영향을 미칠지 생각해보세요.

> 💁 보안은 매우 광범위한 주제이며, 이번 강의에서는 장치를 클라우드에 연결하는 기본적인 내용만 다룹니다. 데이터 전송 중 변경 사항 모니터링, 장치 직접 해킹, 장치 구성 변경 등은 다루지 않습니다. IoT 해킹은 큰 위협이므로 [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn)와 같은 도구가 개발되었습니다. 이러한 도구는 컴퓨터에서 사용하는 안티바이러스 및 보안 도구와 유사하지만, 소형 저전력 IoT 장치에 맞게 설계되었습니다.

## 암호화

장치가 IoT 서비스에 연결할 때, ID를 사용하여 자신을 식별합니다. 문제는 이 ID가 복제될 수 있다는 것입니다. 해커가 악성 장치를 설정하여 실제 장치와 동일한 ID를 사용하면서 잘못된 데이터를 보낼 수 있습니다.

![유효한 장치와 악성 장치가 동일한 ID를 사용하여 텔레메트리를 보낼 수 있음](../../../../../translated_images/iot-device-and-hacked-device-connecting.e0671675df74d6d99eb1dedb5a670e606f698efa6202b1ad4c8ae548db299cc6.ko.png)

이를 해결하기 위해 전송되는 데이터를 장치와 클라우드만 알고 있는 값을 사용하여 암호화된 형식으로 변환합니다. 이 과정을 *암호화*라고 하며, 데이터를 암호화하는 데 사용되는 값을 *암호화 키*라고 합니다.

![암호화를 사용하면 암호화된 메시지만 수락되고 다른 메시지는 거부됨](../../../../../translated_images/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f979e46f2849b573564eeb4a4dc5b52f669f62745397492fb.ko.png)

클라우드 서비스는 암호화 키를 사용하여 데이터를 읽을 수 있는 형식으로 다시 변환하며, 이를 *복호화*라고 합니다. 암호화된 메시지가 키로 복호화되지 않으면 장치가 해킹된 것으로 간주되어 메시지가 거부됩니다.

암호화 및 복호화를 수행하는 기술을 *암호학*이라고 합니다.

### 초기 암호학

가장 초기의 암호학은 대체 암호 방식으로, 약 3,500년 전으로 거슬러 올라갑니다. 대체 암호 방식은 한 글자를 다른 글자로 대체하는 방식입니다. 예를 들어, [Caesar 암호](https://wikipedia.org/wiki/Caesar_cipher)는 알파벳을 정해진 양만큼 이동시키며, 암호화된 메시지의 발신자와 수신자만 이동할 글자 수를 알고 있습니다.

[Vigenère 암호](https://wikipedia.org/wiki/Vigenère_cipher)는 단어를 사용하여 텍스트를 암호화하여 원본 텍스트의 각 글자가 다른 양만큼 이동하도록 했습니다.

암호학은 고대 메소포타미아에서 도공의 유약 제조법을 보호하거나, 인도에서 비밀 연애 편지를 쓰거나, 고대 이집트에서 마법 주문을 비밀로 유지하는 등 다양한 목적으로 사용되었습니다.

### 현대 암호학

현대 암호학은 훨씬 더 발전하여 초기 방식보다 해독하기 어렵습니다. 현대 암호학은 복잡한 수학을 사용하여 데이터를 암호화하며, 가능한 키가 너무 많아 무차별 대입 공격이 불가능합니다.

암호학은 안전한 통신을 위해 다양한 방식으로 사용됩니다. 이 페이지를 GitHub에서 읽고 있다면 웹 사이트 주소가 *HTTPS*로 시작하는 것을 볼 수 있습니다. 이는 브라우저와 GitHub 웹 서버 간의 통신이 암호화되었음을 의미합니다. 누군가 브라우저와 GitHub 간의 인터넷 트래픽을 읽을 수 있다 하더라도 데이터는 암호화되어 읽을 수 없습니다. 컴퓨터는 하드 드라이브의 모든 데이터를 암호화하여 누군가가 이를 훔치더라도 비밀번호 없이는 데이터를 읽을 수 없게 할 수도 있습니다.

> 🎓 HTTPS는 HyperText Transfer Protocol **Secure**의 약자입니다.

안타깝게도 모든 것이 안전한 것은 아닙니다. 일부 장치는 보안이 없거나, 쉽게 해독할 수 있는 키를 사용하거나, 동일한 유형의 모든 장치가 동일한 키를 사용하는 경우도 있습니다. 매우 개인적인 IoT 장치가 WiFi 또는 Bluetooth를 통해 연결하기 위한 동일한 비밀번호를 가지고 있는 사례도 보고된 바 있습니다. 자신의 장치에 연결할 수 있다면 다른 사람의 장치에도 연결할 수 있습니다. 연결되면 매우 개인적인 데이터를 접근하거나 장치를 제어할 수 있습니다.

> 💁 현대 암호학의 복잡성과 암호 해독이 수십억 년이 걸릴 수 있다는 주장에도 불구하고, 양자 컴퓨팅의 발전으로 인해 알려진 모든 암호화를 매우 짧은 시간 안에 해독할 가능성이 생겼습니다!

### 대칭 키와 비대칭 키

암호화는 대칭과 비대칭 두 가지 유형이 있습니다.

**대칭** 암호화는 데이터를 암호화하고 복호화하는 데 동일한 키를 사용합니다. 발신자와 수신자는 동일한 키를 알아야 합니다. 이는 가장 안전하지 않은 유형으로, 키를 공유해야 하기 때문입니다. 발신자가 암호화된 메시지를 수신자에게 보내려면 먼저 수신자에게 키를 보내야 할 수도 있습니다.

![대칭 키 암호화는 동일한 키를 사용하여 메시지를 암호화하고 복호화함](../../../../../translated_images/send-message-symmetric-key.a2e8ad0d495896ffcdf15d25bb4491c695a5cb851457b359fb0f0c89d67707c9.ko.png)

키가 전송 중에 도난당하거나 발신자 또는 수신자가 해킹당해 키가 발견되면 암호화가 해독될 수 있습니다.

![대칭 키 암호화는 해커가 키를 얻지 못할 때만 안전함 - 키를 얻으면 메시지를 가로채고 복호화할 수 있음](../../../../../translated_images/send-message-symmetric-key-hacker.e7cb53db1707adfb1486a8144060cb76435fe8dbdede8cecc09e7d15b2d9a251.ko.png)

**비대칭** 암호화는 암호화 키와 복호화 키, 즉 공개/비공개 키 쌍을 사용합니다. 공개 키는 메시지를 암호화하는 데 사용되지만 복호화할 수 없으며, 비공개 키는 메시지를 복호화하는 데 사용되지만 암호화할 수 없습니다.

![비대칭 암호화는 암호화와 복호화에 다른 키를 사용함. 암호화 키는 메시지 발신자에게 제공되어 메시지를 암호화한 후 수신자에게 보냄](../../../../../translated_images/send-message-asymmetric.7abe327c62615b8c19805252af5d4b6c5e7aaeb8fbc455efeff866fe2d300b62.ko.png)

수신자는 공개 키를 공유하고, 발신자는 이를 사용하여 메시지를 암호화합니다. 메시지가 전송되면 수신자는 비공개 키를 사용하여 이를 복호화합니다. 비대칭 암호화는 비공개 키가 수신자에 의해 비공개로 유지되고 절대 공유되지 않으므로 더 안전합니다. 공개 키는 메시지를 암호화하는 데만 사용되므로 누구나 가질 수 있습니다.

대칭 암호화는 비대칭 암호화보다 빠르며, 비대칭 암호화는 더 안전합니다. 일부 시스템은 두 가지를 모두 사용합니다. 대칭 키를 암호화하고 공유하기 위해 비대칭 암호화를 사용한 다음, 모든 데이터를 암호화하기 위해 대칭 키를 사용합니다. 이렇게 하면 발신자와 수신자 간에 대칭 키를 공유하는 것이 더 안전해지고, 데이터를 암호화하고 복호화하는 속도가 빨라집니다.

## IoT 장치 보호하기

IoT 장치는 대칭 또는 비대칭 암호화를 사용하여 보호할 수 있습니다. 대칭 암호화는 더 간단하지만 덜 안전합니다.

### 대칭 키

IoT 장치를 IoT Hub와 상호작용하도록 설정할 때 연결 문자열을 사용했습니다. 연결 문자열의 예는 다음과 같습니다:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

이 연결 문자열은 세미콜론으로 구분된 세 부분으로 구성되며, 각 부분은 키와 값으로 이루어져 있습니다:

| 키 | 값 | 설명 |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | IoT Hub의 URL |
| DeviceId | `soil-moisture-sensor` | 장치의 고유 ID |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | 장치와 IoT Hub가 알고 있는 대칭 키 |

이 연결 문자열의 마지막 부분인 `SharedAccessKey`는 장치와 IoT Hub가 알고 있는 대칭 키입니다. 이 키는 장치에서 클라우드로, 또는 클라우드에서 장치로 전송되지 않습니다. 대신 전송되거나 수신되는 데이터를 암호화하는 데 사용됩니다.

✅ 실험해보세요. IoT 장치에 연결할 때 연결 문자열의 `SharedAccessKey` 부분을 변경하면 어떤 일이 발생할지 생각해보세요. 직접 시도해보세요.

장치가 처음 연결을 시도할 때, URL, 만료 시간(보통 현재 시간으로부터 1일), 그리고 서명을 포함하는 공유 액세스 서명(SAS) 토큰을 보냅니다. 이 서명은 URL과 만료 시간을 연결 문자열의 공유 액세스 키로 암호화한 값입니다.

IoT Hub는 이 서명을 공유 액세스 키로 복호화하며, 복호화된 값이 URL과 만료 시간과 일치하면 장치가 연결을 허용받습니다. 또한 현재 시간이 만료 시간 이전인지 확인하여 악성 장치가 실제 장치의 SAS 토큰을 캡처하여 사용하는 것을 방지합니다.

이 방법은 발신자가 올바른 장치임을 확인하는 우아한 방법입니다. 암호화되지 않은 데이터와 암호화된 데이터를 모두 보내면, 서버는 암호화된 데이터를 복호화하여 복호화된 값이 암호화되지 않은 데이터와 일치하는지 확인합니다. 일치하면 발신자와 수신자가 동일한 대칭 암호화 키를 가지고 있음을 의미합니다.
💁 IoT 기기는 만료 시간 때문에 정확한 시간을 알아야 하며, 보통 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 서버에서 읽어옵니다. 시간이 정확하지 않으면 연결이 실패할 수 있습니다.
연결 후, 디바이스에서 IoT Hub로 보내는 데이터나 IoT Hub에서 디바이스로 보내는 모든 데이터는 공유 액세스 키를 사용해 암호화됩니다.

✅ 여러 디바이스가 동일한 연결 문자열을 공유하면 어떤 일이 발생할까요?

> 💁 이 키를 코드에 저장하는 것은 보안상 좋지 않은 관행입니다. 해커가 소스 코드를 얻으면 키를 탈취할 수 있습니다. 또한, 코드를 배포할 때마다 각 디바이스에 대해 업데이트된 키로 다시 컴파일해야 하므로 더 어렵습니다. 이 키를 하드웨어 보안 모듈(HSM)에서 로드하는 것이 더 좋습니다. HSM은 IoT 디바이스에 내장된 칩으로, 암호화된 값을 저장하고 코드에서 이를 읽을 수 있습니다.
>
> IoT를 학습할 때는 이전 강의에서 했던 것처럼 키를 코드에 넣는 것이 더 쉬울 수 있지만, 이 키가 공개 소스 코드 관리에 체크인되지 않도록 주의해야 합니다.

디바이스에는 2개의 키와 이에 대응하는 2개의 연결 문자열이 있습니다. 이를 통해 키를 교체할 수 있습니다. 즉, 첫 번째 키가 손상되었을 경우 두 번째 키로 전환하고 첫 번째 키를 재생성할 수 있습니다.

### X.509 인증서

공개/비공개 키 쌍을 사용하는 비대칭 암호화를 사용할 때, 데이터를 보내고자 하는 사람에게 공개 키를 제공해야 합니다. 문제는, 키를 받는 사람이 그것이 실제로 당신의 공개 키인지, 아니면 누군가가 당신인 척하는 것인지 어떻게 확신할 수 있을까요? 키를 제공하는 대신, 신뢰할 수 있는 제3자에 의해 검증된 인증서에 공개 키를 포함시켜 제공할 수 있습니다. 이를 X.509 인증서라고 합니다.

X.509 인증서는 공개/비공개 키 쌍의 공개 키 부분을 포함하는 디지털 문서입니다. 일반적으로 [인증 기관(CA)](https://wikipedia.org/wiki/Certificate_authority)이라고 불리는 신뢰할 수 있는 조직 중 하나에 의해 발급되며, CA가 디지털 서명을 통해 키가 유효하며 당신으로부터 온 것임을 나타냅니다. 여권이나 운전면허증을 발급한 국가를 신뢰하듯이, CA를 신뢰하기 때문에 인증서를 신뢰하고 공개 키가 인증서에 명시된 사람으로부터 온 것임을 믿을 수 있습니다. 인증서는 비용이 들기 때문에 테스트 목적으로 '자체 서명(self-sign)'하여 직접 인증서를 생성할 수도 있습니다.

> 💁 자체 서명 인증서는 프로덕션 릴리스에서 절대 사용해서는 안 됩니다.

이 인증서에는 공개 키의 소유자, 인증서를 발급한 CA의 세부 정보, 유효 기간, 공개 키 자체 등 여러 필드가 포함되어 있습니다. 인증서를 사용하기 전에, 원래 CA에 의해 서명되었는지 확인하는 것이 좋은 관행입니다.

✅ 인증서의 필드 전체 목록은 [Microsoft의 X.509 공개 키 인증서 이해 튜토리얼](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)에서 확인할 수 있습니다.

X.509 인증서를 사용할 때, 송신자와 수신자는 각각 자신의 공개 키와 비공개 키를 가지며, X.509 인증서도 각각 보유합니다. 그런 다음, 서로의 X.509 인증서를 교환하고, 상대방의 공개 키를 사용해 데이터를 암호화하며, 자신의 비공개 키를 사용해 수신한 데이터를 복호화합니다.

![공개 키를 공유하는 대신 인증서를 공유할 수 있습니다. 인증서 사용자는 인증서를 서명한 인증 기관을 통해 그것이 당신으로부터 온 것임을 확인할 수 있습니다.](../../../../../translated_images/send-message-certificate.9cc576ac1e46b76eb58ebc8eedaa522566fa0700076da46f5180aad78c2435db.ko.png)

X.509 인증서를 사용하는 큰 장점 중 하나는 디바이스 간에 공유할 수 있다는 점입니다. 하나의 인증서를 생성하여 IoT Hub에 업로드하고, 이를 모든 디바이스에서 사용할 수 있습니다. 각 디바이스는 IoT Hub에서 수신한 메시지를 복호화하기 위해 비공개 키만 알면 됩니다.

디바이스가 IoT Hub로 보내는 메시지를 암호화하는 데 사용하는 인증서는 Microsoft에서 발행합니다. 이는 많은 Azure 서비스에서 사용하는 동일한 인증서이며, 때로는 SDK에 내장되어 있습니다.

> 💁 공개 키는 말 그대로 공개된 키입니다. Azure 공개 키는 Azure로 보내는 데이터를 암호화하는 데만 사용할 수 있으며, 복호화에는 사용할 수 없으므로 어디에서나 공유할 수 있습니다. 예를 들어, [Azure IoT C SDK 소스 코드](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c)에서도 확인할 수 있습니다.

✅ X.509 인증서에는 많은 전문 용어가 포함되어 있습니다. [X.509 인증서 용어에 대한 초보자 가이드](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)에서 자주 접할 수 있는 용어의 정의를 읽어보세요.

## X.509 인증서 생성 및 사용

X.509 인증서를 생성하는 단계는 다음과 같습니다:

1. 공개/비공개 키 쌍 생성. 공개/비공개 키 쌍을 생성하는 데 가장 널리 사용되는 알고리즘 중 하나는 [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA)입니다.

1. 공개 키와 관련 데이터를 서명을 위해 제출. 이는 CA를 통해서든 자체 서명을 통해서든 가능합니다.

Azure CLI에는 IoT Hub에서 새로운 디바이스 ID를 생성하고, 공개/비공개 키 쌍을 자동으로 생성하며, 자체 서명 인증서를 생성하는 명령어가 포함되어 있습니다.

> 💁 Azure CLI를 사용하지 않고 세부 단계를 보고 싶다면, [Microsoft IoT Hub 문서의 OpenSSL을 사용한 자체 서명 인증서 생성 튜토리얼](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)을 참조하세요.

### 작업 - X.509 인증서를 사용해 디바이스 ID 생성

1. 다음 명령어를 실행하여 새로운 디바이스 ID를 등록하고, 키와 인증서를 자동으로 생성하세요:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    `<hub_name>`을 IoT Hub의 이름으로 대체하세요.

    이 명령어는 `soil-moisture-sensor-x509`라는 ID를 가진 디바이스를 생성하여 이전 강의에서 생성한 디바이스 ID와 구분합니다. 이 명령어는 현재 디렉터리에 두 개의 파일도 생성합니다:

    * `soil-moisture-sensor-x509-key.pem` - 이 파일은 디바이스의 비공개 키를 포함합니다.
    * `soil-moisture-sensor-x509-cert.pem` - 이 파일은 디바이스의 X.509 인증서 파일입니다.

    이 파일들을 안전하게 보관하세요! 비공개 키 파일은 공개 소스 코드 관리에 체크인되지 않아야 합니다.

### 작업 - 디바이스 코드에서 X.509 인증서 사용

X.509 인증서를 사용해 IoT 디바이스를 클라우드에 연결하는 관련 가이드를 따라 작업하세요:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [단일 보드 컴퓨터 - Raspberry Pi/가상 IoT 디바이스](single-board-computer-x509.md)

---

## 🚀 도전 과제

Resource Group 및 IoT Hub와 같은 Azure 서비스를 생성, 관리 및 삭제하는 방법은 여러 가지가 있습니다. 그 중 하나는 [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn)입니다. 이는 Azure 서비스를 관리할 수 있는 GUI를 제공하는 웹 기반 인터페이스입니다.

[portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn)에 접속하여 포털을 탐색해보세요. IoT Hub를 생성한 후 삭제할 수 있는지 확인해보세요.

**힌트** - 포털을 통해 서비스를 생성할 때, Resource Group을 미리 생성할 필요는 없습니다. 서비스를 생성하는 동안 Resource Group을 생성할 수 있습니다. 작업이 끝나면 반드시 삭제하세요!

Azure Portal에 대한 문서, 튜토리얼 및 가이드는 [Azure 포털 문서](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn)에서 확인할 수 있습니다.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## 복습 및 자습

* [Wikipedia의 암호학 역사 페이지](https://wikipedia.org/wiki/History_of_cryptography)에서 암호학의 역사를 읽어보세요.
* [Wikipedia의 X.509 페이지](https://wikipedia.org/wiki/X.509)에서 X.509 인증서에 대해 읽어보세요.

## 과제

[새로운 IoT 디바이스 구축](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.