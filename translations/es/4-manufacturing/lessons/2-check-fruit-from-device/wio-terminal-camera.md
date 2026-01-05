<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-26T14:14:51+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "es"
}
-->
# Captura una imagen - Wio Terminal

En esta parte de la lección, agregarás una cámara a tu Wio Terminal y capturarás imágenes con ella.

## Hardware

El Wio Terminal necesita una cámara.

La cámara que usarás es una [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Esta es una cámara de 2 megapíxeles basada en el sensor de imagen OV2640. Se comunica a través de una interfaz SPI para capturar imágenes y utiliza I2C para configurar el sensor.

## Conecta la cámara

La ArduCam no tiene un conector Grove; en su lugar, se conecta tanto a los buses SPI como I2C a través de los pines GPIO del Wio Terminal.

### Tarea - conecta la cámara

Conecta la cámara.

![Un sensor ArduCam](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.es.png)

1. Los pines en la base de la ArduCam deben conectarse a los pines GPIO del Wio Terminal. Para facilitar la identificación de los pines correctos, coloca la etiqueta de pines GPIO que viene con el Wio Terminal alrededor de los pines:

    ![El Wio Terminal con la etiqueta de pines GPIO](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.es.png)

1. Usando cables de puente, realiza las siguientes conexiones:

    | Pin de ArduCAM | Pin de Wio Terminal | Descripción                             |
    | -------------- | ------------------- | --------------------------------------- |
    | CS             | 24 (SPI_CS)         | Selección de chip SPI                   |
    | MOSI           | 19 (SPI_MOSI)       | Salida del controlador SPI, entrada del periférico |
    | MISO           | 21 (SPI_MISO)       | Entrada del controlador SPI, salida del periférico |
    | SCK            | 23 (SPI_SCLK)       | Reloj serial SPI                        |
    | GND            | 6 (GND)             | Tierra - 0V                             |
    | VCC            | 4 (5V)              | Fuente de alimentación de 5V            |
    | SDA            | 3 (I2C1_SDA)        | Datos seriales I2C                      |
    | SCL            | 5 (I2C1_SCL)        | Reloj serial I2C                        |

    ![El Wio Terminal conectado a la ArduCam con cables de puente](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.es.png)

    Las conexiones GND y VCC proporcionan una fuente de alimentación de 5V a la ArduCam. Funciona a 5V, a diferencia de los sensores Grove que funcionan a 3V. Esta energía proviene directamente de la conexión USB-C que alimenta el dispositivo.

    > 💁 Para la conexión SPI, las etiquetas de los pines en la ArduCam y los nombres de los pines del Wio Terminal utilizados en el código aún usan la convención de nombres antigua. Las instrucciones en esta lección usarán la nueva convención de nombres, excepto cuando los nombres de los pines se utilicen en el código.

1. Ahora puedes conectar el Wio Terminal a tu computadora.

## Programa el dispositivo para conectarse a la cámara

El Wio Terminal ahora puede ser programado para usar la cámara ArduCAM conectada.

### Tarea - programa el dispositivo para conectarse a la cámara

1. Crea un proyecto nuevo para el Wio Terminal usando PlatformIO. Llama a este proyecto `fruit-quality-detector`. Agrega código en la función `setup` para configurar el puerto serial.

1. Agrega código para conectarte a WiFi, con tus credenciales de WiFi en un archivo llamado `config.h`. No olvides agregar las bibliotecas necesarias al archivo `platformio.ini`.

1. La biblioteca de ArduCam no está disponible como una biblioteca de Arduino que pueda instalarse desde el archivo `platformio.ini`. En su lugar, deberá instalarse desde su página de GitHub. Puedes obtenerla de las siguientes maneras:

    * Clonando el repositorio desde [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Visitando el repositorio en GitHub en [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) y descargando el código como un archivo zip desde el botón **Code**

1. Solo necesitas la carpeta `ArduCAM` de este código. Copia toda la carpeta dentro de la carpeta `lib` de tu proyecto.

    > ⚠️ Debes copiar toda la carpeta, de modo que el código esté en `lib/ArduCam`. No copies solo el contenido de la carpeta `ArduCam` en la carpeta `lib`, copia la carpeta completa.

1. El código de la biblioteca ArduCam funciona para múltiples tipos de cámaras. El tipo de cámara que deseas usar se configura utilizando banderas del compilador, lo que mantiene la biblioteca construida lo más pequeña posible al eliminar el código para cámaras que no estás utilizando. Para configurar la biblioteca para la cámara OV2640, agrega lo siguiente al final del archivo `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Esto establece 2 banderas del compilador:

      * `ARDUCAM_SHIELD_V2` para indicar a la biblioteca que la cámara está en una placa Arduino, conocida como shield.
      * `OV2640_CAM` para indicar a la biblioteca que solo incluya código para la cámara OV2640.

1. Agrega un archivo de encabezado en la carpeta `src` llamado `camera.h`. Este contendrá el código para comunicarse con la cámara. Agrega el siguiente código a este archivo:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Este es un código de bajo nivel que configura la cámara utilizando las bibliotecas de ArduCam y extrae las imágenes cuando sea necesario utilizando el bus SPI. Este código es muy específico para la ArduCam, por lo que no necesitas preocuparte por cómo funciona en este momento.

1. En `main.cpp`, agrega el siguiente código debajo de las otras declaraciones `include` para incluir este nuevo archivo y crear una instancia de la clase de cámara:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Esto crea una `Camera` que guarda las imágenes como JPEGs con una resolución de 640x480. Aunque se admiten resoluciones más altas (hasta 3280x2464), el clasificador de imágenes funciona con imágenes mucho más pequeñas (227x227), por lo que no es necesario capturar y enviar imágenes más grandes.

1. Agrega el siguiente código debajo de esto para definir una función que configure la cámara:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Esta función `setupCamera` comienza configurando el pin de selección de chip SPI (`PIN_SPI_SS`) como alto, haciendo que el Wio Terminal sea el controlador SPI. Luego inicia los buses I2C y SPI. Finalmente, inicializa la clase de cámara, que configura los ajustes del sensor de la cámara y asegura que todo esté correctamente conectado.

1. Llama a esta función al final de la función `setup`:

    ```cpp
    setupCamera();
    ```

1. Compila y sube este código, y verifica la salida del monitor serial. Si ves `Error setting up the camera!`, verifica el cableado para asegurarte de que todos los cables estén conectando los pines correctos en la ArduCam a los pines GPIO correctos en el Wio Terminal, y que todos los cables de puente estén correctamente asentados.

## Captura una imagen

El Wio Terminal ahora puede ser programado para capturar una imagen cuando se presione un botón.

### Tarea - captura una imagen

1. Los microcontroladores ejecutan tu código continuamente, por lo que no es fácil activar algo como tomar una foto sin reaccionar a un sensor. El Wio Terminal tiene botones, por lo que la cámara puede configurarse para activarse con uno de los botones. Agrega el siguiente código al final de la función `setup` para configurar el botón C (uno de los tres botones en la parte superior, el más cercano al interruptor de encendido).

    ![El botón C en la parte superior, cerca del interruptor de encendido](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.es.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    El modo `INPUT_PULLUP` esencialmente invierte una entrada. Por ejemplo, normalmente un botón enviaría una señal baja cuando no se presiona y una señal alta cuando se presiona. Cuando se configura como `INPUT_PULLUP`, envía una señal alta cuando no se presiona y una señal baja cuando se presiona.

1. Agrega una función vacía para responder a la pulsación del botón antes de la función `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Llama a esta función en el método `loop` cuando se presione el botón:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Este código verifica si el botón está presionado. Si lo está, se llama a la función `buttonPressed` y el bucle se retrasa por 2 segundos. Esto es para permitir tiempo para que el botón sea liberado y evitar que una pulsación larga se registre dos veces.

    > 💁 El botón en el Wio Terminal está configurado como `INPUT_PULLUP`, por lo que envía una señal alta cuando no se presiona y una señal baja cuando se presiona.

1. Agrega el siguiente código a la función `buttonPressed`:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Este código inicia la captura de la cámara llamando a `startCapture`. El hardware de la cámara no funciona devolviendo los datos cuando los solicitas; en su lugar, envías una instrucción para comenzar la captura, y la cámara trabajará en segundo plano para capturar la imagen, convertirla a JPEG y almacenarla en un búfer local en la propia cámara. La llamada `captureReady` luego verifica si la captura de la imagen ha terminado.

    Una vez que la captura ha terminado, los datos de la imagen se copian del búfer de la cámara a un búfer local (array de bytes) con la llamada `readImageToBuffer`. La longitud del búfer se envía al monitor serial.

1. Compila y sube este código, y verifica la salida en el monitor serial. Cada vez que presiones el botón C, se capturará una imagen y verás el tamaño de la imagen enviado al monitor serial.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Las imágenes diferentes tendrán tamaños diferentes. Se comprimen como JPEGs y el tamaño de un archivo JPEG para una resolución dada depende de lo que haya en la imagen.

> 💁 Puedes encontrar este código en la carpeta [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Has capturado imágenes exitosamente con tu Wio Terminal.

## Opcional - verifica las imágenes de la cámara usando una tarjeta SD

La forma más sencilla de ver las imágenes capturadas por la cámara es escribirlas en una tarjeta SD en el Wio Terminal y luego verlas en tu computadora. Realiza este paso si tienes una tarjeta microSD de repuesto y un lector de tarjetas microSD en tu computadora o un adaptador.

El Wio Terminal solo admite tarjetas microSD de hasta 16GB de tamaño. Si tienes una tarjeta SD más grande, no funcionará.

### Tarea - verifica las imágenes de la cámara usando una tarjeta SD

1. Formatea una tarjeta microSD como FAT32 o exFAT utilizando las aplicaciones relevantes en tu computadora (Utilidad de Discos en macOS, Explorador de Archivos en Windows, o herramientas de línea de comandos en Linux).

1. Inserta la tarjeta microSD en el lector justo debajo del interruptor de encendido. Asegúrate de que esté completamente insertada hasta que haga clic y se quede en su lugar; es posible que necesites empujarla con una uña o una herramienta delgada.

1. Agrega las siguientes declaraciones `include` en la parte superior del archivo `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Agrega la siguiente función antes de la función `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Esto configura la tarjeta SD utilizando el bus SPI.

1. Llama a esta función desde la función `setup`:

    ```cpp
    setupSDCard();
    ```

1. Agrega el siguiente código encima de la función `buttonPressed`:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Esto define una variable global para un contador de archivos. Se utiliza para los nombres de los archivos de imagen, de modo que se puedan capturar múltiples imágenes con nombres de archivo incrementales: `1.jpg`, `2.jpg`, y así sucesivamente.

    Luego define la función `saveToSDCard`, que toma un búfer de datos de bytes y la longitud del búfer. Se crea un nombre de archivo utilizando el contador de archivos, y el contador se incrementa para el siguiente archivo. Los datos binarios del búfer se escriben en el archivo.

1. Llama a la función `saveToSDCard` desde la función `buttonPressed`. La llamada debe estar **antes** de que se elimine el búfer:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Compila y sube este código, y verifica la salida en el monitor serial. Cada vez que presiones el botón C, se capturará una imagen y se guardará en la tarjeta SD.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. Apaga el Wio Terminal y expulsa la tarjeta microSD presionándola ligeramente y soltándola, y saldrá. Es posible que necesites usar una herramienta delgada para hacerlo. Conecta la tarjeta microSD a tu computadora para ver las imágenes.

    ![Una imagen de un plátano capturada con la ArduCam](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.es.jpg)
> 💁 Puede que la cámara necesite unas cuantas imágenes para ajustar el balance de blancos. Notarás esto según el color de las imágenes capturadas, las primeras pueden verse descoloridas. Siempre puedes solucionar esto cambiando el código para capturar algunas imágenes que se ignoren en la función `setup`.


---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.