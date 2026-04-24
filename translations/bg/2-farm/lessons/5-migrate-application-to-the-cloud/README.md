# Мигрирайте логиката на вашето приложение към облака

![Скица на урока](../../../../../translated_images/bg/lesson-9.dfe99c8e891f48e1.webp)

> Скица от [Nitya Narasimhan](https://github.com/nitya). Кликнете върху изображението за по-голяма версия.

Този урок беше част от [IoT за начинаещи Проект 2 - Серия за дигитално земеделие](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) от [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Контролирайте вашето IoT устройство със serverless код](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Тест преди урока

[Тест преди урока](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Въведение

В предишния урок научихте как да свържете вашия мониторинг на влажността на почвата и управление на реле към облачна IoT услуга. Следващата стъпка е да преместите сървърния код, който контролира времето на релето, в облака. В този урок ще научите как да направите това, използвайки serverless функции.

В този урок ще разгледаме:

* [Какво е serverless?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Създаване на serverless приложение](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Създаване на IoT Hub тригер](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Изпращане на директни заявки от serverless код](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Деплой на вашия serverless код в облака](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Какво е serverless?

Serverless, или serverless изчисления, включва създаването на малки блокове код, които се изпълняват в облака в отговор на различни видове събития. Когато събитието се случи, вашият код се изпълнява и получава данни за събитието. Тези събития могат да бъдат от различни източници, включително уеб заявки, съобщения в опашка, промени в база данни или съобщения, изпратени към IoT услуга от IoT устройства.

![Събития, изпратени от IoT услуга към serverless услуга, обработвани едновременно от множество функции](../../../../../translated_images/bg/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Ако сте използвали тригери в база данни, можете да мислите за това като за нещо подобно – код, който се задейства от събитие, като например добавяне на ред.

![Когато много събития се изпратят едновременно, serverless услугата се мащабира, за да ги обработи всички едновременно](../../../../../translated_images/bg/serverless-scaling.f8c769adf0413fd1.webp)

Вашият код се изпълнява само когато събитието се случи, а през останалото време не е активен. Това прави serverless много мащабируемо – ако много събития се случат едновременно, облачният доставчик може да изпълни вашата функция толкова пъти, колкото е необходимо, на различни налични сървъри. Недостатъкът е, че ако трябва да споделяте информация между събитията, трябва да я съхранявате някъде, например в база данни, вместо в паметта.

Вашият код се пише като функция, която приема детайли за събитието като параметър. Можете да използвате широк набор от програмни езици за писане на тези serverless функции.

> 🎓 Serverless често се нарича Functions as a Service (FaaS), тъй като всяко събитие се имплементира като функция в кода.

Въпреки името, serverless всъщност използва сървъри. Името идва от това, че като разработчик не се интересувате от сървърите, необходими за изпълнението на вашия код – важното е, че кодът ви се изпълнява в отговор на събитие. Облачният доставчик има serverless *runtime*, който управлява разпределението на сървъри, мрежи, съхранение, CPU, памет и всичко останало, необходимо за изпълнението на вашия код. Това означава, че не плащате за сървър, а за времето, през което кодът ви се изпълнява, и за използваната памет.

> 💰 Serverless е един от най-евтините начини за изпълнение на код в облака. Например, към момента на писане, един облачен доставчик позволява всички ваши serverless функции да се изпълняват общо 1,000,000 пъти месечно безплатно, а след това таксува $0.20 за всеки 1,000,000 изпълнения. Когато кодът ви не се изпълнява, не плащате.

Като IoT разработчик, serverless моделът е идеален. Можете да напишете функция, която се извиква в отговор на съобщения, изпратени от всяко IoT устройство, свързано към вашата облачна IoT услуга. Вашият код ще обработва всички изпратени съобщения, но ще се изпълнява само когато е необходимо.

✅ Върнете се към кода, който написахте като сървърен код за слушане на съобщения през MQTT. Как мислите, че този код може да се изпълнява в облака, използвайки serverless? Какви промени може да са необходими, за да поддържа serverless изчисления?

> 💁 Serverless моделът се разширява и към други облачни услуги освен изпълнението на код. Например, в облака са налични serverless бази данни с модел на ценообразуване, базиран на заявките към базата данни, като заявки за селекция или вмъкване. Цената обикновено зависи от сложността на заявката – например, селекция на един ред по първичен ключ ще струва по-малко от сложна операция с множество таблици и хиляди редове.

## Създаване на serverless приложение

Услугата за serverless изчисления от Microsoft се нарича Azure Functions.

![Лого на Azure Functions](../../../../../translated_images/bg/azure-functions-logo.1cfc8e3204c9c44a.webp)

Краткото видео по-долу предоставя преглед на Azure Functions.

[![Преглед на Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Кликнете върху изображението, за да гледате видеото.

✅ Отделете време да направите проучване и прочетете прегледа на Azure Functions в [документацията на Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

За да пишете Azure Functions, започвате с приложение за Azure Functions на избрания от вас език. Azure Functions поддържа Python, JavaScript, TypeScript, C#, F#, Java и Powershell. В този урок ще научите как да напишете приложение за Azure Functions на Python.

> 💁 Azure Functions също поддържа персонализирани обработчици, така че можете да пишете функции на всеки език, който поддържа HTTP заявки, включително по-стари езици като COBOL.

Приложенията за функции се състоят от една или повече *тригери* – функции, които реагират на събития. Можете да имате множество тригери в едно приложение, като всички споделят обща конфигурация. Например, в конфигурационния файл на вашето приложение можете да зададете детайли за връзка с вашия IoT Hub, които всички функции в приложението могат да използват.

### Задача - инсталиране на инструментите за Azure Functions

> Към момента на писане, инструментите за Azure Functions не работят напълно на Apple Silicon с Python проекти. Ще трябва да използвате Mac с Intel, Windows PC или Linux PC.

Една от страхотните функции на Azure Functions е, че можете да ги изпълнявате локално. Същата среда за изпълнение, която се използва в облака, може да се стартира на вашия компютър, което ви позволява да пишете код, който реагира на IoT съобщения, и да го тествате локално. Можете дори да дебъгвате кода си, докато се обработват събития. След като сте доволни от кода си, можете да го деплойнете в облака.

Инструментите за Azure Functions са налични като CLI, известен като Azure Functions Core Tools.

1. Инсталирайте Azure Functions Core Tools, следвайки инструкциите в [документацията за Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Инсталирайте разширението за Azure Functions за VS Code. Това разширение предоставя поддръжка за създаване, дебъгване и деплой на Azure Functions. Вижте [документацията за разширението за Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) за инструкции как да го инсталирате.

Когато деплойнете приложението си в облака, то ще използва малко количество облачно съхранение за съхранение на файлове и логове. Когато изпълнявате приложението локално, можете да използвате емулатор за съхранение, наречен [Azurite](https://github.com/Azure/Azurite), който действа като облачно съхранение.

> 🎓 В Azure, съхранението, което Azure Functions използва, е акаунт за съхранение. Тези акаунти могат да съхраняват файлове, данни в таблици или опашки. Можете да споделяте един акаунт между различни приложения.

1. Azurite е Node.js приложение, така че ще трябва да инсталирате Node.js. Можете да намерите инструкции за инсталация на [уебсайта на Node.js](https://nodejs.org/).

1. Инсталирайте Azurite с командата:

    ```sh
    npm install -g azurite
    ```

1. Създайте папка `azurite` за съхранение на данни:

    ```sh
    mkdir azurite
    ```

1. Стартирайте Azurite, като посочите новата папка:

    ```sh
    azurite --location azurite
    ```

    Azurite ще се стартира и ще бъде готов за връзка с локалната среда за изпълнение.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Задача - създаване на проект за Azure Functions

CLI за Azure Functions може да се използва за създаване на ново приложение.

1. Създайте папка за приложението и навигирайте до нея. Наречете я `soil-moisture-trigger`:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Създайте Python виртуална среда в тази папка:

    ```sh
    python3 -m venv .venv
    ```

1. Активирайте виртуалната среда:

    * В Windows:
        * Ако използвате Command Prompt, изпълнете:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ако използвате PowerShell, изпълнете:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * В macOS или Linux, изпълнете:

        ```cmd
        source ./.venv/bin/activate
        ```

1. Създайте приложение за функции в тази папка:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Това ще създаде три файла:

    * `host.json` - съдържа настройки за приложението.
    * `local.settings.json` - съдържа локални настройки, като връзки към IoT Hub.
    * `requirements.txt` - файл с необходимите Pip пакети.

1. Актуализирайте `local.settings.json`, за да се свърже с Azurite:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Инсталирайте необходимите Pip пакети:

    ```sh
    pip install -r requirements.txt
    ```

1. Стартирайте средата за изпълнение, за да тествате:

    ```sh
    func start
    ```

    Ще видите, че средата се стартира и съобщава, че не са намерени функции.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Ако получите известие от защитната стена, дайте достъп, тъй като приложението `func` трябва да може да чете и записва в мрежата ви.
> ⚠️ Ако използвате macOS, може да се появят предупреждения в изхода:
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
> Можете да ги игнорирате, стига приложението Functions да стартира правилно и да показва работещите функции. Както е споменато в [този въпрос в Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), това може да бъде пренебрегнато.

1. Спрете приложението Functions, като натиснете `ctrl+c`.

1. Отворете текущата папка във VS Code, като или стартирате VS Code и след това отворите тази папка, или изпълните следната команда:

    ```sh
    code .
    ```

    VS Code ще разпознае вашия проект за Functions и ще покаже известие със следното съобщение:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Известието](../../../../../translated_images/bg/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Изберете **Yes** от това известие.

1. Уверете се, че виртуалната среда на Python работи в терминала на VS Code. Ако е необходимо, я спрете и рестартирайте.

## Създаване на тригер за събития от IoT Hub

Приложението Functions е обвивката на вашия сървърлесс код. За да реагирате на събития от IoT Hub, можете да добавите тригер за IoT Hub към това приложение. Този тригер трябва да се свърже към потока от съобщения, които се изпращат към IoT Hub, и да реагира на тях. За да получите този поток от съобщения, вашият тригер трябва да се свърже към *event hub compatible endpoint* на IoT Hub.

IoT Hub е базиран на друга услуга на Azure, наречена Azure Event Hubs. Event Hubs е услуга, която позволява изпращане и получаване на съобщения, а IoT Hub разширява тази функционалност с допълнителни възможности за IoT устройства. Начинът, по който се свързвате, за да четете съобщения от IoT Hub, е същият като при използване на Event Hubs.

✅ Направете проучване: Прочетете общия преглед на Event Hubs в [документацията за Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Как основните функции се сравняват с тези на IoT Hub?

За да се свърже IoT устройство с IoT Hub, то трябва да използва таен ключ, който гарантира, че само разрешени устройства могат да се свържат. Същото важи и при свързване за четене на съобщения – вашият код ще се нуждае от connection string, който съдържа таен ключ, както и детайли за IoT Hub.

> 💁 По подразбиране connection string, който получавате, има права **iothubowner**, което дава на всеки код, който го използва, пълни права върху IoT Hub. Идеално е да се свързвате с най-ниското ниво на права, което е необходимо. Това ще бъде разгледано в следващия урок.

След като вашият тригер се свърже, кодът вътре във функцията ще бъде извикан за всяко съобщение, изпратено към IoT Hub, независимо от устройството, което го е изпратило. Тригерът ще предаде съобщението като параметър.

### Задача - получаване на connection string за Event Hub compatible endpoint

1. От терминала на VS Code изпълнете следната команда, за да получите connection string за Event Hub compatible endpoint на IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Заменете `<hub_name>` с името, което сте използвали за вашия IoT Hub.

1. Във VS Code отворете файла `local.settings.json`. Добавете следната допълнителна стойност в секцията `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Заменете `<connection string>` със стойността от предишната стъпка. Ще трябва да добавите запетая след предишния ред, за да направите JSON-а валиден.

### Задача - създаване на тригер за събития

Сега сте готови да създадете тригера за събития.

1. От терминала на VS Code изпълнете следната команда от папката `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Това ще създаде нова функция, наречена `iot-hub-trigger`. Тригерът ще се свърже към Event Hub compatible endpoint на IoT Hub, така че можете да използвате тригер за Event Hub. Няма специфичен тригер за IoT Hub.

Това ще създаде папка в `soil-moisture-trigger`, наречена `iot-hub-trigger`, която съдържа тази функция. Тази папка ще съдържа следните файлове:

* `__init__.py` - това е Python файлът, който съдържа тригера, използвайки стандартната Python конвенция за именуване на файлове, за да превърне тази папка в Python модул.

    Този файл ще съдържа следния код:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Основата на тригера е функцията `main`. Именно тази функция се извиква със събитията от IoT Hub. Тази функция има параметър, наречен `event`, който съдържа `EventHubEvent`. Всеки път, когато съобщение се изпрати към IoT Hub, тази функция се извиква, като предава това съобщение като `event`, заедно със свойства, които са същите като анотациите, които видяхте в предишния урок.

    Основата на тази функция е да записва събитието в логовете.

* `function.json` - този файл съдържа конфигурацията за тригера. Основната конфигурация е в секция, наречена `bindings`. Binding е термин за връзка между Azure Functions и други услуги на Azure. Тази функция има входящ binding към Event Hub - тя се свързва с Event Hub и получава данни.

    > 💁 Можете също така да имате изходящи bindings, така че изходът на функцията да се изпраща към друга услуга. Например, можете да добавите изходящ binding към база данни и да върнете събитието от IoT Hub от функцията, и то автоматично ще бъде вмъкнато в базата данни.

    ✅ Направете проучване: Прочетете за bindings в [документацията за концепции на Azure Functions triggers и bindings](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Секцията `bindings` включва конфигурация за binding-а. Интересните стойности са:

  * `"type": "eventHubTrigger"` - това указва на функцията, че трябва да слуша събития от Event Hub
  * `"name": "events"` - това е името на параметъра за събитията от Event Hub. Това съвпада с името на параметъра във функцията `main` в Python кода.
  * `"direction": "in"` - това е входящ binding, данните от Event Hub влизат във функцията
  * `"connection": ""` - това определя името на настройката, от която да се прочете connection string. Когато работите локално, това ще прочете тази настройка от файла `local.settings.json`.

    > 💁 Connection string не може да се съхранява във файла `function.json`, той трябва да се чете от настройките. Това е, за да се предотврати случайно излагане на connection string.

1. Поради [грешка в шаблона на Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), `function.json` има неправилна стойност за полето `cardinality`. Актуализирайте това поле от `many` на `one`:

    ```json
    "cardinality": "one",
    ```

1. Актуализирайте стойността на `"connection"` във файла `function.json`, за да сочи към новата стойност, която добавихте в `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Помнете - това трябва да сочи към настройката, а не да съдържа действителния connection string.

1. Connection string съдържа стойността `eventHubName`, така че стойността за това във файла `function.json` трябва да бъде изчистена. Актуализирайте тази стойност на празен низ:

    ```json
    "eventHubName": "",
    ```

### Задача - стартиране на тригера за събития

1. Уверете се, че не стартирате монитора за събития на IoT Hub. Ако той работи едновременно с приложението Functions, приложението няма да може да се свърже и да обработва събития.

    > 💁 Множество приложения могат да се свържат към IoT Hub endpoint-ите, използвайки различни *consumer groups*. Това ще бъде разгледано в по-късен урок.

1. За да стартирате приложението Functions, изпълнете следната команда от терминала на VS Code:

    ```sh
    func start
    ```

    Приложението Functions ще стартира и ще открие функцията `iot-hub-trigger`. След това ще обработи всички събития, които вече са изпратени към IoT Hub през последния ден.

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

    Всяко извикване на функцията ще бъде обградено от блокове `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` в изхода, така че можете да видите колко съобщения са обработени във всяко извикване на функцията.

1. Уверете се, че вашето IoT устройство работи. Ще видите нови съобщения за влажност на почвата, които се появяват в приложението Functions.

1. Спрете и рестартирайте приложението Functions. Ще видите, че то няма да обработва предишни съобщения отново, а само нови съобщения.

> 💁 VS Code също поддържа дебъгване на вашите функции. Можете да зададете точки за спиране, като кликнете върху границата до началото на всеки ред от кода, или като поставите курсора върху ред от кода и изберете *Run -> Toggle breakpoint*, или натиснете `F9`. Можете да стартирате дебъгера, като изберете *Run -> Start debugging*, натиснете `F5`, или изберете панела *Run and debug* и натиснете бутона **Start debugging**. Така можете да видите детайлите на обработваните събития.

#### Отстраняване на проблеми

* Ако получите следната грешка:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Проверете дали Azurite работи и дали сте задали `AzureWebJobsStorage` във файла `local.settings.json` на `UseDevelopmentStorage=true`.

* Ако получите следната грешка:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Проверете дали сте задали `cardinality` във файла `function.json` на `one`.

* Ако получите следната грешка:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Проверете дали сте задали `eventHubName` във файла `function.json` на празен низ.

## Изпращане на заявки за директни методи от сървърлесс код

Досега вашето приложение Functions слушаше съобщения от IoT Hub, използвайки Event Hub compatible endpoint. Сега трябва да изпращате команди към IoT устройството. Това се прави чрез различна връзка към IoT Hub чрез *Registry Manager*. Registry Manager е инструмент, който ви позволява да видите кои устройства са регистрирани в IoT Hub и да комуникирате с тези устройства, като изпращате съобщения от облака към устройството, заявки за директни методи или актуализирате device twin. Можете също така да го използвате, за да регистрирате, актуализирате или изтривате IoT устройства от IoT Hub.

За да се свържете с Registry Manager, ви е необходим connection string.

### Задача - получаване на connection string за Registry Manager

1. За да получите connection string, изпълнете следната команда:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Заменете `<hub_name>` с името, което сте използвали за вашия IoT Hub.

    Connection string се заявява за политиката *ServiceConnect*, използвайки параметъра `--policy-name service`. Когато заявявате connection string, можете да посочите какви права ще позволи този connection string. Политиката ServiceConnect позволява на вашия код да се свърже и да изпраща съобщения към IoT устройства.

    ✅ Направете проучване: Прочетете за различните политики в [документацията за права на IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. Във VS Code отворете файла `local.settings.json`. Добавете следната допълнителна стойност в секцията `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Заменете `<connection string>` със стойността от предишната стъпка. Ще трябва да добавите запетая след предишния ред, за да направите JSON-а валиден.

### Задача - изпращане на заявка за директен метод към устройство

1. SDK за Registry Manager е наличен чрез Pip пакет. Добавете следния ред към файла `requirements.txt`, за да добавите зависимостта към този пакет:

    ```sh
    azure-iot-hub
    ```

1. Уверете се, че терминалът на VS Code има активирана виртуална среда, и изпълнете следната команда, за да инсталирате Pip пакетите:

    ```sh
    pip install -r requirements.txt
    ```

1. Добавете следните импорти към файла `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Това импортира някои системни библиотеки, както и библиотеките за взаимодействие с Registry Manager и изпращане на заявки за директни методи.

1. Премахнете кода от вътрешността на метода `main`, но запазете самия метод.

1. В метода `main` добавете следния код:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Този код извлича тялото на събитието, което съдържа JSON съобщението, изпратено от IoT устройството.

    След това получава ID на устройството от анотациите, предадени със съобщението. Тялото на събитието съдържа съобщението, изпратено като телеметрия, а речникът `iothub_metadata` съдържа свойства, зададени от IoT Hub, като например ID на устройството-изпращач и времето, когато съобщението е изпратено.

    Тази информация след това се записва в логовете. Ще видите този лог в терминала, когато стартирате приложението Function локално.

1. Под това добавете следния код:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Този код получава стойността за влажността на почвата от съобщението. След това проверява влажността и в зависимост от стойността създава помощен клас за заявка за директен метод за `relay_on` или `relay_off`. Заявката за метод не изисква полезен товар, така че се изпраща празен JSON документ.

1. Под това добавете следния код:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Този код зарежда `REGISTRY_MANAGER_CONNECTION_STRING` от файла `local.settings.json`. Стойностите в този файл са достъпни като променливи на средата и могат да бъдат прочетени с помощта на функцията `os.environ`, която връща речник с всички променливи на средата.

> 💁 Когато този код бъде разположен в облака, стойностите от файла `local.settings.json` ще бъдат зададени като *Application Settings* и могат да бъдат прочетени от променливите на средата.

Кодът след това създава инстанция на помощния клас Registry Manager, използвайки връзковия низ.

1. Под това добавете следния код:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Този код указва на Registry Manager да изпрати заявка за директен метод към устройството, което е изпратило телеметрията.

    > 💁 В предишните версии на приложението, които създадохте в по-ранни уроци с помощта на MQTT, командите за управление на релето се изпращаха към всички устройства. Кодът предполагаше, че ще имате само едно устройство. Тази версия на кода изпраща заявката за метод към едно устройство, така че ще работи, ако имате множество конфигурации на сензори за влажност и релета, изпращайки правилната заявка за директен метод към правилното устройство.

1. Стартирайте приложението Functions и се уверете, че вашето IoT устройство изпраща данни. Ще видите как съобщенията се обработват и заявките за директни методи се изпращат. Преместете сензора за влажност на почвата вътре и извън почвата, за да видите как стойностите се променят и релето се включва и изключва.

> 💁 Можете да намерите този код в папката [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Разположете вашия сървърно-базиран код в облака

Вашият код вече работи локално, така че следващата стъпка е да разположите приложението Functions в облака.

### Задача - създайте облачните ресурси

Вашето приложение Functions трябва да бъде разположено в ресурс Functions App в Azure, който се намира в Resource Group, създадена за вашия IoT Hub. Ще ви е необходим и Storage Account, създаден в Azure, за да замени емулатора, който използвате локално.

1. Стартирайте следната команда, за да създадете Storage Account:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Заменете `<storage_name>` с име за вашия Storage Account. Това име трябва да бъде уникално в глобален мащаб, тъй като е част от URL адреса, използван за достъп до акаунта. Можете да използвате само малки букви и цифри за това име, без други символи, и то е ограничено до 24 символа. Използвайте нещо като `sms` и добавете уникален идентификатор накрая, като случайни думи или вашето име.

    Опцията `--sku Standard_LRS` избира ценовия план, като се избира най-ниската цена за обща употреба. Няма безплатен план за съхранение, и плащате за това, което използвате. Разходите са сравнително ниски, като най-скъпото съхранение струва по-малко от 0,05 USD на месец за гигабайт.

    ✅ Прочетете повече за цените на страницата [Azure Storage Account pricing](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn).

1. Стартирайте следната команда, за да създадете Function App:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Заменете `<location>` с местоположението, което използвахте при създаването на Resource Group в предишния урок.

    Заменете `<storage_name>` с името на Storage Account, който създадохте в предишната стъпка.

    Заменете `<functions_app_name>` с уникално име за вашето Functions App. Това име трябва да бъде уникално в глобален мащаб, тъй като е част от URL адреса, който може да се използва за достъп до Functions App. Използвайте нещо като `soil-moisture-sensor-` и добавете уникален идентификатор накрая, като случайни думи или вашето име.

    Опцията `--functions-version 3` задава версията на Azure Functions, която да се използва. Версия 3 е най-новата версия.

    Опцията `--os-type Linux` указва на Functions runtime да използва Linux като операционна система за хостване на тези функции. Функциите могат да бъдат хоствани на Linux или Windows, в зависимост от използвания програмен език. Python приложенията се поддържат само на Linux.

### Задача - качете настройките на приложението си

Когато разработвахте вашето Functions App, съхранявахте някои настройки във файла `local.settings.json` за връзковите низове за вашия IoT Hub. Тези настройки трябва да бъдат записани в Application Settings във вашето Function App в Azure, за да могат да бъдат използвани от вашия код.

> 🎓 Файлът `local.settings.json` е само за локални настройки за разработка и не трябва да бъде качван в системи за контрол на версиите, като GitHub. Когато се разположи в облака, се използват Application Settings. Application Settings са двойки ключ/стойност, хоствани в облака, и се четат от променливите на средата или във вашия код, или от runtime, когато свързва вашия код с IoT Hub.

1. Стартирайте следната команда, за да зададете настройката `IOT_HUB_CONNECTION_STRING` в Application Settings на Functions App:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Заменете `<functions_app_name>` с името, което използвахте за вашето Functions App.

    Заменете `<connection string>` със стойността на `IOT_HUB_CONNECTION_STRING` от вашия файл `local.settings.json`.

1. Повторете горната стъпка, но задайте стойността на `REGISTRY_MANAGER_CONNECTION_STRING` на съответната стойност от вашия файл `local.settings.json`.

Когато стартирате тези команди, те също ще изведат списък с всички Application Settings за Function App. Можете да използвате това, за да проверите дали стойностите са зададени правилно.

> 💁 Ще видите стойност, която вече е зададена за `AzureWebJobsStorage`. Във вашия файл `local.settings.json` това беше зададено на стойност за използване на локалния емулатор за съхранение. Когато създадохте Functions App, подадохте Storage Account като параметър, и това се задава автоматично в тази настройка.

### Задача - разположете вашето Functions App в облака

Сега, когато Functions App е готово, вашият код може да бъде разположен.

1. Стартирайте следната команда от терминала на VS Code, за да публикувате вашето Functions App:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Заменете `<functions_app_name>` с името, което използвахте за вашето Functions App.

Кодът ще бъде пакетиран и изпратен към Functions App, където ще бъде разположен и стартиран. Ще има много изход в конзолата, завършващ с потвърждение за разполагането и списък с разположените функции. В този случай списъкът ще съдържа само тригера.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Уверете се, че вашето IoT устройство работи. Променете нивата на влажност, като регулирате влажността на почвата или преместите сензора вътре и извън почвата. Ще видите как релето се включва и изключва, когато влажността на почвата се променя.

---

## 🚀 Предизвикателство

В предишния урок управлявахте времето за релето, като се отписвахте от MQTT съобщенията, докато релето беше включено, и за кратко след като беше изключено. Тук не можете да използвате този метод - не можете да се отпишете от IoT Hub тригера.

Помислете за различни начини, по които бихте могли да се справите с това във вашето Functions App.

## Тест след лекцията

[Тест след лекцията](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Преглед и самостоятелно обучение

* Прочетете за сървърно-базираното изчисление на страницата [Serverless Computing в Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Прочетете за използването на сървърно-базирани решения в Azure, включително още примери, в публикацията [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Научете повече за Azure Functions на [Azure Functions YouTube канал](https://www.youtube.com/c/AzureFunctions)

## Задание

[Добавете ръчно управление на релето](assignment.md)

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.