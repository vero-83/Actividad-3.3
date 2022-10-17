#include "rk4.h"
#include <cassert>

RungeKutta4::RungeKutta4(DataStruct &_Un):
Un(_Un)
{
  nSteps = 4;
  currentStep = 0;

  coeffsA = new double[4];
  coeffsB = new double[4];
  coeffsA[0] = 0.;
  coeffsA[1] = 0.5;
  coeffsA[2] = 0.5;
  coeffsA[3] = 1.;
  coeffsB[0] = 1.;
  coeffsB[1] = 2.;
  coeffsB[2] = 2.;
  coeffsB[3] = 1.;

  fi = new DataStruct[4];

  fi[0] = DataStruct(Un.getSize());
  fi[1] = DataStruct(Un.getSize());
  fi[2] = DataStruct(Un.getSize());
  fi[3] = DataStruct(Un.getSize());
};

RungeKutta4::~RungeKutta4()
{
  delete[] fi, coeffsA, coeffsB;
};

int RungeKutta4::getNumSteps()
{
  return nSteps;
};

void RungeKutta4::initRK()
{
  currentStep = 0;
};

void RungeKutta4::stepUi(double dt)
{
  assert(currentStep != nSteps-1);

  if(currentStep == 0)
  {
    double *dataUi = Ui.getData();
    const double *dataU  = Un.getData();

    for(int n = 0; n < Ui.getSize(); n++)
    {
      dataUi[n] = dataU[n];
    }
  }
  else
  {
    double *datafi = fi[currentStep-1].getData();
    double *dataUi = Ui.getData();
    const double *dataU  = Un.getData();

    for(int n = 0; n < Ui.getSize(); n++)
    {
      dataUi[n] = dataU[n] + coeffsA[currentStep]*dt* datafi[n];
    }
  }
};

void RungeKutta4::setFi(DataStruct &_F)
{
  double *dataFi = fi[currentStep].getData();
  double *dataF  = _F.getData();

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