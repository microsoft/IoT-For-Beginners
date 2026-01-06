<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-05T22:08:11+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "ne"
}
-->
# Raspberry Pi समस्या समाधान गाइड

यस गाइडले Raspberry Pi उपकरणमा IoT परियोजनाहरू सञ्चालन गर्दा सामना हुने सामान्य समस्याहरूको समाधान प्रदान गर्दछ।  
यो IoT-For-Beginners पाठ्यक्रम पछ्याउने शुरुआतीहरूका लागि डिजाइन गरिएको हो, तर सामान्य Pi विकासका लागि पनि उपयोगी छ।

---

## 1. स्थापना र निर्भरता त्रुटिहरू

### ❗ `ModuleNotFoundError: No module named 'xyz'`
जब आवश्यक Python मोड्युलहरू स्थापना नगरिएका हुन्छन्, यो समस्या हुन्छ।

**समाधान**
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
**अस्वीकरण**:
यो कागजात AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) मार्फत अनुवाद गरिएको हो। हामी सटीकताको प्रयास गर्छौं, तथापि कृत्रिम अनुवादमा त्रुटि वा गलतिहरू हुन सक्ने सम्भावना हुन्छ। मूल कागजातलाई यसको स्वदेशी भाषामा अधिकारिक स्रोतको रूपमा विचार गर्नुपर्छ। महत्वपूर्ण जानकारीका लागि, व्यावसायिक मानवीय अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न कुनै पनि गलतफहमी वा गलत व्याख्याका लागि हामी जिम्मेवार छैनौं।
<!-- CO-OP TRANSLATOR DISCLAIMER END -->