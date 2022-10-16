#ifndef _FLUX_FUNCTIONS
#define _FLUX_FUNCTIONS

#include "DataStructs.h"

// base class for flux functions
class FluxFunction
{
  public:
    FluxFunction();

    virtual void computeFlux(DataStruct &U, DataStruct &F) = 0;
};

class LinearFlux : public FluxFunction
{
  private:
    double c;

  public:
    LinearFlux();

    virtual void computeFlux(DataStruct &U, DataStruct &F);
};

#endif // _FLUX_FUNCTIONS