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

#ifndef RCU_H
#define RCU_H
#include <phosdcstypes.h>
#include "phosdcsclient.h"
#include "fec.h"
#include <QThread>

namespace phosDcs
{
class rcu
{
public:
  
    rcu(Rcu_t rcu);
    virtual ~rcu();
    
    /** Initialise the FEE client */
    int init(QString feeServerName);
    
    /** Turn on the RCU */
    int turnOn(bool on = true);
    
    /** Turn on the RCU */
    int turnOff() { turnOn(false); }
    
signals:
  
    void cardChangedState(phosDcs::fec card, int state);
    
private:
  

    class turnOnFecs : public QThread
    {
      Q_OBJECT
    public:
      
      /** Set FEE client to use */
      void setFeeClient(phosDcsClient *client) { _client = client; }
	
      /** Set the branches */
      void setBranches(std::vector<phosDcs::fec>* branchA, std::vector<phosDcs::fec>* branchB) 
      { _branchA = branchA;  _branchB  = branchB; }
      
      /** on is false if we turn off... */
      void setOn(bool on) { _on = on; }
      
      void run();

    signals:
  
    void cardChangedState(Fec_t card, int state);
      
    private:
      
      phosDcsClient *_client;
      
      std::vector<phosDcs::fec> *_branchA;
      std::vector<phosDcs::fec> *_branchB;
      
      bool _on;
      
    };

    class turnOnTrus : public QThread
    {
      Q_OBJECT
    public:
      void run();

      /** Set FEE client to use */
      void setFeeClient(phosDcsClient *client) { _client = client; }
      
    private:
      
      phosDcsClient *_client;
      
    };

    
    /** The RCU id */
    Rcu_t _rcuId;
  
    /** DCS client */
    phosDcsClient *_feeClient;
    
    /** Vector with the FECs on branch A */
    std::vector<phosDcs::fec> _fecsBranchA;
  
    /** Vector with the FECs on branch B */
    std::vector<phosDcs::fec> _fecsBranchB;
  
    /** Prohibited */
    rcu();
    rcu(const rcu& other);
    rcu& operator=(const rcu& other);
    bool operator==(const rcu& other) const;
};
}

#endif // RCU_H
