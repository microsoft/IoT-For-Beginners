<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-28T12:05:30+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "hr"
}
-->
# Trenirajte detektor kvalitete voća

![Pregled lekcije u obliku sketchnotea](../../../../../translated_images/hr/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ovaj video pruža pregled usluge Azure Custom Vision, koja će biti obuhvaćena u ovoj lekciji.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Kliknite na sliku iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Uvod

Nedavni porast umjetne inteligencije (AI) i strojnog učenja (ML) pruža širok raspon mogućnosti današnjim programerima. ML modeli mogu se obučiti da prepoznaju različite stvari na slikama, uključujući nezrelo voće, što se može koristiti u IoT uređajima za sortiranje proizvoda bilo tijekom berbe ili tijekom obrade u tvornicama ili skladištima.

U ovoj lekciji naučit ćete o klasifikaciji slika - korištenju ML modela za razlikovanje između slika različitih objekata. Naučit ćete kako obučiti klasifikator slika da razlikuje između dobrog i lošeg voća, bilo da je nezrelo, prezrelo, oštećeno ili trulo.

U ovoj lekciji obradit ćemo:

* [Korištenje AI i ML za sortiranje hrane](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Klasifikacija slika putem strojnog učenja](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Obučavanje klasifikatora slika](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Testiranje vašeg klasifikatora slika](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Ponovno obučavanje vašeg klasifikatora slika](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Korištenje AI i ML za sortiranje hrane

Hranjenje globalne populacije je izazovno, posebno po cijeni koja čini hranu dostupnom svima. Jedan od najvećih troškova je radna snaga, pa se farmeri sve više okreću automatizaciji i alatima poput IoT-a kako bi smanjili troškove rada. Ručna berba je radno intenzivna (i često iscrpljujuća), te se zamjenjuje strojevima, posebno u bogatijim zemljama. Unatoč uštedama u troškovima korištenja strojeva za berbu, postoji nedostatak - sposobnost sortiranja hrane tijekom berbe.

Ne sazrijevaju svi usjevi ravnomjerno. Na primjer, rajčice mogu imati još zelenih plodova na lozi kada je većina spremna za berbu. Iako je šteta brati ih prerano, farmerima je jeftinije i lakše sve ubrati strojevima i kasnije odbaciti nezrele plodove.

✅ Pogledajte različite vrste voća ili povrća, bilo da rastu u blizini na farmama ili u vašem vrtu, ili u trgovinama. Jesu li svi iste zrelosti, ili vidite razlike?

Porast automatizirane berbe premjestio je sortiranje proizvoda s berbe na tvornicu. Hrana bi putovala na dugim pokretnim trakama s timovima ljudi koji pregledavaju proizvode i uklanjaju sve što ne zadovoljava potrebne standarde kvalitete. Berba je bila jeftinija zahvaljujući strojevima, ali još uvijek je postojao trošak ručnog sortiranja hrane.

![Ako se otkrije crvena rajčica, nastavlja svoj put neometano. Ako se otkrije zelena rajčica, poluga je izbacuje u otpadnu posudu](../../../../../translated_images/hr/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.png)

Sljedeća evolucija bila je korištenje strojeva za sortiranje, bilo ugrađenih u berač ili u pogonima za obradu. Prva generacija ovih strojeva koristila je optičke senzore za otkrivanje boja, kontrolirajući aktuatore koji su gurali zelene rajčice u otpadnu posudu pomoću poluga ili mlazova zraka, ostavljajući crvene rajčice da nastave na mreži pokretnih traka.

U ovom videu, dok rajčice padaju s jedne pokretne trake na drugu, zelene rajčice se otkrivaju i izbacuju u posudu pomoću poluga.

✅ Koji uvjeti bi bili potrebni u tvornici ili na polju da ovi optički senzori ispravno rade?

Najnovije evolucije ovih strojeva za sortiranje koriste AI i ML, koristeći modele obučene za razlikovanje dobrog proizvoda od lošeg, ne samo po očitim razlikama u boji poput zelene rajčice naspram crvene, već i po suptilnijim razlikama u izgledu koje mogu ukazivati na bolest ili oštećenje.

## Klasifikacija slika putem strojnog učenja

Tradicionalno programiranje uključuje uzimanje podataka, primjenu algoritma na te podatke i dobivanje rezultata. Na primjer, u prošlom projektu uzeli ste GPS koordinate i geozonu, primijenili algoritam koji je pružio Azure Maps i dobili rezultat o tome je li točka unutar ili izvan geozone. Unesete više podataka, dobijete više rezultata.

![Tradicionalni razvoj uzima ulazne podatke i algoritam te daje izlaz. Strojno učenje koristi ulazne i izlazne podatke za obuku modela, a taj model može uzeti nove ulazne podatke za generiranje novih izlaza](../../../../../translated_images/hr/traditional-vs-ml.5c20c169621fa539.webp)

Strojno učenje to preokreće - počinjete s podacima i poznatim izlazima, a algoritam strojnog učenja uči iz podataka. Zatim možete uzeti taj obučeni algoritam, nazvan *model strojnog učenja* ili *model*, i unijeti nove podatke te dobiti nove rezultate.

> 🎓 Proces učenja algoritma strojnog učenja iz podataka naziva se *obuka*. Ulazni podaci i poznati izlazi nazivaju se *podaci za obuku*.

Na primjer, mogli biste dati modelu milijune slika nezrelih banana kao ulazne podatke za obuku, s izlazom za obuku postavljenim na `nezrelo`, i milijune slika zrelih banana kao podatke za obuku s izlazom postavljenim na `zrelo`. Algoritam strojnog učenja tada će stvoriti model na temelju tih podataka. Zatim dajete ovom modelu novu sliku banane i on će predvidjeti je li nova slika zrela ili nezrela banana.

> 🎓 Rezultati ML modela nazivaju se *predikcije*

![2 banane, jedna zrela s predikcijom od 99.7% zrelo, 0.3% nezrelo, i jedna nezrela s predikcijom od 1.4% zrelo, 98.6% nezrelo](../../../../../translated_images/hr/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.png)

ML modeli ne daju binarni odgovor, već daju vjerojatnosti. Na primjer, model može dobiti sliku banane i predvidjeti `zrelo` s 99.7% i `nezrelo` s 0.3%. Vaš kod bi tada odabrao najbolju predikciju i odlučio da je banana zrela.

ML model koji se koristi za otkrivanje slika poput ove naziva se *klasifikator slika* - dobiva označene slike i zatim klasificira nove slike na temelju tih oznaka.

> 💁 Ovo je pojednostavljenje, i postoje mnogi drugi načini za obuku modela koji ne zahtijevaju uvijek označene izlaze, poput nesuperviziranog učenja. Ako želite saznati više o ML-u, pogledajte [ML za početnike, 24-lekcijski kurikulum o strojnim učenjima](https://aka.ms/ML-beginners).

## Obučavanje klasifikatora slika

Da biste uspješno obučili klasifikator slika, trebate milijune slika. Kako se ispostavlja, jednom kada imate klasifikator slika obučen na milijunima ili milijardama različitih slika, možete ga ponovno koristiti i ponovno obučiti koristeći mali skup slika i dobiti odlične rezultate, koristeći proces nazvan *transferno učenje*.

> 🎓 Transferno učenje je proces prijenosa učenja iz postojećeg ML modela na novi model temeljen na novim podacima.

Jednom kada je klasifikator slika obučen za širok raspon slika, njegove unutarnje funkcije su izvrsne u prepoznavanju oblika, boja i uzoraka. Transferno učenje omogućuje modelu da iskoristi ono što je već naučio u prepoznavanju dijelova slike i koristi to za prepoznavanje novih slika.

![Jednom kada možete prepoznati oblike, oni se mogu složiti u različite konfiguracije kako bi se stvorio brod ili mačka](../../../../../translated_images/hr/shapes-to-images.1a309f0ea88dd66f.webp)

Možete to zamisliti kao dječje knjige s oblicima, gdje jednom kada možete prepoznati polukrug, pravokutnik i trokut, možete prepoznati jedrilicu ili mačku ovisno o konfiguraciji tih oblika. Klasifikator slika može prepoznati oblike, a transferno učenje ga uči koja kombinacija čini brod ili mačku - ili zrelu bananu.

Postoji širok raspon alata koji vam mogu pomoći u tome, uključujući usluge temeljene na oblaku koje vam mogu pomoći u obuci vašeg modela, a zatim ga koristiti putem web API-ja.

> 💁 Obuka ovih modela zahtijeva puno računalne snage, obično putem grafičkih procesorskih jedinica (GPU). Ista specijalizirana oprema koja čini igre na vašem Xboxu impresivnima također se može koristiti za obuku modela strojnog učenja. Korištenjem oblaka možete unajmiti vrijeme na moćnim računalima s GPU-ima za obuku ovih modela, dobivajući pristup potrebnoj računalnoj snazi samo za vrijeme koje vam je potrebno.

## Custom Vision

Custom Vision je alat temeljen na oblaku za obuku klasifikatora slika. Omogućuje vam obuku klasifikatora koristeći samo mali broj slika. Možete učitati slike putem web portala, web API-ja ili SDK-a, dajući svakoj slici *oznaku* koja predstavlja klasifikaciju te slike. Zatim obučavate model i testirate ga kako biste vidjeli koliko dobro radi. Kada ste zadovoljni modelom, možete objaviti njegove verzije koje se mogu koristiti putem web API-ja ili SDK-a.

![Logotip Azure Custom Vision](../../../../../translated_images/hr/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.png)

> 💁 Možete obučiti model Custom Vision s samo 5 slika po klasifikaciji, ali više je bolje. Možete dobiti bolje rezultate s barem 30 slika.

Custom Vision je dio niza AI alata od Microsofta nazvanih Cognitive Services. To su AI alati koji se mogu koristiti ili bez ikakve obuke ili s malom količinom obuke. Uključuju prepoznavanje i prijevod govora, razumijevanje jezika i analizu slika. Dostupni su s besplatnim slojem kao usluge u Azureu.

> 💁 Besplatni sloj je više nego dovoljan za stvaranje modela, njegovu obuku, a zatim korištenje za razvojne radove. Možete pročitati o ograničenjima besplatnog sloja na [Custom Vision Limits and quotas stranici na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Zadatak - kreirajte resurs za kognitivne usluge

Da biste koristili Custom Vision, prvo morate kreirati dva resursa za kognitivne usluge u Azureu koristeći Azure CLI, jedan za obuku Custom Vision i jedan za predikciju Custom Vision.

1. Kreirajte Resource Group za ovaj projekt nazvanu `fruit-quality-detector`.

1. Koristite sljedeću naredbu za kreiranje besplatnog resursa za obuku Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja Resource Group.

    Ovo će kreirati resurs za obuku Custom Vision u vašoj Resource Group. Zvat će se `fruit-quality-detector-training` i koristiti `F0` sku, što je besplatni sloj. Opcija `--yes` znači da se slažete s uvjetima i odredbama kognitivnih usluga.

> 💁 Koristite `S0` sku ako već imate besplatni račun koji koristi bilo koju od kognitivnih usluga.

1. Koristite sljedeću naredbu za kreiranje besplatnog resursa za predikciju Custom Vision:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja Resource Group.

    Ovo će kreirati resurs za predikciju Custom Vision u vašoj Resource Group. Zvat će se `fruit-quality-detector-prediction` i koristiti `F0` sku, što je besplatni sloj. Opcija `--yes` znači da se slažete s uvjetima i odredbama kognitivnih usluga.

### Zadatak - kreirajte projekt klasifikatora slika

1. Pokrenite Custom Vision portal na [CustomVision.ai](https://customvision.ai) i prijavite se s Microsoft računom koji ste koristili za svoj Azure račun.

1. Slijedite [sekciju za kreiranje novog projekta u vodiču za brzi početak na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) kako biste kreirali novi projekt Custom Vision. UI se može mijenjati, a ova dokumentacija uvijek je najnoviji referentni izvor.

    Nazovite svoj projekt `fruit-quality-detector`.

    Kada kreirate svoj projekt, obavezno koristite resurs `fruit-quality-detector-training` koji ste ranije kreirali. Koristite *Classification* kao tip projekta, *Multiclass* kao tip klasifikacije i *Food* kao domen.

    ![Postavke za projekt Custom Vision s nazivom postavljenim na fruit-quality-detector, bez opisa, resursom postavljenim na fruit-quality-detector-training, tipom projekta postavljenim na classification, tipom klasifikacije postavljenim na multi class i domenom postavljenom na food](../../../../../translated_images/hr/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.png)

✅ Odvojite malo vremena za istraživanje Custom Vision UI-ja za vaš klasifikator slika.

### Zadatak - obučite svoj projekt klasifikatora slika

Da biste obučili klasifikator slika, trebat će vam više slika voća, i dobrog i lošeg kvaliteta, koje ćete označiti kao dobro i loše, poput zrele i prezrele banane.
💁 Ovi klasifikatori mogu klasificirati slike bilo čega, pa ako nemate voće različite kvalitete pri ruci, možete koristiti dvije različite vrste voća ili mačke i pse!
Idealan scenarij je da svaka slika prikazuje samo voće, s dosljednom pozadinom ili širokim rasponom pozadina. Pobrinite se da u pozadini nema ničega što bi bilo specifično za zrelo ili nezrelo voće.

> 💁 Važno je da pozadine nisu specifične, niti da postoje predmeti koji nisu povezani s onim što se klasificira za svaki tag, jer bi klasifikator mogao klasificirati na temelju pozadine. Postojao je klasifikator za rak kože koji je treniran na madežima, normalnim i kancerogenim, a kancerogeni su uvijek imali ravnala uz njih za mjerenje veličine. Ispostavilo se da je klasifikator bio gotovo 100% točan u prepoznavanju ravnala na slikama, a ne kancerogenih madeža.

Klasifikatori slika rade na vrlo niskoj rezoluciji. Na primjer, Custom Vision može koristiti slike za treniranje i predviđanje do 10240x10240, ali model trenira i pokreće na slikama veličine 227x227. Veće slike se smanjuju na ovu veličinu, pa osigurajte da ono što klasificirate zauzima velik dio slike, inače bi moglo biti premalo na manjoj slici koju koristi klasifikator.

1. Prikupite slike za svoj klasifikator. Trebat će vam najmanje 5 slika za svaki tag kako biste trenirali klasifikator, ali što više, to bolje. Također će vam trebati nekoliko dodatnih slika za testiranje klasifikatora. Sve slike trebaju biti različite slike iste stvari. Na primjer:

    * Koristeći 2 zrele banane, snimite nekoliko slika svake iz različitih kutova, snimajući najmanje 7 slika (5 za treniranje, 2 za testiranje), ali idealno više.

        ![Fotografije 2 različite banane](../../../../../translated_images/hr/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.png)

    * Ponovite isti postupak koristeći 2 nezrele banane.

    Trebali biste imati najmanje 10 slika za treniranje, s najmanje 5 zrelih i 5 nezrelih, te 4 slike za testiranje, 2 zrele i 2 nezrele. Vaše slike trebaju biti u png ili jpeg formatu, manje od 6MB. Ako ih snimate iPhoneom, na primjer, mogu biti slike visoke rezolucije u HEIC formatu, pa će ih trebati pretvoriti i možda smanjiti. Što više slika, to bolje, i trebali biste imati sličan broj zrelih i nezrelih.

    Ako nemate i zrelo i nezrelo voće, možete koristiti različite vrste voća ili bilo koja dva dostupna predmeta. Također možete pronaći neke primjere slika u [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) mapi zrelih i nezrelih banana koje možete koristiti.

1. Slijedite [odjeljak za učitavanje i označavanje slika u vodiču za izradu klasifikatora na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) kako biste učitali slike za treniranje. Označite zrelo voće kao `ripe`, a nezrelo voće kao `unripe`.

    ![Dijalozi za učitavanje koji prikazuju učitavanje slika zrelih i nezrelih banana](../../../../../translated_images/hr/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.png)

1. Slijedite [odjeljak za treniranje klasifikatora u vodiču za izradu klasifikatora na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) kako biste trenirali klasifikator slika na učitanim slikama.

    Bit će vam ponuđen izbor vrste treniranja. Odaberite **Quick Training**.

Klasifikator će se zatim trenirati. Proces treniranja trajat će nekoliko minuta.

> 🍌 Ako odlučite pojesti svoje voće dok se klasifikator trenira, pobrinite se da imate dovoljno slika za testiranje!

## Testirajte svoj klasifikator slika

Nakon što je vaš klasifikator treniran, možete ga testirati tako da mu date novu sliku za klasifikaciju.

### Zadatak - testirajte svoj klasifikator slika

1. Slijedite [dokumentaciju za testiranje modela na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) kako biste testirali svoj klasifikator slika. Koristite slike za testiranje koje ste ranije stvorili, a ne slike koje ste koristili za treniranje.

    ![Nezrela banana predviđena kao nezrela s 98.9% vjerojatnosti, zrela s 1.1% vjerojatnosti](../../../../../translated_images/hr/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.png)

1. Isprobajte sve slike za testiranje koje imate i promatrajte vjerojatnosti.

## Ponovno trenirajte svoj klasifikator slika

Kada testirate svoj klasifikator, možda neće dati rezultate koje očekujete. Klasifikatori slika koriste strojno učenje za predviđanje što se nalazi na slici, na temelju vjerojatnosti da određene značajke slike znače da odgovara određenom tagu. Ne razumije što je na slici - ne zna što je banana niti razumije što čini bananu bananom, a ne brodom. Možete poboljšati svoj klasifikator ponovnim treniranjem s slikama koje pogrešno klasificira.

Svaki put kada napravite predviđanje koristeći opciju brzog testiranja, slika i rezultati se pohranjuju. Te slike možete koristiti za ponovno treniranje modela.

### Zadatak - ponovno trenirajte svoj klasifikator slika

1. Slijedite [dokumentaciju za korištenje predviđene slike za treniranje na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) kako biste ponovno trenirali svoj model, koristeći ispravan tag za svaku sliku.

1. Nakon što je vaš model ponovno treniran, testirajte ga na novim slikama.

---

## 🚀 Izazov

Što mislite da bi se dogodilo ako biste koristili sliku jagode s modelom treniranim na bananama, ili sliku napuhane banane, ili osobu u kostimu banane, ili čak žuti crtani lik poput nekoga iz Simpsona?

Isprobajte i pogledajte kakva su predviđanja. Slike za isprobavanje možete pronaći koristeći [Bing pretraživanje slika](https://www.bing.com/images/trending).

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Pregled i samostalno učenje

* Kada ste trenirali svoj klasifikator, vidjeli ste vrijednosti za *Precision*, *Recall* i *AP* koje ocjenjuju model koji je stvoren. Pročitajte što te vrijednosti znače koristeći [odjeljak za evaluaciju klasifikatora u vodiču za izradu klasifikatora na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Pročitajte kako poboljšati svoj klasifikator koristeći [kako poboljšati svoj Custom Vision model na Microsoft dokumentaciji](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Zadatak

[Trenirajte svoj klasifikator za više vrsta voća i povrća](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.