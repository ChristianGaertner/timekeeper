//
// Created by Christian Gärtner on 11.05.16.
//

#ifndef TIMEKEEPING_TIMEKEEPER_H
#define TIMEKEEPING_TIMEKEEPER_H

#include <USBAPI.h>

#define NUM_LANES 4

class TimeKeeper {
public:
    void start();

    bool running();

    void stop();

    bool triggerLane(int lane);

    int getFastestLane(unsigned long &value);

    bool results(unsigned long (&target)[NUM_LANES]);

    /**
     * currentLaneTime returns true, if the lane has already finished.
     *
     * The current time will always be written to value.
     */
    bool currentLaneTime(int lane, unsigned long &value);

    bool allFinished();

    unsigned long elapsedTime();

private:
    bool _running;
    unsigned long startTime;
    unsigned long finishTimes[NUM_LANES];


};


#endif //TIMEKEEPING_TIMEKEEPER_H
