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


#ifndef RDOMOD_H
#define RDOMOD_H

#include <register.h>
#include <bitset>

/** Readout Mode Configuration Register [3:0]
 */
class RDOMOD : public Register
{
public:
  RDOMOD(Register::Value value = 0x0) : fBits(value) {;}
  RDOMOD(const RDOMOD& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~RDOMOD() {;}
  
  const RDOMOD& operator= (const RDOMOD& other) {fBits = other.fBits; return* this;}
  bool operator== (const RDOMOD& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}
  
  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}	
  const std::bitset<6>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {fBits = value;}
  void SetBits(const std::bitset<6>& bits) {fBits = bits;}
  
  // RDOMOD specific parameters
  static const Register::Access Access = Register::RW;
  static const Register::Address Address = 0x5103;
  static const Register::Type Type = Register::RCU;
  
  // RDOMOD specific members:
  bool GetMCheckChannelAddressMismatch() const;
  void SetMCheckChannelAddressMismatch(bool value);

  bool GetMCheckBlockLengthMismatch() const;
  void SetMCheckBlockLengthMismatch(bool value);

  bool GetRDYEX() const; // Mask Read to Receive “RDYEX”
  void SetRDYEX(bool value);
  
  bool GetSparseReadoutMode() const;
  void SetSparseReadoutMode(bool value);
  
  bool GetSOEOIEIME() const; // SOE/EOE Instruction Memory Execution
  void SetSOEOIEIME(bool value);
  
  bool GetMultiEventBuffer() const;
  void SetMultiEventBuffer(bool value);


private:
  std::bitset<6> fBits;

};

#endif // RDOMOD_H
