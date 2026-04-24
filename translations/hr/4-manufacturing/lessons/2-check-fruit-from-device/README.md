# Provjera kvalitete voća pomoću IoT uređaja

![Pregled lekcije u obliku sketchnotea](../../../../../translated_images/hr/lesson-16.215daf18b00631fb.webp)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Uvod

U prethodnoj lekciji naučili ste o klasifikatorima slika i kako ih trenirati za prepoznavanje dobrog i lošeg voća. Da biste koristili ovaj klasifikator slika u IoT aplikaciji, trebate moći snimiti sliku pomoću neke vrste kamere i poslati tu sliku u oblak na klasifikaciju.

U ovoj lekciji naučit ćete o senzorima kamera i kako ih koristiti s IoT uređajem za snimanje slike. Također ćete naučiti kako pozvati klasifikator slika s vašeg IoT uređaja.

U ovoj lekciji obradit ćemo:

* [Senzori kamera](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Snimanje slike pomoću IoT uređaja](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Objavljivanje vašeg klasifikatora slika](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klasifikacija slika s vašeg IoT uređaja](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Poboljšanje modela](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Senzori kamera

Senzori kamera, kako ime sugerira, su kamere koje možete povezati s vašim IoT uređajem. Oni mogu snimati statične slike ili streaming video. Neki će vraćati sirove podatke slike, dok će drugi komprimirati podatke slike u datoteku poput JPEG-a ili PNG-a. Obično su kamere koje rade s IoT uređajima mnogo manje i niže rezolucije nego što ste navikli, ali možete nabaviti kamere visoke rezolucije koje se mogu usporediti s vrhunskim telefonima. Dostupni su razni izmjenjivi objektivi, višestruki setovi kamera, infracrvene termalne kamere ili UV kamere.

![Svjetlost iz scene prolazi kroz objektiv i fokusira se na CMOS senzor](../../../../../translated_images/hr/cmos-sensor.75f9cd74decb1371.webp)

Većina senzora kamera koristi senzore slike gdje je svaki piksel fotodioda. Objektiv fokusira sliku na senzor slike, a tisuće ili milijuni fotodioda detektiraju svjetlost koja pada na svaku od njih i bilježe to kao podatke piksela.

> 💁 Objektivi preokreću slike, a senzor kamere zatim vraća sliku u ispravan položaj. Isto se događa i u vašim očima - ono što vidite detektira se naopako na stražnjem dijelu oka, a vaš mozak to ispravlja.

> 🎓 Senzor slike poznat je kao senzor aktivnih piksela (APS), a najpopularniji tip APS-a je komplementarni metal-oksidni poluvodički senzor, ili CMOS. Možda ste čuli izraz CMOS senzor koji se koristi za senzore kamera.

Senzori kamera su digitalni senzori, koji šalju podatke slike kao digitalne podatke, obično uz pomoć biblioteke koja omogućuje komunikaciju. Kamere se povezuju pomoću protokola poput SPI-a kako bi omogućile slanje velikih količina podataka - slike su znatno veće od pojedinačnih brojeva iz senzora poput senzora temperature.

✅ Koja su ograničenja veličine slike kod IoT uređaja? Razmislite o ograničenjima, posebno kod hardvera mikrokontrolera.

## Snimanje slike pomoću IoT uređaja

Možete koristiti svoj IoT uređaj za snimanje slike koja će se klasificirati.

### Zadatak - snimanje slike pomoću IoT uređaja

Prođite kroz odgovarajući vodič za snimanje slike pomoću vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Jednoplani računalo - Raspberry Pi](pi-camera.md)
* [Jednoplani računalo - Virtualni uređaj](virtual-device-camera.md)

## Objavljivanje vašeg klasifikatora slika

Svoj klasifikator slika ste trenirali u prethodnoj lekciji. Prije nego što ga možete koristiti s vašeg IoT uređaja, trebate objaviti model.

### Iteracije modela

Kada je vaš model bio treniran u prethodnoj lekciji, mogli ste primijetiti da kartica **Performance** prikazuje iteracije sa strane. Kada ste prvi put trenirali model, vidjeli ste *Iteration 1* tijekom treninga. Kada ste poboljšali model koristeći slike predikcija, vidjeli ste *Iteration 2* tijekom treninga.

Svaki put kada trenirate model, dobivate novu iteraciju. Ovo je način praćenja različitih verzija vašeg modela treniranih na različitim skupovima podataka. Kada radite **Quick Test**, postoji padajući izbornik koji možete koristiti za odabir iteracije, tako da možete usporediti rezultate između više iteracija.

Kada ste zadovoljni s iteracijom, možete je objaviti kako bi bila dostupna za korištenje iz vanjskih aplikacija. Na taj način možete imati objavljenu verziju koju koriste vaši uređaji, zatim raditi na novoj verziji kroz više iteracija, a zatim je objaviti kada budete zadovoljni.

### Zadatak - objavljivanje iteracije

Iteracije se objavljuju iz portala Custom Vision.

