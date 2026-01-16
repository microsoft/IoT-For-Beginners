<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:43:10+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "vi"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) là một máy tính đơn bo mạch. Bạn có thể thêm cảm biến và bộ truyền động bằng cách sử dụng nhiều loại thiết bị và hệ sinh thái khác nhau, và trong các bài học này, chúng ta sẽ sử dụng một hệ sinh thái phần cứng gọi là [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Bạn sẽ lập trình Pi của mình và truy cập các cảm biến Grove bằng Python.

![Một Raspberry Pi 4](../../../../../translated_images/vi/raspberry-pi-4.fd4590d308c3d456.webp)

## Cài đặt

Nếu bạn đang sử dụng Raspberry Pi làm phần cứng IoT của mình, bạn có hai lựa chọn - bạn có thể làm theo tất cả các bài học này và lập trình trực tiếp trên Pi, hoặc bạn có thể kết nối từ xa với một Pi 'không màn hình' và lập trình từ máy tính của mình.

Trước khi bắt đầu, bạn cũng cần kết nối Grove Base Hat với Pi của mình.

### Nhiệm vụ - cài đặt

Cài đặt Grove base hat trên Pi của bạn và cấu hình Pi.

1. Kết nối Grove base hat với Pi của bạn. Đế cắm trên hat vừa khít với tất cả các chân GPIO trên Pi, trượt xuống hết các chân để ngồi chắc chắn trên đế. Nó sẽ bao phủ Pi.

    ![Lắp đặt grove hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Quyết định cách bạn muốn lập trình Pi của mình, và chuyển đến phần liên quan bên dưới:

    * [Làm việc trực tiếp trên Pi của bạn](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Truy cập từ xa để lập trình Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Làm việc trực tiếp trên Pi của bạn

Nếu bạn muốn làm việc trực tiếp trên Pi của mình, bạn có thể sử dụng phiên bản desktop của Raspberry Pi OS và cài đặt tất cả các công cụ cần thiết.

#### Nhiệm vụ - làm việc trực tiếp trên Pi của bạn

Cài đặt Pi của bạn để phát triển.

1. Làm theo hướng dẫn trong [hướng dẫn cài đặt Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) để cài đặt Pi của bạn, kết nối nó với bàn phím/chuột/màn hình, kết nối nó với mạng WiFi hoặc ethernet, và cập nhật phần mềm.

Để lập trình Pi bằng các cảm biến và bộ truyền động Grove, bạn sẽ cần cài đặt một trình soạn thảo để viết mã thiết bị, cùng với các thư viện và công cụ khác nhau để tương tác với phần cứng Grove.

1. Sau khi Pi của bạn khởi động lại, mở Terminal bằng cách nhấp vào biểu tượng **Terminal** trên thanh menu trên cùng, hoặc chọn *Menu -> Accessories -> Terminal*.

1. Chạy lệnh sau để đảm bảo hệ điều hành và phần mềm đã cài đặt được cập nhật:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Chạy các lệnh sau để cài đặt tất cả các thư viện cần thiết cho phần cứng Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Điều này bắt đầu bằng việc cài đặt Git, cùng với Pip để cài đặt các gói Python.

    Một trong những tính năng mạnh mẽ của Python là khả năng cài đặt [gói Pip](https://pypi.org) - đây là các gói mã được viết bởi người khác và được xuất bản lên Internet. Bạn có thể cài đặt một gói Pip lên máy tính của mình chỉ với một lệnh, sau đó sử dụng gói đó trong mã của bạn.

    Các gói Python của Seeed Grove cần được cài đặt từ mã nguồn. Các lệnh này sẽ clone repo chứa mã nguồn của gói này, sau đó cài đặt nó cục bộ.

    > 💁 Mặc định khi bạn cài đặt một gói, nó sẽ có sẵn ở mọi nơi trên máy tính của bạn, và điều này có thể dẫn đến các vấn đề với phiên bản gói - chẳng hạn như một ứng dụng phụ thuộc vào một phiên bản của gói có thể bị lỗi khi bạn cài đặt một phiên bản mới cho một ứng dụng khác. Để giải quyết vấn đề này, bạn có thể sử dụng [môi trường ảo Python](https://docs.python.org/3/library/venv.html), về cơ bản là một bản sao của Python trong một thư mục riêng biệt, và khi bạn cài đặt các gói Pip, chúng sẽ chỉ được cài đặt vào thư mục đó. Bạn sẽ không sử dụng môi trường ảo khi sử dụng Pi của mình. Script cài đặt Grove cài đặt các gói Python của Grove toàn cầu, vì vậy để sử dụng môi trường ảo, bạn sẽ cần thiết lập môi trường ảo sau đó cài đặt lại các gói Grove bên trong môi trường đó. Sử dụng các gói toàn cầu sẽ dễ dàng hơn, đặc biệt vì nhiều nhà phát triển Pi sẽ flash lại một thẻ SD sạch cho mỗi dự án.

    Cuối cùng, điều này kích hoạt giao diện I<sup>2</sup>C.

1. Khởi động lại Pi bằng cách sử dụng menu hoặc chạy lệnh sau trong Terminal:

    ```sh
    sudo reboot
    ```

1. Sau khi Pi khởi động lại, mở lại Terminal và chạy lệnh sau để cài đặt [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - đây là trình soạn thảo bạn sẽ sử dụng để viết mã thiết bị bằng Python.

    ```sh
    sudo apt install code
    ```

    Sau khi cài đặt, VS Code sẽ có sẵn từ thanh menu trên cùng.

    > 💁 Bạn có thể tự do sử dụng bất kỳ IDE hoặc trình soạn thảo Python nào cho các bài học này nếu bạn có công cụ ưa thích, nhưng các bài học sẽ cung cấp hướng dẫn dựa trên việc sử dụng VS Code.

1. Cài đặt Pylance. Đây là một tiện ích mở rộng cho VS Code cung cấp hỗ trợ ngôn ngữ Python. Tham khảo [tài liệu tiện ích mở rộng Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) để biết hướng dẫn cài đặt tiện ích mở rộng này trong VS Code.

### Truy cập từ xa để lập trình Pi

Thay vì lập trình trực tiếp trên Pi, bạn có thể chạy nó ở chế độ 'không màn hình', tức là không kết nối với bàn phím/chuột/màn hình, và cấu hình cũng như lập trình trên đó từ máy tính của bạn, sử dụng Visual Studio Code.

#### Cài đặt hệ điều hành Pi

Để lập trình từ xa, hệ điều hành Pi cần được cài đặt trên thẻ SD.

##### Nhiệm vụ - cài đặt hệ điều hành Pi

Cài đặt hệ điều hành Pi không màn hình.

1. Tải xuống **Raspberry Pi Imager** từ [trang phần mềm Raspberry Pi OS](https://www.raspberrypi.org/software/) và cài đặt nó.

1. Chèn một thẻ SD vào máy tính của bạn, sử dụng bộ chuyển đổi nếu cần.

1. Khởi chạy Raspberry Pi Imager.

1. Từ Raspberry Pi Imager, chọn nút **CHOOSE OS**, sau đó chọn *Raspberry Pi OS (Other)*, tiếp theo là *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager với Raspberry Pi OS Lite được chọn](../../../../../translated_images/vi/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite là một phiên bản của Raspberry Pi OS không có giao diện người dùng desktop hoặc các công cụ dựa trên giao diện người dùng. Những thứ này không cần thiết cho một Pi không màn hình và làm cho cài đặt nhỏ hơn và thời gian khởi động nhanh hơn.

1. Chọn nút **CHOOSE STORAGE**, sau đó chọn thẻ SD của bạn.

1. Khởi chạy **Advanced Options** bằng cách nhấn `Ctrl+Shift+X`. Các tùy chọn này cho phép cấu hình trước Raspberry Pi OS trước khi nó được ghi vào thẻ SD.

    1. Đánh dấu vào ô **Enable SSH**, và đặt mật khẩu cho người dùng `pi`. Đây là mật khẩu bạn sẽ sử dụng để đăng nhập vào Pi sau này.

    1. Nếu bạn dự định kết nối với Pi qua WiFi, đánh dấu vào ô **Configure WiFi**, và nhập SSID và mật khẩu WiFi của bạn, cũng như chọn quốc gia WiFi của bạn. Bạn không cần làm điều này nếu bạn sẽ sử dụng cáp ethernet. Đảm bảo mạng bạn kết nối là cùng mạng với máy tính của bạn.

    1. Đánh dấu vào ô **Set locale settings**, và đặt quốc gia và múi giờ của bạn.

    1. Chọn nút **SAVE**.

1. Chọn nút **WRITE** để ghi hệ điều hành vào thẻ SD. Nếu bạn đang sử dụng macOS, bạn sẽ được yêu cầu nhập mật khẩu của mình vì công cụ cơ bản ghi hình ảnh đĩa cần quyền truy cập đặc quyền.

Hệ điều hành sẽ được ghi vào thẻ SD, và sau khi hoàn tất, thẻ sẽ được hệ điều hành đẩy ra, và bạn sẽ được thông báo. Tháo thẻ SD khỏi máy tính của bạn, chèn nó vào Pi, bật nguồn Pi và đợi khoảng 2 phút để nó khởi động hoàn toàn.

#### Kết nối với Pi

Bước tiếp theo là truy cập từ xa vào Pi. Bạn có thể làm điều này bằng cách sử dụng `ssh`, có sẵn trên macOS, Linux và các phiên bản Windows gần đây.

##### Nhiệm vụ - kết nối với Pi

Truy cập từ xa vào Pi.

1. Khởi chạy Terminal hoặc Command Prompt, và nhập lệnh sau để kết nối với Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Nếu bạn đang sử dụng Windows với phiên bản cũ không có `ssh` được cài đặt, bạn có thể sử dụng OpenSSH. Bạn có thể tìm thấy hướng dẫn cài đặt trong [tài liệu cài đặt OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Điều này sẽ kết nối với Pi của bạn và yêu cầu mật khẩu.

    Khả năng tìm thấy các máy tính trên mạng của bạn bằng cách sử dụng `<hostname>.local` là một bổ sung khá gần đây cho Linux và Windows. Nếu bạn đang sử dụng Linux hoặc Windows và gặp bất kỳ lỗi nào về việc không tìm thấy Hostname, bạn sẽ cần cài đặt phần mềm bổ sung để kích hoạt mạng ZeroConf (còn được Apple gọi là Bonjour):

    1. Nếu bạn đang sử dụng Linux, cài đặt Avahi bằng lệnh sau:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Nếu bạn đang sử dụng Windows, cách dễ nhất để kích hoạt ZeroConf là cài đặt [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Bạn cũng có thể cài đặt [iTunes for Windows](https://www.apple.com/itunes/download/) để có phiên bản mới hơn của tiện ích (không có sẵn độc lập).

    > 💁 Nếu bạn không thể kết nối bằng `raspberrypi.local`, bạn có thể sử dụng địa chỉ IP của Pi. Tham khảo [tài liệu địa chỉ IP Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) để biết hướng dẫn về một số cách lấy địa chỉ IP.

1. Nhập mật khẩu bạn đã đặt trong Advanced Options của Raspberry Pi Imager.

#### Cấu hình phần mềm trên Pi

Sau khi bạn đã kết nối với Pi, bạn cần đảm bảo hệ điều hành được cập nhật và cài đặt các thư viện và công cụ khác nhau để tương tác với phần cứng Grove.

##### Nhiệm vụ - cấu hình phần mềm trên Pi

Cấu hình phần mềm Pi đã cài đặt và cài đặt các thư viện Grove.

1. Từ phiên `ssh` của bạn, chạy lệnh sau để cập nhật sau đó khởi động lại Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi sẽ được cập nhật và khởi động lại. Phiên `ssh` sẽ kết thúc khi Pi khởi động lại, vì vậy hãy đợi khoảng 30 giây sau đó kết nối lại.

1. Từ phiên `ssh` đã kết nối lại, chạy các lệnh sau để cài đặt tất cả các thư viện cần thiết cho phần cứng Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Điều này bắt đầu bằng việc cài đặt Git, cùng với Pip để cài đặt các gói Python.

    Một trong những tính năng mạnh mẽ của Python là khả năng cài đặt [gói Pip](https://pypi.org) - đây là các gói mã được viết bởi người khác và được xuất bản lên Internet. Bạn có thể cài đặt một gói Pip lên máy tính của mình chỉ với một lệnh, sau đó sử dụng gói đó trong mã của bạn.

    Các gói Python của Seeed Grove cần được cài đặt từ mã nguồn. Các lệnh này sẽ clone repo chứa mã nguồn của gói này, sau đó cài đặt nó cục bộ.

    > 💁 Mặc định khi bạn cài đặt một gói, nó sẽ có sẵn ở mọi nơi trên máy tính của bạn, và điều này có thể dẫn đến các vấn đề với phiên bản gói - chẳng hạn như một ứng dụng phụ thuộc vào một phiên bản của gói có thể bị lỗi khi bạn cài đặt một phiên bản mới cho một ứng dụng khác. Để giải quyết vấn đề này, bạn có thể sử dụng [môi trường ảo Python](https://docs.python.org/3/library/venv.html), về cơ bản là một bản sao của Python trong một thư mục riêng biệt, và khi bạn cài đặt các gói Pip, chúng sẽ chỉ được cài đặt vào thư mục đó. Bạn sẽ không sử dụng môi trường ảo khi sử dụng Pi của mình. Script cài đặt Grove cài đặt các gói Python của Grove toàn cầu, vì vậy để sử dụng môi trường ảo, bạn sẽ cần thiết lập môi trường ảo sau đó cài đặt lại các gói Grove bên trong môi trường đó. Sử dụng các gói toàn cầu sẽ dễ dàng hơn, đặc biệt vì nhiều nhà phát triển Pi sẽ flash lại một thẻ SD sạch cho mỗi dự án.

    Cuối cùng, điều này kích hoạt giao diện I<sup>2</sup>C.

1. Khởi động lại Pi bằng cách chạy lệnh sau:

    ```sh
    sudo reboot
    ```

    Phiên `ssh` sẽ kết thúc khi Pi khởi động lại. Không cần kết nối lại.

#### Cấu hình VS Code để truy cập từ xa

Sau khi Pi được cấu hình, bạn có thể kết nối với nó bằng Visual Studio Code (VS Code) từ máy tính của mình - đây là một trình soạn thảo văn bản dành cho nhà phát triển miễn phí mà bạn sẽ sử dụng để viết mã thiết bị bằng Python.

##### Nhiệm vụ - cấu hình VS Code để truy cập từ xa

Cài đặt phần mềm cần thiết và kết nối từ xa với Pi của bạn.

1. Cài đặt VS Code trên máy tính của bạn bằng cách làm theo [tài liệu VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Làm theo hướng dẫn trong [tài liệu Phát triển Từ xa của VS Code sử dụng SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) để cài đặt các thành phần cần thiết.

1. Làm theo cùng hướng dẫn, kết nối VS Code với Pi.

1. Sau khi kết nối, làm theo hướng dẫn [quản lý tiện ích mở rộng](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) để cài đặt tiện ích mở rộng [Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) từ xa lên Pi.

## Hello world
Việc bắt đầu với một ngôn ngữ lập trình hoặc công nghệ mới thường đi kèm với việc tạo một ứng dụng 'Hello World' - một ứng dụng nhỏ hiển thị văn bản như `"Hello World"` để kiểm tra rằng tất cả các công cụ đã được cấu hình đúng cách.

Ứng dụng Hello World dành cho Pi sẽ đảm bảo rằng bạn đã cài đặt Python và Visual Studio Code đúng cách.

Ứng dụng này sẽ nằm trong một thư mục có tên `nightlight`, và nó sẽ được tái sử dụng với các đoạn mã khác trong các phần sau của bài tập này để xây dựng ứng dụng đèn ngủ.

### Nhiệm vụ - hello world

Tạo ứng dụng Hello World.

1. Mở VS Code, trực tiếp trên Pi hoặc trên máy tính của bạn và kết nối với Pi bằng tiện ích mở rộng Remote SSH.

1. Mở Terminal của VS Code bằng cách chọn *Terminal -> New Terminal*, hoặc nhấn `` CTRL+` ``. Terminal sẽ mở tại thư mục chính của người dùng `pi`.

1. Chạy các lệnh sau để tạo một thư mục cho mã của bạn, và tạo một tệp Python có tên `app.py` bên trong thư mục đó:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Mở thư mục này trong VS Code bằng cách chọn *File -> Open...* và chọn thư mục *nightlight*, sau đó chọn **OK**.

    ![Hộp thoại mở của VS Code hiển thị thư mục nightlight](../../../../../translated_images/vi/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. Mở tệp `app.py` từ trình khám phá của VS Code và thêm đoạn mã sau:

    ```python
    print('Hello World!')
    ```

    Hàm `print` sẽ in bất kỳ nội dung nào được truyền vào nó ra console.

1. Từ Terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python app.py
    ```

    > 💁 Bạn có thể cần gọi rõ ràng `python3` để chạy đoạn mã này nếu bạn đã cài đặt Python 2 bên cạnh Python 3 (phiên bản mới nhất). Nếu bạn có Python 2 được cài đặt, thì việc gọi `python` sẽ sử dụng Python 2 thay vì Python 3. Theo mặc định, các phiên bản mới nhất của Raspberry Pi OS chỉ cài đặt Python 3.

    Kết quả sau sẽ xuất hiện trong terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Chương trình 'Hello World' của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.