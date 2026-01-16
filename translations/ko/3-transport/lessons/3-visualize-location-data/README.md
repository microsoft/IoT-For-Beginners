<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-25T00:58:46+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "ko"
}
-->
# 위치 데이터 시각화

![이 강의의 스케치노트 개요](../../../../../translated_images/ko/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> 스케치노트: [Nitya Narasimhan](https://github.com/nitya). 이미지를 클릭하면 더 큰 버전을 볼 수 있습니다.

이 비디오는 이 강의에서 다룰 Azure Maps와 IoT 서비스에 대한 개요를 제공합니다.

[![Azure Maps - Microsoft Azure의 엔터프라이즈 위치 플랫폼](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 위 이미지를 클릭하여 비디오를 시청하세요.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## 소개

지난 강의에서는 센서에서 GPS 데이터를 가져와 서버리스 코드를 사용해 클라우드의 스토리지 컨테이너에 저장하는 방법을 배웠습니다. 이번에는 이러한 데이터를 Azure 지도에 시각화하는 방법을 알아보겠습니다. 웹 페이지에 지도를 생성하고, GeoJSON 데이터 형식에 대해 배우며, 이를 사용해 캡처된 GPS 포인트를 지도에 표시하는 방법을 학습합니다.

이번 강의에서 다룰 내용은 다음과 같습니다:

* [데이터 시각화란 무엇인가](../../../../../3-transport/lessons/3-visualize-location-data)
* [지도 서비스](../../../../../3-transport/lessons/3-visualize-location-data)
* [Azure Maps 리소스 생성](../../../../../3-transport/lessons/3-visualize-location-data)
* [웹 페이지에 지도 표시](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON 형식](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON을 사용해 지도에 GPS 데이터 표시](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 이번 강의에서는 약간의 HTML과 JavaScript를 사용합니다. HTML과 JavaScript를 사용한 웹 개발에 대해 더 배우고 싶다면 [초보자를 위한 웹 개발](https://github.com/microsoft/Web-Dev-For-Beginners)을 확인하세요.

## 데이터 시각화란 무엇인가

데이터 시각화는 말 그대로 데이터를 인간이 더 쉽게 이해할 수 있도록 시각적으로 표현하는 것입니다. 일반적으로 차트나 그래프와 연관되지만, 데이터를 그림으로 표현해 인간이 데이터를 더 잘 이해하고 결정을 내릴 수 있도록 돕는 모든 방법을 포함합니다.

간단한 예를 들어보겠습니다. 농장 프로젝트에서 토양 수분 데이터를 캡처한 적이 있습니다. 2021년 6월 1일 하루 동안 매시간 캡처된 토양 수분 데이터는 다음과 같을 수 있습니다:

| 날짜             | 측정값 |
| ---------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

이 데이터를 이해하는 것은 쉽지 않습니다. 숫자만 나열된 벽처럼 보이기 때문입니다. 이 데이터를 시각화하는 첫 번째 단계로, 선 그래프에 플롯할 수 있습니다:

![위 데이터의 선 그래프](../../../../../translated_images/ko/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

여기에 자동 급수 시스템이 토양 수분 값 450에서 작동한 시점을 나타내는 선을 추가하면 더 명확해집니다:

![토양 수분 선 그래프와 450에서의 선](../../../../../translated_images/ko/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

이 그래프는 토양 수분 수준뿐만 아니라 급수 시스템이 작동한 지점을 빠르게 보여줍니다.

차트는 데이터를 시각화하는 유일한 도구가 아닙니다. 날씨를 추적하는 IoT 장치는 웹 앱이나 모바일 앱을 통해 구름, 비구름 등의 기호를 사용해 날씨 조건을 시각화할 수 있습니다. 데이터를 시각화하는 방법은 매우 다양하며, 진지한 것부터 재미있는 것까지 있습니다.

✅ 데이터를 시각화한 방법을 생각해 보세요. 어떤 방법이 가장 명확했고, 가장 빠르게 결정을 내릴 수 있도록 도와줬나요?

가장 좋은 시각화는 인간이 빠르게 결정을 내릴 수 있도록 돕는 것입니다. 예를 들어, 산업 기계의 다양한 데이터를 보여주는 게이지 벽은 처리하기 어렵지만, 문제가 발생했을 때 깜빡이는 빨간 불은 인간이 결정을 내릴 수 있도록 도와줍니다. 때로는 가장 좋은 시각화가 깜빡이는 불빛일 수도 있습니다!

GPS 데이터를 다룰 때 가장 명확한 시각화 방법은 데이터를 지도에 표시하는 것입니다. 예를 들어, 배송 트럭을 보여주는 지도는 처리 공장의 직원들이 트럭이 언제 도착할지 알 수 있도록 도와줍니다. 이 지도에 트럭의 현재 위치뿐만 아니라 트럭의 내용물에 대한 정보도 표시된다면, 공장 직원들은 냉장 트럭이 가까이 있음을 보고 냉장고 공간을 준비할 수 있습니다.

## 지도 서비스

지도를 다루는 것은 흥미로운 작업이며, Bing Maps, Leaflet, Open Street Maps, Google Maps 등 다양한 선택지가 있습니다. 이번 강의에서는 [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn)를 사용해 GPS 데이터를 표시하는 방법을 배웁니다.

![Azure Maps 로고](../../../../../translated_images/ko/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps는 "최신 지도 데이터를 사용해 웹 및 모바일 애플리케이션에 지리적 컨텍스트를 제공하는 지리공간 서비스 및 SDK 모음"입니다. 개발자는 추천 경로 제공, 교통 사고 정보, 실내 내비게이션, 검색 기능, 고도 정보, 날씨 서비스 등 다양한 기능을 제공하는 아름답고 상호작용적인 지도를 만들 수 있는 도구를 제공합니다.

✅ [지도 코드 샘플](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)을 실험해 보세요.

지도는 빈 캔버스, 타일, 위성 이미지, 도로가 겹쳐진 위성 이미지, 다양한 유형의 회색조 지도, 고도를 보여주는 음영 지도, 야간 지도, 고대비 지도 등으로 표시할 수 있습니다. [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn)와 통합해 실시간 업데이트를 지도에 표시할 수도 있습니다. 핀치, 드래그, 클릭과 같은 이벤트에 반응하도록 지도의 동작을 제어할 수 있으며, 버블, 선, 다각형, 히트맵 등 다양한 레이어를 추가해 지도의 모양을 제어할 수 있습니다. 어떤 스타일의 지도를 구현할지는 선택한 SDK에 따라 달라집니다.

Azure Maps API는 [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [웹 SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), 또는 모바일 앱을 개발하는 경우 [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android)를 통해 액세스할 수 있습니다.

이번 강의에서는 웹 SDK를 사용해 지도를 그리고 센서의 GPS 위치 경로를 표시합니다.

## Azure Maps 리소스 생성

첫 번째 단계는 Azure Maps 계정을 생성하는 것입니다.

### 작업 - Azure Maps 리소스 생성

1. 터미널 또는 명령 프롬프트에서 다음 명령을 실행해 `gps-sensor` 리소스 그룹에 Azure Maps 리소스를 생성하세요:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    이 명령은 `gps-sensor`라는 Azure Maps 리소스를 생성합니다. 사용 중인 계층은 `S1`이며, 다양한 기능을 포함한 유료 계층이지만 무료로 사용할 수 있는 호출량이 넉넉합니다.

    > 💁 Azure Maps 사용 비용을 확인하려면 [Azure Maps 가격 페이지](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn)를 참조하세요.

1. 지도 리소스의 API 키가 필요합니다. 다음 명령을 사용해 이 키를 가져오세요:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    `PrimaryKey` 값을 복사해 두세요.

## 웹 페이지에 지도 표시

이제 다음 단계로, 웹 페이지에 지도를 표시합니다. 이번에는 하나의 `html` 파일만 사용해 간단한 웹 앱을 만듭니다. 하지만 실제 프로덕션 환경이나 팀 환경에서는 웹 앱이 더 많은 구성 요소를 포함할 가능성이 높습니다.

### 작업 - 웹 페이지에 지도 표시

1. 로컬 컴퓨터의 폴더에 `index.html`이라는 파일을 생성하고, 지도를 표시할 HTML 마크업을 추가하세요:

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    지도는 `myMap` `div`에 로드됩니다. 몇 가지 스타일을 추가해 페이지의 너비와 높이를 차지하도록 설정합니다.

    > 🎓 `div`는 웹 페이지의 섹션으로, 이름을 지정하고 스타일을 적용할 수 있습니다.

1. `<head>` 태그 아래에 지도 표시를 제어하는 외부 스타일 시트와 동작을 관리하는 웹 SDK의 외부 스크립트를 추가하세요:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    이 스타일 시트는 지도의 모양을 설정하며, 스크립트 파일은 지도를 로드하는 코드를 포함합니다. 이 코드를 추가하는 것은 C++ 헤더 파일을 포함하거나 Python 모듈을 가져오는 것과 유사합니다.

1. 그 스크립트 아래에 지도를 실행하는 스크립트 블록을 추가하세요.

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    `<subscription_key>`를 Azure Maps 계정의 API 키로 교체하세요.

    `index.html` 페이지를 웹 브라우저에서 열면 시애틀 지역에 초점을 맞춘 지도가 표시됩니다.

    ![미국 워싱턴주 시애틀을 보여주는 지도](../../../../../translated_images/ko/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ 확대 및 중심 좌표를 변경해 지도 표시를 실험해 보세요. 데이터의 위도와 경도에 해당하는 다른 좌표를 추가해 지도의 중심을 변경할 수 있습니다.

> 💁 로컬에서 웹 앱을 더 잘 작업하려면 [http-server](https://www.npmjs.com/package/http-server)를 설치하세요. 이 도구를 사용하려면 [node.js](https://nodejs.org/)와 [npm](https://www.npmjs.com/)이 설치되어 있어야 합니다. 도구가 설치되면 `index.html` 파일이 있는 위치로 이동해 `http-server`를 입력하세요. 웹 앱은 로컬 웹 서버 [http://127.0.0.1:8080/](http://127.0.0.1:8080/)에서 열립니다.

## GeoJSON 형식

이제 웹 앱에 지도가 표시되었으니, 스토리지 계정에서 GPS 데이터를 추출해 지도 위에 마커 레이어로 표시해야 합니다. 그 전에 Azure Maps에서 요구하는 [GeoJSON](https://wikipedia.org/wiki/GeoJSON) 형식을 살펴보겠습니다.

[GeoJSON](https://geojson.org/)은 지리적 데이터를 처리하도록 설계된 특별한 형식을 가진 오픈 표준 JSON 사양입니다. [geojson.io](https://geojson.io)를 사용해 샘플 데이터를 테스트하며 GeoJSON에 대해 배울 수 있으며, GeoJSON 파일을 디버깅하는 데도 유용한 도구입니다.

샘플 GeoJSON 데이터는 다음과 같습니다:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

특히 주목할 점은 데이터가 `FeatureCollection` 내의 `Feature`로 중첩되어 있다는 점입니다. 이 객체 안에는 `geometry`가 있으며, `coordinates`는 위도와 경도를 나타냅니다.

✅ GeoJSON을 작성할 때 객체의 `위도`와 `경도` 순서에 주의하세요. 그렇지 않으면 포인트가 올바른 위치에 나타나지 않을 수 있습니다! GeoJSON은 포인트에 대해 `lat,lon`이 아닌 `lon,lat` 순서를 기대합니다.

`Geometry`는 단일 포인트나 다각형과 같은 다양한 유형을 가질 수 있습니다. 이 예제에서는 경도와 위도 두 좌표가 지정된 포인트입니다.
✅ Azure Maps는 표준 GeoJSON을 지원하며, 원을 그리거나 기타 기하학적 도형을 그릴 수 있는 [확장 기능](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn)을 제공합니다.

## GeoJSON을 사용하여 지도에 GPS 데이터 표시하기

이제 이전 강의에서 구축한 스토리지에서 데이터를 가져올 준비가 되었습니다. 참고로, 데이터는 Blob 스토리지에 여러 파일로 저장되어 있으므로, 파일을 가져와 파싱하여 Azure Maps에서 사용할 수 있도록 해야 합니다.

### 작업 - 웹 페이지에서 스토리지에 접근하도록 설정하기

스토리지에서 데이터를 가져오기 위해 호출을 하면 브라우저 콘솔에서 오류가 발생하는 것을 보고 놀랄 수 있습니다. 이는 외부 웹 앱이 데이터를 읽을 수 있도록 이 스토리지에 대해 [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) 권한을 설정해야 하기 때문입니다.

> 🎓 CORS는 "교차 출처 리소스 공유(Cross-Origin Resource Sharing)"를 의미하며, 보안상의 이유로 Azure에서 명시적으로 설정해야 하는 경우가 많습니다. 이를 통해 예상치 못한 사이트가 데이터에 접근하지 못하도록 방지합니다.

1. 다음 명령어를 실행하여 CORS를 활성화하세요:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    `<storage_name>`을 스토리지 계정 이름으로, `<key1>`을 스토리지 계정의 계정 키로 바꾸세요.

    이 명령어는 모든 웹사이트(와일드카드 `*`는 모든 것을 의미)가 스토리지 계정에서 데이터를 가져오는 *GET* 요청을 할 수 있도록 허용합니다. `--services b`는 이 설정을 Blob에만 적용하도록 지정합니다.

### 작업 - 스토리지에서 GPS 데이터 로드하기

1. `init` 함수의 전체 내용을 다음 코드로 교체하세요:

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    `<storage_name>`을 스토리지 계정 이름으로, `<subscription_key>`를 Azure Maps 계정의 API 키로 바꾸세요.

    여기서 여러 가지 작업이 이루어집니다. 먼저, 이 코드는 스토리지 계정 이름을 사용하여 URL 엔드포인트를 생성하고, 이를 통해 Blob 컨테이너에서 GPS 데이터를 가져옵니다. 이 URL은 `gps-data`에서 데이터를 가져오며, 리소스 유형이 컨테이너(`restype=container`)임을 나타내고, 모든 Blob에 대한 정보를 나열합니다. 이 목록은 Blob 자체를 반환하지 않고, 각 Blob 데이터를 로드할 수 있는 URL을 반환합니다.

    > 💁 이 URL을 브라우저에 입력하면 컨테이너에 있는 모든 Blob의 세부 정보를 확인할 수 있습니다. 각 항목에는 `Url` 속성이 있으며, 이를 브라우저에서 열어 Blob의 내용을 확인할 수도 있습니다.

    이 코드는 이후 각 Blob을 로드하고, `loadJSON` 함수를 호출합니다. 이 함수는 다음 단계에서 생성됩니다. 이후 지도 컨트롤을 생성하고, `ready` 이벤트에 코드를 추가합니다. 이 이벤트는 지도가 웹 페이지에 표시될 때 호출됩니다.

    `ready` 이벤트는 Azure Maps 데이터 소스를 생성합니다. 이 데이터 소스는 나중에 GeoJSON 데이터를 포함하게 될 컨테이너입니다. 이 데이터 소스를 사용하여 버블 레이어(GeoJSON의 각 지점 중심에 원을 표시하는 레이어)를 생성합니다.

1. `init` 함수 아래에 `loadJSON` 함수를 스크립트 블록에 추가하세요:

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    이 함수는 fetch 루틴에 의해 호출되어 JSON 데이터를 파싱하고, 이를 경도와 위도 좌표로 변환하여 GeoJSON으로 읽을 수 있도록 합니다. 파싱된 데이터는 GeoJSON `Feature`의 일부로 설정됩니다. 지도가 초기화되면, 데이터가 표시되는 경로를 따라 작은 원이 나타납니다.

1. HTML 페이지를 브라우저에서 로드하세요. 지도가 로드된 후, 스토리지에서 모든 GPS 데이터를 가져와 지도에 표시합니다.

    ![시애틀 근처 Saint Edward State Park의 지도. 공원이 둘러싸인 경로를 따라 원이 표시됨](../../../../../translated_images/ko/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 이 코드는 [코드](../../../../../3-transport/lessons/3-visualize-location-data/code) 폴더에서 확인할 수 있습니다.

---

## 🚀 도전 과제

정적인 데이터를 지도에 마커로 표시하는 것도 좋지만, 이 웹 앱을 개선하여 애니메이션을 추가하고, 타임스탬프가 있는 JSON 파일을 사용해 마커의 경로를 시간에 따라 표시할 수 있나요? 지도에서 애니메이션을 사용하는 [샘플](https://azuremapscodesamples.azurewebsites.net/)을 참고하세요.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## 복습 및 자기 학습

Azure Maps는 IoT 기기와 작업할 때 특히 유용합니다.

* [Microsoft Docs의 Azure Maps 문서](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn)에서 사용 사례를 조사해 보세요.
* [Microsoft Learn의 Azure Maps로 첫 번째 경로 찾기 앱 만들기 자습형 학습 모듈](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn)을 통해 지도 제작 및 웨이포인트에 대한 지식을 심화하세요.

## 과제

[앱 배포하기](assignment.md)

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보에 대해서는 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생할 수 있는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.