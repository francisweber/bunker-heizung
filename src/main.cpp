#include <Arduino.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>

// ============================================================
// BUNKER-HEIZUNG – Funkmodul 1
// PLUS / MINUS / ON / OFF TX
// ============================================================

// Funkmodul 1
static const int PIN_GDO0 = 4;
static const int PIN_CSN  = 5;
static const int PIN_SCK  = 18;
static const int PIN_MISO = 19;
static const int PIN_MOSI = 23;

// ------------------------------------------------------------
// Original-Codes
// ------------------------------------------------------------

const char *PLUS_CODE =
    "110100001011000100000010";

const char *MINUS_CODE =
    "110100001011000100000001";

const char *ON_CODE =
    "110100001011000100001000";

const char *OFF_CODE =
    "110100001011000100000100";

// ------------------------------------------------------------
// Original gemessene Pulszeiten
// ------------------------------------------------------------

const unsigned int ONE_HIGH  = 1170;
const unsigned int ONE_LOW   = 420;

const unsigned int ZERO_HIGH = 380;
const unsigned int ZERO_LOW  = 1210;

// Abschluss-Puls
const unsigned int END_HIGH = 395;

// Pause zwischen Telegrammen
const unsigned int TELEGRAM_PAUSE = 12350;

// Wiederholungen
const int TELEGRAM_COUNT = 8;


// ------------------------------------------------------------
// Ein Bit senden
// ------------------------------------------------------------

void sendBit(char bit)
{
    if (bit == '1')
    {
        digitalWrite(PIN_GDO0, HIGH);
        delayMicroseconds(ONE_HIGH);

        digitalWrite(PIN_GDO0, LOW);
        delayMicroseconds(ONE_LOW);
    }
    else
    {
        digitalWrite(PIN_GDO0, HIGH);
        delayMicroseconds(ZERO_HIGH);

        digitalWrite(PIN_GDO0, LOW);
        delayMicroseconds(ZERO_LOW);
    }
}


// ------------------------------------------------------------
// Ein komplettes Telegramm senden
// ------------------------------------------------------------

void sendTelegram(const char *code)
{
    for (int i = 0; i < 24; i++)
    {
        sendBit(code[i]);
    }

    // zusätzlicher kurzer HIGH-Puls
    digitalWrite(PIN_GDO0, HIGH);
    delayMicroseconds(END_HIGH);

    // Pause bis zum nächsten Telegramm
    digitalWrite(PIN_GDO0, LOW);
    delayMicroseconds(TELEGRAM_PAUSE);
}


// ------------------------------------------------------------
// Befehl mehrfach senden
// ------------------------------------------------------------

void sendCommand(const char *name, const char *code)
{
    Serial.println();
    Serial.println("========================================");
    Serial.print("SENDE: ");
    Serial.println(name);
    Serial.println("========================================");

    Serial.print("Code: ");
    Serial.println(code);

    for (int i = 0; i < TELEGRAM_COUNT; i++)
    {
        Serial.print("Telegramm ");
        Serial.print(i + 1);
        Serial.print("/");
        Serial.println(TELEGRAM_COUNT);

        sendTelegram(code);
    }

    digitalWrite(PIN_GDO0, LOW);

    Serial.println();
    Serial.print(">>> ");
    Serial.print(name);
    Serial.println(" FERTIG <<<");
    Serial.println();
}


// ------------------------------------------------------------
// Setup
// ------------------------------------------------------------

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("========================================");
    Serial.println("BUNKER-HEIZUNG");
    Serial.println("FUNKMODUL 1");
    Serial.println("PLUS / MINUS / ON / OFF");
    Serial.println("========================================");

    Serial.println();
    Serial.println("Initialisiere Funkmodul...");

    ELECHOUSE_cc1101.setSpiPin(
        PIN_SCK,
        PIN_MISO,
        PIN_MOSI,
        PIN_CSN
    );

    ELECHOUSE_cc1101.Init();

    if (ELECHOUSE_cc1101.getCC1101())
    {
        Serial.println("Funkmodul 1: ERKANNT");
    }
    else
    {
        Serial.println("Funkmodul 1: FEHLER!");
        return;
    }

    // Funkparameter
    ELECHOUSE_cc1101.setMHZ(433.92);
    ELECHOUSE_cc1101.setModulation(2);
    ELECHOUSE_cc1101.setManchester(false);
    ELECHOUSE_cc1101.setCrc(false);
    ELECHOUSE_cc1101.setWhiteData(false);
    ELECHOUSE_cc1101.setCCMode(0);
    ELECHOUSE_cc1101.setPktFormat(3);
    ELECHOUSE_cc1101.setGDO0(PIN_GDO0);

    pinMode(PIN_GDO0, OUTPUT);
    digitalWrite(PIN_GDO0, LOW);

    ELECHOUSE_cc1101.SetTx();

    delay(100);

    Serial.println();
    Serial.println("Funkmodul: TX bereit.");

    Serial.println();
    Serial.println("Tasten:");
    Serial.println("4 = PLUS");
    Serial.println("5 = MINUS");
    Serial.println("6 = ON");
    Serial.println("7 = OFF");

    Serial.println();
    Serial.println("BEREIT.");
}


// ------------------------------------------------------------
// Loop
// ------------------------------------------------------------

void loop()
{
    if (Serial.available())
    {
        char c = Serial.read();

        if (c == '4')
        {
            sendCommand("PLUS", PLUS_CODE);
        }
        else if (c == '5')
        {
            sendCommand("MINUS", MINUS_CODE);
        }
        else if (c == '6')
        {
            sendCommand("ON", ON_CODE);
        }
        else if (c == '7')
        {
            sendCommand("OFF", OFF_CODE);
        }
    }
}