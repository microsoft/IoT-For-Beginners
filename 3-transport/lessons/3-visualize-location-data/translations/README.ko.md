# 위치 데이터 시각화

![A sketchnote overview of this lesson](../../../../sketchnotes/lesson-13.jpg)

> [Nitya Narasimhan](https://github.com/nitya)의 스케치 노트. 더 큰 버전을 보려면 이미지를 클릭하십시오.

이 비디오는 이번 단원에서 다룰 Azure Maps의 IoT에 대한 개요를 제공합니다.

[![Azure Maps - The Microsoft Azure Enterprise Location Platform](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 위 이미지를 클릭하면 영상을 볼 수 있습니다.

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## 개요

지난 수업에서는 서버리스 코드를 사용하여 스토리지 컨테이너의 클라우드에 저장하기 위해 센서에서 GPS 데이터를 가져오는 방법을 배웠습니다. 이제 Azure 맵에서 해당 지점을 시각화하는 방법을 알아봅니다. 웹 페이지에서 지도를 만드는 방법, GeoJSON 데이터 형식 및 이를 사용하여 지도에 캡처된 모든 GPS 지점을 표시하는 방법을 배우게 됩니다.

이 강의에서는 다음을 다룰 것입니다:

- [데이터 시각화란](#what-is-data-visualization)
- [지도 서비스](#map-services)
- [Azure Maps 리소스 만들기](#create-an-azure-maps-resource)
- [웹 페이지에 지도 표시](#show-a-map-on-a-web-page)
- [GeoJSON 형식](#the-geojson-format)
- [GeoJSON을 사용하여 지도에 GPS 데이터 표시하기](#plot-gps-data-on-a-map-using-geojson)

> 💁 This lesson will involve a small amount of HTML and JavaScript. If you would like to learn more about web development using HTML and JavaScript, check out [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners).

## 데이터 시각화란

데이터 시각화는 이름에서 알 수 있듯이 사람이 이해하기 쉽게 데이터를 시각화하는 것입니다. 일반적으로 차트 및 그래프와 연관되지만 사람이 데이터를 더 잘 이해할 수 있을 뿐만 아니라 의사 결정을 내리는 데 도움이 되도록 데이터를 그림으로 나타내는 모든 방법을 말합니다.

간단한 예를 들자면, 지난 농장 프로젝트에서 토양 수분 설정을 캡처했습니다. 2021년 6월 1일에 매시간 수집된 토양 수분 데이터 테이블은 다음과 같을 수 있습니다:

| Date             | Reading |
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

인간으로서, 데이터를 이해하는 것은 어려울 수 있습니다. 이는 아무런 의미가 없는 숫자입니다. 이 데이터를 시각화하는 첫 번째 단계는 꺾은선형 차트에 그리는 것입니다:

![A line chart of the above data](../../../../images/chart-soil-moisture.png)

이는 언제 자동 급수 시스템이 토양 수분 판독값 450을 읽어 켜지는지를 나타내는 선을 추가하여 더욱 발전시킬 수 있습니다.

![A line chart of soil moisture with a line at 450](../../../../images/chart-soil-moisture-relay.png)

이 차트는 토양 수분 수준 뿐만 아니라, 급수 시스템이 켜진 지점을 매우 빠르게 보여줍니다.

차트는 데이터를 시작화하는 유일한 도구가 아닙니다. 날씨를 추적하는 IoT 장치에는 흐린 날의 구름 기호, 비 오는 날의 비구름 등과 같은 기호를 사용하여 날씨 상태를 시각화하는 웹 앱, 또는 모바일 앱이 있을 수 있습니다. 데이터를 시각화하는 방법은 무수히 많고, 진지하고 재미있는 경우도 많습니다.

✅ 시각화된 데이터를 보는 방법에 대해 생각해 보십시오. 어떤 방법이 가장 명확했고 가장 빠르게 결정을 내릴 수 있었습니까?

최고의 시각화를 통해 사람과 사람이 빠르게 의사 결정을 내릴 수 있습니다. 예를 들어 산업용 기계의 모든 판독값을 표시하는 게이지를 갖는 것은 처리하기 어렵지만 무언가 잘못되었을 때 빨간색 표시등이 깜박이면 사람이 결정을 내릴 수 있습니다. 때때로 최고의 시각화는 번쩍이는 불빛입니다!

GPS 데이터로 작업할 때 가장 명확한 시각화는 지도에 데이터를 표시하는 것입니다. 예를 들어 배달 트럭을 표시하는 지도는 가공 공장의 작업자가 트럭이 도착하는 시기를 확인하는 데 도움이 될 수 있습니다. 이 지도가 현재 위치에 있는 트럭 사진보다 더 많은 것을 보여주고 트럭의 내용물에 대한 아이디어를 제공한다면 공장의 작업자는 그에 따라 계획을 세울 수 있습니다. 만약 근처에 냉장 트럭이 보이면 냉장고에 공간을 마련해야 한다는 것을 압니다.

## 지도 서비스

지도로 작업하는 것은 흥미롭습니다. Bing Maps, Leaflet, Open Street Maps 및 Google Maps와 같이 선택할 수 있는 것이 많습니다. 이 단원에서는 [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) 과 GPS 데이터를 표시하는 방법에 대해 알아봅니다.

![The Azure Maps logo](../../../../images/azure-maps-logo.png)

Azure Maps는 "새로운 매핑 데이터를 사용하여 웹 및 모바일 애플리케이션에 지리학적 환경을 제공하는 지리 공간 서비스 및 SDK 모음"입니다. 개발자에게는 권장 교통 경로 제공, 교통 사고에 대한 정보 제공, 실내 내비게이션, 검색 기능, 고도 정보, 날씨 서비스 등을 수행할 수 있는 아름다운 대화형 지도를 만드는 도구가 제공됩니다.

✅ [매핑 코드 샘플](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps) 로 실험하기

지도의 빈 캔버스, 타일, 위성 이미지, 도로가 중첩된 위성 이미지, 다양한 유형의 회색조 지도, 고도를 표시하는 음영 부조가 있는 지도, 야경 지도, 고대비 지도로 지도를 표시할 수 있습니다. [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn)와 통합하여 지도에서 실시간 업데이트를 받을 수 있습니다. 핀치, 드래그와 클릭과 같은 이벤트에 지도가 반응할 수 있도록 다양한 제어를 활성화하여 지도의 동작과 모양을 제어할 수 있습니다. 지도의 모양을 제어하기 위해 버블, 라인, 다각형, 히트 맵 등을 포함하는 레이어를 추가할 수 있습니다. 구현하는 지도의 스타일은 선택한 SDK에 따라 다릅니다.

[REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), 모바일 어플리케이션을 만드는 경우, [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android)를 활용하여 Azure Maps API에 접근할 수 있습니다.

이 수업에서는 웹 SDK를 사용하여 지도와 센서의 GPS 위치 경로를 표시합니다.

## Azure Maps 리소스 만들기

첫 번째 단계는 Azure Maps 계정을 만드는 것입니다.

### 작업 - Azure Maps 리소스 만들기

1. 터미널 또는 명령 프롬프트에서 다음 명령을 실행하여 `gps-sensor` 리소스 그룹에 Azure Maps 리소스를 만듭니다:

   ```sh
   az maps account create --name gps-sensor \
                          --resource-group gps-sensor \
                          --accept-tos \
                          --sku S1
   ```

   이렇게 하면 Azure Maps의 `gps-sensor`라는 리소스가 생성됩니다. 사용 중인 계층은 `S1`으로, 다양한 기능을 포함하는 유료 계층이지만, 무료로 제공되는 부분이 있습니다.

   > 💁 Azure Maps의 사용 비용을 보려면, [Azure Maps 가격 페이지](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn)를 확인하세요.

2. 지도 리소스에 대한 API 키가 필요합니다. 이 키를 얻으려면 다음 명령어를 사용하십시오:

   ```sh
   az maps account keys list --name gps-sensor \
                             --resource-group gps-sensor \
                             --output table
   ```

`PrimaryKey` 값을 복사해 놓으십시오.

## 웹 페이지에 지도 표시

이제 웹 페이지에 지도를 표시하는 다음 단계를 수행할 수 있습니다. 작은 웹 앱에 대해 하나의 `html` 파일만 사용 합니다. 상품이나 팀 환경에서는 웹 앱에 움직이는 부분이 더 많을 가능성이 높습니다!

### 작업 - 웹 페이지에 지도 표시

1. 로컬 컴퓨터의 폴더에 index.html 이라는 파일을 만듭니다. 지도를 보관할 HTML 마크업을 추가합니다:

   ```html
   <html>
     <head>
       <style>
         #myMap {
           width: 100%;
           height: 100%;
         }
       </style>
     </head>

     <body onload="init()">
       <div id="myMap"></div>
     </body>
   </html>
   ```

   지도에 `myMap` `div` 가 로드됩니다. 몇 가지 스타일을 사용하면 페이지의 너비와 높이를 확장할 수 있습니다.

   > 🎓 `div` 는 웹 페이지의 섹션으로, 이름과 스타일을 지정할 수 있습니다.

2. 여는 `<head>` 태그 아래에, 외부 스타일시트를 추가하여 지도 표시를 제어하고, 웹 SDK의 외부 스크립트를 추가하여 해당 동작을 관리합니다:

   ```html
   <link
     rel="stylesheet"
     href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css"
     type="text/css"
   />
   <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
   ```

   이 스타일시트에는 지도 모양에 대한 설정이 포함되어 있으며, 스크립트 파일에는 지도를 로드하는 코드가 포함되어 있습니다. 이 코드를 추가하는 것은 C++ 헤더 파일을 포함하거나 Python 모듈을 가져오는 것과 유사합니다.

3. 해당 스크립트 아래에, 스크립트 블록을 추가하여 지도를 시작합니다.

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

   `<subscription_key>` 를 Azure Maps 계정의 API 키로 변경합니다.

   웹 브라우저에서 `index.html` 페이지를 열면, 지도가 로드되고, 시애틀 지역에 초점이 맞춰져 있어야 합니다.

   ![A map showing Seattle, a city in Washington State, USA](../../../../images/map-image.png)

   ✅ 확대/축소 및 중심 매개변수를 변경하여 지도 표시를 실험합니다. 데이터의 위도와 경도에 해당하는 다른 좌표를 추가하여 지도의 중심을 다시 맞출 수 있습니다.

> 💁 웹 앱을 로컬에서 사용하는 더 좋은 방법은 [http-server](https://www.npmjs.com/package/http-server)를 설치하는 것입니다. 이 도구를 사용하려면 [node.js](https://nodejs.org/) 와 [npm](https://www.npmjs.com/) 이 설치되어 있어야 합니다. 도구들이 설치되면 `index.html` 과 `http-server` 타입의 위치를 다룰 수 있습니다. 웹 앱은 로컬 웹 서버 [http://127.0.0.1:8080/](http://127.0.0.1:8080/)에서 열립니다.

## GeoJSON 형식

이제 지도가 표시되는 웹 앱이 준비되었으므로, 저장소 계정에서 GPS 데이터를 추출하여 지도 위에 있는 마커를 레이어에 표시해야 합니다. 그 전에 Azure Maps에 필요한 [GeoJSON](https://wikipedia.org/wiki/GeoJSON) 형식을 살펴보겠습니다.

[GeoJSON](https://geojson.org/)은 지리적 특정 데이터를 처리하도록 설계된 특수 형식의 개방형 표준 JSON 사양입니다. GeoJSON 파일을 디버깅하는 데 유용한 도구인 [geojson.io](https://geojson.io) 를 사용하여 샘플 데이터를 테스트하여 이에 대해 알아볼 수 있습니다 .

샘플 GeoJSON 데이터는 다음과 같습니다:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [-2.10237979888916, 57.164918677004714]
      }
    }
  ]
}
```

특히 흥미로운 점은 데이터가 `FeatureCollection`내에 `Feature`로 중첩되는 방식입니다. 해당 객체 내에서 위도와 경도를 나타내는 `coordinates`가 있는 `geometry`를 찾을 수 있습니다.

✅ When building your geoJSON, pay attention to the order of `latitude` and `longitude` in the object, or your points will not appear where they should! GeoJSON expects data in the order `lon,lat` for points, not `lat,lon`.

`Geometry` 는 단일 점 또는 다각형과 같은 다른 유형을 가질 수 있습니다. 이 예시에서는 경도와 위도라는 두 좌표가 지정된 점입니다.

✅ Azure Maps는 표준 GeoJSON 과 원 및 기타 기하 도형을 그리는 기능을 비롯한 몇 가지 [향상된 기능들](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn) 을 제공합니다.

## GeoJSON을 사용하여 지도에 GPS 데이터 표시하기

이제 이전 학습에서 빌드한 저장소에서 데이터를 사용할 준비가 되었습니다. 참고로 Blob 저장소에 여러 파일로 저장되므로 Azure Maps에서 데이터를 사용할 수 있도록 파일을 검색하고 구문 분석해야 합니다.

### 작업 - 웹 페이지에서 액세스할 스토리지 구성

데이터를 가져오기 위해 저장소를 호출하면 브라우저 콘솔에서 발생하는 오류를 보고 놀랄 수 있습니다. 외부 웹 앱이 해당 데이터를 읽을 수 있도록 하려면 이 저장소에서 [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) 에 대한 권한을 설정해야 하기 때문입니다.

> 🎓 CORS는 "Cross-Origin Resource Sharing"을 나타내며 일반적으로 보안상의 이유로 Azure에서 명시적으로 설정해야 합니다. 이는 데이터에 접근할 수 있는 것으로 예상하지 않는 사이트를 중지합니다.

1. 다음 명령을 실행하여 CORS를 활성화합니다:

   ```sh
   az storage cors add --methods GET \
                       --origins "*" \
                       --services b \
                       --account-name <storage_name> \
                       --account-key <key1>
   ```

   `<storage_name>` 을 저장소 계정의 이름으로 바꿉니다. `<key1>` 를 저장소 계정의 키로 바꿉니다.

   이 명령은 모든 웹 사이트(와일드 카드 `*` 는 모두를 의미)가 저장소 계정에서 _GET_ 요청, 즉 데이터 가져오기를 수행할 수 있습니다. `--services b` 는 blobs에만 이 설정을 적용한다는 의미입니다.

### 작업 - 저장소에서 GPS 데이터 로드

1. `init` 함수의 전체 내용을 다음 코드로 변경합니다:

   ```javascript
   fetch(
     "https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list"
   )
     .then((response) => response.text())
     .then((str) => new window.DOMParser().parseFromString(str, "text/xml"))
     .then((xml) => {
       let blobList = Array.from(xml.querySelectorAll("Url"));
       blobList.forEach(async (blobUrl) => {
         loadJSON(blobUrl.innerHTML);
       });
     })
     .then((response) => {
       map = new atlas.Map("myMap", {
         center: [-122.26473, 47.73444],
         zoom: 14,
         authOptions: {
           authType: "subscriptionKey",
           subscriptionKey: "<subscription_key>",
         },
       });
       map.events.add("ready", function () {
         var source = new atlas.source.DataSource();
         map.sources.add(source);
         map.layers.add(new atlas.layer.BubbleLayer(source));
         source.add(features);
       });
     });
   ```

   `<storage_name>` 를 저장소 계정의 이름으로 변경합니다. `<subscription_key>` Azure Maps 계정의 API 키로 변경합니다.

   여기에서 여러 가지 일이 발생합니다. 먼저 코드는 저장소 계정 이름을 사용하여 빌드된 URL 엔드포인트를 사용하여 Blob 컨테이너에서 GPS 데이터를 가져옵니다. 이 URL은 리소스 유형이 컨테이너(`restype=container`) 임을 나타내는 `gps-data`에서 검색하고 모든 Blob 에 대한 정보를 나열합니다. 이 목록은 Blob 자체를 반환하지 않지만 Blob 데이터를 로드하는 데 사용할 수 있는 각 Blob에 대한 URL을 반환합니다.

   > 💁 You can put this URL into your browser to see details of all the blobs in your container. Each item will have a `Url` property that you can also load in your browser to see the contents of the blob. 이 URL을 브라우저에 넣으면 컨테이너의 모든 Blob에 대한 세부 정보를 볼 수 있습니다. 각 항목은 Blob의 콘텐츠를 보기 위해 브라우저에 로드할 수 있는 `Url` 속성이 있습니다.

   이 코드는 다음에 생성될 `loadJSON` 함수를 호출하여 각 Blob을 로드합니다. 그런 다음 지도 제어를 만들고 `ready` 이벤트에 코드를 추가합니다. 이 이벤트는 웹 페이지에 지도가 표시될 때 호출됩니다.

   ready 이벤트는 나중에 채워질 GeoJSON 데이터를 포함하는 컨테이너인 Azure Maps 데이터 원본을 만듭니다. 그런 다음 이 데이터 원본을 사용하여 GeoJSON의 각 지점 중심에 있는 지도의 원 집합인 버블 레이어를 만듭니다.

2. `init` 함수 아래의 스크립트 블록에 `loadJSON` 함수를 추가합니다:

   ```javascript
   var map, features;

   function loadJSON(file) {
     var xhr = new XMLHttpRequest();
     features = [];
     xhr.onreadystatechange = function () {
       if (xhr.readyState === XMLHttpRequest.DONE) {
         if (xhr.status === 200) {
           gps = JSON.parse(xhr.responseText);
           features.push(
             new atlas.data.Feature(
               new atlas.data.Point([
                 parseFloat(gps.gps.lon),
                 parseFloat(gps.gps.lat),
               ])
             )
           );
         }
       }
     };
     xhr.open("GET", file, true);
     xhr.send();
   }
   ```

   이 함수는 패치(fetch) 루틴에 의해 호출되어 JSON 데이터를 구문 분석하고 경도 및 위도 좌표를 geoJSON으로 읽도록 변환됩니다. 파싱되면 데이터는 geoJSON의 `Feature`의 일부로 설정됩니다. 지도가 초기화되고 경로 주위에 작은 점들이 나타납니다.

3. 브라우저에서 HTML 페이지를 로드합니다. 지도를 로드한 다음 저장소에서 모든 GPS 데이터를 로드하고 지도에 표시합니다.

   ![A map of Saint Edward State Park near Seattle, with circles showing a path around the edge of the park](../../../../images/map-path.png)

> 💁 이 코드는 [코드](.././code) 폴더에서 찾을 수 있습니다.

---

## 🚀 도전

정적 데이터를 지도에 마커로 표시할 수 있다는 점이 좋습니다. 이 웹 앱에 타임스탬프가 있는 json 파일을 사용하여 애니메이션을 추가하고 시간 경과에 따른 마커의 경로를 표시할 수 있습니까? 여기 지동 애니메이션을 사용한 [일부 샘플들](https://azuremapscodesamples.azurewebsites.net/) 이 있습니다.

## 강의 후 퀴즈

[강의 후 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## 복습 및 독학

Azure Maps은 특히 IoT 장치 작업에 유용합니다.

- [Microsoft 문서의 Azure Maps 문서](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn)에서 일부 용도를 조사합니다.
- [Microsoft의 Azure Maps의 자기 학습 모듈을 사용하여 첫번째 경로 찾기 앱 만들기](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn)를 통해 지도 작성 및 웨이포인트에 대한 지식을 심화하세요.

## 과제

[앱 배포](assignment.md)
