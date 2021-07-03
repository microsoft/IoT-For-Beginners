# Classify an image - Wio Terminal

In this part of the lesson, you will send the image captured by the camera to the Custom Vision service to classify it.

## Classify an image

The Custom Vision service has a REST API you can call from the Wio Terminal use to classify images. This REST API is accessed over an HTTPS connection - a secure HTTP connection.

When interacting with HTTPS endpoints, the client code needs to request the public key certificate from the server being accessed, and use that to encrypt the traffic it sends. Your web browser does this automatically, but microcontrollers do not. You will need to request this certificate manually and use it to create a secure connection to the REST API. These certificates don't change, so once you have a certificate, it can be hard coded in your application.

These certificates contain public keys, and don't need to be kept secure. You can use them in your source code and share them in public on places like GitHub.

### Task - set up a SSL client

1. Open the `fruit-quality-detector` app project if it's not already open

1. Open the `config.h` header file, and add the following:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    This is the *Microsoft Azure DigiCert Global Root G2 certificate* - it's one of the certificates used by many Azure services globally.

    > 💁 To see that this is the certificate to use, run the following command on macOS or Linux. If you are using Windows, you can run this command using the [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > The output will list the DigiCert Global Root G2 certificate.

1. Open `main.cpp` and add the following include directive:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Below the include directives, declare an instance of `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    This class contains code to communicate with web endpoints over HTTPS.

1. In the `connectWiFi` method, set the WiFiClientSecure to use the DigiCert Global Root G2 certificate:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Task - classify an image

1. Add the following as an additional line to the `lib_deps` list in the `platformio.ini` file:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    This imports [ArduinoJson](https://arduinojson.org), an Arduino JSON library, and will be used to decode the JSON response from the REST API.

1. In `config.h`, add constants for the prediction URL and Key from the Custom Vision service:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Replace `<PREDICTION_URL>` with the prediction URL from Custom Vision. Replace `<PREDICTION_KEY>` with the prediction key.

1. In `main.cpp`, add an include directive for the ArduinoJson library:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Add the following function to `main.cpp`, above the `buttonPressed` function.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    This code starts by declaring an `HTTPClient` - a class that contains methods to interact with REST APIs. It then connects the client to the prediction URL using the `WiFiClientSecure` instance that was set up with the Azure public key.

    Once connected, it sends headers - information about the upcoming request that will be made against the REST API. The `Content-Type` header indicates the API call will send raw binary data, the `Prediction-Key` header passes the Custom Vision prediction key.

    Next a POST request is made to the HTTP client, uploading a byte array. This will contain the JPEG image captured from the camera when this function is called.

    > 💁 POST request are meant for sending data, and getting a response. There are other request types such as GET requests that retrieve data. GET requests are used by your web browser to load web pages.

    The POST request returns a response status code. These are well-defined values, with 200 meaning **OK** - the POST request was successful.

    > 💁 You can see all the response status codes in the [List of HTTP status codes page on Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    If a 200 is returned, the result is read from the HTTP client. This is a text response from the REST API with the results of the prediction as a JSON document. The JSON is in the following format:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    The important part here is the `predictions` array. This contains the predictions, with one entry for each tag containing the tag name and the probability. The probabilities returned are floating point numbers from 0-1, with 0 being a 0% chance of matching the tag, and 1 being a 100% chance.

    > 💁 Image classifiers will return the percentages for all tags that have been used. Each tag will have a probability that the image matches that tag.

    This JSON is decoded, and the probabilities for each tag are sent to the serial monitor.

1. In the `buttonPressed` function, either replace the code that saves to the SD card with a call to `classifyImage`, or add it after the image is written, but **before** the buffer is deleted:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 If you replace the code that saves to the SD card you can clean up your code removing the `setupSDCard` and `saveToSDCard` functions.

1. Upload and run your code. Point the camera at some fruit and press the C button. You will see the output in the serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    You will be able to see the image that was taken, and these values in the **Predictions** tab in Custom Vision.

    ![A banana in custom vision predicted ripe at 56.8% and unripe at 43.1%](../../../images/custom-vision-banana-prediction.png)

> 💁 You can find this code in the [code-classify/wio-terminal](code-classify/wio-terminal) folder.

😀 Your fruit quality classifier program was a success!
