#include "mtimer.h"

#include <avr/interrupt.h>
#include "pins.h"

uint8_t cmdBuf = CMD_NOCMD;

static volatile int16_t ledRedTimer = TIMER_OFF;

void mtimerInit()
{
    OUT(LED_RED);

    TIMSK |= (1<<TOIE0);
    TCCR0 = (0 << CS02) | (1<<CS01) | (1<<CS00);
    // 8000000 / 64 = 125000
}

ISR (TIMER0_OVF_vect)
{
    TCNT0 = (256 - 125); // 131..255 => 1ms

    uint8_t btnNow = BTN_NO;
    static uint8_t btnPrev = BTN_NO;
    static uint16_t btnCnt = 0;

    if ((PIN(BTN1) & BTN1_LINE) == 0) {
        btnNow |= BTN_1;
    }

    if (btnNow) {
        if (btnNow == btnPrev) {
            btnCnt++;
        } else {
            btnPrev = btnNow;
        }
    } else {
        if (btnCnt >= SHORT_PRESS) {
            // Handle button
            if (btnPrev == BTN_1) {
                cmdBuf = CMD_BTN1;
            }
        }
        btnCnt = 0;
    }


    if (ledRedTimer > 0) {
        ledRedTimer--;
        if (ledRedTimer == LED_RED_TIMEOUT / 2) {
            SET(LED_RED);
        }
    } else if (ledRedTimer == 0) {
        ledRedTimer = LED_RED_TIMEOUT;
        CLR(LED_RED);
    }
}

uint8_t getCmd()
{
    uint8_t ret = cmdBuf;

    cmdBuf = CMD_NOCMD;

    return ret;
}

void setLedRedTimer(int16_t value)
{
    ledRedTimer = value;
}

