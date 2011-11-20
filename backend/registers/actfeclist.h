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
    ACTFECLIST(RegisterTraits::Value value) : _bits(value) {;}
    virtual ~ACTFECLIST() {;}
  
    RegisterTraits::Access GetAccess() const {return Access;}
    RegisterTraits::Address GetAddress() const {return Address;}
    RegisterTraits::Type GetType() const {return Type;}
    RegisterTraits::Value GetValue() const {return _bits.to_ulong();}
    void SetValue(RegisterTraits::Value value) {_bits = value;}
    
    
    static const RegisterTraits::Access Access = RegisterTraits::RW;
    static const RegisterTraits::Address Address = 0x5100;
    static const RegisterTraits::Type Type = RegisterTraits::RCU;
    
    // ACTFECLIST specifics:
    bool IsFECActive(int branch, int index);
    bool SetFECActive(int branch, int index, bool value = true);
    
private:
  std::bitset<32> _bits;
};

#endif // ACTFECLIST_H
