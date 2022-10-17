#ifndef _RUNGE_KUTTA
#define _RUNGE_KUTTA

#include "DataStructs.h"
#include "FluxFunctions.h"

class RungeKutta4 
{
  private:
    int nSteps;
    int currentStep;

    double *coeffsA, *coeffsB;

    // reference to solution (Un)
    DataStruct &Un;

    // intermediate solution
    DataStruct Ui;

    // flux solutions
    DataStruct *fi;

  public:

    // default constructor
    RungeKutta4(DataStruct &_Un);

    // default destructor
    ~RungeKutta4();

    int getNumSteps();

    void initRK();
    /*
    For the step to work properly, the user must provide the appropriate F for the current Ui.
    This is done this way becase the user might want to modify the Ui or Fi so that 
    Boundary conditions can be imposed
    */
   void stepUi(double dt);
   void setFi(DataStruct &_F);

   // current Ui
   DataStruct* currentU();
};

#endif // _RUNGE_KUTTA 