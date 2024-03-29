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

#ifndef PHOSCONST_H
#define PHOSCONST_H

namespace PHOS
{

const int RAMP_PATTERN = 0;
const int SAWTOOTH_PATTERN = 1;
const int G2_PATTERN = 2;

const int DEFAULT_APD_DAC_VALUE = 512;
const int EXIST = 0;
const int NO_EXIST = -1;

const int CONFIGINFO_MAX_SIZE = 4096;
const unsigned int MAX_MESSAGE_SIZE = 512;

//register types
const unsigned int REGTYPE_ALTRO = 1;
const unsigned int REGTYPE_BC    = 2;
const unsigned int REGTYPE_RCU   = 3;
const unsigned int REGTYPE_RCU_ACL = 4;
const unsigned int REGTYPE_RCU_MEM = 5;
const unsigned int REGTYPE_TRU     = 6;
const unsigned int REGTYPE_TOR     = 7;
const unsigned int REGTYPE_BUSY    = 8;

//TRU registers
const unsigned int TRU_SLOT  = 0;
const unsigned int TRU_A  = 0;
const unsigned int TRU_B = 16;
const unsigned int TRUS_PER_RCU = 2;
const unsigned long int TRU_REGS_BASE_ADDRESS = 0x72;
const unsigned int N_TRU_REGS = 7;


const unsigned int MAX_RESULT_BUFFER_SIZE = 8192;
const unsigned int MAX_WORD_SIZE =  32; //maximum size in character  of one word in the RCU result buffer

const int N_ZROWS_MOD      =  56;                    /**<Number of rows per module*/
const int N_XCOLUMNS_MOD   =  64;

const int N_ZROWS_BRANCH      =  N_ZROWS_BRANCH/2;                    /**<Number of rows per module*/
const int N_XCOLUMNS_BRANCH   =  N_XCOLUMNS_BRANCH/4;

const unsigned int PHOS_GAINS	= 2;  // Number of gains per one PHOS crystal
const unsigned int HIGH_GAIN    =   1;
const unsigned int LOW_GAIN     =   0;


/*Geometrical constants*/
const unsigned int MODULE_0     = 0;
const unsigned int MODULE_1     = 1;
const unsigned int MODULE_2     = 2;
const unsigned int MODULE_3     = 3;
const unsigned int MODULE_4     = 4;
const unsigned int RCU_0       = 0;
const unsigned int RCU_1       = 1;
const unsigned int RCU_2       = 2;
const unsigned int RCU_3       = 3;
const unsigned int Z_0         = 0;
const unsigned int Z_1         = 1;
const unsigned int X_0         = 0;
const unsigned int X_1         = 1;
enum Branch { BRANCH_A=0, BRANCH_B=0 };
// const unsigned int BRANCH_A    = 0;
// const unsigned int BRANCH_B    = 1;


/*Electronics/Hardware constatns*/
const unsigned int PHOS_MODS	= 5; // Number of PHOS modules
const unsigned int TORS_PER_MODULE = 1;
const unsigned int RCUS_PER_MODULE = 4;   ///// Number of RCUs per Module///
const unsigned int BRANCHES_PER_RCU = 2;
const unsigned int CARDS_PER_BRANCH  = 14; 	// Number of FECs per one RCU branch
const unsigned int CARDS_PER_RCU  = BRANCHES_PER_RCU*CARDS_PER_BRANCH; // Number of FECs per one RCU
const unsigned int ALTROS_PER_FEE    = 4;
const unsigned int CHANNELS_PER_ALTRO = 16;
const unsigned int MAX_CARDS_PER_BRANCH = 16;
const unsigned int MAX_CARDS_PER_RCU =  MAX_CARDS_PER_BRANCH*BRANCHES_PER_RCU;
const unsigned int CSPS_PER_FEE    = 32;

const unsigned int MAX_TRIALS  = 5;
const unsigned int MAX_MESSAGE_LENGTH  = 150;
const unsigned int MAX_LOGVIEWER_LINECOUNT = 300;

const unsigned int TURN_ON = 0;
const unsigned int TURN_OFF = 1;

/*
const signed  int APD_OK = 1;
const signed  int APD_DEAD  = -1;
const signed  int APD_ZERO  = -2;
const signed  int APD_CRAZY = -3;
const signed  int APD_UNKNOWN = 2;
*/

const signed int REG_OK = 1;
const signed int REG_DEAD  = -1;
const signed int REG_ZERO  = -2;
const signed int REG_CRAZY = -3;
const signed int REG_UNKNOWN = 2;


/*FEC status constants*/
enum FecStatus{ FEC_OFF = 1,
		FEC_ON  = 2,
                DCS_NOT_MASTER = 3,
                FEC_UNKNOWN  = 4,
                FEC_ERROR    = 5,
                UNKNOWN_PCMVERSION = 6,
                UNKNOWN_ERROR  = 7,
                FEC_STATE_WARNING = 8 };


/*Firmware version of the PHOS boardcontroller*/
const unsigned long int OLD_PCMVERSION = 0x34;
const unsigned long int PCMVERSION = 0x35;

/*Color constants (used only by GUI)*/
const unsigned long int SELECTED_COLOR  =  0x0000ff; //Blue
const unsigned long int ON_COLOR        =  0x00ff00; //Green
const unsigned long int OFF_COLOR       =  0xffffff; //White
const unsigned long int ERROR_COLOR     =  0xff0000; //Red
const unsigned long int UNKNOWN_COLOR   =  0xaaaaaa; //Gray
const unsigned long int WARNING_COLOR   =  0xffff00; //Yellow


const unsigned int MAX_ALTRO_SAMPLES = 1008;
const unsigned int MAX_ALTRO_PRESAMPLES = 15;
const unsigned int MAX_ZEROSUPRESSION_THR = 500;
const unsigned int MAX_ZEROSUPRESSION_MODE = 7;
const unsigned int MAX_READOUT_MODE = 0xf;
const unsigned int MAX_TRU_SAMPLES = 128;

const unsigned int FEC_RD = 0;

const unsigned int FEC_CMD = 1;
const unsigned int FEC_WR = 2;
const unsigned int RCU_CMND = 3;

const unsigned int CMD_TYPE = 20;   //20=Position of the Commmand type LS bit
const unsigned int PAR = 19;   //19=Position of the parity but
const unsigned int BCAST = 18;   //18=Position of the broadcast register bit. Broadacst=1, no broadcast=0 (ms 20 bits)
const unsigned int BC_AL = 17;   //17=Position of command type bit. Boarcontroller=1, Altro=0
const unsigned int BRANCH_SHIFT = 16;   //Branch A=0, Branch B=1
const unsigned int FAD = 12;   //Poistion of least significant bit of FEE adress register (most significant 20 bits)
const unsigned int REGAD = 8;     //Position of least significant bit of CSP adress register (most significant 20 bits)

const unsigned int CAD = 5;    //Position of least significant bit of CSP adress register (most significant 20 bits)
const unsigned int CSPVAL = 0;   //Position of least significant bit of CSP value  register (least significant 20 bits)

const unsigned int REGVAL = 0;   //Position of least significant bit of CSP value  register (least significant 20 bits)

//PHOS::BC
namespace BC
{
  const unsigned long VERSION = 0x20;
}
}


#endif


