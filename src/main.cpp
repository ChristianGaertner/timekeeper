#include "Arduino.h"
#include "ButtonHandler.h"
#include "TimeKeeper.h"

ButtonHandler handler;
TimeKeeper timer;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    handler.initPinMode(pinMode);

    Serial.begin(9600);
    Serial.println("booted");
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


    if (millis() % 500 < 50) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else if (millis() % 100 < 50) {
        digitalWrite(LED_BUILTIN, LOW);
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