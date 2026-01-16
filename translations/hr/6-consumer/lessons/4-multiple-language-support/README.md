<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-28T13:04:48+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "hr"
}
-->
# Podrška za više jezika

![Sketchnote pregled ove lekcije](../../../../../translated_images/hr/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Sketchnote autor [Nitya Narasimhan](https://github.com/nitya). Kliknite na sliku za veću verziju.

Ovaj video daje pregled Azure govorne usluge, pokrivajući pretvaranje govora u tekst i teksta u govor iz prethodnih lekcija, kao i prevođenje govora, temu koja se obrađuje u ovoj lekciji:

[![Prepoznavanje govora s nekoliko linija Python koda s Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Kliknite na sliku iznad za gledanje videa

## Kviz prije predavanja

[Kviz prije predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Uvod

U posljednje tri lekcije naučili ste o pretvaranju govora u tekst, razumijevanju jezika i pretvaranju teksta u govor, sve uz pomoć umjetne inteligencije. Još jedno područje ljudske komunikacije u kojem AI može pomoći je prevođenje jezika - pretvaranje s jednog jezika na drugi, poput engleskog na francuski.

U ovoj lekciji naučit ćete kako koristiti AI za prevođenje teksta, omogućujući vašem pametnom mjeraču vremena interakciju s korisnicima na više jezika.

U ovoj lekciji obradit ćemo:

* [Prevođenje teksta](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Usluge prevođenja](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Stvaranje resursa za prevoditelja](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Podrška za više jezika u aplikacijama uz prevođenje](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Prevođenje teksta pomoću AI usluge](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Ovo je posljednja lekcija u ovom projektu, pa nakon završetka lekcije i zadatka, ne zaboravite očistiti svoje cloud usluge. Trebat će vam usluge za dovršetak zadatka, pa se pobrinite da prvo završite zadatak.
>
> Ako je potrebno, pogledajte [vodič za čišćenje projekta](../../../clean-up.md) za upute kako to učiniti.

## Prevođenje teksta

Prevođenje teksta je problem računalne znanosti koji se istražuje više od 70 godina, a tek sada, zahvaljujući napretku u AI-u i računalnoj snazi, dolazi do točke gdje je gotovo jednako dobro kao ljudski prevoditelji.

> 💁 Porijeklo se može pratiti još dalje, do [Al-Kindija](https://wikipedia.org/wiki/Al-Kindi), arapskog kriptografa iz 9. stoljeća koji je razvio tehnike za prevođenje jezika.

### Strojno prevođenje

Prevođenje teksta započelo je kao tehnologija poznata kao strojno prevođenje (MT), koja može prevoditi između različitih jezičnih parova. MT radi zamjenom riječi u jednom jeziku s drugima, dodajući tehnike za odabir ispravnih načina prevođenja fraza ili dijelova rečenica kada jednostavno prevođenje riječ po riječ nema smisla.

> 🎓 Kada prevoditelji podržavaju prevođenje između jednog jezika i drugog, to se naziva *jezični parovi*. Različiti alati podržavaju različite jezične parove, a ti parovi možda nisu potpuni. Na primjer, prevoditelj može podržavati engleski na španjolski kao jezični par, i španjolski na talijanski kao jezični par, ali ne i engleski na talijanski.

Na primjer, prevođenje "Hello world" s engleskog na francuski može se obaviti zamjenom - "Bonjour" za "Hello", i "le monde" za "world", što dovodi do ispravnog prijevoda "Bonjour le monde".

Zamjene ne funkcioniraju kada različiti jezici koriste različite načine izražavanja iste stvari. Na primjer, engleska rečenica "My name is Jim" prevodi se u "Je m'appelle Jim" na francuski - doslovno "Ja se zovem Jim". "Je" je francuski za "ja", "moi" je "me", ali se spaja s glagolom jer počinje samoglasnikom, pa postaje "m'", "appelle" znači zvati, a "Jim" se ne prevodi jer je ime, a ne riječ koja se može prevesti. Redoslijed riječi također postaje problem - jednostavna zamjena "Je m'appelle Jim" postaje "I myself call Jim", s drugačijim redoslijedom riječi u odnosu na engleski.

> 💁 Neke riječi se nikada ne prevode - moje ime je Jim bez obzira na jezik koji se koristi za predstavljanje. Kada se prevodi na jezike koji koriste različite abecede ili različita slova za različite zvukove, tada se riječi mogu *transliterirati*, odnosno odabrati slova ili znakovi koji daju odgovarajući zvuk kako bi zvučali isto kao zadana riječ.

Idiomi također predstavljaju problem za prevođenje. To su fraze koje imaju razumljivo značenje koje se razlikuje od doslovnog tumačenja riječi. Na primjer, u engleskom idiom "I've got ants in my pants" ne odnosi se doslovno na mrave u odjeći, već na nemir. Ako biste ovo preveli na njemački, zbunili biste slušatelja, jer njemačka verzija glasi "Imam bumbare u stražnjici".

> 💁 Različiti lokaliteti dodaju različite složenosti. Kod idioma "ants in your pants", u američkom engleskom "pants" se odnosi na vanjsku odjeću, dok u britanskom engleskom "pants" znači donje rublje.

✅ Ako govorite više jezika, razmislite o nekim frazama koje se ne prevode direktno.

Sustavi za strojno prevođenje oslanjaju se na velike baze podataka pravila koja opisuju kako prevesti određene fraze i idiome, zajedno sa statističkim metodama za odabir odgovarajućih prijevoda iz mogućih opcija. Ove statističke metode koriste ogromne baze podataka djela koje su ljudi preveli na više jezika kako bi odabrali najvjerojatniji prijevod, tehniku zvanu *statističko strojno prevođenje*. Mnogi od njih koriste međureprezentacije jezika, omogućujući jednom jeziku da se prevede na međureprezentaciju, a zatim s međureprezentacije na drugi jezik. Na taj način dodavanje više jezika uključuje prijevode na i s međureprezentacije, a ne na i s svih drugih jezika.

### Neuronsko prevođenje

Neuronsko prevođenje uključuje korištenje snage AI-a za prevođenje, obično prevodeći cijele rečenice pomoću jednog modela. Ovi modeli se treniraju na ogromnim skupovima podataka koje su ljudi preveli, poput web stranica, knjiga i dokumentacije Ujedinjenih naroda.

Modeli za neuronsko prevođenje obično su manji od modela za strojno prevođenje jer ne trebaju velike baze podataka fraza i idioma. Moderni AI servisi koji pružaju prijevode često kombiniraju više tehnika, miješajući statističko strojno prevođenje i neuronsko prevođenje.

Ne postoji 1:1 prijevod za bilo koji jezični par. Različiti modeli za prevođenje će proizvesti malo drugačije rezultate ovisno o podacima koji su korišteni za treniranje modela. Prijevodi nisu uvijek simetrični - ako prevedete rečenicu s jednog jezika na drugi, a zatim natrag na prvi jezik, možda ćete dobiti malo drugačiju rečenicu kao rezultat.

✅ Isprobajte različite online prevoditelje poput [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) ili Apple aplikaciju za prevođenje. Usporedite prevedene verzije nekoliko rečenica. Također pokušajte prevesti u jednom, a zatim prevesti natrag u drugom.

## Usluge prevođenja

Postoji niz AI usluga koje se mogu koristiti iz vaših aplikacija za prevođenje govora i teksta.

### Cognitive services Speech service

![Logo govorne usluge](../../../../../translated_images/hr/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Govorna usluga koju ste koristili u proteklim lekcijama ima mogućnosti prevođenja za prepoznavanje govora. Kada prepoznate govor, možete zatražiti ne samo tekst govora na istom jeziku, već i na drugim jezicima.

> 💁 Ovo je dostupno samo putem govornog SDK-a, REST API nema ugrađene prijevode.

### Cognitive services Translator service

![Logo usluge prevoditelja](../../../../../translated_images/hr/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

Usluga Translator je posvećena usluga prevođenja koja može prevesti tekst s jednog jezika na jedan ili više ciljanih jezika. Osim prevođenja, podržava širok raspon dodatnih značajki, uključujući maskiranje vulgarnosti. Također vam omogućuje da pružite specifičan prijevod za određenu riječ ili rečenicu, kako biste radili s pojmovima koje ne želite prevesti ili imate specifičan poznati prijevod.

Na primjer, kada prevodite rečenicu "I have a Raspberry Pi", koja se odnosi na jednopločasto računalo, na drugi jezik poput francuskog, želite zadržati naziv "Raspberry Pi" kakav jest, i ne prevoditi ga, dajući "J’ai un Raspberry Pi" umjesto "J’ai une pi aux framboises".

## Stvaranje resursa za prevoditelja

Za ovu lekciju trebat će vam resurs za prevoditelja. Koristit ćete REST API za prevođenje teksta.

### Zadatak - stvaranje resursa za prevoditelja

1. Iz vašeg terminala ili naredbenog retka, pokrenite sljedeću naredbu za stvaranje resursa za prevoditelja u vašoj `smart-timer` grupi resursa.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamijenite `<location>` lokacijom koju ste koristili prilikom stvaranja grupe resursa.

1. Dohvatite ključ za uslugu prevoditelja:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Kopirajte jedan od ključeva.

## Podrška za više jezika u aplikacijama uz prevođenje

U idealnom svijetu, cijela vaša aplikacija trebala bi razumjeti što više različitih jezika, od slušanja govora, do razumijevanja jezika, do odgovaranja govorom. Ovo je puno posla, pa usluge prevođenja mogu ubrzati vrijeme isporuke vaše aplikacije.

![Arhitektura pametnog mjerača vremena koja prevodi japanski na engleski, obrađuje na engleskom, a zatim prevodi natrag na japanski](../../../../../translated_images/hr/translated-smart-timer.08ac20057fdc5c37.webp)

Zamislite da gradite pametni mjerač vremena koji koristi engleski od početka do kraja, razumijevanje govornog engleskog i pretvaranje toga u tekst, provođenje razumijevanja jezika na engleskom, stvaranje odgovora na engleskom i odgovaranje engleskim govorom. Ako želite dodati podršku za japanski, mogli biste započeti s prevođenjem govornog japanskog u engleski tekst, zatim zadržati jezgru aplikacije istom, a zatim prevesti tekst odgovora na japanski prije nego što odgovorite govorom. Ovo bi vam omogućilo brzo dodavanje podrške za japanski, a kasnije možete proširiti na pružanje potpune podrške za japanski od početka do kraja.

> 💁 Nedostatak oslanjanja na strojno prevođenje je taj što različiti jezici i kulture imaju različite načine izražavanja istih stvari, pa prijevod možda neće odgovarati izrazu koji očekujete.

Strojno prevođenje također otvara mogućnosti za aplikacije i uređaje koji mogu prevoditi sadržaj koji korisnici stvaraju dok ga stvaraju. Znanstvena fantastika redovito prikazuje 'univerzalne prevoditelje', uređaje koji mogu prevoditi s vanzemaljskih jezika na (obično) američki engleski. Ti uređaji su manje znanstvena fantastika, a više znanstvena činjenica, ako zanemarimo dio o vanzemaljcima. Već postoje aplikacije i uređaji koji pružaju prijevod govora i pisanog teksta u stvarnom vremenu, koristeći kombinacije govora i usluga prevođenja.

Jedan primjer je mobilna aplikacija [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), demonstrirana u ovom videu:

[![Microsoft Translator funkcija uživo u akciji](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Kliknite na sliku iznad za gledanje videa

Zamislite da imate takav uređaj na raspolaganju, posebno kada putujete ili komunicirate s ljudima čiji jezik ne poznajete. Automatski uređaji za prevođenje u zračnim lukama ili bolnicama pružili bi prijeko potrebna poboljšanja pristupačnosti.

✅ Istražite: Postoje li komercijalno dostupni IoT uređaji za prevođenje? Što je s mogućnostima prevođenja ugrađenim u pametne uređaje?

> 👽 Iako ne postoje pravi univerzalni prevoditelji koji nam omogućuju razgovor s vanzemaljcima, [Microsoft Translator podržava klingonski](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Prevođenje teksta pomoću AI usluge

Možete koristiti AI uslugu za dodavanje ove mogućnosti prevođenja vašem pametnom mjeraču vremena.

### Zadatak - prevođenje teksta pomoću AI usluge

Prođite kroz relevantni vodič za prevođenje teksta na vašem IoT uređaju:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Jednopločasto računalo - Raspberry Pi](pi-translate-speech.md)
* [Jednopločasto računalo - Virtualni uređaj](virtual-device-translate-speech.md)

---

## 🚀 Izazov

Kako strojno prevođenje može koristiti drugim IoT aplikacijama osim pametnih uređaja? Razmislite o različitim načinima na koje prijevodi mogu pomoći, ne samo s izgovorenim riječima već i s tekstom.

## Kviz nakon predavanja

[Kviz nakon predavanja](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Pregled i samostalno učenje

* Pročitajte više o strojnim prijevodima na [stranici o strojnim prijevodima na Wikipediji](https://wikipedia.org/wiki/Machine_translation)
* Pročitajte više o neuronskim strojnim prijevodima na [stranici o neuronskim strojnim prijevodima na Wikipediji](https://wikipedia.org/wiki/Neural_machine_translation)
* Pogledajte popis podržanih jezika za Microsoft govorne usluge u [dokumentaciji o podršci za jezike i glasove za govornu uslugu na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Zadatak

[Izgradite univerzalni prevoditelj](assignment.md)

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.