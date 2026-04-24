# اپنی ایپلیکیشن لاجک کو کلاؤڈ میں منتقل کریں

![اس سبق کا خاکہ](../../../../../translated_images/ur/lesson-9.dfe99c8e891f48e1.webp)

> خاکہ [نیتیا نرسمہن](https://github.com/nitya) کی طرف سے۔ بڑی تصویر دیکھنے کے لیے تصویر پر کلک کریں۔

یہ سبق [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) کے حصے کے طور پر [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) سے پڑھایا گیا تھا۔

[![اپنے IoT ڈیوائس کو سرور لیس کوڈ کے ذریعے کنٹرول کریں](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## لیکچر سے پہلے کا کوئز

[لیکچر سے پہلے کا کوئز](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## تعارف

پچھلے سبق میں، آپ نے سیکھا کہ کس طرح اپنے پودے کی مٹی کی نمی کی نگرانی اور ریلے کنٹرول کو کلاؤڈ پر مبنی IoT سروس سے جوڑنا ہے۔ اگلا مرحلہ یہ ہے کہ ریلے کے وقت کو کنٹرول کرنے والے سرور کوڈ کو کلاؤڈ میں منتقل کیا جائے۔ اس سبق میں آپ سیکھیں گے کہ یہ کام سرور لیس فنکشنز کے ذریعے کیسے کیا جائے۔

اس سبق میں ہم درج ذیل موضوعات کا احاطہ کریں گے:

* [سرور لیس کیا ہے؟](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [سرور لیس ایپلیکیشن بنائیں](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [IoT Hub ایونٹ ٹرگر بنائیں](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [سرور لیس کوڈ سے ڈائریکٹ میتھڈ ریکویسٹ بھیجیں](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [اپنے سرور لیس کوڈ کو کلاؤڈ میں ڈیپلائے کریں](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## سرور لیس کیا ہے؟

سرور لیس، یا سرور لیس کمپیوٹنگ، چھوٹے کوڈ بلاکس بنانے کا عمل ہے جو مختلف قسم کے ایونٹس کے جواب میں کلاؤڈ میں چلتے ہیں۔ جب ایونٹ ہوتا ہے تو آپ کا کوڈ چلتا ہے اور ایونٹ کے بارے میں ڈیٹا اسے فراہم کیا جاتا ہے۔ یہ ایونٹس مختلف چیزوں سے ہو سکتے ہیں، جیسے ویب ریکویسٹ، قطار میں رکھے گئے پیغامات، ڈیٹا بیس میں ڈیٹا میں تبدیلیاں، یا IoT ڈیوائسز کے ذریعے IoT سروس کو بھیجے گئے پیغامات۔

![IoT سروس سے سرور لیس سروس کو بھیجے گئے ایونٹس، جو ایک ساتھ کئی فنکشنز کے ذریعے پروسیس کیے جا رہے ہیں](../../../../../translated_images/ur/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 اگر آپ نے پہلے ڈیٹا بیس ٹرگرز استعمال کیے ہیں، تو آپ اسے اسی طرح سمجھ سکتے ہیں، کوڈ ایونٹ جیسے کہ ایک قطار شامل کرنے پر ٹرگر ہوتا ہے۔

![جب ایک ساتھ کئی ایونٹس بھیجے جاتے ہیں، تو سرور لیس سروس ان سب کو ایک ساتھ چلانے کے لیے اسکیل کرتی ہے](../../../../../translated_images/ur/serverless-scaling.f8c769adf0413fd1.webp)

آپ کا کوڈ صرف اس وقت چلتا ہے جب ایونٹ ہوتا ہے، دوسرے وقتوں میں آپ کا کوڈ زندہ نہیں رہتا۔ ایونٹ ہوتا ہے، آپ کا کوڈ لوڈ ہوتا ہے اور چلتا ہے۔ یہ سرور لیس کو بہت اسکیل ایبل بناتا ہے - اگر ایک ساتھ کئی ایونٹس ہوتے ہیں، تو کلاؤڈ پرووائیڈر آپ کے فنکشن کو جتنی بار ضرورت ہو ایک ساتھ چلانے کے لیے اسکیل کر سکتا ہے، جو بھی سرورز دستیاب ہوں۔ اس کا نقصان یہ ہے کہ اگر آپ کو ایونٹس کے درمیان معلومات شیئر کرنے کی ضرورت ہو، تو آپ کو اسے کہیں محفوظ کرنا ہوگا جیسے ڈیٹا بیس میں، بجائے اس کے کہ اسے میموری میں اسٹور کریں۔

آپ کا کوڈ ایک فنکشن کے طور پر لکھا جاتا ہے جو ایونٹ کی تفصیلات کو پیرامیٹر کے طور پر لیتا ہے۔ آپ سرور لیس فنکشنز لکھنے کے لیے مختلف پروگرامنگ زبانوں کا استعمال کر سکتے ہیں۔

> 🎓 سرور لیس کو فنکشنز ایز اے سروس (FaaS) بھی کہا جاتا ہے کیونکہ ہر ایونٹ ٹرگر کو کوڈ میں ایک فنکشن کے طور پر نافذ کیا جاتا ہے۔

نام کے باوجود، سرور لیس دراصل سرورز استعمال کرتا ہے۔ نام اس لیے ہے کیونکہ آپ بطور ڈیولپر ان سرورز کی پرواہ نہیں کرتے جو آپ کے کوڈ کو چلانے کے لیے ضروری ہیں، آپ صرف اس بات کی پرواہ کرتے ہیں کہ آپ کا کوڈ ایونٹ کے جواب میں چلایا جائے۔ کلاؤڈ پرووائیڈر کے پاس ایک سرور لیس *رَن ٹائم* ہوتا ہے جو سرورز، نیٹ ورکنگ، اسٹوریج، CPU، میموری اور آپ کے کوڈ کو چلانے کے لیے ضروری ہر چیز کو مختص کرنے کا انتظام کرتا ہے۔ اس ماڈل کا مطلب ہے کہ آپ سرور کے لیے سروس کی ادائیگی نہیں کر سکتے، کیونکہ کوئی سرور نہیں ہے۔ اس کے بجائے آپ اس وقت کے لیے ادائیگی کرتے ہیں جب آپ کا کوڈ چل رہا ہو، اور استعمال ہونے والی میموری کی مقدار کے لیے۔

> 💰 سرور لیس کلاؤڈ میں کوڈ چلانے کے سب سے سستے طریقوں میں سے ایک ہے۔ مثال کے طور پر، لکھنے کے وقت، ایک کلاؤڈ پرووائیڈر آپ کے تمام سرور لیس فنکشنز کو ایک مہینے میں مشترکہ طور پر 1,000,000 بار چلانے کی اجازت دیتا ہے اس سے پہلے کہ وہ آپ سے چارج کرنا شروع کریں، اور اس کے بعد وہ ہر 1,000,000 ایگزیکیوشنز کے لیے US$0.20 چارج کرتے ہیں۔ جب آپ کا کوڈ نہیں چل رہا ہوتا، تو آپ ادائیگی نہیں کرتے۔

بطور IoT ڈیولپر، سرور لیس ماڈل مثالی ہے۔ آپ ایک فنکشن لکھ سکتے ہیں جو کسی بھی IoT ڈیوائس کے ذریعے بھیجے گئے پیغامات کے جواب میں بلایا جاتا ہے جو آپ کی کلاؤڈ ہوسٹڈ IoT سروس سے جڑا ہوا ہے۔ آپ کا کوڈ تمام بھیجے گئے پیغامات کو ہینڈل کرے گا، لیکن صرف ضرورت کے وقت چلایا جائے گا۔

✅ اپنے کوڈ پر نظر ڈالیں جو آپ نے MQTT کے ذریعے پیغامات سننے کے لیے سرور کوڈ کے طور پر لکھا تھا۔ یہ کلاؤڈ میں سرور لیس کے ذریعے کیسے چل سکتا ہے؟ آپ کوڈ کو سرور لیس کمپیوٹنگ کی حمایت کے لیے کیسے تبدیل کرنے کے بارے میں سوچتے ہیں؟

> 💁 سرور لیس ماڈل دیگر کلاؤڈ سروسز میں بھی منتقل ہو رہا ہے، کوڈ چلانے کے علاوہ۔ مثال کے طور پر، کلاؤڈ میں سرور لیس ڈیٹا بیسز دستیاب ہیں جو سرور لیس پرائسنگ ماڈل کا استعمال کرتے ہیں جہاں آپ ڈیٹا بیس کے خلاف کیے گئے ہر ریکویسٹ کے لیے ادائیگی کرتے ہیں، جیسے کہ کوئری یا انسرٹ، عام طور پر اس کام کی بنیاد پر قیمتوں کا تعین کرتے ہیں جو ریکویسٹ کو سروس کرنے کے لیے کیا جاتا ہے۔ مثال کے طور پر، ایک قطار کے خلاف ایک قطار کو منتخب کرنے کا ایک واحد آپریشن ایک پیچیدہ آپریشن سے کم قیمت پر ہوگا جو کئی ٹیبلز کو جوڑتا ہے اور ہزاروں قطاریں واپس کرتا ہے۔

## سرور لیس ایپلیکیشن بنائیں

Microsoft کی سرور لیس کمپیوٹنگ سروس کو Azure Functions کہا جاتا ہے۔

![Azure Functions کا لوگو](../../../../../translated_images/ur/azure-functions-logo.1cfc8e3204c9c44a.webp)

نیچے دی گئی مختصر ویڈیو میں Azure Functions کا جائزہ دیا گیا ہے۔

[![Azure Functions کا جائزہ ویڈیو](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 اوپر دی گئی تصویر پر کلک کریں ویڈیو دیکھنے کے لیے۔

✅ کچھ وقت نکالیں اور Azure Functions کا جائزہ [Microsoft Azure Functions documentation](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) میں پڑھیں۔

Azure Functions لکھنے کے لیے، آپ اپنی پسند کی زبان میں Azure Functions ایپ سے شروع کرتے ہیں۔ Azure Functions Python، JavaScript، TypeScript، C#, F#, Java، اور Powershell کو سپورٹ کرتا ہے۔ اس سبق میں آپ سیکھیں گے کہ Python میں Azure Functions ایپ کیسے لکھی جائے۔

> 💁 Azure Functions کسٹم ہینڈلرز کو بھی سپورٹ کرتا ہے تاکہ آپ اپنے فنکشنز کو کسی بھی زبان میں لکھ سکیں جو HTTP ریکویسٹ کو سپورٹ کرتی ہو، بشمول پرانی زبانیں جیسے COBOL۔

Functions ایپس میں ایک یا زیادہ *ٹرگرز* ہوتے ہیں - فنکشنز جو ایونٹس کے جواب میں چلتے ہیں۔ آپ ایک فنکشن ایپ میں ایک سے زیادہ ٹرگرز رکھ سکتے ہیں، جو سب مشترکہ کنفیگریشن شیئر کرتے ہیں۔ مثال کے طور پر، آپ کی Functions ایپ کے کنفیگریشن فائل میں آپ کے IoT Hub کی کنکشن تفصیلات ہو سکتی ہیں، اور ایپ کے تمام فنکشنز ان تفصیلات کو استعمال کر سکتے ہیں تاکہ ایونٹس کے لیے کنیکٹ اور سن سکیں۔

### ٹاسک - Azure Functions ٹولنگ انسٹال کریں

> لکھنے کے وقت، Azure Functions کوڈ ٹولز Apple Silicon پر Python پروجیکٹس کے ساتھ مکمل طور پر کام نہیں کر رہے ہیں۔ آپ کو Intel-based Mac، Windows PC، یا Linux PC استعمال کرنا ہوگا۔

Azure Functions کی ایک بڑی خصوصیت یہ ہے کہ آپ انہیں مقامی طور پر چلا سکتے ہیں۔ وہی رن ٹائم جو کلاؤڈ میں استعمال ہوتا ہے آپ کے کمپیوٹر پر چلایا جا سکتا ہے، جس سے آپ کو کوڈ لکھنے کی اجازت ملتی ہے جو IoT پیغامات کا جواب دیتا ہے اور اسے مقامی طور پر چلاتا ہے۔ آپ یہاں تک کہ اپنے کوڈ کو ایونٹس کو ہینڈل کرتے ہوئے ڈیبگ کر سکتے ہیں۔ جب آپ اپنے کوڈ سے مطمئن ہوں، تو اسے کلاؤڈ میں ڈیپلائے کیا جا سکتا ہے۔

Azure Functions ٹولنگ CLI کے طور پر دستیاب ہے، جسے Azure Functions Core Tools کہا جاتا ہے۔

1. Azure Functions کور ٹولز انسٹال کریں [Azure Functions Core Tools documentation](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) پر دی گئی ہدایات کے مطابق۔

1. Azure Functions کے لیے VS Code ایکسٹینشن انسٹال کریں۔ یہ ایکسٹینشن Azure Functions بنانے، ڈیبگ کرنے اور ڈیپلائے کرنے کے لیے سپورٹ فراہم کرتی ہے۔ [Azure Functions extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) میں دی گئی ہدایات کے مطابق اس ایکسٹینشن کو VS Code میں انسٹال کریں۔

جب آپ اپنی Azure Functions ایپ کو کلاؤڈ میں ڈیپلائے کرتے ہیں، تو اسے ایپلیکیشن فائلز اور لاگ فائلز جیسی چیزوں کو اسٹور کرنے کے لیے تھوڑی مقدار میں کلاؤڈ اسٹوریج استعمال کرنے کی ضرورت ہوتی ہے۔ جب آپ اپنی Functions ایپ کو مقامی طور پر چلاتے ہیں، تو آپ کو کلاؤڈ اسٹوریج سے کنیکٹ کرنے کی ضرورت ہوتی ہے، لیکن اصل کلاؤڈ اسٹوریج استعمال کرنے کے بجائے، آپ ایک اسٹوریج ایمولیٹر استعمال کر سکتے ہیں جسے [Azurite](https://github.com/Azure/Azurite) کہا جاتا ہے۔ یہ مقامی طور پر چلتا ہے لیکن کلاؤڈ اسٹوریج کی طرح کام کرتا ہے۔

> 🎓 Azure میں، وہ اسٹوریج جو Azure Functions استعمال کرتا ہے اسے Azure Storage Account کہا جاتا ہے۔ یہ اکاؤنٹس فائلز، بلاگز، ٹیبلز میں ڈیٹا یا قطاروں میں ڈیٹا اسٹور کر سکتے ہیں۔ آپ ایک اسٹوریج اکاؤنٹ کو کئی ایپس کے درمیان شیئر کر سکتے ہیں، جیسے کہ ایک Functions ایپ اور ایک ویب ایپ۔

1. Azurite ایک Node.js ایپ ہے، لہذا آپ کو Node.js انسٹال کرنا ہوگا۔ آپ [Node.js website](https://nodejs.org/) پر ڈاؤنلوڈ اور انسٹالیشن کی ہدایات تلاش کر سکتے ہیں۔ اگر آپ Mac استعمال کر رہے ہیں، تو آپ اسے [Homebrew](https://formulae.brew.sh/formula/node) سے بھی انسٹال کر سکتے ہیں۔

1. Azurite انسٹال کریں درج ذیل کمانڈ کے ذریعے (`npm` وہ ٹول ہے جو Node.js انسٹال کرنے پر انسٹال ہوتا ہے):

    ```sh
    npm install -g azurite
    ```

1. Azurite کے لیے ایک فولڈر بنائیں تاکہ وہ ڈیٹا اسٹور کرنے کے لیے استعمال کرے:

    ```sh
    mkdir azurite
    ```

1. Azurite چلائیں، اسے اس نئے فولڈر کو پاس کرتے ہوئے:

    ```sh
    azurite --location azurite
    ```

    Azurite اسٹوریج ایمولیٹر لانچ ہوگا اور مقامی Functions رن ٹائم کے کنیکٹ ہونے کے لیے تیار ہوگا۔

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### ٹاسک - Azure Functions پروجیکٹ بنائیں

Azure Functions CLI ایک نئی Functions ایپ بنانے کے لیے استعمال کیا جا سکتا ہے۔

1. اپنی Functions ایپ کے لیے ایک فولڈر بنائیں اور اس میں جائیں۔ اسے `soil-moisture-trigger` کہیں:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. اس فولڈر کے اندر ایک Python ورچوئل ماحول بنائیں:

    ```sh
    python3 -m venv .venv
    ```

1. ورچوئل ماحول کو ایکٹیویٹ کریں:

    * Windows پر:
        * اگر آپ Command Prompt یا Windows Terminal کے ذریعے Command Prompt استعمال کر رہے ہیں، تو درج ذیل کمانڈ چلائیں:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * اگر آپ PowerShell استعمال کر رہے ہیں، تو درج ذیل کمانڈ چلائیں:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS یا Linux پر، درج ذیل کمانڈ چلائیں:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 یہ کمانڈز اسی جگہ سے چلائی جانی چاہئیں جہاں آپ نے ورچوئل ماحول بنانے کی کمانڈ چلائی تھی۔ آپ کو `.venv` فولڈر میں کبھی بھی جانے کی ضرورت نہیں ہوگی، آپ کو ہمیشہ ایکٹیویٹ کمانڈ اور پیکجز انسٹال کرنے یا کوڈ چلانے کی کمانڈز اسی فولڈر سے چلانی چاہئیں جہاں آپ نے ورچوئل ماحول بنایا تھا۔

1. درج ذیل کمانڈ چلائیں تاکہ اس فولڈر میں ایک Functions ایپ بنائی جا سکے:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    یہ موجودہ فولڈر کے اندر تین فائلز بنائے گا:

    * `host.json` - یہ JSON دستاویز آپ کی Functions ایپ کے لیے سیٹنگز پر مشتمل ہے۔ آپ کو ان سیٹنگز کو تبدیل کرنے کی ضرورت نہیں ہوگی۔
    * `local.settings.json` - یہ JSON دستاویز آپ کی ایپ کے لیے مقامی طور پر چلنے کے وقت استعمال ہونے والی سیٹنگز پر مشتمل ہے، جیسے کہ آپ کے IoT Hub کے لیے کنکشن اسٹرنگز۔ یہ سیٹنگز صرف مقامی ہیں، اور انہیں سورس کوڈ کنٹرول میں شامل نہیں کیا جانا چاہیے۔ جب آپ ایپ کو کلاؤڈ میں ڈیپلائے کرتے ہیں، تو یہ سیٹنگز ڈیپلائے نہیں کی جاتی ہیں، بلکہ آپ کی سیٹنگز ایپلیکیشن سیٹنگز سے لوڈ کی جاتی ہیں۔ یہ سبق کے بعد کے حصے میں شامل کیا جائے گا۔
    * `requirements.txt` - یہ ایک [Pip requirements file](https://pip.p
⚠️ اگر آپ کو فائر وال کی اطلاع ملے، تو رسائی کی اجازت دیں کیونکہ `func` ایپلیکیشن کو آپ کے نیٹ ورک پر پڑھنے اور لکھنے کی ضرورت ہے۔
> ⚠️ اگر آپ macOS استعمال کر رہے ہیں، تو آؤٹ پٹ میں انتباہات ہو سکتے ہیں:
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
> جب تک Functions ایپ صحیح طور پر شروع ہو اور چلنے والے فنکشنز کی فہرست دکھائے، آپ ان انتباہات کو نظر انداز کر سکتے ہیں۔ جیسا کہ [Microsoft Docs Q&A پر اس سوال](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) میں ذکر کیا گیا ہے، یہ نظر انداز کیے جا سکتے ہیں۔

1. `ctrl+c` دباکر Functions ایپ کو بند کریں۔

1. موجودہ فولڈر کو VS Code میں کھولیں، یا تو VS Code کھول کر اس فولڈر کو کھولیں، یا درج ذیل کمانڈ چلائیں:

    ```sh
    code .
    ```

    VS Code آپ کے Functions پروجیکٹ کو پہچان لے گا اور ایک نوٹیفکیشن دکھائے گا:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![نوٹیفکیشن](../../../../../translated_images/ur/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    اس نوٹیفکیشن سے **Yes** منتخب کریں۔

1. یقینی بنائیں کہ Python ورچوئل ماحول VS Code ٹرمینل میں چل رہا ہے۔ اگر ضروری ہو تو اسے ختم کریں اور دوبارہ شروع کریں۔

## IoT Hub ایونٹ ٹرگر بنائیں

Functions ایپ آپ کے سرور لیس کوڈ کا شیل ہے۔ IoT Hub ایونٹس کا جواب دینے کے لیے، آپ اس ایپ میں ایک IoT Hub ٹرگر شامل کر سکتے ہیں۔ یہ ٹرگر ان پیغامات کے سلسلے سے جڑنے کی ضرورت ہے جو IoT Hub کو بھیجے جاتے ہیں اور ان کا جواب دیتے ہیں۔ ان پیغامات کے سلسلے کو حاصل کرنے کے لیے، آپ کے ٹرگر کو IoT Hubs کے *ایونٹ ہب کمپٹیبل اینڈ پوائنٹ* سے جڑنے کی ضرورت ہے۔

IoT Hub ایک اور Azure سروس پر مبنی ہے جسے Azure Event Hubs کہتے ہیں۔ Event Hubs ایک سروس ہے جو آپ کو پیغامات بھیجنے اور وصول کرنے کی اجازت دیتی ہے، IoT Hub اس میں IoT ڈیوائسز کے لیے خصوصیات شامل کرتا ہے۔ IoT Hub سے پیغامات پڑھنے کے لیے آپ اسی طرح جڑتے ہیں جیسے آپ Event Hubs استعمال کر رہے ہوں۔

✅ تحقیق کریں: [Azure Event Hubs دستاویزات](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) میں Event Hubs کا جائزہ پڑھیں۔ بنیادی خصوصیات IoT Hub سے کیسے مختلف ہیں؟

IoT ڈیوائس کو IoT Hub سے جڑنے کے لیے ایک خفیہ کلید استعمال کرنی ہوتی ہے جو یقینی بناتی ہے کہ صرف اجازت یافتہ ڈیوائسز جڑ سکیں۔ یہی اصول پیغامات پڑھنے کے لیے جڑنے پر بھی لاگو ہوتا ہے، آپ کے کوڈ کو ایک کنکشن اسٹرنگ کی ضرورت ہوگی جس میں خفیہ کلید اور IoT Hub کی تفصیلات شامل ہوں۔

> 💁 ڈیفالٹ کنکشن اسٹرنگ جو آپ کو ملتی ہے اس میں **iothubowner** اجازتیں ہوتی ہیں، جو کسی بھی کوڈ کو مکمل اجازت دیتی ہیں۔ مثالی طور پر آپ کو کم سے کم ضروری اجازتوں کے ساتھ جڑنا چاہیے۔ یہ اگلے سبق میں شامل کیا جائے گا۔

ایک بار جب آپ کا ٹرگر جڑ جائے، تو IoT Hub کو بھیجے گئے ہر پیغام کے لیے فنکشن کے اندر موجود کوڈ کو کال کیا جائے گا، چاہے وہ پیغام کسی بھی ڈیوائس نے بھیجا ہو۔ ٹرگر کو پیغام ایک پیرامیٹر کے طور پر دیا جائے گا۔

### کام - ایونٹ ہب کمپٹیبل اینڈ پوائنٹ کنکشن اسٹرنگ حاصل کریں

1. VS Code ٹرمینل سے درج ذیل کمانڈ چلائیں تاکہ IoT Hubs ایونٹ ہب کمپٹیبل اینڈ پوائنٹ کے لیے کنکشن اسٹرنگ حاصل کی جا سکے:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` کو اپنے IoT Hub کے نام سے تبدیل کریں۔

1. VS Code میں `local.settings.json` فائل کھولیں۔ `Values` سیکشن کے اندر درج ذیل اضافی ویلیو شامل کریں:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` کو پچھلے مرحلے سے حاصل کردہ ویلیو سے تبدیل کریں۔ اس کو درست JSON بنانے کے لیے اوپر والی لائن کے بعد ایک کاما شامل کریں۔

### کام - ایونٹ ٹرگر بنائیں

اب آپ ایونٹ ٹرگر بنانے کے لیے تیار ہیں۔

1. VS Code ٹرمینل سے `soil-moisture-trigger` فولڈر کے اندر درج ذیل کمانڈ چلائیں:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    یہ ایک نیا فنکشن بنائے گا جسے `iot-hub-trigger` کہا جاتا ہے۔ ٹرگر IoT Hub کے ایونٹ ہب کمپٹیبل اینڈ پوائنٹ سے جڑے گا، لہذا آپ ایونٹ ہب ٹرگر استعمال کر سکتے ہیں۔ IoT Hub کے لیے کوئی مخصوص ٹرگر نہیں ہے۔

یہ `soil-moisture-trigger` فولڈر کے اندر ایک فولڈر بنائے گا جسے `iot-hub-trigger` کہا جاتا ہے، اور اس میں یہ فنکشن ہوگا۔ اس فولڈر میں درج ذیل فائلیں ہوں گی:

* `__init__.py` - یہ Python کوڈ فائل ہے جو ٹرگر پر مشتمل ہے، Python ماڈیول بنانے کے لیے معیاری Python فائل نام کنونشن استعمال کرتی ہے۔

    اس فائل میں درج ذیل کوڈ ہوگا:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    ٹرگر کا مرکزی حصہ `main` فنکشن ہے۔ یہ فنکشن IoT Hub سے ایونٹس کے ساتھ کال کیا جاتا ہے۔ اس فنکشن میں ایک پیرامیٹر `event` ہوتا ہے جو ایک `EventHubEvent` ہوتا ہے۔ ہر بار جب IoT Hub کو پیغام بھیجا جاتا ہے، یہ فنکشن اس پیغام کو `event` کے طور پر پاس کرتا ہے، ساتھ ہی وہ پراپرٹیز جو آپ نے پچھلے سبق میں دیکھی تھیں۔

    اس فنکشن کا مرکزی حصہ ایونٹ کو لاگ کرتا ہے۔

* `function.json` - یہ ٹرگر کے لیے کنفیگریشن پر مشتمل ہے۔ مرکزی کنفیگریشن `bindings` سیکشن میں ہوتی ہے۔ ایک بائنڈنگ Azure Functions اور دیگر Azure سروسز کے درمیان کنکشن کے لیے استعمال ہونے والی اصطلاح ہے۔ اس فنکشن میں ایونٹ ہب کے لیے ایک ان پٹ بائنڈنگ ہے - یہ ایونٹ ہب سے جڑتا ہے اور ڈیٹا وصول کرتا ہے۔

    > 💁 آپ آؤٹ پٹ بائنڈنگ بھی شامل کر سکتے ہیں تاکہ فنکشن کا آؤٹ پٹ کسی دوسری سروس کو بھیجا جا سکے۔ مثال کے طور پر آپ ایک ڈیٹا بیس کے لیے آؤٹ پٹ بائنڈنگ شامل کر سکتے ہیں اور IoT Hub ایونٹ کو فنکشن سے واپس کر سکتے ہیں، اور یہ خود بخود ڈیٹا بیس میں شامل ہو جائے گا۔

    ✅ تحقیق کریں: [Azure Functions triggers and bindings concepts documentation](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) میں بائنڈنگز کے بارے میں پڑھیں۔

    `bindings` سیکشن میں بائنڈنگ کے لیے کنفیگریشن شامل ہوتی ہے۔ دلچسپی کے ویلیوز یہ ہیں:

  * `"type": "eventHubTrigger"` - یہ فنکشن کو بتاتا ہے کہ اسے ایونٹ ہب سے ایونٹس سننے کی ضرورت ہے۔
  * `"name": "events"` - یہ ایونٹ ہب ایونٹس کے لیے پیرامیٹر کا نام ہے۔ یہ Python کوڈ میں `main` فنکشن کے پیرامیٹر نام سے میل کھاتا ہے۔
  * `"direction": "in"` - یہ ایک ان پٹ بائنڈنگ ہے، ایونٹ ہب سے ڈیٹا فنکشن میں آتا ہے۔
  * `"connection": ""` - یہ اس سیٹنگ کا نام ڈیفائن کرتا ہے جس سے کنکشن اسٹرنگ پڑھنی ہے۔ لوکل طور پر چلانے پر، یہ سیٹنگ `local.settings.json` فائل سے پڑھی جائے گی۔

    > 💁 کنکشن اسٹرنگ کو `function.json` فائل میں اسٹور نہیں کیا جا سکتا، اسے سیٹنگز سے پڑھنا ضروری ہے۔ یہ اس لیے ہے تاکہ آپ غلطی سے اپنی کنکشن اسٹرنگ کو ظاہر نہ کریں۔

1. Azure Functions ٹیمپلیٹ میں [ایک بگ](https://github.com/Azure/azure-functions-templates/issues/1250) کی وجہ سے، `function.json` میں `cardinality` فیلڈ کے لیے غلط ویلیو ہے۔ اس فیلڈ کو `many` سے `one` میں اپ ڈیٹ کریں:

    ```json
    "cardinality": "one",
    ```

1. `function.json` فائل میں `"connection"` کی ویلیو کو اس نئی ویلیو کی طرف پوائنٹ کریں جو آپ نے `local.settings.json` فائل میں شامل کی تھی:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 یاد رکھیں - یہ سیٹنگ کی طرف پوائنٹ کرنا چاہیے، اصل کنکشن اسٹرنگ پر مشتمل نہیں ہونا چاہیے۔

1. کنکشن اسٹرنگ میں `eventHubName` ویلیو شامل ہوتی ہے، لہذا `function.json` فائل میں اس کے لیے ویلیو کو خالی کرنا ضروری ہے۔ اس ویلیو کو خالی اسٹرنگ میں اپ ڈیٹ کریں:

    ```json
    "eventHubName": "",
    ```

### کام - ایونٹ ٹرگر چلائیں

1. یقینی بنائیں کہ آپ IoT Hub ایونٹ مانیٹر نہیں چلا رہے ہیں۔ اگر یہ Functions ایپ کے ساتھ ایک ہی وقت میں چل رہا ہو، تو Functions ایپ ایونٹس کو کنزیوم نہیں کر سکے گی۔

    > 💁 متعدد ایپس IoT Hub اینڈ پوائنٹس سے مختلف *کنزیومر گروپس* استعمال کرتے ہوئے جڑ سکتی ہیں۔ یہ اگلے سبق میں شامل کیے جائیں گے۔

1. Functions ایپ چلانے کے لیے، VS Code ٹرمینل سے درج ذیل کمانڈ چلائیں:

    ```sh
    func start
    ```

    Functions ایپ شروع ہو جائے گی، اور `iot-hub-trigger` فنکشن کو دریافت کرے گی۔ یہ IoT Hub کو پچھلے دن میں بھیجے گئے کسی بھی ایونٹس کو پروسیس کرے گی۔

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

    ہر فنکشن کال کے لیے آؤٹ پٹ میں `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` بلاک ہوگا، تاکہ آپ دیکھ سکیں کہ ہر فنکشن کال میں کتنے پیغامات پروسیس کیے گئے۔

1. یقینی بنائیں کہ آپ کا IoT ڈیوائس چل رہا ہے۔ آپ Functions ایپ میں نئے soil moisture پیغامات دیکھیں گے۔

1. Functions ایپ کو بند کریں اور دوبارہ شروع کریں۔ آپ دیکھیں گے کہ یہ پچھلے پیغامات کو دوبارہ پروسیس نہیں کرے گی، بلکہ صرف نئے پیغامات کو پروسیس کرے گی۔

> 💁 VS Code آپ کے Functions کو ڈیبگ کرنے کی بھی حمایت کرتا ہے۔ آپ کوڈ کی ہر لائن کے آغاز پر بارڈر پر کلک کرکے، یا کوڈ کی لائن پر کرسر رکھ کر اور *Run -> Toggle breakpoint* منتخب کرکے، یا `F9` دباکر بریک پوائنٹس سیٹ کر سکتے ہیں۔ آپ *Run -> Start debugging* منتخب کرکے، `F5` دباکر، یا *Run and debug* پین منتخب کرکے اور **Start debugging** بٹن منتخب کرکے ڈیبگر لانچ کر سکتے ہیں۔ ایسا کرنے سے آپ پروسیس کیے جانے والے ایونٹس کی تفصیلات دیکھ سکتے ہیں۔

#### خرابیوں کا پتہ لگانا

* اگر آپ کو درج ذیل خرابی ملے:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    چیک کریں کہ Azurite چل رہا ہے اور آپ نے `local.settings.json` فائل میں `AzureWebJobsStorage` کو `UseDevelopmentStorage=true` پر سیٹ کیا ہے۔

* اگر آپ کو درج ذیل خرابی ملے:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    چیک کریں کہ آپ نے `function.json` فائل میں `cardinality` کو `one` پر سیٹ کیا ہے۔

* اگر آپ کو درج ذیل خرابی ملے:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    چیک کریں کہ آپ نے `function.json` فائل میں `eventHubName` کو خالی اسٹرنگ پر سیٹ کیا ہے۔

## سرور لیس کوڈ سے ڈائریکٹ میتھڈ ریکویسٹ بھیجیں

اب تک آپ کی Functions ایپ IoT Hub سے ایونٹ ہب کمپٹیبل اینڈ پوائنٹ استعمال کرتے ہوئے پیغامات سن رہی ہے۔ اب آپ کو IoT ڈیوائسز کو کمانڈز بھیجنے کی ضرورت ہے۔ یہ IoT Hub سے *Registry Manager* کے ذریعے مختلف کنکشن استعمال کرکے کیا جاتا ہے۔ Registry Manager ایک ٹول ہے جو آپ کو IoT Hub کے ساتھ رجسٹرڈ ڈیوائسز دیکھنے، اور ان ڈیوائسز کے ساتھ کلاؤڈ سے ڈیوائس پیغامات، ڈائریکٹ میتھڈ ریکویسٹ یا ڈیوائس ٹوئن کو اپ ڈیٹ کرنے کی اجازت دیتا ہے۔ آپ اسے IoT Hub سے ڈیوائسز کو رجسٹر، اپ ڈیٹ یا حذف کرنے کے لیے بھی استعمال کر سکتے ہیں۔

Registry Manager سے جڑنے کے لیے، آپ کو ایک کنکشن اسٹرنگ کی ضرورت ہوگی۔

### کام - Registry Manager کنکشن اسٹرنگ حاصل کریں

1. کنکشن اسٹرنگ حاصل کرنے کے لیے درج ذیل کمانڈ چلائیں:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` کو اپنے IoT Hub کے نام سے تبدیل کریں۔

    کنکشن اسٹرنگ *ServiceConnect* پالیسی کے لیے `--policy-name service` پیرامیٹر استعمال کرکے طلب کی جاتی ہے۔ جب آپ کنکشن اسٹرنگ طلب کرتے ہیں، تو آپ اس کنکشن اسٹرنگ کو اجازت دینے والی اجازتیں مخصوص کر سکتے ہیں۔ ServiceConnect پالیسی آپ کے کوڈ کو IoT ڈیوائسز سے جڑنے اور پیغامات بھیجنے کی اجازت دیتی ہے۔

    ✅ تحقیق کریں: [IoT Hub permissions documentation](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) میں مختلف پالیسیوں کے بارے میں پڑھیں۔

1. VS Code میں `local.settings.json` فائل کھولیں۔ `Values` سیکشن کے اندر درج ذیل اضافی ویلیو شامل کریں:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` کو پچھلے مرحلے سے حاصل کردہ ویلیو سے تبدیل کریں۔ اس کو درست JSON بنانے کے لیے اوپر والی لائن کے بعد ایک کاما شامل کریں۔

### کام - ڈیوائس کو ڈائریکٹ میتھڈ ریکویسٹ بھیجیں

1. Registry Manager کے لیے SDK ایک Pip پیکج کے ذریعے دستیاب ہے۔ `requirements.txt` فائل میں درج ذیل لائن شامل کریں تاکہ اس پیکج پر انحصار شامل کیا جا سکے:

    ```sh
    azure-iot-hub
    ```

1. یقینی بنائیں کہ VS Code ٹرمینل میں ورچوئل ماحول فعال ہے، اور درج ذیل کمانڈ چلائیں تاکہ Pip پیکجز انسٹال کیے جا سکیں:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` فائل میں درج ذیل امپورٹس شامل کریں:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    یہ کچھ سسٹم لائبریریز، Registry Manager کے ساتھ تعامل کرنے اور ڈائریکٹ میتھڈ ریکویسٹ بھیجنے کے لیے لائبریریز امپورٹ کرتا ہے۔

1. `main` میتھڈ کے اندر موجود کوڈ کو ہٹا دیں، لیکن خود میتھڈ کو برقرار رکھیں۔

1. `main` میتھڈ میں درج ذیل کوڈ شامل کریں:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    یہ کوڈ ایونٹ کے باڈی کو نکالتا ہے جس میں IoT ڈیوائس کے ذریعے بھیجا گیا JSON پیغام شامل ہوتا ہے۔

    پھر یہ ایونٹ کے ساتھ دی گئی تشریحات سے ڈیوائس ID حاصل کرتا ہے۔ ایونٹ کے باڈی میں ٹیلیمیٹری کے طور پر بھیجا گیا پیغام شامل ہوتا ہے، جبکہ `iothub_metadata` ڈکشنری میں IoT Hub کے ذریعے سیٹ کی گئی پراپرٹیز شامل ہوتی ہیں جیسے کہ بھیجنے والے ڈیوائس کا ID اور پیغام بھیجنے کا وقت۔

    یہ معلومات پھر لاگ کی جاتی ہیں۔ آپ یہ لاگنگ ٹرمینل میں دیکھیں گے جب آپ Functions ایپ کو لوکل طور پر چلائیں گے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    یہ کوڈ پیغام سے soil moisture حاصل کرتا ہے۔ پھر یہ soil moisture کو چیک کرتا ہے، اور ویلیو کے مطابق `relay_on` یا `relay_off` ڈائریکٹ میتھڈ کے لیے ایک ہیلپر کلاس بناتا ہے۔ میتھڈ ریکویسٹ کو کسی پے لوڈ کی ضرورت نہیں ہوتی، لہذا ایک خالی JSON دستاویز بھیجی جاتی ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
یہ کوڈ `local.settings.json` فائل سے `REGISTRY_MANAGER_CONNECTION_STRING` لوڈ کرتا ہے۔ اس فائل میں موجود قدریں ماحول کے متغیرات کے طور پر دستیاب ہوتی ہیں، اور انہیں `os.environ` فنکشن کے ذریعے پڑھا جا سکتا ہے، جو تمام ماحول کے متغیرات کی ڈکشنری واپس کرتا ہے۔

> 💁 جب یہ کوڈ کلاؤڈ پر تعینات کیا جاتا ہے، تو `local.settings.json` فائل میں موجود قدریں *Application Settings* کے طور پر سیٹ کی جاتی ہیں، اور انہیں ماحول کے متغیرات سے پڑھا جا سکتا ہے۔

اس کے بعد کوڈ کنکشن اسٹرنگ استعمال کرتے ہوئے Registry Manager ہیلپر کلاس کا ایک انسٹینس بناتا ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    یہ کوڈ رجسٹری مینیجر کو بتاتا ہے کہ وہ ٹیلی میٹری بھیجنے والے ڈیوائس کو ڈائریکٹ میتھڈ ریکویسٹ بھیجے۔

    > 💁 ایپ کے ان ورژنز میں جو آپ نے پہلے اسباق میں MQTT استعمال کرتے ہوئے بنائے تھے، ریلے کنٹرول کمانڈز تمام ڈیوائسز کو بھیجے جاتے تھے۔ کوڈ نے فرض کیا تھا کہ آپ کے پاس صرف ایک ڈیوائس ہوگا۔ اس ورژن میں کوڈ ایک ہی ڈیوائس کو میتھڈ ریکویسٹ بھیجتا ہے، لہذا یہ کام کرے گا اگر آپ کے پاس نمی سینسرز اور ریلے کے متعدد سیٹ اپ ہوں، اور صحیح ڈائریکٹ میتھڈ ریکویسٹ صحیح ڈیوائس کو بھیجے۔

1. فنکشنز ایپ چلائیں، اور یقینی بنائیں کہ آپ کا IoT ڈیوائس ڈیٹا بھیج رہا ہے۔ آپ دیکھیں گے کہ پیغامات پروسیس ہو رہے ہیں اور ڈائریکٹ میتھڈ ریکویسٹ بھیجے جا رہے ہیں۔ نمی سینسر کو مٹی کے اندر اور باہر حرکت دیں تاکہ قدریں تبدیل ہوں اور ریلے آن اور آف ہو۔

> 💁 آپ یہ کوڈ [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) فولڈر میں تلاش کر سکتے ہیں۔

## اپنی سرور لیس کوڈ کو کلاؤڈ پر تعینات کریں

آپ کا کوڈ اب مقامی طور پر کام کر رہا ہے، لہذا اگلا مرحلہ فنکشنز ایپ کو کلاؤڈ پر تعینات کرنا ہے۔

### ٹاسک - کلاؤڈ وسائل بنائیں

آپ کی فنکشنز ایپ کو Azure میں فنکشنز ایپ ریسورس پر تعینات کرنے کی ضرورت ہے، جو آپ کے IoT Hub کے لیے بنائے گئے Resource Group کے اندر موجود ہوگا۔ آپ کو Azure میں ایک Storage Account بھی بنانا ہوگا تاکہ مقامی طور پر چلنے والے ایمولیٹڈ اسٹوریج کی جگہ لے سکے۔

1. اسٹوریج اکاؤنٹ بنانے کے لیے درج ذیل کمانڈ چلائیں:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>` کو اپنے اسٹوریج اکاؤنٹ کے لیے ایک نام سے تبدیل کریں۔ یہ نام عالمی طور پر منفرد ہونا چاہیے کیونکہ یہ اسٹوریج اکاؤنٹ تک رسائی کے لیے استعمال ہونے والے URL کا حصہ بنتا ہے۔ اس نام کے لیے آپ صرف چھوٹے حروف اور نمبرز استعمال کر سکتے ہیں، کوئی اور کریکٹر نہیں، اور یہ 24 کریکٹرز تک محدود ہے۔ کچھ ایسا استعمال کریں جیسے `sms` اور آخر میں ایک منفرد شناخت کنندہ شامل کریں، جیسے کچھ بے ترتیب الفاظ یا آپ کا نام۔

    `--sku Standard_LRS` قیمت کے درجے کو منتخب کرتا ہے، سب سے کم قیمت والے جنرل پرپز اکاؤنٹ کو منتخب کرتے ہوئے۔ اسٹوریج کا کوئی مفت درجے نہیں ہے، اور آپ جو استعمال کرتے ہیں اس کی قیمت ادا کرتے ہیں۔ قیمتیں نسبتا کم ہیں، سب سے مہنگا اسٹوریج US$0.05 فی مہینہ فی گیگابائٹ سے کم ہے۔

    ✅ قیمتوں کے بارے میں مزید پڑھیں [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn) پر۔

1. فنکشنز ایپ بنانے کے لیے درج ذیل کمانڈ چلائیں:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>` کو اس مقام سے تبدیل کریں جو آپ نے پچھلے سبق میں Resource Group بناتے وقت استعمال کیا تھا۔

    `<storage_name>` کو اس اسٹوریج اکاؤنٹ کے نام سے تبدیل کریں جو آپ نے پچھلے مرحلے میں بنایا تھا۔

    `<functions_app_name>` کو اپنی فنکشنز ایپ کے لیے ایک منفرد نام سے تبدیل کریں۔ یہ نام عالمی طور پر منفرد ہونا چاہیے کیونکہ یہ فنکشنز ایپ تک رسائی کے لیے استعمال ہونے والے URL کا حصہ بنتا ہے۔ کچھ ایسا استعمال کریں جیسے `soil-moisture-sensor-` اور آخر میں ایک منفرد شناخت کنندہ شامل کریں، جیسے کچھ بے ترتیب الفاظ یا آپ کا نام۔

    `--functions-version 3` آپشن Azure Functions کے استعمال کے ورژن کو سیٹ کرتا ہے۔ ورژن 3 تازہ ترین ورژن ہے۔

    `--os-type Linux` فنکشنز رن ٹائم کو بتاتا ہے کہ ان فنکشنز کی میزبانی کے لیے Linux کو OS کے طور پر استعمال کریں۔ فنکشنز کو Linux یا Windows پر ہوسٹ کیا جا سکتا ہے، استعمال شدہ پروگرامنگ زبان پر منحصر ہے۔ Python ایپس صرف Linux پر سپورٹ کی جاتی ہیں۔

### ٹاسک - اپنی ایپلیکیشن سیٹنگز اپ لوڈ کریں

جب آپ نے اپنی فنکشنز ایپ تیار کی، تو آپ نے `local.settings.json` فائل میں IoT Hub کے کنکشن اسٹرنگز کے لیے کچھ سیٹنگز اسٹور کیں۔ انہیں Azure میں اپنی فنکشنز ایپ کی ایپلیکیشن سیٹنگز میں لکھا جانا چاہیے تاکہ آپ کا کوڈ انہیں استعمال کر سکے۔

> 🎓 `local.settings.json` فائل صرف مقامی ترقیاتی سیٹنگز کے لیے ہے، اور انہیں سورس کوڈ کنٹرول جیسے GitHub میں چیک نہیں کیا جانا چاہیے۔ جب کلاؤڈ پر تعینات کیا جاتا ہے، تو ایپلیکیشن سیٹنگز استعمال کی جاتی ہیں۔ ایپلیکیشن سیٹنگز کلاؤڈ میں ہوسٹ کی گئی key/value جوڑیاں ہیں اور انہیں ماحول کے متغیرات سے پڑھا جاتا ہے، یا تو آپ کے کوڈ میں یا رن ٹائم کے ذریعے جب آپ کا کوڈ IoT Hub سے جڑتا ہے۔

1. فنکشنز ایپ ایپلیکیشن سیٹنگز میں `IOT_HUB_CONNECTION_STRING` سیٹنگ سیٹ کرنے کے لیے درج ذیل کمانڈ چلائیں:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>` کو اس نام سے تبدیل کریں جو آپ نے اپنی فنکشنز ایپ کے لیے استعمال کیا تھا۔

    `<connection string>` کو `local.settings.json` فائل سے `IOT_HUB_CONNECTION_STRING` کی قدر سے تبدیل کریں۔

1. اوپر والا مرحلہ دہرائیں، لیکن `REGISTRY_MANAGER_CONNECTION_STRING` کی قدر کو `local.settings.json` فائل سے متعلقہ قدر پر سیٹ کریں۔

جب آپ یہ کمانڈز چلائیں گے، تو یہ فنکشن ایپ کے لیے تمام ایپلیکیشن سیٹنگز کی فہرست بھی آؤٹ پٹ کریں گے۔ آپ اس کا استعمال یہ چیک کرنے کے لیے کر سکتے ہیں کہ آپ کی قدریں صحیح طریقے سے سیٹ کی گئی ہیں۔

> 💁 آپ ایک قدر پہلے سے سیٹ شدہ دیکھیں گے `AzureWebJobsStorage` کے لیے۔ آپ کی `local.settings.json` فائل میں، یہ قدر مقامی اسٹوریج ایمولیٹر استعمال کرنے کے لیے سیٹ کی گئی تھی۔ جب آپ نے فنکشنز ایپ بنائی، تو آپ نے اسٹوریج اکاؤنٹ کو پیرامیٹر کے طور پر پاس کیا، اور یہ خود بخود اس سیٹنگ میں سیٹ ہو جاتا ہے۔

### ٹاسک - اپنی فنکشنز ایپ کو کلاؤڈ پر تعینات کریں

اب جب کہ فنکشنز ایپ تیار ہے، آپ کا کوڈ تعینات کیا جا سکتا ہے۔

1. اپنی فنکشنز ایپ کو پبلش کرنے کے لیے VS Code ٹرمینل سے درج ذیل کمانڈ چلائیں:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>` کو اس نام سے تبدیل کریں جو آپ نے اپنی فنکشنز ایپ کے لیے استعمال کیا تھا۔

کوڈ کو پیک کیا جائے گا اور فنکشنز ایپ کو بھیجا جائے گا، جہاں اسے تعینات اور شروع کیا جائے گا۔ بہت زیادہ کنسول آؤٹ پٹ ہوگا، جو تعیناتی کی تصدیق اور تعینات کردہ فنکشنز کی فہرست کے ساتھ ختم ہوگا۔ اس صورت میں فہرست میں صرف ٹرگر شامل ہوگا۔

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

یقینی بنائیں کہ آپ کا IoT ڈیوائس چل رہا ہے۔ نمی کی سطح کو تبدیل کریں، مٹی کی نمی کو ایڈجسٹ کرکے، یا سینسر کو مٹی کے اندر اور باہر حرکت دے کر۔ آپ دیکھیں گے کہ ریلے مٹی کی نمی کے تبدیل ہونے پر آن اور آف ہو رہا ہے۔

---

## 🚀 چیلنج

پچھلے سبق میں، آپ نے ریلے کے لیے وقت کا انتظام MQTT پیغامات سے ان سبسکرائب کرکے کیا تھا جب ریلے آن تھا، اور تھوڑی دیر کے لیے جب یہ آف ہوا۔ آپ یہاں یہ طریقہ استعمال نہیں کر سکتے - آپ اپنے IoT Hub ٹرگر کو ان سبسکرائب نہیں کر سکتے۔

سوچیں کہ آپ اپنی فنکشنز ایپ میں اس کو ہینڈل کرنے کے لیے مختلف طریقے کیسے استعمال کر سکتے ہیں۔

## لیکچر کے بعد کوئز

[لیکچر کے بعد کوئز](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## جائزہ اور خود مطالعہ

* سرور لیس کمپیوٹنگ کے بارے میں پڑھیں [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing) پر۔
* Azure میں سرور لیس استعمال کرنے کے بارے میں مزید پڑھیں، بشمول کچھ مزید مثالیں [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn) پر۔
* Azure Functions کے بارے میں مزید جانیں [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions) پر۔

## اسائنمنٹ

[مینول ریلے کنٹرول شامل کریں](assignment.md)

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