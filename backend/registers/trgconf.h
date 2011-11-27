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


#ifndef TRGCONF_H
#define TRGCONF_H

#include <register.h>
#include <bitset>


class TRGCONF : public Register
{
public:
  TRGCONF(Register::Value value) : fBits(value) {;}
  TRGCONF(const TRGCONF& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~TRGCONF() {;}
  
  const TRGCONF& operator= (const TRGCONF& other) {        fBits = other.fBits; return* this;}
  bool operator== (const TRGCONF& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}
  
  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}	
  const std::bitset<17>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) { fBits = value;}
  void SetBits(const std::bitset<17>& bits) { fBits = bits;}
  
  // TRGCONF specific parameters
  static const Register::Access Access = Register::RW;
  static const Register::Address Address = 0x5102;
  static const Register::Type Type = Register::RCU;
  
  // TRGCONF specific members:
  unsigned long GetTriggerSource() const;
  void SetTriggerSource(const std::bitset<3>& value);
  
  bool GetTriggerMode() const;
  void SetTriggerMode(bool value);
  
  unsigned long GetTriggerLatency() const;
  void SetTriggerLatency(const std::bitset<13>& value);
  
  
private:
  std::bitset<17> fBits;
  
};

#endif // TRGCONF_H
