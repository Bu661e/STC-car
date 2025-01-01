#include "adc.H"

#ifndef __LIGHT_H__
#define __LIGHT_H__


extern unsigned char buffer_adc[2];

void calc_temp_and_light();

void init_light();

#endif