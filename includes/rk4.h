#ifndef _RUNGE_KUTTA
#define _RUNGE_KUTTA

#include "DataStructs.h"
#include "FluxFunctions.h"

class RungeKutta4 
{
  private:
    int nSteps;
    int currentStep;

    // reference to solution (Un)
    DataStruct &Un;

    // intermediate solution
    DataStruct Ui;

    // flux solutions
    DataStruct f1, f2, f3, f4;

    // reference to flux class
    FluxFunction &flux;

  public:

    // default constructor
    RungeKutta4(DataStruct &_Un, FluxFunction &_F);

    // default destructor
    ~RungeKutta4();

    int getNumSteps();
};

#endif // _RUNGE_KUTTA 