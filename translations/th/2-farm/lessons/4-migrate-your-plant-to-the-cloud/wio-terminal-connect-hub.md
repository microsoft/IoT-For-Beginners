<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T22:02:24+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "th"
}
-->
# เชื่อมต่ออุปกรณ์ IoT ของคุณกับคลาวด์ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเชื่อมต่อ Wio Terminal ของคุณกับ IoT Hub เพื่อส่งข้อมูลเทเลเมทรีและรับคำสั่ง

## เชื่อมต่ออุปกรณ์ของคุณกับ IoT Hub

ขั้นตอนต่อไปคือการเชื่อมต่ออุปกรณ์ของคุณกับ IoT Hub

### งาน - เชื่อมต่อกับ IoT Hub

1. เปิดโปรเจกต์ `soil-moisture-sensor` ใน VS Code

1. เปิดไฟล์ `platformio.ini` ลบการพึ่งพาไลบรารี `knolleary/PubSubClient` ซึ่งเคยใช้เชื่อมต่อกับ MQTT broker สาธารณะ และไม่จำเป็นสำหรับการเชื่อมต่อกับ IoT Hub

1. เพิ่มการพึ่งพาไลบรารีดังต่อไปนี้:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    ไลบรารี `Seeed Arduino RTC` ให้โค้ดสำหรับการทำงานกับนาฬิกาเรียลไทม์ใน Wio Terminal ซึ่งใช้ในการติดตามเวลา ไลบรารีที่เหลือช่วยให้อุปกรณ์ IoT ของคุณเชื่อมต่อกับ IoT Hub

1. เพิ่มโค้ดต่อไปนี้ที่ด้านล่างของไฟล์ `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    โค้ดนี้ตั้งค่าธงคอมไพเลอร์ที่จำเป็นเมื่อคอมไพล์โค้ด Arduino IoT Hub

1. เปิดไฟล์เฮดเดอร์ `config.h` ลบการตั้งค่า MQTT ทั้งหมดและเพิ่มค่าคงที่สำหรับสตริงการเชื่อมต่ออุปกรณ์ดังนี้:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    แทนที่ `<connection string>` ด้วยสตริงการเชื่อมต่อสำหรับอุปกรณ์ของคุณที่คุณคัดลอกไว้ก่อนหน้านี้

1. การเชื่อมต่อกับ IoT Hub ใช้โทเค็นที่อิงตามเวลา ซึ่งหมายความว่าอุปกรณ์ IoT จำเป็นต้องทราบเวลาปัจจุบัน ต่างจากระบบปฏิบัติการเช่น Windows, macOS หรือ Linux ไมโครคอนโทรลเลอร์ไม่ได้ซิงโครไนซ์เวลาปัจจุบันผ่านอินเทอร์เน็ตโดยอัตโนมัติ ดังนั้นคุณจะต้องเพิ่มโค้ดเพื่อรับเวลาปัจจุบันจาก [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server เมื่อได้รับเวลาแล้ว สามารถจัดเก็บไว้ในนาฬิกาเรียลไทม์ใน Wio Terminal เพื่อให้สามารถขอเวลาที่ถูกต้องได้ในภายหลัง หากอุปกรณ์ไม่สูญเสียพลังงาน เพิ่มไฟล์ใหม่ชื่อ `ntp.h` พร้อมโค้ดดังนี้:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    รายละเอียดของโค้ดนี้อยู่นอกเหนือขอบเขตของบทเรียนนี้ โค้ดนี้กำหนดฟังก์ชันชื่อ `initTime` ที่รับเวลาปัจจุบันจาก NTP server และใช้เวลานั้นตั้งค่านาฬิกาใน Wio Terminal

1. เปิดไฟล์ `main.cpp` และลบโค้ด MQTT ทั้งหมด รวมถึงไฟล์เฮดเดอร์ `PubSubClient.h` การประกาศตัวแปร `PubSubClient` เมธอด `reconnectMQTTClient` และ `createMQTTClient` และการเรียกใช้ตัวแปรและเมธอดเหล่านี้ ไฟล์นี้ควรมีเฉพาะโค้ดสำหรับการเชื่อมต่อ WiFi รับค่าความชื้นในดิน และสร้างเอกสาร JSON เท่านั้น

1. เพิ่มคำสั่ง `#include` ต่อไปนี้ที่ด้านบนของไฟล์ `main.cpp` เพื่อรวมไฟล์เฮดเดอร์สำหรับไลบรารี IoT Hub และการตั้งค่าเวลา:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. เพิ่มคำสั่งต่อไปนี้ที่ท้ายฟังก์ชัน `setup` เพื่อตั้งค่าเวลาปัจจุบัน:

    ```cpp
    initTime();
    ```

