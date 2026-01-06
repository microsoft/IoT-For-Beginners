<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-25T01:06:00+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "ko"
}
-->
# 저장 위치 데이터

![이 강의에 대한 스케치노트 개요](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.ko.jpg)

> 스케치노트 제공: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## 소개

지난 강의에서는 GPS 센서를 사용하여 위치 데이터를 캡처하는 방법을 배웠습니다. 이 데이터를 사용하여 음식이 실린 트럭의 위치와 이동 경로를 시각화하려면, 데이터를 클라우드의 IoT 서비스로 전송한 후 저장해야 합니다.

이번 강의에서는 IoT 데이터를 저장하는 다양한 방법을 배우고, 서버리스 코드를 사용하여 IoT 서비스에서 데이터를 저장하는 방법을 학습합니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [구조화된 데이터와 비구조화된 데이터](../../../../../3-transport/lessons/2-store-location-data)
* [GPS 데이터를 IoT Hub로 전송하기](../../../../../3-transport/lessons/2-store-location-data)
* [핫, 웜, 콜드 경로](../../../../../3-transport/lessons/2-store-location-data)
* [서버리스 코드를 사용하여 GPS 이벤트 처리하기](../../../../../3-transport/lessons/2-store-location-data)
* [Azure Storage 계정](../../../../../3-transport/lessons/2-store-location-data)
* [서버리스 코드를 스토리지에 연결하기](../../../../../3-transport/lessons/2-store-location-data)

## 구조화된 데이터와 비구조화된 데이터

컴퓨터 시스템은 데이터를 처리하며, 이 데이터는 다양한 형태와 크기로 제공됩니다. 데이터는 단일 숫자에서부터 대량의 텍스트, 비디오 및 이미지, IoT 데이터까지 다양합니다. 데이터는 일반적으로 두 가지 범주로 나눌 수 있습니다 - *구조화된 데이터*와 *비구조화된 데이터*.

* **구조화된 데이터**는 잘 정의된 고정된 구조를 가지며, 일반적으로 테이블 형태로 관계를 맺고 있는 데이터를 말합니다. 예를 들어, 사람의 이름, 생년월일, 주소와 같은 개인 정보가 이에 해당합니다.

* **비구조화된 데이터**는 고정된 구조가 없거나 자주 변경되는 데이터를 말합니다. 예를 들어, 문서나 스프레드시트와 같은 데이터가 이에 해당합니다.

✅ 연구해보기: 구조화된 데이터와 비구조화된 데이터의 다른 예를 생각해보세요.

> 💁 또한, 고정된 테이블 구조에 맞지 않지만 어느 정도 구조화된 데이터를 *반구조화된 데이터*라고 합니다.

IoT 데이터는 일반적으로 비구조화된 데이터로 간주됩니다.

상업용 농장의 차량에 IoT 장치를 추가한다고 상상해보세요. 차량 유형에 따라 다른 장치를 사용하고 싶을 수 있습니다. 예를 들어:

* 트랙터와 같은 농장 차량에는 GPS 데이터를 사용하여 올바른 필드에서 작업 중인지 확인합니다.
* 창고로 음식을 운송하는 트럭에는 GPS 데이터뿐만 아니라 속도와 가속도 데이터를 사용하여 운전자가 안전하게 운전하고 있는지 확인하며, 운전자 신원 및 시작/정지 데이터를 사용하여 근무 시간 관련 법률 준수를 확인합니다.
* 냉장 트럭에는 온도 데이터를 추가로 사용하여 음식이 너무 뜨겁거나 차가워져서 운송 중에 상하지 않도록 합니다.

이 데이터는 끊임없이 변경될 수 있습니다. 예를 들어, IoT 장치가 트럭 운전석에 있다면, 트레일러가 변경될 때마다 전송되는 데이터가 달라질 수 있습니다. 예를 들어, 냉장 트레일러가 사용될 때만 온도 데이터를 전송할 수 있습니다.

✅ 다른 IoT 데이터는 무엇이 캡처될 수 있을까요? 트럭이 운반할 수 있는 화물 종류와 유지보수 데이터를 생각해보세요.

