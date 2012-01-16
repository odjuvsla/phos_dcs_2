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

/** Active Front End Card List [31:0]
 * 
 * Front end cards are set turned on and off by configuring this register.\n
 *  FEC – Branch A [15:0]\n
 *  FEC – Branch B [31:16]
 */
class ACTFECLIST : public Register
{
public:
  /** Initilise register as 0x0 */
  ACTFECLIST(Register::Value value = 0x0) : fBits(value) {;}
  /** Copies the value state of @a other */
  ACTFECLIST(const ACTFECLIST& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~ACTFECLIST() {;}

  const ACTFECLIST& operator= (const ACTFECLIST& other) {        fBits = other.fBits; return *this;}
  bool operator== (const ACTFECLIST& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}

  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}
  const std::bitset<32>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {        fBits = value;}
  void SetBits(const std::bitset<32>& bits) {        fBits = bits;}

  // ACTFECLIST specific parameters
  static const Register::Access Access = Register::RW;
  static const Register::Address Address = 0x5100;
  static const Register::Type Type = Register::RCU;

  // ACTFECLIST specific members:
  bool GetFECActive(size_t branch, size_t index) const;
  void SetFECActive(size_t branch, size_t index, bool value = true);

private:
  std::bitset<32> fBits;
};

#endif // ACTFECLIST_H
