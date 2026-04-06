# មគ្គុទេសក៍ការដោះស្រាយបញ្ហា Raspberry Pi

មគ្គុទេសក៍នេះផ្តល់នូវដំណោះស្រាយសម្រាប់បញ្ហាទូទៅដែលបានជួបប្រទៈក្នុងការប្រតិបត្ដិគម្រោង IoT លើឧបករណ៍ Raspberry Pi។  
វាត្រូវបានរចនាសម្រាប់អ្នកចាប់ផ្ដើមដែលតាមដានមេរៀន IoT-For-Beginners ប៉ុន្តែវាក៏មានប្រយោជន៍សម្រាប់ការអភិវឌ្ឍ Pi ជាទូទៅផងដែរ។

---

## 1. កំហុសក្នុងការដំឡើង និងការទាមទារ

### ❗ `ModuleNotFoundError: No module named 'xyz'`
នេះកើតឡើងពេលម៉ូឌុល Python ត្រូវការមិនត្រូវបានដំឡើង។

**ដំណោះស្រាយ**
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
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខិតខំដើម្បីរក្សា ភាពត្រឹមត្រូវ សូមព្យាយាមយកចិត្តទុកដាក់ទៅថាការបកប្រែដោយស្វ័យប្រវត្តិនេះអាចមានកំហុស ឬភាពមិនត្រឹមត្រូវ។ ឯកសារដើមក្នុងភាសាតំបន់របស់វាគួរត្រូវបានយកឲ្យជាតំណលទ្ធផលផ្លូវការជាទីបំផុត។ សម្រាប់ព័ត៌មានសំខាន់ៗ គួរតែប្រើការបកប្រែដោយមនុស្សជំនាញ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកប្រែខុសរៀងịa រាក់ទាក់ពីការប្រើប្រាស់ការបកប្រែនេះឡើយ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->