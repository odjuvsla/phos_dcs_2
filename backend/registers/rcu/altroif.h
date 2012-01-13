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


#ifndef ALTROIF_H
#define ALTROIF_H

#include <register.h>
#include <bitset>

class ALTROIF : public Register
{
public:
  ALTROIF(Register::Value value = 0x0) : fBits(value) {;}
  ALTROIF(const ALTROIF& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~ALTROIF() {;}

  const ALTROIF& operator= (const ALTROIF& other) {        fBits = other.fBits; return *this;}
  bool operator== (const ALTROIF& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}

  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}
  const std::bitset<18>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {        fBits = value;}
  void SetBits(const std::bitset<18>& bits) {        fBits = bits;}

  // ALTROIF specific parameters
  static const Register::Access Access = Register::RW;
  static const Register::Address Address = 0x5101;
  static const Register::Type Type = Register::RCU;


  // ALTROIF specific members:
  unsigned long GetCSTBDelay() const; // CSTB programmable Delay
  void SetCSTBDelay(const std::bitset< 2 >& value );

  unsigned long GetIECS() const; // Instruction Error Check Selection
  void SetIECS(const std::bitset<2>& value);

  unsigned long GetSCDR() const; // Sampeling Clock Dividing Ratio
  void SetSCDR(const std::bitset<4>& value); // in practice 2 bits

  unsigned long GetNSamples() const;
  void SetNSamples(const std::bitset<10>& value);


private:
  std::bitset<18> fBits;
};

#endif // ALTROIF_H
