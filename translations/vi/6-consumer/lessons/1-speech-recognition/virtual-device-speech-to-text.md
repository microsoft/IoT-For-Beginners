<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T23:23:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "vi"
}
-->
# Chuyển giọng nói thành văn bản - Thiết bị IoT ảo

Trong phần này của bài học, bạn sẽ viết mã để chuyển đổi giọng nói thu từ micro của bạn thành văn bản bằng dịch vụ giọng nói.

## Chuyển đổi giọng nói thành văn bản

Trên Windows, Linux và macOS, SDK Python của dịch vụ giọng nói có thể được sử dụng để lắng nghe micro của bạn và chuyển đổi bất kỳ giọng nói nào được phát hiện thành văn bản. Nó sẽ lắng nghe liên tục, phát hiện mức âm thanh và gửi giọng nói để chuyển đổi thành văn bản khi mức âm thanh giảm, chẳng hạn như khi kết thúc một đoạn nói.

### Nhiệm vụ - chuyển đổi giọng nói thành văn bản

1. Tạo một ứng dụng Python mới trên máy tính của bạn trong một thư mục có tên `smart-timer` với một tệp duy nhất có tên `app.py` và một môi trường ảo Python.

1. Cài đặt gói Pip cho dịch vụ giọng nói. Đảm bảo rằng bạn đang cài đặt từ một terminal với môi trường ảo đã được kích hoạt.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Nếu bạn gặp lỗi sau:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Bạn sẽ cần cập nhật Pip. Thực hiện điều này với lệnh sau, sau đó thử cài đặt gói lại:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Thêm các import sau vào tệp `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Điều này import một số lớp được sử dụng để nhận diện giọng nói.

1. Thêm đoạn mã sau để khai báo một số cấu hình:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Thay thế `<key>` bằng khóa API cho dịch vụ giọng nói của bạn. Thay thế `<location>` bằng vị trí bạn đã sử dụng khi tạo tài nguyên dịch vụ giọng nói.

    Thay thế `<language>` bằng tên ngôn ngữ bạn sẽ nói, ví dụ `en-GB` cho tiếng Anh, hoặc `zn-HK` cho tiếng Quảng Đông. Bạn có thể tìm danh sách các ngôn ngữ được hỗ trợ và tên của chúng trong [tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Cấu hình này sau đó được sử dụng để tạo một đối tượng `SpeechConfig` sẽ được sử dụng để cấu hình dịch vụ giọng nói.

1. Thêm đoạn mã sau để tạo một bộ nhận diện giọng nói:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Bộ nhận diện giọng nói chạy trên một luồng nền, lắng nghe âm thanh và chuyển đổi bất kỳ giọng nói nào trong đó thành văn bản. Bạn có thể lấy văn bản bằng cách sử dụng một hàm callback - một hàm bạn định nghĩa và truyền cho bộ nhận diện. Mỗi khi giọng nói được phát hiện, callback sẽ được gọi. Thêm đoạn mã sau để định nghĩa một callback, và truyền callback này cho bộ nhận diện, cũng như định nghĩa một hàm để xử lý văn bản, ghi nó ra console:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Bộ nhận diện chỉ bắt đầu lắng nghe khi bạn khởi động nó một cách rõ ràng. Thêm đoạn mã sau để bắt đầu nhận diện. Điều này chạy trong nền, vì vậy ứng dụng của bạn cũng sẽ cần một vòng lặp vô hạn để giữ cho ứng dụng chạy.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Chạy ứng dụng này. Nói vào micro của bạn và âm thanh được chuyển đổi thành văn bản sẽ được xuất ra console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Thử các loại câu khác nhau, cùng với các câu mà từ ngữ nghe giống nhau nhưng có nghĩa khác nhau. Ví dụ, nếu bạn đang nói tiếng Anh, hãy nói 'I want to buy two bananas and an apple too', và chú ý cách nó sử dụng đúng từ to, two và too dựa trên ngữ cảnh của từ, không chỉ âm thanh của nó.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Chương trình chuyển đổi giọng nói thành văn bản của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.