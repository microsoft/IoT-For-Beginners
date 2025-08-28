<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T23:17:21+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "vi"
}
-->
# Chuyển văn bản thành giọng nói - Thiết bị IoT ảo

Trong phần này của bài học, bạn sẽ viết mã để chuyển đổi văn bản thành giọng nói bằng dịch vụ giọng nói.

## Chuyển đổi văn bản thành giọng nói

SDK dịch vụ giọng nói mà bạn đã sử dụng trong bài học trước để chuyển đổi giọng nói thành văn bản cũng có thể được sử dụng để chuyển đổi văn bản trở lại thành giọng nói. Khi yêu cầu giọng nói, bạn cần cung cấp giọng nói sẽ sử dụng vì giọng nói có thể được tạo ra bằng nhiều giọng khác nhau.

Mỗi ngôn ngữ hỗ trợ một loạt các giọng nói khác nhau, và bạn có thể lấy danh sách các giọng nói được hỗ trợ cho từng ngôn ngữ từ SDK dịch vụ giọng nói.

### Nhiệm vụ - chuyển đổi văn bản thành giọng nói

1. Mở dự án `smart-timer` trong VS Code, và đảm bảo môi trường ảo đã được tải trong terminal.

1. Nhập `SpeechSynthesizer` từ gói `azure.cognitiveservices.speech` bằng cách thêm nó vào các import hiện có:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Phía trên hàm `say`, tạo một cấu hình giọng nói để sử dụng với speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Điều này sử dụng cùng API key, vị trí và ngôn ngữ đã được sử dụng bởi recognizer.

1. Bên dưới đoạn này, thêm mã sau để lấy một giọng nói và thiết lập nó trên cấu hình giọng nói:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Đoạn mã này lấy danh sách tất cả các giọng nói có sẵn, sau đó tìm giọng nói đầu tiên khớp với ngôn ngữ đang được sử dụng.

    > 💁 Bạn có thể lấy danh sách đầy đủ các giọng nói được hỗ trợ từ [Tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Nếu bạn muốn sử dụng một giọng nói cụ thể, bạn có thể bỏ qua hàm này và gán cứng giọng nói bằng tên giọng nói từ tài liệu này. Ví dụ:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Cập nhật nội dung của hàm `say` để tạo SSML cho phản hồi:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Bên dưới đoạn này, dừng nhận diện giọng nói, phát SSML, sau đó khởi động lại nhận diện:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Việc nhận diện được dừng lại trong khi văn bản được phát để tránh việc thông báo bắt đầu hẹn giờ bị nhận diện, gửi đến LUIS và có thể bị hiểu nhầm là một yêu cầu đặt hẹn giờ mới.

    > 💁 Bạn có thể thử nghiệm điều này bằng cách bình luận các dòng mã để dừng và khởi động lại nhận diện. Đặt một hẹn giờ, và bạn có thể thấy thông báo đặt một hẹn giờ mới, điều này dẫn đến một thông báo mới, tạo ra một hẹn giờ mới, và cứ thế tiếp diễn mãi mãi!

1. Chạy ứng dụng, và đảm bảo ứng dụng chức năng cũng đang chạy. Đặt một số hẹn giờ, và bạn sẽ nghe thấy một phản hồi bằng giọng nói thông báo rằng hẹn giờ của bạn đã được đặt, sau đó là một phản hồi bằng giọng nói khác khi hẹn giờ hoàn tất.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Chương trình hẹn giờ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.