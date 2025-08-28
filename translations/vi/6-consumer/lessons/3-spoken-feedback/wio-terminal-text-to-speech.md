<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T23:14:20+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "vi"
}
-->
# Chuyển đổi văn bản thành giọng nói - Wio Terminal

Trong phần này của bài học, bạn sẽ chuyển đổi văn bản thành giọng nói để cung cấp phản hồi bằng lời nói.

## Chuyển đổi văn bản thành giọng nói

SDK dịch vụ giọng nói mà bạn đã sử dụng trong bài học trước để chuyển đổi giọng nói thành văn bản cũng có thể được sử dụng để chuyển đổi văn bản thành giọng nói.

## Lấy danh sách các giọng nói

Khi yêu cầu giọng nói, bạn cần cung cấp giọng nói để sử dụng vì giọng nói có thể được tạo ra bằng nhiều giọng khác nhau. Mỗi ngôn ngữ hỗ trợ một loạt các giọng nói khác nhau, và bạn có thể lấy danh sách các giọng nói được hỗ trợ cho mỗi ngôn ngữ từ SDK dịch vụ giọng nói. Tuy nhiên, hạn chế của vi điều khiển xuất hiện ở đây - việc gọi để lấy danh sách các giọng nói được hỗ trợ bởi dịch vụ chuyển đổi văn bản thành giọng nói là một tài liệu JSON có kích thước hơn 77KB, quá lớn để được xử lý bởi Wio Terminal. Tại thời điểm viết, danh sách đầy đủ chứa 215 giọng nói, mỗi giọng được định nghĩa bởi một tài liệu JSON như sau:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

JSON này dành cho giọng **Aria**, có nhiều phong cách giọng nói. Tất cả những gì cần thiết khi chuyển đổi văn bản thành giọng nói là tên ngắn, `en-US-AriaNeural`.

Thay vì tải xuống và giải mã toàn bộ danh sách này trên vi điều khiển của bạn, bạn sẽ cần viết một số mã serverless để lấy danh sách các giọng nói cho ngôn ngữ bạn đang sử dụng, và gọi điều này từ Wio Terminal của bạn. Mã của bạn sau đó có thể chọn một giọng nói phù hợp từ danh sách, chẳng hạn như giọng đầu tiên mà nó tìm thấy.

### Nhiệm vụ - tạo một hàm serverless để lấy danh sách các giọng nói

1. Mở dự án `smart-timer-trigger` của bạn trong VS Code, và mở terminal đảm bảo môi trường ảo đã được kích hoạt. Nếu không, hãy tắt và tạo lại terminal.

1. Mở tệp `local.settings.json` và thêm các thiết lập cho khóa API dịch vụ giọng nói và vị trí:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Thay thế `<key>` bằng khóa API cho tài nguyên dịch vụ giọng nói của bạn. Thay thế `<location>` bằng vị trí bạn đã sử dụng khi tạo tài nguyên dịch vụ giọng nói.

1. Thêm một HTTP trigger mới vào ứng dụng này có tên `get-voices` bằng lệnh sau từ bên trong terminal của VS Code trong thư mục gốc của dự án ứng dụng functions:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Điều này sẽ tạo một HTTP trigger có tên `get-voices`.

1. Thay thế nội dung của tệp `__init__.py` trong thư mục `get-voices` bằng nội dung sau:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Mã này thực hiện một yêu cầu HTTP đến endpoint để lấy danh sách các giọng nói. Danh sách giọng nói này là một khối JSON lớn với các giọng nói cho tất cả các ngôn ngữ, vì vậy các giọng nói cho ngôn ngữ được truyền trong nội dung yêu cầu sẽ được lọc ra, sau đó tên ngắn được trích xuất và trả về dưới dạng danh sách JSON. Tên ngắn là giá trị cần thiết để chuyển đổi văn bản thành giọng nói, vì vậy chỉ giá trị này được trả về.

    > 💁 Bạn có thể thay đổi bộ lọc nếu cần để chọn chỉ các giọng nói bạn muốn.

    Điều này giảm kích thước dữ liệu từ 77KB (tại thời điểm viết) xuống một tài liệu JSON nhỏ hơn nhiều. Ví dụ, đối với các giọng nói tiếng Mỹ, kích thước này là 408 byte.

