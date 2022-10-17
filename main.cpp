#include <iostream>

#include "DataStructs.h"
#include "rk4.h"
#include "FluxFunctions.h"

int main()
{

  DataStruct u(40);
  LinearFlux lf;

  RungeKutta4 rk(u);
  
  std::cout << u.getSize() <<std::endl;
  return 0;
}