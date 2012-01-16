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

/** Trigger Source [16:14].
 * 
 * “100” ≡ CTP – Triger Enabled \n
 * “001” ≡ Software Trigger Enable (0x5306) \n
 * “110” ≡ Auxiliary Trigger Enable
 */
long unsigned int TRGCONF::GetTriggerSource() const
{
  return Register::ReadValue<14,16>(fBits);
}


/** Trigger Source [16:14].
 * 
 * “100” ≡ CTP – Triger Enabled \n
 * “001” ≡ Software Trigger Enable (0x5306) \n
 * “110” ≡ Auxiliary Trigger Enable
 */
void TRGCONF::SetTriggerSource(const std::bitset< 3 >& value)
{
  Register::InsertValue<14>(fBits, value);
}

bool TRGCONF::GetTriggerMode() const
{
/** Trigger Mode [13].
 * 
 * ‘0’ ≡ Trigger mode is TPC {L1 from CTP is mapped to L1 to FEC} \n
 * ‘1’ ≡ Trigger mode is PHOS {L0 from CTP is delivered as L1 to FEC}
 */
  return fBits[13];
}

/** Trigger Mode [13].
 * 
 * ‘0’ ≡ Trigger mode is TPC {L1 from CTP is mapped to L1 to FEC} \n
 * ‘1’ ≡ Trigger mode is PHOS {L0 from CTP is delivered as L1 to FEC}
 */
void TRGCONF::SetTriggerMode(bool value)
{
  fBits[13] = value;
}

/** L1 – L2 Latency [12:0].
 * 
 * When software trigger is issued this latency is used to set the latency between L1 and L2 to FECs.
 */
long unsigned int TRGCONF::GetTriggerLatency() const
{
  return Register::ReadValue<0,12>(fBits);
}

/** L1 – L2 Latency [12:0].
 * 
 * When software trigger is issued this latency is used to set the latency between L1 and L2 to FECs.
 */
void TRGCONF::SetTriggerLatency(const std::bitset< 13 >& value)
{
  Register::InsertValue<0>(fBits, value);
}

