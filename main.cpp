#include <iostream>

#include "DataStructs.h"
#include "rk4.h"
#include "FluxFunctions.h"

int main()
{

  // solution data
  DataStruct u(40);

  // flux function
  LinearFlux lf;

  // time solver
  RungeKutta4 rk(u);
  
  std::cout << u.getSize() <<std::endl;
  return 0;
}