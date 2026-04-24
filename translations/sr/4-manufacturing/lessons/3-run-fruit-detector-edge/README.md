# Покрените детектор воћа на ивици

![Преглед лекције у облику скице](../../../../../translated_images/sr/lesson-17.bc333c3c35ba8e42.webp)

> Скица од [Nitya Narasimhan](https://github.com/nitya). Кликните на слику за већу верзију.

Овај видео даје преглед покретања класификатора слика на IoT уређајима, тема која је обрађена у овој лекцији.

[![Custom Vision AI on Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Квиз пре предавања

[Квиз пре предавања](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Увод

У претходној лекцији користили сте класификатор слика за класификацију зрелог и незрелог воћа, шаљући слику снимљену камером на вашем IoT уређају преко интернета до cloud сервиса. Ови позиви захтевају време, коштају новац, а у зависности од врсте података које користите, могу имати импликације на приватност.

У овој лекцији научићете како да покренете моделе машинског учења (ML) на ивици - на IoT уређајима који раде на вашој мрежи, а не у cloud-у. Научићете предности и недостатке edge computing-а у односу на cloud computing, како да примените ваш AI модел на ивици и како да му приступите са вашег IoT уређаја.

У овој лекцији обрадићемо:

* [Edge computing](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Региструјте IoT Edge уређај](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Подесите IoT Edge уређај](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Извезите ваш модел](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Припремите ваш контејнер за примену](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Примените ваш контејнер](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Користите ваш IoT Edge уређај](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Edge computing

Edge computing подразумева коришћење рачунара који обрађују IoT податке што је ближе могуће месту где се ти подаци генеришу. Уместо да се ова обрада врши у cloud-у, она се премешта на ивицу cloud-а - вашу интерну мрежу.

![Дијаграм архитектуре који приказује интернет услуге у cloud-у и IoT уређаје на локалној мрежи](../../../../../translated_images/sr/cloud-without-edge.b4da641f6022c95e.webp)

До сада сте имали уређаје који прикупљају податке и шаљу их у cloud ради анализе, покрећући serverless функције или AI моделе у cloud-у.

![Дијаграм архитектуре који приказује IoT уређаје на локалној мрежи који се повезују са edge уређајима, а ти edge уређаји се повезују са cloud-ом](../../../../../translated_images/sr/cloud-with-edge.1e26462c62c126fe.webp)

Edge computing подразумева премештање неких cloud услуга са cloud-а на рачунаре који раде на истој мрежи као и IoT уређаји, комуницирајући са cloud-ом само ако је потребно. На пример, можете покренути AI моделе на edge уређајима за анализу зрелости воћа и само слати аналитичке податке назад у cloud, као што је број зрелих комада воћа у односу на незреле.

✅ Размислите о IoT апликацијама које сте до сада изградили. Који делови њих би могли бити премештени на ивицу?

### Предности

Предности edge computing-а су:

1. **Брзина** - edge computing је идеалан за податке који су временски осетљиви јер се радње обављају на истој мрежи као и уређај, уместо да се позиви обављају преко интернета. Ово омогућава веће брзине јер интерне мреже могу радити знатно брже од интернет конекција, са подацима који путују много краћу удаљеност.

    > 💁 Иако се оптички каблови користе за интернет конекције, омогућавајући подацима да путују брзином светлости, подаци могу захтевати време да путују широм света до cloud провајдера. На пример, ако шаљете податке из Европе у cloud услуге у САД, потребно је најмање 28ms да подаци пређу Атлантик у оптичком каблу, а то не укључује време потребно за пренос података до трансатлантског кабла, конверзију из електричних у светлосне сигнале и назад на другој страни, затим из оптичког кабла до cloud провајдера.

    Edge computing такође захтева мањи мрежни саобраћај, смањујући ризик да ваши подаци успоре због загушења на ограниченом пропусном опсегу доступном за интернет конекцију.

1. **Доступност у удаљеним областима** - edge computing функционише када имате ограничену или никакву конекцију, или када је конекција превише скупа за континуирано коришћење. На пример, када радите у хуманитарним катастрофама где је инфраструктура ограничена или у земљама у развоју.

1. **Нижи трошкови** - прикупљање, складиштење, анализа и покретање радњи на edge уређају смањује коришћење cloud услуга, што може смањити укупне трошкове ваше IoT апликације. Недавно је дошло до пораста уређаја дизајнираних за edge computing, као што су AI акцелераторске плоче попут [Jetson Nano од NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), који могу покретати AI радне оптерећења користећи GPU-базирани хардвер на уређајима који коштају мање од 100 америчких долара.

1. **Приватност и безбедност** - са edge computing-ом, подаци остају на вашој мрежи и не отпремају се у cloud. Ово је често пожељно за осетљиве и лично идентификационе информације, посебно зато што подаци не морају бити складиштени након што су анализирани, што значајно смањује ризик од цурења података. Примери укључују медицинске податке и снимке сигурносних камера.

1. **Руковање несигурним уређајима** - ако имате уређаје са познатим безбедносним недостацима које не желите директно повезати на вашу мрежу или интернет, можете их повезати на засебну мрежу са gateway IoT Edge уређајем. Овај edge уређај може такође имати конекцију са вашом широм мрежом или интернетом и управљати токовима података напред и назад.

1. **Подршка за некомпатибилне уређаје** - ако имате уређаје који не могу да се повежу на IoT Hub, на пример уређаје који могу да се повежу само користећи HTTP конекције или уређаје који имају само Bluetooth за повезивање, можете користити IoT edge уређај као gateway уређај, који прослеђује поруке на IoT Hub.

✅ Урадите истраживање: Које друге предности могу постојати за edge computing?

### Недостаци

Постоје недостаци edge computing-а, где cloud може бити пожељнија опција:

1. **Скала и флексибилност** - cloud computing може прилагодити потребе мреже и података у реалном времену додавањем или смањењем сервера и других ресурса. Додавање више edge рачунара захтева ручно додавање више уређаја.

1. **Поузданост и отпорност** - cloud computing пружа више сервера, често на више локација, ради редунданције и опоравка од катастрофа. Да бисте имали исти ниво редунданције на ивици, потребна су велика улагања и много конфигурационог рада.

1. **Одржавање** - cloud провајдери пружају одржавање система и ажурирања.

✅ Урадите истраживање: Који други недостаци могу постојати за edge computing?

Недостаци су заправо супротности предностима коришћења cloud-а - морате сами изградити и управљати овим уређајима, уместо да се ослањате на експертизу и скалу cloud провајдера.

Неки ризици су ублажени самом природом edge computing-а. На пример, ако имате edge уређај који ради у фабрици и прикупља податке са машина, не морате размишљати о неким сценаријима опоравка од катастрофа. Ако фабрика остане без струје, не треба вам резервни edge уређај јер ће машине које генеришу податке које edge уређај обрађује такође бити без струје.

За IoT системе, често ћете желети мешавину cloud и edge computing-а, користећи сваку услугу на основу потреба система, његових корисника и његових одржавалаца.

## Azure IoT Edge

![Azure IoT Edge лого](../../../../../translated_images/sr/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge је услуга која вам може помоћи да преместите радне оптерећења из cloud-а на ивицу. Постављате уређај као edge уређај, а из cloud-а можете применити код на тај edge уређај. Ово вам омогућава да комбинујете могућности cloud-а и ивице.

> 🎓 *Радна оптерећења* је термин за било коју услугу која обавља неку врсту рада, као што су AI модели, апликације или serverless функције.

На пример, можете обучити класификатор слика у cloud-у, а затим из cloud-а применити га на edge уређај. Ваш IoT уређај затим шаље слике edge уређају за класификацију, уместо да шаље слике преко интернета. Ако треба да примените нову итерацију модела, можете га обучити у cloud-у и користити IoT Edge за ажурирање модела на edge уређају на вашу нову итерацију.

> 🎓 Софтвер који се примењује на IoT Edge познат је као *модули*. Подразумевано IoT Edge покреће модуле који комуницирају са IoT Hub-ом, као што су `edgeAgent` и `edgeHub` модули. Када примените класификатор слика, он се примењује као додатни модул.

IoT Edge је уграђен у IoT Hub, тако да можете управљати edge уређајима користећи исту услугу коју бисте користили за управљање IoT уређајима, са истим нивоом безбедности.

IoT Edge покреће код из *контејнера* - самосталних апликација које се покрећу изоловано од осталих апликација на вашем рачунару. Када покренете контејнер, он се понаша као засебан рачунар који ради унутар вашег рачунара, са сопственим софтвером, услугама и апликацијама. Већину времена контејнери не могу приступити ничему на вашем рачунару осим ако не одлучите да делите нешто, као што је фасцикла, са контејнером. Контејнер затим излаже услуге преко отвореног порта на који можете да се повежете или да га изложите вашој мрежи.

![Веб захтев преусмерен на контејнер](../../../../../translated_images/sr/container-web-browser.4ee81dd4f0d8838c.webp)

На пример, можете имати контејнер са веб сајтом који ради на порту 80, подразумеваном HTTP порту, и можете га затим изложити са вашег рачунара такође на порту 80.

✅ Урадите истраживање: Прочитајте о контејнерима и услугама као што су Docker или Moby.

Можете користити Custom Vision за преузимање класификатора слика и њихову примену као контејнере, било директно на уређај или преко IoT Edge-а. Када се покрену у контејнеру, могу се приступити користећи исти REST API као cloud верзија, али са endpoint-ом који показује на Edge уређај који покреће контејнер.

## Региструјте IoT Edge уређај

Да бисте користили IoT Edge уређај, потребно је да буде регистрован у IoT Hub-у.

### Задатак - региструјте IoT Edge уређај

1. Направите IoT Hub у ресурсној групи `fruit-quality-detector`. Дајте му јединствено име засновано на `fruit-quality-detector`.

1. Региструјте IoT Edge уређај назван `fruit-quality-detector-edge` у вашем IoT Hub-у. Команда за ово је слична оној која се користи за регистрацију не-edge уређаја, осим што додајете `--edge-enabled` заставицу.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Замените `<hub_name>` именом вашег IoT Hub-а.

1. Узмите стринг за повезивање вашег уређаја користећи следећу команду:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Замените `<hub_name>` именом вашег IoT Hub-а.

    Направите копију стринга за повезивање који је приказан у излазу.

## Подесите IoT Edge уређај

Када сте креирали регистрацију edge уређаја у вашем IoT Hub-у, можете подесити edge уређај.

### Задатак - Инсталирајте и покрените IoT Edge Runtime

**IoT Edge Runtime покреће само Linux контејнере.** Може се покренути на Linux-у или на Windows-у користећи Linux виртуелне машине.

* Ако користите Raspberry Pi као ваш IoT уређај, он покреће подржану верзију Linux-а и може хостовати IoT Edge Runtime. Пратите [упутство за инсталацију Azure IoT Edge за Linux на Microsoft документацији](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) да бисте инсталирали IoT Edge и подесили стринг за повезивање.

    > 💁 Запамтите, Raspberry Pi OS је варијанта Debian Linux-а.

* Ако не користите Raspberry Pi, али имате Linux рачунар, можете покренути IoT Edge Runtime. Пратите [упутство за инсталацију Azure IoT Edge за Linux на Microsoft документацији](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) да бисте инсталирали IoT Edge и подесили стринг за повезивање.

* Ако користите Windows, можете инсталирати IoT Edge Runtime у Linux виртуелној машини пратећи [секцију за инсталацију и покретање IoT Edge Runtime-а у брзом старту за примену вашег првог IoT Edge модула на Windows уређају на Microsoft документацији](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Можете престати када стигнете до секције *Deploy a module*.

* Ако користите macOS, можете креирати виртуелну машину (VM) у cloud-у коју ћете користити за ваш IoT Edge уређај. Ово су рачунари које можете креирати у cloud-у и приступити им преко интернета. Можете креирати Linux VM који има инсталиран IoT Edge. Пратите [упутство за креирање виртуелне машине која покреће IoT Edge](vm-iotedge.md) за инструкције како то да урадите.

## Извезите ваш модел

Да бисте покренули класификатор на ивици, потребно је да га извез
1. Покрените портал Custom Vision на [CustomVision.ai](https://customvision.ai) и пријавите се ако већ није отворен. Затим отворите свој пројекат `fruit-quality-detector`.

1. Изаберите дугме **Settings** (икона ⚙).

1. У листи *Domains*, изаберите *Food (compact)*.

1. У секцији *Export Capabilities*, уверите се да је изабрано *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. На дну странице Settings, изаберите **Save Changes**.

1. Поново обучите модел помоћу дугмета **Train**, бирајући *Quick training*.

### Задатак - извоз модела

Када је модел обучен, потребно је да се извезе као контејнер.

1. Изаберите картицу **Performance** и пронађите најновију итерацију која је обучена користећи компактни домен.

1. Изаберите дугме **Export** на врху.

1. Изаберите **DockerFile**, а затим одаберите верзију која одговара вашем edge уређају:

    * Ако користите IoT Edge на Linux рачунару, Windows рачунару или виртуелној машини, изаберите *Linux* верзију.
    * Ако користите IoT Edge на Raspberry Pi, изаберите *ARM (Raspberry Pi 3)* верзију.

> 🎓 Docker је један од најпопуларнијих алата за управљање контејнерима, а DockerFile је сет инструкција о томе како да се контејнер подеси.

1. Изаберите **Export** да Custom Vision креира релевантне датотеке, а затим **Download** да их преузмете у zip фајлу.

1. Сачувајте датотеке на рачунар, а затим распакујте фасциклу.

## Припрема контејнера за распоређивање

![Контејнери се граде, затим постављају у регистар контејнера, а потом се распоређују са регистра контејнера на edge уређај користећи IoT Edge](../../../../../translated_images/sr/container-edge-flow.c246050dd60ceefd.webp)

Када преузмете свој модел, потребно је да га изградите у контејнер, а затим поставите у регистар контејнера - онлајн локацију где можете чувати контејнере. IoT Edge затим може преузети контејнер из регистра и поставити га на ваш уређај.

![Лого Azure Container Registry](../../../../../translated_images/sr/azure-container-registry-logo.09494206991d4b29.webp)

Регистар контејнера који ћете користити за ову лекцију је Azure Container Registry. Ова услуга није бесплатна, па да бисте уштедели новац, уверите се да [очистите свој пројекат](../../../clean-up.md) када завршите.

> 💁 Можете видети трошкове коришћења Azure Container Registry на [страници са ценама Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Задатак - инсталирање Docker-а

Да бисте изградили и распоредили класификатор, можда ће бити потребно да инсталирате [Docker](https://www.docker.com/).

Ово ће бити потребно само ако планирате да изградите свој контејнер са уређаја који је различит од оног на којем сте инсталирали IoT Edge - као део инсталације IoT Edge-а, Docker је већ инсталиран.

1. Ако градите Docker контејнер на уређају који је различит од вашег IoT Edge уређаја, пратите упутства за инсталацију Docker-а на [Docker install page](https://www.docker.com/products/docker-desktop) да бисте инсталирали Docker Desktop или Docker engine. Уверите се да је покренут након инсталације.

### Задатак - креирање ресурса регистра контејнера

1. Покрените следећу команду из вашег терминала или командне линије да бисте креирали ресурс Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Замените `<Container registry name>` јединственим именом за ваш регистар контејнера, користећи само слова и бројеве. Засновајте ово на `fruitqualitydetector`. Ово име постаје део URL-а за приступ регистру контејнера, па мора бити глобално јединствено.

1. Пријавите се у Azure Container Registry помоћу следеће команде:

    ```sh
    az acr login --name <Container registry name>
    ```

    Замените `<Container registry name>` именом које сте користили за ваш регистар контејнера.

1. Поставите регистар контејнера у администраторски режим како бисте могли да генеришете лозинку помоћу следеће команде:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Замените `<Container registry name>` именом које сте користили за ваш регистар контејнера.

1. Генеришите лозинке за ваш регистар контејнера помоћу следеће команде:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Замените `<Container registry name>` именом које сте користили за ваш регистар контејнера.

    Сачувајте вредност `PASSWORD`, јер ће вам бити потребна касније.

### Задатак - изградња контејнера

Оно што сте преузели из Custom Vision-а је DockerFile који садржи инструкције о томе како контејнер треба да се изгради, заједно са апликационим кодом који ће се извршавати унутар контејнера да би хостовао ваш модел Custom Vision-а, као и REST API за његово позивање. Можете користити Docker да изградите означени контејнер из DockerFile-а, а затим га поставите у регистар контејнера.

> 🎓 Контејнери добијају ознаку која дефинише име и верзију. Када треба да ажурирате контејнер, можете га изградити са истом ознаком, али новијом верзијом.

1. Отворите терминал или командну линију и идите до распакованог модела који сте преузели из Custom Vision-а.

1. Покрените следећу команду да изградите и означите слику:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Замените `<platform>` платформом на којој ће овај контејнер бити покренут. Ако користите IoT Edge на Raspberry Pi, поставите ово на `linux/armhf`, у супротном поставите на `linux/amd64`.

    > 💁 Ако покрећете ову команду са уређаја на којем је IoT Edge покренут, као што је Raspberry Pi, можете изоставити део `--platform <platform>` јер подразумевано користи тренутну платформу.

    Замените `<Container registry name>` именом које сте користили за ваш регистар контејнера.

    > 💁 Ако користите Linux или Raspberry Pi OS, можда ћете морати да користите `sudo` да бисте покренули ову команду.

    Docker ће изградити слику, конфигуришући сав потребан софтвер. Слика ће бити означена као `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Задатак - постављање контејнера у регистар контејнера

1. Користите следећу команду да поставите свој контејнер у регистар контејнера:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Замените `<Container registry name>` именом које сте користили за ваш регистар контејнера.

    > 💁 Ако користите Linux, можда ћете морати да користите `sudo` да бисте покренули ову команду.

    Контејнер ће бити постављен у регистар контејнера.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Да бисте проверили постављање, можете листати контејнере у вашем регистру помоћу следеће команде:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Замените `<Container registry name>` именом које сте користили за ваш регистар контејнера.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Видећете ваш класификатор у излазним подацима.

## Распоређивање контејнера

Ваш контејнер сада може бити распоређен на ваш IoT Edge уређај. Да бисте га распоредили, потребно је да дефинишете манифест распоређивања - JSON документ који наводи модуле који ће бити распоређени на edge уређај.

### Задатак - креирање манифеста распоређивања

1. Креирајте нову датотеку под називом `deployment.json` негде на вашем рачунару.

1. Додајте следеће у ову датотеку:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Ову датотеку можете пронаћи у фасцикли [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Замените три инстанце `<Container registry name>` именом које сте користили за ваш регистар контејнера. Једна је у секцији `ImageClassifier` модула, а друге две су у секцији `registryCredentials`.

    Замените `<Container registry password>` у секцији `registryCredentials` лозинком вашег регистра контејнера.

1. Из фасцикле која садржи ваш манифест распоређивања, покрените следећу команду:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Замените `<hub_name>` именом вашег IoT Hub-а.

    Модул класификатора слика ће бити распоређен на ваш edge уређај.

### Задатак - проверите да ли класификатор ради

1. Повежите се са IoT edge уређајем:

    * Ако користите Raspberry Pi за покретање IoT Edge-а, повежите се преко ssh-а било из вашег терминала или преко удаљене SSH сесије у VS Code-у.
    * Ако покрећете IoT Edge у Linux контејнеру на Windows-у, пратите кораке у [водичу за проверу успешне конфигурације](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) да бисте се повезали са IoT Edge уређајем.
    * Ако покрећете IoT Edge на виртуелној машини, можете се SSH-ом повезати на машину користећи `adminUsername` и `password` које сте поставили приликом креирања VM-а, и користећи IP адресу или DNS име:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Или:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Унесите своју лозинку када се то затражи.

1. Када сте повезани, покрените следећу команду да бисте добили листу IoT Edge модула:

    ```sh
    iotedge list
    ```

    > 💁 Можда ћете морати да покренете ову команду са `sudo`.

    Видећете покренуте модуле:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Проверите логове за модул класификатора слика помоћу следеће команде:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Можда ћете морати да покренете ову команду са `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Задатак - тестирање класификатора слика

1. Можете користити CURL за тестирање класификатора слика користећи IP адресу или име хоста рачунара који покреће IoT Edge агент. Пронађите IP адресу:

    * Ако сте на истом рачунару на којем је IoT Edge покренут, можете користити `localhost` као име хоста.
    * Ако користите VM, можете користити IP адресу или DNS име VM-а.
    * У супротном, можете добити IP адресу рачунара који покреће IoT Edge:
      * На Windows 10, пратите [водич за проналажење IP адресе](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * На macOS, пратите [водич за проналажење IP адресе на Mac-у](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * На Linux-у, пратите секцију о проналажењу приватне IP адресе у [водичу за проналажење IP адресе у Linux-у](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Можете тестирати контејнер са локалном датотеком покретањем следеће CURL команде:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Замените `<IP address or name>` IP адресом или именом хоста рачунара који покреће IoT Edge. Замените `<file_Name>` именом датотеке за тестирање.

    Видећете резултате предвиђања у излазним подацима:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Овде није потребно обезбедити кључ за предвиђање, јер се не користи Azure ресурс. Уместо тога, безбедност би била конфигурисана на интерној мрежи на основу интерних потреба за безбедношћу, а не ослањајући се на јавну тачку и API кључ.

## Коришћење вашег IoT Edge уређаја

Сада када је класификатор слика распоређен на IoT Edge уређај, можете га користити са вашег IoT уређаја.

### Задатак - коришћење вашег IoT Edge уређаја

Прођите кроз релевантни водич за класификацију слика користећи IoT Edge класификатор:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Рачунар са једном плочом - Raspberry Pi/Виртуелни IoT уређај](single-board-computer.md)

### Поновно обучавање модела

Један од недостатака покретања класификатора слика на IoT Edge-у је то што нису повезани са вашим Custom Vision пројектом. Ако погледате картицу **Predictions** у Custom Vision-у, нећете видети слике које су класификоване користећи класификатор заснован на Edge-у.

Ово је очекивано понашање - слике се не шаљу у облак ради класификације, па неће бити доступне у облаку. Једна од предности коришћења IoT Edge-а је приватност, осигуравајући да слике не напуштају вашу мрежу, друга је могућност рада офлајн, без ослањања на отпремање слика када уређај нема интернет везу. Недостатак је побољшање вашег модела - потребно је имплементирати други начин чувања слика које могу бити ручно рекласификоване ради побољшања и поновног обучавања класификатора слика.

✅ Размислите о начинима за отпремање слика ради поновног обучавања класификатора.

---

## 🚀 Изазов

Покретање AI модела на edge уређајима може бити брже него у облаку - мрежни скок је краћи. Може бити и спорије јер хардвер који покреће модел можда није толико моћан као облак.

Урадите мерења и упоредите да ли је позив вашем edge уређају бржи или спорији од позива облаку? Размислите о разлозима који објашњавају разлику или недостатак разлике. Истражите начине за брже покретање AI модела на edge-у користећи специјализовани хардвер.

## Квиз након предавања

[Квиз након предавања](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Преглед и самостално учење

* Прочитајте више о контејнерима на [страници о виртуализацији на нивоу оперативног система на Википедији](https://wikipedia.org/wiki/OS-level_virtualization).
* Прочитајте више о edge рачунарству, са нагласком на то како 5G може помоћи у проширењу edge рачунарства у [чланку "Шта је edge рачунарство и зашто је важно?" на NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Сазнајте више о покретању AI услуга на IoT Edge гледајући [епизоду "Научите како да користите Azure IoT Edge на унапред припремљеној AI услузи на Edge-у за детекцију језика" из серије Learn Live на Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Задатак

[Покрените друге услуге на edge-у](assignment.md)

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако тежимо тачности, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не сносимо одговорност за било каква неспоразумевања или погрешна тумачења која могу произаћи из коришћења овог превода.