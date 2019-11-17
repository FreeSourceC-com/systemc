/* ---------------------------------------------------------------------
* $name: Peripheral.cpp
*
* Copyright(c) 2019 FreeSourceC.com
* Link address http://freesourcec.com/
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
----------------------------------------------------------------------*/
#include "Peripheral.h"


Peripheral::Peripheral(sc_module_name name) :
    sc_module(name)
    , clock("clock")
    , reset("reset")
    , input_port("input_port")
{
    SC_HAS_PROCESS(Peripheral);
    clock.initialize(0);
    reset.initialize(false);

    SC_METHOD(monitor_input_method);
    dont_initialize();
    sensitive << input_port;
}

Peripheral::~Peripheral() {
	
}

void Peripheral::monitor_input_method(void) {
    printf("[%10s]%s received %d from DUT\n", sc_time_stamp().to_string().c_str(), this->basename(), input_port.read());
}

template<typename porttype, typename datatype>
void Peripheral::writePort(sc_object *obj, porttype port, datatype value) {
    if (!(port = dynamic_cast<porttype> (obj))) {
        /*do nothing*/
    }
    else {
        port->write(value);
    }
}
void Peripheral::get_type(sc_object *obj, std::string &type_port, std::string &type_data) {
    type_port = obj->kind();

    std::string temp_1 = typeid(*obj).name();
    size_t first = temp_1.find('<');
    size_t second = temp_1.find('>');
    const char * temp_2 = temp_1.c_str();
    for (unsigned int i = first + 1; i < second; i++)type_data += temp_2[i];
}

void Peripheral::set_output_port_api(std::string name, unsigned long long value)
{
    std::string port_name = this->basename() + std::string(".") + name;
    sc_object *object = sc_find_object(port_name.c_str());

    if (!object) {
        printf("[%10s]Error (%s) port %s is not found.\n", sc_time_stamp().to_string().c_str(), this->name(),  name.c_str());
        exit(1);
    }
    else {
        std::string type_port("");
        std::string type_data("");
        get_type(object, type_port, type_data);
        if (type_port == "sc_out") {
            if (type_data == "bool") {
                bool temp_value = (bool)value;
                sc_out<bool> *port = 0;
                writePort(object, port, temp_value);
            }
            else if (type_data == "unsigned char") {
                unsigned char temp_value = (unsigned char)value;
                sc_out<unsigned char> *port = 0;
                writePort(object, port, temp_value);
            }
            else if (type_data == "unsigned int") {
                unsigned int temp_value = (unsigned int)value;
                sc_out<unsigned int> *port = 0;
                writePort(object, port, temp_value);
            }
            else if (type_data == "unsigned __int64") {
                unsigned __int64 temp_value = (unsigned __int64)value;
                sc_out<sc_dt::uint64> *port = 0;
                writePort(object, port, temp_value);
            }

        }
        else {
            printf("[%10s]Error (%s) It(%s) is not output port type .\n", sc_time_stamp().to_string().c_str(), this->name(),  name.c_str());
            exit(1);
        }
    }
}

