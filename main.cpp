#include <iostream> // std::cout
#include <fstream> // ofile
#include <string>
#include <math.h>
#include <iostream>

#include "DataStructs.h"
#include "rk4.h"
#include "FluxFunctions.h"
#include "RHSoperator.h"

void write2File(DataStruct &X, DataStruct &U, std::string name);

int main()
{
  int numPoints =  40;
  // solution data
  DataStruct u(numPoints), f(numPoints), xj(numPoints);

  // flux function
  LinearFlux lf;

  // time solver
  RungeKutta4 rk(u);

  // Initial Condition
  double *datax = xj.getData();
  double *dataU = u.getData();
  for(int j = 0; j < numPoints; j++)
  {
    // xj
    datax[j] = double(j)/double(numPoints-1);

    // init Uj
    dataU[j] = sin(2. * M_PI * datax[j]);
  }

  // Operator
  Central1D rhs(u,xj,lf);

  double CFL = .1;
  const double dt = CFL*datax[1];

  // Output Initial Condition
  write2File(xj, u, "initialCondition.csv");

  double t_final = .5;
  double time = 0.;
  DataStruct Ui(u.getSize()); // temp. data
  while(time < t_final)
  {

    // take RK step
    rk.initRK();
    for(int s = 0; s < rk.getNumSteps(); s++)
    {
      rk.stepUi(dt);
      Ui = *rk.currentU();
      rhs.eval(Ui);
      rk.setFi(rhs.ref2RHS());
    }
    rk.finalizeRK(dt);
    time += dt;
  }

  write2File(xj, u, "final.csv");

  return 0;
}


void write2File(DataStruct &X, DataStruct &U, std::string name)
{
  std::ofstream file;
  file.open(name,std::ios_base::trunc);
  if(!file.is_open()) 
  {
    std::cout << "Couldn't open file for Initial Condition" << std::endl;
    exit(1);
  }
  
  for(int j = 0; j < U.getSize(); j++)
  {
    file << X.getData()[j] << " ," << U.getData()[j] << std::endl;
  }

  file.close();
}