#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println(" Bunker-Heizung Funkmodul-Test");
  Serial.println("================================");

  // Unsere SPI-Verdrahtung
  // SCK  = GPIO18
  // MISO = GPIO19
  // MOSI = GPIO23
  // CSN  = GPIO5
  ELECHOUSE_cc1101.setSpiPin(18, 19, 23, 5);

  // Funkmodul initialisieren
  ELECHOUSE_cc1101.Init();

  // Verbindung prüfen
  if (ELECHOUSE_cc1101.getCC1101()) {
    Serial.println("Funkmodul: VERBINDUNG OK");
  } else {
    Serial.println("Funkmodul: FEHLER");
    return;
  }

  // 433,92 MHz
  ELECHOUSE_cc1101.setMHZ(433.92);

  // Empfangsmodus
  ELECHOUSE_cc1101.setCCMode(1);

  // Zunächst ASK/OOK
  ELECHOUSE_cc1101.setModulation(2);

  // Breite Empfangsbandbreite
  ELECHOUSE_cc1101.setRxBW(812.50);

  // Empfang aktivieren
  ELECHOUSE_cc1101.SetRx();

  Serial.println("Frequenz: 433.92 MHz");
  Serial.println("Modulation: ASK/OOK");
  Serial.println("Empfang aktiviert.");
  Serial.println();
  Serial.println("Jetzt Tasten der Original-Fernbedienung druecken.");
  Serial.println();
}

void loop() {
  static unsigned long last_status = 0;

  // RSSI regelmäßig anzeigen
  if (millis() - last_status >= 1000) {
    last_status = millis();

    int rssi = ELECHOUSE_cc1101.getRssi();

    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");
  }

  // Prüfen, ob Daten im RX-FIFO angekommen sind
  if (ELECHOUSE_cc1101.CheckRxFifo(100)) {

    if (ELECHOUSE_cc1101.CheckCRC()) {

      byte buffer[61] = {0};

      int len = ELECHOUSE_cc1101.ReceiveData(buffer);

      Serial.println();
      Serial.println("=== FUNKDATEN EMPFANGEN ===");

      Serial.print("Laenge: ");
      Serial.println(len);

      Serial.print("RSSI: ");
      Serial.print(ELECHOUSE_cc1101.getRssi());
      Serial.println(" dBm");

      Serial.print("LQI: ");
      Serial.println(ELECHOUSE_cc1101.getLqi());

      Serial.print("HEX: ");

      for (int i = 0; i < len; i++) {
        if (buffer[i] < 0x10) {
          Serial.print("0");
        }

        Serial.print(buffer[i], HEX);
        Serial.print(" ");
      }

      Serial.println();
      Serial.println("===========================");
      Serial.println();
    }
  }
}