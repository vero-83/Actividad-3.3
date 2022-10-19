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
  double *dataU = U.getData();
  double *dataF = F.getData();

  for(int n = 0; n < U.getSize(); n++)
  {
    dataF[n] = c * dataU[n];
  };
};

double LinearFlux::computeFlux(const double &Ui)
{
  return c * Ui;
};