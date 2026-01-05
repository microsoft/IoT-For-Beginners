<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-05T12:34:43+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "es"
}
-->
# Guía de solución de problemas

Esta guía te ayuda a resolver problemas comunes al trabajar con el plan de estudios de IoT para principiantes. Los problemas están organizados por categoría para facilitar la navegación.

## Tabla de contenidos

- [Problemas de instalación](../..)
  - [Instalación de Python](../..)
  - [VS Code y extensiones](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Bibliotecas Grove](../..)
- [Problemas de hardware](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Dispositivo virtual (CounterFit)](../..)
- [Problemas de conectividad](../..)
  - [Conexión WiFi](../..)
  - [Servicios en la nube](../..)
  - [MQTT](../..)
- [Problemas con sensores y actuadores](../..)
  - [Sensores Grove](../..)
  - [Cámara](../..)
  - [Micrófono y altavoz](../..)
- [Problemas con el entorno de desarrollo](../..)
  - [VS Code](../..)
  - [Entornos virtuales de Python](../..)
  - [Dependencias](../..)
- [Problemas de rendimiento](../..)
- [Mensajes de error comunes](../..)
- [Obtener ayuda](../..)

---

## Problemas de instalación

### Instalación de Python

#### Problema: La versión de Python es muy antigua
**Error:** `Se requiere Python 3.6 o superior`

