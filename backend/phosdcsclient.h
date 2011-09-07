#ifndef PHOSDCSCLIENT_H
#define PHOSDCSCLIENT_H

#include "phosregisters.h"
#include "phosdcstypes.h"
#include "binarycompiler.h"
#include "FeeSampleClient.hpp"

using namespace dcs;
using namespace dcs::fee;

class phosDcsClient : public FeeSampleClient
{

public:

    /** Default constructor */
    phosDcsClient();

    /** Destructor */
    virtual ~phosDcsClient();

    /** Write an RCU register */
    int writeRcuRegister(Register_t *reg = 0);

    /** Write a FEC register */
    int writeFecRegister(Register_t *reg = 0, AltroCh_t *ch = 0);

private:

    int ExecuteBinary( const char* feeServerName, const vector<unsigned long> & binData, vector<unsigned long> &  resultBuffer );

    /** Binary compiler */
    binaryCompiler *fBinaryCompiler;

    /** Copy constructor, prohibited */
    phosDcsClient(const phosDcsClient& other);

    /** Assignement operator, prohibited */
    phosDcsClient& operator=(const phosDcsClient& other);
};

#endif // PHOSDCSCLIENT_H
