#include "FluxFunctions.h"

FluxFunction::FluxFunction()
{
  
};

LinearFlux::LinearFlux()
{
  c = 1.;
};

void LinearFlux::computeFlux(DataStruct &U, DataStruct &F)
{
  FLOATTYPE *dataU = U.getData();
  FLOATTYPE *dataF = F.getData();

  for(int n = 0; n < U.getSize(); n++)
  {
    dataF[n] = c * dataU[n];
  };
};

FLOATTYPE LinearFlux::computeFlux(const FLOATTYPE &Ui)
{
  return c * Ui;
};