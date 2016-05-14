#include "Arduino.h"
#include "ButtonHandler.h"
#include "TimeKeeper.h"


#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include "SPI.h" // needed by Adafruit_ST7735.h

#define SOFTWARE_VERSION "v0.0.1-SNAPSHOT"


#define TFT_CS     10
#define TFT_RST    0
#define TFT_DC     14

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

ButtonHandler handler;
TimeKeeper timer;

void setup()
{
    Serial.begin(9600);
    Serial.println("TimeKeeping");
    Serial.println("(c) 2016");
    Serial.println("(c) Christian Gaertner - cpgaertner.de");
    Serial.println(SOFTWARE_VERSION);


    Serial.println("init screen");
    tft.initR(INITR_BLACKTAB);
    tft.fillScreen(ST7735_BLACK);

    tft.setCursor(25, 20);
    tft.setTextWrap(false);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.println("KGMSI Westwand");
    tft.setCursor(32, tft.getCursorY());
    tft.println("TimeKeeping");
    tft.println();

    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(40, tft.getCursorY());
    tft.println("(c) 2016");

    tft.println();
    tft.println();
    tft.setCursor(15, tft.getCursorY());
    tft.println("Christian Gaertner");
    tft.setCursor(0, tft.getCursorY());
    tft.println("Software Technologies");
    tft.setCursor(25, tft.getCursorY());
    tft.println("cpgaertner.de");

    tft.setCursor(0, 150);
    tft.println(SOFTWARE_VERSION);

    Serial.println("init buttons");
    handler.initPinMode(pinMode);
}

void loop()
{

    if (!timer.running()) {
        if (handler.startButton())
        {
            while(handler.startButton()); // block until button has been released.
            timer.start();
            Serial.println("==Started==");
        }
        return;
    }

    if (handler.lane1() && timer.triggerLane(0))
    {
        Serial.println("LANE 1: stopped");
    }
    if (handler.lane2() && timer.triggerLane(1))
    {
        Serial.println("LANE 2: stopped");
    }
    if (handler.lane3() && timer.triggerLane(2))
    {
        Serial.println("LANE 3: stopped");
    }
    if (handler.lane4() && timer.triggerLane(3))
    {
        Serial.println("LANE 4: stopped");
    }

    if (handler.startButton() || timer.allFinished())
    {
        unsigned long results[4];
        timer.stop();

        while(handler.startButton()); // block until button has been released.

        timer.results(results);

        Serial.println("++STOPPED++");
        for (int i = 0; i < NUM_LANES; ++i) {
            Serial.print("LANE ");
            Serial.print(String(i + 1, DEC));
            Serial.print(": ");
            Serial.println(String(results[i], DEC));
        }
    }
}