1. Chạy ứng dụng functions của bạn cục bộ. Sau đó, bạn có thể gọi nó bằng một công cụ như curl theo cách tương tự như bạn đã thử nghiệm HTTP trigger `text-to-timer`. Đảm bảo truyền ngôn ngữ của bạn dưới dạng nội dung JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Thay thế `<language>` bằng ngôn ngữ của bạn, chẳng hạn như `en-GB`, hoặc `zh-CN`.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Nhiệm vụ - lấy giọng nói từ Wio Terminal của bạn

1. Mở dự án `smart-timer` của bạn trong VS Code nếu nó chưa được mở.

1. Mở tệp tiêu đề `config.h` và thêm URL cho ứng dụng functions của bạn:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Thay thế `<URL>` bằng URL cho HTTP trigger `get-voices` trên ứng dụng functions của bạn. Điều này sẽ giống với giá trị của `TEXT_TO_TIMER_FUNCTION_URL`, ngoại trừ tên hàm là `get-voices` thay vì `text-to-timer`.

1. Tạo một tệp mới trong thư mục `src` có tên `text_to_speech.h`. Tệp này sẽ được sử dụng để định nghĩa một lớp chuyển đổi từ văn bản thành giọng nói.

1. Thêm các chỉ thị include sau vào đầu tệp `text_to_speech.h` mới:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Thêm mã sau bên dưới để khai báo lớp `TextToSpeech`, cùng với một instance có thể được sử dụng trong phần còn lại của ứng dụng:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Để gọi ứng dụng functions của bạn, bạn cần khai báo một WiFi client. Thêm đoạn mã sau vào phần `private` của lớp:

    ```cpp
    WiFiClient _client;
    ```

1. Trong phần `private`, thêm một trường cho giọng nói đã chọn:

    ```cpp
    String _voice;
    ```

1. Trong phần `public`, thêm một hàm `init` để lấy giọng nói đầu tiên:

    ```cpp
    void init()
    {
    }
    ```

1. Để lấy các giọng nói, một tài liệu JSON cần được gửi đến ứng dụng functions với ngôn ngữ. Thêm đoạn mã sau vào hàm `init` để tạo tài liệu JSON này:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Tiếp theo, tạo một `HTTPClient`, sau đó sử dụng nó để gọi ứng dụng functions để lấy các giọng nói, gửi tài liệu JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Bên dưới đoạn mã này, thêm mã để kiểm tra mã phản hồi, và nếu là 200 (thành công), thì trích xuất danh sách các giọng nói, lấy giọng đầu tiên từ danh sách:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Sau đó, kết thúc kết nối HTTP client:

    ```cpp
    httpClient.end();
    ```

