<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T21:38:56+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "th"
}
-->
# นับจำนวนสินค้าโดยใช้ IoT Device - Virtual IoT Hardware และ Raspberry Pi

การรวมกันของการคาดการณ์และกรอบสี่เหลี่ยมรอบวัตถุสามารถใช้ในการนับจำนวนสินค้าในภาพได้

## แสดงกรอบสี่เหลี่ยมรอบวัตถุ

เพื่อช่วยในการดีบัก คุณสามารถไม่เพียงแค่พิมพ์กรอบสี่เหลี่ยมออกมา แต่ยังสามารถวาดกรอบเหล่านั้นลงบนภาพที่ถูกบันทึกไว้เมื่อมีการถ่ายภาพ

### งาน - พิมพ์กรอบสี่เหลี่ยม

1. ตรวจสอบให้แน่ใจว่าโปรเจกต์ `stock-counter` เปิดอยู่ใน VS Code และ virtual environment ถูกเปิดใช้งานหากคุณใช้ virtual IoT device

1. เปลี่ยนคำสั่ง `print` ใน `for` loop เป็นดังนี้เพื่อพิมพ์กรอบสี่เหลี่ยมลงในคอนโซล:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. รันแอปพลิเคชันโดยให้กล้องชี้ไปที่สินค้าบนชั้นวาง กรอบสี่เหลี่ยมจะถูกพิมพ์ลงในคอนโซล โดยมีค่าซ้าย, บน, กว้าง และสูงในช่วง 0-1

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### งาน - วาดกรอบสี่เหลี่ยมบนภาพ

