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

#include "phosregisters.h"
#include <iostream>

const unsigned long ReadoutRegisters_t::fRcuRegisterAddresses[] = { RcuALTROIF_t::fRegAddress,
        RcuRDOMOD_t::fRegAddress,
        RcuALTROCFG1_t::fRegAddress,
        RcuALTROCFG2_t::fRegAddress,
        RcuL1LAT_t::fRegAddress,
        RcuL1MSGLAT_t::fRegAddress
                                                                  };
const unsigned long ReadoutRegisters_t::fAltroRegisterAddresses[] = { AltroZSTHR_t::fRegAddress,
        AltroTRCFG_t::fRegAddress,
        AltroDPCFG_t::fRegAddress,
        AltroDPCFG2_t::fRegAddress
                                                                    };
const bool ReadoutRegisters_t::fRcuVerify[] = {false, false, false, false, false, false};

const bool ReadoutRegisters_t::fAltroVerify[] = {false, false, false, false};

ReadoutRegisters_t::ReadoutRegisters_t ( RcuALTROIF_t altroif, RcuRDOMOD_t rdoMod, RcuALTROCFG1_t altrocfg1,
        RcuALTROCFG2_t altrocfg2, RcuL1LAT_t lOneLat, RcuL1MSGLAT_t lOneMsgLat ) :
        fRcuALTROIF(),
	fRcuRDOMOD(),
	fRcuALTROCFG1(),
	fRcuALTROCFG2(),
	fRcuL1LAT(),
	fRcuL1MSGLAT(),
	fAltroZSTHR(),
	fAltroTRCFG(),
	fAltroDPCFG(),
	fAltroDPCFG2()

{
    SetRcuALTROIF ( altroif );
    SetRcuRDOMOD ( rdoMod );
    SetRcuALTROCFG ( altrocfg1, altrocfg2 );
    SetRcuL1LAT ( lOneLat );
    SetRcuL1MSGLAT ( lOneMsgLat );
}

const unsigned long* ReadoutRegisters_t::GetRcuRegisterValues()
{
    fRcuRegisterValues[0] = fRcuALTROIF.GetRegisterValue();
    fRcuRegisterValues[1] = fRcuRDOMOD.GetRegisterValue();
    fRcuRegisterValues[2] = fRcuALTROCFG1.GetRegisterValue();
    fRcuRegisterValues[3] = fRcuALTROCFG2.GetRegisterValue();
    fRcuRegisterValues[4] = fRcuL1LAT.GetRegisterValue();
    fRcuRegisterValues[5] = fRcuL1MSGLAT.GetRegisterValue();

    return fRcuRegisterValues;
}

const unsigned long* ReadoutRegisters_t::GetAltroRegisterValues()
{
    fAltroRegisterValues[0] = fAltroZSTHR.GetRegisterValue();
    fAltroRegisterValues[1] = fAltroTRCFG.GetRegisterValue();
    fAltroRegisterValues[2] = fAltroDPCFG.GetRegisterValue();
    fAltroRegisterValues[3] = fAltroDPCFG2.GetRegisterValue();
    return fAltroRegisterValues;
}

void ReadoutRegisters_t::SetRcuALTROIF ( RcuALTROIF_t altroif )
{
    fRcuALTROIF = altroif;
    fAltroTRCFG.SetNSamples ( altroif.GetNumberOfSamples() );

}

void ReadoutRegisters_t::SetRcuRDOMOD ( RcuRDOMOD_t rdomod )
{
    fRcuRDOMOD = rdomod;
    
    fAltroDPCFG2.SetMEBMode ( rdomod.GetMEBMode() );
}