1. Mở tệp `main.cpp`, và thêm chỉ thị include sau vào đầu để bao gồm tệp tiêu đề mới này:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Trong hàm `setup`, bên dưới lệnh gọi đến `speechToText.init();`, thêm đoạn mã sau để khởi tạo lớp `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Biên dịch mã này, tải nó lên Wio Terminal của bạn và kiểm tra thông qua serial monitor. Đảm bảo ứng dụng functions của bạn đang chạy.

    Bạn sẽ thấy danh sách các giọng nói có sẵn được trả về từ ứng dụng functions, cùng với giọng nói đã chọn.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Chuyển đổi văn bản thành giọng nói

Khi bạn đã có một giọng nói để sử dụng, nó có thể được sử dụng để chuyển đổi văn bản thành giọng nói. Các hạn chế về bộ nhớ tương tự với các giọng nói cũng áp dụng khi chuyển đổi giọng nói thành văn bản, vì vậy bạn sẽ cần ghi giọng nói vào thẻ SD để phát qua ReSpeaker.

> 💁 Trong các bài học trước của dự án này, bạn đã sử dụng bộ nhớ flash để lưu trữ giọng nói được thu từ micro. Bài học này sử dụng thẻ SD vì nó dễ dàng hơn để phát âm thanh từ đó bằng cách sử dụng thư viện âm thanh Seeed.

Ngoài ra còn có một hạn chế khác cần xem xét, đó là dữ liệu âm thanh có sẵn từ dịch vụ giọng nói và các định dạng mà Wio Terminal hỗ trợ. Không giống như máy tính đầy đủ, các thư viện âm thanh cho vi điều khiển có thể rất hạn chế trong các định dạng âm thanh mà chúng hỗ trợ. Ví dụ, thư viện Seeed Arduino Audio có thể phát âm thanh qua ReSpeaker chỉ hỗ trợ âm thanh ở tần số mẫu 44.1KHz. Dịch vụ giọng nói Azure có thể cung cấp âm thanh ở một số định dạng, nhưng không định dạng nào sử dụng tần số mẫu này, chúng chỉ cung cấp 8KHz, 16KHz, 24KHz và 48KHz. Điều này có nghĩa là âm thanh cần được chuyển đổi lại thành 44.1KHz, điều mà sẽ cần nhiều tài nguyên hơn Wio Terminal có, đặc biệt là bộ nhớ.

Khi cần xử lý dữ liệu như thế này, thường tốt hơn là sử dụng mã serverless, đặc biệt nếu dữ liệu được lấy thông qua một cuộc gọi web. Wio Terminal có thể gọi một hàm serverless, truyền văn bản để chuyển đổi, và hàm serverless có thể vừa gọi dịch vụ giọng nói để chuyển đổi văn bản thành giọng nói, vừa chuyển đổi lại âm thanh thành tần số mẫu cần thiết. Sau đó, nó có thể trả về âm thanh dưới dạng mà Wio Terminal cần để lưu trữ trên thẻ SD và phát qua ReSpeaker.

### Nhiệm vụ - tạo một hàm serverless để chuyển đổi văn bản thành giọng nói

1. Mở dự án `smart-timer-trigger` của bạn trong VS Code, và mở terminal đảm bảo môi trường ảo đã được kích hoạt. Nếu không, hãy tắt và tạo lại terminal.

1. Thêm một HTTP trigger mới vào ứng dụng này có tên `text-to-speech` bằng lệnh sau từ bên trong terminal của VS Code trong thư mục gốc của dự án ứng dụng functions:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Điều này sẽ tạo một HTTP trigger có tên `text-to-speech`.

1. Gói Pip [librosa](https://librosa.org) có các hàm để chuyển đổi lại âm thanh, vì vậy hãy thêm nó vào tệp `requirements.txt`:

    ```sh
    librosa
    ```

    Sau khi đã thêm, cài đặt các gói Pip bằng lệnh sau từ terminal của VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Nếu bạn đang sử dụng Linux, bao gồm Raspberry Pi OS, bạn có thể cần cài đặt `libsndfile` bằng lệnh sau:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Để chuyển đổi văn bản thành giọng nói, bạn không thể sử dụng trực tiếp khóa API dịch vụ giọng nói, thay vào đó bạn cần yêu cầu một access token, sử dụng khóa API để xác thực yêu cầu access token. Mở tệp `__init__.py` từ thư mục `text-to-speech` và thay thế toàn bộ mã trong đó bằng nội dung sau:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Điều này định nghĩa các hằng số cho vị trí và khóa dịch vụ giọng nói sẽ được đọc từ các thiết lập. Sau đó, nó định nghĩa hàm `get_access_token` để lấy access token cho dịch vụ giọng nói.

1. Bên dưới đoạn mã này, thêm nội dung sau:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Điều này định nghĩa HTTP trigger chuyển đổi văn bản thành giọng nói. Nó trích xuất văn bản để chuyển đổi, ngôn ngữ và giọng nói từ nội dung JSON được gửi đến yêu cầu, xây dựng một số SSML để yêu cầu giọng nói, sau đó gọi REST API liên quan xác thực bằng access token. Cuộc gọi REST API này trả về âm thanh được mã hóa dưới dạng tệp WAV mono 16-bit, 48KHz, được định nghĩa bởi giá trị `playback_format`, được gửi đến cuộc gọi REST API.

    Sau đó, âm thanh này được chuyển đổi lại bởi `librosa` từ tần số mẫu 48KHz thành tần số mẫu 44.1KHz, sau đó âm thanh này được lưu vào một bộ đệm nhị phân và được trả về.

1. Chạy ứng dụng functions của bạn cục bộ, hoặc triển khai nó lên cloud. Sau đó, bạn có thể gọi nó bằng một công cụ như curl theo cách tương tự như bạn đã thử nghiệm HTTP trigger `text-to-timer`. Đảm bảo truyền ngôn ngữ, giọng nói và văn bản dưới dạng nội dung JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Thay thế `<language>` bằng ngôn ngữ của bạn, chẳng hạn như `en-GB`, hoặc `zh-CN`. Thay thế `<voice>` bằng giọng nói bạn muốn sử dụng. Thay thế `<text>` bằng văn bản bạn muốn chuyển đổi thành giọng nói. Bạn có thể lưu đầu ra vào một tệp và phát nó bằng bất kỳ trình phát âm thanh nào có thể phát tệp WAV.

    Ví dụ, để chuyển đổi "Hello" thành giọng nói sử dụng tiếng Anh Mỹ với giọng Jenny Neural, với ứng dụng functions chạy cục bộ, bạn có thể sử dụng lệnh curl sau:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Điều này sẽ lưu âm thanh vào `hello.wav` trong thư mục hiện tại.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Nhiệm vụ - lấy giọng nói từ Wio Terminal của bạn

1. Mở dự án `smart-timer` của bạn trong VS Code nếu nó chưa được mở.

1. Mở tệp tiêu đề `config.h` và thêm URL cho ứng dụng functions của bạn:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Thay thế `<URL>` bằng URL cho HTTP trigger `text-to-speech` trên ứng dụng functions của bạn. Điều này sẽ giống với giá trị của `TEXT_TO_TIMER_FUNCTION_URL`, ngoại trừ tên hàm là `text-to-speech` thay vì `text-to-timer`.

1. Mở tệp tiêu đề `text_to_speech.h`, và thêm phương thức sau vào phần `public` của lớp `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Trong phương thức `convertTextToSpeech`, thêm đoạn mã sau để tạo JSON gửi đến ứng dụng functions:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Điều này ghi ngôn ngữ, giọng nói và văn bản vào tài liệu JSON, sau đó tuần tự hóa nó thành một chuỗi.

