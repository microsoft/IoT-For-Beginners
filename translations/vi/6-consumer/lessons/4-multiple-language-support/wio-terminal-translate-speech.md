<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T23:40:24+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "vi"
}
-->
# Dịch giọng nói - Wio Terminal

Trong phần này của bài học, bạn sẽ viết mã để dịch văn bản bằng dịch vụ dịch thuật.

## Chuyển đổi văn bản thành giọng nói bằng dịch vụ dịch thuật

API REST của dịch vụ giọng nói không hỗ trợ dịch trực tiếp, thay vào đó bạn có thể sử dụng dịch vụ Translator để dịch văn bản được tạo bởi dịch vụ chuyển đổi giọng nói thành văn bản, và văn bản của phản hồi được nói. Dịch vụ này có một API REST mà bạn có thể sử dụng để dịch văn bản, nhưng để dễ sử dụng hơn, nó sẽ được bao bọc trong một HTTP trigger khác trong ứng dụng chức năng của bạn.

### Nhiệm vụ - tạo một chức năng serverless để dịch văn bản

1. Mở dự án `smart-timer-trigger` của bạn trong VS Code, và mở terminal đảm bảo môi trường ảo đã được kích hoạt. Nếu chưa, hãy tắt và tạo lại terminal.

1. Mở tệp `local.settings.json` và thêm các thiết lập cho khóa API và vị trí của dịch vụ dịch thuật:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Thay thế `<key>` bằng khóa API cho tài nguyên dịch vụ dịch thuật của bạn. Thay thế `<location>` bằng vị trí bạn đã sử dụng khi tạo tài nguyên dịch vụ dịch thuật.

1. Thêm một HTTP trigger mới vào ứng dụng này có tên `translate-text` bằng cách sử dụng lệnh sau từ bên trong terminal của VS Code trong thư mục gốc của dự án ứng dụng chức năng:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Điều này sẽ tạo một HTTP trigger có tên `translate-text`.

1. Thay thế nội dung của tệp `__init__.py` trong thư mục `translate-text` bằng nội dung sau:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Mã này trích xuất văn bản và ngôn ngữ từ yêu cầu HTTP. Sau đó, nó thực hiện một yêu cầu tới API REST của dịch vụ dịch thuật, truyền các ngôn ngữ làm tham số cho URL và văn bản cần dịch làm nội dung. Cuối cùng, bản dịch được trả về.

1. Chạy ứng dụng chức năng của bạn cục bộ. Sau đó, bạn có thể gọi nó bằng một công cụ như curl theo cách tương tự như bạn đã thử nghiệm HTTP trigger `text-to-timer`. Đảm bảo truyền văn bản cần dịch và ngôn ngữ dưới dạng JSON body:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Ví dụ này dịch *Définir une minuterie de 30 secondes* từ tiếng Pháp sang tiếng Anh Mỹ. Nó sẽ trả về *Set a 30-second timer*.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Nhiệm vụ - sử dụng chức năng dịch thuật để dịch văn bản

1. Mở dự án `smart-timer` trong VS Code nếu nó chưa được mở.

