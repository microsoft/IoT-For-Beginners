<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T23:30:53+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "vi"
}
-->
# Chuyển giọng nói thành văn bản - Raspberry Pi

Trong phần này của bài học, bạn sẽ viết mã để chuyển đổi giọng nói trong âm thanh thu được thành văn bản bằng cách sử dụng dịch vụ giọng nói.

## Gửi âm thanh đến dịch vụ giọng nói

Âm thanh có thể được gửi đến dịch vụ giọng nói bằng REST API. Để sử dụng dịch vụ giọng nói, trước tiên bạn cần yêu cầu một mã truy cập, sau đó sử dụng mã đó để truy cập REST API. Các mã truy cập này hết hạn sau 10 phút, vì vậy mã của bạn cần yêu cầu chúng thường xuyên để đảm bảo chúng luôn được cập nhật.

### Nhiệm vụ - lấy mã truy cập

1. Mở dự án `smart-timer` trên Pi của bạn.

1. Xóa hàm `play_audio`. Hàm này không còn cần thiết vì bạn không muốn bộ hẹn giờ thông minh lặp lại những gì bạn đã nói.

1. Thêm phần nhập sau vào đầu tệp `app.py`:

    ```python
    import requests
    ```

1. Thêm đoạn mã sau vào phía trên vòng lặp `while True` để khai báo một số cài đặt cho dịch vụ giọng nói:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Thay thế `<key>` bằng khóa API cho tài nguyên dịch vụ giọng nói của bạn. Thay thế `<location>` bằng vị trí bạn đã sử dụng khi tạo tài nguyên dịch vụ giọng nói.

    Thay thế `<language>` bằng tên ngôn ngữ mà bạn sẽ nói, ví dụ `en-GB` cho tiếng Anh, hoặc `zn-HK` cho tiếng Quảng Đông. Bạn có thể tìm danh sách các ngôn ngữ được hỗ trợ và tên ngôn ngữ của chúng trong [tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Bên dưới đoạn này, thêm hàm sau để lấy mã truy cập:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Hàm này gọi một điểm cuối cấp mã, truyền khóa API dưới dạng tiêu đề. Lời gọi này trả về một mã truy cập có thể được sử dụng để gọi các dịch vụ giọng nói.

1. Bên dưới đoạn này, khai báo một hàm để chuyển đổi giọng nói trong âm thanh thu được thành văn bản bằng REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Bên trong hàm này, thiết lập URL REST API và tiêu đề:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Hàm này xây dựng một URL bằng cách sử dụng vị trí của tài nguyên dịch vụ giọng nói. Sau đó, nó điền tiêu đề với mã truy cập từ hàm `get_access_token`, cũng như tốc độ mẫu được sử dụng để thu âm thanh. Cuối cùng, nó định nghĩa một số tham số được truyền cùng với URL chứa ngôn ngữ trong âm thanh.

1. Bên dưới đoạn này, thêm đoạn mã sau để gọi REST API và nhận lại văn bản:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Hàm này gọi URL và giải mã giá trị JSON trong phản hồi. Giá trị `RecognitionStatus` trong phản hồi cho biết liệu lời gọi có thể chuyển đổi giọng nói thành văn bản thành công hay không, và nếu giá trị này là `Success`, thì văn bản sẽ được trả về từ hàm, nếu không thì một chuỗi rỗng sẽ được trả về.

1. Phía trên vòng lặp `while True:`, định nghĩa một hàm để xử lý văn bản trả về từ dịch vụ chuyển đổi giọng nói thành văn bản. Hàm này sẽ chỉ in văn bản ra màn hình điều khiển.

    ```python
    def process_text(text):
        print(text)
    ```

1. Cuối cùng, thay thế lời gọi đến `play_audio` trong vòng lặp `while True` bằng lời gọi đến hàm `convert_speech_to_text`, truyền văn bản đến hàm `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Chạy mã. Nhấn nút và nói vào micro. Thả nút khi bạn hoàn tất, và âm thanh sẽ được chuyển đổi thành văn bản và in ra màn hình điều khiển.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Thử các loại câu khác nhau, cùng với các câu mà các từ nghe giống nhau nhưng có nghĩa khác nhau. Ví dụ, nếu bạn đang nói tiếng Anh, hãy nói 'I want to buy two bananas and an apple too', và chú ý cách nó sử dụng đúng từ to, two và too dựa trên ngữ cảnh của từ, không chỉ dựa vào âm thanh của nó.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Chương trình chuyển đổi giọng nói thành văn bản của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.