<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-26T14:29:25+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "es"
}
-->
# Visualizar datos de GDD usando un Jupyter Notebook

## Instrucciones

En esta lección recopilaste datos de GDD utilizando un sensor IoT. Para obtener buenos datos de GDD, necesitas recopilar datos durante varios días. Para ayudar a visualizar los datos de temperatura y calcular el GDD, puedes usar herramientas como [Jupyter Notebooks](https://jupyter.org) para analizar los datos.

Comienza recopilando datos durante algunos días. Deberás asegurarte de que el código de tu servidor esté funcionando todo el tiempo que tu dispositivo IoT esté activo, ya sea ajustando la configuración de administración de energía o ejecutando algo como [este script de Python para mantener el sistema activo](https://github.com/jaqsparow/keep-system-active).

Una vez que tengas los datos de temperatura, puedes usar el Jupyter Notebook en este repositorio para visualizarlos y calcular el GDD. Los Jupyter Notebooks combinan código e instrucciones en bloques llamados *celdas*, a menudo con código en Python. Puedes leer las instrucciones y luego ejecutar cada bloque de código, uno por uno. También puedes editar el código. En este notebook, por ejemplo, puedes editar la temperatura base utilizada para calcular el GDD de tu planta.

1. Crea una carpeta llamada `gdd-calculation`

1. Descarga el archivo [gdd.ipynb](./code-notebook/gdd.ipynb) y cópialo en la carpeta `gdd-calculation`.

1. Copia el archivo `temperature.csv` creado por el servidor MQTT.

1. Crea un nuevo entorno virtual de Python en la carpeta `gdd-calculation`.

1. Instala algunos paquetes de pip para Jupyter Notebooks, junto con las bibliotecas necesarias para gestionar y graficar los datos:

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. Ejecuta el notebook en Jupyter:

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter se iniciará y abrirá el notebook en tu navegador. Sigue las instrucciones en el notebook para visualizar las temperaturas medidas y calcular los días grado de crecimiento.

    ![El jupyter notebook](../../../../../translated_images/es/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## Rúbrica

| Criterios | Ejemplar | Adecuado | Necesita Mejorar |
| --------- | -------- | -------- | ---------------- |
| Captura de datos | Captura al menos 2 días completos de datos | Captura al menos 1 día completo de datos | Captura algunos datos |
| Cálculo de GDD | Ejecuta exitosamente el notebook y calcula el GDD | Ejecuta exitosamente el notebook | No logra ejecutar el notebook |

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse como la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.