<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T21:28:20+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "th"
}
-->
# สร้างไฟกลางคืน - ฮาร์ดแวร์ IoT เสมือน

ในส่วนนี้ของบทเรียน คุณจะเพิ่ม LED ลงในอุปกรณ์ IoT เสมือนของคุณและใช้มันเพื่อสร้างไฟกลางคืน

## ฮาร์ดแวร์เสมือน

ไฟกลางคืนต้องการตัวกระตุ้นหนึ่งตัว ซึ่งสร้างขึ้นในแอป CounterFit

ตัวกระตุ้นนี้คือ **LED** ในอุปกรณ์ IoT จริง มันจะเป็น [ไดโอดเปล่งแสง](https://wikipedia.org/wiki/Light-emitting_diode) ที่เปล่งแสงเมื่อมีกระแสไฟฟ้าไหลผ่าน สำหรับตัวกระตุ้นแบบดิจิทัลนี้จะมี 2 สถานะ คือ เปิดและปิด การส่งค่า 1 จะเปิด LED และการส่งค่า 0 จะปิด LED

ตรรกะของไฟกลางคืนในรูปแบบ pseudo-code คือ:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### เพิ่มตัวกระตุ้นใน CounterFit

เพื่อใช้ LED เสมือน คุณต้องเพิ่มมันลงในแอป CounterFit

#### งาน - เพิ่มตัวกระตุ้นใน CounterFit

เพิ่ม LED ลงในแอป CounterFit

1. ตรวจสอบให้แน่ใจว่าแอปเว็บ CounterFit กำลังทำงานจากส่วนก่อนหน้าของงานนี้ หากไม่ ให้เริ่มต้นและเพิ่มเซ็นเซอร์แสงอีกครั้ง

1. สร้าง LED:

    1. ในกล่อง *Create actuator* ในแถบ *Actuator* ให้คลิกที่กล่อง *Actuator type* และเลือก *LED*

    1. ตั้งค่า *Pin* เป็น *5*

    1. เลือกปุ่ม **Add** เพื่อสร้าง LED บน Pin 5

    ![การตั้งค่า LED](../../../../../translated_images/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.th.png)

    LED จะถูกสร้างขึ้นและปรากฏในรายการตัวกระตุ้น

    ![LED ที่ถูกสร้างขึ้น](../../../../../translated_images/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.th.png)

    เมื่อ LED ถูกสร้างขึ้นแล้ว คุณสามารถเปลี่ยนสีได้โดยใช้ตัวเลือก *Color* เลือกปุ่ม **Set** เพื่อเปลี่ยนสีหลังจากที่คุณเลือกแล้ว

### เขียนโปรแกรมไฟกลางคืน

ตอนนี้คุณสามารถเขียนโปรแกรมไฟกลางคืนโดยใช้เซ็นเซอร์แสงและ LED ใน CounterFit

#### งาน - เขียนโปรแกรมไฟกลางคืน

เขียนโปรแกรมไฟกลางคืน

1. เปิดโปรเจกต์ไฟกลางคืนใน VS Code ที่คุณสร้างขึ้นในส่วนก่อนหน้าของงานนี้ ปิดและสร้างเทอร์มินัลใหม่เพื่อให้แน่ใจว่ามันกำลังทำงานโดยใช้ virtual environment หากจำเป็น

1. เปิดไฟล์ `app.py`

1. เพิ่มโค้ดต่อไปนี้ในไฟล์ `app.py` เพื่อเชื่อมต่อกับไลบรารีที่จำเป็น โค้ดนี้ควรถูกเพิ่มไว้ด้านบน ใต้บรรทัด `import` อื่น ๆ

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    คำสั่ง `from counterfit_shims_grove.grove_led import GroveLed` นำเข้า `GroveLed` จากไลบรารี Python ของ CounterFit Grove shim ไลบรารีนี้มีโค้ดสำหรับโต้ตอบกับ LED ที่สร้างขึ้นในแอป CounterFit

1. เพิ่มโค้ดต่อไปนี้หลังจากการประกาศ `light_sensor` เพื่อสร้างอินสแตนซ์ของคลาสที่จัดการ LED:

    ```python
    led = GroveLed(5)
    ```

    บรรทัด `led = GroveLed(5)` สร้างอินสแตนซ์ของคลาส `GroveLed` ที่เชื่อมต่อกับ pin **5** ซึ่งเป็น CounterFit Grove pin ที่ LED เชื่อมต่ออยู่

1. เพิ่มการตรวจสอบภายในลูป `while` และก่อน `time.sleep` เพื่อเช็คระดับแสงและเปิดหรือปิด LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    โค้ดนี้ตรวจสอบค่า `light` หากค่านี้น้อยกว่า 300 จะเรียกใช้เมธอด `on` ของคลาส `GroveLed` ซึ่งส่งค่าดิจิทัล 1 ไปยัง LED เพื่อเปิดมัน หากค่าระดับแสงมากกว่าหรือเท่ากับ 300 จะเรียกใช้เมธอด `off` ซึ่งส่งค่าดิจิทัล 0 ไปยัง LED เพื่อปิดมัน

    > 💁 โค้ดนี้ควรถูกเยื้องให้อยู่ในระดับเดียวกับบรรทัด `print('Light level:', light)` เพื่อให้อยู่ภายในลูป while!

1. จากเทอร์มินัลใน VS Code รันคำสั่งต่อไปนี้เพื่อรันแอป Python ของคุณ:

    ```sh
    python3 app.py
    ```

    ค่าระดับแสงจะถูกแสดงผลในคอนโซล

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. เปลี่ยน *Value* หรือการตั้งค่า *Random* เพื่อปรับระดับแสงให้อยู่เหนือและต่ำกว่า 300 LED จะเปิดและปิด

![LED ในแอป CounterFit เปิดและปิดเมื่อระดับแสงเปลี่ยนแปลง](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device)

😀 โปรแกรมไฟกลางคืนของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้