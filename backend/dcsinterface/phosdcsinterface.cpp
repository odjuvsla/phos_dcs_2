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
,_rcu(0)
,_feeClient(0)
,lastACTFECLIST(0)
{
  _rcu = new phosDcs::rcu(_rcuId);
}

PhosDcsInterface::~PhosDcsInterface()
{
  //TODO: implement cleanup!!!
}

int PhosDcsInterface::connect(const QString& feeServerName)
{
  //int error =_rcu->init(feeServerName);
  _feeClient = new PhosDcsClient(feeServerName);
}

int PhosDcsInterface::turnOnOffFec(const FecID& fec, bool turnOn)
{
  if(lastACTFECLIST == 0 ) {
    lastACTFECLIST = new ACTFECLIST(0x0);
    _feeClient->readRcuRegister(lastACTFECLIST);
    PIINFO("ACTFECLIST Read: 0x%X", lastACTFECLIST->GetValue());
  }
  //lastACTFECLIST->SetFECActive(fec.getBranchId(), fec.getFecId(), turnOn);
  //_feeClient->writeFecRegister();
    
}

int PhosDcsInterface::turnOnOffTru(const TruID& tru, bool turnOn)
{

}


int PhosDcsInterface::readRegister(Register* r) const
{
  if(_rcu)
  {
    return _rcu->readRegister(r);
  }
  PIFATAL("RCU object not initialized.");
}

#include "phosdcsinterface.moc"