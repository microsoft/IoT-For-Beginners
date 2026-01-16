<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-28T11:32:46+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "ro"
}
-->
# Vizualizați datele GDD folosind un Jupyter Notebook

## Instrucțiuni

În această lecție ați colectat date GDD folosind un senzor IoT. Pentru a obține date GDD de calitate, trebuie să colectați date pentru mai multe zile. Pentru a ajuta la vizualizarea datelor de temperatură și calcularea GDD, puteți utiliza instrumente precum [Jupyter Notebooks](https://jupyter.org) pentru a analiza datele.

Începeți prin colectarea datelor pentru câteva zile. Va trebui să vă asigurați că codul serverului rulează tot timpul cât dispozitivul IoT este activ, fie ajustând setările de gestionare a energiei, fie rulând ceva precum [acest script Python pentru menținerea sistemului activ](https://github.com/jaqsparow/keep-system-active).

După ce aveți datele de temperatură, puteți utiliza Jupyter Notebook-ul din acest depozit pentru a le vizualiza și a calcula GDD. Jupyter notebooks combină codul și instrucțiunile în blocuri numite *celule*, de obicei cod în Python. Puteți citi instrucțiunile, apoi rula fiecare bloc de cod, bloc cu bloc. De asemenea, puteți edita codul. În acest notebook, de exemplu, puteți edita temperatura de bază utilizată pentru a calcula GDD pentru planta dvs.

1. Creați un folder numit `gdd-calculation`

1. Descărcați fișierul [gdd.ipynb](./code-notebook/gdd.ipynb) și copiați-l în folderul `gdd-calculation`.

1. Copiați fișierul `temperature.csv` creat de serverul MQTT.

1. Creați un nou mediu virtual Python în folderul `gdd-calculation`.

1. Instalați câteva pachete pip pentru Jupyter notebooks, împreună cu biblioteci necesare pentru gestionarea și reprezentarea grafică a datelor:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Rulați notebook-ul în Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter va porni și va deschide notebook-ul în browserul dvs. Parcurgeți instrucțiunile din notebook pentru a vizualiza temperaturile măsurate și a calcula zilele de grad de creștere.

    ![Notebook-ul Jupyter](../../../../../translated_images/ro/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubrică

| Criterii | Exemplar | Adecvat | Necesită îmbunătățiri |
| -------- | --------- | ------- | --------------------- |
| Capturarea datelor | Capturați cel puțin 2 zile complete de date | Capturați cel puțin 1 zi completă de date | Capturați câteva date |
| Calcularea GDD | Rulați cu succes notebook-ul și calculați GDD | Rulați cu succes notebook-ul | Nu reușiți să rulați notebook-ul |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.