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


#ifndef RDOFSMPR_ST_H
#define RDOFSMPR_ST_H

#include <register.h>


class RDOFSMPR_ST : public Register
{
public:
  RDOFSMPR_ST(Register::Value value) : fBits(value) {;}
  RDOFSMPR_ST(const RDOFSMPR_ST& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~RDOFSMPR_ST() {;}

  const RDOFSMPR_ST& operator= (const RDOFSMPR_ST& other) {fBits = other.fBits; return* this;}
  bool operator== (const RDOFSMPR_ST& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}

  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}
  const std::bitset<15>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {fBits = value;}
  void SetBits(const std::bitset<15>& bits) {fBits = bits;}

  // RDOFSMPR_ST specific parameters
  static const Register::Access Access = Register::R;
  static const Register::Address Address = 0x512d;
  static const Register::Type Type = Register::RCU;

  // RDOFSMPR_ST specific members:
  // TODO: implement RDOFSMPR_ST specific members

private:
  std::bitset<15> fBits;
};

#endif // RDOFSMPR_ST_H
