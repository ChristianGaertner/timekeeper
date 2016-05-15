//
// Created by Christian Gärtner on 11.05.16.
//

#include "TimeKeeper.h"

void TimeKeeper::start() {
    if (_running) {
        stop();
    }
    startTime = millis();
    _running = true;
    for (int i = 0; i < NUM_LANES; ++i) {
        finishTimes[i] = 0;
    }
}

void TimeKeeper::stop() {
    _running = false;
    for (int i = 0; i < NUM_LANES; ++i) {
        if (finishTimes[i] != 0) {
            finishTimes[i] = finishTimes[i] - startTime;
        }
    }
}

bool TimeKeeper::running() {
    return _running;
}

bool TimeKeeper::triggerLane(int lane) {
    if (lane >= NUM_LANES || !_running) {
        return false;
    }
    if (this->finishTimes[lane] != 0) {
        return false;
    }
    this->finishTimes[lane] = millis();
    return true;
}

int TimeKeeper::getFastestLane(unsigned long &value) {
    unsigned long smallest = __LONG_MAX__ * 2UL + 1UL; // ULONG_MAX
    int smallestIndex = 0;
    for (int i = 0; i < NUM_LANES; ++i) {
        if (finishTimes[i] < smallest) {
            smallest = finishTimes[i];
            smallestIndex = i;
        }
    }

    value = smallest;
    return smallestIndex;
}

bool TimeKeeper::results(unsigned long (&target)[NUM_LANES]) {
    if (_running) {
        return false;
    }

    for (int i = 0; i < NUM_LANES; ++i) {
        target[i] = finishTimes[i];
    }

    return true;
}

bool TimeKeeper::currentLaneTime(int lane, unsigned long &value) {
    if (!_running) {
        value = 0;
        return true;
    }

    const unsigned long current = finishTimes[lane];

    if (current == 0) {
        value = millis() - startTime;
        return false;
    }

    value = current - startTime;
    return true;
}

bool TimeKeeper::allFinished() {
    bool allFinished = true;
    for (int i = 0; i < NUM_LANES; ++i) {
        allFinished = allFinished && finishTimes[i] != 0;
    }
    return allFinished;
}

unsigned long TimeKeeper::elapsedTime() {
    if (!_running) {
        return 0;
    }

    return millis() - startTime;
}






