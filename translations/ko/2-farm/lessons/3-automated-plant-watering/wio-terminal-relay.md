<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-24T22:17:20+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "ko"
}
-->
# 릴레이 제어 - Wio Terminal

이 레슨에서는 토양 수분 센서에 추가로 Wio Terminal에 릴레이를 추가하고, 토양 수분 수준에 따라 릴레이를 제어하는 방법을 배웁니다.

## 하드웨어

Wio Terminal에는 릴레이가 필요합니다.

사용할 릴레이는 [Grove 릴레이](https://www.seeedstudio.com/Grove-Relay.html)로, 일반적으로 열려 있는 릴레이입니다(즉, 릴레이에 신호가 전달되지 않을 때 출력 회로가 열려 있거나 연결이 끊어져 있음). 이 릴레이는 최대 250V 및 10A의 출력 회로를 처리할 수 있습니다.

이 릴레이는 디지털 액추에이터로, Wio Terminal의 디지털 핀에 연결됩니다. 아날로그/디지털 포트는 이미 토양 수분 센서와 연결되어 있으므로, 이 릴레이는 다른 포트에 연결됩니다. 해당 포트는 I

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서의 원어 버전을 권위 있는 출처로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 책임을 지지 않습니다.