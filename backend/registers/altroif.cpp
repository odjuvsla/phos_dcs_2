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


#include "altroif.h"
#include "assert.h"

int ALTROIF::GetCSTBDelay() const
{
/* CSTB programmable delay, [0,3].
 * This is the delay between the assertion of “cstb” and altro bus to avoid any possibility of glitch on hand shake
 * signals due to 40 bit ALTRO bus driving.
 */
  
  return Register::ReadValue<14,15>(fBits);
}

void ALTROIF::SetCSTBDelay(const std::bitset< 2 >& value)
{
/* CSTB programmable delay, [15:14]
 * This is the delay between the assertion of “cstb” and altro bus to avoid any possibility of glitch on hand shake
 * signals due to 40 bit ALTRO bus driving.
 */

  Register::InsertValue<14>(fBits, value);
}

int ALTROIF::GetIECS() const
{
/* Instruction error check selection ≡ [17:16]
 * “00”:= Contents of Instruction memory are not Checked
 * “01”:= Contents of Instruction memory will be checked against TPC instruction set.
 * “10”:= Contents of Instruction Memory will be checked against PHOS instruction set.
 * “11”:= Contents of Instruction Memory will be checked against FMD instruction set
 */
  return Register::ReadValue<16,17>(fBits);
}

void ALTROIF::SetIECS(const std::bitset<2>& value)
{
/* Instruction error check selection ≡ [17:16]
 * “00”:= Contents of Instruction memory are not Checked
 * “01”:= Contents of Instruction memory will be checked against TPC instruction set.
 * “10”:= Contents of Instruction Memory will be checked against PHOS instruction set.
 * “11”:= Contents of Instruction Memory will be checked against FMD instruction set
 */
  
  Register::InsertValue<16>(fBits, value);
}

int ALTROIF::GetSCDR() const
{
/* Sampling Clock Dividing Ratio: T sampling / TLHC ≡ [13:10]
 * “00”:= divide by 2; Period of sampling clock = 50nsec
 * “01”:= divide by 4; Period of sampling clock = 100nsec
 * “10”:= divide by 8; Period of sampling clock = 200nsec
 * “11”:= divide by 16; Period of sampling clock = 400nsec
 */
  return Register::ReadValue<10,13>(fBits);
};

void ALTROIF::SetSCDR(const std::bitset<4>& value)
{
/* Sampling Clock Dividing Ratio: T sampling / TLHC ≡ [13:10]
 * “00”:= divide by 2; Period of sampling clock = 50nsec
 * “01”:= divide by 4; Period of sampling clock = 100nsec
 * “10”:= divide by 8; Period of sampling clock = 200nsec
 * “11”:= divide by 16; Period of sampling clock = 400nsec
 */
  Register::InsertValue<10>(fBits, value);
}

int ALTROIF::GetNSamples() const
{
  // Nr. Samples / channel ≡ [9:0]
  return Register::ReadValue<0,9>(fBits);
}

void ALTROIF::SetNSamples(const std::bitset< 10 >& value)
{
  // Nr. Samples / channel ≡ [9:0]
  Register::InsertValue<0>(fBits, value);
			      
}


