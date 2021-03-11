/* 
 * File:   ADXL345.h
 * Author: Kenneth Aldana
 *
 * Created on march 10 
 */

#ifndef ADXL345_H
#define	ADXL345_H

#include "I2C.h"

void ADXL345_Write(int add, int data);
int ADXL345_Read(int add);
void ADXL345_Init();

#endif	/* ADXL345_H */