void ReadoutRegisters_t::SetRcuALTROCFG ( RcuALTROCFG1_t altrocfg1, RcuALTROCFG2_t altrocfg2 )
{
    fRcuALTROCFG1 = altrocfg1;

    fAltroZSTHR.SetThreshold ( altrocfg1.GetThreshold() );
    fAltroZSTHR.SetOffset ( altrocfg1.GetOffset() );

    fAltroDPCFG.SetZeroSuppressed ( altrocfg1.IsZeroSuppressionEnabled() );
    //fAltroDPCFG.SetFirstBaselineCorrectionMode( altrocfg2.GetBaselineSubtractionMode() );
    fAltroDPCFG.SetAutomaticBaselineSubtraction ( altrocfg1.UsingAutomaticBaselineSubtraction() );
    fAltroDPCFG.SetFixedBaselineSubtraction(!altrocfg1.IsZeroSuppressionEnabled() || (altrocfg1.IsZeroSuppressionEnabled() && !altrocfg1.UsingAutomaticBaselineSubtraction()));
    //    fAltroDPCFG.SetFixedBaselineSubtraction(
    fRcuALTROCFG2 = altrocfg2;

    fAltroDPCFG2.SetNPreSamples ( altrocfg2.GetNPreSamples() );

}

void ReadoutRegisters_t::Print ( std::ostream& stream, std::string level )
{
    stream << "ReadoutRegisters_t: " << std::endl;
    stream << "-------------------" << std::endl;
    stream << "RCU Registers: " << std::endl;
    fRcuALTROIF.Print ( stream, level );
    fRcuRDOMOD.Print ( stream, level );
    fRcuALTROCFG1.Print ( stream, level );
    fRcuALTROCFG2.Print ( stream, level );
    fRcuL1LAT.Print ( stream, level );
    fRcuL1MSGLAT.Print ( stream, level );
    stream << "-------------------" << std::endl;
    stream << "ALTRO Registers:" << std::endl;
    fAltroZSTHR.Print ( stream, level );
    fAltroTRCFG.Print ( stream, level );
    fAltroDPCFG.Print ( stream, level );
    fAltroDPCFG2.Print ( stream, level );
}

RcuALTROIF_t::RcuALTROIF_t() :
        fNSamples ( 81 ),
        fSampleFreq ( 10000000 ),
        fCstbDelay ( 2 ),
        fInstructionErrorCheck ( 0 )
{

}

RcuALTROIF_t::RcuALTROIF_t ( short nSamples, int sampleFreq, short cstbDelay, short instructionErrorCheck ) :
        fNSamples ( nSamples ),
        fSampleFreq ( sampleFreq ),
        fCstbDelay ( cstbDelay ),
        fInstructionErrorCheck ( instructionErrorCheck )
{

}

int RcuALTROIF_t::GetRegisterValue()
{
    int sampleSetting = -1;

    switch ( fSampleFreq )
    {
    case 20000000:
        sampleSetting = 0x0;
        break;
    case 10000000:
        sampleSetting = 0x1;
        break;
    case 5000000:
        sampleSetting = 0x2;
        break;
    case 2500000:
        sampleSetting = 0x3;
        break;
    default:
        return 0;
    }

    return ( fInstructionErrorCheck & 0x3 ) << 16 |
           ( fCstbDelay & 0x3 ) << 14 |
           ( sampleSetting & 0xf ) << 10 |
           (fNSamples & 0x3ff);
}

void RcuALTROIF_t::SetByRegisterValue ( int value )
{
    fNSamples = value & 0x3ff;
    int samplesetting = ( value >> 10 ) & 0x3;
    fCstbDelay = ( value >> 14 ) & 0x3;
    fInstructionErrorCheck = ( value >> 16 ) & 0x3;

    switch ( samplesetting )
    {
    case 0x0:
        fSampleFreq = 20000000;
        break;
    case 0x1:
        fSampleFreq = 10000000;
        break;
    case 0x2:
        fSampleFreq = 5000000;
        break;
    case 0x3:
        fSampleFreq = 2500000;
        break;
    default:
        fSampleFreq = 10000000;
        break;
    }

}

