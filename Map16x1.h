/*
 * Map16x1.h
 *
 *  Created on: 03.11.2011
 *      Author: bofh
 */

#ifndef MAP16X1_H_
#define MAP16X1_H_

#include "util.h"

class Map16x1 {
public:
	Map16x1();
	virtual ~Map16x1();

	uint8_t map (uint8_t idx);
	void loadFromEeprom (int address);
	void writeToEeprom (int address);

	uint8_t *data;
};

class Map16x1Double {
public:
	Map16x1Double();
	virtual ~Map16x1Double();

	uint8_t map (uint8_t idx);
	void loadFromEeprom (int address);
	void writeToEeprom (int address);

	double *data;
};

#endif /* MAP16X1_H_ */