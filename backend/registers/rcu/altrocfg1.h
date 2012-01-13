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


#ifndef ALTROCFG1_H
#define ALTROCFG1_H

#include <register.h>
#include <bitset>

// This register is copy of ALTRO configuration register. Parameters in this register are used to
// record in the RCU trailer word. Refer to ALTRO manual pages 36, 37.
class ALTROCFG1 : public Register
{
public:
  ALTROCFG1(Register::Value value = 0x0) : fBits(value) {;}
  ALTROCFG1(const ALTROCFG1& other) : fBits(other.fBits.to_ulong()) {;}
  virtual ~ALTROCFG1() {;}
  
  const ALTROCFG1& operator= (const ALTROCFG1& other) {fBits = other.fBits; return* this;}
  bool operator== (const ALTROCFG1& other) const {return fBits.to_ulong() == other.fBits.to_ulong();}
  
  // Register members:
  Register::Access GetAccess() const {return Access;}
  Register::Address GetAddress() const {return Address;}
  Register::Type GetType() const {return Type;}
  Register::Value GetValue() const {return fBits.to_ulong();}	
  const std::bitset<20>& GetBits() const {return fBits;}
  void SetValue(Register::Value value) {fBits = value;}
  void SetBits(const std::bitset<20>& bits) {fBits = bits;}
  
  // ALTROCFG1 specific parameters
  static const Register::Access Access = Register::RW;
  static const Register::Address Address = 0x5104;
  static const Register::Type Type = Register::RCU;
  
  // ALTROCFG1 specific members:
  unsigned long GetFBCM() const // First Baseline Correction Mode [3:0]
  { return Register::ReadValue<0,3>(fBits); }
  void SetFBCM(std::bitset<4> value)
  { Register::InsertValue<0>(fBits, value); }
  
  
  bool GetPolarity() const // Polarity. When set, the ADC data is inverted (1’s C) [4]
  { return fBits[4]; }
  void SetPolarity(bool value = true)
  { fBits[4] = value; }
  
  unsigned long GetNPreSampleE2dBC() const // Nr. Of pre-samples excluded from 2nd baseline corr [6:5]
  { return Register::ReadValue<5,6>(fBits); }
  void SetNPreSampleE2dBC(std::bitset<2> value)
  { Register::InsertValue<5>(fBits, value); }
  
  unsigned long GetNPostSampleE2dBC() const // Nr. Of post-samples excluded from 2nd baseline corr [10:7]
  { return Register::ReadValue<7,10>(fBits); }
  void SetNPostSampleE2dBC(std::bitset<4> value)
  { Register::InsertValue<7>(fBits, value); }
  
  bool GetSecoundBaselineCorrection() const // Enable second baseline correction [11]
  { return fBits[11]; }
  void SetSecoundBaselineCorrection(bool value = true)
  { fBits[11] = value; }
  
  unsigned long GetGlitchFilter() const // Glitch filter configuration for zero suppression [13:12] 
  { return Register::ReadValue<12,13>(fBits); }
  void SetGlitchFilter(std::bitset<2> value)
  { Register::InsertValue<12>(fBits, value); }
  
  unsigned long GetNPostSampleES() const // Nr. Of post-samples excluded from suppression [16:14]
  { return Register::ReadValue<14,16>(fBits); }
  void SetNPostSampleES(std::bitset<3> value)
  { Register::InsertValue<14>(fBits, value); }
  
  unsigned long GetNPreSampleES() const // Nr. Of pre-samples excluded from suppression [18:17]
  { return Register::ReadValue<17,18>(fBits); }
  void SetNPreSampleES(std::bitset<2> value)
  { Register::InsertValue<17>(fBits, value); }

  bool GetZeroSuppression() const // Enable Zero Suppression [19]
  { return fBits[19]; }
  void SetZeroSuppression(bool value = true)
  { fBits[19] = value ;}

  
private:
  std::bitset<20> fBits;

};

#endif // ALTROCFG1_H
