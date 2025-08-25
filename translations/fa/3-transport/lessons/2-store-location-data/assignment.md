<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-25T23:10:18+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "fa"
}
-->
# بررسی اتصال‌های تابع

## دستورالعمل‌ها

اتصال‌های تابع به کد شما اجازه می‌دهند که با بازگرداندن داده‌ها از تابع `main`، بلو‌ب‌ها را در ذخیره‌سازی بلو‌ب ذخیره کنید. حساب ذخیره‌سازی Azure، مجموعه و جزئیات دیگر در فایل `function.json` پیکربندی می‌شوند.

هنگام کار با Azure یا سایر فناوری‌های مایکروسافت، بهترین منبع اطلاعات [مستندات مایکروسافت در docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) است. در این تکلیف، شما باید مستندات اتصال‌های Azure Functions را مطالعه کنید تا نحوه تنظیم اتصال خروجی را بیاموزید.

برخی صفحات که می‌توانید برای شروع مطالعه کنید عبارتند از:

* [مفاهیم اتصال‌ها و محرک‌های Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [بررسی اتصال‌های ذخیره‌سازی بلو‌ب برای Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [اتصال خروجی ذخیره‌سازی بلو‌ب برای Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## معیار ارزیابی

| معیار | عالی | قابل قبول | نیاز به بهبود |
| ------ | ----- | ---------- | ------------- |
| پیکربندی اتصال خروجی ذخیره‌سازی بلو‌ب | توانست اتصال خروجی را پیکربندی کند، بلو‌ب را بازگرداند و آن را با موفقیت در ذخیره‌سازی بلو‌ب ذخیره کند | توانست اتصال خروجی را پیکربندی کند یا بلو‌ب را بازگرداند اما نتوانست آن را با موفقیت در ذخیره‌سازی بلو‌ب ذخیره کند | نتوانست اتصال خروجی را پیکربندی کند |

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حیاتی، توصیه می‌شود از ترجمه انسانی حرفه‌ای استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.