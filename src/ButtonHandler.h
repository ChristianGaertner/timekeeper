#ifndef TIMEKEEPING_BUTTONHANDLER_H
#define TIMEKEEPING_BUTTONHANDLER_H

#include "Arduino.h"

#define NUM_BUTTONS 7

const int START_BUTTON = 2;

const int SB_1 = 3;
const int SB_2 = 4;

const int LANE_1 = 6;
const int LANE_2 = 7;
const int LANE_3 = 8;
const int LANE_4 = 9;

class ButtonHandler {

public:
    ButtonHandler(int activeOn = HIGH);
    bool startButton() {
        return debounce(0, START_BUTTON);
    }
    bool softButton1() {
        return debounce(1, SB_1);
    }

    bool softButton2() {
        return debounce(2, SB_2);
    }

    bool lane1() {
        return debounce(3, LANE_1);
    }

    bool lane2() {
        return debounce(4, LANE_2);
    }

    bool lane3() {
        return debounce(5, LANE_3);
    }

    boolean lane4() {
        return debounce(6, LANE_4);
    }

    void initPinMode(void (*pinMode)(uint8_t, uint8_t));
private:
    int activeOn;
    boolean debounce(int arrayKey, uint8_t pin);
    int last[NUM_BUTTONS];
};


#endif //TIMEKEEPING_BUTTONHANDLER_H
