/*
    Library for controlling and configuring the electronics for the PHOS
    detector at the ALICE Experiment
    Copyright (C) 2011  Oystein Djuvsland <oystein.djuvsland@gmail.com>

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

#include "instructionmaker.h"
#include "phosconstants.h"
#include "../logger/phosdcslogging.h"
#include <phosdcstypes.h>

using namespace phosConstants;
using namespace std;

unsigned long
InstructionMaker::MakeMS20Instruction ( const uint_t registerType,   const bool read,
                                        const unsigned long reg,  const unsigned long branch,
                                        const unsigned long card,  const unsigned long chip,
                                        const unsigned long channel )
{

  stringstream log;

  int tmp_bc_altro = 0;

  int tmpCommand = 0;


  int tmp_broadcast = 0;

  if ( registerType == REGTYPE_BC || ( registerType == REGTYPE_TRU ) )
    {
      tmp_bc_altro = 1;

    }
  else if ( registerType ==  REGTYPE_ALTRO )
    {
      tmp_bc_altro = 0;

      //CRAP PTH: if we are not reading then we are writing, and for the
      //moment the altro is always configured in broadcast mode

      if ( read == false )
        {
          tmp_broadcast = 1;
        }

    }

  if ( read == true )
    {
      tmpCommand = FEC_RD;
    }

  else if ( read == false )
    {
      tmpCommand = FEC_WR;
    }

  // Calculating parity (1 if odd, 0 if even)
  unsigned int tmpInstruction = 0;
  int tmpParity = 0;
  tmpInstruction = ( tmp_bc_altro << BC_AL ) | ( tmp_broadcast << BCAST ) | ( branch<<BRANCH ) | ( card<<FAD ) | ( channel <<REGAD ) | reg;

  int no_ones = 0;
  while ( tmpInstruction )
    {
      no_ones++;
      tmpInstruction = tmpInstruction & ( tmpInstruction - 1 );
    }
  tmpParity = no_ones & 1;

  int command = ( tmpCommand << CMD_TYPE ) | ( tmpParity << PAR ) | ( tmp_bc_altro << BC_AL ) | ( tmp_broadcast << BCAST ) | ( branch<<BRANCH ) | ( card<<FAD ) | ( channel <<REGAD ) | reg;

  log.str ( "" );
  log << hex << "InstructionMaker::MakeMS20Instruction: Command type: " << tmpCommand << ", parity: " << tmpParity << ", BC or ALTRO: " << tmp_bc_altro << ", broadcast: "
  << tmp_broadcast << ", branch: " << branch << ", card: " << card << ", channel: " << channel << ", register: " << reg << dec << endl;
  log << hex << "Command: " << command << endl;

  phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE, __FILE__, __LINE__ );


  return ( tmpCommand << CMD_TYPE ) | ( tmpParity << PAR ) | ( tmp_bc_altro << BC_AL ) | ( tmp_broadcast << BCAST ) | ( branch<<BRANCH ) | ( card<<FAD ) | ( channel <<REGAD ) | reg;


}


unsigned long
InstructionMaker::MakeLS20Instruction ( const bool read, const unsigned long registerValue )
{
  int tmpCommand = 0;
  //int tmp_rw = 0;

  if ( read == true )
    {
      tmpCommand  = FEC_RD ;
    }
  else if ( read == false )
    {
      tmpCommand =  FEC_WR;
    }

  return ( tmpCommand << CMD_TYPE ) | ( registerValue << REGVAL );

}