1. เพิ่มการประกาศตัวแปรต่อไปนี้ที่ด้านบนของไฟล์ ใต้คำสั่ง include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    โค้ดนี้ประกาศ `IOTHUB_DEVICE_CLIENT_LL_HANDLE` ซึ่งเป็นตัวจัดการการเชื่อมต่อกับ IoT Hub

1. ใต้โค้ดนี้ เพิ่มโค้ดดังต่อไปนี้:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    โค้ดนี้ประกาศฟังก์ชัน callback ที่จะถูกเรียกเมื่อการเชื่อมต่อกับ IoT Hub เปลี่ยนสถานะ เช่น การเชื่อมต่อหรือการตัดการเชื่อมต่อ สถานะจะถูกส่งไปยังพอร์ตอนุกรม

1. ใต้โค้ดนี้ เพิ่มฟังก์ชันสำหรับการเชื่อมต่อกับ IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    โค้ดนี้เริ่มต้นโค้ดไลบรารี IoT Hub จากนั้นสร้างการเชื่อมต่อโดยใช้สตริงการเชื่อมต่อในไฟล์เฮดเดอร์ `config.h` การเชื่อมต่อนี้ใช้ MQTT หากการเชื่อมต่อล้มเหลว ข้อความนี้จะถูกส่งไปยังพอร์ตอนุกรม - หากคุณเห็นข้อความนี้ในผลลัพธ์ ให้ตรวจสอบสตริงการเชื่อมต่อ สุดท้าย callback สถานะการเชื่อมต่อจะถูกตั้งค่า

1. เรียกใช้ฟังก์ชันนี้ในฟังก์ชัน `setup` ใต้คำสั่ง `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. เช่นเดียวกับ MQTT client โค้ดนี้ทำงานบนเธรดเดียว ดังนั้นจึงต้องใช้เวลาในการประมวลผลข้อความที่ส่งโดย hub และส่งไปยัง hub เพิ่มโค้ดต่อไปนี้ที่ด้านบนของฟังก์ชัน `loop` เพื่อทำสิ่งนี้:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. สร้างและอัปโหลดโค้ดนี้ คุณจะเห็นการเชื่อมต่อใน serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    ในผลลัพธ์ คุณจะเห็นการดึงเวลาจาก NTP ตามด้วยการเชื่อมต่อ device client อาจใช้เวลาสองสามวินาทีในการเชื่อมต่อ ดังนั้นคุณอาจเห็นค่าความชื้นในดินในผลลัพธ์ในขณะที่อุปกรณ์กำลังเชื่อมต่อ

    > 💁 คุณสามารถแปลงเวลาจาก UNIX time ของ NTP ให้เป็นรูปแบบที่อ่านง่ายขึ้นได้โดยใช้เว็บไซต์เช่น [unixtimestamp.com](https://www.unixtimestamp.com)

## ส่งข้อมูลเทเลเมทรี

ตอนนี้อุปกรณ์ของคุณเชื่อมต่อแล้ว คุณสามารถส่งข้อมูลเทเลเมทรีไปยัง IoT Hub แทน MQTT broker

### งาน - ส่งข้อมูลเทเลเมทรี

1. เพิ่มฟังก์ชันต่อไปนี้เหนือฟังก์ชัน `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    โค้ดนี้สร้างข้อความ IoT Hub จากสตริงที่ส่งผ่านเป็นพารามิเตอร์ ส่งไปยัง hub จากนั้นทำความสะอาดออบเจ็กต์ข้อความ

1. เรียกใช้โค้ดนี้ในฟังก์ชัน `loop` หลังบรรทัดที่ส่งข้อมูลเทเลเมทรีไปยังพอร์ตอนุกรม:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## จัดการคำสั่ง

