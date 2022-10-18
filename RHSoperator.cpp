#include "RHSoperator.h"

Operator::Operator()
{

}


Operator::~Operator()
{

}


Central1D::Central1D(DataStruct &_U, 
                     DataStruct &_mesh, 
                     FluxFunction &_F):
U(_U), mesh(_mesh), F(_F)
{
  RHS = DataStruct(_U.getSize());
}

Central1D::~Central1D()
{

}

void Central1D::eval()
{
  // the BC should be included in the mesh
  // momentarily done here by hand
  double *dataRHS = RHS.getData();
  const double *dataU = U.getData();
  
}