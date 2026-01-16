<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T22:41:45+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "he"
}
-->
# הגדר את המיקרופון והרמקולים שלך - Raspberry Pi

בחלק זה של השיעור, תוסיף מיקרופון ורמקולים ל-Raspberry Pi שלך.

## חומרה

ה-Raspberry Pi זקוק למיקרופון.

ל-Pi אין מיקרופון מובנה, ולכן תצטרך להוסיף מיקרופון חיצוני. ישנן מספר דרכים לעשות זאת:

* מיקרופון USB  
* אוזניות USB  
* רמקול USB משולב  
* מתאם אודיו USB ומיקרופון עם חיבור 3.5 מ"מ  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 מיקרופונים בלוטות' לא נתמכים כולם ב-Raspberry Pi, ולכן אם יש לך מיקרופון או אוזניות בלוטות', ייתכן שתיתקל בבעיות בזיווג או בהקלטת אודיו.

ל-Raspberry Pi יש חיבור אוזניות 3.5 מ"מ. ניתן להשתמש בו כדי לחבר אוזניות, אוזניות עם מיקרופון או רמקול. ניתן גם להוסיף רמקולים באמצעות:

* אודיו HDMI דרך מסך או טלוויזיה  
* רמקולים USB  
* אוזניות USB  
* רמקול USB משולב  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) עם רמקול מחובר, או לחיבור 3.5 מ"מ או ליציאת JST  

## חיבור והגדרת המיקרופון והרמקולים

יש לחבר ולהגדיר את המיקרופון והרמקולים.

### משימה - חיבור והגדרת המיקרופון

1. חבר את המיקרופון באמצעות השיטה המתאימה. לדוגמה, חבר אותו לאחד מחיבורי ה-USB.

1. אם אתה משתמש ב-ReSpeaker 2-Mics Pi HAT, תוכל להסיר את ה-Grove base hat, ואז להתקין את ה-ReSpeaker hat במקומו.

    ![Raspberry Pi עם ReSpeaker hat](../../../../../translated_images/he/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    תצטרך כפתור Grove מאוחר יותר בשיעור זה, אך כפתור כזה מובנה ב-hat הזה, ולכן ה-Grove base hat אינו נחוץ.

    לאחר התקנת ה-hat, תצטרך להתקין דרייברים. עיין בהוראות [Seeed להתחלה](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) להתקנת הדרייברים.

    > ⚠️ ההוראות משתמשות ב-`git` לשכפול מאגר. אם אין לך `git` מותקן ב-Pi שלך, תוכל להתקין אותו על ידי הרצת הפקודה הבאה:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. הרץ את הפקודה הבאה בטרמינל שלך, בין אם על ה-Pi או דרך חיבור SSH מרחוק באמצעות VS Code, כדי לראות מידע על המיקרופון המחובר:

    ```sh
    arecord -l
    ```

    תראה רשימה של מיקרופונים מחוברים. זה ייראה בערך כך:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    בהנחה שיש לך רק מיקרופון אחד, תראה רק ערך אחד. הגדרת מיקרופונים יכולה להיות מסובכת בלינוקס, ולכן הכי קל להשתמש במיקרופון אחד בלבד ולנתק אחרים.

    רשום את מספר הכרטיס, תצטרך אותו מאוחר יותר. בתוצאה למעלה, מספר הכרטיס הוא 1.

### משימה - חיבור והגדרת הרמקול

1. חבר את הרמקולים באמצעות השיטה המתאימה.

1. הרץ את הפקודה הבאה בטרמינל שלך, בין אם על ה-Pi או דרך חיבור SSH מרחוק באמצעות VS Code, כדי לראות מידע על הרמקולים המחוברים:

    ```sh
    aplay -l
    ```

    תראה רשימה של רמקולים מחוברים. זה ייראה בערך כך:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    תמיד תראה `card 0: Headphones` מכיוון שזהו חיבור האוזניות המובנה. אם הוספת רמקולים נוספים, כמו רמקול USB, תראה גם אותו ברשימה.

1. אם אתה משתמש ברמקול נוסף, ולא ברמקול או אוזניות המחוברים לחיבור האוזניות המובנה, עליך להגדיר אותו כברירת מחדל. לשם כך הרץ את הפקודה הבאה:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    פעולה זו תפתח קובץ הגדרות ב-`nano`, עורך טקסט מבוסס טרמינל. גלול למטה באמצעות מקשי החצים במקלדת שלך עד שתמצא את השורה הבאה:

    ```output
    defaults.pcm.card 0
    ```

    שנה את הערך מ-`0` למספר הכרטיס שברצונך להשתמש בו מהרשימה שהתקבלה מהפקודה `aplay -l`. לדוגמה, בתוצאה למעלה יש כרטיס קול שני בשם `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, שמשתמש בכרטיס 1. כדי להשתמש בו, הייתי מעדכן את השורה כך:

    ```output
    defaults.pcm.card 1
    ```

    הגדר ערך זה למספר הכרטיס המתאים. תוכל לנווט למספר באמצעות מקשי החצים במקלדת, ואז למחוק ולהקליד את המספר החדש כרגיל בעת עריכת קבצי טקסט.

1. שמור את השינויים וסגור את הקובץ על ידי לחיצה על `Ctrl+x`. לחץ `y` לשמירת הקובץ, ואז `Enter` כדי לבחור את שם הקובץ.

### משימה - בדיקת המיקרופון והרמקול

1. הרץ את הפקודה הבאה כדי להקליט 5 שניות של אודיו דרך המיקרופון:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    בזמן שהפקודה רצה, השמע רעש למיקרופון, כמו דיבור, שירה, ביטבוקס, נגינה בכלי או כל דבר אחר שמתחשק לך.

1. לאחר 5 שניות, ההקלטה תיעצר. הרץ את הפקודה הבאה כדי להשמיע את האודיו:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    תשמע את האודיו מושמע דרך הרמקולים. כוון את עוצמת הקול ברמקול שלך לפי הצורך.

1. אם עליך לכוון את עוצמת הקול של חיבור המיקרופון המובנה, או לכוון את הגבר המיקרופון, תוכל להשתמש בכלי `alsamixer`. תוכל לקרוא עוד על הכלי הזה בדף [man של Linux alsamixer](https://linux.die.net/man/1/alsamixer).

1. אם אתה מקבל שגיאות בהשמעת האודיו, בדוק את הכרטיס שהגדרת כ-`defaults.pcm.card` בקובץ `alsa.conf`.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.