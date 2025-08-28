<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-28T01:58:16+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "vi"
}
-->
# Xây dựng chu kỳ tưới nước hiệu quả hơn

## Hướng dẫn

Bài học này đã hướng dẫn cách điều khiển relay thông qua dữ liệu cảm biến, và relay đó có thể điều khiển bơm cho hệ thống tưới tiêu. Đối với một khối đất nhất định, việc chạy bơm trong một khoảng thời gian cố định sẽ luôn có tác động giống nhau đến độ ẩm của đất. Điều này có nghĩa là bạn có thể ước tính số giây tưới nước tương ứng với một mức giảm nhất định trong chỉ số độ ẩm của đất. Sử dụng dữ liệu này, bạn có thể xây dựng một hệ thống tưới tiêu được kiểm soát tốt hơn.

Trong bài tập này, bạn sẽ tính toán thời gian bơm cần chạy để đạt được mức tăng độ ẩm đất cụ thể.

> ⚠️ Nếu bạn đang sử dụng phần cứng IoT ảo, bạn có thể thực hiện quy trình này, nhưng hãy mô phỏng kết quả bằng cách tăng chỉ số độ ẩm đất một cách thủ công theo một lượng cố định mỗi giây khi relay bật.

1. Bắt đầu với đất khô. Đo độ ẩm của đất.

1. Thêm một lượng nước cố định, bằng cách chạy bơm trong 1 giây hoặc đổ một lượng cố định vào.

    > Bơm luôn phải chạy ở tốc độ cố định, vì vậy mỗi giây bơm chạy sẽ cung cấp cùng một lượng nước.

1. Chờ cho đến khi mức độ ẩm đất ổn định và ghi lại chỉ số.

1. Lặp lại quy trình này nhiều lần và tạo một bảng kết quả. Một ví dụ về bảng này được đưa ra dưới đây.

    | Tổng thời gian bơm | Độ ẩm đất | Mức giảm |
    | --- | --: | -: |
    | Khô | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Tính mức tăng trung bình độ ẩm đất mỗi giây nước. Trong ví dụ trên, mỗi giây nước làm giảm chỉ số trung bình là 20.3.

1. Sử dụng dữ liệu này để cải thiện hiệu quả mã máy chủ của bạn, chạy bơm trong thời gian cần thiết để đạt được mức độ ẩm đất mong muốn.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Ghi lại dữ liệu độ ẩm đất | Có thể ghi lại nhiều chỉ số sau khi thêm lượng nước cố định | Có thể ghi lại một số chỉ số với lượng nước cố định | Chỉ có thể ghi lại một hoặc hai chỉ số, hoặc không thể sử dụng lượng nước cố định |
| Hiệu chỉnh mã máy chủ | Có thể tính toán mức giảm trung bình trong chỉ số độ ẩm đất và cập nhật mã máy chủ để sử dụng giá trị này | Có thể tính toán mức giảm trung bình, nhưng không thể cập nhật mã máy chủ, hoặc không thể tính toán chính xác mức giảm trung bình nhưng sử dụng giá trị này để cập nhật mã máy chủ đúng cách | Không thể tính toán mức giảm trung bình hoặc cập nhật mã máy chủ |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.