1. Pokrenite portal Custom Vision na [CustomVision.ai](https://customvision.ai) i prijavite se ako ga već nemate otvorenog. Zatim otvorite svoj projekt `fruit-quality-detector`.

1. Odaberite karticu **Performance** iz opcija na vrhu.

1. Odaberite najnoviju iteraciju s popisa *Iterations* sa strane.

1. Kliknite gumb **Publish** za iteraciju.

    ![Gumb za objavljivanje](../../../../../translated_images/hr/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. U dijalogu *Publish Model*, postavite *Prediction resource* na resurs `fruit-quality-detector-prediction` koji ste kreirali u prethodnoj lekciji. Ostavite naziv kao `Iteration2` i kliknite gumb **Publish**.

1. Nakon objavljivanja, kliknite gumb **Prediction URL**. Ovo će prikazati detalje API-ja za predikciju, a te detalje ćete trebati za pozivanje modela s vašeg IoT uređaja. Donji dio je označen *If you have an image file*, i to su detalji koji su vam potrebni. Kopirajte URL koji je prikazan, koji će izgledati ovako:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Gdje će `<location>` biti lokacija koju ste koristili prilikom kreiranja resursa za Custom Vision, a `<id>` će biti dugi ID sastavljen od slova i brojeva.

    Također kopirajte vrijednost *Prediction-Key*. Ovo je sigurnosni ključ koji morate proslijediti prilikom pozivanja modela. Samo aplikacije koje proslijede ovaj ključ smiju koristiti model, sve ostale aplikacije bit će odbijene.

    ![Dijalog API-ja za predikciju koji prikazuje URL i ključ](../../../../../translated_images/hr/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Kada se objavi nova iteracija, imat će drugačiji naziv. Kako mislite da biste promijenili iteraciju koju IoT uređaj koristi?

## Klasifikacija slika s vašeg IoT uređaja

Sada možete koristiti ove podatke za povezivanje kako biste pozvali klasifikator slika s vašeg IoT uređaja.

### Zadatak - klasifikacija slika s vašeg IoT uređaja

Prođite kroz odgovarajući vodič za klasifikaciju slika pomoću vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Jednoplani računalo - Raspberry Pi/Virtualni IoT uređaj](single-board-computer-classify-image.md)

## Poboljšanje modela

Možda ćete primijetiti da rezultati koje dobijete prilikom korištenja kamere povezane s vašim IoT uređajem ne odgovaraju onome što biste očekivali. Predikcije nisu uvijek tako točne kao kod korištenja slika učitanih s vašeg računala. To je zato što je model treniran na različitim podacima od onih koji se koriste za predikcije.

Da biste dobili najbolje rezultate za klasifikator slika, želite trenirati model s slikama koje su što sličnije slikama koje se koriste za predikcije. Ako ste koristili kameru telefona za snimanje slika za trening, na primjer, kvaliteta slike, oštrina i boja bit će drugačiji od kamere povezane s IoT uređajem.

![2 slike banana, jedna niske rezolucije s lošim osvjetljenjem s IoT uređaja, i jedna visoke rezolucije s dobrim osvjetljenjem s telefona](../../../../../translated_images/hr/banana-picture-compare.174df164dc326a42.webp)

Na slici iznad, slika banane s lijeve strane snimljena je pomoću Raspberry Pi kamere, dok je slika s desne strane snimljena istog banana na istom mjestu pomoću iPhonea. Primjetna je razlika u kvaliteti - slika s iPhonea je oštrija, s svjetlijim bojama i većim kontrastom.

✅ Što još može uzrokovati da slike snimljene vašim IoT uređajem imaju netočne predikcije? Razmislite o okruženju u kojem se IoT uređaj može koristiti, koji faktori mogu utjecati na snimanje slike?

Da biste poboljšali model, možete ga ponovno trenirati koristeći slike snimljene s IoT uređaja.

### Zadatak - poboljšanje modela

1. Klasificirajte više slika zrelog i nezrelog voća pomoću vašeg IoT uređaja.

1. U portalu Custom Vision ponovno trenirajte model koristeći slike na kartici *Predictions*.

    > ⚠️ Možete se referirati na [upute za ponovno treniranje klasifikatora u lekciji 1 ako je potrebno](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Ako vaše slike izgledaju vrlo različito od originalnih koje su korištene za trening, možete izbrisati sve originalne slike odabirom na kartici *Training Images* i klikom na gumb **Delete**. Za odabir slike, pomaknite kursor preko nje i pojavit će se kvačica, odaberite tu kvačicu za odabir ili poništavanje slike.

1. Trenirajte novu iteraciju modela i objavite je koristeći gore navedene korake.

1. Ažurirajte URL krajnje točke u svom kodu i ponovno pokrenite aplikaciju.

1. Ponavljajte ove korake dok ne budete zadovoljni rezultatima predikcija.

---

## 🚀 Izazov

Koliko rezolucija slike ili osvjetljenje utječu na predikciju?

Pokušajte promijeniti rezoluciju slika u kodu vašeg uređaja i provjerite hoće li to utjecati na kvalitetu slika. Također pokušajte promijeniti osvjetljenje.

Ako biste kreirali proizvodni uređaj za prodaju farmama ili tvornicama, kako biste osigurali da uvijek daje dosljedne rezultate?

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Pregled i samostalno učenje

Svoj model za prilagođenu viziju ste trenirali koristeći portal. Ovo se oslanja na dostupnost slika - a u stvarnom svijetu možda nećete moći dobiti podatke za trening koji odgovaraju onome što kamera na vašem uređaju snima. Možete zaobići ovo treniranjem direktno s vašeg uređaja koristeći API za trening, kako biste trenirali model koristeći slike snimljene s vašeg IoT uređaja.

* Pročitajte o API-ju za trening u [brzom početku za korištenje Custom Vision SDK-a](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Zadatak

[Odgovorite na rezultate klasifikacije](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.