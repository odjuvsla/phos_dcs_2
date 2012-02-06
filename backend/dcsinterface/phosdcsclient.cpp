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
#include "../pilogger/backend/pilogger.h"
#include <sstream>
#include <cstdio>
#include <QMutex>

using namespace std;

PhosDcsClient::PhosDcsClient(QString feeServerName) : FeeSampleClient()
	,_mutex(new QMutex)
        ,_binaryCompiler(0)
	,_feeServerName(feeServerName)
{

}

PhosDcsClient::~PhosDcsClient()
{

}

int PhosDcsClient::writeRcuRegister(const Register* reg)
{
    QMutexLocker locker(_mutex);
    if (reg)
    {
	std::stringstream log;
	log << hex << "Writing RCU register: 0x" << reg->GetAddress() << " with value: 0x" << reg->GetValue() << dec;
	PIDEBUG("%s", log.str().c_str());
//        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);

	vector<uint_t> binaryData;
	
	_binaryCompiler->MakeWriteReadRcuRegister(reg->GetAddress(), reg->GetValue(), binaryData);
	
	vector<uint_t> result;
	executeBinary(binaryData, result);
	
	return 0;
    }
    return -1;
}

int PhosDcsClient::writeFecRegister(const Register* reg, const AltroChannelID* ch)
{
  QMutexLocker locker(_mutex);
    if (ch)
    {
        std::stringstream log;
        log << "ALTRO channel: " << ch->getAltroChannelID() << ", chip: " << ch->getAltroID() << ", FEC: " << ch->getFecId() << ", branch: " << ch->getBranchId();
	PIDEBUG("%s", log.str().c_str());
        //phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);
	return 0;
    }
    return -1;
}

int PhosDcsClient::readFecRegister(Register* reg, const AltroChannelID* ch)
{
  QMutexLocker locker(_mutex);
}

int PhosDcsClient::readRcuRegister(Register* reg)
{
  QMutexLocker locker(_mutex);
  if (reg)
    {
	std::stringstream log;
	log << hex << "Reading RCU register: 0x" << reg->GetAddress() << dec;
	PIDEBUG("%s", log.str().c_str());
        //phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);

	vector<uint_t> binaryData;
	
	_binaryCompiler->MakeReadRcuRegister(reg->GetAddress(), binaryData);
	
	vector<uint_t> result;
	executeBinary(binaryData, result);
	
	reg->SetValue(result[0]);
	
	return 0;
    }
    return -1;
}

int PhosDcsClient::readBcRegister(Register* reg, const FecID* fec)
{
QMutexLocker locker(_mutex);
  if (reg)
    {
	std::stringstream log;
	log << hex << "Reading BC register: 0x" << reg->GetAddress() << dec;
	PIDEBUG("%s", log.str().c_str());
        //phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_VERBOSE, __FILE__, __LINE__);

	vector<uint_t> binaryData;
	vector<uint_t> regAdds;
	regAdds.push_back(reg->GetAddress());
	_binaryCompiler->MakeReadBcRegister(regAdds, *fec, binaryData);
	
	vector<uint_t> result;
	executeBinary(binaryData, result);
	
	reg->SetValue(result[0]);
	
	return result[0];
    }
    return -1;
}


int PhosDcsClient::executeBinary(const vector<uint_t> & binData, vector<uint_t> &  resultBuffer )
{
  vector<unsigned int> data;

  std::string serverName    = _feeServerName.toStdString();

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
      PIDEBUG("%s", log.str().c_str());
      //phosDcsLogging::Instance()->Logging ( log.str(), LOG_LEVEL_EXTREME_VERBOSE, __FILE__, __LINE__ );

      resultBuffer.push_back ( data[i] );
    }

  return ret;
}
