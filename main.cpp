#include <iostream> // std::cout
#include <fstream> // ofile
#include <string>
#include <math.h>

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

  // Output Initial Condition
  write2File(xj, u, "initialCondition.csv");

  std::cout << u.getSize() <<std::endl;
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