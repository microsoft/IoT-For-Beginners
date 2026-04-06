# Dịch giọng nói - Raspberry Pi

Trong phần này của bài học, bạn sẽ viết mã để dịch văn bản bằng dịch vụ dịch thuật.

## Chuyển đổi văn bản thành giọng nói bằng dịch vụ dịch thuật

API REST của dịch vụ giọng nói không hỗ trợ dịch trực tiếp, thay vào đó bạn có thể sử dụng dịch vụ Translator để dịch văn bản được tạo bởi dịch vụ chuyển giọng nói thành văn bản, và văn bản của phản hồi được nói. Dịch vụ này có một API REST mà bạn có thể sử dụng để dịch văn bản.

### Nhiệm vụ - sử dụng tài nguyên dịch thuật để dịch văn bản

1. Bộ hẹn giờ thông minh của bạn sẽ có 2 ngôn ngữ được thiết lập - ngôn ngữ của máy chủ được sử dụng để huấn luyện LUIS (cũng là ngôn ngữ được sử dụng để tạo các thông điệp nói với người dùng), và ngôn ngữ được người dùng nói. Cập nhật biến `language` thành ngôn ngữ mà người dùng sẽ nói, và thêm một biến mới có tên là `server_language` cho ngôn ngữ được sử dụng để huấn luyện LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Thay thế `<user language>` bằng tên địa phương của ngôn ngữ bạn sẽ nói, ví dụ `fr-FR` cho tiếng Pháp, hoặc `zn-HK` cho tiếng Quảng Đông.

    Thay thế `<server language>` bằng tên địa phương của ngôn ngữ được sử dụng để huấn luyện LUIS.

    Bạn có thể tìm danh sách các ngôn ngữ được hỗ trợ và tên địa phương của chúng trong [tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Nếu bạn không nói được nhiều ngôn ngữ, bạn có thể sử dụng một dịch vụ như [Bing Translate](https://www.bing.com/translator) hoặc [Google Translate](https://translate.google.com) để dịch từ ngôn ngữ ưa thích của bạn sang một ngôn ngữ khác. Các dịch vụ này sau đó có thể phát âm thanh của văn bản đã dịch.
    >
    > Ví dụ, nếu bạn huấn luyện LUIS bằng tiếng Anh, nhưng muốn sử dụng tiếng Pháp làm ngôn ngữ người dùng, bạn có thể dịch các câu như "set a 2 minute and 27 second timer" từ tiếng Anh sang tiếng Pháp bằng Bing Translate, sau đó sử dụng nút **Nghe bản dịch** để nói bản dịch vào micro của bạn.
    >
    > ![Nút nghe bản dịch trên Bing Translate](../../../../../translated_images/vi/bing-translate.348aa796d6efe2a9.webp)

1. Thêm khóa API của dịch vụ dịch thuật bên dưới `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Thay thế `<key>` bằng khóa API cho tài nguyên dịch vụ dịch thuật của bạn.

1. Phía trên hàm `say`, định nghĩa một hàm `translate_text` để dịch văn bản từ ngôn ngữ máy chủ sang ngôn ngữ người dùng:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Các ngôn ngữ nguồn và đích được truyền vào hàm này - ứng dụng của bạn cần chuyển đổi từ ngôn ngữ người dùng sang ngôn ngữ máy chủ khi nhận diện giọng nói, và từ ngôn ngữ máy chủ sang ngôn ngữ người dùng khi cung cấp phản hồi bằng giọng nói.

1. Bên trong hàm này, định nghĩa URL và tiêu đề cho cuộc gọi API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL cho API này không phụ thuộc vào vị trí, thay vào đó vị trí được truyền vào dưới dạng tiêu đề. Khóa API được sử dụng trực tiếp, vì vậy không giống như dịch vụ giọng nói, không cần lấy mã thông báo truy cập từ API cấp mã thông báo.

1. Bên dưới, định nghĩa các tham số và nội dung cho cuộc gọi:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` định nghĩa các tham số để truyền vào cuộc gọi API, truyền ngôn ngữ nguồn và đích. Cuộc gọi này sẽ dịch văn bản từ ngôn ngữ `from` sang ngôn ngữ `to`.

    `body` chứa văn bản cần dịch. Đây là một mảng, vì nhiều khối văn bản có thể được dịch trong cùng một cuộc gọi.

1. Thực hiện cuộc gọi API REST và nhận phản hồi:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Phản hồi trả về là một mảng JSON, với một mục chứa các bản dịch. Mục này có một mảng cho các bản dịch của tất cả các mục được truyền vào nội dung.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Trả về thuộc tính `text` từ bản dịch đầu tiên trong mục đầu tiên của mảng:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Cập nhật vòng lặp `while True` để dịch văn bản từ cuộc gọi `convert_speech_to_text` từ ngôn ngữ người dùng sang ngôn ngữ máy chủ:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Đoạn mã này cũng in phiên bản gốc và phiên bản đã dịch của văn bản ra bảng điều khiển.

1. Cập nhật hàm `say` để dịch văn bản cần nói từ ngôn ngữ máy chủ sang ngôn ngữ người dùng:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Đoạn mã này cũng in phiên bản gốc và phiên bản đã dịch của văn bản ra bảng điều khiển.

1. Chạy mã của bạn. Đảm bảo ứng dụng chức năng của bạn đang chạy, và yêu cầu một bộ hẹn giờ bằng ngôn ngữ người dùng, bằng cách tự nói ngôn ngữ đó hoặc sử dụng một ứng dụng dịch thuật.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Do cách diễn đạt khác nhau trong các ngôn ngữ khác nhau, bạn có thể nhận được các bản dịch hơi khác so với các ví dụ bạn đã cung cấp cho LUIS. Nếu điều này xảy ra, hãy thêm nhiều ví dụ hơn vào LUIS, huấn luyện lại và sau đó xuất bản lại mô hình.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Chương trình hẹn giờ đa ngôn ngữ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.