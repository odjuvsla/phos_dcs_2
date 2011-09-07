#include "phosdcsclient.h"
#include "binarycompiler.h"
#include "../logger/phosdcslogging.h"
#include <sstream>
#include <cstdio>

phosDcsClient::phosDcsClient() : FeeSampleClient()
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
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE);

	vector<uint_t> binaryData;
	
	fBinaryCompiler->MakeWriteReadRcuRegister(reg->GetRegisterAddress(), reg->GetRegisterValue(), binaryData);
    }
}

int phosDcsClient::writeFecRegister(Register_t* reg, AltroCh_t* ch)
{
    if (ch)
    {
        std::stringstream log;
        log << "ALTRO channel: " << ch->getChId() << ", chip: " << ch->getChipId() << ", FEC: " << ch->getFecId() << ", branch: " << ch->getBranchId();
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);
    }
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

  for ( int i = 0; i < binData.size(); i++ )
    {
      data.push_back(binData[i]);
    }

  int ret = writeReadData ( serverName, size, data, flags, errorCode, status );


  resultBuffer.clear();
  for ( int i=0; i< size/4; i++ )
    {

      log.str ( "" );
      log << "PhosFeeClient::ExecuteBinary result data[" << i << "] = 0x" << hex << data[i] << dec;
      phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE );

      resultBuffer.push_back ( data[i] );
    }

  return ret;
}