1. Bên dưới đoạn mã này, thêm đoạn mã sau để gọi ứng dụng functions:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Điều này tạo một HTTPClient, sau đó thực hiện yêu cầu POST sử dụng tài liệu JSON đến HTTP trigger chuyển đổi văn bản thành giọng nói.

1. Nếu cuộc gọi thành công, dữ liệu nhị phân thô được trả về từ cuộc gọi ứng dụng functions có thể được truyền trực tiếp vào một tệp trên thẻ SD. Thêm đoạn mã sau để thực hiện điều này:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Đoạn mã này kiểm tra phản hồi, và nếu là 200 (thành công), dữ liệu nhị phân được truyền vào một tệp trong thư mục gốc của thẻ SD có tên `SPEECH.WAV`.

1. Ở cuối phương thức này, đóng kết nối HTTP:

    ```cpp
    httpClient.end();
    ```

1. Văn bản cần được nói bây giờ có thể được chuyển đổi thành âm thanh. Trong tệp `main.cpp`, thêm dòng sau vào cuối hàm `say` để chuyển đổi văn bản cần nói thành âm thanh:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Nhiệm vụ - phát âm thanh từ Wio Terminal của bạn

**Sắp ra mắt**

## Triển khai ứng dụng chức năng của bạn lên đám mây

Lý do để chạy ứng dụng chức năng cục bộ là vì gói Pip `librosa` trên Linux có một phụ thuộc vào một thư viện không được cài đặt mặc định, và cần phải được cài đặt trước khi ứng dụng chức năng có thể chạy. Ứng dụng chức năng là serverless - không có máy chủ nào bạn có thể tự quản lý, vì vậy không có cách nào để cài đặt thư viện này trước.

Cách để làm điều này là triển khai ứng dụng chức năng của bạn bằng cách sử dụng một Docker container. Container này sẽ được đám mây triển khai bất cứ khi nào cần khởi động một phiên bản mới của ứng dụng chức năng của bạn (chẳng hạn khi nhu cầu vượt quá tài nguyên sẵn có, hoặc nếu ứng dụng chức năng không được sử dụng trong một thời gian và bị đóng lại).

