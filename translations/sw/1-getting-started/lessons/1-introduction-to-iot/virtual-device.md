<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T22:19:04+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "sw"
}
-->
# Kompyuta ya bodi moja ya mtandaoni

Badala ya kununua kifaa cha IoT pamoja na sensa na aktueta, unaweza kutumia kompyuta yako kuiga vifaa vya IoT. Mradi wa [CounterFit](https://github.com/CounterFit-IoT/CounterFit) unakuruhusu kuendesha programu kwa ndani inayofanya kazi kama vifaa vya IoT kama sensa na aktueta, na kufikia sensa na aktueta kutoka kwa msimbo wa Python wa ndani ulioandikwa kwa njia sawa na msimbo ambao ungeandika kwenye Raspberry Pi ukitumia vifaa halisi.

## Usanidi

Ili kutumia CounterFit, utahitaji kusakinisha programu fulani ya bure kwenye kompyuta yako.

### Kazi

Sakinisha programu inayohitajika.

1. Sakinisha Python. Rejelea [ukurasa wa upakuaji wa Python](https://www.python.org/downloads/) kwa maelekezo ya kusakinisha toleo jipya la Python.

1. Sakinisha Visual Studio Code (VS Code). Hii ni mhariri utakaotumia kuandika msimbo wa kifaa chako cha mtandaoni kwa Python. Rejelea [hati ya VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) kwa maelekezo ya kusakinisha VS Code.

    > 💁 Una uhuru wa kutumia IDE au mhariri wowote wa Python kwa masomo haya ikiwa una zana unayopendelea, lakini masomo yatatoa maelekezo kulingana na kutumia VS Code.

1. Sakinisha kiendelezi cha VS Code Pylance. Hiki ni kiendelezi cha VS Code kinachotoa msaada wa lugha ya Python. Rejelea [hati ya kiendelezi cha Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) kwa maelekezo ya kusakinisha kiendelezi hiki kwenye VS Code.

Maelekezo ya kusakinisha na kusanidi programu ya CounterFit yatatolewa wakati unaofaa katika maelekezo ya kazi kwani inasakinishwa kwa msingi wa mradi.

## Hello World

Ni jadi kuanza na lugha mpya ya programu au teknolojia kwa kuunda programu ya 'Hello World' - programu ndogo inayochapisha maandishi kama `"Hello World"` ili kuonyesha kuwa zana zote zimesanidiwa kwa usahihi.

Programu ya Hello World kwa vifaa vya IoT vya mtandaoni itahakikisha kuwa Python na Visual Studio Code zimesakinishwa kwa usahihi. Pia itaunganishwa na CounterFit kwa sensa na aktueta za mtandaoni. Haitatumia vifaa vyovyote, itajiunganisha tu kuthibitisha kila kitu kinafanya kazi.

Programu hii itakuwa kwenye folda inayoitwa `nightlight`, na itatumika tena na msimbo tofauti katika sehemu za baadaye za kazi hii ili kujenga programu ya taa ya usiku.

### Sanidi mazingira ya mtandaoni ya Python

Moja ya vipengele vyenye nguvu vya Python ni uwezo wa kusakinisha [pakiti za Pip](https://pypi.org) - hizi ni pakiti za msimbo zilizoandikwa na watu wengine na kuchapishwa mtandaoni. Unaweza kusakinisha pakiti ya Pip kwenye kompyuta yako kwa amri moja, kisha kutumia pakiti hiyo kwenye msimbo wako. Utatumia Pip kusakinisha pakiti ya kuzungumza na CounterFit.

Kwa chaguo-msingi, unapoweka pakiti, inapatikana kila mahali kwenye kompyuta yako, na hii inaweza kusababisha matatizo na matoleo ya pakiti - kama programu moja kutegemea toleo moja la pakiti ambalo linavunjika unapoweka toleo jipya kwa programu tofauti. Ili kuepuka tatizo hili, unaweza kutumia [mazingira ya mtandaoni ya Python](https://docs.python.org/3/library/venv.html), kimsingi nakala ya Python kwenye folda maalum, na unapoweka pakiti za Pip zinapatikana tu kwenye folda hiyo.

> 💁 Ikiwa unatumia Raspberry Pi basi hukusakinisha mazingira ya mtandaoni kwenye kifaa hicho kudhibiti pakiti za Pip, badala yake unatumia pakiti za kimataifa, kwani pakiti za Grove zimesakinishwa kimataifa na hati ya usakinishaji.

#### Kazi - sanidi mazingira ya mtandaoni ya Python

Sanidi mazingira ya mtandaoni ya Python na usakinishe pakiti za Pip kwa CounterFit.

1. Kutoka kwa terminal au mstari wa amri, endesha yafuatayo mahali unapotaka kuunda na kuingia kwenye saraka mpya:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Sasa endesha yafuatayo kuunda mazingira ya mtandaoni kwenye folda ya `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Unahitaji kuita waziwazi `python3` kuunda mazingira ya mtandaoni iwapo una Python 2 iliyosakinishwa pamoja na Python 3 (toleo jipya). Ikiwa una Python 2 iliyosakinishwa basi kuita `python` kutatumia Python 2 badala ya Python 3.

1. Washa mazingira ya mtandaoni:

    * Kwenye Windows:
        * Ikiwa unatumia Command Prompt, au Command Prompt kupitia Windows Terminal, endesha:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ikiwa unatumia PowerShell, endesha:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Ikiwa unapata hitilafu kuhusu kuendesha hati zilizozuiwa kwenye mfumo huu, utahitaji kuwezesha kuendesha hati kwa kuweka sera ya utekelezaji inayofaa. Unaweza kufanya hivyo kwa kuzindua PowerShell kama msimamizi, kisha kuendesha amri ifuatayo:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Ingiza `Y` unapoulizwa kuthibitisha. Kisha zindua tena PowerShell na jaribu tena.

            Unaweza kuweka upya sera hii ya utekelezaji baadaye ikiwa inahitajika. Unaweza kusoma zaidi kuhusu hili kwenye [ukurasa wa sera za utekelezaji kwenye Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Kwenye macOS au Linux, endesha:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Amri hizi zinapaswa kuendeshwa kutoka mahali ulipoendesha amri ya kuunda mazingira ya mtandaoni. Hautahitaji kamwe kuingia kwenye folda ya `.venv`, unapaswa kila wakati kuendesha amri ya kuwasha na amri zozote za kusakinisha pakiti au kuendesha msimbo kutoka kwenye folda uliyokuwa ukiunda mazingira ya mtandaoni.

1. Mara tu mazingira ya mtandaoni yamewashwa, amri ya chaguo-msingi `python` itaendesha toleo la Python lililotumika kuunda mazingira ya mtandaoni. Endesha yafuatayo kupata toleo:

    ```sh
    python --version
    ```

    Matokeo yanapaswa kuwa na yafuatayo:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Toleo lako la Python linaweza kuwa tofauti - mradi ni toleo la 3.6 au zaidi uko sawa. Ikiwa sivyo, futa folda hii, sakinisha toleo jipya la Python na jaribu tena.

1. Endesha amri zifuatazo kusakinisha pakiti za Pip kwa CounterFit. Pakiti hizi zinajumuisha programu kuu ya CounterFit pamoja na shims za vifaa vya Grove. Shims hizi zinakuruhusu kuandika msimbo kana kwamba unaprogramu ukitumia sensa na aktueta halisi kutoka kwa ekosistimu ya Grove lakini zimeunganishwa na vifaa vya IoT vya mtandaoni.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Pakiti hizi za Pip zitasakinishwa tu kwenye mazingira ya mtandaoni, na hazitapatikana nje ya mazingira haya.

### Andika msimbo

Mara tu mazingira ya mtandaoni ya Python yameandaliwa, unaweza kuandika msimbo wa programu ya 'Hello World'.

#### Kazi - andika msimbo

Unda programu ya Python kuchapisha `"Hello World"` kwenye koni.

1. Kutoka kwa terminal au mstari wa amri, endesha yafuatayo ndani ya mazingira ya mtandaoni kuunda faili ya Python inayoitwa `app.py`:

    * Kutoka Windows endesha:

        ```cmd
        type nul > app.py
        ```

    * Kwenye macOS au Linux, endesha:

        ```cmd
        touch app.py
        ```

1. Fungua folda ya sasa kwenye VS Code:

    ```sh
    code .
    ```

    > 💁 Ikiwa terminal yako inarudisha `command not found` kwenye macOS inamaanisha VS Code haijaongezwa kwenye PATH yako. Unaweza kuongeza VS Code kwenye PATH yako kwa kufuata maelekezo katika [sehemu ya kuzindua kutoka mstari wa amri kwenye hati ya VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) na endesha amri baadaye. VS Code imewekwa kwenye PATH yako kwa chaguo-msingi kwenye Windows na Linux.

1. Wakati VS Code inazinduliwa, itawasha mazingira ya mtandaoni ya Python. Mazingira ya mtandaoni yaliyochaguliwa yataonekana kwenye upau wa hali ya chini:

    ![VS Code ikionyesha mazingira ya mtandaoni yaliyochaguliwa](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.sw.png)

1. Ikiwa terminal ya VS Code tayari inaendesha wakati VS Code inapoanza, haitakuwa na mazingira ya mtandaoni yaliyoamilishwa ndani yake. Jambo rahisi kufanya ni kuua terminal kwa kutumia kitufe cha **Kill the active terminal instance**:

    ![Kitufe cha VS Code Kill the active terminal instance](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.sw.png)

    Unaweza kujua ikiwa terminal ina mazingira ya mtandaoni yaliyoamilishwa kwani jina la mazingira ya mtandaoni litakuwa kiambishi awali kwenye prompt ya terminal. Kwa mfano, inaweza kuwa:

    ```sh
    (.venv) ➜  nightlight
    ```

    Ikiwa huna `.venv` kama kiambishi awali kwenye prompt, mazingira ya mtandaoni hayajaamilishwa kwenye terminal.

1. Zindua terminal mpya ya VS Code kwa kuchagua *Terminal -> New Terminal*, au kubonyeza `` CTRL+` ``. Terminal mpya itapakia mazingira ya mtandaoni, na wito wa kuamilisha hii utaonekana kwenye terminal. Prompt pia itakuwa na jina la mazingira ya mtandaoni (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Fungua faili ya `app.py` kutoka kwa kivinjari cha VS Code na ongeza msimbo ufuatao:

    ```python
    print('Hello World!')
    ```

    Kazi ya `print` inachapisha chochote kinachopitishwa kwake kwenye koni.

1. Kutoka kwa terminal ya VS Code, endesha yafuatayo kuendesha programu yako ya Python:

    ```sh
    python app.py
    ```

    Yafuatayo yatakuwa kwenye matokeo:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Programu yako ya 'Hello World' imefanikiwa!

### Unganisha 'vifaa'

Kama hatua ya pili ya 'Hello World', utaendesha programu ya CounterFit na kuunganisha msimbo wako nayo. Hii ni sawa na kuunganisha vifaa vya IoT kwenye kifaa cha maendeleo.

#### Kazi - unganisha 'vifaa'

1. Kutoka kwa terminal ya VS Code, zindua programu ya CounterFit kwa amri ifuatayo:

    ```sh
    counterfit
    ```

    Programu itaanza kuendesha na kufunguka kwenye kivinjari chako cha mtandao:

    ![Programu ya CounterFit ikifanya kazi kwenye kivinjari](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.sw.png)

    Itakuwa imewekwa alama kama *Disconnected*, na LED kwenye kona ya juu-kulia imezimwa.

1. Ongeza msimbo ufuatao juu ya `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Msimbo huu unaleta darasa la `CounterFitConnection` kutoka kwa moduli ya `counterfit_connection`, ambayo inatoka kwa pakiti ya pip ya `counterfit-connection` uliyosakinisha awali. Kisha inaanzisha muunganisho na programu ya CounterFit inayofanya kazi kwenye `127.0.0.1`, ambayo ni anwani ya IP unayoweza kutumia kila wakati kufikia kompyuta yako ya ndani (inayojulikana kama *localhost*), kwenye bandari 5000.

    > 💁 Ikiwa una programu nyingine zinazofanya kazi kwenye bandari 5000, unaweza kubadilisha hii kwa kusasisha bandari kwenye msimbo, na kuendesha CounterFit ukitumia `CounterFit --port <port_number>`, ukibadilisha `<port_number>` na bandari unayotaka kutumia.

1. Utahitaji kuzindua terminal mpya ya VS Code kwa kuchagua kitufe cha **Create a new integrated terminal**. Hii ni kwa sababu programu ya CounterFit inaendesha kwenye terminal ya sasa.

    ![Kitufe cha VS Code Create a new integrated terminal](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.sw.png)

1. Katika terminal hii mpya, endesha faili ya `app.py` kama awali. Hali ya CounterFit itabadilika kuwa **Connected** na LED itawaka.

    ![CounterFit ikionyesha kama imeunganishwa](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.sw.png)

> 💁 Unaweza kupata msimbo huu kwenye [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) folda.

😀 Muunganisho wako na vifaa umefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asilia katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.