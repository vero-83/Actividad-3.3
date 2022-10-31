#ifndef _FLUX_FUNCTIONS
#define _FLUX_FUNCTIONS

#include "DataStructs.h"

// base class for flux functions
class FluxFunction
{
  public:
    FluxFunction();

    // in U; out F
    virtual void computeFlux(DataStruct &U, DataStruct &F) = 0;

    // same as above but at the node level
    virtual FLOATTYPE computeFlux(const FLOATTYPE &Ui) = 0;
};

class LinearFlux : public FluxFunction
{
  private:
    FLOATTYPE c;

  public:
    LinearFlux();

    // in U; out F
    virtual void computeFlux(DataStruct &U, DataStruct &F);

    // same as above but at the node level
    virtual FLOATTYPE computeFlux(const FLOATTYPE &Ui);
};

#endif // _FLUX_FUNCTIONS