이 데이터는 차량마다 다르지만, 모두 동일한 IoT 서비스로 전송되어 처리됩니다. IoT 서비스는 이러한 비구조화된 데이터를 처리하고, 검색하거나 분석할 수 있는 방식으로 저장해야 하며, 데이터의 다양한 구조를 처리할 수 있어야 합니다.

### SQL vs NoSQL 스토리지

데이터베이스는 데이터를 저장하고 쿼리할 수 있는 서비스를 제공합니다. 데이터베이스는 SQL과 NoSQL 두 가지 유형으로 나뉩니다.

#### SQL 데이터베이스

초기 데이터베이스는 관계형 데이터베이스 관리 시스템(RDBMS) 또는 관계형 데이터베이스로 알려졌습니다. 이러한 데이터베이스는 Structured Query Language(SQL)를 사용하여 데이터를 추가, 제거, 업데이트 또는 쿼리하는 방식으로 작동하며, SQL 데이터베이스로 알려져 있습니다. 이 데이터베이스는 스키마로 구성되며, 이는 스프레드시트와 유사한 잘 정의된 데이터 테이블 세트입니다. 각 테이블에는 여러 개의 이름이 지정된 열이 있습니다. 데이터를 삽입할 때, 테이블에 행을 추가하고 각 열에 값을 입력합니다. 이는 데이터를 매우 고정된 구조로 유지합니다. 열을 비워둘 수는 있지만, 새 열을 추가하려면 데이터베이스에서 이를 추가하고 기존 행에 값을 채워야 합니다. 이러한 데이터베이스는 관계형입니다. 즉, 한 테이블이 다른 테이블과 관계를 맺을 수 있습니다.

![User 테이블의 ID가 Purchases 테이블의 user ID 열과 관계를 맺고, Products 테이블의 ID가 Purchases 테이블의 product ID와 관계를 맺는 관계형 데이터베이스](../../../../../translated_images/sql-database.be160f12bfccefd3.ko.png)

예를 들어, 사용자의 개인 정보를 테이블에 저장한다고 가정하면, 각 사용자마다 고유한 내부 ID가 있으며, 이는 사용자의 이름과 주소를 포함하는 테이블의 행에 사용됩니다. 사용자의 구매 내역과 같은 다른 세부 정보를 다른 테이블에 저장하려면, 새 테이블에 사용자의 ID를 나타내는 열이 하나 있어야 합니다. 사용자를 조회할 때, 해당 ID를 사용하여 한 테이블에서 개인 정보를 가져오고, 다른 테이블에서 구매 내역을 가져올 수 있습니다.

SQL 데이터베이스는 구조화된 데이터를 저장하거나 데이터가 스키마와 일치하도록 보장해야 할 때 이상적입니다.

