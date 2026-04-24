# Мигрирајте логику ваше апликације у облак

![Преглед лекције у облику скице](../../../../../translated_images/sr/lesson-9.dfe99c8e891f48e1.webp)

> Скица од [Nitya Narasimhan](https://github.com/nitya). Кликните на слику за већу верзију.

Ова лекција је део [IoT for Beginners Project 2 - серије о дигиталној пољопривреди](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) из [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Контролишите свој IoT уређај помоћу серверлес кода](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Квиз пре предавања

[Квиз пре предавања](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Увод

У претходној лекцији научили сте како да повежете мониторинг влаге у земљишту и контролу релеја са IoT услугом у облаку. Следећи корак је премештање серверског кода који контролише тајминг релеја у облак. У овој лекцији ћете научити како да то урадите користећи серверлес функције.

У овој лекцији обрадићемо:

* [Шта је серверлес?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Креирање серверлес апликације](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Креирање IoT Hub тригера за догађаје](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Слање директних захтева из серверлес кода](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Деплој вашег серверлес кода у облак](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Шта је серверлес?

Серверлес, или серверлес рачунарство, подразумева креирање малих блокова кода који се извршавају у облаку као одговор на различите врсте догађаја. Када се догађај догоди, ваш код се извршава и добија податке о догађају. Ови догађаји могу бити различити, укључујући веб захтеве, поруке постављене у ред, промене података у бази или поруке које IoT уређаји шаљу IoT услузи.

![Догађаји који се шаљу из IoT услуге серверлес услузи, сви се обрађују истовремено од стране више функција](../../../../../translated_images/sr/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Ако сте раније користили тригере у базама података, можете ово замислити као сличан концепт - код који се активира догађајем, као што је убацивање реда.

![Када се више догађаја пошаље истовремено, серверлес услуга се скалира да их све обради истовремено](../../../../../translated_images/sr/serverless-scaling.f8c769adf0413fd1.webp)

Ваш код се извршава само када се догађај догоди, а у другим временима није активан. Догађај се догоди, ваш код се учитава и извршава. Ово чини серверлес веома скалабилним - ако се много догађаја догоди истовремено, провајдер облака може извршити вашу функцију онолико пута колико је потребно истовремено на доступним серверима. Недостатак овог модела је што, ако треба да делите информације између догађаја, морате их сачувати негде, као у бази података, уместо да их чувате у меморији.

Ваш код је написан као функција која узима детаље о догађају као параметар. Можете користити широк спектар програмских језика за писање ових серверлес функција.

> 🎓 Серверлес се такође назива Функције као услуга (FaaS), јер се сваки тригер догађаја имплементира као функција у коду.

Упркос називу, серверлес заправо користи сервере. Назив потиче од тога што као програмер не морате да бринете о серверима потребним за извршавање вашег кода, већ само о томе да се ваш код извршава као одговор на догађај. Провајдер облака има серверлес *окружење* које управља алокацијом сервера, мрежом, складиштем, процесорима, меморијом и свим осталим потребним за извршавање вашег кода. У овом моделу не плаћате по серверу, већ плаћате за време извршавања вашег кода и количину коришћене меморије.

> 💰 Серверлес је један од најјефтинијих начина за извршавање кода у облаку. На пример, у време писања, један провајдер облака дозвољава да се све ваше серверлес функције изврше укупно 1.000.000 пута месечно пре него што почну да вам наплаћују, а након тога наплаћују 0,20 УСД за сваких 1.000.000 извршења. Када ваш код није активан, не плаћате ништа.

Као IoT програмер, серверлес модел је идеалан. Можете написати функцију која се позива као одговор на поруке послате са било ког IoT уређаја који је повезан са вашом IoT услугом хостираном у облаку. Ваш код ће обрађивати све послате поруке, али ће бити активан само када је потребно.

✅ Погледајте код који сте написали као серверски код који слуша поруке преко MQTT-а. Како би се овај код могао извршавати у облаку користећи серверлес? Како мислите да би код могао бити промењен да подржи серверлес рачунарство?

> 💁 Серверлес модел се шири на друге услуге у облаку поред извршавања кода. На пример, серверлес базе података су доступне у облаку користећи серверлес модел наплате, где плаћате по захтеву направљеном према бази података, као што је упит или убацивање, обично на основу количине посла потребног за обраду захтева. На пример, једноставан селект једног реда према примарном кључу коштаће мање од сложене операције која спаја више табела и враћа хиљаде редова.

## Креирање серверлес апликације

Серверлес услуга за рачунарство од Microsoft-а назива се Azure Functions.

![Лого Azure Functions](../../../../../translated_images/sr/azure-functions-logo.1cfc8e3204c9c44a.webp)

Кратак видео испод даје преглед Azure Functions.

[![Преглед Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Кликните на слику изнад да бисте погледали видео.

✅ Одвојите тренутак да истражите и прочитате преглед Azure Functions у [документацији Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Да бисте писали Azure Functions, потребно је да започнете са Azure Functions апликацијом у језику по вашем избору. Azure Functions подржава Python, JavaScript, TypeScript, C#, F#, Java и Powershell. У овој лекцији ћете научити како да напишете Azure Functions апликацију у Python-у.

> 💁 Azure Functions такође подржава прилагођене хендлере, тако да можете писати функције у било ком језику који подржава HTTP захтеве, укључујући старије језике као што је COBOL.

Апликације функција се састоје од једног или више *тригера* - функција које реагују на догађаје. Можете имати више тригера унутар једне апликације функција, које деле заједничку конфигурацију. На пример, у конфигурационом фајлу ваше апликације функција можете имати детаље о повезивању са вашим IoT Hub-ом, а све функције у апликацији могу користити ове детаље за повезивање и слушање догађаја.

### Задатак - инсталирање алата за Azure Functions

> У време писања, алати за Azure Functions нису у потпуности функционални на Apple Silicon у Python пројектима. Мораћете да користите Mac са Intel процесором, Windows PC или Linux PC.

Једна од одличних карактеристика Azure Functions је да их можете покренути локално. Исто окружење које се користи у облаку може се покренути на вашем рачунару, омогућавајући вам да пишете код који реагује на IoT поруке и да га покренете локално. Можете чак и дебаговати ваш код док се догађаји обрађују. Када будете задовољни кодом, можете га деплојовати у облак.

CLI алат за Azure Functions, познат као Azure Functions Core Tools, доступан је за инсталацију.

1. Инсталирајте Azure Functions Core Tools пратећи упутства у [документацији Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Инсталирајте Azure Functions екстензију за VS Code. Ова екстензија пружа подршку за креирање, дебаговање и деплојовање Azure функција. Погледајте [документацију за Azure Functions екстензију](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) за упутства о инсталацији ове екстензије у VS Code.

Када деплојујете вашу Azure Functions апликацију у облак, она мора користити малу количину облачног складишта за чување ствари као што су фајлови апликације и логови. Када покренете вашу апликацију функција локално, и даље морате да се повежете са облачним складиштем, али уместо стварног облачног складишта, можете користити емулатор складишта назван [Azurite](https://github.com/Azure/Azurite). Овај емулатор ради локално, али се понаша као облачно складиште.

> 🎓 У Azure-у, складиште које Azure Functions користи је Azure Storage Account. Ови налози могу чувати фајлове, блобове, податке у табелама или податке у редовима. Можете делити један Storage Account између више апликација, као што су апликација функција и веб апликација.

1. Azurite је Node.js апликација, па ћете морати да инсталирате Node.js. Можете пронаћи упутства за преузимање и инсталацију на [Node.js вебсајту](https://nodejs.org/). Ако користите Mac, можете га инсталирати и преко [Homebrew](https://formulae.brew.sh/formula/node).

1. Инсталирајте Azurite користећи следећу команду (`npm` је алат који се инсталира са Node.js):

    ```sh
    npm install -g azurite
    ```

1. Креирајте фасциклу названу `azurite` коју Azurite може користити за чување података:

    ```sh
    mkdir azurite
    ```

1. Покрените Azurite, прослеђујући му ову нову фасциклу:

    ```sh
    azurite --location azurite
    ```

    Azurite емулатор складишта ће се покренути и бити спреман за повезивање са локалним окружењем функција.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Задатак - креирање Azure Functions пројекта

CLI алат за Azure Functions може се користити за креирање нове апликације функција.

1. Креирајте фасциклу за вашу апликацију функција и пређите у њу. Назовите је `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Креирајте Python виртуелно окружење унутар ове фасцикле:

    ```sh
    python3 -m venv .venv
    ```

1. Активирајте виртуелно окружење:

    * На Windows-у:
        * Ако користите Command Prompt или Command Prompt кроз Windows Terminal, покрените:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ако користите PowerShell, покрените:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * На macOS-у или Linux-у, покрените:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ове команде треба покренути из исте локације на којој сте покренули команду за креирање виртуелног окружења. Никада нећете морати да улазите у `.venv` фасциклу; увек треба да покренете команду за активирање и било које команде за инсталацију пакета или покретање кода из фасцикле у којој сте креирали виртуелно окружење.

1. Покрените следећу команду да бисте креирали апликацију функција у овој фасцикли:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Ово ће креирати три фајла унутар тренутне фасцикле:

    * `host.json` - овај JSON документ садржи подешавања за вашу апликацију функција. Нећете морати да мењате ова подешавања.
    * `local.settings.json` - овај JSON документ садржи подешавања која ваша апликација користи када се покреће локално, као што су конекциони стрингови за ваш IoT Hub. Ова подешавања су само локална и не треба их додавати у контролу верзија. Када деплојујете апликацију у облак, ова подешавања се не деплојују; уместо тога, ваша подешавања се учитавају из апликационих подешавања. Ово ће бити обрађено касније у лекцији.
    * `requirements.txt` - ово је [Pip фајл захтева](https://pip.pypa.io/en/stable/user_guide/#requirements-files) који садржи Pip пакете потребне за покретање ваше апликације функција.

1. Фајл `local.settings.json` има подешавање за Storage Account који апликација функција користи. Ово подразумевано има празно подешавање, па га треба поставити. Да бисте се повезали са локалним Azurite емулатором складишта, поставите ову вредност на следеће:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Инсталирајте потребне Pip пакете користећи фајл захтева:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Потребни Pip пакети морају бити у овом фајлу, тако да када се апликација функција деплојује у облак, окружење може осигурати да инсталира исправне пакете.

1. Да бисте тестирали да ли све ради исправно, можете покренути окружење функција. Покрените следећу команду:

    ```sh
    func start
    ```

    Видећете да се окружење покреће и извештава да није пронашло ниједну функцију (тригере).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Ако добијете обавештење о заштитном зиду, одобрите приступ јер апликација `func` мора имати могућност читања и писања на вашој мрежи.
> ⚠️ Ако користите macOS, могу се појавити упозорења у излазним подацима:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Можете их игнорисати све док се апликација Functions правилно покреће и приказује активне функције. Као што је наведено у [овом питању на Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), ово упозорење може бити занемарено.

1. Зауставите апликацију Functions притиском на `ctrl+c`.

1. Отворите тренутни директоријум у VS Code, било тако што ћете отворити VS Code па затим овај директоријум, или покретањем следеће команде:

    ```sh
    code .
    ```

    VS Code ће препознати ваш Functions пројекат и приказати обавештење које гласи:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Обавештење](../../../../../translated_images/sr/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Изаберите **Yes** у овом обавештењу.

1. Уверите се да је Python виртуелно окружење покренуто у терминалу VS Code-а. Зауставите га и поново покрените ако је потребно.

## Креирање тригера за догађаје IoT Hub-а

Апликација Functions је оквир за ваш серверлес код. Да бисте реаговали на догађаје IoT Hub-а, можете додати тригер за IoT Hub у ову апликацију. Овај тригер треба да се повеже са током порука које се шаљу IoT Hub-у и да реагује на њих. Да бисте добили овај ток порука, ваш тригер треба да се повеже са *event hub compatible endpoint*-ом IoT Hub-а.

IoT Hub се заснива на другој Azure услузи која се зове Azure Event Hubs. Event Hubs је услуга која омогућава слање и примање порука, а IoT Hub проширује ову функционалност додавањем карактеристика за IoT уређаје. Начин на који се повезујете да бисте читали поруке са IoT Hub-а је исти као када бисте користили Event Hubs.

✅ Урадите мало истраживања: Прочитајте преглед Event Hubs-а у [документацији Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Како се основне карактеристике упоређују са IoT Hub-ом?

Да би се IoT уређај повезао са IoT Hub-ом, мора да користи тајни кључ који осигурава да само дозвољени уређаји могу да се повежу. Исто важи и када се повезујете да бисте читали поруке; ваш код ће требати стринг за повезивање који садржи тајни кључ, као и детаље о IoT Hub-у.

> 💁 Подразумевани стринг за повезивање који добијате има **iothubowner** дозволе, што омогућава било ком коду који га користи пуне дозволе на IoT Hub-у. Идеално би било да се повежете са најнижом потребном нивоу дозвола. Ово ће бити обрађено у следећем лекцији.

Када се ваш тригер повеже, код унутар функције ће бити позван за сваку поруку послату IoT Hub-у, без обзира који уређај је послао поруку. Тригер ће примити поруку као параметар.

### Задатак - добијање стринга за повезивање са Event Hub compatible endpoint-ом

1. Из терминала VS Code-а покрените следећу команду да бисте добили стринг за повезивање са Event Hub compatible endpoint-ом IoT Hub-а:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Замените `<hub_name>` именом које сте користили за ваш IoT Hub.

1. У VS Code-у, отворите датотеку `local.settings.json`. Додајте следећу додатну вредност унутар секције `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Замените `<connection string>` вредношћу из претходног корака. Мораћете да додате зарез након претходне линије да би ово било валидан JSON.

### Задатак - креирање тригера за догађаје

Сада сте спремни да креирате тригер за догађаје.

1. Из терминала VS Code-а покрените следећу команду из директоријума `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Ово креира нову функцију названу `iot-hub-trigger`. Тригер ће се повезати са Event Hub compatible endpoint-ом на IoT Hub-у, тако да можете користити тригер за Event Hub. Не постоји специфичан тригер за IoT Hub.

Ово ће креирати директоријум унутар `soil-moisture-trigger` директоријума назван `iot-hub-trigger` који садржи ову функцију. Овај директоријум ће имати следеће датотеке унутар:

* `__init__.py` - ово је Python датотека која садржи тригер, користећи стандардну Python конвенцију именовања датотека да би овај директоријум постао Python модул.

    Ова датотека ће садржати следећи код:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Језгро тригера је функција `main`. Ова функција се позива са догађајима из IoT Hub-а. Функција има параметар назван `event` који садржи `EventHubEvent`. Сваки пут када се порука пошаље IoT Hub-у, ова функција се позива и прослеђује ту поруку као `event`, заједно са својствима која су иста као и анотације које сте видели у претходној лекцији.

    Језгро ове функције бележи догађај.

* `function.json` - ово садржи конфигурацију за тригер. Главна конфигурација је у секцији названој `bindings`. Binding је термин за везу између Azure Functions и других Azure услуга. Ова функција има улазни binding за Event Hub - повезује се са Event Hub-ом и прима податке.

    > 💁 Можете такође имати излазне binding-е тако да се излаз функције шаље другој услузи. На пример, могли бисте додати излазни binding за базу података и вратити догађај IoT Hub-а из функције, и он ће бити аутоматски уметнут у базу података.

    ✅ Урадите мало истраживања: Прочитајте о binding-има у [документацији о концептима Azure Functions тригера и binding-а](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Секција `bindings` укључује конфигурацију за binding. Вредности од интереса су:

  * `"type": "eventHubTrigger"` - ово говори функцији да треба да слуша догађаје из Event Hub-а
  * `"name": "events"` - ово је име параметра за догађаје Event Hub-а. Ово одговара имену параметра у функцији `main` у Python коду.
  * `"direction": "in"` - ово је улазни binding, подаци из Event Hub-а долазе у функцију
  * `"connection": ""` - ово дефинише име подешавања из којег се чита стринг за повезивање. Када се покреће локално, ово ће читати ово подешавање из датотеке `local.settings.json`.

    > 💁 Стринг за повезивање не може бити сачуван у датотеци `function.json`, мора бити прочитан из подешавања. Ово је да бисте спречили случајно излагање вашег стринга за повезивање.

1. Због [грешке у Azure Functions шаблону](https://github.com/Azure/azure-functions-templates/issues/1250), `function.json` има нетачну вредност за поље `cardinality`. Ажурирајте ово поље са `many` на `one`:

    ```json
    "cardinality": "one",
    ```

1. Ажурирајте вредност `"connection"` у датотеци `function.json` да указује на нову вредност коју сте додали у датотеку `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Запамтите - ово треба да указује на подешавање, а не да садржи стварни стринг за повезивање.

1. Стринг за повезивање садржи вредност `eventHubName`, тако да вредност за ово у датотеци `function.json` треба да буде празан стринг. Ажурирајте ову вредност на празан стринг:

    ```json
    "eventHubName": "",
    ```

### Задатак - покретање тригера за догађаје

1. Уверите се да не покрећете монитор догађаја IoT Hub-а. Ако је ово покренуто истовремено са апликацијом Functions, апликација Functions неће моћи да се повеже и конзумира догађаје.

    > 💁 Више апликација може да се повеже са IoT Hub endpoint-има користећи различите *consumer groups*. Ово ће бити обрађено у каснијој лекцији.

1. Да бисте покренули апликацију Functions, покрените следећу команду из терминала VS Code-а:

    ```sh
    func start
    ```

    Апликација Functions ће се покренути и открити функцију `iot-hub-trigger`. Затим ће обрадити све догађаје који су већ послати IoT Hub-у у последњих дан.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Сваки позив функције ће бити окружен блоком `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` у излазним подацима, тако да можете видети колико је порука обрађено у сваком позиву функције.

1. Уверите се да ваш IoT уређај ради. Видећете нове поруке о влажности земљишта које се појављују у апликацији Functions.

1. Зауставите и поново покрените апликацију Functions. Видећете да неће поново обрађивати претходне поруке, већ само нове поруке.

> 💁 VS Code такође подржава дебаговање ваших Functions. Можете поставити тачке прекида кликом на границу поред почетка сваке линије кода, или постављањем курсора на линију кода и избором *Run -> Toggle breakpoint*, или притиском на `F9`. Можете покренути дебагер избором *Run -> Start debugging*, притиском на `F5`, или избором панела *Run and debug* и избором дугмета **Start debugging**. На овај начин можете видети детаље о догађајима који се обрађују.

#### Решавање проблема

* Ако добијете следећу грешку:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Проверите да ли је Azurite покренут и да ли сте поставили `AzureWebJobsStorage` у датотеци `local.settings.json` на `UseDevelopmentStorage=true`.

* Ако добијете следећу грешку:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Проверите да ли сте поставили `cardinality` у датотеци `function.json` на `one`.

* Ако добијете следећу грешку:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Проверите да ли сте поставили `eventHubName` у датотеци `function.json` на празан стринг.

## Слање захтева за директне методе из серверлес кода

До сада ваша апликација Functions слуша поруке са IoT Hub-а користећи Event Hub compatible endpoint. Сада треба да шаљете команде IoT уређају. Ово се ради коришћењем другачије везе са IoT Hub-ом преко *Registry Manager*-а. Registry Manager је алат који вам омогућава да видите који су уређаји регистровани на IoT Hub-у и комуницирате са тим уређајима слањем порука од облака ка уређају, захтева за директне методе или ажурирањем device twin-а. Такође га можете користити за регистрацију, ажурирање или брисање IoT уређаја са IoT Hub-а.

Да бисте се повезали са Registry Manager-ом, потребан вам је стринг за повезивање.

### Задатак - добијање стринга за повезивање са Registry Manager-ом

1. Да бисте добили стринг за повезивање, покрените следећу команду:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Замените `<hub_name>` именом које сте користили за ваш IoT Hub.

    Стринг за повезивање се захтева за *ServiceConnect* политику користећи параметар `--policy-name service`. Када захтевате стринг за повезивање, можете одредити које дозволе тај стринг за повезивање омогућава. ServiceConnect политика омогућава вашем коду да се повеже и шаље поруке IoT уређајима.

    ✅ Урадите мало истраживања: Прочитајте о различитим политикама у [документацији о дозволама IoT Hub-а](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. У VS Code-у, отворите датотеку `local.settings.json`. Додајте следећу додатну вредност унутар секције `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Замените `<connection string>` вредношћу из претходног корака. Мораћете да додате зарез након претходне линије да би ово било валидан JSON.

### Задатак - слање захтева за директну методу уређају

1. SDK за Registry Manager је доступан преко Pip пакета. Додајте следећу линију у датотеку `requirements.txt` да бисте додали зависност од овог пакета:

    ```sh
    azure-iot-hub
    ```

1. Уверите се да је терминал VS Code-а активирао виртуелно окружење и покрените следећу команду да бисте инсталирали Pip пакете:

    ```sh
    pip install -r requirements.txt
    ```

1. Додајте следеће увозе у датотеку `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Ово увози неке системске библиотеке, као и библиотеке за интеракцију са Registry Manager-ом и слање захтева за директне методе.

1. Уклоните код изнутар методе `main`, али задржите саму методу.

1. У методи `main`, додајте следећи код:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Овај код извлачи тело догађаја које садржи JSON поруку послату од IoT уређаја.

    Затим добија ID уређаја из анотација прослеђених са поруком. Тело догађаја садржи поруку послату као телеметрију, а речник `iothub_metadata` садржи својства постављена од IoT Hub-а као што су ID уређаја пошиљаоца и време када је порука послата.

    Ове информације се затим бележе. Видећете ово бележење у терминалу када локално покренете апликацију Function.

1. Испод овога, додајте следећи код:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Овај код добија вредност влажности земљишта из поруке. Затим проверава влажност земљишта и, у зависности од вредности, креира помоћну класу за захтев за директну методу `relay_on` или `relay_off`. Захтев за методу не треба payload, тако да се шаље празан JSON документ.

1. Испод овога додајте следећи код:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Овај код учитава `REGISTRY_MANAGER_CONNECTION_STRING` из датотеке `local.settings.json`. Вредности у овој датотеци су доступне као променљиве окружења, и могу се читати помоћу функције `os.environ`, која враћа речник свих променљивих окружења.

> 💁 Када се овај код постави у облак, вредности из датотеке `local.settings.json` биће постављене као *Application Settings*, и могу се читати из променљивих окружења.

Код затим креира инстанцу помоћне класе Registry Manager користећи конекциони стринг.

1. Испод овога додајте следећи код:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Овај код упућује Registry Manager да пошаље директан методски захтев уређају који је послао телеметрију.

    > 💁 У верзијама апликације које сте креирали у претходним лекцијама користећи MQTT, команде за контролу релеја су слате свим уређајима. Код је претпостављао да имате само један уређај. Ова верзија кода шаље методски захтев само једном уређају, тако да би функционисала ако имате више поставки сензора влаге и релеја, шаљући прави директан методски захтев правом уређају.

1. Покрените апликацију Functions и уверите се да ваш IoT уређај шаље податке. Видећете да се поруке обрађују и да се директни методски захтеви шаљу. Померите сензор влаге у земљу и ван ње да бисте видели промену вредности и укључивање и искључивање релеја.

> 💁 Овај код можете пронаћи у фасцикли [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Поставите свој серверлес код у облак

Ваш код сада ради локално, па је следећи корак постављање Functions апликације у облак.

### Задатак - креирајте ресурсе у облаку

Ваша Functions апликација треба да буде постављена у Functions App ресурс у Azure-у, који се налази унутар Resource Group коју сте креирали за ваш IoT Hub. Такође ће вам бити потребан Storage Account креиран у Azure-у да замени емулирани који тренутно ради локално.

1. Покрените следећу команду да креирате Storage Account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Замените `<storage_name>` именом за ваш Storage Account. Ово име мора бити глобално јединствено јер је део URL-а који се користи за приступ Storage Account-у. Можете користити само мала слова и бројеве за ово име, без других карактера, и ограничено је на 24 карактера. Користите нешто попут `sms` и додајте јединствени идентификатор на крај, као што су насумичне речи или ваше име.

    Опција `--sku Standard_LRS` бира ниво цена, бирајући најјефтинији општи налог. Не постоји бесплатан ниво складишта, и плаћате за оно што користите. Трошкови су релативно ниски, са најскупљим складиштем мање од 0,05 америчких долара месечно по гигабајту складиштених података.

    ✅ Прочитајте више о ценама на [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Покрените следећу команду да креирате Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Замените `<location>` локацијом коју сте користили приликом креирања Resource Group у претходној лекцији.

    Замените `<storage_name>` именом Storage Account-а који сте креирали у претходном кораку.

    Замените `<functions_app_name>` јединственим именом за вашу Functions App. Ово име мора бити глобално јединствено јер је део URL-а који се користи за приступ Functions App-у. Користите нешто попут `soil-moisture-sensor-` и додајте јединствени идентификатор на крај, као што су насумичне речи или ваше име.

    Опција `--functions-version 3` поставља верзију Azure Functions која ће се користити. Верзија 3 је најновија верзија.

    Опција `--os-type Linux` говори Functions runtime-у да користи Linux као оперативни систем за хостовање ових функција. Functions могу бити хостоване на Linux-у или Windows-у, у зависности од програмског језика који се користи. Python апликације су подржане само на Linux-у.

### Задатак - отпремите своја подешавања апликације

Када сте развијали своју Functions App, сачували сте нека подешавања у датотеци `local.settings.json` за конекционе стрингове за ваш IoT Hub. Ова подешавања треба да буду написана у Application Settings у вашој Functions App у Azure-у како би их ваш код могао користити.

> 🎓 Датотека `local.settings.json` је само за локална подешавања развоја, и не треба да буде укључена у контролу изворног кода, као што је GitHub. Када се постави у облак, користе се Application Settings. Application Settings су парови кључ/вредност хостовани у облаку и читају се из променљивих окружења било у вашем коду или од стране runtime-а када повезује ваш код са IoT Hub-ом.

1. Покрените следећу команду да поставите `IOT_HUB_CONNECTION_STRING` подешавање у Application Settings Functions App-а:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Замените `<functions_app_name>` именом које сте користили за вашу Functions App.

    Замените `<connection string>` вредношћу `IOT_HUB_CONNECTION_STRING` из ваше датотеке `local.settings.json`.

1. Поновите горњи корак, али поставите вредност `REGISTRY_MANAGER_CONNECTION_STRING` на одговарајућу вредност из ваше датотеке `local.settings.json`.

Када покренете ове команде, оне ће такође приказати листу свих Application Settings за функцију апликације. Можете користити ово да проверите да ли су ваше вредности правилно постављене.

> 💁 Видећете вредност која је већ постављена за `AzureWebJobsStorage`. У вашој датотеци `local.settings.json`, ово је било постављено на вредност за коришћење локалног емулираног складишта. Када сте креирали Functions App, прослеђујете Storage Account као параметар, и ово се аутоматски поставља у ово подешавање.

### Задатак - поставите своју Functions App у облак

Сада када је Functions App спремна, ваш код може бити постављен.

1. Покрените следећу команду из терминала у VS Code-у да објавите своју Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Замените `<functions_app_name>` именом које сте користили за вашу Functions App.

Код ће бити упакован и послат Functions App-у, где ће бити постављен и покренут. Биће пуно излазних података у конзоли, који се завршавају потврдом о постављању и листом постављених функција. У овом случају листа ће садржати само тригер.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Уверите се да ваш IoT уређај ради. Промените нивое влаге подешавањем влаге у земљи или померањем сензора у земљу и ван ње. Видећете да се релеј укључује и искључује како се ниво влаге мења.

---

## 🚀 Изазов

У претходној лекцији, управљали сте временом за релеј тако што сте се одјављивали са MQTT порука док је релеј био укључен, и кратко време након што је искључен. Овде не можете користити овај метод - не можете се одјавити са IoT Hub тригера.

Размислите о различитим начинима на које бисте могли да решите ово у вашој Functions App.

## Квиз након предавања

[Квиз након предавања](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Преглед и самостално учење

* Прочитајте више о серверлес рачунарству на [Serverless Computing страници на Википедији](https://wikipedia.org/wiki/Serverless_computing)
* Прочитајте о коришћењу серверлес-а у Azure-у, укључујући још неке примере, на [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Сазнајте више о Azure Functions на [Azure Functions YouTube каналу](https://www.youtube.com/c/AzureFunctions)

## Задатак

[Додајте ручну контролу релеја](assignment.md)

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.