<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-07T01:42:32+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "pcm"
}
-->
# Raspberry Pi Troubleshooting Guide

Dis guide dey provide solutions to common wahala wey fit show wen you dey run IoT projects for Raspberry Pi devices.  
E design for beginners wey dey follow the IoT-For-Beginners curriculum, but e still dey useful for general Pi development.

---

## 1. Installation & Dependency Errors

### ❗ `ModuleNotFoundError: No module named 'xyz'`
Dis one dey happen wen required Python modules no install.

**Fix**
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
**Disclaimer**:
Dis document na wen AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) translate am. Even though we try make e correct well, abeg make you sabi say automated translation fit get error or wahala. Di original document wey e dey dia for im own language na di correct one. For important matter dem, better make person wey sabi human translation do am. We no go responsible if any misunderstanding or wrong meaning show because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->