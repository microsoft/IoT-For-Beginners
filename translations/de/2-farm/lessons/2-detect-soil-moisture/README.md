C, ausgesprochen *I-Quadrat-C*, ist ein Protokoll für mehrere Controller und Peripheriegeräte, bei dem jedes angeschlossene Gerät als Controller oder Peripheriegerät über den I²C-Bus (der Name für ein Kommunikationssystem, das Daten überträgt) agieren kann. Daten werden in adressierten Paketen gesendet, wobei jedes Paket die Adresse des angeschlossenen Geräts enthält, für das es bestimmt ist.

> 💁 Dieses Modell wurde früher als Master/Slave bezeichnet, aber diese Terminologie wird aufgrund ihrer Assoziation mit der Sklaverei zunehmend vermieden. Die [Open Source Hardware Association hat Controller/Peripherie übernommen](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), aber Sie könnten noch auf Verweise auf die alte Terminologie stoßen.

Geräte haben eine Adresse, die beim Anschluss an den I²C-Bus verwendet wird, und diese ist normalerweise fest im Gerät kodiert. Zum Beispiel haben alle Grove-Sensoren von Seeed die gleiche Adresse, sodass alle Lichtsensoren dieselbe Adresse haben, alle Taster eine andere Adresse, die sich von der des Lichtsensors unterscheidet. Einige Geräte bieten Möglichkeiten, die Adresse zu ändern, indem man Jumper-Einstellungen ändert oder Pins miteinander verlötet.

I²C hat einen Bus, der aus 2 Hauptleitungen sowie 2 Stromleitungen besteht:

| Leitung | Name | Beschreibung |
| ---- | --------- | ----------- |
| SDA | Serielle Datenleitung | Diese Leitung dient zum Senden von Daten zwischen Geräten. |
| SCL | Serieller Takt | Diese Leitung sendet ein Taktsignal mit einer vom Controller festgelegten Rate. |
| VCC | Versorgungsspannung | Die Stromversorgung für die Geräte. Diese ist mit den SDA- und SCL-Leitungen verbunden, um deren Stromversorgung über einen Pull-up-Widerstand bereitzustellen, der das Signal ausschaltet, wenn kein Gerät der Controller ist. |
| GND | Masse | Dies stellt eine gemeinsame Masse für den Stromkreis bereit. |

![I2C-Bus mit 3 Geräten, die an die SDA- und SCL-Leitungen angeschlossen sind und eine gemeinsame Masseleitung teilen](../../../../../translated_images/de/i2c.83da845dde02256b.webp)

Um Daten zu senden, gibt ein Gerät eine Startbedingung aus, um anzuzeigen, dass es bereit ist, Daten zu senden. Es wird dann zum Controller. Der Controller sendet anschließend die Adresse des Geräts, mit dem er kommunizieren möchte, sowie die Information, ob er Daten lesen oder schreiben möchte. Nachdem die Daten übertragen wurden, sendet der Controller eine Stoppbedingung, um anzuzeigen, dass er fertig ist. Danach kann ein anderes Gerät zum Controller werden und Daten senden oder empfangen.

I<sup>2</sup>C hat Geschwindigkeitsbegrenzungen mit drei verschiedenen Modi, die mit festen Geschwindigkeiten arbeiten. Der schnellste ist der High-Speed-Modus mit einer maximalen Geschwindigkeit von 3,4 Mbps (Megabit pro Sekunde), obwohl nur sehr wenige Geräte diese Geschwindigkeit unterstützen. Der Raspberry Pi ist beispielsweise auf den Fast-Modus mit 400 Kbps (Kilobit pro Sekunde) begrenzt. Der Standardmodus läuft mit 100 Kbps.

