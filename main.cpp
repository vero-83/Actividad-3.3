#include <iostream> // std::cout
#include <fstream> // ofile
#include <string>
#include <math.h>
#include <iostream>
#include <iomanip> // set precision
#include <mpi.h>

#include "DataStructs.h"
#include "rk4.h"
#include "FluxFunctions.h"
#include "RHSoperator.h"

// declare supporting functions
void write2File(DataStruct &X, DataStruct &U, std::string name);
double calcL2norm(DataStruct &u, DataStruct &uinit);


int main(int narg, char **argv)
{
  int numPoints =  80;

  if(narg != 2)
  {
    std::cout<< "Wrong number of arguments. You should include:" << std::endl;
    std::cout<< "    Num points" << std::endl;
    return 1;
  }else
  {
    numPoints = std::stoi(argv[1]);
  }

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
    dataU[j] = sin(2*2. * M_PI * datax[j]);
  }

  DataStruct Uinit;
  Uinit = u;

  // Operator
  Central1D rhs(u,xj,lf);

  double CFL = 2.4;
  double dt = CFL*datax[1];

  // Output Initial Condition
  write2File(xj, u, "initialCondition.csv");

  double t_final = 5.;
  double time = 0.;
  DataStruct Ui(u.getSize()); // temp. data

  // init timer
  double compTime = MPI_Wtime();

  // main loop
  while(time < t_final)
  {
    if(time+dt >= t_final) dt = t_final - time;

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

  // finishe timer
  compTime = MPI_Wtime() - compTime;

  write2File(xj, u, "final.csv");

  // L2 norm
  double err = calcL2norm(Uinit, u);
  std::cout << std::setprecision(4) << "Comp. time: " << compTime << " sec. Error: " << err << std::endl;

  return 0;
}


// ==================================================================
// AUXILIARY FUNCTIONS
// ==================================================================
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

double calcL2norm(DataStruct &u, DataStruct &uinit)
{
  double err = 0.;
  const double *dataU = u.getData();
  const double *dataInit = uinit.getData();

  for(int n = 0; n < u.getSize(); n++)
  {
    err += (dataU[n] - dataInit[n])*(dataU[n] - dataInit[n]);
  }

  return sqrt( err );
}