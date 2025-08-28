<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-28T16:03:04+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "my"
}
-->
# IoT Edge အတွက် Virtual Machine တစ်ခု ဖန်တီးခြင်း

Azure တွင် သင့်အလိုက် ပြင်ဆင်နိုင်ပြီး သင့်ရဲ့ software ကို run လို့ရတဲ့ cloud-based computer တစ်ခုဖြစ်တဲ့ virtual machine တစ်ခုကို ဖန်တီးနိုင်ပါတယ်။

> 💁 Virtual machine များအကြောင်းပိုမိုသိရှိလိုပါက [Wikipedia ရှိ Virtual Machine စာမျက်နှာ](https://wikipedia.org/wiki/Virtual_machine) ကို ဖတ်ရှုနိုင်ပါတယ်။

## Task - IoT Edge Virtual Machine တစ်ခုကို Set up လုပ်ခြင်း

1. Azure IoT Edge ကို အလိုအလျောက် ထည့်သွင်းပြီးသား VM တစ်ခု ဖန်တီးရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    `<vm_name>` ကို သင့် VM အတွက် နာမည်တစ်ခုဖြင့် အစားထိုးပါ။ ဤနာမည်သည် တစ်ကမ္ဘာလုံးတွင် ထူးခြားရမည်ဖြစ်သောကြောင့် `fruit-quality-detector-vm-` နောက်တွင် သင့်နာမည် သို့မဟုတ် အခြားတန်ဖိုးတစ်ခု ထည့်သွင်းပါ။

    `<username>` နှင့် `<password>` ကို VM သို့ log in ဝင်ရန် အသုံးပြုမည့် username နှင့် password ဖြင့် အစားထိုးပါ။ ဤအချက်များသည် လုံခြုံမှုရှိရမည်ဖြစ်သောကြောင့် admin/password ကဲ့သို့သော အချက်များကို အသုံးမပြုရပါ။

    `<connection_string>` ကို သင့် `fruit-quality-detector-edge` IoT Edge device ၏ connection string ဖြင့် အစားထိုးပါ။

    ဤ command သည် `DS1 v2` virtual machine အဖြစ် ဖန်တီးမည်ဖြစ်သည်။ ဤ category များသည် machine ၏ စွမ်းဆောင်ရည်နှင့် ကုန်ကျစရိတ်ကို ဖော်ပြသည်။ ဤ VM တွင် 1 CPU နှင့် 3.5GB RAM ပါဝင်သည်။

    > 💰 ဤ VM များ၏ လက်ရှိစျေးနှုန်းကို [Azure Virtual Machine pricing guide](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn) တွင် ကြည့်ရှုနိုင်ပါသည်။

    VM ဖန်တီးပြီးပါက IoT Edge runtime ကို အလိုအလျောက် ထည့်သွင်းပြီး သင့် IoT Hub သို့ `fruit-quality-detector-edge` device အဖြစ် ချိတ်ဆက်ထားမည်ဖြစ်သည်။

1. Image classifier ကို VM မှ ခေါ်ရန် သင့်တွင် VM ၏ IP address သို့မဟုတ် DNS name တစ်ခု လိုအပ်ပါမည်။ ဤအတွက် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    `PublicIps` field သို့မဟုတ် `Fqdns` field ၏ တန်ဖိုးကို ကူးယူပါ။

1. VM များသည် ကုန်ကျစရိတ်ရှိသည်။ ယခုစာရေးချိန်တွင် DS1 VM တစ်ခုသည် တစ်နာရီလျှင် $0.06 ခန့် ကုန်ကျသည်။ ကုန်ကျစရိတ်ကို လျှော့ချရန် သင်အသုံးမပြုသောအခါ VM ကို shutdown လုပ်ပြီး သင့် project ပြီးဆုံးပါက delete လုပ်သင့်သည်။

    VM ကို နေ့စဉ် အချိန်တစ်ခုတွင် အလိုအလျောက် shutdown လုပ်ရန် ပြင်ဆင်နိုင်သည်။ ဤအတွက် အောက်ပါ command ကို အသုံးပြုပါ။

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    `<vm_name>` ကို သင့် VM ၏ နာမည်ဖြင့် အစားထိုးပါ။

    `<shutdown_time_utc>` ကို UTC အချိန်ဖြင့် HHMM အဖြစ် သတ်မှတ်ပါ။ ဥပမာ - UTC အချိန် 12:00AM တွင် shutdown လုပ်လိုပါက `0000` သတ်မှတ်ပါ။ အမေရိကန် အနောက်ဘက်ကမ်းရိုးတန်းအချိန် 7:30PM (UTC 2:30AM) တွင် shutdown လုပ်လိုပါက `0230` သတ်မှတ်ပါ။

1. သင့် image classifier သည် edge device တွင် port 80 (HTTP port) တွင် run လုပ်နေမည်ဖြစ်သည်။ ပုံမှန်အားဖြင့် VM များတွင် inbound ports မဖွင့်ထားသောကြောင့် port 80 ကို ဖွင့်ရန် လိုအပ်ပါမည်။ Ports များကို network security groups တွင် ဖွင့်ထားရမည်ဖြစ်သောကြောင့် အရင်ဆုံး သင့် VM ၏ network security group နာမည်ကို သိရန် အောက်ပါ command ကို အသုံးပြုပါ။

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    `Name` field ၏ တန်ဖိုးကို ကူးယူပါ။

1. Port 80 ကို ဖွင့်ရန် rule တစ်ခု ထည့်ရန် အောက်ပါ command ကို run လုပ်ပါ။

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    `<nsg name>` ကို ယခင်အဆင့်တွင် ရရှိသော network security group နာမည်ဖြင့် အစားထိုးပါ။

### Task - VM ကို စီမံခန့်ခွဲပြီး ကုန်ကျစရိတ်ကို လျှော့ချခြင်း

1. သင့် VM ကို အသုံးမပြုသောအခါ shutdown လုပ်သင့်သည်။ VM ကို shutdown လုပ်ရန် အောက်ပါ command ကို အသုံးပြုပါ။

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    `<vm_name>` ကို သင့် VM ၏ နာမည်ဖြင့် အစားထိုးပါ။

    > 💁 `az vm stop` command တစ်ခုလည်း ရှိပါသည်။ သို့သော် ဤ command သည် VM ကို ရပ်တန့်ပေမည့် computer ကို သင့်အတွက် ထိန်းထားမည်ဖြစ်သောကြောင့် run လျှက်ရှိသကဲ့သို့ ကုန်ကျစရိတ်ရှိပါမည်။

1. VM ကို ပြန်လည်စတင်ရန် အောက်ပါ command ကို အသုံးပြုပါ။

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    `<vm_name>` ကို သင့် VM ၏ နာမည်ဖြင့် အစားထိုးပါ။

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွတ်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။