<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-26T22:59:37+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ar"
}
-->
# ربط جهاز إنترنت الأشياء بالسحابة - جهاز إنترنت الأشياء الافتراضي و Raspberry Pi

في هذا الجزء من الدرس، ستقوم بربط جهاز إنترنت الأشياء الافتراضي الخاص بك أو Raspberry Pi بمركز إنترنت الأشياء الخاص بك، لإرسال البيانات واستقبال الأوامر.

## ربط جهازك بمركز إنترنت الأشياء

الخطوة التالية هي ربط جهازك بمركز إنترنت الأشياء.

### المهمة - الربط بمركز إنترنت الأشياء

1. افتح مجلد `soil-moisture-sensor` في VS Code. تأكد من تشغيل البيئة الافتراضية في الطرفية إذا كنت تستخدم جهاز إنترنت أشياء افتراضي.

1. قم بتثبيت بعض حزم Pip الإضافية:

    ```sh
    pip3 install azure-iot-device
    ```

    مكتبة `azure-iot-device` تُستخدم للتواصل مع مركز إنترنت الأشياء الخاص بك.

1. أضف الواردات التالية إلى أعلى ملف `app.py`، أسفل الواردات الموجودة:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    هذا الكود يستورد SDK للتواصل مع مركز إنترنت الأشياء الخاص بك.

1. قم بإزالة السطر `import paho.mqtt.client as mqtt` حيث لم تعد هذه المكتبة مطلوبة. قم بإزالة كل كود MQTT بما في ذلك أسماء المواضيع، وكل الكود الذي يستخدم `mqtt_client` و `handle_command`. احتفظ بحلقة `while True:`، فقط احذف سطر `mqtt_client.publish` من هذه الحلقة.

1. أضف الكود التالي أسفل عبارات الواردات:

    ```python
    connection_string = "<connection string>"
    ```

    استبدل `<connection string>` بسلسلة الاتصال التي استرجعتها للجهاز في وقت سابق من هذا الدرس.

    > 💁 هذا ليس أفضل ممارسة. لا يجب أبدًا تخزين سلاسل الاتصال في كود المصدر، حيث يمكن أن يتم إدخالها في نظام التحكم في الكود والعثور عليها من قبل أي شخص. نحن نفعل ذلك هنا من أجل التبسيط. من الأفضل استخدام شيء مثل متغير بيئة وأداة مثل [`python-dotenv`](https://pypi.org/project/python-dotenv/). ستتعلم المزيد عن هذا في درس قادم.

1. أسفل هذا الكود، أضف التالي لإنشاء كائن عميل جهاز يمكنه التواصل مع مركز إنترنت الأشياء، وربطه:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. قم بتشغيل هذا الكود. سترى جهازك يتصل.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## إرسال البيانات

الآن بعد أن تم ربط جهازك، يمكنك إرسال البيانات إلى مركز إنترنت الأشياء بدلاً من وسيط MQTT.

### المهمة - إرسال البيانات

1. أضف الكود التالي داخل حلقة `while True`، قبل السطر الخاص بالنوم:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    هذا الكود ينشئ رسالة `Message` لمركز إنترنت الأشياء تحتوي على قراءة رطوبة التربة كـ JSON، ثم يرسلها إلى مركز إنترنت الأشياء كرسالة من الجهاز إلى السحابة.

## التعامل مع الأوامر

يحتاج جهازك إلى التعامل مع أمر من كود الخادم للتحكم في المرحل. يتم إرسال هذا كطلب طريقة مباشرة.

## المهمة - التعامل مع طلب طريقة مباشرة

1. أضف الكود التالي قبل حلقة `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    هذا الكود يعرّف طريقة، `handle_method_request`، سيتم استدعاؤها عند استدعاء طريقة مباشرة من قبل مركز إنترنت الأشياء. كل طريقة مباشرة لها اسم، ويتوقع هذا الكود طريقة تسمى `relay_on` لتشغيل المرحل، و`relay_off` لإيقافه.

    > 💁 يمكن أيضًا تنفيذ ذلك في طلب طريقة مباشرة واحدة، مع تمرير الحالة المطلوبة للمرحل في حمولة يمكن تمريرها مع طلب الطريقة وتكون متاحة من كائن `request`.

1. تتطلب الطرق المباشرة استجابة لإبلاغ الكود المستدعي بأنه تم التعامل معها. أضف الكود التالي في نهاية وظيفة `handle_method_request` لإنشاء استجابة للطلب:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    هذا الكود يرسل استجابة لطلب الطريقة المباشرة مع رمز حالة HTTP 200، ويرسلها مرة أخرى إلى مركز إنترنت الأشياء.

1. أضف الكود التالي أسفل تعريف هذه الوظيفة:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    هذا الكود يخبر عميل مركز إنترنت الأشياء باستدعاء وظيفة `handle_method_request` عند استدعاء طريقة مباشرة.

> 💁 يمكنك العثور على هذا الكود في مجلد [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) أو [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 برنامج مستشعر رطوبة التربة الخاص بك متصل بمركز إنترنت الأشياء!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الموثوق. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة تنشأ عن استخدام هذه الترجمة.