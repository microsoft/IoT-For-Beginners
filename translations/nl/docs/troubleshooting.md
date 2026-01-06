<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-06T10:15:53+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "nl"
}
-->
# Raspberry Pi Problemen Oplossen Gids

Deze gids biedt oplossingen voor veelvoorkomende problemen bij het uitvoeren van IoT-projecten op Raspberry Pi-apparaten.  
Het is ontworpen voor beginners die de IoT-For-Beginners-curriculum volgen, maar is ook nuttig voor algemene Pi-ontwikkeling.

---

## 1. Installatie- & Afhankelijkheidsfouten

### ❗ `ModuleNotFoundError: No module named 'xyz'`
Dit gebeurt wanneer vereiste Python-modules niet zijn geïnstalleerd.

**Oplossen**
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
**Vrijwaring**:
Dit document is vertaald met behulp van de AI-vertalingsdienst [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u er rekening mee te houden dat automatische vertalingen fouten of onjuistheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt een professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor enige misverstanden of verkeerde interpretaties voortvloeiend uit het gebruik van deze vertaling.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->