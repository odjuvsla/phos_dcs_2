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
#include <iostream>
#include <stdlib.h>
#include <bitset>
#include <phosdcsclient.h>
#include <../pilogger/backend/pilogger.h>
using namespace std;

void assert(bool val, const char* mes = "")
{
  if( ! val )
  {
    cout <<"error motherfucker: " <<  mes << endl;
    exit(1);
  }
}

int main(int argc, char ** argv)
{
  if(argc < 2 )
    assert(false);
  PhosDcsClient cl(argv[1]);

  Register* reg = new ACTFECLIST(0x1234);
  cl.readRcuRegister(reg);

  PIINFO("ACTFECLIST Read: 0x%X", reg->GetValue());

  


  assert( 0x5100 == ACTFECLIST::Address );
  assert( ACTFECLIST::Address == reg->GetAddress() );
  assert( ACTFECLIST::Access  == reg->GetAccess() );
  assert( Register::RCU  == reg->GetType() );
  assert( 0x1234 == reg->GetValue() );

  reg->SetValue(0x4321);
  assert( 0x4321 == reg->GetValue() );

  // testing ReadValue & InsertValue
  bitset<18> bits(string("1110111"));
  bitset<3> stripped = Register::ReadValue<2,4>(bits);
  assert( stripped == bitset<3>(string("101")) );

  bitset<18> bits2(string("0010100"));
  bitset<3> stripped2 = Register::ReadValue<2,4>(bits2);
  assert( stripped2 == bitset<3>(string("101")) );

  bitset<3> insert(string("010"));
  bitset<18> inserted = Register::InsertValue<2>(bits, insert);
  assert( inserted.to_ulong() == bitset<7>(string("1101011")).to_ulong());

  bitset<3> insert2(string("111"));
  bitset<18> inserted2 = Register::InsertValue<2>(bits2, insert2);
  assert( inserted2.to_ulong() == bitset<7>(string("0011100")).to_ulong());

  return 0;
}
