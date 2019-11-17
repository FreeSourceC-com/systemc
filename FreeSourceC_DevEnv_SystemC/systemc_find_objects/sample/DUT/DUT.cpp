/* ---------------------------------------------------------------------
* $name: DUT.cpp
*
* Copyright(c) 2019 FreeSourceC.com
* Link address http://freesourcec.com/
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
----------------------------------------------------------------------*/
#include "DUT.h"


DUT::DUT(sc_module_name name) :
    sc_module(name)
    , clock("clock")
    , reset("reset")
    , output_port("output_port")
{
    is_zero_clock = true;
    is_reset = false;
    SC_HAS_PROCESS(DUT);
    output_port.initialize(0);

    SC_METHOD(monitor_clock_method);
    dont_initialize();
    sensitive << clock;

    SC_METHOD(monitor_reset_method);
    dont_initialize();
    sensitive << reset;

    SC_METHOD(write_port_method);
    dont_initialize();
    sensitive << ev_write_port;
}

DUT::~DUT() {
	
}

void DUT::monitor_clock_method(void)
{
    unsigned __int64 fre_val = clock.read();
    if (fre_val) {
        is_zero_clock = false;
        printf("[%10s]%s get frequency value is %llu Hz\n", sc_time_stamp().to_string().c_str(), this->basename(), fre_val);
    }
    else {
        is_zero_clock = true;
        printf("[%10s]frequency value is zero\n", sc_time_stamp().to_string().c_str());
    }
    ev_write_port.notify(SC_ZERO_TIME);

}

void DUT::monitor_reset_method(void)
{
    bool rst_val = reset.read();
    if (rst_val) {
        is_reset = true;
        printf("[%10s]resetting...\n", sc_time_stamp().to_string().c_str());
    }
    else {
        is_reset = false;
        printf("[%10s]de-assert reset\n",sc_time_stamp().to_string().c_str());
    }
}

void DUT::write_port_method(void)
{
    if (is_zero_clock || is_reset) {
        output_port.write(0);
    }
    else {
        printf("[%10s]%s change output port to 0xA\n", sc_time_stamp().to_string().c_str(), this->basename());
        output_port.write(0xA);
    }
}

