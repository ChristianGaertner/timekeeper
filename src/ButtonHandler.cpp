#include "ButtonHandler.h"

ButtonHandler::ButtonHandler(int activeOn) {
    this->activeOn = activeOn;
}

void ButtonHandler::initPinMode(void (*pinMode)(uint8_t, uint8_t)) {
    pinMode(START_BUTTON, INPUT);
    pinMode(SB_1, INPUT);
    pinMode(SB_2, INPUT);

    pinMode(LANE_1, INPUT);
    pinMode(LANE_2, INPUT);
    pinMode(LANE_3, INPUT);
    pinMode(LANE_4, INPUT);
}

bool ButtonHandler::debounce(int arrayKey, uint8_t pin) {
    int current = digitalRead(pin);

    if (last[arrayKey] != current)
    {
        delay(5);
        current = digitalRead(pin);
    }

    last[arrayKey] = current;

    return current == activeOn;
}


