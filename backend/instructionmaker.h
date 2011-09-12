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

#ifndef INSTRUCTIONMAKER_H
#define INSTRUCTIONMAKER_H
#include <phosdcstypes.h>

class InstructionMaker
  {
  public:

    InstructionMaker() {}
    ~InstructionMaker() {}

    /** changed for RCU_fw2 (maybe incomplete/incorrect) */
    static unsigned long  MakeMS20Instruction ( const uint_t registerType, const bool read,
        const unsigned long reg, const unsigned long  branch = 0,
        const unsigned long card = 0, const unsigned long chip = 0, const unsigned long channel = 0 );


    /**
     * @param read flag if this is a read operation
     * @param registerValue the value too write
     */
    static unsigned long  MakeLS20Instruction ( const bool read,  const unsigned long registerValue );
  };
#endif
