# Hardware

## 1. Zielsystem

Untersucht wurde eine ältere VEVOR-/China-Dieselheizung mit separater LCD-Steuereinheit und einer unabhängigen 433-MHz-Funkfernbedienung.

Die Funkfernbedienung besitzt vier Tasten:

- ON
- OFF
- PLUS
- MINUS

Die Funkfernbedienung besitzt kein Display.

Die Funksteuerung wurde unabhängig von der später geplanten ESPHome-Oberfläche untersucht.

## 2. ESP32

Verwendet wird ein ESP32 DevKit mit PlatformIO:

- Board: `esp32dev`
- Framework: Arduino
- Flash: 4 MB
- CPU: 160 MHz

Der aktuelle Entwicklungsstand verwendet PlatformIO im Projektverzeichnis.

## 3. Funkmodul

Verwendet wird ein RUIZHI CC1101 433-MHz-Modul.

Im Projekt wird das Modul bewusst als **Funkmodul** bezeichnet.

Technische Bezeichnung:

> RUIZHI CC1101 433 MHz

Versorgung:

- 3,3 V
- gemeinsame Masse mit dem ESP32

## 4. Funkmodul 1 – funktionierender TX-Aufbau

| Funkmodul-Pin | Funktion | ESP32 |
|---|---|---|
| 1 | GND | GND |
| 2 | VCC | 3,3 V |
| 3 | GDO0 | GPIO 4 |
| 4 | CSN | GPIO 5 |
| 5 | SCK | GPIO 18 |
| 6 | MOSI | GPIO 23 |
| 7 | MISO / GDO1 | GPIO 19 |
| 8 | GDO2 | nicht angeschlossen |

SPI:

- SCK = GPIO 18
- MISO = GPIO 19
- MOSI = GPIO 23
- CSN = GPIO 5

GDO0 = GPIO 4.

## 5. Funkmodul 2

Ein zweites identisches Funkmodul wurde zeitweise für unabhängige RX-/TX-Tests verwendet.

Verdrahtung:

- GND → GND
- VCC → 3,3 V
- GDO0 → GPIO 27
- CSN → GPIO 15
- SCK → GPIO 18
- MOSI → GPIO 23
- MISO → GPIO 19
- GDO2 → nicht angeschlossen

Die SPI-Leitungen SCK, MOSI und MISO wurden gemeinsam verwendet. CSN und GDO0 waren getrennt.

Mit beiden Modulen konnte die Funkstrecke unabhängig geprüft werden.

## 6. Verkabelung

Die Verdrahtung wurde durch mehrere Tests überprüft.

Beide Funkmodule wurden vom ESP32 erkannt. Zusätzlich konnte ein vom ersten Funkmodul erzeugtes Rohsignal mit dem zweiten Funkmodul empfangen werden.

Für die weitere Entwicklung gilt daher:

> Die Funkmodul-Verkabelung ist geprüft und wird nicht ohne neue gegenteilige Messung als Fehlerquelle angenommen.

## 7. Originale Steuerung

Das untersuchte System besteht aus:

- Dieselheizung
- älterer LCD-Steuereinheit
- separater 4-Tasten-433-MHz-Funkfernbedienung

Die Funkfernbedienung ist nicht mit der LCD-Steuereinheit identisch.

## 8. Abgrenzung

Die später geplante Untersuchung des Kabel-/Datenbusses zwischen Mainboard und Display ist ein separates Reverse-Engineering-Thema.

Funksteuerung und Display-/Controller-Bus werden im Projekt getrennt dokumentiert.
