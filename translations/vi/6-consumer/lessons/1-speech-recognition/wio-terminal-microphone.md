<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T23:28:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "vi"
}
-->
# Cấu hình micro và loa - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm loa vào Wio Terminal của mình. Wio Terminal đã có sẵn micro tích hợp, và nó có thể được sử dụng để thu âm giọng nói.

## Phần cứng

Wio Terminal đã có sẵn micro tích hợp, và nó có thể được sử dụng để thu âm phục vụ nhận diện giọng nói.

![Micro trên Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.vi.png)

Để thêm loa, bạn có thể sử dụng [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Đây là một bảng mạch ngoài chứa 2 micro MEMS, cùng với cổng kết nối loa và giắc cắm tai nghe.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.vi.png)

Bạn sẽ cần thêm tai nghe, loa với giắc cắm 3.5mm, hoặc loa với kết nối JST như [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Để kết nối ReSpeaker 2-Mics Pi Hat, bạn sẽ cần dây jumper 40 pin-to-pin (còn gọi là dây đực-đực).

> 💁 Nếu bạn quen với việc hàn, bạn có thể sử dụng [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) để kết nối ReSpeaker.

Bạn cũng sẽ cần một thẻ SD để tải xuống và phát lại âm thanh. Wio Terminal chỉ hỗ trợ thẻ SD có dung lượng tối đa 16GB, và chúng cần được định dạng dưới dạng FAT32 hoặc exFAT.

### Nhiệm vụ - kết nối ReSpeaker Pi Hat

1. Khi Wio Terminal đã tắt nguồn, kết nối ReSpeaker 2-Mics Pi Hat với Wio Terminal bằng dây jumper và các cổng GPIO ở mặt sau của Wio Terminal:

    Các chân cần được kết nối theo cách sau:

    ![Sơ đồ chân](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.vi.png)

1. Đặt ReSpeaker và Wio Terminal sao cho các cổng GPIO hướng lên trên, và ở phía bên trái.

1. Bắt đầu từ cổng ở góc trên bên trái của cổng GPIO trên ReSpeaker. Kết nối một dây jumper từ cổng trên cùng bên trái của ReSpeaker đến cổng trên cùng bên trái của Wio Terminal.

1. Lặp lại quá trình này xuống toàn bộ các cổng GPIO ở phía bên trái. Đảm bảo các chân được cắm chắc chắn.

    ![ReSpeaker với các chân bên trái được nối với các chân bên trái của Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.vi.png)

    ![ReSpeaker với các chân bên trái được nối với các chân bên trái của Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.vi.png)

    > 💁 Nếu dây jumper của bạn được kết nối thành dải, hãy giữ chúng lại với nhau - điều này giúp dễ dàng đảm bảo bạn đã kết nối tất cả các dây theo thứ tự.

1. Lặp lại quá trình này với các cổng GPIO ở phía bên phải của ReSpeaker và Wio Terminal. Các dây này cần đi vòng qua các dây đã được kết nối trước đó.

    ![ReSpeaker với các chân bên phải được nối với các chân bên phải của Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.vi.png)

    ![ReSpeaker với các chân bên phải được nối với các chân bên phải của Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.vi.png)

    > 💁 Nếu dây jumper của bạn được kết nối thành dải, hãy tách chúng thành hai dải. Đưa mỗi dải qua một bên của các dây đã có.

    > 💁 Bạn có thể sử dụng băng dính để giữ các chân thành một khối nhằm tránh việc chúng bị tuột ra khi bạn đang kết nối.
    >
    > ![Các chân được cố định bằng băng dính](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.vi.png)

1. Bạn sẽ cần thêm một loa.

    * Nếu bạn sử dụng loa với cáp JST, hãy kết nối nó với cổng JST trên ReSpeaker.

      ![Loa được kết nối với ReSpeaker bằng cáp JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.vi.png)

    * Nếu bạn sử dụng loa với giắc cắm 3.5mm hoặc tai nghe, hãy cắm chúng vào giắc cắm 3.5mm.

      ![Loa được kết nối với ReSpeaker qua giắc cắm 3.5mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.vi.png)

### Nhiệm vụ - thiết lập thẻ SD

1. Kết nối thẻ SD với máy tính của bạn, sử dụng đầu đọc ngoài nếu máy tính không có khe cắm thẻ SD.

1. Định dạng thẻ SD bằng công cụ phù hợp trên máy tính của bạn, đảm bảo sử dụng hệ thống tệp FAT32 hoặc exFAT.

1. Cắm thẻ SD vào khe cắm thẻ SD ở phía bên trái của Wio Terminal, ngay dưới nút nguồn. Đảm bảo thẻ được cắm hoàn toàn và kêu "click" - bạn có thể cần một công cụ mỏng hoặc một thẻ SD khác để giúp đẩy thẻ vào hoàn toàn.

    ![Cắm thẻ SD vào khe cắm thẻ SD dưới công tắc nguồn](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.vi.png)

    > 💁 Để lấy thẻ SD ra, bạn cần đẩy nó vào một chút và nó sẽ bật ra. Bạn sẽ cần một công cụ mỏng như tua vít đầu dẹt hoặc một thẻ SD khác để làm điều này.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.