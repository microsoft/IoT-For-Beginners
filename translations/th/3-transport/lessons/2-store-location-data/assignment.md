<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T21:01:52+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "th"
}
-->
# ตรวจสอบการผูกฟังก์ชัน

## คำแนะนำ

การผูกฟังก์ชันช่วยให้โค้ดของคุณสามารถบันทึก blobs ลงในที่เก็บ blob ได้โดยการส่งคืนจากฟังก์ชัน `main` บัญชี Azure Storage คอลเลกชัน และรายละเอียดอื่น ๆ จะถูกกำหนดค่าในไฟล์ `function.json`

เมื่อทำงานกับ Azure หรือเทคโนโลยีของ Microsoft อื่น ๆ แหล่งข้อมูลที่ดีที่สุดคือ [เอกสารของ Microsoft ที่ docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn) ในงานนี้ คุณจะต้องอ่านเอกสารเกี่ยวกับการผูก Azure Functions เพื่อเรียนรู้วิธีตั้งค่าการผูกผลลัพธ์

หน้าเอกสารที่ควรเริ่มต้นอ่าน ได้แก่:

* [แนวคิดเกี่ยวกับ triggers และ bindings ของ Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [ภาพรวมการผูก Azure Blob storage สำหรับ Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [การผูกผลลัพธ์ Azure Blob storage สำหรับ Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## เกณฑ์การประเมิน

| เกณฑ์ | ดีเยี่ยม | พอใช้ | ต้องปรับปรุง |
| -------- | --------- | -------- | ----------------- |
| การตั้งค่าการผูกผลลัพธ์ blob storage | สามารถตั้งค่าการผูกผลลัพธ์ได้สำเร็จ ส่งคืน blob และบันทึกลงใน blob storage ได้สำเร็จ | สามารถตั้งค่าการผูกผลลัพธ์ได้ หรือส่งคืน blob ได้ แต่ไม่สามารถบันทึกลงใน blob storage ได้สำเร็จ | ไม่สามารถตั้งค่าการผูกผลลัพธ์ได้ |

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้