อุปกรณ์ของคุณจำเป็นต้องจัดการคำสั่งจากโค้ดเซิร์ฟเวอร์เพื่อควบคุมรีเลย์ คำสั่งนี้ถูกส่งเป็นคำขอเมธอดโดยตรง

## งาน - จัดการคำขอเมธอดโดยตรง

1. เพิ่มโค้ดต่อไปนี้ก่อนฟังก์ชัน `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    โค้ดนี้กำหนดเมธอด callback ที่ไลบรารี IoT Hub สามารถเรียกใช้เมื่อได้รับคำขอเมธอดโดยตรง เมธอดที่ถูกเรียกจะถูกส่งในพารามิเตอร์ `method_name` ฟังก์ชันนี้พิมพ์เมธอดที่ถูกเรียกไปยังพอร์ตอนุกรม จากนั้นเปิดหรือปิดรีเลย์ตามชื่อเมธอด

    > 💁 สิ่งนี้สามารถนำไปใช้ในคำขอเมธอดโดยตรงเดียว โดยส่งสถานะที่ต้องการของรีเลย์ใน payload ที่สามารถส่งพร้อมคำขอเมธอดและสามารถเข้าถึงได้จากพารามิเตอร์ `payload`

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชัน `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    คำขอเมธอดโดยตรงต้องการการตอบกลับ และการตอบกลับมีสองส่วน - การตอบกลับเป็นข้อความ และรหัสการตอบกลับ โค้ดนี้จะสร้างผลลัพธ์เป็นเอกสาร JSON ดังนี้:

    ```JSON
    {
        "Result": ""
    }
    ```

    จากนั้นจะถูกคัดลอกไปยังพารามิเตอร์ `response` และขนาดของการตอบกลับนี้จะถูกตั้งค่าในพารามิเตอร์ `response_size` โค้ดนี้จะส่งคืน `IOTHUB_CLIENT_OK` เพื่อแสดงว่าเมธอดถูกจัดการอย่างถูกต้อง

1. เชื่อมโยง callback โดยเพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชัน `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. ฟังก์ชัน `loop` จะเรียกใช้ฟังก์ชัน `IoTHubDeviceClient_LL_DoWork` เพื่อประมวลผลเหตุการณ์ที่ส่งโดย IoT Hub ฟังก์ชันนี้จะถูกเรียกทุก 10 วินาทีเนื่องจากคำสั่ง `delay` ซึ่งหมายความว่าคำขอเมธอดโดยตรงจะถูกประมวลผลทุก 10 วินาทีเท่านั้น เพื่อให้มีประสิทธิภาพมากขึ้น การหน่วงเวลา 10 วินาทีสามารถนำไปใช้เป็นการหน่วงเวลาสั้น ๆ หลายครั้ง โดยเรียกใช้ `IoTHubDeviceClient_LL_DoWork` ทุกครั้ง เพิ่มโค้ดต่อไปนี้เหนือฟังก์ชัน `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    โค้ดนี้จะวนซ้ำซ้ำ ๆ โดยเรียกใช้ `IoTHubDeviceClient_LL_DoWork` และหน่วงเวลา 100ms ทุกครั้ง จะทำเช่นนี้ตามจำนวนครั้งที่จำเป็นเพื่อหน่วงเวลาตามเวลาที่กำหนดในพารามิเตอร์ `delay_time` ซึ่งหมายความว่าอุปกรณ์กำลังรอสูงสุด 100ms เพื่อประมวลผลคำขอเมธอดโดยตรง

1. ในฟังก์ชัน `loop` ลบคำสั่งเรียกใช้ `IoTHubDeviceClient_LL_DoWork` และแทนที่คำสั่ง `delay(10000)` ด้วยโค้ดต่อไปนี้เพื่อเรียกใช้ฟังก์ชันใหม่:

    ```cpp
    work_delay(10000);
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal)

😀 โปรแกรมเซ็นเซอร์ความชื้นในดินของคุณเชื่อมต่อกับ IoT Hub แล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษาจากผู้เชี่ยวชาญ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้