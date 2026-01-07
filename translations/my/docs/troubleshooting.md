<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "271dcd720357806934b2f0d94e19410e",
  "translation_date": "2026-01-06T21:48:53+00:00",
  "source_file": "docs/troubleshooting.md",
  "language_code": "my"
}
-->
# Raspberry Pi ပြဿနာဖြေရှင်းချက်လမ်းညွှန်

ဤလမ်းညွှန်သည် Raspberry Pi စက်ရုပ်များပေါ်တွင် IoT ပရောဂျက်များကို လုပ်ဆောင်စဉ် ကြုံတွေ့ရသည့် ရိုးရိုးရှင်းရှင်းပြဿနာများသို့ ဖြေရှင်းနည်းများကို ပေးဆောင်သည်။  
IoT-For-Beginners သင်ခန်းစာအစီအစဉ်ကို လိုက်နာနေသော စတင်အသုံးပြုသူများအတွက် ရည်ရွယ်ပြီး၊ ပိုင်တီထုတ်လုပ်မှု အများပြည်သူအတွက်လည်း အသုံးဝင်သည်။

---

## ၁။ တပ်ဆင်ခြင်းနှင့် မူဝါဒ အမှားများ

### ❗ `ModuleNotFoundError: No module named 'xyz'`
လိုအပ်သည့် Python မော်ဂျူးများ မတပ်ဆင်ထားသောအခါ ဖြစ်ပေါ်သည်။

**ပြုပြင်နည်း**
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
**ကာကွယ်ချက်**  
ဤစာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ဖြင့် ဘာသာပြန်ထားသည်။ တိကျမှန်ကန်မှုအတွက် ကြိုးစားထားသော်လည်း ပြည့်စုံမှန်ကန်မှုမရှိနိုင်သော အမှားများ ဖြစ်ပေါ်နိုင်ကြောင်း သတိပြုပါရန် မေတ္တာရပ်ခံအပ်ပါသည်။ မူရင်းစာတမ်းကို အသုံးပြုသော ဘာသာစကားဖြင့် ဖြစ်သောကြောင့် အမှန်တကယ် မှန်ကန်သောအရင်းအမြစ်အဖြစ် သတ်မှတ်စဉ်းစားရမည်ဖြစ်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များအား ရှာဖွေဖော်ပြရန် အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုမှုကြောင့် ဖြစ်ပေါ်လာနိုင်သည့် နားမလည်မှုများ သို့မဟုတ် မှားယွင်းအနက်ဖော်ချက်များအတွက် ကျွန်ုပ်တို့သည် တာဝန်မခံနိုင်ပါ။
<!-- CO-OP TRANSLATOR DISCLAIMER END -->