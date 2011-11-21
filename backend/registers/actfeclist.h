/*
    Library for controlling and configuring the electronics for
    the PHOS detector at the ALICE Experiment

    Copyright (C) 2011  Oystein Djuvsland <oystein.djuvsland@gmail.com>,
                        Henrik Qvigstad <henrik.qvigstad@cern.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef ACTFECLIST_H
#define ACTFECLIST_H

#include "register.h"
#include <bitset>

class ACTFECLIST : public Register
{
public:
    ACTFECLIST(Register::Value value) : _bits(value) {;}
    virtual ~ACTFECLIST() {;}
  
    // Register members:
    Register::Access GetAccess() const {return Access;}
    Register::Address GetAddress() const {return Address;}
    Register::Type GetType() const {return Type;}
    Register::Value GetValue() const {return _bits.to_ulong();}
    void SetValue(Register::Value value) {_bits = value;}
    
    // ACTFECLIST specific parameters
    static const Register::Access Access = Register::RW;
    static const Register::Address Address = 0x5100;
    static const Register::Type Type = Register::RCU;
    
    // ACTFECLIST specific members:
    bool IsFECActive(int branch, int index);
    bool SetFECActive(int branch, int index, bool value = true);
    
private:
  std::bitset<32> _bits;
};

#endif // ACTFECLIST_H