void RcuALTROIF_t::Print ( std::ostream& stream, std::string level )
{
    stream << "ALTROIF   : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t # samples\t: " << GetNumberOfSamples() << std::endl
        << "\t Sample freq\t: " << GetSampleFrequency() << std::endl
        << "\t Cstb delay\t: " << GetCstbDelay() << std::endl
        << "\t Inst. check\t: " << InstructionErrorCheck() << std::endl;
    }
}

RcuTRGCONF_t::RcuTRGCONF_t() :
        fSoftwareTrigger ( false ),
        fAuxTrigger ( false ),
        fTTCrxTrigger ( false ),
        fPHOSTriggerMode ( true ),
        fL2LatencyWrtL1 ( 0xfff ),
        fRegisterValue(0)
{

}

RcuTRGCONF_t::RcuTRGCONF_t ( bool softwareTrigger, bool auxTrigger, bool ttcrxTrigger, bool phosTriggerMode, short latency ) :
        fSoftwareTrigger ( softwareTrigger ),
        fAuxTrigger ( auxTrigger ),
        fTTCrxTrigger ( ttcrxTrigger ),
        fPHOSTriggerMode ( phosTriggerMode ),
        fL2LatencyWrtL1 ( latency ),
        fRegisterValue(0)
{

}

int RcuTRGCONF_t::GetRegisterValue()
{
    short triggerSource = 0;
    if ( fSoftwareTrigger )
    {
        if ( fAuxTrigger ) return 0;
        if ( fTTCrxTrigger ) return 0;
        triggerSource = 0x1;
    }
    else if ( fAuxTrigger )
    {
        if ( fTTCrxTrigger ) return 0;
        triggerSource = 0x2;
    }
    else if ( fTTCrxTrigger )
    {
        triggerSource = 0x4;
    }

    return ( triggerSource & 0x7 ) << 14 |
           ( fPHOSTriggerMode & 0x1 ) << 13 |
           (fL2LatencyWrtL1 & 0xfff);

}

void RcuTRGCONF_t::SetByRegisterValue ( int value )
{
    short triggerSource = value >> 14 & 0x3;
    fPHOSTriggerMode = value >> 13 & 0x1;
    fL2LatencyWrtL1 = value & 0xfff;

    switch ( triggerSource )
    {
    case 1:
        DisableAllTriggers();
        fSoftwareTrigger = true;
        break;
    case 2:
        DisableAllTriggers();
        fAuxTrigger = true;
        break;
    case 4:
        DisableAllTriggers();
        fTTCrxTrigger = true;
        break;
    default:
        DisableAllTriggers();
        break;
    }
}

void RcuTRGCONF_t::Print ( std::ostream& stream, std::string level )
{
    stream << "TRGCONF   : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t SW trigger\t: " << IsSoftwareTriggerEnabled() << std::endl
        << "\t Aux trigger\t: " << IsAuxTriggerEnabled() << std::endl
        << "\t TTC trigger\t: " << IsTTCrxTriggerEnabled() << std::endl
        << "\t PHOS mode\t: " << IsPHOSTriggerMode() << std::endl
        << "\t L2-L1 lat.\t: " << GetL2LatencyWrtL1() << std::endl;
    }
}

RcuRDOMOD_t::RcuRDOMOD_t() :
        fMaskRDYRX ( false ),
        fSparseReadout ( false ),
        fSparseReadoutRcu( false),
        fExecuteSequencer ( false ),
        fMEBMode ( false ),
        fRegisterValue(0)
{

}

RcuRDOMOD_t::RcuRDOMOD_t ( bool maskRDYRX, bool sparseReadoutEnabled, bool sparseReadoutRcuEnabled, bool executeSequencer, bool mebMode ) :
        fMaskRDYRX ( maskRDYRX ),
        fSparseReadout ( sparseReadoutEnabled ),
        fSparseReadoutRcu( sparseReadoutRcuEnabled),
        fExecuteSequencer ( executeSequencer ),
        fMEBMode ( mebMode ),
        fRegisterValue(0)
{
}

