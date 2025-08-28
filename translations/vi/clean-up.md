<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T22:34:50+00:00",
  "source_file": "clean-up.md",
  "language_code": "vi"
}
-->
# Dọn dẹp dự án của bạn

Sau khi hoàn thành mỗi dự án, việc xóa các tài nguyên đám mây là một thói quen tốt.

Trong các bài học của từng dự án, bạn có thể đã tạo một số tài nguyên sau:

* Một Nhóm Tài Nguyên (Resource Group)  
* Một IoT Hub  
* Đăng ký thiết bị IoT  
* Một Tài khoản Lưu trữ (Storage Account)  
* Một Ứng dụng Functions (Functions App)  
* Một tài khoản Azure Maps  
* Một dự án custom vision  
* Một Azure Container Registry  
* Một tài nguyên dịch vụ trí tuệ nhân tạo (cognitive services resource)  

Hầu hết các tài nguyên này sẽ không tốn phí - hoặc chúng hoàn toàn miễn phí, hoặc bạn đang sử dụng ở mức miễn phí. Đối với các dịch vụ yêu cầu gói trả phí, bạn có thể đã sử dụng chúng ở mức nằm trong giới hạn miễn phí, hoặc chỉ tốn vài xu.

Ngay cả với chi phí tương đối thấp, việc xóa các tài nguyên này khi bạn hoàn thành vẫn rất đáng làm. Ví dụ, bạn chỉ có thể có một IoT Hub sử dụng gói miễn phí, vì vậy nếu bạn muốn tạo thêm một cái khác, bạn sẽ cần sử dụng gói trả phí.

Tất cả các dịch vụ của bạn đã được tạo bên trong các Nhóm Tài Nguyên, điều này giúp việc quản lý dễ dàng hơn. Bạn có thể xóa Nhóm Tài Nguyên, và tất cả các dịch vụ trong Nhóm Tài Nguyên đó sẽ bị xóa cùng với nó.

Để xóa Nhóm Tài Nguyên, chạy lệnh sau trong terminal hoặc command prompt của bạn:

```sh
az group delete --name <resource-group-name>
```

Thay thế `<resource-group-name>` bằng tên của Nhóm Tài Nguyên mà bạn muốn xóa.

Một thông báo xác nhận sẽ xuất hiện:

```output
Are you sure you want to perform this operation? (y/n): 
```

Nhập `y` để xác nhận và xóa Nhóm Tài Nguyên.

Việc xóa tất cả các dịch vụ sẽ mất một khoảng thời gian.

> 💁 Bạn có thể đọc thêm về cách xóa nhóm tài nguyên trong [tài liệu xóa nhóm tài nguyên và tài nguyên Azure Resource Manager trên Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.