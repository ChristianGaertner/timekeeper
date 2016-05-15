#include "Arduino.h"
#include "ButtonHandler.h"
#include "TimeKeeper.h"


#include "Adafruit_GFX.h"
#include "Adafruit_ST7735.h"
#include "SPI.h" // needed by Adafruit_ST7735.h
#include "UIKit.h"

#define SOFTWARE_VERSION "v0.0.1-SNAPSHOT"


#define TFT_CS     10
#define TFT_RST    0
#define TFT_DC     14

ButtonHandler handler;
TimeKeeper timer;
UIKit ui = UIKit(Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST), &timer, SOFTWARE_VERSION);

void setup()
{
    Serial.begin(9600);
    Serial.println("TimeKeeping");
    Serial.println("(c) 2016");
    Serial.println("(c) Christian Gaertner - cpgaertner.de");
    Serial.println(SOFTWARE_VERSION);


    Serial.println("=> init screen");
    ui.init();
    ui.renderSplashScreen();

    Serial.println("=> init buttons");
    handler.initPinMode(pinMode);
    delay(1000); // hold splash screen for one second
    Serial.println("=> Booted!");
    ui.clear();
}

void loop()
{
    ui.renderScreen();

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