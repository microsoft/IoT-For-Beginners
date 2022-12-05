# Jupyter Notebook을 이용한 GDD 데이터 시각화

## 개요

이번 수업에서 IoT 센서를 사용해 GDD 데이터를 수집했습니다. 좋은 GDD 데이터를 얻기 위해서는 수 일간 데이터를 수집해야 합니다. 온도 데이터를 시각화 하고 GDD를 계산하는 것을 돕기 위해선 [Jupyter Notebooks](https://jupyter.org)과 같은 도구를 사용하여 데이터를 분석할 수 있습니다.

며칠 간 데이터를 수집하는 것으로 시작하십시오. 전원 관리 설정을 조정하거나 [시스템 활성 유지 Python 스크립트](https://github.com/jaqsparow/keep-system-active) 와 같은 것을 실행하여 IoT 장치가 실행되는 동안 서버 코드가 항상 실행되고 있는지 확인해야 합니다.

온도 데이터를 얻은 후에는 이 레포지토리에 있는 Jupyter Notebook을 이용하여 데이터를 시각화하고 GDD를 계산할 수 있습니다. Jupyter Notebook은 _셀_ 이라 불리는 블럭 안에 코드와 지침들이 섞여있습니다. 이는 주로 파이썬으로 작성됩니다. 지침을 읽고, 각각의 코드 블럭을 하나씩 실행할 수 있습니다. 또한 코드를 수정할 수도 있습니다. 예를 들자면 당신의 식물을 위해 GDD를 계산할 때 사용되는 기준 온도를 이 notebook에서 수정할 수 있습니다.

1. `gdd-calculation` 이름을 가진 폴더를 생성합니다.

1. [gdd.ipynb](../code-notebook/gdd.ipynb) 파일을 다운받고 `gdd-calculation`로 복사합니다.

1. MQTT 서버가 생성한 `temperature.csv` 파일을 복사합니다.

1. `gdd-calculation`폴더에 새로운 Python 환경을 생성합니다.

1. 데이터를 관리하고 표시하는 데 필요한 라이브러리와 함께 Jupyter Notebook을 위한 몇가지 pip 패키지들을 설치합니다:

   ```sh
   pip install --upgrade pip
   pip install pandas
   pip install matplotlib
   pip install jupyter
   ```

1. 이 notebook을 Jupyter에서 실행합니다:

   ```sh
   jupyter notebook gdd.ipynb
   ```

   Jupyter가 시작되고 브라우저에서 notebook을 열게 됩니다. notebook의 지시에 따라 측정된 온도를 시각화하고 유효 적산 온도(GDD)를 계산합니다.

   ![The jupyter notebook](../../../../images/gdd-jupyter-notebook.png)

## 평가 기준

| 기준        | 모범 답안                                   | 적절함                                | 개선이 필요함             |
| ----------- | ------------------------------------------- | ------------------------------------- | ------------------------- |
| 데이터 캡쳐 | 최소 완전한 이틀 이상의 데이터를 캡처함     | 최소 완전한 하루 이상의 데이터 캡처함 | 몇개의 데이터를 캡처함    |
| GDD 계산    | 성공적으로 notebook을 실행하고 GDD를 계산함 | 성공적으로 notebook을 실행함          | notebook을 실행할 수 없음 |
