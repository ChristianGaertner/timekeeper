/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "ButtonHandler.h"

ButtonHandler handler;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    handler.initPinMode(pinMode);

    Serial.begin(9600);
    Serial.println("booted");
}

long startTime;
long lane1Time;
long lane2Time;
long lane3Time;
long lane4Time;


boolean running = false;

long startButtonDisabled = 0;

void loop()
{
    if (startButtonDisabled > 0)
    {
        delay(1);
        startButtonDisabled--;
    }

    if (!running) {
        startTime = millis();
        if (!startButtonDisabled && handler.startButton())
        {
            running = true;
            Serial.println("==Started==");
            startButtonDisabled = 2000;
        }
        return;
    }

    if (lane1Time == 0 && handler.lane1())
    {
        lane1Time = millis();
        Serial.println("LANE 1: stopped");
    }
    if (lane2Time == 0 && handler.lane2())
    {
        lane2Time = millis();
        Serial.println("LANE 2: stopped");
    }
    if (lane3Time == 0 && handler.lane3())
    {
        lane3Time = millis();
        Serial.println("LANE 3: stopped");
    }
    if (lane4Time == 0 && handler.lane4())
    {
        lane4Time = millis();
        Serial.println("LANE 4: stopped");
    }

    if (!startButtonDisabled && handler.startButton())
    {
        Serial.println("++STOPPED++");
        Serial.print("LANE 1: "); Serial.println(lane1Time - startTime);
        Serial.print("LANE 2: "); Serial.println(lane2Time - startTime);
        Serial.print("LANE 3: "); Serial.println(lane3Time - startTime);
        Serial.print("LANE 4: "); Serial.println(lane4Time - startTime);
        running = false;
        lane1Time = lane2Time = lane3Time = lane4Time = 0;
        startButtonDisabled = 2000;
    }
}