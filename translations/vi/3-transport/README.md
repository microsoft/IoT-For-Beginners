<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-27T23:45:02+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "vi"
}
-->
# Vận chuyển từ nông trại đến nhà máy - sử dụng IoT để theo dõi giao hàng thực phẩm

Nhiều nông dân trồng thực phẩm để bán - hoặc họ là nông dân thương mại bán toàn bộ sản phẩm họ trồng, hoặc họ là nông dân tự cung tự cấp bán phần dư thừa để mua các nhu yếu phẩm. Bằng cách nào đó, thực phẩm phải được vận chuyển từ nông trại đến người tiêu dùng, và điều này thường dựa vào vận chuyển hàng loạt từ nông trại, đến các trung tâm hoặc nhà máy chế biến, sau đó đến các cửa hàng. Ví dụ, một nông dân trồng cà chua sẽ thu hoạch cà chua, đóng gói chúng vào các thùng, chất các thùng lên xe tải rồi giao đến nhà máy chế biến. Cà chua sau đó sẽ được phân loại, và từ đó được giao đến người tiêu dùng dưới dạng thực phẩm chế biến, bán lẻ, hoặc được tiêu thụ tại các nhà hàng.

IoT có thể hỗ trợ chuỗi cung ứng này bằng cách theo dõi thực phẩm trong quá trình vận chuyển - đảm bảo tài xế đi đúng lộ trình, giám sát vị trí của phương tiện, và nhận thông báo khi phương tiện đến nơi để thực phẩm có thể được dỡ xuống và sẵn sàng cho quá trình chế biến sớm nhất có thể.

> 🎓 *Chuỗi cung ứng* là chuỗi các hoạt động để tạo ra và giao một sản phẩm. Ví dụ, trong việc trồng cà chua, chuỗi này bao gồm hạt giống, đất, phân bón và nguồn nước, trồng cà chua, giao cà chua đến trung tâm tập kết, vận chuyển chúng đến trung tâm địa phương của siêu thị, vận chuyển đến từng siêu thị, bày bán trên kệ, sau đó được bán cho người tiêu dùng và mang về nhà để ăn. Mỗi bước giống như một mắt xích trong chuỗi.

> 🎓 Phần vận chuyển trong chuỗi cung ứng được gọi là *logistics*.

Trong 4 bài học này, bạn sẽ học cách áp dụng Internet of Things để cải thiện chuỗi cung ứng bằng cách giám sát thực phẩm khi chúng được chất lên một chiếc xe tải (ảo), được theo dõi khi di chuyển đến điểm đến. Bạn sẽ học về theo dõi GPS, cách lưu trữ và trực quan hóa dữ liệu GPS, và cách nhận thông báo khi xe tải đến nơi.

> 💁 Những bài học này sẽ sử dụng một số tài nguyên đám mây. Nếu bạn không hoàn thành tất cả các bài học trong dự án này, hãy đảm bảo bạn [Dọn dẹp dự án của mình](../clean-up.md).

## Các chủ đề

1. [Theo dõi vị trí](lessons/1-location-tracking/README.md)
1. [Lưu trữ dữ liệu vị trí](lessons/2-store-location-data/README.md)
1. [Trực quan hóa dữ liệu vị trí](lessons/3-visualize-location-data/README.md)
1. [Hàng rào địa lý](lessons/4-geofences/README.md)

## Ghi nhận

Tất cả các bài học được viết với ♥️ bởi [Jen Looper](https://github.com/jlooper) và [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.