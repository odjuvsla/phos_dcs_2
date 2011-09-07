
#include "../phosdcsclient.h"
#include "phosdcstypes.h"

int main()
{
  phosDcsClient cl;
  
  AltroCh_t ch(3, 2, 1, 0);
 
  RcuRDOMOD_t rdo;
  
  AltroZSTHR_t thr;
  
  cl.writeRcuRegister(&rdo);
  
  cl.writeFecRegister(&thr, &ch);
 
}