1. แพ็กเกจ Pip [Pillow](https://pypi.org/project/Pillow/) สามารถใช้ในการวาดบนภาพได้ ติดตั้งด้วยคำสั่งต่อไปนี้:

    ```sh
    pip3 install pillow
    ```

    หากคุณใช้ virtual IoT device ตรวจสอบให้แน่ใจว่าคุณรันคำสั่งนี้จากภายใน virtual environment ที่เปิดใช้งานแล้ว

1. เพิ่มคำสั่ง import ต่อไปนี้ที่ด้านบนของไฟล์ `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    คำสั่งนี้นำเข้าซอร์สโค้ดที่จำเป็นสำหรับการแก้ไขภาพ

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายไฟล์ `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    โค้ดนี้เปิดภาพที่ถูกบันทึกไว้ก่อนหน้านี้เพื่อแก้ไข จากนั้นวนลูปผ่านการคาดการณ์เพื่อดึงกรอบสี่เหลี่ยม และคำนวณพิกัดล่างขวาโดยใช้ค่ากรอบสี่เหลี่ยมจาก 0-1 ค่าดังกล่าวจะถูกแปลงเป็นพิกัดภาพโดยการคูณกับมิติที่เกี่ยวข้องของภาพ เช่น หากค่าซ้ายคือ 0.5 บนภาพที่กว้าง 600 พิกเซล ค่านี้จะถูกแปลงเป็น 300 (0.5 x 600 = 300)

    กรอบสี่เหลี่ยมแต่ละกรอบจะถูกวาดบนภาพโดยใช้เส้นสีแดง สุดท้ายภาพที่ถูกแก้ไขจะถูกบันทึกโดยเขียนทับภาพต้นฉบับ

1. รันแอปพลิเคชันโดยให้กล้องชี้ไปที่สินค้าบนชั้นวาง คุณจะเห็นไฟล์ `image.jpg` ใน VS Code explorer และสามารถเลือกดูกรอบสี่เหลี่ยมได้

    ![กระป๋องมะเขือเทศ 4 กระป๋องพร้อมกรอบสี่เหลี่ยมรอบแต่ละกระป๋อง](../../../../../translated_images/th/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## นับจำนวนสินค้า

ในภาพที่แสดงด้านบน กรอบสี่เหลี่ยมมีการทับซ้อนกันเล็กน้อย หากการทับซ้อนนี้มีขนาดใหญ่มาก กรอบสี่เหลี่ยมอาจบ่งบอกถึงวัตถุเดียวกัน เพื่อให้นับจำนวนวัตถุได้อย่างถูกต้อง คุณจำเป็นต้องละเว้นกรอบที่มีการทับซ้อนกันมาก

### งาน - นับจำนวนสินค้าโดยละเว้นการทับซ้อน

1. แพ็กเกจ Pip [Shapely](https://pypi.org/project/Shapely/) สามารถใช้ในการคำนวณการทับซ้อน หากคุณใช้ Raspberry Pi คุณจะต้องติดตั้งไลบรารี dependency ก่อน:

    ```sh
    sudo apt install libgeos-dev
    ```

1. ติดตั้งแพ็กเกจ Shapely ด้วยคำสั่งต่อไปนี้:

    ```sh
    pip3 install shapely
    ```

    หากคุณใช้ virtual IoT device ตรวจสอบให้แน่ใจว่าคุณรันคำสั่งนี้จากภายใน virtual environment ที่เปิดใช้งานแล้ว

1. เพิ่มคำสั่ง import ต่อไปนี้ที่ด้านบนของไฟล์ `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    คำสั่งนี้นำเข้าซอร์สโค้ดที่จำเป็นสำหรับการสร้าง polygons เพื่อคำนวณการทับซ้อน

1. เพิ่มโค้ดต่อไปนี้เหนือโค้ดที่วาดกรอบสี่เหลี่ยม:

    ```python
    overlap_threshold = 0.20
    ```

    โค้ดนี้กำหนดเปอร์เซ็นต์การทับซ้อนที่อนุญาตก่อนที่กรอบสี่เหลี่ยมจะถูกพิจารณาว่าเป็นวัตถุเดียวกัน ค่า 0.20 หมายถึงการทับซ้อน 20%

1. ในการคำนวณการทับซ้อนโดยใช้ Shapely กรอบสี่เหลี่ยมต้องถูกแปลงเป็น polygons ของ Shapely เพิ่มฟังก์ชันต่อไปนี้เพื่อทำสิ่งนี้:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    ฟังก์ชันนี้สร้าง polygon โดยใช้กรอบสี่เหลี่ยมของการคาดการณ์

1. ลอจิกสำหรับการลบวัตถุที่ทับซ้อนกันเกี่ยวข้องกับการเปรียบเทียบกรอบสี่เหลี่ยมทั้งหมด หากคู่ใดมีการทับซ้อนกันมากกว่าค่าที่กำหนด ให้ลบหนึ่งในนั้นออก เพื่อเปรียบเทียบการคาดการณ์ทั้งหมด คุณต้องเปรียบเทียบการคาดการณ์ที่ 1 กับ 2, 3, 4 เป็นต้น จากนั้น 2 กับ 3, 4 เป็นต้น โค้ดต่อไปนี้ทำสิ่งนี้:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    การทับซ้อนถูกคำนวณโดยใช้เมธอด `Polygon.intersection` ของ Shapely ซึ่งคืนค่า polygon ที่มีการทับซ้อน พื้นที่จะถูกคำนวณจาก polygon นี้ ค่าการทับซ้อนที่กำหนดไม่ใช่ค่าที่แน่นอน แต่ต้องเป็นเปอร์เซ็นต์ของกรอบสี่เหลี่ยม ดังนั้นกรอบสี่เหลี่ยมที่เล็กที่สุดจะถูกหา และค่าการทับซ้อนที่กำหนดจะถูกใช้ในการคำนวณพื้นที่ที่การทับซ้อนสามารถมีได้โดยไม่เกินเปอร์เซ็นต์การทับซ้อนของกรอบสี่เหลี่ยมที่เล็กที่สุด หากการทับซ้อนเกินค่าที่กำหนด การคาดการณ์จะถูกทำเครื่องหมายเพื่อลบ

    เมื่อการคาดการณ์ถูกทำเครื่องหมายเพื่อลบแล้ว ไม่จำเป็นต้องตรวจสอบอีก ดังนั้น loop ด้านในจะหยุดเพื่อไปตรวจสอบการคาดการณ์ถัดไป คุณไม่สามารถลบรายการจาก list ขณะวนลูปผ่านมันได้ ดังนั้นกรอบสี่เหลี่ยมที่ทับซ้อนกันมากกว่าค่าที่กำหนดจะถูกเพิ่มใน list `to_delete` แล้วลบออกในตอนท้าย

    สุดท้ายจำนวนสินค้าจะถูกพิมพ์ลงในคอนโซล ซึ่งสามารถส่งไปยัง IoT service เพื่อแจ้งเตือนหากระดับสินค้าต่ำ โค้ดทั้งหมดนี้อยู่ก่อนการวาดกรอบสี่เหลี่ยม ดังนั้นคุณจะเห็นการคาดการณ์สินค้าที่ไม่มีการทับซ้อนบนภาพที่ถูกสร้างขึ้น

    > 💁 นี่เป็นวิธีที่ง่ายมากในการลบการทับซ้อน โดยลบกรอบแรกในคู่ที่ทับซ้อนกัน สำหรับโค้ดที่ใช้ในงานจริง คุณอาจต้องเพิ่มลอจิกเพิ่มเติม เช่น การพิจารณาการทับซ้อนระหว่างวัตถุหลายชิ้น หรือหากกรอบสี่เหลี่ยมหนึ่งถูกครอบคลุมโดยอีกกรอบหนึ่ง

1. รันแอปพลิเคชันโดยให้กล้องชี้ไปที่สินค้าบนชั้นวาง ผลลัพธ์จะระบุจำนวนกรอบสี่เหลี่ยมที่ไม่มีการทับซ้อนที่เกินค่าที่กำหนด ลองปรับค่าของ `overlap_threshold` เพื่อดูการคาดการณ์ที่ถูกละเว้น

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) หรือ [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device)

😀 โปรแกรมนับจำนวนสินค้าของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้