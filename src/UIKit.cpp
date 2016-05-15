#include "UIKit.h"


void UIKit::renderScreen() {
    uint16_t color = (timerKeeper->running()) ? ST7735_GREEN : ST7735_RED;
    tft.setCursor(10, 20);
    this->renderTime(timerKeeper->elapsedTime(), color, 2);
}

void UIKit::renderTime(unsigned long elapsed, uint16_t color, uint8_t size) {
    long millis = elapsed % 1000;
    long seconds = elapsed / 1000;
    long minutes = seconds / 60;




    char buff[9];
    snprintf(buff, sizeof(buff), "%02li:%02li.%04li", minutes, seconds, millis);

    for (int i = 0; i < 8; ++i) {
        tft.drawChar(tft.getCursorX() + (i * 10 + 2), tft.getCursorY(), (unsigned char) buff[i], color, ST7735_BLACK, size);
    }
}

void UIKit::renderSplashScreen() {
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
    tft.println(versionString);
}