> 💁 Wenn Sie einen Raspberry Pi mit einem Grove Base Hat als Ihre IoT-Hardware verwenden, können Sie auf der Platine mehrere I<sup>2</sup>C-Steckplätze sehen, die Sie zur Kommunikation mit I<sup>2</sup>C-Sensoren nutzen können. Analoge Grove-Sensoren verwenden ebenfalls I<sup>2</sup>C mit einem ADC, um analoge Werte als digitale Daten zu senden. Der von Ihnen verwendete Lichtsensor simulierte also einen analogen Pin, wobei der Wert über I<sup>2</sup>C gesendet wurde, da der Raspberry Pi nur digitale Pins unterstützt.

### Universal Asynchronous Receiver-Transmitter (UART)

UART umfasst physische Schaltungen, die es zwei Geräten ermöglichen, miteinander zu kommunizieren. Jedes Gerät hat zwei Kommunikationspins – Senden (Tx) und Empfangen (Rx), wobei der Tx-Pin des ersten Geräts mit dem Rx-Pin des zweiten verbunden ist und der Tx-Pin des zweiten Geräts mit dem Rx-Pin des ersten verbunden ist. Dies ermöglicht den Datenaustausch in beide Richtungen.

* Gerät 1 sendet Daten von seinem Tx-Pin, die von Gerät 2 an dessen Rx-Pin empfangen werden.
* Gerät 1 empfängt Daten an seinem Rx-Pin, die von Gerät 2 über dessen Tx-Pin gesendet werden.

