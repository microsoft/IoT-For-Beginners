<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T20:22:03+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "th"
}
-->
# เข้าใจภาษา

![ภาพรวมของบทเรียนนี้ในรูปแบบ Sketchnote](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.th.jpg)

> Sketchnote โดย [Nitya Narasimhan](https://github.com/nitya) คลิกที่ภาพเพื่อดูเวอร์ชันขนาดใหญ่ขึ้น

## แบบทดสอบก่อนเรียน

[แบบทดสอบก่อนเรียน](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## บทนำ

ในบทเรียนที่แล้ว คุณได้แปลงคำพูดเป็นข้อความ สำหรับการนำไปใช้ในโปรแกรมจับเวลาอัจฉริยะ โค้ดของคุณจำเป็นต้องเข้าใจสิ่งที่พูดออกมา คุณอาจสมมติว่าผู้ใช้จะพูดประโยคที่กำหนดไว้ เช่น "ตั้งเวลาสามนาที" และแยกวิเคราะห์ประโยคนั้นเพื่อหาว่าควรตั้งเวลานานแค่ไหน แต่สิ่งนี้ไม่ค่อยเป็นมิตรกับผู้ใช้ หากผู้ใช้พูดว่า "ตั้งเวลาสำหรับสามนาที" คุณหรือฉันอาจเข้าใจความหมาย แต่โค้ดของคุณจะไม่เข้าใจ เพราะมันคาดหวังเพียงประโยคที่กำหนดไว้

นี่คือจุดที่การเข้าใจภาษามีบทบาท โดยใช้โมเดล AI เพื่อแปลความหมายของข้อความและดึงรายละเอียดที่จำเป็นออกมา เช่น การเข้าใจทั้ง "ตั้งเวลาสามนาที" และ "ตั้งเวลาสำหรับสามนาที" ว่าหมายถึงการตั้งเวลาสามนาที

ในบทเรียนนี้ คุณจะได้เรียนรู้เกี่ยวกับโมเดลการเข้าใจภาษา วิธีสร้างโมเดล ฝึกฝน และใช้งานจากโค้ดของคุณ

ในบทเรียนนี้เราจะครอบคลุม:

* [การเข้าใจภาษา](../../../../../6-consumer/lessons/2-language-understanding)
* [สร้างโมเดลการเข้าใจภาษา](../../../../../6-consumer/lessons/2-language-understanding)
* [เจตนาและเอนทิตี](../../../../../6-consumer/lessons/2-language-understanding)
* [ใช้งานโมเดลการเข้าใจภาษา](../../../../../6-consumer/lessons/2-language-understanding)

## การเข้าใจภาษา

มนุษย์ใช้ภาษาในการสื่อสารมาหลายแสนปี เราสื่อสารด้วยคำพูด เสียง หรือการกระทำ และเข้าใจสิ่งที่พูดออกมา ทั้งความหมายของคำ เสียง หรือการกระทำ รวมถึงบริบทของมัน เราเข้าใจความจริงใจและการเสียดสี ทำให้คำเดียวกันสามารถมีความหมายต่างกันได้ขึ้นอยู่กับน้ำเสียงของเรา

✅ ลองคิดถึงบทสนทนาที่คุณเพิ่งมีเมื่อเร็วๆ นี้ มีส่วนใดของบทสนทนาที่คอมพิวเตอร์จะเข้าใจยากเพราะต้องการบริบทหรือไม่?

การเข้าใจภาษา หรือที่เรียกว่าการเข้าใจภาษาธรรมชาติ เป็นส่วนหนึ่งของสาขาปัญญาประดิษฐ์ที่เรียกว่าการประมวลผลภาษาธรรมชาติ (Natural Language Processing หรือ NLP) และเกี่ยวข้องกับการทำความเข้าใจข้อความ เช่น การอ่านจับใจความ หากคุณเคยใช้ผู้ช่วยเสียง เช่น Alexa หรือ Siri คุณก็เคยใช้บริการการเข้าใจภาษาแล้ว บริการเหล่านี้คือ AI ที่ทำงานเบื้องหลังเพื่อแปลงคำพูด เช่น "Alexa เล่นอัลบั้มล่าสุดของ Taylor Swift" ให้กลายเป็นลูกสาวของฉันที่เต้นในห้องนั่งเล่นกับเพลงโปรดของเธอ

> 💁 แม้คอมพิวเตอร์จะก้าวหน้ามาก แต่ก็ยังมีหนทางอีกยาวไกลกว่าจะเข้าใจข้อความได้อย่างแท้จริง เมื่อเราพูดถึงการเข้าใจภาษาด้วยคอมพิวเตอร์ เราไม่ได้หมายถึงการสื่อสารที่ซับซ้อนเหมือนมนุษย์ แต่หมายถึงการดึงรายละเอียดสำคัญจากคำพูด

ในฐานะมนุษย์ เราเข้าใจภาษาโดยไม่ต้องคิดมาก หากฉันขอให้มนุษย์อีกคน "เล่นอัลบั้มล่าสุดของ Taylor Swift" พวกเขาจะเข้าใจทันทีว่าฉันหมายถึงอะไร แต่สำหรับคอมพิวเตอร์ นี่เป็นเรื่องยาก มันต้องแปลงคำพูดเป็นข้อความ และแยกวิเคราะห์ข้อมูลดังนี้:

* ต้องเล่นเพลง
* เพลงนั้นเป็นของศิลปิน Taylor Swift
* เพลงที่ต้องการคืออัลบั้มที่มีหลายเพลงเรียงตามลำดับ
* Taylor Swift มีหลายอัลบั้ม ดังนั้นต้องเรียงตามลำดับเวลา และเลือกอัลบั้มที่เผยแพร่ล่าสุด

✅ ลองคิดถึงประโยคอื่นๆ ที่คุณพูดเมื่อทำการร้องขอ เช่น การสั่งกาแฟหรือขอให้สมาชิกในครอบครัวส่งของบางอย่างให้คุณ ลองแยกประโยคเหล่านั้นออกเป็นข้อมูลที่คอมพิวเตอร์ต้องดึงออกมาเพื่อเข้าใจประโยค

โมเดลการเข้าใจภาษาเป็นโมเดล AI ที่ถูกฝึกให้ดึงรายละเอียดบางอย่างจากภาษา และถูกฝึกสำหรับงานเฉพาะโดยใช้การเรียนรู้แบบถ่ายโอน (Transfer Learning) เช่นเดียวกับที่คุณฝึกโมเดล Custom Vision ด้วยชุดภาพขนาดเล็ก คุณสามารถนำโมเดลมาแล้วฝึกด้วยข้อความที่คุณต้องการให้เข้าใจ

## สร้างโมเดลการเข้าใจภาษา

![โลโก้ LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.th.png)

คุณสามารถสร้างโมเดลการเข้าใจภาษาโดยใช้ LUIS ซึ่งเป็นบริการการเข้าใจภาษาจาก Microsoft ที่เป็นส่วนหนึ่งของ Cognitive Services

### งาน - สร้างทรัพยากรการเขียน

ในการใช้ LUIS คุณต้องสร้างทรัพยากรการเขียน

1. ใช้คำสั่งต่อไปนี้เพื่อสร้างทรัพยากรการเขียนในกลุ่มทรัพยากร `smart-timer` ของคุณ:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    แทนที่ `<location>` ด้วยตำแหน่งที่คุณใช้เมื่อสร้างกลุ่มทรัพยากร

    > ⚠️ LUIS ไม่สามารถใช้งานได้ในทุกภูมิภาค หากคุณได้รับข้อผิดพลาดดังนี้:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > ให้เลือกภูมิภาคอื่น

    คำสั่งนี้จะสร้างทรัพยากรการเขียน LUIS แบบฟรี

### งาน - สร้างแอปการเข้าใจภาษา

1. เปิดพอร์ทัล LUIS ที่ [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) ในเบราว์เซอร์ของคุณ และลงชื่อเข้าใช้ด้วยบัญชีเดียวกับที่คุณใช้สำหรับ Azure

1. ทำตามคำแนะนำในหน้าต่างเพื่อเลือกการสมัครสมาชิก Azure ของคุณ จากนั้นเลือกทรัพยากร `smart-timer-luis-authoring` ที่คุณเพิ่งสร้าง

1. จากรายการ *Conversation apps* ให้เลือกปุ่ม **New app** เพื่อสร้างแอปพลิเคชันใหม่ ตั้งชื่อแอปใหม่ว่า `smart-timer` และตั้งค่า *Culture* เป็นภาษาของคุณ

    > 💁 มีช่องสำหรับทรัพยากรการพยากรณ์ คุณสามารถสร้างทรัพยากรที่สองสำหรับการพยากรณ์ได้ แต่ทรัพยากรการเขียนแบบฟรีอนุญาตให้ทำการพยากรณ์ได้ 1,000 ครั้งต่อเดือน ซึ่งเพียงพอสำหรับการพัฒนา ดังนั้นคุณสามารถปล่อยช่องนี้ว่างไว้

1. อ่านคู่มือที่ปรากฏขึ้นเมื่อคุณสร้างแอปเพื่อทำความเข้าใจขั้นตอนที่คุณต้องทำเพื่อฝึกโมเดลการเข้าใจภาษา ปิดคู่มือเมื่อคุณอ่านเสร็จ

## เจตนาและเอนทิตี

การเข้าใจภาษาขึ้นอยู่กับ *เจตนา* และ *เอนทิตี* เจตนาคือความตั้งใจของคำพูด เช่น การเล่นเพลง การตั้งเวลา หรือการสั่งอาหาร ส่วนเอนทิตีคือสิ่งที่เจตนาอ้างถึง เช่น อัลบั้ม ความยาวของเวลา หรือประเภทของอาหาร ประโยคแต่ละประโยคที่โมเดลแปลความหมายควรมีเจตนาอย่างน้อยหนึ่งอย่าง และอาจมีเอนทิตีหนึ่งหรือมากกว่านั้น

ตัวอย่าง:

| ประโยค                                             | เจตนา            | เอนทิตี                                   |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| "เล่นอัลบั้มล่าสุดของ Taylor Swift"               | *เล่นเพลง*       | *อัลบั้มล่าสุดของ Taylor Swift*          |
| "ตั้งเวลาสามนาที"                                  | *ตั้งเวลา*       | *สามนาที*                                 |
| "ยกเลิกตัวจับเวลา"                                 | *ยกเลิกตัวจับเวลา* | ไม่มี                                      |
| "สั่งพิซซ่าหน้าสับปะรดขนาดใหญ่สามถาดและสลัดซีซาร์" | *สั่งอาหาร*      | *พิซซ่าหน้าสับปะรดขนาดใหญ่สามถาด*, *สลัดซีซาร์* |

✅ สำหรับประโยคที่คุณคิดไว้ก่อนหน้านี้ เจตนาและเอนทิตีในประโยคนั้นคืออะไร?

ในการฝึก LUIS ขั้นแรกคุณต้องตั้งค่าเอนทิตี เอนทิตีเหล่านี้อาจเป็นรายการคำศัพท์ที่กำหนดไว้ล่วงหน้า หรือเรียนรู้จากข้อความ ตัวอย่างเช่น คุณสามารถให้รายการคำศัพท์ของอาหารในเมนูของคุณ พร้อมคำที่มีความหมายเหมือนกัน (หรือคำพ้องความหมาย) ของแต่ละคำ เช่น *มะเขือยาว* และ *มะเขือม่วง* เป็นคำพ้องความหมายของ *มะเขือม่วง* LUIS ยังมีเอนทิตีที่สร้างไว้ล่วงหน้าที่สามารถใช้งานได้ เช่น ตัวเลขและสถานที่

สำหรับการตั้งเวลา คุณสามารถมีเอนทิตีหนึ่งที่ใช้เอนทิตีตัวเลขที่สร้างไว้ล่วงหน้าสำหรับเวลา และอีกเอนทิตีสำหรับหน่วย เช่น นาทีและวินาที แต่ละหน่วยจะมีหลายรูปแบบเพื่อครอบคลุมรูปแบบเอกพจน์และพหูพจน์ เช่น นาทีและนาทียาว

เมื่อกำหนดเอนทิตีแล้ว คุณจะสร้างเจตนา เจตนาเหล่านี้จะถูกเรียนรู้โดยโมเดลจากประโยคตัวอย่างที่คุณให้ (เรียกว่าการพูด) ตัวอย่างเช่น สำหรับเจตนา *ตั้งเวลา* คุณอาจให้ประโยคตัวอย่างดังนี้:

* `ตั้งเวลาหนึ่งวินาที`
* `ตั้งเวลาหนึ่งนาทีสิบสองวินาที`
* `ตั้งเวลาสามนาที`
* `ตั้งเวลาเก้านาทีสามสิบวินาที`

จากนั้นคุณจะบอก LUIS ว่าส่วนใดของประโยคเหล่านี้ที่ตรงกับเอนทิตี:

![ประโยค "ตั้งเวลาหนึ่งนาทีสิบสองวินาที" ถูกแบ่งเป็นเอนทิตี](../../../../../translated_images/sentence-as-intent-entities.301401696f9922590a99343f5c5d211b710b906f212f0d4d034cee3ffb610272.th.png)

ประโยค `ตั้งเวลาหนึ่งนาทีสิบสองวินาที` มีเจตนาเป็น `ตั้งเวลา` และมีเอนทิตี 2 ตัวพร้อมค่าของแต่ละตัว:

|            | เวลา | หน่วย   |
| ---------- | ---: | ------ |
| 1 นาที     | 1    | นาที   |
| 12 วินาที  | 12   | วินาที |

ในการฝึกโมเดลที่ดี คุณต้องมีประโยคตัวอย่างที่หลากหลายเพื่อครอบคลุมวิธีการต่างๆ ที่ผู้ใช้อาจพูดในสิ่งเดียวกัน

> 💁 เช่นเดียวกับโมเดล AI ใดๆ ยิ่งคุณใช้ข้อมูลที่มากและแม่นยำในการฝึกฝน โมเดลก็จะยิ่งดีขึ้น

✅ ลองคิดถึงวิธีการต่างๆ ที่คุณอาจพูดในสิ่งเดียวกันและคาดหวังให้มนุษย์เข้าใจ

### งาน - เพิ่มเอนทิตีในโมเดลการเข้าใจภาษา

สำหรับตัวจับเวลา คุณต้องเพิ่มเอนทิตี 2 ตัว - หนึ่งสำหรับหน่วยเวลา (นาทีหรือวินาที) และอีกหนึ่งสำหรับจำนวนของนาทีหรือวินาที

คุณสามารถดูคำแนะนำในการใช้พอร์ทัล LUIS ได้ใน [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. จากพอร์ทัล LUIS ให้เลือกแท็บ *Entities* และเพิ่มเอนทิตีที่สร้างไว้ล่วงหน้าชื่อ *number* โดยเลือกปุ่ม **Add prebuilt entity** จากนั้นเลือก *number* จากรายการ

1. สร้างเอนทิตีใหม่สำหรับหน่วยเวลาโดยใช้ปุ่ม **Create** ตั้งชื่อเอนทิตีว่า `time unit` และตั้งค่าประเภทเป็น *List* เพิ่มค่า `minute` และ `second` ในรายการ *Normalized values* โดยเพิ่มรูปแบบเอกพจน์และพหูพจน์ในรายการ *synonyms* กด `return` หลังจากเพิ่มคำพ้องความหมายแต่ละคำเพื่อเพิ่มลงในรายการ

    | Normalized value | Synonyms        |
    | ---------------- | --------------- |
    | minute           | minute, minutes |
    | second           | second, seconds |

### งาน - เพิ่มเจตนาในโมเดลการเข้าใจภาษา

1. จากแท็บ *Intents* ให้เลือกปุ่ม **Create** เพื่อสร้างเจตนาใหม่ ตั้งชื่อเจตนานี้ว่า `set timer`

1. ในตัวอย่าง ให้ป้อนวิธีการต่างๆ ในการตั้งเวลาที่ใช้ทั้งนาที วินาที และการรวมกันของนาทีและวินาที ตัวอย่างอาจเป็น:

    * `ตั้งเวลาหนึ่งวินาที`
    * `ตั้งเวลาสี่นาที`
    * `ตั้งเวลาสี่นาทีหกวินาที`
    * `ตั้งเวลาเก้านาทีสามสิบวินาที`
    * `ตั้งเวลาหนึ่งนาทีสิบสองวินาที`
    * `ตั้งเวลาสามนาที`
    * `ตั้งเวลาสามนาทีหนึ่งวินาที`
    * `ตั้งเวลาสามนาทีหนึ่งวินาที`
    * `ตั้งเวลาหนึ่งนาทีหนึ่งวินาที`
    * `ตั้งเวลาสามสิบวินาที`
    * `ตั้งเวลาหนึ่งวินาที`

    ผสมตัวเลขในรูปแบบคำและตัวเลขเพื่อให้โมเดลเรียนรู้การจัดการทั้งสองแบบ

1. เมื่อคุณป้อนตัวอย่างแต่ละตัวอย่าง LUIS จะเริ่มตรวจจับเอนทิตี และจะขีดเส้นใต้และติดป้ายกำกับที่พบ

    ![ตัวอย่างที่มีตัวเลขและหน่วยเวลาถูกขีดเส้นใต้โดย LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.th.png)

### งาน - ฝึกฝนและทดสอบโมเดล

1. เมื่อกำหนดเอนทิตีและเจตนาแล้ว คุณสามารถฝึกโมเดลโดยใช้ปุ่ม **Train** บนเมนูด้านบน เลือกปุ่มนี้ และโมเดลควรฝึกเสร็จในไม่กี่วินาที ปุ่มจะเป็นสีเทาระหว่างการฝึก และจะกลับมาใช้งานได้เมื่อเสร็จสิ้น

1. เลือกปุ่ม **Test** จากเมนูด้านบนเพื่อทดสอบโมเดลการเข้าใจภาษา ป้อนข้อความ เช่น `ตั้งเวลาห้านาทีสี่วินาที` แล้วกด return ข้อความจะปรากฏในกล่องใต้ช่องข้อความที่คุณพิมพ์ และด้านล่างจะเป็น *เจตนาสูงสุด* หรือเจตนาที่ตรวจพบด้วยความน่าจะเป็นสูงสุด ซึ่งควรเป็น `set timer` ชื่อเจตนาจะตามด้วยความน่าจะเป็นที่เจตนาที่ตรวจพบถูกต้อง

1. เลือกตัวเลือก **Inspect** เพื่อดูรายละเอียดของผลลัพธ์ คุณจะเห็นเจตนาที่มีคะแนนสูงสุดพร้อมความน่าจะเป็นเป็นเปอร์เซ็นต์ รวมถึงรายการเอนทิตีที่ตรวจพบ

1. ปิดหน้าต่าง *Test* เมื่อคุณทดสอบเสร็จ

### งาน - เผยแพร่โมเดล

ในการใช้โมเดลนี้จากโค้ด คุณต้องเผยแพร่ เมื่อเผยแพร่จาก LUIS คุณสามารถเผยแพร่ไปยังสภาพแวดล้อมการทดสอบหรือสภาพแวดล้อมการผลิตได้ ในบทเรียนนี้ สภาพแวดล้อมการทดสอบก็เพียงพอแล้ว

1. จากพอร์ทัล LUIS ให้เลือกปุ่ม **Publish** จากเมนูด้านบน

1. ตรวจสอบให้แน่ใจว่าเลือก *Staging slot* แล้วเลือก **Done** คุณจะเห็นการแจ้งเตือนเมื่อแอปพลิเคชันถูกเผยแพร่

1. คุณสามารถทดสอบสิ่งนี้โดยใช้ curl ในการสร้างคำสั่ง curl คุณต้องใช้ค่าทั้งสาม - endpoint, application ID (App ID) และ API key ซึ่งสามารถเข้าถึงได้จากแท็บ **MANAGE** ที่สามารถเลือกได้จากเมนูด้านบน

    1. จากส่วน *Settings* คัดลอก App ID
1. จากส่วน *Azure Resources* ให้เลือก *Authoring Resource* และคัดลอก *Primary Key* และ *Endpoint URL*

1. รันคำสั่ง curl ต่อไปนี้ใน command prompt หรือ terminal ของคุณ:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    แทนที่ `<endpoint url>` ด้วย Endpoint URL จากส่วน *Azure Resources*

    แทนที่ `<app id>` ด้วย App ID จากส่วน *Settings*

    แทนที่ `<primary key>` ด้วย Primary Key จากส่วน *Azure Resources*

    แทนที่ `<sentence>` ด้วยประโยคที่คุณต้องการทดสอบ

1. ผลลัพธ์ของการเรียกนี้จะเป็นเอกสาร JSON ที่แสดงรายละเอียดของการ query, intent ที่มีคะแนนสูงสุด และรายการ entities ที่ถูกแยกตามประเภท

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    JSON ด้านบนมาจากการ query ด้วย `set a timer for 45 minutes and 12 seconds`:

    * `set timer` เป็น intent ที่มีคะแนนสูงสุดที่ 97%
    * มีการตรวจพบ *number* entities สองตัวคือ `45` และ `12`
    * มีการตรวจพบ *time-unit* entities สองตัวคือ `minute` และ `second`

## ใช้โมเดลการเข้าใจภาษา

เมื่อเผยแพร่แล้ว โมเดล LUIS สามารถถูกเรียกใช้งานจากโค้ดได้ ในบทเรียนก่อนหน้านี้ คุณได้ใช้ IoT Hub เพื่อจัดการการสื่อสารกับบริการคลาวด์ โดยการส่ง telemetry และฟังคำสั่ง ซึ่งเป็นแบบ asynchronous - เมื่อ telemetry ถูกส่ง โค้ดของคุณจะไม่รอการตอบกลับ และหากบริการคลาวด์ล่ม คุณจะไม่ทราบ

สำหรับ smart timer เราต้องการการตอบกลับทันที เพื่อที่เราจะสามารถบอกผู้ใช้ว่า timer ถูกตั้งค่าแล้ว หรือแจ้งเตือนว่าบริการคลาวด์ไม่พร้อมใช้งาน ในการทำเช่นนี้ อุปกรณ์ IoT ของเราจะเรียก web endpoint โดยตรง แทนที่จะพึ่งพา IoT Hub

แทนที่จะเรียก LUIS จากอุปกรณ์ IoT คุณสามารถใช้โค้ดแบบ serverless ที่มี trigger ประเภทอื่น - HTTP trigger สิ่งนี้จะช่วยให้แอปฟังก์ชันของคุณสามารถฟังคำขอ REST และตอบกลับได้ ฟังก์ชันนี้จะเป็น REST endpoint ที่อุปกรณ์ของคุณสามารถเรียกได้

> 💁 แม้ว่าคุณสามารถเรียก LUIS โดยตรงจากอุปกรณ์ IoT ของคุณ แต่การใช้โค้ดแบบ serverless จะดีกว่า ด้วยวิธีนี้เมื่อคุณต้องการเปลี่ยนแอป LUIS ที่คุณเรียก เช่น เมื่อคุณฝึกโมเดลที่ดีกว่าหรือฝึกโมเดลในภาษาอื่น คุณจะต้องอัปเดตโค้ดคลาวด์ของคุณเท่านั้น ไม่ต้องปรับใช้โค้ดใหม่ไปยังอุปกรณ์ IoT หลายพันหรือหลายล้านเครื่อง

### งาน - สร้างแอปฟังก์ชันแบบ serverless

1. สร้าง Azure Functions app ชื่อ `smart-timer-trigger` และเปิดใน VS Code

1. เพิ่ม HTTP trigger ให้กับแอปนี้ชื่อ `speech-trigger` โดยใช้คำสั่งต่อไปนี้จากภายใน terminal ของ VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    สิ่งนี้จะสร้าง HTTP trigger ชื่อ `text-to-timer`

1. ทดสอบ HTTP trigger โดยรันแอปฟังก์ชัน เมื่อรันคุณจะเห็น endpoint แสดงใน output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    ทดสอบโดยโหลด URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) ในเบราว์เซอร์ของคุณ

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### งาน - ใช้โมเดลการเข้าใจภาษา

1. SDK สำหรับ LUIS มีให้ใช้งานผ่าน Pip package เพิ่มบรรทัดต่อไปนี้ในไฟล์ `requirements.txt` เพื่อเพิ่ม dependency บนแพ็กเกจนี้:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. ตรวจสอบให้แน่ใจว่า terminal ของ VS Code มี virtual environment เปิดใช้งานอยู่ และรันคำสั่งต่อไปนี้เพื่อติดตั้ง Pip packages:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 หากคุณพบข้อผิดพลาด คุณอาจต้องอัปเกรด pip ด้วยคำสั่งต่อไปนี้:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. เพิ่มรายการใหม่ในไฟล์ `local.settings.json` สำหรับ LUIS API Key, Endpoint URL และ App ID จากแท็บ **MANAGE** ในพอร์ทัล LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    แทนที่ `<endpoint url>` ด้วย Endpoint URL จากส่วน *Azure Resources* ในแท็บ **MANAGE** ซึ่งจะเป็น `https://<location>.api.cognitive.microsoft.com/`

    แทนที่ `<app id>` ด้วย App ID จากส่วน *Settings* ในแท็บ **MANAGE**

    แทนที่ `<primary key>` ด้วย Primary Key จากส่วน *Azure Resources* ในแท็บ **MANAGE**

1. เพิ่ม imports ต่อไปนี้ในไฟล์ `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    สิ่งนี้จะ import ไลบรารีระบบบางตัว รวมถึงไลบรารีสำหรับการโต้ตอบกับ LUIS

1. ลบเนื้อหาในเมธอด `main` และเพิ่มโค้ดต่อไปนี้:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    โค้ดนี้โหลดค่าที่คุณเพิ่มในไฟล์ `local.settings.json` สำหรับแอป LUIS ของคุณ สร้าง credentials object ด้วย API key ของคุณ จากนั้นสร้าง LUIS client object เพื่อโต้ตอบกับแอป LUIS ของคุณ

1. HTTP trigger นี้จะถูกเรียกโดยส่งข้อความที่ต้องการเข้าใจเป็น JSON โดยมีข้อความอยู่ใน property ชื่อ `text` โค้ดต่อไปนี้จะดึงค่าจาก body ของคำขอ HTTP และบันทึกลงใน console เพิ่มโค้ดนี้ในฟังก์ชัน `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. การทำนายจะถูกขอจาก LUIS โดยการส่งคำขอทำนาย - เอกสาร JSON ที่มีข้อความที่ต้องการทำนาย สร้างคำขอนี้ด้วยโค้ดต่อไปนี้:

    ```python
    prediction_request = { 'query' : text }
    ```

1. คำขอนี้สามารถถูกส่งไปยัง LUIS โดยใช้ staging slot ที่แอปของคุณถูกเผยแพร่ไป:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. การตอบกลับการทำนายจะมี intent ที่มีคะแนนสูงสุด พร้อมกับ entities หาก intent ที่มีคะแนนสูงสุดคือ `set timer` entities สามารถถูกอ่านเพื่อรับเวลาที่ต้องการสำหรับ timer:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    * `number` entities จะเป็น array ของตัวเลข เช่น หากคุณพูดว่า *"Set a four minute 17 second timer."* `number` array จะมี 2 ตัวเลข - 4 และ 17
    * `time unit` entities จะเป็น array ของ arrays ของ strings โดยแต่ละ time unit จะเป็น array ของ strings ภายใน array เช่น หากคุณพูดว่า *"Set a four minute 17 second timer."* `time unit` array จะมี 2 arrays โดยแต่ละ array มีค่าเดียว - `['minute']` และ `['second']`

    JSON ของ entities สำหรับ *"Set a four minute 17 second timer."* คือ:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    โค้ดนี้ยังนิยาม count สำหรับเวลารวมของ timer ในวินาที ซึ่งจะถูกเติมค่าจาก entities

1. entities ไม่ได้ถูกเชื่อมโยง แต่เราสามารถทำสมมติฐานเกี่ยวกับพวกมันได้ พวกมันจะอยู่ในลำดับที่พูด ดังนั้นตำแหน่งใน array สามารถใช้เพื่อกำหนดว่าตัวเลขใดตรงกับ time unit ใด เช่น:

    * *"Set a 30 second timer"* - จะมีตัวเลขเดียว `30` และ time unit เดียว `second` ดังนั้นตัวเลขเดียวจะตรงกับ time unit เดียว
    * *"Set a 2 minute and 30 second timer"* - จะมีตัวเลขสองตัว `2` และ `30` และ time unit สองตัว `minute` และ `second` ดังนั้นตัวเลขแรกจะตรงกับ time unit แรก (2 นาที) และตัวเลขที่สองจะตรงกับ time unit ที่สอง (30 วินาที)

    โค้ดต่อไปนี้จะนับจำนวน items ใน number entities และใช้สิ่งนี้เพื่อดึง item แรกจากแต่ละ array จากนั้น item ที่สอง และอื่นๆ เพิ่มโค้ดนี้ภายใน `if` block:

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    สำหรับ *"Set a four minute 17 second timer."* สิ่งนี้จะวนลูปสองครั้ง โดยให้ค่าดังนี้:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. ภายในลูปนี้ ใช้ตัวเลขและ time unit เพื่อคำนวณเวลารวมสำหรับ timer โดยเพิ่ม 60 วินาทีสำหรับแต่ละนาที และจำนวนวินาทีสำหรับ seconds ใดๆ

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. นอกลูปนี้ผ่าน entities บันทึกเวลารวมสำหรับ timer:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. จำนวนวินาทีต้องถูกส่งกลับจากฟังก์ชันเป็นการตอบกลับ HTTP ที่ท้าย `if` block เพิ่มสิ่งต่อไปนี้:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    โค้ดนี้สร้าง payload ที่มีจำนวนวินาทีรวมสำหรับ timer แปลงเป็น JSON string และส่งกลับเป็นผลลัพธ์ HTTP พร้อมสถานะ 200 ซึ่งหมายถึงการเรียกสำเร็จ

1. สุดท้าย นอก `if` block จัดการกรณีที่ intent ไม่ถูกจดจำโดยการส่งกลับ error code:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 เป็นสถานะสำหรับ *not found*

1. รันแอปฟังก์ชันและทดสอบโดยใช้ curl

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    แทนที่ `<text>` ด้วยข้อความของคำขอ เช่น `set a 2 minutes 27 second timer`

    คุณจะเห็น output ต่อไปนี้จากแอปฟังก์ชัน:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    การเรียก curl จะส่งกลับดังนี้:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    จำนวนวินาทีสำหรับ timer อยู่ในค่า `"seconds"`

> 💁 คุณสามารถค้นหาโค้ดนี้ในโฟลเดอร์ [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions)

### งาน - ทำให้ฟังก์ชันของคุณพร้อมใช้งานสำหรับอุปกรณ์ IoT ของคุณ

1. สำหรับอุปกรณ์ IoT ของคุณที่จะเรียก REST endpoint ของคุณ มันจะต้องทราบ URL เมื่อคุณเข้าถึงก่อนหน้านี้ คุณใช้ `localhost` ซึ่งเป็นทางลัดเพื่อเข้าถึง REST endpoints บนเครื่องของคุณเอง เพื่อให้อุปกรณ์ IoT ของคุณเข้าถึงได้ คุณต้องเผยแพร่ไปยังคลาวด์ หรือรับ IP address เพื่อเข้าถึงในเครื่อง

    > ⚠️ หากคุณใช้ Wio Terminal จะง่ายกว่าที่จะรันแอปฟังก์ชันในเครื่อง เนื่องจากจะมี dependency บนไลบรารีที่หมายความว่าคุณไม่สามารถปรับใช้แอปฟังก์ชันในแบบเดียวกับที่คุณเคยทำมาก่อน รันแอปฟังก์ชันในเครื่องและเข้าถึงผ่าน IP address ของคอมพิวเตอร์ของคุณ หากคุณต้องการปรับใช้ในคลาวด์ ข้อมูลจะถูกให้ในบทเรียนถัดไปเกี่ยวกับวิธีการทำเช่นนี้

    * เผยแพร่ Functions app - ทำตามคำแนะนำในบทเรียนก่อนหน้าเพื่อเผยแพร่แอปฟังก์ชันของคุณไปยังคลาวด์ เมื่อเผยแพร่แล้ว URL จะเป็น `https://<APP_NAME>.azurewebsites.net/api/text-to-timer` โดยที่ `<APP_NAME>` จะเป็นชื่อของแอปฟังก์ชันของคุณ ตรวจสอบให้แน่ใจว่าได้เผยแพร่ local settings ของคุณด้วย

      เมื่อทำงานกับ HTTP triggers พวกมันจะถูกป้องกันโดยค่าเริ่มต้นด้วย function app key เพื่อรับ key นี้ รันคำสั่งต่อไปนี้:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      คัดลอกค่าของ entry `default` จากส่วน `functionKeys`

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      key นี้จะต้องถูกเพิ่มเป็น query parameter ใน URL ดังนั้น URL สุดท้ายจะเป็น `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>` โดยที่ `<APP_NAME>` จะเป็นชื่อของแอปฟังก์ชันของคุณ และ `<FUNCTION_KEY>` จะเป็น default function key ของคุณ

      > 💁 คุณสามารถเปลี่ยนประเภทการอนุญาตของ HTTP trigger โดยใช้การตั้งค่า `authlevel` ในไฟล์ `function.json` คุณสามารถอ่านเพิ่มเติมเกี่ยวกับสิ่งนี้ใน [ส่วนการตั้งค่าของเอกสาร Azure Functions HTTP trigger บน Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration)

    * รันแอปฟังก์ชันในเครื่อง และเข้าถึงโดยใช้ IP address - คุณสามารถรับ IP address ของคอมพิวเตอร์ของคุณบนเครือข่ายในเครื่อง และใช้สิ่งนั้นเพื่อสร้าง URL

      ค้นหา IP address ของคุณ:

      * บน Windows 10 ทำตาม [คู่มือการค้นหา IP address](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * บน macOS ทำตาม [วิธีการค้นหา IP address บน Mac guide](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * บน linux ทำตามส่วนการค้นหา private IP address ใน [วิธีการค้นหา IP address ใน Linux guide](https://opensource.com/article/18/5/how-find-ip-address-linux)

      เมื่อคุณมี IP address ของคุณแล้ว คุณจะสามารถเข้าถึงฟังก์ชันที่ `http://`

:7071/api/text-to-timer` โดยที่ `<IP_ADDRESS>` จะเป็นที่อยู่ IP ของคุณ เช่น `http://192.168.1.10:7071/api/text-to-timer`

      > 💁 โปรดทราบว่านี่ใช้พอร์ต 7071 ดังนั้นหลังจากที่อยู่ IP คุณจะต้องใส่ `:7071`

      > 💁 สิ่งนี้จะทำงานได้ก็ต่อเมื่ออุปกรณ์ IoT ของคุณอยู่ในเครือข่ายเดียวกันกับคอมพิวเตอร์ของคุณ

1. ทดสอบ endpoint โดยการเข้าถึงผ่าน curl

---

## 🚀 ความท้าทาย

มีหลายวิธีในการร้องขอสิ่งเดียวกัน เช่น การตั้งเวลา ลองคิดถึงวิธีต่าง ๆ ในการทำสิ่งนี้ และใช้วิธีเหล่านั้นเป็นตัวอย่างในแอป LUIS ของคุณ ทดสอบวิธีเหล่านี้เพื่อดูว่าโมเดลของคุณสามารถจัดการกับวิธีการร้องขอการตั้งเวลาในรูปแบบต่าง ๆ ได้ดีเพียงใด

## แบบทดสอบหลังการบรรยาย

[แบบทดสอบหลังการบรรยาย](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## ทบทวนและศึกษาด้วยตนเอง

* อ่านเพิ่มเติมเกี่ยวกับ LUIS และความสามารถของมันได้ที่ [หน้าคู่มือ Language Understanding (LUIS) บน Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* อ่านเพิ่มเติมเกี่ยวกับการทำความเข้าใจภาษาธรรมชาติได้ที่ [หน้าการทำความเข้าใจภาษาธรรมชาติบน Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* อ่านเพิ่มเติมเกี่ยวกับ HTTP triggers ได้ที่ [หน้าคู่มือ Azure Functions HTTP trigger บน Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## งานที่ได้รับมอบหมาย

[ยกเลิกการตั้งเวลา](assignment.md)

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้