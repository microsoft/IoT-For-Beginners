# قراءة بيانات GPS - Raspberry Pi

في هذا الجزء من الدرس، ستقوم بإضافة مستشعر GPS إلى Raspberry Pi وقراءة القيم منه.

## الأجهزة

يحتاج Raspberry Pi إلى مستشعر GPS.

المستشعر الذي ستستخدمه هو [مستشعر Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). يمكن لهذا المستشعر الاتصال بأنظمة GPS متعددة للحصول على إشارة سريعة ودقيقة. يتكون المستشعر من جزئين - الإلكترونيات الأساسية للمستشعر وهوائي خارجي متصل بسلك رفيع لالتقاط موجات الراديو من الأقمار الصناعية.

هذا المستشعر يعمل عبر UART، لذا يرسل بيانات GPS عبر UART.

## توصيل مستشعر GPS

يمكن توصيل مستشعر Grove GPS بـ Raspberry Pi.

### المهمة - توصيل مستشعر GPS

قم بتوصيل مستشعر GPS.

![مستشعر Grove GPS](../../../../../translated_images/ar/grove-gps-sensor.247943bf69b03f0d.webp)

1. أدخل أحد طرفي كابل Grove في المقبس الموجود على مستشعر GPS. لن يدخل إلا في اتجاه واحد.

1. مع إيقاف تشغيل Raspberry Pi، قم بتوصيل الطرف الآخر من كابل Grove بمقبس UART المسمى **UART** على قبعة Grove Base المثبتة على Pi. يوجد هذا المقبس في الصف الأوسط، على الجانب الأقرب إلى فتحة بطاقة SD، في الطرف الآخر من منافذ USB ومقبس الإيثرنت.

    ![مستشعر Grove GPS متصل بمقبس UART](../../../../../translated_images/ar/pi-gps-sensor.1f99ee2b2f652891.webp)

1. ضع مستشعر GPS بحيث يكون الهوائي المتصل به مرئيًا للسماء - من الأفضل أن يكون بجانب نافذة مفتوحة أو في الخارج. من الأسهل الحصول على إشارة واضحة بدون وجود عوائق أمام الهوائي.

## برمجة مستشعر GPS

يمكن الآن برمجة Raspberry Pi لاستخدام مستشعر GPS المتصل.

### المهمة - برمجة مستشعر GPS

قم ببرمجة الجهاز.

1. قم بتشغيل Pi وانتظر حتى يتم الإقلاع.

1. يحتوي مستشعر GPS على مصباحين LED - مصباح أزرق يومض عند إرسال البيانات، ومصباح أخضر يومض كل ثانية عند استقبال البيانات من الأقمار الصناعية. تأكد من أن المصباح الأزرق يومض عند تشغيل Pi. بعد بضع دقائق، سيبدأ المصباح الأخضر في الوميض - إذا لم يحدث ذلك، قد تحتاج إلى إعادة وضع الهوائي.

