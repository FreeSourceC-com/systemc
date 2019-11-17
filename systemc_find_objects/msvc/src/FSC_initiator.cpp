/* ---------------------------------------------------------------------
* $name: FSC_initiator.cpp
*
* Copyright(c) 2019 FreeSourceC.com
* Link address http://freesourcec.com/
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
----------------------------------------------------------------------*/

#include "FSC_initiator.h"
#include "UnitTest.h"

/* Global time resolution period */
double time_resolution_period;
/* Global time unit */
sc_time_unit time_unit;
void FCS_Init(void)
{
    time_resolution_period = 1;
    time_unit = SC_PS;
    sc_set_time_resolution(time_resolution_period, time_unit);

    UnitTest_Init();
    sc_start();
}

void FCS_DeInit(void)
{
    UnitTest_DeInit();
    sc_stop();
}