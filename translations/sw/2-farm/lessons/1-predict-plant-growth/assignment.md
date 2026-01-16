<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-27T23:20:48+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "sw"
}
-->
# Onyesha data ya GDD kwa kutumia Jupyter Notebook

## Maelekezo

Katika somo hili ulikusanya data ya GDD kwa kutumia sensa ya IoT. Ili kupata data nzuri ya GDD, unahitaji kukusanya data kwa siku kadhaa. Ili kusaidia kuonyesha data ya joto na kuhesabu GDD, unaweza kutumia zana kama [Jupyter Notebooks](https://jupyter.org) kuchambua data hiyo.

Anza kwa kukusanya data kwa siku chache. Utahitaji kuhakikisha kuwa msimbo wa seva yako unafanya kazi muda wote kifaa chako cha IoT kinapofanya kazi, ama kwa kurekebisha mipangilio ya usimamizi wa nguvu au kwa kuendesha kitu kama [scripti hii ya Python ya kuweka mfumo ukiwa hai](https://github.com/jaqsparow/keep-system-active).

Baada ya kuwa na data ya joto, unaweza kutumia Jupyter Notebook katika repo hii kuonyesha data hiyo na kuhesabu GDD. Jupyter notebooks huchanganya msimbo na maelekezo katika vizuizi vinavyoitwa *cells*, mara nyingi msimbo ukiwa katika Python. Unaweza kusoma maelekezo, kisha kuendesha kila kizuizi cha msimbo, kizuizi kwa kizuizi. Unaweza pia kuhariri msimbo. Katika notebook hii kwa mfano, unaweza kuhariri joto la msingi linalotumika kuhesabu GDD kwa mmea wako.

1. Unda folda inayoitwa `gdd-calculation`

1. Pakua faili [gdd.ipynb](./code-notebook/gdd.ipynb) na uiweke ndani ya folda ya `gdd-calculation`.

1. Nakili faili `temperature.csv` iliyoundwa na seva ya MQTT

1. Unda mazingira mapya ya Python ya virtual ndani ya folda ya `gdd-calculation`.

1. Sakinisha baadhi ya pakiti za pip kwa Jupyter notebooks, pamoja na maktaba zinazohitajika kusimamia na kuonyesha data:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Endesha notebook katika Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter itaanza na kufungua notebook katika kivinjari chako. Fuata maelekezo katika notebook ili kuonyesha joto lililopimwa, na kuhesabu siku za digrii za ukuaji.

    ![Notebook ya Jupyter](../../../../../translated_images/sw/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rubric

| Vigezo | Bora Zaidi | Inayotosheleza | Inayohitaji Kuboresha |
| ------- | ---------- | ------------- | --------------------- |
| Kukusanya data | Kukusanya angalau siku 2 kamili za data | Kukusanya angalau siku 1 kamili ya data | Kukusanya data fulani |
| Kuhesabu GDD | Kuendesha notebook kwa mafanikio na kuhesabu GDD | Kuendesha notebook kwa mafanikio | Kushindwa kuendesha notebook |

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.