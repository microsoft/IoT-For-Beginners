<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-28T01:41:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "vi"
}
-->
    This code extracts the temperature from the telemetry message, gets the current date and time, and writes these values as a new row in the CSV file.

1. Run the server code and verify that it creates a CSV file and writes temperature data to it when telemetry messages are received.

✅ Why might saving data to a CSV file be useful for farmers?

## Summary

In this lesson, you learned how temperature affects plant growth and how to calculate Growing Degree Days (GDD) using temperature data. You explored how IoT devices can measure temperature and publish telemetry data, and how server code can capture and store this data for analysis. By using GDD calculations, farmers can predict plant maturity more accurately, optimizing their harvest and reducing labor costs.

## 🚀 Challenge

Modify the server code to calculate the GDD for a specific crop each day and save this value to the CSV file alongside the temperature data. Use the base temperature for the crop in your calculations.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Review & Self-study

Research other factors that influence plant growth, such as soil quality, humidity, or light levels. How could IoT devices be used to measure and optimize these factors?

## Assignment

Create a system using IoT devices and server code to monitor temperature and calculate GDD for a crop of your choice. Use the data to predict when the crop will reach maturity.
Tệp mã này mở tệp CSV, sau đó thêm một hàng mới vào cuối. Hàng này chứa dữ liệu và thời gian hiện tại được định dạng thành dạng dễ đọc, tiếp theo là nhiệt độ nhận được từ thiết bị IoT. Dữ liệu được lưu trữ theo [định dạng ISO 8601](https://wikipedia.org/wiki/ISO_8601) với múi giờ, nhưng không bao gồm microseconds.

1. Chạy mã này giống như trước, đảm bảo rằng thiết bị IoT của bạn đang gửi dữ liệu. Một tệp CSV có tên `temperature.csv` sẽ được tạo trong cùng thư mục. Nếu bạn mở nó, bạn sẽ thấy ngày/giờ và các giá trị đo nhiệt độ:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Chạy mã này trong một khoảng thời gian để thu thập dữ liệu. Lý tưởng nhất là bạn nên chạy nó trong cả ngày để thu thập đủ dữ liệu cho việc tính toán GDD.

    
> 💁 Nếu bạn đang sử dụng Thiết bị IoT ảo, hãy chọn hộp kiểm ngẫu nhiên và đặt một phạm vi để tránh nhận cùng một giá trị nhiệt độ mỗi lần nhiệt độ được trả về.
    ![Chọn hộp kiểm ngẫu nhiên và đặt một phạm vi](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f8c76616b10c7c23a6592321bb1a6310e0b481e72f97d23b3.vi.png) 

    > 💁 Nếu bạn muốn chạy mã này trong cả ngày, thì bạn cần đảm bảo rằng máy tính nơi mã máy chủ của bạn đang chạy sẽ không chuyển sang chế độ ngủ, bằng cách thay đổi cài đặt nguồn hoặc chạy một thứ gì đó như [script Python giữ hệ thống hoạt động này](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Nhiệm vụ - tính toán GDD bằng dữ liệu đã lưu

Khi máy chủ đã thu thập dữ liệu nhiệt độ, GDD cho một loại cây trồng có thể được tính toán.

Các bước để thực hiện điều này thủ công là:

1. Tìm nhiệt độ cơ bản cho cây trồng. Ví dụ, đối với dâu tây, nhiệt độ cơ bản là 10°C.

1. Từ tệp `temperature.csv`, tìm nhiệt độ cao nhất và thấp nhất trong ngày.

1. Sử dụng công thức tính GDD đã được cung cấp trước đó để tính toán GDD.

Ví dụ, nếu nhiệt độ cao nhất trong ngày là 25°C, và thấp nhất là 12°C:

![GDD = 25 + 12 chia cho 2, sau đó trừ đi 10 từ kết quả, cho ra 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.vi.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Do đó, dâu tây đã nhận được **8.5** GDD. Dâu tây cần khoảng 250 GDD để ra quả, vì vậy vẫn còn một thời gian nữa.

---

## 🚀 Thử thách

Cây trồng cần nhiều yếu tố hơn nhiệt độ để phát triển. Những yếu tố nào khác cần thiết?

Đối với những yếu tố này, hãy tìm xem có cảm biến nào có thể đo lường chúng không. Còn các bộ điều khiển để kiểm soát các mức độ này thì sao? Làm thế nào bạn có thể kết hợp một hoặc nhiều thiết bị IoT để tối ưu hóa sự phát triển của cây trồng?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Ôn tập & Tự học

* Đọc thêm về nông nghiệp số trên [trang Wikipedia về Nông nghiệp số](https://wikipedia.org/wiki/Digital_agriculture). Cũng đọc thêm về nông nghiệp chính xác trên [trang Wikipedia về Nông nghiệp chính xác](https://wikipedia.org/wiki/Precision_agriculture).
* Công thức tính ngày độ tăng trưởng đầy đủ phức tạp hơn công thức đơn giản được cung cấp ở đây. Đọc thêm về công thức phức tạp hơn và cách xử lý nhiệt độ dưới mức cơ bản trên [trang Wikipedia về Ngày độ tăng trưởng](https://wikipedia.org/wiki/Growing_degree-day).
* Thực phẩm có thể trở nên khan hiếm trong tương lai nếu chúng ta vẫn sử dụng các phương pháp canh tác hiện tại. Tìm hiểu thêm về các kỹ thuật canh tác công nghệ cao trong [video Nông trại Công nghệ Cao của Tương lai trên YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Bài tập

[Trực quan hóa dữ liệu GDD bằng Jupyter Notebook](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.