✅ SQL을 사용해본 적이 없다면, [Wikipedia의 SQL 페이지](https://wikipedia.org/wiki/SQL)를 읽어보세요.

Microsoft SQL Server, MySQL, PostgreSQL은 잘 알려진 SQL 데이터베이스입니다.

✅ 연구해보기: 이러한 SQL 데이터베이스와 그 기능에 대해 읽어보세요.

#### NoSQL 데이터베이스

NoSQL 데이터베이스는 SQL 데이터베이스의 고정된 구조를 가지지 않기 때문에 NoSQL이라고 불립니다. 문서 데이터베이스라고도 하며, 문서와 같은 비구조화된 데이터를 저장할 수 있습니다.

> 💁 이름과는 달리, 일부 NoSQL 데이터베이스는 SQL을 사용하여 데이터를 쿼리할 수 있습니다.

![NoSQL 데이터베이스의 폴더 안에 있는 문서들](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.ko.png)

NoSQL 데이터베이스는 데이터가 저장되는 방식을 제한하는 사전 정의된 스키마가 없으며, 일반적으로 JSON 문서를 사용하여 비구조화된 데이터를 삽입할 수 있습니다. 이러한 문서는 컴퓨터의 파일처럼 폴더에 정리될 수 있습니다. 각 문서는 다른 문서와 다른 필드를 가질 수 있습니다. 예를 들어, 농장 차량의 IoT 데이터를 저장한다고 가정하면, 일부 문서에는 가속도계와 속도 데이터 필드가 포함될 수 있고, 다른 문서에는 트레일러의 온도 데이터 필드가 포함될 수 있습니다. 내장된 저울로 운반 중인 농산물의 무게를 추적하는 새로운 트럭 유형을 추가한다고 가정하면, IoT 장치가 이 새로운 필드를 추가하고 데이터베이스를 변경하지 않고도 저장할 수 있습니다.

Azure CosmosDB, MongoDB, CouchDB는 잘 알려진 NoSQL 데이터베이스입니다.

✅ 연구해보기: 이러한 NoSQL 데이터베이스와 그 기능에 대해 읽어보세요.

이번 강의에서는 IoT 데이터를 저장하기 위해 NoSQL 스토리지를 사용할 것입니다.

## GPS 데이터를 IoT Hub로 전송하기

지난 강의에서는 IoT 장치에 연결된 GPS 센서에서 GPS 데이터를 캡처했습니다. 이 IoT 데이터를 클라우드에 저장하려면 IoT 서비스로 전송해야 합니다. 이번에도 이전 프로젝트에서 사용했던 Azure IoT Hub를 사용합니다.

![IoT 장치에서 IoT Hub로 GPS 텔레메트리 전송](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.ko.png)

### 작업 - GPS 데이터를 IoT Hub로 전송하기

1. 무료 계층을 사용하여 새 IoT Hub를 만듭니다.

    > ⚠️ 필요하면 [프로젝트 2, 강의 4의 IoT Hub 생성 지침](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud)을 참조하세요.

    새 리소스 그룹을 생성하세요. 새 리소스 그룹 이름은 `gps-sensor`로 지정하고, 새 IoT Hub 이름은 `gps-sensor`를 기반으로 고유한 이름을 지정하세요. 예를 들어, `gps-sensor-<your name>`.

    > 💁 이전 프로젝트에서 사용한 IoT Hub가 아직 있다면 재사용할 수 있습니다. 다른 서비스를 생성할 때 이 IoT Hub의 이름과 리소스 그룹을 기억하세요.

1. IoT Hub에 새 장치를 추가하세요. 이 장치의 이름은 `gps-sensor`로 지정하세요. 장치의 연결 문자열을 가져옵니다.

1. 장치 코드를 업데이트하여 이전 단계에서 가져온 장치 연결 문자열을 사용하여 새 IoT Hub로 GPS 데이터를 전송하세요.

    > ⚠️ 필요하면 [프로젝트 2, 강의 4의 장치를 IoT에 연결하는 지침](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service)을 참조하세요.

1. GPS 데이터를 JSON 형식으로 다음과 같이 전송하세요:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. 하루 메시지 할당량을 초과하지 않도록 GPS 데이터를 매분마다 전송하세요.

Wio Terminal을 사용하는 경우 필요한 모든 라이브러리를 추가하고 NTP 서버를 사용하여 시간을 설정하세요. 또한, 직렬 포트에서 모든 데이터를 읽은 후 GPS 위치를 전송하도록 기존 코드를 사용해야 합니다. JSON 문서를 생성하려면 다음 코드를 사용하세요:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

가상 IoT 장치를 사용하는 경우 가상 환경을 사용하여 필요한 모든 라이브러리를 설치하세요.

Raspberry Pi와 가상 IoT 장치 모두에서 지난 강의의 기존 코드를 사용하여 위도와 경도 값을 가져온 후, 다음 코드를 사용하여 올바른 JSON 형식으로 데이터를 전송하세요:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 이 코드는 [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi), [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device) 폴더에서 찾을 수 있습니다.

장치 코드를 실행하고 `az iot hub monitor-events` CLI 명령을 사용하여 IoT Hub로 메시지가 흐르는지 확인하세요.

## 핫, 웜, 콜드 경로

IoT 장치에서 클라우드로 흐르는 데이터는 항상 실시간으로 처리되는 것은 아닙니다. 일부 데이터는 실시간으로 처리해야 하고, 다른 데이터는 조금 후에 처리할 수 있으며, 또 다른 데이터는 훨씬 나중에 처리될 수 있습니다. 데이터를 처리하는 서비스로 흐르는 경로는 핫, 웜, 콜드 경로로 나뉩니다.

### 핫 경로

핫 경로는 실시간 또는 거의 실시간으로 처리해야 하는 데이터를 나타냅니다. 예를 들어, 차량이 창고에 접근하고 있거나 냉장 트럭의 온도가 너무 높다는 경고를 받는 데 핫 경로 데이터를 사용할 수 있습니다.

핫 경로 데이터를 사용하려면 클라우드 서비스에서 이벤트를 수신하자마자 코드가 이에 응답해야 합니다.

### 웜 경로

웜 경로는 데이터를 수신한 후 짧은 시간 내에 처리할 수 있는 데이터를 나타냅니다. 예를 들어, 일일 차량 주행 거리 보고서를 작성하는 데 웜 경로 데이터를 사용할 수 있습니다.

웜 경로 데이터는 클라우드 서비스에서 수신되자마자 빠르게 액세스할 수 있는 스토리지에 저장됩니다.

### 콜드 경로

콜드 경로는 장기적으로 데이터를 저장하고 필요할 때 처리할 수 있는 데이터를 나타냅니다. 예를 들어, 차량의 연간 주행 거리 보고서를 얻거나 연료 비용을 줄이기 위해 최적의 경로를 찾기 위한 분석을 실행하는 데 콜드 경로 데이터를 사용할 수 있습니다.

콜드 경로 데이터는 데이터 웨어하우스에 저장됩니다. 데이터 웨어하우스는 변경되지 않는 대량의 데이터를 저장하고 빠르고 쉽게 쿼리할 수 있도록 설계된 데이터베이스입니다. 일반적으로 클라우드 애플리케이션에서 정기적으로 실행되는 작업을 통해 웜 경로 스토리지에서 데이터 웨어하우스로 데이터를 이동합니다.

✅ 지금까지 이 강의에서 캡처한 데이터를 생각해보세요. 이 데이터는 핫, 웜, 콜드 경로 중 어디에 해당하나요?

## 서버리스 코드를 사용하여 GPS 이벤트 처리하기

데이터가 IoT Hub로 흐르기 시작하면, Event-Hub 호환 엔드포인트에 게시된 이벤트를 수신하기 위해 서버리스 코드를 작성할 수 있습니다. 이는 웜 경로에 해당하며, 이 데이터는 다음 강의에서 여정을 보고하는 데 사용됩니다.

![IoT 장치에서 IoT Hub로 GPS 텔레메트리 전송 후 Event Hub 트리거를 통해 Azure Functions로 전송](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.ko.png)

### 작업 - 서버리스 코드를 사용하여 GPS 이벤트 처리하기

1. Azure Functions CLI를 사용하여 Azure Functions 앱을 생성하세요. Python 런타임을 사용하고, `gps-trigger`라는 폴더에 생성하며, Functions App 프로젝트 이름도 `gps-trigger`로 지정하세요. 가상 환경을 생성하여 사용하세요.
> ⚠️ 필요하다면 [프로젝트 2, 레슨 5에서 Azure Functions 프로젝트를 생성하는 방법에 대한 지침](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application)을 참조할 수 있습니다.
1. IoT Hub의 Event Hub 호환 엔드포인트를 사용하는 IoT Hub 이벤트 트리거를 추가하세요.

    > ⚠️ 필요하다면 [프로젝트 2, 레슨 5의 IoT Hub 이벤트 트리거 생성 지침](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger)을 참조하세요.

1. `local.settings.json` 파일에 Event Hub 호환 엔드포인트 연결 문자열을 설정하고, 해당 항목의 키를 `function.json` 파일에서 사용하세요.

1. Azurite 앱을 로컬 스토리지 에뮬레이터로 사용하세요.

1. 함수 앱을 실행하여 GPS 장치에서 이벤트를 수신하는지 확인하세요. IoT 장치가 실행 중이며 GPS 데이터를 전송하고 있는지 확인하세요.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Azure Storage Accounts

![Azure Storage 로고](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.ko.png)

Azure Storage Accounts는 다양한 방식으로 데이터를 저장할 수 있는 범용 스토리지 서비스입니다. 데이터를 Blob, 큐, 테이블 또는 파일 형태로 저장할 수 있으며, 동시에 여러 방식으로 저장할 수 있습니다.

### Blob 스토리지

*Blob*이라는 단어는 이진 대형 객체를 의미하지만, 비구조적 데이터를 지칭하는 용어로 자리 잡았습니다. Blob 스토리지에는 IoT 데이터를 포함한 JSON 문서부터 이미지 및 동영상 파일까지 모든 데이터를 저장할 수 있습니다. Blob 스토리지는 관계형 데이터베이스의 테이블과 유사한 *컨테이너*라는 이름의 버킷에 데이터를 저장하는 개념을 가지고 있습니다. 이러한 컨테이너는 하나 이상의 폴더를 포함할 수 있으며, 각 폴더는 컴퓨터 하드 디스크에 파일이 저장되는 방식과 유사하게 다른 폴더를 포함할 수 있습니다.

이 레슨에서는 IoT 데이터를 저장하기 위해 Blob 스토리지를 사용합니다.

✅ 조사해보기: [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)에 대해 읽어보세요.

### 테이블 스토리지

테이블 스토리지는 반구조적 데이터를 저장할 수 있습니다. 테이블 스토리지는 실제로 NoSQL 데이터베이스로, 사전에 정의된 테이블 세트를 요구하지 않으며, 하나 이상의 테이블에 데이터를 저장하도록 설계되었습니다. 각 행을 정의하는 고유 키를 사용합니다.

✅ 조사해보기: [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)에 대해 읽어보세요.

### 큐 스토리지

큐 스토리지는 최대 64KB 크기의 메시지를 큐에 저장할 수 있습니다. 메시지를 큐의 뒤에 추가하고 앞에서 읽어올 수 있습니다. 큐는 저장 공간이 있는 한 메시지를 무기한 저장할 수 있으므로, 메시지를 장기적으로 저장한 후 필요할 때 읽어올 수 있습니다. 예를 들어, GPS 데이터를 처리하는 월간 작업을 실행하려면 매일 큐에 메시지를 추가하고, 한 달이 끝날 때 큐에서 모든 메시지를 처리할 수 있습니다.

✅ 조사해보기: [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)에 대해 읽어보세요.

### 파일 스토리지

파일 스토리지는 클라우드에 파일을 저장하며, 모든 앱이나 장치가 표준 프로토콜을 사용하여 연결할 수 있습니다. 파일 스토리지에 파일을 작성한 후 PC나 Mac에서 드라이브로 마운트할 수 있습니다.

✅ 조사해보기: [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)에 대해 읽어보세요.

## 서버리스 코드와 스토리지 연결

이제 함수 앱이 IoT Hub에서 받은 메시지를 Blob 스토리지에 저장하도록 연결해야 합니다. 이를 수행하는 방법은 두 가지가 있습니다:

* 함수 코드 내부에서 Blob 스토리지 Python SDK를 사용하여 Blob으로 데이터를 저장
* 출력 함수 바인딩을 사용하여 함수의 반환 값을 Blob 스토리지에 바인딩하고 Blob이 자동으로 저장되도록 설정

이 레슨에서는 Python SDK를 사용하여 Blob 스토리지를 다루는 방법을 배웁니다.

![IoT 장치에서 GPS 텔레메트리를 IoT Hub로 전송한 후, 이벤트 허브 트리거를 통해 Azure Functions로 전달하고 Blob 스토리지에 저장](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.ko.png)

데이터는 다음 형식의 JSON Blob으로 저장됩니다:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### 작업 - 서버리스 코드를 스토리지에 연결

1. Azure Storage 계정을 생성하세요. 이름은 `gps<your name>`과 같이 지정하세요.

    > ⚠️ 필요하다면 [프로젝트 2, 레슨 5의 스토리지 계정 생성 지침](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)을 참조하세요.

    이전 프로젝트에서 생성한 스토리지 계정이 있다면 이를 재사용할 수 있습니다.

    > 💁 이 스토리지 계정을 사용하여 이 레슨 후반부에서 Azure Functions 앱을 배포할 수 있습니다.

1. 다음 명령어를 실행하여 스토리지 계정의 연결 문자열을 가져오세요:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    `<storage_name>`을 이전 단계에서 생성한 스토리지 계정 이름으로 바꾸세요.

1. `local.settings.json` 파일에 스토리지 계정 연결 문자열에 대한 새 항목을 추가하고, 이름을 `STORAGE_CONNECTION_STRING`으로 지정하세요.

1. Azure 스토리지 Pip 패키지를 설치하기 위해 `requirements.txt` 파일에 다음을 추가하세요:

    ```sh
    azure-storage-blob
    ```

    이 파일에서 가상 환경에 패키지를 설치하세요.

    > 오류가 발생하면, 다음 명령어를 사용하여 가상 환경에서 Pip 버전을 최신 버전으로 업그레이드한 후 다시 시도하세요:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `iot-hub-trigger`의 `__init__.py` 파일에 다음 import 문을 추가하세요:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    `json` 시스템 모듈은 JSON을 읽고 쓰는 데 사용되며, `os` 시스템 모듈은 연결 문자열을 읽는 데 사용됩니다. `uuid` 시스템 모듈은 GPS 읽기용 고유 ID를 생성하는 데 사용됩니다.

    `azure.storage.blob` 패키지는 Blob 스토리지를 다루기 위한 Python SDK를 포함합니다.

1. `main` 메서드 이전에 다음 헬퍼 함수를 추가하세요:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    Python Blob SDK에는 컨테이너가 없을 경우 생성하는 헬퍼 메서드가 없습니다. 이 코드는 `local.settings.json` 파일(또는 클라우드에 배포된 후에는 Application Settings)에서 연결 문자열을 로드한 다음, 이를 사용하여 Blob 스토리지 계정을 다루는 `BlobServiceClient` 클래스를 생성합니다. 그런 다음 제공된 이름의 컨테이너를 찾기 위해 Blob 스토리지 계정의 모든 컨테이너를 반복합니다. 컨테이너를 찾으면 Blob을 생성할 수 있는 `ContainerClient` 클래스를 반환합니다. 컨테이너를 찾지 못하면 새 컨테이너를 생성하고 해당 클라이언트를 반환합니다.

    새 컨테이너가 생성될 때, 컨테이너의 Blob을 쿼리할 수 있는 공개 액세스 권한이 부여됩니다. 이는 다음 레슨에서 GPS 데이터를 지도에 시각화하는 데 사용됩니다.

1. 토양 수분 코드와 달리, 이 코드는 모든 이벤트를 저장해야 하므로, `main` 함수의 `for event in events:` 루프 내부에서 `logging` 문 아래에 다음 코드를 추가하세요:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    이 코드는 이벤트 메타데이터에서 장치 ID를 가져온 다음 이를 사용하여 Blob 이름을 생성합니다. Blob은 폴더에 저장될 수 있으며, 장치 ID는 폴더 이름으로 사용됩니다. 따라서 각 장치는 모든 GPS 이벤트를 하나의 폴더에 저장합니다. Blob 이름은 이 폴더와 문서 이름으로 구성되며, 슬래시(`/`)로 구분됩니다. 문서 이름은 Python `uuid` 모듈을 사용하여 생성된 고유 ID와 `json` 파일 형식으로 구성됩니다.

    예를 들어, `gps-sensor` 장치 ID의 경우 Blob 이름은 `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`과 같을 수 있습니다.

1. 아래 코드를 추가하세요:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    이 코드는 `get_or_create_container` 헬퍼 클래스를 사용하여 컨테이너 클라이언트를 가져온 다음, Blob 이름을 사용하여 Blob 클라이언트 객체를 가져옵니다. 이러한 Blob 클라이언트는 기존 Blob을 참조하거나, 이 경우처럼 새 Blob을 참조할 수 있습니다.

1. 다음 코드를 추가하세요:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    이 코드는 Blob 스토리지에 작성될 Blob 본문을 생성합니다. 이는 장치 ID, IoT Hub에 텔레메트리가 전송된 시간, 텔레메트리의 GPS 좌표를 포함하는 JSON 문서입니다.

    > 💁 메시지가 전송된 시간을 얻기 위해 현재 시간이 아닌 메시지의 큐에 저장된 시간을 사용하는 것이 중요합니다. Functions 앱이 실행되지 않을 경우 메시지가 허브에 대기 중일 수 있기 때문입니다.

1. 아래 코드를 추가하세요:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    이 코드는 Blob이 작성될 세부 정보를 로깅한 다음, Blob 본문을 새 Blob의 내용으로 업로드합니다.

1. 함수 앱을 실행하세요. 출력에서 모든 GPS 이벤트에 대해 Blob이 작성되는 것을 확인할 수 있습니다:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 IoT Hub 이벤트 모니터를 동시에 실행하지 않도록 하세요.

> 💁 이 코드는 [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions) 폴더에서 확인할 수 있습니다.

### 작업 - 업로드된 Blob 확인

1. 생성된 Blob을 보려면 [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn)라는 무료 도구를 사용하거나 CLI를 사용할 수 있습니다.

    1. CLI를 사용하려면 먼저 계정 키가 필요합니다. 다음 명령어를 실행하여 키를 가져오세요:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        `<storage_name>`을 스토리지 계정 이름으로 바꾸세요.

        `key1` 값을 복사하세요.

    1. 다음 명령어를 실행하여 컨테이너의 Blob을 나열하세요:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        `<storage_name>`을 스토리지 계정 이름으로, `<key1>`을 이전 단계에서 복사한 `key1` 값으로 바꾸세요.

        이 명령어는 컨테이너의 모든 Blob을 나열합니다:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. 다음 명령어를 사용하여 Blob 중 하나를 다운로드하세요:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        `<storage_name>`을 스토리지 계정 이름으로, `<key1>`을 이전 단계에서 복사한 `key1` 값으로 바꾸세요.

        `<blob_name>`을 출력의 `Name` 열에서 전체 이름(폴더 이름 포함)으로 바꾸세요. `<file_name>`을 Blob을 저장할 로컬 파일 이름으로 바꾸세요.

    다운로드한 후, JSON 파일을 VS Code에서 열어 Blob에 GPS 위치 세부 정보가 포함된 것을 확인할 수 있습니다:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### 작업 - Functions 앱을 클라우드에 배포

이제 함수 앱이 작동하므로 클라우드에 배포할 수 있습니다.

1. 이전에 생성한 스토리지 계정을 사용하여 새 Azure Functions 앱을 생성하세요. 이름은 `gps-sensor-` 뒤에 고유 식별자를 추가하여 지정하세요(예: 임의의 단어 또는 이름).

    > ⚠️ 필요하다면 [프로젝트 2, 레슨 5의 Functions 앱 생성 지침](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources)을 참조하세요.

1. `IOT_HUB_CONNECTION_STRING` 및 `STORAGE_CONNECTION_STRING` 값을 Application Settings에 업로드하세요.

    > ⚠️ 필요하다면 [프로젝트 2, 레슨 5의 Application Settings 업로드 지침](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings)을 참조하세요.

1. 로컬 Functions 앱을 클라우드에 배포하세요.
> ⚠️ 필요하다면 [프로젝트 2, 레슨 5에서 Functions 앱 배포에 대한 지침](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud)을 참조하세요.
---

## 🚀 도전 과제

GPS 데이터는 완벽히 정확하지 않으며, 특히 터널이나 높은 건물이 많은 지역에서는 위치가 몇 미터 이상 벗어날 수 있습니다.

위성 내비게이션이 이를 어떻게 극복할 수 있을지 생각해보세요. 내비게이션이 더 나은 위치 예측을 하기 위해 사용할 수 있는 데이터는 무엇일까요?

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## 복습 및 자기 학습

* [위키백과의 데이터 모델 페이지](https://wikipedia.org/wiki/Data_model)에서 구조화된 데이터에 대해 읽어보세요.
* [위키백과의 반구조화 데이터 페이지](https://wikipedia.org/wiki/Semi-structured_data)에서 반구조화된 데이터에 대해 읽어보세요.
* [위키백과의 비구조화 데이터 페이지](https://wikipedia.org/wiki/Unstructured_data)에서 비구조화된 데이터에 대해 읽어보세요.
* [Azure Storage 문서](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)에서 Azure Storage와 다양한 저장소 유형에 대해 더 알아보세요.

## 과제

[함수 바인딩 조사하기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.