int RcuRDOMOD_t::GetRegisterValue()
{
   
   if(fSparseReadout && fSparseReadoutRcu)
   {
      return 0;
   }
    return fMaskRDYRX << 3 |
           fSparseReadoutRcu << 6 |
           fSparseReadout << 2 |
           fExecuteSequencer << 1 |
           fMEBMode;
}

void RcuRDOMOD_t::SetByRegisterValue ( int value )
{
    fMaskRDYRX = ( value >> 3 ) & 0x1;
    fSparseReadout = (value >> 2) & 0x1;
    fSparseReadoutRcu = ( value >> 6 ) & 0x1;
    fExecuteSequencer = ( value >> 1 ) & 0x1;
    fMEBMode = value & 0x1;
}

void RcuRDOMOD_t::Print ( std::ostream& stream, std::string level )
{
    stream << "RDOMOD    : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Mask RDYRX\t: " << IsMaskRDYRXEnabled() << std::endl
        << "\t Sparse rdo\t: " << IsSparseReadoutEnabled() << std::endl
        << "\t Sparse rdo RCU: " << IsSparseReadoutRcuEnabled() << std::endl
        << "\t Exec seq.\t: " << IsExecuteSequencerEnabled() << std::endl
        << "\t MEB mode\t: " << GetMEBMode() << std::endl;
    }
}

RcuALTROCFG1_t::RcuALTROCFG1_t() :
        fZeroSuppressionEnabled ( false ),
        fAutomaticBaselineSubtraction ( false ),
        fOffset ( 0 ),
        fThreshold ( 0 ),
        fRegisterValue(0)
{
}

RcuALTROCFG1_t::RcuALTROCFG1_t ( bool zsEnabled, bool automaticBS, short offset, short zsThreshold ) :
        fZeroSuppressionEnabled ( zsEnabled ),
        fAutomaticBaselineSubtraction ( automaticBS ),
        fOffset ( offset ),
        fThreshold ( zsThreshold )
	,fRegisterValue(0)
{

}

int RcuALTROCFG1_t::GetRegisterValue()
{
    return ( fZeroSuppressionEnabled & 0x1 ) << 15 |
           ( fAutomaticBaselineSubtraction & 0x1 ) << 14 |
           ( fOffset & 0xf ) << 10 |
           (fThreshold & 0x3ff);
}

void RcuALTROCFG1_t::SetByRegisterValue ( int value )
{
    fZeroSuppressionEnabled = ( value >> 15 ) & 0x1;
    fAutomaticBaselineSubtraction = ( value >> 14 ) & 0x1;
    fOffset = ( value >> 10 ) & 0xf;
    fThreshold = value & 0x3ff;
}

void RcuALTROCFG1_t::Print ( std::ostream& stream, std::string level )
{
    stream << "ALTROCFG1 : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Zero suppr.\t: " << IsZeroSuppressionEnabled() << std::endl
        << "\t Auto BS\t: " << UsingAutomaticBaselineSubtraction() << std::endl
        << "\t Offset\t: " << GetOffset() << std::endl
        << "\t Threshold\t: " << GetThreshold() << std::endl;
    }
}

