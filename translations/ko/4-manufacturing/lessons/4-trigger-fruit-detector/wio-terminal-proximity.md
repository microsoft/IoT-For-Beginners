<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-24T21:55:31+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "ko"
}
-->
# 근접 감지 - Wio Terminal

이 수업의 이 부분에서는 Wio Terminal에 근접 센서를 추가하고, 센서로부터 거리를 읽는 방법을 배웁니다.

## 하드웨어

Wio Terminal에는 근접 센서가 필요합니다.

사용할 센서는 [Grove Time of Flight 거리 센서](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)입니다. 이 센서는 레이저 거리 측정 모듈을 사용하여 거리를 감지합니다. 이 센서는 10mm에서 2000mm(1cm - 2m) 범위의 거리를 감지할 수 있으며, 1000mm 이상의 거리는 8109mm로 보고됩니다.

레이저 거리 측정기는 센서의 뒷면에 있으며, Grove 소켓의 반대쪽에 위치합니다.

이 센서는 I

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.