<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T08:37:15+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ro"
}
-->
# Clasifică o imagine folosind un clasificator de imagini bazat pe IoT Edge - Hardware IoT Virtual și Raspberry Pi

În această parte a lecției, vei utiliza clasificatorul de imagini care rulează pe dispozitivul IoT Edge.

## Folosește clasificatorul IoT Edge

Dispozitivul IoT poate fi redirecționat pentru a utiliza clasificatorul de imagini IoT Edge. URL-ul pentru clasificatorul de imagini este `http://<IP address or name>/image`, înlocuind `<IP address or name>` cu adresa IP sau numele gazdei computerului care rulează IoT Edge.

Biblioteca Python pentru Custom Vision funcționează doar cu modele găzduite în cloud, nu cu modele găzduite pe IoT Edge. Acest lucru înseamnă că va trebui să utilizezi API-ul REST pentru a apela clasificatorul.

### Sarcină - folosește clasificatorul IoT Edge

1. Deschide proiectul `fruit-quality-detector` în VS Code dacă nu este deja deschis. Dacă folosești un dispozitiv IoT virtual, asigură-te că mediul virtual este activat.

1. Deschide fișierul `app.py` și elimină declarațiile de import din `azure.cognitiveservices.vision.customvision.prediction` și `msrest.authentication`.

1. Adaugă următorul import în partea de sus a fișierului:

    ```python
    import requests
    ```

1. Șterge tot codul după ce imaginea este salvată într-un fișier, de la `image_file.write(image.read())` până la sfârșitul fișierului.

1. Adaugă următorul cod la sfârșitul fișierului:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Înlocuiește `<URL>` cu URL-ul clasificatorului tău.

    Acest cod face o cerere POST REST către clasificator, trimițând imaginea ca corp al cererii. Rezultatele sunt returnate ca JSON, iar acestea sunt decodificate pentru a afișa probabilitățile.

1. Rulează codul, cu camera îndreptată spre niște fructe, un set de imagini adecvat, sau fructe vizibile pe webcam-ul tău dacă folosești hardware IoT virtual. Vei vedea rezultatul în consolă:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Poți găsi acest cod în folderul [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) sau [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Programul tău de clasificare a calității fructelor a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.