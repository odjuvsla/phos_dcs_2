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

#ifndef PHOSDCSTYPES_H
#define PHOSDCSTYPES_H

#include "phosconstants.h"
#include "phosdcslogging.h"
#include <sstream>
#include <cstdlib>

typedef unsigned int uint_t;
typedef unsigned short ushort_t;
typedef unsigned long ulong_t;

using namespace phosConstants;

/** Module ID */
class ModuleID
{
public:

    /** Constructor checks value
     * @param id [0,4]
     */
    ModuleID(ushort_t id):
            fModuleId(id)
    {
        if (id >= PHOS_MODS)
        {
            std::stringstream log;

            log << "Module number: " << id << " is not valid (0 - 4 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fModuleId = id;
    }

    virtual ~ModuleID() {;}

    /** @return Module ID [0,4]*/
    short getModuleId() {
        return fModuleId;
    }

private:
    short fModuleId;

    /** Default constructor disallowed */
    ModuleID();

};

/** ID of RCU and Module */
class RcuID : public ModuleID

{
public:
    /** Constructor checks value
     * @param rcuID [0,3]
     * @param modID [0,4]
     */
    RcuID(ushort_t rcuID, ushort_t modID)
    : ModuleID(modID),
      fRcuId(rcuID)
    {
        if (rcuID >= RCUS_PER_MODULE)
        {
            std::stringstream log;

            log << "Rcu number: " << rcuID << " is not valid (0 - 3 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fRcuId = rcuID;
    }

    /** @return RCU ID [0,3]*/
    short getRcuId() {
        return fRcuId;
    }

private:
    short fRcuId;

    /** Default constructor disallowed */
    RcuID();

};

/** ID of Branch, RCU, and Module */
class BranchID : public RcuID
{
public:
    /** Constructor checks value
      * @param id [0,1]
      * @param rcuID [0,3]
      * @param modID [0,4]
      */
    BranchID(ushort_t id, ushort_t rcuID, ushort_t modID) : RcuID(rcuID, modID),
            fBranchId(id)
    {
        if (id >= BRANCHES_PER_RCU)
        {
            std::stringstream log;

            log << "Branch number: " << id << " is not valid (0 or 1 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fBranchId = id;
    }
    /** @return Branch ID [0,1] */
    ushort_t getBranchId() {
        return fBranchId;
    }

private:
    ushort_t fBranchId;

    /** Default constructor disallowed */
    BranchID();

};

/** ID of FEC, Branch, RCU, and Module */
class FecID : public BranchID
{
public:
    /** Constructor checks value
     * @param id [1,14]
     * @param branchID [0,1]
     * @param rcuID [0,3]
     * @param modID [0,4]
     */
    FecID(ushort_t id, ushort_t branchID, ushort_t rcuID, ushort_t modID) : BranchID(branchID, rcuID, modID),
            fFecId(id)
    {
        if (id > CARDS_PER_BRANCH && id >0)
        {
            std::stringstream log;

            log << "Card number: " << id << " is too high (there are " << CARDS_PER_BRANCH << " cards per branch, card 0 is TRU), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fFecId = id;
    }

    /** @return FEC ID [1,14] */
    ushort_t getFecId() {
        return fFecId;
    }

private:
  
    ushort_t fFecId;

    /** Default constructor disallowed */
    FecID();
};

/** ID of TRU(Branch), RCU, and Module */
class TruID : public BranchID
{
public:
      /** Constructor checks value
       * @param id [1,14], both TRU and Branch
       * @param rcuID [0,3]
       * @param modID [0,4]
       */
    TruID(ushort_t id, ushort_t rcuID, ushort_t modID) : BranchID(id, rcuID, modID),
            fTruId(id)
    {
        if (id >= TRUS_PER_RCU)
        {
            std::stringstream log;
            log << "TRU number: " << id << " is too high (there are " << TRUS_PER_RCU << " TRUs per RCU, card 0 is TRU), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
    }

    /** @return TRU ID [0,1] */
    ushort_t getTruId() {
        return fTruId;
    }

    /** @return Corresponding FEC Register {0,16} */
    ushort_t getFECRegister() {
        return fTruId*16;
    }
private:

    ushort_t fTruId;

    TruID();
};

/** ID of FEC, Branch, RCU, and Module */
class AltroID : public FecID
{
public:
    /** Constructor checks value
     * @param id {0,2,3,4}
     * @param fecID [1,14]
     * @param branchID [0,1]
     * @param rcuID [0,3]
     * @param modID [0,4]
     */
    AltroID(ushort_t id, ushort_t fecID, ushort_t branchID, short rcuID, short modID) : FecID(fecID, branchID, rcuID, modID),
            fChipId(id)
    {
        if (id > ALTROS_PER_FEE || id == 1)
        {
            std::stringstream log;

            log << "ALTRO chip number: " << id << " is not allowed (0, 2, 3, 4 are accepted), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fChipId = id;
    }

    /** @return ALTRO ID {0,2,3,4} */
    ushort_t getAltroID() {
        return fChipId;
    }

private:
    ushort_t fChipId;

    /** Default constructor disallowed */
    AltroID();

};

class AltroChannelID : public AltroID
{

public:
    /** Constructor checks value
     * @param id {0} U [2,16]
     * @param altroID {0,2,3,4}
     * @param fecID [1,14]
     * @param branchID [0,1]
     * @param rcuID [0,3]
     * @param modID [0,4]
     */
    AltroChannelID(ushort_t id, ushort_t altroID, ushort_t fecID, ushort_t branchID, short rcuID, short modID) : AltroID(altroID, fecID, branchID, rcuID, modID),
            fChannelId(id)
    {
        if (id > CHANNELS_PER_ALTRO || id == 1)
        {
            std::stringstream log;

            log << "ALTRO channel: " << id << " is not allowed (must be less than: " << CHANNELS_PER_ALTRO << "), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fChannelId = id;
    }

    /** @return ALTRO Channel {0} U [2,16] */
    ushort_t getAltroChannelID() {
        return fChannelId;
    }

private:

    /** The channel number */
    ushort_t fChannelId;

    /** Default constructor disallowed */
    AltroChannelID();

};

struct FeeServer_t
{
    std::string fName;
    int fModId;
    int fRcuId;
    int fZ;
    int fX;
};

#endif

