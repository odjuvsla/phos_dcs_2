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

#include "phosdcsinterface.h"
#include "idtypes.h"
#include "rcu.h"
#include "../pilogger/backend/pilogger.h"


using namespace phosDcs;

PhosDcsInterface::PhosDcsInterface(const RcuID& rcu) :
 _rcuId(rcu)
,_feeClient(0)
,lastACTFECLIST(0)
{
}

PhosDcsInterface::~PhosDcsInterface()
{
  //TODO: implement cleanup!!!
}

int PhosDcsInterface::connect(const QString& feeServerName)
{
  PIDEBUG("Initializing _feeClient, PhosDcsClient::PhosDcsClient(\"%s\")", feeServerName.toStdString().c_str());
  _feeClient = new PhosDcsClient(feeServerName);

  phosDcsLogging::Instance()->Logging("PhosDcsInterface::connect does not return error code if appropriate", LOG_LEVEL_WARNING);
  return 0;
}

/** Turn on a single FEC on the RCU */
int PhosDcsInterface::turnOnOffFec(const FecID& fec, bool turnOn)
{
  /*if(lastACTFECLIST == 0 ) {
    lastACTFECLIST = new ACTFECLIST(0x0);
    _feeClient->readRcuRegister(lastACTFECLIST);
    PIINFO("ACTFECLIST Read: 0x%X", lastACTFECLIST->GetValue());
  }
  *///lastACTFECLIST->SetFECActive(fec.getBranchId(), fec.getFecId(), turnOn);
  //_feeClient->writeFecRegister();
  PIDEBUG("PhosDcsInterface::turnOnOffFec not implemented")
  exit(1);
}

/** Turn on a single TRU on the RCU */
int PhosDcsInterface::turnOnOffTru(const TruID& tru, bool turnOn)
{

}

/** update the List of active FEC */
int PhosDcsInterface::updateActiveFec()
{
  if(lastACTFECLIST == 0 ) {
    lastACTFECLIST = new ACTFECLIST(0x0);
  }
  _feeClient->readRcuRegister(lastACTFECLIST);
  PIINFO("ACTFECLIST Read: 0x%X", lastACTFECLIST->GetValue());
}


int PhosDcsInterface::applyApdSettings() const
{
  phosDcsLogging::Instance()->Logging("PhosDcsInterface::applyApdSettings not implemented", LOG_LEVEL_ERROR);
  //TODO: implement
  return 1;
}

int PhosDcsInterface::applyApdSettings(const FecID& fec) const
{
  phosDcsLogging::Instance()->Logging("PhosDcsInterface::applyApdSettings not implemented", LOG_LEVEL_ERROR);
  //TODO: implement
    return 1;
}

int PhosDcsInterface::applyReadoutSettings(const ReadoutSettings_t& readoutSettings) const
{
  phosDcsLogging::Instance()->Logging("PhosDcsInterface::applyReadoutSettings not implemented", LOG_LEVEL_ERROR);
  //TODO: implement 
    return 1;
}



int PhosDcsInterface::readRegister(Register* r) const
{
}

#include "phosdcsinterface.moc"