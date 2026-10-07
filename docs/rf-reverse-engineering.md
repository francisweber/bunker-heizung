# 433-MHz-Funk – Reverse Engineering

## 1. Ziel

Ziel war es, die originale 433-MHz-Funkfernbedienung der untersuchten älteren Dieselheizungs-Steuerung mit einem ESP32 und einem CC1101-Funkmodul zu empfangen, zu analysieren und anschließend zu reproduzieren.

Das Ziel war nicht, ein allgemeines Protokoll für alle China-Dieselheizungen zu behaupten.

Die Ergebnisse gelten zunächst für das konkret untersuchte Fernbedienungs-/Controller-Paar.

## 2. Fernbedienung

Die untersuchte Fernbedienung ist eine separate 4-Tasten-Fernbedienung ohne Display:

- ON
- OFF
- PLUS
- MINUS

## 3. Empfang

Die ersten Tests wurden mit dem CC1101 als Empfänger durchgeführt.

Ermittelte bzw. verwendete Funkparameter:

- Frequenz: 433,92 MHz
- Modulation: ASK/OOK
- GDO0 als Rohdatenausgang

Die Signalstärke des Signals der Originalfernbedienung war gegenüber dem Leerlauf deutlich erkennbar.

## 4. Rohsignal

Die Flanken des GDO0-Signals wurden zeitlich aufgezeichnet.

Dabei zeigte sich ein wiederkehrendes Pulsformat.

### Bit 1

- HIGH: ungefähr 1170 µs
- LOW: ungefähr 420 µs

### Bit 0

- HIGH: ungefähr 380 µs
- LOW: ungefähr 1210 µs

Die Werte schwanken in den realen Aufnahmen geringfügig.

## 5. Telegrammlänge

Die Nutzdaten eines Telegramms bestehen aus 24 Bits.

Die vier Befehle wurden mehrfach aufgezeichnet und miteinander verglichen.

## 6. Ermittelte Befehle

### PLUS

```text
110100001011000100000010
```

### MINUS

```text
110100001011000100000001
```

### ON

```text
110100001011000100001000
```

### OFF

```text
110100001011000100000100
```

Die ersten 20 Bits sind bei den vier untersuchten Befehlen identisch. Die letzten vier Bits unterscheiden sich entsprechend dem Befehl.

Diese Struktur ist eine experimentelle Beobachtung für die untersuchte Fernbedienung.

## 7. Wiederholungsstruktur

Die Originalfernbedienung sendet bei längerem Tastendruck nicht nur ein einzelnes 24-Bit-Telegramm.

Zwischen den Telegrammen wurde eine Pause von ungefähr 12,35 ms gemessen.

Wichtig ist außerdem ein zusätzlicher kurzer HIGH-Puls direkt vor dieser Pause:

- zusätzlicher HIGH-Puls: ungefähr 395 µs
- anschließend LOW-Pause: ungefähr 12.350 µs

Damit ergibt sich vereinfacht:

```text
24 Bit
→ HIGH ca. 395 µs
→ LOW ca. 12.350 µs
→ nächstes Telegramm
```

Dieser zusätzliche Abschlussimpuls war für die erfolgreiche TX-Reproduktion relevant.

## 8. TX-Reproduktion

Die erste Generation der TX-Versuche reproduzierte zwar ähnliche Pulszeiten, reagierte aber nicht auf dem Original-Controller.

Bei der weiteren Analyse wurden insbesondere folgende Fehlerquellen ausgeschlossen bzw. korrigiert:

- falsche Polarität
- fehlender zusätzlicher Abschlussimpuls
- unzureichende Wiederholung der Telegramme

Die erfolgreiche Version verwendet die gemessene Originalpolarität und den zusätzlichen Abschlussimpuls.

## 9. Erfolgreicher Referenzstand

Der funktionierende Code befindet sich in:

```text
src/main.cpp
```

Er verwendet:

- 433,92 MHz
- ASK/OOK
- keine Manchester-Codierung
- keine CRC
- keine Whitening-Daten
- asynchronen Raw-Modus
- 24-Bit-Telegramme
- 395-µs-Abschlussimpuls
- 12.350-µs-Pause
- acht Wiederholungen

## 10. Funktionaler Nachweis

Der Original-LCD-Controller reagierte erfolgreich auf alle vier reproduzierten Befehle:

- PLUS
- MINUS
- ON
- OFF

Damit ist die Funkübertragung für die untersuchte Steuerung als funktionierend bestätigt.

## 11. Nicht bestätigte Annahmen

Nicht aus den Messungen ableiten sollte man:

- dass alle China-Dieselheizungen dasselbe Funkprotokoll verwenden
- dass andere Fernbedienungsgenerationen dieselbe Bitlänge besitzen
- dass die 24 Bit eine allgemeingültige Protokollstruktur darstellen
- dass externe Dokumentationen mit anderen Bitlängen direkt auf dieses System übertragbar sind

Die hier dokumentierten Werte stammen aus der Messung des konkreten Systems.
