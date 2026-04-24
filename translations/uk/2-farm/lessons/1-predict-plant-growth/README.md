    This code extracts the temperature from the telemetry message, gets the current date and time, and writes these as a new row in the CSV file.

1. Run the server code and ensure it is capturing telemetry data from your IoT device. Check the CSV file to confirm that the data is being saved correctly.

✅ Why do you think saving data in a CSV file might be useful for farmers or researchers?

## Summary

In this lesson, you learned about the importance of temperature in plant growth and how to calculate Growing Degree Days (GDD) to predict plant maturity. You also explored how IoT devices can be used to measure and publish temperature data, and how server code can capture and store this data for analysis.

By using IoT and digital agriculture techniques, farmers can optimize their crop yields, reduce waste, and make more informed decisions about their farming practices.

## 🚀 Challenge

Using the temperature data saved in the CSV file, write a Python script to calculate the total GDD for a specific crop. Use the base temperature for the crop and the temperature data from the CSV file to calculate the GDD for each day, then sum these values to get the total GDD.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Review & Self-study

1. Research how GDD is used in different types of farming, such as vineyards, orchards, or grain farming.
2. Investigate other environmental factors that can be measured with IoT devices to improve farming practices, such as soil moisture, light levels, or pest activity.

## Assignment

Create a complete IoT solution to monitor temperature and calculate GDD for a specific crop. Your solution should include:

1. An IoT device to measure and publish temperature data.
2. Server code to capture and store the temperature data in a CSV file.
3. A Python script to calculate the total GDD for the crop based on the stored data.

Document your solution and explain how it could help a farmer optimize their crop production.
Цей код відкриває CSV-файл, а потім додає новий рядок в кінці. Рядок містить поточну дату і час, відформатовані у зручний для читання формат, а також температуру, отриману від IoT-пристрою. Дані зберігаються у [форматі ISO 8601](https://wikipedia.org/wiki/ISO_8601) з часовою зоною, але без мікросекунд.

1. Запустіть цей код так само, як і раніше, переконавшись, що ваш IoT-пристрій надсилає дані. У тій самій папці буде створено CSV-файл під назвою `temperature.csv`. Якщо ви відкриєте його, то побачите дати/часи та вимірювання температури:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Запустіть цей код протягом певного часу, щоб зібрати дані. Ідеально, якщо ви запустите його на цілий день, щоб зібрати достатньо даних для розрахунку GDD.

    
> 💁 Якщо ви використовуєте віртуальний IoT-пристрій, виберіть випадкову галочку та встановіть діапазон, щоб уникнути отримання однакової температури кожного разу, коли повертається значення температури.
    ![Виберіть випадкову галочку та встановіть діапазон](../../../../../translated_images/uk/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Якщо ви хочете запустити це на цілий день, вам потрібно переконатися, що комп'ютер, на якому працює ваш серверний код, не перейде в режим сну, або змінити налаштування живлення, або запустити щось на кшталт [цього скрипту Python для підтримки активності системи](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Ви можете знайти цей код у папці [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Завдання - розрахувати GDD за збереженими даними

Після того, як сервер збере дані про температуру, можна розрахувати GDD для рослини.

Кроки для ручного виконання:

1. Знайдіть базову температуру для рослини. Наприклад, для полуниці базова температура становить 10°C.

1. У файлі `temperature.csv` знайдіть найвищу та найнижчу температуру за день.

1. Використовуйте формулу розрахунку GDD, наведеної раніше, щоб обчислити GDD.

Наприклад, якщо найвища температура за день становить 25°C, а найнижча — 12°C:

![GDD = 25 + 12 поділити на 2, потім відняти 10 від результату, отримуючи 8.5](../../../../../translated_images/uk/gdd-calculation-strawberries.59f57db94b22adb8.webp)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Отже, полуниця отримала **8.5** GDD. Полуниця потребує близько 250 GDD, щоб почати плодоносити, тому ще потрібно трохи часу.

---

## 🚀 Виклик

Рослинам потрібне не лише тепло для росту. Що ще необхідно?

Для цих потреб знайдіть, чи існують датчики, які можуть їх вимірювати. А як щодо актуаторів для контролю цих рівнів? Як би ви зібрали один або кілька IoT-пристроїв для оптимізації росту рослин?

## Тест після лекції

[Тест після лекції](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Огляд та самостійне навчання

* Дізнайтеся більше про цифрове сільське господарство на [сторінці Вікіпедії про цифрове сільське господарство](https://wikipedia.org/wiki/Digital_agriculture). Також прочитайте більше про точне землеробство на [сторінці Вікіпедії про точне землеробство](https://wikipedia.org/wiki/Precision_agriculture).
* Повний розрахунок градусів росту (GDD) є складнішим, ніж спрощений, наведений тут. Дізнайтеся більше про складнішу формулу та як враховувати температури нижче базової на [сторінці Вікіпедії про градуси росту](https://wikipedia.org/wiki/Growing_degree-day).
* Їжа може стати дефіцитною в майбутньому, якщо ми продовжимо використовувати ті самі методи землеробства. Дізнайтеся більше про високотехнологічні методи землеробства в цьому [відео про високотехнологічні ферми майбутнього на YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Завдання

[Візуалізуйте дані GDD за допомогою Jupyter Notebook](assignment.md)

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.