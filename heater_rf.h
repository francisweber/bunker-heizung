#pragma once

#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>

// ============================================================
// BUNKER-HEIZUNG – 433 MHz Funksteuerung
// VEVOR Dieselheizung
//
// Reproduziertes Originalprotokoll:
// 24 Bit
// 1 = HIGH 1170 µs / LOW 420 µs
// 0 = HIGH  380 µs / LOW 1210 µs
// Abschlussimpuls = HIGH 395 µs
// Telegrammpause = LOW 12350 µs
// 8 Telegramme pro Befehl
// ============================================================

// ------------------------------------------------------------
// Funkmodul 1 – Pinbelegung
// ------------------------------------------------------------

static const int HEATER_RF_GDO0 = 4;
static const int HEATER_RF_CSN  = 5;
static const int HEATER_RF_SCK  = 18;
static const int HEATER_RF_MISO = 19;
static const int HEATER_RF_MOSI = 23;

// ------------------------------------------------------------
// Original-Codes
// ------------------------------------------------------------

static const char *HEATER_RF_PLUS =
    "110100001011000100000010";

static const char *HEATER_RF_MINUS =
    "110100001011000100000001";

static const char *HEATER_RF_ON =
    "110100001011000100001000";

static const char *HEATER_RF_OFF =
    "110100001011000100000100";

// ------------------------------------------------------------
// Gemessene Pulszeiten
// ------------------------------------------------------------

static const unsigned int HEATER_RF_ONE_HIGH  = 1170;
static const unsigned int HEATER_RF_ONE_LOW   = 420;

static const unsigned int HEATER_RF_ZERO_HIGH = 380;
static const unsigned int HEATER_RF_ZERO_LOW  = 1210;

static const unsigned int HEATER_RF_END_HIGH  = 395;

static const unsigned int HEATER_RF_PAUSE     = 12350;

static const int HEATER_RF_TELEGRAM_COUNT = 8;

// ------------------------------------------------------------
// Initialisierung
// ------------------------------------------------------------

inline bool heater_rf_init()
{
    ELECHOUSE_cc1101.setSpiPin(
        HEATER_RF_SCK,
        HEATER_RF_MISO,
        HEATER_RF_MOSI,
        HEATER_RF_CSN
    );

    ELECHOUSE_cc1101.Init();

    if (!ELECHOUSE_cc1101.getCC1101())
    {
        return false;
    }

    ELECHOUSE_cc1101.setMHZ(433.92);
    ELECHOUSE_cc1101.setModulation(2);
    ELECHOUSE_cc1101.setManchester(false);
    ELECHOUSE_cc1101.setCrc(false);
    ELECHOUSE_cc1101.setWhiteData(false);
    ELECHOUSE_cc1101.setCCMode(0);
    ELECHOUSE_cc1101.setPktFormat(3);
    ELECHOUSE_cc1101.setGDO0(HEATER_RF_GDO0);

    pinMode(HEATER_RF_GDO0, OUTPUT);
    digitalWrite(HEATER_RF_GDO0, LOW);

    ELECHOUSE_cc1101.SetTx();

    return true;
}

// ------------------------------------------------------------
// Einzelnes Bit senden
// ------------------------------------------------------------

inline void heater_rf_send_bit(char bit)
{
    if (bit == '1')
    {
        digitalWrite(HEATER_RF_GDO0, HIGH);
        delayMicroseconds(HEATER_RF_ONE_HIGH);

        digitalWrite(HEATER_RF_GDO0, LOW);
        delayMicroseconds(HEATER_RF_ONE_LOW);
    }
    else
    {
        digitalWrite(HEATER_RF_GDO0, HIGH);
        delayMicroseconds(HEATER_RF_ZERO_HIGH);

        digitalWrite(HEATER_RF_GDO0, LOW);
        delayMicroseconds(HEATER_RF_ZERO_LOW);
    }
}

// ------------------------------------------------------------
// Ein vollständiges Telegramm senden
// ------------------------------------------------------------

inline void heater_rf_send_telegram(const char *code)
{
    // 24 Datenbits
    for (int i = 0; i < 24; i++)
    {
        heater_rf_send_bit(code[i]);
    }

    // Abschlussimpuls
    digitalWrite(HEATER_RF_GDO0, HIGH);
    delayMicroseconds(HEATER_RF_END_HIGH);

    digitalWrite(HEATER_RF_GDO0, LOW);

    // Pause bis zum nächsten Telegramm
    delayMicroseconds(HEATER_RF_PAUSE);
}

// ------------------------------------------------------------
// Befehl senden
// ------------------------------------------------------------

inline void heater_rf_send(const char *code)
{
    for (int i = 0; i < HEATER_RF_TELEGRAM_COUNT; i++)
    {
        heater_rf_send_telegram(code);
    }

    digitalWrite(HEATER_RF_GDO0, LOW);
}

// ------------------------------------------------------------
// Komfortfunktionen
// ------------------------------------------------------------

inline void heater_rf_on()
{
    heater_rf_send(HEATER_RF_ON);
}

inline void heater_rf_off()
{
    heater_rf_send(HEATER_RF_OFF);
}

inline void heater_rf_plus()
{
    heater_rf_send(HEATER_RF_PLUS);
}

inline void heater_rf_minus()
{
    heater_rf_send(HEATER_RF_MINUS);
}