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


#include "trgconf.h"

long unsigned int TRGCONF::GetTriggerSource() const
{
/* Trigger Source [16:14]
 * “100” ≡ CTP – Triger Enabled
 * “001” ≡ Software Trigger Enable (0x5306)
 * “110” ≡ Auxiliary Trigger Enable
 */
  return Register::ReadValue<14,16>(fBits);
}


void TRGCONF::SetTriggerSource(const std::bitset< 3 >& value)
{
/* Trigger Source [16:14]
 * “100” ≡ CTP – Triger Enabled
 * “001” ≡ Software Trigger Enable (0x5306)
 * “110” ≡ Auxiliary Trigger Enable
 */
  Register::InsertValue<14>(fBits, value);
}

bool TRGCONF::GetTriggerMode() const
{
/* Trigger Mode [13]
 * ‘0’ ≡ Trigger mode is TPC {L1 from CTP is mapped to L1 to FEC}
 * ‘1’ ≡ Trigger mode is PHOS {L0 from CTP is delivered as L1 to FEC}
 */
  return fBits[13];
}

void TRGCONF::SetTriggerMode(bool value)
{
/* Trigger Mode [13]
 * ‘0’ ≡ Trigger mode is TPC {L1 from CTP is mapped to L1 to FEC}
 * ‘1’ ≡ Trigger mode is PHOS {L0 from CTP is delivered as L1 to FEC}
 */
  fBits[13] = value;
}

long unsigned int TRGCONF::GetTriggerLatency() const
{
/* L1 – L2 Latency [12:0]
 * When software trigger is issued this latency is used to set the latency between L1 and L2 to FECs.
 */
  return Register::ReadValue<0,12>(fBits);
}

void TRGCONF::SetTriggerLatency(const std::bitset< 13 >& value)
{
/* L1 – L2 Latency [12:0]
 * When software trigger is issued this latency is used to set the latency between L1 and L2 to FECs.
 */
  Register::InsertValue<0>(fBits, value);
}

