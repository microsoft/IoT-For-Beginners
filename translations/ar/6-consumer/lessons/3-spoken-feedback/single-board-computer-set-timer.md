<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T00:07:19+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "ar"
}
-->
# ضبط مؤقت - الأجهزة الافتراضية لإنترنت الأشياء و Raspberry Pi

في هذا الجزء من الدرس، ستقوم باستدعاء الكود الخالي من الخوادم لفهم الكلام وضبط مؤقت على جهاز إنترنت الأشياء الافتراضي أو Raspberry Pi بناءً على النتائج.

## ضبط مؤقت

النص الذي يتم إرجاعه من استدعاء تحويل الكلام إلى نص يحتاج إلى إرساله إلى الكود الخالي من الخوادم ليتم معالجته بواسطة LUIS، حيث يتم الحصول على عدد الثواني للمؤقت. يمكن استخدام هذا العدد من الثواني لضبط المؤقت.

يمكن ضبط المؤقت باستخدام فئة `threading.Timer` في Python. تأخذ هذه الفئة وقت التأخير ودالة، وبعد وقت التأخير يتم تنفيذ الدالة.

### المهمة - إرسال النص إلى الدالة الخالية من الخوادم

1. افتح مشروع `smart-timer` في VS Code، وتأكد من تحميل البيئة الافتراضية في الطرفية إذا كنت تستخدم جهاز إنترنت الأشياء الافتراضي.

1. فوق دالة `process_text`، قم بتعريف دالة تسمى `get_timer_time` لاستدعاء نقطة النهاية REST التي أنشأتها:

    ```python
    def get_timer_time(text):
    ```

1. أضف الكود التالي إلى هذه الدالة لتحديد عنوان URL للاستدعاء:

    ```python
    url = '<URL>'
    ```

    استبدل `<URL>` بعنوان URL لنقطة النهاية التي أنشأتها في الدرس السابق، سواء على جهاز الكمبيوتر الخاص بك أو في السحابة.

1. أضف الكود التالي لتعيين النص كخاصية يتم تمريرها كـ JSON إلى الاستدعاء:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. أسفل هذا، قم باسترجاع `seconds` من حمولة الاستجابة، مع إرجاع 0 إذا فشل الاستدعاء:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    عمليات الاستدعاء HTTP الناجحة تُرجع رمز حالة في نطاق 200، والكود الخالي من الخوادم الخاص بك يُرجع 200 إذا تم معالجة النص والتعرف عليه كنية ضبط المؤقت.

### المهمة - ضبط مؤقت في خيط خلفي

1. أضف بيان الاستيراد التالي في أعلى الملف لاستيراد مكتبة threading في Python:

    ```python
    import threading
    ```

1. فوق دالة `process_text`، أضف دالة للتحدث بالرد. في الوقت الحالي، ستكتب فقط إلى وحدة التحكم، ولكن لاحقًا في هذا الدرس ستتحدث النص.

    ```python
    def say(text):
        print(text)
    ```

1. أسفل هذا، أضف دالة سيتم استدعاؤها بواسطة المؤقت للإعلان عن انتهاء المؤقت:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    تأخذ هذه الدالة عدد الدقائق والثواني للمؤقت، وتبني جملة للإعلان عن انتهاء المؤقت. ستتحقق من عدد الدقائق والثواني، وتضمّن كل وحدة زمنية فقط إذا كان لها قيمة. على سبيل المثال، إذا كان عدد الدقائق 0، فسيتم تضمين الثواني فقط في الرسالة. يتم إرسال هذه الجملة بعد ذلك إلى دالة `say`.

1. أسفل هذا، أضف دالة `create_timer` التالية لإنشاء مؤقت:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    تأخذ هذه الدالة العدد الإجمالي للثواني للمؤقت الذي سيتم إرساله في الأمر، وتحوله إلى دقائق وثواني. ثم تقوم بإنشاء وتشغيل كائن مؤقت باستخدام العدد الإجمالي للثواني، مع تمرير دالة `announce_timer` وقائمة تحتوي على الدقائق والثواني. عندما ينقضي المؤقت، ستستدعي دالة `announce_timer`، وستمرر محتويات هذه القائمة كمعلمات - بحيث يتم تمرير العنصر الأول في القائمة كمعامل `minutes`، والعنصر الثاني كمعامل `seconds`.

1. في نهاية دالة `create_timer`، أضف بعض الكود لبناء رسالة يتم التحدث بها إلى المستخدم للإعلان عن بدء المؤقت:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    مرة أخرى، يتم تضمين وحدة الزمن التي لها قيمة فقط. يتم إرسال هذه الجملة بعد ذلك إلى دالة `say`.

1. أضف ما يلي إلى نهاية دالة `process_text` للحصول على الوقت للمؤقت من النص، ثم إنشاء المؤقت:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    يتم إنشاء المؤقت فقط إذا كان عدد الثواني أكبر من 0.

1. قم بتشغيل التطبيق، وتأكد من تشغيل تطبيق الوظائف أيضًا. قم بضبط بعض المؤقتات، وسيظهر الإخراج ضبط المؤقت، ثم سيظهر عند انتهاء المؤقت:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) أو [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 لقد نجح برنامج المؤقت الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.