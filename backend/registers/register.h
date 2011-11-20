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


#ifndef REGISTER_H
#define REGISTER_H
#include <sys/types.h>

namespace RegisterTraits {
 enum Access { R=4, RW=6};
 enum Type { ALTRO, BC, RCU, TRU};
 typedef int16_t Address;
 typedef int32_t Value;
}

class Register
{
  public:
    virtual ~Register() {;}
    
    virtual RegisterTraits::Access GetAccess() const = 0;
    virtual RegisterTraits::Address GetAddress() const = 0;
    virtual RegisterTraits::Type GetType() const = 0;
    virtual RegisterTraits::Value GetValue() const = 0;
    virtual void SetValue(RegisterTraits::Value value) = 0;
        
};

#endif // REGISTER_H
