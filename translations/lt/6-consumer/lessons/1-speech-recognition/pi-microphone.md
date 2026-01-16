<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-28T19:26:55+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "lt"
}
-->
# Konfigūruokite mikrofoną ir garsiakalbius - Raspberry Pi

Šioje pamokos dalyje pridėsite mikrofoną ir garsiakalbius prie savo Raspberry Pi.

## Aparatūra

Raspberry Pi reikalingas mikrofonas.

Pi neturi integruoto mikrofono, todėl jums reikės pridėti išorinį mikrofoną. Tai galima padaryti keliais būdais:

* USB mikrofonas
* USB ausinės su mikrofonu
* USB viskas viename garsiakalbis su mikrofonu
* USB garso adapteris ir mikrofonas su 3,5 mm jungtimi
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth mikrofonai ne visi palaikomi Raspberry Pi, todėl jei turite Bluetooth mikrofoną ar ausines, gali kilti problemų sujungiant arba įrašant garsą.

Raspberry Pi turi 3,5 mm ausinių jungtį. Galite ją naudoti prijungdami ausines, ausines su mikrofonu arba garsiakalbį. Taip pat galite pridėti garsiakalbius naudodami:

* HDMI garso išvestį per monitorių ar televizorių
* USB garsiakalbius
* USB ausines su mikrofonu
* USB viskas viename garsiakalbis su mikrofonu
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) su prijungtu garsiakalbiu, arba per 3,5 mm jungtį, arba per JST jungtį

## Prijunkite ir konfigūruokite mikrofoną ir garsiakalbius

Mikrofonas ir garsiakalbiai turi būti prijungti ir sukonfigūruoti.

### Užduotis - prijunkite ir konfigūruokite mikrofoną

1. Prijunkite mikrofoną naudodami tinkamą metodą. Pavyzdžiui, prijunkite jį per vieną iš USB jungčių.

1. Jei naudojate ReSpeaker 2-Mics Pi HAT, galite nuimti Grove bazinę plokštę ir uždėti ReSpeaker plokštę jos vietoje.

    ![Raspberry Pi su ReSpeaker plokšte](../../../../../translated_images/lt/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Vėliau šioje pamokoje jums reikės Grove mygtuko, tačiau vienas jau yra integruotas šioje plokštėje, todėl Grove bazinė plokštė nereikalinga.

    Kai plokštė bus pritvirtinta, jums reikės įdiegti keletą tvarkyklių. Žr. [Seeed pradinės instrukcijos](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) tvarkyklių diegimo instrukcijoms.

    > ⚠️ Instrukcijose naudojamas `git`, kad būtų galima klonuoti saugyklą. Jei jūsų Pi nėra įdiegta `git`, galite ją įdiegti vykdydami šią komandą:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Paleiskite šią komandą savo terminale, arba tiesiogiai Pi, arba prisijungę per VS Code ir nuotolinę SSH sesiją, kad pamatytumėte informaciją apie prijungtą mikrofoną:

    ```sh
    arecord -l
    ```

    Pamatysite prijungtų mikrofonų sąrašą. Jis atrodys maždaug taip:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Jei turite tik vieną mikrofoną, turėtumėte matyti tik vieną įrašą. Mikrofonų konfigūravimas Linux sistemoje gali būti sudėtingas, todėl geriausia naudoti tik vieną mikrofoną ir atjungti kitus.

    Užsirašykite kortelės numerį, nes jo prireiks vėliau. Aukščiau pateiktame išvestyje kortelės numeris yra 1.

### Užduotis - prijunkite ir konfigūruokite garsiakalbį

1. Prijunkite garsiakalbius naudodami tinkamą metodą.

1. Paleiskite šią komandą savo terminale, arba tiesiogiai Pi, arba prisijungę per VS Code ir nuotolinę SSH sesiją, kad pamatytumėte informaciją apie prijungtus garsiakalbius:

    ```sh
    aplay -l
    ```

    Pamatysite prijungtų garsiakalbių sąrašą. Jis atrodys maždaug taip:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Visada matysite `card 0: Headphones`, nes tai yra integruota ausinių jungtis. Jei pridėjote papildomus garsiakalbius, tokius kaip USB garsiakalbis, jie taip pat bus rodomi sąraše.

1. Jei naudojate papildomą garsiakalbį, o ne garsiakalbį ar ausines, prijungtas prie integruotos ausinių jungties, turite jį sukonfigūruoti kaip numatytąjį. Norėdami tai padaryti, paleiskite šią komandą:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Tai atidarys konfigūracijos failą `nano`, terminalo pagrindu veikiančiame teksto redaktoriuje. Slinkite žemyn naudodami rodyklių klavišus klaviatūroje, kol rasite šią eilutę:

    ```output
    defaults.pcm.card 0
    ```

    Pakeiskite reikšmę iš `0` į kortelės numerį, kurį norite naudoti iš sąrašo, gauto iš `aplay -l` komandos. Pavyzdžiui, aukščiau pateiktame išvestyje yra antra garso kortelė, vadinama `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, naudojanti kortelę 1. Norėdami ją naudoti, atnaujinsiu eilutę taip:

    ```output
    defaults.pcm.card 1
    ```

    Nustatykite šią reikšmę tinkamam kortelės numeriui. Galite naršyti iki numerio naudodami rodyklių klavišus klaviatūroje, tada ištrinti ir įvesti naują numerį kaip įprasta redaguojant tekstinius failus.

1. Išsaugokite pakeitimus ir uždarykite failą paspausdami `Ctrl+x`. Paspauskite `y`, kad išsaugotumėte failą, tada `return`, kad patvirtintumėte failo pavadinimą.

### Užduotis - išbandykite mikrofoną ir garsiakalbį

1. Paleiskite šią komandą, kad įrašytumėte 5 sekundes garso per mikrofoną:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Kol ši komanda veikia, skleiskite garsą į mikrofoną, pavyzdžiui, kalbėdami, dainuodami, beatboxindami, grodami instrumentu ar kaip tik norite.

1. Po 5 sekundžių įrašymas sustos. Paleiskite šią komandą, kad atkurtumėte garsą:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Išgirsite garsą, atkuriamą per garsiakalbius. Jei reikia, sureguliuokite garsiakalbio išvesties garsumą.

1. Jei reikia sureguliuoti integruotos mikrofono jungties garsumą arba mikrofono stiprinimą, galite naudoti `alsamixer` įrankį. Daugiau apie šį įrankį galite perskaityti [Linux alsamixer man puslapyje](https://linux.die.net/man/1/alsamixer).

1. Jei gaunate klaidų atkuriant garsą, patikrinkite kortelę, kurią nustatėte kaip `defaults.pcm.card` `alsa.conf` faile.

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, kylančius dėl šio vertimo naudojimo.