<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-25T00:32:47+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "ko"
}
-->
# 마이크와 스피커 설정하기 - Wio Terminal

이 강의의 이 부분에서는 Wio Terminal에 스피커를 추가합니다. Wio Terminal에는 이미 내장 마이크가 있어 음성을 캡처할 수 있습니다.

## 하드웨어

Wio Terminal에는 이미 내장 마이크가 있어 음성 인식을 위한 오디오를 캡처할 수 있습니다.

![Wio Terminal의 마이크](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.ko.png)

스피커를 추가하려면 [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)을 사용할 수 있습니다. 이 보드는 2개의 MEMS 마이크, 스피커 커넥터, 헤드폰 소켓을 포함한 외부 보드입니다.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.ko.png)

헤드폰, 3.5mm 잭이 있는 스피커, 또는 [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)과 같은 JST 연결이 있는 스피커 중 하나를 추가해야 합니다.

ReSpeaker 2-Mics Pi Hat을 연결하려면 40핀 점퍼 케이블(일명 male-to-male 점퍼 케이블)이 필요합니다.

> 💁 납땜에 익숙하다면 [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html)을 사용하여 ReSpeaker를 연결할 수 있습니다.

오디오를 다운로드하고 재생하려면 SD 카드도 필요합니다. Wio Terminal은 최대 16GB 크기의 SD 카드만 지원하며, FAT32 또는 exFAT 형식으로 포맷해야 합니다.

### 작업 - ReSpeaker Pi Hat 연결하기

1. Wio Terminal의 전원을 끈 상태에서 점퍼 케이블과 Wio Terminal 뒷면의 GPIO 소켓을 사용하여 ReSpeaker 2-Mics Pi Hat을 Wio Terminal에 연결합니다.

    핀은 다음과 같이 연결해야 합니다:

    ![핀 다이어그램](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.ko.png)

1. GPIO 소켓이 위를 향하도록 ReSpeaker와 Wio Terminal을 배치하고, 왼쪽에 위치시킵니다.

1. ReSpeaker의 GPIO 소켓 왼쪽 상단에서 시작합니다. 점퍼 케이블을 사용하여 ReSpeaker의 왼쪽 상단 소켓에서 Wio Terminal의 왼쪽 상단 소켓으로 연결합니다.

1. GPIO 소켓의 왼쪽을 따라 이 과정을 반복합니다. 핀이 단단히 고정되었는지 확인하세요.

    ![왼쪽 핀이 Wio Terminal의 왼쪽 핀에 연결된 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.ko.png)

    ![왼쪽 핀이 Wio Terminal의 왼쪽 핀에 연결된 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.ko.png)

    > 💁 점퍼 케이블이 리본 형태로 연결되어 있다면, 케이블을 함께 유지하세요. 이렇게 하면 모든 케이블을 순서대로 연결하기가 더 쉬워집니다.

1. ReSpeaker와 Wio Terminal의 GPIO 소켓 오른쪽에서도 동일한 과정을 반복합니다. 이 케이블은 이미 연결된 케이블 주위를 돌아가야 합니다.

    ![오른쪽 핀이 Wio Terminal의 오른쪽 핀에 연결된 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.ko.png)

    ![오른쪽 핀이 Wio Terminal의 오른쪽 핀에 연결된 ReSpeaker](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.ko.png)

    > 💁 점퍼 케이블이 리본 형태로 연결되어 있다면, 두 개의 리본으로 나누세요. 기존 케이블 양쪽으로 각각 통과시킵니다.

    > 💁 핀이 빠지지 않도록 테이프를 사용해 고정할 수 있습니다.
    >
    > ![테이프로 고정된 핀](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.ko.png)

1. 스피커를 추가해야 합니다.

    * JST 케이블이 있는 스피커를 사용하는 경우, ReSpeaker의 JST 포트에 연결합니다.

      ![JST 케이블로 ReSpeaker에 연결된 스피커](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.ko.png)

    * 3.5mm 잭이 있는 스피커나 헤드폰을 사용하는 경우, 3.5mm 잭 소켓에 삽입합니다.

      ![3.5mm 잭 소켓으로 ReSpeaker에 연결된 스피커](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.ko.png)

### 작업 - SD 카드 설정하기

1. SD 카드를 컴퓨터에 연결합니다. SD 카드 슬롯이 없는 경우 외부 리더기를 사용하세요.

1. 컴퓨터에서 적절한 도구를 사용해 SD 카드를 포맷합니다. 파일 시스템은 FAT32 또는 exFAT을 사용해야 합니다.

1. Wio Terminal의 왼쪽 전원 버튼 바로 아래에 있는 SD 카드 슬롯에 SD 카드를 삽입합니다. 카드가 완전히 들어가고 클릭 소리가 나도록 삽입하세요. 얇은 도구나 다른 SD 카드를 사용해 끝까지 밀어 넣어야 할 수도 있습니다.

    ![전원 스위치 아래 SD 카드 슬롯에 SD 카드를 삽입하는 모습](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.ko.png)

    > 💁 SD 카드를 꺼내려면 약간 밀어 넣으면 튀어나옵니다. 이를 위해 얇은 도구(예: 일자 드라이버 또는 다른 SD 카드)가 필요할 수 있습니다.

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.