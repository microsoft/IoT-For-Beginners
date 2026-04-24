# เรียกใช้งานตัวตรวจจับวัตถุจากอุปกรณ์ IoT ของคุณ - Wio Terminal

เมื่อคุณเผยแพร่ตัวตรวจจับวัตถุแล้ว คุณสามารถใช้งานมันจากอุปกรณ์ IoT ของคุณได้

## คัดลอกโปรเจกต์ตัวจำแนกรูปภาพ

ส่วนใหญ่ของตัวตรวจจับสต็อกของคุณจะเหมือนกับตัวจำแนกรูปภาพที่คุณสร้างไว้ในบทเรียนก่อนหน้า

### งาน - คัดลอกโปรเจกต์ตัวจำแนกรูปภาพ

1. เชื่อมต่อ ArduCam กับ Wio Terminal ของคุณ โดยทำตามขั้นตอนจาก [บทเรียนที่ 2 ของโปรเจกต์การผลิต](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera)

    คุณอาจต้องการยึดกล้องให้อยู่ในตำแหน่งเดียว เช่น แขวนสายเคเบิลไว้บนกล่องหรือกระป๋อง หรือยึดกล้องกับกล่องด้วยเทปสองหน้า

1. สร้างโปรเจกต์ Wio Terminal ใหม่โดยใช้ PlatformIO ตั้งชื่อโปรเจกต์นี้ว่า `stock-counter`

1. ทำตามขั้นตอนจาก [บทเรียนที่ 2 ของโปรเจกต์การผลิต](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) เพื่อถ่ายภาพจากกล้อง

1. ทำตามขั้นตอนจาก [บทเรียนที่ 2 ของโปรเจกต์การผลิต](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) เพื่อเรียกใช้งานตัวจำแนกรูปภาพ โค้ดส่วนใหญ่จะถูกนำมาใช้ซ้ำสำหรับการตรวจจับวัตถุ

## เปลี่ยนโค้ดจากตัวจำแนกเป็นตัวตรวจจับวัตถุ

โค้ดที่คุณใช้สำหรับการจำแนกรูปภาพนั้นคล้ายกับโค้ดสำหรับการตรวจจับวัตถุ ความแตกต่างหลักคือ URL ที่เรียกใช้งานซึ่งคุณได้รับจาก Custom Vision และผลลัพธ์ของการเรียกใช้งาน

### งาน - เปลี่ยนโค้ดจากตัวจำแนกเป็นตัวตรวจจับวัตถุ

1. เพิ่มคำสั่ง include ต่อไปนี้ที่ด้านบนของไฟล์ `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. เปลี่ยนชื่อฟังก์ชัน `classifyImage` เป็น `detectStock` ทั้งชื่อฟังก์ชันและการเรียกใช้งานในฟังก์ชัน `buttonPressed`

1. เหนือฟังก์ชัน `detectStock` ให้ประกาศค่า threshold เพื่อกรองการตรวจจับที่มีความน่าจะเป็นต่ำ:

    ```cpp
    const float threshold = 0.3f;
    ```

    ไม่เหมือนกับตัวจำแนกรูปภาพที่คืนค่าเพียงผลลัพธ์เดียวต่อแท็ก ตัวตรวจจับวัตถุจะคืนค่าหลายผลลัพธ์ ดังนั้นผลลัพธ์ที่มีความน่าจะเป็นต่ำจะต้องถูกกรองออก

1. เหนือฟังก์ชัน `detectStock` ให้ประกาศฟังก์ชันเพื่อประมวลผลการคาดการณ์:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    ฟังก์ชันนี้จะรับรายการการคาดการณ์และพิมพ์ผลลัพธ์ไปยัง serial monitor

1. ในฟังก์ชัน `detectStock` ให้แทนที่เนื้อหาของ `for` loop ที่วนผ่านการคาดการณ์ด้วยโค้ดต่อไปนี้:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    โค้ดนี้จะวนผ่านการคาดการณ์ เปรียบเทียบความน่าจะเป็นกับค่า threshold การคาดการณ์ทั้งหมดที่มีความน่าจะเป็นสูงกว่าค่า threshold จะถูกเพิ่มลงใน `list` และส่งไปยังฟังก์ชัน `processPredictions`

1. อัปโหลดและรันโค้ดของคุณ ชี้กล้องไปที่วัตถุบนชั้นวางและกดปุ่ม C คุณจะเห็นผลลัพธ์ใน serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 คุณอาจต้องปรับค่า `threshold` ให้เหมาะสมกับรูปภาพของคุณ

    คุณจะสามารถเห็นภาพที่ถ่ายและค่าต่างๆ เหล่านี้ในแท็บ **Predictions** ใน Custom Vision

    ![กระป๋องซอสมะเขือเทศ 4 กระป๋องบนชั้นวาง พร้อมการคาดการณ์ 4 รายการที่มีค่าความน่าจะเป็น 35.8%, 33.5%, 25.7% และ 16.6%](../../../../../translated_images/th/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal)

😀 โปรแกรมนับสต็อกของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้