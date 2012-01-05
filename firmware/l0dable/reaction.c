#include <sysinit.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "basic/basic.h"
#include "basic/config.h"
#include "basic/random.h"

#include "lcd/render.h"
#include "lcd/print.h"

#include "usetable.h"
/** reaction.c
 *  First l0dable for my r0ket
 *  Improvement is welcome
 *
 * AUTHOR: hubba
*/
void ram(void)
{
    char x = gpioGetValue(RB_LED1);
    int rand_wait = 0;
    int react_time=0;
    int start_time = 0;
    int end_time = 0;

    gpioSetValue (RB_LED1,0);           //upperleft LED off
    lcdClear();
    lcdPrintln("Hello");
    lcdPrintln(GLOBAL(nickname));
    lcdPrintln("ReACTION");
    lcdRefresh();
    delayms(500);
    while(1)
    {
        react_time = 0;
        lcdPrintln("Press ENTER if ");
        lcdPrintln("LED is on!");
        lcdRefresh();
        rand_wait = getRandom();
        rand_wait = rand_wait%50;
        rand_wait = 40 + rand_wait*4;        // Minimum pause time is 400ms
        for(int i =0; i<=rand_wait; i++)     //directly calling delayms(rand_wait) didn't work
        {
            delayms(10);
        }
        gpioSetValue (RB_LED1, 1);          //upperleft LED ON
        getInputWaitRelease();
        start_time = getTimer()*(SYSTICKSPEED);
        while (getInputWait() != BTN_ENTER);    //wait for user input
        {

        }
        end_time =  getTimer()*(SYSTICKSPEED);
        react_time = end_time - start_time;     //measure  used time
        lcdClear();
        lcdPrint("Needed ");
        lcdPrintInt(react_time);
        lcdPrintln(" ms");
        lcdPrintln("DOWN: Exit");
        lcdPrintln("0ther: New game");
        lcdRefresh();
        gpioSetValue (RB_LED1,0);           //upperleft LED off

        getInputWaitRelease();
        if(getInputWait() ==  BTN_DOWN)     //Check for Exit/new game
        {
            gpioSetValue (RB_LED1, x);      //upperleft LED as before l0dable executed
            return;
        }
    }
    /* NEVER LAND HERE */
    lcdPrintln("Flow-Error");
    lcdRefresh();
    return;
};
