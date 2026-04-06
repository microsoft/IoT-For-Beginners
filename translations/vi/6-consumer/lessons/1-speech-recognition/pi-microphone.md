# Cấu hình micro và loa - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm micro và loa vào Raspberry Pi.

## Phần cứng

Raspberry Pi cần một micro.

Pi không có micro tích hợp, bạn sẽ cần thêm một micro bên ngoài. Có nhiều cách để làm điều này:

* Micro USB  
* Tai nghe USB  
* Loa ngoài USB tích hợp micro  
* Bộ chuyển đổi âm thanh USB và micro với jack 3.5mm  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 Micro Bluetooth không được hỗ trợ hoàn toàn trên Raspberry Pi, vì vậy nếu bạn có micro hoặc tai nghe Bluetooth, bạn có thể gặp vấn đề khi ghép nối hoặc thu âm thanh.

Raspberry Pi có một jack tai nghe 3.5mm. Bạn có thể sử dụng nó để kết nối tai nghe, tai nghe có micro hoặc loa. Bạn cũng có thể thêm loa bằng cách:

* Âm thanh HDMI qua màn hình hoặc TV  
* Loa USB  
* Tai nghe USB  
* Loa ngoài USB tích hợp micro  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) với loa được gắn, thông qua jack 3.5mm hoặc cổng JST  

## Kết nối và cấu hình micro và loa

Micro và loa cần được kết nối và cấu hình.

### Nhiệm vụ - kết nối và cấu hình micro

1. Kết nối micro bằng phương pháp phù hợp. Ví dụ, kết nối qua một trong các cổng USB.

1. Nếu bạn đang sử dụng ReSpeaker 2-Mics Pi HAT, bạn có thể tháo Grove base hat, sau đó gắn ReSpeaker hat vào vị trí của nó.

    ![Một Raspberry Pi với ReSpeaker hat](../../../../../translated_images/vi/pi-respeaker-hat.f00fabe7dd039a93.webp)

    Bạn sẽ cần một nút Grove sau này trong bài học, nhưng một nút đã được tích hợp trong hat này, vì vậy Grove base hat không cần thiết.

    Sau khi hat được gắn, bạn sẽ cần cài đặt một số driver. Tham khảo [hướng dẫn bắt đầu của Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) để biết hướng dẫn cài đặt driver.

    > ⚠️ Hướng dẫn sử dụng `git` để clone một repository. Nếu bạn chưa cài đặt `git` trên Pi, bạn có thể cài đặt bằng cách chạy lệnh sau:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Chạy lệnh sau trong Terminal trên Pi, hoặc kết nối bằng VS Code và phiên SSH từ xa để xem thông tin về micro đã kết nối:

    ```sh
    arecord -l
    ```

    Bạn sẽ thấy danh sách các micro đã kết nối. Nó sẽ giống như sau:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Giả sử bạn chỉ có một micro, bạn sẽ chỉ thấy một mục. Việc cấu hình micro có thể phức tạp trên Linux, vì vậy tốt nhất là chỉ sử dụng một micro và rút bất kỳ micro nào khác.

    Ghi lại số card, vì bạn sẽ cần nó sau này. Trong đầu ra ở trên, số card là 1.

### Nhiệm vụ - kết nối và cấu hình loa

1. Kết nối loa bằng phương pháp phù hợp.

1. Chạy lệnh sau trong Terminal trên Pi, hoặc kết nối bằng VS Code và phiên SSH từ xa để xem thông tin về loa đã kết nối:

    ```sh
    aplay -l
    ```

    Bạn sẽ thấy danh sách các loa đã kết nối. Nó sẽ giống như sau:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Bạn sẽ luôn thấy `card 0: Headphones` vì đây là jack tai nghe tích hợp. Nếu bạn đã thêm loa bổ sung, chẳng hạn như loa USB, bạn sẽ thấy nó được liệt kê.

1. Nếu bạn đang sử dụng loa bổ sung, và không phải loa hoặc tai nghe kết nối với jack tai nghe tích hợp, bạn cần cấu hình nó làm mặc định. Để làm điều này, chạy lệnh sau:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Lệnh này sẽ mở một tệp cấu hình trong `nano`, một trình chỉnh sửa văn bản dựa trên terminal. Cuộn xuống bằng các phím mũi tên trên bàn phím cho đến khi bạn tìm thấy dòng sau:

    ```output
    defaults.pcm.card 0
    ```

    Thay đổi giá trị từ `0` thành số card của card bạn muốn sử dụng từ danh sách trả về từ lệnh `aplay -l`. Ví dụ, trong đầu ra ở trên có một card âm thanh thứ hai gọi là `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, sử dụng card 1. Để sử dụng card này, tôi sẽ cập nhật dòng thành:

    ```output
    defaults.pcm.card 1
    ```

    Đặt giá trị này thành số card phù hợp. Bạn có thể điều hướng đến số bằng các phím mũi tên trên bàn phím, sau đó xóa và nhập số mới như bình thường khi chỉnh sửa tệp văn bản.

1. Lưu thay đổi và đóng tệp bằng cách nhấn `Ctrl+x`. Nhấn `y` để lưu tệp, sau đó `return` để chọn tên tệp.

### Nhiệm vụ - kiểm tra micro và loa

1. Chạy lệnh sau để ghi âm 5 giây âm thanh qua micro:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Trong khi lệnh này đang chạy, tạo âm thanh vào micro như nói, hát, beatbox, chơi nhạc cụ hoặc bất cứ điều gì bạn thích.

1. Sau 5 giây, việc ghi âm sẽ dừng. Chạy lệnh sau để phát lại âm thanh:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Bạn sẽ nghe âm thanh được phát lại qua loa. Điều chỉnh âm lượng đầu ra trên loa nếu cần.

1. Nếu bạn cần điều chỉnh âm lượng của cổng micro tích hợp, hoặc điều chỉnh độ nhạy của micro, bạn có thể sử dụng tiện ích `alsamixer`. Bạn có thể đọc thêm về tiện ích này trên [trang man của Linux alsamixer](https://linux.die.net/man/1/alsamixer).

1. Nếu bạn gặp lỗi khi phát lại âm thanh, hãy kiểm tra card bạn đã đặt làm `defaults.pcm.card` trong tệp `alsa.conf`.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.