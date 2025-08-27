<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:10:09+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "th"
}
-->
# สร้างเครื่องเสมือนที่รัน IoT Edge

ใน Azure คุณสามารถสร้างเครื่องเสมือน (Virtual Machine) ซึ่งเป็นคอมพิวเตอร์ในระบบคลาวด์ที่คุณสามารถปรับแต่งได้ตามต้องการและติดตั้งซอฟต์แวร์ของคุณเองเพื่อใช้งาน

> 💁 คุณสามารถอ่านข้อมูลเพิ่มเติมเกี่ยวกับเครื่องเสมือนได้ที่ [หน้าวิกิพีเดียเกี่ยวกับเครื่องเสมือน](https://wikipedia.org/wiki/Virtual_machine)

## งาน - ตั้งค่าเครื่องเสมือน IoT Edge

1. รันคำสั่งต่อไปนี้เพื่อสร้างเครื่องเสมือนที่มี Azure IoT Edge ติดตั้งไว้ล่วงหน้า:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    แทนที่ `<vm_name>` ด้วยชื่อสำหรับเครื่องเสมือนนี้ ชื่อนี้ต้องไม่ซ้ำกันทั่วโลก ดังนั้นให้ใช้ชื่อเช่น `fruit-quality-detector-vm-` พร้อมชื่อของคุณหรือค่าที่คุณต้องการต่อท้าย

    แทนที่ `<username>` และ `<password>` ด้วยชื่อผู้ใช้และรหัสผ่านที่ใช้ในการเข้าสู่ระบบเครื่องเสมือน ชื่อผู้ใช้และรหัสผ่านต้องมีความปลอดภัยพอสมควร ดังนั้นคุณไม่สามารถใช้ admin/password ได้

    แทนที่ `<connection_string>` ด้วย connection string ของอุปกรณ์ IoT Edge `fruit-quality-detector-edge` ของคุณ

    คำสั่งนี้จะสร้างเครื่องเสมือนที่ถูกกำหนดค่าเป็น `DS1 v2` เครื่องเสมือนประเภทนี้บ่งบอกถึงความสามารถของเครื่องและค่าใช้จ่ายที่เกี่ยวข้อง เครื่องนี้มี CPU 1 ตัวและ RAM 3.5GB

    > 💰 คุณสามารถดูราคาปัจจุบันของเครื่องเสมือนเหล่านี้ได้ที่ [คู่มือราคาของ Azure Virtual Machine](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    เมื่อเครื่องเสมือนถูกสร้างขึ้น ระบบ IoT Edge runtime จะถูกติดตั้งโดยอัตโนมัติและกำหนดค่าให้เชื่อมต่อกับ IoT Hub ของคุณในฐานะอุปกรณ์ `fruit-quality-detector-edge`

1. คุณจะต้องใช้ IP address หรือ DNS name ของเครื่องเสมือนเพื่อเรียกใช้งาน image classifier จากเครื่องนี้ รันคำสั่งต่อไปนี้เพื่อรับข้อมูลนี้:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    คัดลอกค่าจากฟิลด์ `PublicIps` หรือ `Fqdns`

1. เครื่องเสมือนมีค่าใช้จ่าย ในขณะที่เขียนนี้ เครื่อง DS1 VM มีค่าใช้จ่ายประมาณ $0.06 ต่อชั่วโมง เพื่อประหยัดค่าใช้จ่าย คุณควรปิดเครื่องเสมือนเมื่อไม่ได้ใช้งาน และลบเครื่องเมื่อคุณเสร็จสิ้นโครงการนี้

    คุณสามารถตั้งค่าให้เครื่องเสมือนปิดโดยอัตโนมัติในเวลาที่กำหนดในแต่ละวัน วิธีนี้จะช่วยลดค่าใช้จ่ายหากคุณลืมปิดเครื่อง ใช้คำสั่งต่อไปนี้เพื่อกำหนดค่า:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    แทนที่ `<vm_name>` ด้วยชื่อของเครื่องเสมือนของคุณ

    แทนที่ `<shutdown_time_utc>` ด้วยเวลาที่คุณต้องการให้เครื่องเสมือนปิดโดยใช้รูปแบบ 4 หลักเป็น HHMM ตัวอย่างเช่น หากคุณต้องการปิดเครื่องตอนเที่ยงคืน UTC ให้ตั้งค่าเป็น `0000` สำหรับเวลา 19:30 น. ในฝั่งตะวันตกของสหรัฐอเมริกา ให้ใช้ `0230` (19:30 น. ในฝั่งตะวันตกของสหรัฐอเมริกาคือ 2:30 น. UTC)

1. image classifier ของคุณจะรันบนอุปกรณ์ edge นี้ โดยฟังการเชื่อมต่อที่พอร์ต 80 (พอร์ต HTTP มาตรฐาน) โดยค่าเริ่มต้น เครื่องเสมือนจะบล็อกพอร์ตขาเข้า ดังนั้นคุณจะต้องเปิดพอร์ต 80 พอร์ตจะถูกเปิดใน network security groups ดังนั้นคุณต้องทราบชื่อของ network security group สำหรับเครื่องเสมือนของคุณ ซึ่งสามารถหาได้ด้วยคำสั่งต่อไปนี้:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    คัดลอกค่าจากฟิลด์ `Name`

1. รันคำสั่งต่อไปนี้เพื่อเพิ่มกฎเปิดพอร์ต 80 ใน network security group:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    แทนที่ `<nsg name>` ด้วยชื่อ network security group จากขั้นตอนก่อนหน้า

### งาน - จัดการเครื่องเสมือนของคุณเพื่อลดค่าใช้จ่าย

1. เมื่อคุณไม่ได้ใช้งานเครื่องเสมือน คุณควรปิดเครื่อง เพื่อปิดเครื่องเสมือน ใช้คำสั่งต่อไปนี้:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    แทนที่ `<vm_name>` ด้วยชื่อของเครื่องเสมือนของคุณ

    > 💁 มีคำสั่ง `az vm stop` ซึ่งจะหยุดเครื่องเสมือน แต่ยังคงจัดสรรคอมพิวเตอร์ให้คุณอยู่ ดังนั้นคุณยังคงต้องจ่ายค่าใช้จ่ายเหมือนกับเครื่องยังทำงานอยู่

1. หากต้องการเริ่มต้นเครื่องเสมือนใหม่ ใช้คำสั่งต่อไปนี้:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    แทนที่ `<vm_name>` ด้วยชื่อของเครื่องเสมือนของคุณ

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษาจากผู้เชี่ยวชาญ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้