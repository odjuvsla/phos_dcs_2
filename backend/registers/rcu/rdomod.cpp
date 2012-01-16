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

/** MEB (multi event buffer) Mode [0].
 * 
 * ‘0’ ≡ Multi event buffer mode is set to 4 \n
 * ‘1’ ≡ Multi event buffer mode is set to 8
 */
bool RDOMOD::GetMultiEventBuffer() const
{
  return fBits[0];
}

/** MEB (multi event buffer) Mode [0].
 * 
 * ‘0’ ≡ Multi event buffer mode is set to 4 \n
 * ‘1’ ≡ Multi event buffer mode is set to 8
 */
void RDOMOD::SetMultiEventBuffer(bool value)
{
  fBits[0] = value;
}

/** Mask Read to Receive “RDYEX” [3].
 * 
 * “1” ≡ Ready to receive command is masked, means even if the ready to receive
 * command is not given from DDL still data will be delivered from RCU to SIU. 
 * {Used for debugging purposes} \n
 * “0” ≡ Ready to receive command (open link) must be given before data is to be 
 * received.
 */
bool RDOMOD::GetRDYEX() const
{
  return fBits[3];
}

/** Mask Read to Receive “RDYEX” [3].
 * “1” ≡ Ready to receive command is masked, means even if the ready to receive
 * command is not given from DDL still data will be delivered from RCU to SIU.
 * {Used for debugging purposes} \n
 * “0” ≡ Ready to receive command (open link) must be given before data is to be
 * received.
 */
void RDOMOD::SetRDYEX(bool value)
{
  fBits[3] = value;
}

bool RDOMOD::GetSOEOIEIME() const
{
  return fBits[1];
}

/** SOE/EOE Instruction Memory Execution [1].
 *
 * ‘0’ ≡ Sequence in the instruction memory will not be executed on SOE/EOE. \n
 * ‘1’ ≡ Sequence in the instruction memory will be executed on SOE/EOE and
 * result from result memory will be sent as payload.
 */
void RDOMOD::SetSOEOIEIME(bool value)
{
  fBits[1] = value;
}

/** Sparse Readout Mode [2].
 *
 * ‘0’ ≡ Read out mode is “full readout” according to readout list memory. \n
 * ‘1’ ≡ Read out mode is “sparse readout” according to readout list memory.
 */
bool RDOMOD::GetSparseReadoutMode() const
{
  return fBits[2];
}

/** Sparse Readout Mode [2].
 *
 * ‘0’ ≡ Read out mode is “full readout” according to readout list memory. \n
 * ‘1’ ≡ Read out mode is “sparse readout” according to readout list memory.
 */
void RDOMOD::SetSparseReadoutMode(bool value)
{
  fBits[2] = value;
}

/** Mask Check of Block Length Mismatch [4].
 *
 * [4] = “1” ≡ check of Block Length mismatch will be masked (not checked) \n
 * [4]= “0” ≡ check of Block Length mismatch will not be masked (checked)
 */
bool RDOMOD::GetMCheckBlockLengthMismatch() const
{
return fBits[4];
}

/** Mask Check of Block Length Mismatch [4].
 *
 * [4] = “1” ≡ check of Block Length mismatch will be masked (not checked) \n
 * [4]= “0” ≡ check of Block Length mismatch will not be masked (checked)
 */
void RDOMOD::SetMCheckBlockLengthMismatch(bool value)
{
fBits[4] = value;
}

/** Mask Check of Channel Address Mismatch [5].
 *
 * [5] = “1” ≡ check of Channel address mismatch will be masked (not checked) \n
 * [5]= “0” ≡ check of Channel address mismatch will not be masked (checked)
 */
bool RDOMOD::GetMCheckChannelAddressMismatch() const
{
return fBits[5];
}

/** Mask Check of Channel Address Mismatch [5].
 *
 * [5] = “1” ≡ check of Channel address mismatch will be masked (not checked) \n
 * [5]= “0” ≡ check of Channel address mismatch will not be masked (checked)
 */
void RDOMOD::SetMCheckChannelAddressMismatch(bool value)
{
fBits[5] = value;
}
