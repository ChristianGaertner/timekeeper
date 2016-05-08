//
// Created by Christian Gärtner on 08.05.16.
//

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
    boolean startButton() {
        return debounce(0, START_BUTTON);
    }
    boolean softButton1() {
        return debounce(0, SB_1);
    }

    boolean softButton2() {
        return debounce(0, SB_2);
    }

    boolean lane1() {
        return debounce(0, LANE_1);
    }

    boolean lane2() {
        return debounce(0, LANE_2);
    }

    boolean lane3() {
        return debounce(0, LANE_3);
    }

    boolean lane4() {
        return debounce(0, LANE_4);
    }

    void initPinMode(void (*pinMode)(uint8_t, uint8_t));
private:
    boolean debounce(int arrayKey, uint8_t pin);
    int last[NUM_BUTTONS];
};


#endif //TIMEKEEPING_BUTTONHANDLER_H
