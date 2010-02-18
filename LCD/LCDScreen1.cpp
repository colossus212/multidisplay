/*
    Copyright 2009-10 Stephan Martin, Dominik Gummel

    This file is part of Multidisplay.

    Multidisplay is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Multidisplay is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Multidisplay.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/pgmspace.h>

#include "WProgram.h"
#include "MultidisplayDefines.h"
#include "MultidisplayController.h"
#include "LCDController.h"
#include "LCDScreen1.h"

LCDScreen1::LCDScreen1() {
	flags.f.doCal=1;
	flags.f.doTypK = 1;
	flags.f.serial = SERIALOUT_ENABLED;
	flags.f.refreshRate = 0;

}

LCDScreen1::~LCDScreen1() {
	// TODO Auto-generated destructor stub
}

void LCDScreen1::customInit() {
	//Line1
	lcdp->lcdCommandWriteAndPrintIn_P (0x80, PSTR("EGT:"));
	//Line=3
	lcdp->lcdCommandWriteAndPrintIn_P (0x94, PSTR("LD:        Max:"));
}

void LCDScreen1::customDraw() {
	int val = 0;
	int boostMapped = 0;

	//Calibrate it:
	val = mController.sdata.calLambda/10;
	boostMapped = map(mController.sdata.anaIn[BOOSTPIN], 0, 4096, 0, 200);
	boostMapped = constrain(boostMapped, 0, 200);

	lcdp->commandWrite(0x80+5);               //Line 1, position 5!

	char buf[12];
	//AGT1+AGT2/2 thats because off my 2 Probes
	lcdp->printIn( itoa((mController.sdata.calAgt[0]+mController.sdata.calAgt[1])/2, buf, 10));

	lcdp->print(32);                           //Print a " " at the end, to clear in case its needed

	lcdp->commandWrite(0x80+14);              //Line 3,

	lcdController.printfloat(mController.sdata.calCaseTemp,1);

	lcdp->print(223);                         //Print a " " at the end, to clear in case its needed
	lcdp->printIn( "C");                       //Print a " " at the end, to clear in case its needed

	lcdp->commandWrite(0x94+3);

	if(mController.sdata.calBoost < 0.0) {
		lcdp->printIn("-");
	} else {
		lcdp->printIn(" ");
	}
	lcdController.printfloat(abs(mController.sdata.calBoost),2);              //Shows current Boost

	//Check for new MaxLD, and then save the point where to make the square
	if(mController.sdata.calBoost > mController.sdata.maxLd) {
		mController.sdata.maxLd  = mController.sdata.calBoost;
		mController.sdata.maxLdt = boostMapped/10;
	}

	lcdp->commandWrite(0x94+16);
	lcdController.printfloat(mController.sdata.maxLd,2);                    //Max Boost

	//Lets draw the dot:
	lcdp->commandWrite(0xC0);              // Line 2
	for (int i=0; i <= 19; i++) {
		if(i==val) {
			lcdp->print(8);        //thats the Dot
		} else {
			if(i <= LAMBDALOWERLIMIT) {
				//from 0-4 a minus then nothing
				lcdp->print(6);
			} else {
				if(i <= LAMBDAUPPERLIMIT) {
					//from 5-15 ist nothing and then a plus
					lcdp->print(5);
				} else {
					lcdp->print(7);
				}
			}
		}
	}

	//Now lets make the Bar:
	lcdp->commandWrite(0xD4);                // Line 4
	lcdController.drawBar(20,boostMapped);

	//And draw a Dot at the max pos & 0 Pos

	lcdp->commandWrite(0xD4 + mController.sdata.maxLdt);                // Line 4
	lcdp->print(255);

	lcdp->commandWrite(0xD4 + mController.sdata.ldCalPoint);                // Line 4
	lcdp->print(255);

}

