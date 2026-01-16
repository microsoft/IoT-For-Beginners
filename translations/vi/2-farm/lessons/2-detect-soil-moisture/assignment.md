<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T21:54:19+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "vi"
}
-->
# Hiệu chỉnh cảm biến của bạn

## Hướng dẫn

Trong bài học này, bạn đã thu thập các giá trị đo từ cảm biến độ ẩm đất, được đo trong khoảng từ 0-1023. Để chuyển đổi những giá trị này thành các chỉ số độ ẩm đất thực tế, bạn cần hiệu chỉnh cảm biến của mình. Bạn có thể làm điều này bằng cách lấy các giá trị đo từ các mẫu đất, sau đó tính toán độ ẩm đất theo trọng lượng từ các mẫu này.

Bạn sẽ cần lặp lại các bước này nhiều lần để thu thập đủ dữ liệu, với độ ẩm đất khác nhau mỗi lần.

1. Lấy một giá trị đo độ ẩm đất bằng cảm biến độ ẩm đất. Ghi lại giá trị này.

1. Lấy một mẫu đất và cân nó. Ghi lại trọng lượng này.

1. Làm khô đất - một lò nướng ấm ở 110°C (230°F) trong vài giờ là cách tốt nhất, bạn cũng có thể làm điều này dưới ánh nắng mặt trời, hoặc đặt nó ở một nơi ấm áp, khô ráo cho đến khi đất hoàn toàn khô. Đất nên trở nên bột và tơi xốp.

    > 💁 Trong phòng thí nghiệm, để có kết quả chính xác nhất, bạn nên làm khô trong lò nướng từ 48-72 giờ. Nếu trường học của bạn có lò sấy, hãy xem liệu bạn có thể sử dụng chúng để làm khô lâu hơn không. Thời gian làm khô càng lâu, mẫu đất càng khô và kết quả càng chính xác.

1. Cân lại đất.

    > 🔥 Nếu bạn làm khô đất trong lò nướng, hãy đảm bảo rằng nó đã nguội trước khi cân!

Độ ẩm đất theo trọng lượng được tính như sau:

![độ ẩm đất % là trọng lượng đất ướt trừ trọng lượng đất khô, chia cho trọng lượng đất khô, nhân với 100](../../../../../translated_images/vi/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - trọng lượng của đất ướt  
* W - trọng lượng của đất khô  

Ví dụ, giả sử bạn có một mẫu đất nặng 212g khi ướt và 197g khi khô.

![Phép tính đã được điền](../../../../../translated_images/vi/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6%  

Trong ví dụ này, đất có độ ẩm theo trọng lượng là 7.6%.

Khi bạn đã có các giá trị đo cho ít nhất 3 mẫu, hãy vẽ một đồ thị biểu diễn % độ ẩm đất so với giá trị đo từ cảm biến độ ẩm đất và thêm một đường phù hợp nhất với các điểm. Sau đó, bạn có thể sử dụng đồ thị này để tính toán độ ẩm đất theo trọng lượng cho một giá trị đo từ cảm biến bằng cách đọc giá trị từ đường biểu diễn.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Thu thập dữ liệu hiệu chỉnh | Thu thập ít nhất 3 mẫu hiệu chỉnh | Thu thập ít nhất 2 mẫu hiệu chỉnh | Thu thập ít nhất 1 mẫu hiệu chỉnh |
| Thực hiện giá trị đo đã hiệu chỉnh | Thành công vẽ đồ thị hiệu chỉnh và thực hiện giá trị đo từ cảm biến, sau đó chuyển đổi nó thành độ ẩm đất theo trọng lượng | Thành công vẽ đồ thị hiệu chỉnh | Không thể vẽ đồ thị |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.