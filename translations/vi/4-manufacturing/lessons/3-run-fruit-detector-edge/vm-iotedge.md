<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T21:12:41+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "vi"
}
-->
# Tạo máy ảo chạy IoT Edge

Trong Azure, bạn có thể tạo một máy ảo - một máy tính trên đám mây mà bạn có thể cấu hình theo ý muốn và chạy phần mềm của riêng mình trên đó.

> 💁 Bạn có thể đọc thêm về máy ảo trên [trang Wikipedia về Máy ảo](https://wikipedia.org/wiki/Virtual_machine).

## Nhiệm vụ - Thiết lập máy ảo IoT Edge

1. Chạy lệnh sau để tạo một máy ảo đã được cài đặt sẵn Azure IoT Edge:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Thay thế `<vm_name>` bằng tên cho máy ảo này. Tên này cần phải là duy nhất trên toàn cầu, vì vậy hãy sử dụng một cái gì đó như `fruit-quality-detector-vm-` kèm theo tên của bạn hoặc một giá trị khác ở cuối.

    Thay thế `<username>` và `<password>` bằng tên người dùng và mật khẩu để đăng nhập vào máy ảo. Những thông tin này cần phải tương đối an toàn, vì vậy bạn không thể sử dụng admin/password.

    Thay thế `<connection_string>` bằng chuỗi kết nối của thiết bị IoT Edge `fruit-quality-detector-edge` của bạn.

    Lệnh này sẽ tạo một máy ảo được cấu hình là máy ảo loại `DS1 v2`. Các loại này cho biết mức độ mạnh mẽ của máy, và do đó chi phí của nó. Máy ảo này có 1 CPU và 3.5GB RAM.

    > 💰 Bạn có thể xem giá hiện tại của các máy ảo này trên [hướng dẫn giá máy ảo Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Sau khi máy ảo được tạo, runtime IoT Edge sẽ được cài đặt tự động và cấu hình để kết nối với IoT Hub của bạn dưới dạng thiết bị `fruit-quality-detector-edge`.

1. Bạn sẽ cần địa chỉ IP hoặc tên DNS của máy ảo để gọi trình phân loại hình ảnh từ đó. Chạy lệnh sau để lấy thông tin này:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Sao chép giá trị của trường `PublicIps` hoặc trường `Fqdns`.

1. Máy ảo tốn tiền. Tại thời điểm viết bài, một máy DS1 VM có giá khoảng $0.06 mỗi giờ. Để giảm chi phí, bạn nên tắt máy ảo khi không sử dụng và xóa nó khi hoàn thành dự án này.

    Bạn có thể cấu hình máy ảo của mình để tự động tắt vào một thời điểm nhất định mỗi ngày. Điều này có nghĩa là nếu bạn quên tắt máy, bạn sẽ không bị tính phí nhiều hơn thời gian cho đến khi máy tự động tắt. Sử dụng lệnh sau để thiết lập:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Thay thế `<vm_name>` bằng tên của máy ảo của bạn.

    Thay thế `<shutdown_time_utc>` bằng thời gian UTC mà bạn muốn máy ảo tắt, sử dụng 4 chữ số dưới dạng HHMM. Ví dụ, nếu bạn muốn tắt vào nửa đêm UTC, bạn sẽ đặt giá trị này là `0000`. Đối với 7:30PM ở bờ Tây Hoa Kỳ, bạn sẽ sử dụng 0230 (7:30PM ở bờ Tây Hoa Kỳ là 2:30AM UTC).

1. Trình phân loại hình ảnh của bạn sẽ chạy trên thiết bị edge này, lắng nghe trên cổng 80 (cổng HTTP tiêu chuẩn). Theo mặc định, các máy ảo có các cổng inbound bị chặn, vì vậy bạn sẽ cần mở cổng 80. Các cổng được mở trên các nhóm bảo mật mạng, vì vậy trước tiên bạn cần biết tên của nhóm bảo mật mạng cho máy ảo của mình, mà bạn có thể tìm thấy bằng lệnh sau:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Sao chép giá trị của trường `Name`.

1. Chạy lệnh sau để thêm một quy tắc mở cổng 80 cho nhóm bảo mật mạng:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Thay thế `<nsg name>` bằng tên nhóm bảo mật mạng từ bước trước.

### Nhiệm vụ - quản lý máy ảo để giảm chi phí

1. Khi bạn không sử dụng máy ảo của mình, bạn nên tắt nó. Để tắt máy ảo, sử dụng lệnh sau:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Thay thế `<vm_name>` bằng tên của máy ảo của bạn.

    > 💁 Có một lệnh `az vm stop` sẽ dừng máy ảo, nhưng nó vẫn giữ máy tính được phân bổ cho bạn, vì vậy bạn vẫn phải trả phí như thể nó vẫn đang chạy.

1. Để khởi động lại máy ảo, sử dụng lệnh sau:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Thay thế `<vm_name>` bằng tên của máy ảo của bạn.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.