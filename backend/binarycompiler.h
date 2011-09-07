#ifndef BINARYCOMPILER_H
#define BINARYCOMPILER_H

#include <vector>
#include <string>
#include "phosdcstypes.h"
#include <qglobal.h>

using namespace std;

class binaryCompiler
  {
  public:
    binaryCompiler();
    ~binaryCompiler();

    /**
     * Write to a continious block of RCU memory and read it back
     * @param regAdd is the register base address
     * @param regVal contains the values to write
     * @param binData is a vector which will be filled the generated code
     * @param nVal is the value number of registers to write
     * @return 0 if success
     */
    int MakeWriteReadRcuBlock(uint_t regAdd, std::vector<uint_t>& regVal, std::vector<uint_t>& binData, uint_t nVal);

    /**
     * Write a value to an RCU register and read it back
     * @param regAdd is the register address
     * @param regVal is the value to write
     * @param binData is a vector which will be filled the generated code
     * @return 0 if success
     */
    int MakeWriteReadRcuRegister(uint_t regAdd, uint_t regVal, std::vector<uint_t>& binData);
    
    /**
     * Read a continious block of RCU registers
     * @param regAdd is the register base address
     * @param binData is a vector which will be filled the generated code
     * @param nVal is the value number of registers to read
     * @return 0 if success
     */
    int MakeReadRcuBlock(uint_t regAdd, std::vector<uint_t>& binData, uint_t nVal);

    /** 
     * Read an RCU register
     * @param regAdd is the register address
     * @param binData is a vector which will be filled the generated code
     * @return 0 if success
     */
    int MakeReadRcuRegister(uint_t regAdd, std::vector<uint_t>& binData);

    /**
     * Read the result memory
     * @param binData contains the generated code
     * @param nVal is the number of values to read back
     * @return 0 if success
     */
    int MakeReadResultMemory ( std::vector<uint_t> & binData, uint_t nVal );

    /**
     * Write to several registers on a FEC and read back the result
     * @param registerType REGTYPE_ALTRO or REGTYPE_BC
     * @param regAdds contains the addresses we will write
     * @param regVals contains the values we will write
     * @param channel is the channel ID we want to write to (contains only the FEC ID if BC reg)
     * @param binData will contain the generated code
     * @param nVals is the number of registers to write
     * @return 0 if success
     */
    int MakeWriteFecRegisters(int registerType, std::vector<uint_t> regAdds, std::vector<uint_t>& regVals, AltroCh_t channel, std::vector<uint_t> binData, uint_t nVals);
    
    /**
     * Read several registers on a FEC and read back the result
     * @param registerType REGTYPE_ALTRO or REGTYPE_BC
     * @param regAdds contains the addresses we will write
     * @param channel is the channel ID we want to write to (contains only the FEC ID if BC reg)
     * @param binData will contain the generated code
     * @param nVals is the number of registers to write
     * @return 0 if success
     */
    int MakeReadFecRegisters(int registerType, std::vector<uint_t> regAdds, AltroCh_t channel, vector<uint_t> binData, uint_t nVals);
    
    /** 
     * Write to several ALTRO registers
     * @param regAdds contains the addresses we will write
     * @param regVals contains the values we will write
     * @param channel is the channel ID we want to write to
     * @param binData will contain the generated code
     * @param nVals is the number of registers to write
     * @return 0 if success
     */
    int MakeWriteReadAltroRegisters(std::vector<uint_t>& regAdds, std::vector<uint_t>& regVals, AltroCh_t channel, std::vector<uint_t> binData, uint_t nVals);
    
    /** 
     * Write to several board controller registers
     * @param regAdds contains the addresses we will write
     * @param regVals contains the values we will write
     * @param binData will contain the generated code
     * @param nVals is the number of registers to write
     * @return 0 if success
     */
    int MakeWriteReadBCRegisters(std::vector<uint_t> regAdds, std::vector<uint_t>& regVals, Fec_t card, std::vector<uint_t> binData, uint_t nVals);
    
    
  private:

  };

#endif
