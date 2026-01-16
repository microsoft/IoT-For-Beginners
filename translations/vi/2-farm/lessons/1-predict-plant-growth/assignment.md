<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T21:26:44+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "vi"
}
-->
# Hình dung dữ liệu GDD bằng Jupyter Notebook

## Hướng dẫn

Trong bài học này, bạn đã thu thập dữ liệu GDD bằng cảm biến IoT. Để có dữ liệu GDD tốt, bạn cần thu thập dữ liệu trong nhiều ngày. Để hỗ trợ hình dung dữ liệu nhiệt độ và tính toán GDD, bạn có thể sử dụng các công cụ như [Jupyter Notebooks](https://jupyter.org) để phân tích dữ liệu.

Bắt đầu bằng cách thu thập dữ liệu trong vài ngày. Bạn cần đảm bảo mã máy chủ của mình chạy liên tục trong thời gian thiết bị IoT hoạt động, bằng cách điều chỉnh cài đặt quản lý năng lượng hoặc chạy một thứ gì đó như [script Python giữ hệ thống hoạt động này](https://github.com/jaqsparow/keep-system-active).

Khi đã có dữ liệu nhiệt độ, bạn có thể sử dụng Jupyter Notebook trong kho lưu trữ này để hình dung và tính toán GDD. Jupyter notebooks kết hợp mã và hướng dẫn trong các khối gọi là *cells*, thường là mã Python. Bạn có thể đọc hướng dẫn, sau đó chạy từng khối mã, từng khối một. Bạn cũng có thể chỉnh sửa mã. Trong notebook này chẳng hạn, bạn có thể chỉnh sửa nhiệt độ cơ sở được sử dụng để tính toán GDD cho cây trồng của mình.

1. Tạo một thư mục có tên `gdd-calculation`

1. Tải xuống tệp [gdd.ipynb](./code-notebook/gdd.ipynb) và sao chép nó vào thư mục `gdd-calculation`.

1. Sao chép tệp `temperature.csv` được tạo bởi máy chủ MQTT

1. Tạo một môi trường ảo Python mới trong thư mục `gdd-calculation`.

1. Cài đặt một số gói pip cho Jupyter notebooks, cùng với các thư viện cần thiết để quản lý và vẽ dữ liệu:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Chạy notebook trong Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter sẽ khởi động và mở notebook trong trình duyệt của bạn. Làm theo các hướng dẫn trong notebook để hình dung nhiệt độ đã đo và tính toán số ngày độ tăng trưởng.

    ![Jupyter notebook](../../../../../translated_images/vi/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Thu thập dữ liệu | Thu thập ít nhất 2 ngày dữ liệu đầy đủ | Thu thập ít nhất 1 ngày dữ liệu đầy đủ | Thu thập một số dữ liệu |
| Tính toán GDD | Chạy thành công notebook và tính toán GDD | Chạy thành công notebook | Không thể chạy notebook |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.