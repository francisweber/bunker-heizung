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

## 5. Verkabelung

Die Verdrahtung des aktuell verwendeten Funkmoduls wurde durch mehrere Tests überprüft.

Für die weitere Entwicklung gilt daher:

> Die Funkmodul-Verkabelung ist geprüft und wird nicht ohne neue gegenteilige Messung als Fehlerquelle angenommen.

## 6. Originale Steuerung

Das untersuchte System besteht aus:

- Dieselheizung
- älterer LCD-Steuereinheit
- separater 4-Tasten-433-MHz-Funkfernbedienung

Die Funkfernbedienung ist nicht mit der LCD-Steuereinheit identisch.

## 7. Abgrenzung

Die später geplante Untersuchung des Kabel-/Datenbusses zwischen Mainboard und Display ist ein separates Reverse-Engineering-Thema.

Funksteuerung und Display-/Controller-Bus werden im Projekt getrennt dokumentiert.