RcuALTROCFG2_t::RcuALTROCFG2_t ( short nAltroBuffers, short nPreSamples, short nSamples, bool sparseReadout, int sampleFreq) :
        fNAltroBuffers(4)
        ,fNPreSamples(nPreSamples)
        ,fNSamples(nSamples)
        ,fSparseReadout(sparseReadout)
        ,fSampleFreq(10000000)
{
      SetNAltroBuffers(nAltroBuffers);
    SetSampleFrequency(sampleFreq);

}
int RcuALTROCFG2_t::GetRegisterValue()
{
    int sampleSetting = 0x1;

    switch ( fSampleFreq )
    {
    case 20000000:
        sampleSetting = 0x0;
        break;
    case 10000000:
        sampleSetting = 0x1;
        break;
    case 5000000:
        sampleSetting = 0x2;
        break;
    case 2500000:
        sampleSetting = 0x3;
        break;
    default:
      break;
    }
   
    return ((fNAltroBuffers == 4 ? 0 : 1) & 0x1) << 24 |
		     (fNPreSamples & 0xf) << 20 |
		     (fNSamples & 0x3ff) << 10 |
		     (fSparseReadout & 0x1) << 9 |
		     (sampleSetting & 0xf) << 5 ;
}

void RcuALTROCFG2_t::SetNAltroBuffers(short int nAltroBuffers)
{
    if (nAltroBuffers == 4 || nAltroBuffers == 8)
    {
        fNAltroBuffers = nAltroBuffers;
    }
    else
    {
        std::cout << "ERROR: Number of ALTRO buffers can only be 4 or 8, setting value to 4." << std::endl;
        fNAltroBuffers = 4;
    }
}
void RcuALTROCFG2_t::SetSampleFrequency(int sampleFreq)
{
    if (sampleFreq == 20000000 || sampleFreq == 10000000 || sampleFreq == 5000000 || sampleFreq == 2500000)
    {
        fSampleFreq = sampleFreq;
    }
    else
    {
        std::cout << "ERROR: Sampling frequency can only be 20 MHz, 10 MHz, 5 MHz or 2.5 MHz (please pass value in Hz)" << std::endl;
    }
}

void RcuALTROCFG2_t::SetByRegisterValue ( int value )
{
    fNAltroBuffers =  ((value >> 24 ) & 0x1) == 0 ? 4 : 8;
    fNPreSamples = (value >> 20) & 0xf;
    fNSamples = (value >> 10) & 0x3ff;
    fSparseReadout = (value >> 9) & 0x1;
    int samplesetting  = (value >> 5)  & 0xf;
    
     switch ( samplesetting )
    {
    case 0x0:
        fSampleFreq = 20000000;
        break;
    case 0x1:
        fSampleFreq = 10000000;
        break;
    case 0x2:
        fSampleFreq = 5000000;
        break;
    case 0x3:
        fSampleFreq = 2500000;
        break;
    default:
        fSampleFreq = 10000000;
        break;
    }
}

void RcuALTROCFG2_t::Print ( std::ostream& stream, std::string level )
{
    stream << "ALTROCFG2 : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
       stream << "\t # ALTRO buff\t: " << GetNAltroBuffers() << std::endl;
        stream << "\t Pre Samples\t: " << GetNPreSamples() << std::endl;
	stream << "\t Sparse RO\t: " << IsSparseReadoutEnabled() << std::endl;
	stream << "\t Sample freq\t: " << GetSampleFrequency() << std::endl;
    }
}

int AltroZSTHR_t::GetRegisterValue() const
{
    return ( fOffset << 10 ) | fThreshold;
}

void AltroZSTHR_t::SetByRegisterValue ( int value )
{
    fThreshold = value & 0x3ff;
    fOffset = ( value >> 10 ) & 0x3ff;
}

void AltroZSTHR_t::Print ( std::ostream& stream, std::string level )
{
    stream << "ZSTHR     : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Threshold\t: " << GetThreshold() << std::endl
        << "\t Offset\t: " << GetOffset() << std::endl;
    }
}

int AltroTRCFG_t::GetRegisterValue() const
{
    return ( fStart << 10 ) | fStop;
}

void AltroTRCFG_t::SetByRegisterValue ( int value )
{
    fStart = ( value >> 10 ) & 0x3ff;
    fStop = ( value & 0x3ff );
}

void AltroTRCFG_t::Print ( std::ostream& stream, std::string level )
{
    stream << "TRCFG     : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Start\t: " << GetStart() << std::endl
        << "\t Stop\t: " << GetStop() << std::endl
        << "\t # samples\t: " << GetNSamples() << std::dec << std::endl;
    }
}

