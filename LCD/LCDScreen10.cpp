/*
 * LCDScreen10.cpp
 *
 *  Created on: 02.04.2010
 *      Author: bofh
 */

#include "LCDScreen10.h"

#include "WProgram.h"
#include "MultidisplayDefines.h"
#include "MultidisplayController.h"
#include "LCDController.h"
#include "BoostController.h"

LCDScreen10::LCDScreen10() {
	flags.f.doCal=1;
	flags.f.doTypK = 1;
//	flags.f.serial = SERIALOUT_ENABLED;
	flags.f.serial = SERIALOUT_TUNERPRO_ADX;
	flags.f.refreshRate = 10;
	flags.f.loadBar = 0;
	flags.f.loadDot = 0;
	flags.f.loadVBar = 0;
	flags.f.loadBigFont2 = 0;
	flags.f.loadBigFont4 = 1;
}

LCDScreen10::~LCDScreen10() {
}


void LCDScreen10::customInit() {
    lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[0], PSTR("THR:"));
    lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[0]+10, PSTR("CT:"));
    lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[1], PSTR("LAMBDA:"));
    lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[2], PSTR("RPM:"));
    lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[2]+10, PSTR("BST:"));
//    lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[3], PSTR("N75:"));
}


void LCDScreen10::customDraw() {

    lcdp->commandWrite(0x80 + 5);
    lcdController.printInt(0x80 + 5, data.calThrottle, 3 );
    lcdController.printFloat2DP(0x80 + 14, data.calCaseTemp);
    lcdController.printFloat2DP(lcdController.ystart[1] + 8, data.calLambdaF);
//    lcdController.printInt (lcdController.ystart[1]+ 14, data.anaIn[LAMBDAPIN], 4);
    lcdController.printInt(lcdController.ystart[2] + 5, data.calRPM, 4);
    lcdController.printFloat2DP(lcdController.ystart[2] + 14, data.calBoost);

//    lcdController.printInt(lcdController.ystart[3], data.anaIn[BOOSTPIN]);
//    lcdController.printInt(lcdController.ystart[3]+10, data.anaIn[BOOST2PIN]);

//#ifdef BOOSTPID
//    if ( boostController.boostPid->GetMode() == MANUAL )
//    	lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[3]+5, PSTR("M"));
//    else {
//    	lcdp->lcdCommandWriteAndPrintIn_P (lcdController.ystart[3]+5, PSTR("A"));
//      lcdController.printFloat2DP(lcdController.ystart[3] + 7, boostController.boostSetPoint);
//    }
//#endif
#ifdef BOOSTN75
    lcdController.printInt(lcdController.ystart[3], digitalRead(NORDSCHLEIFENPIN), 1);
//    lcdController.printInt(lcdController.ystart[3] + 1, digitalRead(FREEANALOG2), 1);
    lcdController.printFloat2DP(lcdController.ystart[3] + 5, boostController.n75_manual_normal);
    lcdController.printFloat2DP(lcdController.ystart[3] + 9, boostController.n75_manual_race);
    lcdController.printFloat2DP(lcdController.ystart[3] + 13, boostController.boostOutput);
#endif


//    lcdController.printInt(lcdController.ystart[3] + 13, digitalRead(FREEANALOG2), 4);

//	lcdController.printBigNum ( (double)data.calBoost, LCD_WIDTH-9, 9, 0, LCD_BIGFONT_4);
//	lcdp->commandWrite(0x80);
//	lcdController.printFloat2DP(-1.56789);

//	lcdController.printBigNum ( -1.594, LCD_WIDTH-0, 0, 0, LCD_BIGFONT_4);
//	lcdController.printBigNum ( -1.55432, LCD_WIDTH-0, 0, 0, LCD_BIGFONT_2);
//	lcdController.printBigNum ( -1.554, LCD_WIDTH-10, 5, 0, LCD_BIGFONT_2);
//	lcdController.printBigNum ( 0.864, LCD_WIDTH-10, 5, 2, LCD_BIGFONT_2);

//	lcdController.printOneNumber2 (0, 0, 0);
//	lcdController.printOneNumber2 (1, 3, 0);
//	lcdController.printOneNumber2 (2, 6, 0);
//	lcdController.printOneNumber2 (3, 9, 0);
//	lcdController.printOneNumber2 (4, 12, 0);
//	lcdController.printOneNumber2 (5, 15, 0);
//	lcdController.printOneNumber2 (6, 18, 0);

//	lcdController.printOneNumber4 (0, 0, 0);
//	lcdController.printOneNumber4 (1, 3, 0);
//	lcdController.printOneNumber4 (2, 6, 0);
//	lcdController.printOneNumber4 (3, 9, 0);
//	lcdController.printOneNumber4 (4, 12, 0);
//	lcdController.printOneNumber4 (5, 15, 0);
//	lcdController.printOneNumber4 (6, 18, 0);
 }
