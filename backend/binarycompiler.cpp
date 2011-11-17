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

#include "binarycompiler.h"
#include "registermaps/RcuRegisterMap.h"
#include "instructionmaker.h"
#include "../logger/phosdcslogging.h"
#include "phosconstants.h"

using namespace phosConstants;

binaryCompiler::binaryCompiler()
{

}

binaryCompiler::~binaryCompiler()
{

}

int binaryCompiler::MakeWriteReadRcuRegister(uint_t regAdd, uint_t regVal, vector< uint_t >& binData)
{
  vector<uint_t> vals;
  vals.push_back(regVal);
  return MakeWriteReadRcuBlock(regAdd, vals, binData, 1);
}

int binaryCompiler::MakeWriteReadRcuBlock(uint_t regAdd, std::vector<uint_t >& regVal, vector< uint_t >& binData, uint_t nVal)
{
  
  binData.push_back ( RcuRegisterMap::RCU_WRITE_MEMBLOCK|nVal );

  binData.push_back ( regAdd );

  for ( size_t i = 0; i < nVal; i++ )
    {
      binData.push_back ( regVal[i] );
    }

  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  MakeReadRcuBlock ( regAdd, binData, nVal );

  stringstream log;
  for ( size_t i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeWriteReadRcuBlock: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE, __FILE__, __LINE__ );
    }

  return 0;

}

int binaryCompiler::MakeReadRcuBlock(uint_t regAdd, vector< uint_t >& binData, uint_t nVal)
{
  
  binData.push_back ( RcuRegisterMap::RCU_READ_MEMBLOCK|nVal );

  binData.push_back ( regAdd );

  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  stringstream log;
  
//   for ( int i = 0; i < binData.size(); ++i )
//     {
//       log.str ( "" );
//       log << "BinaryCompiler::MakeReadRcuBlock: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
//       phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );
//     }

  return 0;

}

int binaryCompiler::MakeReadRcuRegister(uint_t regAdd, vector< uint_t >& binData)
{
  return MakeReadRcuBlock(regAdd, binData, 1);
}

int binaryCompiler::MakeReadResultMemory ( vector<uint_t> & binData, uint_t nVal )
{
  return MakeReadRcuBlock ( RcuRegisterMap::Result_MEM, binData, nVal );
}

int binaryCompiler::MakeWriteFecRegisters(uint_t registerType, vector< uint_t > regAdds, vector< uint_t >& regVals, AltroCh_t channel, vector< uint_t > &binData)
{
  int ret = 0;

  if ( ( registerType == REGTYPE_BC ) || ( registerType ==  REGTYPE_ALTRO ) || ( registerType == REGTYPE_TRU ) )
    {
  
      binData.push_back ( ( RcuRegisterMap::RCU_WRITE_MEMBLOCK | ( regAdds.size()*2+2 ) ) );
      binData.push_back ( RcuRegisterMap::Instruction_MEM );

      int j = 0;

      for ( uint_t i=0; i<regAdds.size(); i++ )
        {
          binData.push_back ( instructionMaker::MakeMS20Instruction ( registerType, false, regAdds[i], channel.getBranchId(), channel.getFecId(), channel.getChipId(), channel.getChId() ) );
          binData.push_back ( instructionMaker::MakeLS20Instruction ( false, regVals[j] ) );
          j++;
        }
      
      binData.push_back ( RcuRegisterMap::END );
      binData.push_back ( RcuRegisterMap::ENDMEM );
      binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );
    }
  stringstream log;
  for ( size_t i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE, __FILE__, __LINE__ );
    }

  return ret;

}

int binaryCompiler::MakeReadFecRegisters(uint_t registerType, vector< uint_t > regAdds, AltroCh_t channel, vector< uint_t > &binData)
{
  binData.push_back ( RcuRegisterMap::RCU_WRITE_MEMBLOCK| ( regAdds.size()+2 ) );
  binData.push_back ( RcuRegisterMap::Instruction_MEM );

  for ( uint_t i=0; i<regAdds.size(); i++ )
    {
      if ( registerType == REGTYPE_ALTRO )
        {
          binData.push_back ( instructionMaker::MakeMS20Instruction ( registerType, true, regAdds[i],  channel.getBranchId(), channel.getFecId(), channel.getChipId(), channel.getChId() ) );
        }
      else
        {
          binData.push_back ( instructionMaker::MakeMS20Instruction ( registerType, true, regAdds[i], channel.getBranchId(), channel.getFecId()));
        }

    }

  binData.push_back ( RcuRegisterMap::END );
  binData.push_back ( RcuRegisterMap::ENDMEM );
  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  stringstream log;
  for ( size_t i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeReadFeeRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE,  __FILE__, __LINE__ );
    }

  return 0;

}

int binaryCompiler::MakeWriteReadAltroRegisters(vector< uint_t >& regAdds, std::vector<uint_t >& regVals, AltroCh_t channel, vector< uint_t > &binData)
{
  return 0;
}

int binaryCompiler::MakeWriteReadBCRegisters(vector< uint_t > regAdds, vector< uint_t >& regVals, Fec_t card, vector< uint_t > &binData)
{
  return 0;
}

int binaryCompiler::MakeReadBcRegister(vector< uint_t > regAdds, Fec_t card, vector< uint_t >& binData)
{
  AltroCh_t channel(0, 0, card.getFecId(), card.getBranchId(), card.getRcuId(), card.getModuleId());
  return MakeReadFecRegisters(REGTYPE_BC, regAdds, channel, binData);
}
