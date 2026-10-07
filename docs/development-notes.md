# Entwicklungsnotizen und wichtige Stolpersteine

Dieses Dokument enthält praktische Erfahrungen, die während der Entwicklung viel Zeit gekostet haben.

## 1. Serielle Ausgabe mit `?`, `x` oder unlesbaren Zeichen

### Problem

Nach Reset oder beim Öffnen des seriellen Monitors erschienen teilweise Zeichen wie:

```text
?
x
� �
```

Teilweise sah die Ausgabe wie zufälliger Datenmüll aus.

### Falsche Reaktion

Mehrfach wurde zunächst angenommen, dass der gerade getestete Code oder die Funkkommunikation fehlerhaft sei.

Dadurch wurden unnötig Codeänderungen und weitere Tests durchgeführt.

### Lösung

Seriellen Monitor öffnen und bei einer nicht sauber startenden Ausgabe einmal die **EN-Taste** des ESP32 drücken.

Danach startet der ESP32 sauber neu und die normale Programmausgabe erscheint.

### Regel für zukünftige Tests

> Vor einem Test immer einen sauberen ESP32-Start sicherstellen. Bei unlesbarer Startausgabe einmal EN drücken.

Nicht wegen einzelner `?`, `x` oder unlesbarer Zeichen sofort den Funkcode ändern.

## 2. BOOT und EN nicht verwechseln

### BOOT

Die BOOT-Taste kann beim Flashen erforderlich sein, wenn PlatformIO beim Upload bei `Connecting...` stehen bleibt.

### EN

EN führt einen normalen Reset des ESP32 aus.

Für unsere seriellen Funktionstests war EN die wichtige Taste, um einen sauberen Testlauf zu erhalten.

## 3. Funkverkabelung nicht ständig erneut infrage stellen

Die Verdrahtung des Funkmoduls wurde mehrfach überprüft.

Beide Module konnten erkannt werden und ein Rohsignal konnte vom TX-Modul zum RX-Modul übertragen werden.

Nach erfolgreicher Prüfung sollte die Verkabelung als feste Grundlage behandelt werden.

Nur bei neuen widersprüchlichen Messungen sollte sie erneut untersucht werden.

## 4. Erste TX-Versuche

Mehrere frühe TX-Varianten erzeugten zwar Funkaktivität, wurden vom Originalcontroller aber nicht akzeptiert.

Das zeigte:

> Funkaktivität allein bedeutet noch keine korrekte Reproduktion des Originalsignals.

## 5. Polarität

Ein späterer Test mit invertierter Pulsform führte nicht zur Reaktion des Originalcontrollers.

Die erfolgreiche Variante verwendet die Polarität der Originalaufnahme direkt:

- `1` = HIGH ca. 1170 µs / LOW ca. 420 µs
- `0` = HIGH ca. 380 µs / LOW ca. 1210 µs

## 6. Zusätzlicher Abschlussimpuls

Die detaillierte Originalaufnahme zeigte nach den 24 Nutzbits einen zusätzlichen kurzen HIGH-Puls von ungefähr 395 µs.

Danach folgt die ungefähr 12.350 µs lange LOW-Pause.

Dieser Abschlussimpuls fehlte bei früheren TX-Versuchen.

Die erfolgreiche Reproduktion enthält ihn.

## 7. Wiederholungen

Die Originalfernbedienung sendet bei einem längeren Tastendruck wiederholte Telegramme.

Deshalb wurde die erfolgreiche TX-Implementierung auf mehrere identische Telegramme ausgelegt.

## 8. Wichtigste Arbeitsregel

Bei Reverse Engineering möglichst früh von Vermutungen zu Messungen wechseln.

Nicht:

> „Das ist bestimmt UART.“

Sondern:

> „Welche Flanken und Zeiten sind tatsächlich messbar?“

Erst nach der Messung soll entschieden werden, welche Struktur daraus abgeleitet werden kann.

## 9. Goldstand

Nach erfolgreicher Reproduktion aller vier Befehle wurde `src/main.cpp` als funktionierender Referenzstand betrachtet.

Dieser Stand sollte vor weiteren Umbauten per Git gesichert werden.

## 10. ESPHome erst nach erfolgreicher Funkreproduktion

Die Funkkommunikation wurde zunächst unabhängig von ESPHome in PlatformIO entwickelt.

Das war hilfreich, weil dadurch Funkanalyse und Web-/Automatisierungslogik getrennt voneinander untersucht werden konnten.

Die ESPHome-Integration erfolgt erst auf Basis des bestätigten Funk-Goldstands.
