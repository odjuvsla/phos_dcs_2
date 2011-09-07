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
    Module_t(short id)
    {
        if (id >= PHOS_MODS)
        {
            std::stringstream log;

            log << "Mdoule number: " << id << " is too high (0 - 4 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
            exit(-1);
        }
        fModuleId = id;
    }

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
    Rcu_t(short id, short modId) : Module_t(modId)
    {
        if (id >= BRANCHES_PER_RCU)
        {
            std::stringstream log;

            log << "Rcu number: " << id << " is too high (0 - 4 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
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
    Branch_t(ushort_t id, short rcuId = -1, short modId = -1) : Rcu_t(rcuId, modId)
    {
        if (id >= BRANCHES_PER_RCU)
        {
            std::stringstream log;

            log << "Branch number: " << id << " is too high (0 or 1 is allowed), exiting...";
            phosDcsLogging::Instance()->Logging(log.str(), LOG_LEVEL_ERROR);
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

    Fec_t(ushort_t id, ushort_t branch, short rcu = -1, short mod = -1) : Branch_t(branch, rcu, mod)
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

class Chip_t : public Fec_t
{
public:
    /** Constructor checks value */
    Chip_t(ushort_t id, ushort_t fecId, ushort_t branchId, short rcuId = -1, short modId = -1) : Fec_t(fecId, branchId, rcuId, modId)
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
    AltroCh_t(ushort_t id, ushort_t chipId, ushort_t fecId, ushort_t branchId, short rcuId = -1, short modId = -1) : Chip_t(chipId, fecId, branchId, rcuId, modId)
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
  
#endif
