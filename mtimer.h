#ifndef MTIMER_H
#define MTIMER_H

#include <inttypes.h>

#define LED_RED_TIMEOUT     400

#define BTN_NO              0
#define BTN_1               0b00000001
#define BTN_2               0b00000010
#define BTN_3               0b00000100

#define SHORT_PRESS         50

#define TIMER_OFF           -1

enum {
    CMD_NOCMD,

    CMD_BTN1,
    CMD_BTN2,
    CMD_BTN3,

};

void mtimerInit();
uint8_t getCmd();
void setLedRedTimer(int16_t value);

#endif // MTIMER_H
