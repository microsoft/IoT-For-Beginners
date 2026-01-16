<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-24T22:03:39+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "ko"
}
-->
# Jupyter Notebook을 사용하여 GDD 데이터 시각화하기

## 지침

이 강의에서는 IoT 센서를 사용하여 GDD 데이터를 수집했습니다. 좋은 GDD 데이터를 얻으려면 여러 날 동안 데이터를 수집해야 합니다. 온도 데이터를 시각화하고 GDD를 계산하려면 [Jupyter Notebooks](https://jupyter.org)와 같은 도구를 사용하여 데이터를 분석할 수 있습니다.

먼저 며칠 동안 데이터를 수집하세요. IoT 장치가 작동하는 동안 서버 코드가 항상 실행되도록 하려면 전원 관리 설정을 조정하거나 [이 시스템 활성 유지 Python 스크립트](https://github.com/jaqsparow/keep-system-active)와 같은 것을 실행해야 합니다.

온도 데이터를 확보한 후, 이 저장소에 있는 Jupyter Notebook을 사용하여 데이터를 시각화하고 GDD를 계산할 수 있습니다. Jupyter Notebook은 *셀*이라고 불리는 블록에 코드와 지침을 혼합하여 작성되며, 종종 Python 코드로 구성됩니다. 지침을 읽고 각 코드 블록을 하나씩 실행할 수 있으며, 코드를 편집할 수도 있습니다. 예를 들어, 이 노트북에서는 식물의 GDD를 계산하는 데 사용되는 기준 온도를 편집할 수 있습니다.

1. `gdd-calculation`이라는 폴더를 만드세요.

1. [gdd.ipynb](../../../../../2-farm/lessons/1-predict-plant-growth/code-notebook/gdd.ipynb) 파일을 다운로드하여 `gdd-calculation` 폴더에 복사하세요.

1. MQTT 서버에서 생성된 `temperature.csv` 파일을 복사하세요.

1. `gdd-calculation` 폴더에 새로운 Python 가상 환경을 만드세요.

1. Jupyter Notebook과 데이터를 관리하고 시각화하는 데 필요한 라이브러리를 설치하세요:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Jupyter에서 노트북을 실행하세요:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter가 시작되며 브라우저에서 노트북이 열립니다. 노트북의 지침을 따라 측정된 온도를 시각화하고 생장도일(GDD)을 계산하세요.

    ![Jupyter Notebook](../../../../../translated_images/ko/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## 평가 기준

| 기준 | 우수 | 적절 | 개선 필요 |
| ---- | ---- | ---- | -------- |
| 데이터 수집 | 최소 2일 이상의 완전한 데이터를 수집 | 최소 1일 이상의 완전한 데이터를 수집 | 일부 데이터만 수집 |
| GDD 계산 | 노트북을 성공적으로 실행하고 GDD를 계산 | 노트북을 성공적으로 실행 | 노트북 실행 불가 |

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있지만, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.