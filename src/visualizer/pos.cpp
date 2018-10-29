#include "pos.h"
#include "mem.h"
using namespace smashpp;

HEADERS* CreateHeaders(void){
  HEADERS* Heads = (HEADERS*) Calloc(1, sizeof(HEADERS));
  Heads->iPos    = 0;
  Heads->Pos     = (POS*) Calloc(1, sizeof(POS));
  return Heads;
}

void UpdateHeaders(HEADERS* Heads){
  Heads->iPos++;
  Heads->Pos = (POS*) Realloc(Heads->Pos, (Heads->iPos+1) * sizeof(POS));
}

void RemoveHeaders(HEADERS* Headers){
  for(u64 n=0 ; n < Headers->iPos ; ++n)
    Free(Headers->Pos);
  Free(Headers);
}