Bạn có thể tìm thấy hướng dẫn để thiết lập ứng dụng chức năng và triển khai qua Docker trong [tài liệu tạo chức năng trên Linux bằng hình ảnh tùy chỉnh trên Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Sau khi đã triển khai, bạn có thể chuyển mã Wio Terminal của mình để truy cập chức năng này:

1. Thêm chứng chỉ Azure Functions vào `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIFWjCCBEKgAwIBAgIQDxSWXyAgaZlP1ceseIlB4jANBgkqhkiG9w0BAQsFADBa\r\n"
        "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n"
        "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\r\n"
        "MDcyMTIzMDAwMFoXDTI0MTAwODA3MDAwMFowTzELMAkGA1UEBhMCVVMxHjAcBgNV\r\n"
        "BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEgMB4GA1UEAxMXTWljcm9zb2Z0IFJT\r\n"
        "QSBUTFMgQ0EgMDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCqYnfP\r\n"
        "mmOyBoTzkDb0mfMUUavqlQo7Rgb9EUEf/lsGWMk4bgj8T0RIzTqk970eouKVuL5R\r\n"
        "IMW/snBjXXgMQ8ApzWRJCZbar879BV8rKpHoAW4uGJssnNABf2n17j9TiFy6BWy+\r\n"
        "IhVnFILyLNK+W2M3zK9gheiWa2uACKhuvgCca5Vw/OQYErEdG7LBEzFnMzTmJcli\r\n"
        "W1iCdXby/vI/OxbfqkKD4zJtm45DJvC9Dh+hpzqvLMiK5uo/+aXSJY+SqhoIEpz+\r\n"
        "rErHw+uAlKuHFtEjSeeku8eR3+Z5ND9BSqc6JtLqb0bjOHPm5dSRrgt4nnil75bj\r\n"
        "c9j3lWXpBb9PXP9Sp/nPCK+nTQmZwHGjUnqlO9ebAVQD47ZisFonnDAmjrZNVqEX\r\n"
        "F3p7laEHrFMxttYuD81BdOzxAbL9Rb/8MeFGQjE2Qx65qgVfhH+RsYuuD9dUw/3w\r\n"
        "ZAhq05yO6nk07AM9c+AbNtRoEcdZcLCHfMDcbkXKNs5DJncCqXAN6LhXVERCw/us\r\n"
        "G2MmCMLSIx9/kwt8bwhUmitOXc6fpT7SmFvRAtvxg84wUkg4Y/Gx++0j0z6StSeN\r\n"
        "0EJz150jaHG6WV4HUqaWTb98Tm90IgXAU4AW2GBOlzFPiU5IY9jt+eXC2Q6yC/Zp\r\n"
        "TL1LAcnL3Qa/OgLrHN0wiw1KFGD51WRPQ0Sh7QIDAQABo4IBJTCCASEwHQYDVR0O\r\n"
        "BBYEFLV2DDARzseSQk1Mx1wsyKkM6AtkMB8GA1UdIwQYMBaAFOWdWTCCR1jMrPoI\r\n"
        "VDaGezq1BE3wMA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYI\r\n"
        "KwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADA0BggrBgEFBQcBAQQoMCYwJAYI\r\n"
        "KwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTA6BgNVHR8EMzAxMC+g\r\n"
        "LaArhilodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vT21uaXJvb3QyMDI1LmNybDAq\r\n"
        "BgNVHSAEIzAhMAgGBmeBDAECATAIBgZngQwBAgIwCwYJKwYBBAGCNyoBMA0GCSqG\r\n"
        "SIb3DQEBCwUAA4IBAQCfK76SZ1vae4qt6P+dTQUO7bYNFUHR5hXcA2D59CJWnEj5\r\n"
        "na7aKzyowKvQupW4yMH9fGNxtsh6iJswRqOOfZYC4/giBO/gNsBvwr8uDW7t1nYo\r\n"
        "DYGHPpvnpxCM2mYfQFHq576/TmeYu1RZY29C4w8xYBlkAA8mDJfRhMCmehk7cN5F\r\n"
        "JtyWRj2cZj/hOoI45TYDBChXpOlLZKIYiG1giY16vhCRi6zmPzEwv+tk156N6cGS\r\n"
        "Vm44jTQ/rs1sa0JSYjzUaYngoFdZC4OfxnIkQvUIA4TOFmPzNPEFdjcZsgbeEz4T\r\n"
        "cGHTBPK4R28F44qIMCtHRV55VMX53ev6P3hRddJb\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Thay đổi tất cả các lần bao gồm `
<WiFiClient.h>` thành `<WiFiClientSecure.h>`.

1. Thay đổi tất cả các trường `WiFiClient` thành `WiFiClientSecure`.

1. Trong mỗi lớp có trường `WiFiClientSecure`, thêm một constructor và đặt chứng chỉ trong constructor đó:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.