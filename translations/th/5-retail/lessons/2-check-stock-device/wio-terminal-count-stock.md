<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T21:39:34+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "th"
}
-->
# นับสต็อกจากอุปกรณ์ IoT ของคุณ - Wio Terminal

การผสมผสานระหว่างการทำนายและกรอบสี่เหลี่ยมรอบวัตถุสามารถใช้ในการนับสต็อกในภาพได้

## นับสต็อก

![กระป๋องซอสมะเขือเทศ 4 กระป๋องพร้อมกรอบสี่เหลี่ยมรอบแต่ละกระป๋อง](../../../../../translated_images/th/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

ในภาพด้านบน กรอบสี่เหลี่ยมมีการทับซ้อนกันเล็กน้อย หากการทับซ้อนนี้มากขึ้น กรอบสี่เหลี่ยมอาจบ่งบอกถึงวัตถุเดียวกัน เพื่อให้นับวัตถุได้อย่างถูกต้อง คุณจำเป็นต้องละเว้นกรอบที่มีการทับซ้อนกันมากเกินไป

### งาน - นับสต็อกโดยละเว้นการทับซ้อน

1. เปิดโปรเจกต์ `stock-counter` ของคุณ หากยังไม่ได้เปิด

1. เหนือฟังก์ชัน `processPredictions` ให้เพิ่มโค้ดต่อไปนี้:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    โค้ดนี้กำหนดเปอร์เซ็นต์การทับซ้อนที่อนุญาตก่อนที่กรอบสี่เหลี่ยมจะถือว่าเป็นวัตถุเดียวกัน ค่า 0.20 หมายถึงการทับซ้อน 20%

1. ด้านล่างนี้ และเหนือฟังก์ชัน `processPredictions` ให้เพิ่มโค้ดต่อไปนี้เพื่อคำนวณการทับซ้อนระหว่างสี่เหลี่ยมสองอัน:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    โค้ดนี้กำหนดโครงสร้าง `Point` เพื่อเก็บจุดในภาพ และโครงสร้าง `Rect` เพื่อกำหนดสี่เหลี่ยมโดยใช้พิกัดมุมบนซ้ายและมุมล่างขวา จากนั้นกำหนดฟังก์ชัน `area` เพื่อคำนวณพื้นที่ของสี่เหลี่ยมจากพิกัดมุมบนซ้ายและมุมล่างขวา

    ต่อไป กำหนดฟังก์ชัน `overlappingArea` เพื่อคำนวณพื้นที่ที่ทับซ้อนกันของสี่เหลี่ยมสองอัน หากไม่มีการทับซ้อน จะคืนค่าเป็น 0

1. ด้านล่างฟังก์ชัน `overlappingArea` ให้ประกาศฟังก์ชันเพื่อแปลงกรอบสี่เหลี่ยมเป็น `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    โค้ดนี้รับการทำนายจากตัวตรวจจับวัตถุ ดึงกรอบสี่เหลี่ยมออกมา และใช้ค่าจากกรอบสี่เหลี่ยมเพื่อกำหนดสี่เหลี่ยม ด้านขวาคำนวณจากด้านซ้ายบวกกับความกว้าง ด้านล่างคำนวณจากด้านบนบวกกับความสูง

1. การทำนายจำเป็นต้องถูกเปรียบเทียบกัน และหากการทำนายสองรายการมีการทับซ้อนเกินเกณฑ์ที่กำหนด หนึ่งในนั้นจำเป็นต้องถูกลบออก เกณฑ์การทับซ้อนเป็นเปอร์เซ็นต์ ดังนั้นจำเป็นต้องคูณด้วยขนาดของกรอบสี่เหลี่ยมที่เล็กที่สุดเพื่อตรวจสอบว่าการทับซ้อนเกินเปอร์เซ็นต์ที่กำหนดของกรอบสี่เหลี่ยมหรือไม่ ไม่ใช่เปอร์เซ็นต์ของภาพทั้งหมด เริ่มต้นด้วยการลบเนื้อหาในฟังก์ชัน `processPredictions`

1. เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `processPredictions` ที่ว่างเปล่า:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    โค้ดนี้ประกาศเวกเตอร์เพื่อเก็บการทำนายที่ไม่มีการทับซ้อน จากนั้นวนลูปผ่านการทำนายทั้งหมด โดยสร้าง `Rect` จากกรอบสี่เหลี่ยม

    ต่อไป โค้ดนี้วนลูปผ่านการทำนายที่เหลือ โดยเริ่มจากรายการถัดจากการทำนายปัจจุบัน วิธีนี้ช่วยหยุดการเปรียบเทียบการทำนายซ้ำ - เมื่อเปรียบเทียบ 1 และ 2 แล้ว ไม่จำเป็นต้องเปรียบเทียบ 2 กับ 1 อีกต่อไป แต่เปรียบเทียบกับ 3, 4 เป็นต้น

    สำหรับการทำนายแต่ละคู่ จะคำนวณพื้นที่ที่ทับซ้อนกัน จากนั้นเปรียบเทียบกับพื้นที่ของกรอบสี่เหลี่ยมที่เล็กที่สุด - หากการทับซ้อนเกินเกณฑ์เปอร์เซ็นต์ของกรอบสี่เหลี่ยมที่เล็กที่สุด การทำนายจะถูกทำเครื่องหมายว่าไม่ผ่าน หากหลังจากเปรียบเทียบการทับซ้อนทั้งหมดแล้ว การทำนายผ่านการตรวจสอบ จะถูกเพิ่มในคอลเลกชัน `passed_predictions`

    > 💁 นี่เป็นวิธีที่ง่ายมากในการลบการทับซ้อน โดยลบรายการแรกในคู่ที่ทับซ้อนกัน สำหรับโค้ดที่ใช้ในงานจริง คุณอาจต้องการเพิ่มตรรกะเพิ่มเติม เช่น การพิจารณาการทับซ้อนระหว่างวัตถุหลายชิ้น หรือหากกรอบสี่เหลี่ยมหนึ่งถูกครอบคลุมโดยอีกกรอบหนึ่ง

1. หลังจากนี้ ให้เพิ่มโค้ดต่อไปนี้เพื่อส่งรายละเอียดของการทำนายที่ผ่านไปยัง serial monitor:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    โค้ดนี้วนลูปผ่านการทำนายที่ผ่านการตรวจสอบและพิมพ์รายละเอียดของพวกมันไปยัง serial monitor

1. ด้านล่างนี้ ให้เพิ่มโค้ดเพื่อพิมพ์จำนวนรายการที่นับได้ไปยัง serial monitor:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    จากนั้นสามารถส่งข้อมูลนี้ไปยังบริการ IoT เพื่อแจ้งเตือนหากระดับสต็อกต่ำ

1. อัปโหลดและรันโค้ดของคุณ ชี้กล้องไปที่วัตถุบนชั้นวางและกดปุ่ม C ลองปรับค่าของ `overlap_threshold` เพื่อดูการทำนายที่ถูกละเว้น

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal)

😀 โปรแกรมนับสต็อกของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้