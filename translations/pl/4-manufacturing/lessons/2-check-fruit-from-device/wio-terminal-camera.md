<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-26T06:34:51+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "pl"
}
-->
# Zrób zdjęcie - Wio Terminal

W tej części lekcji dodasz kamerę do swojego Wio Terminal i zrobisz zdjęcia za jej pomocą.

## Sprzęt

Wio Terminal potrzebuje kamery.

Kamera, której użyjesz, to [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Jest to kamera o rozdzielczości 2 megapikseli, oparta na czujniku obrazu OV2640. Komunikuje się za pomocą interfejsu SPI, aby przechwytywać obrazy, i używa I2C do konfiguracji czujnika.

## Podłącz kamerę

ArduCam nie posiada gniazda Grove, zamiast tego łączy się z magistralami SPI i I2C za pomocą pinów GPIO na Wio Terminal.

### Zadanie - podłącz kamerę

Podłącz kamerę.

![Czujnik ArduCam](../../../../../translated_images/pl/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. Piny na spodzie ArduCam muszą być podłączone do pinów GPIO na Wio Terminal. Aby łatwiej było znaleźć odpowiednie piny, przyklej naklejkę z oznaczeniami pinów GPIO, która jest dołączona do Wio Terminal:

    ![Wio Terminal z naklejką oznaczającą piny GPIO](../../../../../translated_images/pl/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Używając przewodów połączeniowych, wykonaj następujące połączenia:

    | Pin ArduCAM | Pin Wio Terminal | Opis                                    |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | Wybór układu SPI                        |
    | MOSI        | 19 (SPI_MOSI)    | Wyjście kontrolera SPI, wejście peryferyjne |
    | MISO        | 21 (SPI_MISO)    | Wejście kontrolera SPI, wyjście peryferyjne |
    | SCK         | 23 (SPI_SCLK)    | Zegar szeregowy SPI                     |
    | GND         | 6 (GND)          | Masa - 0V                               |
    | VCC         | 4 (5V)           | Zasilanie 5V                            |
    | SDA         | 3 (I2C1_SDA)     | Dane szeregowe I2C                      |
    | SCL         | 5 (I2C1_SCL)     | Zegar szeregowy I2C                     |

    ![Wio Terminal podłączony do ArduCam za pomocą przewodów połączeniowych](../../../../../translated_images/pl/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    Połączenia GND i VCC dostarczają zasilanie 5V do ArduCam. Kamera działa na 5V, w przeciwieństwie do czujników Grove, które działają na 3V. Zasilanie pochodzi bezpośrednio z połączenia USB-C, które zasila urządzenie.

    > 💁 W przypadku połączenia SPI etykiety pinów na ArduCam i nazwy pinów Wio Terminal używane w kodzie nadal korzystają ze starej konwencji nazewnictwa. Instrukcje w tej lekcji będą używać nowej konwencji nazewnictwa, z wyjątkiem przypadków, gdy nazwy pinów są używane w kodzie.

1. Teraz możesz podłączyć Wio Terminal do komputera.

## Zaprogramuj urządzenie, aby połączyć się z kamerą

Wio Terminal można teraz zaprogramować, aby korzystał z podłączonej kamery ArduCAM.

### Zadanie - zaprogramuj urządzenie, aby połączyć się z kamerą

1. Utwórz nowy projekt Wio Terminal w PlatformIO. Nazwij ten projekt `fruit-quality-detector`. Dodaj kod w funkcji `setup`, aby skonfigurować port szeregowy.

1. Dodaj kod do połączenia z WiFi, umieszczając dane logowania w pliku `config.h`. Nie zapomnij dodać wymaganych bibliotek do pliku `platformio.ini`.

1. Biblioteka ArduCam nie jest dostępna jako biblioteka Arduino, którą można zainstalować z pliku `platformio.ini`. Zamiast tego trzeba ją zainstalować ze źródła z ich strony GitHub. Możesz to zrobić na dwa sposoby:

    * Klonując repozytorium z [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Przechodząc do repozytorium na GitHub pod adresem [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) i pobierając kod jako plik zip za pomocą przycisku **Code**

1. Potrzebujesz tylko folderu `ArduCAM` z tego kodu. Skopiuj cały folder do folderu `lib` w swoim projekcie.

    > ⚠️ Należy skopiować cały folder, aby kod znajdował się w `lib/ArduCam`. Nie kopiuj tylko zawartości folderu `ArduCam` do folderu `lib`, skopiuj cały folder.

1. Kod biblioteki ArduCam działa dla wielu typów kamer. Typ kamery, której chcesz użyć, jest konfigurowany za pomocą flag kompilatora - dzięki temu biblioteka jest jak najmniejsza, usuwając kod dla kamer, których nie używasz. Aby skonfigurować bibliotekę dla kamery OV2640, dodaj następujący kod na końcu pliku `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Ustawia to dwie flagi kompilatora:

      * `ARDUCAM_SHIELD_V2`, aby poinformować bibliotekę, że kamera znajduje się na płytce Arduino, znanej jako shield.
      * `OV2640_CAM`, aby poinformować bibliotekę, aby uwzględniała tylko kod dla kamery OV2640.

1. Dodaj plik nagłówkowy do folderu `src`, nazwij go `camera.h`. Będzie on zawierał kod do komunikacji z kamerą. Dodaj do tego pliku następujący kod:

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

    Jest to kod niskopoziomowy, który konfiguruje kamerę za pomocą bibliotek ArduCam i pobiera obrazy w razie potrzeby za pomocą magistrali SPI. Kod ten jest bardzo specyficzny dla ArduCam, więc na tym etapie nie musisz się martwić, jak działa.

1. W pliku `main.cpp` dodaj następujący kod poniżej innych instrukcji `include`, aby dołączyć nowy plik i utworzyć instancję klasy kamery:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Tworzy to obiekt `Camera`, zapisujący obrazy jako JPEG w rozdzielczości 640x480. Chociaż obsługiwane są wyższe rozdzielczości (do 3280x2464), klasyfikator obrazu działa na znacznie mniejszych obrazach (227x227), więc nie ma potrzeby przechwytywania i przesyłania większych obrazów.

1. Dodaj poniższy kod, aby zdefiniować funkcję konfigurującą kamerę:

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

    Funkcja `setupCamera` zaczyna od skonfigurowania pinu wyboru układu SPI (`PIN_SPI_SS`) jako wysokiego, czyniąc Wio Terminal kontrolerem SPI. Następnie uruchamia magistrale I2C i SPI. Na końcu inicjalizuje klasę kamery, która konfiguruje ustawienia czujnika kamery i upewnia się, że wszystko jest poprawnie podłączone.

1. Wywołaj tę funkcję na końcu funkcji `setup`:

    ```cpp
    setupCamera();
    ```

1. Zbuduj i wgraj ten kod, a następnie sprawdź dane wyjściowe w monitorze szeregowym. Jeśli zobaczysz komunikat `Error setting up the camera!`, sprawdź okablowanie, aby upewnić się, że wszystkie przewody są podłączone do odpowiednich pinów na ArduCam i Wio Terminal, a wszystkie przewody są dobrze osadzone.

## Zrób zdjęcie

Wio Terminal można teraz zaprogramować tak, aby robił zdjęcie po naciśnięciu przycisku.

### Zadanie - zrób zdjęcie

1. Mikrokontrolery wykonują kod w sposób ciągły, więc trudno jest wywołać coś takiego jak zrobienie zdjęcia bez reakcji na czujnik. Wio Terminal ma przyciski, więc kamerę można skonfigurować tak, aby była wyzwalana jednym z przycisków. Dodaj poniższy kod na końcu funkcji `setup`, aby skonfigurować przycisk C (jeden z trzech przycisków na górze, ten najbliżej przełącznika zasilania).

    ![Przycisk C na górze, najbliżej przełącznika zasilania](../../../../../translated_images/pl/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Tryb `INPUT_PULLUP` zasadniczo odwraca wejście. Na przykład, normalnie przycisk wysyła niski sygnał, gdy nie jest naciśnięty, i wysoki sygnał, gdy jest naciśnięty. Gdy ustawiony jest na `INPUT_PULLUP`, wysyła wysoki sygnał, gdy nie jest naciśnięty, i niski sygnał, gdy jest naciśnięty.

1. Dodaj pustą funkcję reagującą na naciśnięcie przycisku przed funkcją `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Wywołaj tę funkcję w metodzie `loop`, gdy przycisk jest naciśnięty:

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

    Ten klucz sprawdza, czy przycisk jest naciśnięty. Jeśli jest naciśnięty, wywoływana jest funkcja `buttonPressed`, a pętla opóźnia się o 2 sekundy. Ma to na celu umożliwienie zwolnienia przycisku, aby długie naciśnięcie nie zostało zarejestrowane dwukrotnie.

    > 💁 Przycisk na Wio Terminal jest ustawiony na `INPUT_PULLUP`, więc wysyła wysoki sygnał, gdy nie jest naciśnięty, i niski sygnał, gdy jest naciśnięty.

1. Dodaj poniższy kod do funkcji `buttonPressed`:

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

    Ten kod rozpoczyna przechwytywanie obrazu, wywołując `startCapture`. Sprzęt kamery nie działa w ten sposób, że zwraca dane na żądanie, zamiast tego wysyłasz instrukcję rozpoczęcia przechwytywania, a kamera działa w tle, aby przechwycić obraz, przekonwertować go na JPEG i zapisać w lokalnym buforze na samej kamerze. Wywołanie `captureReady` sprawdza, czy przechwytywanie obrazu zostało zakończone.

    Po zakończeniu przechwytywania dane obrazu są kopiowane z bufora na kamerze do lokalnego bufora (tablicy bajtów) za pomocą wywołania `readImageToBuffer`. Długość bufora jest następnie wysyłana do monitora szeregowego.

1. Zbuduj i wgraj ten kod, a następnie sprawdź dane wyjściowe w monitorze szeregowym. Za każdym razem, gdy naciśniesz przycisk C, obraz zostanie przechwycony, a jego rozmiar zostanie wysłany do monitora szeregowego.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Różne obrazy będą miały różne rozmiary. Są one kompresowane jako JPEG, a rozmiar pliku JPEG dla danej rozdzielczości zależy od tego, co znajduje się na obrazie.

> 💁 Kod ten znajdziesz w folderze [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Udało Ci się przechwycić obrazy za pomocą Wio Terminal.

## Opcjonalne - zweryfikuj obrazy z kamery za pomocą karty SD

Najłatwiejszym sposobem zobaczenia obrazów przechwyconych przez kamerę jest zapisanie ich na karcie SD w Wio Terminal, a następnie obejrzenie ich na komputerze. Wykonaj ten krok, jeśli masz wolną kartę microSD i gniazdo microSD w komputerze lub adapter.

Wio Terminal obsługuje tylko karty microSD o pojemności do 16 GB. Jeśli masz większą kartę SD, nie będzie działać.

### Zadanie - zweryfikuj obrazy z kamery za pomocą karty SD

1. Sformatuj kartę microSD jako FAT32 lub exFAT za pomocą odpowiednich aplikacji na komputerze (Disk Utility na macOS, File Explorer na Windows lub narzędzi wiersza poleceń w Linux).

1. Włóż kartę microSD do gniazda tuż poniżej przełącznika zasilania. Upewnij się, że jest całkowicie wsunięta, aż kliknie i pozostanie na miejscu. Może być konieczne użycie paznokcia lub cienkiego narzędzia.

1. Dodaj następujące instrukcje `include` na początku pliku `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Dodaj następującą funkcję przed funkcją `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Funkcja ta konfiguruje kartę SD za pomocą magistrali SPI.

1. Wywołaj tę funkcję z funkcji `setup`:

    ```cpp
    setupSDCard();
    ```

1. Dodaj poniższy kod powyżej funkcji `buttonPressed`:

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

    Definiuje to globalną zmienną dla licznika plików. Jest ona używana do nazw plików obrazów, aby można było przechwycić wiele obrazów z rosnącymi nazwami plików - `1.jpg`, `2.jpg` i tak dalej.

    Następnie definiuje funkcję `saveToSDCard`, która przyjmuje bufor danych bajtowych i długość bufora. Tworzona jest nazwa pliku przy użyciu licznika plików, a licznik plików jest zwiększany, aby przygotować się na kolejny plik. Dane binarne z bufora są następnie zapisywane do pliku.

1. Wywołaj funkcję `saveToSDCard` z funkcji `buttonPressed`. Wywołanie powinno być **przed** usunięciem bufora:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Zbuduj i wgraj ten kod, a następnie sprawdź dane wyjściowe w monitorze szeregowym. Za każdym razem, gdy naciśniesz przycisk C, obraz zostanie przechwycony i zapisany na karcie SD.

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

1. Wyłącz zasilanie karty microSD i wysuń ją, delikatnie wciskając i zwalniając, a karta wyskoczy. Może być konieczne użycie cienkiego narzędzia, aby to zrobić. Podłącz kartę microSD do komputera, aby obejrzeć obrazy.

    ![Zdjęcie banana wykonane za pomocą ArduCam](../../../../../translated_images/pl/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.jpg)
💁 Może zająć kilka zdjęć, zanim balans bieli aparatu dostosuje się. Zauważysz to na podstawie kolorów uchwyconych zdjęć, pierwsze kilka może wyglądać na nieprawidłowe. Zawsze możesz obejść ten problem, zmieniając kod tak, aby uchwycić kilka zdjęć, które są ignorowane w funkcji `setup`.


**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.