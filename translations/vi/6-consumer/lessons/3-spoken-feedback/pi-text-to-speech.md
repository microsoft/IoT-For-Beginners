<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T23:18:57+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "vi"
}
-->
# Chuyển đổi văn bản thành giọng nói - Raspberry Pi

Trong phần này của bài học, bạn sẽ viết mã để chuyển đổi văn bản thành giọng nói bằng dịch vụ giọng nói.

## Chuyển đổi văn bản thành giọng nói bằng dịch vụ giọng nói

Văn bản có thể được gửi đến dịch vụ giọng nói thông qua REST API để nhận giọng nói dưới dạng tệp âm thanh có thể phát lại trên thiết bị IoT của bạn. Khi yêu cầu giọng nói, bạn cần cung cấp giọng nói để sử dụng, vì giọng nói có thể được tạo bằng nhiều giọng khác nhau.

Mỗi ngôn ngữ hỗ trợ một loạt các giọng nói khác nhau, và bạn có thể thực hiện yêu cầu REST đối với dịch vụ giọng nói để lấy danh sách các giọng nói được hỗ trợ cho từng ngôn ngữ.

### Nhiệm vụ - lấy giọng nói

1. Mở dự án `smart-timer` trong VS Code.

1. Thêm đoạn mã sau vào phía trên hàm `say` để yêu cầu danh sách các giọng nói cho một ngôn ngữ:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Đoạn mã này định nghĩa một hàm gọi là `get_voice` sử dụng dịch vụ giọng nói để lấy danh sách các giọng nói. Sau đó, nó tìm giọng nói đầu tiên phù hợp với ngôn ngữ đang được sử dụng.

    Hàm này sau đó được gọi để lưu trữ giọng nói đầu tiên, và tên giọng nói được in ra console. Giọng nói này có thể được yêu cầu một lần và giá trị được sử dụng cho mọi lần gọi để chuyển đổi văn bản thành giọng nói.

    > 💁 Bạn có thể lấy danh sách đầy đủ các giọng nói được hỗ trợ từ [Tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Nếu bạn muốn sử dụng một giọng nói cụ thể, bạn có thể xóa hàm này và mã hóa cứng giọng nói thành tên giọng nói từ tài liệu này. Ví dụ:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Nhiệm vụ - chuyển đổi văn bản thành giọng nói

1. Bên dưới đoạn mã này, định nghĩa một hằng số cho định dạng âm thanh sẽ được lấy từ dịch vụ giọng nói. Khi bạn yêu cầu âm thanh, bạn có thể làm điều này với một loạt các định dạng khác nhau.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Định dạng bạn có thể sử dụng phụ thuộc vào phần cứng của bạn. Nếu bạn gặp lỗi `Invalid sample rate` khi phát âm thanh, hãy thay đổi giá trị này sang một giá trị khác. Bạn có thể tìm danh sách các giá trị được hỗ trợ trong [Tài liệu REST API chuyển đổi văn bản thành giọng nói trên Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Bạn sẽ cần sử dụng âm thanh định dạng `riff`, và các giá trị cần thử là `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` và `riff-48khz-16bit-mono-pcm`.

1. Bên dưới đoạn mã này, khai báo một hàm gọi là `get_speech` để chuyển đổi văn bản thành giọng nói bằng REST API của dịch vụ giọng nói:

    ```python
    def get_speech(text):
    ```

1. Trong hàm `get_speech`, định nghĩa URL để gọi và các headers cần truyền:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Đoạn mã này thiết lập headers để sử dụng token truy cập được tạo, đặt nội dung thành SSML và định nghĩa định dạng âm thanh cần thiết.

1. Bên dưới đoạn mã này, định nghĩa SSML để gửi đến REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    SSML này thiết lập ngôn ngữ và giọng nói để sử dụng, cùng với văn bản cần chuyển đổi.

1. Cuối cùng, thêm mã trong hàm này để thực hiện yêu cầu REST và trả về dữ liệu âm thanh dạng nhị phân:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Nhiệm vụ - phát âm thanh

1. Bên dưới hàm `get_speech`, định nghĩa một hàm mới để phát âm thanh được trả về từ cuộc gọi REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech` được truyền vào hàm này sẽ là dữ liệu âm thanh dạng nhị phân được trả về từ REST API. Sử dụng đoạn mã sau để mở dữ liệu này dưới dạng tệp wave và truyền nó đến PyAudio để phát âm thanh:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Đoạn mã này sử dụng một luồng PyAudio, giống như khi thu âm thanh. Điểm khác biệt ở đây là luồng được thiết lập thành luồng đầu ra, và dữ liệu được đọc từ dữ liệu âm thanh và đẩy vào luồng.

    Thay vì mã hóa cứng các chi tiết luồng như tốc độ mẫu, nó được đọc từ dữ liệu âm thanh.

1. Thay thế nội dung của hàm `say` bằng đoạn mã sau:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Đoạn mã này chuyển đổi văn bản thành giọng nói dưới dạng dữ liệu âm thanh nhị phân, và phát âm thanh.

1. Chạy ứng dụng, và đảm bảo ứng dụng chức năng cũng đang chạy. Đặt một số bộ hẹn giờ, và bạn sẽ nghe thấy phản hồi bằng giọng nói thông báo rằng bộ hẹn giờ của bạn đã được đặt, sau đó là một phản hồi bằng giọng nói khác khi bộ hẹn giờ hoàn tất.

    Nếu bạn gặp lỗi `Invalid sample rate`, hãy thay đổi `playback_format` như đã mô tả ở trên.

> 💁 Bạn có thể tìm đoạn mã này trong thư mục [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Chương trình hẹn giờ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.