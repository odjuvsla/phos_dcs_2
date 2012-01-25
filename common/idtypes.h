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
#include <string.h>

typedef unsigned int uint_t;
typedef unsigned short ushort_t;
typedef unsigned long ulong_t;


/** Module ID */
class ModuleID
{
public:

    /** Constructor checks value
     * @param id [0,4]
     */
    ModuleID(ushort_t id)
      : moduleId(id)
      { testModuleID(moduleId); }
      

    ModuleID(const ModuleID& other)
      : moduleId(other.moduleId)
      {;}

    virtual ~ModuleID() {;}

    /** @return Module ID [0,4]*/
    ushort_t getModuleId()
      { return moduleId; }

    static void testModuleID(ushort_t id) {
        if ( id >= PHOS::PHOS_MODS) {
            std::stringstream log;

            log << "Module number: " << id << " is not valid (0 - 4 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
    }

    virtual std::string toString() {
      std::stringstream ss;
      ss << "id_mod:" << moduleId;
      return ss.str();
    }
 
private:
    ushort_t moduleId;

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
      : ModuleID(modID), rcuID(rcuID)
      {testRcuID(rcuID);}
    
    /** Constructor checks value
     * @param rcuID [0,3]
     */
    RcuID(ushort_t rcuID, const ModuleID& modID)
      : ModuleID(modID), rcuID(rcuID)
      {testRcuID(rcuID);}

    RcuID(const RcuID& other)
      : ModuleID(other), rcuID(other.rcuID)
      {;}

    /** @return RCU ID [0,3]*/
    ushort_t getRcuId() {
        return rcuID;
    }

    static void testRcuID(bool rcuID) {
      if (rcuID >= PHOS::RCUS_PER_MODULE) {
        std::stringstream log;
        log << "Rcu number: " << rcuID << " is not valid (0 - 3 is allowed), exiting...";
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
        exit(-1);
      }
    }

    virtual std::string toString() {
      std::stringstream ss(ModuleID::toString());
      ss << "_rcu:" << rcuID;
      return ss.str();
    }

private:
    ushort_t rcuID;

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
    BranchID(ushort_t id, ushort_t rcuID, ushort_t modID)
      : RcuID(rcuID, modID), branchId(id)
      { testBranchID(branchId);}

    /** Constructor checks value
      * @param id [0,1]
      */
    BranchID(ushort_t id, const RcuID& other)
      : RcuID(other), branchId(id)
      { testBranchID(id); }

    BranchID(const BranchID& other)
      : RcuID(other), branchId(other.branchId)
      {;}
	    
    /** @return Branch ID [0,1] */
    ushort_t getBranchId() {
        return branchId;
    }

    static void testBranchID(ushort_t branchID) {
      if (branchID >= PHOS::BRANCHES_PER_RCU) {
        std::stringstream log;
        log << "Branch number: " << branchID << " is not valid (0 or 1 is allowed), exiting...";
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
        exit(-1);
      }
    }
    
    virtual std::string toString() {
      std::stringstream ss(RcuID::toString());
      ss << "_brc:" << branchId;
      return ss.str();
    }

private:
    ushort_t branchId;

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
    FecID(ushort_t id, ushort_t branchID, ushort_t rcuID, ushort_t modID)
      : BranchID(branchID, rcuID, modID), fecID(id)
	{testFecID(fecID);}

   /** Constructor checks value
     * @param id [1,14]
     */
    FecID(ushort_t id, const BranchID& other)
      : BranchID(other), fecID(id)
	{testFecID(fecID);}

    FecID(const FecID& other)
      : BranchID(other), fecID(other.fecID)
      {;}


    /** @return FEC ID [1,14] */
    ushort_t getFecId() {
        return fecID;
    }

    static void testFecID(ushort_t id) {
      if (id > PHOS::CARDS_PER_BRANCH || id ==0) {
        std::stringstream log;
        log << "Card number: " << id << " is out of bounds: [1," << PHOS::CARDS_PER_BRANCH << "] (card 0 is TRU), exiting...";
        phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
        exit(-1);
      }
    }

    virtual std::string toString() {
      std::stringstream ss(BranchID::toString());
      ss << "_fec:" << fecID;
      return ss.str();
    }

private:
  
    ushort_t fecID;

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
        if (id >= PHOS::TRUS_PER_RCU)
        {
            std::stringstream log;
            log << "TRU number: " << id << " is too high (there are " << PHOS::TRUS_PER_RCU << " TRUs per RCU, card 0 is TRU), exiting...";
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

    virtual std::string toString() {
      std::stringstream ss(BranchID::toString());
      ss << "_tru:" << fTruId;
      return ss.str();
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
    AltroID(ushort_t id, ushort_t fecID, ushort_t branchID, ushort_t rcuID, ushort_t modID) : FecID(fecID, branchID, rcuID, modID),
            fChipId(id)
    {
        if (id > PHOS::ALTROS_PER_FEE || id == 1)
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

    virtual std::string toString() {
      std::stringstream ss(FecID::toString());
      ss << "_altro:" << fChipId;
      return ss.str();
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
    AltroChannelID(ushort_t id, ushort_t altroID, ushort_t fecID, ushort_t branchID, ushort_t rcuID, ushort_t modID) : AltroID(altroID, fecID, branchID, rcuID, modID),
            fChannelId(id)
    {
        if (id > PHOS::CHANNELS_PER_ALTRO || id == 1)
        {
            std::stringstream log;

            log << "ALTRO channel: " << id << " is not allowed (must be less than: " << PHOS::CHANNELS_PER_ALTRO << "), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fChannelId = id;
    }

    /** @return ALTRO Channel {0} U [2,16] */
    ushort_t getAltroChannelID() {
        return fChannelId;
    }

    virtual std::string toString() {
      std::stringstream ss(AltroID::toString());
      ss << "_cha:" << fChannelId;
      return ss.str();
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

