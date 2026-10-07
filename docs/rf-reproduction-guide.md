# Anleitung zur Reproduktion einer weiteren Funkfernbedienung

Dieses Dokument beschreibt die Vorgehensweise, die sich beim untersuchten System bewährt hat.

Es dient als Arbeitsanleitung für eine spätere andere Mainboard-/Display-/Fernbedienungsvariante.

## 1. Hardware vorbereiten

- ESP32 anschließen
- CC1101-Funkmodul anschließen
- Versorgung mit 3,3 V sicherstellen
- gemeinsame Masse herstellen
- SPI-Verbindung prüfen

Vor weiteren Messungen sicherstellen, dass das Funkmodul vom ESP32 erkannt wird.

## 2. Seriellen Monitor sauber starten

Nach Upload den seriellen Monitor öffnen.

Wenn unmittelbar Zeichen wie `?`, `x` oder unlesbare Zeichen erscheinen:

1. nicht sofort den Code ändern
2. einmal die EN-Taste des ESP32 drücken
3. auf einen sauberen Neustart warten
4. erst danach den eigentlichen Test durchführen

Die BOOT-Taste ist davon zu unterscheiden. Sie wird hauptsächlich benötigt, wenn der ESP32 beim Flashen nicht automatisch in den Bootloader geht.

## 3. Empfang zunächst als Rohsignal untersuchen

Nicht sofort ein bestimmtes Protokoll annehmen.

Zunächst:

- Frequenz untersuchen
- Modulation untersuchen
- GDO0-Rohsignal aufzeichnen
- Flanken zeitlich vermessen
- mehrere Tastendrücke vergleichen

## 4. Wiederholungen untersuchen

Ein einzelner Tastendruck kann aus mehreren identischen Telegrammen bestehen.

Deshalb nicht nur das erste erkannte Telegramm betrachten.

Dokumentieren:

- Telegrammlänge
- Pause zwischen Telegrammen
- zusätzliche Impulse
- Verhalten bei kurzem Tastendruck
- Verhalten bei langem Tastendruck

## 5. Pulszeiten bestimmen

Für jedes erkannte Symbol HIGH- und LOW-Dauer messen.

Nicht vorschnell annehmen, dass das Signal UART, Manchester oder ein anderes bekanntes Verfahren ist.

Erst die physikalische Pulsfolge dokumentieren.

## 6. Befehle vergleichen

Mindestens zwei oder besser alle verfügbaren Tasten aufzeichnen.

Danach prüfen:

- gemeinsamer Präfix
- variable Bits
- Länge
- mögliche Befehlsfelder
- zusätzliche Prüfinformationen

## 7. Originalsignal mit eigener Übertragung vergleichen

Die eigene TX-Aufnahme muss hinsichtlich

- Polarität
- HIGH-Zeiten
- LOW-Zeiten
- Telegrammlänge
- Wiederholungsabstand
- Abschlussimpuls

mit der Originalaufnahme verglichen werden.

## 8. Erst danach am Originalcontroller testen

Wenn die Rohdaten möglichst genau reproduziert werden, das Signal am Originalcontroller testen.

Bei sicherheitsrelevanten Tests am Heizgerät besonders vorsichtig vorgehen.

## 9. Erfolgreichen Stand sofort sichern

Sobald der Originalcontroller reproduzierbar reagiert:

1. funktionierenden Code nicht weiter verändern
2. Rohaufnahme sichern
3. Befehle und Timing dokumentieren
4. Git-Commit erstellen
5. erst danach die Integration in ESPHome beginnen

## 10. Für eine zweite Steuerung

Bei einer anderen Steuerung nicht automatisch die Werte dieses Projekts übernehmen.

Stattdessen zunächst prüfen:

- Frequenz
- Modulation
- Bit-/Symbolstruktur
- Telegrammlänge
- Timing
- Wiederholungsmechanismus
- Befehle

Die hier ermittelte Vorgehensweise ist wiederverwendbar; die konkreten Telegrammdaten sind es möglicherweise nicht.
