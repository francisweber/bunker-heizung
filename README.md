# Bunker-Heizung

ESP32-basierte Fernsteuerung einer VEVOR-/China-Dieselheizung über die originale 433-MHz-Funkfernbedienung.

## Weboberfläche

Die Bunker-Heizung kann über die integrierte ESPHome-Weboberfläche bedient werden:

**URL:**

http://bunker-heizung.local

Dort stehen die Funktionen:

- Heizung EIN
- Heizung AUS
- Heizung PLUS
- Heizung MINUS

## Aktueller Stand

Die 433-MHz-Funksteuerung der untersuchten älteren Steuerung wurde erfolgreich reverse-engineered und mit einem ESP32 und einem RUIZHI CC1101 Funkmodul reproduziert.

Alle vier Befehle funktionieren mit dem originalen LCD-Controller:

- PLUS
- MINUS
- ON
- OFF

Der aktuelle funktionierende Referenzstand befindet sich in `src/main.cpp`.

## Hardware

- ESP32 DevKit / `esp32dev`
- RUIZHI CC1101 433 MHz Funkmodul
- separate 4-Tasten-Funkfernbedienung ohne Display
- ältere LCD-Steuereinheit des Dieselheizers

Details: `docs/hardware.md`

## Funkprotokoll

Das konkret untersuchte System verwendet:

- 433,92 MHz
- ASK/OOK
- 24 Bit Nutztelegramm
- definierte HIGH-/LOW-Pulszeiten
- wiederholte Telegramme
- zusätzlichen kurzen Abschlussimpuls

Details: `docs/rf-reverse-engineering.md`

## Reproduktionsanleitung

Die Vorgehensweise für die Untersuchung einer weiteren Steuerungs-/Fernbedienungsvariante ist in `docs/rf-reproduction-guide.md` dokumentiert.

## Entwicklungsnotizen

Bekannte Stolpersteine und wichtige Erfahrungen aus der Entwicklung stehen in `docs/development-notes.md`.

## Varianten

Die aktuell untersuchte Steuerung wird als eigene Variante behandelt. Weitere Mainboards, Displays und Fernbedienungsgenerationen sollen später getrennt untersucht werden.

Details: `docs/controller-variants.md`

## Quellen

Externe Referenzen und deren konkrete Bedeutung für das Projekt: `docs/sources.md`

## Geplante Erweiterungen / TODO

Die grundlegende Fernsteuerung der Heizung über das originale 433-MHz-Funkprotokoll ist umgesetzt.

Für die nächste Ausbaustufe sind folgende Erweiterungen geplant:

- [ ] Raumtemperatursensor HTU31 integrieren
- [ ] DS18B20 zur Messung der Warmlufttemperatur am Heizungsausgang integrieren
- [ ] Temperaturwerte über die ESPHome-Weboberfläche anzeigen
- [ ] Temperaturverlauf zur Erkennung des Heizbetriebs auswerten
- [ ] Schnittstelle zwischen originalem LCD-Controller und Heizung untersuchen
- [ ] Display-/Controller-Signale am ESP32 abgreifen
- [ ] Betriebszustand der Heizung aus Temperatur- und Controllerdaten ableiten
- [ ] Display-/Controller-Steuerung perspektivisch in die ESPHome-Steuerung integrieren

### Vorgesehener Pinplan

Der aktuelle Funkaufbau bleibt unverändert.

| Funktion | ESP32-Pin |
|---|---:|
| Funkmodul GDO0 | GPIO 4 |
| Funkmodul CSN | GPIO 5 |
| Funkmodul SCK | GPIO 18 |
| Funkmodul MISO | GPIO 19 |
| Funkmodul MOSI | GPIO 23 |
| HTU31 SDA | GPIO 21 |
| HTU31 SCL | GPIO 22 |
| DS18B20 Warmlufttemperatur | GPIO 25 |
| Display-/Controller-Schnittstelle | GPIO 16 |

> **Hinweis:** GPIO 21, 22, 25 und 16 sind für die geplanten Erweiterungen zunächst vorgesehen. Die tatsächliche Eignung und Verdrahtung wird vor der Umsetzung der jeweiligen Erweiterung geprüft.
