<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T23:01:34+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "vi"
}
-->
# Dịch giọng nói - Thiết bị IoT ảo

Trong phần này của bài học, bạn sẽ viết mã để dịch giọng nói khi chuyển đổi thành văn bản bằng dịch vụ giọng nói, sau đó dịch văn bản bằng dịch vụ Translator trước khi tạo phản hồi bằng giọng nói.

## Sử dụng dịch vụ giọng nói để dịch giọng nói

Dịch vụ giọng nói có thể nhận giọng nói và không chỉ chuyển đổi thành văn bản cùng ngôn ngữ, mà còn dịch đầu ra sang các ngôn ngữ khác.

### Nhiệm vụ - sử dụng dịch vụ giọng nói để dịch giọng nói

1. Mở dự án `smart-timer` trong VS Code và đảm bảo môi trường ảo đã được tải trong terminal.

1. Thêm các câu lệnh import sau đây bên dưới các câu lệnh import hiện có:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Điều này nhập các lớp được sử dụng để dịch giọng nói và thư viện `requests` sẽ được sử dụng để gọi dịch vụ Translator sau trong bài học này.

1. Bộ hẹn giờ thông minh của bạn sẽ có 2 ngôn ngữ được thiết lập - ngôn ngữ của máy chủ được sử dụng để huấn luyện LUIS (ngôn ngữ này cũng được sử dụng để tạo các thông điệp nói với người dùng), và ngôn ngữ được người dùng nói. Cập nhật biến `language` thành ngôn ngữ mà người dùng sẽ nói, và thêm một biến mới gọi là `server_language` cho ngôn ngữ được sử dụng để huấn luyện LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Thay thế `<user language>` bằng tên địa phương của ngôn ngữ bạn sẽ nói, ví dụ `fr-FR` cho tiếng Pháp, hoặc `zn-HK` cho tiếng Quảng Đông.

    Thay thế `<server language>` bằng tên địa phương của ngôn ngữ được sử dụng để huấn luyện LUIS.

    Bạn có thể tìm danh sách các ngôn ngữ được hỗ trợ và tên địa phương của chúng trong [Tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Nếu bạn không nói được nhiều ngôn ngữ, bạn có thể sử dụng dịch vụ như [Bing Translate](https://www.bing.com/translator) hoặc [Google Translate](https://translate.google.com) để dịch từ ngôn ngữ ưa thích của bạn sang một ngôn ngữ khác. Các dịch vụ này sau đó có thể phát âm thanh của văn bản đã dịch. Lưu ý rằng trình nhận diện giọng nói sẽ bỏ qua một số âm thanh đầu ra từ thiết bị của bạn, vì vậy bạn có thể cần sử dụng một thiết bị bổ sung để phát văn bản đã dịch.
    >
    > Ví dụ, nếu bạn huấn luyện LUIS bằng tiếng Anh, nhưng muốn sử dụng tiếng Pháp làm ngôn ngữ người dùng, bạn có thể dịch các câu như "set a 2 minute and 27 second timer" từ tiếng Anh sang tiếng Pháp bằng Bing Translate, sau đó sử dụng nút **Nghe bản dịch** để nói bản dịch vào micro của bạn.
    >
    > ![Nút nghe bản dịch trên Bing Translate](../../../../../translated_images/vi/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Thay thế các khai báo `recognizer_config` và `recognizer` bằng đoạn mã sau:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Điều này tạo một cấu hình dịch để nhận diện giọng nói bằng ngôn ngữ người dùng và tạo các bản dịch bằng ngôn ngữ người dùng và ngôn ngữ máy chủ. Sau đó, nó sử dụng cấu hình này để tạo một trình nhận diện dịch - một trình nhận diện giọng nói có thể dịch đầu ra của nhận diện giọng nói sang nhiều ngôn ngữ.

    > 💁 Ngôn ngữ gốc cần được chỉ định trong `target_languages`, nếu không bạn sẽ không nhận được bất kỳ bản dịch nào.

1. Cập nhật hàm `recognized`, thay thế toàn bộ nội dung của hàm bằng đoạn mã sau:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Đoạn mã này kiểm tra xem sự kiện nhận diện có được kích hoạt do giọng nói đã được dịch hay không (sự kiện này có thể được kích hoạt vào các thời điểm khác, chẳng hạn khi giọng nói được nhận diện nhưng không được dịch). Nếu giọng nói đã được dịch, nó tìm bản dịch trong từ điển `args.result.translations` khớp với ngôn ngữ máy chủ.

    Từ điển `args.result.translations` được khóa bằng phần ngôn ngữ của cài đặt địa phương, không phải toàn bộ cài đặt. Ví dụ, nếu bạn yêu cầu một bản dịch sang `fr-FR` cho tiếng Pháp, từ điển sẽ chứa một mục cho `fr`, không phải `fr-FR`.

    Văn bản đã dịch sau đó được gửi đến IoT Hub.

1. Chạy đoạn mã này để kiểm tra các bản dịch. Đảm bảo ứng dụng chức năng của bạn đang chạy và yêu cầu một bộ hẹn giờ bằng ngôn ngữ người dùng, bằng cách tự nói ngôn ngữ đó hoặc sử dụng ứng dụng dịch.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Dịch văn bản bằng dịch vụ Translator

Dịch vụ giọng nói không hỗ trợ dịch văn bản trở lại thành giọng nói, thay vào đó bạn có thể sử dụng dịch vụ Translator để dịch văn bản. Dịch vụ này có một REST API mà bạn có thể sử dụng để dịch văn bản.

### Nhiệm vụ - sử dụng tài nguyên Translator để dịch văn bản

1. Thêm khóa API Translator bên dưới `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Thay thế `<key>` bằng khóa API cho tài nguyên dịch vụ Translator của bạn.

1. Phía trên hàm `say`, định nghĩa một hàm `translate_text` sẽ dịch văn bản từ ngôn ngữ máy chủ sang ngôn ngữ người dùng:

    ```python
    def translate_text(text):
    ```

1. Bên trong hàm này, định nghĩa URL và headers cho cuộc gọi REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL cho API này không phụ thuộc vào vị trí, thay vào đó vị trí được truyền vào dưới dạng một header. Khóa API được sử dụng trực tiếp, vì vậy không giống như dịch vụ giọng nói, không cần lấy token truy cập từ API cấp phát token.

1. Bên dưới đoạn mã này, định nghĩa các tham số và nội dung cho cuộc gọi:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` định nghĩa các tham số để truyền vào cuộc gọi API, truyền ngôn ngữ nguồn và ngôn ngữ đích. Cuộc gọi này sẽ dịch văn bản từ ngôn ngữ `from` sang ngôn ngữ `to`.

    `body` chứa văn bản cần dịch. Đây là một mảng, vì nhiều khối văn bản có thể được dịch trong cùng một cuộc gọi.

1. Thực hiện cuộc gọi REST API và nhận phản hồi:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Phản hồi trả về là một mảng JSON, với một mục chứa các bản dịch. Mục này có một mảng cho các bản dịch của tất cả các mục được truyền vào nội dung.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Trả về thuộc tính `text` từ bản dịch đầu tiên của mục đầu tiên trong mảng:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Cập nhật hàm `say` để dịch văn bản cần nói trước khi SSML được tạo:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Đoạn mã này cũng in phiên bản gốc và phiên bản đã dịch của văn bản ra console.

1. Chạy đoạn mã của bạn. Đảm bảo ứng dụng chức năng của bạn đang chạy và yêu cầu một bộ hẹn giờ bằng ngôn ngữ người dùng, bằng cách tự nói ngôn ngữ đó hoặc sử dụng ứng dụng dịch.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Do cách diễn đạt khác nhau trong các ngôn ngữ khác nhau, bạn có thể nhận được các bản dịch hơi khác so với các ví dụ bạn đã cung cấp cho LUIS. Nếu điều này xảy ra, hãy thêm nhiều ví dụ hơn vào LUIS, huấn luyện lại và sau đó xuất bản lại mô hình.

> 💁 Bạn có thể tìm đoạn mã này trong thư mục [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Chương trình hẹn giờ đa ngôn ngữ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.