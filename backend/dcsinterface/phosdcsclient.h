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

#ifndef PHOSDCSCLIENT_H
#define PHOSDCSCLIENT_H

#include "register.h"
#include "phosregisters.h"
#include "idtypes.h"
#include "binarycompiler.h"
//#pragma GCC diagnostic ignored "-Weffc++"
#include "FeeSampleClient.hpp"
//#pragma GCC diagnostic error "-Weffc++"

class QMutex;

using namespace dcs;
using namespace dcs::fee;

class PhosDcsClient : public FeeSampleClient
{

public:

    /** Default constructor */
    PhosDcsClient(QString feeServerName);

    /** Destructor */
    virtual ~PhosDcsClient();

    /** Write an RCU register */
    int writeRcuRegister(Register *reg);

    /** Write a FEC register */
    int writeFecRegister(Register *reg, AltroChannelID *ch = 0);

    /** Read an RCU register */
    int readRcuRegister(Register *reg);

    /** Read a FEC register */
    int readFecRegister(Register *reg, AltroChannelID *ch = 0);

    /** Read a board contoller register on a FEC */
    int readBcRegister(Register *reg, FecID *fec = 0);

private:

    int executeBinary(const vector<uint_t> & binData, vector<uint_t> &  resultBuffer );
    
    /** Mutex lock */
    QMutex *_mutex;

    /** Binary compiler */
    binaryCompiler *_binaryCompiler;
    
    /** FEE server name */
    QString _feeServerName;
      
    /** Default constructor, prohibited */
    PhosDcsClient();
    
    /** Copy constructor, prohibited */
    PhosDcsClient(const PhosDcsClient& other);

    /** Assignement operator, prohibited */
    PhosDcsClient& operator=(const PhosDcsClient& other);
};

#endif // PHOSDCSCLIENT_H
