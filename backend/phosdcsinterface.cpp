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
#include "phosdcstypes.h"
#include "rcu.h"
#include "../pilogger/backend/pilogger.h"


using namespace phosDcs;

phosDcsInterface::phosDcsInterface(Rcu_t rcu, QString feeServerName) :
_rcuId(rcu)
,_rcu(0)
,_feeClient(0)
,_feeServerName(feeServerName)
{
  _rcu = new phosDcs::rcu(_rcuId);
}

phosDcsInterface::~phosDcsInterface()
{
}

int phosDcsInterface::init()
{
  return _rcu->init(_feeServerName);
}

int phosDcsInterface::turnOnRcu()
{
  return _rcu->turnOn();
}

int phosDcsInterface::turnOnFec(const Fec_t& fec)
{

}

int phosDcsInterface::turnOnTru(const Tru_t& fec)
{

}

int phosDcsInterface::turnOffRcu()
{

}

int phosDcsInterface::turnOffFec(const Fec_t& fec)
{

}

int phosDcsInterface::turnOffTru(const Tru_t& tru)
{

}

int phosDcsInterface::toggleRcu()
{

}

int phosDcsInterface::toggleFec(const Fec_t& fec)
{

}

int phosDcsInterface::toggleTru(const Tru_t& tru)
{

}

int phosDcsInterface::readRegister(Register* r) const
{
  if(_rcu)
  {
    return _rcu->readRegister(r);
  }
  PIFATAL("RCU object not initialized.");
}
