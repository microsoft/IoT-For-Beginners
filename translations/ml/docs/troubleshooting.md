<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-07T01:42:56+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "ml"
}
-->
# Raspberry Pi പ്രശ്‌നപരിഹാര മാർഗ്ഗദർശി

ഈ മാർഗ്ഗദർശി Raspberry Pi ഉപകരണങ്ങളിലെ IoT പ്രൊജക്റ്റുകൾ പ്രവർത്തിപ്പിക്കുമ്പോൾ ഉണ്ടാകുന്ന സാധാരണ പ്രശ്‌നങ്ങൾക്കുള്ള പരിഹാരങ്ങൾ നൽകുന്നു.  
ഇത് IoT-For-Beginners പാഠ്യപദ്ധതി പിന്തുടരുന്ന തുടക്കക്കാർക്ക് രൂപകൽപ്പന ചെയ്തതാണെങ്കിലും, പൊതുവായ Pi വികസനത്തിനും ഇത് ഉപകാരപ്രദമാണ്.

---

## 1. ഇൻസ്റ്റളേഷൻ & ഡിപ്പൻഡൻസി പിശകുകൾ

### ❗ `ModuleNotFoundError: No module named 'xyz'`
ആവശ്യമായ Python മാഡ്യൂളുകൾ ഇൻസ്റ്റാൾ ചെയ്തിട്ടില്ലെങ്കിൽ ഇത് നടക്കും.

**പരിഹാരം**
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
**അസത്യവാഗ്ദാനം**:  
ഈ പ്രമാണം എ.ഐ. ഭാഷാന്തര സേവനമായ [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് ഭാഷാന്തരപ്പെടുത്തി. നാം കൃത്യതയ്ക്കായി ശ്രമിച്ചിട്ടുണ്ടെങ്കിലും, സ്വയംഭാഷാന്തരങ്ങളിൽ പിഴവുകൾ അല്ലെങ്കിൽ അസത്യതകൾ ഉണ്ടാകാനാണ് സാധ്യത. അടിയന്തര വിവരങ്ങൾക്ക്, പ്രൊഫഷണൽ മനുഷ്യൻകൂടെയുള്ള ഭാഷാന്തരം നിർദേശിക്കുന്നു. ഈ ഭാഷാന്തരത്തിന്റെ ഉപയോഗം മൂലം ഉണ്ടാവുന്ന തെറ്റിദ്ധാരണകൾക്കോ തെറ്റായ വ്യാഖ്യാനങ്ങളിലേക്കോ ഞങ്ങൾ ഉത്തരവാദിത്വമുള്ളവർ കണക്കാക്കപ്പെടുകയില്ല.  
അസൽ പ്രമാണം അതിന്റെ മാതൃഭാഷയിൽ തന്നെ വിശ്വാസയോഗ്യ സ്രോതസ്സായി പരിഗണിക്കേണ്ടതാണ്.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->