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


#ifndef ALTROCFG2_H
#define ALTROCFG2_H

#include <register.h>
#include <bitset>


class ALTROCFG2 : public Register
{
public:
  ALTROCFG2(Register::Value value) : fBits(value) {;}
  ALTROCFG2(const ALTROCFG2& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~ALTROCFG2() {;}
  
  const ALTROCFG2& operator= (const ALTROCFG2& other) {fBits = other.fBits; return* this;}
  bool operator== (const ALTROCFG2& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}
  
  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}	
  const std::bitset<25>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {fBits = value;}
  void SetBits(const std::bitset<25>& bits) {fBits = bits;}
  
  // ALTROCFG2 specific parameters
  static const Register::Access Access = Register::RW;
  static const Register::Address Address = 0x5105;
  static const Register::Type Type = Register::RCU;
  
  // ALTROCFG2 specific members:
  //TODO: Implement in ALTROCFG2 specific members
  
private:
  std::bitset<25> fBits;
};

#endif // ALTROCFG2_H
