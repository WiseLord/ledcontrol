#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "mtimer.h"
#include "pins.h"

enum {
    LED_OFF,
    LED_ON,
    LED_BLINK
};

int main(void)
{
    IN(BTN1);
    SET(BTN1);
    mtimerInit();
    sei();

    uint8_t cmd;
    uint8_t ledRed = LED_OFF;

    while (1) {
        cmd = getCmd();

        if (cmd == CMD_BTN1) {
            switch (ledRed) {
            case LED_OFF:
                ledRed = LED_ON;
                setLedRedTimer(TIMER_OFF);
                SET(LED_RED);
                break;
            case LED_ON:
                ledRed = LED_BLINK;
                setLedRedTimer(LED_RED_TIMEOUT);
                CLR(LED_RED);
                break;
            default:
                ledRed = LED_OFF;
                setLedRedTimer(TIMER_OFF);
                CLR(LED_RED);
                break;
            }
        }
    }

    return 0;
}
