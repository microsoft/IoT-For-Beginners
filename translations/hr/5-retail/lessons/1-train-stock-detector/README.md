<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-28T14:22:26+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "hr"
}
-->
# Trenirajte detektor zaliha

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ovaj video daje pregled prepoznavanja objekata pomoću Azure Custom Vision servisa, usluge koja će biti obrađena u ovoj lekciji.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Kliknite na sliku iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Uvod

U prethodnom projektu koristili ste AI za treniranje klasifikatora slika - modela koji može prepoznati sadrži li slika nešto, poput zrelog ili nezrelog voća. Druga vrsta AI modela koja se može koristiti sa slikama je prepoznavanje objekata. Ovi modeli ne klasificiraju sliku prema oznakama, već su obučeni za prepoznavanje objekata i mogu ih pronaći na slikama, ne samo detektirajući da je objekt prisutan, već i gdje se nalazi na slici. Ovo omogućuje brojanje objekata na slikama.

U ovoj lekciji naučit ćete o prepoznavanju objekata, uključujući kako se može koristiti u maloprodaji. Također ćete naučiti kako trenirati detektor objekata u oblaku.

U ovoj lekciji obradit ćemo:

* [Prepoznavanje objekata](../../../../../5-retail/lessons/1-train-stock-detector)
* [Korištenje prepoznavanja objekata u maloprodaji](../../../../../5-retail/lessons/1-train-stock-detector)
* [Treniranje detektora objekata](../../../../../5-retail/lessons/1-train-stock-detector)
* [Testiranje vašeg detektora objekata](../../../../../5-retail/lessons/1-train-stock-detector)
* [Ponovno treniranje vašeg detektora objekata](../../../../../5-retail/lessons/1-train-stock-detector)

## Prepoznavanje objekata

Prepoznavanje objekata uključuje detekciju objekata na slikama pomoću AI-a. Za razliku od klasifikatora slika koji ste trenirali u prošlom projektu, prepoznavanje objekata nije usmjereno na predviđanje najbolje oznake za cijelu sliku, već na pronalaženje jednog ili više objekata na slici.

### Prepoznavanje objekata vs klasifikacija slika

Klasifikacija slika odnosi se na klasifikaciju cijele slike - koje su vjerojatnosti da cijela slika odgovara svakoj oznaci. Dobivate natrag vjerojatnosti za svaku oznaku korištenu za treniranje modela.

