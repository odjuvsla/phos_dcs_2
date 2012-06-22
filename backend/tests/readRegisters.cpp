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
    assert(false, "argument required, example: $ ./readRegister");
  PhosDcsClient cl(argv[1]);

  Register* reg = new ACTFECLIST(0x1234);
  cl.readRcuRegister(reg);

  PIINFO("ACTFECLIST Read: 0x%X", reg->GetValue());

  



  return 0;
}
