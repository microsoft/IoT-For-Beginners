<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T22:01:13+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "th"
}
-->
# เชื่อมต่ออุปกรณ์ IoT ของคุณกับคลาวด์ - ฮาร์ดแวร์ IoT เสมือนและ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเชื่อมต่ออุปกรณ์ IoT เสมือนหรือ Raspberry Pi ของคุณกับ IoT Hub เพื่อส่งข้อมูลเทเลเมทรีและรับคำสั่ง

## เชื่อมต่ออุปกรณ์ของคุณกับ IoT Hub

ขั้นตอนถัดไปคือการเชื่อมต่ออุปกรณ์ของคุณกับ IoT Hub

### งาน - เชื่อมต่อกับ IoT Hub

1. เปิดโฟลเดอร์ `soil-moisture-sensor` ใน VS Code ตรวจสอบให้แน่ใจว่าสภาพแวดล้อมเสมือนกำลังทำงานในเทอร์มินัล หากคุณใช้อุปกรณ์ IoT เสมือน

1. ติดตั้งแพ็กเกจ Pip เพิ่มเติม:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` เป็นไลบรารีสำหรับสื่อสารกับ IoT Hub ของคุณ

1. เพิ่มการนำเข้าต่อไปนี้ที่ด้านบนของไฟล์ `app.py` ใต้การนำเข้าที่มีอยู่:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    โค้ดนี้นำเข้า SDK เพื่อสื่อสารกับ IoT Hub ของคุณ

1. ลบบรรทัด `import paho.mqtt.client as mqtt` เนื่องจากไลบรารีนี้ไม่จำเป็นอีกต่อไป ลบโค้ด MQTT ทั้งหมดรวมถึงชื่อหัวข้อ โค้ดทั้งหมดที่ใช้ `mqtt_client` และ `handle_command` เก็บลูป `while True:` ไว้ เพียงลบบรรทัด `mqtt_client.publish` ออกจากลูปนี้

1. เพิ่มโค้ดต่อไปนี้ใต้คำสั่งนำเข้า:

    ```python
    connection_string = "<connection string>"
    ```

    แทนที่ `<connection string>` ด้วยสตริงการเชื่อมต่อที่คุณดึงมาได้สำหรับอุปกรณ์ก่อนหน้านี้ในบทเรียนนี้

    > 💁 นี่ไม่ใช่วิธีปฏิบัติที่ดีที่สุด สตริงการเชื่อมต่อไม่ควรถูกเก็บไว้ในซอร์สโค้ด เนื่องจากอาจถูกตรวจสอบในระบบควบคุมซอร์สโค้ดและถูกค้นพบโดยใครก็ตาม เราทำเช่นนี้เพื่อความเรียบง่าย ในทางที่ดีควรใช้สิ่งต่าง ๆ เช่นตัวแปรสภาพแวดล้อมและเครื่องมืออย่าง [`python-dotenv`](https://pypi.org/project/python-dotenv/) คุณจะได้เรียนรู้เพิ่มเติมเกี่ยวกับเรื่องนี้ในบทเรียนถัดไป

1. ใต้โค้ดนี้ ให้เพิ่มโค้ดต่อไปนี้เพื่อสร้างออบเจ็กต์ client ของอุปกรณ์ที่สามารถสื่อสารกับ IoT Hub และเชื่อมต่อมัน:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. รันโค้ดนี้ คุณจะเห็นอุปกรณ์ของคุณเชื่อมต่อ

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## ส่งข้อมูลเทเลเมทรี

ตอนนี้อุปกรณ์ของคุณเชื่อมต่อแล้ว คุณสามารถส่งข้อมูลเทเลเมทรีไปยัง IoT Hub แทนที่จะส่งไปยัง MQTT broker

### งาน - ส่งข้อมูลเทเลเมทรี

1. เพิ่มโค้ดต่อไปนี้ภายในลูป `while True` ก่อนคำสั่ง sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    โค้ดนี้สร้าง `Message` ของ IoT Hub ที่มีการอ่านค่าความชื้นในดินในรูปแบบสตริง JSON จากนั้นส่งไปยัง IoT Hub เป็นข้อความจากอุปกรณ์ไปยังคลาวด์

## จัดการคำสั่ง

อุปกรณ์ของคุณจำเป็นต้องจัดการคำสั่งจากโค้ดเซิร์ฟเวอร์เพื่อควบคุมรีเลย์ คำสั่งนี้ถูกส่งมาในรูปแบบคำขอ direct method

## งาน - จัดการคำขอ direct method

1. เพิ่มโค้ดต่อไปนี้ก่อนลูป `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    โค้ดนี้กำหนดเมธอด `handle_method_request` ที่จะถูกเรียกเมื่อ direct method ถูกเรียกโดย IoT Hub แต่ละ direct method มีชื่อ และโค้ดนี้คาดหวังเมธอดที่ชื่อ `relay_on` เพื่อเปิดรีเลย์ และ `relay_off` เพื่อปิดรีเลย์

    > 💁 สิ่งนี้สามารถถูกนำไปใช้ใน direct method เดียว โดยส่งสถานะที่ต้องการของรีเลย์ใน payload ที่สามารถส่งไปพร้อมกับคำขอเมธอดและสามารถเข้าถึงได้จากออบเจ็กต์ `request`

1. Direct method ต้องการการตอบกลับเพื่อแจ้งโค้ดที่เรียกว่าคำขอได้รับการจัดการแล้ว เพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชัน `handle_method_request` เพื่อสร้างการตอบกลับคำขอ:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    โค้ดนี้ส่งการตอบกลับไปยังคำขอ direct method พร้อมรหัสสถานะ HTTP 200 และส่งกลับไปยัง IoT Hub

1. เพิ่มโค้ดต่อไปนี้ใต้การกำหนดฟังก์ชันนี้:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    โค้ดนี้บอก client ของ IoT Hub ให้เรียกฟังก์ชัน `handle_method_request` เมื่อ direct method ถูกเรียก

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) หรือ [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device)

😀 โปรแกรมเซ็นเซอร์ความชื้นในดินของคุณเชื่อมต่อกับ IoT Hub แล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้