1. قم بتشغيل VS Code، إما مباشرة على Pi، أو عبر الاتصال باستخدام إضافة Remote SSH.

    > ⚠️ يمكنك الرجوع إلى [التعليمات الخاصة بإعداد وتشغيل VS Code في الدرس الأول إذا لزم الأمر](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. مع الإصدارات الأحدث من Raspberry Pi التي تدعم البلوتوث، هناك تعارض بين منفذ السيريال المستخدم للبلوتوث والمنفذ المستخدم بواسطة منفذ Grove UART. لإصلاح ذلك، قم بما يلي:

    1. من نافذة الأوامر في VS Code، قم بتحرير ملف `/boot/config.txt` باستخدام `nano`، وهو محرر نصوص مدمج في نافذة الأوامر، باستخدام الأمر التالي:

        ```sh
        sudo nano /boot/config.txt
        ```

        > لا يمكن تحرير هذا الملف باستخدام VS Code لأنه يتطلب أذونات `sudo`، وهي أذونات مرتفعة. VS Code لا يعمل بهذه الأذونات.

    1. استخدم مفاتيح الأسهم للتنقل إلى نهاية الملف، ثم انسخ الكود أدناه والصقه في نهاية الملف:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        يمكنك اللصق باستخدام اختصارات لوحة المفاتيح العادية لجهازك (`Ctrl+v` على Windows، Linux أو Raspberry Pi OS، `Cmd+v` على macOS).

    1. احفظ هذا الملف واخرج من nano بالضغط على `Ctrl+x`. اضغط على `y` عندما يُطلب منك حفظ التعديلات، ثم اضغط على `enter` لتأكيد الكتابة فوق `/boot/config.txt`.

        > إذا ارتكبت خطأ، يمكنك الخروج دون حفظ، ثم تكرار هذه الخطوات.

    1. قم بتحرير ملف `/boot/cmdline.txt` في nano باستخدام الأمر التالي:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. يحتوي هذا الملف على عدد من أزواج المفتاح/القيمة مفصولة بمسافات. قم بإزالة أي أزواج مفتاح/قيمة للمفتاح `console`. قد تبدو مثل هذا:

        ```output
        console=serial0,115200 console=tty1 
        ```

        يمكنك التنقل إلى هذه الإدخالات باستخدام مفاتيح الأسهم، ثم الحذف باستخدام مفاتيح `del` أو `backspace` العادية.

        على سبيل المثال، إذا كان ملفك الأصلي يبدو هكذا:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        النسخة الجديدة ستكون:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. اتبع الخطوات أعلاه لحفظ هذا الملف والخروج من nano.

    1. أعد تشغيل Pi، ثم أعد الاتصال بـ VS Code بمجرد إعادة تشغيل Pi.

1. من نافذة الأوامر، قم بإنشاء مجلد جديد في دليل المستخدم `pi` يسمى `gps-sensor`. أنشئ ملفًا في هذا المجلد يسمى `app.py`.

1. افتح هذا المجلد في VS Code.

1. يرسل وحدة GPS بيانات UART عبر منفذ سيريال. قم بتثبيت حزمة Pip `pyserial` للتواصل مع المنفذ السيريال من كود Python الخاص بك:

    ```sh
    pip3 install pyserial
    ```

1. أضف الكود التالي إلى ملف `app.py` الخاص بك:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    يقوم هذا الكود باستيراد وحدة `serial` من حزمة Pip `pyserial`. ثم يتصل بمنفذ السيريال `/dev/ttyAMA0` - هذا هو عنوان منفذ السيريال الذي يستخدمه Grove Pi Base Hat لمنفذ UART الخاص به. ثم يقوم بمسح أي بيانات موجودة من هذا الاتصال السيريالي.

    بعد ذلك، يتم تعريف دالة تسمى `print_gps_data` تقوم بطباعة السطر الممرر إليها إلى وحدة التحكم.

    بعد ذلك، يقوم الكود بالتكرار إلى الأبد، حيث يقرأ أكبر عدد ممكن من الأسطر النصية من المنفذ السيريالي في كل تكرار. يستدعي دالة `print_gps_data` لكل سطر.

    بعد قراءة جميع البيانات، ينام التكرار لمدة ثانية واحدة، ثم يحاول مرة أخرى.

1. قم بتشغيل هذا الكود. سترى المخرجات الخام من مستشعر GPS، شيء مثل التالي:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > إذا حصلت على أحد الأخطاء التالية عند إيقاف وإعادة تشغيل الكود، أضف كتلة `try - except` إلى حلقة while الخاصة بك.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 يمكنك العثور على هذا الكود في مجلد [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 لقد نجحت في برمجة مستشعر GPS الخاص بك!

---

**إخلاء المسؤولية**:  
تم ترجمة هذا المستند باستخدام خدمة الترجمة بالذكاء الاصطناعي [Co-op Translator](https://github.com/Azure/co-op-translator). بينما نسعى لتحقيق الدقة، يرجى العلم أن الترجمات الآلية قد تحتوي على أخطاء أو معلومات غير دقيقة. يجب اعتبار المستند الأصلي بلغته الأصلية المصدر الرسمي. للحصول على معلومات حاسمة، يُوصى بالاستعانة بترجمة بشرية احترافية. نحن غير مسؤولين عن أي سوء فهم أو تفسيرات خاطئة ناتجة عن استخدام هذه الترجمة.