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


#include "rdomod.h"

bool RDOMOD::GetMultiEventBuffer() const
{
/* MEB (multi event buffer) Mode [0]
 * ‘0’ ≡ Multi event buffer mode is set to 4
 * ‘1’ ≡ Multi event buffer mode is set to 8
 */
  return fBits[0];
}

void RDOMOD::SetMultiEventBuffer(bool value)
{
/* MEB (multi event buffer) Mode [0]
 * ‘0’ ≡ Multi event buffer mode is set to 4
 * ‘1’ ≡ Multi event buffer mode is set to 8
 */
  fBits[0] = value;
}

bool RDOMOD::GetRDYEX() const
{
/* Mask Read to Receive “RDYEX” [3]
 * “1” ≡ Ready to receive command is masked, means even if the ready to receive
 * command is not given from DDL still data will be delivered from RCU to SIU.
 * {Used for debugging purposes}
 * “0” ≡ Ready to receive command (open link) must be given before data is to be
 * received.
 */
  return fBits[3];
}

void RDOMOD::SetRDYEX(bool value)
{
/* Mask Read to Receive “RDYEX” [3]
 * “1” ≡ Ready to receive command is masked, means even if the ready to receive
 * command is not given from DDL still data will be delivered from RCU to SIU.
 * {Used for debugging purposes}
 * “0” ≡ Ready to receive command (open link) must be given before data is to be
 * received.
 */
  fBits[3] = value;
}

bool RDOMOD::GetSOEOIEIME() const
{
/* SOE/EOE Instruction Memory Execution [1]
 * ‘0’ ≡ Sequence in the instruction memory will not be executed on SOE/EOE.
 * ‘1’ ≡ Sequence in the instruction memory will be executed on SOE/EOE and
 * result from result memory will be sent as payload.
 */
  return fBits[1];
}

void RDOMOD::SetSOEOIEIME(bool value)
{
/* SOE/EOE Instruction Memory Execution [1]
 * ‘0’ ≡ Sequence in the instruction memory will not be executed on SOE/EOE.
 * ‘1’ ≡ Sequence in the instruction memory will be executed on SOE/EOE and
 * result from result memory will be sent as payload.
 */
  fBits[1] = value;
}

bool RDOMOD::GetSparseReadoutMode() const
{
/* Sparse Readout Mode [2]
 * ‘0’ ≡ Read out mode is “full readout” according to readout list memory.
 * ‘1’ ≡ Read out mode is “sparse readout” according to readout list memory.
 */
  return fBits[2];
}

void RDOMOD::SetSparseReadoutMode(bool value)
{
/* Sparse Readout Mode [2]
 * ‘0’ ≡ Read out mode is “full readout” according to readout list memory.
 * ‘1’ ≡ Read out mode is “sparse readout” according to readout list memory.
 */
  fBits[2] = value;
}

bool RDOMOD::GetMCheckBlockLengthMismatch() const
{
/* Mask Check of [Channel Address / Block Length] Mismatch [5][4]
 * [4] = “1” ≡ check of Block Length mismatch will be masked (not checked)
 * [4]= “0” ≡ check of Block Length mismatch will not be masked (checked)
 */
return fBits[4];
}

void RDOMOD::SetMCheckBlockLengthMismatch(bool value)
{
/* Mask Check of [Channel Address / Block Length] Mismatch [5][4]
 * [4] = “1” ≡ check of Block Length mismatch will be masked (not checked)
 * [4]= “0” ≡ check of Block Length mismatch will not be masked (checked)
 */
fBits[4] = value;
}

bool RDOMOD::GetMCheckChannelAddressMismatch() const
{
/* Mask Check of [Channel Address / Block Length] Mismatch [5][4]
 * [5] = “1” ≡ check of Channel address mismatch will be masked (not checked)
 * [5]= “0” ≡ check of Channel address mismatch will not be masked (checked)
 */
return fBits[5];
}

void RDOMOD::SetMCheckChannelAddressMismatch(bool value)
{
/* Mask Check of [Channel Address / Block Length] Mismatch [5][4]
 * [5] = “1” ≡ check of Channel address mismatch will be masked (not checked)
 * [5]= “0” ≡ check of Channel address mismatch will not be masked (checked)
 */
fBits[5] = value;
}
