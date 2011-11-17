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


class Module_t
{
public:

    /** Constructor checks value */
    Module_t(ushort_t id):
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

    virtual ~Module_t() {}

    short getModuleId() {
        return fModuleId;
    }

private:
    short fModuleId;

    /** Default constructor disallowed */
    Module_t();

};

class Rcu_t : public Module_t

{
public:
    /** Constructor checks value */
    Rcu_t(ushort_t id, short modId) : Module_t(modId),
            fRcuId(id)
    {
        if (id >= RCUS_PER_MODULE)
        {
            std::stringstream log;

            log << "Rcu number: " << id << " is not valid (0 - 4 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fRcuId = id;
    }

    short getRcuId() {
        return fRcuId;
    }

private:
    short fRcuId;

    /** Default constructor disallowed */
    Rcu_t();

};

class Branch_t : public Rcu_t
{
public:
    /** Constructor checks value */
    Branch_t(ushort_t id, short rcuId, short modId) : Rcu_t(rcuId, modId),
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

    ushort_t getBranchId() {
        return fBranchId;
    }

private:
    ushort_t fBranchId;

    /** Default constructor disallowed */
    Branch_t();

};

class Fec_t : public Branch_t
{
public:

    Fec_t(ushort_t id, ushort_t branch, short rcu, short mod) : Branch_t(branch, rcu, mod),
            fFecId(id)
    {
        if (id > CARDS_PER_BRANCH)
        {
            std::stringstream log;

            log << "Card number: " << id << " is too high (there are " << CARDS_PER_BRANCH << " cards per branch, card 0 is TRU), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR, __FILE__, __LINE__);
            exit(-1);
        }
        fFecId = id;
    }

    ushort_t getFecId() {
        return fFecId;
    }

private:
  
    ushort_t fFecId;

    /** Default constructor disallowed */
    Fec_t();
};

class Tru_t : public Fec_t
{
public:
    Tru_t(ushort_t id, short rcu, short mod) : Fec_t(id*(CARDS_PER_BRANCH+2), id, rcu, mod),
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
    ushort_t getTruId() {
        return fTruId;
    }
private:

    ushort_t fTruId;

    Tru_t();
};

class Chip_t : public Fec_t
{
public:
    /** Constructor checks value */
    Chip_t(ushort_t id, ushort_t fecId, ushort_t branchId, short rcuId, short modId) : Fec_t(fecId, branchId, rcuId, modId),
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

    ushort_t getChipId() {
        return fChipId;
    }

private:
    ushort_t fChipId;

    /** Default constructor disallowed */
    Chip_t();

};

class AltroCh_t : public Chip_t
{

public:
    /** Constructor checks value */
    AltroCh_t(ushort_t id, ushort_t chipId, ushort_t fecId, ushort_t branchId, short rcuId, short modId) : Chip_t(chipId, fecId, branchId, rcuId, modId),
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

    ushort_t getChId() {
        return fChannelId;
    }

private:

    /** The channel number */
    ushort_t fChannelId;

    /** Default constructor disallowed */
    AltroCh_t();

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
