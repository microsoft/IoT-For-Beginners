<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T10:07:15+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "vi"
}
-->
# Hướng Dẫn Khắc Phục Sự Cố

Hướng dẫn này giúp bạn giải quyết các vấn đề phổ biến khi làm việc với chương trình học IoT cho Người Mới Bắt Đầu. Các sự cố được tổ chức theo danh mục để dễ dàng điều hướng.

## Mục Lục

- [Các Vấn Đề Cài Đặt](../..)
  - [Cài Đặt Python](../..)
  - [VS Code và Các Tiện Ích Mở Rộng](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Thư Viện Grove](../..)
- [Các Vấn Đề Phần Cứng](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Thiết Bị Ảo (CounterFit)](../..)
- [Các Vấn Đề Kết Nối](../..)
  - [Kết Nối WiFi](../..)
  - [Dịch Vụ Đám Mây](../..)
  - [MQTT](../..)
- [Các Vấn Đề Cảm Biến và Bộ Chấp Hành](../..)
  - [Cảm Biến Grove](../..)
  - [Máy Ảnh](../..)
  - [Micro và Loa](../..)
- [Các Vấn Đề Môi Trường Phát Triển](../..)
  - [VS Code](../..)
  - [Môi Trường Ảo Python](../..)
  - [Phụ Thuộc](../..)
- [Các Vấn Đề Hiệu Suất](../..)
- [Các Thông Báo Lỗi Thường Gặp](../..)
- [Nhận Trợ Giúp](../..)

---

## Các Vấn Đề Cài Đặt

### Cài Đặt Python

#### Vấn đề: Phiên bản Python quá cũ
**Lỗi:** `Cần Python 3.6 trở lên`

