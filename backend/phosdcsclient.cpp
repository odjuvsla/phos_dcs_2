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

#include "phosdcsclient.h"
#include "binarycompiler.h"
#include "../logger/phosdcslogging.h"
#include <sstream>
#include <cstdio>

phosDcsClient::phosDcsClient() : FeeSampleClient(),
fBinaryCompiler(0)
{

}

phosDcsClient::~phosDcsClient()
{

}

int phosDcsClient::writeRcuRegister(Register_t* reg)
{
    if (reg)
    {
	std::stringstream log;
	log << hex << "Writing RCU register: 0x" << reg->GetRegisterAddress() << " with value: 0x" << reg->GetRegisterValue() << dec;
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);

	vector<uint_t> binaryData;
	
	fBinaryCompiler->MakeWriteReadRcuRegister(reg->GetRegisterAddress(), reg->GetRegisterValue(), binaryData);
	
	return 0;
    }
    return -1;
}

int phosDcsClient::writeFecRegister(Register_t* reg, AltroCh_t* ch)
{
    if (ch)
    {
        std::stringstream log;
        log << "ALTRO channel: " << ch->getChId() << ", chip: " << ch->getChipId() << ", FEC: " << ch->getFecId() << ", branch: " << ch->getBranchId();
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);
	return 0;
    }
    return -1;
}

int phosDcsClient::ExecuteBinary( const char* feeServerName, const vector<unsigned long> & binData, vector<unsigned long> &  resultBuffer )
{

  vector<unsigned int> data;
  //data.resize ( binData.size() );
  std::string serverName    = feeServerName;

  stringstream log;

  size_t size          = binData.size() *4;
  unsigned short flags = 0;
  short errorCode      = 0;
  short status         = 0;

  for ( size_t i = 0; i < binData.size(); i++ )
    {
      data.push_back(binData[i]);
    }

  int ret = writeReadData ( serverName, size, data, flags, errorCode, status );


  resultBuffer.clear();
  for ( size_t i=0; i< size/4; i++ )
    {

      log.str ( "" );
      log << "PhosFeeClient::ExecuteBinary result data[" << i << "] = 0x" << hex << data[i] << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE, __FILE__, __LINE__ );

      resultBuffer.push_back ( data[i] );
    }

  return ret;
}
