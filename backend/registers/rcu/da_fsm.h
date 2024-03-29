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


#ifndef DA_FSM_H
#define DA_FSM_H

#include <register.h>


class DA_FSM : public Register
{
public:
  DA_FSM(Register::Value value = 0x0) : fBits(value) {;}
  DA_FSM(const DA_FSM& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~DA_FSM() {;}

  const DA_FSM& operator= (const DA_FSM& other) {fBits = other.fBits; return* this;}
  bool operator== (const DA_FSM& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}

  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}
  const std::bitset<30>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {fBits = value;}
  void SetBits(const std::bitset<30>& bits) {fBits = bits;}

  // DA_FSM specific parameters
  static const Register::Access Access = Register::R;
  static const Register::Address Address = 0x5130;
  static const Register::Type Type = Register::RCU;

  // DA_FSM specific members:
  // TODO: implement DA_FSM specific members

private:
  std::bitset<30> fBits;
};

#endif // DA_FSM_H
