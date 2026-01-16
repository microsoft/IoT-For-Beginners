<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T15:13:27+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "hr"
}
-->
# Vizualizacija GDD podataka pomoću Jupyter Notebooka

## Upute

U ovoj lekciji prikupili ste GDD podatke pomoću IoT senzora. Da biste dobili kvalitetne GDD podatke, potrebno je prikupljati podatke tijekom više dana. Za vizualizaciju temperaturnih podataka i izračunavanje GDD-a možete koristiti alate poput [Jupyter Notebooks](https://jupyter.org) za analizu podataka.

Započnite prikupljanjem podataka za nekoliko dana. Morate osigurati da vaš poslužiteljski kod radi cijelo vrijeme dok vaš IoT uređaj radi, bilo prilagodbom postavki upravljanja energijom ili pokretanjem nečega poput [ovog Python skripta za održavanje sustava aktivnim](https://github.com/jaqsparow/keep-system-active).

Kada imate temperaturne podatke, možete koristiti Jupyter Notebook u ovom repozitoriju za njihovu vizualizaciju i izračunavanje GDD-a. Jupyter notebook kombinira kod i upute u blokovima koji se nazivaju *ćelije*, često kod u Pythonu. Možete čitati upute, a zatim pokretati svaki blok koda, blok po blok. Također možete uređivati kod. Na primjer, u ovom notebooku možete urediti osnovnu temperaturu koja se koristi za izračunavanje GDD-a za vašu biljku.

1. Kreirajte mapu pod nazivom `gdd-calculation`

1. Preuzmite datoteku [gdd.ipynb](./code-notebook/gdd.ipynb) i kopirajte je u mapu `gdd-calculation`.

1. Kopirajte datoteku `temperature.csv` koju je kreirao MQTT poslužitelj.

1. Kreirajte novi Python virtualni okoliš u mapi `gdd-calculation`.

1. Instalirajte nekoliko pip paketa za Jupyter notebooke, zajedno s bibliotekama potrebnim za upravljanje i prikaz podataka:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Pokrenite notebook u Jupyteru:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter će se pokrenuti i otvoriti notebook u vašem pregledniku. Prođite kroz upute u notebooku kako biste vizualizirali izmjerene temperature i izračunali dane rasta (GDD).

    ![Jupyter notebook](../../../../../translated_images/hr/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrika

| Kriterij | Izvrsno | Zadovoljavajuće | Potrebno poboljšanje |
| -------- | -------- | --------------- | -------------------- |
| Prikupljanje podataka | Prikupljeno najmanje 2 kompletna dana podataka | Prikupljen najmanje 1 kompletan dan podataka | Prikupljeno nešto podataka |
| Izračunavanje GDD-a | Uspješno pokrenut notebook i izračunat GDD | Uspješno pokrenut notebook | Nije moguće pokrenuti notebook |

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.