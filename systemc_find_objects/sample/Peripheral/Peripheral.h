/* ---------------------------------------------------------------------
* $name: Peripheral.h
*
* Copyright(c) 2019 FreeSourceC.com
* Link address http://freesourcec.com/
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
----------------------------------------------------------------------*/
#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__

#include "systemc.h"

class Peripheral:
	public sc_module
{
public:
    
    sc_out<unsigned __int64> clock;
    sc_out<bool>             reset; //active high
    sc_in<unsigned int > input_port;

	Peripheral(sc_module_name name);
	~Peripheral();


    void set_output_port_api(std::string name, unsigned long long value);
private:
    void monitor_input_method(void);
    void get_type(sc_object *obj, std::string &type_port, std::string &type_data);
    template<typename porttype, typename datatype>
    void writePort(sc_object *obj, porttype port, datatype value);
};

#endif /* __PERIPHERAL_H__ */