![UART mit dem Tx-Pin eines Chips, der mit dem Rx-Pin eines anderen verbunden ist, und umgekehrt](../../../../../translated_images/de/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Die Daten werden bitweise gesendet, und dies wird als *serielle* Kommunikation bezeichnet. Die meisten Betriebssysteme und Mikrocontroller verfügen über *serielle Ports*, also Verbindungen, die serielle Daten senden und empfangen können und Ihrem Code zur Verfügung stehen.

UART-Geräte haben eine [Baudrate](https://wikipedia.org/wiki/Symbol_rate) (auch bekannt als Symbolrate), die die Geschwindigkeit angibt, mit der Daten in Bits pro Sekunde gesendet und empfangen werden. Eine übliche Baudrate ist 9.600, was bedeutet, dass 9.600 Bits (0 und 1) Daten pro Sekunde gesendet werden.

UART verwendet Start- und Stoppbits – das heißt, es sendet ein Startbit, um anzuzeigen, dass es gleich ein Byte (8 Bits) Daten senden wird, und ein Stoppbit, nachdem es die 8 Bits gesendet hat.

Die Geschwindigkeit von UART hängt von der Hardware ab, aber selbst die schnellsten Implementierungen überschreiten nicht 6,5 Mbps (Megabit pro Sekunde, oder Millionen von Bits, 0 oder 1, die pro Sekunde gesendet werden).

Sie können UART über GPIO-Pins verwenden – Sie können einen Pin als Tx und einen anderen als Rx festlegen und diese dann mit einem anderen Gerät verbinden.

> 💁 Wenn Sie einen Raspberry Pi mit einem Grove Base Hat als Ihre IoT-Hardware verwenden, können Sie auf der Platine einen UART-Steckplatz sehen, den Sie zur Kommunikation mit Sensoren nutzen können, die das UART-Protokoll verwenden.

### Serial Peripheral Interface (SPI)

SPI ist für die Kommunikation über kurze Entfernungen konzipiert, beispielsweise auf einem Mikrocontroller, um mit einem Speichergerät wie Flash-Speicher zu kommunizieren. Es basiert auf einem Controller/Peripherie-Modell, bei dem ein einzelner Controller (normalerweise der Prozessor des IoT-Geräts) mit mehreren Peripheriegeräten interagiert. Der Controller steuert alles, indem er eine Peripherie auswählt und Daten sendet oder anfordert.

> 💁 Wie bei I<sup>2</sup>C sind die Begriffe Controller und Peripherie neuere Änderungen, sodass Sie möglicherweise noch die älteren Begriffe sehen.

SPI-Controller verwenden drei Drähte sowie einen zusätzlichen Draht pro Peripheriegerät. Peripheriegeräte verwenden vier Drähte. Diese Drähte sind:

| Draht | Name | Beschreibung |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | Dieser Draht dient zum Senden von Daten vom Controller an die Peripherie. |
| CIPO | Controller Input, Peripheral Output | Dieser Draht dient zum Senden von Daten von der Peripherie an den Controller. |
| SCLK | Serial Clock | Dieser Draht sendet ein Taktsignal mit einer vom Controller festgelegten Rate. |
| CS   | Chip Select | Der Controller hat mehrere Drähte, einen pro Peripheriegerät, und jeder Draht ist mit dem CS-Draht des entsprechenden Peripheriegeräts verbunden. |

![SPI mit einem Controller und zwei Peripheriegeräten](../../../../../translated_images/de/spi.297431d6f98b386b.webp)

Der CS-Draht wird verwendet, um jeweils ein Peripheriegerät zu aktivieren, das über die COPI- und CIPO-Drähte kommuniziert. Wenn der Controller das Peripheriegerät wechseln muss, deaktiviert er den CS-Draht, der mit dem derzeit aktiven Peripheriegerät verbunden ist, und aktiviert dann den Draht, der mit dem Peripheriegerät verbunden ist, mit dem er als Nächstes kommunizieren möchte.

SPI ist *voll-duplex*, was bedeutet, dass der Controller gleichzeitig Daten senden und empfangen kann, und zwar vom selben Peripheriegerät über die COPI- und CIPO-Drähte. SPI verwendet ein Taktsignal auf dem SCLK-Draht, um die Geräte zu synchronisieren, sodass es im Gegensatz zum direkten Senden über UART keine Start- und Stoppbits benötigt.

Für SPI gibt es keine definierten Geschwindigkeitsbegrenzungen, und Implementierungen können oft mehrere Megabyte Daten pro Sekunde übertragen.

IoT-Entwicklerkits unterstützen häufig SPI über einige der GPIO-Pins. Beispielsweise können Sie auf einem Raspberry Pi die GPIO-Pins 19, 21, 23, 24 und 26 für SPI verwenden.

### Drahtlos

Einige Sensoren können über standardisierte drahtlose Protokolle wie Bluetooth (hauptsächlich Bluetooth Low Energy, oder BLE), LoRaWAN (ein **Lo**ng **Ra**nge Low Power Networking-Protokoll) oder WiFi kommunizieren. Diese ermöglichen den Einsatz von entfernten Sensoren, die nicht physisch mit einem IoT-Gerät verbunden sind.

Ein Beispiel hierfür sind kommerzielle Bodenfeuchtigkeitssensoren. Diese messen die Bodenfeuchtigkeit in einem Feld und senden die Daten über LoRaWAN an ein Hub-Gerät, das die Daten verarbeitet oder über das Internet weiterleitet. Dadurch kann der Sensor entfernt vom IoT-Gerät sein, das die Daten verwaltet, was den Stromverbrauch reduziert und den Bedarf an großen WiFi-Netzwerken oder langen Kabeln verringert.

BLE ist beliebt für fortschrittliche Sensoren wie Fitness-Tracker, die am Handgelenk getragen werden. Diese kombinieren mehrere Sensoren und senden die Sensordaten über BLE an ein IoT-Gerät, beispielsweise Ihr Telefon.

✅ Haben Sie Bluetooth-Sensoren bei sich, in Ihrem Haus oder in Ihrer Schule? Dazu könnten Temperatur- oder Bewegungssensoren, Geräte-Tracker und Fitnessgeräte gehören.

Eine beliebte Methode für kommerzielle Geräte, sich zu verbinden, ist Zigbee. Zigbee verwendet WiFi, um Mesh-Netzwerke zwischen Geräten zu bilden, wobei jedes Gerät sich mit so vielen nahegelegenen Geräten wie möglich verbindet und eine große Anzahl von Verbindungen wie ein Spinnennetz bildet. Wenn ein Gerät eine Nachricht ins Internet senden möchte, kann es diese an die nächstgelegenen Geräte senden, die sie dann an andere nahegelegene Geräte weiterleiten und so weiter, bis sie einen Koordinator erreicht und ins Internet gesendet werden kann.

> 🐝 Der Name Zigbee bezieht sich auf den Schwänzeltanz von Honigbienen nach ihrer Rückkehr zum Bienenstock.

## Bodenfeuchtigkeit messen

Sie können die Feuchtigkeitswerte im Boden mit einem Bodenfeuchtigkeitssensor, einem IoT-Gerät und einer Zimmerpflanze oder einem nahegelegenen Stück Erde messen.

### Aufgabe – Bodenfeuchtigkeit messen

Arbeiten Sie die entsprechende Anleitung durch, um die Bodenfeuchtigkeit mit Ihrem IoT-Gerät zu messen:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Einplatinencomputer - Raspberry Pi](pi-soil-moisture.md)
* [Einplatinencomputer - Virtuelles Gerät](virtual-device-soil-moisture.md)

## Sensor-Kalibrierung

Sensoren basieren auf der Messung elektrischer Eigenschaften wie Widerstand oder Kapazität.

> 🎓 Widerstand, gemessen in Ohm (Ω), ist der Grad des Widerstands gegen den elektrischen Strom, der durch ein Material fließt. Wenn eine Spannung an ein Material angelegt wird, hängt die Menge des Stroms, der durch das Material fließt, vom Widerstand des Materials ab. Weitere Informationen finden Sie auf der [Wikipedia-Seite über elektrischen Widerstand](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Kapazität, gemessen in Farad (F), ist die Fähigkeit einer Komponente oder eines Schaltkreises, elektrische Energie zu sammeln und zu speichern. Weitere Informationen finden Sie auf der [Wikipedia-Seite über Kapazität](https://wikipedia.org/wiki/Capacitance).

Diese Messungen sind nicht immer nützlich – stellen Sie sich einen Temperatursensor vor, der Ihnen eine Messung von 22,5 kΩ liefert! Stattdessen muss der gemessene Wert in eine nützliche Einheit umgewandelt werden, indem er kalibriert wird – das heißt, die gemessenen Werte werden mit der gemessenen Größe abgeglichen, um neue Messungen in die richtige Einheit umrechnen zu können.

Einige Sensoren sind bereits vorkalibriert. Beispielsweise war der Temperatursensor, den Sie in der letzten Lektion verwendet haben, bereits so kalibriert, dass er eine Temperaturmessung in °C zurückgeben kann. Im Werk würde der erste Sensor, der hergestellt wird, einer Reihe bekannter Temperaturen ausgesetzt und der Widerstand gemessen. Dies würde dann verwendet, um eine Berechnung zu erstellen, die den gemessenen Wert in Ω (die Einheit des Widerstands) in °C umwandeln kann.

> 💁 Die Formel zur Berechnung des Widerstands aus der Temperatur wird als [Steinhart-Hart-Gleichung](https://wikipedia.org/wiki/Steinhart–Hart_equation) bezeichnet.

### Kalibrierung des Bodenfeuchtigkeitssensors

Die Bodenfeuchtigkeit wird entweder durch gravimetrischen oder volumetrischen Wassergehalt gemessen.

* Gravimetrisch ist das Gewicht des Wassers in einer Gewichtseinheit des Bodens, gemessen als Anzahl der Kilogramm Wasser pro Kilogramm trockenen Boden.
* Volumetrisch ist das Volumen des Wassers in einer Volumeneinheit des Bodens, gemessen als Anzahl der Kubikmeter Wasser pro Kubikmeter trockenen Boden.

> 🇺🇸 Für Amerikaner können diese Einheiten aufgrund ihrer Konsistenz in Pfund statt Kilogramm oder in Kubikfuß statt Kubikmeter gemessen werden.

Bodenfeuchtigkeitssensoren messen elektrischen Widerstand oder Kapazität – dies variiert nicht nur mit der Bodenfeuchtigkeit, sondern auch mit der Bodenart, da die Bestandteile des Bodens seine elektrischen Eigenschaften verändern können. Idealerweise sollten Sensoren kalibriert werden – das heißt, Messwerte des Sensors werden mit Messungen verglichen, die mit einer wissenschaftlicheren Methode ermittelt wurden. Beispielsweise kann ein Labor den gravimetrischen Wassergehalt des Bodens mit Proben eines bestimmten Feldes berechnen, die einige Male im Jahr entnommen werden, und diese Zahlen zur Kalibrierung des Sensors verwenden, indem die Sensorwerte mit dem gravimetrischen Wassergehalt abgeglichen werden.

![Ein Diagramm von Spannung vs. Bodenfeuchtigkeitsgehalt](../../../../../translated_images/de/soil-moisture-to-voltage.df86d80cda158700.webp)

Das obige Diagramm zeigt, wie ein Sensor kalibriert wird. Die Spannung wird für eine Bodenprobe erfasst, die dann im Labor gemessen wird, indem das feuchte Gewicht mit dem trockenen Gewicht verglichen wird (indem das Gewicht im feuchten Zustand gemessen, dann im Ofen getrocknet und im trockenen Zustand gemessen wird). Sobald einige Messwerte erfasst wurden, können diese in einem Diagramm dargestellt und eine Linie an die Punkte angepasst werden. Diese Linie kann dann verwendet werden, um Bodenfeuchtigkeitssensorwerte, die von einem IoT-Gerät erfasst wurden, in tatsächliche Bodenfeuchtigkeitsmessungen umzuwandeln.

💁 Bei resistiven Bodenfeuchtigkeitssensoren steigt die Spannung mit zunehmender Bodenfeuchtigkeit. Bei kapazitiven Bodenfeuchtigkeitssensoren sinkt die Spannung mit zunehmender Bodenfeuchtigkeit, sodass die Diagramme für diese Sensoren abwärts statt aufwärts geneigt wären.

![Ein Bodenfeuchtigkeitswert, der aus dem Diagramm interpoliert wurde](../../../../../translated_images/de/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Das obige Diagramm zeigt einen Spannungswert von einem Bodenfeuchtigkeitssensor, und indem man diesem Wert zur Linie im Diagramm folgt, kann die tatsächliche Bodenfeuchtigkeit berechnet werden.

Dieser Ansatz bedeutet, dass der Landwirt nur einige Labormessungen für ein Feld durchführen muss, dann kann er IoT-Geräte verwenden, um die Bodenfeuchtigkeit zu messen – was die Zeit für die Messung erheblich verkürzt.

---

## 🚀 Herausforderung

Resistive und kapazitive Bodenfeuchtigkeitssensoren haben eine Reihe von Unterschieden. Was sind diese Unterschiede, und welcher Typ (falls überhaupt) ist der beste für einen Landwirt? Ändert sich diese Antwort zwischen Entwicklungsländern und Industrieländern?

## Quiz nach der Vorlesung

[Quiz nach der Vorlesung](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Überprüfung & Selbststudium

Lesen Sie mehr über die Hardware und Protokolle, die von Sensoren und Aktoren verwendet werden:

* [GPIO Wikipedia-Seite](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia-Seite](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia-Seite](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia-Seite](https://wikipedia.org/wiki/I²C)
* [Zigbee Wikipedia-Seite](https://wikipedia.org/wiki/Zigbee)

## Aufgabe

[Kalibrieren Sie Ihren Sensor](assignment.md)

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.