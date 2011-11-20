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
#include <cassert>
using namespace std;

int main()
{
  Register* reg = new ACTFECLIST(0x1234);
  assert( ACTFECLIST::Address == reg->GetAddress() );
  assert( ACTFECLIST::Access  == reg->GetAccess() );
  assert( RegisterTraits::RCU  == reg->GetType() );
  assert( 0x1234 == reg->GetValue() );
  
  reg->SetValue(0x4321);
  assert( 0x4321 == reg->GetValue() );
  
  
  return 0;
}