1. Bộ hẹn giờ thông minh của bạn sẽ có 2 ngôn ngữ được thiết lập - ngôn ngữ của máy chủ được sử dụng để huấn luyện LUIS (ngôn ngữ này cũng được sử dụng để xây dựng các thông điệp nói với người dùng), và ngôn ngữ được nói bởi người dùng. Cập nhật hằng số `LANGUAGE` trong tệp tiêu đề `config.h` thành ngôn ngữ sẽ được nói bởi người dùng, và thêm một hằng số mới có tên `SERVER_LANGUAGE` cho ngôn ngữ được sử dụng để huấn luyện LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Thay thế `<user language>` bằng tên địa phương cho ngôn ngữ bạn sẽ nói, ví dụ `fr-FR` cho tiếng Pháp, hoặc `zn-HK` cho tiếng Quảng Đông.

    Thay thế `<server language>` bằng tên địa phương cho ngôn ngữ được sử dụng để huấn luyện LUIS.

    Bạn có thể tìm danh sách các ngôn ngữ được hỗ trợ và tên địa phương của chúng trong [Tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Nếu bạn không nói được nhiều ngôn ngữ, bạn có thể sử dụng một dịch vụ như [Bing Translate](https://www.bing.com/translator) hoặc [Google Translate](https://translate.google.com) để dịch từ ngôn ngữ ưa thích của bạn sang một ngôn ngữ khác. Các dịch vụ này sau đó có thể phát âm thanh của văn bản đã dịch.
    >
    > Ví dụ, nếu bạn huấn luyện LUIS bằng tiếng Anh, nhưng muốn sử dụng tiếng Pháp làm ngôn ngữ người dùng, bạn có thể dịch các câu như "set a 2 minute and 27 second timer" từ tiếng Anh sang tiếng Pháp bằng Bing Translate, sau đó sử dụng nút **Listen translation** để nói bản dịch vào micro của bạn.
    >
    > ![Nút nghe bản dịch trên Bing Translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.vi.png)

1. Thêm khóa API và vị trí của dịch vụ dịch thuật bên dưới `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Thay thế `<KEY>` bằng khóa API cho tài nguyên dịch vụ dịch thuật của bạn. Thay thế `<LOCATION>` bằng vị trí bạn đã sử dụng khi tạo tài nguyên dịch vụ dịch thuật.

1. Thêm URL trigger dịch thuật bên dưới `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Thay thế `<URL>` bằng URL cho HTTP trigger `translate-text` trên ứng dụng chức năng của bạn. Điều này sẽ giống với giá trị của `TEXT_TO_TIMER_FUNCTION_URL`, ngoại trừ tên chức năng là `translate-text` thay vì `text-to-timer`.

1. Thêm một tệp mới vào thư mục `src` có tên `text_translator.h`.

1. Tệp tiêu đề `text_translator.h` mới này sẽ chứa một lớp để dịch văn bản. Thêm nội dung sau vào tệp này để khai báo lớp:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Điều này khai báo lớp `TextTranslator`, cùng với một instance của lớp này. Lớp có một trường duy nhất cho WiFi client.

1. Trong phần `public` của lớp này, thêm một phương thức để dịch văn bản:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Phương thức này nhận ngôn ngữ cần dịch từ và ngôn ngữ cần dịch sang. Khi xử lý giọng nói, giọng nói sẽ được dịch từ ngôn ngữ người dùng sang ngôn ngữ máy chủ LUIS, và khi đưa ra phản hồi, nó sẽ dịch từ ngôn ngữ máy chủ LUIS sang ngôn ngữ người dùng.

1. Trong phương thức này, thêm mã để tạo một JSON body chứa văn bản cần dịch và các ngôn ngữ:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Bên dưới đó, thêm mã để gửi body tới ứng dụng chức năng serverless:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Tiếp theo, thêm mã để nhận phản hồi:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Cuối cùng, thêm mã để đóng kết nối và trả về văn bản đã dịch:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Nhiệm vụ - dịch giọng nói nhận diện và các phản hồi

1. Mở tệp `main.cpp`.

1. Thêm một chỉ thị include ở đầu tệp cho tệp tiêu đề lớp `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Văn bản được nói khi một bộ hẹn giờ được thiết lập hoặc hết hạn cần được dịch. Để làm điều này, thêm nội dung sau làm dòng đầu tiên của hàm `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Điều này sẽ dịch văn bản sang ngôn ngữ của người dùng.

1. Trong hàm `processAudio`, văn bản được lấy từ âm thanh đã ghi với lệnh `String text = speechToText.convertSpeechToText();`. Sau lệnh này, dịch văn bản:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Điều này sẽ dịch văn bản từ ngôn ngữ của người dùng sang ngôn ngữ được sử dụng trên máy chủ.

1. Biên dịch mã này, tải nó lên Wio Terminal của bạn và thử nghiệm thông qua serial monitor. Khi bạn thấy `Ready` trong serial monitor, nhấn nút C (nút ở bên trái, gần công tắc nguồn nhất), và nói. Đảm bảo ứng dụng chức năng của bạn đang chạy, và yêu cầu một bộ hẹn giờ bằng ngôn ngữ người dùng, bằng cách nói ngôn ngữ đó hoặc sử dụng ứng dụng dịch thuật.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Chương trình hẹn giờ đa ngôn ngữ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.