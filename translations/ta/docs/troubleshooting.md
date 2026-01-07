<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-07T01:42:10+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "ta"
}
-->
# ரச்பெரி பை பிரச்சனைகளுக்கான வழிகாட்டி

இந்த வழிகாட்டி ரச்பெரி பை சாதனங்களில் ஐஓடி திட்டங்களை இயக்கும் போது ஏற்படும் பொதுவான பிரச்சனைகள் மற்றும் அவற்றுக்கான தீர்வுகளை வழங்குகிறது.  
இது ஐஓடி-பிக்னர்ஸ் பாடத்திட்டத்தை பின்பற்றும் ஆரம்ப நிலை பயனாளர்களுக்காக வடிவமைக்கப்பட்டது, ஆனால் பொதுவான பை வளர்ச்சிக்கு கூட பயனுள்ளதாக உள்ளது.

---

## 1. நிறுவல் மற்றும் சார்பு பிழைகள்

### ❗ `ModuleNotFoundError: No module named 'xyz'`
தேவைப்படும் பைத்தான் தொகுதிகள் நிறுவப்படாத போது இது ஏற்படுகிறது.

**தீர்வு**
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
**பாதுகாப்புத்தகவல்**:  
இந்தக் கடிதம் AI மொழிபெயர்ப்பு சேவை [Co-op Translator](https://github.com/Azure/co-op-translator) மூலம் மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்கு முயன்றாலும், தானாக நடைபெறும் மொழிபெயர்ப்பில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்க வாய்ப்பு உள்ளது என்பதை கவனிக்கவும். தாய்மொழியில் உள்ள மூலக் கடிதத்தையே அதிகாரப்பூர்வமான ஆதாரமாக கருதவேண்டும். முக்கியமான தகவலுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பை பரிந்துரைக்கிறோம். இந்த மொழிபெயர்ப்பின் பயன்பாட்டால் ஏற்படும் ஏதாவது தவறறிதல்கள் அல்லது புரிதல்தவறுகளுக்கு நாங்கள் பொறுப்பல்ல அல்ல.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->