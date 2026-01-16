<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-28T12:25:03+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "sl"
}
-->
# Preverjanje kakovosti sadja z IoT napravo

![Sketchnote pregled te lekcije](../../../../../translated_images/sl/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote avtorja [Nitya Narasimhan](https://github.com/nitya). Kliknite sliko za večjo različico.

## Kviz pred predavanjem

[Kviz pred predavanjem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Uvod

V prejšnji lekciji ste se naučili o klasifikatorjih slik in kako jih naučiti prepoznavati dobro in slabo sadje. Da bi ta klasifikator slik uporabili v IoT aplikaciji, morate biti sposobni zajeti sliko s kamero in jo poslati v oblak za klasifikacijo.

V tej lekciji se boste naučili o senzorjih kamer in kako jih uporabiti z IoT napravo za zajem slike. Prav tako se boste naučili, kako poklicati klasifikator slik iz vaše IoT naprave.

V tej lekciji bomo obravnavali:

* [Senzorje kamer](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Zajem slike z IoT napravo](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Objava vašega klasifikatorja slik](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klasifikacija slik z vaše IoT naprave](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Izboljšanje modela](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Senzorji kamer

Senzorji kamer, kot že ime pove, so kamere, ki jih lahko povežete z vašo IoT napravo. Lahko zajamejo statične slike ali snemajo video. Nekateri vrnejo surove podatke slike, drugi pa stisnejo podatke v slikovno datoteko, kot je JPEG ali PNG. Kamere, ki delujejo z IoT napravami, so običajno manjše in imajo nižjo ločljivost, kot ste jih vajeni, vendar lahko dobite tudi kamere z visoko ločljivostjo, ki se lahko kosajo z najboljšimi telefoni. Na voljo so različne zamenljive leče, večkamerne nastavitve, infrardeče termalne kamere ali UV kamere.

![Svetloba iz prizora prehaja skozi lečo in se osredotoči na CMOS senzor](../../../../../translated_images/sl/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Večina senzorjev kamer uporablja slikovne senzorje, kjer je vsak piksel fotodioda. Leča osredotoči sliko na slikovni senzor, tisoče ali milijone fotodiod pa zazna svetlobo, ki pada nanje, in jo zabeleži kot podatke o pikslih.

> 💁 Leče obrnejo slike, senzor kamere pa nato sliko obrne nazaj v pravilno smer. Enako se dogaja v vaših očeh – kar vidite, je zaznano obrnjeno na zadnji strani očesa, vaš možgani pa to popravijo.

> 🎓 Slikovni senzor je znan kot senzor z aktivnimi piksli (APS), najbolj priljubljena vrsta APS pa je senzor iz komplementarnega kovinsko-oksidnega polprevodnika ali CMOS. Morda ste že slišali izraz CMOS senzor za slikovne senzorje.

Senzorji kamer so digitalni senzorji, ki pošiljajo slikovne podatke kot digitalne podatke, običajno s pomočjo knjižnice, ki omogoča komunikacijo. Kamere se povezujejo z uporabo protokolov, kot je SPI, da omogočijo pošiljanje velikih količin podatkov – slike so bistveno večje od posameznih številk iz senzorjev, kot je temperaturni senzor.

✅ Kakšne so omejitve glede velikosti slik pri IoT napravah? Razmislite o omejitvah, zlasti pri strojni opremi mikrokrmilnikov.

## Zajem slike z IoT napravo

Svojo IoT napravo lahko uporabite za zajem slike, ki jo želite klasificirati.

### Naloga – zajem slike z IoT napravo

Sledite ustreznemu vodniku za zajem slike z vašo IoT napravo:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Enokartični računalnik - Raspberry Pi](pi-camera.md)
* [Enokartični računalnik - Virtualna naprava](virtual-device-camera.md)

## Objava vašega klasifikatorja slik

V prejšnji lekciji ste naučili svoj klasifikator slik. Preden ga lahko uporabite z vašo IoT napravo, morate model objaviti.

### Iteracije modela

Ko ste v prejšnji lekciji trenirali model, ste morda opazili, da zavihek **Performance** prikazuje iteracije na strani. Ko ste prvič trenirali model, ste videli *Iteration 1*. Ko ste izboljšali model z napovednimi slikami, ste videli *Iteration 2*.

Vsakič, ko trenirate model, dobite novo iteracijo. To je način za sledenje različnim različicam vašega modela, treniranega na različnih podatkovnih nizih. Ko izvedete **Quick Test**, lahko uporabite spustni meni za izbiro iteracije in primerjate rezultate med več iteracijami.

Ko ste zadovoljni z iteracijo, jo lahko objavite, da bo na voljo za uporabo zunanjim aplikacijam. Tako lahko imate objavljeno različico, ki jo uporabljajo vaše naprave, nato pa delate na novi različici skozi več iteracij in jo objavite, ko ste z njo zadovoljni.

### Naloga – objava iteracije

Iteracije se objavljajo iz portala Custom Vision.

1. Odprite portal Custom Vision na [CustomVision.ai](https://customvision.ai) in se prijavite, če še niste. Nato odprite svoj projekt `fruit-quality-detector`.

1. Izberite zavihek **Performance** iz možnosti na vrhu.

1. Izberite najnovejšo iteracijo s seznama *Iterations* na strani.

1. Kliknite gumb **Publish** za iteracijo.

    ![Gumb za objavo](../../../../../translated_images/sl/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. V pogovornem oknu *Publish Model* nastavite *Prediction resource* na vir `fruit-quality-detector-prediction`, ki ste ga ustvarili v prejšnji lekciji. Pustite ime kot `Iteration2` in kliknite gumb **Publish**.

1. Ko je objavljeno, kliknite gumb **Prediction URL**. To bo prikazalo podrobnosti o napovednem API-ju, ki jih boste potrebovali za klic modela iz vaše IoT naprave. Spodnji del je označen kot *If you have an image file*, in to so podrobnosti, ki jih potrebujete. Kopirajte prikazani URL, ki bo nekaj takega:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Kjer bo `<location>` lokacija, ki ste jo uporabili pri ustvarjanju vira Custom Vision, in `<id>` bo dolg ID, sestavljen iz črk in številk.

    Prav tako kopirajte vrednost *Prediction-Key*. To je varnostni ključ, ki ga morate posredovati, ko kličete model. Samo aplikacije, ki posredujejo ta ključ, lahko uporabljajo model, vse druge aplikacije so zavrnjene.

    ![Pogovorno okno napovednega API-ja, ki prikazuje URL in ključ](../../../../../translated_images/sl/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Ko je nova iteracija objavljena, bo imela drugačno ime. Kako mislite, da bi spremenili iteracijo, ki jo uporablja IoT naprava?

## Klasifikacija slik z vaše IoT naprave

Zdaj lahko uporabite te podatke za povezavo, da pokličete klasifikator slik iz vaše IoT naprave.

### Naloga – klasifikacija slik z vaše IoT naprave

Sledite ustreznemu vodniku za klasifikacijo slik z vašo IoT napravo:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Enokartični računalnik - Raspberry Pi/Virtualna IoT naprava](single-board-computer-classify-image.md)

## Izboljšanje modela

Morda boste ugotovili, da rezultati, ki jih dobite pri uporabi kamere, povezane z vašo IoT napravo, ne ustrezajo vašim pričakovanjem. Napovedi niso vedno tako natančne kot pri slikah, naloženih z vašega računalnika. To je zato, ker je bil model treniran na drugačnih podatkih, kot se uporabljajo za napovedi.

Za najboljše rezultate klasifikatorja slik želite model trenirati s slikami, ki so čim bolj podobne slikam, uporabljenim za napovedi. Če ste na primer za treniranje uporabili kamero telefona, se kakovost slike, ostrina in barve razlikujejo od kamere, povezane z IoT napravo.

![2 slike banan, ena z nizko ločljivostjo in slabšo osvetlitvijo z IoT naprave, druga z visoko ločljivostjo in dobro osvetlitvijo s telefonom](../../../../../translated_images/sl/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Na zgornji sliki je slika banane na levi posneta z Raspberry Pi kamero, slika na desni pa z iPhone-om. Opazna je razlika v kakovosti – slika z iPhone-a je ostrejša, z živahnejšimi barvami in večjim kontrastom.

✅ Kaj bi še lahko povzročilo, da slike, zajete z vašo IoT napravo, dajejo napačne napovedi? Razmislite o okolju, v katerem se uporablja IoT naprava, in o dejavnikih, ki lahko vplivajo na zajeto sliko.

Za izboljšanje modela ga lahko ponovno trenirate z uporabo slik, zajetih z IoT naprave.

### Naloga – izboljšanje modela

1. Klasificirajte več slik zrelega in nezrelega sadja z vašo IoT napravo.

1. Na portalu Custom Vision ponovno trenirajte model z uporabo slik na zavihku *Predictions*.

    > ⚠️ Če potrebujete, si oglejte [navodila za ponovno treniranje klasifikatorja v lekciji 1](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Če so vaše slike zelo drugačne od prvotnih, uporabljenih za treniranje, lahko izbrišete vse prvotne slike tako, da jih izberete na zavihku *Training Images* in kliknete gumb **Delete**. Za izbiro slike premaknite kazalec nad njo, da se prikaže kljukica, nato kliknite kljukico za izbiro ali preklic izbire slike.

1. Trenutno novo iteracijo modela in jo objavite z zgornjimi koraki.

1. Posodobite URL končne točke v svoji kodi in ponovno zaženite aplikacijo.

1. Ponavljajte te korake, dokler ne boste zadovoljni z rezultati napovedi.

---

## 🚀 Izziv

Koliko vplivata ločljivost slike ali osvetlitev na napoved?

Poskusite spremeniti ločljivost slik v kodi vaše naprave in preverite, ali to vpliva na kakovost slik. Prav tako poskusite spremeniti osvetlitev.

Če bi ustvarili napravo za prodajo kmetijam ali tovarnam, kako bi zagotovili, da vedno daje dosledne rezultate?

## Kviz po predavanju

[Kviz po predavanju](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Pregled in samostojno učenje

Svoj model Custom Vision ste trenirali z uporabo portala. To temelji na razpoložljivosti slik – v resničnem svetu morda ne boste mogli pridobiti podatkov za treniranje, ki ustrezajo slikam, ki jih zajame kamera na vaši napravi. To lahko rešite tako, da trenirate neposredno iz vaše naprave z uporabo API-ja za treniranje, da trenirate model z uporabo slik, zajetih z vaše IoT naprave.

* Preberite več o API-ju za treniranje v [hitrem začetku uporabe Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Naloga

[Odgovorite na rezultate klasifikacije](assignment.md)

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.