/* ---------------------------------------------------------------------
* $name: UnitTest.cpp
*
* Copyright(c) 2019 FreeSourceC.com
* Link address http://freesourcec.com/
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
----------------------------------------------------------------------*/
#include "UnitTest.h"
#include "DUT.h"
#include "Peripheral.h"

DUT *obj_dut;
Peripheral * obj_peripheral;
sc_signal<sc_dt::uint64> clk_sig;
sc_signal<bool> rst_sig;
sc_signal<unsigned int> port_sig;


void peripheral_write( std::string token,std::string name, unsigned long long value);
void UnitTest_Init(void)
{
    obj_dut = new DUT("dut");
    obj_peripheral = new Peripheral("peripheral");

    //bind port
    obj_dut->clock(clk_sig);
    obj_peripheral->clock(clk_sig);

    obj_dut->reset(rst_sig);
    obj_peripheral->reset(rst_sig);

    obj_dut->output_port(port_sig);
    obj_peripheral->input_port(port_sig);
}

void UnitTest_DeInit(void)
{
    delete obj_dut;
    delete obj_peripheral;
}

TEST(OR_GATE_Check,check_out_port_init)
{


    for (unsigned int val = 10; val < 100000; val = val * 100) {
        peripheral_write("peripheral", "clock", val);
        sc_start(10, SC_PS);
        EXPECT_EQ(clk_sig.read(), val);
    }
    bool init_val = false;
    for (unsigned int i = 0; i < 4; i++) {
        obj_peripheral->set_output_port_api("reset", init_val);
        sc_start(10, SC_PS);
        EXPECT_EQ(rst_sig.read(), init_val);
        init_val = !init_val;
    }
    system("pause");
}

void peripheral_write(std::string token, std::string name, unsigned long long value) {
    Peripheral *obj;
    if (!(obj = dynamic_cast<Peripheral *>(sc_find_object(token.c_str())))) {

    }
    else {
        obj->set_output_port_api(name, value);
    }
}