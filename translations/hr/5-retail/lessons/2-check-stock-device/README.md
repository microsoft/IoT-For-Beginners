<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-28T14:26:06+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "hr"
}
-->
# Provjera zaliha s IoT uređajem

![Sketchnote pregled ove lekcije](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.hr.jpg)

> Sketchnote autorice [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Uvod

U prethodnoj lekciji naučili ste o različitim primjenama detekcije objekata u maloprodaji. Također ste naučili kako trenirati detektor objekata za prepoznavanje zaliha. U ovoj lekciji naučit ćete kako koristiti svoj detektor objekata s IoT uređaja za brojanje zaliha.

U ovoj lekciji obradit ćemo:

* [Brojanje zaliha](../../../../../5-retail/lessons/2-check-stock-device)
* [Pozivanje detektora objekata s IoT uređaja](../../../../../5-retail/lessons/2-check-stock-device)
* [Ograničavajuće okvire](../../../../../5-retail/lessons/2-check-stock-device)
* [Ponovno treniranje modela](../../../../../5-retail/lessons/2-check-stock-device)
* [Brojanje zaliha](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Ovo je posljednja lekcija u ovom projektu, pa nakon što završite ovu lekciju i zadatak, ne zaboravite očistiti svoje cloud usluge. Usluge će vam trebati za dovršetak zadatka, stoga prvo dovršite zadatak.
>
> Ako je potrebno, pogledajte [vodič za čišćenje projekta](../../../clean-up.md) za upute kako to učiniti.

## Brojanje zaliha

Detektori objekata mogu se koristiti za provjeru zaliha, bilo za brojanje zaliha ili za osiguravanje da su zalihe tamo gdje bi trebale biti. IoT uređaji s kamerama mogu se postaviti po cijeloj trgovini za praćenje zaliha, počevši od ključnih mjesta gdje je važno brzo nadopunjavanje, poput područja gdje se drže male količine artikala visoke vrijednosti.

Na primjer, ako kamera gleda na police koje mogu držati 8 konzervi rajčice, a detektor objekata prepozna samo 7 konzervi, tada jedna nedostaje i treba je nadopuniti.

![7 konzervi rajčice na polici, 4 na gornjem redu, 3 na donjem](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.hr.png)

Na slici iznad, detektor objekata prepoznao je 7 konzervi rajčice na polici koja može držati 8 konzervi. IoT uređaj ne samo da može poslati obavijest o potrebi za nadopunjavanjem, već može i naznačiti lokaciju nedostajućeg artikla, što je važan podatak ako koristite robote za nadopunjavanje polica.

> 💁 Ovisno o trgovini i popularnosti artikla, nadopunjavanje se vjerojatno ne bi dogodilo ako nedostaje samo jedna konzerva. Trebali biste izraditi algoritam koji određuje kada treba nadopuniti zalihe na temelju vaših proizvoda, kupaca i drugih kriterija.

✅ U kojim biste drugim scenarijima mogli kombinirati detekciju objekata i robote?

Ponekad se na policama može naći pogrešna roba. To može biti ljudska pogreška prilikom nadopunjavanja ili kupci koji se predomisle i vrate artikl na prvo dostupno mjesto. Kada je riječ o nepropadljivoj robi poput konzervirane hrane, to je samo smetnja. Ako je riječ o kvarljivoj robi poput smrznutih ili rashlađenih proizvoda, to može značiti da se proizvod više ne može prodati jer je nemoguće utvrditi koliko je dugo bio izvan zamrzivača.

Detekcija objekata može se koristiti za otkrivanje neočekivanih artikala, ponovno upozoravajući čovjeka ili robota da što prije vrati artikl na ispravno mjesto.

![Nepoznata konzerva baby kukuruza na polici s rajčicom](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.hr.png)

Na slici iznad, konzerva baby kukuruza stavljena je na policu pored rajčice. Detektor objekata to je prepoznao, omogućujući IoT uređaju da obavijesti čovjeka ili robota da vrati konzervu na ispravno mjesto.

## Pozivanje detektora objekata s IoT uređaja

Detektor objekata koji ste trenirali u prethodnoj lekciji može se pozvati s vašeg IoT uređaja.

### Zadatak - objavite iteraciju svog detektora objekata

Iteracije se objavljuju putem Custom Vision portala.

1. Otvorite Custom Vision portal na [CustomVision.ai](https://customvision.ai) i prijavite se ako već niste. Zatim otvorite svoj projekt `stock-detector`.

1. Odaberite karticu **Performance** iz opcija na vrhu.

1. Odaberite najnoviju iteraciju s popisa *Iterations* sa strane.

1. Kliknite gumb **Publish** za iteraciju.

    ![Gumb za objavu](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.hr.png)

1. U dijaloškom okviru *Publish Model*, postavite *Prediction resource* na resurs `stock-detector-prediction` koji ste stvorili u prethodnoj lekciji. Ostavite naziv kao `Iteration2` i kliknite gumb **Publish**.

1. Nakon objave, kliknite gumb **Prediction URL**. Ovo će prikazati detalje API-ja za predikciju, a te detalje ćete trebati za pozivanje modela s vašeg IoT uređaja. Donji dio označen je *If you have an image file*, i to su detalji koji su vam potrebni. Kopirajte prikazani URL koji će izgledati ovako:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Gdje će `<location>` biti lokacija koju ste koristili prilikom stvaranja Custom Vision resursa, a `<id>` će biti dugi ID sastavljen od slova i brojeva.

    Također kopirajte vrijednost *Prediction-Key*. Ovo je sigurnosni ključ koji morate proslijediti prilikom pozivanja modela. Samo aplikacije koje proslijede ovaj ključ mogu koristiti model, sve ostale aplikacije bit će odbijene.

    ![Dijaloški okvir za API predikcije koji prikazuje URL i ključ](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.hr.png)

✅ Kada se objavi nova iteracija, imat će drugačiji naziv. Kako mislite da biste promijenili iteraciju koju koristi IoT uređaj?

### Zadatak - pozovite svoj detektor objekata s IoT uređaja

Slijedite odgovarajući vodič u nastavku kako biste koristili detektor objekata s vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Jednoplani računalo - Raspberry Pi/Virtualni uređaj](single-board-computer-object-detector.md)

## Ograničavajući okviri

Kada koristite detektor objekata, ne dobivate samo prepoznate objekte s njihovim oznakama i vjerojatnostima, već i ograničavajuće okvire objekata. Oni definiraju gdje je detektor objekata prepoznao objekt s danom vjerojatnošću.

> 💁 Ograničavajući okvir je okvir koji definira područje koje sadrži prepoznati objekt, okvir koji definira granicu za objekt.

Rezultati predikcije u kartici **Predictions** u Custom Visionu imaju ograničavajuće okvire nacrtane na slici koja je poslana na predikciju.

![4 konzerve rajčice na polici s predikcijama za 4 detekcije od 35.8%, 33.5%, 25.7% i 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.hr.png)

Na slici iznad, prepoznate su 4 konzerve rajčice. U rezultatima je crveni kvadrat prekriven za svaki objekt koji je prepoznat na slici, označavajući ograničavajući okvir za sliku.

✅ Otvorite predikcije u Custom Visionu i pogledajte ograničavajuće okvire.

Ograničavajući okviri definirani su s 4 vrijednosti - top, left, height i width. Ove vrijednosti su na skali od 0-1, predstavljajući pozicije kao postotak veličine slike. Ishodište (pozicija 0,0) je gornji lijevi kut slike, tako da je top vrijednost udaljenost od vrha, a dno ograničavajućeg okvira je top plus height.

![Ograničavajući okvir oko konzerve rajčice](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.hr.png)

Slika iznad je široka 600 piksela i visoka 800 piksela. Ograničavajući okvir počinje na 320 piksela od vrha, dajući top koordinatu od 0.4 (800 x 0.4 = 320). S lijeve strane, okvir počinje na 240 piksela, dajući left koordinatu od 0.4 (600 x 0.4 = 240). Visina okvira je 240 piksela, dajući height vrijednost od 0.3 (800 x 0.3 = 240). Širina okvira je 120 piksela, dajući width vrijednost od 0.2 (600 x 0.2 = 120).

| Koordinata | Vrijednost |
| ---------- | ---------: |
| Top        | 0.4       |
| Left       | 0.4       |
| Height     | 0.3       |
| Width      | 0.2       |

Korištenje postotnih vrijednosti od 0-1 znači da bez obzira na veličinu slike, okvir počinje 0.4 puta duž i dolje, te ima visinu od 0.3 i širinu od 0.2.

Možete koristiti ograničavajuće okvire u kombinaciji s vjerojatnostima za procjenu točnosti detekcije. Na primjer, detektor objekata može prepoznati više objekata koji se preklapaju, primjerice prepoznati jednu konzervu unutar druge. Vaš kod može provjeriti ograničavajuće okvire, shvatiti da je to nemoguće, i ignorirati sve objekte koji se značajno preklapaju s drugim objektima.

![Dva ograničavajuća okvira preklapaju konzervu rajčice](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.hr.png)

U primjeru iznad, jedan ograničavajući okvir označava predviđenu konzervu rajčice s 78.3%. Drugi okvir je nešto manji i nalazi se unutar prvog okvira s vjerojatnošću od 64.3%. Vaš kod može provjeriti ograničavajuće okvire, vidjeti da se potpuno preklapaju i ignorirati nižu vjerojatnost jer nije moguće da jedna konzerva bude unutar druge.

✅ Možete li zamisliti situaciju u kojoj je valjano prepoznati jedan objekt unutar drugog?

## Ponovno treniranje modela

Kao i kod klasifikatora slika, možete ponovno trenirati svoj model koristeći podatke prikupljene s vašeg IoT uređaja. Korištenje ovih podataka iz stvarnog svijeta osigurat će da vaš model dobro funkcionira kada se koristi s vašeg IoT uređaja.

Za razliku od klasifikatora slika, ne možete samo označiti sliku. Umjesto toga, morate pregledati svaki ograničavajući okvir koji je model prepoznao. Ako je okvir oko pogrešnog objekta, treba ga izbrisati, ako je na pogrešnom mjestu, treba ga prilagoditi.

### Zadatak - ponovno treniranje modela

1. Provjerite jeste li prikupili niz slika koristeći svoj IoT uređaj.

1. Na kartici **Predictions**, odaberite sliku. Vidjet ćete crvene okvire koji označavaju ograničavajuće okvire prepoznatih objekata.

1. Pregledajte svaki ograničavajući okvir. Prvo ga odaberite i vidjet ćete skočni prozor s oznakom. Koristite ručke na uglovima okvira za prilagodbu veličine ako je potrebno. Ako je oznaka pogrešna, uklonite je pomoću gumba **X** i dodajte ispravnu oznaku. Ako okvir ne sadrži objekt, izbrišite ga pomoću gumba za smeće.

1. Zatvorite uređivač kada završite i slika će se premjestiti s kartice **Predictions** na karticu **Training Images**. Ponovite postupak za sve predikcije.

1. Koristite gumb **Train** za ponovno treniranje modela. Nakon što se model trenira, objavite iteraciju i ažurirajte svoj IoT uređaj da koristi URL nove iteracije.

1. Ponovno implementirajte svoj kod i testirajte svoj IoT uređaj.

## Brojanje zaliha

Kombinacijom broja prepoznatih objekata i ograničavajućih okvira možete brojati zalihe na polici.

### Zadatak - brojanje zaliha

Slijedite odgovarajući vodič u nastavku za brojanje zaliha koristeći rezultate detektora objekata s vašeg IoT uređaja:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Jednoplani računalo - Raspberry Pi/Virtualni uređaj](single-board-computer-count-stock.md)

---

## 🚀 Izazov

Možete li prepoznati pogrešne zalihe? Trenirajte svoj model na više objekata, a zatim ažurirajte svoju aplikaciju da vas upozori ako se prepoznaju pogrešne zalihe.

Možda čak idite korak dalje i prepoznajte zalihe postavljene jedna pored druge na istoj polici te provjerite je li nešto stavljeno na pogrešno mjesto definirajući granice ograničavajućih okvira.

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Pregled i samostalno učenje

* Saznajte više o tome kako arhitektirati sustav za detekciju zaliha od kraja do kraja iz [vodiča za obrazac detekcije nedostatka zaliha na rubu na Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Saznajte druge načine za izgradnju rješenja za maloprodaju od kraja do kraja kombinirajući niz IoT i cloud usluga gledajući ovaj [Iza kulisa rješenja za maloprodaju - Hands On! video na YouTubeu](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Zadatak

[Koristite svoj detektor objekata na rubu](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.