# Steuerungsvarianten

## Variante A – aktuell untersucht

Status: **Funksteuerung erfolgreich reproduziert**

Merkmale:

- ältere Dieselheizung
- separates LCD-Bedienteil
- separate 4-Tasten-Funkfernbedienung ohne Display
- 433-MHz-Funk
- 24-Bit-Telegramme
- ON / OFF / PLUS / MINUS funktionieren

Diese Variante ist der Referenzstand des Projekts.

## Variante B – zukünftige andere Steuerung

Geplant ist die Untersuchung eines weiteren Mainboards bzw. einer weiteren Display-/Controller-Generation.

Dabei darf nicht vorausgesetzt werden, dass:

- die gleiche Fernbedienung verwendet wird
- die gleiche Frequenz verwendet wird
- die gleiche Bitlänge verwendet wird
- das gleiche Timing verwendet wird
- die gleichen Befehlswerte verwendet werden

Die Untersuchung soll nach der in `rf-reproduction-guide.md` beschriebenen Methode erfolgen.

## Display-/Controller-Bus

Ein weiterer geplanter Entwicklungsschritt ist das Abgreifen des Datenverkehrs zwischen Mainboard und Display.

Ziel ist perspektivisch die Erfassung von Informationen wie:

- Betriebszustand
- Heizstufe
- Temperatur
- Fehlerzustände
- weitere vom Controller übertragene Daten

Dieser Teil ist getrennt von der 433-MHz-Funksteuerung zu behandeln.

Die Funksteuerung dient zur Übertragung von Befehlen.

Der Display-/Controller-Bus soll perspektivisch zur Erfassung von Statusinformationen dienen.
