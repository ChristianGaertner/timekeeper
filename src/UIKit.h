//
// Created by Christian Gärtner on 15.05.16.
//

#ifndef TIMEKEEPING_UIKIT_H
#define TIMEKEEPING_UIKIT_H


#include "Adafruit_ST7735.h"
#include "Adafruit_GFX.h"
#include "TimeKeeper.h"

class UIKit {
public:
    UIKit(Adafruit_ST7735 tft, TimeKeeper * timeKeeper, const char * versionString)
            : tft(tft), timerKeeper(timeKeeper), versionString(versionString) {};

    void init() { tft.initR(INITR_BLACKTAB); }

    void clear() { tft.fillScreen(ST7735_BLACK); }

    void renderScreen();

    void renderSplashScreen();

private:
    Adafruit_ST7735 tft;
    TimeKeeper * timerKeeper;
    const char * versionString;

    void renderTime(unsigned long elapsed, uint16_t color, uint8_t size);
};


#endif //TIMEKEEPING_UIKIT_H