**Giải pháp:**
1. Tải Python 3 mới nhất từ [python.org](https://www.python.org/downloads/)
2. Khi cài đặt trên Windows, chọn "Add Python to PATH"
3. Xác minh cài đặt:
   ```bash
   python3 --version
   ```

#### Vấn đề: Nhiều phiên bản Python gây xung đột
**Triệu chứng:** Chạy sai phiên bản Python, các gói cài đặt sai vị trí

**Giải pháp:**
- **Windows:** Dùng `py -3` thay vì `python` để gọi Python 3 một cách rõ ràng
- **macOS/Linux:** Dùng `python3` thay vì `python`
- Luôn tạo và sử dụng môi trường ảo cho các dự án

#### Vấn đề: Không tìm thấy lệnh pip
**Lỗi:** `'pip' không được nhận dạng là lệnh nội bộ hoặc bên ngoài`

**Giải pháp:**
1. Thử dùng `pip3` thay vì `pip`
2. Hoặc dùng `python -m pip` hoặc `python3 -m pip`
3. Đảm bảo Python đã được thêm vào PATH (cài lại Python và chọn tùy chọn này)

### VS Code và Các Tiện Ích Mở Rộng

#### Vấn đề: Tiện ích Pylance không hoạt động
**Triệu chứng:** Không có IntelliSense Python, hoàn thành mã hoặc kiểm tra kiểu

**Giải pháp:**
1. Mở Command Palette VS Code (`Ctrl+Shift+P` hoặc `Cmd+Shift+P`)
2. Chạy "Python: Select Interpreter"
3. Chọn thông dịch Python đúng (môi trường ảo nếu dùng)
4. Tải lại cửa sổ VS Code

#### Vấn đề: VS Code không nhận diện môi trường ảo
**Triệu chứng:** Chọn sai thông dịch Python

**Giải pháp:**
1. Đảm bảo bạn đã kích hoạt môi trường ảo trong terminal
2. Mở Command Palette và chạy "Python: Select Interpreter"
3. Chọn thông dịch từ thư mục `.venv`
4. Kiểm tra thanh trạng thái (góc dưới bên trái) hiển thị phiên bản Python đúng

### PlatformIO (Wio Terminal)

#### Vấn đề: Cài đặt PlatformIO thất bại
**Lỗi:** Lỗi khác nhau trong quá trình cài PlatformIO

**Giải pháp:**
1. Đảm bảo VS Code được cập nhật
2. Cài tiện ích C/C++ trước
3. Khởi động lại VS Code sau khi cài PlatformIO
4. Kiểm tra kết nối Internet (PlatformIO tải các file lớn)

#### Vấn đề: Board không được PlatformIO nhận dạng
**Triệu chứng:** Không thể tải mã lên Wio Terminal

**Giải pháp:**
1. Thử cáp USB khác (một số cáp chỉ sạc)
2. Kiểm tra Device Manager (Windows) hoặc `ls /dev/tty*` (macOS/Linux)
3. Cài hoặc cập nhật driver USB
4. Thử cổng USB khác
5. Trượt công tắc nguồn trên Wio Terminal hai lần nhanh để vào chế độ bootloader

#### Vấn đề: Lỗi biên dịch trong PlatformIO
**Lỗi:** `fatal error: Arduino.h: No such file or directory`

**Giải pháp:**
1. Xóa thư mục `.pio` trong dự án
2. Chạy "PlatformIO: Rebuild" trong Command Palette
3. Đảm bảo `platformio.ini` có cấu hình board đúng:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Thư Viện Grove

#### Vấn đề: Thư viện Grove không import được trên Raspberry Pi
**Lỗi:** `ModuleNotFoundError: No module named 'grove'`

**Giải pháp:**
1. Cài lại thư viện Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Nếu dùng môi trường ảo, bạn có thể cần cài đặt toàn cục hoặc sao chép thư viện
3. Kiểm tra I2C đã bật: `sudo raspi-config nonint do_i2c 0`

#### Vấn đề: Cảm biến Grove không được phát hiện
**Lỗi:** `IOError: [Errno 121] Remote I/O error`

**Giải pháp:**
1. Kiểm tra kết nối vật lý (đảm bảo cáp Grove được cắm chặt)
2. Xác nhận cảm biến cắm đúng cổng (analog, digital, I2C, UART)
3. Chạy `i2cdetect -y 1` để xem thiết bị có xuất hiện trên bus I2C không
4. Thử cáp Grove khác
5. Đảm bảo Grove Base Hat đã được gắn đúng chân GPIO của Raspberry Pi

---

## Các Vấn Đề Phần Cứng

### Raspberry Pi

#### Vấn đề: Raspberry Pi không khởi động
**Triệu chứng:** Không hiển thị, đèn LED không hoạt động hoặc màn hình vân cầu vồng

**Giải pháp:**
1. **Kiểm tra nguồn:** Dùng bộ nguồn USB-C 5V 3A chính hãng cho Pi 4
2. **Vấn đề thẻ SD:** 
   - Định dạng lại thẻ SD và cài lại Raspberry Pi OS
   - Thử thẻ SD khác (dùng thương hiệu khuyến nghị)
   - Đảm bảo thẻ SD được cắm đúng cách
3. **Kiểm tra kết nối HDMI:** Thử cả hai cổng HDMI trên Pi 4, dùng cổng HDMI gần nguồn hơn

#### Vấn đề: Không thể SSH vào Raspberry Pi
**Triệu chứng:** Kết nối bị từ chối hoặc hết thời gian chờ

**Giải pháp:**
1. Bật SSH:
   - Khi ghi hình thẻ SD bằng Raspberry Pi Imager, cấu hình SSH trong tùy chọn nâng cao
   - Hoặc tạo file rỗng tên `ssh` (không có phần mở rộng) trong phân vùng boot
2. Tìm địa chỉ IP của Pi:
   - Kiểm tra thiết bị kết nối trên router
   - Dùng `ping raspberrypi.local` (nếu hỗ trợ mDNS)
   - Dùng công cụ quét mạng như `nmap` hoặc Angry IP Scanner
3. Kiểm tra mạng:
   - Đảm bảo Pi và máy tính cùng mạng
   - Thử kết nối bằng cáp ethernet thay vì WiFi
4. Xác minh tên đăng nhập/mật khẩu (mặc định: user `pi`, mật khẩu `raspberry`)

#### Vấn đề: Grove Base Hat không nhận diện
**Triệu chứng:** Cảm biến không hoạt động, lỗi I2C

**Giải pháp:**
1. Đảm bảo Base Hat được cắm chắc chắn trên tất cả chân GPIO
2. Kiểm tra xem có chân GPIO nào bị cong trên Pi hoặc Base Hat không
3. Bật giao diện I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Kiểm tra I2C hoạt động: `i2cdetect -y 1`

#### Vấn đề: Raspberry Pi chạy chậm
**Triệu chứng:** Giao diện bị lag, phản hồi chậm

**Giải pháp:**
1. Kiểm tra tốc độ thẻ SD (dùng Class 10 trở lên, hoặc SSD qua USB)
2. Giải phóng dung lượng đĩa: kiểm tra bằng `df -h`, xóa file không cần thiết
3. Giảm bộ nhớ GPU trong `raspi-config` nếu không dùng camera/màn hình nhiều
4. Đóng các ứng dụng không cần thiết
5. Xem xét nâng cấp lên Pi 4 với nhiều RAM hơn nếu đang dùng Pi 3 hoặc cũ hơn

### Wio Terminal

#### Vấn đề: Màn hình Wio Terminal không hiển thị
**Triệu chứng:** Không có hình sau khi tải mã

**Giải pháp:**
1. Kiểm tra xem mã có khởi tạo màn hình (thư viện TFT_eSPI) không
2. Cập nhật firmware Wio Terminal từ [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Thêm đoạn mã khởi tạo màn hình:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Thử tải ví dụ mẫu từ PlatformIO để kiểm tra phần cứng

#### Vấn đề: WiFi trên Wio Terminal không hoạt động
**Triệu chứng:** Không thể kết nối WiFi, lỗi mạng

**Giải pháp:**
1. **Cập nhật firmware WiFi:** Làm theo [hướng dẫn cập nhật firmware WiFi Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Kiểm tra thông tin WiFi:** Đảm bảo SSID và mật khẩu đúng
3. **Băng tần WiFi:** Wio Terminal chỉ hỗ trợ WiFi 2.4GHz (không hỗ trợ 5GHz)
4. **Cường độ tín hiệu:** Di chuyển gần router hơn
5. **Cài đặt router:** Một số mạng doanh nghiệp/WPA-Enterprise có thể không hoạt động

#### Vấn đề: Wio Terminal không được máy tính nhận dạng
**Triệu chứng:** Thiết bị USB không hiện trong máy tính

**Giải pháp:**
1. **Thử cáp USB khác:** Dùng cáp truyền dữ liệu, không dùng cáp chỉ sạc
2. **Vào chế độ bootloader:** Trượt công tắc nguồn xuống hai lần nhanh
   - Đèn LED xanh nhấp nháy, thiết bị hiện là "Arduino" trong Device Manager
3. **Cài driver (Windows):**
   - Tải và cài đặt [driver USB Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Thử cổng USB khác:** Tránh dùng hub USB, kết nối trực tiếp
5. **Cập nhật driver USB hệ thống**

#### Vấn đề: Cảm biến không hoạt động trên Wio Terminal
**Triệu chứng:** Cảm biến Grove không đọc dữ liệu

**Giải pháp:**
1. Kiểm tra kết nối cáp Grove
2. Xác nhận dùng đúng cổng Grove (bên trái hoặc bên phải)
3. Bao gồm thư viện phù hợp cho cảm biến
4. Kiểm tra yêu cầu nguồn của cảm biến
5. Thử cảm biến với mã ví dụ từ thư viện

### Thiết Bị Ảo (CounterFit)

#### Vấn đề: Ứng dụng CounterFit không khởi động
**Lỗi:** Nhiều lỗi Python khi khởi chạy CounterFit

**Giải pháp:**
1. Đảm bảo môi trường ảo đã được kích hoạt
2. Cài đặt/lại CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Kiểm tra cổng 5000 chưa được sử dụng:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Dừng tiến trình đang dùng cổng 5000 hoặc đổi sang cổng khác:
   ```bash
   counterfit --port 5001
   ```

#### Vấn đề: Không thể kết nối đến CounterFit từ mã
**Lỗi:** Kết nối bị từ chối hoặc hết thời gian chờ

**Giải pháp:**
1. Kiểm tra CounterFit đang chạy: Mở trình duyệt tới `http://127.0.0.1:5000`
2. Kiểm tra URL kết nối trong mã có khớp với địa chỉ CounterFit không
3. Đảm bảo tường lửa không chặn kết nối
4. Thử khởi động lại cả ứng dụng CounterFit và mã của bạn

#### Vấn đề: Cảm biến không hiển thị trong CounterFit
**Triệu chứng:** Cảm biến đã tạo không xuất hiện trên giao diện CounterFit

**Giải pháp:**
1. Tạo cảm biến trong giao diện CounterFit trước khi chạy mã
2. Tải lại trang trình duyệt
3. Kiểm tra loại cảm biến khớp với loại mã mong đợi
4. Xóa bộ nhớ cache trình duyệt

---

## Các Vấn Đề Kết Nối

### Kết Nối WiFi

#### Vấn đề: Thiết bị không thể kết nối WiFi
**Triệu chứng:** Hết thời gian chờ kết nối, xác thực thất bại

**Giải pháp:**
1. **Kiểm tra SSID và mật khẩu:** Đảm bảo thông tin đúng
2. **Băng tần WiFi:** Phần lớn thiết bị IoT chỉ hỗ trợ 2.4GHz (không hỗ trợ 5GHz)
3. **Cài đặt router:**
   - Tắt cách ly điểm truy cập nếu bật
   - Dùng bảo mật WPA2-PSK (tránh WPA3, WEP hoặc mạng mở)
   - Đảm bảo DHCP được bật
4. **Mạng ẩn:** Nếu SSID ẩn, có thể bạn cần cấu hình rõ ràng
5. **Cường độ tín hiệu:** Để thiết bị gần router hơn
6. **Nhiễu:** Các thiết bị khác, lò vi sóng, tường có thể gây nhiễu

#### Vấn đề: Kết nối WiFi thường xuyên bị ngắt
**Triệu chứng:** Kết nối không ổn định

**Giải pháp:**
1. Kiểm tra độ ổn định router, cân nhắc khởi động lại
2. Cập nhật firmware thiết bị
3. Dùng IP tĩnh thay vì DHCP
4. Giảm khoảng cách đến router hoặc dùng bộ mở rộng WiFi
5. Kiểm tra nhiễu từ thiết bị khác
6. Đảm bảo nguồn cấp đủ (đặc biệt với Raspberry Pi)

### Dịch Vụ Đám Mây

#### Vấn đề: Không thể kết nối Azure IoT Hub
**Lỗi:** Xác thực thất bại, kết nối bị từ chối

**Giải pháp:**
1. **Xác minh thông tin:**
   - Kiểm tra chuỗi kết nối đúng
   - Đảm bảo không có khoảng trắng hoặc ngắt dòng thừa trong chuỗi kết nối
2. **Kiểm tra đăng ký thiết bị:** Thiết bị phải được đăng ký trên IoT Hub
3. **Tường lửa/proxy:** Cho phép MQTT (cổng 8883) hoặc HTTPS (cổng 443) outbound
4. **Vùng IoT Hub:** Đảm bảo IoT Hub đang chạy và không khác vùng gây trễ
5. **Giới hạn hạn ngạch:** Kiểm tra xem có vượt giới hạn tầng miễn phí không
6. **Kiểm tra kết nối:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Vấn đề: Azure Functions không kích hoạt
**Triệu chứng:** Tin nhắn gửi đi nhưng hàm không chạy

**Giải pháp:**
1. Kiểm tra Function App đang chạy (không bị dừng)
2. Xác minh chuỗi kết nối trong cài đặt Function App
3. Kiểm tra nhật ký hàm trong Azure Portal
4. Đảm bảo điểm cuối tương thích Event Hub được cấu hình đúng
5. Kiểm tra định dạng tin nhắn phù hợp với hàm
6. Kiểm tra gói dịch vụ Function App (tiêu thụ hay chuyên dụng)

### MQTT
#### Vấn đề: Kết nối MQTT thất bại  
**Lỗi:** Kết nối bị từ chối, xác thực không thành công

**Giải pháp:**  
1. **Địa chỉ broker:** Kiểm tra URL/IP broker có đúng không  
2. **Cổng:** Kiểm tra số cổng (1883 cho không mã hóa, 8883 cho TLS)  
3. **Xác thực:** Kiểm tra tên đăng nhập/mật khẩu nếu cần  
4. **TLS/SSL:** Đảm bảo chứng chỉ hợp lệ và được tin cậy  
5. **Firewall:** Kiểm tra cổng không bị chặn  
6. **Kiểm tra bằng client MQTT:** Dùng MQTT Explorer hoặc mosquitto_pub/sub để test

#### Vấn đề: Tin nhắn MQTT không nhận được  
**Triệu chứng:** Tin nhắn đã được publish nhưng người đăng ký không nhận được

**Giải pháp:**  
1. **Tên chủ đề:** Kiểm tra chủ đề của người đăng ký trùng chính xác với người publish  
2. **Mức QoS:** Thử QoS 1 hoặc 2 thay vì 0  
3. **Ký tự đại diện:** Kiểm tra sử dụng ký tự đại diện đúng (`+` cho một cấp, `#` cho nhiều cấp)  
4. **Tin nhắn giữ lại:** Publisher có thể đặt cờ retain để giữ tin nhắn cuối cùng  
5. **Thời gian kết nối:** Đảm bảo người đăng ký kết nối trước khi tin nhắn được publish

---

## Vấn đề với cảm biến và bộ chấp hành

### Cảm biến Grove

#### Vấn đề: Cảm biến trả về giá trị sai  
**Triệu chứng:** Đọc được giá trị 0, -1 hoặc giá trị vô nghĩa

**Giải pháp:**  
1. **Kiểm tra kết nối:** Đảm bảo cảm biến được kết nối đúng cách  
2. **Cổng đúng:** Kiểm tra cảm biến cắm đúng loại cổng:  
   - Cảm biến tương tự → cổng Analog (A0, A2, A4)  
   - Cảm biến số → cổng Digital (D5, D16, D18, v.v.)  
   - Cảm biến I2C → cổng I2C  
3. **Hiệu chỉnh:** Một số cảm biến cần hiệu chỉnh (độ ẩm đất, ánh sáng)  
4. **Tắt nguồn khởi động lại:** Ngắt kết nối rồi kết nối lại cảm biến  
5. **Hồ sơ cảm biến:** Kiểm tra thông số kỹ thuật và yêu cầu của cảm biến

#### Vấn đề: Cảm biến độ ẩm đất điện dung luôn báo ẩm  
**Triệu chứng:** Cảm biến đo độ ẩm cao ngay cả khi đất khô

**Giải pháp:**  
1. **Cần hiệu chỉnh:** Cảm biến đất cần hiệu chỉnh:  
   - Đọc giá trị trong không khí (mức khô)  
   - Đọc giá trị trong nước (mức ướt)  
   - Lập bản đồ các giá trị giữa hai mức này  
2. **Kiểm tra lớp phủ cảm biến:** Cảm biến có thể bị hỏng lớp phủ nếu bị trầy xước  
3. **Vị trí đặt:** Đảm bảo cảm biến được cắm hoàn toàn vào đất

#### Vấn đề: Đọc sai cảm biến nhiệt độ/độ ẩm  
**Triệu chứng:** DHT11/DHT22 hiển thị nhiệt độ hoặc độ ẩm sai

**Giải pháp:**  
1. **Vị trí cảm biến:** Tránh ánh nắng trực tiếp, nguồn nhiệt hoặc luồng khí  
2. **Thời gian khởi động:** Cho cảm biến 2 giây sau khi bật nguồn trước khi đọc  
3. **Tần suất đọc:** Cảm biến DHT cần thời gian giữa các lần đọc (ít nhất 2 giây)  
4. **Kiểm tra ngưng tụ:** Có thể ảnh hưởng đến đọc giá trị  
5. **Chất lượng cảm biến:** DHT11 kém chính xác hơn DHT22

### Camera

#### Vấn đề: Camera không được phát hiện trên Raspberry Pi  
**Lỗi:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Giải pháp:**  
1. **Bật giao diện camera:**  
   ```bash
   sudo raspi-config
   ```
   Vào Interface Options → Camera → Enable  
2. **Kiểm tra cáp ruy băng:** Đảm bảo cáp camera được cắm đúng  
   - Mặt xanh hướng về cổng USB trên Pi Zero  
   - Mặt xanh hướng ra khỏi cổng USB trên Pi 4  
3. **Cập nhật firmware:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Test camera:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Vấn đề: Hình ảnh camera chất lượng kém  
**Triệu chứng:** Hình mờ, tối hoặc màu nhạt

**Giải pháp:**  
1. **Lấy nét:** Bỏ lớp bảo vệ trên ống kính, điều chỉnh nét nếu có thể  
2. **Ánh sáng:** Đảm bảo đủ ánh sáng  
3. **Cài đặt camera:** Điều chỉnh phơi sáng, ISO, cân bằng trắng trong code  
4. **Ổn định:** Giữ camera cố định, dùng giá ba chân nếu cần  
5. **Độ phân giải:** Không vượt quá độ phân giải tối đa của camera

### Microphone và Loa

#### Vấn đề: Không có âm thanh vào/ra  
**Triệu chứng:** Micro không ghi âm, loa không phát âm

**Giải pháp:**  
1. **Kiểm tra kết nối:** Xác nhận thiết bị âm thanh được kết nối đúng  
2. **Kiểm tra phần cứng:**  
   - Loa: `speaker-test -t wav -c 2`  
   - Microphone: `arecord -l` để liệt kê, `arecord test.wav` để ghi âm  
3. **Cài đặt âm lượng:** Kiểm tra và điều chỉnh volume:  
   ```bash
   alsamixer
   ```
4. **Chọn thiết bị âm thanh:** Chỉ định đúng thiết bị trong code  
5. **Vấn đề driver:** Cập nhật ALSA hoặc cài lại driver âm thanh

#### Vấn đề: ReSpeaker hat không hoạt động  
**Triệu chứng:** Thiết bị âm thanh không được nhận

**Giải pháp:**  
1. **Cài driver:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Kiểm tra cài đặt:** `arecord -l` phải liệt kê ReSpeaker  
3. **Cập nhật firmware:** Một số phiên bản Pi OS cần cập nhật driver  
4. **Kiểm tra kết nối:** Đảm bảo hat được cắm đúng vào chân GPIO

---

## Vấn đề môi trường phát triển

### VS Code

#### Vấn đề: Terminal không tự động kích hoạt môi trường ảo  
**Triệu chứng:** Terminal mở ra nhưng không kích hoạt venv

**Giải pháp:**  
1. **Chọn Python interpreter:** Command Palette → "Python: Select Interpreter" → Chọn venv  
2. **Khởi động lại VS Code** sau khi chọn interpreter  
3. **Kiểm tra cài đặt:** Trong `settings.json`, thêm:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Vấn đề: Code không chạy trên thiết bị  
**Triệu chứng:** Code chạy nhưng thiết bị không phản hồi

**Giải pháp:**  
1. **Đảm bảo code đã lưu** (kiểm tra dấu chấm trên tab file)  
2. **Kiểm tra Python đang chạy:** `which python` hoặc `where python`  
3. **Với Wio Terminal:** Đảm bảo code được tải lên qua PlatformIO (nhấn nút upload)  
4. **Với Raspberry Pi:** SSH vào Pi và chạy code ở đó  
5. **Kiểm tra cửa sổ output** xem có lỗi không

#### Vấn đề: IntelliSense không hiện hàm thư viện  
**Triệu chứng:** Không có autocomplete cho module import

**Giải pháp:**  
1. Đảm bảo thư viện đã được cài trong môi trường hiện tại  
2. Tải lại cửa sổ VS Code  
3. Kiểm tra Python interpreter đúng  
4. Cài stubs kiểu nếu có: `pip install types-<library-name>`

### Môi trường ảo Python

#### Vấn đề: Không thể tạo môi trường ảo  
**Lỗi:** `The virtual environment was not created successfully`

**Giải pháp:**  
1. **Cài module venv:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Đã bao gồm sẵn trong Python  
   - Windows: Cài lại Python với đủ thành phần  
2. **Kiểm tra cài đặt Python:** Đảm bảo Python đã cài đúng  
3. **Dùng đường dẫn đầy đủ:** Thử `python3 -m venv .venv` với lệnh python3 rõ ràng

#### Vấn đề: Gói cài sai vị trí  
**Triệu chứng:** Lỗi import sau khi cài gói

**Giải pháp:**  
1. **Đảm bảo venv đang kích hoạt:** Dấu nhắc lệnh có `(.venv)`  
2. **Kiểm tra vị trí pip:** `which pip` phải trỏ tới `.venv/bin/pip`  
3. **Cài lại trong venv:** Kích hoạt venv rồi `pip install <package>`  
4. **Không dùng sudo với pip** trong môi trường ảo

#### Vấn đề: Môi trường ảo không di động  
**Triệu chứng:** Venv không chạy sau khi di chuyển hoặc trên máy khác

**Giải pháp:**  
1. **Không di chuyển venv:** Xóa và tạo lại nơi mới  
2. **Dùng requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Tạo lại venv:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # hoặc activate.bat trên Windows
   pip install -r requirements.txt
   ```
  
### Phụ thuộc

#### Vấn đề: Cài gói thất bại  
**Lỗi:** Các lỗi pip khác nhau khi cài đặt

**Giải pháp:**  
1. **Cập nhật pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Cài công cụ build:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Cài Visual Studio Build Tools  
3. **Kiểm tra kết nối internet**  
4. **Thử chỉ số gói khác:** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **Cài phiên bản cụ thể:** `pip install <package>==<version>`

#### Vấn đề: Xung đột phụ thuộc  
**Lỗi:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Giải pháp:**  
1. **Dùng môi trường ảo mới** cho mỗi dự án  
2. **Cập nhật gói:** `pip install --upgrade <package>`  
3. **Kiểm tra yêu cầu:** Dùng `pip check` tìm xung đột  
4. **Cài phiên bản tương thích:** Chỉ định phạm vi phiên bản trong requirements.txt

---

## Vấn đề hiệu năng

### Vấn đề: Code chạy chậm  
**Triệu chứng:** Trễ, timeout, không phản hồi

**Giải pháp:**  
1. **Giảm tần suất đọc cảm biến:** Không đọc quá thường xuyên  
2. **Tối ưu vòng lặp:** Tránh busy-waiting, dùng sleep() hoặc delay  
3. **Vấn đề bộ nhớ:**  
   - Đóng ứng dụng không cần thiết  
   - Giải phóng dung lượng lưu trữ  
   - Giám sát với `top` hoặc `htop` trên Pi  
4. **Tốc độ thẻ SD:** Dùng thẻ SD hoặc SSD nhanh hơn cho Raspberry Pi  
5. **Trễ mạng:** Dùng thao tác async cho các cuộc gọi mạng

### Vấn đề: Lỗi hết bộ nhớ  
**Lỗi:** `MemoryError` hoặc hệ thống bị treo

**Giải pháp:**  
1. **Với Raspberry Pi:**  
   - Đóng ứng dụng không cần thiết  
   - Tăng không gian swap  
   - Dùng OS nhẹ hơn (phiên bản Lite)  
   - Nâng cấp RAM (Pi 4 có các tùy chọn 2/4/8GB)  
2. **Với Wio Terminal:**  
   - Giảm dung lượng bộ đệm  
   - Dùng hình ảnh kích thước nhỏ hơn  
   - Tối ưu chuỗi ký tự  
   - Kiểm tra rò rỉ bộ nhớ (bộ nhớ không được giải phóng)

### Vấn đề: Mất dữ liệu hoặc hỏng  
**Triệu chứng:** Tin nhắn mất, tập tin hỏng

**Giải pháp:**  
1. **Vấn đề thẻ SD:**  
   - Dùng thẻ SD chất lượng (tránh thẻ rẻ/nhái)  
   - Sao lưu thường xuyên  
   - Tắt nguồn đúng cách (không rút điện đột ngột)  
2. **Tràn bộ đệm:** Tăng dung lượng bộ đệm trong code  
3. **Độ tin cậy mạng:** Thêm logic thử lại và xử lý lỗi  
4. **Chất lượng dịch vụ:** Dùng MQTT QoS 1 hoặc 2 cho các tin nhắn quan trọng

---

## Các thông báo lỗi phổ biến

### `ModuleNotFoundError: No module named 'X'`  
**Nguyên nhân:** Gói chưa được cài hoặc môi trường ảo chưa được kích hoạt

**Giải pháp:**  
```bash
pip install X
```
Đảm bảo đã kích hoạt môi trường ảo trước.

### `Permission denied` trên Linux/macOS  
**Nguyên nhân:** Cần quyền nâng cao hoặc lỗi quyền truy cập file

**Giải pháp:**  
- Với thao tác hệ thống: Dùng `sudo`  
- Với pip: KHÔNG dùng sudo với venv, kích hoạt venv trước  
- Với cổng serial: Thêm user vào nhóm dialout: `sudo usermod -a -G dialout $USER`, sau đó đăng xuất/đăng nhập lại

### `OSError: [Errno 98] Address already in use`  
**Nguyên nhân:** Cổng đã được sử dụng bởi tiến trình khác

**Giải pháp:**  
1. Tìm tiến trình đang dùng cổng: `lsof -i :<port>` hoặc `netstat -ano | findstr :<port>`  
2. Dừng tiến trình hoặc dùng cổng khác trong code

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Nguyên nhân:** Xác thực chứng chỉ SSL thất bại

**Giải pháp:**  
1. Cập nhật chứng chỉ: `pip install --upgrade certifi`  
2. Kiểm tra giờ hệ thống chính xác: `date`  
3. Chỉ dùng cho phát triển (không dùng trong sản xuất): Tắt xác thực trong code

### `IndentationError: unexpected indent`  
**Nguyên nhân:** Lỗi thụt lề Python (hòa lẫn tab và space)

**Giải pháp:**  
1. Dùng thụt lề nhất quán (4 space theo chuẩn Python)  
2. Cấu hình trình soạn thảo dùng space thay tab  
3. VS Code: Đặt `"editor.insertSpaces": true` và `"editor.tabSize": 4`

### `UnicodeDecodeError` hoặc `UnicodeEncodeError`  
**Nguyên nhân:** Lỗi mã hóa ký tự

**Giải pháp:**  
```python
# Khi đọc tập tin
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Khi ghi tập tin
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Nhận trợ giúp

Nếu bạn đã thử các bước khắc phục trên mà vẫn có vấn đề:

### 1. Kiểm tra tài nguyên sẵn có  
- **Tài liệu:** Đọc [README](README.md) và hướng dẫn bài học  
- **Hướng dẫn phần cứng:** Xem [hardware.md](hardware.md) cho thông tin phần cứng cụ thể  
- **Wiki Seeed Studio:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) cho các linh kiện Grove

### 2. Tìm kiếm các vấn đề tương tự  
- **GitHub Issues:** Tìm kiếm [các issue sẵn có](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Tìm kiếm theo thông báo lỗi  
- **Forum thiết bị:** Tham khảo forum Raspberry Pi hoặc Arduino

### 3. Tạo issue GitHub  
Nếu không tìm được giải pháp:  
1. Truy cập [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Nhấn "New Issue"  
3. Cung cấp:  
   - Mô tả rõ ràng vấn đề  
   - Các bước để tái hiện vấn đề  
   - Thông báo lỗi (toàn bộ)  
   - Phiên bản phần cứng/phần mềm  
   - Những gì bạn đã thử  
   - Ảnh chụp màn hình nếu có

### 4. Tham gia cộng đồng  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Cung cấp báo cáo lỗi tốt  
Một báo cáo lỗi tốt bao gồm:
- **Môi trường:** Hệ điều hành, phiên bản Python, phần cứng sử dụng  
- **Các bước tái hiện:** Các bước chính xác gây ra sự cố  
- **Hành vi mong đợi:** Điều gì nên xảy ra  
- **Hành vi thực tế:** Điều gì thực sự xảy ra  
- **Thông báo lỗi:** Toàn bộ văn bản lỗi, không dùng ảnh chụp màn hình  
- **Mã nguồn:** Ví dụ mã tối thiểu tái hiện được sự cố  

---

## Mẹo phòng tránh

### Thực hành tốt chung
1. **Luôn sao lưu:** Sao lưu thường xuyên các thẻ SD/mã code hoạt động  
2. **Ghi chú thay đổi:** Ghi lại những gì hoạt động trong phần bình luận  
3. **Kiểm soát phiên bản:** Sử dụng git để theo dõi thay đổi mã  
4. **Kiểm tra dần:** Kiểm tra các thay đổi nhỏ trước khi kết hợp  
5. **Đọc kỹ lỗi:** Chúng thường chỉ rõ vấn đề chính xác  
6. **Cập nhật thường xuyên:** Giữ phần mềm/phần cứng luôn mới  
7. **Dùng linh kiện chất lượng:** Tránh cáp/nguồn rẻ tiền  
8. **Nguồn điện ổn định:** Dùng nguồn phù hợp (đặc biệt với Pi)  

### Quy trình phát triển
1. **Bắt đầu đơn giản:** Dùng mã ví dụ có sẵn và hoạt động  
2. **Thay đổi từng bước:** Dễ tìm lỗi hơn  
3. **Kiểm tra thường xuyên:** Phát hiện lỗi sớm  
4. **Giữ gọn gàng:** Tổ chức file và mã nguồn có logic  
5. **Bình luận mã:** Tương lai bạn sẽ cảm ơn điều này  

---

*Hướng dẫn xử lý sự cố này được duy trì bởi cộng đồng. Nếu bạn tìm ra giải pháp cho vấn đề không có trong danh sách, vui lòng [đóng góp](CONTRIBUTING.md) để giúp đỡ người khác!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Tuyên bố từ chối trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi nỗ lực đảm bảo độ chính xác, vui lòng lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn tham khảo chính xác nhất. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp do con người thực hiện. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->