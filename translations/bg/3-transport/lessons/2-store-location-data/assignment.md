<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T09:57:24+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "bg"
}
-->
# Разследване на свързвания на функции

## Инструкции

Свързванията на функции позволяват на вашия код да записва обекти в blob хранилище, като ги връща от функцията `main`. Акаунтът за Azure Storage, колекцията и други детайли се конфигурират в файла `function.json`.

Когато работите с Azure или други технологии на Microsoft, най-добрият източник на информация е [документацията на Microsoft на docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). В това задание ще трябва да прочетете документацията за свързванията на Azure Functions, за да разберете как да настроите изходното свързване.

Някои страници, които да разгледате за начало, са:

* [Концепции за тригери и свързвания на Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Преглед на свързванията за Azure Blob Storage за Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Изходно свързване за Azure Blob Storage за Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Критерии за оценка

| Критерий | Отлично | Задоволително | Нуждае се от подобрение |
| -------- | --------- | -------- | ----------------- |
| Конфигуриране на изходното свързване за blob хранилище | Успешно конфигурирано изходното свързване, върнат е обектът и е записан в blob хранилище | Успешно конфигурирано изходното свързване или върнат е обектът, но не е записан в blob хранилище | Неуспешно конфигуриране на изходното свързване |

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.