![Klasifikacija slika indijskih oraščića i paste od rajčice](../../../../../translated_images/hr/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

U gornjem primjeru, dvije slike su klasificirane pomoću modela treniranog za klasifikaciju posuda s indijskim oraščićima ili konzervi paste od rajčice. Prva slika prikazuje posudu s indijskim oraščićima i ima dva rezultata iz klasifikatora slika:

| Oznaka          | Vjerojatnost |
| ---------------- | -----------: |
| `indijski oraščići` | 98.4%       |
| `pasta od rajčice`  | 1.6%        |

Druga slika prikazuje konzervu paste od rajčice, a rezultati su:

| Oznaka          | Vjerojatnost |
| ---------------- | -----------: |
| `indijski oraščići` | 0.7%        |
| `pasta od rajčice`  | 99.3%       |

Mogli biste koristiti ove vrijednosti s pragom postotka za predviđanje što se nalazi na slici. No što ako slika sadrži više konzervi paste od rajčice ili i indijske oraščiće i pastu od rajčice? Rezultati vjerojatno ne bi dali ono što želite. Tu dolazi prepoznavanje objekata.

Prepoznavanje objekata uključuje treniranje modela za prepoznavanje objekata. Umjesto da mu dajete slike koje sadrže objekt i govorite mu da je svaka slika jedna oznaka ili druga, označavate dio slike koji sadrži određeni objekt i dodjeljujete mu oznaku. Možete označiti jedan objekt na slici ili više njih. Na taj način model uči kako sam objekt izgleda, a ne samo kako izgledaju slike koje sadrže objekt.

Kada ga zatim koristite za predviđanje slika, umjesto da dobijete popis oznaka i postotaka, dobivate popis detektiranih objekata, s njihovim okvirima i vjerojatnošću da okvir sadrži dodijeljenu oznaku.

> 🎓 *Okviri* su pravokutnici oko objekta.

![Prepoznavanje objekata indijskih oraščića i paste od rajčice](../../../../../translated_images/hr/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

Gornja slika sadrži i posudu s indijskim oraščićima i tri konzerve paste od rajčice. Detektor objekata detektirao je indijske oraščiće, vraćajući okvir koji sadrži indijske oraščiće s postotkom vjerojatnosti da okvir sadrži objekt, u ovom slučaju 97.6%. Detektor objekata također je detektirao tri konzerve paste od rajčice i pruža tri odvojena okvira, po jedan za svaku detektiranu konzervu, a svaki ima postotak vjerojatnosti da okvir sadrži konzervu paste od rajčice.

✅ Razmislite o nekim različitim scenarijima za koje biste mogli koristiti AI modele temeljene na slikama. Koji bi trebali klasifikaciju, a koji prepoznavanje objekata?

### Kako funkcionira prepoznavanje objekata

Prepoznavanje objekata koristi složene ML modele. Ovi modeli rade tako da dijele sliku na više ćelija, a zatim provjeravaju je li središte okvira središte slike koja odgovara jednoj od slika korištenih za treniranje modela. Možete to zamisliti kao neku vrstu pokretanja klasifikatora slika na različitim dijelovima slike kako biste pronašli podudaranja.

> 💁 Ovo je drastično pojednostavljenje. Postoji mnogo tehnika za prepoznavanje objekata, a više o njima možete pročitati na [stranici o prepoznavanju objekata na Wikipediji](https://wikipedia.org/wiki/Object_detection).

Postoji niz različitih modela koji mogu raditi prepoznavanje objekata. Jedan posebno poznat model je [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), koji je izuzetno brz i može detektirati 20 različitih klasa objekata, poput ljudi, pasa, boca i automobila.

✅ Pročitajte više o YOLO modelu na [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Modele za prepoznavanje objekata moguće je ponovno trenirati koristeći transferno učenje za detekciju prilagođenih objekata.

## Korištenje prepoznavanja objekata u maloprodaji

Prepoznavanje objekata ima više primjena u maloprodaji. Neke od njih uključuju:

* **Provjera i brojanje zaliha** - prepoznavanje kada su zalihe na policama niske. Ako su zalihe preniske, mogu se poslati obavijesti osoblju ili robotima za ponovno punjenje polica.
* **Detekcija maski** - u trgovinama s politikama nošenja maski tijekom javnozdravstvenih događaja, prepoznavanje objekata može prepoznati ljude s maskama i bez njih.
* **Automatizirano naplaćivanje** - detekcija predmeta uzetih s polica u automatiziranim trgovinama i odgovarajuće naplaćivanje kupcima.
* **Detekcija opasnosti** - prepoznavanje razbijenih predmeta na podu ili prolivenih tekućina, obavještavanje čistača.

✅ Provedite istraživanje: Koje su još primjene prepoznavanja objekata u maloprodaji?

## Treniranje detektora objekata

Možete trenirati detektor objekata koristeći Custom Vision, na sličan način kao što ste trenirali klasifikator slika.

### Zadatak - kreirajte detektor objekata

1. Kreirajte grupu resursa za ovaj projekt pod nazivom `stock-detector`.

1. Kreirajte besplatni Custom Vision resurs za treniranje i besplatni Custom Vision resurs za predikciju u grupi resursa `stock-detector`. Nazovite ih `stock-detector-training` i `stock-detector-prediction`.

    > 💁 Možete imati samo jedan besplatni resurs za treniranje i predikciju, stoga provjerite jeste li očistili svoj projekt iz prethodnih lekcija.

    > ⚠️ Možete se referirati na [upute za kreiranje resursa za treniranje i predikciju iz projekta 4, lekcija 1 ako je potrebno](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Pokrenite Custom Vision portal na [CustomVision.ai](https://customvision.ai) i prijavite se s Microsoft računom koji ste koristili za svoj Azure račun.

1. Slijedite [odjeljak Kreiranje novog projekta u vodiču za brzi početak na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) kako biste kreirali novi Custom Vision projekt. Koristite naziv `stock-detector`.

    Kada kreirate svoj projekt, obavezno koristite resurs `stock-detector-training` koji ste ranije kreirali. Koristite tip projekta *Object Detection* i domenu *Products on Shelves*.

    ![Postavke za Custom Vision projekt s nazivom postavljenim na fruit-quality-detector, bez opisa, resursom postavljenim na fruit-quality-detector-training, tipom projekta postavljenim na classification, vrstama klasifikacije postavljenim na multi class i domenama postavljenim na food](../../../../../translated_images/hr/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ Domena *Products on Shelves* posebno je usmjerena na detekciju zaliha na policama trgovina. Pročitajte više o različitim domenama u [dokumentaciji o odabiru domena na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection).

✅ Odvojite malo vremena za istraživanje Custom Vision sučelja za vaš detektor objekata.

### Zadatak - trenirajte svoj detektor objekata

Za treniranje modela trebat će vam skup slika koje sadrže objekte koje želite detektirati.

1. Prikupite slike koje sadrže objekt za detekciju. Trebat će vam najmanje 15 slika koje sadrže svaki objekt za detekciju iz različitih kutova i u različitim uvjetima osvjetljenja, ali što više to bolje. Ovaj detektor objekata koristi domenu *Products on Shelves*, stoga pokušajte postaviti objekte kao da su na polici trgovine. Također će vam trebati nekoliko slika za testiranje modela. Ako detektirate više od jednog objekta, trebat će vam neke testne slike koje sadrže sve objekte.

    > 💁 Slike s više različitih objekata računaju se prema minimalnih 15 slika za sve objekte na slici.

    Vaše slike trebaju biti u formatu png ili jpeg, manje od 6MB. Ako ih kreirate, primjerice, iPhoneom, možda će biti visoke rezolucije u HEIC formatu, pa će ih trebati konvertirati i eventualno smanjiti. Što više slika to bolje, i trebali biste imati sličan broj zrelih i nezrelih.

    Model je dizajniran za proizvode na policama, stoga pokušajte fotografirati objekte na policama.

    Možete pronaći neke primjere slika koje možete koristiti u [mapi images](../../../../../5-retail/lessons/1-train-stock-detector/images) s indijskim oraščićima i pastom od rajčice koje možete koristiti.

1. Slijedite [odjeljak Upload i označavanje slika u vodiču za brzi početak na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) kako biste učitali svoje slike za treniranje. Kreirajte relevantne oznake ovisno o vrstama objekata koje želite detektirati.

    ![Dijalozi za upload koji prikazuju upload slika zrelih i nezrelih banana](../../../../../translated_images/hr/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    Kada crtate okvire za objekte, držite ih čvrsto oko objekta. Može potrajati neko vrijeme da označite sve slike, ali alat će detektirati ono što misli da su okviri, čineći proces bržim.

    ![Označavanje paste od rajčice](../../../../../translated_images/hr/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 Ako imate više od 15 slika za svaki objekt, možete trenirati nakon 15, a zatim koristiti značajku **Predložene oznake**. Ovo će koristiti trenirani model za detekciju objekata na neoznačenim slikama. Zatim možete potvrditi detektirane objekte ili odbaciti i ponovno nacrtati okvire. Ovo može uštedjeti *puno* vremena.

1. Slijedite [odjeljak Treniranje detektora u vodiču za brzi početak na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) kako biste trenirali detektor objekata na svojim označenim slikama.

    Bit će vam ponuđen izbor vrste treniranja. Odaberite **Quick Training**.

Detektor objekata će se zatim trenirati. Trebat će nekoliko minuta da treniranje završi.

## Testiranje vašeg detektora objekata

Kada je vaš detektor objekata treniran, možete ga testirati dajući mu nove slike za detekciju objekata.

### Zadatak - testirajte svoj detektor objekata

1. Koristite gumb **Quick Test** za upload testnih slika i provjeru jesu li objekti detektirani. Koristite testne slike koje ste ranije kreirali, a ne bilo koju od slika koje ste koristili za treniranje.

    ![3 konzerve paste od rajčice detektirane s vjerojatnostima od 38%, 35.5% i 34.6%](../../../../../translated_images/hr/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.png)

1. Isprobajte sve testne slike koje imate i promatrajte vjerojatnosti.

## Ponovno treniranje vašeg detektora objekata

Kada testirate svoj detektor objekata, možda neće dati rezultate koje očekujete, isto kao i kod klasifikatora slika u prethodnom projektu. Možete poboljšati svoj detektor objekata ponovnim treniranjem s pogrešnim slikama.

Svaki put kada napravite predikciju koristeći opciju brzog testiranja, slika i rezultati se pohranjuju. Možete koristiti te slike za ponovno treniranje modela.

1. Koristite karticu **Predictions** za pronalaženje slika koje ste koristili za testiranje.

1. Potvrdite sve točne detekcije, izbrišite netočne i dodajte sve nedostajuće objekte.

1. Ponovno trenirajte i ponovno testirajte model.

---

## 🚀 Izazov

Što bi se dogodilo ako biste koristili detektor objekata s predmetima koji izgledaju slično, poput konzervi iste marke paste od rajčice i sjeckane rajčice?

Ako imate bilo kakve predmete koji izgledaju slično, testirajte ih dodavanjem njihovih slika u svoj detektor objekata.

## Kviz nakon predavanja
[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Pregled i Samostalno Učenje

* Kada ste trenirali svoj detektor objekata, vidjeli ste vrijednosti za *Preciznost*, *Povrat* i *mAP* koje ocjenjuju model koji je stvoren. Pročitajte više o tome što te vrijednosti znače koristeći [sekciju Procjena detektora u vodiču za brzi početak izrade detektora objekata na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Pročitajte više o detekciji objekata na [stranici Detekcija objekata na Wikipediji](https://wikipedia.org/wiki/Object_detection)

## Zadatak

[Usporedite domene](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.