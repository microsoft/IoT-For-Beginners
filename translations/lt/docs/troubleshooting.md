<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-06T21:49:20+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "lt"
}
-->
# Raspberry Pi trikčių šalinimo vadovas

Šiame vadove pateikiami sprendimai dažniausiai pasitaikančioms problemoms, susiduriant su IoT projektais Raspberry Pi įrenginiuose.  
Jis skirtas pradedantiesiems, kurie seka IoT-For-Beginners mokymo programą, tačiau taip pat yra naudingas bendram Pi vystymui.

---

## 1. Diegimo ir priklausomybių klaidos

### ❗ `ModuleNotFoundError: No module named 'xyz'`
Tai nutinka, kai reikalingi Python moduliai nėra įdiegti.

**Sprendimas**
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
**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Esant kritinei informacijai rekomenduojamas profesionalus žmogaus vertimas. Mes neprisiimame atsakomybės už bet kokius nesusipratimus ar neteisingus interpretavimus, kylančius naudojant šį vertimą.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->