**Solución:**
1. Descarga la última versión de Python 3 desde [python.org](https://www.python.org/downloads/)
2. Durante la instalación en Windows, marca "Add Python to PATH"
3. Verifica la instalación:
   ```bash
   python3 --version
   ```

#### Problema: Múltiples versiones de Python causan conflictos
**Síntomas:** Se ejecuta una versión incorrecta de Python, los paquetes se instalan en una ubicación incorrecta

**Solución:**
- **Windows:** Usa `py -3` en lugar de `python` para llamar explícitamente a Python 3
- **macOS/Linux:** Usa `python3` en lugar de `python`
- Siempre crea y usa entornos virtuales para los proyectos

#### Problema: Comando pip no encontrado
**Error:** `'pip' no se reconoce como un comando interno o externo`

**Solución:**
1. Intenta usar `pip3` en lugar de `pip`
2. O usa `python -m pip` o `python3 -m pip`
3. Asegúrate de que Python esté agregado al PATH (reinstala Python y marca la opción)

### VS Code y extensiones

#### Problema: La extensión Pylance no funciona
**Síntomas:** No hay IntelliSense de Python, autocompletado ni verificación de tipos

**Solución:**
1. Abre la paleta de comandos de VS Code (`Ctrl+Shift+P` o `Cmd+Shift+P`)
2. Ejecuta "Python: Select Interpreter"
3. Elige el intérprete correcto de Python (entorno virtual si usas uno)
4. Recarga la ventana de VS Code

#### Problema: VS Code no detecta el entorno virtual
**Síntomas:** Se selecciona un intérprete incorrecto de Python

**Solución:**
1. Asegúrate de haber activado el entorno virtual en la terminal
2. Abre la paleta de comandos y ejecuta "Python: Select Interpreter"
3. Selecciona el intérprete desde la carpeta `.venv`
4. Comprueba que la barra de estado (abajo a la izquierda) muestre la versión correcta de Python

### PlatformIO (Wio Terminal)

#### Problema: Fallo en la instalación de PlatformIO
**Error:** Varios errores durante la instalación de PlatformIO

**Solución:**
1. Asegúrate de que VS Code esté actualizado
2. Instala primero la extensión C/C++
3. Reinicia VS Code después de instalar PlatformIO
4. Verifica tu conexión a internet (PlatformIO descarga archivos pesados)

#### Problema: PlatformIO no detecta la placa
**Síntomas:** No se puede cargar código en Wio Terminal

**Solución:**
1. Prueba con otro cable USB (algunos cables son solo para cargar)
2. Revisa el Administrador de dispositivos (Windows) o `ls /dev/tty*` (macOS/Linux)
3. Instala o actualiza los drivers USB
4. Intenta con otro puerto USB
5. Desliza el interruptor de encendido del Wio Terminal dos veces rápido para entrar en modo bootloader

#### Problema: Errores de compilación en PlatformIO
**Error:** `fatal error: Arduino.h: No existe el archivo o el directorio`

**Solución:**
1. Borra la carpeta `.pio` en tu proyecto
2. Ejecuta "PlatformIO: Rebuild" desde la paleta de comandos
3. Asegúrate de que `platformio.ini` tenga la configuración correcta de la placa:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Bibliotecas Grove

#### Problema: Error al importar la biblioteca Grove en Raspberry Pi
**Error:** `ModuleNotFoundError: No module named 'grove'`

**Solución:**
1. Reinstala las bibliotecas Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Si usas entorno virtual, puede que debas instalarlas globalmente o copiar las bibliotecas
3. Verifica que I2C esté habilitado: `sudo raspi-config nonint do_i2c 0`

#### Problema: Sensor Grove no detectado
**Error:** `IOError: [Errno 121] Error de E/S remoto`

**Solución:**
1. Revisa las conexiones físicas (asegúrate que el cable Grove esté completamente insertado)
2. Verifica que el sensor esté conectado al puerto correcto (analógico, digital, I2C, UART)
3. Ejecuta `i2cdetect -y 1` para ver si el dispositivo aparece en el bus I2C
4. Prueba con otro cable Grove
5. Asegúrate de que Grove Base Hat esté correctamente colocado sobre los pines GPIO de Raspberry Pi

---

## Problemas de hardware

### Raspberry Pi

#### Problema: Raspberry Pi no arranca
**Síntomas:** No muestra imagen, no hay actividad en LEDs, o pantalla arcoíris

**Solución:**
1. **Revisa la fuente de alimentación:** Usa fuente oficial USB-C 5V 3A para Pi 4
2. **Problemas con la tarjeta SD:** 
   - Reformatea la tarjeta SD y reinstala Raspberry Pi OS
   - Prueba con otra tarjeta SD (usa marcas recomendadas)
   - Asegúrate de que la tarjeta SD esté bien insertada
3. **Revisa la conexión HDMI:** Prueba ambos puertos HDMI en Pi 4, utiliza el puerto HDMI más cercano a la fuente de alimentación

#### Problema: No se puede conectar por SSH a Raspberry Pi
**Síntomas:** Conexión rechazada o tiempo de espera agotado

**Solución:**
1. Habilita SSH:
   - Cuando grabes la tarjeta SD con Raspberry Pi Imager, configura SSH en opciones avanzadas
   - O crea un archivo vacío llamado `ssh` (sin extensión) en la partición de arranque
2. Encuentra la IP de la Pi:
   - Revisa dispositivos conectados en tu router
   - Usa `ping raspberrypi.local` (si funciona mDNS)
   - Usa herramientas de escaneo de red como `nmap` o Angry IP Scanner
3. Verifica la red:
   - Asegúrate que la Pi esté en la misma red que tu equipo
   - Prueba con conexión por cable Ethernet en lugar de WiFi
4. Verifica usuario/contraseña (por defecto: usuario `pi`, contraseña `raspberry`)

#### Problema: No se reconoce Grove Base Hat
**Síntomas:** Sensores no funcionan, errores I2C

**Solución:**
1. Asegúrate de que Base Hat esté bien asentado en todos los pines GPIO
2. Revisa que no haya pines doblados en la Pi o el Base Hat
3. Habilita interfaz I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verifica que I2C funcione: `i2cdetect -y 1`

#### Problema: Raspberry Pi funciona lento
**Síntomas:** Interfaz lenta, respuesta demorada

**Solución:**
1. Revisa la velocidad de la tarjeta SD (usa clase 10 o mejor, o SSD via USB)
2. Libera espacio en disco: `df -h` para revisar, elimina archivos innecesarios
3. Reduce memoria GPU en `raspi-config` si no usas cámara o pantalla intensivamente
4. Cierra aplicaciones innecesarias
5. Considera actualizar a Pi 4 con más RAM si usas Pi 3 o versiones anteriores

### Wio Terminal

#### Problema: Pantalla del Wio Terminal se queda en blanco
**Síntomas:** No hay salida de pantalla tras cargar código

**Solución:**
1. Verifica si el código inicializa la pantalla (biblioteca TFT_eSPI)
2. Actualiza el firmware del Wio Terminal desde [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Añade código de inicialización de pantalla:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Intenta cargar un ejemplo de PlatformIO para probar el hardware

#### Problema: WiFi no funciona en Wio Terminal
**Síntomas:** No se conecta a WiFi, errores de red

**Solución:**
1. **Actualiza firmware WiFi:** Sigue la [guía de actualización de firmware WiFi para Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Revisa credenciales WiFi:** Asegúrate que SSID y contraseña sean correctos
3. **Banda WiFi:** Wio Terminal solo soporta WiFi 2.4 GHz (no 5 GHz)
4. **Intensidad de señal:** Acércate al router
5. **Configuración del router:** Algunas redes empresariales o WPA-Enterprise pueden no funcionar

#### Problema: Wio Terminal no reconocido por el equipo
**Síntomas:** Dispositivo USB no detectado

**Solución:**
1. **Prueba otro cable USB:** Usa cable de datos, no solo de carga
2. **Entra en modo bootloader:** Desliza el interruptor de encendido hacia abajo dos veces rápido
   - El LED azul debería parpadear, el dispositivo aparece como "Arduino" en el Administrador de dispositivos
3. **Instala drivers (Windows):**
   - Descarga e instala [driver USB de Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Prueba otro puerto USB:** Evita concentradores USB, usa conexión directa
5. **Actualiza drivers USB del sistema**

#### Problema: Sensores no funcionan en Wio Terminal
**Síntomas:** Sensores Grove no leen datos

**Solución:**
1. Verifica conexiones de cables Grove
2. Asegúrate de usar el puerto Grove correcto (izquierdo o derecho)
3. Incluye las bibliotecas correctas para el sensor
4. Revisa requisitos de alimentación del sensor
5. Prueba el sensor con código de ejemplo de la biblioteca

### Dispositivo virtual (CounterFit)

#### Problema: La app CounterFit no inicia
**Error:** Varios errores de Python al iniciar CounterFit

**Solución:**
1. Asegúrate de que el entorno virtual esté activado
2. Instala/reinstala CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Verifica que el puerto 5000 no esté ya en uso:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Termina el proceso que usa el puerto 5000 o usa otro puerto:
   ```bash
   counterfit --port 5001
   ```

#### Problema: No se puede conectar a CounterFit desde el código
**Error:** Conexión rechazada o tiempo de espera agotado

**Solución:**
1. Verifica que CounterFit esté corriendo: Abre navegador en `http://127.0.0.1:5000`
2. Comprueba que la URL de conexión en el código coincida con la dirección de CounterFit
3. Asegúrate de que el firewall no bloquee la conexión
4. Intenta reiniciar tanto la app CounterFit como tu código

#### Problema: Sensores no aparecen en CounterFit
**Síntomas:** Sensores creados no se muestran en la interfaz de CounterFit

**Solución:**
1. Crea sensores en la interfaz de CounterFit antes de ejecutar el código
2. Actualiza la página del navegador
3. Verifica que el tipo de sensor coincida con lo que espera el código
4. Limpia la caché del navegador

---

## Problemas de conectividad

### Conexión WiFi

#### Problema: El dispositivo no puede conectarse a WiFi
**Síntomas:** Tiempo de conexión agotado, falló la autenticación

**Solución:**
1. **Revisa SSID y contraseña:** Verifica que las credenciales sean correctas
2. **Banda WiFi:** La mayoría de dispositivos IoT solo soportan 2.4 GHz (no 5 GHz)
3. **Configuración del router:**
   - Desactiva aislamiento AP si está habilitado
   - Usa seguridad WPA2-PSK (evita WPA3, WEP o redes abiertas)
   - Asegúrate que DHCP esté habilitado
4. **Redes ocultas:** Si el SSID está oculto, puede que necesites configurarlo explícitamente
5. **Intensidad de señal:** Acerca el dispositivo al router
6. **Interferencias:** Otros dispositivos, microondas o paredes pueden interferir

#### Problema: La conexión WiFi se cae con frecuencia
**Síntomas:** Conectividad intermitente

**Solución:**
1. Revisa la estabilidad del router y considera reiniciarlo
2. Actualiza el firmware del dispositivo
3. Usa IP estática en lugar de DHCP
4. Acércate al router o añade un repetidor WiFi
5. Revisa interferencias de otros dispositivos
6. Verifica que la fuente de alimentación sea adecuada (especialmente para Raspberry Pi)

### Servicios en la nube

#### Problema: No se puede conectar a Azure IoT Hub
**Error:** Fallo de autenticación, conexión rechazada

**Solución:**
1. **Verifica credenciales:**
   - Revisa que la cadena de conexión sea correcta
   - Asegúrate de que no haya espacios extras o saltos de línea en la cadena
2. **Verifica el registro del dispositivo:** El dispositivo debe estar registrado en IoT Hub
3. **Firewall/proxy:** Asegúrate que salidas MQTT (puerto 8883) o HTTPS (puerto 443) estén permitidas
4. **Región de IoT Hub:** Asegúrate que IoT Hub esté activo y no en una región diferente que cause latencia
5. **Límites de cuota:** Verifica si se han superado límites del nivel gratuito
6. **Prueba la conexión:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problema: Azure Functions no se activan
**Síntomas:** Se envían mensajes pero la función no se ejecuta

**Solución:**
1. Comprueba que la Function App esté en ejecución (no detenida)
2. Verifica la cadena de conexión en la configuración de la Function App
3. Revisa los registros de la función en Azure Portal
4. Asegúrate de que el endpoint compatible con Event Hub esté configurado correctamente
5. Verifica que el formato del mensaje coincida con lo que espera la función
6. Revisa el plan de servicio de la Function App (consumo vs dedicado)

### MQTT
#### Problema: La conexión MQTT falla  
**Error:** Conexión rechazada, autenticación fallida

**Solución:**  
1. **Dirección del broker:** Verifique que la URL/IP del broker sea correcta  
2. **Puerto:** Compruebe el número de puerto (1883 para sin cifrar, 8883 para TLS)  
3. **Autenticación:** Verifique usuario/contraseña si se requieren  
4. **TLS/SSL:** Asegúrese de que los certificados sean válidos y confiables  
5. **Cortafuegos:** Verifique que el puerto no esté bloqueado  
6. **Pruebe con cliente MQTT:** Use MQTT Explorer o mosquitto_pub/sub para probar

#### Problema: No se reciben mensajes MQTT  
**Síntomas:** Mensajes publicados pero no recibidos por los suscriptores

**Solución:**  
1. **Nombres de tema:** Verifique que el tema del suscriptor coincida exactamente con el del publicador  
2. **Nivel QoS:** Intente QoS 1 o 2 en lugar de 0  
3. **Comodines:** Compruebe que los comodines se usen correctamente (`+` para nivel único, `#` para múltiples niveles)  
4. **Mensajes retenidos:** El publicador puede activar la bandera de retención para mantener el último mensaje  
5. **Momento de la conexión:** Asegúrese de que el suscriptor se conecte antes de que se publiquen los mensajes

---

## Problemas con Sensores y Actuadores

### Sensores Grove

#### Problema: El sensor devuelve valores incorrectos  
**Síntomas:** Lecturas son 0, -1 o valores sin sentido

**Solución:**  
1. **Revise conexiones:** Asegúrese de que el sensor esté correctamente conectado  
2. **Puerto correcto:** Verifique que el sensor esté en el tipo de puerto correcto:  
   - Sensores analógicos → Puertos analógicos (A0, A2, A4)  
   - Sensores digitales → Puertos digitales (D5, D16, D18, etc.)  
   - Sensores I2C → Puertos I2C  
3. **Calibración:** Algunos sensores necesitan calibración (humedad del suelo, luz)  
4. **Ciclo de encendido:** Desconecte y vuelva a conectar el sensor  
5. **Datasheet del sensor:** Revise especificaciones y requerimientos del sensor

#### Problema: Sensor capacitivo de humedad del suelo siempre marca húmedo  
**Síntomas:** Sensor registra alta humedad incluso cuando está seco

**Solución:**  
1. **Necesita calibración:** Los sensores de suelo requieren calibración:  
   - Lea valor en aire (línea base seca)  
   - Lea valor en agua (línea base húmeda)  
   - Mapear lecturas entre estos valores  
2. **Revise el recubrimiento del sensor:** Los sensores de humedad pueden degradarse si el recubrimiento está dañado  
3. **Colocación:** Asegúrese de que el sensor esté completamente insertado en el suelo

#### Problema: Lecturas incorrectas de sensor de temperatura/humedad  
**Síntomas:** DHT11/DHT22 muestra temperatura o humedad errónea

**Solución:**  
1. **Ubicación del sensor:** Evite luz solar directa, fuentes de calor o corrientes de aire  
2. **Tiempo de calentamiento:** Deje 2 segundos después de energizar antes de leer  
3. **Frecuencia de lectura:** Los sensores DHT necesitan tiempo entre lecturas (al menos 2 segundos)  
4. **Chequeo de condensación:** Puede afectar las lecturas  
5. **Calidad del sensor:** DHT11 es menos preciso que DHT22

### Cámara

#### Problema: Cámara no detectada en Raspberry Pi  
**Error:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Solución:**  
1. **Activar interfaz de cámara:**  
   ```bash
   sudo raspi-config
   ```
   Vaya a Opciones de Interfaz → Cámara → Activar  
2. **Revisar cable plano:** Asegúrese de que el cable de la cámara esté correctamente insertado  
   - El lado azul mira hacia los puertos USB en Pi Zero  
   - El lado azul mira hacia fuera de los puertos USB en Pi 4  
3. **Actualizar firmware:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Probar cámara:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Problema: Imagen de cámara de baja calidad  
**Síntomas:** Imágenes borrosas, oscuras o deslavadas

**Solución:**  
1. **Enfoque:** Retire la película protectora del lente, ajuste enfoque si es ajustable  
2. **Iluminación:** Asegure una iluminación adecuada  
3. **Configuración de cámara:** Ajuste exposición, ISO, balance de blancos en el código  
4. **Estabilidad:** Mantenga cámara fija, use trípode si es necesario  
5. **Resolución:** No exceda la resolución máxima de la cámara

### Micrófono y Altavoz

#### Problema: Sin entrada/salida de audio  
**Síntomas:** Micrófono no graba, altavoz no reproduce

**Solución:**  
1. **Verificar conexiones:** Asegúrese de que los dispositivos de audio estén correctamente conectados  
2. **Probar hardware:**  
   - Altavoz: `speaker-test -t wav -c 2`  
   - Micrófono: `arecord -l` para listar, `arecord test.wav` para grabar  
3. **Configuraciones de volumen:** Revise y ajuste volumen:  
   ```bash
   alsamixer
   ```
4. **Seleccionar dispositivo de audio:** Especifique dispositivo correcto en el código  
5. **Problemas de driver:** Actualice ALSA o reinstale controladores de audio

#### Problema: No funciona el hat ReSpeaker  
**Síntomas:** Dispositivo de audio no detectado

**Solución:**  
1. **Instalar controladores:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Verificar instalación:** `arecord -l` debería listar ReSpeaker  
3. **Actualizar firmware:** Algunas versiones de Pi OS requieren actualizar drivers  
4. **Comprobar conexión:** Asegúrese de que el hat esté correctamente conectado a los pines GPIO

---

## Problemas en el Entorno de Desarrollo

### VS Code

#### Problema: Terminal no activa entorno virtual automáticamente  
**Síntomas:** Terminal abre pero no activa venv

**Solución:**  
1. **Configurar intérprete Python:** Paleta de comandos → "Python: Select Interpreter" → Seleccione venv  
2. **Reiniciar VS Code** después de seleccionar intérprete  
3. **Verificar configuración:** En `settings.json`, agregar:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Problema: Código no se ejecuta en dispositivo  
**Síntomas:** Código corre pero no pasa nada en el dispositivo

**Solución:**  
1. **Verificar que el código esté guardado** (revisar punto en pestaña del archivo)  
2. **Verificar qué Python se está ejecutando:** `which python` o `where python`  
3. **Para Wio Terminal:** Asegúrese de subir código vía PlatformIO (clic en botón cargar)  
4. **Para Raspberry Pi:** Hacer SSH al Pi y ejecutar código allí  
5. **Verificar ventana de salida** para errores

#### Problema: IntelliSense no muestra funciones de librería  
**Síntomas:** Sin autocompletar para módulos importados

**Solución:**  
1. Asegúrese que la librería esté instalada en el entorno actual  
2. Recargue la ventana de VS Code  
3. Verifique que el intérprete Python sea correcto  
4. Instale stubs de tipo si están disponibles: `pip install types-<nombre-librería>`

### Entornos Virtuales Python

#### Problema: No se puede crear entorno virtual  
**Error:** `The virtual environment was not created successfully`

**Solución:**  
1. **Instalar módulo venv:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Debería venir incluido con Python  
   - Windows: Reinstale Python con todos los componentes  
2. **Verificar instalación de Python:** Confirme que Python esté correctamente instalado  
3. **Usar ruta completa:** Intente `python3 -m venv .venv` con llamada explícita a python3

#### Problema: Paquetes instalados en ubicación incorrecta  
**Síntomas:** Error de importación tras instalar paquete

**Solución:**  
1. **Verifique que venv esté activado:** El prompt debe mostrar `(.venv)`  
2. **Comprobar ubicación de pip:** `which pip` debe apuntar a `.venv/bin/pip`  
3. **Reinstale en venv:** Active venv y luego `pip install <paquete>`  
4. **No usar sudo con pip** en entorno virtual

#### Problema: Entorno virtual no portátil  
**Síntomas:** Venv no funciona tras moverlo o en otro equipo

**Solución:**  
1. **No mover venv:** Elimínelo y créelo en la nueva ubicación  
2. **Use requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Recrear venv:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # o activate.bat en Windows
   pip install -r requirements.txt
   ```
  
### Dependencias

#### Problema: Fallo al instalar paquete  
**Error:** Diversos errores de pip durante la instalación

**Solución:**  
1. **Actualizar pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Instalar herramientas de compilación:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Instalar Visual Studio Build Tools  
3. **Verificar conexión a internet**  
4. **Probar otro índice de paquetes:** `pip install --index-url https://pypi.org/simple/ <paquete>`  
5. **Instalar versión específica:** `pip install <paquete>==<versión>`

#### Problema: Conflictos de dependencias  
**Error:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Solución:**  
1. **Usar entorno virtual nuevo** para cada proyecto  
2. **Actualizar paquetes:** `pip install --upgrade <paquete>`  
3. **Verificar requisitos:** Usar `pip check` para encontrar conflictos  
4. **Instalar versiones compatibles:** Especificar rangos de versión en requirements.txt

---

## Problemas de Rendimiento

### Problema: Código corre lento  
**Síntomas:** Retrasos, tiempos de espera, comportamiento no responsivo

**Solución:**  
1. **Reducir frecuencia de lectura de sensores:** No leer sensores muy seguido  
2. **Optimizar bucles:** Evitar espera activa, usar sleep() o demoras  
3. **Problemas de memoria:**  
   - Cerrar aplicaciones innecesarias  
   - Liberar espacio de almacenamiento  
   - Monitorizar con `top` o `htop` en Pi  
4. **Velocidad de tarjeta SD:** Usar tarjeta SD o SSD más rápida para Raspberry Pi  
5. **Retrasos en red:** Usar operaciones asincrónicas para llamadas en red

### Problema: Errores por falta de memoria  
**Error:** `MemoryError` o congelamiento del sistema

**Solución:**  
1. **Para Raspberry Pi:**  
   - Cerrar aplicaciones innecesarias  
   - Aumentar espacio swap  
   - Usar sistema operativo ligero (versión Lite)  
   - Ampliar RAM (Pi 4 tiene opciones de 2/4/8GB)  
2. **Para Wio Terminal:**  
   - Reducir tamaños de buffer  
   - Usar imágenes más pequeñas  
   - Optimizar uso de cadenas  
   - Buscar fugas de memoria (memoria no liberada)

### Problema: Pérdida o corrupción de datos  
**Síntomas:** Mensajes faltantes, archivos corruptos

**Solución:**  
1. **Problemas con tarjeta SD:**  
   - Usar tarjetas SD de calidad (evitar baratas/falsificadas)  
   - Realizar copias de seguridad periódicas  
   - Apagar correctamente (no cortar energía)  
2. **Desbordamiento de buffer:** Aumentar buffers en el código  
3. **Fiabilidad de red:** Implementar lógica de reintento y manejo de errores  
4. **Calidad de Servicio:** Usar MQTT QoS 1 o 2 para mensajes importantes

---

## Mensajes Comunes de Error

### `ModuleNotFoundError: No module named 'X'`  
**Causa:** Paquete no instalado o entorno virtual no activado

**Solución:**  
```bash
pip install X
```
Asegúrese de activar el entorno virtual primero.

### `Permission denied` en Linux/macOS  
**Causa:** Se necesitan permisos elevados o problema con permisos de archivo

**Solución:**  
- Para operaciones del sistema: usar `sudo`  
- Para pip: NO use sudo con venv; active primero venv  
- Para puerto serial: Añadir usuario al grupo dialout: `sudo usermod -a -G dialout $USER`, luego cierre sesión/ingrese de nuevo

### `OSError: [Errno 98] Address already in use`  
**Causa:** Puerto ya está siendo usado por otro proceso

**Solución:**  
1. Encontrar proceso que usa el puerto: `lsof -i :<puerto>` o `netstat -ano | findstr :<puerto>`  
2. Matar proceso o usar puerto diferente en su código

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Causa:** Fallo en la validación del certificado SSL

**Solución:**  
1. Actualizar certificados: `pip install --upgrade certifi`  
2. Verificar que la hora del sistema sea correcta: `date`  
3. Solo para desarrollo (no producción): Desactivar verificación en código

### `IndentationError: unexpected indent`  
**Causa:** Problemas con indentación en Python (mezcla de tabulaciones/espacios)

**Solución:**  
1. Usar indentación consistente (4 espacios es estándar Python)  
2. Configurar editor para usar espacios en lugar de tabulaciones  
3. VS Code: Setear `"editor.insertSpaces": true` y `"editor.tabSize": 4`

### `UnicodeDecodeError` o `UnicodeEncodeError`  
**Causa:** Problemas con codificación de caracteres

**Solución:**  
```python
# Al leer archivos
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Al escribir archivos
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Obtener Ayuda

Si ha probado estos pasos y aún tiene problemas:

### 1. Revisar Recursos Existentes  
- **Documentación:** Revise el [README](README.md) y las instrucciones de la lección  
- **Guías de hardware:** Consulte [hardware.md](hardware.md) para info específica de hardware  
- **Wiki Seeed Studio:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) para componentes Grove

### 2. Buscar Problemas Similares  
- **Issues de GitHub:** Busque en [issues existentes](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Busque mensajes de error similares  
- **Foros de dispositivos:** Consulte foros de Raspberry Pi o Arduino

### 3. Crear un Issue en GitHub  
Si no encuentra solución:  
1. Vaya a [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Haga clic en "New Issue"  
3. Proporcione:  
   - Descripción clara del problema  
   - Pasos para reproducirlo  
   - Mensajes de error (texto completo)  
   - Versiones de hardware/software  
   - Qué ha intentado ya  
   - Capturas de pantalla si son relevantes

### 4. Unirse a la Comunidad  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Proporcionar Buen Reporte de Bug  
Un buen reporte de bug incluye:
- **Entorno:** SO, versión de Python, hardware utilizado
- **Pasos para reproducir:** Pasos exactos que causan el problema
- **Comportamiento esperado:** Lo que debería suceder
- **Comportamiento actual:** Lo que realmente sucede
- **Mensajes de error:** Texto completo del error, no capturas de pantalla
- **Código:** Ejemplo mínimo de código que reproduce el problema

---

## Consejos para la prevención

### Mejores prácticas generales
1. **Haz copias de seguridad:** Copias regulares de tarjetas SD/código que funcionen
2. **Documenta cambios:** Anota qué funciona en los comentarios
3. **Control de versiones:** Usa git para rastrear cambios de código
4. **Prueba incrementalmente:** Prueba cambios pequeños antes de combinarlos
5. **Lee los mensajes de error:** A menudo te dicen exactamente qué está mal
6. **Actualiza regularmente:** Mantén el software/firmware actualizado
7. **Usa componentes de calidad:** Evita cables/fuentes de alimentación baratos
8. **Alimentación estable:** Usa una fuente de alimentación adecuada (especialmente para Pi)

### Flujo de trabajo de desarrollo
1. **Comienza simple:** Empieza con código de ejemplo que funcione
2. **Un cambio a la vez:** Más fácil encontrar qué causa el fallo
3. **Prueba con frecuencia:** Detecta problemas temprano
4. **Mantén limpio:** Organiza archivos y código de forma lógica
5. **Comenta el código:** Tu yo futuro lo agradecerá

---

*Esta guía de solución de problemas es mantenida por la comunidad. Si encuentras una solución a un problema no listado aquí, considera [contribuir](CONTRIBUTING.md) para ayudar a otros.*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Aviso Legal**:
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Aunque nos esforzamos por la precisión, tenga en cuenta que las traducciones automáticas pueden contener errores o inexactitudes. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos responsabilizamos por malentendidos o interpretaciones erróneas que resulten del uso de esta traducción.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->