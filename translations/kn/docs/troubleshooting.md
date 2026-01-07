<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-07T01:43:09+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "kn"
}
-->
# ರಾಸ್ಪ್ಬೆರಿ ಪೈ ಸಮಸ್ಯೆ ಪರಿಹಾರ ಮಾರ್ಗದರ್ಶಿ

ಈ ಮಾರ್ಗದರ್ಶಿ ರಾಸ್ಪ್ಬೆರಿ ಪೈ ಸಾಧನಗಳಲ್ಲಿ ಐಒಟಿ ಯೋಜನೆಗಳನ್ನು ನಡೆಸುವಾಗ ಎದುರಾಗುವ ಸಾಮಾನ್ಯ ಸಮಸ್ಯೆಗಳಿಗೆ ಪರಿಹಾರಗಳನ್ನು ಒದಗಿಸುತ್ತದೆ.  
ಇದು ಐಒಟಿ-ಫಾರ್-ಬಿಗಿನರ್ಸ್ ಪಠ್ಯಕ್ರಮವನ್ನು ಅನುಸರಿಸುವಆರಂಭಿಕರಿಗಾಗಿ ರೂಪಿಸಲಾಗಿದೆ, ಆದರೆ ಸಾಮಾನ್ಯ ಪೈ ಅಭಿವೃದ್ಧಿಗಾಗಿ ಸಹ ಉಪಯುಕ್ತವಾಗಿದೆ.

---

## 1. ಸ್ಥಾಪನೆ ಮತ್ತು ಅವಲಂಬನೆಯ ದೋಷಗಳು

### ❗ `ModuleNotFoundError: No module named 'xyz'`
ಬೇಕಾದ ಪೈಥಾನ್ ಮೊಡ್ಯೂಲ್‌ಗಳು ಸ್ಥಾಪಿತವಾಗದಿದ್ದಾಗ ಇದು ಸಂಭವಿಸುತ್ತದೆ.

**ಪರಿಹಾರ**
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
**ಕಾರ್ಯದೃಢತಾ ಸೂಚನೆ**:
ಈ ದಸ್ತಾವೇಜು AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಉಪಯೋಗಿಸಿ ಅನುವದಿಸಲಾಗಿದೆ. ನಾವು ತೊಂದರೆರಹಿತ ಶುದ್ಧತೆಯನ್ನು ಸಾಧಿಸಲು ಪ್ರಯತ್ನಿಸುತ್ತೇವೆ ಎಂದು ಸೋಂಕಿಕೊಂಡಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ದೋಷಗಳು ಅಥವಾ ಅಸತ್ಯತೆಗಳಿರಬಹುದು ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯ ಮೂಲ ದಸ್ತಾವೇಜನ್ನು ಅಧಿಕೃತ ಮೂಲ ಎಂದು ಪರಿಗಣಿಸಬೇಕು. ಗಂಭೀರ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗಿದೆ. ಈ ಅನುವಾದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ತಪ್ಪು ತಿಳುವಳಿಕೆ ಅಥವಾ ತಪ್ಪಾಗಿ ಅರ್ಥಮಾಡಿಕೊಳ್ಳುವುದಕ್ಕಾಗಿ ನಾವು ಜವಾಬ್ದಾರರಾಗಿರುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->