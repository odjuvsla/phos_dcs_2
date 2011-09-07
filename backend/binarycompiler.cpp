
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

  for ( int i = 0; i < nVal; i++ )
    {
      binData.push_back ( regVal[i] );
    }

  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  MakeReadRcuBlock ( regAdd, binData, nVal );

  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
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

int binaryCompiler::MakeWriteFecRegisters(int registerType, vector< uint_t > regAdds, vector< uint_t >& regVals, AltroCh_t channel, vector< uint_t > binData, uint_t nVals)
{
  int ret = 0;

  if ( ( registerType == REGTYPE_BC ) || ( registerType ==  REGTYPE_ALTRO ) || ( registerType == REGTYPE_TRU ) )
    {
  
      binData.push_back ( ( RcuRegisterMap::RCU_WRITE_MEMBLOCK | ( nVals*2+2 ) ) );
      binData.push_back ( RcuRegisterMap::Instruction_MEM );

      int j = 0;

      for ( int i=0; i<nVals; i++ )
        {
          binData.push_back ( InstructionMaker::MakeMS20Instruction ( registerType, false, regAdds[i], channel.getBranchId(), channel.getFecId(), channel.getChipId(), channel.getChId() ) );
          binData.push_back ( InstructionMaker::MakeLS20Instruction ( false, regVals[j] ) );
          j++;
        }
      
      binData.push_back ( RcuRegisterMap::END );
      binData.push_back ( RcuRegisterMap::ENDMEM );
      binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );
    }
  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeWriteReadFeeRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE, __FILE__, __LINE__ );
    }

  return ret;

}

int binaryCompiler::MakeReadFecRegisters(int registerType, vector< uint_t > regAdds, AltroCh_t channel, vector< uint_t > binData, uint_t nVals)
{
  binData.push_back ( RcuRegisterMap::RCU_WRITE_MEMBLOCK| ( nVals+2 ) );
  binData.push_back ( RcuRegisterMap::Instruction_MEM );

  for ( int i=0; i<nVals; i++ )
    {
      if ( registerType == REGTYPE_ALTRO )
        {
          binData.push_back ( InstructionMaker::MakeMS20Instruction ( registerType, true, regAdds[i],  channel.getBranchId(), channel.getFecId(), channel.getChipId(), channel.getChId() ) );
        }
      else
        {
          binData.push_back ( InstructionMaker::MakeMS20Instruction ( registerType, true, regAdds[i], channel.getBranchId(), channel.getFecId()));
        }

    }

  binData.push_back ( RcuRegisterMap::END );
  binData.push_back ( RcuRegisterMap::ENDMEM );
  binData.push_back ( RcuRegisterMap::CE_CMD_TRAILER );

  stringstream log;
  for ( int i = 0; i < binData.size(); ++i )
    {
      log.str ( "" );
      log << "BinaryCompiler::MakeReadFeeRegisterBinary: block data[" << i << "] = 0x" << hex << binData.at ( i ) << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE,  __FILE__, __LINE__ );
    }

  return 0;

}

int binaryCompiler::MakeWriteReadAltroRegisters(vector< uint_t >& regAdds, std::vector<uint_t >& regVals, AltroCh_t channel, vector< uint_t > binData, uint_t nVals)
{

}

int binaryCompiler::MakeWriteReadBCRegisters(vector< uint_t > regAdds, vector< uint_t >& regVals, Fec_t card, vector< uint_t > binData, uint_t nVals)
{

}
