#include <sysinit.h>
#include <string.h>

#include "basic/basic.h"
#include "basic/config.h"

#include "lcd/render.h"
#include "lcd/print.h"

#include "usetable.h"

/**************************************************************************/

void ram(void) {
    int v,mv,c,p;
    do{
        lcdClear();
        lcdPrintln("Battery status:");
//        c=GetChrgStat();
	c=!gpioGetValue(RB_PWR_CHRG);
        mv=GetVoltage();
        v=mv/1000;
        p=(3500-mv)/-7*10; // seems to be 3500 mV [firmware/basic/voltage.c]

        lcdNl();
        if(c){
            lcdPrintln("CHARGING");
        }else if (mv<3550){
            lcdPrintln("  Charge NOW!");
        }else if (mv<3650){
            lcdPrintln("  Charge soon");
        }else if (mv<4000){
            lcdPrintln("      OK");
        }else if(mv<4200){
            lcdPrintln("     Good");
        }else{
            lcdPrintln("     Full");
        };

        lcdNl();
        lcdPrint("    ");
        lcdPrint(IntToStr(v,2,0));
        lcdPrint(".");
        lcdPrint(IntToStr(mv%1000,3,F_ZEROS));
        lcdPrintln("V");
        lcdPrint("    ");
	lcdPrint(IntToStr(p/10,3,0));
        lcdPrint(".");
        lcdPrint(IntToStr(p%10,1,F_ZEROS));
        lcdPrint("%");

        lcdNl();
        if(!c){
            lcdPrintln("(not charging)");
        };
        lcdRefresh();
    } while ((getInputWaitTimeout(242))==BTN_NONE);
}
