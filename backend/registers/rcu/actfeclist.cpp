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


#include "actfeclist.h"

/** Get FEC Active Value
 * 
 * @param branch [0,1], A:0, B:1
 * @param index [0,14], (includes TRU at idx 0) TODO: Figure out the indexing
 * @param value value of bit, true equals on.
 */
bool ACTFECLIST::GetFECActive(size_t branch, size_t index) const
{
  if( branch ) // if branch B:
    return fBits[16+index];
  else // if branch A:
    return fBits[index];
}


/** Set FEC Active Value
 * @param branch [0,1], A:0, B:1
 * @param index [0,14],(includes TRU at idx 0) TODO: Figure out the indexing
 * @param value value of bit, true equals on.
 */
void ACTFECLIST::SetFECActive(size_t branch, size_t index, bool value)
{
  
  if( branch ) // if branch B:
    fBits[16+index] = value;
  else // if branch A:
    fBits[index] = value;

}

