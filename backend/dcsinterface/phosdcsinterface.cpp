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
#include "rcu.h"
#include "../pilogger/backend/pilogger.h"
#include <bc/bcversion.h>
#include <QString>

#include "idtypes.h"
#include "phosconstants.h"
using namespace PHOS;

#include <sstream>
using namespace std;


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
int PhosDcsInterface::turnOnOffFec(const FecID& fec, FecStatus newStatus)
{
  if(lastACTFECLIST == 0 ) {
    lastACTFECLIST = new ACTFECLIST(0x0);
    _feeClient->readRcuRegister(lastACTFECLIST);
    PIINFO("ACTFECLIST Read: 0x%X", lastACTFECLIST->GetValue());
  }

  // Warn if last know if same status as last known ACTFECLIST
  if(FEC_ON == newStatus && lastACTFECLIST->GetFECActive(fec.getBranchId(), fec.getFecId()))
    phosDcsLogging::Instance()->Logging("PhosDcsInterface::turnOnOffFec: request fec on, when last known fec already on", LOG_LEVEL_WARNING);
  if(FEC_OFF == newStatus && lastACTFECLIST->GetFECActive(fec.getBranchId(), fec.getFecId()))
    phosDcsLogging::Instance()->Logging("PhosDcsInterface::turnOnOffFec: request fec off, when last known fec already off", LOG_LEVEL_WARNING);

  // set new status 
  lastACTFECLIST->SetFECActive(fec.getBranchId(), fec.getFecId(), FEC_ON==newStatus);

  // Write new status
  int error = _feeClient->writeFecRegister(lastACTFECLIST);

  if( !error ) { // if no error
    // Check BC version
    BCVERSION bcvReg(0x0);
    _feeClient->readBcRegister(&bcvReg, &fec);
    if(BC::VERSION == bcvReg ) { // BCVERSION should equal
      stringstream ss("wrote ACFECLIST(");
      ss << std::hex << *lastACTFECLIST << ")" << " to rcu" << endl;
      emit updatedFecStatus(fec, newStatus, QString(ss.str().c_str()));
      return 0; // sucess;
    }
    else { // different, assume card is in state of error.
      stringstream message;
      message << "FEC (" << ") did not return correct BCVERSION (" << endl;
      phosDcsLogging::Instance()->Logging("error", LOG_LEVEL_ERROR);
      emit updatedFecStatus(fec, FEC_ERROR, message.str().c_str());
      return 1; // error
    }
  }
  else { // error in reading of Writing of ACTFECLIST.
    // TODO: consider error
    delete lastACTFECLIST;
    return error;
  }
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

  // Loop over fec cards
  for(int bidx = 0; bidx < 2; ++bidx) { // Branch Index
    for(int fidx = 1; fidx <= CARDS_PER_BRANCH; ++fidx) { // Fec Index
      FecID fecID(fidx, bidx, _rcuId);
      if( lastACTFECLIST->GetFECActive(bidx, fidx) )
      {
	BCVERSION bcvReg(0x0);
	_feeClient->readBcRegister(&bcvReg, &fecID);

	// Check BC version
	if(BC::VERSION != bcvReg ) { // if different, assume card is in state of error.
	  stringstream message;
	  message << "FEC (" << ") did not return correct BCVERSION (" << endl;
	  phosDcsLogging::Instance()->Logging("error", LOG_LEVEL_ERROR);
	  emit updatedFecStatus(fecID, FEC_ERROR, message.str().c_str());
	  continue;
	}

	//if this point is reached, assume card is not in state of error, and thus on
	emit updatedFecStatus(fecID, FEC_ON, "no error found, assume FEC is on.");
      }
      else // if not lastACTFECLIST->GetFECActive
      {
	emit updatedFecStatus(fecID, FEC_OFF, "ACTEFLIST of rcu sugest FEC is Off");
      }
    }
  }
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
  //TODO: implement
}


#include "phosdcsinterface.moc"