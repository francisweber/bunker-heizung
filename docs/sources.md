# Externe Quellen

Diese Liste enthält nur Quellen, die für das Projekt bzw. die spätere Weiterentwicklung tatsächlich relevant sind.

## 1. Afterburner

Projekt von Ray Jones.

https://mrjones.id.au/afterburner/

Relevanz:

- verschiedene China-Dieselheizer und Controller-Varianten
- Informationen zu UHF-/433-MHz-Fernbedienungen
- Abbildungen und Hinweise zu älteren Steuerungen
- später möglicherweise interessant für die Untersuchung des Controller-/Display-Busses

## 2. Afterburner V3.5 User Manual

https://mrjones.id.au/afterburner/assets/files/UserManual-V3.5.pdf

Relevanz:

Die Dokumentation beschreibt unter anderem eine 433-MHz-UHF-Fernbedienung mit vier Funktionen und zeigt eine zum untersuchten Fernbedienungstyp passende OEM-Fernbedienung.

Wichtig:

Die Dokumentation erwähnt eine 20-Bit-Codierung für eine dort beschriebene Fernbedienung. Das wurde nicht als identisch mit dem in diesem Projekt experimentell ermittelten 24-Bit-Telegramm angenommen.

Die Quelle dient daher als Referenz für Hardware-/Controllerfamilien und nicht als Beweis für das hier ermittelte Protokoll.

## 3. Afterburner V3.2 User Manual

http://www.mrjones.id.au/afterburner/assets/files/UserManual-V3.2.pdf

Relevanz:

Ältere Version der Afterburner-Dokumentation und zusätzliche Referenz für Controller- und Heizungsvarianten.

## 4. BluetoothHeater

https://gitlab.com/mrjones.id.au/bluetoothheater

Relevanz:

Projekt aus demselben Umfeld. Besonders interessant für spätere Untersuchungen von Controller-/Heizungs-Kommunikation.

## 5. DieselHeaterRF

https://github.com/jakkik/DieselHeaterRF

Relevanz:

Reverse Engineering bzw. Steuerung einer anderen Generation von Dieselheizer-Fernbedienungen.

Wichtig:

Nicht als direktes Protokoll dieses Projekts verwenden. Die dort behandelte Fernbedienungsgeneration unterscheidet sich von der hier untersuchten separaten 4-Tasten-Fernbedienung.

## 6. vevor_heater_control

https://github.com/zatakon/vevor_heater_control

Relevanz:

Alternative Open-Source-Arbeiten zur Steuerung von VEVOR-/China-Dieselheizungen.

Dient als zusätzliche technische Referenz.

## 7. Eigene Messdaten haben Vorrang

Die externen Quellen dienten zur Einordnung und als technische Referenz.

Für die konkrete Funkreproduktion dieses Projekts gelten die eigenen Messdaten als maßgebliche Grundlage:

- Original-RF-Captures
- gemessene Pulszeiten
- gemessene Telegrammlänge
- gemessene Wiederholungsstruktur
- erfolgreich getestete TX-Signale
- Reaktion des Originalcontrollers

Externe Quellen dürfen diese eigenen Messungen nicht stillschweigend ersetzen.
