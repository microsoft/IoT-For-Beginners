<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-27T21:04:06+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "vi"
}
-->
# Chụp ảnh - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm một camera vào Wio Terminal của mình và chụp ảnh từ nó.

## Phần cứng

Wio Terminal cần một camera.

Camera bạn sẽ sử dụng là [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Đây là một camera 2 megapixel dựa trên cảm biến hình ảnh OV2640. Nó giao tiếp qua giao diện SPI để chụp ảnh và sử dụng I2C để cấu hình cảm biến.

## Kết nối camera

ArduCam không có cổng Grove, thay vào đó nó kết nối với cả bus SPI và I2C thông qua các chân GPIO trên Wio Terminal.

### Nhiệm vụ - kết nối camera

Kết nối camera.

![Một cảm biến ArduCam](../../../../../translated_images/vi/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. Các chân ở đáy của ArduCam cần được kết nối với các chân GPIO trên Wio Terminal. Để dễ dàng tìm đúng chân, hãy gắn nhãn dán chân GPIO đi kèm với Wio Terminal xung quanh các chân:

    ![Wio Terminal với nhãn dán chân GPIO](../../../../../translated_images/vi/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Sử dụng dây nhảy, thực hiện các kết nối sau:

    | Chân ArduCAM | Chân Wio Terminal | Mô tả                                   |
    | ------------ | ----------------- | --------------------------------------- |
    | CS           | 24 (SPI_CS)       | SPI Chip Select                         |
    | MOSI         | 19 (SPI_MOSI)     | SPI Controller Output, Peripheral Input |
    | MISO         | 21 (SPI_MISO)     | SPI Controller Input, Peripheral Output |
    | SCK          | 23 (SPI_SCLK)     | SPI Serial Clock                        |
    | GND          | 6 (GND)           | Ground - 0V                             |
    | VCC          | 4 (5V)            | Nguồn điện 5V                           |
    | SDA          | 3 (I2C1_SDA)      | I2C Serial Data                         |
    | SCL          | 5 (I2C1_SCL)      | I2C Serial Clock                        |

    ![Wio Terminal được kết nối với ArduCam bằng dây nhảy](../../../../../translated_images/vi/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    Kết nối GND và VCC cung cấp nguồn điện 5V cho ArduCam. Nó hoạt động ở 5V, không giống như các cảm biến Grove hoạt động ở 3V. Nguồn điện này được cung cấp trực tiếp từ kết nối USB-C cấp nguồn cho thiết bị.

    > 💁 Đối với kết nối SPI, các nhãn chân trên ArduCam và tên chân Wio Terminal được sử dụng trong mã vẫn sử dụng quy ước đặt tên cũ. Các hướng dẫn trong bài học này sẽ sử dụng quy ước đặt tên mới, ngoại trừ khi tên chân được sử dụng trong mã.

1. Bây giờ bạn có thể kết nối Wio Terminal với máy tính của mình.

## Lập trình thiết bị để kết nối với camera

Wio Terminal bây giờ có thể được lập trình để sử dụng camera ArduCAM đã được gắn.

### Nhiệm vụ - lập trình thiết bị để kết nối với camera

1. Tạo một dự án Wio Terminal mới bằng PlatformIO. Đặt tên dự án này là `fruit-quality-detector`. Thêm mã vào hàm `setup` để cấu hình cổng nối tiếp.

1. Thêm mã để kết nối WiFi, với thông tin đăng nhập WiFi của bạn trong một tệp có tên `config.h`. Đừng quên thêm các thư viện cần thiết vào tệp `platformio.ini`.

1. Thư viện ArduCam không có sẵn dưới dạng thư viện Arduino có thể được cài đặt từ tệp `platformio.ini`. Thay vào đó, nó cần được cài đặt từ mã nguồn trên trang GitHub của họ. Bạn có thể lấy nó bằng cách:

    * Clone repo từ [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Truy cập repo trên GitHub tại [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) và tải mã dưới dạng tệp zip từ nút **Code**

1. Bạn chỉ cần thư mục `ArduCAM` từ mã này. Sao chép toàn bộ thư mục vào thư mục `lib` trong dự án của bạn.

    > ⚠️ Toàn bộ thư mục phải được sao chép, vì vậy mã nằm trong `lib/ArduCam`. Đừng chỉ sao chép nội dung của thư mục `ArduCam` vào thư mục `lib`, hãy sao chép toàn bộ thư mục.

1. Mã thư viện ArduCam hoạt động cho nhiều loại camera. Loại camera bạn muốn sử dụng được cấu hình bằng các cờ trình biên dịch - điều này giúp thư viện được xây dựng nhỏ nhất có thể bằng cách loại bỏ mã cho các camera bạn không sử dụng. Để cấu hình thư viện cho camera OV2640, thêm đoạn sau vào cuối tệp `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Điều này thiết lập 2 cờ trình biên dịch:

      * `ARDUCAM_SHIELD_V2` để thông báo cho thư viện rằng camera nằm trên một bo mạch Arduino, được gọi là shield.
      * `OV2640_CAM` để thông báo cho thư viện chỉ bao gồm mã cho camera OV2640.

1. Thêm một tệp tiêu đề vào thư mục `src` có tên `camera.h`. Tệp này sẽ chứa mã để giao tiếp với camera. Thêm đoạn mã sau vào tệp này:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Đây là mã cấp thấp cấu hình camera bằng cách sử dụng các thư viện ArduCam và trích xuất hình ảnh khi cần thiết bằng bus SPI. Mã này rất cụ thể cho ArduCam, vì vậy bạn không cần lo lắng về cách nó hoạt động ở thời điểm này.

1. Trong `main.cpp`, thêm đoạn mã sau bên dưới các câu lệnh `include` khác để bao gồm tệp mới này và tạo một thể hiện của lớp camera:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Điều này tạo một `Camera` lưu hình ảnh dưới dạng JPEG với độ phân giải 640 x 480. Mặc dù các độ phân giải cao hơn được hỗ trợ (lên đến 3280x2464), bộ phân loại hình ảnh hoạt động trên các hình ảnh nhỏ hơn nhiều (227x227) nên không cần chụp và gửi các hình ảnh lớn hơn.

1. Thêm đoạn mã sau bên dưới để định nghĩa một hàm thiết lập camera:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Hàm `setupCamera` này bắt đầu bằng cách cấu hình chân SPI chip select (`PIN_SPI_SS`) ở mức cao, làm cho Wio Terminal trở thành bộ điều khiển SPI. Sau đó, nó khởi động các bus I2C và SPI. Cuối cùng, nó khởi tạo lớp camera, cấu hình các cài đặt cảm biến camera và đảm bảo mọi thứ được kết nối đúng cách.

1. Gọi hàm này ở cuối hàm `setup`:

    ```cpp
    setupCamera();
    ```

1. Xây dựng và tải mã này lên, sau đó kiểm tra đầu ra từ màn hình nối tiếp. Nếu bạn thấy `Error setting up the camera!`, hãy kiểm tra lại dây nối để đảm bảo tất cả các dây cáp đang kết nối đúng chân trên ArduCam với đúng chân GPIO trên Wio Terminal, và tất cả các dây nhảy được cắm chắc chắn.

## Chụp ảnh

Wio Terminal bây giờ có thể được lập trình để chụp ảnh khi một nút được nhấn.

### Nhiệm vụ - chụp ảnh

1. Các vi điều khiển chạy mã của bạn liên tục, vì vậy không dễ dàng để kích hoạt một hành động như chụp ảnh mà không phản ứng với một cảm biến. Wio Terminal có các nút, vì vậy camera có thể được thiết lập để kích hoạt bởi một trong các nút. Thêm đoạn mã sau vào cuối hàm `setup` để cấu hình nút C (một trong ba nút ở trên cùng, nút gần công tắc nguồn nhất).

    ![Nút C ở trên cùng gần công tắc nguồn](../../../../../translated_images/vi/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Chế độ `INPUT_PULLUP` thực chất đảo ngược một đầu vào. Ví dụ, thông thường một nút sẽ gửi tín hiệu thấp khi không được nhấn và tín hiệu cao khi được nhấn. Khi được đặt thành `INPUT_PULLUP`, chúng gửi tín hiệu cao khi không được nhấn và tín hiệu thấp khi được nhấn.

1. Thêm một hàm trống để phản hồi khi nút được nhấn trước hàm `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Gọi hàm này trong phương thức `loop` khi nút được nhấn:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Đoạn mã này kiểm tra xem nút có được nhấn hay không. Nếu được nhấn, hàm `buttonPressed` sẽ được gọi và vòng lặp sẽ tạm dừng trong 2 giây. Điều này để cho phép thời gian để nút được nhả ra để một lần nhấn dài không được đăng ký hai lần.

    > 💁 Nút trên Wio Terminal được đặt thành `INPUT_PULLUP`, vì vậy gửi tín hiệu cao khi không được nhấn và tín hiệu thấp khi được nhấn.

1. Thêm đoạn mã sau vào hàm `buttonPressed`:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Đoạn mã này bắt đầu chụp ảnh bằng cách gọi `startCapture`. Phần cứng camera không hoạt động bằng cách trả về dữ liệu khi bạn yêu cầu, thay vào đó bạn gửi một lệnh để bắt đầu chụp, và camera sẽ hoạt động trong nền để chụp ảnh, chuyển đổi nó thành JPEG và lưu trữ trong một bộ đệm cục bộ trên chính camera. Lệnh `captureReady` sau đó kiểm tra xem việc chụp ảnh đã hoàn thành hay chưa.

    Khi việc chụp đã hoàn thành, dữ liệu hình ảnh được sao chép từ bộ đệm trên camera vào một bộ đệm cục bộ (mảng byte) với lệnh `readImageToBuffer`. Độ dài của bộ đệm sau đó được gửi đến màn hình nối tiếp.

1. Xây dựng và tải mã này lên, sau đó kiểm tra đầu ra trên màn hình nối tiếp. Mỗi lần bạn nhấn nút C, một hình ảnh sẽ được chụp và bạn sẽ thấy kích thước hình ảnh được gửi đến màn hình nối tiếp.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Các hình ảnh khác nhau sẽ có kích thước khác nhau. Chúng được nén dưới dạng JPEG và kích thước của tệp JPEG cho một độ phân giải nhất định phụ thuộc vào nội dung trong hình ảnh.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Bạn đã chụp ảnh thành công với Wio Terminal của mình.

## Tùy chọn - xác minh hình ảnh camera bằng thẻ SD

Cách dễ nhất để xem các hình ảnh được chụp bởi camera là ghi chúng vào thẻ SD trong Wio Terminal và sau đó xem chúng trên máy tính của bạn. Thực hiện bước này nếu bạn có một thẻ microSD dự phòng và một khe cắm thẻ microSD trên máy tính của bạn hoặc một bộ chuyển đổi.

Wio Terminal chỉ hỗ trợ thẻ microSD có dung lượng tối đa 16GB. Nếu bạn có thẻ SD lớn hơn, nó sẽ không hoạt động.

### Nhiệm vụ - xác minh hình ảnh camera bằng thẻ SD

1. Định dạng một thẻ microSD dưới dạng FAT32 hoặc exFAT bằng các ứng dụng liên quan trên máy tính của bạn (Disk Utility trên macOS, File Explorer trên Windows, hoặc sử dụng các công cụ dòng lệnh trên Linux).

1. Chèn thẻ microSD vào khe cắm ngay bên dưới công tắc nguồn. Đảm bảo nó được đẩy vào hoàn toàn cho đến khi nó kêu "click" và giữ nguyên vị trí, bạn có thể cần đẩy nó bằng móng tay hoặc một công cụ mỏng.

1. Thêm các câu lệnh `include` sau vào đầu tệp `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Thêm hàm sau trước hàm `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Hàm này cấu hình thẻ SD bằng bus SPI.

1. Gọi hàm này từ hàm `setup`:

    ```cpp
    setupSDCard();
    ```

1. Thêm đoạn mã sau phía trên hàm `buttonPressed`:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Đoạn mã này định nghĩa một biến toàn cục cho số lượng tệp. Biến này được sử dụng cho tên tệp hình ảnh để nhiều hình ảnh có thể được chụp với các tên tệp tăng dần - `1.jpg`, `2.jpg` và cứ thế.

    Sau đó, nó định nghĩa hàm `saveToSDCard` nhận một bộ đệm dữ liệu byte và độ dài của bộ đệm. Một tên tệp được tạo bằng số lượng tệp, và số lượng tệp được tăng lên sẵn sàng cho tệp tiếp theo. Dữ liệu nhị phân từ bộ đệm sau đó được ghi vào tệp.

1. Gọi hàm `saveToSDCard` từ hàm `buttonPressed`. Lệnh gọi này nên **trước** khi bộ đệm bị xóa:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Xây dựng và tải mã này lên, sau đó kiểm tra đầu ra trên màn hình nối tiếp. Mỗi lần bạn nhấn nút C, một hình ảnh sẽ được chụp và lưu vào thẻ SD.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. Tắt nguồn Wio Terminal và tháo thẻ microSD bằng cách đẩy nhẹ vào và thả ra, thẻ sẽ bật ra. Bạn có thể cần sử dụng một công cụ mỏng để làm điều này. Cắm thẻ microSD vào máy tính của bạn để xem các hình ảnh.

    ![Hình ảnh một quả chuối được chụp bằng ArduCam](../../../../../translated_images/vi/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.jpg)
> 💁 Có thể mất vài hình ảnh để cân bằng trắng của máy ảnh tự điều chỉnh. Bạn sẽ nhận thấy điều này dựa trên màu sắc của các hình ảnh được chụp, vài hình đầu tiên có thể trông không đúng màu. Bạn luôn có thể khắc phục điều này bằng cách thay đổi mã để chụp vài hình ảnh bị bỏ qua trong hàm `setup`.


---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.