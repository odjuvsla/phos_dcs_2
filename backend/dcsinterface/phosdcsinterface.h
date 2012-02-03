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

#ifndef PHOSDCSINTERFACE_H
#define PHOSDCSINTERFACE_H

#include "idtypes.h"
#include "phosdcsclient.h"
#include "phosreadoutsettings.h"

#include <string>
#include "rcu.h"
#include <actfeclist.h>

class PhosDcsInterface : public QObject
{
  Q_OBJECT
  
public:
  
    /** Constructor takes RCU id as input */
    PhosDcsInterface(const RcuID& rcu);
    
    /** Destructor */
    virtual ~PhosDcsInterface();

public slots:
    /** Connect/Initilise the interface */
    int connect(const QString& feeServerName);

    /* turn resources on/off*/
    int turnOnOffFec(const FecID &fec, bool turnOn);
    
    int turnOnOffTru(const TruID &tru, bool turnOn);

    int updateActiveFec();

    /** Apply APD settings for the RCU */
    int applyApdSettings() const;
    
    /** Apply APD settings for a FEC on the RCU */
    int applyApdSettings(const FecID &fec) const;
    
    /** Apply the read out registers */
    int applyReadoutSettings(const ReadoutSettings_t &readoutSettings ) const;
    
    /** Read an  RCU register */
    int readRegister(Register *r) const;

    
private:

    /** Which RCU do we handle */
    RcuID _rcuId;
  
    /** Pointer to the FEE client */
    PhosDcsClient *_feeClient;

    /** Last known ACTFECLIST */
    ACTFECLIST* lastACTFECLIST;
    
    /** Prohibited */
    PhosDcsInterface();
    PhosDcsInterface(const PhosDcsInterface& other);
    PhosDcsInterface& operator=(const PhosDcsInterface& other);
    bool operator==(const PhosDcsInterface& other) const;
};

#endif // PHOSDCSINTERFACE_H
