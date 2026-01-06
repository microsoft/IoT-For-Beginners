<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-06T10:16:16+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "vi"
}
-->
# Hướng Dẫn Khắc Phục Sự Cố Raspberry Pi

Hướng dẫn này cung cấp giải pháp cho các sự cố phổ biến gặp phải khi chạy các dự án IoT trên thiết bị Raspberry Pi.  
Nó được thiết kế dành cho người mới bắt đầu theo chương trình IoT-For-Beginners, nhưng cũng hữu ích cho phát triển Pi nói chung.

---

## 1. Lỗi Cài Đặt & Phụ Thuộc

### ❗ `ModuleNotFoundError: No module named 'xyz'`
Điều này xảy ra khi các mô-đun Python cần thiết chưa được cài đặt.

**Khắc phục**
```bash
pip3 install <module_name>

 Permission denied when running scripts

Often caused by accessing GPIO, I2C or system hardware without elevated privileges.
Quick fix:
sudo python3 script.py

Recommended fix (no sudo needed every time):
sudo usermod -aG gpio,i2c,spi $USER
sudo reboot

2. GPIO / I2C / SPI Not Working
❗ RuntimeError: No access to GPIO

Add user to GPIO group:
sudo usermod -aG gpio $USER
sudo reboot

❗ I2C / SPI devices not detected

Enable interfaces:
sudo raspi-config
→ Interface Options
→ Enable I2C / Enable SPI

Check if I2C device appears:
i2cdetect -y 1

3. Camera / Video Issues
❗ Camera not detected or fails to start

Enable camera interface:
sudo raspi-config
→ Interface Options → Camera → Enable
sudo reboot

Check if camera is visible:
vcgencmd get_camera

4. Wi-Fi / SSH / Connectivity Problems
| Problem                          | Fix                                           |
| -------------------------------- | --------------------------------------------- |
| SSH connection refused           | `sudo raspi-config → Interface Options → SSH` |
| Device not showing on network    | Check IP using: `hostname -I`                 |
| Slow Wi-Fi / unstable connection | Prefer 2.4 GHz band, update OS                |
| Unable to access Pi headless     | Add `ssh` file to boot partition              |


5. Performance Issues
Raspberry Pi running slow / laggy

Close unused applications

Reduce background services

Use Lite OS if no desktop needed

Ensure sufficient power supply (5V/3A or better)

Check CPU load:
top
htop

Storage issues:
sudo apt autoremove
sudo apt clean
df -h

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Tuyên bố từ chối trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ nguyên bản nên được xem là nguồn thông tin chính xác nhất. Đối với những thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm về bất kỳ hiểu lầm hoặc sai lệch nào phát sinh từ việc sử dụng bản dịch này.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->