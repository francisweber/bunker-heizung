# Bunker-Heizung

ESP32-basierte Fernsteuerung einer VEVOR-/China-Dieselheizung über die originale 433-MHz-Funkfernbedienung.

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

## Nächster Entwicklungsschritt

Die funktionierende Funksteuerung soll in ESPHome integriert und über die ESPHome-Weboberfläche bedienbar gemacht werden.

Später vorgesehen ist zusätzlich die Untersuchung des Kabel-/Datenbusses zwischen Mainboard und Display, um Statusinformationen des Heizgeräts auszulesen.
