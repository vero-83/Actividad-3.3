#include "rk4.h"

RungeKutta4::RungeKutta4(DataStruct &_Un, FluxFunction &_F):
Un(_Un),
flux(_F)
{
  nSteps = 4;
  currentStep = 0;

  f1 = DataStruct(Un.getSize());
  f2 = DataStruct(Un.getSize());
  f3 = DataStruct(Un.getSize());
  f4 = DataStruct(Un.getSize());
};

RungeKutta4::~RungeKutta4()
{
  
};

int RungeKutta4::getNumSteps()
{
  return nSteps;
};