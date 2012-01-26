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

class PhosDcsInterface : public QObject
{

  Q_OBJECT
public:
  
    /** Constructor takes RCU id as input */
    PhosDcsInterface(RcuID rcu, QString feeServerName);
    
    /** Destructor */
    virtual ~PhosDcsInterface();

public slots:
    /** Initilise the interface */
    int init();
    
    /** Turn on the FECs on the RCU */
    int turnOnRcu();
    
    /** Turn on a single FEC on the RCU */
    int turnOnFec(const FecID &fec);
    
    /** Turn on a single TRU on the RCU */
    int turnOnTru(const TruID &tru);
    
    /** Turn off the FECs on the RCU */
    int turnOffRcu();
    
    /** Turn off a single FEC on the RCU */
    int turnOffFec(const FecID &fec);
    
    /** Turn off a single TRU on the RCU */
    int turnOffTru(const TruID &tru);
    
    /** Toggle on/off the FECs on the RCU */
    int toggleRcu();
    
    /** Toggle on/off a single FEC on the RCU */
    int toggleFec(const FecID &fec);
    
    /** Toggle on/off a TRU on the RCU */
    int toggleTru(const TruID &tru);
    
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
  
    /** Our RCU object */
    phosDcs::rcu *_rcu;
    
    /** Pointer to the FEE client */
    PhosDcsClient *_feeClient;
    
    /** Name of the FEE server */
    QString _feeServerName;
    
    /** Prohibited */
    PhosDcsInterface();
    PhosDcsInterface(const PhosDcsInterface& other);
    PhosDcsInterface& operator=(const PhosDcsInterface& other);
    bool operator==(const PhosDcsInterface& other) const;
};

#endif // PHOSDCSINTERFACE_H
