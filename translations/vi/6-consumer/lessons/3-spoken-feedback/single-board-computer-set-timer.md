<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T23:21:15+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "vi"
}
-->
# Đặt hẹn giờ - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ gọi mã serverless của mình để hiểu giọng nói và đặt hẹn giờ trên thiết bị IoT ảo hoặc Raspberry Pi dựa trên kết quả.

## Đặt hẹn giờ

Văn bản được trả về từ cuộc gọi chuyển đổi giọng nói thành văn bản cần được gửi đến mã serverless của bạn để được xử lý bởi LUIS, từ đó nhận lại số giây cho hẹn giờ. Số giây này sẽ được sử dụng để đặt hẹn giờ.

Hẹn giờ có thể được đặt bằng cách sử dụng lớp `threading.Timer` trong Python. Lớp này nhận thời gian trễ và một hàm, sau thời gian trễ, hàm sẽ được thực thi.

### Nhiệm vụ - gửi văn bản đến hàm serverless

1. Mở dự án `smart-timer` trong VS Code và đảm bảo môi trường ảo đã được tải trong terminal nếu bạn đang sử dụng thiết bị IoT ảo.

1. Phía trên hàm `process_text`, khai báo một hàm có tên `get_timer_time` để gọi REST endpoint mà bạn đã tạo:

    ```python
    def get_timer_time(text):
    ```

1. Thêm đoạn mã sau vào hàm này để xác định URL cần gọi:

    ```python
    url = '<URL>'
    ```

    Thay thế `<URL>` bằng URL của REST endpoint mà bạn đã xây dựng trong bài học trước, có thể trên máy tính của bạn hoặc trên đám mây.

1. Thêm đoạn mã sau để đặt văn bản làm thuộc tính được truyền dưới dạng JSON trong cuộc gọi:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Bên dưới đoạn này, lấy `seconds` từ payload phản hồi, trả về 0 nếu cuộc gọi thất bại:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Các cuộc gọi HTTP thành công trả về mã trạng thái trong khoảng 200, và mã serverless của bạn sẽ trả về 200 nếu văn bản được xử lý và nhận diện là ý định đặt hẹn giờ.

### Nhiệm vụ - đặt hẹn giờ trên một luồng nền

1. Thêm câu lệnh import sau ở đầu tệp để nhập thư viện threading của Python:

    ```python
    import threading
    ```

1. Phía trên hàm `process_text`, thêm một hàm để phát âm phản hồi. Hiện tại, hàm này chỉ ghi ra console, nhưng sau này trong bài học, hàm này sẽ phát âm văn bản.

    ```python
    def say(text):
        print(text)
    ```

1. Bên dưới đoạn này, thêm một hàm sẽ được gọi bởi hẹn giờ để thông báo rằng hẹn giờ đã hoàn tất:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Hàm này nhận số phút và giây của hẹn giờ, sau đó tạo một câu để thông báo rằng hẹn giờ đã hoàn tất. Nó sẽ kiểm tra số phút và giây, và chỉ bao gồm đơn vị thời gian nếu có giá trị. Ví dụ, nếu số phút là 0 thì chỉ bao gồm giây trong thông báo. Câu này sau đó được gửi đến hàm `say`.

1. Bên dưới đoạn này, thêm hàm `create_timer` sau để tạo hẹn giờ:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Hàm này nhận tổng số giây của hẹn giờ được gửi trong lệnh, sau đó chuyển đổi thành phút và giây. Nó tạo và khởi động một đối tượng hẹn giờ sử dụng tổng số giây, truyền vào hàm `announce_timer` và một danh sách chứa số phút và giây. Khi hẹn giờ kết thúc, nó sẽ gọi hàm `announce_timer` và truyền nội dung của danh sách này làm tham số - vì vậy mục đầu tiên trong danh sách sẽ được truyền làm tham số `minutes`, và mục thứ hai làm tham số `seconds`.

1. Ở cuối hàm `create_timer`, thêm một số đoạn mã để tạo thông báo được phát âm cho người dùng, thông báo rằng hẹn giờ đang bắt đầu:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Một lần nữa, đoạn này chỉ bao gồm đơn vị thời gian có giá trị. Câu này sau đó được gửi đến hàm `say`.

1. Thêm đoạn sau vào cuối hàm `process_text` để lấy thời gian cho hẹn giờ từ văn bản, sau đó tạo hẹn giờ:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Hẹn giờ chỉ được tạo nếu số giây lớn hơn 0.

1. Chạy ứng dụng và đảm bảo ứng dụng hàm cũng đang chạy. Đặt một số hẹn giờ, và đầu ra sẽ hiển thị hẹn giờ đang được đặt, sau đó hiển thị khi hẹn giờ kết thúc:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) hoặc [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Chương trình hẹn giờ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.