int AltroDPCFG_t::GetRegisterValue() const
{

    return fFirstBaselineCorrection |
           ( fPolarity << 4 ) |
           ( fPreExcluded2 << 5 ) |
           ( fPostExcluded2 << 7 ) |
           ( fSecondBaselineCorrection << 11 ) |
           ( fGlitchFilterConfig << 12 ) |
           ( fPostExcludedZS << 14 ) |
           ( fPreExcludedZS << 17 ) |
           ( fZeroSuppression << 19 );

}

void AltroDPCFG_t::SetByRegisterValue ( int value )
{
    fFirstBaselineCorrection = value & 0xf;
    fPolarity = ( value >> 4 ) & 0x1;
    fPreExcluded2 = ( value >> 5 ) & 0x3;
    fPostExcluded2 = ( value >> 7 ) & 0xf;
    fSecondBaselineCorrection = ( value >> 11 ) & 0x1;
    fGlitchFilterConfig = ( value >> 12 ) & 0x3;
    fPostExcludedZS = ( value >> 14 ) & 0x7;
    fPreExcludedZS = ( value >> 17 ) & 0x3;
    fZeroSuppression = ( value >> 19 ) & 0x1;
}

void AltroDPCFG_t::Print ( std::ostream& stream, std::string level )
{
    stream << "DPCFG     : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Zero suppr\t: " << IsZeroSuppressed() << std::endl
        << "\t Auto BS\t: " << IsAutomaticBaselineSubtracted() << std::endl
        << "\t Fixed BS\t: " << IsFixedBaselineSubtracted() << std::endl;
    }
}

short AltroDPCFG2_t::GetRegisterValue() const
{
    return fNPreTriggerSamples |
           fMEBMode << 4 |
           fDigitalFilterEnabled << 5 |
           fPowerSaveEnabled << 6;
}

void AltroDPCFG2_t::SetByRegisterValue ( int value )
{
    fNPreTriggerSamples = value & 0xf;
    fMEBMode = ( value >> 4 ) & 0x1;
    fDigitalFilterEnabled = ( value >> 5 ) & 0x1;
    fPowerSaveEnabled = ( value >> 6 ) & 0x1;
}

void AltroDPCFG2_t::Print ( std::ostream& stream, std::string level )
{
    stream << "DPCFG2     : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t # Pre sampl.\t: " << GetNPreSamples() << std::endl
        << "\t MEB mode\t: " << GetMEBMode() << std::endl
        << "\t Digital filter\t: " << IsFilterEnabled() << std::endl
        << "\t Power save\t: " << IsPowerSaveEnabled() << std::endl;
    }
}


void RcuL1LAT_t::SetByRegisterValue ( int value )
{
    fLatency = value & 0xfff;
    fUncertainty = ( value >> 12 ) & 0xf;
}

void RcuL1LAT_t::Print ( std::ostream& stream, std::string level )
{
    stream << "L1_LATENCY     : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Latency (BC)\t: " << GetLatency() << std::endl
        << "\t Uncertainty (BC)\t: " << GetUncertainty() << std::endl;
    }
}

void RcuL1MSGLAT_t::SetByRegisterValue ( int value )
{
    fMinLatency = ( value >> 16 ) & 0xfff;
    fMaxLatency = value & 0xffff;
}

void RcuL1MSGLAT_t::Print ( std::ostream& stream, std::string level )
{
    stream << "L1_MSG_LATENCY    : 0x" << std::hex << GetRegisterValue() << std::dec << std::endl;
    if ( level == std::string ( "V" ) )
    {
        stream << "\t Min. latency (BC)\t: " << GetMinLatency() << std::endl
        << "\t Max. latency (BC)\t: " << GetMaxLatency() << std::endl;
    }
}

