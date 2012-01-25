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

#include "rcu.h"
#include "../pilogger/backend/pilogger.h"
#include <registers.h>

using namespace phosDcs;

#include "phosconstants.h"
using namespace PHOS;


rcu::rcu(RcuID rcu):
_rcuId(rcu)
,_feeClient(0)
{
  for(int i = 0; i < CARDS_PER_BRANCH; i++)
  {
    FecID fA(i+1, BRANCH_A, _rcuId.getRcuId(), _rcuId.getModuleId());
    phosDcs::fec cardA(fA);
    _fecsBranchA.push_back(cardA);
    FecID fB(i+1+MAX_CARDS_PER_BRANCH, BRANCH_B, _rcuId.getRcuId(), _rcuId.getModuleId());
    phosDcs::fec cardB(fB);
    _fecsBranchB.push_back(cardB);
  }
}

rcu::~rcu()
{

}

int rcu::init(QString feeServerName)
{
  _feeClient = new phosDcsClient(feeServerName);
  _feeClient->registerFeeServerName(feeServerName.toStdString().c_str());
  int nServices = _feeClient->startFeeClient();
  std::stringstream log;
  log << "Initialised FEE server: " << feeServerName.toStdString() << ", " << nServices << " registered.";
  phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_INFO, __FILE__, __LINE__);

  return nServices;
}

int rcu::turnOn(bool on)
{
  rcu::turnOnFecs t;
  t.setFeeClient(_feeClient);
  t.setBranches(&_fecsBranchA, &_fecsBranchB);
  t.setOn(on);
  t.start();
  return 0;
}

void rcu::turnOnFecs::run()
{
  ACTFECLIST actList;
  
  std::vector<phosDcs::fec>::iterator it;
  for(it = _branchA->begin(); it < _branchA->end(); ++it)
  {
    unsigned int fecCardNumber = (*it).getCardNumber(); // card number pr branch
    _client->readRcuRegister(&actList);
    //actList.GetRegisterBits().set((*it).getCardNumber(), _on);
    actList.SetFECActive(0, fecCardNumber); // branch 0/A 
    _client->writeRcuRegister(&actList);
    usleep(500000);
    FecID f = (*it).getFecId();
    BCVERSION reg(0x0);
    _client->readBcRegister(&reg, &f);

    int state = FEE_STATE_UNKNOWN;
    
    if(reg.GetValue() == PCMVERSION)
    {
	state = FEE_STATE_ON;
    }
    else if(reg.GetValue() == OLD_PCMVERSION)
    {
      state = FEE_STATE_WARNING;
    }
    else
    {
      state = FEE_STATE_ERROR;
    }
  }
  for(it = _branchB->begin(); it < _branchB->end(); ++it)
  {
    unsigned int fecCardNumber = (*it).getCardNumber(); // card number pr branch
    _client->readRcuRegister(&actList);
    //actList.GetRegisterBits().set((*it).getCardNumber(), _on);
    actList.SetFECActive(1, fecCardNumber); // branch 0/A
    _client->writeRcuRegister(&actList);
    usleep(500000);
    FecID f = (*it).getFecId();
    BCVERSION reg(0x0);
    _client->readBcRegister(&reg, &f);

    int state = FEE_STATE_UNKNOWN;
    
    if(reg.GetValue() == PCMVERSION)
    {
	state = FEE_STATE_ON;
	
    }
    else if(reg.GetValue() == OLD_PCMVERSION)
    {
      state = FEE_STATE_WARNING;
    }
    else
    {
      state = FEE_STATE_ERROR;
    }
    emit cardChangedState(f, state);
  }

}

void rcu::turnOnTrus::run()
{
  ACTFECLIST actList;
  
  _client->readRcuRegister(&actList);

  //actList.GetRegisterBits().set(TRU_A);
  actList.SetFECActive(BRANCH_A, TRU_SLOT);
  _client->writeRcuRegister(&actList);
  usleep(500000);
  //actList.GetRegisterBits().set(TRU_B);
  actList.SetFECActive(BRANCH_B, TRU_SLOT); // branch A==0, FECCARD
  _client->writeRcuRegister(&actList);
}

int rcu::readRegister(Register* reg) const
{
  if(_feeClient)
  {
    return _feeClient->readRcuRegister(reg);
  }
  PIFATAL("RCU object not initialized.");
  return -1;
}
