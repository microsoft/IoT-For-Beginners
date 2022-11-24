# Geofences

![A sketchnote overview of this lesson](../../../../sketchnotes/lesson-14.jpg)

> [Nitya Narasimhan](https://github.com/nitya)의 스케치 노트입니다. 사진을 클릭하여 크게 보세요

이 비디오는 Geofence에 대한 개요와 Azure Maps에서 Geofence를 사용하는 방법을 제공하며, 이 레슨에서 다룰 주제는 아래와 같습니다.

[![Geofencing with Azure Maps from the Microsoft Developer IoT show](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 영상을 시청하려면 이미지를 클릭하세요

## 강의 전 퀴즈

[강의 전 퀴즈](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## 도입

지난 3번의 수업에서, 여러분은 농장에서 물류 허브로 농산물을 운반하는 트럭을 찾기 위해 IoT를 사용했습니다. GPS의 데이터를 캡처하여 저장할 클라우드로 전송하고, 시각화하여 지도에 표현하였습니다. 공급망의 효율성을 높이기 위한 다음 단계는 트럭이 물류 허브에 도착하려고 할 때 알림을 받는 것 입니다. 사전 알람을 통해 직원들은 차량이 도착하자 마자 지게차 등의 장비들을 가지고 짐을 내릴 준비를 할 수 있습니다. 이렇게 하면 직원들은 기다림 없이 빠르게 짐을 내릴 수 있고, 여러분은 기다리는 트럭 운전사 혹은 다른 직원들에게 돈을 지불하지 않아도 됩니다.

이번 강의에서는 Geofence 정의 지리 공간 영역에 대하여 배웁니다(예: 물류 허브 2Km 이내 주행구역). 그리고 GPS 좌표가 Geofence 내부 또는 외부에 있는지 테스트하여 GPS센서가 해당 범위 내에 도착했는지 여부를 확인하고자 합니다. 


이번 강의에서는 다음을 다룹니다 :

- [지오펜스(Geofence)란](#지오펜스(Geofence)란)
- [지오펜스(Geofence) 정의](#지오펜스(Geofence)-정의)
- [Geofence에 대한 테스트 포인트](#Geofence에-대한-테스트-포인트)
- [서버리스 코드의 Geofence 사용](#서버리스-코드의-Geofence-사용)

> 🗑 이 강의가 3강의 마지막 강의이므로 이 강의와 과제를 마친 후에는 클라우드 서비스를 정리하는 것을 잊지 마세요. 할당을 완료하려면 클라우드 서비스가 필요하기에 강의 이전에 클라우드 서비스 작업을 완료 해 주세요.
>
> 필요한 경우 [프로젝트 가이드 정리](../../../../clean-up.md) 를 참고하세요

## 지오펜스(Geofence)란

A geofence is a virtual perimeter for a real-world geographic region. Geofences can be circles defined as a point and a radius (for example a circle 100m wide around a building), or a polygon covering an area such as a school zone, city limits, or university or office campus.

![Some geofence examples showing a circular geofence around the Microsoft company store, and a polygon geofence around the Microsoft west campus](../../../images/geofence-examples.png)

> 💁 You may have already used geofences without knowing. If you've set a reminder using the iOS reminders app or Google Keep based off a location, you have used a geofence. These apps will set up a geofence based off the location given and alert you when your phone enters the geofence.

There are many reasons why you would want to know that a vehicle is inside or outside a geofence:

- Preparation for unloading - getting a notification that a vehicle has arrived on-site allows a crew to be prepared to unload the vehicle, reducing vehicle waiting time. This can allow a driver to make more deliveries in a day with less waiting time.
- Tax compliance - some countries, such as New Zealand, charge road taxes for diesel vehicles based on the vehicle weight when driving on public roads only. Using geofences allows you to track the mileage driven on public roads as opposed to private roads on sites such as farms or logging areas.
- Monitoring theft - if a vehicle should only remain in a certain area such as on a farm, and it leaves the geofence, it might have been stolen.
- Location compliance - some parts of a work site, farm or factory may be off-limits to certain vehicles, such as keeping vehicles that carry artificial fertilizers and pesticides away from fields growing organic produce. If a geofence is entered, then a vehicle is outside of compliance and the driver can be notified.

✅ Can you think of other uses for geofences?

Azure Maps, the service you used in the last lesson to visualize GPS data, allows you to define geofences, then test to see if a point is inside or outside of the geofence.

## 지오펜스(Geofence) 정의

지오펜스는 이전 학습에서 지도에 추가한 지점과 동일하게 GeoJSON을 사용하여 정의됩니다. 이 경우, `FeatureCollection` 의 `Point` 값 대신, `FeatureCollection` 이 `Polygon`을 포함하게 됩니다.

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Polygon",
        "coordinates": [
          [
            [-122.13393688201903, 47.63829579223815],
            [-122.13389128446579, 47.63782047131512],
            [-122.13240802288054, 47.63783312249837],
            [-122.13238388299942, 47.63829037035086],
            [-122.13393688201903, 47.63829579223815]
          ]
        ]
      },
      "properties": {
        "geometryId": "1"
      }
    }
  ]
}
```

다각형의 각 점은 경도, 위도의 배열 쌍으로 정의되며, 이러한 점들은 `coordinates` 로 설정된 배열에 있습니다. 지난 수업의 `Point`에서, `coordinates`는 위도와 경도 2 개의 값을 포함하는 배열이었습니다. `Polygon`은 위도와 경도 배열을 포함하는 배열입니다.

> 💁 기억하세요, GeoJSON 은 좌표에 `latitude, longitude`가 아닌 `longitude, latitude` 를 사용합니다.

다각형 좌표 배열에는 항상 다각형의 점 수보다 1개 더 많은 항목이 있으며, 마지막 항목은 첫 번째 항목과 동일한 것으로 다각형을 닫습니다. 예를 들어 직사각형의 경우 5개의 점이 있습니다.

![A rectangle with coordinates](../../../../images/polygon-points.png)

다각형 좌표는 왼쪽 상단의 47, -122에서 시작해 오른쪽으로 47, -121 이동한 다음, 아래로 46, -121 이동하고, 오른쪽으로 46, -122 이동한 다음 다시 시작점인 47, -122로 돌아옵니다. 이렇게 하면 다각형에 왼쪽 위, 오른쪽 위, 오른쪽 아래, 왼쪽 아래, 왼쪽 위의 5개의 점이 제공되어 다각형을 닫습니다.

✅ 집이나 학교 주변의 GeoJSON 다각형을 만들어 보세요. [GeoJSON.io](https://geojson.io/) 같은 도구를 사용하세요.

### 작업 - 지오펜스 정의

Azure Maps에서 지오펜스를 사용하려면, 먼저 Azure Maps 계정에 업로드해야 합니다.업로드하면 지오펜스에 대한 지점을 테스트할 수 있는 고유 ID를 받게 됩니다. 지오펜스를 Azure Maps에 업로드하려면, 지도 웹 API를 사용해야 합니다. [curl](https://curl.se) 이라는 도구를 사용해 Azure Maps web API를 호출할 수 있습니다.

> 🎓 Curl 은 웹 끝점에 대한 요청을 만드는 명령어 도구입니다.

1. Linux, macOS, 또는 최신 버전의 Windows 10 를 사용하는 경우 curl 이 이미 설치되어 있을 수 있습니다. 터미널 또는 명령어에서 다음을 실행하여 확인합니다:

   ```sh
   curl --version
   ```

   curl의 버전 정보가 표시되지 않으면, [curl 다운로드 페이지](https://curl.se/download.html)에서 설치해야 합니다.

   > 💁 Postman를 사용한 경헙이 있다면, 원하는 경우 이를 대신 사용할 수 있습니다.

2. 다각형이 포함된 GeoJSON 파일을 생성합니다. GPS 센서를 사용하여 이를 테스트할 것이므로, 현재의 위치 주변에 다각형을 만듭니다. 위에 제공된 GeoJSON 예제를 편집하여 수동으로 만들거나, [GeoJSON.io](https://geojson.io/) 같은 도구를 사용할 수 있습니다.

   GeoJSON은 `Polygon` 타입의 `geometry`의 `Feature`를 포함한 `FeatureCollection`을 가지고 있습니다.

   **반드시** `geometry` 요소와 동일한 레벨의 `properties` 요소를 추가해야 합니다. 이는 `geometryId`를 포함하고 있습니다:

   ```json
   "properties": {
       "geometryId": "1"
   }
   ```

   [GeoJSON.io](https://geojson.io/)를 사용하는 경우, JSON 파일을 다운로드 한 후, 또는 JSON 편집기에서 비어있는 `properties` 요소에 수동으로 이 항목을 추가해야 합니다.

   이 `geometryId` 는 이 파일에서 고유해야 합니다. You can upload multiple geofences as multiple `Features` in the `FeatureCollection` in the same GeoJSON file, as long as each one has a different `geometryId`. 다각형은 다른 파일에서 다른 시간대에 업로드 된 경우, 동일한 `geometryId`를 가질 수 있습니다.

3. 이 파일을 `geofence.json`로 저장하고, 터미널 또는 콘솔에 저장된 위치로 이동합니다.

4. 다음 curl 명령을 실행하여 GeoFence를 생성합니다:

   ```sh
   curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
        --header 'Content-Type: application/json' \
        --include \
        --data @geofence.json
   ```

   `<subscription_key>` 을 Azure Maps 계정의 API key를 가지고 있는 URL로 바꿉니다.

   URL은 `https://atlas.microsoft.com/mapData/upload` API를 통해 지도 데이터를 업로드하는데 사용됩니다. 호출에는 사용할 Azure Maps API를 지정하는 `api-version` 매개 변수가 포함되어 있습니다. 이는 API가 시간이 지남에 따라 변경될 수 있지만 이전 버전과의 호환성을 유지하기 위한 것입니다. 업로드되는 데이터 형식은 `geojson`로 설정됩니다.

   이것은 API 업로드를 위한 POST 요청을 실행하고 `location`이라고 부르는 응답 헤더 목록을 반환합니다.

   ```output
   content-type: application/json
   location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
   x-ms-azuremaps-region: West US 2
   x-content-type-options: nosniff
   strict-transport-security: max-age=31536000; includeSubDomains
   x-cache: CONFIG_NOCACHE
   date: Sat, 22 May 2021 21:34:57 GMT
   content-length: 0
   ```

   > 🎓 웹 엔드포인트를 호출할 때, `key=value`와 같은 키 값 쌍 뒤에 `?`를 더해서 매개 변수를 전달할 수 있습니다. 키 값 쌍은 `&`로 구분됩니다.

5. Azure Maps 은 이를 즉시 처리하지 않으므로, `location` 헤더에 제공된 URL을 사용하여 업로드 요청이 완료되었는지 확인해야 합니다. 상태를 보려면 이 위치에 GET 요청을 만드십시오. `location` URL 끝에 subscription key `&subscription-key=<subscription_key>` 와 같이 추가하고, `<subscription_key>` 를 Azure Maps 계정의 API 키로 변경합니다. 다음 명령을 실행합니다:

   ```sh
   curl --request GET '<location>&subscription-key=<subscription_key>'
   ```

   `<location>` 를 `location` 헤더 값으로 변경합니다. 그리고 `<subscription_key>` 를 Azure Maps 계정의 API 키 값으로 변경합니다.

6. 응답에서 `status` 값을 확인하십시오. `Succeeded`가 아닌 경우, 잠시 기다렸다가 다시 시도하십시오.

7. 상태가 `Succeeded`로 돌아오면, 응답에서 `resourceLocation` 를 확인하십시오. 여기에는 GeoJson 객체의 고유한 ID (UDID라고 함)에 대한 세부 정보가 포함되어 있습니다. UDID 는 `metadata/` 뒤에 오는 값dmfh `api-version`을 포함하지 않습니다. 예를 들어, `resourceLocation` 이 다음과 같은 경우:

   ```json
   {
     "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
   }
   ```

   그러면 UDID는 `7c3776eb-da87-4c52-ae83-caadf980323a` 입니다.

   이 UDID 의 사본을 보관하십시오. 지오펜스를 테스트하는데 필요한 것입니다.

## Geofence에 대한 테스트 포인트

우선 다각형이 Azure Maps에 표시되면, 여러분은 점을 테스트하여 해당 점이 Geofence 내부에 있는지 외부에 있는지 확인할 수 있습니다. 웹 API 요청을 작성하고 Geofence의 UDID를 전달하며 테스트할 지점의 위도와 경도를 API에 전송합니다.

해당 요청 시 `searchBuffer`라는 값을 전달 할 수도 있습니다. 이는 결과를 반환할 때 얼마나 정확해야하는지를 지도 API에 알려줍니다. 이러한 이유는 GPS가 완벽하게 정확하지 않고, 때떄로 위치가 미터단위 혹은 그 이하로 달라질 수 있기 때문입니다. 검색 버퍼의 기본값은 50m이지만 0m에서 500m 사이의 값을 설정할 수 있습니다.

API 호출 결과 중 `거리`값이 반환됩니다. 이는 Geofence 가장자리에서 가장 가까운 지점까지 양수 값으로 측정된 것으로, 점이 Geofence 밖에 있으면 양수값이고 안에 있으면 음수 값 입니다. 이 거리가 버퍼보다 작으면 실제 거리가 미터 단위로 반환됩니다. 그렇지 않으면 값이 999또는 -999로 반환됩니다. 999는 양수이므로 검색 버퍼보다 Geofence 밖에 있음을 의미하고, -999는 음수이므로 검색 버퍼보다 지오펜스 안쪽에 있음을 의미합니다. 

![A geofence with a 50m search buffer around in](../../../../images/search-buffer-and-distance.png)

위 이미지에서 지오펜스에는 50m 검색 버퍼가 있습니다.

- 지오펜스 중앙의 한 점, 검색 버퍼 내부의 한 점 사이의 거리는 **-999**입니다.
- 검색 버퍼를 훨씬 벗어난 지점의 거리는 **999**입니다.
- 지오펜스에서 6m 떨어진 지오펜스 내부 및 검색 버퍼 내부 지점의 거리는 **6m**입니다.
- 지오펜스에서 39m 떨어진 지오펜스 바깥쪽 및 검색 버퍼 내부 지점의 거리는 **39m**입니다.

Geofence의 가장자리까지의 거리를 알고, 차량 위치를 기반으로 결정을 할 때 이를 GPS 판독값, 속도 및 도로 데이터와 같은 다른 정보와 결합하는 것이 중요합니다. 

예를 들어, 차량이 Geofence 옆에 있는 도로를 따라 주행하고 있다고 가정하겠습니다. 만약 Geofence 내부로 어떠한 차량의 접근이 없었음에도 불구하고 하나라도 GPS값이 부정확하거나, 옆 도로로 주행하고 있는 차량을 Geofence 내부에 있다고 배치하는 경우 해당 값은 무시될 수 있습니다.

![A GPS trail showing a vehicle passing the Microsoft campus on the 520, with GPS readings along the road except for one on the campus, inside a geofence](../../../../images/geofence-crossing-inaccurate-gps.png)

위 이미지에서 마이크로소프트 캠퍼스 일부에 Geofence가 있습니다. 빨간 색 선은 트럭이 520번 도로를 주행하는 모습을 보여주며, GPS 판독값을 보여주는 원이 표시됩니다. 대부분의 값들은 정확하게 520번 도로를 따라 주행하지만 Geofence 내부에 하나 정도 작은 부정확한 정보가 있습니다. 판독값이 완벽하게 정확할 수 있는 방법은 없습니다. 트럭이 520번 도로에서 캡퍼스 방향으로 돌렸다가 다시 520번 도로로 돌아갈 수 있는 도로가 없습니다. 이 Geofence를 확인하는 코드는 Geofence 테스트 결과에 대해 작업하기 전에 이전 판독값을 고려해야 합니다.

✅ GPS 판독값이 올바른 것으로 간주될 수 있는지 확인하기 위해 어떤 추가 데이터가 필요할까요?

### 작업 - Geofence에 대한 테스트 포인트

1. 웹 API 쿼리의 URL을 작성하는 것으로 시작합니다. 형식은 다음과 같습니다.

   ```output
   https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
   ```

   `<subscription_key>`를 AzureMaps 계정의 API 키로 바꿉니다.

    이전 작업의 지오펜스의 UDID로 `<UDID>`를 바꿉니다.

    `<lat>`와 `<lon>`을 테스트할 위도와 경도로 바꿉니다.
    
   이 URL은 `https://atlas.microsoft.com/spatial/geofence/json`API를 통해 GeoJSON을 사용하여 정의된 Geofence를 쿼리합니다. `1.0` 버전 이상의 API 버전을 대상으로 하며, `deviceId`의 매개변수는 필수이고, 위도와 경도가 나오는 장치의 이름이어야 합니다.

   기본 검색 버퍼는 50m이며, `searchBuffer=<distance>`와 같은 추가 매개변수를 전달하여 이 값을 변경할 수 있습니다. `<distance>` 는 검색 버퍼 거리(0~500 사이값, m 단위)로 설정합니다.

1. curl을 사용하여 다음 URL에 GET 요청을 작성합니다.

   ```sh
   curl --request GET '<URL>'
   ```

   > 💁 `BadRequest` 응답 코드가 표시되면 다음과 같은 오류가 발생합니다.
   >
   > ```output
   > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
   > ```
   >
   > 이렇게 하면 GeoJSON은 `geometryId`가 있는 `properties` 섹션이 누락됩니다. GeoJSON을 수정한 다음 위의 단계를 반복하여 다시 업로드하고 새 UDID를 받아야 합니다.

1. 응답에는 Geofence를 만드는데 사용되는 GeoJSON에 정의된 각 다각형에 대하여 `geometries`목록이 포함됩니다. 각 geometry는 `distance`, `nearestLat`, `nearestLon` 와 같은 3가지 분야가 있습니다.

   ```output
   {
       "geometries": [
           {
               "deviceId": "gps-sensor",
               "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
               "geometryId": "1",
               "distance": 999.0,
               "nearestLat": 47.645875,
               "nearestLon": -122.142713
           }
       ],
       "expiredGeofenceGeometryId": [],
       "invalidPeriodGeofenceGeometryId": []
   }
   ```

   - `nearestLat`와 `nearestLon` 는 Geofence의 가장자리에 있는 test 장소에서 가장 가까운 지점의 위도와 경도입니다.

   - `distance` is the distance from the location being tested to the closest point on the edge of the geofence. Negative numbers mean inside the geofence, positive outside. This value will be less than 50 (the default search buffer), or 999.
   - `distance`는 test하는 위치에서 Geofence의 edge와 가장 가까이에 있는 지점까지의 거리입니다. 음수는 Geofence 안에 있음을 양수는 Geofence 밖에 있음을 의미합니다. 이 값으 기본 검색 버퍼 값인 50보다 작거나 999입니다.

1. Geofence 내부 및 외부의 위치에서 위의 작업을 여러 번 반복합니다. 

## 서버리스 코드의 Geofence 사용

You can now add a new trigger to your Functions app to test the IoT Hub GPS event data against the geofence.

### Consumer groups

As you will remember from previous lessons, the IoT Hub will allow you to replay events that have been received by the hub but not processed. But what would happen if multiple triggers connected? How will it know which one has processed which events.

The answer is it can't! Instead you can define multiple separate connections to read off events, and each one can manage the replay of unread messages. These are called _consumer groups_. When you connect to the endpoint, you can specify which consumer group you want to connect to. Each component of your application will connect to a different consumer group

![One IoT Hub with 3 consumer groups distributing the same messages to 3 different functions apps](../../../images/consumer-groups.png)

In theory up to 5 applications can connect to each consumer group, and they will all receive messages when they arrive. It's best practice to have only one application access each consumer group to avoid duplicate message processing, and ensure when restarting all queued messages are processed correctly. For example, if you launched your Functions app locally as well as running it in the cloud, they would both process messages, leading to duplicate blobs stored in the storage account.

If you review the `function.json` file for the IoT Hub trigger you created in an earlier lesson, you will see the consumer group in the event hub trigger binding section:

```json
"consumerGroup": "$Default"
```

When you create an IoT Hub, you get the `$Default` consumer group created by default. If you want to add an additional trigger, you can add this using a new consumer group.

> 💁 In this lesson, you will use a different function to test the geofence to the one used to store the GPS data. This is to show how to use consumer groups and separate the code to make it easier to read and understand. In a production application there are many ways you might architect this - putting both on one function, using a trigger on the storage account to run a function to check the geofence, or using multiple functions. There is no 'right way', it depends on the rest of your application and your needs.

### Task - create a new consumer group

1. Run the following command to create a new consumer group called `geofence` for your IoT Hub:

   ```sh
   az iot hub consumer-group create --name geofence \
                                    --hub-name <hub_name>
   ```

   Replace `<hub_name>` with the name you used for your IoT Hub.

1. If you want to see all the consumer groups for an IoT Hub, run the following command:

   ```sh
   az iot hub consumer-group list --output table \
                                  --hub-name <hub_name>
   ```

   Replace `<hub_name>` with the name you used for your IoT Hub. This will list all the consumer groups.

   ```output
   Name      ResourceGroup
   --------  ---------------
   $Default  gps-sensor
   geofence  gps-sensor
   ```

> 💁 When you ran the IoT Hub event monitor in an earlier lesson, it connected to the `$Default` consumer group. This was why you can't run the event monitor and an event trigger. If you want to run both, then you can use other consumer groups for all your function apps, and keep `$Default` for the event monitor.

### Task - create a new IoT Hub trigger

1. Add a new IoT Hub event trigger to your `gps-trigger` function app that you created in an earlier lesson. Call this function `geofence-trigger`.

   > ⚠️ You can refer to [the instructions for creating an IoT Hub event trigger from project 2, lesson 5 if needed](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Configure the IoT Hub connection string in the `function.json` file. The `local.settings.json` is shared between all triggers in the Function App.

1. Update the value of the `consumerGroup` in the `function.json` file to reference the new `geofence` consumer group:

   ```json
   "consumerGroup": "geofence"
   ```

1. You will need to use the subscription key for your Azure Maps account in this trigger, so add a new entry to the `local.settings.json` file called `MAPS_KEY`.

1. Run the Functions App to ensure it is connecting and processing messages. The `iot-hub-trigger` from the earlier lesson will also run and upload blobs to storage.

   > To avoid duplicate GPS readings in blob storage, you can stop the Functions App you have running in the cloud. To do this, use the following command:
   >
   > ```sh
   > az functionapp stop --resource-group gps-sensor \
   >                     --name <functions_app_name>
   > ```
   >
   > Replace `<functions_app_name>` with the name you used for your Functions App.
   >
   > You can restart it later with the following command:
   >
   > ```sh
   > az functionapp start --resource-group gps-sensor \
   >                     --name <functions_app_name>
   > ```
   >
   > Replace `<functions_app_name>` with the name you used for your Functions App.

### Task - test the geofence from the trigger

Earlier in this lesson you used curl to query a geofence to see if a point was located inside or outside. You can make a similar web request from inside your trigger.

1. To query the geofence, you need its UDID. Add a new entry to the `local.settings.json` file called `GEOFENCE_UDID` with this value.

1. Open the `__init__.py` file from the new `geofence-trigger` trigger.

1. Add the following import to the top of the file:

   ```python
   import json
   import os
   import requests
   ```

   The `requests` package allows you to make web API calls. Azure Maps doesn't have a Python SDK, you need to make web API calls to use it from Python code.

1. Add the following 2 lines to the start of the `main` method to get the Maps subscription key:

   ```python
   maps_key = os.environ['MAPS_KEY']
   geofence_udid = os.environ['GEOFENCE_UDID']
   ```

1. Inside the `for event in events` loop, add the following to get the latitude and longitude from each event:

   ```python
   event_body = json.loads(event.get_body().decode('utf-8'))
   lat = event_body['gps']['lat']
   lon = event_body['gps']['lon']
   ```

   This code converts the JSON from the event body to a dictionary, then extracts the `lat` and `lon` from the `gps` field.

1. When using `requests`, rather than building up a long URL as you did with curl, you can use just the URL part and pass the parameters as a dictionary. Add the following code to define the URL to call and configure the parameters:

   ```python
   url = 'https://atlas.microsoft.com/spatial/geofence/json'

   params = {
       'api-version': 1.0,
       'deviceId': 'gps-sensor',
       'subscription-key': maps_key,
       'udid' : geofence_udid,
       'lat' : lat,
       'lon' : lon
   }
   ```

   The items in the `params` dictionary will match the key value pairs you used when calling the web API via curl.

1. Add the following lines of code to call the web API:

   ```python
   response = requests.get(url, params=params)
   response_body = json.loads(response.text)
   ```

   This calls the URL with the parameters, and gets back a response object.

1. Add the following code below this:

   ```python
   distance = response_body['geometries'][0]['distance']

   if distance == 999:
       logging.info('Point is outside geofence')
   elif distance > 0:
       logging.info(f'Point is just outside geofence by a distance of {distance}m')
   elif distance == -999:
       logging.info(f'Point is inside geofence')
   else:
       logging.info(f'Point is just inside geofence by a distance of {distance}m')
   ```

   This code assumes 1 geometry, and extracts the distance from that single geometry. It then logs different messages based off the distance.

1. Run this code. You will see in the logging output if the GPS coordinates are inside or outside the geofence, with a distance if the point is within 50m. Try this code with different geofences based off the location of your GPS sensor, try moving the sensor (for example tethered to WiFi from a mobile phone, or with different coordinates on the virtual IoT device) to see this change.

1. When you are ready, deploy this code to your Functions app in the cloud. Don't forget to deploy the new Application Settings.

   > ⚠️ You can refer to [the instructions for uploading Application Settings from project 2, lesson 5 if needed](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

   > ⚠️ You can refer to [the instructions for deploying your Functions app from project 2, lesson 5 if needed](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 You can find this code in the [code/functions](code/functions) folder.

---

## 🚀 Challenge

In this lesson you added one geofence using a GeoJSON file with a single polygon. You can upload multiple polygons at the same time, as long as they have different `geometryId` values in the `properties` section.

Try uploading a GeoJSON file with multiple polygons and adjust your code to find which polygon the GPS coordinates are closest to or in.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Review & Self Study

- Read more on geofences and some of their use cases on the [Geofencing page on Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
- Read more on Azure Maps geofencing API on the [Microsoft Azure Maps Spatial - Get Geofence documentation](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
- Read more on consumer groups in the [Features and terminology in Azure Event Hubs - Event consumers documentation on Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers)

## Assignment

[Send notifications using Twilio](assignment.md)
