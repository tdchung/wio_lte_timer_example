#include <ublox_sara_r4.h>

#ifndef GNSS_PWR_PIN
#define GNSS_PWR_PIN  28 // PB12
#endif

HardwareTimer timer3(3);
HardwareTimer timer4(4);

void setup()
{
    // gnss configuration
    SerialGNSS.begin(SerialGNSS_BAUDRATE);
    pinMode(GNSS_PWR_PIN, OUTPUT);
    digitalWrite(GNSS_PWR_PIN, HIGH);

    // timer 3 and 4 with channel 1
    timer3.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
    timer4.setMode(TIMER_CH1, TIMER_OUTPUT_COMPARE);
    timer3.pause();
    timer4.pause();
    timer3.setPeriod(500000);
    timer3.attachInterrupt(TIMER_CH1, handler3);
    timer4.setPeriod(1000000);
    timer4.attachInterrupt(TIMER_CH1, handler4);
    timer3.refresh();
    timer4.refresh();
    timer3.resume();
    timer4.resume();
}

void loop()
{
}

void handler3(void)
{
    SerialUSB.println("Count 3: ");
    while(SerialGNSS.available())
    {
        SerialDebug.write(SerialGNSS.read());
    }
}

void handler4(void)
{
    SerialUSB.println("Count 4: ");
}