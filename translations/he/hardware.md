# חומרה

ה-**T** ב-IoT הוא **דברים** ומתייחס למכשירים שמתקשרים עם העולם סביבנו. כל פרויקט מבוסס על חומרה אמיתית הזמינה לסטודנטים ולחובבים. יש לנו שתי אפשרויות של חומרת IoT לשימוש, בהתאם להעדפה אישית, ידע או העדפות בשפת תכנות, מטרות לימוד וזמינות. בנוסף, סיפקנו גרסה של 'חומרה וירטואלית' עבור אלו שאין להם גישה לחומרה, או שרוצים ללמוד יותר לפני שמתחייבים לרכישה.

> 💁 אין צורך לרכוש חומרת IoT כדי להשלים את המשימות. ניתן לבצע הכל באמצעות חומרה וירטואלית.

אפשרויות החומרה הפיזית הן Arduino או Raspberry Pi. לכל פלטפורמה יש יתרונות וחסרונות משלה, ואלו מכוסים באחד השיעורים הראשונים. אם עדיין לא החלטתם על פלטפורמת חומרה, תוכלו לעיין [בשיעור השני של הפרויקט הראשון](./1-getting-started/lessons/2-deeper-dive/README.md) כדי להחליט איזו פלטפורמת חומרה מעניינת אתכם ללמוד.

החומרה הספציפית נבחרה כדי להפחית את המורכבות של השיעורים והמשימות. למרות שחומרה אחרת עשויה לעבוד, איננו יכולים להבטיח שכל המשימות יתמכו במכשיר שלכם ללא חומרה נוספת. לדוגמה, לרבים ממכשירי Arduino אין WiFi, שהוא הכרחי כדי להתחבר לענן - ה-Wio Terminal נבחר מכיוון שיש לו WiFi מובנה.

תצטרכו גם כמה פריטים שאינם טכניים, כמו אדמה או צמח בעציץ, ופירות או ירקות.

## רכישת הערכות

![לוגו של Seeed Studios](../../translated_images/he/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios באדיבותם סיפקו את כל החומרה כערכות קלות לרכישה:

### Arduino - Wio Terminal

**[IoT למתחילים עם Seeed ו-Microsoft - ערכת התחלה של Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![ערכת החומרה של Wio Terminal](../../translated_images/he/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT למתחילים עם Seeed ו-Microsoft - ערכת התחלה של Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![ערכת החומרה של Raspberry Pi Terminal](../../translated_images/he/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

כל קוד המכשיר עבור Arduino נכתב ב-C++. כדי להשלים את כל המשימות תצטרכו את הדברים הבאים:

### חומרת Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *אופציונלי* - כבל USB-C או מתאם USB-A ל-USB-C. ל-Wio Terminal יש יציאת USB-C ומגיע עם כבל USB-C ל-USB-A. אם למחשב שלכם יש רק יציאות USB-C, תצטרכו כבל USB-C או מתאם USB-A ל-USB-C.

### חיישנים ומפעילים ספציפיים ל-Arduino

אלו רלוונטיים לשימוש במכשיר Arduino Wio Terminal, ואינם רלוונטיים לשימוש ב-Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* אוזניות או רמקול אחר עם חיבור 3.5 מ"מ, או רמקול JST כמו:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* כרטיס microSD בגודל 16GB או פחות, יחד עם מתאם לשימוש בכרטיס SD עם המחשב אם אין לכם אחד מובנה. **שימו לב** - ה-Wio Terminal תומך רק בכרטיסי SD עד 16GB, הוא אינו תומך בקיבולות גבוהות יותר.

## Raspberry Pi

כל קוד המכשיר עבור Raspberry Pi נכתב ב-Python. כדי להשלים את כל המשימות תצטרכו את הדברים הבאים:

### חומרת Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 גרסאות החל מ-Pi 2B ומעלה אמורות לעבוד עם המשימות בשיעורים אלו. אם אתם מתכננים להריץ את VS Code ישירות על ה-Pi, אז תצטרכו Pi 4 עם 2GB או יותר של RAM. אם אתם מתכוונים לגשת ל-Pi מרחוק, כל Pi 2B ומעלה יעבוד.
* כרטיס microSD (ניתן להשיג ערכות Raspberry Pi שמגיעות עם כרטיס microSD), יחד עם מתאם לשימוש בכרטיס SD עם המחשב אם אין לכם אחד מובנה.
* ספק כוח USB (ניתן להשיג ערכות Raspberry Pi 4 שמגיעות עם ספק כוח). אם אתם משתמשים ב-Raspberry Pi 4 תצטרכו ספק כוח USB-C, מכשירים מוקדמים יותר דורשים ספק כוח micro-USB.

### חיישנים ומפעילים ספציפיים ל-Raspberry Pi

אלו רלוונטיים לשימוש ב-Raspberry Pi, ואינם רלוונטיים לשימוש במכשיר Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [מודול מצלמה של Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* מיקרופון ורמקול:

  השתמשו באחד מהבאים (או שווה ערך):
  * כל מיקרופון USB עם כל רמקול USB, או רמקול עם כבל חיבור 3.5 מ"מ, או שימוש ביציאת אודיו HDMI אם ה-Raspberry Pi מחובר למסך או טלוויזיה עם רמקולים
  * כל אוזניות USB עם מיקרופון מובנה
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) עם
    * אוזניות או רמקול אחר עם חיבור 3.5 מ"מ, או רמקול JST כמו:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [חיישן אור Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [כפתור Grove](https://www.seeedstudio.com/Grove-Button.html)

## חיישנים ומפעילים

רוב החיישנים והמפעילים הדרושים משמשים הן במסלול הלימוד של Arduino והן במסלול הלימוד של Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [חיישן לחות וטמפרטורה Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [חיישן לחות קרקע קיבולי Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [ממסר Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [חיישן מרחק Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## חומרה אופציונלית

השיעורים על השקיה אוטומטית עובדים באמצעות ממסר. כאופציה, ניתן לחבר את הממסר למשאבת מים המופעלת באמצעות USB באמצעות החומרה המפורטת למטה.

* [משאבת מים 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [מסוף USB](https://www.adafruit.com/product/3628)
* צינורות סיליקון
* חוטים אדומים ושחורים
* מברג קטן שטוח

## חומרה וירטואלית

המסלול של חומרה וירטואלית יספק סימולטורים עבור החיישנים והמפעילים, המיושמים ב-Python. בהתאם לזמינות החומרה שלכם, תוכלו להריץ זאת על מכשיר הפיתוח הרגיל שלכם, כמו Mac, PC, או להריץ זאת על Raspberry Pi ולסמלץ רק את החומרה שאין לכם. לדוגמה, אם יש לכם את מצלמת Raspberry Pi אך לא את חיישני Grove, תוכלו להריץ את קוד המכשיר הווירטואלי על ה-Pi ולסמלץ את חיישני Grove, אך להשתמש במצלמה פיזית.

החומרה הווירטואלית תשתמש בפרויקט [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

כדי להשלים את השיעורים הללו תצטרכו מצלמת רשת, מיקרופון ופלט אודיו כמו רמקולים או אוזניות. אלו יכולים להיות מובנים או חיצוניים, וצריכים להיות מוגדרים לעבוד עם מערכת ההפעלה שלכם ולהיות זמינים לשימוש מכל היישומים.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.