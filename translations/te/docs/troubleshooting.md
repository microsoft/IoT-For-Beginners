<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-07T01:42:43+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "te"
}
-->
# Raspberry Pi సమస్య పరిష్కరణ గైడ్

ఈ గైడ్ Raspberry Pi పరికరాల్లో IoT ప్రాజెక్టులు నడుపుతూ ఎదురయ్యే సాధారణ సమస్యలకు పరిష్కారాలను అందిస్తుంది.  
ఇది IoT-For-Beginners పార్ధకం పాటించే మ nuevosుక్కల కోసం రూపొందించబడినప్పటికీ, సాధారణ Pi అభివృద్ధికి కూడా ఉపయోగకరం.

---

## 1. ఇన్స్టాలేషన్ & ఆధారాలు తప్పిదాలు

### ❗ `ModuleNotFoundError: No module named 'xyz'`
అవసరమైన Python modules ఇన్స్టాల్ చేయబడలేదు గా ఇది జరుగుతుంది.

**పరిష్కారం**
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
**అస్పష్టపరిచాం**:  
ఈ డాక్యుమెంట్‌ను AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మనం సరైన అనువాదానికి ప్రయత్నించినప్పటికీ, ఆటోమేటెడ్ అనువాదాల్లో తప్పులు లేదా అసత్యతలు ఉంటాయని జాగ్రత్త వహించండి. మూల డాక్‌మెంటు దాని స్థానిక భాషలోనే అధికారిక వనరుగా పరిగణించాలి. కీలక సమాచారం కోసం, నిపుణులైన మానవ అనువాదం సిఫార్సు చేయబడుతుంది. ఈ అనువాదం వాడుక వల్ల ఏర్పడిన ఏ విధమైన గందరగోళం లేదా తప్పుగా అర్థం చేసుకోవడంలో మేము బాధ్యత రహితం.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->