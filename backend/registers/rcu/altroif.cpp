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

/** CSTB programmable delay, [0,3].
 *
 * This is the delay between the assertion of “cstb” and altro bus to avoid any possibility of glitch on hand shake
 * signals due to 40 bit ALTRO bus driving.
 */
unsigned long ALTROIF::GetCSTBDelay() const
{
  return Register::ReadValue<14,15>(fBits);
}

/** CSTB programmable delay, [15:14]
 *
 * This is the delay between the assertion of “cstb” and altro bus to avoid any possibility of glitch on hand shake
 * signals due to 40 bit ALTRO bus driving.
 */
void ALTROIF::SetCSTBDelay(const std::bitset< 2 >& value)
{

  Register::InsertValue<14>(fBits, value);
}

/** Instruction error check selection ≡ [17:16]
 *
 * “00”:= Contents of Instruction memory are not Checked \n
 * “01”:= Contents of Instruction memory will be checked against TPC instruction set. \n
 * “10”:= Contents of Instruction Memory will be checked against PHOS instruction set. \n
 * “11”:= Contents of Instruction Memory will be checked against FMD instruction set \n
 */
unsigned long ALTROIF::GetIECS() const
{
  return Register::ReadValue<16,17>(fBits);
}

/** Instruction error check selection ≡ [17:16]
 *
 * “00”:= Contents of Instruction memory are not Checked \n
 * “01”:= Contents of Instruction memory will be checked against TPC instruction set. \n
 * “10”:= Contents of Instruction Memory will be checked against PHOS instruction set. \n
 * “11”:= Contents of Instruction Memory will be checked against FMD instruction set \n
 */
void ALTROIF::SetIECS(const std::bitset<2>& value)
{
  Register::InsertValue<16>(fBits, value);
}

/** Sampling Clock Dividing Ratio: T sampling / TLHC ≡ [13:10]
 *
 * “00”:= divide by 2; Period of sampling clock = 50nsec \n
 * “01”:= divide by 4; Period of sampling clock = 100nsec \n
 * “10”:= divide by 8; Period of sampling clock = 200nsec \n
 * “11”:= divide by 16; Period of sampling clock = 400nsec \n
 */
unsigned long ALTROIF::GetSCDR() const
{
  return Register::ReadValue<10,13>(fBits);
}

/** Sampling Clock Dividing Ratio: T sampling / TLHC ≡ [13:10]
 *
 * “00”:= divide by 2; Period of sampling clock = 50nsec \n
 * “01”:= divide by 4; Period of sampling clock = 100nsec \n
 * “10”:= divide by 8; Period of sampling clock = 200nsec \n
 * “11”:= divide by 16; Period of sampling clock = 400nsec
 */
void ALTROIF::SetSCDR(const std::bitset<4>& value)
{
  Register::InsertValue<10>(fBits, value);
}

/** Nr Samples / channel == [9:0] */
unsigned long ALTROIF::GetNSamples() const
{
  return Register::ReadValue<0,9>(fBits);
}

/** Nr Samples pr. channel == [9:0] */
void ALTROIF::SetNSamples(const std::bitset< 10 >& value)
{
  Register::InsertValue<0>(fBits, value);
}


