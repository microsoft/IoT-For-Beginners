# Apelează detectorul de obiecte de pe dispozitivul tău IoT - Hardware IoT Virtual și Raspberry Pi

După ce detectorul tău de obiecte a fost publicat, acesta poate fi utilizat de pe dispozitivul tău IoT.

## Copiază proiectul clasificatorului de imagini

Majoritatea detectorului tău de stocuri este similară cu clasificatorul de imagini pe care l-ai creat într-o lecție anterioară.

### Sarcină - copiază proiectul clasificatorului de imagini

1. Creează un folder numit `stock-counter` fie pe computerul tău dacă folosești un dispozitiv IoT virtual, fie pe Raspberry Pi-ul tău. Dacă folosești un dispozitiv IoT virtual, asigură-te că setezi un mediu virtual.

1. Configurează hardware-ul camerei.

    * Dacă folosești un Raspberry Pi, va trebui să montezi PiCamera. De asemenea, ai putea dori să fixezi camera într-o poziție stabilă, de exemplu, prin agățarea cablului peste o cutie sau o conservă, sau fixând camera pe o cutie cu bandă dublu-adezivă.
    * Dacă folosești un dispozitiv IoT virtual, va trebui să instalezi CounterFit și CounterFit PyCamera shim. Dacă intenționezi să folosești imagini statice, capturează câteva imagini pe care detectorul tău de obiecte nu le-a văzut încă. Dacă intenționezi să folosești camera web, asigură-te că aceasta este poziționată astfel încât să poată vedea stocurile pe care le detectezi.

1. Repetă pașii din [lecția 2 a proiectului de fabricație](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) pentru a captura imagini de la cameră.

1. Repetă pașii din [lecția 2 a proiectului de fabricație](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) pentru a apela clasificatorul de imagini. Majoritatea acestui cod va fi reutilizat pentru a detecta obiecte.

## Modifică codul de la un clasificator la un detector de imagini

Codul pe care l-ai folosit pentru a clasifica imagini este foarte similar cu cel pentru detectarea obiectelor. Principala diferență constă în metoda apelată din SDK-ul Custom Vision și rezultatele apelului.

### Sarcină - modifică codul de la un clasificator la un detector de imagini

1. Șterge cele trei linii de cod care clasifică imaginea și procesează predicțiile:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Elimină aceste trei linii.

1. Adaugă următorul cod pentru a detecta obiecte în imagine:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Acest cod apelează metoda `detect_image` pe predictor pentru a rula detectorul de obiecte. Apoi adună toate predicțiile cu o probabilitate peste un prag, afișându-le în consolă.

    Spre deosebire de un clasificator de imagini care returnează un singur rezultat per etichetă, detectorul de obiecte va returna rezultate multiple, așa că orice rezultat cu o probabilitate scăzută trebuie filtrat.

1. Rulează acest cod și va captura o imagine, o va trimite la detectorul de obiecte și va afișa obiectele detectate. Dacă folosești un dispozitiv IoT virtual, asigură-te că ai setat o imagine corespunzătoare în CounterFit sau că ai selectat camera web. Dacă folosești un Raspberry Pi, asigură-te că camera ta este îndreptată spre obiectele de pe un raft.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Este posibil să fie nevoie să ajustezi `threshold` la o valoare potrivită pentru imaginile tale.

    Vei putea vedea imaginea capturată și aceste valori în fila **Predictions** din Custom Vision.

    ![4 conserve de pastă de roșii pe un raft cu predicții pentru cele 4 detecții de 35.8%, 33.5%, 25.7% și 16.6%](../../../../../translated_images/ro/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Poți găsi acest cod în folderul [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) sau [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Programul tău de numărare a stocurilor a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.