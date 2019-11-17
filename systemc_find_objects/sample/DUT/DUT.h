/* ---------------------------------------------------------------------
* $name: DUT.h
*
* Copyright(c) 2019 FreeSourceC.com
* Link address http://freesourcec.com/
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
----------------------------------------------------------------------*/
#ifndef __DUT_H__
#define __DUT_H__

#include "systemc.h"

class DUT:
	public sc_module
{
public:
    
    sc_in<unsigned __int64> clock;
    sc_in<bool>             reset; //active high
    sc_out<unsigned int > output_port;
	DUT(sc_module_name name);
	~DUT();
private:
    void monitor_clock_method(void);
    void monitor_reset_method(void);
    void write_port_method(void);
    sc_event ev_write_port;
    bool is_zero_clock;
    bool is_reset;
};

#endif /* __DUT_H__ */
