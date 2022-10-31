#include "rk4.h"
#include <cassert>

RungeKutta4::RungeKutta4(DataStruct &_Un):
Un(_Un)
{
  nSteps = 4;
  currentStep = 0;

  coeffsA = new FLOATTYPE[4];
  coeffsB = new FLOATTYPE[4];
  coeffsA[0] = 0.;
  coeffsA[1] = 0.5;
  coeffsA[2] = 0.5;
  coeffsA[3] = 1.;
  coeffsB[0] = 1.;
  coeffsB[1] = 2.;
  coeffsB[2] = 2.;
  coeffsB[3] = 1.;

  fi = new DataStruct[nSteps];

  fi[0].setSize(Un.getSize());
  fi[1].setSize(Un.getSize());
  fi[2].setSize(Un.getSize());
  fi[3].setSize(Un.getSize());

  Ui.setSize(Un.getSize());
};

RungeKutta4::~RungeKutta4()
{
  delete[] fi;
  delete[] coeffsA;
  delete[] coeffsB;
};

int RungeKutta4::getNumSteps()
{
  return nSteps;
};

void RungeKutta4::initRK()
{
  currentStep = 0;
};

void RungeKutta4::stepUi(FLOATTYPE dt)
{
  assert(currentStep < nSteps);

  if(currentStep == 0)
  {
    FLOATTYPE *dataUi = Ui.getData();
    const FLOATTYPE *dataU  = Un.getData();

    for(int n = 0; n < Ui.getSize(); n++)
    {
      dataUi[n] = dataU[n];
    }
  }
  else
  {
    FLOATTYPE *datafi = fi[currentStep-1].getData();
    FLOATTYPE *dataUi = Ui.getData();
    const FLOATTYPE *dataU  = Un.getData();

    for(int n = 0; n < Ui.getSize(); n++)
    {
      dataUi[n] = dataU[n] + coeffsA[currentStep]*dt* datafi[n];
    }
  }
};

void RungeKutta4::finalizeRK(const FLOATTYPE dt)
{
  FLOATTYPE *dataUn = Un.getData();
  FLOATTYPE *dataUi = Ui.getData();

  // set Ui to 0
  for(int n = 0; n < Ui.getSize(); n++)
  {
    dataUi[n] = 0.;
  }
  
  for(int s = 0; s < nSteps; s++)
  {
    const FLOATTYPE *dataFi = fi[s].getData();
    const FLOATTYPE b = coeffsB[s];

    for(int n = 0; n < Ui.getSize(); n++)
    {
      dataUi[n] += b * dataFi[n];
    }
  }

  const FLOATTYPE oneDiv6 = 1. / 6.;
  for(int n = 0; n < Ui.getSize(); n++)
  {
    dataUn[n] += dt * oneDiv6 * dataUi[n];
  }
};

void RungeKutta4::setFi(DataStruct &_F)
{
  FLOATTYPE *dataFi = fi[currentStep].getData();
  const FLOATTYPE *dataF  = _F.getData();

  for(int n = 0; n < Ui.getSize(); n++)
  {
    dataFi[n] = dataF[n];
  }

  currentStep++;
};

DataStruct * RungeKutta4::currentU()
{
  return &Ui;
};