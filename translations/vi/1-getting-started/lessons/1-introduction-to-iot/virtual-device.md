# Máy tính bảng đơn ảo

Thay vì mua một thiết bị IoT cùng với các cảm biến và bộ truyền động, bạn có thể sử dụng máy tính của mình để mô phỏng phần cứng IoT. Dự án [CounterFit](https://github.com/CounterFit-IoT/CounterFit) cho phép bạn chạy một ứng dụng cục bộ để mô phỏng phần cứng IoT như cảm biến và bộ truyền động, và truy cập chúng từ mã Python cục bộ được viết theo cách tương tự như khi bạn viết mã trên Raspberry Pi sử dụng phần cứng thực.

## Cài đặt

Để sử dụng CounterFit, bạn cần cài đặt một số phần mềm miễn phí trên máy tính của mình.

### Nhiệm vụ

Cài đặt phần mềm cần thiết.

1. Cài đặt Python. Tham khảo [trang tải xuống Python](https://www.python.org/downloads/) để biết hướng dẫn cài đặt phiên bản Python mới nhất.

1. Cài đặt Visual Studio Code (VS Code). Đây là trình soạn thảo bạn sẽ sử dụng để viết mã cho thiết bị ảo bằng Python. Tham khảo [tài liệu VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) để biết hướng dẫn cài đặt VS Code.

    > 💁 Bạn có thể sử dụng bất kỳ IDE hoặc trình soạn thảo Python nào mà bạn ưa thích cho các bài học này, nhưng các hướng dẫn sẽ dựa trên việc sử dụng VS Code.

1. Cài đặt tiện ích mở rộng Pylance cho VS Code. Đây là một tiện ích mở rộng cung cấp hỗ trợ ngôn ngữ Python cho VS Code. Tham khảo [tài liệu tiện ích mở rộng Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) để biết hướng dẫn cài đặt tiện ích này trong VS Code.

Hướng dẫn cài đặt và cấu hình ứng dụng CounterFit sẽ được cung cấp vào thời điểm thích hợp trong các hướng dẫn bài tập, vì ứng dụng này được cài đặt theo từng dự án.

## Hello world

Khi bắt đầu với một ngôn ngữ lập trình hoặc công nghệ mới, thông thường bạn sẽ tạo một ứng dụng 'Hello World' - một ứng dụng nhỏ xuất ra văn bản như `"Hello World"` để kiểm tra xem tất cả các công cụ đã được cấu hình đúng chưa.

Ứng dụng Hello World cho phần cứng IoT ảo sẽ đảm bảo rằng bạn đã cài đặt Python và Visual Studio Code đúng cách. Nó cũng sẽ kết nối với CounterFit để sử dụng các cảm biến và bộ truyền động IoT ảo. Ứng dụng này sẽ không sử dụng phần cứng thực, chỉ kết nối để kiểm tra mọi thứ hoạt động.

Ứng dụng này sẽ nằm trong một thư mục có tên `nightlight`, và sẽ được tái sử dụng với mã khác trong các phần sau của bài tập để xây dựng ứng dụng đèn ngủ.

### Cấu hình môi trường ảo Python

Một trong những tính năng mạnh mẽ của Python là khả năng cài đặt [gói Pip](https://pypi.org) - đây là các gói mã được viết bởi người khác và công bố trên Internet. Bạn có thể cài đặt một gói Pip trên máy tính của mình chỉ với một lệnh, sau đó sử dụng gói đó trong mã của mình. Bạn sẽ sử dụng Pip để cài đặt một gói để giao tiếp với CounterFit.

Theo mặc định, khi bạn cài đặt một gói, nó sẽ có sẵn ở mọi nơi trên máy tính của bạn, và điều này có thể dẫn đến các vấn đề về phiên bản gói - chẳng hạn như một ứng dụng phụ thuộc vào một phiên bản của gói nhưng lại bị lỗi khi bạn cài đặt phiên bản mới cho một ứng dụng khác. Để giải quyết vấn đề này, bạn có thể sử dụng [môi trường ảo Python](https://docs.python.org/3/library/venv.html), về cơ bản là một bản sao của Python trong một thư mục riêng biệt, và khi bạn cài đặt các gói Pip, chúng chỉ được cài đặt trong thư mục đó.

> 💁 Nếu bạn đang sử dụng Raspberry Pi, bạn không cần thiết lập môi trường ảo trên thiết bị đó để quản lý các gói Pip, thay vào đó bạn sử dụng các gói toàn cục, vì các gói Grove được cài đặt toàn cục bởi tập lệnh cài đặt.

#### Nhiệm vụ - cấu hình môi trường ảo Python

Cấu hình môi trường ảo Python và cài đặt các gói Pip cho CounterFit.

1. Từ terminal hoặc dòng lệnh của bạn, chạy lệnh sau tại một vị trí tùy chọn để tạo và điều hướng đến một thư mục mới:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Bây giờ chạy lệnh sau để tạo một môi trường ảo trong thư mục `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Bạn cần gọi rõ ràng `python3` để tạo môi trường ảo trong trường hợp bạn đã cài đặt Python 2 cùng với Python 3 (phiên bản mới nhất). Nếu bạn đã cài đặt Python 2, thì gọi `python` sẽ sử dụng Python 2 thay vì Python 3.

1. Kích hoạt môi trường ảo:

    * Trên Windows:
        * Nếu bạn đang sử dụng Command Prompt hoặc Command Prompt thông qua Windows Terminal, chạy:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Nếu bạn đang sử dụng PowerShell, chạy:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Nếu bạn gặp lỗi về việc chạy script bị vô hiệu hóa trên hệ thống này, bạn sẽ cần bật chạy script bằng cách thiết lập chính sách thực thi phù hợp. Bạn có thể làm điều này bằng cách khởi chạy PowerShell với quyền quản trị viên, sau đó chạy lệnh sau:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Nhập `Y` khi được yêu cầu xác nhận. Sau đó khởi chạy lại PowerShell và thử lại.

            Bạn có thể đặt lại chính sách thực thi này sau nếu cần. Bạn có thể đọc thêm về điều này trong [trang Chính sách thực thi trên Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Trên macOS hoặc Linux, chạy:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Các lệnh này nên được chạy từ cùng vị trí mà bạn đã chạy lệnh để tạo môi trường ảo. Bạn sẽ không bao giờ cần điều hướng vào thư mục `.venv`, bạn chỉ cần chạy lệnh kích hoạt và bất kỳ lệnh nào để cài đặt gói hoặc chạy mã từ thư mục bạn đã ở khi tạo môi trường ảo.

1. Khi môi trường ảo đã được kích hoạt, lệnh `python` mặc định sẽ chạy phiên bản Python được sử dụng để tạo môi trường ảo. Chạy lệnh sau để kiểm tra phiên bản:

    ```sh
    python --version
    ```

    Kết quả đầu ra sẽ chứa:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Phiên bản Python của bạn có thể khác - miễn là nó từ phiên bản 3.6 trở lên thì bạn ổn. Nếu không, hãy xóa thư mục này, cài đặt phiên bản Python mới hơn và thử lại.

1. Chạy các lệnh sau để cài đặt các gói Pip cho CounterFit. Các gói này bao gồm ứng dụng chính CounterFit cũng như các shims cho phần cứng Grove. Các shims này cho phép bạn viết mã như thể bạn đang lập trình sử dụng các cảm biến và bộ truyền động vật lý từ hệ sinh thái Grove nhưng được kết nối với các thiết bị IoT ảo.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Các gói pip này sẽ chỉ được cài đặt trong môi trường ảo và sẽ không khả dụng bên ngoài môi trường này.

### Viết mã

Khi môi trường ảo Python đã sẵn sàng, bạn có thể viết mã cho ứng dụng 'Hello World'.

#### Nhiệm vụ - viết mã

Tạo một ứng dụng Python để in `"Hello World"` ra console.

1. Từ terminal hoặc dòng lệnh của bạn, chạy lệnh sau bên trong môi trường ảo để tạo một tệp Python có tên `app.py`:

    * Trên Windows, chạy:

        ```cmd
        type nul > app.py
        ```

    * Trên macOS hoặc Linux, chạy:

        ```cmd
        touch app.py
        ```

1. Mở thư mục hiện tại trong VS Code:

    ```sh
    code .
    ```

    > 💁 Nếu terminal của bạn trả về `command not found` trên macOS, điều đó có nghĩa là VS Code chưa được thêm vào PATH của bạn. Bạn có thể thêm VS Code vào PATH bằng cách làm theo hướng dẫn trong [phần Khởi chạy từ dòng lệnh trong tài liệu VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) và chạy lại lệnh sau đó. VS Code được thêm vào PATH theo mặc định trên Windows và Linux.

1. Khi VS Code khởi chạy, nó sẽ kích hoạt môi trường ảo Python. Môi trường ảo được chọn sẽ xuất hiện trong thanh trạng thái dưới cùng:

    ![VS Code hiển thị môi trường ảo được chọn](../../../../../translated_images/vi/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Nếu Terminal của VS Code đã chạy khi VS Code khởi động, nó sẽ không có môi trường ảo được kích hoạt. Cách dễ nhất là tắt terminal bằng nút **Kill the active terminal instance**:

    ![Nút Kill the active terminal instance của VS Code](../../../../../translated_images/vi/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Bạn có thể biết terminal đã kích hoạt môi trường ảo hay chưa bằng cách kiểm tra tên của môi trường ảo có xuất hiện làm tiền tố trên prompt của terminal hay không. Ví dụ, nó có thể là:

    ```sh
    (.venv) ➜  nightlight
    ```

    Nếu bạn không thấy `.venv` làm tiền tố trên prompt, môi trường ảo không được kích hoạt trong terminal.

1. Khởi chạy một terminal mới trong VS Code bằng cách chọn *Terminal -> New Terminal*, hoặc nhấn `` CTRL+` ``. Terminal mới sẽ tải môi trường ảo, và lệnh kích hoạt sẽ xuất hiện trong terminal. Prompt cũng sẽ có tên của môi trường ảo (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Mở tệp `app.py` từ trình khám phá của VS Code và thêm mã sau:

    ```python
    print('Hello World!')
    ```

    Hàm `print` sẽ in bất kỳ nội dung nào được truyền vào nó ra console.

1. Từ terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python app.py
    ```

    Kết quả đầu ra sẽ là:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Chương trình 'Hello World' của bạn đã thành công!

### Kết nối 'phần cứng'

Như một bước 'Hello World' thứ hai, bạn sẽ chạy ứng dụng CounterFit và kết nối mã của mình với nó. Đây là tương đương ảo của việc cắm phần cứng IoT vào một bộ phát triển.

#### Nhiệm vụ - kết nối 'phần cứng'

1. Từ terminal của VS Code, khởi chạy ứng dụng CounterFit bằng lệnh sau:

    ```sh
    counterfit
    ```

    Ứng dụng sẽ bắt đầu chạy và mở trong trình duyệt web của bạn:

    ![Ứng dụng Counter Fit chạy trong trình duyệt](../../../../../translated_images/vi/counterfit-first-run.433326358b669b31.webp)

    Nó sẽ được đánh dấu là *Disconnected*, với đèn LED ở góc trên bên phải tắt.

1. Thêm mã sau vào đầu tệp `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Mã này nhập lớp `CounterFitConnection` từ module `counterfit_connection`, được cung cấp bởi gói pip `counterfit-connection` mà bạn đã cài đặt trước đó. Sau đó, nó khởi tạo một kết nối đến ứng dụng CounterFit đang chạy trên `127.0.0.1`, đây là một địa chỉ IP bạn luôn có thể sử dụng để truy cập máy tính cục bộ của mình (thường được gọi là *localhost*), trên cổng 5000.

    > 💁 Nếu bạn có các ứng dụng khác đang chạy trên cổng 5000, bạn có thể thay đổi điều này bằng cách cập nhật cổng trong mã và chạy CounterFit bằng `CounterFit --port <port_number>`, thay `<port_number>` bằng cổng bạn muốn sử dụng.

1. Bạn sẽ cần khởi chạy một terminal mới trong VS Code bằng cách chọn nút **Create a new integrated terminal**. Điều này là do ứng dụng CounterFit đang chạy trong terminal hiện tại.

    ![Nút Create a new integrated terminal của VS Code](../../../../../translated_images/vi/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Trong terminal mới này, chạy tệp `app.py` như trước. Trạng thái của CounterFit sẽ thay đổi thành **Connected** và đèn LED sẽ sáng lên.

    ![Counter Fit hiển thị trạng thái đã kết nối](../../../../../translated_images/vi/counterfit-connected.ed30b46d8f79b092.webp)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Kết nối của bạn với phần cứng đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.